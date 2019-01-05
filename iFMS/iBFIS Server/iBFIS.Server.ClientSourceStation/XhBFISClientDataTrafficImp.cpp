#include "stdafx.h"
#include "XhBFISClientDataTrafficImp.h"
#include "iSOC_MonFactoryManagement.h"
#include "IcmsP_Utility.h"
#include "XhLogDisplayInterface.h"
#include "iFVR_Configuration.h"
#include "IBFISSyncClient.h"
#include "iBFISDBOperation.h"
#include <sstream>
#include "IcmsP_XmlParser.h"
#include "iSOC_ErrorDef.h"
#include <boost/tokenizer.hpp>
#include <boost/xpressive/xpressive_dynamic.hpp>
#include "iBFIS_Communication.h"
#include <boost/format.hpp>
#include <boost\date_time\gregorian\gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#define BOOST_DATE_TIME_SOURCE


XhBFISClientDataTrafficImp::XhBFISClientDataTrafficImp()
{
	m_pClientSource = NULL;
	m_pThread = NULL;
	m_bCheckUnFinishEmp = FALSE;
	iSOC_MonFactoryManagement fmt;
	m_pCallbackManager = static_cast<ICallbackManagement*>(fmt.CreateObject(OBJECT_TYPE_CALLBACK_MANAGER, "", __FUNCTION__));
}

XhBFISClientDataTrafficImp::~XhBFISClientDataTrafficImp()
{
	STRY;
	if (m_pCallbackManager)
	{
		iSOC_MonFactoryManagement fmt;
		fmt.ReleaseObject((CISocObject**)&m_pCallbackManager, __FUNCTION__);
		m_pCallbackManager = NULL;
	}
	SCATCH;
}

ISOC_BOOL XhBFISClientDataTrafficImp::Init()
{
	STRY;
	iSOC_MonFactoryManagement fmt;
	m_pClientSource = static_cast<IBFISClientSource*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_CLIENTSOURCE,"",__FUNCTION__));
	if (m_pClientSource == nullptr)
	{
		DISPLAY_LOG("服务端模块","创建客户端业务源失败","","",0);
		return FALSE;
	}
	else
	{
		DISPLAY_LOG("服务端模块","创建客户端业务源成功","","",1);
	}
	m_pClientSource->Init();
	m_pClientSource->QueryLocalBranchId(m_strLocalBranchId);
	m_bCheckUnFinishEmp = FALSE;

	InitStation();

	iCMSP_XmlParser xmlParser;
	bool bRet = xmlParser.Load("./Config/BankPluginConfig.xml");
	int nRet = -1;
	if (false == bRet)
	{
		TTRACE(" %s 加载插件配置文件失败\r\n", __FUNCTION__);
		return TRUE;
	}
	bRet = xmlParser.FindElem(_T("bankplugin"));
	if (false == bRet)
	{
		TTRACE(" %s 插件配置文查找元素失败\r\n", __FUNCTION__);
		return TRUE;
	}

	//CString strPluginName = xmlParser.GetAttrib(_T("pluginName"));
	if (m_pThread == nullptr)
	{
		m_pThread = static_cast<IThread*>(fmt.CreateObject(OBJECT_TYPE_THREAD, "", __FUNCTION__));
		if (m_pThread)
		{
			m_pThread->SetRunAbleInterface(this);
			m_pThread->Start();
		}
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISClientDataTrafficImp::UnInit()
{
	STRY;
	m_bCheckUnFinishEmp = TRUE;
	if (m_pThread && m_pThread->IsAlive())
	{
		Sleep(30);
	}
	SAFE_DELETE(m_pThread);
	UnInitStation();
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISClientDataTrafficImp::InitStation()
{
	STRY;
	//
	iSOC_MonFactoryManagement fmt;
	m_pCommunicateSource = (IBFISCommunicateSyncServer*)fmt.CreateObject(OBJECT_TYPE_BFIS_COMMUNICATESYNCSERVER,"",__FUNCTION__);
	if (fmt.CheckObjectCanBeUse(m_pCommunicateSource))
	{
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_LOGIN_2_SERVER,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_IS_ALIVE,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_BRANCHINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_PRODUCEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_USERMAPINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_ROLEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_PURVIEWINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_ROLEPURVIEWINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_EMPLOYEEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_EMPLOYEEPURVIEWINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_CLIENTINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_BUSINESSINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_BUSINESSFILEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_BUSINESSRELATEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_BUSINESSINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_TRANSPARENTDATA,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_1stACCESS_2_LOGIN_SERVER,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_CLIENTINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_SUPEREMPLOYEE,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_PRODUCEID,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_BRANCHINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_PRODUCEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_SET_USERMAPINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_ROLEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_PURVIEWINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_SET_ROLEPURVIEWINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_EMPLOYEEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_SET_EMPLOYEEPURVIEWINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_CLIENTINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_BUSINESSINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_SET_TRANSPARENTDATA,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_BRANCHINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_PRODUCEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_ROLEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_PURVIEWINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_EMPLOYEEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_CLIENTINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_BUSINESSINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_BRANCHINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_PRODUCEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_ROLEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_PURVIEWINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_EMPLOYEEINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_CLIENTINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_BUSINESSINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_TRANSPARENTDATA,this);
        m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_MCSERVERINFO, this);
        m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_BUSINESSINFOUNFINISH,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_SCRIPTINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_SCRIPTINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_SCRIPTINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_SCRIPTINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_SCRIPTINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_OPERATELOGINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_OPERATELOGINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_OPERATELOGINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_OPERATELOGINFO,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_DISKANDCONNECT,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_DISKANDCONNECT,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_DISKCODEANDCOUNT,this);
		m_pCommunicateSource->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_RECORDSTATUS,this);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISClientDataTrafficImp::UnInitStation()
{
	STRY;
	if (m_pCommunicateSource)
	{
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_LOGIN_2_SERVER,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_IS_ALIVE,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_BRANCHINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_PRODUCEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_USERMAPINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_ROLEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_PURVIEWINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_ROLEPURVIEWINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_EMPLOYEEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_EMPLOYEEPURVIEWINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_CLIENTINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_BUSINESSINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_BUSINESSFILEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_BUSINESSRELATEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_BUSINESSINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_TRANSPARENTDATA,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_1stACCESS_2_LOGIN_SERVER,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_CLIENTINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_SUPEREMPLOYEE,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_PRODUCEID,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_BRANCHINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_PRODUCEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_SET_USERMAPINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_ROLEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_PURVIEWINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_SET_ROLEPURVIEWINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_EMPLOYEEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_SET_EMPLOYEEPURVIEWINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_CLIENTINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_BUSINESSINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_SET_TRANSPARENTDATA,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_BRANCHINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_PRODUCEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_ROLEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_PURVIEWINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_EMPLOYEEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_CLIENTINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_BUSINESSINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_BRANCHINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_PRODUCEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_ROLEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_PURVIEWINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_EMPLOYEEINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_CLIENTINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_BUSINESSINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_TRANSPARENTDATA,this);
        m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_BUSINESSINFOUNFINISH,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_SCRIPTINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_SCRIPTINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_SCRIPTINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_GET_SCRIPTINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_SCRIPTINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_OPERATELOGINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_UPDATE_OPERATELOGINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_DEL_OPERATELOGINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_OPERATELOGINFO,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_DISKANDCONNECT,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_DISKANDCONNECT,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_DISKCODEANDCOUNT,this);
		m_pCommunicateSource->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_RECORDSTATUS,this);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISClientDataTrafficImp::HandleUnFixedTermBusiness(vector<ST_BusinessInfo>& vecBusiness,ST_StoreSet& stStoreSet)
{
	STRY;
	CTime cLocalDayTime = CTime::GetCurrentTime();
	for each(auto business in vecBusiness)
	{
		if (business.nMarkerType == 21 || business.nMarkerType == 22)
		{
			ST_ProduceInfo stProduce;
			if (business.strProduceId == "")
			{
				CString strTime; 
				strTime.Format("%s",business.strDateTime);
				COleDateTime businessTime;
				businessTime.ParseDateTime(strTime);
				CTime strSetTime(businessTime.GetYear() + stStoreSet.nUnFixedTermSaveTime,businessTime.GetMonth(),businessTime.GetDay(),businessTime.GetHour(),
					businessTime.GetMinute(),businessTime.GetSecond());
				CTimeSpan stSpan = cLocalDayTime - strSetTime;
				int nRealDay = stSpan.GetDays();
				if (nRealDay > 0)
				{
					m_pClientSource->ManageBusinessInfo(DBO_DEL,business);	
					ST_ClientInfo stClientInfo;
					stClientInfo.strClientId = business.strClientId;
					if(m_pClientSource->QueryClientInfoByID(stClientInfo))
					{
						m_pClientSource->ManageClientInfo(DBO_DEL,stClientInfo);
					}
				}
			}	
			if(business.strProduceId != "" && m_pClientSource->QueryProduceInfoById(business.strProduceId,stProduce))
			{
				if(stProduce.nType == 1)
				{ 
					CString strTime; 
					strTime.Format("%s",business.strDateTime);
					COleDateTime businessTime;
					businessTime.ParseDateTime(strTime);
					CTime strSetTime(businessTime.GetYear()+stStoreSet.nUnFixedTermSaveTime ,businessTime.GetMonth(),businessTime.GetDay(),businessTime.GetHour(),
						businessTime.GetMinute(),businessTime.GetSecond());
					CTimeSpan stSpan = cLocalDayTime - strSetTime;
					int nRealDay = stSpan.GetDays();
					if (nRealDay > 0)
					{
						m_pClientSource->ManageBusinessInfo(DBO_DEL,business);
						ST_ClientInfo stClientInfo;
						stClientInfo.strClientId = business.strClientId;
						if(m_pClientSource->QueryClientInfoByID(stClientInfo))
						{
							m_pClientSource->ManageClientInfo(DBO_DEL,stClientInfo);
						}
					}
				}
				else
				{
					CString strTime; 
					strTime.Format("%s",stProduce.strPublishEndTime);
					COleDateTime businessTime;
					businessTime.ParseDateTime(strTime);
					CTime strSetTime(businessTime.GetYear() + stStoreSet.nFixedTermSaveTime ,businessTime.GetMonth(),businessTime.GetDay(),businessTime.GetHour(),
						businessTime.GetMinute(),businessTime.GetSecond());
					CTimeSpan stSpan = cLocalDayTime - strSetTime;
					int nRealDay = stSpan.GetDays();
					if (nRealDay > 0)
					{
						m_pClientSource->ManageBusinessInfo(DBO_DEL,business);
						ST_ClientInfo stClientInfo;
						stClientInfo.strClientId = business.strClientId;
						if(m_pClientSource->QueryClientInfoByID(stClientInfo))
						{
							m_pClientSource->ManageClientInfo(DBO_DEL,stClientInfo);
						}
					}
				}
			}
		}
		else if (business.nMarkerType == 31 || business.nMarkerType == 32)
		{
			ST_ProduceInfo stMarkCancelProduce;
			if (business.strProduceId == "")
			{
				CString strTime; 
				strTime.Format("%s",business.strDateTime);
				COleDateTime businessTime;
				businessTime.ParseDateTime(strTime);
				CTime strDelFileDateOnUnFixedTerm(businessTime.GetYear()+stStoreSet.nUnFixedTermSaveTime,businessTime.GetMonth(),businessTime.GetDay(),businessTime.GetHour(),
					businessTime.GetMinute(),businessTime.GetSecond());

				CString strTime1; 
				strTime1.Format("%s",business.strOffDisputeTime);
				COleDateTime businessTime1;
				businessTime1.ParseDateTime(strTime1);
				CTime strDelFileDateOnMarkCancel(businessTime1.GetYear()+stStoreSet.nMarkCanceledSaveTime,businessTime1.GetMonth(),businessTime1.GetDay(),businessTime1.GetHour(),
					businessTime1.GetMinute(),businessTime1.GetSecond());

				CTimeSpan stSpan = strDelFileDateOnMarkCancel - strDelFileDateOnUnFixedTerm;
				int nCompareDay = stSpan.GetDays();
				CTime strDelFileDate  = nCompareDay > 0 ? strDelFileDateOnMarkCancel : strDelFileDateOnUnFixedTerm;
				
				CTimeSpan stRealSpan = cLocalDayTime - strDelFileDate;
				int nRealDay = stRealSpan.GetDays();
				if (nRealDay > 0)
				{				
					m_pClientSource->ManageBusinessInfo(DBO_DEL,business);
					ST_ClientInfo stClientInfo;
					stClientInfo.strClientId = business.strClientId;
					if(m_pClientSource->QueryClientInfoByID(stClientInfo))
					{
						m_pClientSource->ManageClientInfo(DBO_DEL,stClientInfo);
					}
				}
			}
			if(business.strProduceId != "" && m_pClientSource->QueryProduceInfoById(business.strProduceId,stMarkCancelProduce))
			{
				if(stMarkCancelProduce.nType == 1)
				{ 
					CString strTime; 
					strTime.Format("%s",business.strDateTime);
					COleDateTime businessTime;
					businessTime.ParseDateTime(strTime);
					CTime strDelFileDateOnUnFixedTerm(businessTime.GetYear()+stStoreSet.nUnFixedTermSaveTime,businessTime.GetMonth(),businessTime.GetDay(),businessTime.GetHour(),
						businessTime.GetMinute(),businessTime.GetSecond());

					CString strTime1; 
					strTime1.Format("%s",business.strOffDisputeTime);
					COleDateTime businessTime1;
					businessTime1.ParseDateTime(strTime1);
					CTime strDelFileDateOnMarkCancel(businessTime1.GetYear()+stStoreSet.nMarkCanceledSaveTime,businessTime1.GetMonth(),businessTime1.GetDay(),businessTime1.GetHour(),
						businessTime1.GetMinute(),businessTime1.GetSecond());

					CTimeSpan stSpan = strDelFileDateOnMarkCancel - strDelFileDateOnUnFixedTerm;
					int nCompareDay = stSpan.GetDays();
					CTime strDelFileDate  = nCompareDay > 0 ? strDelFileDateOnMarkCancel : strDelFileDateOnUnFixedTerm;

					CTimeSpan stRealSpan = cLocalDayTime - strDelFileDate;
					int nRealDay = stRealSpan.GetDays();
					if (nRealDay > 0)
					{
						m_pClientSource->ManageBusinessInfo(DBO_DEL,business);
						ST_ClientInfo stClientInfo;
						stClientInfo.strClientId = business.strClientId;
						if(m_pClientSource->QueryClientInfoByID(stClientInfo))
						{
							m_pClientSource->ManageClientInfo(DBO_DEL,stClientInfo);
						}
					}
				}
				else
				{
					CString strTime; 
					strTime.Format("%s",stMarkCancelProduce.strPublishEndTime);
					COleDateTime businessTime;
					businessTime.ParseDateTime(strTime);
					CTime strDelFileDateOnUnFixedTerm(businessTime.GetYear()+stStoreSet.nFixedTermSaveTime,businessTime.GetMonth(),businessTime.GetDay(),businessTime.GetHour(),
						businessTime.GetMinute(),businessTime.GetSecond());

					CString strTime1; 
					strTime1.Format("%s",business.strOffDisputeTime);
					COleDateTime businessTime1;
					businessTime1.ParseDateTime(strTime1);
					CTime strDelFileDateOnMarkCancel(businessTime1.GetYear()+stStoreSet.nMarkCanceledSaveTime,businessTime1.GetMonth(),businessTime1.GetDay(),businessTime1.GetHour(),
						businessTime1.GetMinute(),businessTime1.GetSecond());

					CTimeSpan stSpan = strDelFileDateOnMarkCancel - strDelFileDateOnUnFixedTerm;
					int nCompareDay = stSpan.GetDays();
					CTime strDelFileDate  = nCompareDay > 0 ? strDelFileDateOnMarkCancel : strDelFileDateOnUnFixedTerm;

					CTimeSpan stRealSpan = cLocalDayTime - strDelFileDate;
					int nRealDay = stRealSpan.GetDays();
					if (nRealDay > 0)
					{
						m_pClientSource->ManageBusinessInfo(DBO_DEL,business);
						ST_ClientInfo stClientInfo;
						stClientInfo.strClientId = business.strClientId;
						if(m_pClientSource->QueryClientInfoByID(stClientInfo))
						{
							m_pClientSource->ManageClientInfo(DBO_DEL,stClientInfo);
						}
					}
				}
			}
		}
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
ISOC_BOOL XhBFISClientDataTrafficImp::HandleDelBusinessByVideoEndTime(vector<ST_BusinessInfo>& vecBusiness, ST_StoreSet& stStoreSet)
{
	CTime cLocalDayTime = CTime::GetCurrentTime();
	if (!vecBusiness.empty())
	{
		for (auto item = vecBusiness.begin(); item != vecBusiness.end(); item++)
		{
			if(item->strExtendedInfo1 == "")
			{
				continue;
			}
			CString strTime;
			strTime.Format("%s", item->strExtendedInfo1);
			COleDateTime businessTime;
			businessTime.ParseDateTime(strTime);
			CTime strEndTime;
			if (item->nMarkerType == 12  || item->nMarkerType == 21 || item->nMarkerType == 11)
			{
				CTime strSetTime(businessTime.GetYear()+ stStoreSet.nMarkCanceledSaveTime, businessTime.GetMonth(), businessTime.GetDay(), businessTime.GetHour(),
					businessTime.GetMinute(), businessTime.GetSecond());
				strEndTime = strSetTime;
			}
			else
			{
				CTime strSetTime(businessTime.GetYear(), businessTime.GetMonth(), businessTime.GetDay(), businessTime.GetHour(),
					businessTime.GetMinute(), businessTime.GetSecond());
				strEndTime = strSetTime;
			}
			CTimeSpan stSpan = cLocalDayTime - strEndTime;
			int nRealDay = stSpan.GetDays();
			if (nRealDay >= 0)
			{
				m_pClientSource->ManageBusinessInfo(DBO_DEL, *item);
				ST_ClientInfo stClientInfo;
				stClientInfo.strClientId = item->strClientId;
				if (m_pClientSource->QueryClientInfoByID(stClientInfo))
				{
					m_pClientSource->ManageClientInfo(DBO_DEL, stClientInfo);
				}
			}
			
		}
	}
	return TRUE;
}
ISOC_VOID XhBFISClientDataTrafficImp::Run()
{
	while(!m_bCheckUnFinishEmp)
	{
		Sleep(60 * 1000);
		vector<ST_BusinessInfo> vecAllBusiness;
		vector<ST_BusinessFileInfo> vecBusinessFile;
		vector<ST_BusinessRelateInfo> vecBusinessRelate;
		ST_BusinessQueryParam stBusinessQueryParam;
		stBusinessQueryParam.strStartTime = "2000-01-01 01:01:01";
		CTime time = CTime::GetCurrentTime();
		CString strTime1 = time.Format("%Y-%m-%d %H:%M:%S");
		stBusinessQueryParam.strEndTime = strTime1;
		stBusinessQueryParam.nPageSize = 1000;
		stBusinessQueryParam.nMarkerType = -1;
		ST_StoreSet stStoreSet;
		PraseGetKeyValueData(stStoreSet);
		TimingDelOperateLog(stStoreSet.nOperateLogSaveTime);
		int nCount = 0;
		ST_BusinessFileInfo stBusinessFileInfo;
		stBusinessFileInfo.nType = 5;
		vecBusinessFile.push_back(stBusinessFileInfo);
		while(m_pClientSource->QueryBusinessInfoByCondition(stBusinessQueryParam, vecAllBusiness, nCount, vecBusinessFile, vecBusinessRelate))
		{	
			stBusinessQueryParam.nPageIndex++;
			if (stBusinessQueryParam.nPageIndex > nCount/stBusinessQueryParam.nPageSize)
			{
				break;
			}
		}	
		HandleDelBusinessByVideoEndTime(vecAllBusiness, stStoreSet);
		//string strNull;
		/*if (m_pCommunicateSource)
		{
		m_pCommunicateSource->AddNotifyMsg(DBO_QUERY,IBFIS_MSG_CLIENT_NOTIFY_DISKANDCONNECT,strNull);
		}*/

		/*int nDay = 0;
		vector<ST_BusinessInfo> vecBusiness;
		vector<ST_BusinessInfo> vecAllBusiness;
		vector<ST_BusinessFileInfo> vecBusinessFile;
		vector<ST_BusinessRelateInfo> vecBusinessRelate;
		if (!m_pClientSource)
		{
			DISPLAY_LOG("服务端模块", "查询业务失败", "Client对象为空", "", 0);
		}       
		int nInfoCount = 0;
		if (m_pClientSource->QueryBusinessInfoUnFinished(vecBusiness, nInfoCount, vecBusinessFile, vecBusinessRelate) != QueryFail)
		{
			CTime cLocalDayTime = CTime::GetCurrentTime();
			for each(auto business in vecBusiness)
			{
				CString strTime; 
				strTime.Format("%s",business.strDateTime);
				COleDateTime businessTime;
				businessTime.ParseDateTime(strTime);
				CTime strSetTime(businessTime.GetYear(),businessTime.GetMonth(),businessTime.GetDay(),businessTime.GetHour(),
					businessTime.GetMinute(),businessTime.GetSecond());
				CTimeSpan stSpan = cLocalDayTime - strSetTime;
				int nRealDay = stSpan.GetDays();	
				if (nRealDay - stStoreSet.nNeedAddInforSaveTime > 0)
				{
					m_pClientSource->ManageBusinessInfo(DBO_DEL,business);
					ST_ClientInfo stClientInfo;
					stClientInfo.strClientId = business.strClientId;
					if(m_pClientSource->QueryClientInfoByID(stClientInfo))
					{
						m_pClientSource->ManageClientInfo(DBO_DEL,stClientInfo);
					}
				}
			}
		}
		ST_BusinessQueryParam stBusinessQueryParam;
		stBusinessQueryParam.strStartTime = "2000-01-01 01:01:01";
		CTime time = CTime::GetCurrentTime(); 
		CString strTime1 = time.Format("%Y-%m-%d %H:%M:%S");
		stBusinessQueryParam.strEndTime = strTime1;
		stBusinessQueryParam.nPageSize = 1000;
		stBusinessQueryParam.nMarkerType = -1;
		int nCount = 0;
		if (m_pClientSource->QueryBusinessInfoByCondition(stBusinessQueryParam,vecAllBusiness,nCount,vecBusinessFile,vecBusinessRelate))
		{
			HandleUnFixedTermBusiness(vecAllBusiness,stStoreSet);
		}*/
		Sleep(100 * 60 * 1000);
	}
}
ISOC_BOOL XhBFISClientDataTrafficImp::PraseGetKeyValueData(ST_StoreSet& stStoreSet)
{
	STRY;
	if (m_pClientSource)
	{
		vector<ST_KeyValueInfo> vecKeyValueInfo;
		if (m_pClientSource->QueryKeyValueInfoByTypeAndCode("StorageSetting","",vecKeyValueInfo) > 0)
		{
			if (vecKeyValueInfo.empty())
			{
				return FALSE;
			}
			if (vecKeyValueInfo[0].strValue == "")
			{
				return FALSE;
			}
			CString strxml;
			strxml.Format("%s",vecKeyValueInfo[0].strValue.c_str());
			iCMSP_XmlParser XmlParser;
			XmlParser.SetDoc(strxml, strxml.GetLength());
			if (XmlParser.FindElem("StoreSet"))
			{
				XmlParser.IntoElem();
				if (XmlParser.FindElem("FixedTermSaveTime"))
				{
					stStoreSet.nFixedTermSaveTime = XmlParser.GetDataInt();
				}
				if (XmlParser.FindElem("UnFixedTermSaveTime"))
				{
					stStoreSet.nUnFixedTermSaveTime = XmlParser.GetDataInt();
				}
				/*if (XmlParser.FindElem("NeedAddInforSaveTime"))
				{
					stStoreSet.nNeedAddInforSaveTime = XmlParser.GetDataInt();
				}*/
				if (XmlParser.FindElem("MarkCanceledSaveTime"))
				{
					stStoreSet.nMarkCanceledSaveTime = XmlParser.GetDataInt();
				}
			}
			vecKeyValueInfo.clear();
		} 
		if (m_pClientSource->QueryKeyValueInfoByTypeAndCode("LogSetting","",vecKeyValueInfo) > 0)
		{
			if (vecKeyValueInfo.empty())
			{
				TTRACE("没有配置需要查询的磁盘");
			}
			if (vecKeyValueInfo[0].strValue == "")
			{
				TTRACE("没有配置需要查询的磁盘");
			}
			CString strxml;
			strxml.Format("%s",vecKeyValueInfo[0].strValue.c_str());
			iCMSP_XmlParser XmlParser;
			XmlParser.SetDoc(strxml, strxml.GetLength());
			if (XmlParser.FindElem("LogSaveSet"))
			{
				XmlParser.IntoElem();
				if (XmlParser.FindElem("LogSaveDay"))
				{
					stStoreSet.nOperateLogSaveTime = XmlParser.GetDataInt();
				} 
			}
		} 
		vecKeyValueInfo.clear();
	}
	return TRUE;
	SCATCH;
	return FALSE;
}

void XhBFISClientDataTrafficImp::DisConnect(UINT64 fromAddr)
{
	char szMsg[255] = {0};
	string strUrl;
	string strName;
	STRY;
	Poco::FastMutex::ScopedLock myLock(m_csLockClientContext);
	auto iter = m_mapClientContext.find(fromAddr);
	if (iter != m_mapClientContext.end())
	{
		strName = iter->second.stInfo.strName;
		strUrl = iter->second.strUrl;
		m_mapClientContext.erase(iter);
	}
	//for (map<string,UINT64>::iterator iter1 = m_mapUserName.begin(); iter1 != m_mapUserName.end(); iter1++)
	//{
	//	if (iter1->second == fromAddr)
	//	{
	//		m_mapUserName.erase(iter1->first);
	//		break;
	//	}
	//}
	SCATCH;

	if (!strName.empty() && !strUrl.empty())
	{
		sprintf(szMsg, "用户[%s[%s] ]已退出", strName.c_str(), strUrl.c_str());
		DISPLAY_LOG("服务端模块", szMsg, "", "", 1);
	}
}

int XhBFISClientDataTrafficImp::OnRecvData(UINT64 fromAddr,DWORD_PTR& d)
{
	STRY;
	switch(d)
	{
	    case IBFIS_MSG_CLIENT_IS_ALIVE:
	    {
			if (m_pCommunicateSource)
				m_pCommunicateSource->DoSendData(reinterpret_cast<HANDLE>(fromAddr), DBO_INVAILED, d, "");
		    return 1;
	    }
	}
	return -1;
	SCATCH;
	return -1;
}
ISOC_BOOL XhBFISClientDataTrafficImp::GetDeviceInfo(vector<string>& vecDrives)	
{
	DWORD dw = ::GetLogicalDriveStrings(0, NULL);
	TCHAR* pAllDrivers = new TCHAR[dw];
	::GetLogicalDriveStrings(dw, pAllDrivers);
	LPCTSTR pDriver = pAllDrivers;
	DWORD DriverNum = 0;
	int nDriveType = 0;
	while(pDriver[0] != 0)
	{
		nDriveType = GetDriveType(pDriver);
		if(nDriveType == 4 || nDriveType == 3)
		{
			vecDrives.push_back(pDriver);
			DriverNum++;
		}
		pDriver = _tcschr(pDriver, 0) + 1;
	}
	delete[] pAllDrivers;
	return TRUE;		
}
int XhBFISClientDataTrafficImp::OnRecvData(UINT64 fromAddr,DWORD_PTR& d,std::string& s)
{
	STRY;
	char szMsg[255] = {0};
	string strInfo = _T("");
	{
		Poco::FastMutex::ScopedLock myLock(m_csLockClientContext);
		GetEmployeeName(fromAddr,strInfo);
	}
	
	//sprintf(szMsg,"收到用户[%s]发来的操作[%s]",strInfo.c_str(),Cmd2Msg(d).c_str());
	//DISPLAY_LOG("服务端模块",szMsg,"","",1);
	TTRACE("[服务端模块]收到用户[%s]发来的操作[%d]\r\n",strInfo.c_str(), d);
	switch(d)
	{
	case IBFIS_MSG_CLIENT_ADD_BRANCHINFO:
	case IBFIS_MSG_CLIENT_UPDATE_BRANCHINFO:
	case IBFIS_MSG_CLIENT_DEL_BRANCHINFO:
		{
			STRY;
			BFIS::BranchInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_BranchInfo stInfo(msg);
				DBOperType enType;
				enType = Cmd2DataOperType(d);
				sprintf(szMsg,"执行操作[%s]",Cmd2Msg(d).c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",1);
				if(m_pClientSource->ManageBranchInfo(enType,stInfo) > 0)
				{
					m_pCommunicateSource->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_BRANCHINFO,s);
					//更新提前同步上来没有ParentId的网点信息
					vector<ST_BranchInfo> vecInfo;
					m_pClientSource->GetBranchInfo(vecInfo);
					for each(auto branchinfo in vecInfo)
					{
						if((m_strLocalBranchId != "" || m_strLocalBranchId == "" && m_pClientSource && 
							m_pClientSource->QueryLocalBranchId(m_strLocalBranchId)) && branchinfo.strParentId != "")
						{
							//vector<ST_BranchInfo> vecBranchInfo;
							//branchinfo.strParentId == m_strLocalBranchId;
							m_pClientSource->ManageBranchInfo(DBO_UPDATE,branchinfo);
						}
					}
					return 1;
				}
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_PRODUCEINFO:
	case IBFIS_MSG_CLIENT_UPDATE_PRODUCEINFO:
	case IBFIS_MSG_CLIENT_DEL_PRODUCEINFO:
		{
			STRY;
			BFIS::ProduceInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_ProduceInfo stInfo(msg);
				DBOperType enType;
				enType = Cmd2DataOperType(d);
				sprintf(szMsg,"执行操作[%s]",Cmd2Msg(d).c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",1);
				if(m_pClientSource->ManageProduceInfo(enType,stInfo) > 0)
				{
					m_pCommunicateSource->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_PRODUCEINFO,s);
					return 1;
				}
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_SET_USERMAPINFO:
		{
			STRY;
			BFIS::UserMapInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_UserMapInfo stInfo(msg);
				sprintf(szMsg,"执行操作[%s]",Cmd2Msg(d).c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",1);
				//1.根据EmployeeId删除
				if (!m_pClientSource || !m_pClientSource->DelUsermapByEmployeeId(stInfo.strEmployeeId))
				{
					sprintf(szMsg,"执行操作[%s]失败",Cmd2Msg(d).c_str());
					DISPLAY_LOG("服务端模块",szMsg,"根据员工Id删除用户关系映射信息失败","",0);
					return -1;
				}
				m_pCommunicateSource->AddNotifyMsg(DBO_DEL,IBFIS_MSG_CLIENT_NOTIFY_USERMAPINFO,s);
				//2.删除项或添加项
				if(stInfo.strUserMapInfoId == _T("") ||stInfo.strSocUsername == _T("") || stInfo.strSocPassword == _T("")
					|| m_pClientSource->ManageUsermapInfo(DBO_ADD,stInfo) > 0)
				{
					m_pCommunicateSource->AddNotifyMsg(DBO_ADD,IBFIS_MSG_CLIENT_NOTIFY_USERMAPINFO,s);
					return 1;
				}
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_ROLEINFO:
	case IBFIS_MSG_CLIENT_UPDATE_ROLEINFO:
	case IBFIS_MSG_CLIENT_DEL_ROLEINFO:
		{
			STRY;
			BFIS::RoleInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_RoleInfo stInfo(msg);			
				DBOperType enType;
				enType = Cmd2DataOperType(d);
				sprintf(szMsg,"执行操作[%s]",Cmd2Msg(d).c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",1);
				if(m_pClientSource->ManageRoleInfo(enType,stInfo) > 0)
				{
					m_pCommunicateSource->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_ROLEINFO,s);
					return 1;
				}						
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_PURVIEWINFO:
	case IBFIS_MSG_CLIENT_UPDATE_PURVIEWINFO:
	case IBFIS_MSG_CLIENT_DEL_PURVIEWINFO:
		{
			STRY;
			BFIS::PurviewInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_PurviewInfo stInfo(msg);
				DBOperType enType;
				enType = Cmd2DataOperType(d);
				sprintf(szMsg,"执行操作[%s]",Cmd2Msg(d).c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",1);
				if(m_pClientSource->ManagePurviewInfo(enType,stInfo) > 0)
				{
					m_pCommunicateSource->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_PURVIEWINFO,s);
					return 1;
				}
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_EMPLOYEEINFO:
	case IBFIS_MSG_CLIENT_UPDATE_EMPLOYEEINFO:
	case IBFIS_MSG_CLIENT_DEL_EMPLOYEEINFO:
		{
			STRY;
			BFIS::EmployeeInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_EmployeeInfo stInfo(msg);		
				DBOperType enType;
				enType = Cmd2DataOperType(d);
				sprintf(szMsg,"执行操作[%s]",Cmd2Msg(d).c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",1);
				if(stInfo.strBranchId != m_strLocalBranchId && stInfo.strExtendedInfo2.compare("100") != 0) //"100"支行管理员只添加到总行
				{
					DBOperType enType;
					enType = Cmd2DataOperType(d);
					m_pCommunicateSource->AddNotifyMsg(enType,MSG_ISSUED_EMPLOYEEINFO,s);
				}
				if(m_pClientSource->ManageEmployeeInfo(enType,stInfo) > 0)
				{
					m_pCommunicateSource->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEINFO,s);
					return 1;
				}			
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_CLIENTINFO:
	case IBFIS_MSG_CLIENT_UPDATE_CLIENTINFO:
	case IBFIS_MSG_CLIENT_DEL_CLIENTINFO:
		{
			STRY;
			BFIS::ClientInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_ClientInfo stInfo(msg);
				DBOperType enType;
				enType = Cmd2DataOperType(d);
				sprintf(szMsg,"执行操作[%s]",Cmd2Msg(d).c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",1);
				if(m_pClientSource->ManageClientInfo(enType,stInfo) > 0)
				{
					m_pCommunicateSource->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_CLIENTINFO,s);
					return 1;
				}
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_SCRIPTINFO:
	case IBFIS_MSG_CLIENT_UPDATE_SCRIPTINFO:
	case IBFIS_MSG_CLIENT_DEL_SCRIPTINFO:
		{
			STRY;
			BFIS::ScriptInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_ScriptInfo stInfo(msg);
				DBOperType enType;
				enType = Cmd2DataOperType(d);
				sprintf(szMsg,"执行操作[%s]",Cmd2Msg(d).c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",1);
				if(m_pClientSource->ManageScriptInfo(enType,stInfo) > 0)
				{
					m_pCommunicateSource->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_SCRIPTINFO,s);
					return 1;
				}
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_OPERATELOGINFO:
	case IBFIS_MSG_CLIENT_UPDATE_OPERATELOGINFO:
	case IBFIS_MSG_CLIENT_DEL_OPERATELOGINFO:
		{
			STRY;
			BFIS::OperateLogInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_OperateLogInfo stInfo(msg);
				DBOperType enType;
				enType = Cmd2DataOperType(d);
				sprintf(szMsg,"执行操作[%s]",Cmd2Msg(d).c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",1);
				if(m_pClientSource->ManageOperateLogInfo(enType,stInfo) > 0)
				{
					//m_pCommunicateSource->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_OPERATELOGINFO,s);
					return 1;
				}
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_SUPEREMPLOYEE:
		{
			STRY;
			std::string strLocalBranchId;
			s = "";
			if (!m_pClientSource || !m_pClientSource->QueryLocalBranchId(strLocalBranchId))
			{
				return -1;
			}
// 			if (bRet)
// 			{
// 				s = strLocalBranchId;
// 				return 0;
// 			}
			ST_EmployeeInfo stEmployeeInfo;
			stEmployeeInfo.strBranchId = strLocalBranchId;
			if (m_pClientSource && !m_pClientSource->QueryEmployeeInfoByRoleLevel(-1,stEmployeeInfo))//不存在超级管理员
			{
				DISPLAY_LOG("数据库模块","查询超级管理员失败","","",0);
				s = stEmployeeInfo.strBranchId;
				return 0;
			}
			else
			{
				//std::string strEmployeeInfo;
				if(stEmployeeInfo.ConvertToString(s))
				{
					return 1;
				}
				else
				{
					DISPLAY_LOG("数据库模块","序列化管理员用户失败","","",0);
					return 0;
				}
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_OPERATELOGINFO:
	case IBFIS_MSG_CLIENT_QUERY_DISKANDCONNECT:
		{
			STRY;
			ST_CallBackInfo info;
			info.pCallBackAddr = this;
			info.pSelfCallback = [this](ST_CallBackInfo tskInfo)->int
			{
				if (tskInfo.vecDwordArry.size() != 2 || tskInfo.vecStrArry.size() != 1)
					return ISOC_ERR_FAILED;
				HANDLE hVaule = (HANDLE)(tskInfo.vecDwordArry[0]);
				DWORD_PTR cmd = tskInfo.vecDwordArry[1];
				int nRet = 0;
				if (m_pCommunicateSource)
					nRet = m_pCommunicateSource->DoSendData(hVaule, DBO_QUERY, cmd, tskInfo.vecStrArry);
				if (nRet <= 0)
					SFTRACE("OnRecvData", "查询任务[%d] 处理状态[%d] \r\n", static_cast<int>(cmd), nRet);
			};
				
			info.bIsQueue = false;
			info.nCallIdx = fromAddr;
			info.vecDwordArry.push_back(fromAddr);
			if (IBFIS_MSG_CLIENT_QUERY_DISKANDCONNECT == d)
				d = IBFIS_MSG_CLIENT_NOTIFY_DISKANDCONNECT;
			info.vecDwordArry.push_back(d);
			info.vecStrArry.push_back(s);
			m_pCallbackManager->AddCallBack(info, __FUNCTION__);
			return 1;
			SCATCH;
			return -1;
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_DISKCODEANDCOUNT:
		{
			vector<string> vecAllDisk;
			GetDeviceInfo(vecAllDisk);
			iCMSP_XmlParser XmlParser;
			XmlParser.AddElem("DiskSet");
			for (auto iter = vecAllDisk.begin(); iter!=vecAllDisk.end(); ++iter )
			{
				XmlParser.AddChildElem("Drive",(LPCTSTR)iter->c_str());
			}
			CString strXml = XmlParser.GetDoc();
			s = strXml;
			if (s == "")
			{
				return -1;
			}
			return 1;
		}
		break;
	case IBFIS_MSG_CLIENT_IS_ALIVE:
		{
			s = boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time());
			int nRet = -1;
			if (m_pCommunicateSource)
				nRet = m_pCommunicateSource->DoSendData((HANDLE)fromAddr, DBO_QUERY, IBFIS_MSG_CLIENT_IS_ALIVE, s);
			return nRet;
		}
		break;
	}
	sprintf(szMsg,"执行操作[%s]失败",Cmd2Msg(d).c_str());
	DISPLAY_LOG("服务端模块",szMsg,"","",0);
	return -1;
	SCATCH;
	return -1;
}

int XhBFISClientDataTrafficImp::OnRecvData(UINT64 fromAddr,DWORD_PTR& d1,std::vector<std::string>& v1)
{
	STRY;
	char szMsg[255] = {0};
	string strInfo = _T("");
	{
		Poco::FastMutex::ScopedLock myLock(m_csLockClientContext);
		GetEmployeeName(fromAddr,strInfo);
	}
	//sprintf(szMsg,"收到用户[%s]发来的操作[%s]",strInfo.c_str(),Cmd2Msg(d1).c_str());
	//DISPLAY_LOG("服务端模块",szMsg,"","",1);
	TTRACE("[服务端模块]收到用户[%s]发来的操作[%d]\r\n",strInfo.c_str(), d1);
	switch(d1)
	{
	case IBFIS_MSG_CLIENT_LOGIN_2_SERVER:
	case IBFIS_MSG_CLIENT_GET_BRANCHINFO:
	case IBFIS_MSG_CLIENT_GET_PRODUCEINFO:
	case IBFIS_MSG_CLIENT_GET_PURVIEWINFO:
	case IBFIS_MSG_CLIENT_GET_ROLEINFO:
	case IBFIS_MSG_CLIENT_GET_ROLEPURVIEWINFO:
	case IBFIS_MSG_CLIENT_GET_EMPLOYEEINFO:
	case IBFIS_MSG_CLIENT_GET_EMPLOYEEPURVIEWINFO:
	case IBFIS_MSG_CLIENT_GET_USERMAPINFO:
	case IBFIS_MSG_CLIENT_GET_CLIENTINFO:
	case IBFIS_MSG_CLIENT_GET_SCRIPTINFO:
		{
			STRY;
			if (m_pCallbackManager)
			{
				ST_CallBackInfo info;
				info.pSelfCallback = [this, strInfo](ST_CallBackInfo tskInfo)->int
				{
#pragma region login task handle
					std::string strResult;
					if (tskInfo.vecDwordArry.size() <= 1)
						return ISOC_ERR_FAILED;
					HANDLE hVaule = (HANDLE)(tskInfo.vecDwordArry[0]);
					DWORD_PTR cmd = tskInfo.vecDwordArry[1];
					int nRet = 0;
					IBFISSerializeDataMemoryModel* pEmployeepurviewInfo = nullptr;

					switch (cmd)
					{
					case IBFIS_MSG_CLIENT_LOGIN_2_SERVER:
						{
							char szMsg[255] = {0};
							sprintf(szMsg,"收到用户[%s]发来登录消息",strInfo.c_str());
							DISPLAY_LOG("服务端模块",szMsg,"","",1);
							nRet = ClientLogin2(tskInfo.vecDwordArry[0], tskInfo.vecStrArry);
						}
						break;
					case IBFIS_MSG_CLIENT_GET_BRANCHINFO:
						{
							nRet = ClientGetBranchInfo(tskInfo.vecStrArry);
						}
						break;
					case IBFIS_MSG_CLIENT_GET_PRODUCEINFO:
						{
							nRet = ClientGetProduceInfo(tskInfo.vecStrArry);
						}
						break;
					case IBFIS_MSG_CLIENT_GET_PURVIEWINFO:
						{
							nRet = ClientGetPurviewInfo(tskInfo.vecStrArry);
						}
						break;
					case IBFIS_MSG_CLIENT_GET_ROLEINFO:
						{
							nRet = ClientGetRoleInfo(tskInfo.vecStrArry);
						}
						break;
					case IBFIS_MSG_CLIENT_GET_ROLEPURVIEWINFO:
						{
							nRet = ClientGetPolepurviewInfo(tskInfo.vecStrArry);
						}
						break;
					case IBFIS_MSG_CLIENT_GET_EMPLOYEEINFO:
						{
							nRet = ClientGetEmployeeInfo(tskInfo.vecStrArry);
						}
						break;
					case IBFIS_MSG_CLIENT_GET_EMPLOYEEPURVIEWINFO:
						{
							
							//nRet = ClientGetEmployeepurviewInfo(tskInfo.vecStrArry, vecData);
							nRet = ClientGetEmployeepurviewInfo(tskInfo.vecStrArry);
							if (nRet <= 0)
							{
								tskInfo.vecStrArry.clear();
								tskInfo.vecStrArry.push_back("获取员工权限信息失败");
							}
						}
						break;
					case IBFIS_MSG_CLIENT_GET_USERMAPINFO:
						{
							nRet = ClientGetUserMapInfo(tskInfo.vecStrArry);
						}
						break;
					case IBFIS_MSG_CLIENT_GET_CLIENTINFO:
						{
							nRet = ClientGetClientInfo(tskInfo.vecStrArry);
						}
						break;
					case IBFIS_MSG_CLIENT_GET_SCRIPTINFO:
						{
							nRet = ClientGetScriptInfo(tskInfo.vecStrArry);
						}
						break;
					}

					DWORD dwTimeProcessTime = GetTickCount();
					if (nRet <= 0)
					{
						std::string strDes;
						if (tskInfo.vecStrArry.size() > 0)
							strDes = tskInfo.vecStrArry[0];
						SFTRACE("OnRecvData", "登录命令[%d] 处理失败[%d] 错误描述[%s] \r\n", static_cast<int>(cmd), nRet, strDes.c_str());
					}
					
					DWORD_PTR result = static_cast<DWORD_PTR>(nRet);
					if (m_pCommunicateSource)
					{
						if (nRet <= 0)
						{
							nRet = m_pCommunicateSource->DoSendData(hVaule, (DBOperType)0, cmd, tskInfo.vecStrArry, result);
							if (nRet <= 0)
							{
								SFTRACE("OnRecvData", " -- id:%d  handle:%u  send state:%d  \r\n", cmd, hVaule, nRet);
							}
						}
						else
						{
							if (nullptr == pEmployeepurviewInfo)
								nRet = m_pCommunicateSource->DoSendData(hVaule, (DBOperType)0, cmd, tskInfo.vecStrArry, result);
							else
							{
								iCMSP_ReadLock readLock(*pEmployeepurviewInfo->GetWRLock(), __FUNCTION__);
								int nPacketSize = pEmployeepurviewInfo->GetPacketCount();
								for (int i = 0; i < nPacketSize; ++i)
								{
									BYTE *pData = nullptr;
									int nDataSize = 0;
									int nTotalSize = 0;
									int nRet = pEmployeepurviewInfo->GetDataPacket(i, &pData, nDataSize, nTotalSize);
									if (nRet > 0 && pData)
										nRet = m_pCommunicateSource->DoSendData(hVaule, (DBOperType)0, cmd, pData, nDataSize, result);
									if (nRet <= 0)
									{
										SFTRACE("OnRecvData", " -- id:%d  handle:%u  send state:%d  \r\n", cmd, hVaule, nRet);
									}
								}
							}
							
						}
					}

					return nRet;
#pragma endregion login task handle
				};

				info.pCallBackAddr = this;
				info.vecStrArry = v1;
				info.bIsQueue = true;
				info.nCallIdx = fromAddr;
				info.vecDwordArry.push_back(fromAddr);
				info.vecDwordArry.push_back(d1);
				m_pCallbackManager->AddCallBack(info, __FUNCTION__);
				return 1;
			}
			else
			{
				sprintf(szMsg,"收到用户[%s]发来的操作[%s] 任务管理实例化失败",strInfo.c_str(),Cmd2Msg(d1).c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",1);
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_GET_BUSINESSINFO:
		{
			vector<ST_BusinessInfo> vecInfo;
			if (m_pClientSource && m_pClientSource->GetBusinessInfo(vecInfo))
			{
				for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; iter ++)
				{
					std::string strInfo;
					bool bSuccess = iter->ConvertToString(strInfo);
					if(!bSuccess)
					{
						char szMsg[255] = {0};
						sprintf(szMsg,"业务信息[%s]串行化失败",iter->strBusinessInfoId.c_str());
						DISPLAY_LOG("服务端模块",szMsg,"","",0);
					}
					else
					{
						v1.push_back(strInfo);
					}
				}
				if(!v1.empty() || vecInfo.empty())
				{
					return 1;
				}
			}
			else
			{
				string strError = _T("获取业务信息失败");
				v1.push_back(strError);
			}
		}
		break;
	case IBFIS_MSG_CLIENT_GET_BUSINESSFILEINFO:
		{
			vector<ST_BusinessFileInfo> vecInfo;
			if (m_pClientSource && m_pClientSource->GetBusinessFileInfo(vecInfo))
			{
				for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; iter ++)
				{
					std::string strInfo;
					bool bSuccess = iter->ConvertToString(strInfo);
					if(!bSuccess)
					{
						char szMsg[255] = {0};
						sprintf(szMsg,"业务文件信息[%s]串行化失败",iter->strRecordId.c_str());
						DISPLAY_LOG("服务端模块",szMsg,"","",0);
					}
					else
					{
						v1.push_back(strInfo);
					}
				}
				if(!v1.empty() || vecInfo.empty())
				{
					return 1;
				}	
			}
			else
			{
				string strError = _T("获取业务文件信息失败");
				v1.push_back(strError);
			}
		}
		break;
	case IBFIS_MSG_CLIENT_GET_BUSINESSRELATEINFO:
		{
			vector<ST_BusinessRelateInfo> vecInfo;
			if (m_pClientSource && m_pClientSource->GetBusinessRelateInfo(vecInfo))
			{
				for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; iter ++)
				{
					std::string strInfo;
					bool bSuccess = iter->ConvertToString(strInfo);
					if(!bSuccess)
					{
						char szMsg[255] = {0};
						sprintf(szMsg,"业务关联信息[%s]串行化失败",iter->strBusinessRelateInfoId.c_str());
						DISPLAY_LOG("服务端模块",szMsg,"","",0);
					}
					else
					{
						v1.push_back(strInfo);
					}
				}
				if(!v1.empty() || vecInfo.empty())
				{
					return 1;
				}	
			}
			else
			{
				string strError = _T("获取业务关联信息失败");
				v1.push_back(strError);
			}
		}
		break;
	case IBFIS_MSG_CLIENT_SET_ROLEPURVIEWINFO:
		{
			STRY;
			vector<std::string> vecInfo = v1;
			v1.clear();
			bool bDel = false;
			for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; ++iter)
			{
				BFIS::RolePurviewInfo msg;
				bool bSuccess = msg.ParseFromString(*iter);
				if (bSuccess)
				{
					ST_RolePurviewInfo stInfo(msg);
					if (!bDel)
					{
						if (!m_pClientSource || !m_pClientSource->DelRolePurviewByRoleId(stInfo.strRoleId))
						{
							return -1;
						}
						bDel = true;
						m_pCommunicateSource->AddNotifyMsg(DBO_DEL,IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO,*iter);
					}
					if(stInfo.strRoleInfoPurviewId != _T("") && stInfo.strPruviewInfoId != _T("") &&
						m_pClientSource->ManageRolePurviewInfo(DBO_ADD,stInfo) > 0)
					{
						v1.push_back(*iter);
					}
				}
				else
				{
					DISPLAY_LOG("服务端模块","设置用户权限","解析失败","",0);
					return -1;
				}
			}
			if(v1.empty() && bDel)
			{
				return 1;
			}
			if(!v1.empty() || vecInfo.empty())
			{
				m_pCommunicateSource->AddNotifyMsg(DBO_ADD,IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO,v1);
				return 1;
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_SET_EMPLOYEEPURVIEWINFO:
		{
			STRY;

			vector<std::string> vecInfo = v1;
			v1.clear();
			bool bDel = false;
			for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; ++iter)
			{
				BFIS::EmployeePurviewInfo msg;
				bool bSuccess = msg.ParseFromString(*iter);
				if (bSuccess)
				{
					ST_EmployeePurviewInfo stInfo(msg);
					if (!bDel)
					{
						int nHasData = 0;
						if (!m_pClientSource || !m_pClientSource->DelEmployeePurviewByEmployeeId(stInfo.strEmployeeId, nHasData))
						{
							return -1;
						}
						bDel = true;
						if (nHasData > 0)
							m_pCommunicateSource->AddNotifyMsg(DBO_DEL,IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEPURVIEWINFO,*iter);
					}
					if(stInfo.strEmployeePurviewId != _T("") && stInfo.strPurviewInfoId != _T("") && 
						m_pClientSource->ManageEmployeePurviewInfo(DBO_ADD,stInfo) > 0)
					{
						v1.push_back(*iter);
					}
				}
			}
			if(v1.empty() && bDel)
			{
				return 1;
			}
			if(!v1.empty()|| vecInfo.empty())
			{
				m_pCommunicateSource->AddNotifyMsg(DBO_ADD,IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEPURVIEWINFO,v1);
				return 1;
			}
			return 1;
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_SET_TRANSPARENTDATA:
		{
			STRY;
			if (m_pClientSource && m_pClientSource->SetTransparentData(v1[0],v1[1],v1[2]) > 0)
			{
				m_pCommunicateSource->AddNotifyMsg(DBO_ADD,IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO,v1);
				return 1;
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_DEL_TRANSPARENTDATA:
		{
			STRY;
			if (m_pClientSource && m_pClientSource->DelTransparentData(v1[0],v1[1],v1[2]) > 0)
			{
				m_pCommunicateSource->AddNotifyMsg(DBO_DEL,IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO,v1);
				return 1;
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_GET_TRANSPARENTDATA:
		{
			STRY;
			vector<ST_KeyValueInfo> vecInfo;
			vector<std::string> vStr = v1;
			v1.clear();
			if (m_pClientSource && m_pClientSource->GetTransparentData(vStr[0],vStr[1],vStr[2],vecInfo) >= 0)
			{
				//
				int nIndex = 0;
				for (auto iter = vecInfo.begin() ; iter != vecInfo.end(); iter ++)
				{
					std::string strTemp = iter->strType;
					strTemp += ',';
					strTemp += iter->strCode;
					strTemp += ',';
					strTemp += iter->strValue;
					strTemp += ';';
					v1.push_back(strTemp);
				}
				if(!v1.empty() || vecInfo.empty())
				{
					return 1;
				}
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_CLIENTINFO:
		{
			STRY;
			if (v1.empty())
			{
				DISPLAY_LOG("服务端模块", "查询客户信息失败", "查询参数为空", "", 0);
				return -1;
			}

			vector<ST_ClientInfo> vecStInfo;
			vector<std::string> vecInfo = v1;
			ST_ClientInfo stInfo;
			int nType = atoi(vecInfo[0].c_str());
			int nCount = 0;
			switch (nType)
			{
			case 1:
			case 2:
				{
					nType = atoi(vecInfo[0].c_str());
					nCount = atoi(vecInfo[1].c_str());
					stInfo.strCredenitial = vecInfo[2];
					stInfo.strName = vecInfo[3];
					stInfo.strCredenitialsType = vecInfo[4];
					vecStInfo.push_back(stInfo);
					v1.clear();
					if (m_pClientSource && m_pClientSource->QueryClientInfoByCondition(nType, nCount, vecStInfo) >= 0)
					{
						for (auto iter = vecStInfo.begin(); iter != vecStInfo.end(); ++iter)
						{
							std::string strTemp;
							iter->ConvertToString(strTemp);
							v1.push_back(strTemp);
						}
						if (!v1.empty() || vecStInfo.empty())
						{
							return 1;
						}
					}
					break;
				}
			case 3:
				{
					std::string strCustomerId = vecInfo[1];
					iSOC_MonFactoryManagement fmt;
					IBFISDBOperation* pDBO = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
					if (pDBO)
					{
						stInfo.strClientId = strCustomerId;
						int nRet = pDBO->QueryClientInfoByID(stInfo);
						if (nRet < 0 || nRet == QuerySuccessWithoutResult)
						{
							//DISPLAY_LOG("服务端模块", "根据客户id查询客户信息失败", strCustomerId.c_str(), "", 0);
							return -2;
						}
						v1.clear();
						std::string strTemp;
						stInfo.ConvertToString(strTemp);
						v1.push_back(strTemp);
						return 1;
					}
				}
			default:
				{
					std::stringstream os;
					os << "未知的查询类型" << nType;
					DISPLAY_LOG("服务端模块", "查询客户信息失败", os.str().c_str(), "", 0);
				}
				break;
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_PRODUCEID:
		{
			STRY;
			auto iter = v1.begin();
			std::string strInfoId = *iter;
			int nCount = atoi((*(++iter)).c_str());
			v1.clear();
			std::map<std::string ,int> mapInfo;
			if (m_pClientSource && strInfoId != "" && m_pClientSource->QueryBusinessInfoByEmployeeIdAndCount(strInfoId,nCount,mapInfo)
				|| m_pClientSource && strInfoId == "" && m_pClientSource->QueryHotProduceIdByCount(nCount,mapInfo))
			{
				if(mapInfo.empty())
				{
					return 0;
				}
				for (auto iter = mapInfo.begin() ; iter != mapInfo.end() ; iter ++)
				{
					ST_ProduceIdQueryParam stInfo;
					stInfo.strInfoId = iter->first;
					stInfo.nCount = iter->second;
					std::string strTemp;
					if(stInfo.ConvertToString(strTemp))
					{
						v1.push_back(strTemp);
					}
				}
				if(!v1.empty())
				{
					return 1;
				}
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_MCSERVERINFO:
		{
			STRY;
			v1.clear();
			int nRet = -1;
			iSOC_MonFactoryManagement fmt;
			IBFISSyncClient* pClient = (IBFISSyncClient*)fmt.CreateObject(OBJECT_TYPE_BFISSYNC_CLIENT, "", __FUNCTION__);
			if (!pClient)
			{
				DISPLAY_LOG("备份模块", "初始化", "获取上级SMS信息失败,Client对象为空", "", 0);
				//return -1;
			}
			else
			{
				std::string strMCIp, strMCUser, strMCPwd, strPort;
				nRet = pClient->GetParentSMSInfo(strMCIp, strPort, strMCUser, strMCPwd);
				if (nRet <= 0)
				{
					//DISPLAY_LOG("备份模块", "初始化", "获取上级SMS信息失败", "", 0);
					//return -2;
				}
				else
				{
					DISPLAY_LOG("备份模块", "初始化", "获取上级SMS信息成功", "", 1);
					int sMCPort = atoi(strPort.c_str());

					std::string strParentBranchID, strParentBranchName, strParentPID;
					nRet = pClient->GetParentBranchInfo(strParentBranchID, strParentBranchName, strParentPID);
					if (nRet <= 0)
					{
						DISPLAY_LOG("备份模块", "初始化", "获取上级网点信息失败", "", 0);
						//return -2;
					}
					else
					{
						std::string strData;
						ST_MCServer parentInfo;
						parentInfo.strBranchID = strParentBranchID;
						parentInfo.strBranchName = strParentBranchName;
						parentInfo.strMCIP = strMCIp;
						parentInfo.sPort = sMCPort;
						parentInfo.strMCUserName = strMCUser;
						parentInfo.strMCUserPwd = strMCPwd;
						parentInfo.nIsLocal = 0;
						bool bSerilize = parentInfo.Convert2String(strData);
						if (bSerilize)
						{
							v1.push_back(strData);
						}
						else
						{
							DISPLAY_LOG("备份模块", "客户端获取SMS信息失败", "序列化上级SMS信息失败", "", 0);
						}
					}
				}
			}

			IBFISDBOperation* pDBO = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
			if (!pDBO)
			{
				DISPLAY_LOG("备份模块", "初始化", "获取本级网点信息失败,pDBO对象为空", "", 0);
				return -1;
			}

			ST_BranchInfo stCurrentBranchInfo;
			nRet = pDBO->GetLocalBranchInfo(stCurrentBranchInfo);
			if (nRet < 0/* || nRet == QuerySuccessWithoutResult*/)  //为空的话说明是刚搭建的环境，未注册
			{
				DISPLAY_LOG("备份模块", "初始化", "获取本级网点信息失败,查询结果为空", "", 0);
				return -1;
			}

			std::string strData;
			ST_MCServer currentInfo;
			iFVR_Configuration config;
			currentInfo.strBranchID = stCurrentBranchInfo.strBranchId;
			currentInfo.strBranchName = stCurrentBranchInfo.strName;
			currentInfo.strMCIP = config.GetString("SMS", "SMSIP");
			currentInfo.sPort = config.GetInt("SMS", "SMSPort");
			currentInfo.strMCUserName = config.GetString("SMS", "SMSUser");
			currentInfo.strMCUserPwd = config.GetString("SMS", "SMSPwd");
			currentInfo.nIsLocal = 1;
			bool bSerilize = currentInfo.Convert2String(strData);
			if (bSerilize)
			{
				v1.push_back(strData);
			}
			else
			{
				DISPLAY_LOG("备份模块", "客户端获取SMS信息失败", "序列化本级SMS信息失败", "", 0);
			}
			return 1;
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_DISCONNECT:
		{
			//DisConnect(fromAddr);
			return 1;
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_RECORDSTATUS:
		{
			if(m_pCommunicateSource)
			{
				m_pCommunicateSource->AddNotifyMsg(DBO_UPDATE,d1,v1);
			}
			return 1;
		}
		break;
	}

	if(d1 != IBFIS_MSG_CLIENT_1stACCESS_2_LOGIN_SERVER)
	{
		sprintf(szMsg,"执行操作[%s]失败",Cmd2Msg(d1).c_str());
		DISPLAY_LOG("服务端模块",szMsg,"","",0);
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISClientDataTrafficImp::OnRecvData(UINT64 fromAddr,DWORD_PTR& d1,std::vector<std::string>& v1,std::vector<std::string>& v2, std::vector<std::string>& v3)
{
	STRY;
	char szMsg[255] = {0};
	string strInfo;
	{
		Poco::FastMutex::ScopedLock myLock(m_csLockClientContext);
		GetEmployeeName(fromAddr,strInfo);
	}
	//sprintf(szMsg,"收到用户%s发来操作%s",strInfo.c_str(),Cmd2Msg(d1).c_str());
	//DISPLAY_LOG("服务端模块",szMsg,"","",1);
	TTRACE("[服务端模块]收到用户[%s]发来的操作[%d]\r\n",strInfo.c_str(), d1);
	DBOperType enType;
	enType = Cmd2DataOperType(d1);
	switch(d1)
	{
	case IBFIS_MSG_CLIENT_ADD_BUSINESSINFO:
	case IBFIS_MSG_CLIENT_UPDATE_BUSINESSINFO:
	case IBFIS_MSG_CLIENT_DEL_BUSINESSINFO:
		{
			STRY;
			if (v1.size() != 1)
			{
                DISPLAY_LOG("服务端模块", "添加业务信息失败", "业务信息为空", "", 1);
				return -1;
			}
			vector<string> vecInfo1 = v1;
			vector<string> vecInfo2 = v2;
			vector<string> vecInfo3 = v3;
			v1.clear();
			v2.clear();
			v3.clear();
			for (auto iter = vecInfo1.begin() ; iter != vecInfo1.end() ; ++iter)
			{
				BFIS::BusinessInfo msg;
				bool bSuccess = msg.ParseFromString(*iter);
				if (bSuccess)
				{
					ST_BusinessInfo stBusinessInfo(msg);
					if(!m_pClientSource || m_pClientSource->ManageBusinessInfo(enType,stBusinessInfo) <= 0)
					{
						sprintf(szMsg,"执行操作%s失败1",Cmd2Msg(d1).c_str());
						DISPLAY_LOG("服务端模块",szMsg,"","",0);
						return -0xFFFF; //标识插入业务文件失败(BusinessInfo文件已存在)
					}
				
					v1.push_back(*iter);
					if(!v1.empty())
						m_pCommunicateSource->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_BUSINESSINFO,v1);
				}
			}
			for (auto iter = vecInfo2.begin() ; iter != vecInfo2.end() ; ++iter)
			{
				BFIS::BusinessFileInfo msg;
				bool bSuccess = msg.ParseFromString(*iter);
				if (bSuccess)
				{
					ST_BusinessFileInfo stBusinessFileInfo(msg);
					if (m_pClientSource->ManageBusinessFileInfo(enType,stBusinessFileInfo) <= 0)
					{
						sprintf(szMsg,"执行操作%s失败2",Cmd2Msg(d1).c_str());
						DISPLAY_LOG("服务端模块",szMsg,"","",0);
						return -0xFFFF; //标识插入业务文件失败(FileInfo文件已经存在)
					}
					v2.push_back(*iter);
					if (!v1.empty() && !v2.empty())
						m_pCommunicateSource->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_BUSINESSFILEINFO,v1);
				}
			}
			for (auto iter = vecInfo3.begin() ; iter != vecInfo3.end() ; ++iter)
			{
				BFIS::BusinessRelateInfo msg;
				bool bSuccess = msg.ParseFromString(*iter);
				if (bSuccess)
				{
					ST_BusinessRelateInfo stBusinessRelateInfo(msg);
					if (m_pClientSource->ManageBusinessRelateInfo(enType,stBusinessRelateInfo) <= 0)
					{
						sprintf(szMsg,"执行操作%s失败3",Cmd2Msg(d1).c_str());
						DISPLAY_LOG("服务端模块",szMsg,"","",0);
						return -0xFFFF; //标识插入业务文件失败(RelateInfo文件已经存在)
					}
					v3.push_back(*iter);
					if(!v1.empty() && !v3.empty())
						m_pCommunicateSource->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_BUSINESSRELATEINFO,v1);
				}
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_BUSINESSINFO:
		{
			if(v1.empty())
			{
				DISPLAY_LOG("服务端模块", "查询业务失败", "查询业务条件为空", "", 0);
				return -1;
			}
			vector<string> vecInfo = v1;
			vector<ST_BusinessInfo> vecBusiness;
			vector<ST_BusinessFileInfo> vecBusinessFile;
			vector<ST_BusinessRelateInfo> vecBusinessRelate;
			v1.clear();
            if (!m_pClientSource)
            {
                DISPLAY_LOG("服务端模块", "查询业务失败", "Client对象为空", "", 0);
                return -1;
            }
			for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; ++iter)
			{
				BFIS::BusinessQueryParam msg;
				bool bSuccess = msg.ParseFromString(*iter);
                if (!bSuccess)
                {
                    DISPLAY_LOG("服务端模块", "查询业务失败", "反序列化查询参数失败", "", 0);
                    return -2;
                }
                ST_BusinessQueryParam stInfo(msg);
                int nInfoCount = 0;
                if (m_pClientSource->QueryBusinessInfoByCondition(stInfo, vecBusiness, nInfoCount, vecBusinessFile, vecBusinessRelate) != QueryFail)
                {
                    char szBuf[255] = { 0 };
                    sprintf(szBuf, "%d", nInfoCount);
                    std::string strTemp = szBuf;
                    v1.push_back(strTemp);
                    TTRACE("QueryBusinessInfoByCondition:BusinessSize:%d,FileSize:%d,RelateSize:%d \r\n",
                        vecBusiness.size(), vecBusinessFile.size(), vecBusinessRelate.size());
                    for (auto it = vecBusiness.begin(); it != vecBusiness.end(); it++)
                    {
                        string strInfo = _T("");
                        it->ConvertToString(strInfo);
                        v1.push_back(strInfo);
                    }
                    for (auto it = vecBusinessFile.begin(); it != vecBusinessFile.end(); it++)
                    {
                        string strInfo = _T("");
                        it->ConvertToString(strInfo);
                        v2.push_back(strInfo);
                    }
                    for (auto it = vecBusinessRelate.begin(); it != vecBusinessRelate.end(); it++)
                    {
                        string strInfo = _T("");
                        it->ConvertToString(strInfo);
                        v3.push_back(strInfo);
                    }
                }
			}
		}
		break;
    case IBFIS_MSG_CLIENT_QUERY_BUSINESSINFOUNFINISH:
        {     
            vector<ST_BusinessInfo> vecBusiness;
            vector<ST_BusinessFileInfo> vecBusinessFile;
            vector<ST_BusinessRelateInfo> vecBusinessRelate;;
            if (!m_pClientSource)
            {
                DISPLAY_LOG("服务端模块", "查询业务失败", "Client对象为空", "", 0);
                return -1;
            }       
            int nInfoCount = 0;
            if (m_pClientSource->QueryBusinessInfoUnFinished(vecBusiness, nInfoCount, vecBusinessFile, vecBusinessRelate) != QueryFail)
            {
                char szBuf[255] = { 0 };
                sprintf(szBuf, "%d", nInfoCount);
                std::string strTemp = szBuf;
                v1.push_back(strTemp);
                TTRACE("QueryBusinessInfoByCondition:BusinessSize:%d,FileSize:%d,RelateSize:%d \r\n",
                    vecBusiness.size(), vecBusinessFile.size(), vecBusinessRelate.size());
                for (auto it = vecBusiness.begin(); it != vecBusiness.end(); it++)
                {
                    string strInfo = _T("");
                    it->ConvertToString(strInfo);
                    v1.push_back(strInfo);
                }
                for (auto it = vecBusinessFile.begin(); it != vecBusinessFile.end(); it++)
                {
                    string strInfo = _T("");
                    it->ConvertToString(strInfo);
                    v2.push_back(strInfo);
                }
                for (auto it = vecBusinessRelate.begin(); it != vecBusinessRelate.end(); it++)
                {
                    string strInfo = _T("");
                    it->ConvertToString(strInfo);
                    v3.push_back(strInfo);
                }
            }       
        }
        break;
	}
	return 1;
	SCATCH;
	return -1;
}

DBOperType XhBFISClientDataTrafficImp::Cmd2DataOperType(DWORD dwCmd)
{
	STRY;
	DBOperType enType = DBO_INVAILED;
	switch(dwCmd)
	{
	case IBFIS_MSG_CLIENT_ADD_BRANCHINFO:				
	case IBFIS_MSG_CLIENT_ADD_PRODUCEINFO:		
	case IBFIS_MSG_CLIENT_SET_USERMAPINFO:			
	case IBFIS_MSG_CLIENT_ADD_ROLEINFO:				
	case IBFIS_MSG_CLIENT_ADD_PURVIEWINFO:			
	case IBFIS_MSG_CLIENT_SET_ROLEPURVIEWINFO:		
	case IBFIS_MSG_CLIENT_ADD_EMPLOYEEINFO:			
	case IBFIS_MSG_CLIENT_SET_EMPLOYEEPURVIEWINFO:	
	case IBFIS_MSG_CLIENT_ADD_CLIENTINFO:
	case IBFIS_MSG_CLIENT_ADD_BUSINESSINFO:
	case IBFIS_MSG_CLIENT_ADD_SCRIPTINFO:
	case IBFIS_MSG_CLIENT_ADD_OPERATELOGINFO:
		{
			enType = DBO_ADD;
		}
		break;
	case IBFIS_MSG_CLIENT_UPDATE_BRANCHINFO:				
	case IBFIS_MSG_CLIENT_UPDATE_PRODUCEINFO:				
	case IBFIS_MSG_CLIENT_UPDATE_ROLEINFO:				
	case IBFIS_MSG_CLIENT_UPDATE_PURVIEWINFO:				
	case IBFIS_MSG_CLIENT_UPDATE_EMPLOYEEINFO:			
	case IBFIS_MSG_CLIENT_UPDATE_CLIENTINFO:
	case IBFIS_MSG_CLIENT_UPDATE_BUSINESSINFO:
    case IBFIS_MSG_CLIENT_UPDATE_SCRIPTINFO:
	case IBFIS_MSG_CLIENT_UPDATE_OPERATELOGINFO:
		{
			enType = DBO_UPDATE;
		}
		break;
	case IBFIS_MSG_CLIENT_DEL_BRANCHINFO:				
	case IBFIS_MSG_CLIENT_DEL_PRODUCEINFO:			
	case IBFIS_MSG_CLIENT_DEL_ROLEINFO:				
	case IBFIS_MSG_CLIENT_DEL_PURVIEWINFO:			
	case IBFIS_MSG_CLIENT_DEL_EMPLOYEEINFO:			
	case IBFIS_MSG_CLIENT_DEL_CLIENTINFO:
	case IBFIS_MSG_CLIENT_DEL_BUSINESSINFO:
	case IBFIS_MSG_CLIENT_DEL_SCRIPTINFO:
	case IBFIS_MSG_CLIENT_DEL_OPERATELOGINFO:
		{
			enType = DBO_DEL;
		}
		break;
	}
	return enType;
	SCATCH;
	return DBO_INVAILED;
}

string XhBFISClientDataTrafficImp::Cmd2Msg(DWORD dwCmd)
{
	STRY;
	string strInfo;
	switch(dwCmd)
	{
	case IBFIS_MSG_CLIENT_GET_BRANCHINFO:
		{
			strInfo = _T("获取网点信息");
		}
		break;
	case IBFIS_MSG_CLIENT_GET_PRODUCEINFO:
		{
			strInfo = _T("获取产品信息");
		}
		break;
	case IBFIS_MSG_CLIENT_GET_USERMAPINFO:
		{
			strInfo = _T("获取用户关系映射信息");
		}
		break;
	case IBFIS_MSG_CLIENT_GET_ROLEINFO:
		{
			strInfo = _T("获取信息");
		}
		break;
	case IBFIS_MSG_CLIENT_GET_PURVIEWINFO:
		{
			strInfo = _T("获取权限信息");
		}
		break;
	case IBFIS_MSG_CLIENT_GET_ROLEPURVIEWINFO:
		{
			strInfo = _T("获取角色权限信息");
		}
		break;
	case IBFIS_MSG_CLIENT_GET_EMPLOYEEINFO:
		{
			strInfo = _T("获取员工信息");
		}
		break;
	case IBFIS_MSG_CLIENT_GET_EMPLOYEEPURVIEWINFO:
		{
			strInfo = _T("获取员工权限信息");
		}
		break;
	case IBFIS_MSG_CLIENT_GET_CLIENTINFO:
		{
			strInfo = _T("获取客户信息");
		}
		break;
	case IBFIS_MSG_CLIENT_GET_BUSINESSINFO:
		{
			strInfo = _T("获取业务信息");
		}
		break;
	case IBFIS_MSG_CLIENT_GET_BUSINESSFILEINFO:
		{
			strInfo = _T("获取业务文件信息");
		}
		break;
	case IBFIS_MSG_CLIENT_GET_BUSINESSRELATEINFO:
		{
			strInfo = _T("获取业务关联信息");
		}
		break;
	case IBFIS_MSG_CLIENT_LOGIN_2_SERVER:
		{
			strInfo = _T("登录服务器");
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_BRANCHINFO:
		{
			strInfo = _T("添加网点信息");
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_PRODUCEINFO:
		{
			strInfo = _T("添加产品信息");
		}
		break;
	case IBFIS_MSG_CLIENT_SET_USERMAPINFO:	
		{
			strInfo = _T("添加用户关系映射信息");
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_ROLEINFO:
		{
			strInfo = _T("添加角色信息");
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_PURVIEWINFO:	
		{
			strInfo = _T("添加权限信息");
		}
		break;
	case IBFIS_MSG_CLIENT_SET_ROLEPURVIEWINFO:	
		{
			strInfo = _T("添加角色权限信息");
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_EMPLOYEEINFO:
		{
			strInfo = _T("添加员工信息");
		}
		break;
	case IBFIS_MSG_CLIENT_SET_EMPLOYEEPURVIEWINFO:	
		{
			strInfo = _T("添加员工权限信息");
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_CLIENTINFO:
		{
			strInfo = _T("添加客户信息");
		}
		break;
	case IBFIS_MSG_CLIENT_ADD_BUSINESSINFO:
		{
			strInfo = _T("添加业务信息");
		}
		break;
	case IBFIS_MSG_CLIENT_UPDATE_BRANCHINFO:
		{
			strInfo = _T("更新网点信息");
		}
		break;
	case IBFIS_MSG_CLIENT_UPDATE_PRODUCEINFO:
		{
			strInfo = _T("更新产品信息");
		}
		break;
	case IBFIS_MSG_CLIENT_UPDATE_ROLEINFO:	
		{
			strInfo = _T("更新角色信息");
		}
		break;
	case IBFIS_MSG_CLIENT_UPDATE_PURVIEWINFO:
		{
			strInfo = _T("更新权限信息");
		}
		break;
	case IBFIS_MSG_CLIENT_UPDATE_EMPLOYEEINFO:	
		{
			strInfo = _T("更新员工信息");
		}
		break;
	case IBFIS_MSG_CLIENT_UPDATE_CLIENTINFO:
		{
			strInfo = _T("更新客户信息");
		}
		break;
	case IBFIS_MSG_CLIENT_UPDATE_BUSINESSINFO:
		{
			strInfo = _T("更新业务信息");
		}
		break;
	case IBFIS_MSG_CLIENT_DEL_BRANCHINFO:	
		{
			strInfo = _T("删除网点信息");
		}
		break;
	case IBFIS_MSG_CLIENT_DEL_PRODUCEINFO:	
		{
			strInfo = _T("删除产品信息");
		}
		break;
	case IBFIS_MSG_CLIENT_DEL_ROLEINFO:		
		{
			strInfo = _T("删除角色信息");
		}
		break;
	case IBFIS_MSG_CLIENT_DEL_PURVIEWINFO:	
		{
			strInfo = _T("删除权限信息");
		}
		break;
	case IBFIS_MSG_CLIENT_DEL_EMPLOYEEINFO:		
		{
			strInfo = _T("删除员工信息");
		}
		break;
	case IBFIS_MSG_CLIENT_DEL_CLIENTINFO:
		{
			strInfo = _T("删除客户信息");
		}
		break;
	case IBFIS_MSG_CLIENT_DEL_BUSINESSINFO:
		{
			strInfo = _T("删除业务信息");
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_BUSINESSINFO:
		{
			strInfo = _T("查询业务信息");
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_CLIENTINFO:
		{
			strInfo = _T("查询客户信息");
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_SUPEREMPLOYEE:
		{
			strInfo = _T("查询管理员信息");
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_PRODUCEID:
		{
			strInfo = _T("查询用户经常使用的产品ID和使用频率");
		}
		break;
    case IBFIS_MSG_CLIENT_QUERY_MCSERVERINFO:
        {
            strInfo = _T("查询MC信息");
            break;
        }
	case IBFIS_MSG_CLIENT_ADD_OPERATELOGINFO:
		{
			strInfo = _T("添加操作日志");
			break;
		}
	case IBFIS_MSG_CLIENT_QUERY_OPERATELOGINFO:
		{
			strInfo = _T("查询操作日志信息");
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_DISKANDCONNECT:
		{
			strInfo = _T("查询磁盘信息和连接状态");
		}
		break;
    default:
        {
            std::stringstream os;
            os << "未知操作类型:" << dwCmd;
            strInfo = os.str();
        }
	}
	return strInfo;
	SCATCH;
	return _T("");
}

int XhBFISClientDataTrafficImp::ClientLogin2( UINT64 fromAddr, std::vector<std::string>& v1 )
{
	STRY;
	ST_EmployeeInfo stInfo;
	auto itor = v1.begin();
	string strUrl = *itor;
	string strUsername = *(++itor);
	string strPassword = *(++itor);
	//auto iter1 = m_mapUserName.find(strUsername);
	/*if (iter1 != m_mapUserName.end())
	{
	m_pCommunicateSource->AddNotifyMsg(DBO_UPDATE,IBFIS_MSG_CLIENT_NOTIFY_RECONNECT,strUsername,(DWORD_PTR)iter1->second);
	}*/
	if (m_pClientSource && m_pClientSource->UserLogin(strUsername,strPassword,stInfo) > 0)
	{
		v1.clear();
		v1.push_back(stInfo.strBranchId);
		ST_Login stLogin;
		stLogin.stInfo = stInfo;
		stLogin.strUrl = strUrl;
		//保存Handle对应信息
		Poco::FastMutex::ScopedLock myLock(m_csLockClientContext);
		auto iter = m_mapClientContext.find(fromAddr);
		if (iter != m_mapClientContext.end())
		{
			iter->second = stLogin;
		}
		else
		{
			m_mapClientContext[fromAddr] = stLogin;
			//m_mapUserName[strUsername] = fromAddr;
		}
		return ISOC_ERR_SUCCESS;
	}
	else
	{
		std::string strError = _T("用户名/密码错误,登录失败");
		v1.clear();
		v1.push_back(strError);
		return ISOC_ERR_FAILED;
	}
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}

int XhBFISClientDataTrafficImp::ClientGetBranchInfo( std::vector<std::string>& v1 )
{
	STRY;
	vector<ST_BranchInfo> vecInfo;
	if (m_pClientSource && m_pClientSource->GetBranchInfo(vecInfo))
	{
		v1.clear();
		for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; iter ++)
		{
			std::string strInfo;
			bool bSuccess = iter->ConvertToString(strInfo);
			if(!bSuccess)
			{
				char szMsg[255] = {0};
				sprintf(szMsg,"网点信息[%s]串行化失败",iter->strBranchId.c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",0);
			}
			else
			{
				v1.push_back(strInfo);
			}
		}
		if(v1.size() > 0 || vecInfo.empty())
		{
			return ISOC_ERR_SUCCESS;
		}
	}
	else
	{
		std::string strError = _T("获取网点信息失败");
		v1.clear();
		v1.push_back(strError);
	}
	return ISOC_ERR_FAILED;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}

int XhBFISClientDataTrafficImp::ClientGetProduceInfo( std::vector<std::string>& v1 )
{
	STRY;
	if (m_pClientSource && m_pClientSource->GetProduceInfo(v1))
	{
		TTRACE("[服务端模块]获取产品数量:%d \r\n",v1.size());
		return ISOC_ERR_SUCCESS;
	}
	else
	{
		v1.clear();
		std::string strError = _T("获取产品信息失败");
		v1.push_back(strError);
	}
	return ISOC_ERR_FAILED;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}

int XhBFISClientDataTrafficImp::ClientGetPurviewInfo( std::vector<std::string>& v1 )
{
	STRY;
	vector<ST_PurviewInfo> vecInfo;
	if (m_pClientSource && m_pClientSource->GetPurviewInfo(vecInfo))
	{
		v1.clear();
		for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; iter ++)
		{
			std::string strInfo;
			bool bSuccess = iter->ConvertToString(strInfo);
			if(!bSuccess)
			{
				char szMsg[255] = {0};
				sprintf(szMsg,"权限信息[%s]串行化失败",iter->strPurviewInfoId.c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",0);
			}
			else
			{
				v1.push_back(strInfo);
			}
		}
		if(v1.size() > 0 || vecInfo.empty())
		{
			return ISOC_ERR_SUCCESS;
		}
	}
	else
	{
		std::string strError = _T("获取权限信息失败");
		v1.clear();
		v1.push_back(strError);
	}
	return ISOC_ERR_FAILED;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}

int XhBFISClientDataTrafficImp::ClientGetRoleInfo( std::vector<std::string>& v1 )
{
	STRY;
	vector<ST_RoleInfo> vecInfo;
	if (m_pClientSource && m_pClientSource->GetRoleInfo(vecInfo))
	{
		v1.clear();
		for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; iter ++)
		{
			std::string strInfo;
			bool bSuccess = iter->ConvertToString(strInfo);
			if(!bSuccess)
			{
				char szMsg[255] = {0};
				sprintf(szMsg,"角色信息[%s]串行化失败",iter->strRoleInfoId.c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",0);
			}
			else
			{
				v1.push_back(strInfo);
			}
		}
		if(v1.size() > 0 || vecInfo.empty())
		{
			return ISOC_ERR_SUCCESS;
		}
	}
	else
	{
		std::string strError = _T("获取角色信息失败");
		v1.clear();
		v1.push_back(strError);
	}
	return ISOC_ERR_FAILED;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}

int XhBFISClientDataTrafficImp::ClientGetPolepurviewInfo( std::vector<std::string>& v1 )
{
	STRY;
	vector<ST_RolePurviewInfo> vecInfo;
	if (m_pClientSource && m_pClientSource->GetRolePurviewInfo(vecInfo))
	{
		for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; iter ++)
		{
			std::string strInfo;
			bool bSuccess = iter->ConvertToString(strInfo);
			if(!bSuccess)
			{
				char szMsg[255] = {0};
				sprintf(szMsg,"角色权限信息[%s]串行化失败",iter->strRoleInfoPurviewId.c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",0);
			}
			else
			{
				v1.push_back(strInfo);
			}
		}
		if(v1.size() > 0 || vecInfo.empty())
		{
			return ISOC_ERR_SUCCESS;
		}
	}
	else
	{
		std::string strError = _T("获取角色权限信息失败");
		v1.clear();
		v1.push_back(strError);
	}
	return ISOC_ERR_FAILED;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}

int XhBFISClientDataTrafficImp::ClientGetEmployeeInfo( std::vector<std::string>& v1 )
{
	STRY;
	vector<ST_EmployeeInfo> vecInfo;
	if (m_pClientSource && m_pClientSource->GetEmployeeInfo(vecInfo))
	{
		for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; iter ++)
		{
			std::string strInfo;
			bool bSuccess = iter->ConvertToString(strInfo);
			if(!bSuccess)
			{
				char szMsg[255] = {0};
				sprintf(szMsg,"员工信息[%s]串行化失败",iter->strEmployeeId.c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",0);
			}
			else
			{
				v1.push_back(strInfo);
			}
		}
		if(v1.size() > 0 || vecInfo.empty())
		{
			return ISOC_ERR_SUCCESS;
		}
	}
	else
	{
		std::string strError = _T("获取员工信息失败");
		v1.clear();
		v1.push_back(strError);
	}
	return ISOC_ERR_FAILED;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}

int XhBFISClientDataTrafficImp::ClientGetEmployeepurviewInfo( std::vector<std::string>& v1 )
{
	STRY;
	vector<ST_EmployeePurviewInfo> vecInfo;
	if (m_pClientSource && m_pClientSource->GetEmployeePurviewInfo(vecInfo))
	{
		for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; iter ++)
		{
			std::string strInfo;
			bool bSuccess = iter->ConvertToString(strInfo);
			if(!bSuccess)
			{
				char szMsg[255] = {0};
				sprintf(szMsg,"员工权限信息[%s]串行化失败",iter->strEmployeePurviewId.c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",0);
			}
			else
			{
				v1.push_back(strInfo);
			}
		}
		if(v1.size() > 0 || vecInfo.empty())
		{
			return ISOC_ERR_SUCCESS;
		}
	}
	else
	{
		std::string strError = _T("获取员工权限信息失败");
		v1.clear();
		v1.push_back(strError);
	}
	return ISOC_ERR_FAILED;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}

int XhBFISClientDataTrafficImp::ClientGetEmployeepurviewInfo(IBFISSerializeDataMemoryModel ** pEmployeepurviewInfo)
{
	STRY;
	if (m_pClientSource)
		return m_pClientSource->GetEmployeePurviewInfo(pEmployeepurviewInfo);
	SCATCH;
	return -1;
}

int XhBFISClientDataTrafficImp::ClientGetUserMapInfo(  std::vector<std::string>& v1 )
{
	STRY;
	vector<ST_UserMapInfo> vecInfo;
	if (m_pClientSource && m_pClientSource->GetUsermapInfo(vecInfo))
	{
		for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; iter ++)
		{
			std::string strInfo;
			bool bSuccess = iter->ConvertToString(strInfo);
			if(!bSuccess)
			{
				char szMsg[255] = {0};
				sprintf(szMsg,"用户关系映射信息[%s]串行化失败",iter->strUserMapInfoId.c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",0);
			}
			else
			{
				v1.push_back(strInfo);
			}
		}
		if(v1.size() > 0 || vecInfo.empty())
		{
			return ISOC_ERR_SUCCESS;
		}
	}
	else
	{
		std::string strError = _T("获取用户关系映射信息失败");
		v1.clear();
		v1.push_back(strError);
	}
	return ISOC_ERR_FAILED;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}

int XhBFISClientDataTrafficImp::ClientGetClientInfo( std::vector<std::string>& v1)
{
	STRY;
	if (m_pClientSource && m_pClientSource->GetClientInfo(v1))
	{
		return ISOC_ERR_SUCCESS;
	}
	else
	{
		std::string strError = _T("获取客户信息失败");
		v1.clear();
		v1.push_back(strError);
	}
	return ISOC_ERR_FAILED;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}

int XhBFISClientDataTrafficImp::ClientGetScriptInfo(std::vector<std::string>& v1)
{
	STRY;
	vector<ST_ScriptInfo> vecInfo;
	if (m_pClientSource && m_pClientSource->GetScriptInfoData(vecInfo) >= 0)
	{
		for (auto iter = vecInfo.begin() ; iter != vecInfo.end() ; iter ++)
		{
			std::string strInfo;
			bool bSuccess = iter->ConvertToString(strInfo);
			if(!bSuccess)
			{
				char szMsg[255] = {0};
				sprintf(szMsg,"话术信息[%s]串行化失败",iter->strScriptId.c_str());
				DISPLAY_LOG("服务端模块",szMsg,"","",0);
			}
			else
			{
				v1.push_back(strInfo);
			}
		}
		if(v1.size() > 0 || vecInfo.empty())
		{
			return ISOC_ERR_SUCCESS;
		}
	}
	else
	{
		std::string strError = _T("获取会话信息失败");
		v1.clear();
		v1.push_back(strError);
	}
	return ISOC_ERR_FAILED;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}

std::string XhBFISClientDataTrafficImp::PackMeg( std::vector<std::string>& v1 )
{
	std::string strMeg;
	for each(auto &var in v1)
	{
		if (strMeg.size() > 0)
			strMeg += "<StreamItem>";
		strMeg += var;
	}
	return strMeg;
}

int XhBFISClientDataTrafficImp::ParseMeg( std::string& meg, std::vector<std::string>& v1 )
{
	if (meg.size() > 0)
	{
		boost::xpressive::cregex reg = boost::xpressive::cregex::compile("<StreamItem>");
		const char *megC = meg.c_str();
		boost::xpressive::cregex_token_iterator pos(megC, megC + meg.size(), reg, -1);
		for (; pos != boost::xpressive::cregex_token_iterator(); ++pos)
		{
			v1.push_back(*pos);
		}
	}
	return true;
}

bool XhBFISClientDataTrafficImp::GetEmployeeName(UINT64 fromAddr,string& strInfo)
{
	STRY;
	auto iter = m_mapClientContext.find(fromAddr);
	if (iter != m_mapClientContext.end())
	{
		//strInfo = iter->second.stInfo.strName;
		CString strTemp;
		strTemp.Format("%s[%s]",iter->second.stInfo.strName.c_str(),iter->second.strUrl.c_str());
		strInfo = strTemp;
		return true;
	}
	else
	{
		HANDLE hContext = reinterpret_cast<HANDLE>(fromAddr);
		char ip[30] = {0};
		iBFIS_CommunicationServer::GetClientAddr(hContext,ip);
		strInfo = ip;
		return true;
	}
	return false;
	SCATCH;
	return false;
}

ISOC_BOOL XhBFISClientDataTrafficImp::GetEmployeeId(UINT64 fromAddr,string& strId)
{
	STRY;
	strId = "";
	Poco::FastMutex::ScopedLock myLock(m_csLockClientContext);
	auto iter = m_mapClientContext.find(fromAddr);
	if (iter != m_mapClientContext.end())
	{
		strId = iter->second.stInfo.strEmployeeId;
		return true;
	}
	return false;
	SCATCH;
	return false;
}
ISOC_BOOL XhBFISClientDataTrafficImp::TimingDelOperateLog(int nOperateLogSaveTime)
{
	STRY;
	std::vector<ST_OperateLogInfo> vecOperateLogInfo;
	time_t it;
	it = time(NULL);

	long seconds = 24  *3600 * nOperateLogSaveTime;
	it -= seconds;

	struct tm *p = localtime(&it);
	char* szTime = new char[30];
	sprintf(szTime,"%04d-%02d-%02d %02d:%02d:%02d",p->tm_year+1900,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	string strTime = szTime;
	if(m_pClientSource)
	{
		m_pClientSource->QueryNeedDelOperateLogInfo(vecOperateLogInfo,strTime);
		for(auto iter = vecOperateLogInfo.begin(); iter != vecOperateLogInfo.end(); iter++)
		{
			m_pClientSource->ManageOperateLogInfo(DBO_DEL,*iter);
		}
	}
	delete[] szTime;
	return TRUE;
	SCATCH;
	return FALSE;
}