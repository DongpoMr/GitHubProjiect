#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////�ļ���ģ��ӿڵĶ���/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_CreateFileLockSession
*��  �ܣ������ļ�����Session
*��  ����
		 [IN] lMCSession MC�Ự
		 [IN OUT] pFileLockSession �ļ������Ự
		 [IN] pStateCallback ״̬�ص�
		 [IN] dwCookie ״̬�ص��д�����û�����
		 [IN] dwReserved ��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateFileLockSession(IN const ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pFileLockSession,
													 IN iSOC_OperatorStateCallback pStateCallback = ISOC_NULL,
													 IN ISOC_DWORDPTR dwCookie = 0,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ReleaseFileLockSession
*��  �ܣ������ļ������Ự
*��  ����
		 [IN] lFileLockSession	�ļ������Ự
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseFileLockSession(IN ISOC_LONGPTR lFileLockSession);

/******************************************************************************************************************************
*��������iSOC_GetLockCenterListHead
*��  �ܣ���ȡ��ǰ�û����õ��������ĵ��б�
*��  ����
		 [IN] lFileLockSession	�ļ������Ự
		 [IN OUT] pCenterListHead ��������ͷ��ʶ��Ҫ�õ��ļ���������������Ϣ,��ʹ�������������������ȡ����ȡ�ľ���ṹ��Ϊ��ST_CenterInfo
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetFileLockCenterListHead(IN const ISOC_LONGPTR lFileLockSession,IN OUT ISOC_LONGPTR* pCenterListHead);

/******************************************************************************************************************************
*��������iSOC_GetFileLockInfo
*��  �ܣ���ȡ������Ϣ
*��  ����
		 [IN] lFileLockSession �ļ������Ự
		 [IN] pCenterInfo Ҫ��ѯ���ļ���������
		 [IN] pCallback ���ղ�ѯ���ݵĻص�
		 [IN] dwCookie �ص��д��е��û�����
		 [IN] dwReserved ��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetFileLockInfo(IN const ISOC_LONGPTR lFileLockSession,IN const ST_CenterInfo* pCenterInfo,IN iSOC_FileLockInfoCallback pCallback,IN ISOC_DWORDPTR dwCookie,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_LockVodFile
*��  �ܣ�����VOD�ļ�
*��  ����
		 [IN] lFileLockSession �ļ������Ự
		 [IN OUT] pLockInfo ����Ϣ��������ʱ��IDΪ0�������ɹ���SDK���޸�ID��ֵΪ����ID
		 [IN] pLockItem �������ļ���Ϣ
		 [IN] nLockItemCount �ļ���Ϣ����
		 [IN] dwReserved ��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LockVodFile(IN const ISOC_LONGPTR lFileLockSession,IN OUT ST_FileLockInfo* pLockInfo,IN ST_FileLockItem* pLockItem,IN ISOC_INT nLockItemCount,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_UnLockVodFile
*��  �ܣ������Ѿ�������VOD�ļ�
*��  ����
		 [IN] lFileLockSession �ļ������Ự
		 [IN] pCenterInfo ������Ϣ
		 [IN] pLockInfo ����Ϣ
		 [IN] dwReserved ��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UnLockVodFile(IN const ISOC_LONGPTR lFileLockSession, IN ST_CenterInfo* pCenterInfo,IN ST_FileLockInfo* pLockInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_GetCenterLockSpaceInfo
*��  �ܣ���ȡ�����ļ�������Ϣ
*��  ����
		 [IN] lFileLockSession �ļ������Ự
		 [IN] pCenterInfo ������Ϣ
		 [IN OUT] pSpaceInfo �������������ռ���Ϣ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetCenterLockSpaceInfo(IN const ISOC_LONGPTR lFileLockSession,IN ST_CenterInfo* pCenterInfo,IN OUT ST_FileLockSpaceInfo* pSpaceInfo);
#ifdef __cplusplus
}
#endif