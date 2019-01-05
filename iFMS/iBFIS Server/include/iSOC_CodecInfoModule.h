#pragma once
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////�������ģ��ӿڵĶ���/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_CreateCodecInfoSession
*��  �ܣ�������������Ự
*��  ����
		[IN OUT] pCodecInfoSession ��������Ự��ʶ
		[IN] dwReserved ��չֵ����ΪNULL
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע���ڲ�ʹ�ô˻Ự��һ��Ҫʹ��iSOC_ReleaseCodecInfoSession���˱�������Ự���٣���Ȼ�������ڴ�й©
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateCodecInfoSession(IN OUT ISOC_LONGPTR *pCodecInfoSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ReleaseCodecInfoSession
*��  �ܣ����ٱ�������Ự
*��  ����
		 [IN] lCodecInfoSession ������Ϣ�Ự��ʶ
		 [IN] dwReserved ��չֵ����ΪNULL
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseCodecInfoSession(IN ISOC_LONGPTR lCodecInfoSession,IN ISOC_DWORDPTR dwReserved = NULL);

/******************************************************************************************************************************
*��������iSOC_GetDevVideoCodecInfo
*��  �ܣ���ȡ��������������Ϣ
*��  ����
		 [IN] lCodecSession ��������Ự��ʶ
		 [IN] lMCSession
		 [IN] deviceInfo
		 [OUT]  lDataListHead ��������ͷ��ʶ��Ҫ�õ�����ı��������Ϣ��ʹ�������������������ȡ����ȡ�ľ���ṹ��Ϊ��ST_VideoInfo
		 [OUT] bAudio �Ƿ�����Ƶ��Ϣ
		 [OUT] pAudioInfo ��Ƶ��Ϣ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDevVideoCodecInfo(IN const ISOC_LONGPTR lCodecSession,IN const ISOC_LONGPTR lMCSession,IN const ST_DeviceItem deviceInfo,IN OUT ISOC_LONGPTR* lDataListHead,IN OUT ISOC_BOOL& bAudio,OUT ST_AudioInfo* pAudioInfo);

/******************************************************************************************************************************
*��������iSOC_GetVodVideoCodecInfo
*��  �ܣ���ȡ��������������Ϣ
*��  ����
		 [IN] lCodecSession ��������Ự��ʶ
		 [IN] lMCSession
		 [IN] VodInfo
		 [OUT] pVideoInfo ��Ƶ��Ϣ
		 [OUT] bAudio �Ƿ�����Ƶ��Ϣ
		 [OUT] pAudioInfo ��Ƶ��Ϣ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodVideoCodecInfo(IN const ISOC_LONGPTR lCodecSession,IN const ISOC_LONGPTR lMCSession,IN const ST_VodFileInfo VodInfo,IN OUT ST_VideoInfo* pVideoInfo,IN OUT ISOC_BOOL& bAudio,IN OUT ST_AudioInfo* pAudioInfo);

#ifdef __cplusplus
}
#endif
