#include "stdafx.h"
#include "XhBFISDataProviderImp.h"
#include "iSOC_MonFactoryManagement.h"
#include "XhLogDisplayInterface.h"
#include "IcmsP_Utility.h"
#include "IcmsP_XmlParser.h"
#include <set>


std::string ByteToHex(BYTE *Buff, int nLen)
{
	if (Buff==NULL || nLen<=0)
		return TEXT("");

	std::string str;
	char szTemp[10];

	for (int i=0; i<nLen; i++)
	{
		sprintf_s(szTemp, TEXT("%02X"), Buff[i]);
		str+=szTemp;
	}

	return str;
}

int	HexToByte(std::string str, BYTE *Buff)
{
	if (Buff == nullptr)
		return 0;

	char szTemp[10];
	for (int i=0; i<str.size()/2; i++)
	{
		ZeroMemory(szTemp, 10);
		strncpy_s(szTemp, str.c_str()+i*2, 2);
		unsigned long nTemp = strtoul(szTemp, NULL, 16);
		Buff[i] = (BYTE)nTemp;
	}

	return str.size()/2;
}

XhBFISDataProviderImp::XhBFISDataProviderImp():m_pSerializeEmployeePurviewInfo(nullptr)
{

}
XhBFISDataProviderImp::~XhBFISDataProviderImp()
{
	iSOC_MonFactoryManagement fmt;
	if (m_pSerializeEmployeePurviewInfo)
		fmt.ReleaseObject((CISocObject**)(&m_pSerializeEmployeePurviewInfo), __FUNCTION__);
	m_pSerializeEmployeePurviewInfo = nullptr;
}

ISOC_BOOL XhBFISDataProviderImp::Init()
{
	STRY;
	iSOC_MonFactoryManagement fmt;
	m_pDBOper = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
	if (m_pDBOper == nullptr)
	{
		DISPLAY_LOG("缓存模块","创建数据库操作对象失败","","",0);
		return FALSE;
	}
	else
	{
		DISPLAY_LOG("缓存模块","创建数据库操作对象成功","","",1);
	}

	//m_pSerializeEmployeePurviewInfo = static_cast<IBFISSerializeDataMemoryModel*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_SERIALIZEDATAMEMORY, "", __FUNCTION__));
	//if (m_pSerializeEmployeePurviewInfo == nullptr)
	//{
	//	DISPLAY_LOG("缓存模块", "创建二进制内存缓存错误", "", "", 0);
	//}
	//else
	//	m_pSerializeEmployeePurviewInfo->SetEachPackageStoredDataNumber(3000);

	ClearDatabase();
	DoLoadData();
	return TRUE;
	SCATCH;
	return FALSE;
}

void XhBFISDataProviderImp::ClearDatabase()
{
	if (m_pDBOper)
	{
		std::string key;
		vector<ST_RolePurviewInfo> vecRolePurviewInfo;
		std::set<std::string> mapRolePurviewInfo;
		m_pDBOper->QueryRolePurviewInfo(vecRolePurviewInfo);
		for (auto var = vecRolePurviewInfo.begin(); var != vecRolePurviewInfo.end(); ++var)
		{
			key = var->strRoleId + var->strPruviewInfoId;
			auto find = mapRolePurviewInfo.find(key);
			if (find != mapRolePurviewInfo.end())
			{
				m_pDBOper->ManageRolePurviewInfo(DBOperType::DBO_DEL, *var);
				continue;
			}
			mapRolePurviewInfo.insert(key);
		}

		vector<ST_EmployeePurviewInfo> vecEmployeePurviewInfo;
		m_pDBOper->QueryEmployeePurviewInfo(vecEmployeePurviewInfo, 100);
		std::set<std::string> mapEmployeePurviewInfo;
		for (auto var = vecEmployeePurviewInfo.begin(); var != vecEmployeePurviewInfo.end(); ++var)
		{
			key = var->strEmployeeId + var->strPurviewInfoId;
			auto find = mapEmployeePurviewInfo.find(key);
			if (find != mapEmployeePurviewInfo.end())
			{
				m_pDBOper->ManageEmployeePurviewInfoById(DBOperType::DBO_DEL, *var);
				continue;
			}
			mapEmployeePurviewInfo.insert(key);
		}
	}
}

ISOC_BOOL XhBFISDataProviderImp::UnInit()
{
	STRY;
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::SendReqGetSocUserGroup()
{
    if(m_pDBOper)
    {
        return m_pDBOper->SendReqGetSocUserGroup();
    }
    return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::SendReqGetEquipmentPermission()
{
    if (m_pDBOper)
    {
        return m_pDBOper->SendReqGetEquipmentPermission();
    }
    return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageEmployeeInfoAndSocUser(DBOperType enOperType,ST_EmployeeInfo& sEmployeeInfo)
{
    if (m_pDBOper)
    {
        return m_pDBOper->ManageEmployeeInfoAndSocUser(enOperType,sEmployeeInfo);
    }
}
ISOC_INT XhBFISDataProviderImp::GetSerializeDataEmployeePurviewInfo(IBFISSerializeDataMemoryModel ** pEmployeepurviewInfo)
{
	STRY;
	if (nullptr == pEmployeepurviewInfo)
		return -1;
	*pEmployeepurviewInfo = m_pSerializeEmployeePurviewInfo;
	return 1;
	SCATCH;
	return -1;
}
ISOC_BOOL XhBFISDataProviderImp::DoLoadData()
{
	STRY;
	Poco::FastMutex::ScopedLock myLoadLock(m_csLockEmployeePurviewInfo);
	if (!m_pDBOper || !m_pDBOper->QuerySqlStatus())
	{
		DISPLAY_LOG("缓存模块","数据库未连接","","",0);
		return FALSE;
	}
	//
	DWORD_PTR dwAll = 1;
	vector<ST_BranchInfo> vecBranchInfo;
	std::string strInfo;
	if(!m_pDBOper->QueryBranchInfo(vecBranchInfo,dwAll))
	{
		DISPLAY_LOG("缓存模块","加载网点信息到缓存失败","","",0);
	}
	for (auto iter = vecBranchInfo.begin(); iter != vecBranchInfo.end() ; ++iter)
	{
		m_mapBranchInfo[iter->strBranchId] = *iter;
		if(iter->ConvertToString(strInfo))
			m_mapBranch[iter->strBranchId] = strInfo;
	}
	vector<ST_ClientInfo> vecClientInfo;
	if(!m_pDBOper->QueryClientInfo(vecClientInfo,"",dwAll))
	{
		DISPLAY_LOG("缓存模块","加载客户信息到缓存失败","","",0);
	}
	for (auto iter = vecClientInfo.begin() ; iter != vecClientInfo.end() ; ++iter)
	{
		std::string strClientKey = iter->strClientId + iter->strCredenitial;
		m_mapClientInfo[strClientKey] = *iter;
		if(iter->ConvertToString(strInfo))
			m_mapClient[strClientKey] = strInfo;
	}
	vector<ST_EmployeeInfo> vecEmployeeInfo;
	if(!m_pDBOper->QueryEmployeeInfo(vecEmployeeInfo,dwAll))
	{
		DISPLAY_LOG("缓存模块","加载员工信息到缓存失败","","",0);
	}
	for (auto iter = vecEmployeeInfo.begin() ; iter != vecEmployeeInfo.end() ; ++iter)
	{
		BYTE cbyte[40]={0};
		HexToByte(iter->strPassword,cbyte);
		iter->strPassword = reinterpret_cast<char*>(cbyte);
		m_mapEmployeeInfo[iter->strEmployeeId] = *iter;
		if(iter->ConvertToString(strInfo))
		{
			m_mapEmployee[iter->strEmployeeId] = strInfo;
		}
	}
	vector<ST_EmployeePurviewInfo> vecEmployeePurviewInfo;
	if (m_pSerializeEmployeePurviewInfo)
	{
		ST_EmployeePurviewInfoList stList;
		if (m_pDBOper->QueryEmployeePurviewInfo(stList.vecEmployeePurview, dwAll))
		{
			stList.ConvertToArrary(m_pSerializeEmployeePurviewInfo);
		}
		else
		{
			DISPLAY_LOG("缓存模块", "加载员工权限信息到缓存失败", "", "", 0);
		}
	}
	else
	{
		if (!m_pDBOper->QueryEmployeePurviewInfo(vecEmployeePurviewInfo, dwAll))
		{
			DISPLAY_LOG("缓存模块", "加载员工权限信息到缓存失败", "", "", 0);
		}
		for (auto iter = vecEmployeePurviewInfo.begin(); iter != vecEmployeePurviewInfo.end(); ++iter)
		{
			m_mapEmployeePurviewInfo[iter->strEmployeePurviewId] = *iter;
			if (iter->ConvertToString(strInfo))
				m_mapEmployeePurview[iter->strEmployeePurviewId] = strInfo;
		}
	}
	

	vector<ST_ProduceInfo> vecProduceInfo;
	if(!m_pDBOper->QueryProduceInfo(vecProduceInfo,dwAll))
	{
		DISPLAY_LOG("缓存模块","加载产品信息到缓存失败","","",0);
	}
	TTRACE("[缓存模块]加载的产品信息数量为:%d \r\n",vecProduceInfo.size());
	for (auto iter = vecProduceInfo.begin() ; iter != vecProduceInfo.end() ; ++iter)
	{
		m_mapProduceInfo[iter->strProduceId] = *iter;
		if(iter->ConvertToString(strInfo))
			m_mapProduce[iter->strProduceId] = strInfo;
	}
	vector<ST_RoleInfo> vecRoleInfo;
	if(!m_pDBOper->QueryRoleInfo(vecRoleInfo,dwAll))
	{
		DISPLAY_LOG("缓存模块","加载角色信息到缓存失败","","",0);
	}
	for (auto iter = vecRoleInfo.begin() ; iter != vecRoleInfo.end() ; ++iter)
	{
		m_mapRoleInfo[iter->strRoleInfoId] = *iter;
		if(iter->ConvertToString(strInfo))
			m_mapRole[iter->strRoleInfoId] = strInfo;
	}
	vector<ST_RolePurviewInfo> vecRolePurviewInfo;
	if(!m_pDBOper->QueryRolePurviewInfo(vecRolePurviewInfo,dwAll))
	{
		DISPLAY_LOG("缓存模块","加载角色权限信息到缓存失败","","",0);
	}
	for (auto iter = vecRolePurviewInfo.begin() ; iter != vecRolePurviewInfo.end() ; ++iter)
	{
		m_mapRolePurviewInfo[iter->strRoleInfoPurviewId] = *iter;
		if(iter->ConvertToString(strInfo))
			m_mapRolePurview[iter->strRoleInfoPurviewId] = strInfo;
	}
	vector<ST_UserMapInfo> vecUserMapInfo;
	if(!m_pDBOper->QueryUserMapInfo(vecUserMapInfo,dwAll))
	{
		DISPLAY_LOG("缓存模块","加载用户关系映射信息到缓存失败","","",0);
	}
	for (auto iter = vecUserMapInfo.begin() ; iter != vecUserMapInfo.end() ; ++iter)
	{
		m_mapUsermapInfo[iter->strUserMapInfoId] = *iter;
		if(iter->ConvertToString(strInfo))
			m_mapUsermap[iter->strUserMapInfoId] = strInfo;
	}
	vector<ST_PurviewInfo> vecPurviewInfo;
	if (!m_pDBOper->QueryPurviewInfo(vecPurviewInfo,dwAll))
	{
		DISPLAY_LOG("缓存模块","加载权限信息到缓存失败","","",0);
	}
	for (auto iter = vecPurviewInfo.begin() ; iter != vecPurviewInfo.end() ; ++iter)
	{
		m_mapPurviewInfo[iter->strPurviewInfoId] = *iter;
		if(iter->ConvertToString(strInfo))
			m_mapPurview[iter->strPurviewInfoId] = strInfo;
	}

	vector<ST_ScriptInfo> vecScriptInfo;
	if (!m_pDBOper->QueryScriptInfo(vecScriptInfo,dwAll))
	{
		DISPLAY_LOG("缓存模块","加载权限信息到缓存失败","","",0);
	}
	for (auto iter = vecScriptInfo.begin() ; iter != vecScriptInfo.end() ; ++iter)
	{
		m_mapScriptInfo[iter->strScriptId] = *iter;
		/*if(iter->ConvertToString(strInfo))
			m_mapScriptInfo[iter->vecScriptInfo] = strInfo;*/
	}
// 	if (!m_pDBOper->GetLocalBranchId(m_strLocalBranchId))
// 	{
// 		DISPLAY_LOG("缓存模块","获取本地网点Id失败","","",0);
// 	}
	QueryLocalBranchId(m_strLocalBranchId);
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryRoleInfo(vector<ST_RoleInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockRoleInfo);
	vecInfo.clear();
	for (auto iter = m_mapRoleInfo.begin() ; iter != m_mapRoleInfo.end() ; ++iter)
	{
		vecInfo.push_back(iter->second);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryBranchInfo(vector<ST_BranchInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockBranchInfo);
	vecInfo.clear();
	for (auto iter = m_mapBranchInfo.begin() ; iter != m_mapBranchInfo.end() ; ++iter)
	{
		vecInfo.push_back(iter->second);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryClientInfo(vector<ST_ClientInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockClientInfo);
	vecInfo.clear();
	for (auto iter = m_mapClientInfo.begin() ; iter != m_mapClientInfo.end() ; ++iter)
	{
		vecInfo.push_back(iter->second);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryUserMapInfo(vector<ST_UserMapInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockUsermapInfo);
	vecInfo.clear();
	for (auto iter = m_mapUsermapInfo.begin() ; iter != m_mapUsermapInfo.end() ; ++iter)
	{
		vecInfo.push_back(iter->second);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryProduceInfo(vector<ST_ProduceInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockProduceInfo);
	vecInfo.clear();
	for (auto iter = m_mapProduceInfo.begin() ; iter != m_mapProduceInfo.end() ; ++iter)
	{
		vecInfo.push_back(iter->second);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryPurviewInfo(vector<ST_PurviewInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockPurviewInfo);
	vecInfo.clear();
	for (auto iter = m_mapPurviewInfo.begin() ; iter != m_mapPurviewInfo.end() ; ++iter)
	{
		vecInfo.push_back(iter->second);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryEmployeeInfo(vector<ST_EmployeeInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockEmployeeInfo);
	vecInfo.clear();
	for (auto iter = m_mapEmployeeInfo.begin() ; iter != m_mapEmployeeInfo.end() ; ++iter)
	{
		vecInfo.push_back(iter->second);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryRolePurviewInfo(vector<ST_RolePurviewInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockRolePurviewInfo);
	vecInfo.clear();
	for (auto iter = m_mapRolePurviewInfo.begin() ; iter != m_mapRolePurviewInfo.end() ; ++iter)
	{
		vecInfo.push_back(iter->second);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockEmployeePurviewInfo);
	vecInfo.clear();
	for (auto iter = m_mapEmployeePurviewInfo.begin() ; iter != m_mapEmployeePurviewInfo.end() ; ++iter)
	{
		vecInfo.push_back(iter->second);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryBusinessInfo(vector<ST_BusinessInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockBusinessInfo);
	if (!m_pDBOper || m_pDBOper->QueryBusinessInfo(vecInfo) <= 0)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryBusinessFileInfo(vector<ST_BusinessFileInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockBusinessFileInfo);
	if (!m_pDBOper || m_pDBOper->QueryBusinessFileInfo(vecInfo) <= 0)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockBusinessRelateInfo);
	if (!m_pDBOper || m_pDBOper->QueryBusinessRelateInfo(vecInfo) <= 0)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryLocalBranchId(string& strInfo)
{
	STRY;
	ST_BranchInfo stInfo;
	int nRet = -1;
	if (!m_pDBOper || (nRet = m_pDBOper->GetLocalBranchInfo(stInfo)) == QueryFail)
	{
		return FALSE; 
	}
	else if (nRet == QuerySuccessWithoutResult)
	{
		strInfo = _T("");
	}
	else
	{
		strInfo = stInfo.strBranchId;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryEmployeeByConditions(const string& strUsername,const string& strPassword,ST_EmployeeInfo& stEmployeeInfo)
{
	STRY;
	BOOL bFind = FALSE;
	vector<ST_EmployeeInfo> vecInfo;
	if (m_strLocalBranchId == _T(""))
	{
		QueryLocalBranchId(m_strLocalBranchId);
	}
	if (m_strLocalBranchId == "" || !QueryEmployeeInfoByBranchId(m_strLocalBranchId,vecInfo))
	{
		return FALSE;
	}
	else
	{
		for (auto iter = m_mapBranchInfo.begin() ; iter != m_mapBranchInfo.end() ; ++iter)
		{
			if(iter->second.strParentId == m_strLocalBranchId)
			{
				QueryEmployeeInfoByBranchId(iter->second.strBranchId,vecInfo);
			}
		}
	}
	if (vecInfo.size() < 1)
	{
		return FALSE;
	}
	/*MD5 iMD5;
	iMD5.GenerateMD5((unsigned char*)strPassword.c_str(), strlen(strPassword.c_str()));
	string MD5Passwrd = iMD5.ToString();
	string MD5Passwrd = ByteToHex((unsigned char*)strPassword.c_str(),strlen(strPassword.c_str()))*/;
	for (int i = 0 ; i < vecInfo.size() ; i ++)
	{
		if(vecInfo[i].strName == strUsername && vecInfo[i].strPassword == strPassword)
		{
			bFind = TRUE;
			stEmployeeInfo = vecInfo[i];
			break;
		}
	}
	return bFind;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryEmployeeInfoByBranchId(const string& strBranchId,vector<ST_EmployeeInfo>& vecEmployeeInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockEmployeeInfo);
	for (auto iter = m_mapEmployeeInfo.begin() ; iter != m_mapEmployeeInfo.end() ; ++iter)
	{
		if(iter->second.strBranchId == strBranchId || iter->second.strExtendedInfo2.compare("100") == 0)
		{
			vecEmployeeInfo.push_back(iter->second);
		}
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryRoleInfoById(const string& strRoleId,ST_RoleInfo& stRoleInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockRoleInfo);
	auto iter = m_mapRoleInfo.find(strRoleId);
	if (iter != m_mapRoleInfo.end())
	{
		stRoleInfo = iter->second;
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryBranchInfoById(const string& strBranchId,ST_BranchInfo& stBranchInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockBranchInfo);
	auto iter = m_mapBranchInfo.find(strBranchId);
	if (iter != m_mapBranchInfo.end())
	{
		stBranchInfo = iter->second;
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryClientInfoByCredenitial(const string& strCredenitial,ST_ClientInfo& stClientInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockClientInfo);
	auto iter = m_mapClientInfo.find(strCredenitial);
	if (iter != m_mapClientInfo.end())
	{
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryUserMapInfoById(const string& strUserMapId,ST_UserMapInfo& stUserMapInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockUsermapInfo);
	auto iter = m_mapUsermapInfo.find(strUserMapId);
	if (iter != m_mapUsermapInfo.end())
	{
		stUserMapInfo = iter->second;
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryUserMapInfoByEmployeeId(const string& strInfo,vector<ST_UserMapInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockUsermapInfo);
	for (auto iter = m_mapUsermapInfo.begin() ; iter != m_mapUsermapInfo.end() ; ++iter)
	{
		if(iter->second.strEmployeeId == strInfo)
		{
			vecInfo.push_back(iter->second);
		}
	}

	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryProduceInfoById(const string& strProduceId,ST_ProduceInfo& stProduceInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockProduceInfo);
	auto iter = m_mapProduceInfo.find(strProduceId);
	if (iter != m_mapProduceInfo.end())
	{
		stProduceInfo = iter->second;
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryPurviewInfoById(const string& strPurviewId,ST_PurviewInfo& stPurviewInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockPurviewInfo);
	auto iter = m_mapPurviewInfo.find(strPurviewId);
	if (iter != m_mapPurviewInfo.end())
	{
		stPurviewInfo = iter->second;
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryEmployeeInfoById(const string& strEmployeeId,ST_EmployeeInfo& stEmployeeInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockEmployeeInfo);
	auto iter = m_mapEmployeeInfo.find(strEmployeeId);
	if (iter != m_mapEmployeeInfo.end())
	{
		stEmployeeInfo = iter->second;
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryRolePurviewInfoById(const string& strRolePurviewId,ST_RolePurviewInfo& stRolePurviewInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockRolePurviewInfo);
	auto iter = m_mapRolePurviewInfo.find(strRolePurviewId);
	if (iter != m_mapRolePurviewInfo.end())
	{
		stRolePurviewInfo = iter->second;
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryRolePurviewInfoByRoleId(const string& strInfo,vector<ST_RolePurviewInfo>& vecInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockRolePurviewInfo);
	for (auto iter = m_mapRolePurviewInfo.begin() ; iter != m_mapRolePurviewInfo.end() ; ++iter)
	{
		if (iter->second.strRoleId == strInfo)
		{
			vecInfo.push_back(iter->second);
		}
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryEmployeePurviewInfoById(const string& strEmployeePurviewId,ST_EmployeePurviewInfo& stEmployeePurviewInfo)
{
	STRY;
	if (m_pSerializeEmployeePurviewInfo)
	{
		int nKey = 0;
		int nDataPos = 0;
		iCMSP_ReadLock wrLock(*m_pSerializeEmployeePurviewInfo->GetWRLock(), __FUNCTION__);
		int nRet = m_pSerializeEmployeePurviewInfo->GetDataPacketPos(strEmployeePurviewId, nKey, nDataPos);
		if (nRet > 0)
		{
			BYTE *pData = nullptr;
			int nUserDataSize = 0;
			int nTotalSize = 0;
			nRet = m_pSerializeEmployeePurviewInfo->GetDataPacket(nKey, &pData, nUserDataSize, nTotalSize);
			if (nRet > 0)
			{
				ST_EmployeePurviewInfoList stList;
				nRet = stList.ConvertToStruct(pData, nUserDataSize, stList.vecEmployeePurview);
				if (stList.vecEmployeePurview.size() >= nDataPos && nDataPos > 0)
				{
					stEmployeePurviewInfo = stList.vecEmployeePurview[nDataPos - 1];
					return TRUE;
				}
			}
		}
	}
	else
	{
		Poco::FastMutex::ScopedLock myLock(m_csLockEmployeePurviewInfo);
		auto iter = m_mapEmployeePurviewInfo.find(strEmployeePurviewId);
		if (iter != m_mapEmployeePurviewInfo.end())
		{
			stEmployeePurviewInfo = iter->second;
			return TRUE;
		}
	}


	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryEmployeePurviewInfoByEmployeeId(const string& strInfo,vector<ST_EmployeePurviewInfo>& vecInfo)
{
	STRY;
	if (m_pSerializeEmployeePurviewInfo)
	{
		std::unordered_map<std::string, SERIALIZE_POS_INFO_STB> mapDataPosInfo;
		iCMSP_ReadLock wrLock(*m_pSerializeEmployeePurviewInfo->GetWRLock(), __FUNCTION__);
		int nRet = m_pSerializeEmployeePurviewInfo->GetDataPacketPos(strInfo, mapDataPosInfo);
		if (nRet > 0)
		{
			for each (auto &var in mapDataPosInfo)
			{
				int nKey = var.second.nPacketKey;
				int nDataPos = var.second.nDataPos;
				BYTE *pData = nullptr;
				int nUserDataSize = 0;
				int nTotalSize = 0;
				nRet = m_pSerializeEmployeePurviewInfo->GetDataPacket(nKey, &pData, nUserDataSize, nTotalSize);
				if (nRet > 0)
				{
					ST_EmployeePurviewInfoList stList;
					nRet = stList.ConvertToStruct(pData, nUserDataSize, stList.vecEmployeePurview);
					if (stList.vecEmployeePurview.size() >= nDataPos && nDataPos > 0)
					{
						vecInfo.push_back(stList.vecEmployeePurview[nDataPos - 1]);
					}
				}
			}
		}
	}
	else
	{
		Poco::FastMutex::ScopedLock myLock(m_csLockEmployeePurviewInfo);
		for (auto iter = m_mapEmployeePurviewInfo.begin(); iter != m_mapEmployeePurviewInfo.end(); ++iter)
		{
			if (iter->second.strEmployeeId == strInfo)
			{
				vecInfo.push_back(iter->second);
			}
		}
	}

	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryBusinessInfoUnFinished(vector<ST_BusinessInfo>& vecInfo,int& nTotalCount)
{
    STRY;
    if (!m_pDBOper || m_pDBOper->QueryBusinessInfoUnFinished(vecInfo) == QueryFail)      
    {
        return FALSE;
    }
    nTotalCount = 0;
    return TRUE;
    SCATCH;
    return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryBusinessInfoByCondition(ST_BusinessQueryParam stInfo,vector<ST_BusinessInfo>& vecInfo,int& nTotalCount)
{
	STRY;
#if 1
	if (!m_pDBOper || m_pDBOper->QueryBusinessInfoByCondition(stInfo,vecInfo) == QueryFail ||
		m_pDBOper->QueryBusinessInfoCountByCondition(stInfo,nTotalCount) == QueryFail)
	{
		return FALSE;
	}
#else
	vector<ST_BusinessInfo> vecBusiness;
	//查询所有业务信息
	if (!m_pDBOper || m_pDBOper->QueryBusinessInfo(vecBusiness,1) < 1)
	{
		return FALSE;
	}
	for (auto iter = vecBusiness.begin() ; iter  != vecBusiness.end() ; iter ++)
	{
		if (stInfo.strBranchId != _T("") && iter->strBranchId != stInfo.strBranchId || 
			stInfo.strCustomerId != _T("") && iter->strClientId != stInfo.strCustomerId ||
			stInfo.strEmployeeId != _T("") && iter->strEmployeeId != stInfo.strEmployeeId ||
			stInfo.strProduceId != _T("") && iter->strProduceId != stInfo.strProduceId)
		{
			continue;
		}
		CString strTemp[3];
		strTemp[0] = iter->strDateTime.c_str();
		strTemp[1] = stInfo.strStartTime.c_str();
		strTemp[2] = stInfo.strEndTime.c_str();
		int nYear[3],nMon[3],nDay[3],nHour[3],nMin[3],nSec[3];
		for (int i = 0 ; i < 3 ; i ++)
		{
			if(strTemp[i].Find("-") != -1)
			{
				_stscanf(strTemp[i],_T("%d-%d-%d %d:%d:%d"),&nYear[i],&nMon[i],&nDay[i],&nHour[i],&nMin[i],&nSec[i]);
			}
			else
			{
				_stscanf(strTemp[i],_T("%d/%d/%d %d:%d:%d"),&nYear[i],&nMon[i],&nDay[i],&nHour[i],&nMin[i],&nSec[i]);
			}
		}
		CTime t0(nYear[0],nMon[0],nDay[0],nHour[0],nMin[0],nSec[0]);
		CTime t1(nYear[1],nMon[1],nDay[1],nHour[1],nMin[1],nSec[1]);
		CTime t2(nYear[2],nMon[2],nDay[2],nHour[2],nMin[2],nSec[2]);
		if(t0 > t1 && t2 > t0)
		{
			vecInfo.push_back(*iter);
		}
	}
#endif
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryBusinessFileInfoByBusinessInfoId(string strInfo,vector<ST_BusinessFileInfo>& vecInfo)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->QueryBusinessFileInfoByBusinessInfoId(strInfo,vecInfo) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryBusinessRelateInfoByBusinessInfoId(string strInfo,vector<ST_BusinessRelateInfo>& vecInfo)
{
	STRY;
	/*if (!m_pDBOper || m_pDBOper->QueryBusinessRelateInfoByBusinessInfoId(strInfo,vecInfo) == QueryFail)
	{
	return FALSE;
	}*/
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryEmployeeInfoByRoleLevel(const int nRoleLevel,ST_EmployeeInfo& stEmployeeInfo)
{
	
	std::string strRoleId = "";
	//TTRACE("角色条数：%d 员工条数: %d",m_mapRoleInfo.size(),m_mapEmployeeInfo.size());
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockRoleInfo);
	for (auto iter  = m_mapRoleInfo.begin() ; iter != m_mapRoleInfo.end() ; ++iter)
	{
		if (iter->second.strBranchInfoId == stEmployeeInfo.strBranchId && iter->second.nRoleLevel == nRoleLevel)
		{
			strRoleId = iter->second.strRoleInfoId;
			break;
		}
	}
	SCATCH;

	STRY;
	if(strRoleId != "")
	{
		Poco::FastMutex::ScopedLock myLock(m_csLockEmployeeInfo);
		for (auto it = m_mapEmployeeInfo.begin() ;it != m_mapEmployeeInfo.end() ; ++it)
		{
			TTRACE("员工NAME:%s,员工role:%s, 超级管理员role：%s \r\n",it->second.strName.c_str(),it->second.strRoleId.c_str(),strRoleId.c_str());
			if (it->second.strRoleId == strRoleId)
			{
				stEmployeeInfo = it->second;
				return TRUE;
			}
		}
		DISPLAY_LOG("数据库模块","查询超级管理员失败","","",0);
	}
	else
	{
		TTRACE("管理员角色为空");
		m_strLocalBranchId = stEmployeeInfo.strBranchId;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::ManageRoleInfo(DBOperType oper,ST_RoleInfo stInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockRoleInfo);
	if (!m_pDBOper || !m_pDBOper->QuerySqlStatus())
	{
		DISPLAY_LOG("缓存模块","数据库未连接","","",0);
		return FALSE;
	}
	if(m_pDBOper->ManageRoleInfo(oper,stInfo) == QueryFail)
	{
		return FALSE;
	}
	else
	{
		auto iter = m_mapRoleInfo.find(stInfo.strRoleInfoId);
		if (iter != m_mapRoleInfo.end())
		{
			if (oper == DBO_DEL)
			{
				m_mapRoleInfo.erase(iter);
			}
			else if (oper ==DBO_UPDATE)
			{
				iter->second = stInfo;
			}
		}
		else
		{
			if (oper == DBO_ADD)
			{
				m_mapRoleInfo[stInfo.strRoleInfoId] = stInfo;
			}
		}
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageBranchInfo(DBOperType oper,ST_BranchInfo stInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockBranchInfo);
	if (!m_pDBOper || !m_pDBOper->QuerySqlStatus())
	{
		DISPLAY_LOG("缓存模块","数据库未连接","","",0);
		return FALSE;
	}
	if(m_pDBOper->ManageBranchInfo(oper,stInfo) == QueryFail)
	{
		return FALSE;
	}
	else
	{
		auto iter = m_mapBranchInfo.find(stInfo.strBranchId);
		if (iter != m_mapBranchInfo.end())
		{
			if (oper == DBO_DEL)
			{
				m_mapBranchInfo.erase(iter);
			}
			else if (oper ==DBO_UPDATE)
			{
				iter->second = stInfo;
			}
		}
		else
		{
			if (oper == DBO_ADD)
			{
				m_mapBranchInfo[stInfo.strBranchId] = stInfo;
			}
		}
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageClientInfo(DBOperType oper,ST_ClientInfo stInfo,int nValue /*= 0*/)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockClientInfo);
	if (!m_pDBOper || !m_pDBOper->QuerySqlStatus())
	{
		DISPLAY_LOG("缓存模块","数据库未连接","","",0);
		return FALSE;
	}
	if(m_pDBOper->ManageClientInfo(oper,stInfo,nValue) == QueryFail)
	{
		return FALSE;
	}
	else
	{
		std::string strClientKey = stInfo.strClientId + stInfo.strCredenitial;
		auto iter = m_mapClientInfo.find(strClientKey);
		if (iter != m_mapClientInfo.end())
		{
			if (oper == DBO_DEL)
			{
				m_mapClientInfo.erase(iter);
			}
			else if (oper == DBO_UPDATE)
			{
				iter->second = stInfo;
			}
		}
		else
		{
			if (oper == DBO_ADD)
			{
				m_mapClientInfo[strClientKey] = stInfo;
			}
		}
		//
		string strInfo;
		auto it = m_mapClient.find(strClientKey);
		if (it != m_mapClient.end())
		{
			if (oper == DBO_DEL)
			{
				m_mapClient.erase(it);
			}
			else if (oper ==DBO_UPDATE)
			{
				if(stInfo.ConvertToString(strInfo))
					it->second = strInfo;
			}
		}
		else
		{
			if (oper == DBO_ADD)
			{
				if(stInfo.ConvertToString(strInfo))
					m_mapClient[strClientKey] = strInfo;
			}
		}
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageUserMapInfo(DBOperType oper,ST_UserMapInfo stInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockUsermapInfo);
	if (!m_pDBOper || !m_pDBOper->QuerySqlStatus())
	{
		DISPLAY_LOG("缓存模块","数据库未连接","","",0);
		return FALSE;
	}
	if(m_pDBOper->ManageUserMapInfo(oper,stInfo) == QueryFail)
	{
		return FALSE;
	}
	else
	{
		auto iter = m_mapUsermapInfo.find(stInfo.strUserMapInfoId);
		if (iter != m_mapUsermapInfo.end())
		{
			if (oper == DBO_DEL)
			{
				m_mapUsermapInfo.erase(iter);
			}
			else if (oper ==DBO_UPDATE)
			{
				iter->second = stInfo;
			}
		}
		else
		{
			if (oper == DBO_ADD)
			{
				m_mapUsermapInfo[stInfo.strUserMapInfoId] = stInfo;
			}
		}
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageProduceInfo(DBOperType oper,ST_ProduceInfo stInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockProduceInfo);
	if (!m_pDBOper || !m_pDBOper->QuerySqlStatus())
	{
		DISPLAY_LOG("缓存模块","数据库未连接","","",0);
		return FALSE;
	}
	if (stInfo.strPublishEndTime > "2037-12-31 00:00:00")
	{
		stInfo.strPublishEndTime = "2037-12-31 00:00:00";
	}
	if(m_pDBOper->ManageProduceInfo(oper,stInfo) == QueryFail)
	{
		return FALSE;
	}
	else
	{
		auto iter = m_mapProduceInfo.find(stInfo.strProduceId);
		if (iter != m_mapProduceInfo.end())
		{
			if (oper == DBO_DEL)
			{
				m_mapProduceInfo.erase(iter);
			}
			else if (oper ==DBO_UPDATE)
			{
				iter->second = stInfo;
			}
		}
		else
		{
			if (oper == DBO_ADD)
			{
				m_mapProduceInfo[stInfo.strProduceId] = stInfo;
			}
		}
		//
		string strInfo;
		auto it = m_mapProduce.find(stInfo.strProduceId);
		if (it != m_mapProduce.end())
		{
			if (oper == DBO_DEL)
			{
				m_mapProduce.erase(it);
			}
			else if (oper ==DBO_UPDATE)
			{
				if(stInfo.ConvertToString(strInfo))
					it->second = strInfo;
			}
		}
		else
		{
			if (oper == DBO_ADD)
			{
				if(stInfo.ConvertToString(strInfo))
					m_mapProduce[stInfo.strProduceId] = strInfo;
			}
		}
	}
	TTRACE("[缓存模块]管理产品信息，产品数量:%d,%d \r\n",m_mapProduceInfo.size(),m_mapProduce.size());
	return TRUE;
	SCATCH;
	return FALSE;
}

#define DATAPROVIDER_UPDATE_MAP_CACHE(updateType, updateContainer, updateId, updateData) { \
                switch(updateType)\
                {\
                case DBO_ADD:\
					updateContainer[updateId] = updateData;\
					break;\
                case DBO_UPDATE:\
                    updateContainer[updateId] = updateData;\
                    break;\
                case DBO_DEL:\
                    auto iter = updateContainer.find(updateId);\
                    if(iter != updateContainer.end())\
                        updateContainer.erase(iter);\
                    break;\
                }\
                }

ISOC_BOOL XhBFISDataProviderImp::ManagePurviewInfo(DBOperType oper,ST_PurviewInfo stInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockPurviewInfo);
	if (!m_pDBOper || !m_pDBOper->QuerySqlStatus())
	{
		DISPLAY_LOG("缓存模块","数据库未连接","","",0);
		return FALSE;
	}
	if(m_pDBOper->ManagePurviewInfo(oper,stInfo) == QueryFail)
	{
		return FALSE;
	}

    DATAPROVIDER_UPDATE_MAP_CACHE(oper, m_mapPurviewInfo, stInfo.strParentPurviewId, stInfo);
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageEmployeeInfo(DBOperType oper,ST_EmployeeInfo stInfo)
{
	STRY;
	switch(oper)
	{
	case DBO_ADD:
		{
			stInfo.strPassword = ByteToHex((unsigned char*)stInfo.strPassword.c_str(),strlen(stInfo.strPassword.c_str()));	
			/*MD5 iMD5;strPassword
			iMD5.GenerateMD5((unsigned char*)stInfo.strPassword.c_str(), strlen(stInfo.strPassword.c_str()));
			stInfo. = iMD5.ToString();*/

		}
		break;
	case DBO_UPDATE:
		{
			ST_EmployeeInfo stEmployeeInfo;			
			QueryEmployeeInfoById(stInfo.strEmployeeId,stEmployeeInfo);
			// ReSharper disable CppCStyleCast
			string strPassword = ByteToHex((unsigned char*)stEmployeeInfo.strPassword.c_str(),strlen(stEmployeeInfo.strPassword.c_str()));
			// ReSharper restore CppCStyleCast
			if (stInfo.strPassword != strPassword)
			{
				// ReSharper disable once CppCStyleCast
				stInfo.strPassword = ByteToHex((unsigned char*)stInfo.strPassword.c_str(),strlen(stInfo.strPassword.c_str()));
				/*MD5 iMD5;
				iMD5.GenerateMD5((unsigned char*)stInfo.strPassword.c_str(), strlen(stInfo.strPassword.c_str()));
				stInfo.strPassword = iMD5.ToString();*/
			}
		}
		break;
	}	
	Poco::FastMutex::ScopedLock myLock(m_csLockEmployeeInfo);
	if (!m_pDBOper || !m_pDBOper->QuerySqlStatus())
	{
		DISPLAY_LOG("缓存模块","数据库未连接","","",0);
		return FALSE;
	}
	if(m_pDBOper->ManageEmployeeInfo(oper,stInfo) == QueryFail)
	{
		return FALSE;
	}
	
	BYTE cbyte[40]={0};
	HexToByte(stInfo.strPassword,cbyte);
	stInfo.strPassword = (char*)cbyte;
    DATAPROVIDER_UPDATE_MAP_CACHE(oper, m_mapEmployeeInfo, stInfo.strEmployeeId, stInfo);
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageRolePurviewInfo(DBOperType oper,ST_RolePurviewInfo stInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockRolePurviewInfo);
	if (!m_pDBOper || !m_pDBOper->QuerySqlStatus())
	{
		DISPLAY_LOG("缓存模块","数据库未连接","","",0);
		return FALSE;
	}
	if(m_pDBOper->ManageRolePurviewInfo(oper,stInfo) == QueryFail)
	{
		return FALSE;
	}

    DATAPROVIDER_UPDATE_MAP_CACHE(oper, m_mapRolePurviewInfo, stInfo.strRoleInfoPurviewId, stInfo);
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageEmployeePurviewInfo(DBOperType oper,ST_EmployeePurviewInfo stInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockEmployeePurviewInfo);
	if (!m_pDBOper || !m_pDBOper->QuerySqlStatus())
	{
		DISPLAY_LOG("缓存模块","数据库未连接","","",0);
		return FALSE;
	}
	if(m_pDBOper->ManageEmployeePurviewInfo(oper,stInfo) == QueryFail)
	{
		return FALSE;
	}
	if (nullptr == m_pSerializeEmployeePurviewInfo)
	{
		DATAPROVIDER_UPDATE_MAP_CACHE(oper, m_mapEmployeePurviewInfo, stInfo.strEmployeePurviewId, stInfo);
		return TRUE;
	}
	SCATCH;
	return UpdataSerializeEmployeePurviewInfo(oper, stInfo);
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::ManageBusinessInfo(DBOperType oper,ST_BusinessInfo stInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockBusinessInfo);
	if (!m_pDBOper || m_pDBOper->ManageBusinessInfo(oper,stInfo) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageBusinessFileInfo(DBOperType oper,ST_BusinessFileInfo stInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockBusinessFileInfo);
	if (!m_pDBOper || m_pDBOper->ManageBusinessFileInfo(oper,stInfo) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageBusinessRelateInfo(DBOperType oper,ST_BusinessRelateInfo stInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockBusinessRelateInfo);
	if (!m_pDBOper || m_pDBOper->ManageBusinessRelationInfo(oper,stInfo) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

inline void FillVecData(const std::map<std::string, std::string>& src, std::vector<std::string>& dest)
{
    for (auto iter = src.begin(); iter != src.end(); ++iter)
    {
        dest.push_back(iter->second);
    }
}

ISOC_BOOL XhBFISDataProviderImp::QueryInfo(SyncDataType enType,vector<string>& vecInfo)
{
	STRY;
	switch(enType)
	{
	case DataType_BranceInfo:          { FillVecData(m_mapBranch,          vecInfo); break; }
	case DataType_ClientInfo:          { FillVecData(m_mapClient,          vecInfo); break; }
	case DataType_RoleInfo:            { FillVecData(m_mapRole,            vecInfo); break; }
    case DataType_ProduceInfo:         { FillVecData(m_mapProduce,         vecInfo); break; }
	case DataType_EmployeeInfo:        { FillVecData(m_mapEmployee,        vecInfo); break; } 
    case DataType_EmployeePurviewInfo: { FillVecData(m_mapEmployeePurview, vecInfo); break; } 
    case DataType_PurviewInfo:         { FillVecData(m_mapPurview,         vecInfo); break; } 
    case DataType_RolePurviewInfo:     { FillVecData(m_mapRolePurview,     vecInfo); break; } 
    case DataType_UserMapInfo:         { FillVecData(m_mapUsermap,         vecInfo); break; }
    case DataType_BusinessInfo:
    case DataType_BusinessFileInfo:
    case DataType_BusinessRelationInfo:
        {
            return FALSE;
        }
        break;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_INT XhBFISDataProviderImp::ManageTransparentData(DBOperType oper,std::string strType,std::string strCode,std::string strValue)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->ManageTransparentData(oper,strType,strCode,strValue) < 0)
	{
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

ISOC_BOOL XhBFISDataProviderImp::QueryKeyValueInfoByTypeAndCode(std::string strType,std::string strCode,vector<ST_KeyValueInfo>& vecKeyValueInfo)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->QueryKeyValueInfoByTypeAndCode(strType,strCode,vecKeyValueInfo) < 0)
	{
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

ISOC_BOOL XhBFISDataProviderImp::QueryBusinessInfoById(const std::string& strBusinessId,ST_BusinessInfo& stInfo)
{
	STRY;
	int nRet = -1;
	stInfo.strBusinessInfoId = strBusinessId;
	if (m_pDBOper && (nRet = m_pDBOper->QueryBusinessInfoByID(stInfo)) >= 0)
	{
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryBusinessInfoBySerialNumber(const std::string& strSerialNumber,ST_BusinessInfo& stInfo)
{
	STRY;
	int nRet = -1;
	stInfo.strSerialNumber = strSerialNumber;
	if (m_pDBOper && (nRet = m_pDBOper->QueryBusinessInfoBySerialNumber(stInfo)) >= 0)
	{
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryBusinessInfoByEmployeeIdAndCount(std::string strClientId,int nCount,map<std::string,int>& mapInfo)
{
	STRY;
	int nRet = -1;
	if (m_pDBOper && (nRet = m_pDBOper->QueryBusinessInfoByEmployeeIdAndCount(strClientId,nCount,mapInfo)) >= 0)
	{
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryHotProduceIdByCount(int nCount,map<std::string,int>& mapInfo)
{
	STRY;
	int nRet = -1;
	if (m_pDBOper && (nRet = m_pDBOper->QueryHotProduceIdByCount(nCount,mapInfo)) >= 0)
	{
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryTaskNotMigrated(int nCount,vector<ST_BusinessFileInfo>& vecInfos,int nMigrated /*= 0*/)
{
	STRY;
	int nRet = -1;
	if (m_pDBOper && (nRet = m_pDBOper->QueryTaskNotMigrated(vecInfos,nCount)) >= 0)
	{
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::SetMigratedBusinessFileInfo(std::string strRecordId,int nMigrated /*= 0*/)
{
	STRY;
	if (m_pDBOper && m_pDBOper->SetMigratedBusinessFileInfo(strRecordId,nMigrated))
	{
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::SetMigratedBusinessInfo(std::string strBusinessInfoId,int nMigrated /*= 0*/)
{
	STRY;
	if (m_pDBOper && m_pDBOper->SetMigratedBusinessInfo(strBusinessInfoId,nMigrated))
	{
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryTaskNotMigrated(int nCount,vector<ST_BusinessInfo>& vecInfos,int nMigrated /*= 0*/)
{
	STRY;
	if (m_pDBOper && m_pDBOper->QueryTaskNotMigrated(vecInfos,nCount, nMigrated))
	{
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::ModifyLocalBranchId(string strLocalBranchId)
{
	STRY;
// 	m_strLocalBranchId = strLocalBranchId;
// 	ModifyConfigFile(strLocalBranchId);
	return TRUE;
	SCATCH;
	return FALSE;
}

// ReSharper disable CppMemberFunctionMayBeStatic
ISOC_BOOL XhBFISDataProviderImp::ModifyConfigFile(string strBranchId) const
// ReSharper restore CppMemberFunctionMayBeStatic
{
	STRY;
	CString strPath = GetWorkingDirectory();
	strPath += _T("\\Config\\iBFIS.Server.Config.ini");
	WritePrivateProfileString(_T("LocalBranchInfo"),_T("LocalBranchId"),strBranchId.c_str(),strPath);
	return TRUE;
	SCATCH;
	return FALSE;
}

bool XhBFISDataProviderImp::UpdataSerializeEmployeePurviewInfo(DBOperType oper,ST_EmployeePurviewInfo stInfo)
{
	STRY;
	if (nullptr == m_pSerializeEmployeePurviewInfo)
		return false;
	iCMSP_WriteLock wrLock(*m_pSerializeEmployeePurviewInfo->GetWRLock(), __FUNCTION__);
	if (DBO_ADD == oper)
	{
		int nKey = -1;
		if (m_pSerializeEmployeePurviewInfo->GetNotFullPacket(nKey) > 0)
		{
			BYTE *pData = nullptr;
			int nUserDataSize = 0;
			int nTotalDataSize = 0;
			int nRet = m_pSerializeEmployeePurviewInfo->GetDataPacket(nKey, &pData, nUserDataSize, nTotalDataSize);
			if (nRet <= 0)
				return false;
			ST_EmployeePurviewInfoList stList;
			stList.ConvertToStruct(pData, nUserDataSize, stList.vecEmployeePurview);
			stList.vecEmployeePurview.push_back(stInfo);
			nRet = stList.ConvertToArrary(m_pSerializeEmployeePurviewInfo, nKey);
			if (nRet > 0)
				return true;
		}
		else
		{
			ST_EmployeePurviewInfoList stList;
			stList.vecEmployeePurview.push_back(stInfo);
			int nRet = stList.ConvertToArrary(m_pSerializeEmployeePurviewInfo);
			if (nRet > 0)
				return true;
		}
	}
	else if (DBO_UPDATE == oper || DBO_DEL == oper)
	{
		int nKey = 0;
		int nDataPos = 0;
		int nRet = m_pSerializeEmployeePurviewInfo->GetDataPacketPos(stInfo.strEmployeePurviewId, nKey, nDataPos);
		if (nRet <= 0)
			return false;

		BYTE *pData = nullptr;
		int nUserDataSize = 0;
		int nTotalDataSize = 0;
		nRet = m_pSerializeEmployeePurviewInfo->GetDataPacket(nKey, &pData, nUserDataSize, nTotalDataSize);
		if (nRet <= 0)
			return false;

		ST_EmployeePurviewInfoList stList;
		nRet = stList.ConvertToStruct(pData, nUserDataSize, stList.vecEmployeePurview);
		if (nRet <= 0)
			return false;

		if (DBO_UPDATE == oper)
		{
			if (nDataPos <= stList.vecEmployeePurview.size() && nDataPos > 0)
			{
				stList.vecEmployeePurview[nDataPos - 1].strEmployeePurviewId = stInfo.strEmployeePurviewId;
				stList.vecEmployeePurview[nDataPos - 1].strEmployeeId = stInfo.strEmployeeId;
				stList.vecEmployeePurview[nDataPos - 1].strPurviewInfoId = stInfo.strPurviewInfoId;
				stList.vecEmployeePurview[nDataPos - 1].nExtendedInfo = stInfo.nExtendedInfo;
				stList.vecEmployeePurview[nDataPos - 1].strExtendedInfo1 = stInfo.strExtendedInfo1;
				stList.vecEmployeePurview[nDataPos - 1].strExtendedInfo2 = stInfo.strExtendedInfo2;
				return stList.ConvertToArrary(m_pSerializeEmployeePurviewInfo, nKey);
			}
		}
		else if (DBO_DEL == oper)
		{
			auto  itor = stList.vecEmployeePurview.begin();
			if (nDataPos <= stList.vecEmployeePurview.size() && nDataPos > 0)
			{
				itor += (nDataPos - 1);
				m_pSerializeEmployeePurviewInfo->DelDataPacketPos(itor->strEmployeePurviewId);
				m_pSerializeEmployeePurviewInfo->DelDataPacketPos(itor->strEmployeeId, itor->strEmployeePurviewId);
				stList.vecEmployeePurview.erase(itor);
				return stList.ConvertToArrary(m_pSerializeEmployeePurviewInfo, nKey);
			}
		}
	}
	SCATCH;
	return false;
}

ISOC_INT XhBFISDataProviderImp::QueryClientInfoByCondition(int nType,int nCount,vector<ST_ClientInfo>& vecInfo)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->QueryClientInfoByCondition(nType,nCount,vecInfo) == QueryFail)
	{
		return -1;
	}
	if (vecInfo.empty())
	{
		return 0; 
	}
	return 1;
	SCATCH;
	return -1;
}

ISOC_BOOL XhBFISDataProviderImp::QueryClientInfoByID(IN OUT ST_ClientInfo& sClientInfo,IN bool bOverlapped /*= true*/)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->QueryClientInfoByID(sClientInfo,bOverlapped) != QuerySuccessWithResult)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::ManageTaskPlanInfo(DBOperType enOperType,vector<ST_TaskPlan>& stInfo)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->ManageTaskPlanInfo(enOperType,stInfo) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageMigrateLogInfo(DBOperType enOperType,ST_MigrateLogInfo& stInfo)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->ManageMigrateLogInfo(enOperType,stInfo) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryMigrateLogInfoByCondition(const ST_QueryCondition& stCondition,std::vector<ST_MigrateLogInfo>& vecInfo)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->QueryMigrateLogInfoByCondition(stCondition,vecInfo) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryMigrateLogInfoCountByCondition(const ST_QueryCondition& stCondition,int& nTotalCount)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->QueryMigrateLogInfoCountByCondition(stCondition,nTotalCount) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_INT XhBFISDataProviderImp::QueryBusinessRelateInfoById(std::string strId,ST_BusinessRelateInfo& stInfo)
{
	STRY;
	stInfo.strBusinessRelateInfoId = strId;
	if (m_pDBOper)
	{
		return m_pDBOper->ManageBusinessRelationInfo(DBO_QUERY,stInfo);
	}
	return QueryFail;
	SCATCH;
	return QueryFail;
}
ISOC_INT XhBFISDataProviderImp::QueryBusinessFileInfoById(std::string strId,ST_BusinessFileInfo& stInfo)
{
	STRY;
	stInfo.strRecordId = strId;
	if (m_pDBOper)
	{
		return m_pDBOper->ManageBusinessFileInfo(DBO_QUERY,stInfo);
	}
	return QueryFail;
	SCATCH;
	return QueryFail;
}
ISOC_BOOL XhBFISDataProviderImp::SetSyncComplete(SyncDataType enDataType,string strId)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->SetSyncComplete(enDataType,strId);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_INT XhBFISDataProviderImp::QueryProduceNeed2Sync(string strSyncTime,std::vector<ST_ProduceInfo>& vecInfo)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryProduceNeed2Sync(strSyncTime,vecInfo);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_INT XhBFISDataProviderImp::QueryMinProduceSyncTime(string& strSyncTime)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryMinProduceSyncTime(strSyncTime);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryClientInfoLastSyncTime(std::string& strTime)
{
	STRY;
	CString strTemp;
	strTime = "";
	if (m_pDBOper && m_pDBOper->QueryClientInfoLastSyncTime(strTemp))
	{
		strTime = strTemp;
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_INT XhBFISDataProviderImp::QueryClientInfo3Param(std::vector<ST_ClientInfo>& vecInfos ,const string& strTime /*= ""*/,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryClientInfo(vecInfos,strTime,dwReserved);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

QueryResultType XhBFISDataProviderImp::GetLocalBranchInfo(IN OUT ST_BranchInfo& stInfo)
{   
    STRY;
    if (m_pDBOper)
    {
        return m_pDBOper->GetLocalBranchInfo(stInfo);
    }
    return QueryFail;
    SCATCH;
    return QueryFail;
}
ISOC_BOOL XhBFISDataProviderImp::QueryBranchInfoNeed2Sync(std::vector<ST_BranchInfo>& vecInfo)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryBranchInfo(vecInfo);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryRoleInfoNeed2Sync(std::vector<ST_RoleInfo>& vecInfo)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryRoleInfo(vecInfo);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryRolePurviewInfoNeed2Sync(std::vector<ST_RolePurviewInfo>& vecInfo)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryRolePurviewInfo(vecInfo);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryEmployeeInfoNeed2Sync(std::vector<ST_EmployeeInfo>& vecInfo)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryEmployeeInfo(vecInfo);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryEmployeePurviewInfoNeed2Sync(std::vector<ST_EmployeePurviewInfo>& vecInfo)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryEmployeePurviewInfo(vecInfo);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryProduceInfoNeed2Sync(std::vector<ST_ProduceInfo>& vecInfo)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryProduceInfo(vecInfo);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryBusinessInfoNeed2Sync(std::vector<ST_BusinessInfo>& vecInfo)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryBusinessInfo(vecInfo);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryBusinessFileInfoNeed2Sync(std::vector<ST_BusinessFileInfo>& vecInfo)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryBusinessFileInfo(vecInfo);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryBusinessRelateInfoNeed2Sync(std::vector<ST_BusinessRelateInfo>& vecInfo)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->QueryBusinessRelateInfo(vecInfo);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::UpdateUserPermission(vector<ST_EmployeeInfo>& stEmployeeInfo)
{
	STRY;
	if (m_pDBOper)
	{
		return m_pDBOper->UpdateUserPermission(stEmployeeInfo);
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::ManageScriptInfo(DBOperType enType,ST_ScriptInfo& info,DWORD_PTR dwReserved)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockScriptInfo);
	if (!m_pDBOper || m_pDBOper->ManageScriptInfo(enType,info) == QueryFail)
	{
		return FALSE;
	}
	DATAPROVIDER_UPDATE_MAP_CACHE(enType, m_mapScriptInfo, info.strScriptId, info);
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryScriptInfo(IN int nAll,vector<ST_ScriptInfo>& vecScriptInfo)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->QueryScriptInfo(vecScriptInfo) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::ManageOperateLogInfo(DBOperType enType,ST_OperateLogInfo& info,DWORD_PTR dwReserved)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->ManageOperateLogInfo(enType,info) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDataProviderImp::QueryOperateLogInfoByEmployeeId(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strEmployeeId)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->QueryOperateLogInfoByEmployeeId(vecInfos,strEmployeeId) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_INT XhBFISDataProviderImp::QueryDeskStatus(IN std::vector<std::string> vecDisk,OUT int& nDiskTotal,OUT int& nDiskFree)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->QueryDeskStatus(vecDisk,nDiskTotal,nDiskFree) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryScriptInfoById(const std::string& strScriptId,ST_ScriptInfo& stInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockScriptInfo);
	auto iter = m_mapScriptInfo.find(strScriptId);
	if (iter != m_mapScriptInfo.end())
	{
		stInfo = iter->second;
		return TRUE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryScriptInfoByCache(vector<ST_ScriptInfo>& vecScriptInfo)
{
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockScriptInfo);
	vecScriptInfo.clear();
	for (auto iter = m_mapScriptInfo.begin() ; iter != m_mapScriptInfo.end() ; ++iter)
	{
		vecScriptInfo.push_back(iter->second);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDataProviderImp::QueryNeedDelOperateLogInfo(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strTime)
{
	STRY;
	if (!m_pDBOper || m_pDBOper->QueryNeedDelOperateLogInfo(vecInfos,strTime) == QueryFail)
	{
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}