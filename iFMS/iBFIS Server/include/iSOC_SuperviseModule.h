#pragma  once
#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

///////////////////////////////////������ģ��ӿڶ���////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************************************************************
*��������iSOC_CreateSuperviseSession
*��  �ܣ�����������Ự��ʶ
*��  ����
		[IN OUT] pLSuperviseSession ������Ự��ʶ
		[IN] pCallback ������ص�����,���ڸ��ּ���¼���֪ͨ
		[IN] dwReserved ��չ����,��ΪNULL
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateSuperviseSession(IN OUT ISOC_LONGPTR* pLSuperviseSession,IN ISOC_LONGPTR pLMCSession, IN iSOC_SuperviseCallback pCallback, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_CreateSuperviseSession
*��  �ܣ����ʵʱ������¼�
*��  ����
		 [IN] pLSuperviseSession ������Ự��ʶ
		 [IN] pLLiveSession ʵʱ���Ự��ʶ
		 [IN] stDevInfo �豸��Ϣ
		 [IN] nRecordTime ¼��ʱ��
		 [IN] strDescription �������
		 [IN] ppstUserList ת���û��б�
		 [IN] nUserCount ת���û�����
		 [IN] dwReserved ��չ����,��ΪNULL
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddLiveSupervise(IN ISOC_LONGPTR pLSuperviseSession, IN ISOC_LONGPTR pLLiveSession, IN ST_DeviceItem stDevInfo,IN ISOC_SYSTEMTIME stStartTime,IN ISOC_SYSTEMTIME stEndTime, IN const ISOC_STR strDescription, IN const ST_UserInfo* pstUserList, IN ISOC_INT nUserCount,IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_CreateSuperviseSession
*��  �ܣ����VOD����¼�
*��  ����
		 [IN] pLSuperviseSession ������Ự��ʶ
		 [IN] pLVODSession VOD�Ự��ʶ
		 [IN] stVodFileInfo VOD�ļ���Ϣ
		 [IN] strDescription �������
		 [IN] ppstUserList ת���û��б�
		 [IN] nUserCount ת���û�����
		 [IN] dwReserved ��չ����,��ΪNULL
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddVodSupervise(IN ISOC_LONGPTR pLSuperviseSession, IN ISOC_LONGPTR pLVODSession, IN ST_VodFileInfo stVodFileInfo, IN ISOC_SYSTEMTIME stStartTime,IN ISOC_SYSTEMTIME stEndTime,  IN const ISOC_STR strDescription, IN const ST_UserInfo* pstUserList, IN ISOC_INT nUserCount, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_CreateSuperviseSession
*��  �ܣ��������¼�
*��  ����
		 [IN] pLSuperviseSession ������Ự��ʶ
		 [IN] nSuperviseID ����¼�ID
		 [IN] pstUserInfo �û���Ϣ
		 [IN] strDescription ������Ϣ
		 [IN] strDescription �������
		 [IN] dwCookie �û�����
		 [IN] dwReserved ��չ����,��ΪNULL
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UpdateSupervise(IN ISOC_LONGPTR pLSuperviseSession, IN ISOC_INT nSuperviseID, IN const ST_UserInfo* pstUserInfo, IN ISOC_STR strDescription, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_CreateSuperviseSession
*��  �ܣ����ʵʱ������¼�
*��  ����
		 [IN] pLSuperviseSession ������Ự��ʶ

		 [IN] pstStartTime ��ѯ��ʼʱ��
		 [IN] pstEndTime ��ѯ����ʱ��
		 [IN] dwReserved ��չ����,��ΪNULL
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע����ѯ���ͨ������sessionʱ����Ļص�������֪ͨ
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetSuperviseInfo(IN ISOC_LONGPTR pLSuperviseSession, IN ST_UserInfo* pstUserInfo, IN ISOC_SYSTEMTIME* pstStartTime, IN ISOC_SYSTEMTIME* pstEndTime, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseSuperviseSession(IN ISOC_LONGPTR pLSuperviseSession, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_DelSupervise
*��  �ܣ�ɾ������¼�
*��  ����
		 [IN] pLSuperviseSession ������Ự��ʶ
		 [IN] nSuperviseID ����¼�ID
		 [IN] pstUserInfo �û���Ϣ
		 [IN] dwCookie �û�����
		 [IN] dwReserved ��չ����,��ΪNULL
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelSupervise(IN ISOC_LONGPTR pLSuperviseSession, IN ISOC_INT nSuperviseID, IN const ST_UserInfo* pstUserInfo, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);


#ifdef __cplusplus
}
#endif