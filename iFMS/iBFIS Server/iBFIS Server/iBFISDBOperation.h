#pragma  once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include <vector>
#include <map>
using namespace std;

#include "iBFIS_UniqueDefine.h"
interface IBFISDBOperation:public CISocObject
{
	IBFISDBOperation()
	{
		m_nObjectType = OBJECT_TYPE_BFISSYNC_DBOPERATORSOURCE;
	}
	virtual ~IBFISDBOperation(){};

	virtual ISOC_BOOL KeepConnect() = 0;
	//ָ�����ݿ�����
	virtual ISOC_BOOL SetDataBaseName(IN string strName) = 0;

	virtual ISOC_BOOL SetLocalBranchId(string strGuid) = 0;
	//��ȡ��������Id
	virtual QueryResultType GetLocalBranchInfo(IN OUT ST_BranchInfo& stInfo) = 0;

	//�������ݿ�
	virtual ISOC_BOOL ConnectToDataBase(IN string strIP,IN string strPort,IN string strUser,IN string strPwd) = 0;

	//��ȡ������Ϣ
	virtual ISOC_BOOL GetDataBaseConfig(IN OUT string strIP,IN OUT string strPort,IN OUT string strUser,IN OUT string strPwd) = 0;

	//��ѯ���ݿ������״̬
	virtual ISOC_BOOL QuerySqlStatus() = 0;

	//�����ݿ�Ͽ����ӻ�����ʧ��ʱ������������
	virtual ISOC_BOOL ReConnectToDataBase() = 0;

	//�Ͽ����ݿ�����
	virtual ISOC_BOOL DisConnectDataBase() = 0;

	//
	virtual ISOC_INT QueryClientInfoByCondition(IN int nType,IN int nCount,vector<ST_ClientInfo>& vecInfo) = 0;
	virtual QueryResultType QueryClientInfoByID(IN OUT ST_ClientInfo& sClientInfo,IN bool bOverlapped = true) = 0;

	//����������Ϣ����
	virtual QueryResultType ManageBranchInfo(IN DBOperType enOperType, IN OUT ST_BranchInfo& sBranchInfo) = 0;

	//�ͻ���Ϣ����
	virtual QueryResultType ManageClientInfo(IN DBOperType enOperType, IN OUT ST_ClientInfo& sClientInfo,IN int nValue = 0) = 0;

	//��ɫ��Ϣ����
	virtual QueryResultType ManageRoleInfo(IN DBOperType enOperType, IN OUT ST_RoleInfo& sRoleInfo) = 0;

	//��Ʒ��Ϣ����
	virtual QueryResultType ManageProduceInfo(IN DBOperType enOperType, IN OUT ST_ProduceInfo& sProduceInfo) = 0;

	//ҵ����Ϣ����
	virtual QueryResultType ManageBusinessInfo(IN DBOperType enOperType, IN OUT ST_BusinessInfo& sBusinessInfo) = 0;

	//ҵ���ѯ
	virtual QueryResultType QueryBusinessInfoBySerialNumber(IN OUT ST_BusinessInfo& sBusinessInfo,IN bool bOverlapped = true) = 0;
	virtual QueryResultType QueryBusinessInfoByID(IN OUT ST_BusinessInfo& sBusinessInfo,IN bool bOverlapped = true) = 0;
	virtual QueryResultType QueryBusinessInfoByCondition(ST_BusinessQueryParam stInfo,IN OUT vector<ST_BusinessInfo>& vecInfo) = 0;
	virtual QueryResultType QueryBusinessInfoUnFinished(IN OUT vector<ST_BusinessInfo>& vecInfo) = 0;
    virtual QueryResultType QueryBusinessInfoCountByCondition(ST_BusinessQueryParam stInfo,IN OUT int& nCount) = 0;
	virtual QueryResultType QueryBusinessFileInfoByBusinessInfoId(string strInfo,IN OUT vector<ST_BusinessFileInfo>& vecInfo) = 0;
	virtual QueryResultType QueryBusinessRelateInfoByBusinessInfoId(string strInfo,IN OUT vector<ST_BusinessRelateInfo>& vecInfo) = 0;
	
	//��ѯ�ͻ�����ʹ�õĲ�ƷId�Լ�ʹ�ô���
	virtual QueryResultType QueryBusinessInfoByEmployeeIdAndCount(string strId,int nCount,IN OUT map<std::string,int>& mapInfo) = 0;
	virtual QueryResultType QueryHotProduceIdByCount(int nCount,IN OUT map<std::string,int>& mapInfo) = 0;
	virtual QueryResultType QueryProduceNeed2Sync(IN string strSyncTime,IN OUT vector<ST_ProduceInfo>& vecInfo) = 0;
	virtual QueryResultType QueryMinProduceSyncTime(OUT string& strSyncTime) = 0;

	//��Ա��Ϣ����
	virtual QueryResultType ManageEmployeeInfo(IN DBOperType enOperType, IN OUT ST_EmployeeInfo& sEmployeeInfo) = 0;

	//��ԱȨ����Ϣ����
	virtual QueryResultType ManageEmployeePurviewInfo(IN DBOperType enOperType, IN OUT ST_EmployeePurviewInfo& sEmployeePurviewInfo) = 0;
	virtual QueryResultType ManageEmployeePurviewInfoById(IN DBOperType enOperType, IN OUT ST_EmployeePurviewInfo& sEmployeePurviewInfo) = 0;

	//ҵ���ļ���Ϣ����
	virtual QueryResultType ManageBusinessFileInfo(IN DBOperType enOperType, IN OUT ST_BusinessFileInfo& sBusinessFileInfo) = 0;

	//ҵ�������Ϣ����
	virtual QueryResultType ManageBusinessRelationInfo(IN DBOperType enOperType, IN OUT ST_BusinessRelateInfo& sBusinessRelationInfo) = 0;

	//�û�Ȩ����Ϣ����
	virtual QueryResultType ManagePurviewInfo(IN DBOperType enOperType, IN OUT ST_PurviewInfo& sPurviewInfo) = 0;

	//��ɫȨ����Ϣ����
	virtual QueryResultType ManageRolePurviewInfo(IN DBOperType enOperType, IN OUT ST_RolePurviewInfo& sRolePurviewInfo) = 0;

	//�û���ϵӳ����Ϣ����
	virtual QueryResultType ManageUserMapInfo(IN DBOperType enOperType, IN OUT ST_UserMapInfo& sUserMapInfo) = 0;
   
	//����Key-Value��
	virtual ISOC_INT ManageTransparentData(DBOperType oper,std::string strType,std::string strCode,std::string strValue) = 0;
	virtual ISOC_INT QueryKeyValueInfoByTypeAndCode(std::string strType,std::string strCode,vector<ST_KeyValueInfo>& vecKeyValueInfo) = 0;

	//��������ƻ���
	virtual ISOC_INT ManageTaskPlanInfo(DBOperType oper,IN OUT vector<ST_TaskPlan>& vecInfos) = 0;
    //��������Ϣ
	virtual QueryResultType ManageScriptInfo(IN DBOperType enOperType, IN OUT ST_ScriptInfo& sScriptInfo) = 0;
	//�������������Ϣ
	virtual QueryResultType ManageOperateLogInfo(IN DBOperType enOperType, IN OUT ST_OperateLogInfo& sOperateLogInfo) = 0;
	//����ͬ�����
	virtual ISOC_BOOL SetSyncComplete(IN SyncDataType enDataType,IN string strId) = 0;

	//ɾ����Ϣ
	virtual ISOC_BOOL DeleteInfoById(IN SyncDataType enDataType,IN string strId) = 0;

	//ҵ����Ϣ����

	//��ȡ���֤�Ƿ��Ѵ���
	virtual ISOC_BOOL GetIsCredenitialExisted(IN string strCredenitial) = 0;

	//��ȡ������Ϣ
	virtual ISOC_INT QueryBranchInfo(vector<ST_BranchInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//��ȡ�ͻ���Ϣ
	virtual ISOC_INT QueryClientInfo(vector<ST_ClientInfo>& vecInfos,const string& strTime = "", DWORD_PTR dwReserved = 0 ) = 0;

	//��ȡ��ɫ��Ϣ
	virtual ISOC_INT QueryRoleInfo(vector<ST_RoleInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//��ȡ��Ʒ��Ϣ
	virtual ISOC_INT QueryProduceInfo(vector<ST_ProduceInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//��ȡҵ����Ϣ
	virtual ISOC_INT QueryBusinessInfo(vector<ST_BusinessInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//��ȡҵ���ļ���Ϣ
	virtual ISOC_INT QueryBusinessFileInfo(vector<ST_BusinessFileInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//��ȡҵ�������Ϣ
	virtual ISOC_INT QueryBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//��ȡԱ����Ϣ
	virtual ISOC_INT QueryEmployeeInfo(vector<ST_EmployeeInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//��ȡԱ��Ȩ����Ϣ
	virtual ISOC_INT QueryEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//��ȡȨ����Ϣ
	virtual ISOC_INT QueryPurviewInfo(vector<ST_PurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//��ȡ�û���Ȩ����Ϣ
	virtual ISOC_INT QueryRolePurviewInfo(vector<ST_RolePurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//��ȡ�û���ϵӳ����Ϣ
	virtual ISOC_INT QueryUserMapInfo(vector<ST_UserMapInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;
	
	//��ȡ������Ϣ
	virtual ISOC_INT QueryScriptInfo(vector<ST_ScriptInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	virtual ISOC_BOOL QueryClientInfoLastSyncTime(CString& strTime,DWORD_PTR dwReserved = 0) = 0;
	
	//���ñ��������Ƿ�Ǩ�Ƶı�ʶ
	virtual ISOC_BOOL SetMigratedBusinessFileInfo(std::string strRecordId,int nMigrated = 0) = 0;
	
	virtual ISOC_BOOL SetMigratedBusinessInfo(std::string strBusinessInfoId,int nMigrated = 0) = 0;

	//��ȡδ��Ǩ�Ƶı�������
	virtual QueryResultType QueryTaskNotMigrated(vector<ST_BusinessFileInfo>& vecInfos,int nCount,int nMigrated = 0) = 0;

	virtual QueryResultType QueryTaskNotMigrated(vector<ST_BusinessInfo>& vecInfos,int nCount,int nMigrated = 0) = 0;

	//Ǩ����־����
	virtual QueryResultType ManageMigrateLogInfo(IN DBOperType enOperType,IN OUT ST_MigrateLogInfo& stInfo) = 0;
	virtual QueryResultType QueryMigrateLogInfoByCondition(IN const ST_QueryCondition& stCondition,std::vector<ST_MigrateLogInfo>& vecInfo) = 0;
	virtual QueryResultType QueryMigrateLogInfoCountByCondition(IN const ST_QueryCondition& stCondition,int& nTotalCount) = 0;
    
    virtual ISOC_BOOL GetMCSessoon(LONG_PTR pMCSession) = 0;
    virtual ISOC_BOOL ManageEmployeeInfoAndSocUser(IN DBOperType enOperType,ST_EmployeeInfo& sEmployeeInfo) = 0;
    virtual ISOC_BOOL SendReqGetSocUserGroup() = 0;
    virtual ISOC_BOOL SendReqGetEquipmentPermission() = 0;
	virtual ISOC_BOOL UpdateUserPermission(vector<ST_EmployeeInfo>& stEmployeeInfo) = 0;
	virtual ISOC_BOOL QueryOperateLogInfoByEmployeeId(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strEmployeeId) = 0;
	virtual ISOC_INT QueryDeskStatus(IN std::vector<std::string> vecDisk,OUT int& nDiskTotal,OUT int& nDiskFree) = 0;
	virtual ISOC_BOOL QueryNeedDelOperateLogInfo(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strTime) = 0;
};