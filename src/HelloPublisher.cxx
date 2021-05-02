#include <iostream>
#include <string>
#include <cstdlib>

#include "Hello.h"
#include "HelloPublisher.h"
#include "HelloWorld.h"
#include "HelloWorldSupport.h"



#define POLL_PERIOD_SEC                     1	        // ����Ƶ��
#define MAX_CONSECUTIVE_WRITE_ERROR         10			// ����д��������ֵ


//
// ����������
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
    
	// ����������
    if (verbose) {
        std::cout << "����������..." << std::endl;
    }
    publisher = participant->create_publisher(
                        DDS_PUBLISHER_QOS_DEFAULT,
                        NULL,           /* ������ */
                        DDS_STATUS_MASK_NONE);
    if (publisher == NULL) {
        std::cerr << "! �޷�����DDS������" << std::endl;
        goto exitFn;
    }

    // ��������д����
    if (verbose) {
        std::cout << "��������д����..." << std::endl;
    }
    dataWriter = publisher->create_datawriter(
                        topic,
                        DDS_DATAWRITER_QOS_DEFAULT,
                        NULL,           /* ������ */
                        DDS_STATUS_MASK_NONE);
    if (dataWriter == NULL) {
        std::cerr << "! �޷�����DDS����д����" << std::endl;
        goto exitFn;
    }

    // ת������д����
    helloWriter = HelloWorldDataWriter::narrow(dataWriter);
    if (helloWriter == NULL) {
        std::cerr << "! �޷�ת������д���߳�HelloWorldDataWriter"
                  << std::endl;
        goto exitFn;
    }

    // ��������ʵ��
    instance = HelloWorldTypeSupport::create_data_ex(
                        DDS_BOOLEAN_FALSE);
    if (instance == NULL) {
        std::cerr << "! �޷���������ʵ��" << std::endl;
        std::cerr << "! �������ܿ����������ڴ治����ɵ�"
                  << std::endl;
        goto exitFn;
    }

    // ���ø��ش�С
    /*if (!DDS_OctetSeq_ensure_length(&instance->payload, 
                        dataSize, 
                        HELLODDS_MAX_PAYLOAD_SIZE)) {
        std::cerr << "! �޷����ø��ش�С" << dataSize 
                  << std::endl;
        std::cerr << "! �ܿ�������Ϊ��ʹ�õ�ֵ̫��"
                  << "(���ֵ��"  
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

    // ��������
    std::cout << "��������(enter������һ��)...";
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
            std::cerr << "! д����" <<  rc << std::endl;
            if (++i > MAX_CONSECUTIVE_WRITE_ERROR) {
                std::cerr << "! ����ʧ�ܵ�������, "
                          << "ֹͣд����..." << std::endl;
                goto exitFn;
            }
        }
        i = 0;
        if (verbose) {
            std::cout << "����" << instance->sampleId 
                      << "������...";
        }
        if (sampleCount != 0 && instance->sampleId >= sampleCount) {
            std::cout << "\n������" << instance->sampleId 
                      << "������." << std::endl;
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

