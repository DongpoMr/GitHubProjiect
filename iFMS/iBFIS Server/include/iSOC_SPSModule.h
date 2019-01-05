#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"

enum SPSSessionType
{
    LIVE,
    VOD
};

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_CreateSPSSession
*��  �ܣ�����SPS���ƻỰ
*��  ����
		 [IN OUT]	pSPSSession  	SPS�Ự��ʶ
		 [IN]		lMCSession		MC�Ự��ʶ
		 [IN]		type     		SPS����
		 [IN]		param       	������������typeΪLIVEʱ��Ӧ�����豸�ṹ�壬��typeΪVODʱ��Ӧ����ST_VodFileInfo�ṹ��
		 [IN]		param    		��������
		 [IN]       pCallBack		����״̬�ص�
		 [IN]		dwCookie		�û�����
		 [IN]		dwReserved		��չ����
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateSPSSession(IN OUT ISOC_LONGPTR* pSPSSession, IN const ISOC_LONGPTR lMCSession
						, IN SPSSessionType type, ISOC_VOID* param, ISOC_INT paramLen, IN iSOC_OperatorStateCallback pCallBack = NULL
						,IN ISOC_DWORDPTR dwCookie = NULL, ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_CreateSPSSession
*��  �ܣ�����SPS���ƻỰ
*��  ����
        [IN]	lSPSSession  	SPS�Ự��ʶ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseSPSSession(IN ISOC_LONGPTR lSPSSession, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_RegisterRecvMsgFromSPSServerCallback
*��  �ܣ�ע���SPS���������ص�����ص�
*��  ����
		 [IN]	lSPSSession	SPS�Ự��ʶ
		 [IN]	dwCMDID		�����ʶ
		 [IN]	pCallback	�ص�����ָ��
		 [IN]	dwUserCookie �û��Զ���Cookie
		 [IN]	dwReserved	��������
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������������-4˵���Ѿ�����
		 һ��һ���Ļص���Ϣ
*��  ע�����Զ��ע��ͬһ�������ʶ�����ע���ʱ��pCallback,dwUserCookie,dwReserved����������������һ��Ҫ��ͬ������ע��ģ�
		 ����ᷢ������
******************************************************************************************************************************/						
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterRecvMsgFromSPSServerCallback(IN const ISOC_LONGPTR lSPSSession, IN const ISOC_DWORD dwCMDID
						, IN iSOC_OnGotDataCallback pCallback, IN ISOC_DWORDPTR dwUserCookie, IN ISOC_DWORDPTR dwReserved = 0);
	
/******************************************************************************************************************************
*��������iSOC_RemoveRecvMsgFromSPSServerCallback
*��  �ܣ��Ƴ���SPS���������ص�����ص�
*��  ����
		 [IN]	lSPSSession	SPS�Ự��ʶ
		 [IN]	dwCMDID		�����ʶ
		 [IN]	pCallback	�ص�����ָ��
		 [IN]	dwUserCookie �û��Զ���Cookie
		 [IN]	dwReserved	��������
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��ȡ��������������-4˵��û���ҵ�
		 ��Ӧ�Ļص���Ϣ
*��  ע������ϵͳʵ���˿��Զ��ע��һ�������ʶ�Ĺ��ܣ��������Ƴ���ʱ����ز���Ҫ��ע��ʱ����һ�²��ܳɹ��Ƴ�
******************************************************************************************************************************/	
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveRecvMsgFromSPSServerCallback(IN const ISOC_LONGPTR lSPSSession,IN const ISOC_DWORD dwCMDID
						,IN iSOC_OnGotDataCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);
					
/******************************************************************************************************************************
*��������iSOC_SendCmd2SPSServer
*��  �ܣ����������SPS������
*��  ����
		 [IN]	lSPSSession SPS�Ự��ʶ
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
iSOC_EXPORT_MODE ISOC_INT iSOC_SendCmd2SPSServer(IN const ISOC_LONGPTR lSPSSession,IN const ISOC_STR strXmlOut,IN const ISOC_INT nOutXmlLen,
												IN const ISOC_INT nCmdSubType,IN const ISOC_INT nOverTime,IN ISOC_DWORDPTR dwCookie = NULL,
												IN const iSOC_OnGotDataCallback pOnGotDataCallback = NULL,IN iSOC_OnAffairOverTimeCallback pOnOverTimeballback = NULL);


#ifdef __cplusplus
}
#endif