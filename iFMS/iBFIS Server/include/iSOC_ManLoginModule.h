#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_InitSobeyManagerSystem
*��  �ܣ���ʼ��SDK
*��  ������		 
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_InitSobeyManagerSystem();

/******************************************************************************************************************************
*��������iSOC_UnInitSobeyManagerSystem
*��  �ܣ�����ʼ��SDK
*��  ������	 
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UnInitSobeyManagerSystem();



iSOC_EXPORT_MODE ISOC_INT iSOC_ManUserLogin(IN const ISOC_STR strIpAddress,IN const ISOC_WORD wPort,IN const ISOC_STR strUserName,IN const ISOC_STR strUserPwd,IN OUT ISOC_LONGPTR* pMCSession,IN iSOC_OperatorStateCallback pCallBack = NULL,IN ISOC_DWORDPTR dwCookie = NULL,IN ISOC_STR strServerType = ISIS8000_SERVER,IN ISOC_DWORDPTR dwReserved = 0);
iSOC_EXPORT_MODE ISOC_INT iSOC_ManUserLogout(IN ISOC_LONGPTR lMCSession,IN ISOC_DWORDPTR dwReserved);

/******************************************************************************************************************************
*��������iSOC_ManGetUserInfo
*��  �ܣ������û���Ϣ
*��  ����
		 [IN]		lMCSession	MC�Ự��ʶ
		 [IN OUT]	pUserInfo	�û���Ϣ�ṹ��
		 [IN]		dwReserved	��������������Ϊ0
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ManGetUserInfo(IN const ISOC_LONGPTR lMCSession,IN OUT ST_UserInfo* pUserInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ManSendCmd2MCServer
*��  �ܣ����������MC������
*��  ����
		 [IN]	lMCSession MC�Ự��ʶ
		 [IN]	pOutData ��������
		 [IN]	nOutDataLen �����
		 [IN]	nCmdSubType ��������
		 [IN]	nOverTime �������ʱʱ�䣬�Ժ���Ϊ��λ
		 [IN]	dwCookie �û��Զ���Cookie
		 [IN]	pOnGotDataCallback ��������Ļص�����
		 [IN]	pOnOverTimeballBack �������ʱʱ�Ļص�����	
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ����������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ManSendCmd2MCServer(IN const ISOC_LONGPTR lMCSession,IN const ISOC_BYTE* pOutData,IN const ISOC_INT nOutDataLen,
												IN const ISOC_INT nCmdSubType,IN const ISOC_INT nOverTime,IN ISOC_DWORDPTR dwCookie = NULL,
												IN const iSOC_OnGotDataCallback pOnGotDataCallback = NULL,IN iSOC_OnAffairOverTimeCallback pOnOverTimeballback = NULL);

/******************************************************************************************************************************
*��������iSOC_ManRegisterRecvMsgFromMCServerCallback
*��  �ܣ�ע���MC���������ص�����ص�
*��  ����
		 [IN]	lMCSession	MC�Ự��ʶ
		 [IN]	dwCMDID		�����ʶ
		 [IN]	pCallback	�ص�����ָ��
		 [IN]	dwUserCookie �û��Զ���Cookie
		 [IN]	dwReserved	��������
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������������-4˵���Ѿ�����
		 һ��һ���Ļص���Ϣ
*��  ע�����Զ��ע��ͬһ�������ʶ�����ע���ʱ��pCallback,dwUserCookie,dwReserved����������������һ��Ҫ��ͬ������ע��ģ�
		 ����ᷢ������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ManRegisterRecvMsgFromMCServerCallback(IN const ISOC_LONGPTR lMCSession,IN const ISOC_DWORD dwCMDID,IN iSOC_OnGotDataCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);


/******************************************************************************************************************************
*��������iSOC_ManRemoveRecvMsgFromMCServerCallback
*��  �ܣ��Ƴ���MC���������ص�����ص�
*��  ����
		 [IN]	lMCSession	MC�Ự��ʶ
		 [IN]	dwCMDID		�����ʶ
		 [IN]	pCallback	�ص�����ָ��
		 [IN]	dwUserCookie �û��Զ���Cookie
		 [IN]	dwReserved	��������
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������������-4˵��û���ҵ�
		 ��Ӧ�Ļص���Ϣ
*��  ע������ϵͳʵ���˿��Զ��ע��һ�������ʶ�Ĺ��ܣ��������Ƴ���ʱ����ز���Ҫ��ע��ʱ����һ�²��ܳɹ��Ƴ�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ManRemoveRecvMsgFromMCServerCallback(IN const ISOC_LONGPTR lMCSession,IN const ISOC_DWORD dwCMDID,IN iSOC_OnGotDataCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);

#ifdef __cplusplus
}
#endif
