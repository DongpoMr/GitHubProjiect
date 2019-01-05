#pragma once
#include "iBFISDBOperation.h"
#include "IBFISDataProvider.h"
#include "iBFIS_SerializationDataMemoryModel.h"
#include "IBFISSerializeDataMemoryModel.h"
//#include "iCMSP_SimpleLock.h"
#include <map>

using namespace std;

#include "Poco/Mutex.h"

class XhBFISDataProviderImp : public IBFISDataProvider
{
public:
	XhBFISDataProviderImp();
	~XhBFISDataProviderImp();

	virtual ISOC_BOOL Init();
	virtual ISOC_BOOL UnInit();
	//查询所有
	virtual ISOC_BOOL QueryRoleInfo(vector<ST_RoleInfo>& vecInfo);
	virtual ISOC_BOOL QueryRolePurviewInfo(vector<ST_RolePurviewInfo>& vecInfo);

	virtual ISOC_BOOL QueryLocalBranchId(string& strInfo);
	virtual ISOC_BOOL QueryBranchInfo(vector<ST_BranchInfo>& vecInfo);

	virtual ISOC_BOOL QueryClientInfo(vector<ST_ClientInfo>& vecInfo);

	virtual ISOC_BOOL QueryUserMapInfo(vector<ST_UserMapInfo>& vecInfo);

	virtual ISOC_BOOL QueryProduceInfo(vector<ST_ProduceInfo>& vecInfo);

	virtual ISOC_BOOL QueryPurviewInfo(vector<ST_PurviewInfo>& vecInfo);

	virtual ISOC_BOOL QueryEmployeeInfo(vector<ST_EmployeeInfo>& vecInfo);
	virtual ISOC_BOOL QueryEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecInfo);

	virtual ISOC_BOOL QueryBusinessInfo(vector<ST_BusinessInfo>& vecInfo);
	virtual ISOC_BOOL QueryBusinessFileInfo(vector<ST_BusinessFileInfo>& vecInfo);
	virtual ISOC_BOOL QueryBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecInfo);
	virtual ISOC_BOOL QueryBusinessInfoByCondition(ST_BusinessQueryParam stInfo,vector<ST_BusinessInfo>& vecInfo,int& nTotalCount);
	virtual ISOC_BOOL QueryBusinessInfoUnFinished(vector<ST_BusinessInfo>& vecInfo,int& nTotalCount);
	virtual ISOC_BOOL QueryBusinessFileInfoByBusinessInfoId(string strInfo,vector<ST_BusinessFileInfo>& vecInfo);
	virtual ISOC_BOOL QueryBusinessRelateInfoByBusinessInfoId(string strInfo,vector<ST_BusinessRelateInfo>& vecInfo);

	//查询string类型[暂时只用于查询ClientInfo和ProduceInfo]
	virtual ISOC_BOOL QueryInfo(SyncDataType enType,vector<string>& vecInfo);

	//按条件查询
	virtual ISOC_BOOL QueryClientInfoByID(IN OUT ST_ClientInfo& sClientInfo,IN bool bOverlapped = true);
	virtual ISOC_INT QueryClientInfoByCondition(int nType,int nCount,vector<ST_ClientInfo>& vecInfo);
	virtual ISOC_BOOL QueryClientInfoByCredenitial(const string& strCredenitial,ST_ClientInfo& stClientInfo);

	virtual ISOC_BOOL QueryBranchInfoById(const string& strBranchId,ST_BranchInfo& stBranchInfo);

	virtual ISOC_BOOL QueryProduceInfoById(const string& strProduceId,ST_ProduceInfo& stProduceInfo);

	virtual ISOC_BOOL QueryUserMapInfoById(const string& strUserMapId,ST_UserMapInfo& stUserMapInfo);
	virtual ISOC_BOOL QueryUserMapInfoByEmployeeId(const string& strInfo,vector<ST_UserMapInfo>& vecInfo);

	virtual ISOC_BOOL QueryPurviewInfoById(const string& strPurviewId,ST_PurviewInfo& stPurviewInfo);

	virtual ISOC_BOOL QueryRoleInfoById(const string& strRoleId,ST_RoleInfo& stRoleInfo);
	virtual ISOC_BOOL QueryRolePurviewInfoById(const string& strRolePurviewId,ST_RolePurviewInfo& stRolePurviewInfo);
	virtual ISOC_BOOL QueryRolePurviewInfoByRoleId(const string& strInfo,vector<ST_RolePurviewInfo>& vecInfo);

	virtual ISOC_BOOL QueryEmployeeInfoById(const string& strEmployeeId,ST_EmployeeInfo& stEmployeeInfo);
	virtual ISOC_BOOL QueryEmployeeByConditions(const string& strUsername,const string& strPassword,ST_EmployeeInfo& stEmployeeInfo);
	virtual ISOC_BOOL QueryEmployeeInfoByBranchId(const string& strBranchId,vector<ST_EmployeeInfo>& vecEmployeeInfo);
	virtual ISOC_BOOL QueryEmployeePurviewInfoById(const string& strEmployeePurviewId,ST_EmployeePurviewInfo& stEmployeePurviewInfo);
	virtual ISOC_BOOL QueryEmployeePurviewInfoByEmployeeId(const string& strInfo,vector<ST_EmployeePurviewInfo>& vecInfo);
	virtual ISOC_BOOL QueryEmployeeInfoByRoleLevel(const int nRoleLevel,ST_EmployeeInfo& stEmployeeInfo);

	virtual ISOC_BOOL QueryKeyValueInfoByTypeAndCode(std::string strType,std::string strCode,vector<ST_KeyValueInfo>& vecKeyValueInfo);

	virtual ISOC_BOOL QueryBusinessInfoBySerialNumber(const std::string& strSerialNumber,ST_BusinessInfo& stInfo);
	virtual ISOC_BOOL QueryBusinessInfoById(const std::string& strBusinessId,ST_BusinessInfo& stInfo);
	virtual ISOC_BOOL QueryBusinessInfoByEmployeeIdAndCount(std::string strClientId,int nCount,map<std::string,int>& mapInfo);
	virtual ISOC_BOOL QueryHotProduceIdByCount(int nCount,map<std::string,int>& mapInfo);

	virtual ISOC_BOOL QueryTaskNotMigrated(int nCount,vector<ST_BusinessFileInfo>& vecInfos,int nMigrated = 0);
	virtual ISOC_BOOL SetMigratedBusinessFileInfo(std::string strRecordId,int nMigrated = 0);
	virtual ISOC_BOOL QueryTaskNotMigrated(int nCount,vector<ST_BusinessInfo>& vecInfos,int nMigrated = 0);
	virtual ISOC_BOOL SetMigratedBusinessInfo(std::string strBusinessInfoId,int nMigrated = 0);


	virtual ISOC_BOOL ManageRoleInfo(DBOperType oper,ST_RoleInfo stInfo);
	virtual ISOC_BOOL ManageBranchInfo(DBOperType oper,ST_BranchInfo stInfo);
	virtual ISOC_BOOL ManageClientInfo(DBOperType oper,ST_ClientInfo stInfo,int nValue = 0);
	virtual ISOC_BOOL ManageUserMapInfo(DBOperType oper,ST_UserMapInfo stInfo);
	virtual ISOC_BOOL ManageProduceInfo(DBOperType oper,ST_ProduceInfo stInfo);
	virtual ISOC_BOOL ManagePurviewInfo(DBOperType oper,ST_PurviewInfo stInfo);
	virtual ISOC_BOOL ManageEmployeeInfo(DBOperType oper,ST_EmployeeInfo stInfo);
	virtual ISOC_BOOL ManageRolePurviewInfo(DBOperType oper,ST_RolePurviewInfo stInfo);
	virtual ISOC_BOOL ManageEmployeePurviewInfo(DBOperType oper,ST_EmployeePurviewInfo stInfo);
	virtual ISOC_BOOL ManageBusinessInfo(DBOperType oper,ST_BusinessInfo stInfo);
	virtual ISOC_BOOL ManageBusinessFileInfo(DBOperType oper,ST_BusinessFileInfo stInfo);
	virtual ISOC_BOOL ManageBusinessRelateInfo(DBOperType oper,ST_BusinessRelateInfo stInfo);
	virtual ISOC_INT  ManageTransparentData(DBOperType oper,std::string strType,std::string strCode,std::string strValue);
	virtual ISOC_INT  ManageTaskPlanInfo(DBOperType enOperType,vector<ST_TaskPlan>& stInfo);

	virtual ISOC_BOOL ModifyLocalBranchId(string strLocalBranchId);

	virtual ISOC_BOOL ManageMigrateLogInfo(DBOperType enOperType,ST_MigrateLogInfo& stInfo);
	virtual ISOC_BOOL QueryMigrateLogInfoByCondition(const ST_QueryCondition& stCondition,std::vector<ST_MigrateLogInfo>& vecInfo);
	virtual ISOC_BOOL QueryMigrateLogInfoCountByCondition(const ST_QueryCondition& stCondition,int& nTotalCount);

	virtual ISOC_INT QueryBusinessRelateInfoById(std::string strId,ST_BusinessRelateInfo& stInfo);
	virtual ISOC_INT QueryBusinessFileInfoById(std::string strId,ST_BusinessFileInfo& stInfo);
	virtual ISOC_BOOL SetSyncComplete(SyncDataType enDataType,string strId);
	virtual ISOC_INT QueryProduceNeed2Sync(string strSyncTime,std::vector<ST_ProduceInfo>& vecInfo);
	virtual ISOC_INT QueryMinProduceSyncTime(string& strSyncTime);
	virtual ISOC_BOOL QueryClientInfoLastSyncTime(std::string& strTime);
	virtual ISOC_INT QueryClientInfo3Param(std::vector<ST_ClientInfo>& vecInfos ,const string& strTime = "",DWORD_PTR dwReserved = 0);

	//查询需要同步的信息
	virtual ISOC_BOOL QueryBranchInfoNeed2Sync(std::vector<ST_BranchInfo>& vecInfo);
	virtual ISOC_BOOL QueryRoleInfoNeed2Sync(std::vector<ST_RoleInfo>& vecInfo);
	virtual ISOC_BOOL QueryRolePurviewInfoNeed2Sync(std::vector<ST_RolePurviewInfo>& vecInfo);
	virtual ISOC_BOOL QueryEmployeeInfoNeed2Sync(std::vector<ST_EmployeeInfo>& vecInfo);
	virtual ISOC_BOOL QueryEmployeePurviewInfoNeed2Sync(std::vector<ST_EmployeePurviewInfo>& vecInfo);
	virtual ISOC_BOOL QueryProduceInfoNeed2Sync(std::vector<ST_ProduceInfo>& vecInfo);
	virtual ISOC_BOOL QueryBusinessInfoNeed2Sync(std::vector<ST_BusinessInfo>& vecInfo);
	virtual ISOC_BOOL QueryBusinessFileInfoNeed2Sync(std::vector<ST_BusinessFileInfo>& vecInfo);
	virtual ISOC_BOOL QueryBusinessRelateInfoNeed2Sync(std::vector<ST_BusinessRelateInfo>& vecInfo);
	virtual QueryResultType GetLocalBranchInfo(IN OUT ST_BranchInfo& stInfo);
	virtual ISOC_BOOL SendReqGetSocUserGroup();
	virtual ISOC_BOOL SendReqGetEquipmentPermission();
	virtual ISOC_BOOL ManageEmployeeInfoAndSocUser(DBOperType enOperType,ST_EmployeeInfo& sEmployeeInfo);
	virtual ISOC_BOOL UpdateUserPermission(vector<ST_EmployeeInfo>& stEmployeeInfo);
	virtual ISOC_BOOL ManageScriptInfo(DBOperType enType,ST_ScriptInfo& info,DWORD_PTR dwReserved = 0);
	virtual ISOC_BOOL QueryScriptInfo(IN int nAll,vector<ST_ScriptInfo>& vecScriptInfo);
	virtual ISOC_BOOL ManageOperateLogInfo(DBOperType enType,ST_OperateLogInfo& info,DWORD_PTR dwReserved = 0);
	virtual ISOC_BOOL QueryOperateLogInfoByEmployeeId(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strEmployeeId);
	virtual ISOC_INT QueryDeskStatus(IN std::vector<std::string> vecDisk,OUT int& nDiskTotal,OUT int& nDiskFree);
	virtual ISOC_BOOL QueryScriptInfoById(const std::string& strScriptId,ST_ScriptInfo& stInfo);
	virtual ISOC_BOOL QueryScriptInfoByCache(vector<ST_ScriptInfo>& vecScriptInfo);
	virtual ISOC_BOOL QueryNeedDelOperateLogInfo(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strTime);

	//接口-获取保存在内存模式中的数据
	virtual ISOC_INT GetSerializeDataEmployeePurviewInfo(IBFISSerializeDataMemoryModel **pEmployeePurviewInfo);
private:
	ISOC_BOOL DoLoadData();
	ISOC_BOOL ModifyConfigFile(string strBranchId) const;
	bool UpdataSerializeEmployeePurviewInfo(DBOperType oper,ST_EmployeePurviewInfo stInfo);
	void ClearDatabase();
private:
	IBFISSerializeDataMemoryModel   *m_pSerializeEmployeePurviewInfo;
	//查询
	map<string,ST_RoleInfo> m_mapRoleInfo;
	map<string,ST_ClientInfo> m_mapClientInfo;
	map<string,ST_BranchInfo> m_mapBranchInfo;
	map<string,ST_UserMapInfo> m_mapUsermapInfo;
	map<string,ST_ProduceInfo> m_mapProduceInfo;
	map<string,ST_PurviewInfo> m_mapPurviewInfo;
	map<string,ST_EmployeeInfo> m_mapEmployeeInfo;
	map<string,ST_RolePurviewInfo> m_mapRolePurviewInfo;
	map<string,ST_EmployeePurviewInfo> m_mapEmployeePurviewInfo;
	map<string,ST_ScriptInfo> m_mapScriptInfo;
	string m_strLocalBranchId;

	map<string,string> m_mapRole;
	map<string,string> m_mapClient;
	map<string,string> m_mapBranch;
	map<string,string> m_mapUsermap;
	map<string,string> m_mapProduce;
	map<string,string> m_mapPurview;
	map<string,string> m_mapEmployee;
	map<string,string> m_mapRolePurview;
	map<string,string> m_mapEmployeePurview;

	IBFISDBOperation* m_pDBOper;
	Poco::FastMutex	m_csLockRoleInfo;
	Poco::FastMutex	m_csLockClientInfo;
	Poco::FastMutex	m_csLockBranchInfo;
	Poco::FastMutex	m_csLockUsermapInfo;
	Poco::FastMutex	m_csLockProduceInfo;
	Poco::FastMutex	m_csLockPurviewInfo;
	Poco::FastMutex	m_csLockEmployeeInfo;
	Poco::FastMutex	m_csLockRolePurviewInfo;
	Poco::FastMutex	m_csLockEmployeePurviewInfo;
	Poco::FastMutex  m_csLockBusinessInfo;
	Poco::FastMutex	m_csLockBusinessFileInfo;
	Poco::FastMutex	m_csLockBusinessRelateInfo;
	Poco::FastMutex m_csLockScriptInfo;
};