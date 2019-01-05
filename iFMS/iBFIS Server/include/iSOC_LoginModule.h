#pragma once
#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_InitSobeyMonitorSystem
*��  �ܣ���ʼ��SDK
*��  ������		 
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��ע��:�˺������ļ���������˲�����DLL����Ӧ�ó���ĳ�ʼ�������е���
		��΢��MSDN����ȷ˵���˲�����DLL����Ӧ�ó����ʼ�������в����ļ���������ܻ����Ӧ�ó����޷��������߿��������⣩��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_InitSobeyMonitorSystem();

/******************************************************************************************************************************
*��������iSOC_UnInitSobeyMonitorSystem
*��  �ܣ�����ʼ��SDK
*��  ������	 
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UnInitSobeyMonitorSystem();


/******************************************************************************************************************************
*��������iSOC_UserLogin
*��  �ܣ��û���¼
*��  ����
		 [IN] strIpAddress ���������IP��ַ
		 [IN] wPort ����������˿�
		 [IN] strUserName �û���
		 [IN] strUserPwd ����
		 [IN OUT] pMCSession �������ĻỰ��ʶ�����MC�Ự��ʶ
		 [IN] pCallBack ����״̬�ص�����ָ��
		 [IN] dwCookie �û�Cookie�������û�ʹ�ã��ڲ���״̬�ص��н��û����õ�Cookie����
		 [IN] nClientType �ͻ������ͣ�����Ϊ��1��ʾΪ�ͻ��˵�¼��2��ʾΪ����ǽ���ƶ˵�¼��3��ʾΪ����ǽ��������¼
		 [IN] strServerType ������ϵͳ���ͣ��μ�iSOC_Datatype_Define.h�з��������Ͷ���
		 [IN] dwReserved ����������һ������Ϊ������ֵΪ10001ʱ���¼ʱ�������������ȡ��ʼ�����ݣ����豸���ݵȣ�
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UserLogin(IN const ISOC_STR strIpAddress,IN const ISOC_WORD wPort,IN const ISOC_STR strUserName,IN const ISOC_STR strUserPwd,IN OUT ISOC_LONGPTR* pMCSession,IN iSOC_OperatorStateCallback pCallBack = NULL,IN ISOC_DWORDPTR dwCookie = NULL,IN ISOC_INT nClientType = 1,IN const ISOC_STR strServerType = SOBEY_SERVER,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_UserLogout
*��  �ܣ��û�ע��
*��  ����
		 [IN] lMCSession MC�Ự��ʶ
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������
*��  ע������ɹ�ע������Ӧ��MC�Ự��ʶ���������Դ���ᱻ�ͷţ���ˣ��ɹ�ע����MC�Ự��ʶ��Ӧ���ٱ�ʹ��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UserLogout(IN const ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*��������iSOC_GetUserInfo
*��  �ܣ������û���Ϣ
*��  ����
		 [IN]		lMCSession	MC�Ự��ʶ
		 [IN OUT]	pUserInfo	�û���Ϣ�ṹ��
		 [IN]		dwReserved	��������������Ϊ0
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetUserInfo(IN const ISOC_LONGPTR lMCSession,IN OUT ST_UserInfo* pUserInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_GetDeviceCount
*��  �ܣ���ȡ�豸����
*��  ����
		 [IN] lMCSession MC�Ự��ʶ
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������
*��  ע����ȡ���豸����������֯������Ŀ
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceCount(IN const ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*��������iSOC_GetDeviceInfoByIndex
*��  �ܣ�ͨ��������Ż�ȡ�豸��Ϣ
*��  ����
		 [IN] lMCSession MC�Ự��ʶ
		 [IN OUT] pDevInfo �豸��Ϣ�ṹ��ָ��
		 [IN] nIdx ������š���������Ǵ�0-�豸����-1��ֵ
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ����������
*��  ע����ȡ���豸��Ϣ���豸IDֵΪ��ֵ��ʾ���õ�����ϢΪ��֯��������Ϣ
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceInfoByIndex(IN const ISOC_LONGPTR lMCSession,IN OUT ST_DeviceItem *pDevInfo,IN const ISOC_INT nIdx);

/******************************************************************************************************************************
*��������iSOC_GetDeviceInfoByUnitCode
*��  �ܣ�ͨ��ͳһ�����ȡ�豸��Ϣ
*��  ����
		 [IN] lMCSession MC�Ự��ʶ
		 [IN OUT] pDevInfo �豸��Ϣ�ṹ��ָ��
		 [IN] strUnitCode �豸ͳһ����
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ����������
*��  ע����ȡ���豸��Ϣ���豸IDֵΪ��ֵ��ʾ���õ�����ϢΪ��֯��������Ϣ
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceInfoByUnitCode(IN const ISOC_LONGPTR lMCSession,IN OUT ST_DeviceItem *pDevInfo,IN const ISOC_STR strUnitCode);

/******************************************************************************************************************************
*��������iSOC_GetDeviceInfoByDeviceId
*��  �ܣ�ͨ���豸ID��ȡ�豸��Ϣ
*��  ����
	     [IN] lMCSession MC�Ự��ʶ
		 [IN OUT] pDevInfo �豸��Ϣ�ṹ��ָ��
		 [IN] iDeviceId �豸IDֵ����IDֵΪȫ��Ψһ��IDֵ������ӦST_DeviceItem�е�lDeviceID
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ����������
*��  ע����ȡ���豸��Ϣ���豸IDֵΪ��ֵ��ʾ���õ�����ϢΪ��֯��������Ϣ
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceInfoByDeviceId(IN const ISOC_LONGPTR lMCSession,IN OUT ST_DeviceItem *pDevInfo,IN const ISOC_ID iDeviceId);

/******************************************************************************************************************************
*��������iSOC_GetDeviceInfoByIcmsSignAndIcmsDeviceId
*��  �ܣ�ͨ��ICMS��ʶ���豸���ڷֿص�ID��IcmsId��ȡ�豸��Ϣ
*��  ����
	     [IN] lMCSession MC�Ự��ʶ
		 [IN OUT] pDevInfo �豸��Ϣ�ṹ��ָ��
		 [IN] strICMSSign �豸��ICMS��ʶ
		 [IN] iICMSDeviceId �豸���ڷֿص�ID����ֵ����ȫ��Ψһ�ģ������豸���ڷֿ���ȫ��Ψһ�ġ���ֵ��ӦST_DeviceItem�е�lIcmsId
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ����������
*��  ע����ȡ���豸��Ϣ���豸IDֵΪ��ֵ��ʾ���õ�����ϢΪ��֯��������Ϣ��ʹ�ô˺��������豸��Ч����ߵģ�����ʹ�ô˺���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceInfoByIcmsSignAndIcmsDeviceId(IN const ISOC_LONGPTR lMCSession,IN OUT ST_DeviceItem *pDevInfo,IN ISOC_STR strICMSSign,IN ISOC_ID iICMSDeviceId);


/******************************************************************************************************************************
*��������iSOC_RegisterDeviceChangedNotifyCallback
*��  �ܣ������豸���»ص�
*��  ����
	     [IN] lMCSession MC�Ự��ʶ
		 [IN] pCallback �豸����ص�����
		 [IN] dwCookie �û�cookie
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ����������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterDeviceChangedNotifyCallback(IN const ISOC_LONGPTR lMCSession,IN iSOC_DeviceInfoChangedCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*��������iSOC_RegisterPermissionChangedNotifyCallback
*��  �ܣ�����Ȩ�޸��»ص�
*��  ����
	     [IN] lMCSession MC�Ự��ʶ
		 [IN] pCallback �豸����ص�����
		 [IN] dwCookie �û�cookie
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ����������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterPermissionChangedNotifyCallback(IN const ISOC_LONGPTR lMCSession,IN iSOC_PermissionChangedCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*��������iSOC_CheckDevicePermission
*��  �ܣ��ж��豸Ȩ��
*��  ����
		 [IN] lMCSession MC�Ự��ʶ
		 [IN] stDevInfo �豸��Ϣ�ṹ��
		 [IN] nPermissionCode ���豸Ȩ�޴��룬�����ֵ�μ�iSOC_Datatype_Define.h���豸Ȩ���붨��
*����ֵ��������ж�ӦȨ�޷���ISOC_TRUE�������ж�ӦȨ�޷���ISOC_FALSE
*��  ע�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ����������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_BOOL iSOC_CheckDevicePermission(IN const ISOC_LONGPTR lMCSession,IN const ST_DeviceItem stDevInfo,IN const ISOC_INT nPermissionCode);

/******************************************************************************************************************************
*��������iSOC_CheckSystemPermission
*��  �ܣ��ж�ϵͳȨ��
*��  ����
		 [IN] lMCSession MC�Ự��ʶ
		 [IN] nPermissionCode ϵͳȨ�޴��룬�����ֵ�μ�iSOC_Datatype_Define.h��ϵͳȨ���붨��
		 [IN] dwReserved ��������������ΪNULL
*����ֵ��������ж�ӦȨ�޷���ISOC_TRUE�������ж�ӦȨ�޷���ISOC_FALSE
*��  ע�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ����������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_BOOL iSOC_CheckSystemPermission(IN const ISOC_LONGPTR lMCSession,IN const ISOC_INT nPermissionCode,IN ISOC_DWORDPTR dwReserved = NULL);

/******************************************************************************************************************************
*��������iSOC_SendCmd2MCServer
*��  �ܣ����������MC������
*��  ����
		 [IN]	lMCSession MC�Ự��ʶ
		 [IN]	strXmlOut ��������
		 [IN]	nOutXmlLen �����
		 [IN]	nCmdSubType ��������
		 [IN]	nOverTime �������ʱʱ�䣬�Ժ���Ϊ��λ
		 [IN]	dwCookie �û��Զ���Cookie
		 [IN]	pOnGotDataCallback ��������Ļص�����
		 [IN]	pOnOverTimeballBack �������ʱʱ�Ļص�����	
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ����������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SendCmd2MCServer(IN const ISOC_LONGPTR lMCSession,IN const ISOC_STR strXmlOut,IN const ISOC_INT nOutXmlLen,
												IN const ISOC_INT nCmdSubType,IN const ISOC_INT nOverTime,IN ISOC_DWORDPTR dwCookie = NULL,
												IN const iSOC_OnGotDataCallback pOnGotDataCallback = NULL,IN iSOC_OnAffairOverTimeCallback pOnOverTimeballback = NULL);

/******************************************************************************************************************************
*��������iSOC_RegisterRecvMsgFromMCServerCallback
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
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterRecvMsgFromMCServerCallback(IN const ISOC_LONGPTR lMCSession,IN const ISOC_DWORD dwCMDID,IN iSOC_OnGotDataCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);


/******************************************************************************************************************************
*��������iSOC_RemoveRecvMsgFromMCServerCallback
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
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveRecvMsgFromMCServerCallback(IN const ISOC_LONGPTR lMCSession,IN const ISOC_DWORD dwCMDID,IN iSOC_OnGotDataCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);


/******************************************************************************************************************************
*��������iSOC_GetOnlineClientInfo
*��  �ܣ���ȡ���߿ͻ��˵���Ϣ
*��  ����
		 [IN] lMCSession MC�Ự��ʶ
		 [IN] pCallBack	 �ͻ�����Ϣ�ص�������strDes�����˿ͻ��˵���Ϣ����ʽΪip:name�����磺172.16.12.1:client1
		 [IN] dwCookie	 �û�COOKIE
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������
*��  ע��ÿ�ص�һ�η���һ���ͻ�����Ϣ�����ͬʱ���߶���ͻ��ˣ��ͻ��������ص�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetOnlineClientsInfo(IN const ISOC_LONGPTR lMCSession,IN iSOC_OnGotOnlineClientInfoCallback pCallBack,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*��������iSOC_SetRecvServerTimeCallback
*��  �ܣ������յ�������ͬ����ʱ��ʱ�Ļص�����
*��  ����
		 [IN] lMCSession MC�Ự��ʶ
		 [IN] pCallBack	 ʱ����Ϣ�ص�����
		 [IN] dwCookie	 �û�COOKIE
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������
*��  ע��ÿ�ص�һ�η���һ���ͻ�����Ϣ�����ͬʱ���߶���ͻ��ˣ��ͻ��������ص�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetRecvServerTimeCallback(IN const ISOC_LONGPTR lMCSession,IN iSOC_OnRecvServerTimeCallback pCallback,IN ISOC_DWORDPTR dwCookie);

//���ôӷ�������Ϣ��ͨ����չ�������ã�dwExtendData����ST_ServerInfo�ṹ��ָ��
#define ISOC_SET_SLAVE_SERVER_INFO    0x00000001

/******************************************************************************************************************************
*��������iSOC_MCModuleExtendFunc
*��  �ܣ�MC��ص���չ����
*��  ����
[IN]		lMCSession			MC�Ự��ʶ
[IN]		nExteydType			����չ������
[IN]		dwExtendData		����չ��������Ϣ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLDownloadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_MCModuleExtendFunc(IN const ISOC_LONGPTR lMCSession,IN const ISOC_INT nExteydType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*��������iSOC_SetTransparentData
*��  �ܣ�����͸��ͨ������
*��  ����
[IN]		lMCSession			MC�Ự��ʶ
[IN]		strKey
[IN]		nDataArea
[IN]		strContent
[IN]		dwExtendData		����չ��������Ϣ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLDownloadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetTransparentData(IN const ISOC_LONGPTR lMCSession,IN const ISOC_STR strKey,IN ISOC_INT nDataArea,IN const ISOC_STR strContent,IN iSOC_OperatorStateCallback pOperatorCallback,IN ISOC_DWORDPTR dwCookie = ISOC_NULL,IN ISOC_DWORDPTR dwReserved = ISOC_NULL);


iSOC_EXPORT_MODE ISOC_INT iSOC_DelTransparentData(IN const ISOC_LONGPTR lMCSession,IN const ISOC_STR strKey,IN ISOC_INT nDataArea,IN iSOC_OperatorStateCallback pOperatorCallback,IN ISOC_DWORDPTR dwCookie = ISOC_NULL,IN ISOC_DWORDPTR dwReserved = ISOC_NULL);

/******************************************************************************************************************************
*��������iSOC_GetTransparentData
*��  �ܣ���ȡ͸��ͨ������
*��  ����
[IN]		lMCSession			MC�Ự��ʶ
[IN]		nExteydType			����չ������
[IN]		dwExtendData		����չ��������Ϣ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLDownloadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetTransparentData(IN const ISOC_LONGPTR lMCSession,IN const ISOC_INT nDataArea,IN const ISOC_STR strKey,IN iSOC_OnGotTransparentDataInfoCallback pCallback,IN ISOC_DWORDPTR dwCookie = ISOC_NULL,IN ISOC_DWORDPTR dwReserved = ISOC_NULL);


iSOC_EXPORT_MODE ISOC_INT iSOC_GetSystemTypeAndVersion(IN const ISOC_LONGPTR lMCSession,IN OUT ISOC_CHAR chServerType[20],IN OUT ISOC_CHAR chVersion[16]);

/******************************************************************************************************************************
*��������iSOC_GetServerInfoList
*��  �ܣ���ȡ��¼�û���Ȩ�޵ķ�������Ϣ
*��  ����
		 [IN]	lMCSession	MC�Ự��ʶ
		 [IN]	enServerType ����������
		 [IN]	pServerInfoHeader	��������Ϣͷ��ʹ�����������������صĽṹ������Ϊ��ST_ServerInfo
		 [IN]	dwReserved	��������
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������������-4˵��û���ҵ�
		 ��Ӧ�Ļص���Ϣ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetServerInfoList(IN const ISOC_LONGPTR lMCSession,IN ST_ServerInfo::EN_ServerType enServerType,IN OUT ISOC_LONGPTR* pServerInfoHeader,IN ISOC_DWORDPTR dwReserved);

/******************************************************************************************************************************
*��������iSOC_GetLocalSystemVersion
*��  �ܣ���ȡ��ǰϵͳsdk�汾��
*��  ����
		[IN OUT]	chLocalVersion ����SDK�汾��

*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������������-4˵��û���ҵ�
		 ��Ӧ�Ļص���Ϣ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLocalSystemVersion(IN OUT ISOC_CHAR chLocalVersion[20]);

#ifdef __cplusplus
}
#endif