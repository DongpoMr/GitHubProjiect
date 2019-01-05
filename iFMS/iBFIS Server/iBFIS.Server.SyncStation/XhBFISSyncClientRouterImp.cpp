#include "StdAfx.h"
#include "XhBFISSyncClientRouterImp.h"
#include "IcmsP_Utility.h"
#include "iSOC_MonFactoryManagement.h"
#include "XhLogDisplayInterface.h"
#include "BFIS.ProtoMessageDefine.pb.h"
#include "iFVR_Configuration.h"
#include <map>
#include "ICallbackManagement.h"
#include "XhAutoScalUseTime.h"
#include "IcmsP_XmlParser.h"
#include <boost\thread.hpp>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <set>
#include "XhBFISOutgoingDeviceSyncClient.h"

#define KEEP_ALIVE 1001
#define RECONNECTION_COUNT 2
#define HEART_OUTTIME  40 * 1000

XhBFISSyncClientRouterImp::XhBFISSyncClientRouterImp(void):m_pTimer(NULL),m_usRemotePort(0),m_bNeedStop(FALSE),
	m_bNeedReConnect(FALSE),m_hServerContext(nullptr),m_nSyncInterval(10*60),m_strUrl(""),m_strRemoteIP(""),m_dwHeartTime(0),
	m_outgoingDevice(nullptr)
{
	m_pNetClient = new iBFIS_CommunicationClient;
	m_pNetClient->SetRMICallbackSkin(this);
	STRY;
	iSOC_MonFactoryManagement fmt;
	m_pCache = (IBFISDataProvider*)fmt.CreateObject(OBJECT_TYPE_BFISSERVER_CACHESOURCE,_T(""), __FUNCTION__);
	if (!m_pCache)
	{
		DISPLAY_LOG(_T("ͬ������"),_T("��ȡ���ݿ��������ʧ��"), _T("����������������"), _T(""), 0);
		return;
	}
	m_pComm = (IBFISCommunicateSyncServer*)fmt.CreateObject(OBJECT_TYPE_BFIS_COMMUNICATESYNCSERVER,"", __FUNCTION__);
	if (!m_pComm)
	{
		DISPLAY_LOG(_T("ͬ������"),_T("��ȡͨ�Ŷ���ʧ��"),"","",0);
		return;
	}

	std::string strLocalId;
	if(m_pCache && m_pCache->QueryLocalBranchId(strLocalId))
	{
		m_stBranchInfo.strBranchId = strLocalId;
		m_pCache->QueryBranchInfoById(strLocalId,m_stBranchInfo);
	}

	m_bIsStopReconnectThread = false;
	m_spCheckConnectThread.reset();
	ReadOutgoingDeviceXml();
	SCATCH;
}  


XhBFISSyncClientRouterImp::~XhBFISSyncClientRouterImp(void)
{
	m_bIsStopReconnectThread = true;
	if (m_spCheckConnectThread)
	{
		m_cheackConnectCondition.notify_all();
		m_spCheckConnectThread->join();
	}

	UnInit();
	SAFE_DELETE(m_pThread);
	if (m_pNetClient)
	{
		m_pNetClient->SetRMICallbackSkin(NULL);
		m_pNetClient->DisConnect();
		SAFE_DELETE(m_pNetClient);
	}
}

int XhBFISSyncClientRouterImp::OnInvoke(HANDLE hContext, DWORD_PTR& d)
{
	STRY;
	if (MSG_ISSUED_ALLOWSYNC == d)
	{
		SFTRACE("SyncInfo", "��ʼͬ��...\r\n");
		m_syncEvent.SendEvent();
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::OnInvoke( HANDLE hContext,DWORD_PTR& d,BYTE* pData,int nDataLen )
{
	STRY;
	//DISPLAY_LOG("1111","�����յ���Ϣ","","",1);
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::OnInvoke(HANDLE hContext,DWORD_PTR& d,std::string& s)
{
	STRY;
	if (MSG_ISSUED_ROLEPURVIEW == d)
	{
		if (m_pCache)
		{
			vector<ST_RoleInfo> vecRoleInfo;
			if (m_pCache->QueryRoleInfo(vecRoleInfo))
			{
				for each(auto var in vecRoleInfo)
				{
					if (var.strRoleInfoId.compare(s) == 0 && var.nExtendedInfo == -2)
					{
						s.clear();
						return 1;
					}
				}
			}

			vector<ST_RolePurviewInfo> vecCurrInfo;
			m_pCache->QueryRolePurviewInfoByRoleId(s, vecCurrInfo);
			SFTRACE("RolePurview", "ɾ����ɫȨ��[%s]\r\n", s.c_str());
			for each (auto var in vecCurrInfo)
			{
				m_pCache->ManageRolePurviewInfo(DBO_DEL, var);
			}
		}
		s.clear();
	}
	return 1;
	//DISPLAY_LOG("2222","�����յ���Ϣ","","",1);
	SCATCH;
	return -1;
}
int XhBFISSyncClientRouterImp::OnInvoke(HANDLE hContext,std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2)
{
	STRY;
	//DISPLAY_LOG("2222","�����յ���Ϣ","","",1);
	
	switch(v1[1])
	{
	case IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO:
		{
			STRY;
			if(v2[1] == "112505")
			{
				return 1;
			}
			if (m_pCache && m_pCache->ManageTransparentData((DBOperType)v1[0],v2[0],v2[1],v2[2]) > 0)
			{
				m_pComm->AddNotifyMsg((DBOperType)v1[0],IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO,v2);
				return 1;
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_QUERY_OPERATELOGINFO:
		{
			STRY;
			BFIS::EmployeeInfo msg;
			msg.ParseFromString(v2[0]);
			ST_EmployeeInfo stEmployeeInfo(msg);
			//�����û�
			v2.clear();
			if (stEmployeeInfo.strBranchId == m_stBranchInfo.strBranchId)
			{
				vector<ST_OperateLogInfo> vecOprateLog;
				if(m_pCache && m_pCache->QueryOperateLogInfoByEmployeeId(vecOprateLog,stEmployeeInfo.strEmployeeId))
				{
					for (auto iter = vecOprateLog.begin() ; iter != vecOprateLog.end() ; iter ++)
					{
						std::string strInfo;
						bool bSuccess = iter->ConvertToString(strInfo);
						if(!bSuccess)
						{
							char szMsg[255] = {0};
							sprintf(szMsg,"������־��Ϣ[%s]���л�ʧ��",iter->strOperateLogId.c_str());
							DISPLAY_LOG("�����ģ��",szMsg,"","",0);
						}
						else
						{
							v2.push_back(strInfo);
						}
					}
				}
			}
			return 1;
			SCATCH;
		}
		break;
	default:
		{
			TTRACE("%s[%d]:������Ϣ����, δ֪����Ϣ����[%d]\r\n",__FUNCTION__,__LINE__,v1[1]);
		}
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::OnInvoke(HANDLE hContext,DWORD_PTR& d1,std::vector<std::string>& v1)
{
	STRY;
	int nRet = -1;
	DWORD_PTR dwSync = QueryType_SyncAll;
	switch(d1)
	{
	//�·�����
	/*case MSG_GET_CLIENTINFO:
		{
			ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
			if(pCallback)
			{
				ST_CallBackInfo info;
				info.bIsQueue = true;
				info.nCallIdx = (int)hContext;
				info.pCallBackAddr = this;
				info.pSelfCallback = [v1,this](ST_CallBackInfo& info) -> int
				{
					STRY;
					HandleIssuedClientInfo(v1);
					SCATCH;
					return 1;
				};
				pCallback->AddCallBack(info,__FUNCTION__);
				nRet = 1;
			}
			else
			{
				nRet = HandleIssuedClientInfo(v1);
			}
			v1.clear();
		}
		break;*/
	case MSG_ISSUED_PRODUCEINFO:
		{
			ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
			if(pCallback)
			{
				ST_CallBackInfo info;
				info.bIsQueue = true;
				info.nCallIdx = (int)hContext;
				info.pCallBackAddr = this;
				info.pSelfCallback = [v1,this](ST_CallBackInfo& info) -> int
				{
					STRY;
					HandleIssuedProduceInfo(v1);
					SCATCH;
					return 1;
			
				};
				pCallback->AddCallBack(info,__FUNCTION__);
				nRet = 1;
				
			}
			else
			{
				nRet = HandleIssuedProduceInfo(v1);
			}
			v1.clear();
		}
		break;
	case MSG_ISSUED_ROLEINFO:
		{
			ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
			if(pCallback)
			{
				ST_CallBackInfo info;
				info.bIsQueue = true;
				info.nCallIdx = (int)hContext;
				info.pCallBackAddr = this;
				info.pSelfCallback = [v1,this](ST_CallBackInfo& info) -> int
				{
					STRY;
					HandleIssuedRoleInfo(v1);
					SCATCH;
					return 1;
				};
				pCallback->AddCallBack(info,__FUNCTION__);
				nRet = 1;

			}
			else
			{
				nRet = HandleIssuedRoleInfo(v1);
			}
			v1.clear();
			//nRet = HandleIssuedRoleInfo(v1);
		}
        break;
    case MSG_ISSUED_BRANCHINFO:
        {
			ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
			if(pCallback)
			{
				ST_CallBackInfo info;
				info.bIsQueue = true;
				info.nCallIdx = (int)hContext;
				info.pCallBackAddr = this;
				info.pSelfCallback = [v1,this](ST_CallBackInfo& info) -> int
				{
					STRY;
					HandleIssuedBranchInfo(v1);
					SCATCH;
					return 1;
				};
				pCallback->AddCallBack(info,__FUNCTION__);
				nRet = 1;

			}
			else
			{
				nRet = HandleIssuedBranchInfo(v1);
			}
			v1.clear();
            //nRet = HandleIssuedBranchInfo(v1);
        }
		break;
    case MSG_ISSUED_EMPLOYEEINFO:
        {
			ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
			if(pCallback)
			{
				ST_CallBackInfo info;
				info.bIsQueue = true;
				info.nCallIdx = (int)hContext;
				info.pCallBackAddr = this;
				info.pSelfCallback = [v1,this](ST_CallBackInfo& info) -> int
				{
					STRY;
					HandleIssuedEmployeeInfo(v1);
					SCATCH;
					return 1;
				};
				pCallback->AddCallBack(info,__FUNCTION__);
				nRet = 1;
			}
			else
			{
				nRet = HandleIssuedEmployeeInfo(v1);
			}
			v1.clear();
            //nRet = HandleIssuedEmployeeInfo(v1);
        }
        break;
	case MSG_ISSUED_SCRIPTINFO:
		{
			ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
			if(pCallback)
			{
				ST_CallBackInfo info;
				info.bIsQueue = true;
				info.nCallIdx = (int)hContext;
				info.pCallBackAddr = this;
				info.pSelfCallback = [v1,this](ST_CallBackInfo& info) -> int
				{
					STRY;
					HandleIssuedScriptInfo(v1);
					SCATCH;
					return 1;
				};
				pCallback->AddCallBack(info,__FUNCTION__);
				nRet = 1;
			}
			else
			{
				nRet = HandleIssuedScriptInfo(v1);
			}
			v1.clear();
		}
		break;
#if 0
	case MSG_ISSUED_PURVIEWINFO:
		{
			nRet = HandleIssuedPurviewInfo(v1);
		}
		break;
#endif
	case MSG_ISSUED_ROLEPURVIEW:
		{
			ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
			if(pCallback)
			{
				ST_CallBackInfo info;
				info.bIsQueue = true;
				info.nCallIdx = (int)hContext;
				info.pCallBackAddr = this;
				info.pSelfCallback = [v1,this](ST_CallBackInfo& info) -> int
				{
					STRY;
					HandleIssuedRolePurviewInfo(v1);
					SCATCH;
					return 1;
				};
				pCallback->AddCallBack(info,__FUNCTION__);
				nRet = 1;
			}
			else
			{
				nRet = HandleIssuedRolePurviewInfo(v1);
			}
			v1.clear();
			//nRet = HandleIssuedRolePurviewInfo(v1);
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO:
		{
			nRet = HandleIssuedRolePurviewInfo(v1, -1);
		}
		break;
	//��ȡ��ȥ{}
	case MSG_UPLOAD_BUSINESSINFO:
		{
			vector<ST_BusinessInfo> vecBusinessInfo;
			if(!GetNeedSyncBusinessInfo(vecBusinessInfo,dwSync))
			{
				DISPLAY_LOG(_T("ǿ��ͬ������"),_T("��ȡ�ϴ�ҵ����Ϣʧ��"), _T(""), _T(""), 0);
			}
			if (vecBusinessInfo.empty())
			{
				DISPLAY_LOG(_T("ǿ��ͬ������"),_T("δ�ϴ�ҵ����ϢΪ�գ������ò���"), _T(""), _T(""), 1);
				nRet = 1;
			}
			else
			{
				for (auto iter = vecBusinessInfo.begin(); iter != vecBusinessInfo.end(); iter ++)
				{
					std::string strBuf;
					if(iter->ConvertToString(strBuf))
					{
						v1.push_back(strBuf);
					}
				}
				nRet = 1;
			}
		}
		break;
	case MSG_UPLOAD_BUSINESSFILEINFO:
		{
			vector<ST_BusinessFileInfo> vecBusinessFileInfo;
			if(!GetNeedSyncBusinessFileInfo(vecBusinessFileInfo,dwSync))
			{
				DISPLAY_LOG(_T("ǿ��ͬ������"),_T("��ȡ�ϴ�ҵ���ļ���Ϣʧ��"), _T(""), _T(""), 0);
			}
			if (vecBusinessFileInfo.empty())
			{
				DISPLAY_LOG(_T("ǿ��ͬ������"),_T("δ�ϴ�ҵ���ļ���ϢΪ�գ������ò���"), _T(""), _T(""), 1);
				nRet = 1;
			}
			else
			{
				for (auto iter = vecBusinessFileInfo.begin(); iter != vecBusinessFileInfo.end(); iter ++)
				{
					std::string strBuf;
					if(iter->ConvertToString(strBuf))
					{
						v1.push_back(strBuf);
					}
				}
				nRet = 1;
			}
		}
		break;
	case MSG_UPLOAD_BUSINESSRELATEINFO:
		{
			vector<ST_BusinessRelateInfo> vecBusinessRelateInfo;
			if(!GetNeedSyncBusinessRelateInfo(vecBusinessRelateInfo,dwSync))
			{
				DISPLAY_LOG(_T("ǿ��ͬ������"),_T("��ȡ�ϴ�ҵ���ļ���Ϣʧ��"), _T(""), _T(""), 0);
			}
			if (vecBusinessRelateInfo.empty())
			{
				DISPLAY_LOG(_T("ǿ��ͬ������"),_T("δ�ϴ�ҵ���ļ���ϢΪ�գ������ò���"), _T(""), _T(""), 1);
				nRet = 1;
			}
			else
			{
				for (auto iter = vecBusinessRelateInfo.begin(); iter != vecBusinessRelateInfo.end(); iter ++)
				{
					std::string strBuf;
					if(iter->ConvertToString(strBuf))
					{
						v1.push_back(strBuf);
					}
				}
				nRet = 1;
			}
		}
		break;
	case MSG_UPLOAD_CLIENTINFO:
		{
			/*XhAutoScalUseTime strtime("�ϴ��ͻ���Ϣ",true);
			vector<ST_ClientInfo> vecClient;
			if(!GetNeedSyncClientInfo(vecClient,dwSync))
			{
			DISPLAY_LOG(_T("ǿ��ͬ������"),_T("��ȡ�ϴ��û���Ϣʧ��"), _T(""), _T(""), 0);
			}
			if (vecClient.empty())
			{
			DISPLAY_LOG(_T("ǿ��ͬ������"),_T("δ�ϴ��û���ϢΪ�գ������ò���"), _T(""), _T(""), 1);
			nRet = 1;
			}
			else
			{
			for (auto iter = vecClient.begin(); iter != vecClient.end(); iter ++)
			{
			std::string strBuf;
			if(iter->ConvertToString(strBuf))
			{
			v1.push_back(strBuf);
			}
			}
			nRet = 1;
			}*/
			return 1;
		}
		break;
	case MSG_UPLOAD_EMPLOYEEINFO:
		{
			vector<ST_EmployeeInfo> vecEmployeeInfo;
			if(!GetNeedSyncEmployeeInfo(vecEmployeeInfo,dwSync))
			{
				DISPLAY_LOG(_T("ǿ��ͬ������"),_T("��ȡ�ϴ��û���Ϣʧ��"), _T(""), _T(""), 0);
			}
			if (vecEmployeeInfo.empty())
			{
				DISPLAY_LOG(_T("ǿ��ͬ������"),_T("δ�ϴ��û���ϢΪ�գ������ò���"), _T(""), _T(""), 1);
				nRet = 1;
			}
			else
			{
				for (auto iter = vecEmployeeInfo.begin(); iter != vecEmployeeInfo.end(); iter ++)
				{
					std::string strBuf;
					if(iter->ConvertToString(strBuf))
					{
						v1.push_back(strBuf);
					}
				}
				nRet = 1;
			}
		}
		break;
	case MSG_UPLOAD_EMPLOYEEPURVIEWINFO:
		{
			vector<ST_EmployeePurviewInfo> vecEmployeePurviewInfo;
			DWORD_PTR dwType = QueryType_SyncAll;
			if(!GetNeedSyncEmployeePurviewInfo(vecEmployeePurviewInfo,QueryType_SyncAll))
			{
				DISPLAY_LOG(_T("ǿ��ͬ������"),_T("��ȡ�ϴ�Ա��Ȩ����Ϣʧ��"), _T(""), _T(""), 0);
			}
			else if (vecEmployeePurviewInfo.empty())
			{
				DISPLAY_LOG(_T("ǿ��ͬ������"),_T("δ�ϴ�Ա��Ȩ����ϢΪ�գ������ò���"), _T(""), _T(""), 1);
				nRet = 1;
			}
			else
			{
				for (auto iter = vecEmployeePurviewInfo.begin() ; iter != vecEmployeePurviewInfo.end(); iter ++)
				{
					std::string strInfo;
					if (iter->ConvertToString(strInfo))
					{
						v1.push_back(strInfo);
					}
				}
				nRet = 1;
			}
		}
		break;
	case MSG_ISSUED_MIGRATETASKINFO:
		{
			ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
			if(pCallback)
			{
				ST_CallBackInfo info;
				info.bIsQueue = true;
				info.nCallIdx = (int)hContext;
				info.pCallBackAddr = this;
				info.pSelfCallback = [v1,this](ST_CallBackInfo& info) -> int
				{
					STRY;
					HandleIssuedMigrateTasknfo(v1);
					SCATCH;
					return 1;
				};
				pCallback->AddCallBack(info,__FUNCTION__);
				nRet = 1;
			}
			else
			{
				nRet = HandleIssuedMigrateTasknfo(v1);
			}
		}
		break;
	case MSG_OUTGOING_EMPLOYEEPURVIEWINFO:
		{
			ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER, "", __FUNCTION__);
			if (pCallback)
			{
				ST_CallBackInfo info;
				info.bIsQueue = true;
				info.nCallIdx = (int)hContext;
				info.pCallBackAddr = this;
				info.pSelfCallback = [v1, this](ST_CallBackInfo& info) -> int
				{
					STRY;
					HandleIssuedEmployeePurviewInfo(v1);
					SCATCH;
					return 1;
				};
				pCallback->AddCallBack(info, __FUNCTION__);
				nRet = 1;
			}
			else
			{
				nRet = HandleIssuedEmployeePurviewInfo(v1);
			}
			v1.clear();
			return 1;
		}
		break;
	default:
		{
			TTRACE("%s[%d]:������Ϣ����, δ֪����Ϣ����[%d]\r\n",__FUNCTION__,__LINE__,d1);
		}
	}
	return nRet;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::OnInvoke(HANDLE hContext,DWORD_PTR& d1,DWORD_PTR& d2,std::string& s)
{
	STRY;
	int nRet = -1;
	switch(d1)
	{
	case IBFIS_MSG_CLIENT_NOTIFY_PRODUCEINFO:
		{
			BFIS::ProduceInfo msg;
			if(msg.ParseFromString(s))
			{
				ST_ProduceInfo stInfo(msg);
				nRet = ProduceInfoNotify((int)d2,stInfo);
				if(nRet != -1 && m_pComm->AddNotifyMsg((DBOperType)d2,d1,s) <= 0)
				{
					DISPLAY_LOG("ͬ��","[����֪ͨ]֪ͨ�ͻ��˸��²�Ʒ��Ϣ","ʧ��","",0);
				}
				return nRet;
			}
			DISPLAY_LOG("ͬ��","[����֪ͨ]���²�Ʒ��Ϣ","����ʧ��","",0);
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_CLIENTINFO:
		{
			BFIS::ClientInfo msg;
			if(msg.ParseFromString(s))
			{
				ST_ClientInfo stInfo(msg);
				nRet = ClientInfoNotify((int)d2,stInfo);
				if(nRet != -1 && m_pComm->AddNotifyMsg((DBOperType)d2,d1,s) <= 0)
				{
					DISPLAY_LOG("ͬ��","[����֪ͨ]֪ͨ�ͻ��˸��¿ͻ���Ϣ","ʧ��","",0);
				}
				return nRet;
			}
			DISPLAY_LOG("ͬ��","[����֪ͨ]���¿ͻ���Ϣ","����ʧ��","",0);
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_BUSINESSDOCKMAGINFO:
		{
			if (m_pComm->DoSendData(nullptr, (DBOperType)d2, d1, s) <= 0)
			{
				DISPLAY_LOG("ͬ��", "[ҵ��֪ͨ]֪ͨ�ͻ���ҵ��Խ���Ϣ", "ʧ��", "", 0);
				return 0;
			}
			return 1;
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_ROLEINFO:
		{		
			BFIS::RoleInfo msg;
			if(msg.ParseFromString(s))
			{
				vector<string> vecRoleInfo;
				vecRoleInfo.push_back(s);
				HandleIssuedRoleInfo(vecRoleInfo);
				vecRoleInfo.clear();
				ST_RoleInfo stInfo(msg);
				if(m_pComm->AddNotifyMsg((DBOperType)d2,d1,s) <= 0)
				{
					DISPLAY_LOG("ͬ��","[ҵ��֪ͨ]֪ͨ�ͻ��˽�ɫ��Ϣ","ʧ��","",0);
				}
				return 1;
			}
			DISPLAY_LOG("ͬ��","[ҵ��֪ͨ]֪ͨ�ͻ��˽�ɫ��Ϣ","����ʧ��","",0);
		}
		break;
	case MSG_ISSUED_EMPLOYEEINFO:
		{
			STRY;
			BFIS::EmployeeInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_EmployeeInfo stInfo(msg);		
				DBOperType enType = (DBOperType)d2;
				if(stInfo.strBranchId == m_stBranchInfo.strBranchId)
				{
					if(m_pCache && m_pCache->ManageEmployeeInfo(enType,stInfo) > 0)
					{
					    m_pCache->ManageEmployeeInfoAndSocUser(enType,stInfo);
						m_pComm->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEINFO,s);
						return 1;
					}
				}						
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO:
		{
			STRY;
			BFIS::RolePurviewInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_RolePurviewInfo stInfo(msg);		
				DBOperType enType = (DBOperType)d2;				
				if(m_pCache && m_pCache->ManageRolePurviewInfo(enType,stInfo) > 0)
				{		
					m_pComm->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO,s);
					return 1;
				}									
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_BUSINESSINFO:
		{
			STRY;
			BFIS::BusinessInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_BusinessInfo stInfo(msg);		
				DBOperType enType = (DBOperType)d2;	
				ST_BusinessInfo stBusinessInfo;
				if(m_pCache && m_pCache->QueryBusinessInfoById(stInfo.strBusinessInfoId,stBusinessInfo)> 0)
				{		
					stInfo.nMigrated = stBusinessInfo.nMigrated;
					m_pCache->ManageBusinessInfo(enType,stInfo);
					//m_pComm->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO,s);
					return 1;
				}									
			}
			SCATCH;
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_DISKANDCONNECT:
		{
			ST_DiskAndConnectStatus stDiskAndConnectStatus;
			vector<string> vecdisk;
			string strStatus;
			if (m_pCache)
			{
				vector<ST_KeyValueInfo> vecKeyValueInfo;
				if (m_pCache->QueryKeyValueInfoByTypeAndCode("DiskSetting","",vecKeyValueInfo))
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
				stDiskAndConnectStatus.strBranchId = m_stBranchInfo.strBranchId;
				if(stDiskAndConnectStatus.ConvertToString(strStatus))
				{	
					s = strStatus;
					return 1;
				}
				DISPLAY_LOG("��ѯ","[��ѯ��Ϣ]��ѯ�����ڴ���Ϣ","����ʧ��","",0);
			}
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_SCRIPTINFO:
		{
			STRY;
			BFIS::ScriptInfo msg;
			bool bSuccess = msg.ParseFromString(s);
			if (bSuccess)
			{
				ST_ScriptInfo stInfo(msg);		
				DBOperType enType = (DBOperType)d2;	
				if(m_pCache && m_pCache->ManageScriptInfo(enType,stInfo))
				{		
					//m_pCache->ManageBusinessInfo(enType,stInfo);
					m_pComm->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_SCRIPTINFO,s);
					return 1;
				}									
			}
			SCATCH;
		}
		break;
	}
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::OnConnected( HANDLE hContext )
{
	STRY;
	{
		Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
		m_bNeedReConnect = FALSE;
		m_hServerContext = hContext;
	}

	auto future = boost::async(boost::launch::async, [this]()
	{
		DoLogin();
	});
	
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::OnDisConnected( HANDLE hContext )
{
	STRY;
	m_bNeedReConnect = TRUE;
	m_hServerContext = nullptr;
	m_cheackConnectCondition.notify_all();
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::OnGotError(HANDLE hContext,int nErrorCode,std::string strErrorDes)
{
	STRY;

	SCATCH;
	return -1;
}


bool XhBFISSyncClientRouterImp::ReConnect2Server()
{
	int nRet = -1;
	if (m_bNeedReConnect && m_strRemoteIP != "")	
	{
		DISPLAY_LOG(_T("ͬ������"),_T("��������������..."), _T(""), _T(""), 1);
		LONG lListenIP = htonl(inet_addr(m_strRemoteIP.c_str()));  
		nRet = DoConnect(lListenIP, m_usRemotePort);
		if (nRet != 0 || m_bNeedReConnect)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("����������ʧ�ܣ��ȴ�����"), _T(""), _T(""), 0);
		}
		else
		{
			DISPLAY_LOG(_T("ͬ������"),_T("�����������������ɹ�"), _T(""), _T(""), 1);
		}
	}
	return nRet == 0 ? true : false;
}

ISOC_VOID XhBFISSyncClientRouterImp::Run()
{
	STRY;
	int waitCount = 0;
	while(!m_bNeedStop)
	{
		//1.���ж��Ƿ���Ҫ����
		if (m_bNeedReConnect)	
		{
			Sleep(1000);
			//ReConnect2Server(); //timer ����������������߶������������ͻ
			continue;
		}

		STRY;
		if (!m_syncEvent.Wait(60))
			continue;
		SCATCH;

		if (m_bNeedStop)
			break;
		//ѯ�ʷ������Ƿ�æ
#if 0
		STRY;
		iBFIS_CommunicationInvoker invoke(m_hServerContext);
		DWORD_PTR dwCmd = MSG_ISBUSY;
		int nRet = invoke.Invoke(dwCmd);
		if (nRet <= 0)
		{
			Sleep(3*1000);
			continue;
		}
		SCATCH;
#endif

		//2.�����Ҫͬ��������
		SaveBackupData();
		LoadBackupData();
		//2.0 �ϴ�������Ϣ
		STRY;
		int nRet = 1;
		std::vector<ST_BranchInfo> vecBranchInfo;
		if(!GetNeedSyncBranchInfo(vecBranchInfo))
		{
			SFTRACE("SyncInfo", "��ȡ��Ҫͬ����������Ϣʧ��\r\n");
			continue;
		}
		int syncNum = vecBranchInfo.size();
		if (syncNum > 0)
		{
			nRet = DoSyncBranchInfo(vecBranchInfo);
			if(nRet <= 0)
			{
				SFTRACE("SyncInfo", "ͬ��������Ϣʧ��,�ȴ����� nRet[%d]\r\n", nRet);
				Sleep(1000);
				continue;
			}
		}
		SFTRACE("SyncInfo", "ͬ��������Ϣ�ɹ�[%d]\r\n", syncNum);
		SCATCH;

#if 0
		//2.2 ��ȡȨ����Ϣ
		STRY;
		int nRet = 1;
		nRet = DoSyncPurview();
		if (nRet <= 0)
		{
			SFTRACE("SyncInfo", "ͬ��Ȩ����Ϣʧ��,�ȴ����� nRet[%d]\r\n", nRet);
			Sleep(1000);
			continue;
		}
		SFTRACE("SyncInfo", "ͬ��Ȩ����Ϣ�ɹ�\r\n");
		SCATCH;
#endif
		//2.4�ϴ��ͻ���Ϣ
		STRY;
		int nRet = 1;
		std::vector<ST_ClientInfo> vecClient;
 		if(!GetNeedSyncClientInfo(vecClient))
		{
			SFTRACE("SyncInfo", "��ȡ��Ҫͬ���Ŀͻ���Ϣʧ�� nRet[%d]\r\n", nRet);
			continue;
		}
		
		int clientSize = vecClient.size();
		if (clientSize > 0)
		{
			nRet = DoSyncClientInfo(vecClient);
			if (nRet <= 0)
			{
				SFTRACE("SyncInfo", "ͬ���ͻ���Ϣʧ��,�ȴ����� nRet[%d]\r\n", nRet);
				Sleep(1000);
				continue;
			}
		}
		SFTRACE("SyncInfo", "ͬ���ͻ��ųɹ�[%d]\r\n", clientSize);
		SCATCH;
		//2.5 �ϴ�Ա����Ϣ
		STRY;
		int nRet = 1;
		std::vector<ST_EmployeeInfo> vecEmployee;
		if(!m_pCache->QueryEmployeeInfoNeed2Sync(vecEmployee))
		{
			SFTRACE("SyncInfo", "��ȡδͬ��Ա����Ϣʧ�ܣ��ȴ�����\r\n");
			Sleep(1000);
			continue;
		}
		int employeeSize = vecEmployee.size();
		if (employeeSize > 0)
		{
			nRet = DoSyncEmployeeInfo(vecEmployee);
			if (nRet <= 0)
			{
				SFTRACE("SyncInfo", "ͬ��Ա����Ϣʧ��,�ȴ����� nRet[%d]\r\n", nRet);
				Sleep(1000);
				continue;
			}
		}
		SFTRACE("SyncInfo", "ͬ��Ա����Ϣ�ɹ�[%d]\r\n", employeeSize);
		SCATCH;
		// �ϴ�Ա��Ȩ����Ϣ
		STRY;
		int nRet = 1;
		std::vector<ST_EmployeePurviewInfo> vecEmployeePurviewInfo;
		if(!m_pCache->QueryEmployeePurviewInfoNeed2Sync(vecEmployeePurviewInfo))
		{
			SFTRACE("SyncInfo", "��ȡδͬ��Ա��Ȩ����Ϣʧ�ܣ��ȴ�����\r\n");
			Sleep(1000);
			continue;
		}
		int employeePurviewSize = vecEmployeePurviewInfo.size();
		if (employeePurviewSize > 0)
		{
			nRet = DoSyncEmployeePurviewInfo(vecEmployeePurviewInfo);
			if (nRet <= 0)
			{
				SFTRACE("SyncInfo", "ͬ��Ա��Ȩ����Ϣʧ��,�ȴ����� nRet[%d]\r\n", nRet);
				Sleep(1000);
				continue;
			}
		}
		SFTRACE("SyncInfo", "ͬ��Ա��Ȩ����Ϣ�ɹ�[%d]\r\n", employeePurviewSize);
		SCATCH;
		//2.7 ͬ��ҵ����Ϣ
		STRY;
		int nRet = 1;
		std::vector<ST_BusinessInfo> vecBusinessInfos;
		if(!m_pCache->QueryBusinessInfoNeed2Sync(vecBusinessInfos))
		{
			SFTRACE("SyncInfo", "��ȡδͬ��ҵ����Ϣʧ�ܣ��ȴ�����\r\n");
			Sleep(1000);
			continue;
		}
		int businessSize = vecBusinessInfos.size();
		if (businessSize > 0)
		{
			nRet = DoSyncBusinessInfo(vecBusinessInfos);
			if (nRet <= 0)
			{
				SFTRACE("SyncInfo", "ͬ��ҵ����Ϣʧ��,�ȴ����� nRet[%d]\r\n", nRet);
				Sleep(1000);
				continue;
			}
		}
		SFTRACE("SyncInfo", "ͬ��ҵ����Ϣ�ɹ�[%d]\r\n", businessSize);
		SCATCH;
		//2.8 ͬ��ҵ���ļ���Ϣ
		STRY;
		int nRet = 1;
		std::vector<ST_BusinessFileInfo> vecBusinessFileInfos;
		if(!m_pCache->QueryBusinessFileInfoNeed2Sync(vecBusinessFileInfos))
		{
			SFTRACE("SyncInfo", "��ȡδͬ��ҵ���ļ���Ϣʧ�ܣ��ȴ�����\r\n");
			Sleep(1000);
			continue;
		}
		int businessFileSize = vecBusinessFileInfos.size();
		if (businessFileSize > 0)
		{
			nRet = DoSyncBusinessFileInfo(vecBusinessFileInfos);
			if (nRet <= 0)
			{
				SFTRACE("SyncInfo", "ͬ��ҵ���ļ���Ϣʧ��,�ȴ����� nRet[%d]\r\n", nRet);
				Sleep(1000);
				continue;
			}
		}
		SFTRACE("SyncInfo", "ͬ��ҵ����Ϣ�ɹ�[%d]\r\n", businessFileSize);
		SCATCH;

		//if (false == m_bFristSync.load())
		{

			//2.1 �ϴ��û�����Ϣ
			STRY;
			int nRet = 1;
			std::vector<ST_RoleInfo> vecRole;
			if (!m_pCache || !m_pCache->QueryRoleInfo(vecRole))
			{
				SFTRACE("SyncInfo", "��ȡ��Ҫͬ���Ľ�ɫ��Ϣʧ��\r\n");
				continue;
			}
			int roleSize = vecRole.size();
			if (roleSize > 0)
			{
				nRet = DoSyncRoleInfo(vecRole);
				if (nRet <= 0)
				{
					SFTRACE("SyncInfo", "ͬ����ɫ��Ϣʧ��,�ȴ����� nRet[%d]\r\n", nRet);
					Sleep(1000);
					continue;
				}
			}
			SFTRACE("SyncInfo", "ͬ����ɫ��Ϣ�ɹ�[%d]\r\n", roleSize);
			SCATCH;
#if 0   //����ͬ��-�¼���ɫȨ��,�ϼ��ǲ����޸��¼������Ľ�ɫ�Ľ�ɫȨ��
			//2.3 �ϴ��û���Ȩ��
			STRY;
			int nRet = 1;
			std::vector<ST_RolePurviewInfo> vecRolePurview;
			if (!GetNeedSyncRolePurviewInfo(vecRolePurview))
			{
				SFTRACE("SyncInfo", "��ȡ��Ҫͬ���Ľ�ɫȨ����Ϣʧ��\r\n");
				continue;
			}
			int rolePurviewSize = vecRolePurview.size();
			if (rolePurviewSize > 0)
			{
				nRet = DoSyncRolePurview(vecRolePurview);
				if (nRet <= 0)
				{
					SFTRACE("SyncInfo", "ͬ����ɫȨ����Ϣʧ��,�ȴ����� nRet[%d]\r\n", nRet);
					Sleep(1000);
					continue;
				}
			}
			SFTRACE("SyncInfo", "ͬ����ɫȨ����Ϣ�ɹ�[%d]\r\n", rolePurviewSize);
			SCATCH;
#endif
		}
		STRY;
		Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
		if (m_hServerContext)
		{
			iBFIS_CommunicationInvoker invoke(m_hServerContext);
			DWORD_PTR dwCmd = MSG_ISSUED_SYNC_ACK;
			int nRet = invoke.Invoke(dwCmd);
			SFTRACE("SyncInfo", "֪ͨ�ϼ�ͬ����� nRet[%d]\r\n", nRet);
		}
		SCATCH;
	}
	SCATCH;
}

int XhBFISSyncClientRouterImp::Init(string strIp,string strPort,string strUser,string strPwd)
{
	STRY;
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::UnInit()
{
	STRY;
	StopSync();
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::DoConnect( IN ISOC_LONG remoteIp, IN ISOC_SHORT remotePort, IN ISOC_DWORDPTR dwReserved /*= 0*/ )
{
	if (!m_pNetClient)
	{
		m_pNetClient = new iBFIS_CommunicationClient;
		m_pNetClient->SetRMICallbackSkin(this);
	}

	std::string strIp;
	long lIP = htonl(remoteIp);
	in_addr addr;
	addr.S_un.S_addr = lIP;
	strIp = inet_ntoa(addr);
	m_strRemoteIP = strIp;
	m_usRemotePort = remotePort;
	CString strDes;
	strDes.Format("�������ӷ�����[%s��%d]",strIp.c_str(), remotePort);
	DISPLAY_LOG("ͬ������",(LPCTSTR)strDes,"","",1);
	int nRet = m_pNetClient->Connect(strIp.c_str(), remotePort);
	if (nRet == 0)
	{
		DISPLAY_LOG(_T("ͬ������"),_T("���ӷ������������ɹ�"), _T(""), _T(""), 1); 
		m_bNeedReConnect = FALSE;
	}
	else
	{
		m_bNeedReConnect =TRUE;
		DISPLAY_LOG(_T("ͬ������"),_T("���ӷ�����������ʧ��"), _T(""), _T(""), 0); 
	}

	if (nullptr == m_spCheckConnectThread)
		m_spCheckConnectThread.reset(new boost::thread(std::bind(&XhBFISSyncClientRouterImp::ConnectCheckTh, this)));

	return nRet;
}

int XhBFISSyncClientRouterImp::DoDisConnect( IN ISOC_DWORDPTR dwReserved /*= 0*/ )
{
	if (m_pNetClient)
	{
		return m_pNetClient->DisConnect();
	}
	return 1;
}

int XhBFISSyncClientRouterImp::ExtendFunction( IN const ISOC_INT nExtendType,IN ISOC_DWORDPTR dwExtendData )
{
	STRY;
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::DoSyncClientInfo( vector<ST_ClientInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if (vecInfos.empty())
		return 1;
	DISPLAY_LOG(_T("ͬ������"), _T("�ϴ��ͻ���Ϣ��ʼ"), _T(""), _T(""), 1);

	int nSuccessCount = 0;
	int nFailedCount = 0;
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter++)
	{
		//1.���л�����
		std::string strOutData;
		bool bSeralizeSuccess = iter->ConvertToString(strOutData);
		if (!bSeralizeSuccess)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("���л��ͻ�����ʧ��"), _T(""), _T(""), 0); 
			return -1;
		}
		int nRet = -1;
		char szBuf[255] = {0};
		DWORD_PTR dwCmd = MSG_UPLOAD_CLIENTINFO;
		STRY;
		Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
		if (nullptr == m_hServerContext)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
			return -1;
		}
		iBFIS_CommunicationInvoker invoke(m_hServerContext);
		nRet = invoke.Invoke(dwCmd, strOutData);
		SCATCH;
		if (nRet <= 0)
		{
			TTRACE(_T("%s[%d]:ͬ���ͻ���Ϣʧ�ܣ�ID:%s  ������[%d]\r\n"),__FUNCTION__,__LINE__,iter->strClientId.c_str(), nRet);
			/*sprintf(szBuf,_T("ͬ���ͻ���Ϣʧ�ܣ�ID:%s\r\n"),iter->strClientId.c_str());
			DISPLAY_LOG("ͬ������",szBuf,"","",0);*/
			++nFailedCount;
		}
		else
		{
			++nSuccessCount;
			if (nRet == OT_EXIST)	//˵�����������Ѿ��ϴ������û����������᷵�ظ��û���ID���������к͸��û���ص�����
			{
				BFIS::ClientInfo msgAck;
				msgAck.ParseFromString(strOutData);
				ST_ClientInfo stClientInfo;
				stClientInfo.strClientId = msgAck.strclientid();
				stClientInfo.strName = msgAck.strname();
                stClientInfo.strCredenitialsType = msgAck.strcredenitialstype();
				stClientInfo.strCredenitial = msgAck.strcredenitial();
				stClientInfo.strPhone = msgAck.strphone();
				stClientInfo.strContent = msgAck.strcontent();
				stClientInfo.nExtendedInfo = msgAck.nextendedinfo();
				stClientInfo.strExtendedInfo1 = msgAck.strextendedinfo1();
				stClientInfo.strExtendedInfo2 = msgAck.strextendedinfo2();
				BOOL bRet = m_pCache->ManageClientInfo(DBO_UPDATE, stClientInfo, 1);
				TTRACE("%s[%d]:�ϴ��ͻ���Ϣ�������������Ѵ��ڸÿͻ������±��ؿͻ�id,old id:%s,new id:%s,����:%s\r\n"
					,__FUNCTION__, __LINE__, iter->strClientId.c_str(), stClientInfo.strClientId.c_str(), bRet == FALSE ? "ʧ��":"�ɹ�");
				
				//sprintf(szBuf,"�ϴ��ͻ���Ϣ�������������Ѵ��ڸÿͻ������±��ؿͻ�id,old id:%s,new id:%s,����:%s\r\n",
				//	iter->strClientId.c_str(), stClientInfo.strClientId.c_str(), bRet == FALSE?"ʧ��":"�ɹ�");
				//DISPLAY_LOG("ͬ������",szBuf,"","",bRet == FALSE ? 0 : 1);

				if (bRet)
				{
					//����ͬ��״̬
					m_pCache->SetSyncComplete(DataType_ClientInfo, iter->strClientId);
				}
			}
			else
			{
				//����ͬ��״̬
				m_pCache->SetSyncComplete(DataType_ClientInfo, iter->strClientId);
				//sprintf(szBuf,"ͬ���ͻ���Ϣ:%s�ɹ�",iter->strClientId.c_str());
				//DISPLAY_LOG("ͬ������",szBuf,"","",1);
				TTRACE("%s[%d]:ͬ���ͻ���Ϣ:%s�ɹ�\r\n", __FUNCTION__, __LINE__, iter->strClientId.c_str());
			}
			
		}
// 		//�洢ͬ��ʱ��
// 		CString strTime = _T("");
// 		if(!m_pDbOper->QueryClientInfoLastSyncTime(strTime))
// 		{
// 			DISPLAY_LOG(_T("ͬ������"),_T("�洢ͬ��ʱ��ʧ�ܣ��ȴ�����"), _T(""), _T(""), 0);
// 			Sleep(1000);
// 			return false;
// 		}
	}
	char szBuf[255] = { 0 };
	sprintf(szBuf, "�ϴ��ͻ���Ϣ�������ɹ�[%d]����¼��ʧ��[%d]����¼", nSuccessCount, nFailedCount);
	DISPLAY_LOG("ͬ������", szBuf, "", "", 1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::StartSync( IN ISOC_DWORDPTR dwReserved /*= 0*/ )
{
	STRY;
	if(m_pThread)
	{
		m_pThread->SetRunAbleInterface(this);
		m_pThread->Start();
	}
	else
	{
		iSOC_MonFactoryManagement fmt;
		m_pThread = (IThread*)fmt.CreateObject(OBJECT_TYPE_THREAD,"",__FUNCTION__);
		if(m_pThread)
		{
			m_pThread->SetRunAbleInterface(this);
			m_pThread->Start();
		}
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::StopSync( IN ISOC_DWORDPTR dwReserved /*= 0*/ )
{
	STRY;
	m_bNeedStop = TRUE;
	if (m_pThread)
	{
		m_syncEvent.SendEvent();
		while(m_pThread->IsAlive())
		{
			Sleep(30);
		}
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::SetLocalUrl(IN const string& szUrl,IN ISOC_DWORDPTR dwReserved /*= 0*/)
{
	m_strUrl = szUrl;
	return 1;
}

bool XhBFISSyncClientRouterImp:: GetNeedSyncClientInfo(vector<ST_ClientInfo>& vecClientInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pCache->QueryClientInfo3Param(vecClientInfo,"",dwReserved))
	{
		DISPLAY_LOG(_T("ͬ������"),_T("��ȡδͬ���û���Ϣʧ�ܣ��ȴ�����"), _T(""), _T(""), 0);
		Sleep(1000);
		return false;
	}
	return true;
	SCATCH;
	return false;
}

bool XhBFISSyncClientRouterImp::GetNeedSyncBusinessInfo(vector<ST_BusinessInfo>& vecBusinessInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pCache->QueryBusinessInfoNeed2Sync(vecBusinessInfo))
	{
		DISPLAY_LOG(_T("ͬ������"),_T("��ȡδͬ��ҵ����Ϣʧ�ܣ��ȴ�����"), _T(""), _T(""), 0);
		Sleep(1000);
		return false;
	}
	return true;
	SCATCH;
	return false;
}
bool XhBFISSyncClientRouterImp::GetNeedSyncBusinessFileInfo(vector<ST_BusinessFileInfo>& vecBusinessFileInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pCache->QueryBusinessFileInfoNeed2Sync(vecBusinessFileInfo))
	{
		DISPLAY_LOG(_T("ͬ������"),_T("��ȡδͬ��ҵ���ļ���Ϣʧ�ܣ��ȴ�����"), _T(""), _T(""), 0);
		Sleep(1000);
		return false;
	}
	return true;
	SCATCH;
	return false;
}
bool XhBFISSyncClientRouterImp::GetNeedSyncBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecBusinessRelateInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pCache->QueryBusinessRelateInfoNeed2Sync(vecBusinessRelateInfo))
	{
		DISPLAY_LOG(_T("ͬ������"),_T("��ȡδͬ��ҵ�������Ϣʧ�ܣ��ȴ�����"), _T(""), _T(""), 0);
		Sleep(1000);
		return false;
	}
	return true;
	SCATCH;
	return false;
}
bool XhBFISSyncClientRouterImp::GetNeedSyncEmployeeInfo(vector<ST_EmployeeInfo>& vecEmployeeInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pCache->QueryEmployeeInfoNeed2Sync(vecEmployeeInfo))
	{
		DISPLAY_LOG(_T("ͬ������"),_T("��ȡδͬ����Ա��Ϣʧ�ܣ��ȴ�����"), _T(""), _T(""), 0);
		Sleep(1000);
		return false;
	}
	return true;
	SCATCH;
	return false;
}

bool XhBFISSyncClientRouterImp::GetNeedSyncEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecEmployeePurviewInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if(!m_pCache->QueryEmployeePurviewInfoNeed2Sync(vecEmployeePurviewInfo))
	{
		DISPLAY_LOG(_T("ͬ������"),_T("��ȡδͬ����Ա��Ϣʧ�ܣ��ȴ�����"), _T(""), _T(""), 0);
		Sleep(1000);
		return false;
	}
	return true;
	SCATCH;
	return false;
}

int XhBFISSyncClientRouterImp::DoSyncBusinessInfo( vector<ST_BusinessInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if (vecInfos.empty())
		return 1;

	DISPLAY_LOG(_T("ͬ������"), _T("�ϴ�ҵ����Ϣ��ʼ"), _T(""), _T(""), 1);
	int nSuccessCount = 0;
	int nFailedCount  = 0;
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter++)
	{
		std::string strOutData;
		bool bSeralizeSuccess = iter->ConvertToString(strOutData);
		if (!bSeralizeSuccess)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("���л�ҵ����Ϣʧ��"), _T(""), _T(""), 0); 
			return -1;
		}
		int nRet = -1;
		STRY;
		Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
		if (nullptr == m_hServerContext)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
			return -1;
		}
		iBFIS_CommunicationInvoker invoke(m_hServerContext);
		DWORD_PTR dwCmd = MSG_UPLOAD_BUSINESSINFO;
		nRet = invoke.Invoke(dwCmd, strOutData);
		SCATCH;
		if (nRet <= 0)
		{
			TTRACE(_T("%s[%d]:ͬ���ϴ�ҵ����Ϣʧ��,ID:%s,����ֵ��%d\r\n")
				   ,__FUNCTION__,__LINE__,iter->strBusinessInfoId.c_str(),nRet);
			//char szBuf[255] = {0};
			//sprintf(szBuf,"ͬ���ϴ�ҵ����Ϣʧ��,ID:%s",iter->strBusinessInfoId.c_str());
			//DISPLAY_LOG("ͬ������",szBuf,"","",0);
			nFailedCount ++;
	 	}
		else
 		{
			//����ͬ��״̬
 			nRet = m_pCache->SetSyncComplete(DataType_BusinessInfo, iter->strBusinessInfoId);
			TTRACE(_T("%s[%d]:�����ϴ�ҵ����Ϣͬ����ʶ[%s],ID:%s,���ݿⷵ��ֵ��%d\r\n")
				   ,__FUNCTION__,__LINE__,nRet>0?"�ɹ�":"ʧ��",iter->strBusinessInfoId.c_str(),nRet);
			//char szBuf[255] = {0};
			//sprintf(szBuf,"ͬ���ϴ�ҵ����Ϣ%s,ID:%s",iter->strBusinessInfoId.c_str(),nRet>0?"�ɹ�":"ʧ��");
			//DISPLAY_LOG("ͬ������",szBuf,"","",nRet>0?1:0);
			nSuccessCount++;
		}
	}
	CString strDes;
	strDes.Format("�ϴ�ҵ����Ϣ�������ɹ�[%d]����¼��ʧ��[%d]����¼",nSuccessCount,nFailedCount);
	DISPLAY_LOG("ͬ������",(LPCTSTR)strDes, "", "", 1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::DoSyncBusinessFileInfo( vector<ST_BusinessFileInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if (vecInfos.empty())
		return 1;

	DISPLAY_LOG(_T("ͬ������"), _T("�ϴ�ҵ���ļ���Ϣ��ʼ"), _T(""), _T(""), 1);
	int nSuccessCount = 0;
	int nFailedCount  = 0;
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter++)
	{
		std::string strOutData;
		bool bSeralizeSuccess = iter->ConvertToString(strOutData);
		if (!bSeralizeSuccess)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("���л�ҵ���ļ���Ϣʧ��"), _T(""), _T(""), 0); 
			return -1;
		}

		int nRet = -1;
		STRY;
		Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
		if (nullptr == m_hServerContext)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
			return -1;
		}
		iBFIS_CommunicationInvoker invoke(m_hServerContext);
		DWORD_PTR dwCmd = MSG_UPLOAD_BUSINESSFILEINFO;
		nRet = invoke.Invoke(dwCmd, strOutData);
		SCATCH;
		if (nRet <= 0)
		{
			TTRACE(_T("%s[%d]:ͬ��ҵ���ļ���Ϣʧ��,ID:%s,����ֵ��%d\r\n"),__FUNCTION__,__LINE__,iter->strRecordId.c_str(),nRet);
			//char szBuf[255] = {0};
			//sprintf(szBuf,"ͬ��ҵ���ļ���Ϣʧ��,ID:%s",iter->strRecordId.c_str());
			//DISPLAY_LOG("ͬ������",szBuf,"","",0);
			nFailedCount++;
		}
		else
		{
			//����ͬ��״̬
			nRet = m_pCache->SetSyncComplete(DataType_BusinessFileInfo, iter->strRecordId);
			TTRACE(_T("%s[%d]:����ҵ����Ϣͬ����ʶ[%s],ID:%s,���ݿⷵ��ֵ��%d\r\n")
				,__FUNCTION__,__LINE__,nRet>0?"�ɹ�":"ʧ��",iter->strRecordId.c_str(),nRet);
			//char szBuf[255] = {0};
			//sprintf(szBuf,"ͬ��ҵ���ļ���Ϣ�ɹ�,ID:%s",iter->strRecordId.c_str());
			//DISPLAY_LOG("ͬ������",szBuf,"","",1);
			nSuccessCount++;
		}
	}
	CString strDes;
	strDes.Format("�ϴ�ҵ���ļ���Ϣ�������ɹ�[%d]����¼��ʧ��[%d]����¼",nSuccessCount,nFailedCount);
	DISPLAY_LOG("ͬ������",(LPCTSTR)strDes, "", "", 1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::DoSyncBusinessRelateInfo( vector<ST_BusinessRelateInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if (vecInfos.empty())
		return 1;

	int nSuccessCount = 0;
	int nFailedCount  = 0;
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter++)
	{
		std::string strOutData;
		bool bSeralizeSuccess = iter->ConvertToString(strOutData);
		if (!bSeralizeSuccess)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("���л�ҵ�������Ϣʧ��"), _T(""), _T(""), 0); 
			return -1;
		}
		int nRet = -1;
		STRY;
		Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
		if (nullptr == m_hServerContext)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
			return -1;
		}
		iBFIS_CommunicationInvoker invoke(m_hServerContext);
		DWORD_PTR dwCmd = MSG_UPLOAD_BUSINESSRELATEINFO;
		nRet = invoke.Invoke(dwCmd, strOutData);
		SCATCH;
		if (nRet <= 0)
		{
			TTRACE(_T("%s[%d]:ͬ��ҵ�������Ϣʧ��,ID:%s,����ֵ��%d\r\n"),__FUNCTION__,__LINE__,iter->strBusinessRelateInfoId.c_str(),nRet);
			char szBuf[255] = {0};
			sprintf(szBuf,"ͬ��ҵ�������Ϣʧ��,ID:%s",iter->strBusinessRelateInfoId.c_str());
			DISPLAY_LOG("ͬ������",szBuf,"","",0);
			nFailedCount++;
		}
		else
		{
			//����ͬ��״̬
			nRet = m_pCache->SetSyncComplete(DataType_BusinessRelationInfo, iter->strBusinessRelateInfoId);
			TTRACE(_T("%s[%d]:����ҵ�����ͬ����ʶ[%s],ID:%s,���ݿⷵ��ֵ��%d\r\n")
				,__FUNCTION__,__LINE__,nRet>0?"�ɹ�":"ʧ��",iter->strBusinessRelateInfoId.c_str(),nRet);
			char szBuf[255] = {0};
			sprintf(szBuf,"ͬ��ҵ�������Ϣ�ɹ�,ID:%s",iter->strBusinessRelateInfoId.c_str());
			DISPLAY_LOG("ͬ������",szBuf,"","",1);
			nSuccessCount++;
		}
	}
	CString strDes;
	strDes.Format("ͬ��ҵ�������Ϣ���ɹ�[%d]����¼��ʧ��[%d]����¼",nSuccessCount,nFailedCount);
	DISPLAY_LOG("ͬ������",(LPCTSTR)strDes, "", "", 1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::SetSyncInterval( IN ISOC_INT nSecond, IN ISOC_DWORDPTR dwReserved /*= 0*/ )
{
	STRY;
	m_nSyncInterval = nSecond;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::DoSyncEmployeeInfo( vector<ST_EmployeeInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if (vecInfos.empty())
		return 1;

	DISPLAY_LOG(_T("ͬ������"), _T("�ϴ�Ա����Ϣ��ʼ"), _T(""), _T(""), 1);
	int nSuccessCount = 0;
	int nFailedCount  = 0;
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter ++)
	{
		if (iter->nExtendedInfo != 1)
		{
			std::string strOutData;
			bool bSeralizeSuccess = iter->ConvertToString(strOutData);
			if (!bSeralizeSuccess)
			{
				DISPLAY_LOG(_T("ͬ������"),_T("���л�Ա����Ϣʧ��"), _T(""), _T(""), 0); 
				return -1;
			}
			int nRet = -1;
			STRY;
			Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
			if (nullptr == m_hServerContext)
			{
				DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
				return -1;
			}
			iBFIS_CommunicationInvoker invoke(m_hServerContext);
			DWORD_PTR dwCmd = MSG_UPLOAD_EMPLOYEEINFO;
			nRet = invoke.Invoke(dwCmd, strOutData);
			SCATCH;
			if (nRet <= 0)
			{
				TTRACE(_T("%s[%d]:ͬ��Ա����Ϣʧ��,ID:%s,����ֵ��%d\r\n"),__FUNCTION__,__LINE__,iter->strEmployeeId.c_str(),nRet);
				//char szBuf[256] = {0};
				//sprintf(szBuf,"ͬ��Ա����Ϣʧ��,ID:%s ",iter->strEmployeeId.c_str());
				//DISPLAY_LOG("ͬ������",szBuf,"","",0);
				nFailedCount++;
			}
			else
			{
				//����ͬ��״̬
				nRet = m_pCache->SetSyncComplete(DataType_EmployeeInfo, iter->strEmployeeId);
				TTRACE(_T("%s[%d]:����Ա��ͬ����ʶ[%s],ID:%s,���ݿⷵ��ֵ��%d\r\n")
					,__FUNCTION__,__LINE__,nRet>0?"�ɹ�":"ʧ��",iter->strEmployeeId.c_str(),nRet);
				//char szBuf[256] = {0};
				//sprintf(szBuf,"ͬ��Ա����Ϣ�ɹ�,ID:%s",iter->strEmployeeId.c_str());
				//DISPLAY_LOG("ͬ������",szBuf,"","",1);
				nSuccessCount++;
			}
		}
	}	
	CString strDes;
	strDes.Format("�ϴ�Ա����Ϣ�������ɹ�[%d]����¼��ʧ��[%d]����¼",nSuccessCount,nFailedCount);
	DISPLAY_LOG("ͬ������",(LPCTSTR)strDes, "", "", 1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::DoSyncEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecInfos, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (vecInfos.empty())
		return 1;

	DISPLAY_LOG(_T("ͬ������"), _T("�ϴ�Ա��Ȩ����Ϣ��ʼ"), _T(""), _T(""), 1);
	int nSuccessCount = 0;
	int nFailedCount  = 0;
	//iBFIS_CommunicationInvoker invoke(m_hServerContext);
	DWORD_PTR dwCmd /*= MSG_DELETE_EMPLOYEEPURVIEWINFO*/;
#if 0
	vector<std::string> vecStr;
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter ++)
	{
		auto it = find(vecStr.begin(),vecStr.end(),(*iter).strEmployeeId);
		if (it == vecStr.end())
		{
			vecStr.push_back((*iter).strEmployeeId);
		}
	}
	int nRet = 0;
	STRY;
	Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
	iBFIS_CommunicationInvoker invoke(m_hServerContext);
	nRet = invoke.Invoke(dwCmd, vecStr);
	SCATCH;
	if (nRet < 0)
	{
		DISPLAY_LOG("ͬ������","������ɾ��Ա����Ϣʧ��","","",0);
		return -1;
	}
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter ++)
	{
		std::string strInfo;
		bool bSeralizeSuccess = (ST_EmployeePurviewInfo(*iter)).ConvertToString(strInfo);
		if (!bSeralizeSuccess)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("���л�Ա����Ϣʧ��"), _T(""), _T(""), 0); 
			return -1;
		}
		dwCmd = MSG_UPLOAD_EMPLOYEEPURVIEWINFO;
		nRet = -1;
		STRY;
		Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
		iBFIS_CommunicationInvoker invoke(m_hServerContext);
		nRet = invoke.Invoke(dwCmd, strInfo);
		SCATCH;
		if (nRet <= 0)
		{
			TTRACE(_T("%s[%d]:ͬ����ԱȨ����Ϣʧ��,ID:%s,����ֵ��%d\r\n"),__FUNCTION__,__LINE__,iter->strEmployeePurviewId.c_str(),nRet);
			nFailedCount++;
		}
		else
		{
			//����ͬ��״̬
			nRet = m_pCache->SetSyncComplete(DataType_EmployeePurviewInfo, iter->strEmployeePurviewId);
			TTRACE(_T("%s[%d]:���ù�ԱȨ��ͬ����ʶ[%s],ID:%s,���ݿⷵ��ֵ��%d\r\n")
				,__FUNCTION__,__LINE__,nRet>0?"�ɹ�":"ʧ��",iter->strEmployeePurviewId.c_str(),nRet);
			nSuccessCount++;
		}
	}
#endif
	//����Ա��id����
	map<std::string, vector<ST_EmployeePurviewInfo> > mapUploadInfos;
	for each(auto& item in vecInfos)
	{
		auto iter = mapUploadInfos.find(item.strEmployeeId);
		if (iter == mapUploadInfos.end())
		{
			vector<ST_EmployeePurviewInfo> vecTmp;
			mapUploadInfos[item.strEmployeeId] = vecTmp;
			mapUploadInfos[item.strEmployeeId].push_back(item);
		}
		else
		{
			iter->second.push_back(item);
		}
	}

	for (auto iter = mapUploadInfos.begin(); iter != mapUploadInfos.end(); iter++)
	{
		vector<std::string> vecStrUploadData;
		for (auto iterInfo = iter->second.begin(); iterInfo != iter->second.end(); iterInfo++)
		{
			std::string strInfo;
			bool bSeralizeSuccess = iterInfo->ConvertToString(strInfo);
			if (!bSeralizeSuccess)
			{
				DISPLAY_LOG(_T("ͬ������"),_T("���л�Ա����Ϣʧ��"), _T(""), _T(""), 0); 
				return -1;
			}
			vecStrUploadData.push_back(strInfo);
		}
		dwCmd = MSG_UPLOAD_EMPLOYEEPURVIEWINFO;
		int nRet = -1;
		STRY;
		Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
		if (nullptr == m_hServerContext)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
			return -1;
		}
		iBFIS_CommunicationInvoker invoke(m_hServerContext);
		nRet = invoke.Invoke(dwCmd, vecStrUploadData);
		SCATCH;
		if (nRet <= 0)
		{
			TTRACE(_T("%s[%d]:ͬ����ԱȨ����Ϣʧ��,ID:%s,����ֵ��%d\r\n"),__FUNCTION__,__LINE__,iter->first.c_str(),nRet);
			nFailedCount++;
		}
		else
		{
			//����ͬ��״̬
			nRet = m_pCache->SetSyncComplete(DataType_EmployeePurviewInfo, iter->first);
			TTRACE(_T("%s[%d]:���ù�ԱȨ��ͬ����ʶ[%s],ID:%s,���ݿⷵ��ֵ��%d\r\n")
				,__FUNCTION__,__LINE__,nRet>0?"�ɹ�":"ʧ��",iter->first.c_str(),nRet);
			nSuccessCount++;
		}
	}
	CString strDes;
	strDes.Format("�ϴ�Ա��Ȩ����Ϣ�������ɹ�[%d]����¼��ʧ��[%d]����¼",nSuccessCount,nFailedCount);
	DISPLAY_LOG("ͬ������",(LPCTSTR)strDes, "", "", 1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::DoSyncProduceInfo(DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	std::vector<std::string> vecGetData;
	std::string strSyncTime = "";
	if (m_pCache && m_pCache->QueryMinProduceSyncTime(strSyncTime) != QueryFail)
	{
		vecGetData.push_back(strSyncTime);
	}
	else
	{
		DISPLAY_LOG("ͬ������","��ȡ��Ҫͬ���Ĳ�Ʒ��Ϣʧ��","��ѯ��Ʒͬ��ʱ��ʧ��","",0);
		return -1;
	}
	int nRet = -1;
	STRY;
	Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
	if (nullptr == m_hServerContext)
	{
		DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
		return -1;
	}
	iBFIS_CommunicationInvoker invoke(m_hServerContext);
	DWORD_PTR dwCmd = MSG_GET_PRODUCEINFO;
	nRet = invoke.Invoke(dwCmd, vecGetData);
	SCATCH;
	if (nRet < 0)
	{
		TTRACE(_T("%s[%d]:��ȡ��Ʒ��Ϣʧ�ܷ���ֵ��%d\r\n"),__FUNCTION__,__LINE__,nRet);
		DISPLAY_LOG("ͬ������","��ȡ��Ʒ��Ϣʧ��","","",0);
	}
	else
	{
		if(vecGetData.empty())
		{
			DISPLAY_LOG("ͬ������","��ȡ��Ҫͬ���Ĳ�Ʒ��ϢΪ��","","",1);
		}
		for each(auto strdata in vecGetData)
		{
			BFIS::ProduceInfo msg;
			if(msg.ParseFromString(strdata))
			{
				ST_ProduceInfo stInfo(msg);
				int nRet = StoreProduceInfo(DBO_ADD,stInfo);
				if (nRet && m_pCache)
				{
					m_pCache->SetSyncComplete(DataType_ProduceInfo,stInfo.strProduceId);
					if(m_pComm->AddNotifyMsg(DBO_ADD,IBFIS_MSG_CLIENT_NOTIFY_PRODUCEINFO,strdata) <= 0)
					{
						TTRACE(_T("%s[%d]:����֪ͨʧ��,��ƷID:%s \r\n"),__FUNCTION__,__LINE__,stInfo.strProduceId.c_str());
					}
				}
			}
		}
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::DoSyncBranchInfo(vector<ST_BranchInfo>& vecInfos,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	DISPLAY_LOG(_T("ͬ������"), _T("�ϴ�������Ϣ��ʼ"), _T(""), _T(""), 1);
	std::string strTemp;
	char szBuf[255] = {0};
	int nSuccessCount = 0;
	int nFailedCount = 0;
	DWORD_PTR dwCmd = MSG_UPLOAD_BRANCHINFO;
	for (auto iter = vecInfos.begin() ; iter != vecInfos.end(); iter ++)
	{
		if(iter->ConvertToString(strTemp))
		{
			int nRet = -1;
			STRY;
			Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
			if (nullptr == m_hServerContext)
			{
				DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
				return -1;
			}
			iBFIS_CommunicationInvoker invoke(m_hServerContext);
			nRet = invoke.Invoke(dwCmd,strTemp);
			SCATCH;
			if(nRet <= 0)
			{
				TTRACE(_T("%s[%d]:�ϴ�����%s[%s]��Ϣʧ��,������[%d] \r\n"), __FUNCTION__, __LINE__, iter->strName.c_str(), iter->strBranchId.c_str(), nRet);
				//sprintf(szBuf,"�ϴ�����%s[%s]��Ϣʧ��",iter->strName.c_str(),iter->strBranchId.c_str());
				//DISPLAY_LOG("ͬ������",szBuf,"","",0);
				++nFailedCount;
			}
			else
			{
				m_pCache->SetSyncComplete(DataType_BranceInfo, iter->strBranchId);
				TTRACE(_T("%s[%d]:�ϴ�����%s[%s]��Ϣ�ɹ� \r\n"), __FUNCTION__, __LINE__, iter->strName.c_str(), iter->strBranchId.c_str());
				//sprintf(szBuf, "�ϴ�����%s[%s]��Ϣ�ɹ�", iter->strName.c_str(), iter->strBranchId.c_str());
				//DISPLAY_LOG("ͬ������", szBuf, "", "", 1);
				++nSuccessCount;
			}
		}
	}
	char szBuf2[255] = { 0 };
	sprintf(szBuf2, "�ϴ�������Ϣ�������ɹ�[%d]����¼��ʧ��[%d]����¼", nSuccessCount, nFailedCount);
	DISPLAY_LOG(_T("ͬ������"), szBuf2, _T(""), _T(""), 1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::DoSyncRoleInfo(std::vector<ST_RoleInfo>& vecInfos,DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	DISPLAY_LOG(_T("ͬ������"), _T("�ϴ���ɫ��Ϣ��ʼ"), _T(""), _T(""), 1);
	std::string strData;
	DWORD_PTR dwCmd = MSG_UPLOAD_ROLEINFO;
	char szBuf[255] = {0};
	int nSuccessCount = 0;
	int nFailedCount = 0;
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter ++)
	{
		if(iter->nExtendedInfo == -2)
		{
			if(iter->ConvertToString(strData))
			{
				int nRet = -1;
				STRY;
				Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
				if (nullptr == m_hServerContext)
				{
					DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
					return -1;
				}
				iBFIS_CommunicationInvoker invoke(m_hServerContext);
				nRet = invoke.Invoke(dwCmd,strData);
				SCATCH;
				if(nRet <= 0)
				{
					TTRACE(_T("%s[%d]:�ϴ���ɫ%s[%s]��Ϣʧ��,������[%d] \r\n"), __FUNCTION__, __LINE__, iter->strRoleName.c_str(), iter->strRoleInfoId.c_str(), nRet);
					//sprintf(szBuf,"�ϴ��û�%s[%s]��Ϣʧ��",iter->strRoleName.c_str(),iter->strRoleInfoId.c_str());
					//DISPLAY_LOG("ͬ������",szBuf,"","",0);
					++nFailedCount;
				}
				else
				{
					m_pCache->SetSyncComplete(DataType_RoleInfo, iter->strRoleInfoId);
					//sprintf(szBuf,"�ϴ��û�%s[%s]��Ϣ�ɹ�",iter->strRoleName.c_str(),iter->strRoleInfoId.c_str());
					//DISPLAY_LOG("ͬ������",szBuf,"","",1);
					TTRACE(_T("%s[%d]:�ϴ���ɫ%s[%s]��Ϣ�ɹ� \r\n"), __FUNCTION__, __LINE__, iter->strRoleName.c_str(), iter->strRoleInfoId.c_str());
					++nSuccessCount;
				}
			}
		}		
	}
	char szBuf2[255] = { 0 };
	sprintf(szBuf2, "�ϴ���ɫ��Ϣ�������ɹ�[%d]����¼��ʧ��[%d]����¼", nSuccessCount, nFailedCount);
	DISPLAY_LOG(_T("ͬ������"), szBuf2, _T(""), _T(""), 1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::DoSyncRolePurview(std::vector<ST_RolePurviewInfo>& vecInfos,DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	DISPLAY_LOG(_T("ͬ������"), _T("�ϴ���ɫȨ����Ϣ��ʼ"), _T(""), _T(""), 1);
	
	DWORD_PTR dwCmd = MSG_UPLOAD_ROLEPURVIEWINFO;

	std::vector<string> dataVec;
	for(auto iter = vecInfos.begin();iter != vecInfos.end();iter++)
	{
		std::string data;
		if (iter->ConvertToString(data))
		{
			dataVec.push_back(std::move(data));
		}
		else
		{
			return -1;
		}
	}

	int nFailedCount = 0;
	int nSuccessCount = dataVec.size();

	int nRet = -1;
	STRY;
	Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
	if (nullptr == m_hServerContext)
	{
		DISPLAY_LOG(_T("ͬ������"), _T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0);
		return -1;
	}
	
	iBFIS_CommunicationInvoker invoke(m_hServerContext);
	nRet = invoke.Invoke(dwCmd, dataVec);
	SCATCH;
	if (nRet <= 0)
	{
		TTRACE(_T("%s[%d]:ͬ���û�Ȩ����Ϣʧ��,������[%d]\r\n"), __FUNCTION__, __LINE__, nRet);
		nFailedCount = nSuccessCount;
		nSuccessCount = 0;
	}

	CString strDes;
	strDes.Format("�ϴ���ɫȨ����Ϣ�������ɹ�[%d]����¼��ʧ��[%d]����¼", nSuccessCount, nFailedCount);
	DISPLAY_LOG("ͬ������", (LPCTSTR)strDes, "", "", 1);
	return 1;
	SCATCH;
	return -1;
}
int	XhBFISSyncClientRouterImp::ReadClientInfoSyncTime(std::string& strTime)
{
	STRY;
	char* buffer = new char[21];
	ifstream in("ClientInfoSyncTime.txt");
	if (!in.is_open())
	{
		cout << "Error opening file"; 
	}
	if (!in.eof())
	{
		in.getline(buffer, 21);
	}
	strTime = buffer;
	delete[] buffer;
	return 1;
	SCATCH;
	return -1;
}
int XhBFISSyncClientRouterImp::WriteClientInfoSyncTime()
{
	STRY;
	time_t tt = time(NULL);//��䷵�ص�ֻ��һ��ʱ��cuo
	tm* t = localtime(&tt);
	char* szTime =  new char[21];
	sprintf(szTime,"%d-%02d-%02d %02d:%02d:%02d\n",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min,
		t->tm_sec);
	ofstream out("ClientInfoSyncTime.txt");
	if (out.is_open())
	{
		out << szTime;
		out.close();
	}
	delete[] szTime;
	return 1;
	SCATCH;
	return -1;
}
int XhBFISSyncClientRouterImp::GetSyncClientInfo(DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	//��ѯ�ͻ���Ϣ���ͬ��ʱ��
	std::string strTime = "";
	if (ReadClientInfoSyncTime(strTime) < 0)
	{
		DISPLAY_LOG("ͬ��", "��ȡ�ͻ���Ϣ���ͬ��ʱ��ʧ��", "", "", 0);
		return -1;
	}
	/*if (!m_pCache || !m_pCache->QueryClientInfoLastSyncTime(strTime))
	{
		DISPLAY_LOG("ͬ��","��ȡ�ͻ���Ϣ���ͬ��ʱ��ʧ��","","",0);
		return -1;
	}*/
	if(strTime == "")
	{
		strTime = "2000-01-01 00:00:00";
	}
	std::vector<std::string> vecClientInfo;
	vecClientInfo.push_back(strTime);
	DWORD_PTR dwCmd = MSG_GET_CLIENTINFO;
	int nRet = -1;
	STRY;
	Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
	if (nullptr == m_hServerContext)
	{
		DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
		return -1;
	}
	iBFIS_CommunicationInvoker invoke(m_hServerContext);
	nRet = invoke.Invoke(dwCmd,vecClientInfo);
	SCATCH;
	if (nRet <=0 )
	{
		TTRACE(_T("%s[%d]:��ȡ�ͻ���Ϣʧ�ܷ���ֵ��%d\r\n"),__FUNCTION__,__LINE__,nRet);
		DISPLAY_LOG("ͬ������","��ȡ�ͻ���Ϣʧ��","","",0);
	}
	else
	{
#if 1
		if(vecClientInfo.empty())
		{
			DISPLAY_LOG("ͬ������","��Ҫͬ���Ŀͻ���ϢΪ��","","",1);
		}
		for each(auto clientinfo in vecClientInfo)
		{
			BFIS::ClientInfo msg;
			if(msg.ParseFromString(clientinfo))
			{
				ST_ClientInfo stInfo(msg);
				int nRet = StoreClientInfo(DBO_ADD,stInfo);
				if (nRet && m_pCache)
				{
					m_pCache->SetSyncComplete(DataType_ClientInfo,stInfo.strClientId);
					if(m_pComm->AddNotifyMsg(DBO_ADD,IBFIS_MSG_CLIENT_NOTIFY_CLIENTINFO,clientinfo) <= 0)
					{
						TTRACE(_T("%s[%d]:����֪ͨʧ��,�ͻ�ID:%s"),__FUNCTION__,__LINE__,stInfo.strClientId.c_str());
					}
				}
			}
		}
#else
		int nSuccessCount = 0;
		int nFailedCount  = 0;
		vector<ST_ClientInfo> vecInfo = m_vecBackupClient;
		m_vecBackupClient.clear();
		for (int i = 0 ; i < vecInfo.size() ; i ++)
		{
			DBOperType enType = DBO_INVAILED;
			ST_ClientInfo stClientInfo;
			BOOL bStore = StoreClientInfo(enType,stClientInfo,nFailedCount,nSuccessCount);
			if (bStore)
			{
				string strInfo;
				bool bSuccess = stClientInfo.ConvertToString(strInfo);
				if (bSuccess)
				{
					if(m_pComm->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_CLIENTINFO,strInfo) <= 0)
					{
						TTRACE(_T("%s[%d]:����֪ͨʧ��,�ͻ�ID:%s"),__FUNCTION__,__LINE__,stClientInfo.strClientId.c_str());
					}
				}
			}
			else
			{
				m_vecBackupClient.push_back(stClientInfo);
			}
		}
		if (vecClientInfo.empty())
		{
			TTRACE(_T("%s[%d]:δ��ȡ���ͻ���Ϣ���������Ƿ�����ӣ�"),__FUNCTION__,__LINE__);
			DISPLAY_LOG("ͬ������","��ȡ���ͻ���ϢΪ��","�������Ƿ��Ѿ����?","",1);
		}
		else
		{
			for (auto iter = vecClientInfo.begin() ; iter != vecClientInfo.end() ; iter ++)
			{
				BFIS::ClientInfo msg;
				bool bSuccess = msg.ParseFromString(*iter);
				if (bSuccess)
				{
					DBOperType enType = DBO_INVAILED;
					ST_ClientInfo stClientInfo(msg);
					BOOL bStore = StoreClientInfo(enType,stClientInfo,nFailedCount,nSuccessCount);
					if (bStore)
					{
						string strInfo;
						bSuccess = stClientInfo.ConvertToString(strInfo);
						if (bSuccess)
						{
							if(m_pComm->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_CLIENTINFO,strInfo) <= 0)
							{
								TTRACE(_T("%s[%d]:����֪ͨʧ��,�ͻ�ID:%s"),__FUNCTION__,__LINE__,stClientInfo.strClientId.c_str());
							}
						}
					}
					else
					{
						m_vecBackupClient.push_back(stClientInfo);
					}
				}
			}
		}
		CString strDes;
		strDes.Format("��ȡ�ͻ���Ϣ���ɹ�[%d]����¼��ʧ��[%d]����¼",nSuccessCount,nFailedCount);
		DISPLAY_LOG("ͬ������",(LPCTSTR)strDes, "", "", 1);
#endif
	}
	WriteClientInfoSyncTime();
	return 1;
	SCATCH;
	return -1;
}
#if 0
int XhBFISSyncClientRouterImp::DoSyncPurview( DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	std::vector<std::string> vecPurview;
	iBFIS_CommunicationInvoker invoke(m_hServerContext);
	DWORD_PTR dwCmd = MSG_GET_PURVIEWINFO;
	int nRet = invoke.Invoke(dwCmd, vecPurview);
	if (nRet <= 0)
	{
		SFTRACE("SyncInfo", "%s[%d]:��ȡȨ����Ϣʧ�ܷ���ֵ��%d\r\n", __FUNCTION__, __LINE__, nRet);
	}
	else
	{
		vector<ST_PurviewInfo> vecInfo = m_vecBackupPurview;
		m_vecBackupPurview.clear();
		for (int i = 0 ; i < vecInfo.size() ; i ++)
		{
			DBOperType enType = DBO_INVAILED;
			ST_PurviewInfo stPurviewInfo;
			BOOL bStore = StorePurviewInfo(enType,stPurviewInfo);
			if (bStore)
			{
				string strInfo;
				bool bSuccess = stPurviewInfo.ConvertToString(strInfo);
				if (bSuccess)
				{
					if(m_pComm->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_PURVIEWINFO,strInfo) <= 0)
					{
						TTRACE(_T("%s[%d]:����֪ͨʧ��,Ȩ��ID:%s"),__FUNCTION__,__LINE__,stPurviewInfo.strPurviewInfoId.c_str());
					}
				}
			}
			else
			{
				m_vecBackupPurview.push_back(stPurviewInfo);
			}
		}
		if (vecPurview.empty())
		{
			SFTRACE("SyncInfo", "%s[%d]:δ��ȡ��Ȩ����Ϣ���������Ƿ��Ѿ���ӣ�", __FUNCTION__, __LINE__);
		}
		else
		{
			for (auto iter = vecPurview.begin(); iter != vecPurview.end(); iter++)
			{
				BFIS::PurviewInfo msg;
				bool bSuccess = msg.ParseFromString(*iter);
				if (bSuccess)
				{
					DBOperType enType = DBO_INVAILED;
					ST_PurviewInfo stPurviewInfo(msg);
					BOOL bStore = StorePurviewInfo(enType,stPurviewInfo);
					if (bStore)
					{
						string strInfo;
						bSuccess = stPurviewInfo.ConvertToString(strInfo);
						if (bSuccess)
						{
							if(m_pComm->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_PURVIEWINFO,strInfo) <= 0)
							{
								TTRACE(_T("%s[%d]:����֪ͨʧ��,Ȩ��ID:%s"),__FUNCTION__,__LINE__,stPurviewInfo.strPurviewInfoId.c_str());
							}
						}
					}
					else
					{
						m_vecBackupPurview.push_back(stPurviewInfo);
					}
				}
			}
		}
	}
	return 1;
	SCATCH;
	return -1;
}
#endif
int XhBFISSyncClientRouterImp::DoLogin( DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if(m_stBranchInfo.strBranchId == "")
	{
		TTRACE("[ͬ������]��¼�ϼ�������ʧ��,û�б���������Ϣ %s[%d]\r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	DWORD_PTR dwCmd = MSG_LOGIN;
	std::string strOutData;
	m_stBranchInfo.ConvertToString(strOutData);
	std::vector<std::string> vecInfo;
	vecInfo.push_back(strOutData);
	vecInfo.push_back(m_strUrl);

	Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
	if (nullptr == m_hServerContext)
	{
		DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
		return -1;
	}
	iBFIS_CommunicationInvoker invoke(m_hServerContext);
	int nRet = invoke.Invoke(dwCmd, vecInfo);
	if (nRet <= 0)
	{
		m_hServerContext = nullptr;
		m_bNeedReConnect = TRUE;
		m_cheackConnectCondition.notify_all();
	}
		
	return nRet;
	SCATCH;
	return -1;
}


int XhBFISSyncClientRouterImp::HandleIssuedProduceInfo(const vector<std::string>& vecGetData , DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	//vector<std::string> vecGetData = vecInfos;
	//vecInfos.clear();
	DISPLAY_LOG("ͬ������","���¼���Ʒ��Ϣͬ����ʼ...","","",1);
	for (auto iter = vecGetData.begin(); iter != vecGetData.end(); iter++)
	{
		BFIS::ProduceInfo msg;
		bool bSuccess = msg.ParseFromString(*iter);
		if (!bSuccess)
		{
			DISPLAY_LOG("ǿ��ͬ��","�����·��Ĳ�Ʒ��Ϣ","���л�ʧ��","",0);
			return -1;
		}
		ST_ProduceInfo stProduceInfo(msg),stInfo;
		BOOL bRet = FALSE;
		if (m_pCache && m_pCache->QueryProduceInfoById(stProduceInfo.strProduceId,stInfo))
		{
			bRet = m_pCache->ManageProduceInfo(DBO_UPDATE, stProduceInfo);
			TTRACE(_T("%s[%d]:���²�Ʒ��Ϣ%s����ƷID��%s\r\n"),__FUNCTION__,__LINE__, !bRet?_T("ʧ��"):_T("�ɹ�")
				, stProduceInfo.strProduceId.c_str());
			char szBuf[1024] = {0};
			/*sprintf(szBuf,"���²�Ʒ��Ϣ%s,��ƷID:%s",!bRet?_T("ʧ��"):_T("�ɹ�"),stProduceInfo.strProduceId.c_str());
			DISPLAY_LOG("ͬ������",szBuf,"","",!bRet?0:1);*/
		}
		else if(m_pCache)
		{
			bRet = m_pCache->ManageProduceInfo(DBO_ADD, stProduceInfo);
			TTRACE(_T("%s[%d]:��Ӳ�Ʒ��Ϣ%s����ƷID��%s\r\n"),__FUNCTION__,__LINE__, !bRet?_T("ʧ��"):_T("�ɹ�")
				, stProduceInfo.strProduceId.c_str());
			char szBuf[1024] = {0};
			/*sprintf(szBuf,"��Ӳ�Ʒ��Ϣ%s,��ƷID:%s",!bRet?_T("ʧ��"):_T("�ɹ�"),stProduceInfo.strProduceId.c_str());
			DISPLAY_LOG("ͬ������",szBuf,"","",!bRet?0:1);*/
		}
		/*if (bRet)
		{
			std::string strInfo;
			if(stProduceInfo.ConvertToString(strInfo))
			{
				vecInfos.push_back(strInfo);
			}
		}*/
	}
	DISPLAY_LOG("ͬ������","���¼���Ʒ��Ϣͬ�����","","",1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::HandleIssuedRoleInfo(const vector<std::string>& vecGetData , DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	/*vector<std::string> vecGetData = vecInfos;
	vecInfos.clear();*/
	char szBuff[255] = { 0 };
	sprintf(szBuff, "���¼���ɫ��Ϣͬ����ʼ,���ݴ�С[%d]", vecGetData.size());
	DISPLAY_LOG("ͬ������", szBuff, "", "", 1);
	for (auto iter = vecGetData.begin(); iter != vecGetData.end(); iter++)
	{
		BFIS::RoleInfo msg;
		bool bSuccess = msg.ParseFromString(*iter);
		if (!bSuccess)
		{
			DISPLAY_LOG("ǿ��ͬ��","�����·��Ľ�ɫ��Ϣ","���л�ʧ��","",0);
			return -1;
		}
		ST_RoleInfo stRoleInfo(msg),stInfo;
		stRoleInfo.strBranchInfoId = m_stBranchInfo.strBranchId;
		BOOL bRet = FALSE;
		if (m_pCache && m_pCache->QueryRoleInfoById(stRoleInfo.strRoleInfoId,stInfo))
		{
			bRet = m_pCache->ManageRoleInfo(DBO_UPDATE, stRoleInfo);
			TTRACE(_T("%s[%d]:���½�ɫ��Ϣ%s����ID��%s\r\n"),__FUNCTION__,__LINE__, !bRet?_T("ʧ��"):_T("�ɹ�")
				, stRoleInfo.strRoleInfoId.c_str());
			//char szBuf[1024] = {0};
			//sprintf(szBuf,"���½�ɫ��Ϣ%s,��ID:%s",!bRet?_T("ʧ��"):_T("�ɹ�"),stRoleInfo.strRoleInfoId.c_str());
			//DISPLAY_LOG("ͬ������",szBuf,"","",!bRet?0:1);
		}
		else if (m_pCache)
		{
			bRet = m_pCache->ManageRoleInfo(DBO_ADD, stRoleInfo);
			TTRACE(_T("%s[%d]:��ӽ�ɫ��Ϣ%s����ID��%s\r\n"),__FUNCTION__,__LINE__, !bRet?_T("ʧ��"):_T("�ɹ�")
				, stRoleInfo.strRoleInfoId.c_str());
			//char szBuf[1024] = {0};
			//sprintf(szBuf,"��ӽ�ɫ��Ϣ%s,��ID:%s",!bRet?_T("ʧ��"):_T("�ɹ�"),stRoleInfo.strRoleInfoId.c_str());
			//DISPLAY_LOG("ͬ������",szBuf,"","",!bRet?0:1);
		}
		/*if (bRet)
		{
			std::string strInfo;
			if(stRoleInfo.ConvertToString(strInfo))
			{
				vecInfos.push_back(strInfo);
			}
		}*/
	}
	DISPLAY_LOG("ͬ������", "���¼���ɫ��Ϣͬ�����", "", "", 1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::HandleIssuedRolePurviewInfo(const vector<std::string>& vecGetData , DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	//vector<std::string> vecGetData = vecInfos;
	//vecInfos.clear();
	vector<ST_RoleInfo> vecRoleInfo;
	string strRoleInfoId;
	ST_RoleInfo stHaveRoleInfo;
	char szBuff[255] = { 0 };
	sprintf(szBuff, "���¼���ɫȨ����Ϣͬ����ʼ,���ݴ�С[%d]", vecGetData.size());
	DISPLAY_LOG("ͬ������", szBuff, "", "", 1);

	if(m_pCache && m_pCache->QueryRoleInfo(vecRoleInfo))
	{
		for each(auto roleinfo in vecRoleInfo)
		{
			if(roleinfo.nExtendedInfo == -2 && roleinfo.strBranchInfoId == m_stBranchInfo.strBranchId)
			{
				strRoleInfoId = roleinfo.strRoleInfoId;
				break;
			}
		}
	}
	vector<ST_RolePurviewInfo> vecCurrInfo;
	vector<ST_RolePurviewInfo> vecRolePurviewInfoParse;
	std::set<std::string>  roleMap;
	for (auto iter = vecGetData.begin(); iter != vecGetData.end(); iter++)
	{
		BFIS::RolePurviewInfo msg;
		bool bSuccess = msg.ParseFromString(*iter);
		if (!bSuccess)
		{
			DISPLAY_LOG("ǿ��ͬ��", "�����·��Ľ�ɫȨ����Ϣ", "���л�ʧ��", "", 0);
			return -1;
		}
		ST_RolePurviewInfo stRolePurviewInfo(msg);
		auto var = roleMap.find(stRolePurviewInfo.strRoleId);
		if (var == roleMap.end())
		{
			roleMap.insert(stRolePurviewInfo.strRoleId);
			if (m_pCache)
			{
				m_pCache->QueryRolePurviewInfoByRoleId(stRolePurviewInfo.strRoleId, vecCurrInfo);
			}
		}
		vecRolePurviewInfoParse.push_back(std::move(stRolePurviewInfo));
	}

	for each(auto itor in vecRolePurviewInfoParse)
	{
		ST_RoleInfo strHaveRoleInfo;
		if (m_pCache && !m_pCache->QueryRoleInfoById(itor.strRoleId, strHaveRoleInfo))
		{
			itor.strRoleId = strRoleInfoId;
		}

		bool bSucess = false;
		for (auto var = vecCurrInfo.begin(); var != vecCurrInfo.end(); ++var)
		{
			if (itor.strRoleInfoPurviewId == var->strRoleInfoPurviewId)
			{
				int bRet = m_pCache->ManageRolePurviewInfo(DBO_UPDATE, itor);
				TTRACE(_T("%s[%d]:���½�ɫȨ����Ϣ%s����ɫȨ��ID��%s\r\n"), __FUNCTION__, __LINE__, !bRet ? _T("ʧ��") : _T("�ɹ�")
					, itor.strRoleInfoPurviewId.c_str());
				vecCurrInfo.erase(var);
				bSucess = true;
				break;
			}
		}

		if (false == bSucess)
		{
			int bRet = m_pCache->ManageRolePurviewInfo(DBO_ADD, itor);
			TTRACE(_T("%s[%d]:��ӽ�ɫȨ����Ϣ%s����ɫȨ��ID��%s\r\n"), __FUNCTION__, __LINE__, !bRet ? _T("ʧ��") : _T("�ɹ�")
				, itor.strRoleInfoPurviewId.c_str());
		}
	}

	for each (auto var in vecCurrInfo)
	{
		if (m_pCache)
		{
			m_pCache->ManageRolePurviewInfo(DBO_DEL, var);
		}
	}

	DISPLAY_LOG("ͬ������", "���¼���ɫȨ����Ϣͬ�����...", "", "", 1);
	return 1;
	SCATCH;
	return -1;
}
#if 0
int XhBFISSyncClientRouterImp::HandleIssuedPurviewInfo(vector<std::string>& vecInfos , DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	vector<std::string> vecGetData = vecInfos;
	vecInfos.clear();
	for (auto iter = vecGetData.begin(); iter != vecGetData.end(); iter++)
	{
		BFIS::PurviewInfo msg;
		bool bSuccess = msg.ParseFromString(*iter);
		if (!bSuccess)
		{
			DISPLAY_LOG("ǿ��ͬ��","�����·���Ȩ����Ϣ","���л�ʧ��","",0);
			return -1;
		}
		ST_PurviewInfo stPurviewInfo(msg);
		//
		QueryResultType enResult = m_pDbOper->ManagePurviewInfo(DBO_QUERY, stPurviewInfo);
		QueryResultType enOperaor = QueryFail;
		switch(enResult)
		{
		case QuerySuccessWithResult:
			{
				enOperaor = m_pDbOper->ManagePurviewInfo(DBO_UPDATE, stPurviewInfo);
				TTRACE(_T("%s[%d]:����Ȩ����Ϣ%s��Ȩ��ID��%s\r\n"),__FUNCTION__,__LINE__, enOperaor == QueryFail?_T("ʧ��"):_T("�ɹ�")
					, stPurviewInfo.strPurviewInfoId.c_str());
				char szBuf[1024] = {0};
				sprintf(szBuf,"����Ȩ����Ϣ%s,Ȩ��ID:%s",enOperaor == QueryFail?_T("ʧ��"):_T("�ɹ�"),stPurviewInfo.strPurviewInfoId.c_str());
				DISPLAY_LOG("ͬ������",szBuf,"","",enOperaor == QueryFail?0:1);
				break;
			}
		case QuerySuccessWithoutResult:
			{
				enOperaor = m_pDbOper->ManagePurviewInfo(DBO_ADD, stPurviewInfo);
				TTRACE(_T("%s[%d]:���Ȩ����Ϣ%s��Ȩ��ID��%s\r\n"),__FUNCTION__,__LINE__, enOperaor == QueryFail?_T("ʧ��"):_T("�ɹ�")
					, stPurviewInfo.strPurviewInfoId);
				char szBuf[1024] = {0};
				sprintf(szBuf,"���Ȩ����Ϣ%s,Ȩ��ID:%s",enOperaor == QueryFail?_T("ʧ��"):_T("�ɹ�"),stPurviewInfo.strPurviewInfoId.c_str());
				DISPLAY_LOG("ͬ������",szBuf,"","",enOperaor == QueryFail?0:1);
				break;
			}
		default:
			{
				DISPLAY_LOG("ͬ������", "����Ȩ����Ϣ","��ѯ���ݿ�ʧ��","",0);
				return -1;
				break;
			}
		}
		if (enOperaor != QueryFail)
		{
			std::string strInfo;
			if(stPurviewInfo.ConvertToString(strInfo))
			{
				vecInfos.push_back(strInfo);
			}
		}
	}
	return 1;
	SCATCH;
	return -1;
}
#endif

int XhBFISSyncClientRouterImp::HandleIssuedClientInfo(const vector<std::string>& vecGetData , DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	//vector<std::string> vecGetData = vecInfos;
	//vecInfos.clear();
	DISPLAY_LOG("ͬ������", "���¼��ͻ���Ϣͬ����ʼ...", "", "", 1);
	for (auto iter = vecGetData.begin(); iter != vecGetData.end(); iter++)
	{
		BFIS::ClientInfo msg;
		bool bSuccess = msg.ParseFromString(*iter);
		if (!bSuccess)
		{
			DISPLAY_LOG("ǿ��ͬ��","�����·��Ŀͻ���Ϣ","���л�ʧ��","",0);
			return -1;
		}
		ST_ClientInfo stClientInfo(msg),stInfo;
		BOOL bRet = FALSE;
		std::string strClientKey = stClientInfo.strClientId + stClientInfo.strCredenitial;
		if (m_pCache && (bRet = m_pCache->QueryClientInfoByCredenitial(strClientKey,stInfo)))
		{
			if (bRet)
			{
				bRet = m_pCache->ManageClientInfo(DBO_UPDATE, stClientInfo);
				TTRACE(_T("%s[%d]:���¿ͻ���Ϣ%s���ͻ�ID��%s\r\n"),__FUNCTION__,__LINE__, !bRet?_T("ʧ��"):_T("�ɹ�")
					, stClientInfo.strClientId.c_str());
				//char szBuf[1024] = {0};
				//sprintf(szBuf,"���¿ͻ���Ϣ%s,�ͻ�ID:%s",!bRet?_T("ʧ��"):_T("�ɹ�"),stClientInfo.strClientId.c_str());
				//DISPLAY_LOG("ͬ������",szBuf,"","",!bRet?0:1);
			}
			else
			{
				bRet = m_pCache->ManageClientInfo(DBO_ADD, stClientInfo);
				TTRACE(_T("%s[%d]:��ӿͻ���Ϣ%s���ͻ�ID��%s\r\n"),__FUNCTION__,__LINE__, !bRet?_T("ʧ��"):_T("�ɹ�")
					, stClientInfo.strClientId.c_str());
				//char szBuf[1024] = {0};
				//sprintf(szBuf,"��ӿͻ���Ϣ%s,�ͻ�ID:%s",!bRet?_T("ʧ��"):_T("�ɹ�"),stClientInfo.strClientId.c_str());
				//DISPLAY_LOG("ͬ������",szBuf,"","",!bRet?0:1);
			}
		}
		/*if (bRet)
		{
			std::string strInfo;
			if(stClientInfo.ConvertToString(strInfo))
			{
				vecInfos.push_back(strInfo);
			}
		}*/
	}
	DISPLAY_LOG("ͬ������", "���¼��ͻ���Ϣͬ�����...", "", "", 1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::IssuedBranchInfo()
{
    if (m_vecIssuedBranchInfo.size() > 0)
    {
        
    }
}
void XhBFISSyncClientRouterImp::ConnectCheckTh()
{
	STRY;
	boost::unique_lock<boost::mutex> lock(m_cheackConnectMutex);
	m_cheackConnectCondition.wait_for(lock, boost::chrono::seconds(20));
	SCATCH;

	bool bIsReconnect = true;   //��һ�ν���  ����Ϊtrue
	STRY;
	while (false == m_bIsStopReconnectThread)
	{
		STRY;
		boost::unique_lock<boost::mutex> lock(m_cheackConnectMutex);
		if (m_bNeedReConnect)
			m_cheackConnectCondition.wait_for(lock, boost::chrono::seconds(10));
		else
			m_cheackConnectCondition.wait_for(lock, boost::chrono::seconds(30));
		SCATCH;

		STRY;
		bool bSucess = false;
		for (int i = 0; i < RECONNECTION_COUNT; ++i)
		{
			STRY;
			Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
			if (m_hServerContext == nullptr)
				continue;
			iBFIS_CommunicationInvoker invoke(m_hServerContext);
			DWORD_PTR dwCmd = MSG_IS_ALIVE;
			int nRet = -1;
			nRet = invoke.Invoke(dwCmd);
			if (nRet > 0)
			{
				bSucess = true;
				break;
			}
			else
			{
				TTRACE(" ���¼�������Ϣ����ʧ��[%d]\r\n", nRet);
			}
			SCATCH;
			Sleep(2 * 1000);
		}

		if (bSucess)
		{
			continue;
		}
				
		SCATCH;

		if (m_hServerContext)
		{
			DISPLAY_LOG(_T("ͬ������"), _T("���ϼ�����������ʧЧ"), _T(""), _T(""), 0);
		}
		

		STRY;
		Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
		m_bNeedReConnect = TRUE;
		m_hServerContext = nullptr;
		SCATCH;
		bIsReconnect = true;

		if (ReConnect2Server())
		{
			STRY;
			boost::unique_lock<boost::mutex> lock(m_cheackConnectMutex);
			m_cheackConnectCondition.wait_for(lock, boost::chrono::seconds(20));
			SCATCH;
		}
	}
	SCATCH;
}
int XhBFISSyncClientRouterImp::HandleIssuedBranchInfo(const vector<std::string>& vecInfos , DWORD_PTR dwReserved )
{
    STRY;  
    //vector<std::string> vecGetData = vecInfos;
    vector<std::string> vecRemainData;
    vector<ST_BranchInfo> vecBranchInfo;
    //vecInfos.clear();
    ST_BranchInfo stInfo;
    m_pCache->GetLocalBranchInfo(stInfo); 
	DISPLAY_LOG("ͬ������","���¼�������Ϣͬ����ʼ...","","",1);
    for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter++)
    {
        BFIS::BranchInfo msg;
        bool bSuccess = msg.ParseFromString(*iter);
        if (!bSuccess)
        {
            DISPLAY_LOG("ǿ��ͬ��","�����·��������Ϣ","���л�ʧ��","",0);
            return -1;
        }
        ST_BranchInfo stBranchInfo(msg);      
        BOOL bRet = FALSE;          
        if(stBranchInfo.strJDBRID == stInfo.strJDBRID)
        {
            stInfo.strName = stBranchInfo.strName;
            stInfo.strAddress = stBranchInfo.strAddress;
            stInfo.strParentJDBRID = stBranchInfo.strParentJDBRID;
            stInfo.strParentName = stBranchInfo.strParentName;
            stInfo.strJDTYPE = stBranchInfo.strJDTYPE;
            bRet = m_pCache->ManageBranchInfo(DBO_UPDATE, stInfo);
        }
        else
        {
            vecBranchInfo.push_back(stBranchInfo);
            vecRemainData.push_back(*iter);
        }
    }
	DISPLAY_LOG("ͬ������","���¼�������Ϣͬ�����","","",1);
    if (m_pComm)
    {
        vector<ST_EmployeeInfo> vecEmployeeInfo;
        m_pComm->SetOfflineSyscData(vecBranchInfo,vecEmployeeInfo);
        //m_pComm->AddNotifyMsg(DBO_UPDATE,MSG_ISSUED_BRANCHINFO,vecRemainData);
    }
    return 1;
    SCATCH;
    return -1;
}
int XhBFISSyncClientRouterImp::HandleIssuedEmployeeInfo(const vector<std::string>& vecGetData , DWORD_PTR dwReserved )
{
    STRY;  
    //vector<std::string> vecGetData = vecInfos;
    vector<std::string> vecRemainData;
    vector<ST_EmployeeInfo> vecEmployeeInfo;
	vector<ST_RoleInfo> vecQueryRoleInfo;
	vector<ST_EmployeeInfo> vecQueryEmployee;
    ST_RoleInfo stRoleInfo;
	ST_RoleInfo stSuperRoleInfo;
    // vecInfos.clear();
    ST_BranchInfo stInfo;
	if (m_pCache)
	{
		m_pCache->GetLocalBranchInfo(stInfo);
		m_pCache->QueryRoleInfo(vecQueryRoleInfo);
		m_pCache->QueryEmployeeInfo(vecQueryEmployee);
	}	 
	if (!vecQueryRoleInfo.empty())
    {
        int pos = 0;
        for (vecQueryRoleInfo[pos]; pos<vecQueryRoleInfo.size(); pos++)
        {
            if (vecQueryRoleInfo[pos].nExtendedInfo == -2 && vecQueryRoleInfo[pos].strBranchInfoId == stInfo.strBranchId)
            {
                stRoleInfo = vecQueryRoleInfo[pos];
            }
			if (vecQueryRoleInfo[pos].nExtendedInfo == 0 && vecQueryRoleInfo[pos].strBranchInfoId == stInfo.strBranchId)
			{
				stSuperRoleInfo = vecQueryRoleInfo[pos];
			}
        }
    }
	DISPLAY_LOG("ͬ������", "���¼�Ա����Ϣͬ����ʼ...", "", "", 1);
	TTRACE(" ���¼�Ա����Ϣͬ�� size[%d] size[%d] \r\n", vecQueryEmployee.size(), vecGetData.size());
	bool    b_loginSync = true;
	for (auto iter = vecGetData.begin(); iter != vecGetData.end(); iter++)
	{
		BFIS::EmployeeInfo msg;
		bool bSuccess = msg.ParseFromString(*iter);
		if (!bSuccess)
		{
			DISPLAY_LOG("ǿ��ͬ��","�����·���Ա����Ϣ","���л�ʧ��","",0);
			return -1;
		}
		ST_EmployeeInfo stEmployeeInfo(msg);
		//TTRACE(" ���¼�Ա����Ϣͬ��strBranchId[%s] [%s] nExtendedInfo[%d] \r\n", stEmployeeInfo.strBranchId.c_str(), stInfo.strBranchId.c_str(), stEmployeeInfo.nExtendedInfo);
		
		if (stEmployeeInfo.strBranchId == stInfo.strBranchId &&
			stEmployeeInfo.strRoleId != stSuperRoleInfo.strRoleInfoId)
		{
			if (stEmployeeInfo.nExtendedInfo != 1)
				b_loginSync = false;

			int nSize = vecQueryEmployee.size();
			bool bFindUseEmp = false;
			for (auto var = vecQueryEmployee.begin();  var != vecQueryEmployee.end(); ++var)
			{
				if (stEmployeeInfo.strTLNUM == var->strTLNUM)
				{
					//TTRACE(" ���¼�Ա����Ϣͬ�� Name[%s] strTLNUM[%s]\r\n", stEmployeeInfo.strName.c_str(), stEmployeeInfo.strTLNUM.c_str());
					var->strGW = stEmployeeInfo.strGW;
					var->strSTS = stEmployeeInfo.strSTS;
					var->strUSERNAME = stEmployeeInfo.strUSERNAME;
					var->strTLINST = stEmployeeInfo.strTLINST;
					var->strROLENAME = stEmployeeInfo.strROLENAME;
					var->strUSERSTATUS = stEmployeeInfo.strUSERSTATUS;
					var->strCardId = stEmployeeInfo.strCardId;
					var->nFlag = stEmployeeInfo.nFlag;
					if (!stEmployeeInfo.strTEL.empty())
					{
						var->strTEL = stEmployeeInfo.strTEL;
					}
					int nRet = m_pCache->ManageEmployeeInfo(DBO_UPDATE, *var);
					if (nRet > 0)
					{
						m_pCache->ManageEmployeeInfoAndSocUser(DBO_UPDATE, *var);
					}
					bFindUseEmp = true;
					vecQueryEmployee.erase(var);
					break;
				}
			}

			if (false == bFindUseEmp)
			{
				CString strTemp = _T("");
				GuidProducer(strTemp);
				stEmployeeInfo.strBranchId = stInfo.strBranchId;
				stEmployeeInfo.strEmployeeId = strTemp;
				stEmployeeInfo.strRoleId = stRoleInfo.strRoleInfoId;
				int nRet = m_pCache->ManageEmployeeInfo(DBO_ADD, stEmployeeInfo);
				if (nRet > 0)
				{
					m_pCache->ManageEmployeeInfoAndSocUser(DBO_ADD, stEmployeeInfo);
				}
			}
		}
		else
		{
			if (stEmployeeInfo.strJDBRID != stInfo.strJDBRID)
			{
				vecEmployeeInfo.push_back(stEmployeeInfo);
				vecRemainData.push_back(*iter);
			}
		}
	}

	if (false == b_loginSync)
	{
		//TTRACE(" ���¼�Ա����Ϣͬ�� [%d]\r\n", vecQueryEmployee.size());
		for (auto var = vecQueryEmployee.begin(); var != vecQueryEmployee.end(); ++var)
		{
			if (var->nExtendedInfo != 1 && var->strRoleId != stSuperRoleInfo.strRoleInfoId)
			{
				var->nFlag = 1;
				m_pCache->ManageEmployeeInfo(DBO_UPDATE, *var);
				//TTRACE(" ���¼�Ա����Ϣͬ�� ͣ���û� [%s]\r\n", var->strName.c_str());
			}
		}
	}

	DISPLAY_LOG("ͬ������","���¼�Ա����Ϣͬ�����","","",1);
    if (m_pComm && vecEmployeeInfo.size() > 0)
    {
        vector<ST_BranchInfo> vecBranchInfo;
        m_pComm->SetOfflineSyscData(vecBranchInfo,vecEmployeeInfo);
        //m_pComm->AddNotifyMsg(DBO_UPDATE,MSG_ISSUED_EMPLOYEEINFO,vecRemainData);
    }
    return 1;
    SCATCH;
    return -1;
}

int XhBFISSyncClientRouterImp::HandleIssuedMigrateTasknfo(const vector<std::string>& vecInfos , DWORD_PTR dwReserved)
{
	STRY;
	ST_TaskPlan stTaskPlan;
	vector<ST_TaskPlan> vecTaskPlan;
	m_pCache->ManageTaskPlanInfo(DBO_DEL,vecTaskPlan);
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter++)
	{
		BFIS::TaskPlan msg;
		bool bSuccess = msg.ParseFromString(*iter);
		if (!bSuccess)
		{
			DISPLAY_LOG("ǿ��ͬ��","�����·��ı���������Ϣ","���л�ʧ��","",0);
			return -1;
		}
		ST_TaskPlan stTaskPlan(msg);
		vecTaskPlan.push_back(stTaskPlan);		
		m_pCache->ManageTaskPlanInfo(DBO_ADD,vecTaskPlan);
		vecTaskPlan.clear();
	}
	return 1;
	SCATCH;
	return -1;
}
void XhBFISSyncClientRouterImp::SaveBackupData()
{
	STRY;
	FILE* pFile = fopen("d:\\a.data","wb");
	if (!pFile)
	{
		TTRACE("д�뱾���ļ�ʧ�ܣ�û�н������ݱ���");
		return;
	}
	char ch;
	for (int i = 0 ; i < m_vecBackupClient.size() ; i ++)
	{
		ch = fputc(DataType_ClientInfo,pFile);
		int nSize = 0;
		m_vecBackupClient[i].ConvertToArrary(NULL,&nSize);
		fwrite(&nSize,sizeof(int),1,pFile);
		char* pBuf = new char[nSize];
		m_vecBackupClient[i].ConvertToArrary(pBuf,&nSize);
		fwrite(pBuf,nSize,1,pFile);
		delete pBuf;
	}
	for (int i = 0 ; i < m_vecBackupProduce.size() ; i ++)
	{
		ch = fputc(DataType_ProduceInfo,pFile);
		int nSize = 0;
		m_vecBackupProduce[i].ConvertToArrary(NULL,&nSize);
		fwrite(&nSize,sizeof(int),1,pFile);
		char*pBuf = new char[nSize];
		m_vecBackupProduce[i].ConvertToArrary(pBuf,&nSize);
		//fwrite(&m_vecBackupProduce[i],sizeof(ST_ProduceInfo),1,pFile);
		fwrite(pBuf,nSize,1,pFile);
		delete pBuf;
	}
#if 0
	for (int i = 0 ; i < m_vecBackupPurview.size() ; i ++)
	{
		ch = fputc(DataType_PurviewInfo,pFile);
		int nSize = 0;
		m_vecBackupPurview[i].ConvertToArrary(NULL,&nSize);
		fwrite(&nSize,sizeof(int),1,pFile);
		char* pBuf = new char[nSize];
		m_vecBackupPurview[i].ConvertToArrary(pBuf,&nSize);
		fwrite(pBuf,nSize,1,pFile);
		delete pBuf;
	}
#endif
	for (int i = 0 ; i < m_vecBackupRole.size() ; i ++)
	{
		ch = fputc(DataType_RoleInfo,pFile);
		int nSize = 0;
		m_vecBackupRole[i].ConvertToArrary(NULL,&nSize);
		fwrite(&nSize,sizeof(int),1,pFile);
		char* pBuf = new char[nSize];
		m_vecBackupRole[i].ConvertToArrary(pBuf,&nSize);
		fwrite(pBuf,nSize,1,pFile);
		delete pBuf;
	}
	for (int i = 0 ; i < m_vecBackupRolePurview.size() ; i ++)
	{
		ch = fputc(DataType_RolePurviewInfo,pFile);
		int nSize = 0;
		m_vecBackupRolePurview[i].ConvertToArrary(NULL,&nSize);
		fwrite(&nSize,sizeof(int),1,pFile);
		char* pBuf = new char[nSize];
		m_vecBackupRolePurview[i].ConvertToArrary(pBuf,&nSize);
		fwrite(pBuf,nSize,1,pFile);
		delete pBuf;
	}
	fclose(pFile);
	SCATCH;
}

void XhBFISSyncClientRouterImp::LoadBackupData()
{
	STRY;
	m_vecBackupClient.clear();
	m_vecBackupProduce.clear();
	m_vecBackupPurview.clear();
	m_vecBackupRole.clear();
	m_vecBackupRolePurview.clear();
	//
	FILE* pFile = fopen("d:\\a.data","rb");
	if (!pFile)
	{
		TTRACE("��ȡ�����ļ�ʧ�ܣ�û�н������ݱ���");
		return;
	}
	char ch;
	while(!feof(pFile))
	{
		char* pBuf = NULL;
		int nSize = 0;
		ch = fgetc(pFile);
		switch((int)ch)
		{
		case DataType_ClientInfo:
			{
				fread(&nSize,sizeof(int),1,pFile);
				pBuf = new char[nSize];
				fread(pBuf,nSize,1,pFile);
				BFIS::ClientInfo msg;
				msg.ParseFromArray(pBuf,nSize);
				ST_ClientInfo stInfo(msg);
				m_vecBackupClient.push_back(stInfo);
			}
			break;
		case DataType_ProduceInfo:
			{
				fread(&nSize,sizeof(int),1,pFile);
				pBuf= new char[nSize];
				fread(pBuf,nSize,1,pFile);
				BFIS::ProduceInfo msg;
				msg.ParseFromArray(pBuf,nSize);
				ST_ProduceInfo stInfo(msg);
				m_vecBackupProduce.push_back(stInfo);
			}
			break;
#if 0
		case DataType_PurviewInfo:
			{
				fread(&nSize,sizeof(int),1,pFile);
				pBuf= new char[nSize];
				fread(pBuf,nSize,1,pFile);
				BFIS::PurviewInfo msg;
				msg.ParseFromArray(pBuf,nSize);
				ST_PurviewInfo stInfo(msg);
				m_vecBackupPurview.push_back(stInfo);
			}
			break;
#endif
		case DataType_RoleInfo:
			{
				fread(&nSize,sizeof(int),1,pFile);
				pBuf= new char[nSize];
				fread(pBuf,nSize,1,pFile);
				BFIS::RoleInfo msg;
				msg.ParseFromArray(pBuf,nSize);
				ST_RoleInfo stInfo(msg);
				m_vecBackupRole.push_back(stInfo);
			}
			break;
		case DataType_RolePurviewInfo:
			{
				fread(&nSize,sizeof(int),1,pFile);
				pBuf= new char[nSize];
				fread(pBuf,nSize,1,pFile);
				BFIS::RolePurviewInfo msg;
				msg.ParseFromArray(pBuf,nSize);
				ST_RolePurviewInfo stInfo(msg);
				m_vecBackupRolePurview.push_back(stInfo);
			}
			break;
		}
		delete pBuf;
	}
	fclose(pFile);
	SCATCH;
}

BOOL XhBFISSyncClientRouterImp::StoreRoleInfo(DBOperType& enType,ST_RoleInfo& stRoleInfo)
{
	STRY;
	ST_RoleInfo stInfo;
	BOOL bRet = FALSE;
	if (m_pCache && (bRet = m_pCache->QueryRoleInfoById(stRoleInfo.strRoleInfoId,stInfo)))
	{
		bRet ? enType = DBO_UPDATE : enType = DBO_ADD;
	}
	bRet  = m_pCache->ManageRoleInfo(enType, stRoleInfo);
	char szBuf[255] = {0};
	sprintf(szBuf,"%s�û���%s,�û���ID:%s\r\n", enType == DBO_ADD ? _T("����"):_T("����"),
		!bRet ? _T("ʧ��"):_T("�ɹ�"),stRoleInfo.strRoleInfoId.c_str());
	TTRACE("%s[%s_%d] \r\n",szBuf,__FUNCTION__,__LINE__);
	DISPLAY_LOG("ͬ������",szBuf,"","",!bRet? 0 : 1);
	return (!bRet ? FALSE:TRUE);
	SCATCH;
	return FALSE;
}

BOOL XhBFISSyncClientRouterImp::StoreClientInfo(DBOperType enType,ST_ClientInfo& stClientInfo)
{
	STRY;
	if(!m_pCache)
		return FALSE;
	BOOL bRet;
	ST_ClientInfo stInfo;
	std::string strClientKey = stClientInfo.strClientId + stClientInfo.strCredenitial;
	bRet = m_pCache->QueryClientInfoByCredenitial(strClientKey,stInfo);
	{
		bRet ? enType = DBO_UPDATE : enType = DBO_ADD;
	}
	bRet = m_pCache->ManageClientInfo(enType, stClientInfo);
	char szBuf[255] = {0};
	sprintf(szBuf,"%s�ͻ���Ϣ%s,�ͻ�ID:%s\r\n", enType == DBO_ADD ? _T("����"):_T("����"),
		!bRet?_T("ʧ��"):_T("�ɹ�"),stClientInfo.strClientId.c_str());
	TTRACE("%s[%s_%d] \r\n",szBuf,__FUNCTION__,__LINE__);
	DISPLAY_LOG("ͬ������",szBuf,"","",!bRet ? 0 : 1);
	return bRet;
	SCATCH;
	return FALSE;
}
#if 0
BOOL XhBFISSyncClientRouterImp::StorePurviewInfo(DBOperType& enType,ST_PurviewInfo& stPurviewInfo)
{
	STRY;
	QueryResultType enResult = m_pDbOper->ManagePurviewInfo(DBO_QUERY, stPurviewInfo);
	switch(enResult)
	{
	case QuerySuccessWithResult:
		{
			enType = DBO_UPDATE;
		}
		break;
	case QuerySuccessWithoutResult:
		{
			enType = DBO_ADD;
		}
		break;
	default:
		{
			DISPLAY_LOG("ͬ������", "����Ȩ����Ϣ","��ѯ���ݿ�ʧ��","",0);
			return FALSE;
		}
	}
	QueryResultType enOperaor = m_pDbOper->ManagePurviewInfo(enType, stPurviewInfo);
	char szBuf[255] = {0};
	sprintf(szBuf,_T("%s[%d]:%sȨ����Ϣ%s��Ȩ��ID��%s\r\n"),__FUNCTION__,__LINE__,
		enType == DBO_ADD ? _T("����"):_T("����"),enOperaor == QueryFail ? _T("ʧ��"):_T("�ɹ�"),
		stPurviewInfo.strPurviewInfoId.c_str());
	DISPLAY_LOG("ͬ������",szBuf,"","",enOperaor == QueryFail ? 0 : 1);
	return(enOperaor == QueryFail ? FALSE : TRUE);
	SCATCH;
	return FALSE;
}
#endif
BOOL XhBFISSyncClientRouterImp::StoreProduceInfo(DBOperType enType,ST_ProduceInfo& stProduceInfo)
{
	STRY;
	BOOL bRet = FALSE;
	ST_ProduceInfo stInfo;
	if (m_pCache && (bRet = m_pCache->QueryProduceInfoById(stProduceInfo.strProduceId,stInfo)))
	{
		bRet ? enType = DBO_UPDATE : enType = DBO_ADD;
	}
	bRet = m_pCache->ManageProduceInfo(enType, stProduceInfo);
	char szBuf[1024] = {0};
	sprintf(szBuf,_T("%s��Ʒ��Ϣ%s����ƷID��%s\r\n"),enType == DBO_ADD ? _T("����"):_T("����"), 
		!bRet?_T("ʧ��"):_T("�ɹ�"), stProduceInfo.strProduceId.c_str());
	TTRACE("%s[%s_%d] \r\n",szBuf,__FUNCTION__,__LINE__);
	DISPLAY_LOG("ͬ������",szBuf,"","",!bRet?0:1);
	return bRet;
	SCATCH;
	return FALSE;
}

BOOL XhBFISSyncClientRouterImp::StoreRolePurviewInfo(DBOperType& enType,ST_RolePurviewInfo& stRolePurviewInfo)
{
	STRY;
	BOOL bRet = FALSE;
	ST_RolePurviewInfo stInfo;
	if (m_pCache && (bRet = m_pCache->QueryRolePurviewInfoById(stRolePurviewInfo.strRoleInfoPurviewId,stInfo)))
	{
		bRet ? enType = DBO_UPDATE : enType = DBO_ADD;
	}
	bRet = m_pCache->ManageRolePurviewInfo(enType, stRolePurviewInfo);
	char szBuf[255] = {0};
	sprintf(szBuf,"%s�û���Ȩ����Ϣ%s,�û���Ȩ��ID:%s\r\n",enType == DBO_ADD ? _T("����"):_T("����"),
		!bRet?_T("ʧ��"):_T("�ɹ�"),stRolePurviewInfo.strRoleInfoPurviewId.c_str());
	TTRACE("%s[%s_%d] \r\n",szBuf,__FUNCTION__,__LINE__);
	DISPLAY_LOG("ͬ������",szBuf,"","",!bRet ? 0 : 1);
	return bRet;
	SCATCH;
	return FALSE;
}

int XhBFISSyncClientRouterImp::GetParentSMSInfo(string& strIp, string& strPort, string& strUser, string& strPwd)
{
    
    std::vector<string> vecInfos;
    DWORD_PTR dwCmd = MSG_GET_SMS_LOGININFO;
	int nRet = -1;
	STRY;
	Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
	if (nullptr == m_hServerContext)
	{
		DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
		return -1;
	}
	iBFIS_CommunicationInvoker invoke(m_hServerContext);
    nRet = invoke.Invoke(dwCmd, vecInfos);
	SCATCH;
    if (nRet <= 0)
    {
        return nRet;
    }
    if (vecInfos.size() < 4)
    {
        TTRACE("%s[%d]:��ȡ�ϼ�sms��Ϣʧ��,vec size :%d\r\n", __FUNCTION__, __LINE__, vecInfos.size());
        return -2;
    }
    strIp = vecInfos[0];
    strPort = vecInfos[1];
    strUser = vecInfos[2];
    strPwd = vecInfos[3];
    return 1;
}

bool XhBFISSyncClientRouterImp::GetNeedSyncBranchInfo(vector<ST_BranchInfo>& vecBranchInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
    /*if (NULL != m_pCache && m_pCache->QueryBranchInfoNeed2Sync(vecBranchInfo) > 0)
    {
    return true;
    }*/
    if (NULL != m_pCache && m_pCache->QueryBranchInfo(vecBranchInfo)>0)
    {
        return true;
    }
	return false;
	SCATCH;
	return false;
}

bool XhBFISSyncClientRouterImp::GetNeedSyncRoleInfo(vector<ST_RoleInfo>& vecRoleInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (NULL != m_pCache && m_pCache->QueryRoleInfoNeed2Sync(vecRoleInfo) > 0)
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}

bool XhBFISSyncClientRouterImp::GetNeedSyncRolePurviewInfo(vector<ST_RolePurviewInfo>& vecRolePurviewInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (NULL != m_pCache && m_pCache->QueryRolePurviewInfoNeed2Sync(vecRolePurviewInfo) > 0)
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}

int XhBFISSyncClientRouterImp::GetParentBranchInfo(string& strBranchID, string& strBranchName, string& strParentID)
{
    STRY;
    std::vector<string> vecInfos;
    DWORD_PTR dwCmd = MSG_GET_PARENT_BRANCHINFO;
	int nRet = -1;
	STRY;
	Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
	if (nullptr == m_hServerContext)
	{
		DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
		return -1;
	}
	iBFIS_CommunicationInvoker invoke(m_hServerContext);
    nRet = invoke.Invoke(dwCmd, vecInfos);
	SCATCH;
    if (nRet <= 0)
    {
        return nRet;
    }
    if (vecInfos.size() < 3)
    {
        TTRACE("%s[%d]:��ȡ�ϼ�������Ϣʧ��,vec size :%d\r\n", __FUNCTION__, __LINE__, vecInfos.size());
        return -2;
    }
    strBranchID = vecInfos[0];
    strBranchName = vecInfos[1];
    strParentID = vecInfos[2];
    return 1;
    SCATCH;
    return -1;
}

int XhBFISSyncClientRouterImp::DoNotifyData(IN DWORD_PTR d1,IN DWORD_PTR d2, IN string s, IN DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
	if (nullptr == m_hServerContext)
	{
		DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
		return -1;
	}
	iBFIS_CommunicationInvoker invoke(m_hServerContext);
	return invoke.Invoke(d1,d2,s);
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::DoNotifyData(std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2, IN DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
	if (nullptr == m_hServerContext)
	{
		DISPLAY_LOG(_T("ͬ������"),_T("�������Ͽ���δ���ӳɹ�"), _T(""), _T(""), 0); 
		return -1;
	}
	iBFIS_CommunicationInvoker invoke(m_hServerContext);
	return invoke.Invoke(v1,v2);
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::ClientInfoNotify(int nType,ST_ClientInfo& stInfo)
{
	STRY;
	char szTemp[255] = {0};
	if (m_pCache && m_pCache->ManageClientInfo((DBOperType)nType,stInfo) != QueryFail)
	{
		sprintf(szTemp,"[����֪ͨ]���¿ͻ���ϢName:%s[ClientId:%s]",stInfo.strName.c_str(),stInfo.strClientId.c_str());
		DISPLAY_LOG("ͬ��",szTemp,"�ɹ�","",1);
		return 1;
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::ProduceInfoNotify(int nType,ST_ProduceInfo& stInfo)
{
	STRY;
	char szTemp[255] = {0};
	if (m_pCache && m_pCache->ManageProduceInfo((DBOperType)nType,stInfo) != QueryFail)
	{
		sprintf(szTemp,"[����֪ͨ]���²�Ʒ��ϢName:%s[ProduceId:%s]",stInfo.strName.c_str(),stInfo.strProduceId.c_str());
		DISPLAY_LOG("ͬ��",szTemp,"�ɹ�","",1);
		return 1;
	}
	return -1;
	SCATCH;
	return -1;
}

void XhBFISSyncClientRouterImp::ReadOutgoingDeviceXml()
{
	CString strFMSConfigPath = GetWorkingDirectory();
	strFMSConfigPath += "\\Config\\OutgoingDevice.xml";
	iCMSP_XmlParser xmlParser;
	const bool b_ret = xmlParser.Load(strFMSConfigPath);
	if (true == b_ret)
	{
		TTRACE(" �ɹ����ز�������ļ�\r\n");
		if (xmlParser.FindElem("FMS"))
		{
			xmlParser.IntoElem();
			if (xmlParser.FindElem("OutgoingDevice"))
			{
				int nEnable = xmlParser.GetAttribInt("enable");
				if (nEnable > 0)
				{
					m_outgoingDevice = std::make_shared<XhBFISOutgoingDeviceSyncClient>(this);
					CString ip = xmlParser.GetAttrib("ip");
					int port = xmlParser.GetAttribInt("port");
					int timeInterval = xmlParser.GetAttribInt("timeInterval");
					int syncFrequency = xmlParser.GetAttribInt("syncFrequency");
					int lastSyncTime = xmlParser.GetAttribInt("lastSyncTime");
					int waitFinishTime = xmlParser.GetAttribInt("waitFinishTime");
					std::string strTime = boost::gregorian::to_iso_string(boost::gregorian::day_clock::local_day());
					int currTime = boost::lexical_cast<int>(strTime);
					int time = (currTime - lastSyncTime) - syncFrequency;
					char szMeg[50] = { 0 };
					sprintf(szMeg, "ͬ��ʱ��[%d]", time);
					DISPLAY_LOG("����豸ͬ��", szMeg, "", "", 1);
					if (m_outgoingDevice && time >= 0)
					{
						m_outgoingDevice->Init(ip.GetBuffer(0), port, timeInterval, waitFinishTime);
						m_outgoingDevice->StartSync();
					}
				}
			}
		}
	}
}

ISOC_VOID XhBFISSyncClientRouterImp::OnTimer(IN ISOC_ID iTimerID)
{
	STRY;
	Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
	if (iTimerID == KEEP_ALIVE && m_hServerContext != NULL)
	{
		iBFIS_CommunicationInvoker invoke(m_hServerContext);
		DWORD_PTR dwCmd = MSG_IS_ALIVE;
		int nRet = -1;
		for (int i = 0; i < RECONNECTION_COUNT; ++i)
		{
			nRet = invoke.Invoke(dwCmd);
			if (nRet > 0)
				return;
		}
	}
	SCATCH;

	if (iTimerID == KEEP_ALIVE)
	{
		DISPLAY_LOG(_T("ͬ������"), _T("���ϼ�����������ʧЧ���Ͽ�����..."), _T(""), _T(""), 1);
		STRY;
		Poco::FastMutex::ScopedLock lock(m_csLockConnectServer);
		m_bNeedReConnect = TRUE;
		m_hServerContext = nullptr;
		SCATCH;
		m_pTimer->KillTimer(KEEP_ALIVE);
		ReConnect2Server();
	}
}

void XhBFISSyncClientRouterImp::GuidProducer(CString& strGuid)
{
    STRY;
    GUID gGuid;
    if (S_OK == ::CoCreateGuid(&gGuid))
    {
        strGuid.Format("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",gGuid.Data1,gGuid.Data2,gGuid.Data3,gGuid.Data4[0],
            gGuid.Data4[1],gGuid.Data4[2],gGuid.Data4[3],gGuid.Data4[4],gGuid.Data4[5],gGuid.Data4[6],gGuid.Data4[7]);
    }
    SCATCH;
}
int XhBFISSyncClientRouterImp::HandleIssuedScriptInfo(const vector<std::string>& vecGetData , DWORD_PTR dwReserved)
{
	STRY;
	vector<ST_ScriptInfo> vecScriptInfoByAche;
	if (m_pCache)
		m_pCache->QueryScriptInfoByCache(vecScriptInfoByAche);

	DISPLAY_LOG("ͬ������", "���¼�������Ϣͬ����ʼ...", "", "", 1);
	for (auto iter = vecGetData.begin(); iter != vecGetData.end(); iter++)
	{
		BFIS::ScriptInfo msg;
		bool bSuccess = msg.ParseFromString(*iter);
		if (!bSuccess)
		{
			DISPLAY_LOG("ǿ��ͬ��","�����·�������Ϣ","���л�ʧ��","",0);
			return -1;
		}

		ST_ScriptInfo stScriptInfo(msg);
		BOOL bIsHave = FALSE;
		for (auto iter = vecScriptInfoByAche.begin(); iter != vecScriptInfoByAche.end(); iter++)
		{
			if (iter->strScriptId == stScriptInfo.strScriptId)
			{
				if (!(stScriptInfo == *iter))
				{
					if (m_pCache)
						m_pCache->ManageScriptInfo(DBO_UPDATE, *iter);
				}
				bIsHave = TRUE;
				vecScriptInfoByAche.erase(iter);
				break;
			}
		}
		if (bIsHave == FALSE && m_pCache)
		{
			m_pCache->ManageScriptInfo(DBO_ADD, stScriptInfo);
		}
	}

	for (auto var = vecScriptInfoByAche.begin(); var != vecScriptInfoByAche.end(); ++var)
	{
		if (m_pCache)
			m_pCache->ManageScriptInfo(DBO_DEL, *var);
	}
	DISPLAY_LOG("ͬ������", "���¼�������Ϣͬ�����...", "", "", 1);
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncClientRouterImp::HandleIssuedEmployeePurviewInfo(const vector<std::string>& vecInfos, DWORD_PTR dwReserved)
{
	STRY;
	vector<ST_EmployeePurviewInfo> vecEmployeePurviewInfo;
	if (m_pCache)
		m_pCache->QueryEmployeePurviewInfo(vecEmployeePurviewInfo);

	DISPLAY_LOG("ͬ������", "����ͬ��Ա��Ȩ����Ϣ��ʼ", "", "", 1);
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter++)
	{
		BFIS::EmployeePurviewInfo msg;
		bool bSuccess = msg.ParseFromString(*iter);
		if (!bSuccess)
		{
			DISPLAY_LOG("ǿ��ͬ��", "Ա��Ȩ����Ϣ", "���л�ʧ��", "", 0);
			return -1;
		}

		ST_EmployeePurviewInfo stEmployeePurviewId(msg);
		BOOL bIsHave = FALSE;
		for (auto var = vecEmployeePurviewInfo.begin(); var != vecEmployeePurviewInfo.end(); ++var)
		{
			if (stEmployeePurviewId.strEmployeePurviewId == var->strEmployeePurviewId)
			{
				if (!(stEmployeePurviewId == *var))
				{
					if (m_pCache)
						m_pCache->ManageEmployeePurviewInfo(DBO_UPDATE, *var);
				}
				bIsHave = TRUE;
				vecEmployeePurviewInfo.erase(var);
				break;
			}
		}
		if (bIsHave == FALSE && m_pCache)
		{
			m_pCache->ManageEmployeePurviewInfo(DBO_ADD, stEmployeePurviewId);
		}
	}

	for (auto var = vecEmployeePurviewInfo.begin(); var != vecEmployeePurviewInfo.end(); ++var)
	{
		if (m_pCache)
			m_pCache->ManageEmployeePurviewInfo(DBO_DEL, *var);
	}
	DISPLAY_LOG("ͬ������", "����ͬ��Ա��Ȩ����Ϣ���", "", "", 1);
	return 1;
	SCATCH;
	return -1;
}
