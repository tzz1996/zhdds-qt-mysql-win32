#ifndef __HELLO_PUBLISHER_H_INCLUDED__
#define __HELLO_PUBLISHER_H_INCLUDED__


#include <zhdds/zhdds_cpp.h>



/*!
 * \fn	extern bool startPublisher(DDSDomainParticipant *participant, DDSTopic *topic,
 * 		DDS_Long verbose, DDS_Long dataSize, DDS_Long sampleCount)
 * \brief	����������
 * \author	Zhangzf
 * \date	2013-10-11
 * \param	participant	�������
 * \param	topic		����
 * \param	verbose		����̶�
 * \param	dataSize	���ݴ�С
 * \param	sampleCount	��������
 * \return	true if it succeeds, false if it fails. 
 */
extern bool startPublisher(DDSDomainParticipant *participant,
                        DDSTopic *topic,
                        DDS_Long verbose,
                        DDS_Long dataSize,
                        DDS_Long sampleCount);



#endif            /* !defined(__HELLO_PUBLISHER_H_INCLUDED__) */


