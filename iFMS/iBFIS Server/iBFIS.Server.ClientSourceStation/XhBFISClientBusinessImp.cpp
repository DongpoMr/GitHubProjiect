#include "stdafx.h"
#include "XhBFISClientBusinessImp.h"
#include "iSOC_MonFactoryManagement.h"
#include "XhLogDisplayInterface.h"
#include "IcmsP_Utility.h"

XhBFISClientBusinessImp::XhBFISClientBusinessImp()
{
	m_pDataProvider = nullptr;
}

XhBFISClientBusinessImp::~XhBFISClientBusinessImp()
{
	if (m_pDataProvider)
	{
		SAFE_DELETE(m_pDataProvider);
	}
}

ISOC_BOOL  XhBFISClientBusinessImp::Init()
{
	STRY;
	iSOC_MonFactoryManagement fmt;
	m_pDataProvider = static_cast<IBFISDataProvider*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_CACHESOURCE,"",__FUNCTION__));
	if (!m_pDataProvider)
	{
		DISPLAY_LOG("服务端业务模块","创建缓存对象失败","","",0);
		return FALSE;
	}
	else
	{
		DISPLAY_LOG("服务端业务模块","创建缓存对象成功","","",1);
	}
	m_pDataProvider->Init();
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL  XhBFISClientBusinessImp::UnInit()
{
	STRY;

	return TRUE;
	SCATCH;
	return FALSE;
}

int XhBFISClientBusinessImp::UserLogin(string strUserName, string strPwd,ST_EmployeeInfo& stInfo, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	int nFind = -1;
	//查询该用户名密码是否存在
	const string strUsername = strUserName;
	const string strPassword = strPwd;
	if(!m_pDataProvider || !m_pDataProvider->QueryEmployeeByConditions(strUserName,strPassword,stInfo))
	{
		//DISPLAY_LOG("服务端业务模块","用户名或密码错误","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::UserLogout(string strUserName, string strPwd, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;

	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::GetProduceInfo(vector<ST_ProduceInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryProduceInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询产品信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::GetProduceInfo(vector<string>& vecInfos,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (!m_pDataProvider || !m_pDataProvider->QueryInfo(DataType_ProduceInfo,vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询产品信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::ManageProduceInfo(DBOperType enType, ST_ProduceInfo& info, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManageProduceInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理产品信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::GetClientInfo(vector<ST_ClientInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryClientInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询客户信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::GetClientInfo(vector<string>& vecInfos,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (!m_pDataProvider || !m_pDataProvider->QueryInfo(DataType_ClientInfo,vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询客户信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::ManageClientInfo(DBOperType enType, ST_ClientInfo& info, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManageClientInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理客户信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::GetUsermapInfo(vector<ST_UserMapInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryUserMapInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询用户关系映射信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::ManageUsermapInfo(DBOperType enType, ST_UserMapInfo& info, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManageUserMapInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理用户关系映射信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

bool XhBFISClientBusinessImp::DelUsermapByEmployeeId(const string& strInfo)
{
	STRY;
	if (strInfo == _T(""))
	{
		return false;
	}
	vector<ST_UserMapInfo> vecInfo;
	if (!m_pDataProvider || !m_pDataProvider->QueryUserMapInfoByEmployeeId(strInfo,vecInfo))
	{
		DISPLAY_LOG("服务端业务模块","通过EmployeeId查找Usermap失败","","",0);
		return false;
	}
	for (int i = 0 ; i < vecInfo.size() ; i ++)
	{
		if(!m_pDataProvider->ManageUserMapInfo(DBO_DEL,vecInfo[i]))
		{
			return false;
		}
	}
	return true;
	SCATCH;
	return false;
}

int XhBFISClientBusinessImp::GetRoleInfo(vector<ST_RoleInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryRoleInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询角色信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::ManageRoleInfo(DBOperType enType, ST_RoleInfo& info, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManageRoleInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理角色信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::GetRolePurviewInfo(vector<ST_RolePurviewInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryRolePurviewInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询角色权限信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::ManageRolePurviewInfo(DBOperType enType, ST_RolePurviewInfo& info, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManageRolePurviewInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理角色权限信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

bool XhBFISClientBusinessImp::DelRolePurviewByRoleId(const string& strInfo)
{
	STRY;
	vector<ST_RolePurviewInfo> vecInfo;
	if (!m_pDataProvider || !m_pDataProvider->QueryRolePurviewInfoByRoleId(strInfo,vecInfo))
	{
		DISPLAY_LOG("服务端业务模块","通过RoleId查询RolePurview失败","","",0);
		return false;
	}
	for (int i = 0 ; i < vecInfo.size() ; i ++)
	{
		if (!m_pDataProvider->ManageRolePurviewInfo(DBO_DEL,vecInfo[i]))
		{
			return false;
		}
	}
	return true;
	SCATCH;
	return false;
}

int XhBFISClientBusinessImp::GetBranchInfo(vector<ST_BranchInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryBranchInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询网点信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::ManageBranchInfo(DBOperType enType, ST_BranchInfo& info, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManageBranchInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理网点信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

bool XhBFISClientBusinessImp::ModifyLocalBranchId(string strLocalBranchId)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ModifyLocalBranchId(strLocalBranchId))
	{
		DISPLAY_LOG("服务端业务模块","修改本地网点Id失败","","",0);
		return false;
	}
	return true;
	SCATCH;
	return false;
}

bool XhBFISClientBusinessImp::QueryLocalBranchId(string& strLocalBranchId)
{
	STRY;
	if (!m_pDataProvider || !m_pDataProvider->QueryLocalBranchId(strLocalBranchId))
	{
		return false;
	}
	return true;
	SCATCH;
	return false;
}
int XhBFISClientBusinessImp::GetEmployeeInfo(vector<ST_EmployeeInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryEmployeeInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询员工信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
ISOC_BOOL XhBFISClientBusinessImp::QueryKeyValueInfoByTypeAndCode(std::string strType,std::string strCode,vector<ST_KeyValueInfo>& vecKeyValueInfo)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryKeyValueInfoByTypeAndCode(strType,strCode,vecKeyValueInfo))
	{
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::ManageEmployeeInfo(DBOperType enType, ST_EmployeeInfo& info, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManageEmployeeInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理员工信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::GetEmployeePurviewInfo(IBFISSerializeDataMemoryModel ** pEmployeepurviewInfo, DWORD_PTR dwReserved)
{
	STRY;
	if (m_pDataProvider)
		return m_pDataProvider->GetSerializeDataEmployeePurviewInfo(pEmployeepurviewInfo);
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::GetEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryEmployeePurviewInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询员工权限信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::ManageEmployeePurviewInfo(DBOperType enType, ST_EmployeePurviewInfo& info, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManageEmployeePurviewInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理员工权限信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

bool XhBFISClientBusinessImp::DelEmployeePurviewByEmployeeId(const string& strInfo, int& nHasData)
{
	STRY;
	vector<ST_EmployeePurviewInfo> vecInfo;
	if (!m_pDataProvider || !m_pDataProvider->QueryEmployeePurviewInfoByEmployeeId(strInfo,vecInfo))
	{
		DISPLAY_LOG("服务端业务模块","通过EmployeId查询EmployeePurview失败","","",0);
		return false;
	}
	for (int i = 0 ; i < vecInfo.size() ; i ++)
	{
		if (!m_pDataProvider->ManageEmployeePurviewInfo(DBO_DEL,vecInfo[i]))
		{
			return false;
		}
		nHasData = 1;
	}
	return true;
	SCATCH;
	return false;
}

int XhBFISClientBusinessImp::GetPurviewInfo(vector<ST_PurviewInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryPurviewInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询权限信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::ManagePurviewInfo(DBOperType enType, ST_PurviewInfo& info, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManagePurviewInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理权限信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::GetBusinessInfo(vector<ST_BusinessInfo>& vecInfos,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryBusinessInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询业务信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
ISOC_BOOL XhBFISClientBusinessImp::QueryClientInfoByID(ST_ClientInfo& sClientInfo,bool bOverlapped)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryClientInfoByID(sClientInfo,bOverlapped))
	{
		DISPLAY_LOG("服务端业务模块","管理业务信息失败","","",0);
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
int XhBFISClientBusinessImp::ManageBusinessInfo(DBOperType enType,ST_BusinessInfo& info,DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManageBusinessInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理业务信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::GetBusinessFileInfo(vector<ST_BusinessFileInfo>& vecInfos,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryBusinessFileInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询业务文件信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::ManageBusinessFileInfo(DBOperType enType,ST_BusinessFileInfo& info,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManageBusinessFileInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理业务文件信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::GetBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecInfos,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryBusinessRelateInfo(vecInfos))
	{
		DISPLAY_LOG("服务端业务模块","查询业务关联信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::ManageBusinessRelateInfo(DBOperType enType,ST_BusinessRelateInfo& info,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->ManageBusinessRelateInfo(enType,info))
	{
		DISPLAY_LOG("服务端业务模块","管理业务关联信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::QueryBusinessInfoUnFinished(vector<ST_BusinessInfo>& vecBusiness,int& nInfoCount,vector<ST_BusinessFileInfo>& vecBusinessFile,vector<ST_BusinessRelateInfo>& vecBusinessRelate)
{
    STRY;
    if (!m_pDataProvider || m_pDataProvider->QueryBusinessInfoUnFinished(vecBusiness,nInfoCount) == QueryFail)
    {
        TTRACE("查询业务信息失败:%s[%d] \r\n",__FUNCTION__,__LINE__);
        return -1;
    }
    for (auto iter = vecBusiness.begin() ; iter != vecBusiness.end() ; ++iter)
    {
        vector<ST_BusinessFileInfo> vecInfo1;
        if (m_pDataProvider->QueryBusinessFileInfoByBusinessInfoId(iter->strBusinessInfoId,vecInfo1) != QueryFail)
        {
            for (auto it = vecInfo1.begin() ; it != vecInfo1.end() ; ++it)
            {
                vecBusinessFile.push_back(*it);
            }
        }
        vector<ST_BusinessRelateInfo> vecInfo2;
        if (m_pDataProvider->QueryBusinessRelateInfoByBusinessInfoId(iter->strBusinessInfoId,vecInfo2) != QueryFail)
        {
            for (auto it = vecInfo2.begin() ; it != vecInfo2.end() ; ++it)
            {
                vecBusinessRelate.push_back(*it);
            }
        }
    }
    return 1;
    SCATCH;
    return -1;
}
int XhBFISClientBusinessImp::QueryBusinessInfoByCondition(ST_BusinessQueryParam stInfo,vector<ST_BusinessInfo>& vecBusiness,int& nInfoCount,vector<ST_BusinessFileInfo>& vecBusinessFile,vector<ST_BusinessRelateInfo>& vecBusinessRelate)
{
	STRY;
	if (!m_pDataProvider || m_pDataProvider->QueryBusinessInfoByCondition(stInfo,vecBusiness,nInfoCount) == QueryFail)
	{
		TTRACE("查询业务信息失败:%s[%d] \r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	if (!vecBusinessFile.empty())
	{
		if (vecBusinessFile[0].nType == 5)
		{
			return TRUE;
		}
	}	
	for (auto iter = vecBusiness.begin() ; iter != vecBusiness.end() ; ++iter)
	{
		vector<ST_BusinessFileInfo> vecInfo1;
		if (m_pDataProvider->QueryBusinessFileInfoByBusinessInfoId(iter->strBusinessInfoId,vecInfo1) != QueryFail)
		{
			for (auto it = vecInfo1.begin() ; it != vecInfo1.end() ; ++it)
			{
				vecBusinessFile.push_back(*it);
			}
		}
	/*	vector<ST_BusinessRelateInfo> vecInfo2;
		if (m_pDataProvider->QueryBusinessRelateInfoByBusinessInfoId(iter->strBusinessInfoId,vecInfo2) != QueryFail)
		{
			for (auto it = vecInfo2.begin() ; it != vecInfo2.end() ; ++it)
			{
				vecBusinessRelate.push_back(*it);
			}
		}*/
	}
	return 1;
	SCATCH;
	return -1;
}
ISOC_BOOL XhBFISClientBusinessImp::QueryBusinessInfo(vector<ST_BusinessInfo>& vecInfo)
{
	STRY;
	if (!m_pDataProvider || m_pDataProvider->QueryBusinessInfo(vecInfo) == QueryFail)
	{
		TTRACE("查询业务信息失败:%s[%d] \r\n",__FUNCTION__,__LINE__);
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISClientBusinessImp::QueryProduceInfoById(const string& strProduceId,ST_ProduceInfo& stProduceInfo)
{
	STRY;
	if (!m_pDataProvider || m_pDataProvider->QueryProduceInfoById(strProduceId,stProduceInfo) == QueryFail)
	{
		TTRACE("查询业务信息失败:%s[%d] \r\n",__FUNCTION__,__LINE__);
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
int XhBFISClientBusinessImp::SetTransparentData(std::string strType,std::string strCode,std::string strValue,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (!m_pDataProvider || m_pDataProvider->ManageTransparentData(DBO_ADD,strType,strCode,strValue) < 0)
	{
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::DelTransparentData(std::string strType,std::string strCode,std::string strValue,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (!m_pDataProvider || m_pDataProvider->ManageTransparentData(DBO_DEL,strType,strCode,strValue) < 0)
	{
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

bool XhBFISClientBusinessImp::QueryEmployeeInfoByRoleLevel(const int nRoleLevel,ST_EmployeeInfo& stEmployeeInfo)
{
	STRY;
	if (!m_pDataProvider || !m_pDataProvider->QueryEmployeeInfoByRoleLevel(nRoleLevel,stEmployeeInfo))
	{
		return false;
	}
	return true;
	SCATCH;
	return false;
}

bool XhBFISClientBusinessImp::QueryBusinessInfoByEmployeeIdAndCount(std::string strClientId,int nCount,map<std::string,int>& mapInfo)
{
	STRY;
	if (m_pDataProvider && m_pDataProvider->QueryBusinessInfoByEmployeeIdAndCount(strClientId,nCount,mapInfo))
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}

bool XhBFISClientBusinessImp::QueryHotProduceIdByCount(int nCount,map<std::string,int>& mapInfo)
{
	STRY;
	if (m_pDataProvider && m_pDataProvider->QueryHotProduceIdByCount(nCount,mapInfo))
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}

int XhBFISClientBusinessImp::GetTransparentData(std::string strType,std::string strCode,std::string strValue,vector<ST_KeyValueInfo>& vecInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (!m_pDataProvider || m_pDataProvider->QueryKeyValueInfoByTypeAndCode(strType,strCode,vecInfo) < 0)
	{
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISClientBusinessImp::QueryClientInfoByCondition(int nType,int nCount,vector<ST_ClientInfo>& vecInfo)
{
	STRY;
	if (m_pDataProvider == nullptr)
	{
		return -1;
	}
	int nRet = m_pDataProvider->QueryClientInfoByCondition(nType,nCount,vecInfo);
	return nRet;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::ManageScriptInfo(DBOperType enType,ST_ScriptInfo& info,DWORD_PTR dwReserved )
{
	STRY;
	if (m_pDataProvider == nullptr)
	{
		return -1;
	}
	int nRet = m_pDataProvider->ManageScriptInfo(enType,info);
	return nRet;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::GetScriptInfoData(vector<ST_ScriptInfo>& vecInfo,DWORD_PTR dwReserved)
{
	STRY;
	if(!m_pDataProvider || !m_pDataProvider->QueryScriptInfoByCache(vecInfo))
	{
		DISPLAY_LOG("服务端业务模块","查询网点信息失败","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISClientBusinessImp::ManageOperateLogInfo(DBOperType enType,ST_OperateLogInfo& info,DWORD_PTR dwReserved )
{
	STRY;
	if (m_pDataProvider == nullptr)
	{
		return -1;
	}
	int nRet = m_pDataProvider->ManageOperateLogInfo(enType,info);
	return nRet;
	SCATCH;
	return -1;
}
ISOC_BOOL XhBFISClientBusinessImp::QueryOperateLogInfoByEmployeeId(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strEmployeeId)
{
	STRY;
	if (m_pDataProvider == nullptr)
	{
		return FALSE;
	}
	int nRet = m_pDataProvider->QueryOperateLogInfoByEmployeeId(vecInfos,strEmployeeId);
	return nRet;
	SCATCH;
	return FALSE;
}
ISOC_INT XhBFISClientBusinessImp::QueryDeskStatus(IN std::vector<std::string> vecDisk,OUT int& nDiskTotal,OUT int& nDiskFree)
{
	STRY;
	if (m_pDataProvider == nullptr)
	{
		return FALSE;
	}
	int nRet = m_pDataProvider->QueryDeskStatus(vecDisk,nDiskTotal,nDiskFree);
	return nRet;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISClientBusinessImp::QueryNeedDelOperateLogInfo(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strTime)
{
	STRY;
	if (m_pDataProvider == nullptr)
	{
		return FALSE;
	}
	int nRet = m_pDataProvider->QueryNeedDelOperateLogInfo(vecInfos,strTime);
	return nRet;
	SCATCH;
	return FALSE;
}