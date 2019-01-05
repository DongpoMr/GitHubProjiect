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
	//指定数据库名称
	virtual ISOC_BOOL SetDataBaseName(IN string strName) = 0;

	virtual ISOC_BOOL SetLocalBranchId(string strGuid) = 0;
	//获取本地网点Id
	virtual QueryResultType GetLocalBranchInfo(IN OUT ST_BranchInfo& stInfo) = 0;

	//连接数据库
	virtual ISOC_BOOL ConnectToDataBase(IN string strIP,IN string strPort,IN string strUser,IN string strPwd) = 0;

	//获取连接信息
	virtual ISOC_BOOL GetDataBaseConfig(IN OUT string strIP,IN OUT string strPort,IN OUT string strUser,IN OUT string strPwd) = 0;

	//查询数据库的连接状态
	virtual ISOC_BOOL QuerySqlStatus() = 0;

	//当数据库断开连接或连接失败时，需重新连接
	virtual ISOC_BOOL ReConnectToDataBase() = 0;

	//断开数据库连接
	virtual ISOC_BOOL DisConnectDataBase() = 0;

	//
	virtual ISOC_INT QueryClientInfoByCondition(IN int nType,IN int nCount,vector<ST_ClientInfo>& vecInfo) = 0;
	virtual QueryResultType QueryClientInfoByID(IN OUT ST_ClientInfo& sClientInfo,IN bool bOverlapped = true) = 0;

	//银行网点信息管理
	virtual QueryResultType ManageBranchInfo(IN DBOperType enOperType, IN OUT ST_BranchInfo& sBranchInfo) = 0;

	//客户信息管理
	virtual QueryResultType ManageClientInfo(IN DBOperType enOperType, IN OUT ST_ClientInfo& sClientInfo,IN int nValue = 0) = 0;

	//角色信息管理
	virtual QueryResultType ManageRoleInfo(IN DBOperType enOperType, IN OUT ST_RoleInfo& sRoleInfo) = 0;

	//产品信息管理
	virtual QueryResultType ManageProduceInfo(IN DBOperType enOperType, IN OUT ST_ProduceInfo& sProduceInfo) = 0;

	//业务信息管理
	virtual QueryResultType ManageBusinessInfo(IN DBOperType enOperType, IN OUT ST_BusinessInfo& sBusinessInfo) = 0;

	//业务查询
	virtual QueryResultType QueryBusinessInfoBySerialNumber(IN OUT ST_BusinessInfo& sBusinessInfo,IN bool bOverlapped = true) = 0;
	virtual QueryResultType QueryBusinessInfoByID(IN OUT ST_BusinessInfo& sBusinessInfo,IN bool bOverlapped = true) = 0;
	virtual QueryResultType QueryBusinessInfoByCondition(ST_BusinessQueryParam stInfo,IN OUT vector<ST_BusinessInfo>& vecInfo) = 0;
	virtual QueryResultType QueryBusinessInfoUnFinished(IN OUT vector<ST_BusinessInfo>& vecInfo) = 0;
    virtual QueryResultType QueryBusinessInfoCountByCondition(ST_BusinessQueryParam stInfo,IN OUT int& nCount) = 0;
	virtual QueryResultType QueryBusinessFileInfoByBusinessInfoId(string strInfo,IN OUT vector<ST_BusinessFileInfo>& vecInfo) = 0;
	virtual QueryResultType QueryBusinessRelateInfoByBusinessInfoId(string strInfo,IN OUT vector<ST_BusinessRelateInfo>& vecInfo) = 0;
	
	//查询客户经常使用的产品Id以及使用次数
	virtual QueryResultType QueryBusinessInfoByEmployeeIdAndCount(string strId,int nCount,IN OUT map<std::string,int>& mapInfo) = 0;
	virtual QueryResultType QueryHotProduceIdByCount(int nCount,IN OUT map<std::string,int>& mapInfo) = 0;
	virtual QueryResultType QueryProduceNeed2Sync(IN string strSyncTime,IN OUT vector<ST_ProduceInfo>& vecInfo) = 0;
	virtual QueryResultType QueryMinProduceSyncTime(OUT string& strSyncTime) = 0;

	//雇员信息管理
	virtual QueryResultType ManageEmployeeInfo(IN DBOperType enOperType, IN OUT ST_EmployeeInfo& sEmployeeInfo) = 0;

	//雇员权限信息管理
	virtual QueryResultType ManageEmployeePurviewInfo(IN DBOperType enOperType, IN OUT ST_EmployeePurviewInfo& sEmployeePurviewInfo) = 0;
	virtual QueryResultType ManageEmployeePurviewInfoById(IN DBOperType enOperType, IN OUT ST_EmployeePurviewInfo& sEmployeePurviewInfo) = 0;

	//业务文件信息管理
	virtual QueryResultType ManageBusinessFileInfo(IN DBOperType enOperType, IN OUT ST_BusinessFileInfo& sBusinessFileInfo) = 0;

	//业务关联信息管理
	virtual QueryResultType ManageBusinessRelationInfo(IN DBOperType enOperType, IN OUT ST_BusinessRelateInfo& sBusinessRelationInfo) = 0;

	//用户权限信息管理
	virtual QueryResultType ManagePurviewInfo(IN DBOperType enOperType, IN OUT ST_PurviewInfo& sPurviewInfo) = 0;

	//角色权限信息管理
	virtual QueryResultType ManageRolePurviewInfo(IN DBOperType enOperType, IN OUT ST_RolePurviewInfo& sRolePurviewInfo) = 0;

	//用户关系映射信息管理
	virtual QueryResultType ManageUserMapInfo(IN DBOperType enOperType, IN OUT ST_UserMapInfo& sUserMapInfo) = 0;
   
	//管理Key-Value表
	virtual ISOC_INT ManageTransparentData(DBOperType oper,std::string strType,std::string strCode,std::string strValue) = 0;
	virtual ISOC_INT QueryKeyValueInfoByTypeAndCode(std::string strType,std::string strCode,vector<ST_KeyValueInfo>& vecKeyValueInfo) = 0;

	//管理任务计划表
	virtual ISOC_INT ManageTaskPlanInfo(DBOperType oper,IN OUT vector<ST_TaskPlan>& vecInfos) = 0;
    //管理话术信息
	virtual QueryResultType ManageScriptInfo(IN DBOperType enOperType, IN OUT ST_ScriptInfo& sScriptInfo) = 0;
	//管理操作体制信息
	virtual QueryResultType ManageOperateLogInfo(IN DBOperType enOperType, IN OUT ST_OperateLogInfo& sOperateLogInfo) = 0;
	//设置同步完成
	virtual ISOC_BOOL SetSyncComplete(IN SyncDataType enDataType,IN string strId) = 0;

	//删除信息
	virtual ISOC_BOOL DeleteInfoById(IN SyncDataType enDataType,IN string strId) = 0;

	//业务信息操作

	//获取身份证是否已存在
	virtual ISOC_BOOL GetIsCredenitialExisted(IN string strCredenitial) = 0;

	//获取银行信息
	virtual ISOC_INT QueryBranchInfo(vector<ST_BranchInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//获取客户信息
	virtual ISOC_INT QueryClientInfo(vector<ST_ClientInfo>& vecInfos,const string& strTime = "", DWORD_PTR dwReserved = 0 ) = 0;

	//获取角色信息
	virtual ISOC_INT QueryRoleInfo(vector<ST_RoleInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//获取产品信息
	virtual ISOC_INT QueryProduceInfo(vector<ST_ProduceInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//获取业务信息
	virtual ISOC_INT QueryBusinessInfo(vector<ST_BusinessInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//获取业务文件信息
	virtual ISOC_INT QueryBusinessFileInfo(vector<ST_BusinessFileInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//获取业务关联信息
	virtual ISOC_INT QueryBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//获取员工信息
	virtual ISOC_INT QueryEmployeeInfo(vector<ST_EmployeeInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//获取员工权限信息
	virtual ISOC_INT QueryEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//获取权限信息
	virtual ISOC_INT QueryPurviewInfo(vector<ST_PurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//获取用户组权限信息
	virtual ISOC_INT QueryRolePurviewInfo(vector<ST_RolePurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	//获取用户关系映射信息
	virtual ISOC_INT QueryUserMapInfo(vector<ST_UserMapInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;
	
	//获取话术信息
	virtual ISOC_INT QueryScriptInfo(vector<ST_ScriptInfo>& vecInfos, DWORD_PTR dwReserved = 0) = 0;

	virtual ISOC_BOOL QueryClientInfoLastSyncTime(CString& strTime,DWORD_PTR dwReserved = 0) = 0;
	
	//设置备份任务是否被迁移的标识
	virtual ISOC_BOOL SetMigratedBusinessFileInfo(std::string strRecordId,int nMigrated = 0) = 0;
	
	virtual ISOC_BOOL SetMigratedBusinessInfo(std::string strBusinessInfoId,int nMigrated = 0) = 0;

	//获取未被迁移的备份任务
	virtual QueryResultType QueryTaskNotMigrated(vector<ST_BusinessFileInfo>& vecInfos,int nCount,int nMigrated = 0) = 0;

	virtual QueryResultType QueryTaskNotMigrated(vector<ST_BusinessInfo>& vecInfos,int nCount,int nMigrated = 0) = 0;

	//迁移日志管理
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