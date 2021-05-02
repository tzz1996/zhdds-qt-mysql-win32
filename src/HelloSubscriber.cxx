#include <iostream>
#include <string>
#include <iomanip>

#include <stdlib.h>
#include <time.h>

#include <errno.h>

#include "HelloSubscriber.h"
#include "MainWindow.h"

#define POLL_PERIOD_SEC         1	// 发送频率

// 求两个数的最大值
#ifndef MACRO_MAX
#define MACRO_MAX(a,b)    (((a) > (b)) ? (a) : (b))
#endif

#define ONE_MEGABYTE        (1024*1024)		// 兆字节



/*!
 * \class	HelloListener
 * \brief	Hellolistener类. 
 * \author	Zhangzf
 * \date	2013-10-11
 */
#if 0
class HelloListener: public DDSDataReaderListener {
private:
    const int _theVerbose;
    long _theLastSampleId;      
    long _thePayloadSize;       
    long _theSampleLostCount;   
    long _theSampleRcvdCount;   
    long _theSampleRcvdMax;     
	//QTextEdit _textEdit;

public:
    /*!
     * \fn	HelloListener(int verbose, int sampleCount): _theVerbose(verbose), _theLastSampleId(0),
     * 		_thePayloadSize(0), _theSampleLostCount(0), _theSampleRcvdCount(0),
     * 		_theSampleRcvdMax(sampleCount)
     * \brief	构造函数
     * \author	Zhangzf
     * \date	2013-10-11
     * \param	verbose		The verbose. 
     * \param	sampleCount	Number of samples. 
     */
    HelloListener(int verbose, int sampleCount):
        _theVerbose(verbose),
        _theLastSampleId(0),
        _thePayloadSize(0),
        _theSampleLostCount(0),
        _theSampleRcvdCount(0),
        _theSampleRcvdMax(sampleCount) {

    }
    
    /*!
     * \fn	~HelloListener()
     * \brief	析构函数
     * \author	Zhangzf
     * \date	2013-10-11
     */
    ~HelloListener() {}
    
    /*!
     * \fn	HelloListener(const HelloListener &ref): _theVerbose(ref._theVerbose),
     * 		_theLastSampleId(ref._theLastSampleId), _thePayloadSize(ref._thePayloadSize),
     * 		_theSampleLostCount(ref._theSampleLostCount),
     * 		_theSampleRcvdCount(ref._theSampleRcvdCount), _theSampleRcvdMax(ref._theSampleRcvdMax)
     * \brief	拷贝构造
     * \author	Zhangzf
     * \date	2013-10-11
     * \param	ref	The reference. 
     */
    HelloListener(const HelloListener &ref):
        _theVerbose(ref._theVerbose),
        _theLastSampleId(ref._theLastSampleId),
        _thePayloadSize(ref._thePayloadSize),
        _theSampleLostCount(ref._theSampleLostCount),
        _theSampleRcvdCount(ref._theSampleRcvdCount),
        _theSampleRcvdMax(ref._theSampleRcvdMax) {
    }

    /*!
     * \fn	HelloListener &operator=(const HelloListener &ref)
     * \brief	重载=
     * \author	Zhangzf
     * \date	2013-10-11
     * \param	ref	The reference. 
     * \return	A shallow copy of this object. 
     */
    HelloListener &operator=(const HelloListener &ref) {
        _theLastSampleId = ref._theLastSampleId;
        _thePayloadSize  = ref._thePayloadSize;
        _theSampleLostCount = ref._theSampleLostCount;
        _theSampleRcvdCount = ref._theSampleRcvdCount;
        _theSampleRcvdMax = ref._theSampleRcvdMax;
        return *this;
    }


public:
	/*QTextEdit* getQTextEdit() {
		return &_textEdit;
	}*/

    /*!
     * \fn	long getLastSampleId() const
     * \brief	获取最后样本的ID
     * \author	Zhangzf
     * \date	2013-10-11
     * \return	The last sample identifier. 
     */
    long getLastSampleId() const {
        return _theLastSampleId;
    }
    
    /*!
     * \fn	long getPayloadSize() const
     * \brief	获取负载大小
     * \author	Zhangzf
     * \date	2013-10-11
     * \return	The payload size. 
     */
    long getPayloadSize() const {
        return _thePayloadSize;
    }
    
    /*!
     * \fn	long getSampleLostCount() const
     * \brief	获取丢失的样本数量
     * \author	Zhangzf
     * \date	2013-10-11
     * \return	The sample lost count. 
     */
    long getSampleLostCount() const {
        return _theSampleLostCount;
    }

    /*!
     * \fn	long getSampleRcvdCount() const
     * \brief	获取接收的样本数量
     * \author	Zhangzf
     * \date	2013-10-11
     * \return	The sample rcvd count. 
     */
    long getSampleRcvdCount() const {
        return _theSampleRcvdCount;
    }

    /*!
     * \fn	long getSampleRcvdMax() const
     * \brief	获取接收的样本的最大值
     * \author	Zhangzf
     * \date	2013-10-11
     * \return	The sample rcvd maximum. 
     */
    long getSampleRcvdMax() const {
        return _theSampleRcvdMax;
    }
    
    

public:    
    /*!
     * \fn	void processData(HelloWorld &instance)
     * \brief	处理数据
     * \author	Zhangzf
     * \date	2013-10-11
     * \param [in,out]	instance	the instance. 
     */
    void processData(HelloWorld &instance) {
        /* 如果您想访问内部的负载缓存区，并验证数据的完整性
         * 打开下面的注释:
         *
        DDS_Octet *payloadBuffer = NULL;
        payloadBuffer = instance.payload.get_contiguous_buffer();
        
        for (int pos = 0; pos < instance.payload.length(); ++pos) {
            if (payloadBuffer[pos] != (pos & 0xff)) {
                std::cerr << "! 数据不同" << std::endl;
                return;
            }
        }
        */

        /*if (_thePayloadSize == 0) {
            _thePayloadSize = instance.payload.length();
        }*/
        _theLastSampleId = instance.sampleId;
        ++_theSampleRcvdCount;
    }



public:
    /*!
     * \fn	void on_requested_deadline_missed(DDSDataReader* ,
     * 		const DDS_RequestedDeadlineMissedStatus& )
     * \brief	被请求的活性丢失
     * \author	Zhangzf
     * \date	2013-10-11
     * \param		If non-null, the. 
     * \param		The. 
     */
    void on_requested_deadline_missed(DDSDataReader* /*reader*/,
                        const DDS_RequestedDeadlineMissedStatus& /*status*/) {
        if (_theVerbose > 0) {
            //std::cout << "->返回: 被请求的活性丢失." << std::endl;
        }
    }

    
    void on_requested_incompatible_qos(DDSDataReader* /*reader*/,
                        const DDS_RequestedIncompatibleQosStatus& /*status*/) {
        if (_theVerbose > 0) {
            /*std::cout << "->返回: 被请求不匹配的QoS." 
                      << std::endl;*/
        }
    }
    
    
    /*!
     * \fn	void on_sample_rejected(DDSDataReader* , const DDS_SampleRejectedStatus& )
     * \brief	样本被拒绝的
     * \author	Zhangzf
     * \date	2013-10-11
     * \param		If non-null, the. 
     * \param		The. 
     */
    void on_sample_rejected(DDSDataReader* /*reader*/,
                        const DDS_SampleRejectedStatus& /*status*/) {
        if (_theVerbose > 0) {
            //std::cout << "->返回: 样本被拒绝的." << std::endl;
        }
    }

    
    void on_liveliness_changed(DDSDataReader* /*reader*/,
                        const DDS_LivelinessChangedStatus& /*status*/) {
        if (_theVerbose > 0) {
            //std::cout << "->返回: 活性改变." << std::endl;
			//textEdit->appendPlainText("live state change.");
        }
    }

    
    /*!
     * \fn	void on_sample_lost(DDSDataReader* , const DDS_SampleLostStatus& )
     * \brief	样本丢失
     * \author	Zhangzf
     * \date	2013-10-11
     * \param		If non-null, the. 
     * \param		The. 
     */
    void on_sample_lost(DDSDataReader* /*reader*/,
                        const DDS_SampleLostStatus& /*status*/) {
        if (_theVerbose > 0) {
            //std::cout << "->返回: 样本丢失." << std::endl;
        }
        ++_theSampleLostCount;
    }


    
    /*!
     * \fn	void on_subscription_matched(DDSDataReader* , const DDS_SubscriptionMatchedStatus& )
     * \brief	订阅者匹配
     * \author	Zhangzf
     * \date	2013-10-11
     * \param		If non-null, the. 
     * \param		The. 
     */
    void on_subscription_matched(DDSDataReader* /*reader*/,
                        const DDS_SubscriptionMatchedStatus& /*status*/) {
        if (_theVerbose > 0) {
            //std::cout << "->返回: 订阅者匹配." << std::endl;
        }
    }



    /*!
     * \fn	void on_data_available(DDSDataReader* reader)
     * \brief	有效数据匹配
     * \author	Zhangzf
     * \date	2013-10-11
     * \param	reader	If non-null, the reader. 
     */
    void on_data_available(DDSDataReader* reader) {
        HelloWorldSeq dataSeq;
        DDS_SampleInfoSeq infoSeq;
        DDS_ReturnCode_t rc;

       
        if (_theSampleRcvdMax != 0 && 
            (_theSampleRcvdCount >= _theSampleRcvdMax)) {
            return;
        }
        
        //std::cout << "->返回: 有效数据匹配." << std::endl;
        if (_theVerbose > 2) {
            //std::cout << "->返回: 有效数据匹配." << std::endl;
        }

        // 转换数据读取者
        HelloWorldDataReader *helloReader = HelloWorldDataReader::narrow(reader);
        if (helloReader == NULL) {
            //std::cerr << "! 无法转换数据读取者" << std::endl;
            return;
        }

        rc = helloReader->take(
                            dataSeq, 
                            infoSeq, 
                            DDS_LENGTH_UNLIMITED,
                            DDS_ANY_SAMPLE_STATE, 
                            DDS_ANY_VIEW_STATE, 
                            DDS_ANY_INSTANCE_STATE);
        if (rc == DDS_RETCODE_NO_DATA) {
            return;
        } else if (rc != DDS_RETCODE_OK) {
            /*std::cerr << "! 无法从读取者获取数据, 错误 " 
                      << rc << std::endl;*/
            return;
        }

        for (int i = 0; i < dataSeq.length(); ++i) {
            if (infoSeq[i].valid_data) {
                // 处理数据
                processData(dataSeq[i]);    
				// 打印数据内容
				/*std::cout << "接收到数据：";
				HelloWorldTypeSupport::print_data(&dataSeq[i]);
				std::cout << std::endl;*/

				//_textEdit.append("\n _textEdit func");
            }
        }
    
        rc = helloReader->return_loan(dataSeq, infoSeq);
        if (rc != DDS_RETCODE_OK) {
           /* std::cerr << "! 无法返回借出, 错误 "
                      << rc << std::endl;*/
        }
    }
};
#endif

HelloListener::HelloListener():
		_theVerbose(1),
        _theLastSampleId(0),
        _thePayloadSize(0),
        _theSampleLostCount(0),
        _theSampleRcvdCount(0),
		_theSampleRcvdMax(0) {
			main_window = NULL;
}

HelloListener::HelloListener(int verbose, int sampleCount):
        _theVerbose(verbose),
        _theLastSampleId(0),
        _thePayloadSize(0),
        _theSampleLostCount(0),
        _theSampleRcvdCount(0),
        _theSampleRcvdMax(sampleCount) {
			// 注册HelloWorldSeq类型用于signal&slot机制
			qRegisterMetaType<HelloWorldSeq>("HelloWorldSeq");
			main_window = NULL;
    }
    
HelloListener::~HelloListener() {}

HelloListener::HelloListener(const HelloListener &ref):
    _theVerbose(ref._theVerbose),
    _theLastSampleId(ref._theLastSampleId),
    _thePayloadSize(ref._thePayloadSize),
    _theSampleLostCount(ref._theSampleLostCount),
    _theSampleRcvdCount(ref._theSampleRcvdCount),
    _theSampleRcvdMax(ref._theSampleRcvdMax) {
}



/*!
 * \fn	long getLastSampleId() const
 * \brief	获取最后样本的ID
 * \author	Zhangzf
 * \date	2013-10-11
 * \return	The last sample identifier. 
 */
long HelloListener::getLastSampleId() const {
    return _theLastSampleId;
}

/*!
 * \fn	long getPayloadSize() const
 * \brief	获取负载大小
 * \author	Zhangzf
 * \date	2013-10-11
 * \return	The payload size. 
 */
long HelloListener::getPayloadSize() const {
    return _thePayloadSize;
}

/*!
 * \fn	long getSampleLostCount() const
 * \brief	获取丢失的样本数量
 * \author	Zhangzf
 * \date	2013-10-11
 * \return	The sample lost count. 
 */
long HelloListener::getSampleLostCount() const {
    return _theSampleLostCount;
}

/*!
 * \fn	long getSampleRcvdCount() const
 * \brief	获取接收的样本数量
 * \author	Zhangzf
 * \date	2013-10-11
 * \return	The sample rcvd count. 
 */
long HelloListener::getSampleRcvdCount() const {
    return _theSampleRcvdCount;
}

/*!
 * \fn	long getSampleRcvdMax() const
 * \brief	获取接收的样本的最大值
 * \author	Zhangzf
 * \date	2013-10-11
 * \return	The sample rcvd maximum. 
 */
long HelloListener::getSampleRcvdMax() const {
    return _theSampleRcvdMax;
}


  
/*!
 * \fn	void processData(HelloWorld &instance)
 * \brief	处理数据
 * \author	Zhangzf
 * \date	2013-10-11
 * \param [in,out]	instance	the instance. 
 */
void HelloListener::processData(HelloWorld &instance) {
    /* 如果您想访问内部的负载缓存区，并验证数据的完整性
     * 打开下面的注释:
     *
    DDS_Octet *payloadBuffer = NULL;
    payloadBuffer = instance.payload.get_contiguous_buffer();
    
    for (int pos = 0; pos < instance.payload.length(); ++pos) {
        if (payloadBuffer[pos] != (pos & 0xff)) {
            std::cerr << "! 数据不同" << std::endl;
            return;
        }
    }
    */

    /*if (_thePayloadSize == 0) {
        _thePayloadSize = instance.payload.length();
    }*/
    _theLastSampleId = instance.sampleId;
    ++_theSampleRcvdCount;
}



/*!
 * \fn	void on_requested_deadline_missed(DDSDataReader* ,
 * 		const DDS_RequestedDeadlineMissedStatus& )
 * \brief	被请求的活性丢失
 * \author	Zhangzf
 * \date	2013-10-11
 * \param		If non-null, the. 
 * \param		The. 
 */
void HelloListener::on_requested_deadline_missed(DDSDataReader* /*reader*/,
                    const DDS_RequestedDeadlineMissedStatus& /*status*/) {
    if (_theVerbose > 0) {
        //std::cout << "->返回: 被请求的活性丢失." << std::endl;
    }
}


void HelloListener::on_requested_incompatible_qos(DDSDataReader* /*reader*/,
                    const DDS_RequestedIncompatibleQosStatus& /*status*/) {
    if (_theVerbose > 0) {
        std::cout << "->返回: 被请求不匹配的QoS." 
                  << std::endl;
    }
}


/*!
 * \fn	void on_sample_rejected(DDSDataReader* , const DDS_SampleRejectedStatus& )
 * \brief	样本被拒绝的
 * \author	Zhangzf
 * \date	2013-10-11
 * \param		If non-null, the. 
 * \param		The. 
 */
void HelloListener::on_sample_rejected(DDSDataReader* /*reader*/,
                    const DDS_SampleRejectedStatus& /*status*/) {
    if (_theVerbose > 0) {
        std::cout << "->返回: 样本被拒绝的." << std::endl;
    }
}


void HelloListener::on_liveliness_changed(DDSDataReader* /*reader*/,
                    const DDS_LivelinessChangedStatus& /*status*/) {
    if (_theVerbose > 0) {
        std::cout << "->返回: 活性改变." << std::endl;
		//textEdit->appendPlainText("live state change.");
    }
}


/*!
 * \fn	void on_sample_lost(DDSDataReader* , const DDS_SampleLostStatus& )
 * \brief	样本丢失
 * \author	Zhangzf
 * \date	2013-10-11
 * \param		If non-null, the. 
 * \param		The. 
 */
void HelloListener::on_sample_lost(DDSDataReader* /*reader*/,
                    const DDS_SampleLostStatus& /*status*/) {
    if (_theVerbose > 0) {
        std::cout << "->返回: 样本丢失." << std::endl;
    }
    ++_theSampleLostCount;
}



/*!
 * \fn	void on_subscription_matched(DDSDataReader* , const DDS_SubscriptionMatchedStatus& )
 * \brief	订阅者匹配
 * \author	Zhangzf
 * \date	2013-10-11
 * \param		If non-null, the. 
 * \param		The. 
 */
void HelloListener::on_subscription_matched(DDSDataReader* /*reader*/,
                    const DDS_SubscriptionMatchedStatus& /*status*/) {
    if (_theVerbose > 0) {
        std::cout << "->返回: 订阅者匹配." << std::endl;
    }
}

/*!
 * \fn	void on_data_available(DDSDataReader* reader)
 * \brief	有效数据匹配
 * \author	Zhangzf
 * \date	2013-10-11
 * \param	reader	If non-null, the reader. 
 */
void HelloListener::on_data_available(DDSDataReader* reader) {
    HelloWorldSeq dataSeq;
    DDS_SampleInfoSeq infoSeq;
    DDS_ReturnCode_t rc;
	/*QPlainTextEdit textEdit;
	QPlainTextEdit* p_text_edit = &textEdit;*/
	//send_msg();
   
    if (_theSampleRcvdMax != 0 && 
        (_theSampleRcvdCount >= _theSampleRcvdMax)) {
        return;
    }
    
    std::cout << "->返回: 有效数据匹配." << std::endl;
	/*if (main_window != NULL) {
		p_text_edit = main_window->getTextEdit();
		p_text_edit->appendPlainText("data available!");
	}*/

    if (_theVerbose > 2) {
        //std::cout << "->返回: 有效数据匹配." << std::endl;
    }

    // 转换数据读取者
    HelloWorldDataReader *helloReader = HelloWorldDataReader::narrow(reader);
    if (helloReader == NULL) {
        //std::cerr << "! 无法转换数据读取者" << std::endl;
        return;
    }

    rc = helloReader->take(
                        dataSeq, 
                        infoSeq, 
                        DDS_LENGTH_UNLIMITED,
                        DDS_ANY_SAMPLE_STATE, 
                        DDS_ANY_VIEW_STATE, 
                        DDS_ANY_INSTANCE_STATE);
    if (rc == DDS_RETCODE_NO_DATA) {
        return;
    } else if (rc != DDS_RETCODE_OK) {
        /*std::cerr << "! 无法从读取者获取数据, 错误 " 
                  << rc << std::endl;*/
        return;
    }

    for (int i = 0; i < dataSeq.length(); ++i) {
        if (infoSeq[i].valid_data) {
            // 处理数据
            processData(dataSeq[i]);    
			// 打印数据内容
			std::cout << "接收到数据：";
			HelloWorldTypeSupport::print_data(&dataSeq[i]);
			std::cout << std::endl;

			//_textEdit.append("\n _textEdit func");
        }
    }
	// 发送siganl给slot
	send_msg(dataSeq);

    rc = helloReader->return_loan(dataSeq, infoSeq);
    if (rc != DDS_RETCODE_OK) {
       /* std::cerr << "! 无法返回借出, 错误 "
                  << rc << std::endl;*/
    }
}



//
// 启动订阅者
//
#if 1
bool startSubscriber(DDSDomainParticipant *participant,
                        DDSTopic *topic,
                        DDS_Long verbose,
                        DDS_Long sampleCount) {

    DDS_ReturnCode_t rc = DDS_RETCODE_OK;
    DDSSubscriber *subscriber = NULL;
    DDSDataReader *dataReader = NULL;
    DDS_UnsignedLong i = 0;
    DDS_Duration_t poll_period = {POLL_PERIOD_SEC, 0};
    HelloListener listener(verbose, sampleCount);
    
    // 创建订阅者
    if (verbose) {
        std::cout << "创建订阅者..." << std::endl;
    }
    subscriber = participant->create_subscriber(
                        DDS_SUBSCRIBER_QOS_DEFAULT,
                        NULL,           /* 监听者 */
                        DDS_STATUS_MASK_NONE);
    if (subscriber == NULL) {
        std::cerr << "! 无法创建DDS订阅者" << std::endl;
        return false;
    }
    
    
    if (verbose) {
        std::cout << "创建数据读取者..." << std::endl;
    }

    dataReader = subscriber->create_datareader(
                        topic,
                        DDS_DATAREADER_QOS_DEFAULT,
                        &listener,
                        DDS_STATUS_MASK_ALL);
    if (dataReader == NULL) {
        std::cerr << "! 无法创建DDS数据读取者" << std::endl;
        return false;
    }

	// 主循环初始化
	long lastSampleId = -1; 
	//QApplication app();
	//QTextEdit* text_edit = listener.getQTextEdit();
	// 显示程序框
	//text_edit->show();
	//app.exec();

	// 主循环
    for (;;) {
        ZHDDS_Utility_sleep(&poll_period);

        if (sampleCount != 0 && (listener.getSampleRcvdCount() >= sampleCount)) {
            std::cout << "\n接收了" << listener.getSampleRcvdCount()
                      << "个样本数" << std::endl;
			//text_edit->append("\n text_edit func");
            break;
        }
    
        
        if (listener.getLastSampleId() < listener.getLastSampleId()) {
            std::cout << "检测出多个发布者, 或重启了发布者." << std::endl;
            std::cout << "如果您在网络上有多个发布者或者重启了发布者" << std::endl;
            std::cout << "统计结果将不准确.";
            break;
        }

        if (lastSampleId == -1 ||
			listener.getSampleRcvdCount() == listener.getLastSampleId() + 1) {
            if (verbose) {
                printf("没有数据...\n");
            }
           
            continue;
        }

        // 计算统计
		lastSampleId   = listener.getLastSampleId();
    }
    
    
    dataReader->set_listener(NULL);
    return true;
}
#endif
