#include <iostream>
#include <string>
#include <cstdlib>

#include "Hello.h"
#include "HelloPublisher.h"
#include "HelloWorld.h"
#include "HelloWorldSupport.h"



#define POLL_PERIOD_SEC                     1	        // 发送频率
#define MAX_CONSECUTIVE_WRITE_ERROR         10			// 连续写出错的最大值


//
// 启动发布者
//
bool startPublisher(
                        DDSDomainParticipant *participant,
                        DDSTopic *topic,
                        DDS_Long verbose,
                        DDS_Long dataSize,
                        DDS_Long sampleCount) {

    DDSPublisher *publisher              = NULL;
    DDSDataWriter *dataWriter            = NULL;
    HelloWorldDataWriter *helloWriter    = NULL;
    HelloWorld *instance                 = NULL;
    DDS_Octet * payloadBuffer            = NULL;
    bool returnValue                     = false;
    DDS_Long i;
    DDS_ReturnCode_t rc;

	char command[1024];

	DDS_Duration_t poll_period = {POLL_PERIOD_SEC, 0};
    
	// 创建发布者
    if (verbose) {
        std::cout << "创建发布者..." << std::endl;
    }
    publisher = participant->create_publisher(
                        DDS_PUBLISHER_QOS_DEFAULT,
                        NULL,           /* 监听者 */
                        DDS_STATUS_MASK_NONE);
    if (publisher == NULL) {
        std::cerr << "! 无法创建DDS发布者" << std::endl;
        goto exitFn;
    }

    // 创建数据写入者
    if (verbose) {
        std::cout << "创建数据写入者..." << std::endl;
    }
    dataWriter = publisher->create_datawriter(
                        topic,
                        DDS_DATAWRITER_QOS_DEFAULT,
                        NULL,           /* 监听者 */
                        DDS_STATUS_MASK_NONE);
    if (dataWriter == NULL) {
        std::cerr << "! 无法创建DDS数据写入者" << std::endl;
        goto exitFn;
    }

    // 转换数据写入者
    helloWriter = HelloWorldDataWriter::narrow(dataWriter);
    if (helloWriter == NULL) {
        std::cerr << "! 无法转换数据写入者成HelloWorldDataWriter"
                  << std::endl;
        goto exitFn;
    }

    // 创建数据实例
    instance = HelloWorldTypeSupport::create_data_ex(
                        DDS_BOOLEAN_FALSE);
    if (instance == NULL) {
        std::cerr << "! 无法创建数据实例" << std::endl;
        std::cerr << "! 这个问题很可能是由于内存不足造成的"
                  << std::endl;
        goto exitFn;
    }

    // 设置负载大小
    /*if (!DDS_OctetSeq_ensure_length(&instance->payload, 
                        dataSize, 
                        HELLODDS_MAX_PAYLOAD_SIZE)) {
        std::cerr << "! 无法设置负载大小" << dataSize 
                  << std::endl;
        std::cerr << "! 很可能是因为您使用的值太大"
                  << "(最大值是"  
                  << HELLODDS_MAX_PAYLOAD_SIZE
                  << ")" << std::endl;
        goto exitFn;
    }*/

    /*payloadBuffer = instance->payload.get_contiguous_buffer();
    for (i = 0; i < dataSize; ++i) {
        payloadBuffer[i] = (i & 0xff);
    }*/
    
    //sprintf(instance->prefix, "Hello world");
    
	instance->pub_num = 1;

    // 发送数据
    std::cout << "发送数据(enter键发送一次)...";
    i = 0;
    for (instance->sampleId = 1;; ++(instance->sampleId) ) {
		std::cin.getline(command, 1024);
        if (ZH_STRCASECMP(command, "exit") == 0)
			break;
		
		//sprintf(instance->prefix, "Hello world%d", instance->sampleId);
        rc = helloWriter->write(
                        *instance, 
                        DDS_HANDLE_NIL);
        if (rc != DDS_RETCODE_OK) {
            std::cerr << "! 写错误" <<  rc << std::endl;
            if (++i > MAX_CONSECUTIVE_WRITE_ERROR) {
                std::cerr << "! 到达失败的最大次数, "
                          << "停止写入者..." << std::endl;
                goto exitFn;
            }
        }
        i = 0;
        if (verbose) {
            std::cout << "发送" << instance->sampleId 
                      << "个样本...";
        }
        if (sampleCount != 0 && instance->sampleId >= sampleCount) {
            std::cout << "\n共发送" << instance->sampleId 
                      << "个样本." << std::endl;
            break;
        }
    }
    

    returnValue = true;

exitFn:
    if (instance != NULL) {
        HelloWorldTypeSupport::delete_data_ex(instance,
                        DDS_BOOLEAN_FALSE);
        instance = NULL;
    }
    
    return returnValue;
}

