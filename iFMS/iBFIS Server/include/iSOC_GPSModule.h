#pragma once
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////GPSģ��ӿڵĶ���/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************************************************************
*��������iSOC_CreateGPSSession
*��  �ܣ�����GPS�Ự
*��  ����
		 [IN OUT]	pLGPSSession	GPS�Ự��ʶ
		 [IN]		pStateCallback	״̬�ص�����
		 [IN]		dwUserCookie	�û��Զ�������
		 [IN]		dwReserved		����������Ϊ0
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateGPSSession(IN OUT ISOC_LONGPTR* pLGPSSession, \
	IN const iSOC_OperatorStateCallback pStateCallback = ISOC_NULL,\
	IN const ISOC_DWORDPTR dwUserCookie = 0,\
	IN ISOC_DWORDPTR dwReserved = 0	);

/******************************************************************************************************************************
*��������iSOC_ReleaseGPSSession
*��  �ܣ�����GPS�Ự
*��  ����
		 [IN ]	pLGPSSession	GPS�Ự��ʶ
		 [IN]	dwReserved		����������Ϊ0
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseGPSSession(IN ISOC_LONGPTR lGPSSession, IN ISOC_DWORDPTR dwReserved = 0	);

/******************************************************************************************************************************
*��������iSOC_SetGPSDataStreamCallBack
*��  �ܣ�����GPS�������ص�
*��  ����
		 [IN]		pLGPSSession	GPS�Ự��ʶ
		 [IN]		pDataCallBack	GPS�������ص�����
		 [IN]		dwUserCookie	�û��Զ�������
		 [IN]		dwReserved		����������Ϊ0
*����ֵ����
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_VOID iSOC_SetGPSDataStreamCallBack(IN ISOC_LONGPTR lGPSSession, \
	IN const iSOC_OnGotGPSDataCallback pDataCallBack, \
	IN const ISOC_DWORDPTR dwUserCookie = 0, \
	IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_StartGPSStream
*��  �ܣ�����GPS������
*��  ����
		 [IN]		pLGPSSession	GPS�Ự��ʶ
		 [IN]		lMCSession		MC�Ự��ʶ
		 [IN]		stDevItem		���豸��Ϣ
		 [IN]		dwReserved		����������Ϊ0
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartGPSStream(IN ISOC_LONGPTR lGPSSession, \
	IN const ISOC_LONGPTR lMCSession,\
	IN const ST_DeviceItem stDevItem, \
	IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_StopGPSStream
*��  �ܣ�ֹͣGPS������
*��  ����
		 [IN]		pLGPSSession	GPS�Ự��ʶ
		 [IN]		pDevItem		���豸��Ϣ��Ϊ��ʱֹͣ��ǰ���е�GPS������������ָֹͣ����ĳ��GPS������
		 [IN]		dwReserved		����������Ϊ0
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopGPSStream(IN ISOC_LONGPTR lGPSSession, \
	IN const ST_DeviceItem* pDevItem = NULL, \
	IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_GPSExtendFunction
*��  �ܣ�ֹͣGPS������
*��  ����
		 [IN]		pLGPSSession	GPS�Ự��ʶ
		 [IN] nExType ��չ���ͱ�ʶ
		 [IN] dwExtendData ��չ����
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GPSExtendFunction(IN ISOC_LONGPTR lGPSSession, \
	IN ISOC_DWORD dwExtendType,\
	IN ISOC_VOID* pExtendData);

#ifdef __cplusplus
}
#endif