#ifndef __HELLO_SUBSCRIBER_H_INCLUDED__
#define __HELLO_SUBSCRIBER_H_INCLUDED__


#include <zhdds/zhdds_cpp.h>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QMetaType>

#include "Hello.h"
#include "HelloSubscriber.h"
#include "HelloWorld.h"
#include "HelloWorldSupport.h"
#include "qt_mysql.h"

//#include "MainWindow.h"

//QT_BEGIN_NAMESPACE
//class QPlainTextEdit;
//QT_END_NAMESPACE

// 前置声明，避免循环调用
// 并且HelloSubscriber类中只能用指针形式引用MainWindow类
class MainWindow;

/*!
 * \fn	extern bool startSubscriber(DDSDomainParticipant *participant, DDSTopic *topic,
 * 		DDS_Long verbose, DDS_Long sampleCount)
 * \brief	启动订阅者
 * \author	Zhangzf
 * \date	2013-10-11
 * \param	participant	域参与者
 * \param	topic		主题
 * \param	verbose		冗余
 * \param	sampleCount	样本数量
 * \return	true if it succeeds, false if it fails. 
 */
extern bool startSubscriber(DDSDomainParticipant *participant,
                       DDSTopic *topic,
                       DDS_Long verbose,
                       DDS_Long sampleCount);

class HelloListener: public QObject, public DDSDataReaderListener {
	Q_OBJECT

private:
    const int _theVerbose;
    long _theLastSampleId;      
    long _thePayloadSize;       
    long _theSampleLostCount;   
    long _theSampleRcvdCount;   
    long _theSampleRcvdMax;

public:
	// mainwindow
	MainWindow* main_window;

public:

	HelloListener &operator=(const HelloListener &ref) {
        _theLastSampleId = ref._theLastSampleId;
        _thePayloadSize  = ref._thePayloadSize;
        _theSampleLostCount = ref._theSampleLostCount;
        _theSampleRcvdCount = ref._theSampleRcvdCount;
        _theSampleRcvdMax = ref._theSampleRcvdMax;
        return *this;
    }
	HelloListener();
	//HelloListener(class MainWindow* p);
    HelloListener(int verbose, int sampleCount);
    ~HelloListener();
    HelloListener(const HelloListener &ref);

public:
    long getLastSampleId() const;
    long getPayloadSize() const;
    long getSampleLostCount() const;
    long getSampleRcvdCount() const;
    long getSampleRcvdMax() const;
    
    

public:    
    void processData(HelloWorld &instance);

public:
    void on_requested_deadline_missed(DDSDataReader* /*reader*/,
                        const DDS_RequestedDeadlineMissedStatus& /*status*/);
    void on_requested_incompatible_qos(DDSDataReader* /*reader*/,
                        const DDS_RequestedIncompatibleQosStatus& /*status*/);
    void on_sample_rejected(DDSDataReader* /*reader*/,
                        const DDS_SampleRejectedStatus& /*status*/);
    void on_liveliness_changed(DDSDataReader* /*reader*/,
                        const DDS_LivelinessChangedStatus& /*status*/);
    void on_sample_lost(DDSDataReader* /*reader*/,
                        const DDS_SampleLostStatus& /*status*/);
    void on_subscription_matched(DDSDataReader* /*reader*/,
                        const DDS_SubscriptionMatchedStatus& /*status*/);
    void on_data_available(DDSDataReader* reader);

signals:                                   //信号关键字
    void send_msg(HelloWorldSeq dataSeq);  //发射信号函数，带的参数必须和槽一样。声明一下就可以了。
};


#endif            /* !defined(__HELLO_SUBSCRIBER_H_INCLUDED__) */


