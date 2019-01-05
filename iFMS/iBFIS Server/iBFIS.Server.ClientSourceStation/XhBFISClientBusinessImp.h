#pragma once
#include "IBFISClientSource.h"
#include "IBFISDataProvider.h"
#include "IBFISSerializeDataMemoryModel.h"

class XhBFISClientBusinessImp : public IBFISClientSource
{
public:
	XhBFISClientBusinessImp();
	~XhBFISClientBusinessImp();

	virtual ISOC_BOOL Init();
	virtual ISOC_BOOL UnInit();

	//客户端登陆，成功返回大于0的值
	virtual int UserLogin(string strUserName, string strPwd,ST_EmployeeInfo& stInfo, DWORD_PTR dwReserved = 0);
	virtual int UserLogout(string strUserName, string strPwd, DWORD_PTR dwReserved = 0);

	//产品相关
	virtual int GetProduceInfo(vector<ST_ProduceInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	virtual int ManageProduceInfo(DBOperType enType, ST_ProduceInfo& info, DWORD_PTR dwReserved = 0);
	virtual int GetProduceInfo(vector<string>& vecInfos,DWORD_PTR dwReserved = 0);

	//客户相关
	virtual int QueryClientInfoByCondition(int nType,int nCount,vector<ST_ClientInfo>& vecInfo);
	virtual int GetClientInfo(vector<ST_ClientInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	virtual int ManageClientInfo(DBOperType enType, ST_ClientInfo& info, DWORD_PTR dwReserved = 0);
	virtual int GetClientInfo(vector<string>& vecInfos,DWORD_PTR dwReserved = 0);

	//用户关系映射相关
	virtual int GetUsermapInfo(vector<ST_UserMapInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	virtual int ManageUsermapInfo(DBOperType enType, ST_UserMapInfo& info, DWORD_PTR dwReserved = 0);
	virtual bool DelUsermapByEmployeeId(const string& strInfo);

	//角色相关
	virtual int GetRoleInfo(vector<ST_RoleInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	virtual int ManageRoleInfo(DBOperType enType, ST_RoleInfo& info, DWORD_PTR dwReserved = 0);

	//角色权限相关
	virtual int GetRolePurviewInfo(vector<ST_RolePurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	virtual int ManageRolePurviewInfo(DBOperType enType, ST_RolePurviewInfo& info, DWORD_PTR dwReserved = 0);
	virtual bool DelRolePurviewByRoleId(const string& strInfo);

	//网点相关
	virtual int GetBranchInfo(vector<ST_BranchInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	virtual int ManageBranchInfo(DBOperType enType, ST_BranchInfo& info, DWORD_PTR dwReserved = 0);
	virtual bool ModifyLocalBranchId(string strLocalBranchId);
	virtual bool QueryLocalBranchId(string& strLocalBranchId);

	//员工相关
	virtual int GetEmployeeInfo(vector<ST_EmployeeInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	virtual int ManageEmployeeInfo(DBOperType enType, ST_EmployeeInfo& info, DWORD_PTR dwReserved = 0);

	//员工权限相关
	virtual int GetEmployeePurviewInfo(IBFISSerializeDataMemoryModel ** pEmployeepurviewInfo, DWORD_PTR dwReserved = 0);
	virtual int GetEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	virtual int ManageEmployeePurviewInfo(DBOperType enType, ST_EmployeePurviewInfo& info, DWORD_PTR dwReserved = 0);
	virtual bool DelEmployeePurviewByEmployeeId(const string& strInfo, int& nHasData);

	//权限相关
	virtual int GetPurviewInfo(vector<ST_PurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	virtual int ManagePurviewInfo(DBOperType enType, ST_PurviewInfo& info, DWORD_PTR dwReserved = 0);

	//业务相关
	virtual int GetBusinessInfo(vector<ST_BusinessInfo>& vecInfos,DWORD_PTR dwReserved = 0);
	virtual int ManageBusinessInfo(DBOperType enType,ST_BusinessInfo& info,DWORD_PTR dwReserved = 0);

	virtual int GetBusinessFileInfo(vector<ST_BusinessFileInfo>& vecInfos,DWORD_PTR dwReserved = 0);
	virtual int ManageBusinessFileInfo(DBOperType enType,ST_BusinessFileInfo& info,DWORD_PTR dwReserved = 0);

	virtual int GetBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecInfos,DWORD_PTR dwReserved = 0);
	virtual int ManageBusinessRelateInfo(DBOperType enType,ST_BusinessRelateInfo& info,DWORD_PTR dwReserved = 0);

	virtual int QueryBusinessInfoByCondition(ST_BusinessQueryParam stInfo,vector<ST_BusinessInfo>& vecBusiness,int& nInfoCount,vector<ST_BusinessFileInfo>& vecBusinessFile,vector<ST_BusinessRelateInfo>& vecBusinessRelate);
    virtual int QueryBusinessInfoUnFinished(vector<ST_BusinessInfo>& vecBusiness,int& nInfoCount,vector<ST_BusinessFileInfo>& vecBusinessFile,vector<ST_BusinessRelateInfo>& vecBusinessRelate);
	virtual ISOC_BOOL QueryBusinessInfo(vector<ST_BusinessInfo>& vecInfo);
	virtual ISOC_BOOL QueryProduceInfoById(const string& strProduceId,ST_ProduceInfo& stProduceInfo);
	virtual ISOC_BOOL QueryClientInfoByID(ST_ClientInfo& sClientInfo,bool bOverlapped = true);

    virtual int SetTransparentData(std::string strType,std::string strCode,std::string strValue,DWORD_PTR dwReserved = 0);
	virtual int DelTransparentData(std::string strType,std::string strCode,std::string strValue,DWORD_PTR dwReserved = 0);
	virtual int GetTransparentData(std::string strType,std::string strCode,std::string strValue,vector<ST_KeyValueInfo>& vecInfo,DWORD_PTR dwReserved = 0);
	virtual bool QueryEmployeeInfoByRoleLevel(const int nRoleLevel,ST_EmployeeInfo& stEmployeeInfo);
	virtual bool QueryBusinessInfoByEmployeeIdAndCount(std::string strId,int nCount,map<std::string,int>& mapInfo);
	virtual bool QueryHotProduceIdByCount(int nCount,map<std::string,int>& mapInfo);
	virtual ISOC_BOOL QueryKeyValueInfoByTypeAndCode(std::string strType,std::string strCode,vector<ST_KeyValueInfo>& vecKeyValueInfo);
	virtual int ManageScriptInfo(DBOperType enType,ST_ScriptInfo& info,DWORD_PTR dwReserved = 0);
	virtual int GetScriptInfoData(vector<ST_ScriptInfo>& vecInfo,DWORD_PTR dwReserved = 0);
	virtual int ManageOperateLogInfo(DBOperType enType,ST_OperateLogInfo& info,DWORD_PTR dwReserved = 0);
	virtual ISOC_BOOL QueryOperateLogInfoByEmployeeId(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strEmployeeId);
	virtual ISOC_INT QueryDeskStatus(IN std::vector<std::string> vecDisk,OUT int& nDiskTotal,OUT int& nDiskFree);
	virtual ISOC_BOOL QueryNeedDelOperateLogInfo(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strTime);
private:
	IBFISDataProvider* m_pDataProvider;
};