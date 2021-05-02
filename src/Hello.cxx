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


#define DEFAULT_DOMAIN_ID           0				// Ĭ����ID
#define APPLICATION_NAME            "Hello"			// Ӧ�ó�������
#define DEFAULT_PAYLOAD             1024			// Ĭ�ϸ���

#define APP_MODE_UNDEFINED          0				// δ����ģʽ
#define APP_MODE_PUBLISHER          1				// ������ģʽ
#define APP_MODE_SUBSCRIBER         2				// ������ģʽ

#define DEFAULT_TOPIC_NAME          "Hello IDL"		// Ĭ����������

#define DOMAIN_ID_MAX               250				// Ĭ����ID


// �����нṹ��
struct CommandLineArguments {
    DDS_Long    domainId;		// ��ID
    DDS_Long    mode;			// ģʽ
    DDS_Long    dataSize;		// ���ݴ�С
    DDS_Long    sampleCount;	// ��������
    DDS_Long    verbose;        // ����̶� 0=û������, 1=Ӧ������, 2=DDS����
    std::string topicName;		// ��������
    
	// �����в�����ʼ��
    CommandLineArguments() {
        mode      = APP_MODE_UNDEFINED;
        domainId  = DEFAULT_DOMAIN_ID;
        dataSize  = DEFAULT_PAYLOAD;
        sampleCount = 0;
        verbose   = 0;
        topicName = DEFAULT_TOPIC_NAME;
    }
};



// ����<<������
std::ostream &operator<<(std::ostream &os, const DDS_ProductVersion_t &arg) {
    os << (int)arg.major << '.' 
       << (int)arg.minor
       << (char)arg.release << " (build "
       << (int)arg.revision << ')';
    return os;
}


// ����ļ��Ƿ����
static bool fileExist(const char *fileName) {
    std::ifstream stream;
    stream.open(fileName);
    if (!stream) {
        return false;
    }
    stream.close();
    return true;
}



// ����Ӧ�ó���
static bool startApplication(
                        const CommandLineArguments &arg) {
    DDS_ReturnCode_t         rc;
    DDSDomainParticipant *   participant = NULL;
    DDSTopic *               topic = NULL;
    bool                     returnValue = false;

    std::cout <<
        "# ��������������ṩ��QoS����"        << std::endl;

    if (!fileExist("USER_QOS_PROFILES.xml")) {
        char *envVal;
#if defined(ZH_WIN32) && (_MSC_VER > 1310) 
        size_t envValSize;
        _dupenv_s(&envVal, &envValSize, "ZHDDS_QOS_PROFILES"); 
#else 
        envVal = getenv("ZHDDS_QOS_PROFILES");
#endif
        if (envVal == NULL || !fileExist(envVal)) {
            std::cout << "! ����:" << std::endl
                      << "! Ĭ��QoS���Զ����ļ�û���ҵ�." 
                      << std::endl
                      << "! Ӧ�ó���ʹ��DDS��Ĭ��QoS." 
                      << std::endl
                      << "! �������ʹ�ò�ͬ��QoS, ��ȷ����"
                      << "��QoS�����ļ���"
                      << std::endl
                      << "! (USER_QOS_PROFILES.xml)�ڵ�ǰĿ¼"
                      << std::endl
                      << "! ���������û�������ZHDDS_QOS_PROFILES "
                      << std::endl
                      << "! ָ������QoS���Ե��ļ�"
                      << std::endl;
        }
#if defined(ZH_WIN32) && (_MSC_VER > 1310) 
        if (envVal) free(envVal);
#endif
    }

    /* ��������Զ���DDS������QoS,������Ĵ���
     *
    {
        DDS_DomainParticipantFactoryQos factoryQos;
        rc = DDSDomainParticipantFactory::get_instance()->get_qos(factoryQos);
        if (rc != DDS_RETCODE_OK) { 
            std::cerr << "! �޷���ȡ������߹�����QoS: "
                      << rc << std::endl;
            goto exitFn;
        }
        
        // �������޸Ĺ�����QoS
        
        rc = DDSDomainParticipantFactory::get_instance()->set_qos(factoryQos);
        if (rc != DDS_RETCODE_OK) { 
            std::cerr << "! �޷�����������߹�����QoS: "
                      << rc << std::endl;
            goto exitFn;
        }
    }
    */
    
            
    /* ����DDS�������
     *
     
        DDS_DomainParticipantQos myQos;
        DDSDomainParticipantFactory::get_instance()->get_default_participant_qos(
                        myQos);
        // �������޸Ĳ����ߵ�QoS

        // ��'myQos'�����������...
     *
     */
    if (arg.verbose) {
        std::cout << "�����������..." << std::endl;
    }
    participant = DDSDomainParticipantFactory::get_instance()->
                        create_participant(
                        arg.domainId,
                        DDS_PARTICIPANT_QOS_DEFAULT,
                        NULL,   /* ������ */
                        DDS_STATUS_MASK_NONE);
    if (participant == NULL) {
        std::cerr << "! �޷�����DDS�������" << std::endl;
        goto exitFn;
    }


    // ע������
    if (arg.verbose) {
        std::cout << "ע������..." << std::endl;
    }
    rc = HelloWorldTypeSupport::register_type(
                        participant, 
                        HelloWorldTypeSupport::get_type_name());
    if (rc != DDS_RETCODE_OK) {
        std::cerr << "! �޷�ע��"
                  << HelloWorldTypeSupport::get_type_name() 
                  << "��������: " 
                  << rc << std::endl;
        goto exitFn;
    }


    // ��������
    if (arg.verbose) {
        std::cout << "��������..." << std::endl;
    }
    topic = participant->create_topic(
                        arg.topicName.c_str(),
                        HelloWorldTypeSupport::get_type_name(), 
                        DDS_TOPIC_QOS_DEFAULT,
                        NULL,           /* ������ */
                        DDS_STATUS_MASK_NONE);
    if (topic == NULL) {
        std::cerr << "! �޷���������"
                  << arg.topicName
                  << std::endl;
        goto exitFn;
    }

    // ���������߻����Ƕ�����
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
        std::cout << "����..." << std::endl;
    }
    if (participant != NULL) {
        // ɾ��������߰�����ʵ��
        rc = participant->delete_contained_entities();
        if (rc != DDS_RETCODE_OK) {
            std::cerr << "! �޷�ɾ��������߰�����ʵ��: "
                      << rc << std::endl;
        }

		// ɾ���������
        rc = DDSDomainParticipantFactory::get_instance()->delete_participant(
                        participant);
        if (rc != DDS_RETCODE_OK) {
            std::cerr << "! �޷�ɾ���������: " << rc << std::endl;
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
        std::cout << "�����������..." << std::endl;
    }
    participant = DDSDomainParticipantFactory::get_instance()->
                        create_participant(
                        arg.domainId,
                        DDS_PARTICIPANT_QOS_DEFAULT,
                        NULL,   /* ������ */
                        DDS_STATUS_MASK_NONE);
    if (participant == NULL) {
        std::cerr << "! �޷�����DDS�������" << std::endl;
        goto exitFn;
    }


    // ע������
    if (arg.verbose) {
        std::cout << "ע������..." << std::endl;
    }
    rc = HelloWorldTypeSupport::register_type(
                        participant, 
                        HelloWorldTypeSupport::get_type_name());
    if (rc != DDS_RETCODE_OK) {
        std::cerr << "! �޷�ע��"
                  << HelloWorldTypeSupport::get_type_name() 
                  << "��������: " 
                  << rc << std::endl;
        goto exitFn;
    }


    // ��������
    if (arg.verbose) {
        std::cout << "��������..." << std::endl;
    }
    topic = participant->create_topic(
                        arg.topicName.c_str(),
                        HelloWorldTypeSupport::get_type_name(), 
                        DDS_TOPIC_QOS_DEFAULT,
                        NULL,           /* ������ */
                        DDS_STATUS_MASK_NONE);
    if (topic == NULL) {
        std::cerr << "! �޷���������"
                  << arg.topicName
                  << std::endl;
        goto exitFn;
    }

    // ���������߻����Ƕ�����
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
        std::cout << "����..." << std::endl;
    }
    if (participant != NULL) {
        // ɾ��������߰�����ʵ��
        rc = participant->delete_contained_entities();
        if (rc != DDS_RETCODE_OK) {
            std::cerr << "! �޷�ɾ��������߰�����ʵ��: "
                      << rc << std::endl;
        }

		// ɾ���������
        rc = DDSDomainParticipantFactory::get_instance()->delete_participant(
                        participant);
        if (rc != DDS_RETCODE_OK) {
            std::cerr << "! �޷�ɾ���������: " << rc << std::endl;
        }
    }
    return returnValue;
}


// ��ӡ������Ϣ
static void usage() {
    std::cout << "�÷�:" << std::endl;
    std::cout << "    " << APPLICATION_NAME 
                        << " pub [arguments]     ��Ϊ����������" << std::endl;
    std::cout << "    " << APPLICATION_NAME 
                        << " sub [arguments]     ��Ϊ����������" << std::endl;
    std::cout << "��������:" << std::endl;
    std::cout << "  -h | --help                 "
              << "��ʾ��ҳ" << std::endl;
    std::cout << "  -v | --verbose              "
              << "�����������(���ظ�)" << std::endl;
    std::cout << "  -d | --domain <domainID>    "
              << "����DDS��ID [Ĭ��=" << DEFAULT_DOMAIN_ID 
              << ']' << std::endl;
    std::cout << "  -t | --topic <name>         "
              << "������������ [Ĭ��=" << DEFAULT_TOPIC_NAME
              << ']' << std::endl;
    std::cout << "  -s | --size <num>           "
              << "���ø��ش�С���ֽ�Ϊ��λ [Ĭ��=" << DEFAULT_PAYLOAD
              << ']' << std::endl;
    std::cout << "  -c | --sampleCount <num>    "
              << "����Ҫ����/���յ��������� [Ĭ��=0(���޵�)"
              << ']' << std::endl;
    std::cout << std::endl;
}



// ����Ƿ����㹻�Ĳ���
#define ENSURE_ONE_MORE_ARGUMENT(argc, argv, i, argName)                      \
    if (i+1 > argc) {                                                         \
        usage();                                                              \
        std::cerr << "! ����: ��ʧ" << argName                 \
                  << "��ֵ" << std::endl;                                \
        return EXIT_FAILURE;                                                  \
    }


// dds hello��ں���
#if 0
int main(int argc, const char **argv) {
    CommandLineArguments arg;    
    int i;

    std::cout << "Hello����Ӧ�ó���" << std::endl;

    // ȷ�����㹻�������в���
    if (argc < 2) {
        usage();
        std::cerr << "! ��Ч�Ĳ���ֵ." << std::endl;
        std::cerr << "! ����������ָ������ģʽ(pub/sub)" 
                  << std::endl;
        return EXIT_FAILURE;
    }

    // ��������ģʽ    
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
        std::cerr << "! ��Ч��ģʽ: '" << argv[1] << "'" << std::endl;
        std::cerr << "! ��Ч��ģʽֻ��'pub' or 'sub'" << std::endl;
        return EXIT_FAILURE;
    }

    // ����ѡ�����
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
                std::cerr << "! �������ֵ��������" 
                          << argv[i] << std::endl;
                return EXIT_FAILURE;
            }
            if (arg.domainId < 0 || arg.domainId > DOMAIN_ID_MAX) {
                usage();
                std::cerr << "! ��Ч��DDSID: " << arg.domainId
                          << std::endl;
                std::cerr << "! ��ID������0��"
                          << DOMAIN_ID_MAX << "(����)֮��" << std::endl;
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
                std::cerr << "! ��Ч�Ĵ�Сѡ���ֵ:"
                          << argv[i] << std::endl;
                return EXIT_FAILURE;
            }
            if (arg.dataSize <= 0) {
                usage();
                std::cerr << "! ��Ч�Ĵ�С������ֵ: "
                          << arg.dataSize << std::endl;
                return EXIT_FAILURE;
            }
            if (arg.dataSize >= HELLODDS_MAX_PAYLOAD_SIZE) {
                usage();
                std::cerr << "! ��С������ֵ̫��: "
                          << arg.dataSize << std::endl;
                std::cerr << "! �����������������ݴ�С����Ϊ: " 
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
                std::cerr << "! ��Ч����������ѡ���ֵ:"
                          << argv[i] << std::endl;
                return EXIT_FAILURE;
            }
            if (arg.sampleCount < 0) {
                usage();
                std::cerr << "! ��Ч����������������ֵ: "
                          << arg.dataSize << std::endl;
                return EXIT_FAILURE;
            }
            continue;
        }
        
        usage();
        std::cerr << "! δ֪����" << argv[i] << std::endl;
        return EXIT_FAILURE;
    }

    if (arg.verbose) {
        const DDS_ProductVersion_t &prodVersion = 
                        ZHDDSConfigVersion::get_instance().get_product_version();
        std::cout << "�����²�������:" << std::endl;
        std::cout << "    ���ش�С....... : " << arg.dataSize << std::endl;
        std::cout << "    ��������....... : " << arg.sampleCount << std::endl;
        std::cout << "    ��ID........... : " << arg.domainId << std::endl;
        std::cout << "    ��������....... : " << arg.topicName << std::endl;
        std::cout << "��Ʒ�汾........... : " << prodVersion << std::endl;        

    }

    if (arg.verbose > 1) {
        ZHDDSConfigLogger::get_instance()->set_verbosity_by_category(
                        ZHDDS_CONFIG_LOG_CATEGORY_API,
                        ZHDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL);
    }

 
    startApplication(arg);

 
    std::cout << "���." << std::endl;
    return EXIT_SUCCESS;
}
#endif

// qt+mysql������ں���
#if 0
int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QTextEdit textEdit;
	// ���������ʾ��Ϣ��Ϊ100
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

	// ����mysql
	Mysql mysql;
	res = mysql.ConnectToMysql();

	if (res == true) {
		textEdit.append("connect to mysql success!");
	}
	else if (res == false) {
		textEdit.append("connect to mysql failed!");
	}

	// ��ʾ�����
	textEdit.show();
	// �Ͽ�mysql����
	mysql.DisconnectToMysql();

    return app.exec();
}
#endif


// ����
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