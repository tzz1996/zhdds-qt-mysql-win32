#ifndef __HELLO_PUBLISHER_H_INCLUDED__
#define __HELLO_PUBLISHER_H_INCLUDED__


#include <zhdds/zhdds_cpp.h>



/*!
 * \fn	extern bool startPublisher(DDSDomainParticipant *participant, DDSTopic *topic,
 * 		DDS_Long verbose, DDS_Long dataSize, DDS_Long sampleCount)
 * \brief	启动发布者
 * \author	Zhangzf
 * \date	2013-10-11
 * \param	participant	域参与者
 * \param	topic		主题
 * \param	verbose		冗余程度
 * \param	dataSize	数据大小
 * \param	sampleCount	样本数量
 * \return	true if it succeeds, false if it fails. 
 */
extern bool startPublisher(DDSDomainParticipant *participant,
                        DDSTopic *topic,
                        DDS_Long verbose,
                        DDS_Long dataSize,
                        DDS_Long sampleCount);



#endif            /* !defined(__HELLO_PUBLISHER_H_INCLUDED__) */


