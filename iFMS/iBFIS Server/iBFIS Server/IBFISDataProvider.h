#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iBFIS_UniqueDefine.h"
#include "IBFISSerializeDataMemoryModel.h"
#include <vector>
using namespace std;

interface IBFISDataProvider : public CISocObject
{
	IBFISDataProvider()
	{
		m_nObjectType = OBJECT_TYPE_BFISSERVER_CACHESOURCE;
	}
	virtual ~IBFISDataProvider(){};

	virtual ISOC_BOOL Init() = 0;
	virtual ISOC_BOOL UnInit() = 0;
	//查询所有
	virtual ISOC_BOOL QueryBranchInfo(vector<ST_BranchInfo>& vecInfo) = 0;
	
	virtual ISOC_BOOL QueryClientInfo(vector<ST_ClientInfo>& vecInfo) = 0;
	
	virtual ISOC_BOOL QueryUserMapInfo(vector<ST_UserMapInfo>& vecInfo) = 0;
	
	virtual ISOC_BOOL QueryProduceInfo(vector<ST_ProduceInfo>& vecInfo) = 0;
	
	virtual ISOC_BOOL QueryPurviewInfo(vector<ST_PurviewInfo>& vecInfo) = 0;
	
	virtual ISOC_BOOL QueryEmployeeInfo(vector<ST_EmployeeInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryEmployeeInfoByRoleLevel(const int nRoleLevel,ST_EmployeeInfo& stEmployeeInfo) = 0;
	
	virtual ISOC_BOOL QueryRoleInfo(vector<ST_RoleInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryRolePurviewInfo(vector<ST_RolePurviewInfo>& vecInfo) = 0;
	
	virtual ISOC_BOOL QueryBusinessInfo(vector<ST_BusinessInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryBusinessFileInfo(vector<ST_BusinessFileInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecInfo) = 0;
    virtual ISOC_BOOL QueryBusinessInfoUnFinished(vector<ST_BusinessInfo>& vecInfo,int& nTotalCount) = 0;
	virtual ISOC_BOOL QueryBusinessInfoByCondition(ST_BusinessQueryParam stInfo,vector<ST_BusinessInfo>& vecInfo,int& nTotalCount) = 0;
	virtual ISOC_BOOL QueryBusinessFileInfoByBusinessInfoId(string strInfo,vector<ST_BusinessFileInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryBusinessRelateInfoByBusinessInfoId(string strInfo,vector<ST_BusinessRelateInfo>& vecInfo) = 0;
	
	//查询string类型
	virtual ISOC_BOOL QueryInfo(SyncDataType enType,vector<string>& vecInfo) = 0;
	//按条件查询
	
	virtual ISOC_BOOL QueryEmployeeByConditions(const string& strUsername,const string& strPassword,ST_EmployeeInfo& stEmployeeInfo) = 0;
	virtual ISOC_BOOL QueryEmployeeInfoByBranchId(const string& strBranchId,vector<ST_EmployeeInfo>& vecEmployeeInfo) = 0;
	
	virtual ISOC_BOOL QueryBranchInfoById(const string& strBranchId,ST_BranchInfo& stBranchInfo) = 0;

	virtual ISOC_BOOL QueryClientInfoByID(ST_ClientInfo& sClientInfo,bool bOverlapped = true) = 0;
	virtual ISOC_BOOL QueryClientInfoByCredenitial(const string& strCredenitial,ST_ClientInfo& stClientInfo) = 0;
	virtual ISOC_INT  QueryClientInfoByCondition(int nType,int nCount,vector<ST_ClientInfo>& vecInfo) = 0;

	virtual ISOC_BOOL QueryUserMapInfoById(const string& strUserMapId,ST_UserMapInfo& stUserMapInfo) = 0;
	virtual ISOC_BOOL QueryUserMapInfoByEmployeeId(const string& strInfo,vector<ST_UserMapInfo>& vecInfo) = 0;

	virtual ISOC_BOOL QueryProduceInfoById(const string& strProduceId,ST_ProduceInfo& stProduceInfo) = 0;

	virtual ISOC_BOOL QueryPurviewInfoById(const string& strPurviewId,ST_PurviewInfo& stPurviewInfo) = 0;

	virtual ISOC_BOOL QueryRoleInfoById(const string& strRoleId,ST_RoleInfo& stRoleInfo) = 0;
	virtual ISOC_BOOL QueryRolePurviewInfoById(const string& strRolePurviewId,ST_RolePurviewInfo& stRolePurviewInfo) = 0;
	virtual ISOC_BOOL QueryRolePurviewInfoByRoleId(const string& strInfo,vector<ST_RolePurviewInfo>& vecInfo) = 0;

	virtual ISOC_BOOL QueryEmployeeInfoById(const string& strEmployeeId,ST_EmployeeInfo& stEmployeeInfo) = 0;
	virtual ISOC_BOOL QueryEmployeePurviewInfoById(const string& strEmployeePurviewId,ST_EmployeePurviewInfo& stEmployeePurviewInfo) = 0;
	virtual ISOC_BOOL QueryEmployeePurviewInfoByEmployeeId(const string& strInfo,vector<ST_EmployeePurviewInfo>& vecInfo) = 0;

	virtual ISOC_BOOL QueryKeyValueInfoByTypeAndCode(std::string strType,std::string strCode,vector<ST_KeyValueInfo>& vecKeyValueInfo) = 0;

	virtual ISOC_BOOL QueryBusinessInfoBySerialNumber(const std::string& strSerialNumber,ST_BusinessInfo& stInfo) = 0;
	virtual ISOC_BOOL QueryBusinessInfoById(const std::string& strBusinessId,ST_BusinessInfo& stInfo) = 0;
	virtual ISOC_BOOL QueryBusinessInfoByEmployeeIdAndCount(std::string strClientId,int nCount,map<std::string,int>& mapInfo) = 0;
	virtual ISOC_BOOL QueryHotProduceIdByCount(int nCount,map<std::string,int>& mapInfo) = 0;

	virtual ISOC_BOOL QueryTaskNotMigrated(int nCount,vector<ST_BusinessFileInfo>& vecInfos,int nMigrated = 0) = 0;
	virtual ISOC_BOOL SetMigratedBusinessFileInfo(std::string strRecordId,int nMigrated = 0) = 0;
	virtual ISOC_BOOL QueryTaskNotMigrated(int nCount,vector<ST_BusinessInfo>& vecInfos,int nMigrated = 0) = 0;
	virtual ISOC_BOOL SetMigratedBusinessInfo(std::string strBusinessInfoId,int nMigrated = 0) = 0;

	virtual ISOC_BOOL ManageRoleInfo(DBOperType oper,ST_RoleInfo stInfo) = 0;
	virtual ISOC_BOOL ManageBranchInfo(DBOperType oper,ST_BranchInfo stInfo) = 0;
	virtual ISOC_BOOL ManageClientInfo(DBOperType oper,ST_ClientInfo stInfo,int nValue = 0) = 0;
	virtual ISOC_BOOL ManageUserMapInfo(DBOperType oper,ST_UserMapInfo stInfo) = 0;
	virtual ISOC_BOOL ManageProduceInfo(DBOperType oper,ST_ProduceInfo stInfo) = 0;
	virtual ISOC_BOOL ManagePurviewInfo(DBOperType oper,ST_PurviewInfo stInfo) = 0;
	virtual ISOC_BOOL ManageEmployeeInfo(DBOperType oper,ST_EmployeeInfo stInfo) = 0;
	virtual ISOC_BOOL ManageRolePurviewInfo(DBOperType oper,ST_RolePurviewInfo stInfo) = 0;
	virtual ISOC_BOOL ManageEmployeePurviewInfo(DBOperType oper,ST_EmployeePurviewInfo stInfo) = 0;
	virtual ISOC_BOOL ManageBusinessInfo(DBOperType oper,ST_BusinessInfo stInfo) = 0;
	virtual ISOC_BOOL ManageBusinessFileInfo(DBOperType oper,ST_BusinessFileInfo stInfo) = 0;
	virtual ISOC_BOOL ManageBusinessRelateInfo(DBOperType oper,ST_BusinessRelateInfo stInfo) = 0;
	virtual ISOC_INT  ManageTaskPlanInfo(DBOperType enOperType,vector<ST_TaskPlan>& stInfo)= 0;

	virtual ISOC_INT ManageTransparentData(DBOperType oper,std::string strType,std::string strCode,std::string strValue) = 0;
	virtual ISOC_BOOL ModifyLocalBranchId(string strLocalBranchId) = 0; 

	virtual ISOC_BOOL ManageMigrateLogInfo(DBOperType enOperType,ST_MigrateLogInfo& stInfo) = 0;
	virtual ISOC_BOOL QueryMigrateLogInfoByCondition(const ST_QueryCondition& stCondition,std::vector<ST_MigrateLogInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryMigrateLogInfoCountByCondition(const ST_QueryCondition& stCondition,int& nTotalCount) = 0;

    virtual QueryResultType GetLocalBranchInfo(ST_BranchInfo& stInfo) = 0;
	virtual ISOC_BOOL QueryLocalBranchId(string& strInfo) = 0;
	virtual ISOC_INT  QueryBusinessRelateInfoById(std::string strId,ST_BusinessRelateInfo& stInfo) = 0;
	virtual ISOC_INT  QueryBusinessFileInfoById(std::string strId,ST_BusinessFileInfo& stInfo) = 0;
	virtual ISOC_BOOL SetSyncComplete(SyncDataType enDataType,string strId) = 0;
	virtual ISOC_INT QueryProduceNeed2Sync(string strSyncTime,std::vector<ST_ProduceInfo>& vecInfo) = 0;
	virtual ISOC_INT QueryMinProduceSyncTime(string& strSyncTime) = 0;
	virtual ISOC_BOOL QueryClientInfoLastSyncTime(std::string& strTime) = 0;
	virtual ISOC_INT QueryClientInfo3Param(std::vector<ST_ClientInfo>& vecInfos ,const string& strTime = "",DWORD_PTR dwReserved = 0) = 0;
	//查询需要同步的信息
	virtual ISOC_BOOL QueryBranchInfoNeed2Sync(std::vector<ST_BranchInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryRoleInfoNeed2Sync(std::vector<ST_RoleInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryRolePurviewInfoNeed2Sync(std::vector<ST_RolePurviewInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryEmployeeInfoNeed2Sync(std::vector<ST_EmployeeInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryEmployeePurviewInfoNeed2Sync(std::vector<ST_EmployeePurviewInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryProduceInfoNeed2Sync(std::vector<ST_ProduceInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryBusinessInfoNeed2Sync(std::vector<ST_BusinessInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryBusinessFileInfoNeed2Sync(std::vector<ST_BusinessFileInfo>& vecInfo) = 0;
	virtual ISOC_BOOL QueryBusinessRelateInfoNeed2Sync(std::vector<ST_BusinessRelateInfo>& vecInfo) = 0;

    virtual ISOC_BOOL SendReqGetSocUserGroup() = 0;
    virtual ISOC_BOOL SendReqGetEquipmentPermission() = 0;
    virtual ISOC_BOOL ManageEmployeeInfoAndSocUser(IN DBOperType enOperType,ST_EmployeeInfo& sEmployeeInfo) = 0;
	virtual ISOC_BOOL UpdateUserPermission(vector<ST_EmployeeInfo>& stEmployeeInfo) = 0;
	virtual ISOC_BOOL ManageScriptInfo(DBOperType enType,ST_ScriptInfo& info,DWORD_PTR dwReserved = 0) = 0;
	virtual ISOC_BOOL QueryScriptInfo(IN int nAll,vector<ST_ScriptInfo>& vecScriptInfo) = 0;
	virtual ISOC_BOOL ManageOperateLogInfo(DBOperType enType,ST_OperateLogInfo& info,DWORD_PTR dwReserved = 0) = 0;
	virtual ISOC_BOOL QueryOperateLogInfoByEmployeeId(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strEmployeeId) = 0;
	virtual ISOC_INT QueryDeskStatus(IN std::vector<std::string> vecDisk,OUT int& nDiskTotal,OUT int& nDiskFree) = 0;
	virtual ISOC_BOOL QueryScriptInfoById(const std::string& strScriptId,ST_ScriptInfo& stInfo) = 0;
	virtual ISOC_BOOL QueryScriptInfoByCache(vector<ST_ScriptInfo>& vecScriptInfo) = 0;
	virtual ISOC_BOOL QueryNeedDelOperateLogInfo(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strTime) = 0;

	//获取序列化数据接口
	virtual ISOC_INT  GetSerializeDataEmployeePurviewInfo(IBFISSerializeDataMemoryModel** pEmployeepurviewInfo) = 0;
};