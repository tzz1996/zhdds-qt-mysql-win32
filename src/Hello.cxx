#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <zhdds/zhdds_cpp.h>
#include "Hello.h"
#include "HelloWorld.h"
#include "HelloWorldSupport.h"
#include "HelloPublisher.h"
#include "HelloSubscriber.h"

#include "qt_mysql.h"
#include "MainWindow.h"


#define DEFAULT_DOMAIN_ID           0				// 默认域ID
#define APPLICATION_NAME            "Hello"			// 应用程序名称
#define DEFAULT_PAYLOAD             1024			// 默认负载

#define APP_MODE_UNDEFINED          0				// 未定义模式
#define APP_MODE_PUBLISHER          1				// 发布者模式
#define APP_MODE_SUBSCRIBER         2				// 订阅者模式

#define DEFAULT_TOPIC_NAME          "Hello IDL"		// 默认主题名称

#define DOMAIN_ID_MAX               250				// 默认域ID


// 命令行结构体
struct CommandLineArguments {
    DDS_Long    domainId;		// 域ID
    DDS_Long    mode;			// 模式
    DDS_Long    dataSize;		// 数据大小
    DDS_Long    sampleCount;	// 样本数量
    DDS_Long    verbose;        // 冗余程度 0=没有冗余, 1=应用冗余, 2=DDS冗余
    std::string topicName;		// 主题名称
    
	// 命令行参数初始化
    CommandLineArguments() {
        mode      = APP_MODE_UNDEFINED;
        domainId  = DEFAULT_DOMAIN_ID;
        dataSize  = DEFAULT_PAYLOAD;
        sampleCount = 0;
        verbose   = 0;
        topicName = DEFAULT_TOPIC_NAME;
    }
};



// 重载<<操作符
std::ostream &operator<<(std::ostream &os, const DDS_ProductVersion_t &arg) {
    os << (int)arg.major << '.' 
       << (int)arg.minor
       << (char)arg.release << " (build "
       << (int)arg.revision << ')';
    return os;
}


// 检查文件是否存在
static bool fileExist(const char *fileName) {
    std::ifstream stream;
    stream.open(fileName);
    if (!stream) {
        return false;
    }
    stream.close();
    return true;
}



// 启动应用程序
static bool startApplication(
                        const CommandLineArguments &arg) {
    DDS_ReturnCode_t         rc;
    DDSDomainParticipant *   participant = NULL;
    DDSTopic *               topic = NULL;
    bool                     returnValue = false;

    std::cout <<
        "# 以下输出依赖于提供的QoS策略"        << std::endl;

    if (!fileExist("USER_QOS_PROFILES.xml")) {
        char *envVal;
#if defined(ZH_WIN32) && (_MSC_VER > 1310) 
        size_t envValSize;
        _dupenv_s(&envVal, &envValSize, "ZHDDS_QOS_PROFILES"); 
#else 
        envVal = getenv("ZHDDS_QOS_PROFILES");
#endif
        if (envVal == NULL || !fileExist(envVal)) {
            std::cout << "! 警告:" << std::endl
                      << "! 默认QoS策略定义文件没有找到." 
                      << std::endl
                      << "! 应用程序将使用DDS的默认QoS." 
                      << std::endl
                      << "! 如果您想使用不同的QoS, 请确保您"
                      << "有QoS定义文件："
                      << std::endl
                      << "! (USER_QOS_PROFILES.xml)在当前目录"
                      << std::endl
                      << "! 或者是设置环境变量ZHDDS_QOS_PROFILES "
                      << std::endl
                      << "! 指出包含QoS策略的文件"
                      << std::endl;
        }
#if defined(ZH_WIN32) && (_MSC_VER > 1310) 
        if (envVal) free(envVal);
#endif
    }

    /* 如果您想自定义DDS工厂的QoS,打开下面的代码
     *
    {
        DDS_DomainParticipantFactoryQos factoryQos;
        rc = DDSDomainParticipantFactory::get_instance()->get_qos(factoryQos);
        if (rc != DDS_RETCODE_OK) { 
            std::cerr << "! 无法获取域参与者工厂的QoS: "
                      << rc << std::endl;
            goto exitFn;
        }
        
        // 在这里修改工厂的QoS
        
        rc = DDSDomainParticipantFactory::get_instance()->set_qos(factoryQos);
        if (rc != DDS_RETCODE_OK) { 
            std::cerr << "! 无法设置域参与者工厂的QoS: "
                      << rc << std::endl;
            goto exitFn;
        }
    }
    */
    
            
    /* 创建DDS域参与者
     *
     
        DDS_DomainParticipantQos myQos;
        DDSDomainParticipantFactory::get_instance()->get_default_participant_qos(
                        myQos);
        // 在这里修改参与者的QoS

        // 用'myQos'创建域参与者...
     *
     */
    if (arg.verbose) {
        std::cout << "创建域参与者..." << std::endl;
    }
    participant = DDSDomainParticipantFactory::get_instance()->
                        create_participant(
                        arg.domainId,
                        DDS_PARTICIPANT_QOS_DEFAULT,
                        NULL,   /* 监听者 */
                        DDS_STATUS_MASK_NONE);
    if (participant == NULL) {
        std::cerr << "! 无法创建DDS域参与者" << std::endl;
        goto exitFn;
    }


    // 注册类型
    if (arg.verbose) {
        std::cout << "注册类型..." << std::endl;
    }
    rc = HelloWorldTypeSupport::register_type(
                        participant, 
                        HelloWorldTypeSupport::get_type_name());
    if (rc != DDS_RETCODE_OK) {
        std::cerr << "! 无法注册"
                  << HelloWorldTypeSupport::get_type_name() 
                  << "数据类型: " 
                  << rc << std::endl;
        goto exitFn;
    }


    // 创建主题
    if (arg.verbose) {
        std::cout << "创建主题..." << std::endl;
    }
    topic = participant->create_topic(
                        arg.topicName.c_str(),
                        HelloWorldTypeSupport::get_type_name(), 
                        DDS_TOPIC_QOS_DEFAULT,
                        NULL,           /* 监听者 */
                        DDS_STATUS_MASK_NONE);
    if (topic == NULL) {
        std::cerr << "! 无法创建主题"
                  << arg.topicName
                  << std::endl;
        goto exitFn;
    }

    // 创建发布者或者是订阅者
    if (arg.mode == APP_MODE_PUBLISHER) {
        if (!startPublisher(
                        participant, 
                        topic,
                        arg.verbose,
                        arg.dataSize,
                        arg.sampleCount)) {
            goto exitFn;
        }
    } else {
        if (!startSubscriber(
                        participant, 
                        topic,
                        arg.verbose,
                        arg.sampleCount)) {
            goto exitFn;
        }
    }
    returnValue = true;
    
exitFn:
    if (arg.verbose) {
        std::cout << "清理..." << std::endl;
    }
    if (participant != NULL) {
        // 删除域参与者包含的实体
        rc = participant->delete_contained_entities();
        if (rc != DDS_RETCODE_OK) {
            std::cerr << "! 无法删除域参与者包含的实体: "
                      << rc << std::endl;
        }

		// 删除域参与者
        rc = DDSDomainParticipantFactory::get_instance()->delete_participant(
                        participant);
        if (rc != DDS_RETCODE_OK) {
            std::cerr << "! 无法删除域参与者: " << rc << std::endl;
        }
    }
    return returnValue;
}


static bool startApplication2(
                        const CommandLineArguments &arg) {
    DDS_ReturnCode_t         rc;
    DDSDomainParticipant *   participant = NULL;
    DDSTopic *               topic = NULL;
    bool                     returnValue = false;


    if (arg.verbose) {
        std::cout << "创建域参与者..." << std::endl;
    }
    participant = DDSDomainParticipantFactory::get_instance()->
                        create_participant(
                        arg.domainId,
                        DDS_PARTICIPANT_QOS_DEFAULT,
                        NULL,   /* 监听者 */
                        DDS_STATUS_MASK_NONE);
    if (participant == NULL) {
        std::cerr << "! 无法创建DDS域参与者" << std::endl;
        goto exitFn;
    }


    // 注册类型
    if (arg.verbose) {
        std::cout << "注册类型..." << std::endl;
    }
    rc = HelloWorldTypeSupport::register_type(
                        participant, 
                        HelloWorldTypeSupport::get_type_name());
    if (rc != DDS_RETCODE_OK) {
        std::cerr << "! 无法注册"
                  << HelloWorldTypeSupport::get_type_name() 
                  << "数据类型: " 
                  << rc << std::endl;
        goto exitFn;
    }


    // 创建主题
    if (arg.verbose) {
        std::cout << "创建主题..." << std::endl;
    }
    topic = participant->create_topic(
                        arg.topicName.c_str(),
                        HelloWorldTypeSupport::get_type_name(), 
                        DDS_TOPIC_QOS_DEFAULT,
                        NULL,           /* 监听者 */
                        DDS_STATUS_MASK_NONE);
    if (topic == NULL) {
        std::cerr << "! 无法创建主题"
                  << arg.topicName
                  << std::endl;
        goto exitFn;
    }

    // 创建发布者或者是订阅者
    if (arg.mode == APP_MODE_PUBLISHER) {
        if (!startPublisher(
                        participant, 
                        topic,
                        arg.verbose,
                        arg.dataSize,
                        arg.sampleCount)) {
            goto exitFn;
        }
    } else {
        if (!startSubscriber(
                        participant, 
                        topic,
                        arg.verbose,
                        arg.sampleCount)) {
            goto exitFn;
        }
    }
    returnValue = true;
    
exitFn:
    if (arg.verbose) {
        std::cout << "清理..." << std::endl;
    }
    if (participant != NULL) {
        // 删除域参与者包含的实体
        rc = participant->delete_contained_entities();
        if (rc != DDS_RETCODE_OK) {
            std::cerr << "! 无法删除域参与者包含的实体: "
                      << rc << std::endl;
        }

		// 删除域参与者
        rc = DDSDomainParticipantFactory::get_instance()->delete_participant(
                        participant);
        if (rc != DDS_RETCODE_OK) {
            std::cerr << "! 无法删除域参与者: " << rc << std::endl;
        }
    }
    return returnValue;
}


// 打印帮助信息
static void usage() {
    std::cout << "用法:" << std::endl;
    std::cout << "    " << APPLICATION_NAME 
                        << " pub [arguments]     作为发布者运行" << std::endl;
    std::cout << "    " << APPLICATION_NAME 
                        << " sub [arguments]     作为订阅者运行" << std::endl;
    std::cout << "当参数是:" << std::endl;
    std::cout << "  -h | --help                 "
              << "显示此页" << std::endl;
    std::cout << "  -v | --verbose              "
              << "增加输出冗余(可重复)" << std::endl;
    std::cout << "  -d | --domain <domainID>    "
              << "设置DDS域ID [默认=" << DEFAULT_DOMAIN_ID 
              << ']' << std::endl;
    std::cout << "  -t | --topic <name>         "
              << "设置主题名称 [默认=" << DEFAULT_TOPIC_NAME
              << ']' << std::endl;
    std::cout << "  -s | --size <num>           "
              << "设置负载大小以字节为单位 [默认=" << DEFAULT_PAYLOAD
              << ']' << std::endl;
    std::cout << "  -c | --sampleCount <num>    "
              << "设置要发送/接收的样本数量 [默认=0(无限的)"
              << ']' << std::endl;
    std::cout << std::endl;
}



// 检查是否有足够的参数
#define ENSURE_ONE_MORE_ARGUMENT(argc, argv, i, argName)                      \
    if (i+1 > argc) {                                                         \
        usage();                                                              \
        std::cerr << "! 错误: 丢失" << argName                 \
                  << "的值" << std::endl;                                \
        return EXIT_FAILURE;                                                  \
    }


// dds hello入口函数
#if 0
int main(int argc, const char **argv) {
    CommandLineArguments arg;    
    int i;

    std::cout << "Hello例子应用程序" << std::endl;

    // 确保有足够的命令行参数
    if (argc < 2) {
        usage();
        std::cerr << "! 无效的参数值." << std::endl;
        std::cerr << "! 您必须至少指定运行模式(pub/sub)" 
                  << std::endl;
        return EXIT_FAILURE;
    }

    // 解析运行模式    
    if (ZH_STRCASECMP(argv[1], "pub") == 0) {
        arg.mode = APP_MODE_PUBLISHER;
    } else if (ZH_STRCASECMP(argv[1], "sub") == 0) {
        arg.mode = APP_MODE_SUBSCRIBER;
    } else if (!ZH_STRNCMP(argv[1], "-h", 2) || 
               !ZH_STRNCMP(argv[1], "--help", 6)) {
        usage();
        return EXIT_SUCCESS;
    } else {
        usage();
        std::cerr << "! 无效的模式: '" << argv[1] << "'" << std::endl;
        std::cerr << "! 有效的模式只有'pub' or 'sub'" << std::endl;
        return EXIT_FAILURE;
    }

    // 解析选项参数
    for (i = 2; i < argc; ++i) {
        if (!ZH_STRNCMP(argv[i], "-h", 2) || 
            !ZH_STRNCMP(argv[i], "--help", 6)) {
            usage();
            return EXIT_SUCCESS;
        }
        
        if (!ZH_STRNCMP(argv[i], "-v", 2) || 
            !ZH_STRNCMP(argv[i], "--verbose", 9)) {
            ++arg.verbose;
            continue;
        }

        if (!ZH_STRNCMP(argv[i], "-d", 2) || 
            !ZH_STRNCMP(argv[i], "--domain", 8)) {
            char *ptr;
            ENSURE_ONE_MORE_ARGUMENT(argc, argv, i, "--domain")
            arg.domainId = strtol(argv[++i], &ptr, 10);
            if (*ptr != '\0') {
                usage();
                std::cerr << "! 域参数的值不是数字" 
                          << argv[i] << std::endl;
                return EXIT_FAILURE;
            }
            if (arg.domainId < 0 || arg.domainId > DOMAIN_ID_MAX) {
                usage();
                std::cerr << "! 无效的DDSID: " << arg.domainId
                          << std::endl;
                std::cerr << "! 域ID必须在0和"
                          << DOMAIN_ID_MAX << "(包括)之间" << std::endl;
                return EXIT_FAILURE;
            }
            continue;
        }

        if (!ZH_STRNCMP(argv[i], "-s", 2) || 
            !ZH_STRNCMP(argv[i], "--size", 6)) {
            char *ptr;
            ENSURE_ONE_MORE_ARGUMENT(argc, argv, i, "--size")
            arg.dataSize = strtol(argv[++i], &ptr, 10);
            if (*ptr != '\0') {
                usage();
                std::cerr << "! 无效的大小选项的值:"
                          << argv[i] << std::endl;
                return EXIT_FAILURE;
            }
            if (arg.dataSize <= 0) {
                usage();
                std::cerr << "! 无效的大小参数的值: "
                          << arg.dataSize << std::endl;
                return EXIT_FAILURE;
            }
            if (arg.dataSize >= HELLODDS_MAX_PAYLOAD_SIZE) {
                usage();
                std::cerr << "! 大小参数的值太大: "
                          << arg.dataSize << std::endl;
                std::cerr << "! 在这个例子中最大数据大小设置为: " 
                          << HELLODDS_MAX_PAYLOAD_SIZE << std::endl;
                return EXIT_FAILURE;
            }
            continue;
        }

        if (!ZH_STRNCMP(argv[i], "-t", 2) || 
            !ZH_STRNCMP(argv[i], "--topic", 7)) {
            ENSURE_ONE_MORE_ARGUMENT(argc, argv, i, "--topic")
            arg.topicName = std::string(argv[++i]);
            continue;
        }

        if (!ZH_STRNCMP(argv[i], "-c", 2) || 
            !ZH_STRNCMP(argv[i], "--sampleCount", 13)) {
            char *ptr;
            ENSURE_ONE_MORE_ARGUMENT(argc, argv, i, "--sampleCount")
            arg.sampleCount = strtol(argv[++i], &ptr, 10);
            if (*ptr != '\0') {
                usage();
                std::cerr << "! 无效的样本数量选项的值:"
                          << argv[i] << std::endl;
                return EXIT_FAILURE;
            }
            if (arg.sampleCount < 0) {
                usage();
                std::cerr << "! 无效的样本数量参数的值: "
                          << arg.dataSize << std::endl;
                return EXIT_FAILURE;
            }
            continue;
        }
        
        usage();
        std::cerr << "! 未知参数" << argv[i] << std::endl;
        return EXIT_FAILURE;
    }

    if (arg.verbose) {
        const DDS_ProductVersion_t &prodVersion = 
                        ZHDDSConfigVersion::get_instance().get_product_version();
        std::cout << "以以下参数运行:" << std::endl;
        std::cout << "    负载大小....... : " << arg.dataSize << std::endl;
        std::cout << "    样本数量....... : " << arg.sampleCount << std::endl;
        std::cout << "    域ID........... : " << arg.domainId << std::endl;
        std::cout << "    主题名称....... : " << arg.topicName << std::endl;
        std::cout << "产品版本........... : " << prodVersion << std::endl;        

    }

    if (arg.verbose > 1) {
        ZHDDSConfigLogger::get_instance()->set_verbosity_by_category(
                        ZHDDS_CONFIG_LOG_CATEGORY_API,
                        ZHDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL);
    }

 
    startApplication(arg);

 
    std::cout << "完成." << std::endl;
    return EXIT_SUCCESS;
}
#endif

// qt+mysql测试入口函数
#if 0
int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QTextEdit textEdit;
	// 设置最大显示消息数为100
	textEdit.document()->setMaximumBlockCount(100);
	textEdit.setText("tzz is here.");

	bool res = false;
	if (res == true) {
		//std::cout << "res init wrong." << std::endl;
		textEdit.append("res init wrong.");
	}
	if (!res) {
		//std::cout << "res init correct." << std::endl;
		textEdit.append("res init correct.");
	}

	// 连接mysql
	Mysql mysql;
	res = mysql.ConnectToMysql();

	if (res == true) {
		textEdit.append("connect to mysql success!");
	}
	else if (res == false) {
		textEdit.append("connect to mysql failed!");
	}

	// 显示程序框
	textEdit.show();
	// 断开mysql连接
	mysql.DisconnectToMysql();

    return app.exec();
}
#endif


// 测试
#if 0
int main(int argc, char** argv) {
	QApplication app(argc, argv);
	QTextEdit text_edit;
	QPushButton* button = new QPushButton("test");

	text_edit.setText("in main()");
	button->show();

	text_edit.show();
	print(&text_edit, button);

	return app.exec();
}
#endif

#if 1
int main(int argc, char** argv) {
	//Q_INIT_RESOURCE(application);

     QApplication app(argc, argv);
     app.setOrganizationName("Trolltech");
     app.setApplicationName("Application Example");
     MainWindow mainWin;

     mainWin.show();

     return app.exec();

}
#endif