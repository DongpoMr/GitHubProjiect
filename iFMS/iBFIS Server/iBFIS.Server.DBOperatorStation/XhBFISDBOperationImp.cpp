#include "stdafx.h"
#include "XhBFISDBOperationImp.h"
#include "iSOC_AutoInitCOM.h"
#include "IcmsP_Utility.h"
#include "XhLogDisplayInterface.h"
//#include "Registry.h"
#include "iSOC_MonFactoryManagement.h"
#include "Poco/DateTime.h"
#include "iSOC_ManLoginModule.h"
#include "IcmsP_XmlParser.h"
#include "iCMSMon_StructDefine.h"

#define DB_ALIVE_TIMER 1001
#define DB_ALIVE_TIME  20*1000
#define USE_BFIS_ASSERT 1
#define BFIS_ASSERT_STDSTRING(str, operate) { if(str == "") {DISPLAY_LOG("数据库模块", operate, "参数"#str"不能为空","",0); return QueryFail;}}


XhBFISDBOperationImp::XhBFISDBOperationImp():m_bIsDbConnection(FALSE),m_strIp(""),m_strPort(""),m_strUID(""),m_strPWD(""),
	m_pConInfo(NULL),m_nConnectCount(20),m_strDataBaseName("ibfis"),m_pTimer(NULL),m_strLocalBranchId("")
{
    m_nCount = 0; 
	m_ResultCode = 0;
}

XhBFISDBOperationImp::~XhBFISDBOperationImp()
{
    STRY;
	if(m_pTimer)
	{
		iSOC_MonFactoryManagement fmt;
		m_pTimer->KillTimer(-1);
		fmt.ReleaseObject((CISocObject**)&m_pTimer,__FUNCTION__);
	}
    DisConnectDataBase();
    SCATCH;
}

ISOC_BOOL XhBFISDBOperationImp::KeepConnect()
{
	STRY;
	iSOC_MonFactoryManagement fmt;
	m_pTimer = (ITimer*)fmt.CreateObject(OBJECT_TYPE_TIMER,"",__FUNCTION__);
	if(!m_pTimer)
	{
		TTRACE("[数据库]创建定时器失败%s[%d]\r\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	m_pTimer->SetTimer(this,DB_ALIVE_TIMER,DB_ALIVE_TIME);
	return TRUE;
	SCATCH;
	return FALSE;
}

void XhBFISDBOperationImp::OnTimer(IN ISOC_ID iTimerID)
{
	STRY;
	switch(iTimerID)
	{
	case DB_ALIVE_TIMER:
		{
			STRY;

			SimpleConnection conn(this);
			int				nRestAff = 0;
			_RecordsetPtr	recPtr = NULL;

			string strSQL = _T("Select 1;");
			if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)(strSQL.c_str()), recPtr, nRestAff))
			{
				m_bIsDbConnection = FALSE;
				DISPLAY_LOG(_T("数据库"), _T("数据库连接断开"), _T("请等待自动重连"), _T(""), 0);
			}
			if(!m_bIsDbConnection && ReConnectToDataBase())
			{
				m_bIsDbConnection = TRUE;
			}
			SCATCH;
		}
		break;
	}
	SCATCH;
}

ISOC_BOOL XhBFISDBOperationImp::GetDataBaseConfig(IN OUT string strIP,IN OUT string strPort,IN OUT string strUser,IN OUT string strPwd)
{
	STRY;
	strIP = m_strIp;
	strPort = m_strPort;
	strUser = m_strUID;
	strPwd = m_strPWD;
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDBOperationImp::SetDataBaseName(IN string strName)
{
	STRY;
	m_strDataBaseName = strName;
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDBOperationImp::SetLocalBranchId(string strGuid)
{
	STRY;
	m_strLocalBranchId = strGuid;
	SCATCH;
	return FALSE;
}

QueryResultType XhBFISDBOperationImp::GetLocalBranchInfo(IN OUT ST_BranchInfo& stInfo)
{
	STRY;
	QueryResultType ret = QueryFail;
	if (m_strLocalBranchId == "")
	{
		TTRACE("[数据库]获取本地网点信息失败,本地网点GUID为空 \r\n");
		return ret;
	}
#if 0
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strSQL = _T("call proc_localbranch_query()");
	TTRACE("[数据库]查询本地网点信息:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询本地网点信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			varFieldVal = recPtr->GetCollect("BranchId");
			stInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("Name");
			stInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("Address");
			stInfo.strAddress = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("Contact");
			stInfo.strContact = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("Phone");
			stInfo.strPhone = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("Content");
			stInfo.strContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("ExtendedInfo");
			stInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
			varFieldVal = recPtr->GetCollect("ExtendedInfo1");
			stInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("ExtendedInfo2");
			stInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("ParentId");
			stInfo.strParentId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("IsLocal");
			stInfo.nIsLocal = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
		{
			return QuerySuccessWithoutResult;
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
#endif
	stInfo.strBranchId = m_strLocalBranchId;
	ret = QueryBranchInfoByID(stInfo);
	if(ret == QuerySuccessWithResult)//如果查到本地网点，就手动将其IsLocal字段置1，客户端要用到该字段
	{
		stInfo.nIsLocal = 1;
		ManageBranchInfo(DBO_UPDATE,stInfo);
	}
	return ret;
	SCATCH;
	return QueryFail;
}

ISOC_BOOL XhBFISDBOperationImp::ConnectToDataBase(IN string strIP,IN string strPort,IN string strUser,IN string strPwd)
{
    BOOL bRet = FALSE;
    try
    {
        HRESULT hr;
        iSOC_AutoInitCOM autoInitCom;
        Poco::FastMutex::ScopedLock simple(m_csDBLock);

        if(!m_pConInfo)
            m_pConInfo = new ST_DBConnectionInfo[m_nConnectCount];
        if(!m_pConInfo)
            return bRet;

        m_strIp   = strIP;
        m_strPort = strPort;
        m_strUID  = strUser;
        m_strPWD  = strPwd;

        for (int i = 0 ; i < m_nConnectCount ; i ++)
        {
            hr = m_pConInfo[i].pDBConnection.CreateInstance(__uuidof(Connection));
            if(SUCCEEDED(hr))
            {
                char szConnect[255] = {0};
                sprintf(szConnect,"Driver={MySQL ODBC 5.1 Driver};Connect Timeout=10;Server=%s;database=%s",strIP.c_str(),
					m_strDataBaseName.c_str());
                hr = m_pConInfo[i].pDBConnection->Open((_bstr_t)szConnect,(_bstr_t)strUser.c_str(),(_bstr_t)strPwd.c_str(), 
					adConnectUnspecified);
                if(SUCCEEDED(hr))
                {
                    m_bIsDbConnection = TRUE;
                    bRet = TRUE;
                }
                else
                {
                    DISPLAY_LOG("数据库","连接数据库失败","请检查配置是否正确/网络是否畅通","",0);
                    m_bIsDbConnection = FALSE;
                    bRet = FALSE;
                }
            }

        }
    }
    catch(_com_error e)
    {
        CString strError;
        strError.Format(_T("连接数据库失败!\r\n  错误信息：%s"),e.ErrorMessage());
        DISPLAY_LOG("数据库",strError.GetBuffer(0),"","",0);
		strError.ReleaseBuffer(0);
        m_bIsDbConnection = FALSE;
        bRet = FALSE;
    }
    return bRet;
}

ISOC_BOOL XhBFISDBOperationImp::QuerySqlStatus()
{
	STRY;
	return TRUE;
	int             nRestAff = 0;
	BOOL            bRet = FALSE;
	_RecordsetPtr   recPtr = NULL;
	string          strSQL = _T("select 1;");

	for(int x=0;x<m_nConnectCount;x++)
	{
		try
		{
			if (m_pConInfo[x].pDBConnection == NULL)
				return FALSE;

			if (m_pConInfo[x].pDBConnection->GetState() == adStateClosed)
				return FALSE;

			//SimpleConnection conn(this);
			bRet = ExecuteSQL((_bstr_t)(strSQL.c_str()),recPtr,nRestAff);
			//bRet = ExecuteSQLSafe(pcon, (_bstr_t)(strSQL.c_str()),recPtr, nRestAff);
			if (!bRet)
			{
				m_bIsDbConnection = FALSE;
				return FALSE;
			}
			else
			{
				m_bIsDbConnection = TRUE;
				if(recPtr != NULL && recPtr->GetState() == adStateOpen)
					recPtr->Close();    
			}
			// 

		}
		catch (_com_error e)
		{
			TTRACE("%s:%d %s\r\n",_T("[数据库]"),__LINE__,(LPTSTR)(e.Description()));
			m_bIsDbConnection = FALSE;
			return FALSE;
		}      
	}
	return TRUE;

	SCATCH;
	m_bIsDbConnection = FALSE;
	return FALSE;
}

ISOC_BOOL XhBFISDBOperationImp::ReConnectToDataBase()
{
	STRY;
	BOOL bRet = FALSE;
	try
	{
		HRESULT hr;
		iSOC_AutoInitCOM autoInitCom;
		Poco::FastMutex::ScopedLock simple(m_csDBLock);

		if(!m_pConInfo)
			m_pConInfo = new ST_DBConnectionInfo[m_nConnectCount];
		if(!m_pConInfo)
			return bRet;

		for (int i = 0 ; i < m_nConnectCount ; i ++)
		{
			hr = m_pConInfo[i].pDBConnection.CreateInstance(__uuidof(Connection));
			if(SUCCEEDED(hr))
			{
				char szConnect[255] = {0};
				sprintf(szConnect,"Driver={MySQL ODBC 5.1 Driver};Connect Timeout=10;Server=%s;database=%s",m_strIp.c_str(),
					m_strDataBaseName.c_str());
				hr = m_pConInfo[i].pDBConnection->Open((_bstr_t)szConnect,(_bstr_t)m_strUID.c_str(),(_bstr_t)m_strPWD.c_str(), 
					adConnectUnspecified);
				if(SUCCEEDED(hr))
				{
					//DISPLAY_LOG("数据库","自动重连数据库成功","","",1);
					m_bIsDbConnection = TRUE;
					bRet = TRUE;
				}
				else
				{
					DISPLAY_LOG("数据库","自动重连数据库失败","请检查配置是否正确/网络是否畅通","",0);
					m_bIsDbConnection = FALSE;
					bRet = FALSE;
				}
			}

		}
	}
	catch(_com_error e)
	{
		CString strError;
		strError.Format(_T("连接数据库失败!\r\n  错误信息：%s"),e.ErrorMessage());
		DISPLAY_LOG("数据库",strError.GetBuffer(0),"","",0);
		strError.ReleaseBuffer(0);
		m_bIsDbConnection = FALSE;
		bRet = FALSE;
	}
	return bRet;
	SCATCH;
}

ISOC_BOOL XhBFISDBOperationImp::DisConnectDataBase()
{
	STRY;
	iSOC_AutoInitCOM autoInitCom;
	 Poco::FastMutex::ScopedLock myConnLock(m_csDBLock);
    if (NULL != m_pConInfo)
    {
        for (int i = 0 ; i < m_nConnectCount; i ++)
        {
            if(NULL != m_pConInfo[i].pDBConnection && adStateOpen == m_pConInfo[i].pDBConnection->State /*判断数据库连接是否有效*/)
            {
				try
				{
					m_pConInfo[i].pDBConnection->Close();
					//m_pConInfo[i].pDBConnection->Release();
					//m_pConInfo[i].pDBConnection = NULL;
				}
				catch(_com_error e)
				{
					TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
					return FALSE;
				}
            }
		}
        m_bIsDbConnection = FALSE;
		SAFE_DELETE(m_pConInfo);
    }
	return TRUE;
	SCATCH;
    return FALSE;
}

ISOC_INT XhBFISDBOperationImp::QueryClientInfoByCondition(IN int nType,IN int nCount,vector<ST_ClientInfo>& vecInfo)
{
	STRY;
	CString strSQL = _T("");
	CString strMsg = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	ST_ClientInfo stInfo = vecInfo[0];
	vecInfo.clear();
	switch(nType)
	{
	case 1:
		{
#if USE_BFIS_ASSERT
		BFIS_ASSERT_STDSTRING(stInfo.strCredenitial,"按条件查询客户信息");
		BFIS_ASSERT_STDSTRING(stInfo.strName,"按条件查询客户信息");
#else
			if(stInfo.strCredenitial == "" && stInfo.strName == "")
			{
				TTRACE("[数据库]按条件查询客户信息条件错误,身份证号码或客户名为空  \r\n");
				return QueryFail;
			}
#endif
			strMsg = _T("call proc_clientinfo_querybycondition(\"%s\",\"%s\",%d)");
			strSQL.Format(strMsg,stInfo.strName.c_str(),stInfo.strCredenitial.c_str(),nCount);
		}
		break;
	case 2:
		{
			if(stInfo.strCredenitial == "")
			{
				TTRACE("[数据库]按条件查询客户信息条件错误,身份证号码为空 \r\n");
				return QueryFail;
			}
            strMsg = _T("call proc_clientinfo_selectbycredenitial(\"%s\",\"%s\")");
            strSQL.Format(strMsg,stInfo.strCredenitial.c_str(),stInfo.strCredenitialsType.c_str());
		}
		break;
	default:
		TTRACE("[数据库]未知错误:%s[%d] \r\n",__FUNCTION__,__LINE__);
		return QueryFail;
	}
	TTRACE("[数据库]按条件查询客户信息语句%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","按条件查询客户信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_ClientInfo stClientInfo;
				varFieldVal = recPtr->GetCollect("ClientId");
				stClientInfo.strClientId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Name");
				stClientInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("CredenitialsType");
                stClientInfo.strCredenitialsType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Credenitial");
				stClientInfo.strCredenitial = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Phone");
				stClientInfo.strPhone = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Content");
				stClientInfo.strContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				stClientInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				stClientInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				stClientInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				vecInfo.push_back(stClientInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
		{
			return QuerySuccessWithoutResult;
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

ISOC_BOOL XhBFISDBOperationImp::QueryDiffBranchInfo(IN int nAll,IN OUT vector<ST_BranchInfo>& vecBranchInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
	strSQL.Format(strMsg,_T("branchinfo"),nAll);
	TTRACE("[数据库]查询新增网点信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","执行SQL语句失败","查询新增网点信息失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_BranchInfo stBranchInfo;
				varFieldVal = recPtr->GetCollect("BranchId");
				stBranchInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Name");
				stBranchInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Address");
				stBranchInfo.strAddress = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Contact");
				stBranchInfo.strContact = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Phone");
				stBranchInfo.strPhone = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Content");
				stBranchInfo.strContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				stBranchInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				stBranchInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				stBranchInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ParentId");
				stBranchInfo.strParentId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("IsLocal");
				stBranchInfo.nIsLocal = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
                varFieldVal = recPtr->GetCollect("JDBRID");
                stBranchInfo.strJDBRID = varFieldVal.vt == VT_NULL ? "": (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("ParentJDBRID");
                stBranchInfo.strParentJDBRID = varFieldVal.vt == VT_NULL ? "": (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("ParentName");
                stBranchInfo.strParentName = varFieldVal.vt == VT_NULL ? "": (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("JDTYPE");
                stBranchInfo.strJDTYPE = varFieldVal.vt == VT_NULL ? "": (_bstr_t)varFieldVal.bstrVal;
				vecBranchInfo.push_back(stBranchInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

QueryResultType XhBFISDBOperationImp::QueryBranchInfoByID(ST_BranchInfo& sBranchInfo,IN bool bOverlapped /*= true*/)
{
    CString strMsg = _T("");
    CString strSQL = _T("");
    SimpleConnection conn(this);
    int				nRestAff = 0;
    _variant_t		varFieldVal;
    _RecordsetPtr	recPtr = NULL;
    if(sBranchInfo.strBranchId == "")
    {
        TTRACE("[数据库]查询网点信息失败,传入网点ID为空\r\n");
        return QueryFail;
    }
    strMsg = _T("call proc_branchinfo_selectbyid(\"%s\")");
    strSQL.Format(strMsg,sBranchInfo.strBranchId.c_str());
	TTRACE("[数据库]通过ID查询网点信息语句:%s \r\n",strSQL);
    if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
    {       
        DISPLAY_LOG("数据库","通过Id查询网点信息失败","执行SQL语句失败","",0);
        return QueryFail;
    }
    try
    {
        if(nRestAff > 0 && !recPtr->adoEOF)
        {
			if (bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("Name");
				sBranchInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Address");
				sBranchInfo.strAddress = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Contact");
				sBranchInfo.strContact = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Phone");
				sBranchInfo.strPhone = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Content");
				sBranchInfo.strContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sBranchInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sBranchInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sBranchInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ParentId");
				sBranchInfo.strParentId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("IsLocal");
				sBranchInfo.nIsLocal = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
                varFieldVal = recPtr->GetCollect("JDBRID");
                sBranchInfo.strJDBRID = varFieldVal.vt == VT_NULL ? "": (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("ParentJDBRID");
                sBranchInfo.strParentJDBRID = varFieldVal.vt == VT_NULL ? "": (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("ParentName");
                sBranchInfo.strParentName = varFieldVal.vt == VT_NULL ? "": (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("JDTYPE");
                sBranchInfo.strJDTYPE = varFieldVal.vt == VT_NULL ? "": (_bstr_t)varFieldVal.bstrVal;
				TTRACE("\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\"",
					sBranchInfo.strBranchId.c_str(),sBranchInfo.strName.c_str(),sBranchInfo.strAddress.c_str()
					,sBranchInfo.strContact.c_str(),sBranchInfo.strPhone.c_str(),sBranchInfo.strContent.c_str()
					,sBranchInfo.nExtendedInfo,sBranchInfo.strExtendedInfo1.c_str(),
					sBranchInfo.strExtendedInfo2.c_str(),sBranchInfo.nIsLocal, sBranchInfo.strJDBRID.c_str(),
                    sBranchInfo.strParentJDBRID.c_str(),sBranchInfo.strParentName.c_str(),sBranchInfo.strJDTYPE.c_str());
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
        }
		else
		{
			return QuerySuccessWithoutResult;
		}
    }
    catch(_com_error e)
    {
        TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
        return QueryFail;
    }
    return QuerySuccessWithResult;
}

QueryResultType XhBFISDBOperationImp::ManageBranchInfo(DBOperType enOperType, ST_BranchInfo& sBranchInfo)
{
    STRY;
    CString strMsg = _T("");
    CString strSQL = _T("");
    switch(enOperType)
    {
    case DBO_QUERY:
        {
			return QueryBranchInfoByID(sBranchInfo,false);
        }
    case DBO_ADD:
        {
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(sBranchInfo.strBranchId, "添加银行网点信息");
        BFIS_ASSERT_STDSTRING(sBranchInfo.strName,     "添加银行网点信息");
        //BFIS_ASSERT_STDSTRING(sBranchInfo.strAddress,  "添加银行网点信息");
#else
            if(sBranchInfo.strBranchId == "" || sBranchInfo.strName == "" || sBranchInfo.strAddress == "")
            {
                TTRACE("[数据库]添加网点信息失败,传入网点ID、名称以及地址不可为空 \r\n");
                return QueryFail;
            }
#endif
            strMsg = _T("call proc_branchinfo_insert(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\")");
            strSQL.Format(strMsg,sBranchInfo.strBranchId.c_str(),sBranchInfo.strName.c_str(),sBranchInfo.strAddress.c_str()
				,sBranchInfo.strContact.c_str(),sBranchInfo.strPhone.c_str(),sBranchInfo.strContent.c_str()
				,sBranchInfo.nExtendedInfo,sBranchInfo.strExtendedInfo1.c_str(),sBranchInfo.strExtendedInfo2.c_str(),
				sBranchInfo.strParentId.c_str(),sBranchInfo.nIsLocal,sBranchInfo.strJDBRID.c_str(),sBranchInfo.strParentJDBRID .c_str(),
                sBranchInfo.strParentName.c_str(),sBranchInfo.strJDTYPE.c_str());
        }
        break;
    case DBO_UPDATE:
        {
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(sBranchInfo.strBranchId, "更新银行网点信息");
        BFIS_ASSERT_STDSTRING(sBranchInfo.strName,     "更新银行网点信息");
        //BFIS_ASSERT_STDSTRING(sBranchInfo.strAddress,  "更新银行网点信息");
#else
            if(sBranchInfo.strBranchId == "" || sBranchInfo.strName == "" || sBranchInfo.strAddress == "")
            {
                TTRACE("[数据库]更新网点信息失败,传入网点ID、名称以及地址不可为空 \r\n");
                return QueryFail;
            }
#endif
            strMsg = _T("call proc_branchinfo_update(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\")");
			strSQL.Format(strMsg,sBranchInfo.strBranchId.c_str(),sBranchInfo.strName.c_str(),sBranchInfo.strAddress.c_str()
				,sBranchInfo.strContact.c_str(),sBranchInfo.strPhone.c_str(),sBranchInfo.strContent.c_str()
				,sBranchInfo.nExtendedInfo,sBranchInfo.strExtendedInfo1.c_str(),sBranchInfo.strExtendedInfo2.c_str(),
                sBranchInfo.strParentId.c_str(),sBranchInfo.nIsLocal,sBranchInfo.strJDBRID.c_str(),sBranchInfo.strParentJDBRID .c_str(),
                sBranchInfo.strParentName.c_str(),sBranchInfo.strJDTYPE.c_str());
        }
        break;
    case DBO_DEL: 
        {
#if USE_BFIS_ASSERT
            BFIS_ASSERT_STDSTRING(sBranchInfo.strBranchId, "删除银行网点信息");
#else
            if (sBranchInfo.strBranchId == "")
            {
                TTRACE("[数据库]更新网点信息失败,传入网点ID不可为空 \r\n");
                return QueryFail;
            }
#endif
			if (DeleteInfoById(DataType_BranceInfo,sBranchInfo.strBranchId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
        }
        break;
    default:
        {
            TTRACE("[数据库]未知错误%s[%d] \r\n",__FUNCTION__,__LINE__);
            return QueryFail;
        }
    }
    SimpleConnection conn(this);
    int				nRestAff = 0;
    _variant_t		varFieldVal;
    _RecordsetPtr	recPtr = NULL;

	TTRACE("[数据库]语句:%s \r\n",strSQL);
    if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
    {       
        DISPLAY_LOG("数据库","管理网点信息失败","执行SQL语句失败","",0);
        return QueryFail;
    }
    return QuerySuccessWithoutResult;
    SCATCH;
    return QueryFail;
}

ISOC_BOOL XhBFISDBOperationImp::QueryDiffClientInfo(IN int nAll,IN OUT vector<ST_ClientInfo>& vecClientInfo,const string& strTime /*= ""*/)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	if (strTime == "")
	{
		strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
		strSQL.Format(strMsg,_T("clientinfo"),nAll);
	}
	else
	{
		strMsg = _T("call proc_clientinfo_selecttosync(\"%s\")");
		strSQL.Format(strMsg,strTime.c_str());
	}
	TTRACE("[数据库]查询新增客户信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询新增客户信息失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_ClientInfo stClientInfo;
				varFieldVal = recPtr->GetCollect("ClientId");
				stClientInfo.strClientId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Name");
				stClientInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("CredenitialsType");
                stClientInfo.strCredenitialsType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Credenitial");
				stClientInfo.strCredenitial = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Phone");
				stClientInfo.strPhone = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Content");
				stClientInfo.strContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				stClientInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				stClientInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				stClientInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				vecClientInfo.push_back(stClientInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

QueryResultType XhBFISDBOperationImp::QueryClientInfoByCredenitial(IN OUT ST_ClientInfo& sClientInfo,IN bool bOverlapped /*= true*/)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	if(sClientInfo.strCredenitial == "")
	{
		TTRACE("[数据库]通过身份证号码查询客户信息失败，传入客户身份证为空 \r\n");
		return QueryFail;
	}
	strMsg = _T("call proc_clientinfo_selectbycredenitial(\"%s\",\"%s\")");
	strSQL.Format(strMsg,sClientInfo.strCredenitial.c_str(),sClientInfo.strCredenitialsType.c_str());
	TTRACE("[数据库]通过身份证号码查询客户信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过身份证号码查询客户信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			std::string clientUuid = sClientInfo.strClientId;
			while (!recPtr->adoEOF)
			{
				if (bOverlapped)
				{
					varFieldVal = recPtr->GetCollect("ClientId");
					sClientInfo.strClientId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
					varFieldVal = recPtr->GetCollect("Name");
					sClientInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
					varFieldVal = recPtr->GetCollect("CredenitialsType");
					sClientInfo.strCredenitialsType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
					varFieldVal = recPtr->GetCollect("Phone");
					sClientInfo.strPhone = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
					varFieldVal = recPtr->GetCollect("Content");
					sClientInfo.strContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
					varFieldVal = recPtr->GetCollect("ExtendedInfo");
					sClientInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
					varFieldVal = recPtr->GetCollect("ExtendedInfo1");
					sClientInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
					varFieldVal = recPtr->GetCollect("ExtendedInfo2");
					sClientInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
					if (false == clientUuid.empty() && clientUuid.compare(sClientInfo.strClientId) == 0)
						break;
				}
			}

			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
		{
			return QuerySuccessWithoutResult;
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

QueryResultType XhBFISDBOperationImp::QueryClientInfoByID(ST_ClientInfo& sClientInfo,IN bool bOverlapped /*= true*/)
{
    STRY;
    CString strMsg = _T("");
    CString strSQL = _T("");
    SimpleConnection conn(this);
    int				nRestAff = 0;
    _variant_t		varFieldVal;
    _RecordsetPtr	recPtr = NULL;
    if(sClientInfo.strClientId == "")
    {
        TTRACE("[数据库]通过GUID查询客户信息失败，传入客户GUID为空 \r\n");
        return QueryFail;
    }
    strMsg = _T("call proc_clientinfo_selectbyid(\"%s\")");
    strSQL.Format(strMsg,sClientInfo.strClientId.c_str());
	TTRACE("[数据库]通过GUID查询客户信息语句:%s \r\n",strSQL);
    if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
    {       
        DISPLAY_LOG("数据库","通过GUID查询客户信息失败","执行SQL语句失败","",0);
        return QueryFail;
    }
    try
    {
        if(nRestAff > 0 && !recPtr->adoEOF)
        {
			if (bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("Name");
				sClientInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("CredenitialsType");
                sClientInfo.strCredenitialsType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Credenitial");
				sClientInfo.strCredenitial = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Phone");
				sClientInfo.strPhone = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Content");
				sClientInfo.strContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sClientInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sClientInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sClientInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
		{
			return QuerySuccessWithoutResult;
		}
    }
    catch(_com_error e)
    {
        TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
        return QueryFail;
    }
    return QuerySuccessWithResult;
    SCATCH;
    return QueryFail;
}


BOOL XhBFISDBOperationImp::TempWayToAddClientInfo(ST_ClientInfo stClientInfo)
{
	STRY;
	iSOC_AutoInitCOM autoInitCom;
	SimpleConnection conn(this);
	CString strSQL;
	strSQL.Format("insert into ClientInfo(ClientId,Name,CredenitialsType,Credenitial,Phone,Content,ExtendedInfo,ExtendedInfo1,ExtendedInfo2)"
		"Values(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")",stClientInfo.strClientId.c_str(),stClientInfo.strName.c_str(),
		stClientInfo.strCredenitialsType.c_str(),stClientInfo.strCredenitial.c_str(),stClientInfo.strPhone.c_str(),stClientInfo.strContent.c_str(),
        stClientInfo.nExtendedInfo,stClientInfo.strExtendedInfo1.c_str(),stClientInfo.strExtendedInfo2.c_str());
	try
	{
		_variant_t RecordsAffected;
		TTRACE("[数据库]添加客户信息语句:%s \r\n",strSQL);
		conn.m_pCon->Execute((_bstr_t)strSQL,&RecordsAffected,adCmdText);		
		int iRestAff = RecordsAffected.intVal;	
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%s",__FUNCTION__,__LINE__,e.ErrorMessage());
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
#if 0
BOOL XhBFISDBOperationImp::ExcuteSQLByCmd(ST_ClientInfo stClientInfo)
{
	STRY;
	iSOC_AutoInitCOM autoInitCom;
	 SimpleConnection conn(this);
	_CommandPtr pCmd = NULL;
#if 0
	_ParameterPtr inoutParam1 = NULL;
	_ParameterPtr inParam[7];
#endif
	try
	{
// 		CString strMsg = _T("proc_clientinfo_insert(?,\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")");
// 		CString strSQL;
// 		strSQL.Format(stClientInfo.strName.c_str(),stClientInfo.strCredenitial.c_str(),stClientInfo.strPhone.c_str(),
// 			stClientInfo.strContent.c_str(),stClientInfo.nExtendedInfo,stClientInfo.strExtendedInfo1.c_str(),
// 			stClientInfo.strExtendedInfo2.c_str());

		HRESULT hr = pCmd.CreateInstance(__uuidof(Command));
		if (FAILED(hr))
		{
			CString strError;
			strError.Format("%s[%d]:%s",__FUNCTION__,__LINE__,"创建CommandPtr对象失败");
			DISPLAY_LOG("数据库模块",(LPCSTR)strError,"","",0);
		}
// 		inoutParam1.CreateInstance(__uuidof(Parameter));
// 		for (int i = 0 ; i < 7 ; i ++)
// 		{
// 			inParam[i].CreateInstance(__uuidof(Parameter));
// 		}
#if 0
		inoutParam1 = pCmd->CreateParameter(_bstr_t("ClientId"),adVarChar,adParamInputOutput,61);
		inoutParam1->Value=_variant_t(stClientInfo.strClientId.c_str());
		pCmd->Parameters->Append(inoutParam1);
		inParam[0] = pCmd->CreateParameter(_bstr_t("Name"),adVarChar,adParamInput,60);
		inParam[0]->Value=_variant_t(stClientInfo.strName.c_str());
		pCmd->Parameters->Append(inParam[0]);
		inParam[1] = pCmd->CreateParameter(_bstr_t("Credenitial"),adVarChar,adParamInput,60);
		inParam[1]->Value=_variant_t(stClientInfo.strCredenitial.c_str());
		pCmd->Parameters->Append(inParam[1]);
		inParam[2] = pCmd->CreateParameter(_bstr_t("Phone"),adVarChar,adParamInput,20);
		inParam[2]->Value=_variant_t(stClientInfo.strPhone.c_str());
		pCmd->Parameters->Append(inParam[2]);
		inParam[3] = pCmd->CreateParameter(_bstr_t("Content"),adVarChar,adParamInput,20);
		inParam[3]->Value=_variant_t(stClientInfo.strContent.c_str());
		pCmd->Parameters->Append(inParam[3]);
		inParam[4] = pCmd->CreateParameter(_bstr_t("ExtendedInfo"),adInteger,adParamInput,11);
		inParam[4]->Value=int(stClientInfo.nExtendedInfo);
		pCmd->Parameters->Append(inParam[4]);
		inParam[5] = pCmd->CreateParameter(_bstr_t("ExtendedInfo1"),adVarChar,adParamInput,2000);
		inParam[5]->Value=_variant_t(stClientInfo.strExtendedInfo1.c_str());
		pCmd->Parameters->Append(inParam[5]);
		inParam[6] = pCmd->CreateParameter(_bstr_t("ExtendedInfo2"),adVarChar,adParamInput,2000);
		inParam[6]->Value=_variant_t(stClientInfo.strExtendedInfo2.c_str());
		pCmd->Parameters->Append(inParam[6]);

		pCmd->ActiveConnection = conn.m_pCon;
		pCmd->CommandText = _bstr_t("proc_clientinfo_insert");
		pCmd->CommandType = adCmdStoredProc;
#else
		_ParameterPtr paramter;
		CString strSQL;
		strSQL.Format("proc_branchinfo_insert");
		pCmd->ActiveConnection = conn.m_pCon;
		pCmd->CommandText = _bstr_t(strSQL);
		pCmd->CommandType = adCmdStoredProc;

		paramter = pCmd->CreateParameter("BranchId",adVarChar,adParamInput,sizeof("111"),_variant_t("111"));
		pCmd->Parameters->Append(paramter);
		paramter = pCmd->CreateParameter("Name",adVarChar,adParamInput,sizeof("1234"),_variant_t("1234"));
		pCmd->Parameters->Append(paramter);
		paramter = pCmd->CreateParameter("Address",adVarChar,adParamInput,sizeof("aabb"),_variant_t("aabb"));
		pCmd->Parameters->Append(paramter);
#endif


		//pCmd->PutCommandText("proc_clientinfo_insert");
//		pCmd->PutCommandText((LPCSTR)strSQL);
		//pCmd->PutCommandType(adCmdStoredProc);
// 		_variant_t RecordsAffected;
// 		pRecord = pCmd->Execute(NULL,&RecordsAffected,adCmdStoredProc);
		pCmd->Execute(NULL,NULL,adCmdStoredProc);
		//pCmd->Parameters->GetItem("ClientId")->GetValue();
		pCmd.Detach();
	}
	catch(_com_error e)
	{ 
		TTRACE("%s[%d]:%s",__FUNCTION__,__LINE__,e.ErrorMessage());
		DISPLAY_LOG("数据库模块","执行SQL语句失败","","",0);
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
#endif
QueryResultType XhBFISDBOperationImp::ManageClientInfo(DBOperType enOperType, ST_ClientInfo& sClientInfo, IN int nValue/* = 0*/)
{
	STRY;
    CString strMsg = _T("");
    CString strSQL = _T("");
    switch(enOperType)
    {
    case DBO_QUERY:
		if (sClientInfo.strClientId != _T(""))
		{
			return QueryClientInfoByID(sClientInfo,false);
		}
		else if (sClientInfo.strCredenitial != _T(""))
		{
			return QueryClientInfoByCredenitial(sClientInfo);
		}
		else
		{
			DISPLAY_LOG("数据库","查询客户信息失败","传入客户GUID和身份证号均为空","",0);
			return QueryFail;
		}
    case DBO_ADD:
        {
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(sClientInfo.strClientId,    "添加客户信息");
        //BFIS_ASSERT_STDSTRING(sClientInfo.strName,        "添加客户信息");
        //BFIS_ASSERT_STDSTRING(sClientInfo.strCredenitial, "添加客户信息");
#else
            if(sClientInfo.strClientId == "" || sClientInfo.strName == "" || sClientInfo.strCredenitial == "")
            {
                TTRACE("[数据库]添加客户信息失败,传入客户ID、名称以及身份证号为空 \r\n");
                return QueryFail;
			}
#endif
// 			if(TempWayToAddClientInfo(sClientInfo))
// 			{
// 				return QuerySuccessWithoutResult;
// 			}
// 			else
// 			{
// 				return QueryFail;
// 			}
			strSQL.Format("call proc_clientinfo_insert(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")",
				sClientInfo.strClientId.c_str(),sClientInfo.strName.c_str(),sClientInfo.strCredenitialsType.c_str(),
                sClientInfo.strCredenitial.c_str(),sClientInfo.strPhone.c_str(),sClientInfo.strContent.c_str(),sClientInfo.nExtendedInfo,
                sClientInfo.strExtendedInfo1.c_str(),sClientInfo.strExtendedInfo2.c_str());
        }
        break;
    case DBO_UPDATE:
        {
#if USE_BFIS_ASSERT
        //BFIS_ASSERT_STDSTRING(sClientInfo.strClientId,    "更新客户信息");
        //BFIS_ASSERT_STDSTRING(sClientInfo.strName,        "更新客户信息");
        //BFIS_ASSERT_STDSTRING(sClientInfo.strCredenitial, "更新客户信息");
#else
            if(sClientInfo.strClientId == "" || sClientInfo.strName == "" || sClientInfo.strCredenitial == "")
            {
                TTRACE("[数据库]更新客户信息失败,传入客户ID、名称以及身份证号为空 \r\n");
                return QueryFail;
			}
#endif
			if (nValue == 0)
			{
				strMsg = _T("call proc_clientinfo_update(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")");
			}
            else
			{
				strMsg = _T("call proc_clientinfo_updatebycredenitial(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")");
			}
			strSQL.Format(strMsg,sClientInfo.strClientId.c_str(),sClientInfo.strName.c_str(),sClientInfo.strCredenitialsType.c_str(),
                sClientInfo.strCredenitial.c_str(),sClientInfo.strPhone.c_str(),sClientInfo.strContent.c_str(),sClientInfo.nExtendedInfo
				,sClientInfo.strExtendedInfo1.c_str(),sClientInfo.strExtendedInfo2.c_str());
        }
        break;
    case DBO_DEL:
        {
#if USE_BFIS_ASSERT
            BFIS_ASSERT_STDSTRING(sClientInfo.strClientId, "删除客户信息");
#else
            if(sClientInfo.strClientId == "")
            {
                TTRACE("[数据库]删除客户信息失败,传入客户ID为空 \r\n");
                return QueryFail;
            }
#endif
			if (DeleteInfoById(DataType_ClientInfo,sClientInfo.strClientId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
        }
        break;
	default:
		{
			TTRACE("管理客户信息失败，未知错误%s[%d]\r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
    }

    SimpleConnection conn(this);
    int				nRestAff = 0;
    _variant_t		varFieldVal;
    _RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理客户信息语句:%s \r\n",strSQL);
    if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
    {       
        DISPLAY_LOG("数据库","管理客户信息失败,","执行SQL语句失败","",0);
        return QueryFail;
    }
    return QuerySuccessWithoutResult;
	SCATCH;
	return QueryFail;
}

ISOC_BOOL XhBFISDBOperationImp::QueryDiffRoleInfo(IN int nAll,IN OUT vector<ST_RoleInfo>& vecRoleInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
	strSQL.Format(strMsg,_T("roleinfo"),nAll);
	TTRACE("[数据库]查询新增角色信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询新增角色信息失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_RoleInfo stRoleInfo;
				varFieldVal = recPtr->GetCollect("RoleInfoId");
				stRoleInfo.strRoleInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Name");
				stRoleInfo.strRoleName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RoleLevel");
				stRoleInfo.nRoleLevel = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				stRoleInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				stRoleInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				stRoleInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BranchId");
				stRoleInfo.strBranchInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Flag");
				stRoleInfo.nFlag = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
				vecRoleInfo.push_back(stRoleInfo);
                if (stRoleInfo.nExtendedInfo == -1)
                {
                    m_strRoleInfo = stRoleInfo;
                }
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

QueryResultType XhBFISDBOperationImp::QueryRoleInfoByID(ST_RoleInfo& sRoleInfo,IN bool bOverlapped /*= true*/)
{
    STRY;
    CString strMsg = _T("");
    CString strSQL = _T("");
    SimpleConnection conn(this);
    int				nRestAff = 0;
    _variant_t		varFieldVal;
    _RecordsetPtr	recPtr = NULL;
    if(sRoleInfo.strRoleInfoId == "")
    {
        TTRACE("[数据库]通过GUID查询角色信息失败,传入角色GUID为空 \r\n");
        return QueryFail;
    }
    strMsg = _T("call proc_roleinfo_selectbyid(\"%s\")");
    strSQL.Format(strMsg,sRoleInfo.strRoleInfoId.c_str());
	TTRACE("[数据库]通过GUID查询角色信息语句:%s \r\n",strSQL);
    if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
    {       
        DISPLAY_LOG("数据库","通过GUID查询角色信息失败","执行SQL语句失败","",0);
        return QueryFail;
    }
    try
    {
        if(nRestAff > 0 && !recPtr->adoEOF)
        {
			if (bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("Name");
				sRoleInfo.strRoleName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RoleLevel");
				sRoleInfo.nRoleLevel = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sRoleInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sRoleInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sRoleInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BranchId");
				sRoleInfo.strBranchInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Flag");
				sRoleInfo.nFlag = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
        }
		else
		{
			return QuerySuccessWithoutResult;
		}
    }
    catch(_com_error e)
    {
        TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
        return QueryFail;
    }
    return QuerySuccessWithResult;
    SCATCH;
    return QueryFail;
}

QueryResultType XhBFISDBOperationImp::ManageRoleInfo(DBOperType enOperType,ST_RoleInfo& sRoleInfo)
{
    STRY;
    CString strMsg = _T("");
    CString strSQL = _T("");
    switch(enOperType)
    {
    case DBO_QUERY:
        return QueryRoleInfoByID(sRoleInfo,false);
    case DBO_ADD:
        {
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(sRoleInfo.strRoleInfoId,   "添加角色信息");
        BFIS_ASSERT_STDSTRING(sRoleInfo.strRoleName,     "添加角色信息");
        BFIS_ASSERT_STDSTRING(sRoleInfo.strBranchInfoId, "添加角色信息");
#else
            if(sRoleInfo.strRoleInfoId == "" || sRoleInfo.strRoleName == "" || sRoleInfo.strBranchInfoId == "")
            {
                DISPLAY_LOG("数据库","添加角色信息失败","传入角色GUID或角色名称或网点GUID为空","",0);
                return QueryFail;
            }
#endif
            strMsg = _T("call proc_roleinfo_insert(\"%s\",\"%s\",%d,%d,\"%s\",\"%s\",\"%s\",%d)");
            strSQL.Format(strMsg,sRoleInfo.strRoleInfoId.c_str(),sRoleInfo.strRoleName.c_str(),sRoleInfo.nRoleLevel,
				sRoleInfo.nExtendedInfo,sRoleInfo.strExtendedInfo1.c_str(),sRoleInfo.strExtendedInfo2.c_str(),
				sRoleInfo.strBranchInfoId.c_str(),sRoleInfo.nFlag);
        }
        break;
    case DBO_UPDATE:
        {
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(sRoleInfo.strRoleInfoId,   "更新角色信息");
        BFIS_ASSERT_STDSTRING(sRoleInfo.strRoleName,     "更新角色信息");
        BFIS_ASSERT_STDSTRING(sRoleInfo.strBranchInfoId, "更新角色信息");
#else
            if(sRoleInfo.strRoleInfoId == "" || sRoleInfo.strRoleName == "" || sRoleInfo.strBranchInfoId == "")
            {
				DISPLAY_LOG("数据库","更新角色信息失败","传入角色GUID或角色名称或网点GUID为空","",0);
                return QueryFail;
            }
#endif
            strMsg = _T("call proc_roleinfo_update(\"%s\",\"%s\",%d,%d,\"%s\",\"%s\",\"%s\",%d)");
            strSQL.Format(strMsg,sRoleInfo.strRoleInfoId.c_str(),sRoleInfo.strRoleName.c_str(),sRoleInfo.nRoleLevel,
				sRoleInfo.nExtendedInfo,sRoleInfo.strExtendedInfo1.c_str(),sRoleInfo.strExtendedInfo2.c_str(),
				sRoleInfo.strBranchInfoId.c_str(),sRoleInfo.nFlag);
        }
        break;
    case DBO_DEL:
        {
            if(sRoleInfo.strRoleInfoId == "")
            {
                DISPLAY_LOG("数据库","删除角色信息失败","传入角色GUID为空","",0);
                return QueryFail;
            }
			if (DeleteInfoById(DataType_RoleInfo,sRoleInfo.strRoleInfoId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
        }
        break;
	default:
		{
			TTRACE("[数据库]管理角色信息失败，未知错误:%s[%d]",__FUNCTION__,__LINE__);
			return QueryFail;
		}
    }
    SimpleConnection conn(this);
    int				nRestAff = 0;
    _variant_t		varFieldVal;
    _RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理角色信息语句:%s \r\n",strSQL);
    if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
    {       
        DISPLAY_LOG("数据库","管理角色信息失败","执行SQL语句失败","",0);
        return QueryFail;
    }
    return QuerySuccessWithoutResult;
    SCATCH;
    return QueryFail;
}

ISOC_BOOL XhBFISDBOperationImp::QueryDiffProduceInfo(IN int nAll,IN OUT vector<ST_ProduceInfo>& vecProduceInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
	strSQL.Format(strMsg,_T("produceinfo"),nAll);
	TTRACE("[数据库]查询新增产品信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询新增产品信息失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_ProduceInfo sProduceInfo;
				varFieldVal = recPtr->GetCollect("ProduceId");
				sProduceInfo.strProduceId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Name");
				sProduceInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ProduceCode");
				sProduceInfo.strProduceCode = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Period");
				sProduceInfo.nPeriod = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Revenue");
				sProduceInfo.strRevenue = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("MiniAmount");
				sProduceInfo.nMiniAmount = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("RiskLevel");
				sProduceInfo.strRiskLevel = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SerialNumber");
				sProduceInfo.strSerialNumber = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PublishBeginTime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sProduceInfo.strPublishBeinTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("PublishEndTime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sProduceInfo.strPublishEndTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("ProductionType");
				sProduceInfo.strProductionType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ApplicableCustomer");
				sProduceInfo.strApplicableCustomer = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RevenueType");
				sProduceInfo.strRevenueType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("IncrementMoney");
				sProduceInfo.strIncrementMoney = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("CurrencyType");
				sProduceInfo.strCurrentyType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SealsBranch");
				sProduceInfo.strSealsBranch = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RevenueInitialDay");
				sProduceInfo.strRevenueInitialDay = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Deadline");
				sProduceInfo.strDeadLine = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PaymentDay");
				sProduceInfo.strPaymentDay = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("TrusteeFee");
				sProduceInfo.strTrusteeFee = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("CommissionCharge");
				sProduceInfo.strCommissionCharge = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Trustee");
				sProduceInfo.strTrustee = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("OverheadCharge");
				sProduceInfo.strOverheadCharge = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RevenueCalculation");
				sProduceInfo.strRevenueCalculation = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Content");
				sProduceInfo.strContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("MaxTime");
				sProduceInfo.nMaxTime = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("MimiTime");
				sProduceInfo.nMineTime = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("StandardTime");
				sProduceInfo.nStandardTime = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Prequestion");
				sProduceInfo.strPrequestion = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("IsPublished");
				sProduceInfo.nIsPublished = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("IsEnabled");
				sProduceInfo.nIsEnabled = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sProduceInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sProduceInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sProduceInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EnableMigrated");
				sProduceInfo.nEnableMigrated = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
				varFieldVal = recPtr->GetCollect("RecordExistDays");
				sProduceInfo.nRecordExistDays = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
                varFieldVal = recPtr->GetCollect("Type");
                sProduceInfo.nType = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
                varFieldVal = recPtr->GetCollect("RiskLevelDesc");
                sProduceInfo.strRiskLevelDesc = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("PROD_LIFECYCLE");
                sProduceInfo.nPROD_LIFECYCLE = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
				vecProduceInfo.push_back(sProduceInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

QueryResultType XhBFISDBOperationImp::QueryProduceInfoByID(ST_ProduceInfo& sProduceInfo,IN bool bOverlapped /*= true*/)
{
    STRY;
    CString strMsg = _T("");
    CString strSQL = _T("");
    SimpleConnection conn(this);
    int				nRestAff = 0;
    _variant_t		varFieldVal;
    _RecordsetPtr	recPtr = NULL;
    if(sProduceInfo.strProduceId == "")
    {
       DISPLAY_LOG("数据库","通过GUID查询产品信息失败","传入GUID为空","",0);
        return QueryFail;
    }
    strMsg = _T("call proc_produceinfo_selectbyid(\"%s\")");
    strSQL.Format(strMsg,sProduceInfo.strProduceId.c_str());
	TTRACE("[数据库]通过GUID查询产品信息语句:%s \r\n",strSQL);
    if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
    {       
        DISPLAY_LOG("数据库","通过GUID查询产品信息失败","执行SQL语句失败","",0);
        return QueryFail;
    }
    try
    {
        if(nRestAff > 0 && !recPtr->adoEOF)
        {
			if (bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("Name");
				sProduceInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ProduceCode");
				sProduceInfo.strProduceCode = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Period");
				sProduceInfo.nPeriod = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Revenue");
				sProduceInfo.strRevenue = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("MiniAmount");
				sProduceInfo.nMiniAmount = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("RiskLevel");
				sProduceInfo.strRiskLevel = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SerialNumber");
				sProduceInfo.strSerialNumber = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PublishBeginTime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sProduceInfo.strPublishBeinTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("PublishEndTime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sProduceInfo.strPublishEndTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("ProductionType");
				sProduceInfo.strProductionType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ApplicableCustomer");
				sProduceInfo.strApplicableCustomer = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RevenueType");
				sProduceInfo.strRevenueType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("IncrementMoney");
				sProduceInfo.strIncrementMoney = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("CurrencyType");
				sProduceInfo.strCurrentyType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SealsBranch");
				sProduceInfo.strSealsBranch = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RevenueInitialDay");
				sProduceInfo.strRevenueInitialDay = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Deadline");
				sProduceInfo.strDeadLine = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PaymentDay");
				sProduceInfo.strPaymentDay = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("TrusteeFee");
				sProduceInfo.strTrusteeFee = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("CommissionCharge");
				sProduceInfo.strCommissionCharge = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Trustee");
				sProduceInfo.strTrustee = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("OverheadCharge");
				sProduceInfo.strOverheadCharge = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RevenueCalculation");
				sProduceInfo.strRevenueCalculation = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Content");
				sProduceInfo.strContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("MaxTime");
				sProduceInfo.nMaxTime = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("MimiTime");
				sProduceInfo.nMineTime = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("StandardTime");
				sProduceInfo.nStandardTime = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Prequestion");
				sProduceInfo.strPrequestion = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("IsPublished");
				sProduceInfo.nIsPublished = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("IsEnabled");
				sProduceInfo.nIsEnabled = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sProduceInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sProduceInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sProduceInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EnableMigrated");
				sProduceInfo.nEnableMigrated = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
				varFieldVal = recPtr->GetCollect("RecordExistDays");
				sProduceInfo.nRecordExistDays = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
                varFieldVal = recPtr->GetCollect("Type");
                sProduceInfo.nType = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
                varFieldVal = recPtr->GetCollect("RiskLevelDesc");
                sProduceInfo.strRiskLevelDesc = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("PROD_LIFECYCLE");
                sProduceInfo.nPROD_LIFECYCLE = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
        }
		else
		{
			return QuerySuccessWithoutResult;
		}
    }
    catch(_com_error e)
    {
        TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
        return QueryFail;
    }
    return QuerySuccessWithResult;
    SCATCH;
    return QueryFail;
}

QueryResultType XhBFISDBOperationImp::ManageProduceInfo(DBOperType enOperType,ST_ProduceInfo&sProduceInfo)
{
    STRY;
    CString strMsg = _T("");
    CString strSQL = _T("");
	int i = 0;
    switch(enOperType)
    {
    case DBO_QUERY:
		return QueryProduceInfoByID(sProduceInfo,false);
    case DBO_ADD:
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(sProduceInfo.strProduceId,   "添加产品信息");
        BFIS_ASSERT_STDSTRING(sProduceInfo.strName,        "添加产品信息");
        BFIS_ASSERT_STDSTRING(sProduceInfo.strProduceCode, "添加产品信息");
#else
        if(sProduceInfo.strProduceId == "" || sProduceInfo.strName == "" || sProduceInfo.strProduceCode == "")
        {
			TTRACE("[数据库]产品信息:GUID:%s,Name:%s,ProduceCode:%s \r\n",sProduceInfo.strProduceId.c_str(),sProduceInfo.strName.c_str(),
				sProduceInfo.strProduceCode.c_str());
            DISPLAY_LOG("数据库","添加产品信息失败","传入GUID或产品名或产品编号为空","",0);
			return QueryFail;
        }
#endif
        strMsg = _T("call proc_produceinfo_insert(\"%s\",\"%s\",\"%s\",%d,\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,%d,%d,\"%s\",%d,%d,%d,\"%s\",\"%s\",%d,%d,%d,\"%s\",%d)");
        strSQL.Format(strMsg,sProduceInfo.strProduceId.c_str(),sProduceInfo.strName.c_str(),sProduceInfo.strProduceCode.c_str(),sProduceInfo.nPeriod,
			sProduceInfo.strRevenue.c_str(),sProduceInfo.nMiniAmount,sProduceInfo.strRiskLevel.c_str(),sProduceInfo.strSerialNumber.c_str(),
			sProduceInfo.strPublishBeinTime.c_str(),sProduceInfo.strPublishEndTime.c_str(),sProduceInfo.strProductionType.c_str(),sProduceInfo.strApplicableCustomer.c_str(),
			sProduceInfo.strRevenueType.c_str(),sProduceInfo.strIncrementMoney.c_str(),sProduceInfo.strCurrentyType.c_str(),sProduceInfo.strSealsBranch.c_str(),
			sProduceInfo.strRevenueInitialDay.c_str(),sProduceInfo.strDeadLine.c_str(),sProduceInfo.strPaymentDay.c_str(),sProduceInfo.strTrusteeFee.c_str(),
			sProduceInfo.strCommissionCharge.c_str(),sProduceInfo.strTrustee.c_str(),sProduceInfo.strOverheadCharge.c_str(),sProduceInfo.strRevenueCalculation.c_str(),
			sProduceInfo.strContent.c_str(),sProduceInfo.nMaxTime,sProduceInfo.nMineTime,sProduceInfo.nStandardTime,sProduceInfo.strPrequestion.c_str(),
			sProduceInfo.nIsPublished,sProduceInfo.nIsEnabled,sProduceInfo.nExtendedInfo,sProduceInfo.strExtendedInfo1.c_str(),
			sProduceInfo.strExtendedInfo2.c_str(),sProduceInfo.nEnableMigrated,sProduceInfo.nRecordExistDays,
            sProduceInfo.nType,sProduceInfo.strRiskLevelDesc.c_str(),sProduceInfo.nPROD_LIFECYCLE);
        break;
    case DBO_UPDATE:
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(sProduceInfo.strProduceId,   "更新产品信息");
        BFIS_ASSERT_STDSTRING(sProduceInfo.strName,        "更新产品信息");
        BFIS_ASSERT_STDSTRING(sProduceInfo.strProduceCode, "更新产品信息");
#else
        if (sProduceInfo.strProduceId == "" || sProduceInfo.strName == "" || sProduceInfo.strProduceCode == "")
        {
			TTRACE("[数据库]产品信息:GUID:%s,Name:%s,ProduceCode:%s \r\n",sProduceInfo.strProduceId.c_str(),sProduceInfo.strName.c_str(),
				sProduceInfo.strProduceCode.c_str());
            DISPLAY_LOG("数据库","更新产品信息失败","传入GUID或产品名或产品编号为空","",0);
			return QueryFail;
        }
#endif
		strMsg = _T("call proc_produceinfo_update(\"%s\",\"%s\",\"%s\",%d,\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,%d,%d,\"%s\",%d,%d,%d,\"%s\",\"%s\",%d,%d,%d,\"%s\",%d)");
		strSQL.Format(strMsg,sProduceInfo.strProduceId.c_str(),sProduceInfo.strName.c_str(),sProduceInfo.strProduceCode.c_str(),sProduceInfo.nPeriod,
			sProduceInfo.strRevenue.c_str(),sProduceInfo.nMiniAmount,sProduceInfo.strRiskLevel.c_str(),sProduceInfo.strSerialNumber.c_str(),
			sProduceInfo.strPublishBeinTime.c_str(),sProduceInfo.strPublishEndTime.c_str(),sProduceInfo.strProductionType.c_str(),sProduceInfo.strApplicableCustomer.c_str(),
			sProduceInfo.strRevenueType.c_str(),sProduceInfo.strIncrementMoney.c_str(),sProduceInfo.strCurrentyType.c_str(),sProduceInfo.strSealsBranch.c_str(),
			sProduceInfo.strRevenueInitialDay.c_str(),sProduceInfo.strDeadLine.c_str(),sProduceInfo.strPaymentDay.c_str(),sProduceInfo.strTrusteeFee.c_str(),
			sProduceInfo.strCommissionCharge.c_str(),sProduceInfo.strTrustee.c_str(),sProduceInfo.strOverheadCharge.c_str(),sProduceInfo.strRevenueCalculation.c_str(),
			sProduceInfo.strContent.c_str(),sProduceInfo.nMaxTime,sProduceInfo.nMineTime,sProduceInfo.nStandardTime,sProduceInfo.strPrequestion.c_str(),
			sProduceInfo.nIsPublished,sProduceInfo.nIsEnabled,sProduceInfo.nExtendedInfo,sProduceInfo.strExtendedInfo1.c_str(),
			sProduceInfo.strExtendedInfo2.c_str(),sProduceInfo.nEnableMigrated,sProduceInfo.nRecordExistDays,
            sProduceInfo.nType,sProduceInfo.strRiskLevelDesc.c_str(),sProduceInfo.nPROD_LIFECYCLE);
        break;
    case DBO_DEL:
		{
			if(sProduceInfo.strProduceId == "")
			{
				DISPLAY_LOG("数据库","删除产品信息失败","传入GUID为空","",0);
				return QueryFail;
			}
			if (DeleteInfoById(DataType_ProduceInfo,sProduceInfo.strProduceId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
			break;
		}
	default:
		{
			TTRACE("[数据库]管理产品信息失败,未知错误:%s[%d]",__FUNCTION__,__LINE__);
			return QueryFail;
		}
    }
    SimpleConnection conn(this);
    int				nRestAff = 0;
    _variant_t		varFieldVal;
    _RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理产品信息语句:%s \r\n",strSQL);
    if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
    {       
        DISPLAY_LOG("数据库","管理产品信息失败","执行SQL语句失败","",0);
        return QueryFail;
    }
    return QuerySuccessWithoutResult;
    SCATCH;
	return QueryFail;
}

//业务信息管理
QueryResultType XhBFISDBOperationImp::ManageBusinessInfo(IN DBOperType enOperType, IN OUT ST_BusinessInfo& sBusinessInfo)
{
	STRY;
	//CString strMsg = _T("");
	CString strSQL = _T("");
	std::string strTemp;
	switch(enOperType)
	{
	case DBO_QUERY:
		return QueryBusinessInfoByID(sBusinessInfo,false);
	case DBO_ADD:
#if 0
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strBusinessInfoId,      "添加业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strDateTime,            "添加业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strBranchId,            "添加业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strSubEquipmentIcmSign, "添加业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strEmployeeId,          "添加业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strClientId,            "添加业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strProduceId,           "添加业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strSerialNumber,        "添加业务信息");
#else
		if(sBusinessInfo.strBusinessInfoId == _T("") || sBusinessInfo.strDateTime == _T("") ||
			sBusinessInfo.strBranchId == _T("") || sBusinessInfo.strSubEquipmentIcmSign == _T("") ||
			sBusinessInfo.strEmployeeId == _T("") || sBusinessInfo.strClientId == _T("") ||
			sBusinessInfo.strProduceId == _T("") || sBusinessInfo.strSerialNumber == _T(""))
		{
			TTRACE("[数据库],传入业务信息:BusinessInfoId:%s,DateTime:%s,BranchId:%s,SubEquipmentIcmSign:%s,EmployeeId:%s,\
				  ClientId:%s,ProduceId:%s,SerialNumber:%s \r\n",sBusinessInfo.strBusinessInfoId.c_str(),
				  sBusinessInfo.strDateTime.c_str(),sBusinessInfo.strBranchId.c_str(),sBusinessInfo.strSubEquipmentIcmSign.c_str(),
				  sBusinessInfo.strEmployeeId.c_str(),sBusinessInfo.strClientId.c_str(),sBusinessInfo.strProduceId.c_str(),
				  sBusinessInfo.strSerialNumber.c_str());
			DISPLAY_LOG("数据库","增加业务信息失败","传入GUID或时间或网点GUID或子设备IcmSign或员工GUID或客户GUID或产品GUID或流水号为空","",0);
			return QueryFail;
		}
#endif
		strMsg = _T("call proc_businessinfo_insert(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\")");
		strSQL.Format(strMsg,sBusinessInfo.strBusinessInfoId.c_str(),sBusinessInfo.strDateTime.c_str(),sBusinessInfo.strBranchId.c_str(),
			sBusinessInfo.strClientId.c_str(),sBusinessInfo.strEmployeeId.c_str(),sBusinessInfo.strProduceId.c_str(),sBusinessInfo.strSubEquipmentId.c_str(),
			sBusinessInfo.nExtendedInfo,sBusinessInfo.strExtendedInfo1.c_str(),sBusinessInfo.strExtendedInfo2.c_str(),
			sBusinessInfo.strSubEquipmentIcmSign.c_str(),sBusinessInfo.strSerialNumber.c_str(),sBusinessInfo.nMigrated,
			sBusinessInfo.strFileCenter.c_str());
#else
		if(m_BusinessMan.addBusinessInfo(strTemp,sBusinessInfo)){strSQL.Format("%s",strTemp.c_str());}
#endif
		break;
	case DBO_UPDATE:
#if 0
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strBusinessInfoId,      "更新业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strDateTime,            "更新业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strBranchId,            "更新业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strSubEquipmentIcmSign, "更新业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strEmployeeId,          "更新业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strClientId,            "更新业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strProduceId,           "更新业务信息");
        BFIS_ASSERT_STDSTRING(sBusinessInfo.strSerialNumber,        "更新业务信息");
#else
		if(sBusinessInfo.strBusinessInfoId == _T("") || sBusinessInfo.strDateTime == _T("") ||
			sBusinessInfo.strBranchId == _T("") || sBusinessInfo.strSubEquipmentIcmSign == _T("") ||
			sBusinessInfo.strEmployeeId == _T("") || sBusinessInfo.strClientId == _T("") ||
			sBusinessInfo.strProduceId == _T("") || sBusinessInfo.strSerialNumber == _T(""))
		{
			TTRACE("[数据库],传入业务信息:BusinessInfoId:%s,DateTime:%s,BranchId:%s,SubEquipmentIcmSign:%s,EmployeeId:%s,\
				   ClientId:%s,ProduceId:%s,SerialNumber:%s \r\n",sBusinessInfo.strBusinessInfoId.c_str(),
				   sBusinessInfo.strDateTime.c_str(),sBusinessInfo.strBranchId.c_str(),sBusinessInfo.strSubEquipmentIcmSign.c_str(),
				   sBusinessInfo.strEmployeeId.c_str(),sBusinessInfo.strClientId.c_str(),sBusinessInfo.strProduceId.c_str(),
				   sBusinessInfo.strSerialNumber.c_str());
			DISPLAY_LOG("数据库","更新业务信息失败","传入GUID或时间或网点GUID或子设备IcmSign或员工GUID或客户GUID或产品GUID或流水号为空","",0);
			return QueryFail;
		}
#endif
		strMsg = _T("call proc_businessinfo_update(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\",%d)");
		strSQL.Format(strMsg,sBusinessInfo.strBusinessInfoId.c_str(),sBusinessInfo.strDateTime.c_str(),sBusinessInfo.strBranchId.c_str(),
			sBusinessInfo.strClientId.c_str(),sBusinessInfo.strEmployeeId.c_str(),sBusinessInfo.strProduceId.c_str(),sBusinessInfo.strSubEquipmentId.c_str(),
			sBusinessInfo.nExtendedInfo,sBusinessInfo.strExtendedInfo1.c_str(),sBusinessInfo.strExtendedInfo2.c_str(),
			sBusinessInfo.strSubEquipmentIcmSign.c_str(),sBusinessInfo.strSerialNumber.c_str(),sBusinessInfo.nMigrated,
			sBusinessInfo.strFileCenter.c_str());
#else
		if(m_BusinessMan.updateBusinessInfo(strTemp,sBusinessInfo)){strSQL.Format("%s",strTemp.c_str());}
#endif
		break;
	case DBO_DEL:
		{
			if(sBusinessInfo.strBusinessInfoId == "")
			{
				DISPLAY_LOG("数据库","删除业务信息失败","传入GUID为空","",0);
				return QueryFail;
			}
			if (DeleteInfoById(DataType_BusinessInfo,sBusinessInfo.strBusinessInfoId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
		}
		break;
	default:
		{
			TTRACE("[数据库]管理业务信息失败，未知错误%s[%d] \r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理业务信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{   
		DISPLAY_LOG("数据库","管理业务信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	return QuerySuccessWithoutResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::QueryBusinessInfoByID(IN OUT ST_BusinessInfo& sBusinessInfo,IN bool bOverlapped /*= true*/)
{
	STRY;
	if(sBusinessInfo.strBusinessInfoId == "")
	{
		DISPLAY_LOG("数据库","通过GUID查询业务信息失败","传入GUID为空","",0);
		return QueryFail;
	}
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_businessinfo_selectbyid(\"%s\")");
	strSQL.Format(strMsg,sBusinessInfo.strBusinessInfoId.c_str());
	TTRACE("[数据库]通过GUID查询业务信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过GUID查询业务信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			if (bOverlapped)
			{
#if 0
				varFieldVal = recPtr->GetCollect("Datetime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sBusinessInfo.strDateTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("BranchId");
				sBusinessInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ClientId");
				sBusinessInfo.strClientId   = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				sBusinessInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ProduceId");
				sBusinessInfo.strProduceId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SubEquipmentId");
				sBusinessInfo.strSubEquipmentId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sBusinessInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sBusinessInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sBusinessInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SubEquipmentIcmSign");
				sBusinessInfo.strSubEquipmentIcmSign = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SerialNumber");
				sBusinessInfo.strSerialNumber = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Migrated");
				sBusinessInfo.nMigrated = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("FileCenter");
				sBusinessInfo.strFileCenter = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
#else
				m_BusinessMan.querySingleBusinessInfo(varFieldVal,recPtr,sBusinessInfo);
#endif
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

QueryResultType XhBFISDBOperationImp::QueryBusinessInfoBySerialNumber(ST_BusinessInfo& sBusinessInfo,bool bOverlapped/* = true*/)
{
	STRY;
	if(sBusinessInfo.strSerialNumber == "")
	{
		DISPLAY_LOG("数据库","通过流水号查询业务信息失败","传入流水号为空","",0);
		return QueryFail;
	}
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_businessinfo_selectbyserialnumber(\"%s\")");
	strSQL.Format(strMsg,sBusinessInfo.strSerialNumber.c_str());
	TTRACE("[数据库]通过流水号查询业务信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过流水号查询业务信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			if (bOverlapped)
			{
#if 0
				varFieldVal = recPtr->GetCollect("BusInessInfoId");
				sBusinessInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Datetime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sBusinessInfo.strDateTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("BranchId");
				sBusinessInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ClientId");
				sBusinessInfo.strClientId   = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				sBusinessInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ProduceId");
				sBusinessInfo.strProduceId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SubEquipmentId");
				sBusinessInfo.strSubEquipmentId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sBusinessInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sBusinessInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sBusinessInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SubEquipmentIcmSign");
				sBusinessInfo.strSubEquipmentIcmSign = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SerialNumber");
				sBusinessInfo.strSerialNumber = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Migrated");
				sBusinessInfo.nMigrated = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("FileCenter");
				sBusinessInfo.strFileCenter = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
#else
				if(!m_BusinessMan.querySingleBusinessInfo(varFieldVal,recPtr,sBusinessInfo)){return QueryFail;}
#endif
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
ISOC_BOOL XhBFISDBOperationImp::QueryDiffBusinessInfo(IN int nAll,IN OUT vector<ST_BusinessInfo>& vecBusinessInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
	strSQL.Format(strMsg,_T("businessinfo"),nAll);
	TTRACE("[数据库]查询新增业务信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询新增业务信息失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_BusinessInfo sBusinessInfo;
#if 0
				varFieldVal = recPtr->GetCollect("Datetime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sBusinessInfo.strDateTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("BusInessInfoId");
				sBusinessInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BranchId");
				sBusinessInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ClientId");
				sBusinessInfo.strClientId   = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				sBusinessInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ProduceId");
				sBusinessInfo.strProduceId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SubEquipmentId");
				sBusinessInfo.strSubEquipmentId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sBusinessInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sBusinessInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sBusinessInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SubEquipmentIcmSign");
				sBusinessInfo.strSubEquipmentIcmSign = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SerialNumber");
				sBusinessInfo.strSerialNumber = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Migrated");
				sBusinessInfo.nMigrated = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("FileCenter");
				sBusinessInfo.strFileCenter = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
#else
				if(m_BusinessMan.querySingleBusinessInfo(varFieldVal,recPtr,sBusinessInfo))
				{	
#endif
					vecBusinessInfo.push_back(sBusinessInfo);
				}
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDBOperationImp::GetMCSessoon(LONG_PTR pMCSession)
{
    if(NULL == pMCSession)
    {
        return FALSE;
    }
    m_pMCSeesion = pMCSession; 
    int nRet = -1;
    nRet = SendReqGetSocUserGroup();
    if (nRet < 0)
    {
        TTRACE("查询soc用户组信息失败,返回:%d \r\n",nRet);
        return nRet;
    }
    nRet = SendReqGetEquipmentPermission();
    if (nRet < 0)
    {
        TTRACE("查询soc用户权限信息失败,返回:%d \r\n",nRet);
        return nRet;
    }
    return TRUE;
}
int XhBFISDBOperationImp::OnGotUserGroupDataCallback(ISOC_DWORDPTR dwUserCookie, ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen)
{
    XhBFISDBOperationImp *pThis = (XhBFISDBOperationImp*)dwUserCookie;
    if(pThis != NULL)
    {
        pThis->GotUserGroupDataCallback(fromAddr,pData,dataLen);
    }
    return TRUE;
}
int XhBFISDBOperationImp::OnUserCreateStatusCallback(ISOC_DWORDPTR dwUserCookie, ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen)
{
    XhBFISDBOperationImp *pThis = (XhBFISDBOperationImp*)dwUserCookie;
    if(pThis != NULL)
    {
        pThis->UserCreateStatusCallback(fromAddr,pData,dataLen);
    }
    return TRUE;
}
int XhBFISDBOperationImp::UserCreateStatusCallback(ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen)
{
	m_vecUserInfo.clear();
    ST_ICMS_CMD_HEADER* pCMDHead = (ST_ICMS_CMD_HEADER*)pData;
    const char* pXmlinfo = (const char*)pData+sizeof(ST_ICMS_CMD_HEADER);
    if (NULL == pXmlinfo)
    {
        return FALSE;
    }
	CString strxml = pXmlinfo;  
	iCMSP_XmlParser XmlParser;
    XmlParser.SetDoc(strxml, strxml.GetLength());
    if(XmlParser.FindElem("SetUser_Ack"))
    {  
        XmlParser.IntoElem();
		if(XmlParser.FindElem("ResultCode"))
		{
			m_ResultCode = XmlParser.GetDataInt();
		}    
    } 
    return TRUE;
}
int XhBFISDBOperationImp::GotUserGroupDataCallback(ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen)
{
	m_vecUserInfo.clear();
    ST_ICMS_CMD_HEADER* pCMDHead = (ST_ICMS_CMD_HEADER*)pData;
    const char* pXmlinfo = (const char*)pData+sizeof(ST_ICMS_CMD_HEADER);
    if (NULL == pXmlinfo)
    {
        return FALSE;
    }
	CString strxml = pXmlinfo;  
	iCMSP_XmlParser XmlParser;
    XmlParser.SetDoc(strxml, strxml.GetLength());
    if(XmlParser.FindElem("GetAllUserInfo_Ack"))
    {
        XmlParser.IntoElem();
        if (XmlParser.FindElem("UserGroupInfoList"))
        {
            XmlParser.IntoElem();
            while(XmlParser.FindElem("UserGroupInfo"))
            {
                ST_UserGroupInfo stUserGroupInfo;         
                stUserGroupInfo.nUserGroupID = XmlParser.GetAttribInt("UserGroupID");      
                stUserGroupInfo.strUserGroupName = XmlParser.GetAttrib("UserGroupName");
                stUserGroupInfo.strICMSSign= XmlParser.GetAttrib("ICMSSign");
                stUserGroupInfo.nICMSUserGroupID = XmlParser.GetAttribInt("ICMSUserGroupID");
                stUserGroupInfo.strParentICMSSign= XmlParser.GetAttrib("ParentICMSSign");
                stUserGroupInfo.nICMSParentGroupID = XmlParser.GetAttribInt("FindChildElem");         
                m_vecUserGroupInfo.push_back(stUserGroupInfo);
				TTRACE("获取到的用户组名为：%s \r\n",stUserGroupInfo.strUserGroupName.c_str());
            } 
			XmlParser.OutOfElem();
        }   
		if (XmlParser.FindElem("UserInfoList"))
		{
			XmlParser.IntoElem();
			while(XmlParser.FindElem("UserInfo"))
			{
				ST_SocUserInfo stUserInfo;         
				stUserInfo.nUserID = XmlParser.GetAttribInt("UserID");      
				stUserInfo.nUserGroupID = XmlParser.GetAttribInt("UserGroupID");
				stUserInfo.nICMSUserGroupID= XmlParser.GetAttribInt("ICMSUserGroupID");
				stUserInfo.strICMSSign = XmlParser.GetAttrib("ICMSSign");
				stUserInfo.nICMSUserID= XmlParser.GetAttribInt("ICMSUserID");
				stUserInfo.strUserName = XmlParser.GetAttrib("UserName");         
				m_vecUserInfo.push_back(stUserInfo);
			}
		}
    } 
    return TRUE;
}
int XhBFISDBOperationImp::GotEquipmentPermissionDataCallback(ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen)
{
	m_vecSubEquipment.clear();
    ST_ICMS_CMD_HEADER* pCMDHead = (ST_ICMS_CMD_HEADER*)pData;
    const char* pXmlinfo = (const char*)pData+sizeof(ST_ICMS_CMD_HEADER);
    if (pXmlinfo == NULL)
    {
        return FALSE;
    }
    CString strxml = pXmlinfo;
    iCMSP_XmlParser XmlParser;
    XmlParser.SetDoc(strxml, strxml.GetLength());
    if(XmlParser.FindElem("ExecuteAck") && XmlParser.IntoElem())
    {
        if (XmlParser.FindElem("SubEquipmentInfoList") && XmlParser.IntoElem())
        {
            while(XmlParser.FindElem("SubEquipmentInfo"))
            {
                ST_SubEquipment SubEquipment;         
                SubEquipment.nSubEquipmentID = XmlParser.GetAttribInt("SubEquipmentID");
                SubEquipment.strICMSSign = XmlParser.GetAttrib("ICMSSign");
                SubEquipment.nICMSSubEquipmentID= XmlParser.GetAttribInt("ICMSSubEquipmentID");
                SubEquipment.nEquipmentID = XmlParser.GetAttribInt("EquipmentID");
                SubEquipment.nMSCSID= XmlParser.GetAttribInt("MSCSID");
                SubEquipment.nICMSEquipmentID = XmlParser.GetAttribInt("ICMSEquipmentID ");  
                SubEquipment.strSubName = XmlParser.GetAttrib("SubName"); 
                SubEquipment.nSubType = XmlParser.GetAttribInt("SubType"); 
                if (SubEquipment.nSubType == 513)
                {
                    m_vecSubEquipment.push_back(SubEquipment);
                }
            }   
        }         
    }
    return TRUE;
}
int XhBFISDBOperationImp::OnGotEquipmentPermissionDataCallback(ISOC_DWORDPTR dwUserCookie, ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen)
{
    XhBFISDBOperationImp *pThis = (XhBFISDBOperationImp*)dwUserCookie;
    if(pThis != NULL)
    {
        pThis->GotEquipmentPermissionDataCallback(fromAddr,pData,dataLen);
    }
    return TRUE;
}
int __stdcall G_OnAffairOverTimeCallback(ISOC_DWORDPTR dwUserCookie)
{
    return 0;
}
ISOC_BOOL XhBFISDBOperationImp::SendReqGetSocUserGroup()
{
    CString strXmlFormat = _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<GetAllUserInfo_Req>"
        "<Cookie>%d</Cookie>"
        "<ICMSSign>%s</ICMSSign>"
        "</GetAllUserInfo_Req>");

    CString strXML;
    long long Cookie = GetTickCount();
    CString strICMSSign ;
    strICMSSign.Format("%s",m_strLocalBranchId.c_str());
    strXML.Format(strXmlFormat,GetTickCount(),strICMSSign);
    BYTE tmp1[2048] = {0};
    memcpy(tmp1+18,(LPCTSTR)strXML,strXML.GetLength());
    int nCMD = ISMS_GET_USERGROUP_LINK_REQ;
    ST_ICMS_CMD_HEADER* header = (ST_ICMS_CMD_HEADER*)tmp1;
    m_nCount++;
    header->wCmdMainType = ICMS_TYPE_CMDTYPE_CTRL;
    header->dwExndSize = strXML.GetLength();
    header->dwSeqID = m_nCount;
    header->dwCmdSubType = nCMD;
    header->wExtendType = ICMD_TYPE_EXDTYPE_XML;
    header->wSrcType = ICMS_CLIENT_MANAGE;
    ISOC_DWORDPTR pCookie = (ISOC_DWORDPTR)this;
    int nRet = iSOC_ManSendCmd2MCServer(m_pMCSeesion,(BYTE*)tmp1,strXML.GetLength()+18,nCMD,30000,pCookie,OnGotUserGroupDataCallback,G_OnAffairOverTimeCallback);
    return nRet;
}

ISOC_BOOL XhBFISDBOperationImp::SendReqCreateUserGroup()
{
    CString strXmlFormat = _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
        "<SetUserGroupInfo_Req>"
        "<Cookie>%d</Cookie>"
        "<UserGroupInfo UserGroupID="" ParentGroupID="" ICMSSign=%s ICMSUserGroupID="" ICMSParentGroupID=0 UserGroupName=\"%s\" PowerPop="" ExtenInfo="" UpdateType=1/>"
        "</SetUserGroupInfo_Req>");

    CString strXML;
    long long Cookie = GetTickCount();
    CString strICMSSign ;
    strICMSSign.Format("%s",m_strLocalBranchId.c_str());
    strXML.Format(strXmlFormat,GetTickCount(),strICMSSign,m_strRoleInfo.strRoleName.c_str());
    int Len = strXML.GetLength();
    BYTE tmp1[2048] = {0};
    memcpy(tmp1+18,(LPCTSTR)strXML,strXML.GetLength());
    int nCMD = ISMS_SET_USERGROUP_REQ;
    ST_ICMS_CMD_HEADER* header = (ST_ICMS_CMD_HEADER*)tmp1;
    m_nCount++;
    header->wCmdMainType = ICMS_TYPE_CMDTYPE_CTRL;
    header->dwExndSize = strXML.GetLength();
    header->dwSeqID = m_nCount;
    header->dwCmdSubType = nCMD;
    header->wExtendType = ICMD_TYPE_EXDTYPE_XML;
    header->wSrcType = ICMS_CLIENT_MANAGE;
    int nRet = iSOC_ManSendCmd2MCServer(m_pMCSeesion,(BYTE*)tmp1,strXML.GetLength()+18,nCMD,30000,Cookie);
    return nRet;
}
ISOC_BOOL XhBFISDBOperationImp::SendReqModPassword(ST_SocUserInfo& stUserInfo,ST_EmployeeInfo& stEmployee)
{
	CString strXmlFormat = _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
		"<ModUserPass_Req>"
			"<Cookie>%d</Cookie>"
			"<UserID>%d</UserID>"
			"<ICMSSign>%s</ICMSSign>"
			"<ICMSUserID>%d</ICMSUserID>"
			"<PassInfo EncryptType=1 Password=%s>"
		"</ModUserPass_Req>");

	CString strXML;
	long long Cookie = GetTickCount();
	CString strICMSSign ;
	strICMSSign.Format("%s",m_strLocalBranchId.c_str());
	strXML.Format(strXmlFormat,GetTickCount(),stUserInfo.nUserID,strICMSSign,stUserInfo.nICMSUserID,stEmployee.strPassword.c_str());
	int Len = strXML.GetLength();
	BYTE tmp1[1024] =  {0};
	memcpy(tmp1+18,(LPCTSTR)strXML,strXML.GetLength());
	int nCMD =  ISMS_MOD_USER_PASSWORD_REQ;
	ST_ICMS_CMD_HEADER* header = (ST_ICMS_CMD_HEADER*)tmp1;
	m_nCount++;
	header->wCmdMainType = ICMS_TYPE_CMDTYPE_CTRL;
	header->dwExndSize = strXML.GetLength();
	header->dwSeqID = m_nCount;
	header->dwCmdSubType = nCMD;
	header->wExtendType = ICMD_TYPE_EXDTYPE_XML;
	header->wSrcType = ICMS_CLIENT_MANAGE;
	int nRet = iSOC_ManSendCmd2MCServer(m_pMCSeesion,(BYTE*)tmp1,strXML.GetLength()+18,nCMD,30000,Cookie);
	return nRet;
}
ISOC_BOOL XhBFISDBOperationImp::UpdateUserPermission(vector<ST_EmployeeInfo>& vecEmployeeInfo)
{
	STRY;
	SendReqGetSocUserGroup();
	SendReqGetEquipmentPermission();
	Sleep(60 * 1000);
	if (!m_vecUserInfo.empty())
	{
		for each(auto userinfo in m_vecUserInfo)
		{
			for each(auto employeeinfo in vecEmployeeInfo)
			{
				if (userinfo.strUserName == employeeinfo.strTLNUM)
				{
					SendReqSetUserPermission(userinfo);
				}
			}
		}
	}
	else
	{
		TTRACE("soc用户为空");
	}
	for each(auto userGroup in m_vecUserGroupInfo)
	{
		if (userGroup.strUserGroupName == "理财用户组")
		{
			SendReqSetUserGroupPermission(userGroup);
		}
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDBOperationImp::SendReqSetUserPermission(ST_SocUserInfo& stUserInfo)
{
	TTRACE("开始发送信令更新上级员工信息");
	CString strXmlFormat = _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
							  "<ModUserDeviceAuthority_Req>\r\n"
							  "<Cookie>%d</Cookie>\r\n"
							  "<UserID>%d</UserID>\r\n"
							  "<ICMSSign>%s</ICMSSign>\r\n"
							  "<ICMSUserID>%d</ICMSUserID>\r\n"
							  "<DeviceAuthorityInfoList>\r\n"
							  "%s</DeviceAuthorityInfoList>\r\n"
							  "</ModUserDeviceAuthority_Req>"); 

	CString strDeviceAuthFormat = _T("<DeviceAuthorityInfo SubEquipmentID=\"%d\" ICMSSign=\"%s\" ICMSSubEquipmentID=\"%d\" DevPowerPop=\"%s\" UpdateType=\"1\"/>\r\n");
	CString strICMSSign;
	strICMSSign.Format("%s",m_strLocalBranchId.c_str());
	CString strDeviceAuthXML;
	if(m_vecSubEquipment.size() > 0)
	{
		int i = 0;
		for (m_vecSubEquipment[i]; i < m_vecSubEquipment.size(); ++i)
		{      
			CString strDevPowerPop;
			strDevPowerPop.Format("%s","1793,1794,1795");
			CString strChlidDeviceAuthXML;
			strChlidDeviceAuthXML.Format(strDeviceAuthFormat,m_vecSubEquipment[i].nSubEquipmentID,
				strICMSSign,m_vecSubEquipment[i].nICMSSubEquipmentID,strDevPowerPop);
			strDeviceAuthXML += strChlidDeviceAuthXML;
		}
	} 
	CString strXML;
	long long Cookie = GetTickCount();
	CString strDeviceAuth ;
	strDeviceAuth.Format("%s",strDeviceAuthXML);
	strXML.Format(strXmlFormat,Cookie,stUserInfo.nUserID,strICMSSign,stUserInfo.nICMSUserID,strDeviceAuth);
	TTRACE("发送权限信令为：%s\r\n",strXML);
	int Len = strXML.GetLength();
	BYTE* tmp1 = new BYTE[Len+100];
	ZeroMemory(tmp1,Len+100);
	memcpy(tmp1+18,(LPCTSTR)strXML,strXML.GetLength());
	int nCMD = ISMS_MOD_USER_DEVICE_AUTHORITY_REQ;
	ST_ICMS_CMD_HEADER* header = (ST_ICMS_CMD_HEADER*)tmp1;
	m_nCount++;
	header->wCmdMainType = ICMS_TYPE_CMDTYPE_CTRL;
	header->dwExndSize = strXML.GetLength();
	header->dwSeqID = m_nCount;
	header->dwCmdSubType = nCMD;
	header->wExtendType = ICMD_TYPE_EXDTYPE_XML;
	header->wSrcType = ICMS_CLIENT_MANAGE;
	int nRet = 0;
	STRY;
	nRet = iSOC_ManSendCmd2MCServer(m_pMCSeesion,(BYTE*)tmp1,strXML.GetLength()+18,nCMD,30000,Cookie);
	SCATCH;
	SAFE_DELETE_ARRAY(tmp1);
	return nRet;
}
ISOC_BOOL XhBFISDBOperationImp::SendReqCreateUser(ST_EmployeeInfo& sEmployeeInfo,ST_UserGroupInfo& sUserGroupInfo)
{
    CString strXmlFormat = _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
        <SetUser_Req>\r\n\
        <Cookie>%d</Cookie>\r\n\
        <UserInfo UserID=\"0\" ICMSSign=\"%s\" ICMSUserID=\"\" ICMSUserGroupID=\"%d\" UserName=\"%s\" UserLevel=\"\" Phone=\"\" eMail=\"\" SysPowerPop=\"\" ExtenInfo=\"\" UpdateType=\"1\"/>\r\n\
        <PassInfo EncryptType=\"1\" Password=\"%s\"/>\r\n\
        <DeviceAuthorityInfoList>%s\r\n\
        </DeviceAuthorityInfoList>\r\n\
        </SetUser_Req>");

    CString strDeviceAuthFormat = _T("<DeviceAuthorityInfo SubEquipmentID=\"%d\" ICMSSign=\"%s\" ICMSSubEquipmentID=\"%d\" DevPowerPop=\"%s\" UpdateType=\"1\"/>\r\n");
    CString strICMSSign;
    strICMSSign.Format("%s",m_strLocalBranchId.c_str());
    CString strDeviceAuthXML;
    if(m_vecSubEquipment.size() > 0)
    {
        int i = 0;
        for (m_vecSubEquipment[i]; i < m_vecSubEquipment.size(); ++i)
        {      
            CString strDevPowerPop;
            strDevPowerPop.Format("%s","1793,1794,1795");
            CString strChlidDeviceAuthXML;
            strChlidDeviceAuthXML.Format(strDeviceAuthFormat,m_vecSubEquipment[i].nSubEquipmentID,
                    strICMSSign,m_vecSubEquipment[i].nICMSSubEquipmentID,strDevPowerPop);
                    strDeviceAuthXML += strChlidDeviceAuthXML;
        }
    } 
    CString strXML;
    long long Cookie = GetTickCount();
    CString strDeviceAuth ;
    strDeviceAuth.Format("%s",strDeviceAuthXML);
    strXML.Format(strXmlFormat,GetTickCount(),strICMSSign,sUserGroupInfo.nICMSUserGroupID,sEmployeeInfo.strName.c_str(),sEmployeeInfo.strPassword.c_str(),strDeviceAuth);
   
	/*iCMSP_XmlParser XmlParser;
	XmlParser.SetDoc(strXML, strXML.GetLength());
	if(XmlParser.FindElem("SetUser_Req") )
	{
	XmlParser.IntoElem();
	XmlParser.FindElem("UserInfo");
	string sign = XmlParser.GetAttrib("ICMSSign"); 
	string UserName = XmlParser.GetAttrib("UserName");
	int Updatetype = XmlParser.GetAttribInt("UpdateType");
	}
	if(XmlParser.FindElem("DeviceAuthorityInfoList") && XmlParser.IntoElem())
	{
	if(XmlParser.FindElem("DeviceAuthorityInfo"))
	{
	int SubEquipmentID = XmlParser.GetAttribInt("SubEquipmentID");
	int Updatetype = XmlParser.GetAttribInt("UpdateType");
	}
	}*/
    int Len = strXML.GetLength();
    BYTE* tmp1 = new BYTE[Len+100];
    ZeroMemory(tmp1,Len+100);
    memcpy(tmp1+18,(LPCTSTR)strXML,strXML.GetLength());
    int nCMD = ISMS_SET_USER_REQ;
    ST_ICMS_CMD_HEADER* header = (ST_ICMS_CMD_HEADER*)tmp1;
    m_nCount++;
    header->wCmdMainType = ICMS_TYPE_CMDTYPE_CTRL;
    header->dwExndSize = strXML.GetLength();
    header->dwSeqID = m_nCount;
    header->dwCmdSubType = nCMD;
    header->wExtendType = ICMD_TYPE_EXDTYPE_XML;
    header->wSrcType = ICMS_CLIENT_MANAGE;
	int nRet = 0;
	STRY;
	ISOC_DWORDPTR pCookie = (ISOC_DWORDPTR)this;
    int nRet = iSOC_ManSendCmd2MCServer(m_pMCSeesion,(BYTE*)tmp1,strXML.GetLength()+18,nCMD,30000,pCookie,OnUserCreateStatusCallback,G_OnAffairOverTimeCallback);
	SCATCH;
	SAFE_DELETE_ARRAY(tmp1);
    return nRet;
}

ISOC_BOOL XhBFISDBOperationImp::SendReqSetUserGroupPermission(ST_UserGroupInfo& sUserGroupInfo)
{
    CString strXmlFormat = _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<ModUserDeviceAuthority_Req>"
        "<Cookie>%d</Cookie>"
        "<UserID>%d</UserID>"
        "<ICMSSign>%s</ICMSSign>"
        "<ICMSUserID>%d</ICMSUserID>"
        "<DeviceAuthorityInfoList>%s</DeviceAuthorityInfoList>"
        "</ModUserDeviceAuthority_Req>"); 
    int i = 0;
    CString strDeviceAuthXML;
    for (m_vecSubEquipment[i]; i < m_vecSubEquipment.size(); ++i)
    {      
        CString strDevPowerPop;
        strDevPowerPop.Format("%s","1793,1794,1795");
        CString strICMSSign ;
        strICMSSign.Format("%s",m_vecSubEquipment[i].strICMSSign.c_str());
        CString strChlidDeviceAuthXML;
        strChlidDeviceAuthXML.Format("<DeviceAuthorityInfo SubEquipmentID=%d ICMSSign=%s ICMSSubEquipmentID=%d DevPowerPop=\"%s\" UpdateType=1/>\r\n"
            ,m_vecSubEquipment[i].nSubEquipmentID,strICMSSign,m_vecSubEquipment[i].nICMSSubEquipmentID,strDevPowerPop);
        strDeviceAuthXML += strChlidDeviceAuthXML;
    }
    CString strXML;
    long long Cookie = GetTickCount();
    CString strDeviceAuthorityInfo;
    strDeviceAuthorityInfo.Format("%s",strDeviceAuthXML);
    CString strICMSSign ;
    strICMSSign.Format("%s",m_strLocalBranchId.c_str());
    strXML.Format(strXmlFormat,GetTickCount(),sUserGroupInfo.nUserGroupID,strICMSSign,sUserGroupInfo.nICMSUserGroupID,strDeviceAuthorityInfo);
	int Len = strXML.GetLength();
	BYTE* tmp1 = new BYTE[Len+100];
	ZeroMemory(tmp1,Len+100);
	memcpy(tmp1+18,(LPCTSTR)strXML,strXML.GetLength());
    int nCMD = ISMS_MOD_USER_DEVICE_AUTHORITY_REQ;
    ST_ICMS_CMD_HEADER* header = (ST_ICMS_CMD_HEADER*)tmp1;
    m_nCount++;
    header->wCmdMainType = ICMS_TYPE_CMDTYPE_CTRL;
    header->dwExndSize = strXML.GetLength();
    header->dwSeqID = m_nCount;
    header->dwCmdSubType = nCMD;
    header->wExtendType = ICMD_TYPE_EXDTYPE_XML;
    header->wSrcType = ICMS_CLIENT_MANAGE;
    int nRet = 0;
	STRY;
	nRet = iSOC_ManSendCmd2MCServer(m_pMCSeesion,(BYTE*)tmp1,strXML.GetLength()+18,nCMD,30000,Cookie);
	SCATCH;
	SAFE_DELETE_ARRAY(tmp1);
    return TRUE;
}
ISOC_BOOL XhBFISDBOperationImp::SendReqGetEquipmentPermission()
{
    CString strXmlFormat = _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<SubEquipmentInfoReq>"
        "<Cookie>%d</Cookie>"
        "<EquipmentID>""</EquipmentID>"
        "<SubEquipmentIDSet>""</SubEquipmentIDSet>"
        "<ICMSSign></ICMSSign>"
        "<ICMSSubEquipmentIDSet>""</ICMSSubEquipmentIDSet>"
        "<MSCSID>""</MSCSID>"
        "<UintSubEquipmentCode>""</UintSubEquipmentCode>"
        "<BinData>0</BinData>"
        "<UserID></UserID>"
        "</SubEquipmentInfoReq>"); 

    CString strXML;
    long long Cookie = GetTickCount();
    CString strICMSSign ;
    strICMSSign.Format("%s",m_strLocalBranchId.c_str());
    strXML.Format(strXmlFormat,GetTickCount());
    int Len = strXML.GetLength();
    BYTE tmp1[1024] = {0};
    memcpy(tmp1+18,(LPCTSTR)strXML,strXML.GetLength());
    int nCMD = ISMS_GET_SUBEQUIPMENT_REQ;
    ST_ICMS_CMD_HEADER* header = (ST_ICMS_CMD_HEADER*)tmp1;
    m_nCount++;
    header->wCmdMainType = ICMS_TYPE_CMDTYPE_CTRL;
    header->dwExndSize = strXML.GetLength();
    header->dwSeqID = m_nCount;
    header->dwCmdSubType = nCMD;
    header->wExtendType = ICMD_TYPE_EXDTYPE_XML;
    header->wSrcType = ICMS_CLIENT_MANAGE;
    ISOC_DWORDPTR pCookie = (ISOC_DWORDPTR)this;
    int nRet = iSOC_ManSendCmd2MCServer(m_pMCSeesion,(BYTE*)tmp1,strXML.GetLength()+18,nCMD,30000,pCookie,OnGotEquipmentPermissionDataCallback,G_OnAffairOverTimeCallback);
    return nRet;
}
ISOC_BOOL XhBFISDBOperationImp::IsHaveOnUserGroup()
{
    if (m_vecUserGroupInfo.size() > 0)
    {
        int i = 0;
        for (m_vecUserGroupInfo[i]; i < m_vecUserGroupInfo.size(); ++i)
        {
            if (m_vecUserGroupInfo[i].strUserGroupName == m_strRoleInfo.strRoleName)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

ISOC_BOOL XhBFISDBOperationImp::ManageEmployeeInfoAndSocUser(DBOperType enType,ST_EmployeeInfo& sEmployeeInfo)
{   
    STRY;
    int nRet = -1;
	BOOL bRet = FALSE;
	BOOL bHaveUser = FALSE;
#if 0
	if ( FALSE == IsHaveOnUserGroup())
	{
		nRet = SendReqCreateUserGroup();
		if (nRet < 0)
		{
			TTRACE("创建soc用户组失败,返回:%d \r\n",nRet);
			return nRet;
		}
		Sleep(30);
	}
#endif
	vector<ST_RoleInfo> vecRoleInfo;
	ST_RoleInfo strRoleInfo;
	QueryRoleInfo(vecRoleInfo);
	if (vecRoleInfo.empty())
	{
		return FALSE;
	}
	for each(auto roleinfo in vecRoleInfo)
	{
		if(roleinfo.nExtendedInfo == -1)		
		{
			strRoleInfo = roleinfo;
			bRet = TRUE;
			break;
		}
	}
	if (bRet == FALSE)
	{
		return bRet;
	}
	for each(auto userinfo in m_vecUserInfo)
	{
		if (sEmployeeInfo.strName == userinfo.strUserName)
		{
			bHaveUser = TRUE;
		}		
	}
	switch(enType)
	{
	case DBO_ADD:
		{
			if (bHaveUser == FALSE)
			{
				if (m_vecUserGroupInfo.size() > 0)
				{
					int i = 0;
					int nCreateCoount = 0;
					for (m_vecUserGroupInfo[i]; i < m_vecUserGroupInfo.size(); ++i)
					{
						if (m_vecUserGroupInfo[i].strUserGroupName == strRoleInfo.strRoleName)
						{     
RECREATEUSER:
							nRet = SendReqCreateUser(sEmployeeInfo,m_vecUserGroupInfo[i]);
							Sleep(1000);
							if(nCreateCoount < 5 && m_ResultCode == 0)
							{
								nCreateCoount++;
								goto RECREATEUSER;
							}
							m_ResultCode = 0;
						}
					}
				}
				else
				{
					TTRACE("理财用户组为空 \r\n");
				}
				ST_UserMapInfo stUserMapInfo;
				stUserMapInfo.strEmployeeId = sEmployeeInfo.strEmployeeId;
				stUserMapInfo.strSocUsername = sEmployeeInfo.strName;
				stUserMapInfo.strSocPassword = sEmployeeInfo.strPassword;
				string userMapInfoGuid;
				CreateNewGuid(userMapInfoGuid);
				stUserMapInfo.strUserMapInfoId = userMapInfoGuid;
				if(QueryFail == ManageUserMapInfo(DBO_ADD,stUserMapInfo))
				{
					return FALSE;
				}
				return TRUE;
			}
			else
			{
				for each(auto userinfo in m_vecUserInfo)
				{
					if (sEmployeeInfo.strName == userinfo.strUserName)
					{
						SendReqModPassword(userinfo,sEmployeeInfo);
					}		
				}
			}			
		}
		break;
	case DBO_UPDATE:
		{
			for each(auto userinfo in m_vecUserInfo)
			{
				if (sEmployeeInfo.strName == userinfo.strUserName)
				{
					SendReqModPassword(userinfo,sEmployeeInfo);
				}		
			}	
		}
		break;
	}
    return TRUE;
    SCATCH;
    return FALSE;
}
//雇员信息管理
QueryResultType XhBFISDBOperationImp::ManageEmployeeInfo(IN DBOperType enOperType, IN OUT ST_EmployeeInfo& sEmployeeInfo)
{
	STRY;
	CString strSQL = _T("");
	switch(enOperType)
	{
	case DBO_QUERY:
		return QueryEmployeeInfoByID(sEmployeeInfo,false);
	case DBO_ADD:
		{         
#if USE_BFIS_ASSERT
			BFIS_ASSERT_STDSTRING(sEmployeeInfo.strEmployeeId,  "增加员工信息");
			BFIS_ASSERT_STDSTRING(sEmployeeInfo.strBranchId,    "增加员工信息");
			BFIS_ASSERT_STDSTRING(sEmployeeInfo.strName,        "增加员工信息");
			BFIS_ASSERT_STDSTRING(sEmployeeInfo.strPassword,    "增加员工信息");
			//BFIS_ASSERT_STDSTRING(sEmployeeInfo.strCardId,      "增加员工信息");
			//BFIS_ASSERT_STDSTRING(sEmployeeInfo.strRoleId,      "增加员工信息");
#else
			if(sEmployeeInfo.strEmployeeId == _T("") || sEmployeeInfo.strBranchId == _T("") || sEmployeeInfo.strName == _T("") ||
				sEmployeeInfo.strPassword == _T("") || sEmployeeInfo.strCardId == _T("") || sEmployeeInfo.strRoleId == _T(""))
			{
				TTRACE("[数据库]传入员工信息:EmployeeId:%s,BranchId:%s,Name:%s,Password:%s,CardId:%s,RoleId:%s \r\n",
					sEmployeeInfo.strEmployeeId.c_str(),sEmployeeInfo.strBranchId.c_str(),sEmployeeInfo.strName.c_str(),
					sEmployeeInfo.strPassword.c_str(),sEmployeeInfo.strCardId.c_str(),sEmployeeInfo.strRoleId.c_str());
				DISPLAY_LOG("数据库","添加员工信息失败","传入GUID或网点GUID或员工名字或密码或卡ID或角色GUID为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_employeeinfo_insert(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d)",
				sEmployeeInfo.strEmployeeId.c_str(),sEmployeeInfo.strBranchId.c_str(),sEmployeeInfo.strName.c_str(),
				sEmployeeInfo.strPassword.c_str(),sEmployeeInfo.strCardId.c_str(),sEmployeeInfo.strRoleId.c_str(),
				sEmployeeInfo.strPhone.c_str(),sEmployeeInfo.nExtendedInfo,sEmployeeInfo.strExtendedInfo1.c_str(),
				sEmployeeInfo.strExtendedInfo2.c_str(),sEmployeeInfo.nFlag,sEmployeeInfo.stPasswordEidtTime.c_str(),
                sEmployeeInfo.strJDBRID.c_str(),sEmployeeInfo.strTLNUM.c_str(),sEmployeeInfo.strTEL.c_str(),
                sEmployeeInfo.strGW.c_str(),sEmployeeInfo.strSTS.c_str(),sEmployeeInfo.strTLINST.c_str(),
                sEmployeeInfo.strUSERNAME.c_str(),sEmployeeInfo.strROLENAME.c_str(),sEmployeeInfo.strUSERSTATUS.c_str(),sEmployeeInfo.nPassErrorCount);
		}
		break;
	case DBO_UPDATE:
		{
#if USE_BFIS_ASSERT
		    BFIS_ASSERT_STDSTRING(sEmployeeInfo.strEmployeeId,  "更新员工信息");
		    BFIS_ASSERT_STDSTRING(sEmployeeInfo.strBranchId,    "更新员工信息");
		    BFIS_ASSERT_STDSTRING(sEmployeeInfo.strName,        "更新员工信息");
		    BFIS_ASSERT_STDSTRING(sEmployeeInfo.strPassword,    "更新员工信息");
		    //BFIS_ASSERT_STDSTRING(sEmployeeInfo.strCardId,      "更新员工信息");
		    //BFIS_ASSERT_STDSTRING(sEmployeeInfo.strRoleId,      "更新员工信息");
#else
			if(sEmployeeInfo.strEmployeeId == _T("") || sEmployeeInfo.strBranchId == _T("") || sEmployeeInfo.strName == _T("") ||
				sEmployeeInfo.strPassword == _T("") || sEmployeeInfo.strCardId == _T("") || sEmployeeInfo.strRoleId == _T(""))
			{
				TTRACE("[数据库]传入员工信息:EmployeeId:%s,BranchId:%s,Name:%s,Password:%s,CardId:%s,RoleId:%s \r\n",
					sEmployeeInfo.strEmployeeId.c_str(),sEmployeeInfo.strBranchId.c_str(),sEmployeeInfo.strName.c_str(),
					sEmployeeInfo.strPassword.c_str(),sEmployeeInfo.strCardId.c_str(),sEmployeeInfo.strRoleId.c_str());
				DISPLAY_LOG("数据库","更新员工信息失败","传入GUID或网点GUID或员工名字或密码或卡ID或角色GUID为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_employeeinfo_update(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d)",
				sEmployeeInfo.strEmployeeId.c_str(),sEmployeeInfo.strBranchId.c_str(),sEmployeeInfo.strName.c_str(),
				sEmployeeInfo.strPassword.c_str(),sEmployeeInfo.strCardId.c_str(),sEmployeeInfo.strRoleId.c_str(),
				sEmployeeInfo.strPhone.c_str(),sEmployeeInfo.nExtendedInfo,sEmployeeInfo.strExtendedInfo1.c_str(),
                sEmployeeInfo.strExtendedInfo2.c_str(),sEmployeeInfo.nFlag,sEmployeeInfo.stPasswordEidtTime.c_str(),
                sEmployeeInfo.strJDBRID.c_str(),sEmployeeInfo.strTLNUM.c_str(),sEmployeeInfo.strTEL.c_str(),
                sEmployeeInfo.strGW.c_str(),sEmployeeInfo.strSTS.c_str(),sEmployeeInfo.strTLINST.c_str(),
                sEmployeeInfo.strUSERNAME.c_str(),sEmployeeInfo.strROLENAME.c_str(),sEmployeeInfo.strUSERSTATUS.c_str(),sEmployeeInfo.nPassErrorCount);
		}
		break;
	case DBO_DEL:
		{
			if(sEmployeeInfo.strEmployeeId == "")
			{
				DISPLAY_LOG("数据库","删除员工信息失败","传入GUID为空","",0);
				return QueryFail;
			}
			if (DeleteInfoById(DataType_EmployeeInfo,sEmployeeInfo.strEmployeeId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
		}
		break;
	default:
		{
			TTRACE("[数据库]管理员工信息失败，未知错误%s[%d] \r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理员工信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{  
		DISPLAY_LOG("数据库","管理员工信息失败","SQL语句执行失败","",0);
		return QueryFail;
	}
	return QuerySuccessWithoutResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::QueryEmployeeInfoByID(IN OUT ST_EmployeeInfo& sEmployeeInfo,IN bool bOverlapped /*= true*/)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	if (sEmployeeInfo.strEmployeeId == _T(""))
	{
		DISPLAY_LOG("数据库","通过GUID查询员工信息失败","传入GUID为空","",0);
		return QueryFail;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_employeeinfo_selectbyemployeeid(\"%s\")");
	strSQL.Format(strMsg,sEmployeeInfo.strEmployeeId.c_str());
	TTRACE("[数据库]通过GUID查询员工信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过GUID查询员工信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			if(bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("EmployeeId");
				sEmployeeInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BranchId");
				sEmployeeInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Name");
				sEmployeeInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Password");
				sEmployeeInfo.strPassword = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("CardId");
				sEmployeeInfo.strCardId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RoleId");
				sEmployeeInfo.strRoleId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Phone");
				sEmployeeInfo.strPhone = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sEmployeeInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sEmployeeInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sEmployeeInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Flag");
				sEmployeeInfo.nFlag = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
                varFieldVal = recPtr->GetCollect("PasswordEidtTime");
                if(varFieldVal.vt != VT_NULL)
                {
                    DATE dt = varFieldVal.date;  
                    COleDateTime da = COleDateTime(dt);  
                    sEmployeeInfo.stPasswordEidtTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
                }
                varFieldVal = recPtr->GetCollect("JDBRID");
                sEmployeeInfo.strJDBRID = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("TLNUM");
                sEmployeeInfo.strTLNUM = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("TEL");
                sEmployeeInfo.strTEL = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("GW");
                sEmployeeInfo.strGW = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("STS");
                sEmployeeInfo.strSTS = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("TLINST");
                sEmployeeInfo.strTLINST = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("USERNAME");
                sEmployeeInfo.strUSERNAME = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("ROLENAME");
                sEmployeeInfo.strROLENAME = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("USERSTATUS");
                sEmployeeInfo.strUSERSTATUS = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PassErrorCount");
				sEmployeeInfo.nPassErrorCount = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
ISOC_BOOL XhBFISDBOperationImp::QueryDiffEmployeeInfo(IN int nAll,IN OUT vector<ST_EmployeeInfo>& vecEmployeeInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
	strSQL.Format(strMsg,_T("employeeinfo"),nAll);
	TTRACE("[数据库]查询新增员工信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询新增员工信息失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_EmployeeInfo sEmployeeInfo;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				sEmployeeInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BranchId");
				sEmployeeInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Name");
				sEmployeeInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Password");
				sEmployeeInfo.strPassword = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("CardId");
				sEmployeeInfo.strCardId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RoleId");
				sEmployeeInfo.strRoleId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Phone");
				sEmployeeInfo.strPhone = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sEmployeeInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sEmployeeInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sEmployeeInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Flag");
				sEmployeeInfo.nFlag = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
                varFieldVal = recPtr->GetCollect("PasswordEidtTime");
                if(varFieldVal.vt != VT_NULL)
                {
                    DATE dt = varFieldVal.date;  
                    COleDateTime da = COleDateTime(dt);  
                    sEmployeeInfo.stPasswordEidtTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
                }
                varFieldVal = recPtr->GetCollect("JDBRID");
                sEmployeeInfo.strJDBRID = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("TLNUM");
                sEmployeeInfo.strTLNUM = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("TEL");
                sEmployeeInfo.strTEL = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("GW");
                sEmployeeInfo.strGW = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("STS");
                sEmployeeInfo.strSTS = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("TLINST");
                sEmployeeInfo.strTLINST = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("USERNAME");
                sEmployeeInfo.strUSERNAME = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("ROLENAME");
                sEmployeeInfo.strROLENAME = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("USERSTATUS");
                sEmployeeInfo.strUSERSTATUS = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PassErrorCount");
				sEmployeeInfo.nPassErrorCount = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				vecEmployeeInfo.push_back(sEmployeeInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

//员工权限信息管理
QueryResultType XhBFISDBOperationImp::ManageEmployeePurviewInfo(IN DBOperType enOperType, IN OUT ST_EmployeePurviewInfo& sEmployeePurviewInfo)
{
	STRY;
	CString strSQL = _T("");
	switch(enOperType)
	{
	case DBO_QUERY:
		return QueryEmployeePurviewInfoByID(sEmployeePurviewInfo,false);
	case DBO_ADD:
		{
#if USE_BFIS_ASSERT
			BFIS_ASSERT_STDSTRING(sEmployeePurviewInfo.strEmployeePurviewId, "增加员工权限信息失败");
			BFIS_ASSERT_STDSTRING(sEmployeePurviewInfo.strEmployeeId,        "增加员工权限信息失败");
			BFIS_ASSERT_STDSTRING(sEmployeePurviewInfo.strPurviewInfoId,     "增加员工权限信息失败");
#else
			if(sEmployeePurviewInfo.strEmployeePurviewId == _T("") || sEmployeePurviewInfo.strEmployeeId == _T("") || 
				sEmployeePurviewInfo.strPurviewInfoId == _T(""))
			{
				TTRACE("数据库","传入员工信息:EmployeePurviewId:%s,EmployeeId:%s,PurviewInfoId:%s \r\n",
					sEmployeePurviewInfo.strEmployeePurviewId.c_str(),sEmployeePurviewInfo.strEmployeeId.c_str(),
					sEmployeePurviewInfo.strPurviewInfoId.c_str());
				DISPLAY_LOG("数据库","添加员工权限信息失败","传入GUID或员工GUID或权限GUID为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_employeepurview_insert(\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")",
				sEmployeePurviewInfo.strEmployeePurviewId.c_str(),sEmployeePurviewInfo.strEmployeeId.c_str(),
				sEmployeePurviewInfo.strPurviewInfoId.c_str(),sEmployeePurviewInfo.nExtendedInfo,
				sEmployeePurviewInfo.strExtendedInfo1.c_str(),sEmployeePurviewInfo.strExtendedInfo2.c_str());
		}
		break;
	case DBO_UPDATE:
		{
#if USE_BFIS_ASSERT
			BFIS_ASSERT_STDSTRING(sEmployeePurviewInfo.strEmployeePurviewId, "更新员工权限信息失败");
			BFIS_ASSERT_STDSTRING(sEmployeePurviewInfo.strEmployeeId,        "更新员工权限信息失败");
			BFIS_ASSERT_STDSTRING(sEmployeePurviewInfo.strPurviewInfoId,     "更新员工权限信息失败");
#else
			if(sEmployeePurviewInfo.strEmployeePurviewId == _T("") || sEmployeePurviewInfo.strEmployeeId == _T("") || 
				sEmployeePurviewInfo.strPurviewInfoId == _T(""))
			{
				TTRACE("数据库","传入员工信息:EmployeePurviewId:%s,EmployeeId:%s,PurviewInfoId:%s \r\n",
					sEmployeePurviewInfo.strEmployeePurviewId.c_str(),sEmployeePurviewInfo.strEmployeeId.c_str(),
					sEmployeePurviewInfo.strPurviewInfoId.c_str());
				DISPLAY_LOG("数据库","更新员工权限信息失败","传入GUID或员工GUID或权限GUID为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_employeepurview_update(\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")",
				sEmployeePurviewInfo.strEmployeePurviewId.c_str(),sEmployeePurviewInfo.strEmployeeId.c_str(),
				sEmployeePurviewInfo.strPurviewInfoId.c_str(),sEmployeePurviewInfo.nExtendedInfo,
				sEmployeePurviewInfo.strExtendedInfo1.c_str(),sEmployeePurviewInfo.strExtendedInfo2.c_str());
		}
		break;
	case DBO_DEL:
		{
			if(sEmployeePurviewInfo.strEmployeeId == "")
			{
				DISPLAY_LOG("数据库","删除员工权限信息失败","传入员工GUID为空","",0);
				return QueryFail;
			}
			strSQL.Format("call proc_employeepurview_deletebyemployeeid(\"%s\")",sEmployeePurviewInfo.strEmployeeId.c_str());
		}
		break;
	default:
		{
			TTRACE("[数据库]管理员工权限信息失败%s[%d]，未知错误 \r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理员工权限信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{  
		DISPLAY_LOG("数据库","管理员工权限信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	if(nRestAff == 0)
		return QuerySuccessWithoutResult;
	else
		return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::ManageEmployeePurviewInfoById(IN DBOperType enOperType, IN OUT ST_EmployeePurviewInfo & sEmployeePurviewInfo)
{
	STRY;
	CString strSQL = _T("");
	switch (enOperType)
	{
	case DBO_DEL:
	{
		if (sEmployeePurviewInfo.strEmployeePurviewId == "")
		{
			DISPLAY_LOG("数据库", "删除员工权限信息失败", "传入员工GUID为空", "", 0);
			return QueryFail;
		}
		strSQL.Format("call proc_employeepurview_deletebykey(\"%s\")", sEmployeePurviewInfo.strEmployeePurviewId.c_str());
	}
	break;
	default:
	{
		TTRACE("[数据库]管理员工权限信息失败%s[%d]，未知错误 \r\n", __FUNCTION__, __LINE__);
		return QueryFail;
	}
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理员工权限信息语句:%s \r\n", strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL, recPtr, nRestAff))
	{
		DISPLAY_LOG("数据库", "管理员工权限信息失败", "执行SQL语句失败", "", 0);
		return QueryFail;
	}
	if (nRestAff == 0)
		return QuerySuccessWithoutResult;
	else
		return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::QueryEmployeePurviewInfoByID(IN OUT ST_EmployeePurviewInfo& stEmployeePurviewInfo,IN bool bOverlapped /*= true*/)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	if (stEmployeePurviewInfo.strEmployeePurviewId == _T(""))
	{
		DISPLAY_LOG("数据库","通过GUID查询员工权限信息失败","传入GUID为空","",0);
		return QueryFail;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_employeepurview_selectbyid(\"%s\")");
	strSQL.Format(strMsg,stEmployeePurviewInfo.strEmployeePurviewId.c_str());
	TTRACE("[数据库]通过ID查询员工权限信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过ID查询员工权限信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			if(bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("EmployeePurviewID");
				stEmployeePurviewInfo.strEmployeePurviewId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				stEmployeePurviewInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PurviewInfoID");
				stEmployeePurviewInfo.strPurviewInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				stEmployeePurviewInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				stEmployeePurviewInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				stEmployeePurviewInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::QueryEmployeePurviewInfoAll(IN OUT vector<ST_EmployeePurviewInfo>& vecInfos)
{
	STRY;
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strSQL = _T("call proc_employeepurview_select");
	TTRACE("[数据库]通过ID查询员工权限信息语句:%s \r\n", strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL, recPtr, nRestAff))
	{
		DISPLAY_LOG("数据库", "通过ID查询员工权限信息失败", "执行SQL语句失败", "", 0);
		return QueryFail;
	}
	try
	{
		if (nRestAff > 0)
		{
			while (!recPtr->adoEOF)
			{
				ST_EmployeePurviewInfo stEmployeePurviewInfo;
				varFieldVal = recPtr->GetCollect("EmployeePurviewID");
				stEmployeePurviewInfo.strEmployeePurviewId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				stEmployeePurviewInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PurviewInfoID");
				stEmployeePurviewInfo.strPurviewInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				stEmployeePurviewInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				stEmployeePurviewInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				stEmployeePurviewInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				BOOL bHasEmployeePvw = FALSE;
				vecInfos.push_back(stEmployeePurviewInfo);
				recPtr->MoveNext();
			}
			if (recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch (_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
ISOC_BOOL XhBFISDBOperationImp::QueryDiffEmployeePurviewInfo(IN int nAll,IN OUT vector<ST_EmployeePurviewInfo>& vecEmployeePurviewInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
	strSQL.Format(strMsg,_T("employeepurview"),nAll);
	TTRACE("[数据库]查询新增员工权限信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询新增员工权限信息失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_EmployeePurviewInfo stEmployeePurviewInfo;
				varFieldVal = recPtr->GetCollect("EmployeePurviewID");
				stEmployeePurviewInfo.strEmployeePurviewId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				stEmployeePurviewInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PurviewInfoID");
				stEmployeePurviewInfo.strPurviewInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				stEmployeePurviewInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				stEmployeePurviewInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				stEmployeePurviewInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				BOOL bHasEmployeePvw = FALSE;
				if (vecEmployeePurviewInfo.empty())
				{
					vecEmployeePurviewInfo.push_back(stEmployeePurviewInfo);
				}
				else 
				{
					for each(auto iter in vecEmployeePurviewInfo)
					{
						if (iter.strEmployeeId == stEmployeePurviewInfo.strEmployeeId && iter.strPurviewInfoId == stEmployeePurviewInfo.strPurviewInfoId)
						{
							//ManageEmployeePurviewInfo(DBO_DEL, stEmployeePurviewInfo);
							bHasEmployeePvw = TRUE;
							break;
						}
					}
					if (bHasEmployeePvw == FALSE)
					{
						vecEmployeePurviewInfo.push_back(stEmployeePurviewInfo);
					}

				}
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

//业务文件信息管理
QueryResultType XhBFISDBOperationImp::ManageBusinessFileInfo(IN DBOperType enOperType, IN OUT ST_BusinessFileInfo& sBusinessFileInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	switch(enOperType)
	{
	case DBO_QUERY:
		return QueryBusinessFileInfoByID(sBusinessFileInfo,false);
	case DBO_ADD:
		{
#if USE_BFIS_ASSERT
		    BFIS_ASSERT_STDSTRING(sBusinessFileInfo.strRecordId,       "增加业务文件信息失败");
		    BFIS_ASSERT_STDSTRING(sBusinessFileInfo.strBusinessInfoId, "增加业务文件信息失败");
		    BFIS_ASSERT_STDSTRING(sBusinessFileInfo.strRecordBegin,    "增加业务文件信息失败");
		    BFIS_ASSERT_STDSTRING(sBusinessFileInfo.strRecordEnd,      "增加业务文件信息失败");
#else
			if(sBusinessFileInfo.strRecordId == _T("") || sBusinessFileInfo.strBusinessInfoId == _T("") || 
				sBusinessFileInfo.strRecordBegin == _T("") || sBusinessFileInfo.strRecordEnd == _T("") )
			{
				TTRACE("[数据库]传入业务文件信息:RecordId:%s,BusinessInfoId:%s,RecordBegin:%s,RecordEnd:%s \r\n",
					sBusinessFileInfo.strRecordId.c_str(),sBusinessFileInfo.strBusinessInfoId.c_str(),
					sBusinessFileInfo.strRecordBegin.c_str(),sBusinessFileInfo.strRecordEnd.c_str());
				DISPLAY_LOG("数据库","添加业务文件信息失败","传入GUID或业务GUID或录像开始时间或录像结束时间为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_businessfileinfo_insert(\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",%d)",
				sBusinessFileInfo.strRecordId.c_str(),sBusinessFileInfo.strBusinessInfoId.c_str(),sBusinessFileInfo.nType,
				sBusinessFileInfo.strFileId.c_str(),sBusinessFileInfo.strRecordBegin.c_str(),sBusinessFileInfo.strRecordEnd.c_str(),
				sBusinessFileInfo.nExtendedInfo,sBusinessFileInfo.strExtendedInfo1.c_str(),sBusinessFileInfo.strExtendedInfo2.c_str()
				,sBusinessFileInfo.nMigrated,sBusinessFileInfo);
		}
		break;
	case DBO_UPDATE:
		{
#if USE_BFIS_ASSERT
		    BFIS_ASSERT_STDSTRING(sBusinessFileInfo.strRecordId,       "更新业务文件信息失败");
		    BFIS_ASSERT_STDSTRING(sBusinessFileInfo.strBusinessInfoId, "更新业务文件信息失败");
		    BFIS_ASSERT_STDSTRING(sBusinessFileInfo.strRecordBegin,    "更新业务文件信息失败");
		    BFIS_ASSERT_STDSTRING(sBusinessFileInfo.strRecordEnd,      "更新业务文件信息失败");
#else
			if(sBusinessFileInfo.strRecordId == _T("") || sBusinessFileInfo.strBusinessInfoId == _T("") || 
				sBusinessFileInfo.strRecordBegin == _T("") || sBusinessFileInfo.strRecordEnd == _T("") )
			{
				TTRACE("[数据库]传入业务文件信息:RecordId:%s,BusinessInfoId:%s,RecordBegin:%s,RecordEnd:%s \r\n",
					sBusinessFileInfo.strRecordId.c_str(),sBusinessFileInfo.strBusinessInfoId.c_str(),
					sBusinessFileInfo.strRecordBegin.c_str(),sBusinessFileInfo.strRecordEnd.c_str());
				DISPLAY_LOG("数据库","更新业务文件信息失败","传入GUID或业务GUID或录像开始时间或录像结束时间为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_businessfileinfo_update(\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",%d)",
				sBusinessFileInfo.strRecordId.c_str(),sBusinessFileInfo.strBusinessInfoId.c_str(),sBusinessFileInfo.nType,
				sBusinessFileInfo.strFileId.c_str(),sBusinessFileInfo.strRecordBegin.c_str(),sBusinessFileInfo.strRecordEnd.c_str(),
				sBusinessFileInfo.nExtendedInfo,sBusinessFileInfo.strExtendedInfo1.c_str(),sBusinessFileInfo.strExtendedInfo2.c_str()
				,sBusinessFileInfo.nMigrated);
		}
		break;
	case DBO_DEL:
		{
			if(sBusinessFileInfo.strRecordId == "")
			{
				DISPLAY_LOG("数据库","删除业务文件信息失败","传入GUID为空","",0);
				return QueryFail;
			}
			if (DeleteInfoById(DataType_BusinessFileInfo,sBusinessFileInfo.strRecordId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
		}
		break;
	default:
		{
			TTRACE("[数据库]管理业务文件信息失败，未知错误%s[%d] \r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
	}

	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理业务文件信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","管理业务文件信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	return QuerySuccessWithoutResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::QueryBusinessFileInfoByID(IN OUT ST_BusinessFileInfo& sBusinessFileInfo,IN bool bOverlapped /*= true*/)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	if (sBusinessFileInfo.strRecordId == _T(""))
	{
		DISPLAY_LOG("数据库","通过GUID查询业务文件信息","传入GUID为空","",0);
		return QueryFail;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_businessfileinfo_selectbyid(\"%s\")");
	strSQL.Format(strMsg,sBusinessFileInfo.strRecordId.c_str());
	TTRACE("[数据库]通过GUID查询业务文件信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过GUID查询业务文件信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			if (bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("BusinessInfoId");
				sBusinessFileInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Type");
				sBusinessFileInfo.nType = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("FileId");
				sBusinessFileInfo.strFileId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RecordBegin");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sBusinessFileInfo.strRecordBegin = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("RecordEnd");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sBusinessFileInfo.strRecordEnd = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sBusinessFileInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sBusinessFileInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sBusinessFileInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Migrated");
				sBusinessFileInfo.nMigrated = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
ISOC_BOOL XhBFISDBOperationImp::QueryDiffBusinessFileInfo(IN int nAll,IN OUT vector<ST_BusinessFileInfo>& vecBusinessFileInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
	strSQL.Format(strMsg,_T("businessfileinfo"),nAll);
	TTRACE("[数据库]查询新增业务文件信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询新增业务文件信息","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_BusinessFileInfo sBusinessFileInfo;
				varFieldVal = recPtr->GetCollect("RecordId");
				sBusinessFileInfo.strRecordId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BusinessInfoId");
				sBusinessFileInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Type");
				sBusinessFileInfo.nType = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("FileId");
				sBusinessFileInfo.strFileId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RecordBegin");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sBusinessFileInfo.strRecordBegin = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("RecordEnd");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sBusinessFileInfo.strRecordEnd = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sBusinessFileInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sBusinessFileInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sBusinessFileInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Migrated");
				sBusinessFileInfo.nMigrated = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
				vecBusinessFileInfo.push_back(sBusinessFileInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

//业务关联信息管理
QueryResultType XhBFISDBOperationImp::ManageBusinessRelationInfo(IN DBOperType enOperType,IN OUT ST_BusinessRelateInfo& sBusinessRelationInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	switch(enOperType)
	{
	case DBO_QUERY:
		return QueryBusinessRelationInfoByID(sBusinessRelationInfo,false);
	case DBO_ADD:
		{
#if USE_BFIS_ASSERT
		    BFIS_ASSERT_STDSTRING(sBusinessRelationInfo.strBusinessRelateInfoId, "增加业务关联信息失败");
		    BFIS_ASSERT_STDSTRING(sBusinessRelationInfo.strBusinessInfoId,       "增加业务关联信息失败");
#else
			if(sBusinessRelationInfo.strBusinessRelateInfoId == _T("") || sBusinessRelationInfo.strBusinessInfoId == _T(""))
			{
				TTRACE("[数据库]传入业务关联信息:BusinessRelateInfoId:%s,BusinessInfoId:%s \r\n",
					sBusinessRelationInfo.strBusinessRelateInfoId.c_str(),sBusinessRelationInfo.strBusinessInfoId.c_str());
				DISPLAY_LOG("数据库","添加业务关联信息失败","传入GUID或业务GUID为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_businessrelateinfo_insert(\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\")",
				sBusinessRelationInfo.strBusinessRelateInfoId.c_str(),sBusinessRelationInfo.strBusinessInfoId.c_str(),
				sBusinessRelationInfo.nRelateType,sBusinessRelationInfo.strRelate1.c_str(),sBusinessRelationInfo.strRelate2.c_str(),
				sBusinessRelationInfo.strRelate3.c_str());
		}
		break;
	case DBO_UPDATE:
		{
#if USE_BFIS_ASSERT
		    BFIS_ASSERT_STDSTRING(sBusinessRelationInfo.strBusinessRelateInfoId, "更新业务关联信息失败");
		    BFIS_ASSERT_STDSTRING(sBusinessRelationInfo.strBusinessInfoId,       "更新业务关联信息失败");
#else
			if(sBusinessRelationInfo.strBusinessRelateInfoId == _T("") || sBusinessRelationInfo.strBusinessInfoId == _T(""))
			{
				TTRACE("[数据库]传入业务关联信息:BusinessRelateInfoId:%s,BusinessInfoId:%s \r\n",
					sBusinessRelationInfo.strBusinessRelateInfoId.c_str(),sBusinessRelationInfo.strBusinessInfoId.c_str());
				DISPLAY_LOG("数据库","更新业务关联信息失败","传入GUID或业务GUID为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_businessrelateinfo_update(\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\")",
				sBusinessRelationInfo.strBusinessRelateInfoId.c_str(),sBusinessRelationInfo.strBusinessInfoId.c_str(),
				sBusinessRelationInfo.nRelateType,sBusinessRelationInfo.strRelate1.c_str(),sBusinessRelationInfo.strRelate2.c_str(),
				sBusinessRelationInfo.strRelate3.c_str());
		}
		break;
	case DBO_DEL:
		{
			if(sBusinessRelationInfo.strBusinessRelateInfoId == "")
			{
				DISPLAY_LOG("数据库","删除业务关联信息失败","传入GUID为空","",0);
				return QueryFail;
			}
			if (DeleteInfoById(DataType_BusinessRelationInfo,sBusinessRelationInfo.strBusinessRelateInfoId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
		}
		break;
	default:
		{
			TTRACE("[数据库]管理业务信息失败，未知错误%s[%d] \r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
	}


	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理业务关联信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","管理业务关联信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	return QuerySuccessWithoutResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::QueryBusinessRelationInfoByID(IN OUT ST_BusinessRelateInfo& sBusinessRelationInfo,IN bool bOverlapped /*= true*/)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	if (sBusinessRelationInfo.strBusinessRelateInfoId == _T(""))
	{
		DISPLAY_LOG("数据库","通过GUID查询业务关联信息失败","传入GUID为空","",0);
		return QueryFail;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_businessrelateinfo_selectbyid(\"%s\")");
	strSQL.Format(strMsg,sBusinessRelationInfo.strBusinessRelateInfoId.c_str());
	TTRACE("[数据库]通过GUID查询业务关联信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过GUID查询业务关联信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			if (bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("BusinessInfoId");
				sBusinessRelationInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RelateType");
				sBusinessRelationInfo.nRelateType = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Relate1");
				sBusinessRelationInfo.strRelate1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Relate2");
				sBusinessRelationInfo.strRelate2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Relate3");
				sBusinessRelationInfo.strRelate3 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
ISOC_BOOL XhBFISDBOperationImp::QueryDiffBusinessRelationInfo(IN int nAll,IN OUT vector<ST_BusinessRelateInfo>& vecBusinessRelationInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
	strSQL.Format(strMsg,_T("businessrelateinfo"),nAll);
	TTRACE("[数据库]查询新增业务关联信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询新增业务关联信息失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_BusinessRelateInfo sBusinessRelationInfo;
				varFieldVal = recPtr->GetCollect("BusinessRelateInfoId");
				sBusinessRelationInfo.strBusinessRelateInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BusinessInfoId");
				sBusinessRelationInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RelateType");
				sBusinessRelationInfo.nRelateType = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Relate1");
				sBusinessRelationInfo.strRelate1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Relate2");
				sBusinessRelationInfo.strRelate2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Relate3");
				sBusinessRelationInfo.strRelate3 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				vecBusinessRelationInfo.push_back(sBusinessRelationInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

//用户权限信息管理
QueryResultType XhBFISDBOperationImp::ManagePurviewInfo(IN DBOperType enOperType, IN OUT ST_PurviewInfo& sPurviewInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	switch(enOperType)
	{
	case DBO_QUERY:
		return QueryPurviewInfoByID(sPurviewInfo,false);
	case DBO_ADD:
		{
#if USE_BFIS_ASSERT
		    BFIS_ASSERT_STDSTRING(sPurviewInfo.strPurviewInfoId, "增加权限信息失败");
		    BFIS_ASSERT_STDSTRING(sPurviewInfo.strParentPurviewId, "增加权限信息失败");
		    BFIS_ASSERT_STDSTRING(sPurviewInfo.strPurviewCode, "增加权限信息失败");
#else
			if(sPurviewInfo.strPurviewInfoId == _T("") || sPurviewInfo.strParentPurviewId == _T("") || 
				sPurviewInfo.strPurviewCode == _T(""))
			{
				DISPLAY_LOG("数据库","添加权限信息失败","传入GUID或父权限GUID或权限编码为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_purviewinfo_insert(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",sPurviewInfo.strPurviewInfoId.c_str()
				,sPurviewInfo.strParentPurviewId.c_str(),sPurviewInfo.strPurviewCode.c_str(),sPurviewInfo.strDescription.c_str()
				,sPurviewInfo.strExtendedInfo1.c_str(),sPurviewInfo.strExtendedInfo2.c_str());
		}
		break;
	case DBO_UPDATE:
		{
#if USE_BFIS_ASSERT
		    BFIS_ASSERT_STDSTRING(sPurviewInfo.strPurviewInfoId, "更新权限信息失败");
		    BFIS_ASSERT_STDSTRING(sPurviewInfo.strParentPurviewId, "更新权限信息失败");
		    BFIS_ASSERT_STDSTRING(sPurviewInfo.strPurviewCode, "更新权限信息失败");
#else
			if(sPurviewInfo.strPurviewInfoId == _T("") || sPurviewInfo.strParentPurviewId == _T("") || 
				sPurviewInfo.strPurviewCode == _T(""))
			{
				DISPLAY_LOG("数据库","更新权限信息失败","传入GUID或父权限GUID或权限编码为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_purviewinfo_update(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",sPurviewInfo.strPurviewInfoId.c_str()
				,sPurviewInfo.strParentPurviewId.c_str(),sPurviewInfo.strPurviewCode.c_str(),sPurviewInfo.strDescription.c_str(),
				sPurviewInfo.strExtendedInfo1.c_str(),sPurviewInfo.strExtendedInfo2.c_str());
		}
		break;
	case DBO_DEL:
		{
			if(sPurviewInfo.strPurviewInfoId == "")
			{
				DISPLAY_LOG("数据库","更新权限信息失败","传入GUID为空","",0);
				return QueryFail;
			}
			if (DeleteInfoById(DataType_PurviewInfo,sPurviewInfo.strPurviewInfoId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
		}
		break;
	default:
		{
			TTRACE("[数据库]管理权限信息失败，未知错误%s[%d] \r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
	}


	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理权限信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","管理权限信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	return QuerySuccessWithoutResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::QueryPurviewInfoByID(IN OUT ST_PurviewInfo& sPurviewInfo,IN bool bOverlapped /*= true*/)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	if (sPurviewInfo.strPurviewInfoId == _T(""))
	{
		DISPLAY_LOG("数据库","通过GUID查询权限信息失败","传入GUID为空","",0);
		return QueryFail;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_purviewinfo_selectbyid(\"%s\")");
	strSQL.Format(strMsg,sPurviewInfo.strPurviewInfoId.c_str());
	TTRACE("[数据库]通过GUID查询权限信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过GUID查询权限信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			if (bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("ParentPurviewID");
				sPurviewInfo.strParentPurviewId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PurviewCode");
				sPurviewInfo.strPurviewCode = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Description");
				sPurviewInfo.strDescription = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sPurviewInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sPurviewInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
ISOC_BOOL XhBFISDBOperationImp::QueryDiffPurviewInfo(IN int nAll,IN OUT vector<ST_PurviewInfo>& vecPurviewInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
	strSQL.Format(strMsg,_T("purviewinfo"),nAll);
	TTRACE("[数据库]查询新增权限信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询新增权限信息失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_PurviewInfo sPurviewInfo;
				varFieldVal = recPtr->GetCollect("PurviewInfoID");
				sPurviewInfo.strPurviewInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ParentPurviewID");
				sPurviewInfo.strParentPurviewId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PurviewCode");
				sPurviewInfo.strPurviewCode = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Description");
				sPurviewInfo.strDescription = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sPurviewInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sPurviewInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				vecPurviewInfo.push_back(sPurviewInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

//角色权限信息管理
QueryResultType XhBFISDBOperationImp::ManageRolePurviewInfo(IN DBOperType enOperType, IN OUT ST_RolePurviewInfo& sRolePurviewInfo)
{
	STRY;
	CString strSQL = _T("");
	switch(enOperType)
	{
	case DBO_QUERY:
		return QueryRolePurviewInfoByID(sRolePurviewInfo,false);
	case DBO_ADD:
		{
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(sRolePurviewInfo.strRoleInfoPurviewId, "增加角色权限信息失败");
        BFIS_ASSERT_STDSTRING(sRolePurviewInfo.strRoleId,            "增加角色权限信息失败");
        BFIS_ASSERT_STDSTRING(sRolePurviewInfo.strPruviewInfoId,     "增加角色权限信息失败");
#else
			if(sRolePurviewInfo.strRoleInfoPurviewId == _T("") || sRolePurviewInfo.strRoleId == _T("") || 
				sRolePurviewInfo.strPruviewInfoId == _T(""))
			{
				TTRACE("[数据库]角色权限信息:RoleInfoPurviewId:%s,RoleId:%s,PruviewInfoId:%s \r\n",
					sRolePurviewInfo.strRoleInfoPurviewId.c_str(),sRolePurviewInfo.strRoleId.c_str(),
					sRolePurviewInfo.strPruviewInfoId.c_str());
				DISPLAY_LOG("数据库","增加角色权限信息失败","传入GUID或角色GUID或权限GUID为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_roleinfopurview_insert(\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")",
				sRolePurviewInfo.strRoleInfoPurviewId.c_str(),sRolePurviewInfo.strRoleId.c_str(),
				sRolePurviewInfo.strPruviewInfoId.c_str(),sRolePurviewInfo.nExtendedInfo,
				sRolePurviewInfo.strExtendedInfo1.c_str(),sRolePurviewInfo.strExtendedInfo2.c_str());
		}
		break;
	case DBO_UPDATE:
		{
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(sRolePurviewInfo.strRoleInfoPurviewId, "更新角色权限信息失败");
        BFIS_ASSERT_STDSTRING(sRolePurviewInfo.strRoleId,            "更新角色权限信息失败");
        BFIS_ASSERT_STDSTRING(sRolePurviewInfo.strPruviewInfoId,     "更新角色权限信息失败");
#else
			if(sRolePurviewInfo.strRoleInfoPurviewId == _T("") || sRolePurviewInfo.strRoleId == _T("") || 
				sRolePurviewInfo.strPruviewInfoId == _T(""))
			{
				TTRACE("[数据库]角色权限信息:RoleInfoPurviewId:%s,RoleId:%s,PruviewInfoId:%s \r\n",
					sRolePurviewInfo.strRoleInfoPurviewId.c_str(),sRolePurviewInfo.strRoleId.c_str(),
					sRolePurviewInfo.strPruviewInfoId.c_str());
				DISPLAY_LOG("数据库","更新角色权限信息失败","传入GUID或角色GUID或权限GUID为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_roleinfopurview_update(\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")",
				sRolePurviewInfo.strRoleInfoPurviewId.c_str(),sRolePurviewInfo.strRoleId.c_str(),
				sRolePurviewInfo.strPruviewInfoId.c_str(),sRolePurviewInfo.nExtendedInfo,
				sRolePurviewInfo.strExtendedInfo1.c_str(),sRolePurviewInfo.strExtendedInfo2.c_str());
		}
		break;
	case DBO_DEL:
		{
 			if(sRolePurviewInfo.strRoleInfoPurviewId == "")
 			{
 				DISPLAY_LOG("数据库模块","角色权限信息Id为空,删除失败","","",0);
 				return QueryFail;
 			}
 			if (DeleteInfoById(DataType_RolePurviewInfo,sRolePurviewInfo.strRoleInfoPurviewId))
 			{
 				return QuerySuccessWithoutResult;
 			}
 			else
 			{
 				return QueryFail;
 			}
			/*if(sRolePurviewInfo.strRoleId == "")
			{
				DISPLAY_LOG("数据库","删除角色权限信息失败","传入角色GUID为空","",0);
				return QueryFail;
			}
			strSQL.Format("delete from roleinfopurview where RoleId = \"%s\"",sRolePurviewInfo.strRoleId.c_str());*/
		}
		break;
	default:
		{
			TTRACE("'数据库]管理角色权限信息失败，未知错误%s[%d] \r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
	}

	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理角色权限信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","管理角色权限信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	return QuerySuccessWithoutResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::QueryRolePurviewInfoByID(IN OUT ST_RolePurviewInfo& sRolePurviewInfo,IN bool bOverlapped /*= true*/)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	if (sRolePurviewInfo.strRoleInfoPurviewId == _T(""))
	{
		DISPLAY_LOG("数据库","通过GUID查询角色权限失败","传入GUID为空","",0);
		return QueryFail;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_roleinfopurview_selectbyid(\"%s\")");
	strSQL.Format(strMsg,sRolePurviewInfo.strRoleInfoPurviewId.c_str());
	TTRACE("[数据库]通过GUID查询角色权限信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过GUID查询角色权限信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			if (bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("RoleId");
				sRolePurviewInfo.strRoleId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PurviewInfoID");
				sRolePurviewInfo.strPruviewInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sRolePurviewInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sRolePurviewInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sRolePurviewInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
ISOC_BOOL XhBFISDBOperationImp::QueryDiffRolePurviewInfo(IN int nAll,IN OUT vector<ST_RolePurviewInfo>& vecRolePurviewInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
	strSQL.Format(strMsg,_T("roleinfopurview"),nAll);
	TTRACE("[数据库]查询新增角色权限信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询新增角色权限信息失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_RolePurviewInfo sRolePurviewInfo;
				varFieldVal = recPtr->GetCollect("RoleInfoPurviewID");
				sRolePurviewInfo.strRoleInfoPurviewId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RoleId");
				sRolePurviewInfo.strRoleId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PurviewInfoID");
				sRolePurviewInfo.strPruviewInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sRolePurviewInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sRolePurviewInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sRolePurviewInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				vecRolePurviewInfo.push_back(sRolePurviewInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

QueryResultType XhBFISDBOperationImp::ManageUserMapInfo(IN DBOperType enOperType, IN OUT ST_UserMapInfo& sUserMapInfo)
{
	STRY;
	CString strSQL = _T("");
	switch(enOperType)
	{
	case DBO_QUERY:
		return QueryUserMapInfoByID(sUserMapInfo,false);
	case DBO_ADD:
		{
#if USE_BFIS_ASSERT
		    BFIS_ASSERT_STDSTRING(sUserMapInfo.strUserMapInfoId, "增加用户关系映射信息失败");
		    BFIS_ASSERT_STDSTRING(sUserMapInfo.strEmployeeId,    "增加用户关系映射信息失败");
		    BFIS_ASSERT_STDSTRING(sUserMapInfo.strSocUsername,   "增加用户关系映射信息失败");
		    BFIS_ASSERT_STDSTRING(sUserMapInfo.strSocPassword,   "增加用户关系映射信息失败");
#else
			if(sUserMapInfo.strUserMapInfoId == _T("") || sUserMapInfo.strEmployeeId == _T("") || 
				sUserMapInfo.strSocUsername == _T("") || sUserMapInfo.strSocPassword == _T(""))
			{
				TTRACE("[数据库]传入关系映射信息:UserMapInfoId:%s,EmployeeId:%s,SocUsername:%s,SocPassword:%s \r\n",
					sUserMapInfo.strUserMapInfoId.c_str(),sUserMapInfo.strEmployeeId.c_str(),sUserMapInfo.strSocUsername.c_str(),
					sUserMapInfo.strSocPassword.c_str());
				DISPLAY_LOG("数据库","增加关系映射信息失败","传GUID或员工GUID或SOC名或SOC密码为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_uermapinfo_insert(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",sUserMapInfo.strUserMapInfoId.c_str(),
				sUserMapInfo.strEmployeeId.c_str(),sUserMapInfo.strSocUsername.c_str(),sUserMapInfo.strSocPassword.c_str(),
				sUserMapInfo.strExtendedInfo1.c_str(),sUserMapInfo.strExtendedInfo2.c_str());
		}
		break;
	case DBO_UPDATE:
		{
#if USE_BFIS_ASSERT
		    BFIS_ASSERT_STDSTRING(sUserMapInfo.strUserMapInfoId, "更新用户关系映射信息失败");
		    BFIS_ASSERT_STDSTRING(sUserMapInfo.strEmployeeId,    "更新用户关系映射信息失败");
		    BFIS_ASSERT_STDSTRING(sUserMapInfo.strSocUsername,   "更新用户关系映射信息失败");
		    BFIS_ASSERT_STDSTRING(sUserMapInfo.strSocPassword,   "更新用户关系映射信息失败");
#else
			if(sUserMapInfo.strUserMapInfoId == _T("") || sUserMapInfo.strEmployeeId == _T("") || 
				sUserMapInfo.strSocUsername == _T("") || sUserMapInfo.strSocPassword == _T(""))
			{
				TTRACE("[数据库]传入关系映射信息:UserMapInfoId:%s,EmployeeId:%s,SocUsername:%s,SocPassword:%s \r\n",
					sUserMapInfo.strUserMapInfoId.c_str(),sUserMapInfo.strEmployeeId.c_str(),sUserMapInfo.strSocUsername.c_str(),
					sUserMapInfo.strSocPassword.c_str());
				DISPLAY_LOG("数据库","更新关系映射信息失败","传GUID或员工GUID或SOC名或SOC密码为空","",0);
				return QueryFail;
			}
#endif
			strSQL.Format("call proc_uermapinfo_update(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",sUserMapInfo.strUserMapInfoId.c_str(),
				sUserMapInfo.strEmployeeId.c_str(),sUserMapInfo.strSocUsername.c_str(),sUserMapInfo.strSocPassword.c_str(),sUserMapInfo.strExtendedInfo1.c_str(),
				sUserMapInfo.strExtendedInfo2.c_str());
		}
		break;
	case DBO_DEL:
		{
			if(sUserMapInfo.strUserMapInfoId == "")
			{
				DISPLAY_LOG("数据库","删除关系映射失败","传入GUID为空","",0);
				return QueryFail;
			}
			if (DeleteInfoById(DataType_UserMapInfo,sUserMapInfo.strUserMapInfoId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
		}
		break;
	default:
		{
			TTRACE("[数据库]管理关系映射失败，未知错误%s[%d] \r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
	}

	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	TTRACE("[数据库]管理用户关系映射信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","管理用户关系映射信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	return QuerySuccessWithoutResult;
	SCATCH;
	return QueryFail;
}

QueryResultType XhBFISDBOperationImp::QueryUserMapInfoByID(IN OUT ST_UserMapInfo& sUserMapInfo,IN bool bOverlapped /*= true*/)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	if (sUserMapInfo.strUserMapInfoId == _T(""))
	{
		DISPLAY_LOG("数据库","通过GUID查询关系映射信息失败","传入GUID为空","",0);
		return QueryFail;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_uermapinfo_selectbyid(\"%s\")");
	strSQL.Format(strMsg,sUserMapInfo.strUserMapInfoId.c_str());
	TTRACE("[数据库]通过GUID查询用户关系映射信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过GUID查询用户关系映射信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			if (bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("UerMapInfoID");
				sUserMapInfo.strUserMapInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				sUserMapInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SocUserName");
				sUserMapInfo.strSocUsername = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SocUserPassWord");
				sUserMapInfo.strSocPassword = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sUserMapInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sUserMapInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

ISOC_BOOL XhBFISDBOperationImp::QueryDiffUserMapInfo(IN int nAll,IN OUT vector<ST_UserMapInfo>& vecUserMapInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syngetdiffrowsintable(\"%s\",%d)");
	strSQL.Format(strMsg,_T("uermapinfo"),nAll);
	TTRACE("[数据库]查询新增用户关联信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询新增用户关联信息失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_UserMapInfo stUserMapInfo;
				varFieldVal = recPtr->GetCollect("UerMapInfoID");
				stUserMapInfo.strUserMapInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				stUserMapInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SocUserName");
				stUserMapInfo.strSocUsername = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SocUserPassWord");
				stUserMapInfo.strSocPassword = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				stUserMapInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				stUserMapInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				vecUserMapInfo.push_back(stUserMapInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

// void XhBFISDBOperationImp::GuidProducer(CString& strGuid)
// {
// 	STRY;
// 	GUID gGuid;
// 	if (S_OK == ::CoCreateGuid(&gGuid))
// 	{
// 		strGuid.Format("{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",gGuid.Data1,gGuid.Data2,gGuid.Data3,gGuid.Data4[0],
// 			gGuid.Data4[1],gGuid.Data4[2],gGuid.Data4[3],gGuid.Data4[4],gGuid.Data4[5],gGuid.Data4[6],gGuid.Data4[7]);
// 	}
// 	SCATCH;
// }

// BOOL XhBFISDBOperationImp::ReadLastSyncTime(CString& strTime)
// {
// 	STRY;
// 	CString strPath = GetWorkingDirectory();
// 	strPath += _T("\\Config\\iBFIS.ClientInfoSyncTime.Config.ini");
// 	CString strAppName = _T("LastSyncTime");
// 	CString strKeyName = _T("Time");
// 	TCHAR tchBuf[500] = { 0 };
// 	if(!GetPrivateProfileString((LPCTSTR)strAppName,(LPCTSTR)strKeyName,_T(""),tchBuf,500,(LPCTSTR)strPath))
// 	{
// 		return FALSE;
// 	}
// 	strTime.Format("%s",tchBuf);
// 	return TRUE;
// 	SCATCH;
// 	return FALSE;
// }

// BOOL XhBFISDBOperationImp::RestoreLastSyncTime(CString strTime)
// {
// 	STRY;
// 	CString strPath = GetWorkingDirectory();
// 	strPath += _T("\\Config\\iBFIS.ClientInfoSyncTime.Config.ini");
// 
// 	CString strAppName = _T("LastSyncTime");
// 	CString strKeyName = _T("Guid");
// 	CString strTemp = _T("");
// 	GuidProducer(strTemp);
// 	if (strTemp != _T("") && strTime != _T(""))
// 	{
// 		if(WritePrivateProfileString((LPCTSTR)strAppName,(LPCTSTR)strKeyName,(LPCTSTR)strTemp,(LPCTSTR)strPath))
// 		{
// 			strKeyName = _T("Time");
// 			if (WritePrivateProfileString((LPCTSTR)strAppName,(LPCTSTR)strKeyName,(LPCTSTR)strTime,(LPCTSTR)strPath))
// 			{
// 				return TRUE;
// 			}
// 		}
// 	}
// 	return FALSE;
// 	SCATCH
// 	return FALSE;
// }

ISOC_BOOL XhBFISDBOperationImp::QueryClientInfoLastSyncTime(CString& strTime,DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	iSOC_AutoInitCOM autoInitCom;
	_RecordsetPtr recPtr;
	_variant_t varRecordsetAffected;
	_variant_t varFieldVal;
	int nRetAffected = 0;
	SimpleConnection conn(this);
	CString strSQL = _T("call proc_clientinfosynctime_select()");
	try
	{
		recPtr = conn.m_pCon->Execute((_bstr_t)strSQL,&varRecordsetAffected,adCmdText);
		nRetAffected = varRecordsetAffected.intVal;
		if (nRetAffected > 0 && !recPtr->adoEOF)
		{
			varFieldVal = recPtr->GetCollect("max(RowVersion)");
			if(varFieldVal.vt != VT_NULL)
			{
				DATE dt = varFieldVal.date;  
				COleDateTime da = COleDateTime(dt);  
				strTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));
				//RestoreLastSyncTime(strTime);
			}
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%s",__FUNCTION__,__LINE__,e.ErrorMessage());
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

BOOL XhBFISDBOperationImp::ExecuteSQL(_bstr_t strSQL,_RecordsetPtr& CRest,int& nRestAff)
{
    //初始化COM会自动释放
    iSOC_AutoInitCOM autoInitCom;
    STRY;

    _ConnectionPtr& pConn = GetConnection();
    _variant_t sRecordsetAffected;
    try
    {
        CRest = pConn->Execute(strSQL,&sRecordsetAffected,adCmdText);
        nRestAff = sRecordsetAffected.intVal;
    }
    catch (_com_error e)
    {
		char szError[256] = {0};
        sprintf(szError,"%s:%d %s\r\n",_T("[数据库]"),__LINE__,(LPTSTR)(e.Description()));
        DISPLAY_LOG("数据库",szError,"","",0);
        m_bIsDbConnection = FALSE;
    }
    return TRUE;
    SCATCH;
    return FALSE;
}

BOOL XhBFISDBOperationImp::ReconectByConnection(_ConnectionPtr& pcon)
{
    iSOC_AutoInitCOM autoInitCom;
    STRY;
    try
    {
        if (NULL == pcon || pcon->State != adStateClosed)
        {
            pcon->Close();
            HRESULT hr = pcon.CreateInstance(__uuidof(Connection));
            if (FAILED(hr))
                return false;
        }	
        char szConnect[100] = {0};
        sprintf(szConnect,"Driver={MySQL ODBC 5.1 Driver};Connect Timeout=10;Server=%s;database=%s",
			m_strIp.c_str(),m_strDataBaseName.c_str());
        HRESULT hr = pcon->Open(_bstr_t(szConnect), (_bstr_t)(m_strUID.c_str()), (_bstr_t)(m_strPWD.c_str()), adModeUnknown);

        //       HRESULT hr = pcon->Open(m_strIp.c_str(), strUserName.c_str(), strPsw.c_str(), adModeUnknown);
        TTRACE("%s[TID:%u]连接到数据库：%s\r\n", _T("[数据库]"), ::GetCurrentThreadId(), szConnect); 
        return SUCCEEDED(hr);

    }
    catch (_com_error& e)
    {
        TTRACE("%s[TID:%u]连接到数据库失败：%s\r\n"  , _T("[数据库]"), ::GetCurrentThreadId(),(LPTSTR)(e.Description()));
        return false;	
    }
    SCATCH;
    TTRACE("%[TIDs:%u]连接到数据库失败：未知错误!\r\n", _T("[数据库]"), ::GetCurrentThreadId());
    return FALSE;
}

BOOL XhBFISDBOperationImp::ExecuteSQLSafe( _ConnectionPtr& pcon, _bstr_t strSQL,_RecordsetPtr& CRest,int& iRestAff )
{
    iSOC_AutoInitCOM autoInitCom;
    STRY;

    _variant_t RecordsAffected;
    BOOL bSuccess = FALSE;
    try
    {
        CRest = pcon->Execute(strSQL,&RecordsAffected,adCmdText);		
        iRestAff = RecordsAffected.intVal;	
        bSuccess = TRUE;
    }
    catch (_com_error e)
    {
        TTRACE("%s:%d %s\r\n",_T("[数据库]"),__LINE__,(LPTSTR)(e.Description()));
		TTRACE("失败的SQL：%s\r\n",(LPSTR)strSQL);
        DISPLAY_LOG(_T("数据库"),_T("执行数据库查询失败"), (LPTSTR)e.Description(),_T(""),0);
        bSuccess = FALSE;
    }

    if (!bSuccess)  //尝试重连一次
    {
        STRY;
        try
        {
            if (ReconectByConnection(pcon))
            {
                CRest = pcon->Execute(strSQL,&RecordsAffected,adCmdText);		
                iRestAff = RecordsAffected.intVal;	
                DISPLAY_LOG(_T("数据库"),_T("数据库重连成功"), _T(""),_T(""),1);
                bSuccess = TRUE;
            }
        }
        catch (_com_error& e)
        {
            TTRACE("%s:%d 重连后失败：%s\r\n",_T("[数据库]"),__LINE__,(LPTSTR)(e.Description()));
            DISPLAY_LOG(_T("数据库"),_T("重连数据库失败"), (LPTSTR)e.Description(),_T(""),0);
            bSuccess = FALSE;
        }
        SCATCH;
    }
    return bSuccess;

    SCATCH;
    return FALSE;
}

_ConnectionPtr& XhBFISDBOperationImp::GetConnection()
{
    STRY;
    Poco::FastMutex::ScopedLock myConnLock(m_csDBLock);
reloop:
    for (int i = 0 ; i < m_nConnectCount ; i ++)
    {
        try
        {
            if (m_pConInfo[i].bIsFree)
            {
                m_pConInfo[i].bIsFree = false;
                return m_pConInfo[i].pDBConnection;
            }
        }
        catch(_com_error e)
        {
			char szTemp[256] = {0};
            sprintf(szTemp,_T("%s:%d %s\r\n"),_T("[数据库]"),__LINE__,(LPTSTR)(e.Description()));
            DISPLAY_LOG("数据库",szTemp ,"","",0);
            m_bIsDbConnection = FALSE;
        }
    }
    Sleep(200);
    goto reloop;
    SCATCH;
    static _ConnectionPtr con;
    return con;
}

int XhBFISDBOperationImp::FinishedUseConnection( ST_DBConnectionInfo* pDBCon )
{
    STRY;
    for(int x=0;x<m_nConnectCount;x++)
    {
        if(&m_pConInfo[x] == pDBCon)
        {
            m_pConInfo[x].bIsFree = true;
            return 1;
        }
    }
    TTRACE("%s[%d]:发现未被释放的连接%p\r\n",_T("[数据库]"),__LINE__,pDBCon);
    return -1;
    SCATCH;
    return -1;
}

ST_DBConnectionInfo* XhBFISDBOperationImp::GetDBConnection2()
{
    STRY;
    Poco::FastMutex::ScopedLock lockConnection(m_csDBLock);
reLoop:
    for(int x=0;x<m_nConnectCount;x++)
    {
        try
        {
            if(m_pConInfo[x].bIsFree)
            {
                m_pConInfo[x].bIsFree = false;
                return &m_pConInfo[x];
            }
        }
        catch (_com_error e)
        {
            TTRACE("%s:%d %s\r\n",_T("[数据库]"),__LINE__,(LPTSTR)(e.Description()));
            m_bIsDbConnection = FALSE;
        }
    }
    Sleep(200);
    goto reLoop;

    SCATCH;
    return NULL;
}

ISOC_INT XhBFISDBOperationImp::QueryBranchInfo(vector<ST_BranchInfo>& vecInfos, DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	return QueryDiffBranchInfo((int)dwReserved,vecInfos);
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryClientInfo(vector<ST_ClientInfo>& vecInfos,const string& strTime/* = ""*/,DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	return QueryDiffClientInfo((int)dwReserved,vecInfos,strTime);
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryRoleInfo(vector<ST_RoleInfo>& vecInfos, DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	return QueryDiffRoleInfo((int)dwReserved,vecInfos);
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryProduceInfo(vector<ST_ProduceInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	return QueryDiffProduceInfo((int)dwReserved,vecInfos);
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryBusinessInfo(vector<ST_BusinessInfo>& vecInfos, DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	return QueryDiffBusinessInfo((int)dwReserved,vecInfos);
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryBusinessFileInfo(vector<ST_BusinessFileInfo>& vecInfos, DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	return QueryDiffBusinessFileInfo((int)dwReserved,vecInfos);
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecInfos, DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	return QueryDiffBusinessRelationInfo((int)dwReserved,vecInfos);
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryEmployeeInfo(vector<ST_EmployeeInfo>& vecInfos, DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	return QueryDiffEmployeeInfo((int)dwReserved,vecInfos);
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (dwReserved == 100)
	{
		return QueryEmployeePurviewInfoAll(vecInfos);
	}
	else
	{
		return QueryDiffEmployeePurviewInfo((int)dwReserved, vecInfos);
	}
	
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryPurviewInfo(vector<ST_PurviewInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	return QueryDiffPurviewInfo((int)dwReserved,vecInfos);
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryRolePurviewInfo(vector<ST_RolePurviewInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	return QueryDiffRolePurviewInfo((int)dwReserved,vecInfos);
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryUserMapInfo(vector<ST_UserMapInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	return QueryDiffUserMapInfo((int)dwReserved,vecInfos);
	SCATCH;
	return -1;
}

ISOC_BOOL XhBFISDBOperationImp::GetIsCredenitialExisted(IN string strCredenitial)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_iscredenitialexist(\"%s\")");
	strSQL.Format(strMsg,strCredenitial.c_str());
	TTRACE("[数据库]判断身份证号是否存在语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","判断身份证号是否存在","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if (nRestAff == 0 || recPtr->adoEOF)
		{
			return TRUE;
		}
		if(recPtr != NULL && recPtr->GetState() == adStateOpen)
			recPtr->Close();
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDBOperationImp::SetSyncComplete(IN SyncDataType enDataType,IN string strId)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	CString strTableName = _T("");
	switch (enDataType)
	{
	case DataType_BranceInfo:
		strTableName = _T("BranchInfo");
		break;
	case DataType_ClientInfo:
		strTableName = _T("ClientInfo");
		break;
	case DataType_RoleInfo:
		strTableName = _T("RoleInfo");
		break;
	case DataType_ProduceInfo:
		strTableName = _T("ProduceInfo");
		break;
	case DataType_BusinessInfo:
		strTableName = _T("BusInessInfo");
		break;
	case DataType_BusinessFileInfo:
		strTableName = _T("BusinessFileInfo");
		break;
	case DataType_BusinessRelationInfo:
		strTableName = _T("BusinessRelateInfo");
		break;
	case DataType_EmployeeInfo:
		strTableName = _T("EmployeeInfo");
		break;
	case DataType_PurviewInfo:
		strTableName = _T("PurviewInfo");
		break;
	case DataType_RolePurviewInfo:
		strTableName = _T("RoleInfoPurview");
		break;
	case DataType_EmployeePurviewInfo:
		strTableName = _T("EmployeePurview");
		break;
	default:
		return FALSE;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_syncomplete(\"%s\",\"%s\")");
	strSQL.Format(strMsg,strId.c_str(),strTableName);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","执行SQL语句失败","","",0);
		return FALSE;
	}
	try
	{
		if(recPtr != NULL && recPtr->GetState() == adStateOpen)
			recPtr->Close();
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDBOperationImp::DeleteInfoById(IN SyncDataType enDataType,IN string strId)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	CString strTableName = _T("");
	switch (enDataType)
	{
	case DataType_BranceInfo:
		strTableName = _T("BranchInfo");
		break;
	case DataType_ClientInfo:
		strTableName = _T("ClientInfo");
		break;
	case DataType_RoleInfo:
		strTableName = _T("RoleInfo");
		break;
	case DataType_ProduceInfo:
		strTableName = _T("ProduceInfo");
		break;
	case DataType_BusinessInfo:
		strTableName = _T("BusInessInfo");
		break;
	case DataType_BusinessFileInfo:
		strTableName = _T("BusinessFileInfo");
		break;
	case DataType_BusinessRelationInfo:
		strTableName = _T("BusinessRelateInfo");
		break;
	case DataType_EmployeeInfo:
		strTableName = _T("EmployeeInfo");
		break;
	case DataType_PurviewInfo:
		strTableName = _T("PurviewInfo");
		break;
	case DataType_RolePurviewInfo:
		strTableName = _T("RoleInfoPurview");
		break;
	case DataType_EmployeePurviewInfo:
		strTableName = _T("EmployeePurview");
		break;
	case DataType_UserMapInfo:
		strTableName = _T("uermapinfo");
		break;
	case DataType_ScriptInfo:
		strTableName = _T("ScriptInfo");
		break;
	case DataType_OperateLogInfo:
		strTableName = _T("OperateLogInfo");
		break;
	default:
		return FALSE;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_info_deletebyid(\"%s\",\"%s\")");
	strSQL.Format(strMsg,strId.c_str(),strTableName);
	TTRACE("[数据库]通过GUID删除%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过GUID删除失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(recPtr != NULL && recPtr->GetState() == adStateOpen)
			recPtr->Close();
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
QueryResultType XhBFISDBOperationImp::QueryBusinessInfoUnFinished(IN OUT vector<ST_BusinessInfo>& vecInfo)
{
    STRY;
    CString strMsg = _T("");
    CString strSQL = _T("");
    SimpleConnection conn(this);
    int				nRestAff = 0;
    _variant_t		varFieldVal;
    _RecordsetPtr	recPtr = NULL;
    strMsg = _T("call proc_businessinfo_unfinished()");
    strSQL.Format(strMsg);
    TTRACE("[数据库]通过条件查询业务信息语句:%s \r\n",strSQL);
    if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
    {       
        DISPLAY_LOG("数据库","通过条件查询业务信息失败","执行SQL语句失败","",0);
        return QueryFail;
    }
    try
    {
        bool bFlag = false;
        if(nRestAff > 0)
        {
            while(!recPtr->adoEOF)
            {
                bFlag = true;
                ST_BusinessInfo sBusinessInfo;
                if(m_BusinessMan.querySingleBusinessInfo(varFieldVal,recPtr,sBusinessInfo))
                {
                    vecInfo.push_back(sBusinessInfo);
                }
                recPtr->MoveNext();
            }
            if(recPtr != NULL && recPtr->GetState() == adStateOpen)
                recPtr->Close();
        }
        else
        {
            return QuerySuccessWithoutResult;
        }
    }
    catch(_com_error e)
    {
        TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
        return QueryFail;
    }
    return QuerySuccessWithResult;
    SCATCH;
    return QueryFail;
}
QueryResultType XhBFISDBOperationImp::QueryBusinessInfoByCondition(ST_BusinessQueryParam stInfo,IN OUT vector<ST_BusinessInfo>& vecInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_businessinfo_querybycondition(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,%d,\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\")");
	strSQL.Format(strMsg,stInfo.strBranchId.c_str(),stInfo.strEmployeeId.c_str(),stInfo.strCustomerId.c_str(),stInfo.strProduceId.c_str(),
		stInfo.strStartTime.c_str(),stInfo.strEndTime.c_str(),stInfo.nPageSize,stInfo.nPageIndex,stInfo.strSerialNumber.c_str(),stInfo.strCredenitialsType.c_str(),
        stInfo.strBusinessType.c_str(),stInfo.strCardNumber.c_str(),stInfo.nMarkerType,stInfo.strRiskLevel.c_str(),stInfo.strConditionEx.c_str(),
		stInfo.strMediumNum.c_str(),stInfo.strExtendedInfo2.c_str());
	TTRACE("[数据库]通过条件查询业务信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过条件查询业务信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		bool bFlag = false;
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				bFlag = true;
				ST_BusinessInfo sBusinessInfo;
#if 0
				varFieldVal = recPtr->GetCollect("Datetime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sBusinessInfo.strDateTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("BusInessInfoId");
				sBusinessInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BranchId");
				sBusinessInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ClientId");
				sBusinessInfo.strClientId   = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				sBusinessInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ProduceId");
				sBusinessInfo.strProduceId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SubEquipmentId");
				sBusinessInfo.strSubEquipmentId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sBusinessInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sBusinessInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sBusinessInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SubEquipmentIcmSign");
				sBusinessInfo.strSubEquipmentIcmSign = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SerialNumber");
				sBusinessInfo.strSerialNumber = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Migrated");
				sBusinessInfo.nMigrated = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
#else
				if(m_BusinessMan.querySingleBusinessInfo(varFieldVal,recPtr,sBusinessInfo))
				{
#endif
					vecInfo.push_back(sBusinessInfo);
				}
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
		{
			return QuerySuccessWithoutResult;
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

QueryResultType XhBFISDBOperationImp::QueryBusinessFileInfoByBusinessInfoId(string strInfo,IN OUT vector<ST_BusinessFileInfo>& vecInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	if (strInfo == _T(""))
	{
		DISPLAY_LOG("数据库","通过业务GUID查询业务文件信息失败","传入业务GUID为空","",0);
		return QueryFail;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_getbusinessfIleinfobybusinessinfoid(\"%s\")");
	strSQL.Format(strMsg,strInfo.c_str());
	TTRACE("[数据库]通过业务信息GUID查询业务文件信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过业务信息GUID查询业务文件信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_BusinessFileInfo sBusinessFileInfo;
				varFieldVal = recPtr->GetCollect("RecordId");
				sBusinessFileInfo.strRecordId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BusinessInfoId");
				sBusinessFileInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Type");
				sBusinessFileInfo.nType = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("FileId");
				sBusinessFileInfo.strFileId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RecordBegin");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sBusinessFileInfo.strRecordBegin = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("RecordEnd");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sBusinessFileInfo.strRecordEnd = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sBusinessFileInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sBusinessFileInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sBusinessFileInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;


				vecInfo.push_back(sBusinessFileInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

QueryResultType XhBFISDBOperationImp::QueryBusinessRelateInfoByBusinessInfoId(string strInfo,IN OUT vector<ST_BusinessRelateInfo>& vecInfo)
{
	STRY;
	CString strSQL = _T("");
	if (strInfo == _T(""))
	{
		DISPLAY_LOG("数据库","通过业务GUID查询业务关联信息失败","传入业务GUID为空","",0);
		return QueryFail;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strSQL.Format("call proc_getbusinessrelateinfobybusinessinfoid(\"%s\")",strInfo.c_str());
	TTRACE("[数据库]通过业务信息GUID查询业务关联信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过业务信息GUID查询业务关联信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_BusinessRelateInfo sBusinessRelationInfo;
				varFieldVal = recPtr->GetCollect("BusinessRelateInfoId");
				sBusinessRelationInfo.strBusinessRelateInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BusinessInfoId");
				sBusinessRelationInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RelateType");
				sBusinessRelationInfo.nRelateType = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Relate1");
				sBusinessRelationInfo.strRelate1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Relate2");
				sBusinessRelationInfo.strRelate2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Relate3");
				sBusinessRelationInfo.strRelate3 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;

				vecInfo.push_back(sBusinessRelationInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

QueryResultType XhBFISDBOperationImp::QueryBusinessInfoCountByCondition(ST_BusinessQueryParam stInfo,IN OUT int& nCount)
{
	STRY;
	if (stInfo.strStartTime == _T("") || stInfo.strEndTime == _T(""))
	{
		DISPLAY_LOG("数据库","通过条件查询业务信息失败","传入开始时间或结束时间为空","",0);
		return QueryFail;
	}
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strSQL.Format("call proc_businessinfo_count_querybycondition(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\")",
		stInfo.strBranchId.c_str(),stInfo.strEmployeeId.c_str(),stInfo.strCustomerId.c_str(),stInfo.strProduceId.c_str(),
		stInfo.strStartTime.c_str(),stInfo.strEndTime.c_str(),stInfo.strSerialNumber.c_str(),stInfo.strCredenitialsType.c_str(),
        stInfo.strBusinessType.c_str(),stInfo.strCardNumber.c_str(),stInfo.nMarkerType,stInfo.strRiskLevel.c_str(),stInfo.strConditionEx.c_str(),stInfo.strMediumNum.c_str(),
		stInfo.strExtendedInfo2.c_str());
	TTRACE("[数据库]通过条件查询业务信息数量:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过条件查询业务信息数量失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			varFieldVal = recPtr->GetCollect("count(BusInessInfoId)");
			nCount = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
		{
			return QuerySuccessWithoutResult;
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

QueryResultType XhBFISDBOperationImp::QueryBusinessInfoByEmployeeIdAndCount(string strId,int nCount,IN OUT map<std::string,int>& mapInfo)
{
	STRY;
	if (strId == "" || nCount <= 0)
	{
		DISPLAY_LOG("数据库","查询经常使用产品信息失败","传入员工GUID为空或数量小于等于0","",0);
		return QueryFail;
	}
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strSQL.Format("call proc_businessInfo_selectbyemployeeidAndCount(\"%s\",%d)",strId.c_str(),nCount);
	TTRACE("[数据库]查询经常使用的产品:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询经常使用的产品失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			std::string strProduceId;
			int nCount;
			while(!recPtr->adoEOF)
			{
				varFieldVal = recPtr->GetCollect("ProduceId");
				strProduceId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("count");
				nCount = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				mapInfo[strProduceId] = nCount;
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
		{
			return QuerySuccessWithoutResult;
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

QueryResultType XhBFISDBOperationImp::QueryHotProduceIdByCount(int nCount,IN OUT map<std::string,int>& mapInfo)
{
	STRY;
	if (nCount <= 0)
	{
		DISPLAY_LOG("数据库","查询热门产品失败","传入数量小于等于0","",0);
		return QueryFail;
	}
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_businessInfo_mostusually_produce(%d)");
	strSQL.Format(strMsg,nCount);
	TTRACE("[数据库]热门产品查询语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{  
		DISPLAY_LOG("数据库","查询热门产品失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			std::string strProduceId;
			int nCount;
			while(!recPtr->adoEOF)
			{
				varFieldVal = recPtr->GetCollect("ProduceId");
				strProduceId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("count");
				nCount = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				mapInfo[strProduceId] = nCount;
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
		{
			return QuerySuccessWithoutResult;
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

int XhBFISDBOperationImp::CreateNewGuid(std::string& strGUID)
{
	STRY;
	char pBuf[64] = {0};
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snprintf(pBuf,sizeof(pBuf),"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"
			,guid.Data1
			,guid.Data2
			,guid.Data3
			,guid.Data4[0],guid.Data4[1]
		,guid.Data4[2],guid.Data4[3],guid.Data4[4],guid.Data4[5]
		,guid.Data4[6],guid.Data4[7]);
	}
	strGUID = pBuf;
	return 1;
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::QueryKeyValueInfoByTypeAndCode(std::string strType,std::string strCode,vector<ST_KeyValueInfo>& vecKeyValueInfo)
{
	STRY;
	if(strType == "")
	{
		DISPLAY_LOG("数据库","通过类型或编码查询键值信息失败","传入类型为空","",0);
		return -1;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	CString strSql;
	if (strCode == "")
		strSql.Format(_T("call proc_keyvalueinfo_selbytype(\"%s\")"),strType.c_str());
	else
		strSql.Format(_T("call proc_keyvalueinfo_selbytypeCode(\"%s\",\"%s\")"),strType.c_str(),strCode.c_str());
	TTRACE("[数据库]通过条件查询键值信息:%s \r\n",strSql);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSql,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过条件查询键值信息失败","执行SQL语句失败","",0);
		return -1;
	}
	if(nRestAff > 0)
	{
		while(!recPtr->adoEOF)
		{
			ST_KeyValueInfo stKeyValueInfo;
			varFieldVal = recPtr->GetCollect("KeyValeInfoId");
			stKeyValueInfo.strKeyValueInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("Type");
			stKeyValueInfo.strType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("Code");
			stKeyValueInfo.strCode = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("Value");
			stKeyValueInfo.strValue = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("ExtendedInfo");
			stKeyValueInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
			varFieldVal = recPtr->GetCollect("ExtendedInfo1");
			stKeyValueInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			varFieldVal = recPtr->GetCollect("ExtendedInfo1");
			stKeyValueInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;

			vecKeyValueInfo.push_back(stKeyValueInfo);
			recPtr->MoveNext();
		}
		if(recPtr != NULL && recPtr->GetState() == adStateOpen)
			recPtr->Close();
		return 1;
	}
	return -1;
	SCATCH;
	return -1;
}

ISOC_INT XhBFISDBOperationImp::ManageTransparentData(DBOperType oper,std::string strType,std::string strCode,std::string strValue)
{
	STRY;
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	CString strSql;
	switch (oper)
	{
	case DBO_ADD:
		{
#if USE_BFIS_ASSERT
			BFIS_ASSERT_STDSTRING(strType,"添加键值信息");
			BFIS_ASSERT_STDSTRING(strCode,"添加键值信息");
			BFIS_ASSERT_STDSTRING(strValue,"添加键值信息");
#else
			if(strType == "" || strCode == "" || strValue == "")
			{
				TTRACE("[数据库]传入键值信息:Type:%s,Code:%s,Value:%s \r\n",strType.c_str(),strCode.c_str(),strValue.c_str());
				DISPLAY_LOG("数据库","添加键值信息失败","传入类型或编码或值为空","",0);
				return -1;
			}
#endif
			std::string strGUID;
			if(CreateNewGuid(strGUID) <= 0){return -1;}
			strSql.Format(_T("call proc_keyvaleinfo_insert(\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")"),
				strGUID.c_str(),strType.c_str(),strCode.c_str(),strValue.c_str(),0,"","");
		}
		break;
	case DBO_DEL:
		{
#if USE_BFIS_ASSERT
			BFIS_ASSERT_STDSTRING(strType,"删除键值信息");
			BFIS_ASSERT_STDSTRING(strCode,"删除键值信息");
#else
			if(strType == "" && strCode == "")
			{
				TTRACE("[数据库]传入键值信息:Type:%s,Code:%s,Value:%s \r\n",strType.c_str(),strCode.c_str(),strValue.c_str());
				DISPLAY_LOG("数据库","删除键值信息失败","传入类型和编码为空","",0);
				return -1;
			}
#endif
			strSql.Format(_T("call proc_keyvalueinfo_delbyconditon(\"%s\",\"%s\")"),
				strType.c_str(),strCode.c_str(),strValue.c_str());
		}
		break;
	}
	TTRACE("[数据库]管理键值信息:%s \r\n",strSql);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSql,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","管理键值信息失败","执行SQL语句失败","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

ISOC_BOOL XhBFISDBOperationImp::SetMigratedBusinessFileInfo(std::string strRecordId,int nMigrated /*= 0*/)
{
	STRY;
	if (strRecordId == "")
	{
		DISPLAY_LOG("数据库","设置业务文件迁移标识失败","传入GUID为空","",0);
		return FALSE;
	}
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strSQL.Format("call proc_businessfileinfo_setMigrated(\"%s\",%d)",strRecordId.c_str(),nMigrated);
	TTRACE("[数据库]设置任务迁移标识语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","设置任务迁移标识失败","执行SQL语句失败","",0);
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISDBOperationImp::SetMigratedBusinessInfo(std::string strBusinessInfoId,int nMigrated /*= 0*/)
{
	STRY;
	if (strBusinessInfoId == "")
	{
		DISPLAY_LOG("数据库","设置业务信息迁移标识失败","传入GUID为空","",0);
		return FALSE;
	}
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strSQL.Format("call proc_businessinfo_setMigrated(\"%s\",%d)",strBusinessInfoId.c_str(),nMigrated);
	TTRACE("[数据库]设置任务业务信息Id语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","设置业务信息是否被迁移标识","执行SQL语句失败","",0);
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

QueryResultType XhBFISDBOperationImp::QueryTaskNotMigrated(vector<ST_BusinessFileInfo>& vecInfos,int nCount,int nMigrated /*= 0*/)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strSQL.Format("call proc_businessfielinfo_selbyMigrateAndcount(%d,%d)",nMigrated,nCount);
	std::string strText;
	nMigrated == 0 ? (strText = "查询未迁移业务信息") : (strText = "查询迁移业务信息");
	CString strTemp;
	strTemp.Format("[数据库]%s语句:%s \r\n",strText.c_str(),strSQL);
	TTRACE(strTemp);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库",strText,"执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_BusinessFileInfo stInfo;
				varFieldVal = recPtr->GetCollect("RecordId");
				stInfo.strRecordId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BusinessInfoId");
				stInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Type");
				stInfo.nType = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("FileId");
				stInfo.strFileId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RecordBegin");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					stInfo.strRecordBegin = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("RecordEnd");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					stInfo.strRecordEnd = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				stInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				stInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				stInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				vecInfos.push_back(stInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

QueryResultType XhBFISDBOperationImp::QueryTaskNotMigrated(vector<ST_BusinessInfo>& vecInfos,int nCount,int nMigrated /*= 0*/)
{
	STRY;
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strSQL.Format("call proc_businessinfo_selbyMigrateAndcount(%d,%d)",nMigrated,nCount);
	std::string strText;
	nMigrated == 0 ? (strText = "查询未迁移业务信息") : (strText = "查询迁移业务信息");
	CString strTemp;
	strTemp.Format("[数据库]%s语句:%s \r\n",strText.c_str(),strSQL);
	TTRACE(strTemp);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{
		
		DISPLAY_LOG("数据库",strText,"执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_BusinessInfo stInfo;
#if 0
				varFieldVal = recPtr->GetCollect("BusInessInfoId");
				stInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Datetime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					stInfo.strDateTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("BranchId");
				stInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ClientId");
				stInfo.strClientId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				stInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ProduceId");
				stInfo.strProduceId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SubEquipmentId");
				stInfo.strSubEquipmentId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				stInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				stInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				stInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SubEquipmentIcmSign");
				stInfo.strSubEquipmentIcmSign = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SerialNumber");
				stInfo.strSerialNumber = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Migrated");
				stInfo.nMigrated = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
#else
				if(m_BusinessMan.querySingleBusinessInfo(varFieldVal,recPtr,stInfo))
				{
#endif
					vecInfos.push_back(stInfo);
				}
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

ISOC_INT XhBFISDBOperationImp::ManageTaskPlanInfo(DBOperType oper,IN OUT vector<ST_TaskPlan>& vecInfos)
{
	STRY;
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	CString strSql = "";
	switch(oper) 
	{
	case DBO_ADD:
		{
			ST_TaskPlan stInfo = vecInfos[0];
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(stInfo.strPlanID,    "添加备份计划");
        BFIS_ASSERT_STDSTRING(stInfo.strTimeBegin, "添加备份计划");
        BFIS_ASSERT_STDSTRING(stInfo.strTimeEnd,   "添加备份计划");
#else
			if (stInfo.strPlanID == "" || stInfo.strTimeBegin == "" || stInfo.strTimeEnd == "")
			{
				TTRACE("[数据库]传入任务计划信息:PlanID:%s,TimeBegin:%s,TimeEnd:%s \r\n",stInfo.strPlanID.c_str(),
					stInfo.strTimeBegin.c_str(),stInfo.strTimeEnd.c_str());
				DISPLAY_LOG("数据库","添加任务计划失败","传入GUID或开始时间或结束时间为空","",0);
				return QueryFail;
			}
#endif
			strSql.Format("call proc_taskplaninfo_insert(\"%s\",\"%s\",\"%s\",%d,%d)",stInfo.strPlanID.c_str(),
				stInfo.strTimeBegin.c_str(),stInfo.strTimeEnd.c_str(),stInfo.nEnable,stInfo.nOrderID);
		}
		break;
	case DBO_UPDATE:
		{
			ST_TaskPlan stInfo = vecInfos[0];
#if USE_BFIS_ASSERT
        BFIS_ASSERT_STDSTRING(stInfo.strPlanID,    "更新备份计划");
        BFIS_ASSERT_STDSTRING(stInfo.strTimeBegin, "更新备份计划");
        BFIS_ASSERT_STDSTRING(stInfo.strTimeEnd,   "更新备份计划");
#else
			if (stInfo.strPlanID == "" || stInfo.strTimeBegin == "" || stInfo.strTimeEnd == "")
			{
				TTRACE("[数据库]传入任务计划信息:PlanID:%s,TimeBegin:%s,TimeEnd:%s \r\n",stInfo.strPlanID.c_str(),
					stInfo.strTimeBegin.c_str(),stInfo.strTimeEnd.c_str());
				DISPLAY_LOG("数据库","添加任务计划失败","传入GUID或开始时间或结束时间为空","",0);
				return QueryFail;
			}
#endif
			strSql.Format("call proc_taskplaninfo_update(\"%s\",\"%s\",\"%s\",%d,%d)",stInfo.strPlanID.c_str(),
				stInfo.strTimeBegin.c_str(),stInfo.strTimeEnd.c_str(),stInfo.nEnable,stInfo.nOrderID);
		}
		break;
	case DBO_QUERY:
		{
			strSql = "call proc_taskplaninfo_select()";
		}
		break;
	case DBO_DEL:
		{
			strSql = "call proc_taskplaninfo_deleteall()";
		}
		break;
	default:
		{
			TTRACE("[数据库]管理任务计划信息失败，未知错误:%s[%d] \r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
	}
	TTRACE("[数据库]管理任务计划信息语句:%s \r\n",strSql);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSql,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","管理任务计划信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(oper == DBO_QUERY && nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_TaskPlan stInfo;
				varFieldVal = recPtr->GetCollect("PlanId");
				stInfo.strPlanID = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("TimeBegin");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					stInfo.strTimeBegin = da.Format(_T("%H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("TimeEnd");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					stInfo.strTimeEnd = da.Format(_T("%H:%M:%S"));  
                }
                varFieldVal = recPtr->GetCollect("Enable");
                stInfo.nEnable = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.dblVal;
                varFieldVal = recPtr->GetCollect("OrderId");
                stInfo.nOrderID = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.dblVal;
                vecInfos.push_back(stInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::ManageScriptInfo(IN DBOperType enOperType, IN OUT ST_ScriptInfo& sScriptInfo)
{	
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	switch(enOperType)
	{
	case DBO_QUERY:
		{
			return QueryScriptInfoByID(sScriptInfo);
		}
	case DBO_ADD:
		{
			strMsg = _T("call proc_scriptinfo_insert(\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")");
			strSQL.Format(strMsg,sScriptInfo.strScriptId.c_str(),sScriptInfo.strBusinessCode.c_str(),sScriptInfo.strBusinessType.c_str(),
				sScriptInfo.strScriptContent.c_str(),sScriptInfo.nExtendedInfo,sScriptInfo.strExtendedInfo1.c_str(),sScriptInfo.strExtendedInfo2.c_str());
		}
		break;
	case DBO_UPDATE:
		{
			strMsg = _T("call proc_scriptinfo_update(\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\")");
			strSQL.Format(strMsg,sScriptInfo.strScriptId.c_str(),sScriptInfo.strBusinessCode.c_str(),sScriptInfo.strBusinessType.c_str(),
				sScriptInfo.strScriptContent.c_str(),sScriptInfo.nExtendedInfo,sScriptInfo.strExtendedInfo1.c_str(),sScriptInfo.strExtendedInfo2.c_str());
		}
		break;
	case DBO_DEL: 
		{
			if (sScriptInfo.strScriptId != "" && DeleteInfoById(DataType_ScriptInfo,sScriptInfo.strScriptId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
		}
		break;
	default:
		{
			TTRACE("[数据库]未知错误%s[%d] \r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;

	TTRACE("[数据库]语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","管理话术信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	return QuerySuccessWithoutResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::QueryScriptInfoByID(IN OUT ST_ScriptInfo& sScriptInfo,IN bool bOverlapped)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	if (sScriptInfo.strScriptId == _T(""))
	{
		DISPLAY_LOG("数据库","通过GUID话术信息失败","传入GUID为空","",0);
		return QueryFail;
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_scriptinfo_selectbyid(\"%s\")");
	strSQL.Format(strMsg,sScriptInfo.strScriptId .c_str());
	TTRACE("[数据库]通过GUID查询员工信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","通过GUID查询员工信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0 && !recPtr->adoEOF)
		{
			if(bOverlapped)
			{
				varFieldVal = recPtr->GetCollect("ScriptId");
				sScriptInfo.strScriptId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BusinessCode");
				sScriptInfo.strBusinessCode = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BusinessType");
				sScriptInfo.strBusinessType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ScriptContent");
				sScriptInfo.strScriptContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sScriptInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sScriptInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sScriptInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
ISOC_BOOL XhBFISDBOperationImp::QueryDiffScriptInfo(IN int nAll,IN OUT vector<ST_ScriptInfo>& vecScriptInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	strMsg = _T("call proc_scriptinfo_select()");
	strSQL.Format(strMsg);
	TTRACE("[数据库]查询话术信息语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询话术信息失败","执行SQL语句失败","",0);
		return FALSE;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_ScriptInfo stScriptInfo;
				varFieldVal = recPtr->GetCollect("ScriptId");
				stScriptInfo.strScriptId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BusinessCode");
				stScriptInfo.strBusinessCode = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BusinessType");
				stScriptInfo.strBusinessType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ScriptContent");
				stScriptInfo.strScriptContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				stScriptInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				stScriptInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				stScriptInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				vecScriptInfo.push_back(stScriptInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
QueryResultType XhBFISDBOperationImp::ManageOperateLogInfo(IN DBOperType enOperType, IN OUT ST_OperateLogInfo& sOperateLogInfo)
{
	STRY;
	CString strMsg = _T("");
	CString strSQL = _T("");
	switch(enOperType)
	{
	case DBO_QUERY:
		{
			//return QueryScriptInfoByID(sScriptInfo);
		}
	case DBO_ADD:
		{
			strMsg = _T("call proc_operateloginfo_insert(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\")");
			strSQL.Format(strMsg,sOperateLogInfo.strOperateLogId.c_str(),sOperateLogInfo.strModule.c_str(),sOperateLogInfo.strOperateEvent.c_str(),
				sOperateLogInfo.strIp.c_str(),sOperateLogInfo.strEmployeeId.c_str(),sOperateLogInfo.strBranchId.c_str(),sOperateLogInfo.nExtendedInfo,
				sOperateLogInfo.strExtendedInfo1.c_str());
		}
		break;
	case DBO_UPDATE:
		{
			strMsg = _T("call proc_operateloginfo_update(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\")");
			strSQL.Format(strMsg,sOperateLogInfo.strOperateLogId.c_str(),sOperateLogInfo.strModule.c_str(),sOperateLogInfo.strOperateEvent.c_str(),
				sOperateLogInfo.strIp.c_str(),sOperateLogInfo.strEmployeeId.c_str(),sOperateLogInfo.strBranchId.c_str(),sOperateLogInfo.nExtendedInfo,
				sOperateLogInfo.strExtendedInfo1.c_str());
		}
		break;
	case DBO_DEL: 
		{
			if (sOperateLogInfo.strOperateLogId != "" && DeleteInfoById(DataType_OperateLogInfo,sOperateLogInfo.strOperateLogId))
			{
				return QuerySuccessWithoutResult;
			}
			else
			{
				return QueryFail;
			}
		}
		break;
	default:
		{
			TTRACE("[数据库]未知错误%s[%d] \r\n",__FUNCTION__,__LINE__);
			return QueryFail;
		}
	}
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;

	TTRACE("[数据库]语句:%s \r\n",strSQL);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)strSQL,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","管理话术信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	return QuerySuccessWithoutResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::ManageMigrateLogInfo(IN DBOperType enOperType,IN OUT ST_MigrateLogInfo& stInfo)
{
	STRY;
	char szMsg[255] = {0};
	sprintf(szMsg,"%s迁移日志信息",enOperType == DBO_ADD ? "添加" : "更新");
#if USE_BFIS_ASSERT
	BFIS_ASSERT_STDSTRING(stInfo.strMigrateTaskID,		szMsg);
	BFIS_ASSERT_STDSTRING(stInfo.strBusinessID,			szMsg);
	/*BFIS_ASSERT_STDSTRING(stInfo.strProduceID,			szMsg);
	BFIS_ASSERT_STDSTRING(stInfo.strLaunchEmployeeID,	szMsg);*/
#endif
	SimpleConnection conn(this);
	int nRestAff = 0;
	_variant_t varFieldVal;
	_RecordsetPtr recPtr = NULL;
	char szSql[1024] = {0};
	switch(enOperType)
	{
	case DBO_ADD:
		{
			sprintf(szSql,"call proc_migratelog_insert(\"%s\",\"%s\",\"%s\",\"%s\",%d,%d,\"%s\",\"%s\",\"%s\",\"%s\",%d)",
				stInfo.strMigrateTaskID.c_str(),stInfo.strBusinessID.c_str(),stInfo.strProduceID.c_str(),stInfo.strEmployeeID.c_str(),
				stInfo.nType,stInfo.nStatus,stInfo.strAutoTime.c_str(),stInfo.strBeginTime.c_str(),stInfo.strEndTime.c_str(),
				stInfo.strLaunchEmployeeID.c_str(),stInfo.nOrderID);
		}
		break;
	case DBO_UPDATE:
		{
			sprintf(szSql,"call proc_migratelog_update(\"%s\",\"%s\",\"%s\",\"%s\",%d,%d,\"%s\",\"%s\",\"%s\",\"%s\",%d)",
				stInfo.strMigrateTaskID.c_str(),stInfo.strBusinessID.c_str(),stInfo.strProduceID.c_str(),stInfo.strEmployeeID.c_str(),
				stInfo.nType,stInfo.nStatus,stInfo.strAutoTime.c_str(),stInfo.strBeginTime.c_str(),stInfo.strEndTime.c_str(),
				stInfo.strLaunchEmployeeID.c_str(),stInfo.nOrderID);
		}
		break;
	}
	if(strlen(szSql) == 0 || !ExecuteSQLSafe(conn.m_pCon, (_bstr_t)szSql,recPtr,nRestAff))
	{
		DISPLAY_LOG("数据库","管理迁移日志信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	return QuerySuccessWithoutResult;
	SCATCH;
	return QueryFail;
}
QueryResultType XhBFISDBOperationImp::QueryMigrateLogInfoByCondition(IN const ST_QueryCondition& stCondition,std::vector<ST_MigrateLogInfo>& 
	vecInfo)
{
	STRY;
#if USE_BFIS_ASSERT
	BFIS_ASSERT_STDSTRING(stCondition.strCon1,"通过条件查询迁移日志信息");
	BFIS_ASSERT_STDSTRING(stCondition.strCon2,"通过条件查询迁移日志信息");
#endif
	SimpleConnection conn(this);
	int nRestAff = 0;
	_variant_t varFieldVal;
	_RecordsetPtr recPtr = NULL;
	char szSql[1024] = {0};
	sprintf(szSql,"call proc_migratelog_querybycondition(\"%s\",\"%s\",%d,%d)",
		stCondition.strCon1.c_str(),stCondition.strCon2.c_str(),stCondition.nPageSize,stCondition.nPageIndex);
	if(strlen(szSql) == 0 || !ExecuteSQLSafe(conn.m_pCon, (_bstr_t)szSql,recPtr,nRestAff))
	{
		DISPLAY_LOG("数据库","通过条件查询迁移日志信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_MigrateLogInfo stInfo;
				varFieldVal = recPtr->GetCollect("MigrateTaskID");
				stInfo.strMigrateTaskID = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BusinessID");
				stInfo.strBusinessID = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ProduceID");
				stInfo.strProduceID = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeID");
				stInfo.strEmployeeID = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Type");
				stInfo.nType = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Status");
				stInfo.nStatus = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("AutoTime");
				if(varFieldVal.vt != NULL)
				{
					DATE dt = varFieldVal.date;
					COleDateTime da = (COleDateTime)dt;
					stInfo.strAutoTime = da.Format("%Y-%m-%d %H:%M:%S");
				}
				varFieldVal = recPtr->GetCollect("BeginTime");
				if(varFieldVal.vt != NULL)
				{
					DATE dt = varFieldVal.date;
					COleDateTime da = (COleDateTime)dt;
					stInfo.strBeginTime = da.Format("%Y-%m-%d %H:%M:%S");
				}
				varFieldVal = recPtr->GetCollect("EndTime");
				if(varFieldVal.vt != NULL)
				{
					DATE dt = varFieldVal.date;
					COleDateTime da = (COleDateTime)dt;
					stInfo.strEndTime = da.Format("%Y-%m-%d %H:%M:%S");
				}
				varFieldVal = recPtr->GetCollect("LaunchEmployeeID");
				stInfo.strLaunchEmployeeID = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("OrderID");
				stInfo.nOrderID = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;

				vecInfo.push_back(stInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
ISOC_INT XhBFISDBOperationImp::QueryScriptInfo(vector<ST_ScriptInfo>& vecInfos, DWORD_PTR dwReserved)
{
	STRY;
	return QueryDiffScriptInfo((int)dwReserved,vecInfos);
	SCATCH;
	return -1;
}
QueryResultType XhBFISDBOperationImp::QueryMigrateLogInfoCountByCondition(IN const ST_QueryCondition& stCondition,int& nTotalCount)
{
	STRY;
#if USE_BFIS_ASSERT
	BFIS_ASSERT_STDSTRING(stCondition.strCon1,"通过条件查询迁移日志信息总数量");
	BFIS_ASSERT_STDSTRING(stCondition.strCon2,"通过条件查询迁移日志信息总数量");
#endif
	SimpleConnection conn(this);
	int nRestAff = 0;
	_variant_t varFieldVal;
	_RecordsetPtr recPtr = NULL;
	char szSql[1024] = {0};
	sprintf(szSql,"call proc_migratelog_count_querybycondition(\"%s\",\"%s\")",stCondition.strCon1.c_str(),stCondition.strCon2.c_str());
	if(strlen(szSql) == 0 || !ExecuteSQLSafe(conn.m_pCon, (_bstr_t)szSql,recPtr,nRestAff))
	{
		DISPLAY_LOG("数据库","通过条件查询迁移日志信息总数量失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			varFieldVal = recPtr->GetCollect("count(MigrateTaskID)");
			nTotalCount = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

QueryResultType XhBFISDBOperationImp::QueryProduceNeed2Sync(IN string strSyncTime,IN OUT vector<ST_ProduceInfo>& vecInfo)
{
	STRY;
#if USE_BFIS_ASSERT
	BFIS_ASSERT_STDSTRING(strSyncTime,	"查询需要同步的产品信息");
#endif
	char szSql[1024] = {0};
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	sprintf(szSql,"call proc_produceinfo_queryneed2sync(\"%s\")",strSyncTime.c_str());
	TTRACE("[数据库]查询需要同步的产品信息失败:%s \r\n",szSql);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)szSql,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询需要同步的产品信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_ProduceInfo sProduceInfo;
				varFieldVal = recPtr->GetCollect("ProduceId");
				sProduceInfo.strProduceId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Name");
				sProduceInfo.strName = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ProduceCode");
				sProduceInfo.strProduceCode = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Period");
				sProduceInfo.nPeriod = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Revenue");
				sProduceInfo.strRevenue = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("MiniAmount");
				sProduceInfo.nMiniAmount = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("RiskLevel");
				sProduceInfo.strRiskLevel = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SerialNumber");
				sProduceInfo.strSerialNumber = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PublishBeginTime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sProduceInfo.strPublishBeinTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("PublishEndTime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sProduceInfo.strPublishEndTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("ProductionType");
				sProduceInfo.strProductionType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ApplicableCustomer");
				sProduceInfo.strApplicableCustomer = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RevenueType");
				sProduceInfo.strRevenueType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("IncrementMoney");
				sProduceInfo.strIncrementMoney = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("CurrencyType");
				sProduceInfo.strCurrentyType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("SealsBranch");
				sProduceInfo.strSealsBranch = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RevenueInitialDay");
				sProduceInfo.strRevenueInitialDay = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Deadline");
				sProduceInfo.strDeadLine = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("PaymentDay");
				sProduceInfo.strPaymentDay = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("TrusteeFee");
				sProduceInfo.strTrusteeFee = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("CommissionCharge");
				sProduceInfo.strCommissionCharge = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Trustee");
				sProduceInfo.strTrustee = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("OverheadCharge");
				sProduceInfo.strOverheadCharge = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("RevenueCalculation");
				sProduceInfo.strRevenueCalculation = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Content");
				sProduceInfo.strContent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("MaxTime");
				sProduceInfo.nMaxTime = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("MimiTime");
				sProduceInfo.nMineTime = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("StandardTime");
				sProduceInfo.nStandardTime = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("Prequestion");
				sProduceInfo.strPrequestion = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("IsPublished");
				sProduceInfo.nIsPublished = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("IsEnabled");
				sProduceInfo.nIsEnabled = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sProduceInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sProduceInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo2");
				sProduceInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EnableMigrated");
				sProduceInfo.nEnableMigrated = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
				varFieldVal = recPtr->GetCollect("RecordExistDays");
				sProduceInfo.nRecordExistDays = varFieldVal.vt == VT_NULL ? 0 : (double)varFieldVal.dblVal;
                varFieldVal = recPtr->GetCollect("Type");
                sProduceInfo.nType = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
                varFieldVal = recPtr->GetCollect("RiskLevelDesc");
                sProduceInfo.strRiskLevelDesc = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
                varFieldVal = recPtr->GetCollect("PROD_LIFECYCLE");
                sProduceInfo.nPROD_LIFECYCLE = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				vecInfo.push_back(sProduceInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}

QueryResultType XhBFISDBOperationImp::QueryMinProduceSyncTime(OUT string& strSyncTime)
{
	STRY;
	strSyncTime = "";
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	char szSql[1024] = {0};
	_tcscpy(szSql,"call proc_produceinfo_querylastsynctime()");
	TTRACE("[数据库]查询最后一次产品同步时间失败:%s \r\n",szSql);
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)szSql,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询最后一次产品同步时间失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			if(!recPtr->adoEOF)
			{
				varFieldVal = recPtr->GetCollect("max(RowVersion)");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					strSyncTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				if(recPtr != NULL && recPtr->GetState() == adStateOpen)
					recPtr->Close();
			}
		}
		else
			return QuerySuccessWithoutResult;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return QueryFail;
	}
	return QuerySuccessWithResult;
	SCATCH;
	return QueryFail;
}
ISOC_BOOL XhBFISDBOperationImp::QueryOperateLogInfoByEmployeeId(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strEmployeeId)
{
	STRY;
	char szSql[1024] = {0};
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	sprintf(szSql,"call proc_operateloginfo_selectbyemployeeid(\"%s\")",strEmployeeId.c_str());
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)szSql,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询需要同步的产品信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_OperateLogInfo sOperateLogInfo;
				varFieldVal = recPtr->GetCollect("OperateLogId");
				sOperateLogInfo.strOperateLogId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Module");
				sOperateLogInfo.strModule = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("OperateEvent");
				sOperateLogInfo.strOperateEvent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Ip");
				sOperateLogInfo.strIp = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				sOperateLogInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BranchId");
				sOperateLogInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("OperateTime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sOperateLogInfo.stOperateTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sOperateLogInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sOperateLogInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				vecInfos.push_back(sOperateLogInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return TRUE;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISDBOperationImp::QueryNeedDelOperateLogInfo(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strTime)
{
	STRY;
	char szSql[1024] = {0};
	SimpleConnection conn(this);
	int				nRestAff = 0;
	_variant_t		varFieldVal;
	_RecordsetPtr	recPtr = NULL;
	sprintf(szSql,"call proc_operateloginfo_select(\"%s\")",strTime.c_str());
	if (!ExecuteSQLSafe(conn.m_pCon, (_bstr_t)szSql,recPtr,nRestAff))
	{       
		DISPLAY_LOG("数据库","查询需要同步的产品信息失败","执行SQL语句失败","",0);
		return QueryFail;
	}
	try
	{
		if(nRestAff > 0)
		{
			while(!recPtr->adoEOF)
			{
				ST_OperateLogInfo sOperateLogInfo;
				varFieldVal = recPtr->GetCollect("OperateLogId");
				sOperateLogInfo.strOperateLogId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Module");
				sOperateLogInfo.strModule = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("OperateEvent");
				sOperateLogInfo.strOperateEvent = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("Ip");
				sOperateLogInfo.strIp = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("EmployeeId");
				sOperateLogInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("BranchId");
				sOperateLogInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				varFieldVal = recPtr->GetCollect("OperateTime");
				if(varFieldVal.vt != VT_NULL)
				{
					DATE dt = varFieldVal.date;  
					COleDateTime da = COleDateTime(dt);  
					sOperateLogInfo.stOperateTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
				}
				varFieldVal = recPtr->GetCollect("ExtendedInfo");
				sOperateLogInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
				varFieldVal = recPtr->GetCollect("ExtendedInfo1");
				sOperateLogInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
				vecInfos.push_back(sOperateLogInfo);
				recPtr->MoveNext();
			}
			if(recPtr != NULL && recPtr->GetState() == adStateOpen)
				recPtr->Close();
		}
		else
			return TRUE;
	}
	catch(_com_error e)
	{
		TTRACE("%s[%d]:%d, %s\r\n", _T("[数据库]"), __LINE__, e.Error(), (LPTSTR)(e.Description()));
		return FALSE;
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_INT XhBFISDBOperationImp::QueryDeskStatus(IN std::vector<std::string> vecDisk,OUT int& nDiskTotal,OUT int& nDiskFree)
{
	//int DiskCount = 0;  
	//DWORD DiskInfo = GetLogicalDrives();  
	////利用GetLogicalDrives()函数可以获取系统中逻辑驱动器的数量，函数返回的是一个32位无符号整型数据。  
	//while(DiskInfo)//通过循环操作查看每一位数据是否为1，如果为1则磁盘为真,如果为0则磁盘不存在。  
	//{  
	//	if(DiskInfo&1)//通过位运算的逻辑与操作，判断是否为1  
	//	{  
	//		++DiskCount;  
	//	}  
	//	DiskInfo = DiskInfo >> 1;//通过位运算的右移操作保证每循环一次所检查的位置向右移动一位。  
	//	//DiskInfo = DiskInfo/2;  
	//}  
	////-------------------------------------------------------------------  
	//int DSLength = GetLogicalDriveStrings(0,NULL);  
	////通过GetLogicalDriveStrings()函数获取所有驱动器字符串信息长度。  
	//char* DStr = new char[DSLength];//用获取的长度在堆区创建一个c风格的字符串数组  
	//GetLogicalDriveStrings(DSLength,(LPTSTR)DStr);  
	//通过GetLogicalDriveStrings将字符串信息复制到堆区数组中,其中保存了所有驱动器的信息。  

	if(vecDisk.empty())
	{
		nDiskTotal = 0;
		nDiskTotal = 0;
		return TRUE;
	}
	BOOL fResult = FALSE;  
	unsigned _int64 i64FreeBytesToCaller;  
	unsigned _int64 i64TotalBytes;  
	unsigned _int64 i64FreeBytes;  

	for (int i = 0; i < vecDisk.size(); i++)
	{
		fResult = GetDiskFreeSpaceEx(  
			vecDisk[i].c_str(),  
			(PULARGE_INTEGER)&i64FreeBytesToCaller,  
			(PULARGE_INTEGER)&i64TotalBytes,  
			(PULARGE_INTEGER)&i64FreeBytes);
		nDiskFree += (int)(i64FreeBytes/1024/1024/1024);
		nDiskTotal += (int)(i64TotalBytes/1024/1024/1024);
	}	
	return fResult;
}