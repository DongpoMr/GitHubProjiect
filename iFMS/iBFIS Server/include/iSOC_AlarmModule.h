#pragma once
#include "iSOC_UnitDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************************************************************
*��������iSOC_GetAlarmSession
*��  �ܣ���ȡ�����Ự
*��  ����
		 [IN] lMCSession	MC�Ự
		 [IN OUT] pAlarmSession	�����Ự
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lMCSession�����ȡʧ������
*��  ע����ʹ�ñ�����ع���ʱ���ǵ�һ��������Ҫ��ȡһ�������Ự֮����ܽ���������������
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_GetAlarmSession(IN const ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pAlarmSession);

/******************************************************************************************************************************
*��������iSOC_SendManualAlarm
*��  �ܣ������ֶ�����
*��  ����
		 [IN] lAlarmSession	�����Ự
		 [IN] devInfo	�豸��Ϣ�ṹ��
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ��ͨ��iSOC_GetLastErrorDes������lAlarmSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_SendManualAlarm(IN ISOC_LONGPTR lAlarmSession, IN ST_DeviceItem devInfo);

/******************************************************************************************************************************
*��������iSOC_SendCmd2AlarmServer
*��  �ܣ��򱨾��������������ָ��
*��  ����
		 [IN] lAlarmSession	�����Ự
		 [IN] dwXMLType	ָ������
		 [IN] pXmlContext ָ������
		 [IN] nXmlLen ָ�����ݳ���
		 [IN] dwReserved ����������Ĭ��Ϊ0
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ��ͨ��iSOC_GetLastErrorDes������lAlarmSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_SendCmd2AlarmServer(IN const ISOC_LONGPTR lAlarmSession,IN const ISOC_DWORD dwXMLType,IN const ISOC_STR pXmlContext,IN const ISOC_INT nXmlLen,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_SetOnGotAlarmEventCallback
*��  �ܣ����ñ���������������Ϣ�ص�
*��  ����
		 [IN] lAlarmSession	�����Ự
		 [IN] pCallback ����ָ��
		 [IN] dwCookie �û�Cookie
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ��ͨ��iSOC_GetLastErrorDes������lAlarmSession�����ȡʧ������
*��  ע���ڻ�ȡ�������Ự��ͽ�����ʹ�ô˺����������ڸ���ָ��͸�������������ſ��Լ�ʱ�յ����ؽ��
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_SetOnGotAlarmEventCallback(IN const ISOC_LONGPTR lAlarmSession,IN iSOC_WhenOnGotAlarmEventCallback pCallback,IN ISOC_DWORDPTR dwCookie = 0);

/******************************************************************************************************************************
*��������iSOC_SetDeviceDefence
*��  �ܣ������豸�����򳷷�
*��  ����
		 [IN] lAlarmSession	�����Ự
		 [IN] devInfo �豸��Ϣ�ṹ��
		 [IN] bIsDefence �����򳷷���ʶ��ISOC_TRUEΪ����,ISOC_FALSEΪ����
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ��ͨ��iSOC_GetLastErrorDes������lAlarmSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_SetDeviceDefence(IN const ISOC_LONGPTR lAlarmSession,IN ST_DeviceItem devInfo,IN ISOC_BOOL bIsDefence = ISOC_TRUE);

/******************************************************************************************************************************
*��������iSOC_AlarmExtendFunc
*��  �ܣ����������չ����
*��  ����
		 [IN] lAlarmSession	�����Ự
		 [IN] nExtendType	��չ����
		 [IN] dwExtendData	��չ����
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ��ͨ��iSOC_GetLastErrorDes������lAlarmSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_AlarmExtendFunc(IN const ISOC_LONGPTR lAlarmSession,IN const ISOC_INT nExtendType,IN ISOC_DWORDPTR dwExtendData);


/******************************************************************************************************************************
*��������iSOC_GetUnconfirmedAlarmInfo
*��  �ܣ���ȡδ��������Ϣ
*��  ����
		 [IN] lAlarmSession	                �����Ự
		 [IN] pOnGotUnconfirmedAlarmInfo    �ص�����
		 [IN] dwCookie                      �û�����
		 [IN] pStartTime                    ��ʼʱ��
		 [IN] pEndTime                      ����ʱ��
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ�����ʧ�ܿ�ͨ��iSOC_GetLastErrorDes������lMCSession�����ȡʧ������
*��  ע��pStartTimeΪ�ղ����ƿ�ʼʱ�䣬pEndTimeΪ�ղ����ƽ���ʱ��
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_GetUnconfirmedAlarmInfo(IN const ISOC_LONGPTR lAlarmSession,iSOC_OnGotUnconfirmedAlarmInfoCallback pOnGotUnconfirmedAlarmInfoCallback,ISOC_DWORDPTR dwCookie,IN ISOC_SYSTEMTIME *pStartTime,IN ISOC_SYSTEMTIME *pEndTime);

#ifdef __cplusplus
}
#endif