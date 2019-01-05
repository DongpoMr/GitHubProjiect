#include "stdafx.h"
#include "IcmsP_Utility.h"
#include "XhLogDisplayInterface.h"
#include "iSOC_MonFactoryManagement.h"
#include "XhBFISCommunicateSyncServerStationImp.h"
#include "iBFIS_UniqueDefine.h"
#include "BFIS.ProtoMessageDefine.pb.h"
#include "IcmsP_XmlParser.h"
#include "XhAutoScalUseTime.h"
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost\thread.hpp>
#include <boost\date_time\gregorian\gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "xhObjectRefCount.cpp"
#include <boost\filesystem\path.hpp>
#include <boost\filesystem\operations.hpp>
#include <boost\format.hpp>

#define BOOST_DATE_TIME_SOURCE


static int NotifyMegEnTrance(ST_CallBackInfo stCbInfo)
{
	XhBFISCommunicateSyncServerStationImp *pSelf = static_cast<XhBFISCommunicateSyncServerStationImp *>(stCbInfo.pCallBackAddr);
	if (pSelf)
		pSelf->NotifyMegHandle(stCbInfo);
	return 1;
}

XhBFISCommunicateSyncServerStationImp::XhBFISCommunicateSyncServerStationImp() :m_pBankPluginInter(nullptr)
{
	RefCountInfo::setExitStatus(false);
	m_pNetServer = nullptr;
	m_pClientDataTrafficSource = nullptr;
	m_pSyncServer = nullptr;
	m_bNeedStop = FALSE;
	iSOC_MonFactoryManagement fmt;
	m_pCallbackManager = static_cast<ICallbackManagement*>(fmt.CreateObject(OBJECT_TYPE_CALLBACK_MANAGER, "", __FUNCTION__));
	m_csClinetContext.SetCallbackInfoWhenDeadLock();
	m_csNewClinetContext.SetCallbackInfoWhenDeadLock();
	m_csNewBranchClinetContext.SetCallbackInfoWhenDeadLock();
	m_csBranchClinetContext.SetCallbackInfoWhenDeadLock();
}

XhBFISCommunicateSyncServerStationImp::~XhBFISCommunicateSyncServerStationImp()
{
	STRY;
	UnInit();
	if (m_pCallbackManager)
	{
		iSOC_MonFactoryManagement fmt;
		fmt.ReleaseObject((CISocObject**)&m_pCallbackManager, __FUNCTION__);
		m_pCallbackManager = NULL;
	}
	SCATCH;
}

ISOC_BOOL XhBFISCommunicateSyncServerStationImp::Init()
{
	STRY;

	m_pNetServer = new iBFIS_CommunicationServer;
	m_pNetServer->SetRMICallbackSkin(this);

	
	iSOC_MonFactoryManagement fmt;
	m_pClientDataTrafficSource = static_cast<IBFISClientDataTrafficSource*>(fmt.CreateObject(OBJECT_TYPE_BFIS_CLIENTCOMMUNICATION,"",__FUNCTION__));
	if (m_pClientDataTrafficSource == nullptr)
	{
		DISPLAY_LOG("服务端模块","创建客户端数据通信源失败","","",0);
		return FALSE;
	}
	else
	{
		DISPLAY_LOG("服务端模块","创建客户端数据通信源成功","","",1);
	}
	m_pClientDataTrafficSource->Init();
	m_pSyncServer = static_cast<IBFISSyncServer*>(fmt.CreateObject(OBJECT_TYPE_BFISSYNC_SERVER,"",__FUNCTION__));
	if (m_pSyncServer == nullptr)
	{
		DISPLAY_LOG("服务端模块","创建同步服务Server端失败","","",0);
		return FALSE;
	}
	else
	{
		DISPLAY_LOG("服务端模块","创建同步服务Server端成功","","",1);
	}
	m_pSyncServer->CheckIsTopServer(m_nServerType);
	m_pSyncServer->Init();
	m_pSyncClient = static_cast<IBFISSyncClient*>(fmt.CreateObject(OBJECT_TYPE_BFISSYNC_CLIENT,"",__FUNCTION__));
	if (m_pSyncClient == nullptr)
	{
		DISPLAY_LOG("服务端模块","创建同步服务Client端失败","","",0);
		return FALSE;
	}

	//接收更新通知
	//m_pThread = static_cast<IThread*>(fmt.CreateObject(OBJECT_TYPE_THREAD,"",__FUNCTION__));
	//if(m_pThread)
	//{
	//	m_pThread->SetRunAbleInterface(this);
	//	m_pThread->Start();
	//}
	//iSOC_MonFactoryManagement fmt;
	m_pCache = static_cast<IBFISDataProvider*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_CACHESOURCE,"",__FUNCTION__));
	if (m_pCache && m_pCache->QueryLocalBranchId(m_strLocalBranchId))
	{
		m_pCache->QueryBranchInfoById(m_strLocalBranchId,m_stBranchInfo);
	}
	m_dockingThread = std::make_shared<boost::thread>(std::bind(&XhBFISCommunicateSyncServerStationImp::Run, this));
	PraseGetKeyValueData();
	CreateBankDockingPlugin();
	return TRUE;
	SCATCH;
	return FALSE;
}

ISOC_BOOL XhBFISCommunicateSyncServerStationImp::UnInit()
{
	STRY;
	RefCountInfo::setExitStatus();
	m_bNeedStop = TRUE;
	while(m_pThread && m_pThread->IsAlive())
	{
		Sleep(30);
	}

	if (m_dockingThread)
	{
		boost::unique_lock<boost::mutex> locker(m_dockingMtx);
		m_dockingCondition.notify_one();
		locker.unlock();
		m_dockingThread->join();
		m_dockingThread = nullptr;
	}
		
	iSOC_MonFactoryManagement fmt;
	if(fmt.CheckObjectCanBeUse(m_pThread))
	{
		fmt.ReleaseObject(reinterpret_cast<CISocObject**>(&m_pThread), __FUNCTION__);
		m_pThread = nullptr;
	}
	if (m_pBankPluginInter)
	{
		m_pBankPluginInter->StopDockListen(m_stBasicSetting.nPublicPort);
		if(fmt.CheckObjectCanBeUse(m_pBankPluginInter))
		{
			fmt.ReleaseObject(reinterpret_cast<CISocObject**>(&m_pBankPluginInter), __FUNCTION__);
			m_pBankPluginInter = nullptr;
		}
	}

	m_vecNotifyMsg.clear();

	if (m_pNetServer)
	{
		m_pNetServer->Stop();
		m_pNetServer->SetRMICallbackSkin(nullptr);
		SAFE_DELETE(m_pNetServer);
	}
	
	// 	if (m_pClientDataTrafficSource)
	// 	{
	// 		SAFE_DELETE(m_pClientDataTrafficSource);
	// 	}
	// 	if (m_pSyncServer)
	// 	{
	// 		SAFE_DELETE(m_pSyncServer);
	// 	}
	return TRUE;
	SCATCH;
	return FALSE;
}

int XhBFISCommunicateSyncServerStationImp::ClinetNotifyDiskAndConnect(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved)
{
	STRY;

	switch(enType)
	{
	    case DBO_ADD:
	    {
		    AddConnectAndDiskStatus(enType, dwCmd, vecParam, dwReserved);
	    }
	    break;
	    case DBO_DEL:
	    {
		    DelConnectAndDiskStatus(enType, dwCmd, vecParam, dwReserved);
	    }
	    break;
	    case DBO_QUERY:
	    {
		    QueryConnectAndDiskStatus(hClient, enType, dwCmd, vecParam, dwReserved);
	    }
	    break;
	}
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::SendMegToClinet(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved)
{
	STRY;
	readLock locker(m_connectUserClientMtx);
	auto var = m_mapUserClinetContext.find(hClient);
	if (var != m_mapUserClinetContext.end())
	{
		std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
		std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
		AutoObjectRefMgr refObject;
		if (refObject.AddRefCount(refInfo))
		{
			locker.unlock();
			return XhDoSendData(hClient, enType, dwCmd, vecParam, dwReserved);
		}
	}
	TTRACE(" %s 发送句柄不存在1[%p]\r\n", __FUNCTION__, hClient);
	SCATCH;
	return -2000;
}

int XhBFISCommunicateSyncServerStationImp::SendMegToClinet(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR dwCmd, std::string & strParam, IN DWORD_PTR dwReserved)
{
	STRY;
	readLock locker(m_connectUserClientMtx);
	auto var = m_mapUserClinetContext.find(hClient);
	if (var != m_mapUserClinetContext.end())
	{
		std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
		std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
		AutoObjectRefMgr refObject;
		if (refObject.AddRefCount(refInfo))
		{
			locker.unlock();
			return XhDoSendData(hClient, enType, dwCmd, strParam, dwReserved);
		}
	}
	TTRACE(" %s 发送句柄不存在1[%p]\r\n", __FUNCTION__, hClient);
	SCATCH;
	return -2000;
}

int XhBFISCommunicateSyncServerStationImp::SendMegToAllClinet(IN DBOperType enType, IN DWORD_PTR dwCmd, std::string & strParam, IN DWORD_PTR dwReserved)
{
	STRY;
	std::map<HANDLE, std::shared_ptr<ObjectRefCount<HANDLE> > >  mapUserClinetContext;
	STRY;
	readLock locker(m_connectUserClientMtx);
	mapUserClinetContext = m_mapUserClinetContext;
	SCATCH;

	for each (auto &var in mapUserClinetContext)
	{
		readLock locker(m_connectUserClientMtx);
		auto itor = m_mapUserClinetContext.find(var.first);
		if (itor != m_mapUserClinetContext.end())
		{
			std::shared_ptr<ObjectRefCount<HANDLE> > refObj = itor->second;
			std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
			AutoObjectRefMgr refObject;
			if (refObject.AddRefCount(refInfo))
			{
				locker.unlock();
				XhDoSendData(var.first, enType, dwCmd, strParam, dwReserved);
			}
		}
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::SendMegToClinet(_NotifyMessage & stMsg)
{
	STRY;

	std::map<HANDLE, std::shared_ptr<ObjectRefCount<HANDLE> > >  mapUserClinetContext;
	STRY;
	readLock locker(m_connectUserClientMtx);
	mapUserClinetContext = m_mapUserClinetContext;
	SCATCH;

	for each (auto &var in mapUserClinetContext)
	{
		readLock locker(m_connectUserClientMtx);
		auto itor = m_mapUserClinetContext.find(var.first);
		if (itor != m_mapUserClinetContext.end())
		{
			std::shared_ptr<ObjectRefCount<HANDLE> > refObj = itor->second;
			std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
			AutoObjectRefMgr refObject;
			if (refObject.AddRefCount(refInfo))
			{
				locker.unlock();
				if (stMsg.vecStr.size() == 1)
				{
					XhDoSendData(var.first, static_cast<DBOperType>(stMsg.nType), stMsg.dwCmd, stMsg.vecStr[0], stMsg.dwReserved);
				}
				else
				{
					XhDoSendData(var.first, static_cast<DBOperType>(stMsg.nType), stMsg.dwCmd, stMsg.vecStr, stMsg.dwReserved);
				}
			}
		}
	}

	SCATCH;
	return 0;
}

int XhBFISCommunicateSyncServerStationImp::GetArrayKey(IN HANDLE hClient, int nRange)
{
	size_t h1 = std::hash<int>()(reinterpret_cast<int>(hClient));
	return h1 % nRange;//reinterpret_cast<int>(hClient) % nRange;
}

int XhBFISCommunicateSyncServerStationImp::ClinetQueryOperateLogInfo(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved)
{
	STRY;

	int nRet = -2000;

	BFIS::EmployeeInfo msg;
	if (false == msg.ParseFromString(vecParam[0]))
		return -1000;

	ST_EmployeeInfo stEmployeeInfo(msg);
	bool bFind = false;
	//下级用户
	STRY;
	readLock locker(m_connectBranchClientInfoMtx);
	auto var = m_mapBranchContextInfo.find(stEmployeeInfo.strBranchId);
	if (var != m_mapBranchContextInfo.end())
	{
		std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
		std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
		AutoObjectRefMgr refObject;
		if (refObject.AddRefCount(refInfo))
		{
			locker.unlock();
			//发送到指定服务器查询
			if (XhDoSendData(refObj->m_custom, static_cast<DBOperType>(enType), dwCmd, vecParam, dwReserved) > 0)
			{
				bFind = true;
			}
		}
	}
	SCATCH;

	if (bFind)
		return SendMegToClinet(hClient, DBO_UPDATE, IBFIS_MSG_CLIENT_GET_OPERATELOGINFO, vecParam, dwReserved);

	STRY;
	vector<ST_OperateLogInfo> vecOprateLog;
	vector<string> vecStrOperateLog;
	if (m_pCache && m_pCache->QueryOperateLogInfoByEmployeeId(vecOprateLog, stEmployeeInfo.strEmployeeId))
	{
		for (auto iter = vecOprateLog.begin(); iter != vecOprateLog.end(); iter++)
		{
			std::string strInfo;
			bool bSuccess = iter->ConvertToString(strInfo);
			if (!bSuccess)
			{
				char szMsg[255] = { 0 };
				sprintf(szMsg, "操作日志信息[%s]串行化失败", iter->strOperateLogId.c_str());
				DISPLAY_LOG("服务端模块", szMsg, "", "", 0);
			}
			else
			{
				vecStrOperateLog.push_back(strInfo);
			}
		}
	}
	return SendMegToClinet(hClient, DBO_UPDATE, IBFIS_MSG_CLIENT_GET_OPERATELOGINFO, vecStrOperateLog, dwReserved);
	SCATCH;
	return -1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::SendLowerLevelServer( _NotifyMessage &itemMeg)
{
	STRY;
	XhAutoScalUseTime strtime("同步数据到下级服务器", true);
	if (itemMeg.dwCmd == IBFIS_MSG_CLIENT_NOTIFY_ROLEINFO)
	{
		BFIS::RoleInfo msg;
		if (msg.ParseFromString(itemMeg.vecStr[0]))
		{
			ST_RoleInfo stInfo(msg);
			if (stInfo.nExtendedInfo != 1)
				return 1;
		}
	}
	else if (itemMeg.dwCmd == MSG_ISSUED_EMPLOYEEINFO)
	{
		BFIS::EmployeeInfo msg;
		if (msg.ParseFromString(itemMeg.vecStr[0]))
		{
			ST_EmployeeInfo stInfo(msg);
			readLock locker(m_connectBranchClientInfoMtx);
			auto var = m_mapBranchContextInfo.find(stInfo.strBranchId);
			if (var != m_mapBranchContextInfo.end())
			{
				std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
				std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
				AutoObjectRefMgr refObject;
				if (refObject.AddRefCount(refInfo))
				{
					locker.unlock();
					XhDoSendData(refObj->m_custom, itemMeg.dwCmd, itemMeg.nType, itemMeg.vecStr[0]);
					return 1;
				}
			}
		}
		return -1;
	}

	std::vector<ST_TaskPlan> vecPlans;
	vector<string> vecTaskStr;
	if (itemMeg.dwCmd == IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO)
	{
		m_pCache->ManageTaskPlanInfo(DBO_QUERY, vecPlans);
		if (!vecPlans.empty())
		{
			int i = 0;
			for (vecPlans[i]; i < vecPlans.size(); i++)
			{
				string strTemp;
				bool bSuccess = vecPlans[i].ConvertToString(strTemp);
				if (!bSuccess)
				{
					TTRACE("ST_TaskPlan[%s]串行化失败 \r\n", __FUNCTION__);
				}
				vecTaskStr.push_back(strTemp);
				strTemp.clear();
			}
		}
	}

	int nRet = -1;
	DWORD_PTR d1 = itemMeg.dwCmd, d2 = itemMeg.nType;

	std::map<HANDLE, std::shared_ptr<ObjectRefCount<HANDLE> > >  mapBranchClinetContext;
	STRY;
	readLock locker(m_connectBranchClientMtx);
	mapBranchClinetContext = m_mapBranchClinetContext;
	SCATCH;
	
	for each (auto &var in mapBranchClinetContext)
	{
		readLock locker(m_connectBranchClientMtx);
		auto itor = m_mapBranchClinetContext.find(var.first);
		if (itor != m_mapBranchClinetContext.end())
		{
			std::shared_ptr<ObjectRefCount<HANDLE> > refObj = itor->second;
			std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
			AutoObjectRefMgr refObject;
			if (refObject.AddRefCount(refInfo))
			{
				locker.unlock();
				if (itemMeg.dwCmd == IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO)
				{
					nRet = XhDoSendData(var.first, static_cast<DBOperType>(itemMeg.nType), itemMeg.dwCmd, itemMeg.vecStr, itemMeg.dwReserved);
					iBFIS_CommunicationInvoker invoke(var.first);
					DWORD_PTR dwCmd1 = MSG_ISSUED_MIGRATETASKINFO;
					nRet = invoke.Invoke(dwCmd1, vecTaskStr);
					if (nRet <= 0)
					{
						RcfConnectCheck(nRet, var.first);
						TTRACE("[通信模块]发送消息失败,返回错误码[%d],  ID[%d]LL-KEY \r\n", nRet, static_cast<int>(dwCmd1));
					}
				}
				else
				{
					if (itemMeg.vecStr.size() == 1)
					{
						nRet = XhDoSendData(var.first, d1, d2, itemMeg.vecStr[0]);
					}
					else
					{
						iBFIS_CommunicationInvoker invoke(var.first);
						nRet = invoke.Invoke(itemMeg.dwCmd, itemMeg.vecStr);
						if (nRet <= 0)
						{
							RcfConnectCheck(nRet, var.first);
							TTRACE("[通信模块]发送消息失败,返回错误码[%d],  ID[%d]LL-O \r\n", nRet, static_cast<int>(itemMeg.dwCmd));
						}
					}
				}
			}
		}
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::SendHigherServer( _NotifyMessage &itemMeg )
{
	STRY;
	SCATCH;
	return -1;
}

ISOC_VOID XhBFISCommunicateSyncServerStationImp::Run()
{
	iCMSP_XmlParser xmlParser;
	CString strFMSConfigPath = GetWorkingDirectory();
	strFMSConfigPath += "\\Config\\iFMSConfig.xml";
	int timeInterval = 120;
	bool bRet = xmlParser.Load(strFMSConfigPath.GetBuffer(0));
	if (true == bRet)
	{
		TTRACE(" 成功加载插件配置文件\r\n");
		if (xmlParser.FindElem("FMS"))
		{
			xmlParser.IntoElem();
			if (xmlParser.FindElem("DiskSpace"))
			{
				timeInterval = xmlParser.GetAttribInt("timeInterval");
			}
		}
	}
	timeInterval *= 60;
	timeInterval *= 1000;
	STRY;
	std::set<std::string> dockMeg;
	while (false == m_bNeedStop)
	{
		STRY;
		boost::unique_lock<boost::mutex> locker(m_dockingMtx);
		if (m_dockingMegSet.size() <= 0)
		{
			CheckDiskSpace(timeInterval);
			m_dockingCondition.wait_for(locker, boost::chrono::seconds(5));
			continue;
			//m_dockingCondition.wait_for(locker, boost::chrono::milliseconds(1000 * 20));
		}
		else
		{
			dockMeg.swap(m_dockingMegSet);
		}
		SCATCH;
		
		for each (auto &var in dockMeg)
		{
			if (m_bNeedStop)
				break;

			DockingMessageHandle(var);
		}
		dockMeg.clear();
	}
	SCATCH;
}

int XhBFISCommunicateSyncServerStationImp::DoListenOn(IN long localIp, IN short localPort, IN DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (!m_pNetServer)
	{
		m_pNetServer = new iBFIS_CommunicationServer;
		m_pNetServer->SetRMICallbackSkin(this);
	}
	string strIp;
	long lIp = htonl(localIp);
	in_addr addr;
	addr.S_un.S_addr = lIp;
	strIp = inet_ntoa(addr);
	int nRet = m_pNetServer->Start(strIp.c_str(),localPort);
	if (dwReserved <= 0)
		m_localServerCheck.Start(strIp, localPort);
	return nRet;
	SCATCH;
	return -1;
}
int XhBFISCommunicateSyncServerStationImp::StopListen(IN DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (m_pNetServer)
	{
		m_pNetServer->Stop();
	}
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::OnConnected(HANDLE hContext)
{
	STRY;
	writeLock locker(m_connectMtx);
	m_mapClientContext.insert(std::make_pair(hContext, std::make_shared<ObjectRefCount<HANDLE> >(hContext)));
	return 1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::OnDisConnected(HANDLE hContext)
{
	char ip[30] = { 0 };
	STRY;
	writeLock locker(m_connectMtx);
	auto var = m_mapClientContext.find(hContext);
	if (var != m_mapClientContext.end())
	{
		std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
		m_mapClientContext.erase(var);
		locker.unlock();

		std::shared_ptr<RefCountInfo> refCount = refObj->GetRefInfo();
		if (refCount)
		{
			iBFIS_CommunicationServer::GetClientAddr(hContext, ip);
			TTRACE(" 连接断开 --- 对方IP地址[%s]\r\n", ip);

			refCount->DelRefObject(10);
		}
	}
	SCATCH;
	
	STRY;
	writeLock locker(m_connectUserClientMtx);
	auto userVar = m_mapUserClinetContext.find(hContext);
	if (userVar != m_mapUserClinetContext.end())
	{
		//std::shared_ptr<ObjectRefCount<HANDLE> > refObj = userVar->second;
		m_mapUserClinetContext.erase(userVar);
		locker.unlock();
		TTRACE(" 用户连接断开 --- 对方IP地址[%s]\r\n", ip);
		m_pClientDataTrafficSource->DisConnect(reinterpret_cast<UINT64>(hContext));
		return 1;
	}
	SCATCH;

	STRY;
	writeLock locker(m_connectBranchClientMtx);
	auto branchVar = m_mapBranchClinetContext.find(hContext);
	if (branchVar != m_mapBranchClinetContext.end())
	{
		//std::shared_ptr<ObjectRefCount<HANDLE> > refObj = branchVar->second;
		m_mapBranchClinetContext.erase(branchVar);
		locker.unlock();
		
		STRY;
		//删除网点信息
		
		std::map<string, std::shared_ptr<ObjectRefCount<HANDLE> > > mapBranchContextInfo;
		STRY;
		readLock lockerInfo(m_connectBranchClientInfoMtx);
		mapBranchContextInfo = m_mapBranchContextInfo;
		SCATCH;

		for each(auto &var in mapBranchContextInfo)
		{
			writeLock lockerInfo(m_connectBranchClientInfoMtx);
			auto branchInfoItor = m_mapBranchContextInfo.find(var.first);
			if (branchInfoItor != m_mapBranchContextInfo.end())
			{
				std::shared_ptr<ObjectRefCount<HANDLE> > refObj = branchInfoItor->second;
				if (refObj->m_custom == hContext)
				{
					m_mapBranchContextInfo.erase(branchInfoItor);
					lockerInfo.unlock();
					AddNotifyMsg(DBO_DEL, IBFIS_MSG_CLIENT_NOTIFY_DISKANDCONNECT, var.first);
					break;
				}
			}
		}
		SCATCH;
		TTRACE(" 网点连接断开 --- 对方IP地址[%s]\r\n", ip);
		m_pSyncServer->OnDisConnect(reinterpret_cast<UINT64>(hContext));
		return 1;
	}
	SCATCH;
}

int XhBFISCommunicateSyncServerStationImp::OnGotError(HANDLE hContext,int nErrorCode,std::string strErrorDes)
{
	STRY;

	return 1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::OnInvoke(HANDLE hContext,DWORD_PTR& d)
{
	STRY;
	if (LOCAL_MSG_SERVER_IS_ALIVE == d)
	{
#if 0
		bool bFound = false;
		iBFIS_SimpleCS   simpleCS;
		STRY;
		int key = GetArrayKey(hContext, CLINET_CONNET_DISTRIBUTION);
		boost::recursive_mutex::scoped_lock locker(m_arrayAllClinetContext[key].GetArraySimpleCS());
		auto itor = m_arrayAllClinetContext[key].GetContentItem(hContext);
		if (itor != nullptr)
		{
			bFound = true;
			simpleCS.EnterCS(itor->GetCSPtr(), __FUNCTION__);
		}
		SCATCH;

		if (bFound)
		{
			iBFIS_CommunicationInvoker invoke(hContext);
			return invoke.Invoke(d);
		}
#else
		return 1;
#endif
		return 0;
	}
	else
	{
		auto iter = m_mapTaskStation.find(d);
		if (iter != m_mapTaskStation.end())
		{
			int nRet = (iter->second)->OnRecvData(reinterpret_cast<UINT64>(hContext), d);
			if (nRet <= 0)
				TTRACE("命令[%d] 错误[%d] \r\n", static_cast<int>(d), nRet);
			return nRet;
		}
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::OnInvoke(HANDLE hContext,DWORD_PTR& d,std::string& s)
{
	STRY;
	auto iter = m_mapTaskStation.find(d);
	if (iter != m_mapTaskStation.end())
	{
		int nRet = (iter->second)->OnRecvData(reinterpret_cast<UINT64>(hContext),d,s);
		if (nRet <= 0)
			TTRACE("命令[%d] 错误[%d] 描述[%s] \r\n", static_cast<int>(d), nRet, s.c_str());

		if (d == MSG_LOGIN /*|| d == MSG_UPLOAD_BRANCHINFO*/ && nRet > 0)
		{
			TCHAR chIP[30] = { 0 };
			iBFIS_CommunicationServer::GetClientAddr(hContext, chIP);
			TTRACE(" 有新的连接连上1[%s] \r\n", chIP);

			STRY;
			readLock locker(m_connectMtx);
			auto var = m_mapClientContext.find(hContext);
			if (var != m_mapClientContext.end())
			{
				std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
				std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
				AutoObjectRefMgr refObject;
				if (refObject.AddRefCount(refInfo))
				{
					locker.unlock();
					writeLock lockerBranchClient(m_connectBranchClientMtx);
					m_mapBranchClinetContext.insert(std::make_pair(hContext, refObj));
				}
			}
			SCATCH;
		}
		return nRet;
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::OnInvoke(HANDLE hContext,DWORD_PTR& d1,std::vector<std::string>& v1)
{
	STRY;
	//iCMSP_SimpleLock myLock(&m_csLockClientContext,__FUNCTION__);
	auto iter = m_mapTaskStation.find(d1);
	if (iter != m_mapTaskStation.end())
	{
		if (d1 == IBFIS_MSG_CLIENT_LOGIN_2_SERVER)
		{
			char ip[30] = { 0 };
			iBFIS_CommunicationServer::GetClientAddr(hContext, ip);
			TTRACE("有新客户端登录[%s]\r\n", ip);
		}
		int nRet = (iter->second)->OnRecvData(reinterpret_cast<UINT64>(hContext),d1,v1);
		if (nRet <= 0)
		{
			std::string strDes;
			if (v1.size() > 0)
				strDes = v1[0];
			TTRACE("命令[%d] 错误[%d] 描述[%s] \r\n", static_cast<int>(d1), nRet, strDes.c_str());
		}
		if (d1 == IBFIS_MSG_CLIENT_LOGIN_2_SERVER && nRet > 0)
		{
			readLock locker(m_connectMtx);
			auto var = m_mapClientContext.find(hContext);
			if (var != m_mapClientContext.end())
			{
				std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
				std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
				AutoObjectRefMgr refObject;
				if (refObject.AddRefCount(refInfo))
				{
					locker.unlock();
					writeLock lockerUserClient(m_connectUserClientMtx);
					m_mapUserClinetContext.insert(std::make_pair(hContext, refObj));
				}
			}
		}
		else if ((d1 == MSG_LOGIN || d1 == MSG_UPLOAD_BRANCHINFO) && nRet > 0)
		{
			//保存与SyncClient通信的句柄
			STRY;
			BFIS::BranchInfo msg;
			if(msg.ParseFromString(v1[0]))
			{
				ST_BranchInfo stInfo(msg);
				STRY;

				readLock locker(m_connectMtx);
				auto var = m_mapClientContext.find(hContext);
				if (var != m_mapClientContext.end())
				{
					std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
					std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
					AutoObjectRefMgr refObject;
					if (refObject.AddRefCount(refInfo))
					{
						locker.unlock();
						writeLock lockerBranchClient(m_connectBranchClientInfoMtx);
						m_mapBranchContextInfo.insert(std::make_pair(stInfo.strBranchId, refObj));
						lockerBranchClient.unlock();
						AddNotifyMsg(DBO_ADD, IBFIS_MSG_CLIENT_NOTIFY_DISKANDCONNECT, stInfo.strBranchId);
					}
				}
				SCATCH;
			}
			SCATCH;

			STRY;
			if (MSG_LOGIN == d1)
			{
				char ip[30] = { 0 };
				iBFIS_CommunicationServer::GetClientAddr(hContext, ip);
				TTRACE(" 有新客户端登录[%s]\r\n", ip);

				readLock locker(m_connectMtx);
				auto var = m_mapClientContext.find(hContext);
				if (var != m_mapClientContext.end())
				{
					std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
					std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
					AutoObjectRefMgr refObject;
					if (refObject.AddRefCount(refInfo))
					{
						locker.unlock();
						writeLock lockerBranchClient(m_connectBranchClientMtx);
						m_mapBranchClinetContext.insert(std::make_pair(hContext, refObj));
					}
				}
			}
			SCATCH;
		}
		return nRet;
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::OnInvoke(HANDLE hContext,DWORD_PTR& d1,std::vector<std::string>& v1,std::vector<std::string>& v2, std::vector<std::string>& v3)
{
	STRY;
	auto iter = m_mapTaskStation.find(d1);
	if (iter != m_mapTaskStation.end())
	{
		int nRet = (iter->second)->OnRecvData(reinterpret_cast<UINT64>(hContext),d1,v1,v2,v3);
		if (nRet <= 0)
			TTRACE("命令[%d] 错误[%d] \r\n", static_cast<int>(d1), nRet);
		return nRet;
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::OnInvoke(HANDLE hContext,std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2)
{
	STRY;
	auto iter = m_mapTaskStation.find(v1[1]);
	if (iter != m_mapTaskStation.end())
	{
		int nRet = (iter->second)->OnRecvData(reinterpret_cast<UINT64>(hContext),v1,v2);
		if (nRet <= 0)
		{
			std::string strDes;
			if (v2.size() > 0)
				strDes = v2[0];
			TTRACE("命令[%d] 错误[%d] 描述[%s] \r\n", static_cast<int>(v1[1]), nRet, strDes.c_str());
		}
			
		return nRet;
	}
	return -1;
	SCATCH;
	return -1;
}
int XhBFISCommunicateSyncServerStationImp::OnInvoke(HANDLE hContext,DWORD_PTR& d1,DWORD_PTR& d2,std::string& s)
{
	STRY;
	auto iter = m_mapTaskStation.find(d1);
	if (iter != m_mapTaskStation.end())
	{
		int nRet = (iter->second)->OnRecvData(reinterpret_cast<UINT64>(hContext),d1,d2,s);
		if (nRet <= 0)
			TTRACE("命令[%d] 错误[%d] 描述[%s] \r\n", static_cast<int>(d1), nRet, s.c_str());
		return nRet;
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::DoSendData(IN HANDLE hClient, IN DWORD_PTR d1,IN DWORD_PTR d2, IN string s, IN DWORD_PTR dwReserved /*= 0*/)
{
	return 1;
} 
int XhBFISCommunicateSyncServerStationImp::DoSendData(IN HANDLE hClient, std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2, IN DWORD_PTR dwReserved /*= 0*/)
{
	return 1;
}

int XhBFISCommunicateSyncServerStationImp::DoSendData(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN BYTE * pData, IN int nDataSize, IN DWORD_PTR dwReserved)
{
	switch (d1)
	{
	case IBFIS_MSG_CLIENT_GET_EMPLOYEEPURVIEWINFO:
	    {
			return SendLoginQueryInfo(hClient, enType, d1, pData, nDataSize, dwReserved);
	    }
	}
	return 0;
}

int XhBFISCommunicateSyncServerStationImp::DoSendData(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN string s1, IN DWORD_PTR dwReserved /*= 0*/)
{
	if (IBFIS_MSG_CLIENT_NOTIFY_BUSINESSDOCKMAGINFO == d1)
	{
		DISPLAY_LOG("对接模块", "收到上级的对接消息", "成功", "", 1);
		boost::unique_lock<boost::mutex> locker(m_dockingMtx);
		m_dockingMegSet.insert(s1);
		m_dockingCondition.notify_one();
		//对接消息要事实相应，不放在队列中
		//auto future = boost::async(boost::launch::async, [s1, this]()
		//{
		//	DockingMessageHandle(s1);
		//});
		return 1;
	}
	else if (IBFIS_MSG_CLIENT_IS_ALIVE == d1) 
	{
		int nRet = -1;
		STRY;
		readLock locker(m_connectMtx);
		auto var = m_mapClientContext.find(hClient);
		if (var != m_mapClientContext.end())
		{
			std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
			std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
			AutoObjectRefMgr refObject;
			if (refObject.AddRefCount(refInfo))
			{
				locker.unlock();
				STRY;
				nRet = XhDoSendData(hClient, enType, d1, s1);
				SCATCH;
			}
		}
		if (nRet <= 0)
		{
			TTRACE(" 回复客户端心跳失败[%d]\r\n", nRet);
		}
		SCATCH;
		return nRet;
		//return 1;
	}
	else if (MSG_IS_ALIVE == d1)
	{
		int nRet = 0;
		STRY;
		readLock locker(m_connectMtx);
		auto var = m_mapClientContext.find(hClient);
		if (var != m_mapClientContext.end())
		{
			std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
			std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
			AutoObjectRefMgr refObject;
			if (refObject.AddRefCount(refInfo))
			{
				locker.unlock();
				STRY;
				nRet = XhDoSendData(hClient, d1, s1);
				SCATCH;
			}
		}
		if (nRet <= 0)
		{
			TTRACE(" 回复下级心跳消息失败[%d]\r\n", nRet);
		}
		SCATCH;
		return nRet;
	}
	else if (MSG_ISSUED_ROLEPURVIEW == d1)
	{
		STRY;
		readLock locker(m_connectMtx);
		auto var = m_mapClientContext.find(hClient);
		if (var != m_mapClientContext.end())
		{
			std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
			std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
			AutoObjectRefMgr refObject;
			if (refObject.AddRefCount(refInfo))
			{
				locker.unlock();
				STRY;
				iBFIS_CommunicationInvoker invoke(hClient);
				return invoke.Invoke(d1, s1);
				SCATCH;
			}
		}
		SCATCH;
		SFTRACE("外出设备同步", " 同步角色权限[%s]，未找到对应链接\r\n", s1.c_str());
		return 0;
	}
	return 1;
}

int XhBFISCommunicateSyncServerStationImp::DoSendData(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN std::vector<std::string>& v1, IN DWORD_PTR dwReserved /*= 0*/)
{
	switch (d1)
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
		return SendLoginQueryInfo(hClient, enType, d1, v1, dwReserved);
	}
	case IBFIS_MSG_CLIENT_QUERY_OPERATELOGINFO:
	{
		return ClinetQueryOperateLogInfo(hClient, enType, d1, v1, dwReserved);
	}
	case IBFIS_MSG_CLIENT_NOTIFY_DISKANDCONNECT:
	{
		return ClinetNotifyDiskAndConnect(hClient, enType, d1, v1, dwReserved);
	}
	default:
		return SendDefaultInfo(hClient, enType, d1, v1, dwReserved);
	}
}

void XhBFISCommunicateSyncServerStationImp::CheckDiskSpace(int timeInterval)
{
	static DWORD preTimeTick = GetTickCount();
	DWORD currTimeTick = GetTickCount();
	if (currTimeTick < preTimeTick)
	{
		preTimeTick = currTimeTick;
		return;
	}
	else if ((currTimeTick - preTimeTick) >= timeInterval)
	{
		preTimeTick = currTimeTick;
		std::map<HANDLE, std::shared_ptr<ObjectRefCount<HANDLE> > >  mapUserClinetContext;
		STRY;
		writeLock locker(m_connectUserClientMtx);
		mapUserClinetContext = m_mapUserClinetContext;
		SCATCH;
		STRY;
		for (auto var  = mapUserClinetContext.begin(); var != mapUserClinetContext.end(); ++var)
		{
			CheckDiskSpaceInfo(var->first);
		}
		SCATCH;
	}
}

int XhBFISCommunicateSyncServerStationImp::XhDoSendData( IN HANDLE hClient, IN DBOperType enType,IN DWORD_PTR d1, IN string& s1, IN DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	//客户端不接收业务方面的通知
	if (d1 == IBFIS_MSG_CLIENT_NOTIFY_BUSINESSINFO || d1 == IBFIS_MSG_CLIENT_NOTIFY_BUSINESSFILEINFO
		|| d1 == IBFIS_MSG_CLIENT_NOTIFY_BUSINESSRELATEINFO)
	{
		return 1;
	}
	DWORD_PTR d2 = static_cast<DWORD_PTR>(enType);
	string strMsg = Cmd2Msg(enType,d1);
	if (hClient == nullptr)
	{
		char szMsg[255] = {0};
		sprintf(szMsg,"%s[%d]传入客户端句柄为NULL,%s失败",__FUNCTION__,__LINE__,strMsg.c_str());
		DISPLAY_LOG("服务端模块",szMsg,"","",0);
		return -1;
	}
	iBFIS_CommunicationInvoker invoke(hClient);
	int nRet = invoke.Invoke(d1,d2,s1);
	if (nRet <= 0)
	{
		RcfConnectCheck(nRet, hClient);
		char szMsg[255] = { 0 };
		if (strMsg == "")
		{
			TTRACE("[通信模块]发送消息失败,返回错误码[%d],  ID[%d]1 \r\n", nRet, static_cast<int>(d1));
		}
		else
		{
			sprintf(szMsg, "[通信模块]发送消息失败,返回错误码[%d],功能[%s]1", nRet, strMsg.c_str());
			DISPLAY_LOG("服务端模块", szMsg, "", "", 0);
		}
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::XhDoSendData( IN HANDLE hClient, IN DBOperType enType,IN DWORD_PTR d1, IN std::vector<std::string>& v1, IN DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	//客户端不接收业务方面的通知
	if (d1 == IBFIS_MSG_CLIENT_NOTIFY_BUSINESSINFO || d1 == IBFIS_MSG_CLIENT_NOTIFY_BUSINESSFILEINFO 
		|| d1 == IBFIS_MSG_CLIENT_NOTIFY_BUSINESSRELATEINFO)
	{
		return 1;
	}
	string strMsg = Cmd2Msg(enType,d1);
	std::vector<DWORD_PTR> vecCmd;
	if (hClient == nullptr)
	{
		char szMsg[255] = {0};
		sprintf(szMsg,"%s[%d]传入客户端句柄为NULL,%s失败",__FUNCTION__,__LINE__,strMsg.c_str());
		DISPLAY_LOG("服务端模块",szMsg,"","",0);
		return -1;
	}
	vecCmd.push_back(static_cast<DWORD_PTR>(enType));
	vecCmd.push_back(d1);
	iBFIS_CommunicationInvoker invoke(hClient);
	int nRet = invoke.Invoke(vecCmd,v1);
	if (nRet <= 0)
	{
		RcfConnectCheck(nRet, hClient);
		if (strMsg == "")
		{
			TTRACE("[通信模块]发送消息失败,返回错误码[%d], ID[%d]2 \r\n", nRet, static_cast<int>(d1)); 
		}
		else
		{
			char szMsg[255] = { 0 };
			sprintf(szMsg, "[通信模块]发送消息失败,返回错误码[%d] 功能[%s]2", nRet, strMsg.c_str());
			DISPLAY_LOG("服务端模块", szMsg, "", "", 0);
		}
		return nRet;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::XhDoSendData( IN HANDLE hClient, IN DWORD_PTR d1,IN DWORD_PTR d2, IN string s, IN DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if (hClient == nullptr)
	{
		DISPLAY_LOG("服务端模块","无法发送数据","传入客户端句柄为NULL","",0);
		return -1;
	}
	iBFIS_CommunicationInvoker invoke(hClient);
	int nRet = invoke.Invoke(d1,d2,s);
	if (nRet <= 0)
	{
		RcfConnectCheck(nRet, hClient);
		TTRACE("[通信模块]发送消息失败,返回错误码[%d], ID[%d]3 \r\n", nRet, static_cast<int>(d1));
	}
	
	return nRet;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::XhDoSendData( IN HANDLE hClient, std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2, IN DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if (hClient == nullptr /*|| v1.size() != 2*/)
	{
		DISPLAY_LOG("服务端模块","无法发送数据","传入客户端句柄为NULL","",0);
		return -1;
	}
	iBFIS_CommunicationInvoker invoke(hClient);
	int nRet = invoke.Invoke(v1,v2);
	if (nRet <= 0)
	{
		RcfConnectCheck(nRet, hClient);
		TTRACE("[通信模块]发送消息失败,返回错误码[%d]4 \r\n", nRet);
	}
	return nRet;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::XhDoSendData(IN HANDLE hClient, IN DWORD_PTR d1, IN string s, IN DWORD_PTR dwReserved)
{
	STRY;
	if (hClient == nullptr /*|| v1.size() != 2*/)
	{
		DISPLAY_LOG("服务端模块", "无法发送数据", "传入客户端句柄为NULL", "", 0);
		return -1;
	}
	iBFIS_CommunicationInvoker invoke(hClient);
	int nRet = invoke.Invoke(d1, s);
	if (nRet <= 0)
	{
		RcfConnectCheck(nRet, hClient);
		TTRACE("[通信模块]发送消息失败,返回错误码[%d] ID[%d]5 \r\n", nRet, static_cast<int>(d1));
	}
	return nRet;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::ExtendFunction(IN const int nExtendType, IN DWORD_PTR dwExtendData)
{
	STRY;

	return 1;
	SCATCH;
	return -1;
}

string XhBFISCommunicateSyncServerStationImp::Cmd2Msg(IN DBOperType enType,IN DWORD_PTR dwCmd)
{
	STRY;
	string strInfo;
	switch(enType)
	{
	case DBO_ADD:
		strInfo = _T("增加");
		break;
	case DBO_DEL:
		strInfo = _T("删除");
		break;
	case DBO_UPDATE:
		strInfo = _T("更新");
		break;
	case DBO_QUERY:
		strInfo = _T("查询");
	default:
		return _T("");
	}
	switch(dwCmd)
	{
	case IBFIS_MSG_CLIENT_NOTIFY_BRANCHINFO:
		strInfo += _T("网点信息");
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_PRODUCEINFO:
		strInfo += _T("产品信息");
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_USERMAPINFO:	
		strInfo += _T("用户关系映射信息");
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_ROLEINFO:	
		strInfo += _T("角色信息");
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_PURVIEWINFO:
		strInfo += _T("权限信息");
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO:	
		strInfo += _T("角色权限信息");
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEINFO:		
		strInfo += _T("员工信息");
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEPURVIEWINFO:	
		strInfo += _T("员工权限信息");
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_CLIENTINFO:		
		strInfo += _T("客户信息");
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_BUSINESSINFO:
		strInfo += _T("业务信息");
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_BUSINESSFILEINFO:
		strInfo += _T("业务文件信息");
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_BUSINESSRELATEINFO:
		strInfo += _T("业务关联信息");
		break;
	default:
		return _T("");
	}
	return strInfo;
	SCATCH;
	return _T("");
}

int XhBFISCommunicateSyncServerStationImp::RegisterRecvMessageCallbackSkin(IN DWORD_PTR dwCmdID,IN IBFISTaskStation* pProcessStation,IN ISOC_DWORDPTR dwReserved /*= 0*/)
{
	STRY;
	m_mapTaskStation[dwCmdID] = pProcessStation;
	return 1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::UnRegisterRecvMessageCallbackSkin(IN DWORD_PTR dwCmdID,IN IBFISTaskStation* pProcessStation,IN ISOC_DWORDPTR dwReserved /*= 0*/)
{
	STRY;
	auto iter = m_mapTaskStation.find(dwCmdID);
	if (iter != m_mapTaskStation.end())
	{
		m_mapTaskStation.erase(iter);
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::AddNotifyMsg(IN DBOperType enType,IN DWORD_PTR dwCmdID,IN string s1,IN DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	//iCMSP_SimpleLock lockNotifyMsgContext(&m_csNotifyMsg,__FUNCTION__);
	//_NotifyMessage stMsg;
	//stMsg.nType = static_cast<int>(enType);
	//stMsg.dwCmd = dwCmdID;
	//stMsg.vecStr.push_back(s1);
	//stMsg.dwReserved = dwReserved;
	//m_vecNotifyMsg.push_back(stMsg);

	ST_CallBackInfo info;
	info.pSelfCallback = NotifyMegEnTrance;
	info.pCallBackAddr = this;
	info.vecStrArry.push_back(s1);
	info.bIsQueue = false;
	info.vecDwordArry.push_back(dwCmdID);
	info.vecDwordArry.push_back(enType);
	info.vecDwordArry.push_back(dwReserved);
	m_pCallbackManager->AddCallBack(info, __FUNCTION__);

	return 1;
	SCATCH;
	return -1;
}



int XhBFISCommunicateSyncServerStationImp::AddNotifyMsg(IN DBOperType enType,IN DWORD_PTR dwCmdID,IN std::vector<std::string>& v1,IN DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (dwCmdID == IBFIS_MSG_CLIENT_NOTIFY_RECORDSTATUS)
	{
		if (m_strPluginName != "JZ")
		{
			HandleDockingRecvVideoStatus(v1);
		}
		return 1;
	}
	//iCMSP_SimpleLock lockNotifyMsgContext(&m_csNotifyMsg,__FUNCTION__);
	//_NotifyMessage stMsg;
	//stMsg.nType = static_cast<int>(enType);
	//stMsg.dwCmd = dwCmdID;
	//stMsg.vecStr = v1;
	//stMsg.dwReserved = dwReserved;
	//m_vecNotifyMsg.push_back(stMsg);

	ST_CallBackInfo info;
	info.pSelfCallback = NotifyMegEnTrance;
	info.pCallBackAddr = this;
	info.vecStrArry = v1;
	info.bIsQueue = false;
	info.vecDwordArry.push_back(dwCmdID);
	info.vecDwordArry.push_back(enType);
	info.vecDwordArry.push_back(dwReserved);
	m_pCallbackManager->AddCallBack(info, __FUNCTION__);
	return 1;
	SCATCH;
	return -1;
}
int XhBFISCommunicateSyncServerStationImp::SetOfflineSyscData(vector<ST_BranchInfo>& vecBranchInfo, vector<ST_EmployeeInfo>& vecEmployeeInfo)
{
	STRY;
	if (!vecBranchInfo.empty())
	{
		m_vecBranchInfo = vecBranchInfo;
	}
	if (!vecEmployeeInfo.empty())
	{
		m_vecEmployeeInfo = vecEmployeeInfo;
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISCommunicateSyncServerStationImp::GetOfflineSyscData(vector<ST_BranchInfo>& vecBranchInfo, vector<ST_EmployeeInfo>& vecEmployeeInfo)
{
	STRY;
	if (!m_vecBranchInfo.empty())
	{
		vecBranchInfo = m_vecBranchInfo;
		m_vecBranchInfo.clear();
	}
	if (!m_vecEmployeeInfo.empty())
	{
		vecEmployeeInfo = m_vecEmployeeInfo;
		m_vecEmployeeInfo.clear();
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISCommunicateSyncServerStationImp::CheckIsTopServer(int nNum)
{
	m_nServerType = nNum;
	return TRUE;
}
BOOL XhBFISCommunicateSyncServerStationImp::PraseGetKeyValueData()
{
	STRY;
	if (m_pCache)
	{
		vector<ST_KeyValueInfo> vecKeyValueInfo;
		if (m_pCache->QueryKeyValueInfoByTypeAndCode("SynchroSetting","",vecKeyValueInfo))
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
			if (XmlParser.FindElem("SyncSet"))
			{
				XmlParser.IntoElem();
				if (XmlParser.FindElem("SynchroInfoPath"))
				{
					m_stBasicSetting.strSynchroInfoPath = XmlParser.GetData();
				}
				if (XmlParser.FindElem("AutomaticSynchroChecked"))
				{
					m_stBasicSetting.nAutomaticSynchroChecked = XmlParser.GetDataInt();
				}
				if (XmlParser.FindElem("SynchroTime"))
				{
					m_stBasicSetting.strSynchroTime = XmlParser.GetData();
				} 
				if (XmlParser.FindElem("CoreSystemIP"))
				{
					m_stBasicSetting.strCoreSystemIP = XmlParser.GetData();
				} 
				if (XmlParser.FindElem("FinancialSystemIP"))
				{
					m_stBasicSetting.strFinancialSystemIP = XmlParser.GetData();
				} 
				if (XmlParser.FindElem("PublicPort"))
				{
					m_stBasicSetting.nPublicPort = XmlParser.GetDataInt();
				} 
			}
			vecKeyValueInfo.clear();
		}       
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
BOOL XhBFISCommunicateSyncServerStationImp::ReviewBusinessSerialNum(ST_BusinessDockMsgInfo& stBusinessDockMsgInfo)
{
	STRY;
	//vector<string> vecSerialNumList;
	char* pLine;
	char decollEnterAndLF[] = {124};
	pLine = strtok((char*)stBusinessDockMsgInfo.strExtendedInfo.c_str(),decollEnterAndLF);
	while(pLine != NULL)
	{ 
		ST_BusinessQueryParam stBusinessQueryParam;
		stBusinessQueryParam.strSerialNumber = pLine;
		vector<ST_BusinessInfo> vecBusinessInfo;
		int nCount = 0;
		if (m_pCache && m_pCache->QueryBusinessInfoByCondition(stBusinessQueryParam, vecBusinessInfo, nCount))
		{
			vecBusinessInfo[0].nExtendedInfo = 1;
			m_pCache->ManageBusinessInfo(DBO_UPDATE, vecBusinessInfo[0]);
		}
		//vecSerialNumList.push_back(pLine);
		pLine = strtok(NULL,decollEnterAndLF);

	}
	/*for (auto iter = vecSerialNumList.begin();iter != vecSerialNumList.end();++iter)
	{
		ST_BusinessQueryParam stBusinessQueryParam;
		stBusinessQueryParam.strSerialNumber = *iter;
		vector<ST_BusinessInfo> vecBusinessInfo;
		int nCount = 0;
		if (m_pCache && m_pCache->QueryBusinessInfoByCondition(stBusinessQueryParam,vecBusinessInfo,nCount))
		{
			vecBusinessInfo[0].nExtendedInfo = 1;
			m_pCache->ManageBusinessInfo(DBO_UPDATE,vecBusinessInfo[0]);
		}
	}*/
	return TRUE;
	SCATCH;
	return FALSE;
}
void XhBFISCommunicateSyncServerStationImp::GetRandomSerialNum(string& strRandomSerialNum)
{
	STRY;
	CTime t = CTime::GetCurrentTime(); //获取系统日期
	CString strDateTime;
	strDateTime.Format("%04d%02d%02d%02d%02d%02d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	strRandomSerialNum = /*m_stBranchInfo.strJDBRID + */strDateTime.GetBuffer(0);
	SCATCH;
}

bool XhBFISCommunicateSyncServerStationImp::CreateBankDockingPlugin()
{
	iCMSP_XmlParser xmlParser;
	std::string fullPath;
	STRY;
	fullPath = boost::filesystem::initial_path<boost::filesystem::path>().string();
	SCATCH;
	if (fullPath.empty())
	{
		fullPath = "./Config/BankPluginConfig.xml";
	}
	else
	{
		fullPath = (boost::format("%1%%2%") % fullPath %"\\Config\\BankPluginConfig.xml").str();
	}

	TTRACE(" %s 加载插件配置文件Path[%s]\r\n", MODULE_NAME, fullPath.c_str());
	bool bRet = xmlParser.Load(fullPath.c_str());
	int nRet = -1;
	if (false == bRet)
	{
		TTRACE(" %s 加载插件配置文件失败 %s\r\n", MODULE_NAME, __FUNCTION__);
		return false;
	}
	bRet = xmlParser.FindElem(_T("bankplugin"));
	if (false == bRet)
	{
		TTRACE(" %s 插件配置文查找元素失败 %s\r\n",MODULE_NAME,__FUNCTION__);
		return false;
	}
	m_strPluginName = xmlParser.GetAttrib(_T("pluginName"));
	if (m_strPluginName.IsEmpty())
	{
		TTRACE(" %s 银行插件名字为空 %s\r\n",MODULE_NAME,__FUNCTION__);
		return false;
	}

	iSOC_MonFactoryManagement fmt;
	m_pBankPluginInter = static_cast<IBFISBankPluginInterface*>(fmt.CreateObject(OBJECT_TYPE_BFIS_BASE_PLUGIN, m_strPluginName,__FUNCTION__));
	if (nullptr == m_pBankPluginInter)
	{
		TTRACE(" %s 银行插件创建失败 %s\r\n",MODULE_NAME,__FUNCTION__);
		return false;
	}
	m_pBankPluginInter->SetMegCb(this);
	m_pBankPluginInter->SetParam(m_stBasicSetting.strFinancialSystemIP,m_stBasicSetting.strCoreSystemIP);
	nRet = m_pBankPluginInter->StartDockListen(m_stBasicSetting.nPublicPort);
	if (nRet != 1)
	{
		TTRACE(" %s 监听失败 %s 错误码：%d \r\n",MODULE_NAME,__FUNCTION__,nRet);
		return false;
	}
	return true;
}
void XhBFISCommunicateSyncServerStationImp::MsgCallback( ST_BusinessDockMsgInfo* pBusinessDockMsgInfo,const IBFIS_DWORDPTR dwCookie,IBFIS_DWORDPTR dwResevered )
{
	STRY;
	STRY;
	m_stBusinessDockMsgInfo = *pBusinessDockMsgInfo;
	if (pBusinessDockMsgInfo->nSystemType == 4)
	{
		ReviewBusinessSerialNum(*pBusinessDockMsgInfo);
	}
	if (pBusinessDockMsgInfo->nSystemType == 1)
	{
		string strRecvMsg = "0000";
		m_pBankPluginInter->SendDataToBusinessSystem((BYTE*)strRecvMsg.c_str(), strRecvMsg.size());
	}
	SCATCH;
	string strInfo;
	if(pBusinessDockMsgInfo->ConvertToString(strInfo))
	{
		DISPLAY_LOG("通知", "[更新通知]收到对接信息", "成功", "", 1);
		boost::unique_lock<boost::mutex> locker(m_dockingMtx);
		m_dockingMegSet.insert(strInfo);
		m_dockingCondition.notify_one();
		//对接消息要事实相应，不放在队列中
		//auto future = boost::async(boost::launch::async, [strInfo, this]()
		//{
		//	DockingMessageHandle(strInfo);
		//});
		return;
	}
	else
	{
		SFTRACE("Docking", "[更新通知]收到对接信息转换失败 strCredenitialNum[%s]strChannelSerialNum[%s]\r\n", pBusinessDockMsgInfo->strCredenitialNum.c_str(), pBusinessDockMsgInfo->strChannelSerialNum.c_str());
	}
	return;
	SCATCH;
	return;
}
void XhBFISCommunicateSyncServerStationImp::GetRecvMessage(string& strRecvMsg,string strSucessedFlag,string strDescribeInfo)
{
	string strRspCode = strSucessedFlag;
	//string strVideoSerialNum;
	CString strMsgXml;
	if (m_stBusinessDockMsgInfo.nBootFlag == 2)
	{
		strMsgXml =_T("<?xml version=\"1.0\" encoding=\"GB18030\"?><root><resp><RspCode>%s</RspCode><RspMsg>%s</RspMsg><VideoSerialNum>%s</VideoSerialNum><BootFlag>%d</BootFlag></resp></root>");
	}
	else
	{
		strMsgXml =_T("<?xml version=\"1.0\" encoding=\"GB18030\"?><root><resp><RspCode>%s</RspCode><RspMsg>%s</RspMsg><BootFlag>%d</BootFlag></resp></root>");
	}
	if(strSucessedFlag == "1")
	{
		strRspCode = "000000";
	}
	else if(strSucessedFlag == "0")
	{
		strRspCode = "000001";
	}
	//GetRandomSerialNum(strVideoSerialNum);
	CString strMsg;
	if (m_stBusinessDockMsgInfo.nBootFlag == 2)
	{
		strMsg.Format(strMsgXml,strRspCode.c_str(),strDescribeInfo.c_str(),m_stBusinessDockMsgInfo.strIBFISSerialNum.c_str(), m_stBusinessDockMsgInfo.nBootFlag);
	}
	else
	{
		strMsg.Format(strMsgXml,strRspCode.c_str(),strDescribeInfo.c_str(),m_stBusinessDockMsgInfo.nBootFlag);
	}
	strRecvMsg = strMsg.GetBuffer(0);
}
int XhBFISCommunicateSyncServerStationImp::AddConnectAndDiskStatus(IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved)
{
	bool bFind = false;
	std::string strInfo;
	STRY;
	readLock locker(m_connectBranchClientInfoMtx);
	auto var = m_mapBranchContextInfo.find(vecParam[0]);
	if (var != m_mapBranchContextInfo.end())
	{
		std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
		std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
		AutoObjectRefMgr refObject;
		if (refObject.AddRefCount(refInfo))
		{
			locker.unlock();
			if (XhDoSendData(refObj->m_custom, static_cast<DBOperType>(enType), dwCmd, strInfo, dwReserved) > 0)
			{
				bFind = true;
			}
		}
	}
	SCATCH;

	if (bFind)
		SendMegToAllClinet(DBO_UPDATE, dwCmd, strInfo, dwReserved);

	return 1;
}
int XhBFISCommunicateSyncServerStationImp::DelConnectAndDiskStatus(IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved)
{
	STRY;
	ST_DiskAndConnectStatus stDiskAndConnectStatus;
	stDiskAndConnectStatus.nConnectStatus = 0;
	stDiskAndConnectStatus.strBranchId = vecParam[0];
	std::string strStatus;
	if(stDiskAndConnectStatus.ConvertToString(strStatus))
	{
		SendMegToAllClinet(DBO_UPDATE, dwCmd, strStatus, dwReserved);
	}
	else
	{
		DISPLAY_LOG("查询","[查询信息]查询磁盘内存信息","解析失败","",0);
	}
	SCATCH;
	return 1;
}
int XhBFISCommunicateSyncServerStationImp::QueryConnectAndDiskStatus(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved)
{
	ST_DiskAndConnectStatus stDiskAndConnectStatus;
	vector<string> vecdisk;
	string strStatus;
	if (m_pCache)
	{
		vector<ST_KeyValueInfo> vecKeyValueInfo;
		if (m_pCache->QueryKeyValueInfoByTypeAndCode("DiskSetting","",vecKeyValueInfo) > 0)
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
			if (XmlParser.FindElem("DiskSet"))
			{
				XmlParser.IntoElem();
				while (XmlParser.FindElem("Drive"))
				{
					string strDisk;
					strDisk = XmlParser.GetData() + "\\";
					vecdisk.push_back(strDisk);
				}
			}
			vecKeyValueInfo.clear();
		} 
	}
	if (m_pCache && m_pCache->QueryDeskStatus(vecdisk,stDiskAndConnectStatus.nDiskTatolSpace,stDiskAndConnectStatus.nDiskFreeSpace))
	{
		stDiskAndConnectStatus.nConnectStatus = 1;
		stDiskAndConnectStatus.strBranchId = m_strLocalBranchId;
		if(stDiskAndConnectStatus.ConvertToString(strStatus))
		{
			SendMegToClinet(hClient, DBO_UPDATE, dwCmd, strStatus, dwReserved);
		}
		else
		{
			DISPLAY_LOG("查询","[查询信息]查询磁盘内存信息","解析失败","",0);
		}	
	}

	STRY;

	std::map<string, std::shared_ptr<ObjectRefCount<HANDLE> > > mapBranchContextInfo;
	STRY;
	readLock locker(m_connectBranchClientInfoMtx);
	mapBranchContextInfo = m_mapBranchContextInfo;
	SCATCH;

	for each (auto &var in  mapBranchContextInfo)
	{
		readLock locker(m_connectBranchClientInfoMtx);
		auto itor = m_mapBranchContextInfo.find(var.first);
		if (itor != m_mapBranchContextInfo.end())
		{
			std::shared_ptr<ObjectRefCount<HANDLE> > refObj = itor->second;
			std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
			AutoObjectRefMgr refObject;
			if (refObject.AddRefCount(refInfo))
			{
				locker.unlock();
				string strInfo;
				if (XhDoSendData(refObj->m_custom, static_cast<DBOperType>(enType), dwCmd, strInfo, dwReserved) > 0)
				{
					SendMegToClinet(hClient, DBO_UPDATE, dwCmd, strInfo, dwReserved);
				}
			}
		}
	}
	SCATCH;
	return 1;
}

int XhBFISCommunicateSyncServerStationImp::CheckDiskSpaceInfo(IN HANDLE hClient, IN DWORD_PTR dwReserved)
{
	STRY;
	ST_DiskAndConnectStatus stDiskAndConnectStatus;
	vector<string> vecdisk;
	string strStatus;
	if (m_pCache)
	{
		vector<ST_KeyValueInfo> vecKeyValueInfo;
		if (m_pCache->QueryKeyValueInfoByTypeAndCode("DiskSetting", "", vecKeyValueInfo) > 0)
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
			strxml.Format("%s", vecKeyValueInfo[0].strValue.c_str());
			iCMSP_XmlParser XmlParser;
			XmlParser.SetDoc(strxml, strxml.GetLength());
			if (XmlParser.FindElem("DiskSet"))
			{
				XmlParser.IntoElem();
				while (XmlParser.FindElem("Drive"))
				{
					string strDisk;
					strDisk = XmlParser.GetData() + "\\";
					vecdisk.push_back(strDisk);
				}
			}
			vecKeyValueInfo.clear();
		}
	}
	if (m_pCache && m_pCache->QueryDeskStatus(vecdisk, stDiskAndConnectStatus.nDiskTatolSpace, stDiskAndConnectStatus.nDiskFreeSpace))
	{
		stDiskAndConnectStatus.nConnectStatus = 1;
		stDiskAndConnectStatus.strBranchId = m_strLocalBranchId;
		if (stDiskAndConnectStatus.ConvertToString(strStatus))
		{
			return SendMegToClinet(hClient, DBO_UPDATE, IBFIS_MSG_CLIENT_NOTIFY_DISKANDCONNECT, strStatus, dwReserved);
		}
		else
		{
			DISPLAY_LOG("查询", "[查询信息]查询磁盘内存信息", "解析失败", "", 0);
		}
	}
	SCATCH;
	return -1;
}

int XhBFISCommunicateSyncServerStationImp::SendLoginQueryInfo(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN BYTE * pData, IN int nDataSize, IN DWORD_PTR dwReserved)
{
	int nRet = -2000;
	STRY;
	readLock locker(m_connectMtx);
	auto var = m_mapClientContext.find(hClient);
	if (var != m_mapClientContext.end())
	{
		std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
		std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
		AutoObjectRefMgr refObject;
		if (refObject.AddRefCount(refInfo))
		{
			locker.unlock();
			iBFIS_CommunicationInvoker invoke(hClient);
			if (dwReserved > 0)
			{
				nRet = invoke.Invoke(d1, pData, nDataSize);
				if (nRet <= 0)
				{
					RcfConnectCheck(nRet, hClient);
					TTRACE("[通信模块]发送消息失败,返回错误码[%d] ID[%d]Login \r\n", nRet, static_cast<int>(d1));
				}
			}
		}
	}
	else
	{
		SFTRACE("OnRecvData", "未发现对应句柄[%u] 错误码[%d]\r\n", hClient, nRet);
	}
	SCATCH;
	return nRet;
}

int XhBFISCommunicateSyncServerStationImp::SendDefaultInfo(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN std::vector<std::string>& v1, IN DWORD_PTR dwReserved)
{
	STRY;
	readLock locker(m_connectMtx);
	auto var = m_mapClientContext.find(hClient);
	if (var != m_mapClientContext.end())
	{
		std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
		std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
		AutoObjectRefMgr refObject;
		if (refObject.AddRefCount(refInfo))
		{
			locker.unlock();
			iBFIS_CommunicationInvoker invoke(hClient);
			return invoke.Invoke(d1, v1);
		}
	}
	SCATCH;
	return -2000;
}

int XhBFISCommunicateSyncServerStationImp::SendLoginQueryInfo(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN std::vector<std::string>& v1, IN DWORD_PTR dwReserved)
{
	int nRet = -2000;

	STRY;
	readLock locker(m_connectMtx);
	auto var = m_mapClientContext.find(hClient);
	if (var != m_mapClientContext.end())
	{
		std::shared_ptr<ObjectRefCount<HANDLE> > refObj = var->second;
		std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
		AutoObjectRefMgr refObject;
		if (refObject.AddRefCount(refInfo))
		{
			locker.unlock();
			iBFIS_CommunicationInvoker invoke(hClient);
			if (dwReserved > 0)
			{
				nRet = invoke.Invoke(d1, v1);
				if (nRet <= 0)
				{
					RcfConnectCheck(nRet, hClient);
					TTRACE("[通信模块]发送消息失败,返回错误码[%d] ID[%d]Login1\r\n", nRet, static_cast<int>(d1));
				}
			}
			else
			{
				std::string strDes;
				if (v1.size() == 1)
					strDes = v1[0];
				nRet = invoke.Invoke(d1, dwReserved, strDes);
				if (nRet <= 0)
				{
					RcfConnectCheck(nRet, hClient);
					TTRACE("[通信模块]发送消息失败,返回错误码[%d] ID[%d]Login1\r\n", nRet, static_cast<int>(d1));
				}
			}
		}
	}
	else
	{
		SFTRACE("OnRecvData", "未发现对应句柄[%u] 错误码[%d]\r\n", hClient, nRet);
	}
	SCATCH;
	return nRet;
}

void XhBFISCommunicateSyncServerStationImp::NotifyMegHandle( ST_CallBackInfo stCallBackInfo )
{
	STRY;
	if (stCallBackInfo.vecDwordArry.size() < 3)
	{
		char szMeg[255] = {0};
		sprintf(szMeg,"参数个数不对[%d]", stCallBackInfo.vecDwordArry.size());
		DISPLAY_LOG("对接模块",szMeg,"","",0);
		return;
	}
	DWORD_PTR dwCmd = stCallBackInfo.vecDwordArry[0];
	DWORD_PTR enType = stCallBackInfo.vecDwordArry[1];
	DWORD_PTR dwReserved = stCallBackInfo.vecDwordArry[2];


	_NotifyMessage stMsg;
	stMsg.nType = static_cast<int>(enType);
	stMsg.dwCmd = dwCmd;
	stMsg.vecStr = stCallBackInfo.vecStrArry;
	stMsg.dwReserved = dwReserved;

	SendMegToClinet(stMsg);

	if (stMsg.dwCmd == IBFIS_MSG_CLIENT_NOTIFY_PRODUCEINFO || /*itMsg->dwCmd == IBFIS_MSG_CLIENT_NOTIFY_CLIENTINFO ||*/
		/*stMsg.dwCmd == IBFIS_MSG_CLIENT_NOTIFY_BUSINESSDOCKMAGINFO ||*/ stMsg.dwCmd == IBFIS_MSG_CLIENT_NOTIFY_ROLEINFO ||
		stMsg.dwCmd == MSG_ISSUED_EMPLOYEEINFO || stMsg.dwCmd == IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO ||
		stMsg.dwCmd == IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO || stMsg.dwCmd == IBFIS_MSG_CLIENT_NOTIFY_BUSINESSINFO ||
		stMsg.dwCmd == IBFIS_MSG_CLIENT_NOTIFY_SCRIPTINFO
		)
	{
		SendLowerLevelServer(stMsg);
	}
	else if (stMsg.dwCmd != IBFIS_MSG_CLIENT_NOTIFY_PRODUCEINFO && m_pSyncClient != nullptr)	//上传给上级服务器
	{
		/*XhAutoScalUseTime strtime("上传数据给上级服务器",true);
		auto iter = m_mapTaskStation.find(itMsg->dwCmd);
		if (iter != m_mapTaskStation.end())
		{
			DWORD_PTR d1 = itMsg->dwCmd,d2 = itMsg->nType;
			int nRet = -1;
			if (itMsg->vecStr.size() == 1)
			{
				m_pSyncClient->DoNotifyData(d1,d2,itMsg->vecStr[0]);
			}
			else
			{
				std::vector<DWORD_PTR> vecInfo;
				vecInfo.push_back(d1);
				vecInfo.push_back(d2);
				m_pSyncClient->DoNotifyData(vecInfo,itMsg->vecStr);
			}
		}*/
	}

	SCATCH;
}

void XhBFISCommunicateSyncServerStationImp::DockingMessageHandle(std::string meg)
{
	
	STRY;
	BFIS::BusinessDockMsgInfo msg;
	if (msg.ParseFromString(meg)) 
	{
		ST_BusinessDockMsgInfo stInfo(msg);
		
		STRY;
		if (m_strPluginName == "JZ")
		{
			SFTRACE("Docking", " %s 进入对接函数, [%s] \r\n", __FUNCTION__, stInfo.strJDBRID.c_str());
			if (stInfo.strJDBRID == m_stBranchInfo.strJDBRID)
			{
				std::map<HANDLE, std::shared_ptr<ObjectRefCount<HANDLE> > > mapClientContext;
				STRY;
				readLock locker(m_connectUserClientMtx);
				mapClientContext = m_mapUserClinetContext;
				SCATCH;
				SFTRACE("Docking", "当前连接客户端的数量为[%d] \r\n", mapClientContext.size());
				for each (auto &var in mapClientContext)
				{
					readLock locker(m_connectUserClientMtx);
					auto itor = m_mapUserClinetContext.find(var.first);
					if (itor != m_mapUserClinetContext.end())
					{
						std::shared_ptr<ObjectRefCount<HANDLE> > refObj = itor->second;
						std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
						AutoObjectRefMgr refObject;
						if (refObject.AddRefCount(refInfo))
						{
							locker.unlock();
							int nRet = XhDoSendData(var.first, DBO_ADD, IBFIS_MSG_CLIENT_NOTIFY_BUSINESSDOCKMAGINFO, meg, 0);
							SFTRACE("Docking", "对接信息发送到客户端，执行端操作[%d] 返回值[%d] strCredenitialNum[%s] \r\n", stInfo.nBootFlag, nRet, stInfo.strCredenitialNum.c_str());
						}
					}
				}
			}
		}
		else
		{
			std::map<HANDLE, std::shared_ptr<ObjectRefCount<HANDLE> > > mapClientContext;
			STRY;
			readLock locker(m_connectUserClientMtx);
			mapClientContext = m_mapUserClinetContext;
			SCATCH;

			TTRACE(" 当前连接客户端的数量为[%d] IP[%s] 执行端操作[%d]\r\n", mapClientContext.size(), stInfo.strTerminalIP.c_str(), stInfo.nBootFlag);
			STRY;
			std::set<HANDLE> invalidContextSet;
			bool bSucess = false;
			for each (auto &var in mapClientContext)
			{
				readLock locker(m_connectUserClientMtx);
				auto itor = m_mapUserClinetContext.find(var.first);
				if (itor != m_mapUserClinetContext.end())
				{
					string strUrl = "";
					HANDLE hContext = nullptr;
					TCHAR chIP[32] = { 0 };
					iBFIS_CommunicationServer::GetClientAddr(var.first, chIP);
					strUrl = chIP;
					if (stInfo.strTerminalIP != "" && string::npos != strUrl.find(stInfo.strTerminalIP))
					{
						hContext = var.first;
					}
					else
						continue;
						
					std::shared_ptr<ObjectRefCount<HANDLE> > refObj = itor->second;
					std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
					AutoObjectRefMgr refObject;
					if (refObject.AddRefCount(refInfo))
					{
						locker.unlock();
						int nRet = -1;
						nRet = XhDoSendData(hContext, DBO_ADD, IBFIS_MSG_CLIENT_NOTIFY_BUSINESSDOCKMAGINFO, meg, 0);
						//int nRet = XhDoSendData(var, DBO_ADD,IBFIS_MSG_CLIENT_NOTIFY_BUSINESSDOCKMAGINFO, meg, 0);
						char szMeg[255] = { 0 };
						sprintf(szMeg, "对接信息发送到客户端IP[%s]，执行端操作[%d] 返回值[%d] hContext[%p]", chIP, stInfo.nBootFlag, nRet, hContext);
						if (nRet > 0)
						{
							bSucess = true;
							DISPLAY_LOG("对接模块", szMeg, "成功", "", 1);
							break;
						}
						else
						{
							DISPLAY_LOG("对接模块", szMeg, "", "", 0);
							invalidContextSet.insert(hContext);
						}
					}
				}
			}

			if (bSucess)
			{
				
				for each(auto &var in invalidContextSet)  //有重复的，可能退出的时候没有删除句柄
				{
					TTRACE(" DockingMessageHandle 删除无效句柄[%p]\r\n", var);
					OnDisConnected(var);
				}
			}
			SCATCH;
			return;
		}
		SCATCH;

		//锦州银行遍历下级所有机构
		std::map<string, std::shared_ptr<ObjectRefCount<HANDLE> > > mapClientContext;
		STRY;
		readLock locker(m_connectBranchClientInfoMtx);
		mapClientContext = m_mapBranchContextInfo;
		SCATCH;
		for each (auto &var in mapClientContext)
		{
			readLock locker(m_connectBranchClientInfoMtx);
			auto itor = m_mapBranchContextInfo.find(var.first);
			if (itor != m_mapBranchContextInfo.end())
			{
				std::shared_ptr<ObjectRefCount<HANDLE> > refObj = itor->second;
				std::shared_ptr<RefCountInfo> refInfo = refObj->GetRefInfo();
				AutoObjectRefMgr refObject;
				if (refObject.AddRefCount(refInfo))
				{
					locker.unlock();
					ST_BranchInfo stBranchInfo;
					if (m_pCache && m_pCache->QueryBranchInfoById(var.first, stBranchInfo))
					{
						if (stBranchInfo.strJDBRID == stInfo.strJDBRID)  //存在相同的机构号
						{
							int nRet = XhDoSendData(refObj->m_custom, DBO_ADD, IBFIS_MSG_CLIENT_NOTIFY_BUSINESSDOCKMAGINFO, meg);
							SFTRACE("Docking", "对接信息发送到下级网点[%s] 返回值[%d] strCredenitialNum[%s] \r\n", stBranchInfo.strName.c_str(), nRet, stInfo.strCredenitialNum.c_str());
							//return;
						}
					}
				}
			}
		}
	}
	else
	{
		SFTRACE("Docking", "对接信息解析失败 \r\n");
		return;
	}
	SCATCH;
}

void XhBFISCommunicateSyncServerStationImp::HandleDockingRecvVideoStatus(std::vector<std::string>& v1)
{
	STRY;
	string strRecvMsg = "";
	string strStr1 = "";
	string strStr2 = "";
	if (v1[0] == "1") 
	{	
		strStr1 = "1";
		strStr2 = "Sucessed";	
	}
	else 
	{
		if (m_strPluginName.Compare("NC") == 0)
		{
			strStr1 = v1[0];
			strStr2 = v1[1];
		}
		else
		{
			strStr1 = "0";
			strStr2 = "Failure";
		}
	}
	GetRecvMessage(strRecvMsg, strStr1, strStr2);
	if (m_pBankPluginInter)
	{
		int nRet = m_pBankPluginInter->SendDataToBusinessSystem((BYTE*)strRecvMsg.c_str(), strRecvMsg.size());
		SFTRACE("Docking", "返回录像状态[%s]失败,返回[%d]\r\n", strRecvMsg.c_str(), nRet);
	}
	SCATCH;
}