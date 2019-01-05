#pragma once
#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_GetMigrateV20CenterListInfo
*��  �ܣ���ȡ��ǰ�û����õ�Ǩ�����ĵ��б�
*��  ����
		 [IN] lMCSession	�������ĻỰ
		 [IN OUT] pCenterListHead ��������ͷ��ʶ��Ҫ�õ������Ǩ��������Ϣ��ʹ�������������������ȡ����ȡ�ľ���ṹ��Ϊ��ST_CenterInfo
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMigrateV20CenterListInfo(IN const ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pCenterListHead);

/******************************************************************************************************************************
*��������iSOC_CreateMigrateV20Session
*��  �ܣ����������iSOC2.0Ǩ�Ʒ�������Ǩ�ƻỰ
*��  ����
		 [IN] lMCSession	�������ĻỰ
		 [IN OUT] pMigrateSession	Ǩ�ƻỰ
		 [IN] pStateCallback	״̬�ص�
		 [IN] dwCookie			��Ӧ��״̬�ص����û�Cookie
		 [IN] dwReserved	��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��ʹ����ɺ�Ҫ��ʱ��������,����һ��Ǩ�������Ӧһ���Ự
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateMigrateV20Session(IN const ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pMigrateSession,IN iSOC_OperatorStateCallback pStateCallback = NULL,IN ISOC_DWORDPTR dwCookie = 0,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ReleaseMigrateV20Session
*��  �ܣ����������iSOC2.0Ǩ�Ʒ�������Ǩ�ƻỰ
*��  ����
		 [IN] lMigrateSession	Ǩ�ƻỰ
		 [IN] dwReserved	��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseMigrateV20Session(IN ISOC_LONGPTR lMigrateSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_SetMigrateV20Info
*��  �ܣ�����Ǩ����Ϣ
*��  ����
		[IN] lMigrateSession	Ǩ�ƻỰ
		[IN] strMigrateDesc		Ǩ������
		[IN] strTaskUniqueFlag	Ǩ�Ʊ�ʶ�����û���¼���Ǩ���йصı�ʶ��Ϣ������Ϊ��
		[IN] dwReserved	��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetMigrateV20Info(IN const ISOC_LONGPTR lMigrateSession,IN const ISOC_STR strMigrateDesc,IN const ISOC_STR strTaskUniqueFlag,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_SetMigrateV20CenterInfo
*��  �ܣ�����Ǩ������Ҫִ�е�Ǩ��������Ϣ
*��  ����
		 [IN] lMigrateSession	Ǩ�ƻỰ
		 [IN] centerInfo		Ǩ��������Ϣ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע���ڿ�ʼǨ��֮ǰ����Ҫ����Ǩ��������Ϣ
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetMigrateV20CenterInfo(IN const ISOC_LONGPTR lMigrateSession,IN ST_CenterInfo* pCenterInfo);

/******************************************************************************************************************************
*��������iSOC_SetMigrateV20Speed
*��  �ܣ�����Ǩ���ٶ�
*��  ����
		 [IN] lMigrateSession	Ǩ�ƻỰ
		 [IN] nSpeed			Ǩ���ٶ�
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetMigrateV20Speed(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nSpeed);

/******************************************************************************************************************************
*��������iSOC_AddMigrateV20TaskItem
*��  �ܣ���Ǩ�����������һ����������
*��  ����
		 [IN] lMigrateSession	Ǩ�ƻỰ
		 [IN] migrateItem		Ǩ����������Ϣ
		 [IN] dwReserved		��������
*����ֵ�����óɹ��������������������ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע����Щ�����Ǽ�ʱ�ģ���Ӻ���Ƚ����񻺴��ڱ��أ��ڿ�ʼ�����ʱ��Żᷢ�͸�������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddMigrateV20TaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ST_MigrateItem* pMigrateItem,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_DelMigrateV20TaskItem
*��  �ܣ�ɾ�����ص�δ��ʼ��Ǩ����������
*��  ����
		 [IN] lMigrateSession	Ǩ�ƻỰ
		 [IN] nTaskItemIdx		�����������������ֵ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע���˺���ֻ����ɾ������δ�ύ���������ϵ�������������Ѿ��ύ��ɾ����Ч
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelMigrateV20TaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemIdx);

/******************************************************************************************************************************
*��������iSOC_StartMigrateV20Task
*��  �ܣ���ʼǨ������
*��  ����
		 [IN] lMigrateSession	Ǩ�ƻỰ
		 [IN] dwReserved		��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartMigrateV20Task(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ControlMigrateV20Task
*��  �ܣ����Ѿ������ڷ�������Ǩ�Ʒ���������
*��  ����
		 [IN] lMigrateSession	Ǩ�ƻỰ
		 [IN] nControlCode		�����룬��ȡֵΪ��1:��ʼ,2:ֹͣ,3:��ͣ,4:ɾ��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlMigrateV20Task(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nControlCode);

/******************************************************************************************************************************
*��������iSOC_GetMigrateV20Info
*��  �ܣ���ȡǨ�Ʒ�����Ϣ
*��  ����
		 [IN] lMigrateSession	Ǩ�ƻỰ
		 [IN OUT] pInfo			Ǩ��������Ϣ
		 [IN] dwReserved		��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMigrateV20Info(IN const ISOC_LONGPTR lMigrateSession,IN OUT ST_MigrateInfo* pInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_AttachMigrateV20Task
*��  �ܣ����ӵ�һ��Ǩ������
*��  ����
		 [IN] lMigrateSession	Ǩ�ƻỰ
		 [IN] pInfo				Ǩ��������Ϣ
		 [IN] dwReserved		��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AttachMigrateV20Task(IN const ISOC_LONGPTR lMigrateSession,IN ST_MigrateInfo* pMigrateInfo,ISOC_DWORDPTR dwReserved = 0);





/******************************************************************************************************************************
*��������iSOC_CreateMigrateManagementSession
*��  �ܣ�����Ǩ�ƹ���Ự
*��  ����
		 [IN] lMCSession		�������ĻỰ
		 [IN] pMigrateManSession	Ǩ�ƹ���Ự
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateMigrateManagementSession(IN ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pMigrateManSession);

/******************************************************************************************************************************
*��������iSOC_ReleaseMigrateManagementSession
*��  �ܣ�����Ǩ�ƹ���Ự
*��  ����
		 [IN] pMigrateManSession	Ǩ�ƹ���Ự
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseMigrateManagementSession(IN ISOC_LONGPTR lMigrateManSession);

/******************************************************************************************************************************
*��������iSOC_QueryMigrateInfo
*��  �ܣ���ѯǨ��������Ϣ
*��  ����
		 [IN] pMigrateManSession	Ǩ�ƹ���Ự
		 [IN] centerInfo			������Ϣ
		 [IN] nFlishFlag			������ɱ�ʶ��1Ϊ��ɣ�2Ϊδ���
		 [IN] pDeviceList			�豸ID�б�ID֮����","�����������ѯδ��ɵ�Ǩ�������豸ID�б����Ϊ��
		 [IN] pStartTime			Ǩ�ƿ�ʼʱ��
		 [IN] pEndTime				Ǩ�ƽ���ʱ��
		 [IN] pCallback				Ǩ��������Ϣ�ص�
		 [IN] dwCookie				�ص��з��ص��û�Cookie
		 [IN] dwReserved			��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��2.0ʹ�ô˺�����ȡδ��ɵ�Ǩ������1.58��Ȼʹ����ǰ�Ľӿ�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_QueryMigrateInfo(IN const ISOC_LONGPTR lMigrateManSession,IN ST_CenterInfo* pCenterInfo,IN ISOC_INT nFlishFlag,IN const ISOC_STR pDeviceList,IN ISOC_SYSTEMTIME* pStartTime,
												IN ISOC_SYSTEMTIME* pEndTime,IN iSOC_FileMigrateInfoCallback pCallback,IN ISOC_DWORDPTR dwCookie,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_SetMigrateCatalogInfo
*��  �ܣ�����Ǩ�Ʊ�Ŀ��Ϣ
*��  ����
		 [IN] pMigrateManSession	Ǩ�ƹ���Ự
		 [IN] centerInfo			������Ϣ
		 [IN] migrateInfo			Ǩ����Ϣ
		 [IN] strCatalogInfo		��Ŀ��Ϣ�ַ���
		 [IN] nLenth				��Ŀ��Ϣ�ַ�������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetMigrateCatalogInfo(IN const ISOC_LONGPTR lMigrateManSession,IN ST_CenterInfo* pCenterInfo,IN ST_MigrateInfo* pMigrateInfo,IN ISOC_STR strCatalogInfo,IN ISOC_INT nLenth);

/******************************************************************************************************************************
*��������iSOC_SetMigrateCatalogInfo
*��  �ܣ�����Ǩ�Ʊ�Ŀ��Ϣ
*��  ����
		 [IN] pMigrateManSession	Ǩ�ƹ���Ự
		 [IN] centerInfo			������Ϣ
		 [IN] migrateInfo			Ǩ����Ϣ
		 [OUT] strCatalogInfo		��Ŀ��Ϣ�ַ���
		 [OUT] nLenth				��Ŀ��Ϣ�ַ�������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMigrateCatalogInfo(IN const ISOC_LONGPTR lMigrateManSession,IN ST_CenterInfo *pCenterInfo,IN ST_MigrateInfo *pMigrateInfo,OUT ISOC_STR* pStrCatalog,OUT ISOC_INT* pNLen);

/******************************************************************************************************************************
*��������iSOC_DelMigrateTask
*��  �ܣ�ɾ���Ѿ���ɻ���δ��ɵ�Ǩ������
*��  ����
		 [IN] pMigrateManSession	Ǩ�ƹ���Ự
		 [IN] centerInfo			������Ϣ
		 [IN] migrateInfo			Ǩ����Ϣ
		 [IN] dwReserved			��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelMigrateTask(IN const ISOC_LONGPTR lMigrateManSession,IN ST_CenterInfo *pCenterInfo,IN ST_MigrateInfo *pMigrateInfo,IN ISOC_DWORDPTR dwReserved = 0);
#ifdef __cplusplus
}
#endif