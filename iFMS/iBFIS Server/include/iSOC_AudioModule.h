#pragma once
#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_CreateDeviceTalkSession
*��  �ܣ������豸�Խ��Ự
*��  ����
		[IN OUT]	lpDeviceTalkSession	�豸�Խ��Ự 
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lDeviceTalkSession�����ȡʧ������
*��  ע��һ���Ự��Ӧһ���豸�ĶԽ�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateDeviceTalkSession(IN OUT ISOC_LONGPTR * lpDeviceTalkSession);

/******************************************************************************************************************************
*��������iSOC_SetDeviceTalkInfo
*��  �ܣ������豸�Խ���Ϣ
*��  ����	
		[IN]	lDeviceTalkSession	�豸�Խ��Ự
		[IN]	lMCSession			�������ĻỰ
		[IN]	stAudioInfo			��Ƶ��Ϣ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lDeviceTalkSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetDeviceTalkInfo(IN ISOC_LONGPTR lDeviceTalkSession,IN ISOC_LONGPTR lMCSession,IN ST_AudioInfo stAudioInfo);

/******************************************************************************************************************************
*��������iSOC_SetDeviceTalkInfo
*��  �ܣ���ȡ�豸֧�ֵĶԽ���Ϣ
*��  ����	
		[IN]	lDeviceTalkSession	�豸�Խ��Ự
		[OUT]	ppAudioInfo			��Ƶ��Ϣָ��
		[IN OUT] nAudioInfoCount	��Ƶ��Ϣ����
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lDeviceTalkSession�����ȡʧ������
*��  ע���˺���Ҫ�ڿ�ʼ�Խ�֮��ſ��Ե���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceSupportedTalkInfo(IN ISOC_LONGPTR lDeviceTalkSession,OUT ST_AudioInfo** ppAudioInfo,IN OUT ISOC_INT& nAudioInfoCount);

/******************************************************************************************************************************
*��������iSOC_SetDeviceTalkType
*��  �ܣ������豸������
*��  ����	
		[IN]	lDeviceTalkSession	�豸�Խ��Ự
		[IN]	nTalkType			�Խ�����:0��������ȡ��Ƶ  1��ͨ��iSOC_PushAudioBuff������Ƶ����
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lDeviceTalkSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetDeviceTalkType(IN ISOC_LONGPTR lDeviceTalkSession,IN ISOC_INT nTalkType=0);

/******************************************************************************************************************************
*��������iSOC_PushAudioBuff
*��  �ܣ������豸�Խ�����
*��  ����	
		[IN]	lDeviceTalkSession	�豸�Խ��Ự
		[IN]	pBuff				��Ƶ����
		[IN]nBuffLen				���ݳ���
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lDeviceTalkSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_PushAudioBuff(IN ISOC_LONGPTR lDeviceTalkSession,IN ISOC_BYTE* pBuff,IN ISOC_INT nBuffLen);

/******************************************************************************************************************************
*��������iSOC_StartDeviceTalk
*��  �ܣ���ָ���豸��ʼ�Խ�
*��  ����
		[IN]	lDeviceTalkSession	�豸�Խ��Ự
		[IN]	stDevInfo			�豸��Ϣ
		[IN]	dwReserved			������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lDeviceTalkSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartDeviceTalk(IN ISOC_LONGPTR lDeviceTalkSession,IN ST_DeviceItem stDevInfo,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*��������iSOC_StopDeviceTalk
*��  �ܣ�ֹͣ�Խ�
*��  ����
		[IN]  DeviceTalkSession �豸�Խ��Ự
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lDeviceTalkSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopDeviceTalk(IN ISOC_LONGPTR lDeviceTalkSession);

/******************************************************************************************************************************
*��������iSOC_RealseDeviceTalkSession
*��  �ܣ������豸�Խ��Ự
*��  ����
		[IN]  DeviceTalkSession �豸�Խ��Ự
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lDeviceTalkSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RealseDeviceTalkSession(IN ISOC_LONGPTR lDeviceTalkSession);

/******************************************************************************************************************************
*��������iSOC_CreateMonitorTalkSession
*��  �ܣ������ͻ��˶Խ��Ự
*��  ����
		[IN OUT]	lpMonitorTalkSession	�ͻ��˶Խ��Ự
		[IN]		lMCSession				�������ĻỰ
		[IN]		stAudioInfo				��Ƶ��Ϣ������audioCodecId ---- G711:0x02 ,G726:0x04
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lMonitorTalkSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateMonitorTalkSession(IN OUT ISOC_LONGPTR *lpMonitorTalkSession,IN ISOC_LONGPTR lMCSession,IN ST_AudioInfo stAudioInfo);


/******************************************************************************************************************************
*��������iSOC_CtrlLocalAudioListen
*��  �ܣ����ƿͻ����Ƿ����
*��  ����
		[IN]	lMonitorTalkSession	�ͻ��˶Խ��Ự
		[IN]	bStart				�Ƿ�����������TRUE����ʼ������FALSE��ֹͣ����
		[IN]	nPort				�����˿ڣ�Ĭ��Ϊ61000
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lMonitorTalkSession�����ȡʧ������
*��  ע�������Ҫ�����Է��ͻ��˵ĶԽ����뿪ʼ�˼���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CtrlLocalAudioListen(IN ISOC_LONGPTR lMonitorTalkSession,IN ISOC_BOOL bStart = TRUE,IN ISOC_INT nPort = 61000);

/******************************************************************************************************************************
*��������iSOC_CtrlMonitorTalk
*��  �ܣ������豸�Խ�
*��  ����
		[IN]	lMonitorTalkSession		�ͻ��˶Խ��Ự
		[IN]	strMonitorIP				�Խ��ͻ���IP��ַ
		[IN]	nPort					�˿�
		[IN]	bStart					�Ƿ�ʼ�Խ���TRUE:��ʼ��FALSE:ֹͣ
		[IN]	bBroadCast				�Ƿ�㲥
		[IN]	dwReserved				������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lMonitorTalkSession�����ȡʧ������
*��  ע���˺������Զ�ε��ã����ò�ͬ�Ŀͻ���IP��ַ�Ͷ˿ڣ��Ͷ���ͻ��˶Խ�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CtrlMonitorTalk(IN ISOC_LONGPTR lMonitorTalkSession,IN const ISOC_STR strMonitorIP,IN ISOC_INT nPort = 61000,IN ISOC_BOOL bStart = TRUE,IN ISOC_BOOL bBroadCast = FALSE,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*��������iSOC_RealseMonitorTalkSession
*��  �ܣ����ٿͻ��˶Խ��Ự
*��  ����
		[IN]	lMonitorTalkSession		�ͻ��˶Խ��Ự
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lMonitorTalkSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RealseMonitorTalkSession(IN ISOC_LONGPTR lMonitorTalkSession);

#ifdef __cplusplus
}
#endif