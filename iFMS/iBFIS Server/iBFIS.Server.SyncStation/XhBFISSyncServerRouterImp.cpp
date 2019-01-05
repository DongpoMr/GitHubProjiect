#include "StdAfx.h"
#include "XhBFISSyncServerRouterImp.h"
#include "iBFIS_Communication.h"
#include "iBFIS_UniqueDefine.h"
#include "IcmsP_Utility.h"
#include "BFIS.ProtoMessageDefine.pb.h"
#include "iSOC_MonFactoryManagement.h"
#include "XhLogDisplayInterface.h"
#include "iFVR_Configuration.h"
#include "iBFIS_DataType_Define.h"
#include <afxinet.h>
#define MODULE_NAME "[�����ģ��]"
#include <windows.h>
#include "shlwapi.h"
#include <iostream>
#include "WinBase.h"
#include <fstream>
#include "IcmsP_XmlParser.h"
#include <direct.h> 
#include "ICallbackManagement.h"
#include "xhObjectRefCount.cpp"
#include <set>
#include <cstdio>

#define  CHECK_CONNECT_DEL(x) \
	if (x.isDel())\
	{\
		return 1;\
	}\
		

class XhAutoSetBusy
{
public:
    XhAutoSetBusy(BOOL& busy);
    ~XhAutoSetBusy();

private:
    BOOL& _bBusy;
};

XhAutoSetBusy::XhAutoSetBusy(BOOL& busy) :_bBusy(busy)
{
    _bBusy = TRUE;
}

XhAutoSetBusy::~XhAutoSetBusy()
{
    _bBusy = FALSE;
}
int	HexToByte(std::string str, BYTE *Buff)
{
	if (Buff == NULL)
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
XhBFISSyncServerRouterImp::XhBFISSyncServerRouterImp(void) : m_bNeedStop(FALSE),m_bNeedReConnect(FALSE),
	m_pListctrl(NULL),m_bBusy(FALSE),m_strLocalBranchId(""),m_mapClientCount(0),m_bManualSync(FALSE), m_bSyncSubServer(true)
{
	STRY;
	iSOC_MonFactoryManagement fmt;
	m_pCache = (IBFISDataProvider*)fmt.CreateObject(OBJECT_TYPE_BFISSERVER_CACHESOURCE,"",__FUNCTION__);
    if (m_pCache && m_pCache->QueryLocalBranchId(m_strLocalBranchId))
    {
        m_pCache->QueryBranchInfoById(m_strLocalBranchId,m_stBranchInfo);
    }
	m_syncSubServerThread = std::make_shared<boost::thread>(boost::bind(&XhBFISSyncServerRouterImp::SyncSubServerWork, this));
    DISPLAY_LOG("ͬ������", "���������������", m_pCache == NULL ? "ʧ��" : "�ɹ�", "", m_pCache == NULL ? 0 : 1);
	SCATCH;
}


XhBFISSyncServerRouterImp::~XhBFISSyncServerRouterImp(void)
{
	STRY;
	m_bSyncSubServer = false;
	if (m_syncSubServerThread && m_syncSubServerThread->joinable())
	{
		m_syncEvent.SendEvent();
		m_syncSubServerThread->join();
		m_syncSubServerThread = nullptr;
	}


	auto iter = m_vecThread.begin();
	while(iter != m_vecThread.end())
	{
		iter = m_vecThread.erase(iter);
	}

	m_bSync = FALSE;
	if (m_pThread)
	{
		m_condition.notify_all();
		while (m_pThread->IsAlive())
		{
			Sleep(30);
		}
	}
	UnInit();
	SCATCH;
}

int XhBFISSyncServerRouterImp::OnRecvData(UINT64 fromAddr,DWORD_PTR& d)
{
	STRY;
	switch(d)
	{
	case MSG_ISBUSY:
		if(!m_bBusy)
			return 1;
	case MSG_IS_ALIVE:
	    {
		readLock readLocker(m_csLockClientContext);
		auto itor = m_mapClientContext.find(fromAddr);
		if (itor != m_mapClientContext.end())
		{
			std::shared_ptr<RefCountInfo> refInfo = itor->second->GetRefInfo();
			AutoObjectRefMgr refObject;
			if (refObject.AddRefCount(refInfo))
			{
				readLocker.unlock();
				iBFIS_CommunicationInvoker invoke((HANDLE)fromAddr);
				int nRet = invoke.Invoke(d);
				TTRACE("���͸��¼���������ֵ %d  ����[%s] \r\n", nRet, __FUNCTION__);
				return nRet;
			}
		}
		//if (m_pComm)
		//	m_pComm->DoSendData((HANDLE)fromAddr, DBOperType(0), d, "");
		TTRACE("δ�ҵ���� ����[%s]\r\n",__FUNCTION__);
		return -1;
	    }
	case MSG_ISSUED_SYNC_ACK:
		{
			std::string brand;
			STRY;
			readLock readLocker(m_csLockClientContext);
			auto itor = m_mapClientContext.find(fromAddr);
			if (itor != m_mapClientContext.end())
			{
				brand = itor->second->m_custom.stInfo.strBranchId;
				SFTRACE("SyncInfo", "�¼�����[%s] ͬ�����\r\n", itor->second->m_custom.stInfo.strName.c_str());
			}
			SCATCH;
			m_syncEvent.SendEvent();

			STRY;
			if (!brand.empty())
			{
				if (m_syncFile.is_open())
				{
					boost::unique_lock<boost::mutex> lock(m_fileMutex);
					m_syncFile << brand.c_str() << std::endl;
				}
			}
			SCATCH;
			return 1;
		}
	case MSG_OUTGOING_DEVICE_SYNC:
		{
		ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER, "", __FUNCTION__);
		if (pCallback)
		{
			ST_CallBackInfo info;
			info.bIsQueue = false;
			info.pCallBackAddr = this;
			info.pSelfCallback = [this, fromAddr](ST_CallBackInfo& info)->int
			{
				vector<ST_RoleInfo> vecRoleInfo;
				if (m_pCache)
					m_pCache->QueryRoleInfo(vecRoleInfo);

				vector<ST_RolePurviewInfo> branchRolePurview;
				vector<ST_RoleInfo> branchRoleInfo;
				vector<std::string> vecConvertToStringRoleInfo;
				int currCount = 0;
				std::string strRoleInfo;
				for each(auto var in vecRoleInfo)
				{
					if (var.ConvertToString(strRoleInfo))
					{
						vecConvertToStringRoleInfo.push_back(strRoleInfo);
						strRoleInfo.clear();
					}
					vector<ST_RolePurviewInfo> vecRolePurviewInfo;
					if (m_pCache->QueryRolePurviewInfoByRoleId(var.strRoleInfoId, branchRolePurview))
					{
						int size = branchRolePurview.size();
						if (currCount == size)
						{
							DWORD dwCmd = MSG_ISSUED_ROLEPURVIEW;
							std::string strRoleInfoId = var.strRoleInfoId;
							int nRet = m_pComm->DoSendData(reinterpret_cast<HANDLE>(fromAddr), DBOperType::DBO_INVAILED, MSG_ISSUED_ROLEPURVIEW, strRoleInfoId);
							SFTRACE("����豸ͬ��", " ͬ����ɫȨ��[%s] ״̬[%d]\r\n", var.strRoleInfoId.c_str(), nRet);
							continue;
						}
						else
							currCount = size;
					}
				}

				if (m_pComm)
				{
					int nRet = 0;
					int size = vecConvertToStringRoleInfo.size();
					if (size > 0)
						nRet = m_pComm->DoSendData(reinterpret_cast<HANDLE>(fromAddr), DBOperType::DBO_INVAILED, MSG_ISSUED_ROLEINFO, vecConvertToStringRoleInfo);
					SFTRACE("����豸ͬ��", " ͬ����ɫ��С[%d] ״̬[%d]\r\n", size, nRet);

					size = branchRolePurview.size();
					if (size > 0)
					{
						std::string strRolePurviewInfo;
						vector<std::string> branchConvertRolePurview;
						for each(auto var in branchRolePurview)
						{
							if (var.ConvertToString(strRolePurviewInfo))
							{
								branchConvertRolePurview.push_back(strRolePurviewInfo);
								strRolePurviewInfo.clear();
							}
						}
						nRet = m_pComm->DoSendData(reinterpret_cast<HANDLE>(fromAddr), DBOperType::DBO_INVAILED, MSG_ISSUED_ROLEPURVIEW, branchConvertRolePurview);
						SFTRACE("����豸ͬ��", " ͬ����ɫȨ�޴�С[%d] ״̬[%d]\r\n", size, nRet);
					}

					vector<ST_EmployeeInfo> vecEmployeeInfo;
					if (m_pCache && m_pCache->QueryEmployeeInfo(vecEmployeeInfo))
					{
						std::string strEmployeeinfo;
						vector<std::string> vecConvertEmployeeInfo;
						for each(auto employeeinfo in vecEmployeeInfo)
						{
							if (employeeinfo.ConvertToString(strEmployeeinfo))
							{
								vecConvertEmployeeInfo.push_back(strEmployeeinfo);
							}
						}

						size = vecConvertEmployeeInfo.size();
						if (size > 0)
							nRet = m_pComm->DoSendData(reinterpret_cast<HANDLE>(fromAddr), DBOperType::DBO_INVAILED, MSG_ISSUED_EMPLOYEEINFO, vecConvertEmployeeInfo);
						SFTRACE("����豸ͬ��", " ͬ��Ա����С[%d] ״̬[%d]\r\n", size, nRet);
					}

					vector<ST_EmployeePurviewInfo> vecEmployeePurviewInfo;
					if (m_pCache && m_pCache->QueryEmployeePurviewInfo(vecEmployeePurviewInfo))
					{
						std::string strEmployeePurviewInfo;
						vector<std::string> vecConvertEmployeePurviewInfo;
						for each(auto employeeinfo in vecEmployeePurviewInfo)
						{
							if (employeeinfo.ConvertToString(strEmployeePurviewInfo))
							{
								vecConvertEmployeePurviewInfo.push_back(strEmployeePurviewInfo);
								strEmployeePurviewInfo.clear();
							}
						}

						size = vecConvertEmployeePurviewInfo.size();
						if (size > 0)
							nRet = m_pComm->DoSendData(reinterpret_cast<HANDLE>(fromAddr), DBOperType::DBO_INVAILED, MSG_OUTGOING_EMPLOYEEPURVIEWINFO, vecConvertEmployeePurviewInfo);
						SFTRACE("����豸ͬ��", " ͬ��Ա��Ȩ�޴�С[%d] ״̬[%d]\r\n", size, nRet);
					}

					vector<ST_ProduceInfo> vecProduceInfo;
					vector<std::string> vecConvertProduceInfo;
					std::string strProduceInfo;
					if (m_pCache && m_pCache->QueryProduceInfo(vecProduceInfo))
					{
						for each(auto scriptinfo in vecProduceInfo)
						{
							if (scriptinfo.ConvertToString(strProduceInfo))
							{
								vecConvertProduceInfo.push_back(strProduceInfo);
								strProduceInfo.clear();
							}
						}

						size = vecConvertProduceInfo.size();
						if (size > 0)
							nRet = m_pComm->DoSendData(reinterpret_cast<HANDLE>(fromAddr), DBOperType::DBO_INVAILED, MSG_ISSUED_PRODUCEINFO, vecConvertProduceInfo);
						SFTRACE("����豸ͬ��", " ͬ����Ʒ��С[%d] ״̬[%d]\r\n", size, nRet);
					}
					std::string strScriptInfo;
					vector<std::string> vecConvertScriptInfo;
					vector<ST_ScriptInfo> vecScriptInfo;
					if (m_pCache && m_pCache->QueryScriptInfoByCache(vecScriptInfo))
					{
						for each(auto scriptinfo in vecScriptInfo)
						{
							if (scriptinfo.ConvertToString(strScriptInfo))
							{
								vecConvertScriptInfo.push_back(strScriptInfo);
							}
						}

						size = vecConvertScriptInfo.size();
						if (size > 0)
							nRet = m_pComm->DoSendData(reinterpret_cast<HANDLE>(fromAddr), DBOperType::DBO_INVAILED, MSG_ISSUED_SCRIPTINFO, vecConvertScriptInfo);
						SFTRACE("����豸ͬ��", " ͬ��������С[%d] ״̬[%d]\r\n", size, nRet);
					}
				}
				return 1;
			};
			pCallback->AddCallBack(info, __FUNCTION__);
			return 1;
		}
		break;
		}
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnRecvData(UINT64 fromAddr,DWORD_PTR& d,std::string& s)
{
	ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
	if(pCallback)
	{
		ST_CallBackInfo info;
		info.bIsQueue = true;
		info.nCallIdx = (int)fromAddr;
		info.pCallBackAddr = this;
		
		info.pSelfCallback = [this,fromAddr,s,d](ST_CallBackInfo&) -> int
		{
			STRY;
			XhAutoSetBusy ab(m_bBusy);
			//TTRACE(_T("%s[%d]:�յ����Կͻ��˵���Ϣ,message type:%d\r\n"),__FUNCTION__,__LINE__,d);
			DBOperType enType = DBO_INVAILED;
			string strInfo = _T("");
			char szMsg[255];
			if (d != MSG_LOGIN)
			{
				int nSync = 0;
				GetBranchName(fromAddr,strInfo, nSync);
				//if (2 == nSync && false == strInfo.empty())
				//{
				//	sprintf(szMsg, "�յ�����[%s]�����Ĳ���[%s]", strInfo.c_str(), Cmd2Msg(d).c_str());
				//	DISPLAY_LOG("ҵ��ģ��", szMsg, "", "", 1);
				//}
			}
			switch(d)
			{
			case MSG_UPLOAD_BRANCHINFO:
				{
					BFIS::BranchInfo msg;
					bool bSuccess = msg.ParseFromString(s);
					if(bSuccess)
					{
						ST_BranchInfo stInfo(msg);
						vector<ST_BranchInfo> vecBranchInfo;
						stInfo.nIsLocal = 0;
						if(stInfo.strParentId == "")
						{
							if (m_pCache && m_pCache->QueryBranchInfo(vecBranchInfo))
							{
								if (!vecBranchInfo.empty())
								{
									for each(auto branch in vecBranchInfo)
									{
										if(stInfo.strParentJDBRID == branch.strJDBRID)
										{
											stInfo.strParentId = branch.strBranchId;
										}
									}
								}
							}
							/*if(m_strLocalBranchId != "" || m_strLocalBranchId == "" && GetLocalBranchId(m_strLocalBranchId))
							{
								FOUTPUTDBGSTRING("����ȡ���ı�������IDΪ:%s[%s:%d]�� \r\n",m_strLocalBranchId.c_str(),__FUNCTION__,__LINE__);
								stInfo.strParentId = m_strLocalBranchId;
							}*/
							else
							{
								char szBuf[255] = {0};
								sprintf(szBuf,"�����¼�%s��ParentIDʧ��",stInfo.strBranchId.c_str());
								DISPLAY_LOG("ͬ������",szBuf,"��ȡ��������IDʧ��","",0);
							}
						}
						int nRet = OnGotUploadBranchInfo(stInfo);
						TTRACE(_T("%s[%d]:�յ������¼��ϴ�������Ϣ������ID:%s�����ݿ��������ֵ:%d\r\n"),__FUNCTION__,__LINE__,
							stInfo.strBranchId.c_str(),nRet);
						//�¼���¼ʱ���·���Ʒ��Ϣ�Ϳͻ���Ϣ			
						return nRet;
					}
				}
				break;
			case MSG_UPLOAD_CLIENTINFO:
				{
					std::string s1 = s;
					BFIS::ClientInfo msg;
					bool bSuccess = msg.ParseFromString(s1);
					if (bSuccess)
					{
						ST_ClientInfo stClientInfo(msg);
						int nRet = OnGotUpLoadClientInfo(stClientInfo);
						TTRACE(_T("%s[%d]:�յ������¼��ϴ��ͻ���Ϣ���ͻ�ID:%s�����ݿ��������ֵ:%d\r\n"),__FUNCTION__,__LINE__,
							stClientInfo.strClientId.c_str(),nRet);
						if (nRet == OT_EXIST)	//˵�����������Ѿ��ϴ������û����������᷵�ظ��û���ID���������к͸��û���ص�����
						{
							stClientInfo.ConvertToString(s1);
							enType = DBO_UPDATE;
						}
						else
							enType = DBO_ADD;
						//�ظ�Client
						if(m_pComm->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_CLIENTINFO,s1) <= 0)
						{
							TTRACE(_T("%s[%d]:����֪ͨʧ��,�ͻ�ID:%s"),__FUNCTION__,__LINE__,stClientInfo.strClientId.c_str());
						}
						return nRet;
					}
					break;
				}
			case MSG_UPLOAD_BUSINESSINFO:
				{
					BFIS::BusinessInfo msg;
					bool bSucess = msg.ParseFromString(s);
					ST_BusinessInfo stBusinessInfo(msg);
					int nRet = OnGotUpLoadBusinessInfo(stBusinessInfo);
					TTRACE(_T("%s[%d]:�յ������¼��ϴ�ҵ����Ϣ��ҵ��ID:%s�����ݿ��������ֵ:%d\r\n"),__FUNCTION__,__LINE__,
						stBusinessInfo.strBusinessInfoId.c_str(),nRet);
					return nRet;
					break;
				}
			case MSG_UPLOAD_BUSINESSFILEINFO:
				{
					BFIS::BusinessFileInfo msg;
					bool bSucess = msg.ParseFromString(s);
					ST_BusinessFileInfo stBusinessFileInfo(msg);
					int nRet = OnGotUpLoadBusinessFileInfo(stBusinessFileInfo);
					TTRACE(_T("%s[%d]:�յ������¼��ϴ�ҵ���ļ���Ϣ��ҵ���ļ�ID:%s�����ݿ��������ֵ:%d\r\n"),
						__FUNCTION__,__LINE__,stBusinessFileInfo.strRecordId.c_str(),nRet);
					return nRet;
				}
				break;
			case MSG_UPLOAD_BUSINESSRELATEINFO:
				{
					BFIS::BusinessRelateInfo msg;
					bool bSucess = msg.ParseFromString(s);
					ST_BusinessRelateInfo stBusinessRelateInfo(msg);
					int nRet = OnGotUpLoadBusinessRelateInfo(stBusinessRelateInfo);
					TTRACE(_T("%s[%d]:�յ������¼��ϴ�ҵ�������Ϣ��ҵ�������ϢID:%s�����ݿ��������ֵ:%d\r\n"),
						__FUNCTION__,__LINE__,stBusinessRelateInfo.strBusinessRelateInfoId.c_str(),nRet);
					return nRet;
				}
				break;
			case MSG_UPLOAD_EMPLOYEEINFO:
				{
					BFIS::EmployeeInfo msg;
					bool bSucess = msg.ParseFromString(s);
					ST_EmployeeInfo stEmployeeInfo(msg);
					int nRet = OnGotUpLoadEmployeeInfo(stEmployeeInfo);
					TTRACE(_T("%s[%d]:�յ������¼��ϴ�Ա����Ϣ��Ա����ϢID:%s�����ݿ��������ֵ:%d\r\n"),
						__FUNCTION__,__LINE__,stEmployeeInfo.strEmployeeId.c_str(),nRet);
					if (nRet == OT_EXIST)
						{enType = DBO_UPDATE;}
					else
						{enType = DBO_ADD;}
					if(m_pComm->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEINFO,s) <= 0)
					{
						TTRACE(_T("%s[%d]:����֪ͨʧ��,Ա����ϢID:%s"),__FUNCTION__,__LINE__,stEmployeeInfo.strEmployeeId.c_str());
					}
					return nRet;
					break;
				}
				case MSG_UPLOAD_ROLEINFO:
				{
					BFIS::RoleInfo msg;
					if(msg.ParseFromString(s))
					{
						ST_RoleInfo stInfo(msg);
						int nRet = OnGotUpLoadRoleInfo(stInfo);
						TTRACE(_T("%s[%d]:�յ������¼��ϴ���ɫ��Ϣ����ɫ��ϢID:%s�����ݿ��������ֵ:%d\r\n"),
							__FUNCTION__,__LINE__,stInfo.strRoleInfoId.c_str(),nRet);
						if(nRet > 0 && m_pComm->AddNotifyMsg(enType,IBFIS_MSG_CLIENT_NOTIFY_ROLEINFO,s) <= 0)
						{
							TTRACE(_T("%s[%d]:����֪ͨʧ��,��ɫ��ϢID:%s"),__FUNCTION__,__LINE__,stInfo.strRoleInfoId.c_str());
						}
						return nRet;
					}
				}
				break;
			case IBFIS_MSG_CLIENT_SYNC_PRODUCE:
			{
				BFIS::ProduceInfo googleInfo;
				bool bParse = googleInfo.ParseFromString(strInfo);
				if (!bParse)
				{
					DISPLAY_LOG("ͬ������", "ͬ����Ʒ��Ϣʧ��", "�����л���Ʒ��Ϣʧ��", "", 0);
					return -1;
				}

				DWORD_PTR dwCmd = MSG_ISSUED_PRODUCEINFO;
				std::vector<std::string> vecProduceInfo;
				vecProduceInfo.push_back(strInfo);

				std::map<UINT64, std::shared_ptr<ObjectRefCount<ST_Login> > >  mapClientContext;
				STRY;
				readLock readLocker(m_csLockClientContext);
				mapClientContext = m_mapClientContext;
				SCATCH;

				for each (auto & var in mapClientContext)
				{
					readLock readLocker(m_csLockClientContext);
					auto iter = m_mapClientContext.find(var.first);
					if (iter != m_mapClientContext.end())
					{
						std::shared_ptr<RefCountInfo> refInfo = iter->second->GetRefInfo();
						AutoObjectRefMgr refObject;
						if (refObject.AddRefCount(refInfo))
						{
							readLocker.unlock();
							iBFIS_CommunicationInvoker invoke((HANDLE)var.first);
							int nRet = invoke.Invoke(dwCmd, vecProduceInfo);
							char szBuf[255] = { 0 };
							sprintf(szBuf, "�·���Ʒ��Ϣ������%s[%s]%s", iter->second->m_custom.stInfo.strName.c_str(),
								iter->second->m_custom.stInfo.strBranchId.c_str(), nRet <= 0 ? "ʧ��" : "�ɹ�");
							DISPLAY_LOG("ͬ������", szBuf, "", "", nRet <= 0 ? 0 : 1);
						}
					}
				}
			return 1;
		}
	case MSG_CLIENT_SET_MANUALSYNC:
		{
			STRY;
			BFIS::ManualSyncParameter msg;
			if(msg.ParseFromString(s))
			{
				m_bManualSync = TRUE;
				ST_ManualSyncParameter stInfo(msg);	
				m_stManualSyncParameter = stInfo;
				int nRet = HandleManualSync(stInfo);
				return nRet;
			}
			SCATCH;
		}
		break;
	}
	if (d != MSG_LOGIN)
	{
		sprintf(szMsg,"ִ������[%s]�����Ĳ���[%s]ʧ��",strInfo.c_str(),Cmd2Msg(d).c_str());
		DISPLAY_LOG("ҵ��ģ��",szMsg,"","",0);
	}
	return -1;
	SCATCH;
			return 1;
		};
		pCallback->AddCallBack(info,__FUNCTION__);
	}
	return 1;
}
int XhBFISSyncServerRouterImp::DoSendData(IN HANDLE hSysHandle, IN DBOperType enType, IN DWORD_PTR d1, IN std::vector<std::string>& v1, IN DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	std::vector<DWORD_PTR> vecCmd;
	if (hSysHandle == NULL)
	{
		char szMsg[255] = {0};
		sprintf(szMsg,"%s[%d]�����¼����������ΪNULL,%sʧ��",__FUNCTION__,__LINE__);
		DISPLAY_LOG("�����ģ��",szMsg,"","",0);
		return -1;
	}
	vecCmd.push_back((DWORD_PTR)enType);
	vecCmd.push_back(d1);
	iBFIS_CommunicationInvoker invoke(hSysHandle);
	int nRet = invoke.Invoke(vecCmd,v1);
	if (nRet <= 0)
	{
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::DoSyncKeyValueInfo(void* toAddr,DWORD_PTR dwReserved)
{
	STRY;
	vector<ST_KeyValueInfo> vecKeyValueInfo1;
	vector<ST_KeyValueInfo> vecKeyValueInfo2;
	vector<ST_KeyValueInfo> vecKeyValueInfo3;
	vector<ST_KeyValueInfo> vecKeyValueInfo4;
	DWORD_PTR d1 = IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO;
	if (m_pCache && m_pCache->QueryKeyValueInfoByTypeAndCode("BasicSetting","",vecKeyValueInfo1))
	{
		if (!vecKeyValueInfo1.empty())
		{
			vector<string> vecStr;
			vecStr.push_back(vecKeyValueInfo1[0].strType);
			vecStr.push_back(vecKeyValueInfo1[0].strCode);
			vecStr.push_back("");
			DoSendData((HANDLE)toAddr,DBO_DEL,d1,vecStr);
			vector<string> vecStr1;
			vecStr1.push_back(vecKeyValueInfo1[0].strType);
			vecStr1.push_back(vecKeyValueInfo1[0].strCode);
			vecStr1.push_back(vecKeyValueInfo1[0].strValue);
			DoSendData((HANDLE)toAddr,DBO_ADD,d1,vecStr1);
			vecKeyValueInfo1.clear();
		}	
	}
	if (m_pCache && m_pCache->QueryKeyValueInfoByTypeAndCode("StorageSetting","",vecKeyValueInfo2))
	{
		if (!vecKeyValueInfo2.empty())
		{
			vector<string> vecStr;
			vecStr.push_back(vecKeyValueInfo2[0].strType);
			vecStr.push_back(vecKeyValueInfo2[0].strCode);
			vecStr.push_back("");
			DoSendData((HANDLE)toAddr,DBO_DEL,d1,vecStr);
			vector<string> vecStr1;
			vecStr1.push_back(vecKeyValueInfo2[0].strType);
			vecStr1.push_back(vecKeyValueInfo2[0].strCode);
			vecStr1.push_back(vecKeyValueInfo2[0].strValue);
			DoSendData((HANDLE)toAddr,DBO_ADD,d1,vecStr1);
			vecKeyValueInfo2.clear();
		}
	}
	if (m_pCache && m_pCache->QueryKeyValueInfoByTypeAndCode("PasswordStrategy","",vecKeyValueInfo3))
	{
		if (!vecKeyValueInfo3.empty())
		{
			vector<string> vecStr;
			vecStr.push_back(vecKeyValueInfo3[0].strType);
			vecStr.push_back(vecKeyValueInfo3[0].strCode);
			vecStr.push_back("");
			DoSendData((HANDLE)toAddr,DBO_DEL,d1,vecStr);
			vector<string> vecStr1;
			vecStr1.push_back(vecKeyValueInfo3[0].strType);
			vecStr1.push_back(vecKeyValueInfo3[0].strCode);
			vecStr1.push_back(vecKeyValueInfo3[0].strValue);
			DoSendData((HANDLE)toAddr,DBO_ADD,d1,vecStr1);
			vecKeyValueInfo3.clear();
		}		
	}
	if (m_pCache && m_pCache->QueryKeyValueInfoByTypeAndCode("LogSetting","",vecKeyValueInfo4))
	{
		if (!vecKeyValueInfo4.empty())
		{
			vector<string> vecStr;
			vecStr.push_back(vecKeyValueInfo4[0].strType);
			vecStr.push_back(vecKeyValueInfo4[0].strCode);
			vecStr.push_back("");
			DoSendData((HANDLE)toAddr,DBO_DEL,d1,vecStr);
			vector<string> vecStr1;
			vecStr1.push_back(vecKeyValueInfo4[0].strType);
			vecStr1.push_back(vecKeyValueInfo4[0].strCode);
			vecStr1.push_back(vecKeyValueInfo4[0].strValue);
			DoSendData((HANDLE)toAddr,DBO_ADD,d1,vecStr1);
			vecKeyValueInfo4.clear();
		}	
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::DoSyncMigrateTaskInfo(void* toAddr,DWORD_PTR dwReserved)
{
	STRY;
	vector<ST_TaskPlan> vecTaskPlanInfo;
	if (m_pCache)
	{
		m_pCache->ManageTaskPlanInfo(DBO_QUERY,vecTaskPlanInfo);
	}
	std::string strTemp;
    vector<std::string> vecTemp;
    iBFIS_CommunicationInvoker invoke((HANDLE)toAddr);
    DWORD dwCmd = MSG_ISSUED_MIGRATETASKINFO;
	if (!vecTaskPlanInfo.empty())
	{
		for each(auto taskplaninfo in vecTaskPlanInfo)
		{
			if(taskplaninfo.ConvertToString(strTemp))
			{
				vecTemp.push_back(strTemp);
			}
		}
		if(invoke.Invoke(dwCmd,vecTemp) < 0) //=0��ʾ�Ѿ�����
		{
			TTRACE("�·��豸��Ϣʧ�� \r\n");
		}
	}  
	return 1;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::OnRecvData(UINT64 fromAddr,DWORD_PTR& d1,std::vector<std::string>& v1)
{
	STRY;
    XhAutoSetBusy ab(m_bBusy);
	//string strInfo = _T("");
	char szMsg[255];
	//int nSync = 0;
	//GetBranchName(fromAddr,strInfo, nSync);
	//if (nSync == 2)
	//{
	//	sprintf(szMsg, "�յ�����3[%s]�����Ĳ���[%s]", strInfo.c_str(), Cmd2Msg(d1).c_str());
	//	DISPLAY_LOG("ҵ��ģ��", szMsg, "", "", 1);
	//}

	//TTRACE(_T("%s[%d]:�յ����Կͻ��˵���Ϣ,message type:%d\r\n"),__FUNCTION__,__LINE__,d1);
    switch (d1)
    {
    case MSG_LOGIN:
    {
        BFIS::BranchInfo msg;
        bool bSucess = msg.ParseFromString(v1[0]);
		ST_BranchInfo stBranchInfo(msg);
		SFTRACE("LoginStatusLog","����[%s]�ѵ�¼,����ID[%s]����IP[%s] \r\n",stBranchInfo.strName.c_str(), stBranchInfo.strBranchId.c_str(), stBranchInfo.strAddress.c_str());
        if (stBranchInfo.strParentId == "")
        {
            if (m_strLocalBranchId == "" && GetLocalBranchId(m_strLocalBranchId) || m_strLocalBranchId != "")
            {
				FOUTPUTDBGSTRING("����ȡ����������ID:%s[%s:%d]�� \r\n",m_strLocalBranchId.c_str(),__FUNCTION__,__LINE__);
                //stBranchInfo.strParentId = m_strLocalBranchId;
				vector<ST_BranchInfo> vecBranchInfo;
				stBranchInfo.nIsLocal = 0;
				if(stBranchInfo.strParentId == "")
				{
					if (m_pCache && m_pCache->QueryBranchInfo(vecBranchInfo))
					{
						if (!vecBranchInfo.empty())
						{
							for each(auto branch in vecBranchInfo)
							{
								if(stBranchInfo.strParentJDBRID == branch.strJDBRID)
								{
									stBranchInfo.strParentId = branch.strBranchId;
								}
							}
						}
					}
				}
            }
            else
            {
                TTRACE("��ȡ����������Ϣʧ��,�����¼���������ParentIdʧ�� \r\n");
            }
        }
        
		std::shared_ptr<ObjectRefCount<ST_Login> > spObjectRef = std::make_shared<ObjectRefCount<ST_Login> >();
		if (nullptr == spObjectRef)
		{
			sprintf(szMsg, "�������ʧ��,����%s[Url:%s]�����Ĳ���[%s]", stBranchInfo.strName.c_str(), v1[1].c_str(), Cmd2Msg(d1).c_str());
			DISPLAY_LOG("ҵ��ģ��", szMsg, "", "", 0);
			return -1;
		}
		spObjectRef->m_custom.notifyStatus.store(-1);
		spObjectRef->m_custom.stInfo = stBranchInfo;
		spObjectRef->m_custom.strUrl = v1[1];
		{
			writeLock writeLocker(m_csLockClientContext);
			auto iter = m_mapClientContext.find(fromAddr);
			if (iter != m_mapClientContext.end())
			{
				iter->second = spObjectRef;
			}
			else
			{
				m_mapClientContext[fromAddr] = spObjectRef;
			}
		}
        sprintf(szMsg, "�յ�����%s[Url:%s]�����Ĳ���[%s]", stBranchInfo.strName.c_str(), v1[1].c_str(), Cmd2Msg(d1).c_str());
        DISPLAY_LOG("ҵ��ģ��", szMsg, "", "", 1);
        //
        SetBranchLoginLog(stBranchInfo);

		ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
		if(pCallback)
		{
			ST_CallBackInfo info;
			info.bIsQueue = false;
			info.nCallIdx = info.GetCallIndex();
			info.pCallBackAddr = this;
			info.pSelfCallback = [this,fromAddr](ST_CallBackInfo& info)->int
			{
				readLock readLocker(m_csLockClientContext);
				auto iter = m_mapClientContext.find(fromAddr);
				if (iter != m_mapClientContext.end())
				{
					STRY;
					std::shared_ptr<RefCountInfo> refInfo = iter->second->GetRefInfo();
					std::string strBranch = iter->second->m_custom.stInfo.strBranchId;
					AutoObjectRefMgr refObject;
					if (refObject.AddRefCount(refInfo))
					{
						readLocker.unlock();
						vector<ST_RoleInfo> vecRoleInfo;
						if (m_pCache && m_pCache->QueryRoleInfo(vecRoleInfo))
						{
							vector<ST_RolePurviewInfo> branchRolePurview;
							vector<ST_RoleInfo> branchRoleInfo;
							int currSize = 0;
							for each(auto var in vecRoleInfo)
							{
								if (var.strBranchInfoId == m_stBranchInfo.strBranchId && var.nExtendedInfo != -2)   //���ϼ������Ľ�ɫ���µ��¼�
								{
									branchRoleInfo.push_back(var);
									if (m_pCache->QueryRolePurviewInfoByRoleId(var.strRoleInfoId, branchRolePurview))
									{
										int size = branchRolePurview.size();
										if (currSize == size)
										{
											iBFIS_CommunicationInvoker invoke((HANDLE)fromAddr);
											DWORD dwCmd = MSG_ISSUED_ROLEPURVIEW;
											invoke.Invoke(dwCmd, var.strRoleInfoId);  //��Ӧ��ɫȨ��Ϊ�յ�ʱ��
											SFTRACE("RolePurview", "��ɫID[%s]��ɫName[%s]����ID[%s]\r\n", var.strRoleInfoId.c_str(), var.strRoleName.c_str(), var.strBranchInfoId.c_str());
											continue;
										}
										else
											currSize = size;
									}
								}
							}
							DoSyncRoleInfo((HANDLE)fromAddr, branchRoleInfo);
							DoSyncRolePurviewInfo((HANDLE)fromAddr, branchRolePurview);
						}
						CHECK_CONNECT_DEL(refObject);
						vector<ST_EmployeeInfo> vecEmployeeInfo;
						if (m_pCache && m_pCache->QueryEmployeeInfo(vecEmployeeInfo))
						{
							vector<ST_EmployeeInfo> vecTemp;
							for each(auto employeeinfo in vecEmployeeInfo)
							{
								if (employeeinfo.nExtendedInfo == 1 && employeeinfo.strBranchId.compare(strBranch) == 0 && employeeinfo.strExtendedInfo2.compare("100") != 0)
								{
									vecTemp.push_back(employeeinfo);
								}
							}
							DoSyncEmployeeInfo((HANDLE)fromAddr, vecTemp);
						}
						CHECK_CONNECT_DEL(refObject);
						DoSyncKeyValueInfo((HANDLE)fromAddr);
						DoSyncMigrateTaskInfo((HANDLE)fromAddr);
						DoSyncScriptInfo((HANDLE)fromAddr);
						iter->second->m_custom.notifyStatus.store(0);
					}
					SCATCH;
				}
				return 1;
			};
			pCallback->AddCallBack(info,__FUNCTION__);
		}
		
        //DoRealTimeSync();        
        return 1;
    }
        break;
    case MSG_GET_CLIENTINFO:
    {
        if (IssueSyncClientInfo(v1,1) < 0)
        {
            return -1;
        }
    }
        break;
        // 	case MSG_GET_ROLEINFO:
        // 		{
        // 			if(IssueSyncRoleInfo(v1) < 0)
        // 			{
        // 				m_bBusy = FALSE;
        // 				return -1;
        // 			}
        // 		}
        // 		break;
        // 	case MSG_GET_ROLEPURVIEW:
        // 		{
        // 			if(IssueSyncRolePurviewInfo(v1) < 0)
        // 			{
        // 				m_bBusy = FALSE;
        // 				return -1;
        // 			}
        // 		}
        // 		break;
    case MSG_GET_PRODUCEINFO:
		{
			if (IssueSyncProduceInfo(v1) < 0)
			{
				return -1;
			}
		}
		break;
	case MSG_UPLOAD_ROLEPURVIEWINFO:
		{
			vector<std::string> vecStr = std::move(v1);
			v1.clear();
#if 0    //���账���¼��ϴ���Ȩ����Ϣ
			ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
			if(pCallback)
			{
				ST_CallBackInfo info;
				info.bIsQueue = true;
				info.nCallIdx = (int)fromAddr;
				info.pCallBackAddr = this;
				info.pSelfCallback = [this,vecStr](ST_CallBackInfo&) -> int
				{
					STRY;
					struct PolePurviewParse
					{
						std::string         strData;
						ST_RolePurviewInfo stPurviewInfo;
						PolePurviewParse(BFIS::RolePurviewInfo msg, std::string data) :stPurviewInfo(msg), strData(data)
						{}
					};

					if (nullptr == m_pCache)
						return 1;

					std::set<std::string>  roleInfoSet;
					vector<PolePurviewParse>   vecParseRoleInfo;
					for (auto iter = vecStr.begin();iter != vecStr.end();iter ++)
					{
						BFIS::RolePurviewInfo msg;
						if (msg.ParseFromString(*iter))
						{
							PolePurviewParse stParsePurviewInfo(msg, *iter);
							auto var = roleInfoSet.find(stParsePurviewInfo.stPurviewInfo.strRoleId);
							if (var == roleInfoSet.end())
							{
								roleInfoSet.insert(stParsePurviewInfo.stPurviewInfo.strRoleId);
								vector<ST_RolePurviewInfo> vecRolePurviewInfo;
								m_pCache->QueryRolePurviewInfoByRoleId(stParsePurviewInfo.stPurviewInfo.strRoleId, vecRolePurviewInfo);
								for each(auto& itor in vecRolePurviewInfo)
								{
									m_pCache->ManageRolePurviewInfo(DBO_DEL, itor);
								}
							}
							vecParseRoleInfo.push_back(std::move(stParsePurviewInfo));
						}
					}

					for each (auto var in vecParseRoleInfo)
					{
						int nRet = OnGotUpLoadRolePurviewInfo(var.stPurviewInfo);
						TTRACE(_T("%s[%d]:�յ������¼��ϴ���ɫȨ����Ϣ����ɫȨ��ID:%s�����ݿ��������ֵ:%d\r\n"),
							__FUNCTION__, __LINE__, var.stPurviewInfo.strRoleInfoPurviewId.c_str(), nRet);
						if (nRet > 0 && m_pComm->AddNotifyMsg(DBO_ADD, IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO, var.strData) <= 0)
						{
							TTRACE(_T("%s[%d]:��ӽ�ɫȨ����Ϣ����֪ͨʧ��,��ɫȨ��ID:%s"), __FUNCTION__, __LINE__, var.stPurviewInfo.strRoleInfoPurviewId.c_str());
						}
					}
					SCATCH;
					return 1;
				};
				pCallback->AddCallBack(info,__FUNCTION__);
			}
#endif
			return 1;
		}
		break;
    case MSG_UPLOAD_EMPLOYEEPURVIEWINFO:
		{
			vector<std::string> vecStr = v1;
			v1.clear();

			ICallbackManagement* pCallback = iSOC_CreateObject<ICallbackManagement>(OBJECT_TYPE_CALLBACK_MANAGER,"",__FUNCTION__);
			if(pCallback)
			{
				ST_CallBackInfo info;
				info.bIsQueue = true;
				info.nCallIdx = (int)fromAddr;
				info.pCallBackAddr = this;
				info.pSelfCallback = [this,vecStr](ST_CallBackInfo&) -> int
				{
					STRY;
					bool bFirst = false;
					for (auto iter = vecStr.begin(); iter != vecStr.end(); iter++)
					{
						BFIS::EmployeePurviewInfo msg;
						bool bSuccess = msg.ParseFromString(*iter);
						if (!bSuccess)
						{
							DISPLAY_LOG("ͬ������", "����Ա��Ȩ����Ϣʧ��", "", "", 0);
							return -1;
						}
						ST_EmployeePurviewInfo stEmployeePurviewInfo(msg);
						if (!bFirst)
						{
							if (QueryFail == m_pCache->ManageEmployeePurviewInfo(DBO_DEL, stEmployeePurviewInfo))
							{
								return -1;
							}
							bFirst = true;
						}
						int nRet = OnGotUpLoadEmployeePurviewInfo(stEmployeePurviewInfo);
						TTRACE(_T("%s[%d]:�յ������¼��ϴ�Ա��Ȩ����Ϣ��Ա��Ȩ����ϢID:%s�����ݿ��������ֵ:%d\r\n"),
							__FUNCTION__, __LINE__, stEmployeePurviewInfo.strEmployeePurviewId.c_str(), nRet);
						//char szMsg[255] = { 0 };
						//sprintf(szMsg, "�յ������¼��ϴ�Ա��Ȩ����Ϣ��Ա��Ȩ����ϢID:%s", stEmployeePurviewInfo.strEmployeePurviewId.c_str());
						//DISPLAY_LOG("ͬ������", szMsg, "", "", nRet > 0 ? 1 : 0);
					}
					SCATCH;
					return 1;
				};
				pCallback->AddCallBack(info,__FUNCTION__);
			}
			
				/*if (nRet > 0)
				{
					std::string strInfo;
					bool bSuccess = stEmployeePurviewInfo.ConvertToString(strInfo);
					if (bSuccess)
					{
						v1.push_back(strInfo);
					}
				}*/
				/*else
				{
				return -1;
				}*/
		}
		break;
    case MSG_GET_SMS_LOGININFO:
		{
			iFVR_Configuration config;
			std::string strSMSIp, strSMSPort, strUserName, strUserPwd;
			strSMSIp = config.GetString("SMS", "SMSIP", "");
			strUserName = config.GetString("SMS", "SMSUser", "");
			strUserPwd = config.GetString("SMS", "SMSPwd", "");
			strSMSPort = config.GetString("SMS", "SMSPort", "5150");
			v1.clear();
			v1.push_back(strSMSIp);
			v1.push_back(strSMSPort);
			v1.push_back(strUserName);
			v1.push_back(strUserPwd);
			return 1;
			break;
		}
    case MSG_GET_PARENT_BRANCHINFO:
        {
            v1.clear();
//            iSOC_MonFactoryManagement fmt;
//             IBFISDBOperation* pDBO = (IBFISDBOperation*)fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__);
//             if (!pDBO)
//             {
// 				m_bBusy = FALSE;
//                 DISPLAY_LOG("ͬ������", "��ȡ����������Ϣʧ��", "���ݿ����Ϊ��", "", 0);
//                 return -1;
//             }
// 
//             int nRet = pDBO->GetLocalBranchInfo(m_stBranchInfo);
			if (m_pCache && m_pCache->QueryLocalBranchId(m_strLocalBranchId))
			{
				m_pCache->QueryBranchInfoById(m_strLocalBranchId,m_stBranchInfo);
				v1.push_back(m_stBranchInfo.strBranchId);
				v1.push_back(m_stBranchInfo.strName);
				v1.push_back(m_stBranchInfo.strParentId);
			}
            return 1;
            break;
        }
    }
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnRecvData(UINT64 fromAddr, DWORD_PTR& d1, DWORD_PTR& d2, std::string& s)
{
	STRY;
	if(s == "")
		return -1;
    XhAutoSetBusy ab(m_bBusy);
	int nRet = -1;
	switch(d1)
	{
	case IBFIS_MSG_CLIENT_NOTIFY_BRANCHINFO:
		{
			BFIS::BranchInfo msg;
			if(msg.ParseFromString(s))
			{
				ST_BranchInfo stInfo(msg);
				if(m_strLocalBranchId != "" || m_strLocalBranchId == "" && GetLocalBranchId(m_strLocalBranchId))
				{
					if(stInfo.strBranchId != m_strLocalBranchId)
					{
						nRet = BranchInfoNotify((int)d2,stInfo);
						if(nRet != -1 && stInfo.ConvertToString(s) && m_pComm->AddNotifyMsg((DBOperType)d2,d1,s) <= 0)
						{
							DISPLAY_LOG("ͬ��","[����֪ͨ]֪ͨ�ͻ��˸���������Ϣ","ʧ��","",0);
						}
					}
				}
				return nRet;
			}
			DISPLAY_LOG("ͬ��","[����֪ͨ]����������Ϣ","����ʧ��","",0);
		}
		break;
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
// 	case IBFIS_MSG_CLIENT_NOTIFY_USERMAPINFO:
// 		{
// 			BFIS::UserMapInfo msg;
// 			if(msg.ParseFromString(s))
// 			{
// 				ST_UserMapInfo stInfo(msg);
// 				return UserMapInfoNotify((int)d1,stInfo);
// 			}
// 			DISPLAY_LOG("ͬ��","[����֪ͨ]����ӳ����Ϣ","����ʧ��","",0);
// 		}
// 		break;
	case IBFIS_MSG_CLIENT_NOTIFY_ROLEINFO:
		{
			BFIS::RoleInfo msg;
			if(msg.ParseFromString(s))
			{
				ST_RoleInfo stInfo(msg);
				nRet = RoleInfoNotify((int)d2,stInfo);
				if(nRet != -1 && m_pComm->AddNotifyMsg((DBOperType)d2,d1,s) <= 0)
				{
					DISPLAY_LOG("ͬ��","[����֪ͨ]֪ͨ�ͻ��˸��½�ɫ��Ϣ","ʧ��","",0);
				}
				return nRet;
			}
			DISPLAY_LOG("ͬ��","[����֪ͨ]���½�ɫ��Ϣ","����ʧ��","",0);
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEINFO:
		{
			BFIS::EmployeeInfo msg;
			if(msg.ParseFromString(s))
			{
				ST_EmployeeInfo stInfo(msg);
				nRet = EmployeeInfoNotify((int)d2,stInfo);
				if(nRet != -1 && m_pComm->AddNotifyMsg((DBOperType)d2,d1,s) <= 0)
				{
					DISPLAY_LOG("ͬ��","[����֪ͨ]֪ͨ�ͻ��˸���Ա����Ϣ","ʧ��","",0);
				}
				return nRet;
			}
			DISPLAY_LOG("ͬ��","[����֪ͨ]����Ա����Ϣ","����ʧ��","",0);
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
	case IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO:
		{
			BFIS::RolePurviewInfo msg;
			if(msg.ParseFromString(s))
			{
				ST_RolePurviewInfo stInfo(msg);
				std::vector<ST_RolePurviewInfo> vecInfo;
				vecInfo.push_back(stInfo);
				nRet =  RolePurviewInfoNotify((int)d2,vecInfo);
				if(nRet != -1 && m_pComm->AddNotifyMsg((DBOperType)d2,d1,s) <= 0)
				{
					DISPLAY_LOG("ͬ��","[����֪ͨ]֪ͨ�ͻ��˸��½�ɫȨ����Ϣ","ʧ��","",0);
				}
				return nRet;
			}
			DISPLAY_LOG("ͬ��","[����֪ͨ]���½�ɫȨ����Ϣ","����ʧ��","",0);
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEPURVIEWINFO:
		{
			BFIS::EmployeePurviewInfo msg;
			if(msg.ParseFromString(s))
			{
				ST_EmployeePurviewInfo stInfo(msg);
				std::vector<ST_EmployeePurviewInfo> vecInfo;
				vecInfo.push_back(stInfo);
				nRet = EmployeePurviewInfoNotify((int)d2,vecInfo);
				if(nRet != -1 && m_pComm->AddNotifyMsg((DBOperType)d2,d1,s) <= 0)
				{
					DISPLAY_LOG("ͬ��","[����֪ͨ]֪ͨ�ͻ��˸���Ա��Ȩ����Ϣ","ʧ��","",0);
				}
				return nRet;
			}
			DISPLAY_LOG("ͬ��","[����֪ͨ]����Ա��Ȩ����Ϣ","����ʧ��","",0);
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_BUSINESSINFO:
		{		
			BFIS::BusinessInfo msg;
			if(msg.ParseFromString(s))
			{
				ST_BusinessInfo stInfo(msg);
				ST_BusinessInfo stBusinessInfo;
				if(m_pCache && m_pCache->QueryBusinessInfoById(stInfo.strBusinessInfoId,stBusinessInfo))
				{
					if (stBusinessInfo.nMarkerType < 50 && stBusinessInfo.nMarkerType != 0)
					{
						stInfo.nMarkerType = stBusinessInfo.nMarkerType;
					}				
				}
				nRet = BusinessInfoNotify((int)d2,stInfo);
				return nRet;
			}
			/*else
			{
				DISPLAY_LOG("ͬ��","[����֪ͨ]����ҵ����Ϣ","����ʧ��","",0);
			}*/
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_BUSINESSFILEINFO:
		{
			BFIS::BusinessFileInfo msg;
			if(msg.ParseFromString(s))
			{
				ST_BusinessFileInfo stInfo(msg);
				nRet = BusinessFileInfoNotify((int)d2,stInfo);
				return nRet;
			}
			else
			{
				DISPLAY_LOG("ͬ��","[����֪ͨ]����ҵ����Ϣ","����ʧ��","",0);
			}
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_BUSINESSRELATEINFO:
		{
			BFIS::BusinessRelateInfo msg;
			if(msg.ParseFromString(s))
			{
				ST_BusinessRelateInfo stInfo(msg);
				nRet = BusinessRelateInfoNotify((int)d2,stInfo);
				return nRet;
			}
			else
			{
				DISPLAY_LOG("ͬ��","[����֪ͨ]����ҵ����Ϣ","����ʧ��","",0);
			}
		}
		break;
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnRecvData(UINT64 fromAddr, std::vector<DWORD_PTR>& v1, std::vector<std::string>& v2)
{
	STRY;
    XhAutoSetBusy ab(m_bBusy);
	int nRet = -1;
	int nType = v1[1];
	//string strInfo = _T("");
	char szMsg[255];
	int nSync = 0;
	//GetBranchName(fromAddr,strInfo, nSync);
	//if (nSync == 2)
	{
		//sprintf(szMsg, "�յ�����1[%s]�����Ĳ���[%s]", strInfo.c_str(), Cmd2Msg(v1[0]).c_str());
		//DISPLAY_LOG("ҵ��ģ��", szMsg, "", "", 1);
		//TTRACE(_T("%s[%d]:�յ�����1[%s]�����Ĳ���[%s]\r\n"),__FUNCTION__, __LINE__, strInfo.c_str(), Cmd2Msg(v1[0]).c_str());
	}


	switch(v1[0])
	{
	case IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO:
		{
			std::vector<ST_RolePurviewInfo> vecInfo;
			for each(auto& info in v2)
			{
				BFIS::RolePurviewInfo msg;
				if(msg.ParseFromString(info))
				{
					ST_RolePurviewInfo stInfo(msg);
					vecInfo.push_back(stInfo);
				}
			}
			nRet = RolePurviewInfoNotify((int)v1[1],vecInfo);
			if(nRet != -1 && m_pComm->AddNotifyMsg((DBOperType)v1[1],v1[0],v2) <= 0)
			{
				DISPLAY_LOG("ͬ��","[����֪ͨ]֪ͨ�ͻ��˸��½�ɫȨ����Ϣ","ʧ��","",0);
			}
			return nRet;
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEPURVIEWINFO:
		{
			std::vector<ST_EmployeePurviewInfo> vecInfo;
			for each(auto& info in v2)
			{
				BFIS::EmployeePurviewInfo msg;
				if(msg.ParseFromString(info))
				{
					ST_EmployeePurviewInfo stInfo(msg);
					vecInfo.push_back(stInfo);
				}
			}
			nRet = EmployeePurviewInfoNotify((int)v1[1],vecInfo);
			if(nRet != -1 && m_pComm->AddNotifyMsg((DBOperType)v1[1],v1[0],v2) <= 0)
			{
				DISPLAY_LOG("ͬ��","[����֪ͨ]֪ͨ�ͻ��˸���Ա��Ȩ����Ϣ","ʧ��","",0);
			}
			return nRet;
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO:
		{
			ST_KeyValueInfo Info;
			Info.strType = v2[0];
			Info.strCode = v2[1];
			Info.strValue = v2[2];
			nRet = KeyValueInfoNotify((int)v1[1],Info);
			if(nRet != -1 && m_pComm->AddNotifyMsg((DBOperType)v1[1],v1[0],v2) <= 0)
			{
				DISPLAY_LOG("ͬ��","[����֪ͨ]֪ͨ�ͻ��˸��¼�ֵ��Ϣ","ʧ��","",0);
			}
			return nRet;
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_BUSINESSINFO:
		{
			for each(auto info in v2)
			{
				BFIS::BusinessInfo msg;
				if(msg.ParseFromString(info))
				{
					ST_BusinessInfo stInfo(msg);
					BusinessInfoNotify(nType,stInfo);
				}
				else
					TTRACE("ͬ��[����֪ͨ]����ҵ����Ϣʧ��%s[%d] \r\n",__FUNCTION__,__LINE__);
			}
			return 1;
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_BUSINESSFILEINFO:
		{
			for each(auto info in v2)
			{
				BFIS::BusinessFileInfo msg;
				if(msg.ParseFromString(info))
				{
					ST_BusinessFileInfo stInfo(msg);
					BusinessFileInfoNotify(nType,stInfo);
				}
				else
					TTRACE("ͬ��[����֪ͨ]����ҵ���ļ���Ϣʧ��%s[%d] \r\n",__FUNCTION__,__LINE__);
			}
			return 1;
		}
		break;
	case IBFIS_MSG_CLIENT_NOTIFY_BUSINESSRELATEINFO:
		{
			for each(auto info in v2)
			{
				BFIS::BusinessRelateInfo msg;
				if(msg.ParseFromString(info))
				{
					ST_BusinessRelateInfo stInfo(msg);
					BusinessRelateInfoNotify(nType,stInfo);
				}
				else
					TTRACE("ͬ��[����֪ͨ]����ҵ�������Ϣʧ��%s[%d] \r\n",__FUNCTION__,__LINE__);
			}
			return 1;
		}
		break;
	}
	return -1;
	SCATCH;
	return -1;
}

void XhBFISSyncServerRouterImp::SetDisplayListCtrl(CListCtrl* pList)
{
	m_pListctrl = pList;
}

void XhBFISSyncServerRouterImp::SetBranchLoginLog(ST_BranchInfo stBranchInfo)
{
	STRY;
	if (stBranchInfo.strBranchId == "")
	{
		TTRACE("���������¼��־ʧ�ܣ���������IDΪ��.%s[%d] \r\n",__FUNCTION__,__LINE__);
		return;
	}
	//��ѯ֧����Ϣ�Ƿ���ڣ������������
	if (m_pCache)
	{
		ST_BranchInfo stQuery;
		/*stQuery = stBranchInfo;*/
		if(m_pCache->QueryBranchInfoById(stBranchInfo.strBranchId,stQuery) > 0)
		{
			//m_pCache->ManageBranchInfo(DBO_UPDATE,stBranchInfo);
		}
		else
		{
			m_pCache->ManageBranchInfo(DBO_ADD, stBranchInfo);
		}
	}
	if (FindBranchLog(stBranchInfo.strBranchId.c_str()))
	{
		ModifyBranchLog(stBranchInfo);
	}
	else
	{
		CString strDes;
		if(stBranchInfo.strName != "")
		{
			strDes.Format("���㡾%s���ѵ�¼",stBranchInfo.strName.c_str());
			DISPLAY_LOG("ͬ������",(LPCTSTR)strDes, "", "", 1);
		}
		AddBranchLog(stBranchInfo);
	}
	SCATCH;
}

bool XhBFISSyncServerRouterImp::AddBranchLog(ST_BranchInfo stBranchInfo)
{
	STRY;
	if (m_pListctrl == NULL)
	{
		TTRACE("����ؼ�������.%s[%d] \r\n",__FUNCTION__,__LINE__);
		return false;
	}
	if (stBranchInfo.strBranchId == "")
	{
		TTRACE("��������¼��־ʧ�ܣ���������IDΪ��.%s[%d] \r\n",__FUNCTION__,__LINE__);
		return false;
	}
	/*
	string strBranchId;
	string strName;
	string strAddress;
	string strContact;
	string strPhone;
	string strContent;
	int	   nExtendedInfo;
	string strExtendedInfo1;
	string strExtendedInfo2;
	*/
	int nIndex = m_pListctrl->GetItemCount();
	CString strTemp;
	strTemp.Format("%d",nIndex + 1);
	m_pListctrl->InsertItem(nIndex,strTemp);
	m_pListctrl->SetItemText(nIndex,1,stBranchInfo.strBranchId.c_str());
	m_pListctrl->SetItemText(nIndex,2,stBranchInfo.strName.c_str());
	m_pListctrl->SetItemText(nIndex,3,stBranchInfo.strAddress.c_str());
	m_pListctrl->SetItemText(nIndex,4,stBranchInfo.strContact.c_str());
	m_pListctrl->SetItemText(nIndex,5,stBranchInfo.strPhone.c_str());
	m_pListctrl->SetItemText(nIndex,6,stBranchInfo.strContent.c_str());
	strTemp.Format("%d",stBranchInfo.nExtendedInfo);
	m_pListctrl->SetItemText(nIndex,7,strTemp);
	m_pListctrl->SetItemText(nIndex,8,stBranchInfo.strExtendedInfo1.c_str());
	m_pListctrl->SetItemText(nIndex,9,stBranchInfo.strExtendedInfo1.c_str());
    m_pListctrl->SetItemText(nIndex,10,stBranchInfo.strJDBRID.c_str());
    m_pListctrl->SetItemText(nIndex,11,stBranchInfo.strJDBRID.c_str());
    m_pListctrl->SetItemText(nIndex,12,stBranchInfo.strParentJDBRID.c_str());
    m_pListctrl->SetItemText(nIndex,13,stBranchInfo.strJDTYPE.c_str());
	try
	{
		ST_BranchInfo* pBranchInfo = new ST_BranchInfo;
		if (pBranchInfo != NULL)
		{
// 			memset(pBranchInfo,0,sizeof(ST_BranchInfo));
// 			memcpy(pBranchInfo,&stBranchInfo,sizeof(ST_BranchInfo));
			*pBranchInfo = stBranchInfo;
			m_pListctrl->SetItemData(nIndex,(DWORD)pBranchInfo);
		}
		else
		{
			TTRACE("�����������ʧ�ܣ�BranchInfoId:%s \r\n",stBranchInfo.strBranchId);
		}
		if(m_pListctrl->GetItemCount() > 0)
		{
			//PostMessage((m_pListctrl->GetParent())->m_hWnd,MSG_BTN_SHOW,(WPARAM)(1),(LPARAM)0);
		}
	}
	catch(...)
	{
		return false;
	}
	return true;
	SCATCH;
	return false;
}

bool XhBFISSyncServerRouterImp::ModifyBranchLog(ST_BranchInfo stBranchInfo)
{
	STRY;
	if (stBranchInfo.strBranchId == "")
	{
		TTRACE("�޸������¼��־ʧ�ܣ���������IDΪ��.%s[%d] \r\n",__FUNCTION__,__LINE__);
		return false;
	}
	CString strBranchName = _T("");
	BOOL bFlag = FALSE;
	int nCount = m_pListctrl->GetItemCount();
	for (int nIndex = 0 ; nIndex < nCount ; nIndex ++)
	{
		ST_BranchInfo* pBranchInfo = (ST_BranchInfo* )m_pListctrl->GetItemData(nIndex);
		if (pBranchInfo != NULL && pBranchInfo->strBranchId == stBranchInfo.strBranchId)
		{
			CString strTemp;
			strBranchName = pBranchInfo->strName.c_str();
			m_pListctrl->SetItemText(nIndex,2,stBranchInfo.strName.c_str());
			m_pListctrl->SetItemText(nIndex,3,stBranchInfo.strAddress.c_str());
			m_pListctrl->SetItemText(nIndex,4,stBranchInfo.strContact.c_str());
			m_pListctrl->SetItemText(nIndex,5,stBranchInfo.strPhone.c_str());
			m_pListctrl->SetItemText(nIndex,6,stBranchInfo.strContent.c_str());
			strTemp.Format("%d",stBranchInfo.nExtendedInfo);
			m_pListctrl->SetItemText(nIndex,7,strTemp);
			m_pListctrl->SetItemText(nIndex,8,stBranchInfo.strExtendedInfo1.c_str());
			m_pListctrl->SetItemText(nIndex,9,stBranchInfo.strExtendedInfo1.c_str());
            m_pListctrl->SetItemText(nIndex,10,stBranchInfo.strJDBRID.c_str());
            m_pListctrl->SetItemText(nIndex,11,stBranchInfo.strParentJDBRID.c_str());
            m_pListctrl->SetItemText(nIndex,12,stBranchInfo.strParentName.c_str());
            m_pListctrl->SetItemText(nIndex,13,stBranchInfo.strJDTYPE.c_str());
			//
			//memcpy(pBranchInfo,&stBranchInfo,sizeof(ST_BranchInfo));
			*pBranchInfo = stBranchInfo;
			m_pListctrl->SetItemData(nIndex,(DWORD)pBranchInfo);
			bFlag = TRUE;
			break;
		}
	}
	if (!bFlag)
	{
		return false;
	}
	//�޸������������
	if (strBranchName != stBranchInfo.strName.c_str())
	{
		CString strDes;
		strDes.Format("��%s���ѵ�¼",stBranchInfo.strName.c_str());
		DISPLAY_LOG("ͬ������",(LPCTSTR)strDes, "", "", 1);
		CString* strName = new CString(stBranchInfo.strName.c_str());
		//PostMessage((m_pListctrl->GetParent())->m_hWnd,MSG_BTN_SHOW,(WPARAM)(100),(LPARAM)(strName));
	}
	return true;
	SCATCH;
	return false;
}

bool XhBFISSyncServerRouterImp::FindBranchLog(CString strBranchInfoId)
{
	STRY;
	if (m_pListctrl == NULL)
	{
		return false;
	}
	if (strBranchInfoId == "")
	{
		TTRACE("����������־ʧ�ܣ���������IDΪ��.%s[%d] \r\n",__FUNCTION__,__LINE__);
		return false;
	}
	bool bFind = false;
	int nCount = m_pListctrl->GetItemCount();
	for (int i = 0 ;i < nCount ; i ++)
	{
		CString strTemp;
		strTemp = m_pListctrl->GetItemText(i,1);
		if (strTemp == strBranchInfoId)
		{
			bFind = true;
			break;
		}
	}
	return bFind;
	SCATCH;
	return false;
}

void XhBFISSyncServerRouterImp::SetBranchLogoutLog(ST_BranchInfo stBranchInfo)
{
	STRY;
	if (stBranchInfo.strBranchId == "")
	{
		TTRACE("��������ǳ���־ʧ�ܣ���������IDΪ��.%s[%d] \r\n",__FUNCTION__,__LINE__);
		return;
	}
	if (m_pListctrl == NULL)
	{
		return;
	}
	for (int i = 0 ; i < m_pListctrl->GetItemCount() ; i ++ )
	{
		CString strTemp;
		strTemp = m_pListctrl->GetItemText(i,1);
		if (strTemp == stBranchInfo.strBranchId.c_str())
		{
			ST_BranchInfo* pBranchInfo = (ST_BranchInfo*)m_pListctrl->GetItemData(i);
			if (pBranchInfo != NULL)
			{
				delete pBranchInfo;
				pBranchInfo = NULL;
			}
			m_pListctrl->DeleteItem(i);
			break;
		}
	}
	if (m_pListctrl->GetItemCount() == 0)
	{
		//PostMessage((m_pListctrl->GetParent())->m_hWnd,MSG_BTN_SHOW,(WPARAM)(-1),(LPARAM)0);
	}
	SCATCH;
}
void XhBFISSyncServerRouterImp::HandleReadProductInfo()
{
    if (m_vecProduceInfo.size() > 0)
    {
        vector<ST_ProduceInfo> vecProduceInfo;
        vector<ST_ProduceInfo> vecRemainProduceInfo;
        BOOL bIsRemainProduceInfo = TRUE;
        if (m_pCache && m_pCache->QueryProduceInfo(vecProduceInfo))
        {
            int i = 0;           
            for (m_vecProduceInfo[i]; i<m_vecProduceInfo.size(); ++i)
            {	
				bIsRemainProduceInfo = TRUE;
				int j = 0;
                for (vecProduceInfo[j]; j< vecProduceInfo.size(); ++j)
                {				
                    if (m_vecProduceInfo[i].strProduceCode == vecProduceInfo[j].strProduceCode)
                    {
                        vecProduceInfo[j].strName = m_vecProduceInfo[i].strName;
                        vecProduceInfo[j].strProductionType = m_vecProduceInfo[i].strProductionType;
                        vecProduceInfo[j].strRiskLevel = m_vecProduceInfo[i].strRiskLevel;
                        vecProduceInfo[j].strRiskLevelDesc = m_vecProduceInfo[i].strRiskLevelDesc;
                        vecProduceInfo[j].strRevenueType = m_vecProduceInfo[i].strRevenueType;
                        vecProduceInfo[j].strPublishBeinTime= m_vecProduceInfo[i].strPublishBeinTime;
                        vecProduceInfo[j].strPublishEndTime = m_vecProduceInfo[i].strPublishEndTime;
                        vecProduceInfo[j].nPROD_LIFECYCLE = m_vecProduceInfo[i].nPROD_LIFECYCLE;
                        vecProduceInfo[j].strApplicableCustomer = m_vecProduceInfo[i].strApplicableCustomer;
                        vecProduceInfo[j].strProductionType = m_vecProduceInfo[i].strProductionType;
                        m_pCache->ManageProduceInfo(DBO_UPDATE, vecProduceInfo[j]);
                        bIsRemainProduceInfo = FALSE;
                        break;
                    }
                }
                if (bIsRemainProduceInfo == TRUE)
                {
                    vecRemainProduceInfo.push_back(m_vecProduceInfo[i]);
                }               
            }
            m_vecProduceInfo.clear();
            i = 0;
            for (vecRemainProduceInfo[i]; i<vecRemainProduceInfo.size(); ++i)
            {
                CString strTemp = _T("");
                GuidProducer(strTemp);
                vecRemainProduceInfo[i].strProduceId = strTemp;
                m_pCache->ManageProduceInfo(DBO_ADD, vecRemainProduceInfo[i]);
            }
            vecRemainProduceInfo.clear();
        }
    }
}

void XhBFISSyncServerRouterImp::HandleReadBranchInfo()
{
    int i = 0;
	vector<ST_BranchInfo> vecBranchInfo;
	vector<ST_BranchInfo> vecLocalAllBranchInfo;
	ST_BranchInfo stInfo;
    if (m_pCache)
    {
        m_pCache->GetLocalBranchInfo(stInfo);
		m_pCache->QueryBranchInfo(vecLocalAllBranchInfo);
    }
    for (m_vecBranchInfo[i]; i<m_vecBranchInfo.size(); ++i)
    {        
        BOOL bRet = FALSE;    
		BOOL bIsHaveBranch = FALSE;
        if (m_pCache)
        {
            if(m_vecBranchInfo[i].strJDBRID == stInfo.strJDBRID)
            {           
                stInfo.strName = m_vecBranchInfo[i].strName;
                stInfo.strAddress = m_vecBranchInfo[i].strAddress;
                stInfo.strParentJDBRID = m_vecBranchInfo[i].strParentJDBRID;
                stInfo.strParentName = m_vecBranchInfo[i].strParentName;
                stInfo.strJDTYPE = m_vecBranchInfo[i].strJDTYPE;
                bRet = m_pCache->ManageBranchInfo(DBO_UPDATE, stInfo);
            }
			else if (m_vecBranchInfo[i].strJDTYPE == "1" || m_vecBranchInfo[i].strJDTYPE == "2")
			{
				for each(auto branchinfo in vecLocalAllBranchInfo)
				{
					if (m_vecBranchInfo[i].strJDBRID == branchinfo.strJDBRID)
					{					
						m_vecSubBranchInfo.push_back(branchinfo);
						bIsHaveBranch = TRUE;
						break;
					}					
				}
				if (bIsHaveBranch == FALSE)
				{
					CString strTemp = _T("");
					GuidProducer(strTemp);
					m_vecBranchInfo[i].strBranchId = strTemp;
					m_vecBranchInfo[i].strParentId = stInfo.strBranchId;
					m_vecBranchInfo[i].nIsLocal = 0;
					m_pCache->ManageBranchInfo(DBO_ADD,m_vecBranchInfo[i]);
					m_vecSubBranchInfo.push_back(m_vecBranchInfo[i]);
				}			
			}
            else
            {
                vecBranchInfo.push_back(m_vecBranchInfo[i]);
            }
        }            
    }
#if 0
	Poco::FastMutex::ScopedLock mylock(m_csLockClientContext);
	std::vector<HANDLE> vecClient;
	for each(const auto& context in m_mapClientContext)
	{        
	vecClient.push_back((HANDLE)context.first);
	}
	for each(const auto& context in vecClient)
	{
	DoSyncBranchInfo(context,m_vecBranchInfo);
	}
#endif
}
int XhBFISSyncServerRouterImp::EmployeeStopUse()
{
	vector<ST_EmployeeInfo> vecQueryEmployeeInfo;
	vector<ST_RoleInfo> vecQueryRoleInfo;
	ST_RoleInfo stSuperRoleInfo;
	//ST_RoleInfo stRoleInfo;
	ST_BranchInfo stLocalBranchInfo;
	if (m_pCache)
	{
		m_pCache->GetLocalBranchInfo(stLocalBranchInfo);
		m_pCache->QueryEmployeeInfo(vecQueryEmployeeInfo);
		m_pCache->QueryRoleInfo(vecQueryRoleInfo);
	}
	if (!vecQueryRoleInfo.empty())
	{
		int pos = 0;
		for (vecQueryRoleInfo[pos]; pos<vecQueryRoleInfo.size(); pos++)
		{
			/*if (vecQueryRoleInfo[pos].nExtendedInfo == -2 && vecQueryRoleInfo[pos].strBranchInfoId == m_stBranchInfo.strBranchId)
			{
				stRoleInfo = vecQueryRoleInfo[pos];
			}*/
			if (vecQueryRoleInfo[pos].nExtendedInfo == 0 && vecQueryRoleInfo[pos].strBranchInfoId == m_stBranchInfo.strBranchId)
			{
				stSuperRoleInfo = vecQueryRoleInfo[pos];
			}
		}
	}
	int i = 0;
	BOOL bStopUseEmp = TRUE;
	for (vecQueryEmployeeInfo[i]; i < vecQueryEmployeeInfo.size(); ++i)
	{
		if (vecQueryEmployeeInfo[i].strBranchId == stLocalBranchInfo.strBranchId &&
			vecQueryEmployeeInfo[i].strRoleId != stSuperRoleInfo.strRoleInfoId &&
			vecQueryEmployeeInfo[i].nExtendedInfo != 1)
		{
			int j = 0;
			bStopUseEmp = TRUE;
			for(m_vecEmployeeInfo[j]; j < m_vecEmployeeInfo.size(); ++j)
			{
				if (m_vecEmployeeInfo[j].strTLNUM == vecQueryEmployeeInfo[i].strTLNUM )
				{
					bStopUseEmp = FALSE;
					break;
				}
			}
			if (bStopUseEmp == TRUE)
			{
				//vecQueryEmployeeInfo[i].nFlag = 1;
				//m_pCache->ManageEmployeeInfo(DBO_UPDATE, vecQueryEmployeeInfo[i]);		
			}
		}	
	}
	return 1;
}

int XhBFISSyncServerRouterImp::HanaleSubBranchEmployInfo()
{
	STRY;
	vector<ST_EmployeeInfo> vecQueryEmployeeInfo;
	vector<ST_RoleInfo> vecQueryRoleInfo;
	ST_RoleInfo stRoleInfo;
	if (m_pCache)
	{
		m_pCache->QueryEmployeeInfo(vecQueryEmployeeInfo);
		m_pCache->QueryRoleInfo(vecQueryRoleInfo);
	}
	int i = 0;
	BOOL bIsExistEmp = FALSE;	
	if (!vecQueryRoleInfo.empty())
	{
		int pos = 0;
		for (vecQueryRoleInfo[pos]; pos<vecQueryRoleInfo.size(); pos++)
		{
			if (vecQueryRoleInfo[pos].nExtendedInfo == -2 && vecQueryRoleInfo[pos].strBranchInfoId == m_stBranchInfo.strBranchId)
			{
				stRoleInfo = vecQueryRoleInfo[pos];
			}
		}
	}
	for each(auto employee in m_vecEmployeeInfo)
	{  
		for each(auto branchinfo in m_vecSubBranchInfo)
		{    
			if (employee.strJDBRID == branchinfo.strJDBRID)
			{
				int j = 0;
				bIsExistEmp = FALSE;
				for (vecQueryEmployeeInfo[j]; j<vecQueryEmployeeInfo.size(); j++)
				{
					if(employee.strTLNUM == vecQueryEmployeeInfo[j].strTLNUM)
					{
						vecQueryEmployeeInfo[j].strGW        = employee.strGW;       
						vecQueryEmployeeInfo[j].strSTS       = employee.strSTS;       
						vecQueryEmployeeInfo[j].strTLNUM     = employee.strTLNUM;     
						vecQueryEmployeeInfo[j].strUSERNAME  = employee.strUSERNAME; 
						vecQueryEmployeeInfo[j].strTLINST    = employee.strTLINST;    
						vecQueryEmployeeInfo[j].strROLENAME  = employee.strROLENAME; 
						vecQueryEmployeeInfo[j].strUSERSTATUS =employee.strUSERSTATUS;
						vecQueryEmployeeInfo[j].strCardId    = employee.strCardId; 
						m_pCache->ManageEmployeeInfo(DBO_UPDATE, vecQueryEmployeeInfo[j]);
						bIsExistEmp = TRUE;
						break;
					}               
				} 
				if (bIsExistEmp == FALSE)
				{
					CString strTemp = _T("");
					GuidProducer(strTemp);
					employee.strEmployeeId = strTemp;
					employee.strBranchId = branchinfo.strBranchId;
					employee.strRoleId = stRoleInfo.strRoleInfoId;
					BOOL bRet = m_pCache->ManageEmployeeInfoAndSocUser(DBO_ADD,employee);
					if (bRet)
					{
						BOOL bRet = m_pCache->ManageEmployeeInfo(DBO_ADD,employee);
						//m_pCache->ManageEmployeeInfoAndSocUser(DBO_ADD,employee);
					}
				}             	
			}	
		}
	}
	return 1;
	SCATCH;
	return -1;
}
void XhBFISSyncServerRouterImp::HandleReadEmployInfo()
{
    int i = 0;
	vector<ST_EmployeeInfo> vecEmployeeInfo;
    vector<ST_EmployeeInfo> vecQueryEmployeeInfo;
    vector<ST_RoleInfo> vecQueryRoleInfo;
	ST_RoleInfo stSuperRoleInfo;
    ST_RoleInfo stRoleInfo;
    ST_BranchInfo stInfo;
    if (m_pCache)
    {
        m_pCache->GetLocalBranchInfo(stInfo);
        m_pCache->QueryEmployeeInfo(vecQueryEmployeeInfo);
        m_pCache->QueryRoleInfo(vecQueryRoleInfo);
    }
	if (!vecQueryRoleInfo.empty())
	{
		int pos = 0;
		for (vecQueryRoleInfo[pos]; pos<vecQueryRoleInfo.size(); pos++)
		{
			if (vecQueryRoleInfo[pos].nExtendedInfo == -2 && vecQueryRoleInfo[pos].strBranchInfoId == m_stBranchInfo.strBranchId)
			{
				stRoleInfo = vecQueryRoleInfo[pos];
			}
			if (vecQueryRoleInfo[pos].nExtendedInfo == 0 && vecQueryRoleInfo[pos].strBranchInfoId == m_stBranchInfo.strBranchId)
			{
				stSuperRoleInfo = vecQueryRoleInfo[pos];
			}
		}
	}
	//EmployeeStopUse();
	//HanaleSubBranchEmployInfo();
    for (m_vecEmployeeInfo[i]; i<m_vecEmployeeInfo.size(); ++i)
    {        
        BOOL bRet = FALSE;   
        BOOL IsExistEmp = FALSE;
        if (m_pCache)
        {
            if(m_vecEmployeeInfo[i].strJDBRID == stInfo.strJDBRID)
            {      
                 for (int j = 0; j<vecQueryEmployeeInfo.size(); j++)
                 {
                     if(m_vecEmployeeInfo[i].strTLNUM == vecQueryEmployeeInfo[j].strTLNUM && vecQueryEmployeeInfo[j].strCardId != "-1"
						 && m_vecEmployeeInfo[i].strTLNUM !="")
                     {
                         vecQueryEmployeeInfo[j].strGW        = m_vecEmployeeInfo[i].strGW;       
                         vecQueryEmployeeInfo[j].strSTS       = m_vecEmployeeInfo[i].strSTS;       
                         vecQueryEmployeeInfo[j].strTLNUM     = m_vecEmployeeInfo[i].strTLNUM;     
                         vecQueryEmployeeInfo[j].strUSERNAME  = m_vecEmployeeInfo[i].strUSERNAME; 
                         vecQueryEmployeeInfo[j].strTLINST    = m_vecEmployeeInfo[i].strTLINST;    
                         vecQueryEmployeeInfo[j].strROLENAME  = m_vecEmployeeInfo[i].strROLENAME; 
                         vecQueryEmployeeInfo[j].strUSERSTATUS =m_vecEmployeeInfo[i].strUSERSTATUS;
						 if (m_vecEmployeeInfo[i].strTEL != "")
						 {
							 vecQueryEmployeeInfo[j].strTEL = m_vecEmployeeInfo[i].strTEL;
						 }
                         //vecQueryEmployeeInfo[j].strCardId    = m_vecEmployeeInfo[i].strCardId; 
                         bRet = m_pCache->ManageEmployeeInfo(DBO_UPDATE, vecQueryEmployeeInfo[j]);
                         IsExistEmp = TRUE;
						 if (m_vecEmployeeInfo[i].strTLINST != "2" || m_vecEmployeeInfo[i].strUSERSTATUS != "N")
						 {
							 SFTRACE("EmployeeInfo", "����Ա����Ϣ GW[%s] STS[%s] TLNUM[%s] USERNAME[%s] TLINST[%s] ROLENAME[%s] USERSTATUS[%s] JDBRID[%s] \r\n",\
								 m_vecEmployeeInfo[i].strGW.c_str(), m_vecEmployeeInfo[i].strSTS.c_str(), m_vecEmployeeInfo[i].strTLNUM.c_str(), m_vecEmployeeInfo[i].strUSERNAME.c_str(),\
								 m_vecEmployeeInfo[i].strTLINST.c_str(), m_vecEmployeeInfo[i].strROLENAME.c_str(), m_vecEmployeeInfo[i].strUSERSTATUS.c_str(), m_vecEmployeeInfo[i].strJDBRID.c_str());
						 }
                         break;
                     }               
                 } 
                 if (IsExistEmp == FALSE)
                 {
                     CString strTemp = _T("");
                     GuidProducer(strTemp);
                     m_vecEmployeeInfo[i].strEmployeeId = strTemp;
                     m_vecEmployeeInfo[i].strBranchId = stInfo.strBranchId;
                     m_vecEmployeeInfo[i].strRoleId = stRoleInfo.strRoleInfoId;
					 bRet = m_pCache->ManageEmployeeInfoAndSocUser(DBO_ADD,m_vecEmployeeInfo[i]);
                     if (bRet)
                     {
						 m_pCache->ManageEmployeeInfo(DBO_ADD, m_vecEmployeeInfo[i]);
                     }
					 if (m_vecEmployeeInfo[i].strTLINST != "2" || m_vecEmployeeInfo[i].strUSERSTATUS != "N")
					 {
						 SFTRACE("EmployeeInfo", "����Ա����Ϣ GW[%s] STS[%s] TLNUM[%s] USERNAME[%s] TLINST[%s] ROLENAME[%s] USERSTATUS[%s] JDBRID[%s]\r\n", \
							 m_vecEmployeeInfo[i].strGW.c_str(), m_vecEmployeeInfo[i].strSTS.c_str(), m_vecEmployeeInfo[i].strTLNUM.c_str(), m_vecEmployeeInfo[i].strUSERNAME.c_str(), \
							 m_vecEmployeeInfo[i].strTLINST.c_str(), m_vecEmployeeInfo[i].strROLENAME.c_str(), m_vecEmployeeInfo[i].strUSERSTATUS.c_str(), m_vecEmployeeInfo[i].strJDBRID.c_str());
					 }
                 }             
            }
            else
            {
                vecEmployeeInfo.push_back(m_vecEmployeeInfo[i]);
            }
        }      
    }
#if 0
	Poco::FastMutex::ScopedLock mylock(m_csLockClientContext);
	std::vector<HANDLE> vecClient;
	for each(const auto& context in m_mapClientContext)
	{
	vecClient.push_back((HANDLE)context.first);
	}
	for each(const auto& context in vecClient)
	{
	DoSyncEmployeeInfo(context,vecEmployeeInfo);
#endif
}
void XhBFISSyncServerRouterImp::HandleUserPurview()
{
	STRY;
	vector<ST_BranchInfo> vecAllBranchInfo;
	vector<ST_BranchInfo> vecUpBranchInfo;
	vector<ST_EmployeeInfo> vecAllEmployee;
	vector<ST_EmployeeInfo> vecUpEmployeeInfo;
	if (m_pCache)
	{
		m_pCache->QueryBranchInfo(vecAllBranchInfo);
		m_pCache->QueryEmployeeInfo(vecAllEmployee);
	}
	for each(auto branchinfo in vecAllBranchInfo)
	{
		if (branchinfo.strJDTYPE == "2" || branchinfo.strParentJDBRID == "")
		{
			vecUpBranchInfo.push_back(branchinfo);
		}
	}
	int i = 0;
	for (vecAllEmployee[i]; i<vecAllEmployee.size(); ++i)
	{        
		for each(auto branchinfo in vecUpBranchInfo)
		{
			if(vecAllEmployee[i].strJDBRID == branchinfo.strJDBRID)
			{
				vecUpEmployeeInfo.push_back(vecAllEmployee[i]);
			}
		}
	}
	if (m_pCache && m_pCache->UpdateUserPermission(vecUpEmployeeInfo))
	{
		TTRACE("�����ϼ��û�Ȩ��");
	}
	SCATCH;
}
BOOL XhBFISSyncServerRouterImp::PraseURL(CString& strFtpPath,CString& strFtpAdd,CString& strFtpUser,CString& strFtpPass,int& nFtpPort)
{
	STRY;
    vector<string> vecKindList;
    vector<string> vecPassAndAddress;
    //string strURL = " ftp://dsp:dsp@10.6.30.99:21/test ";
    //string strURL = URL.substr(6);
	string strURL = m_stBasicSetting.strSynchroInfoPath.substr(6);
	strURL.erase(strURL.find_last_not_of(' ') + 1, string::npos);    //ȥ���ַ���ĩβ�ո�    
	strURL.erase(0, strURL.find_first_not_of(' '));					 //ȥ���ַ����׿ո� 
	//if (m_strFtpPath == strURL)
    //{
    //    return FALSE;
    //}
    //char cURL[200];
    //strcpy(cURL,strURL.c_str());
    //m_strFtpPath = cURL;    
    char* pLine;
    char* decoll = ":";
    char* decoll1 = "@";
    if (strURL == "")
    {
		DISPLAY_LOG("ͬ��ģ��","����FTP��URLΪ��","","",0);
        TTRACE("����FTP��URLΪ��");
        return FALSE;
    }
    pLine = strtok ((char*)strURL.c_str(),decoll);
    while(pLine != NULL)
    { 
        vecKindList.push_back(pLine);
        pLine = strtok(NULL,decoll);
    }
    if (vecKindList.size() < 3)
    {
		DISPLAY_LOG("ͬ��ģ��","����FTP��URL����ȷ","","",0);
        TTRACE("����FTP��URL����ȷ");
        return FALSE;
    }
    strFtpUser.Format("%s",vecKindList[0].c_str());
    pLine = strtok ((char*)vecKindList[1].c_str(),decoll1);
    while(pLine != NULL)
    { 
        vecPassAndAddress.push_back(pLine);
        pLine = strtok(NULL,decoll1);
    }
    if (vecPassAndAddress.size() < 2)
    {
        DISPLAY_LOG("ͬ��ģ��","����FTP��URL����ȷ","","",0);
        return FALSE;
    }
    strFtpPass.Format("%s",vecPassAndAddress[0].c_str());
    strFtpAdd.Format("%s",vecPassAndAddress[1].c_str());
    string ftpPortAndPath = vecKindList[2];
    int pos = ftpPortAndPath.find('/');
	if (pos <= 0)
	{
		DISPLAY_LOG("ͬ��ģ��","����FTP��URL����ȷ","","",0);
		return FALSE;
	}
    strFtpPath.Format("%s",ftpPortAndPath.substr(pos+1).c_str());
    nFtpPort = atoi(ftpPortAndPath.erase(pos,strFtpPath.GetLength()+1).c_str());
    return TRUE;
	SCATCH;
	return FALSE;
}
int CheckDir(char* Dir)  
{  
	FILE *fp = NULL;  
	char TempDir[200];  
	memset(TempDir,'\0',sizeof(TempDir));  
	sprintf(TempDir,Dir);  
	strcat(TempDir,"\\");  
	strcat(TempDir,".temp.fortest");  
	fp = fopen(TempDir,"w");  
	if (!fp)  
	{  
		if(_mkdir(Dir)==0)  
		{  
			return 1;//�ļ��д����ɹ�  
		}  
		else  
		{  
			return -1;//can not make a dir;  
		}  
	}  
	else  
	{  
		fclose(fp);  
	}  
	return 0;  
} 
BOOL XhBFISSyncServerRouterImp::GetFileFromFTP(CString LocalPath)
{  
    int nRet = FALSE;
    CString sErr; 
    CString strFtpPath;  
    CString strFtpAdd;
    CString strFtpUser;
    CString strFtpPass;
    int nFtpPort;    
    CString sTemp ;
    CString sLocalTemp ;
    CString sTempFtpPath;
    nRet = PraseURL( strFtpPath,strFtpAdd,strFtpUser,strFtpPass,nFtpPort);
	if (nRet == FALSE)
	{
		DISPLAY_LOG("ͬ��ģ��","����FTP URLʧ��","","",0);
		return nRet;
	}
	time_t lastTime  = time(NULL) - 86400;
	struct tm *tmpter1 = localtime(&lastTime);
	char strTime1[8] ={};
	
	sprintf(strTime1,"%04d%02d%02d",tmpter1->tm_year+1900,tmpter1->tm_mon+1,tmpter1->tm_mday);
	CString strDateFtpPath = "/"+strFtpPath + "/" + strTime1;
	TTRACE("����ftp��·��Ϊ��%s \r\n",strDateFtpPath);
	char szTemp[128];
	memset(szTemp, 0, sizeof(LocalPath));
	strcpy(szTemp, LocalPath.GetBuffer(LocalPath.GetLength()));
	nRet = CheckDir(szTemp);
	if (nRet < 0)
	{
		DISPLAY_LOG("ͬ��ģ��","������ʱ�ļ���ʧ��","","",0);
	}
    CInternetSession  pInternetCon(AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS); 
    CFtpConnection *pFtpCon ;
    try 
    {
        pFtpCon =pInternetCon.GetFtpConnection(strFtpAdd,strFtpUser,strFtpPass,21/*nFtpPort*/);
        if ( pFtpCon != NULL)
        {
            CFtpFileFind FtpFinder( pFtpCon ) ;
            BOOL bWork = FtpFinder.FindFile( strDateFtpPath );
			if (bWork == FALSE)
			{
				DISPLAY_LOG("FTP","����FTP��·������","","",0)
				TTRACE("����FTP��·������");
				return FALSE;
			}
            while ( bWork )
            {
REREADNEXTFILE:
                bWork = FtpFinder.FindNextFile();
                if ( FtpFinder.IsDots() ) 
                    continue;
                if(FtpFinder.IsDirectory() )
                {  
                    //��Ŀ¼
                    sTemp.Empty() ;
                    sTemp = FtpFinder.GetFileName();
                    sTempFtpPath.Empty() ;
                    sTempFtpPath = strDateFtpPath.Left( strDateFtpPath.GetLength() - 3 )  ;
                    sTempFtpPath += sTemp + "//*" ;
                    sLocalTemp.Empty() ;
                    sLocalTemp = LocalPath + "//" + sTemp ;
                    CFileStatus rStatus;
                    if(!(CFile::GetStatus(sLocalTemp, rStatus)))
                    {       
                        LPSECURITY_ATTRIBUTES lpSecurityAttributes;
                        if(!CreateDirectoryA((LPCTSTR)sLocalTemp,NULL))
                        {
                            DWORD dErr = GetLastError() ;
                            sErr.Format( "������Ŀ¼ʧ��: ERROR  %d" ,dErr ) ;
                            return FALSE ; 
                        }
                    }
                    GetFileFromFTP(sLocalTemp) ;
                }
                else
                {
                    sTemp.Empty() ;
                    sTemp = FtpFinder.GetFileName();
					if(m_bManualSync == FALSE)
					{
						for each(auto filename in m_vecFileName)
						{
							if (sTemp == filename.c_str())
							{
								goto REREADNEXTFILE;
							}
						}
					}			
                    sLocalTemp.Empty() ;
                    sLocalTemp = LocalPath + "//" + sTemp ;
                    //sTemp.Empty() ;
                    //sTemp = FtpFinder.GetFilePath();
					CString sTemp1 = strDateFtpPath+"//"+ sTemp;
                    CFileStatus   rStatus;
                    if( !( CFile::GetStatus( sLocalTemp, rStatus ) ) )
                    {
                        //�ļ������ڣ�����֮
                        if( !( pFtpCon->GetFile( sTemp1, sLocalTemp, true, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_BINARY, 1) ) )
                        {
                            //����ʧ��
							DISPLAY_LOG("FTP","�ļ����ص�����ʧ��","","",0);
							SFTRACE("SyncLog","�ļ�%s����ʧ�� \r\n",sTemp);
                            DWORD dErr = GetLastError();
                            sErr.Format( "����ʧ��: ERROR  %d" ,dErr ) ;
                            return FALSE ;
                        } 
						//else
						//{
							//SFTRACE("SyncLog","�ļ�%sͬ���ɹ� \r\n",sTemp);
						//}
                    }
                }
            }
            FtpFinder.Close() ;
        }
		else
		{
			TTRACE("����ftpʧ�ܣ�ʧ�ܵ�·��Ϊ��%s",strDateFtpPath);
		}
    }
    catch (CInternetException * pEx)
    {
        TCHAR szError[1024];
        pEx->GetErrorMessage(szError,1024) ;
        sErr.Format( "����FTPʧ��:%s", pEx ) ;
        pEx->Delete();
        pFtpCon=NULL;
        return FALSE ;
    }
    return TRUE ;
}

BOOL XhBFISSyncServerRouterImp::PraseGetKeyValueData()
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
        if(m_pCache->QueryKeyValueInfoByTypeAndCode("PasswordStrategy","",vecKeyValueInfo))
        {
            if (vecKeyValueInfo.empty())
            {
                return	FALSE;
            }
            CString strxml;
			strxml.Format("%s",vecKeyValueInfo[0].strValue.c_str());
            iCMSP_XmlParser XmlParser;
            XmlParser.SetDoc(strxml, strxml.GetLength());
            if (XmlParser.FindElem("PwdSet"))
            {
                XmlParser.IntoElem();
                if (XmlParser.FindElem("TimeoutLockChecked"))
                {
                    m_stPasswordStrategy.nTimeoutLockChecked = XmlParser.GetDataInt();
                }
                if (XmlParser.FindElem("PWDValidTime"))
                {
                    m_stPasswordStrategy.strPWDValidTime = XmlParser.GetData();
                }
                if (XmlParser.FindElem("RemindAdvanceTime"))
                {
                    m_stPasswordStrategy.strRemindAdvanceTime = XmlParser.GetData();
                } 
                if (XmlParser.FindElem("ErrorLockChecked"))
                {
                    m_stPasswordStrategy.nErrorLockChecked = XmlParser.GetDataInt();
                } 
                if (XmlParser.FindElem("MaxErrorTimes"))
                {
                    m_stPasswordStrategy.nMaxErrorTimes = XmlParser.GetDataInt();
                } 
                if (XmlParser.FindElem("ForcedModifyChecked"))
                {
                    m_stPasswordStrategy.nForcedModifyChecked = XmlParser.GetDataInt();
                } 
                if (XmlParser.FindElem("InitialPWD"))
                {
                    m_stPasswordStrategy.strInitialPWD = XmlParser.GetData();
                } 
            }
            vecKeyValueInfo.clear();
        }
		if (m_stPasswordStrategy.strInitialPWD == "" || m_stBasicSetting.strSynchroInfoPath == "")
		{
			return FALSE;
		}
    }
	return TRUE;
	SCATCH;
	return FALSE;
}
std::string UTF8ToGDB(const char* str)
{
    std::string result;
    WCHAR *strSrc;
    TCHAR *szRes;

    //�����ʱ�����Ĵ�С
    int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    strSrc = new WCHAR[i+1];
    MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

    //�����ʱ�����Ĵ�С
    i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
    szRes = new TCHAR[i+1];
    WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

    result = szRes;
    delete []strSrc;
    delete []szRes;
    return result;
}
vector<string> ReadFindCltFile(string fileName)
{
    vector<string> vecFileLineContentList;
    vector<string> vecFileContentList;
    vector<string> vecCtlFileNameList;

    ifstream iReader(fileName);
    string strTemp((std::istreambuf_iterator<char>(iReader)),  
        std::istreambuf_iterator<char>());
    char* pLine;
    char decollEnterAndLF[3] = {10,13};
    pLine = strtok((char*)strTemp.c_str(),decollEnterAndLF);
    while(pLine != NULL)
    { 
        vecFileLineContentList.push_back(pLine);
        pLine = strtok(NULL,decollEnterAndLF);
    }
    char* pCtl;
    char decollEsc[2] = {27};
    int i = 0;
    for (vecFileLineContentList[i];i<vecFileLineContentList.size();++i)
    {
        char tempLine[1024] = {};
        pCtl = strtok ((char*)vecFileLineContentList[i].c_str(),decollEsc);
        while(pCtl != NULL)
        { 
            vecFileContentList.push_back(pCtl);
            pCtl = strtok(NULL,decollEsc);
        }
    }
    int j = 0;
    for (vecFileContentList[j];j < vecFileContentList.size(); ++j)
    {   
        int IsCtlFile = vecFileContentList[j].find(".dat");
        if (IsCtlFile > 0)
        {
            vecCtlFileNameList.push_back(vecFileContentList[j]);
        }
    }
    return vecCtlFileNameList;
}


vector<string> FindOppositeDatFile(vector<string> vecAllFileList,vector<string> vecDatFileNameList)
{
    int i = 0;
    int j = 0;
    vector<string> vecFindDatFileNameList;
    for (vecDatFileNameList[i];i<vecDatFileNameList.size();++i)
    {
        for (vecAllFileList[j];j<vecAllFileList.size();++j)
        {
            if (vecDatFileNameList[i] == vecAllFileList[j])
            {
                vecFindDatFileNameList.push_back(vecDatFileNameList[i]);
            }
        }
    }
    return vecFindDatFileNameList;
}
vector<string> strtokDefine(char* strStr,const char decoll)
{
    vector<string> vecDestStr;
READHEADER: 
    char* strDest = strStr;
    while(*strStr)
    {
        if ( *strStr++ == decoll)
        {
            *(strStr-1) = '\0'; 
            vecDestStr.push_back(strDest);
            goto READHEADER; 
        }          
    }
	if (strDest != NULL)
    {
		vecDestStr.push_back(strDest);
    }
	//vecDestStr.push_back(strStr-1);     
    return vecDestStr;
}
void XhBFISSyncServerRouterImp::FileContentPraseToBranchInfo(vector<string> vecFilePathList)
{
    int i = 0;
    int j = 0;
    vector<string> vecFileLineContentList;
    vector<string> vecFileContentList;
    for (vecFilePathList[0];i<vecFilePathList.size();++i)
    {
        fstream iReader(vecFilePathList[0]);
        string strTempRead((std::istreambuf_iterator<char>(iReader)),  
            std::istreambuf_iterator<char>());  
        string strTemp = UTF8ToGDB(strTempRead.c_str());
        char* pLine;
        char decollEnterAndLF[3] = {10,13};
        pLine = strtok ((char*)strTemp.c_str(),decollEnterAndLF);
        while(pLine != NULL)
        { 
            vecFileLineContentList.push_back(pLine);
            pLine = strtok(NULL,decollEnterAndLF);
        }
    }
    for (vecFileLineContentList[j];j < vecFileLineContentList.size();++j)
    {
        char deEsc = 27;
        vecFileContentList = strtokDefine((char*)vecFileLineContentList[j].c_str(),deEsc);
		if (vecFileContentList.size() == 6)
		{
			ST_BranchInfo stBranchInfo;
			stBranchInfo.strJDBRID = vecFileContentList[0];
			stBranchInfo.strName = vecFileContentList[1];
			stBranchInfo.strAddress = vecFileContentList[2];
			stBranchInfo.strParentJDBRID = vecFileContentList[3];
			stBranchInfo.strParentName = vecFileContentList[4];
			stBranchInfo.strJDTYPE = vecFileContentList[5];
			m_vecBranchInfo.push_back(stBranchInfo);
		}     
        vecFileContentList.clear();
    } 
	VirturlBranchInfo();
}
int XhBFISSyncServerRouterImp::VirturlBranchInfo()
{
	STRY
	vector<ST_BranchInfo> vecBranchInfo;
	for each(auto branchinfo in m_vecBranchInfo)
	{
		if (branchinfo.strJDTYPE == "2" && branchinfo.strJDBRID != "02001")
		{
			vecBranchInfo.push_back(branchinfo);
		}
	}
	int i = 0;
	for ( m_vecBranchInfo[i]; i<m_vecBranchInfo.size(); ++i)
	{
		for each (auto stinfo in vecBranchInfo)
		{
			if (m_vecBranchInfo[i].strJDBRID == stinfo.strJDBRID)
			{
				m_vecBranchInfo[i].strJDTYPE = "3";
				m_vecBranchInfo[i].strParentJDBRID = stinfo.strJDBRID + "a";
				m_vecBranchInfo[i].strName = stinfo.strName + "����";
			}
			if(m_vecBranchInfo[i].strParentJDBRID == stinfo.strJDBRID)
			{
				m_vecBranchInfo[i].strParentJDBRID = stinfo.strJDBRID + "a";
			}
		}
	}
	for each (auto stinfo in vecBranchInfo)
	{
		stinfo.strJDBRID = stinfo.strJDBRID + "a";
		m_vecBranchInfo.push_back(stinfo);
	}
	return TRUE;
	SCATCH;
	return FALSE;
}
string StrToTime(string strSrc)
{
	STRY;
	CString strTime;
	if (strSrc != "")
	{
		strTime.Format("%s-%s-%s 00:00:00",strSrc.substr(0,4).c_str(),strSrc.substr(4,2).c_str(),strSrc.substr(6,2).c_str());
	}	
	return strTime.GetBuffer(0);
	SCATCH;
	return NULL;
}
void XhBFISSyncServerRouterImp::FileContentPraseToFinancProduceInfo(vector<string> vecFilePathList)
{
    int i = 0;
    int j = 0;
	BOOL bIsSame = FALSE;
    vector<string> vecFileLineContentList;
    vector<string> vecFileContentList;
    for (vecFilePathList[0];i<vecFilePathList.size();++i)
    {
        fstream iReader(vecFilePathList[0]);
        string strTempRead((std::istreambuf_iterator<char>(iReader)),  
            std::istreambuf_iterator<char>());  
        string strTemp = UTF8ToGDB(strTempRead.c_str()); 
        char* pLine;
        char decollEnterAndLF[3] = {10,13};
        pLine = strtok ((char*)strTemp.c_str(),decollEnterAndLF);
        while(pLine != NULL)
        { 
            vecFileLineContentList.push_back(pLine);
            pLine = strtok(NULL,decollEnterAndLF);
        }
    }
    for (vecFileLineContentList[j];j < vecFileLineContentList.size();++j)
    {      
        char deEsc = 27;
        vecFileContentList = strtokDefine((char*)vecFileLineContentList[j].c_str(),deEsc);       
		if (vecFileContentList.size() == 9)
		{
			ST_ProduceInfo stProduceInfo;
			stProduceInfo.strProduceCode = vecFileContentList[0];
			stProduceInfo.strName = vecFileContentList[1];
			stProduceInfo.strRiskLevel = vecFileContentList[2];
			stProduceInfo.strPublishBeinTime = StrToTime(vecFileContentList[3]);
			stProduceInfo.strPublishEndTime = StrToTime(vecFileContentList[4]);
			stProduceInfo.nPROD_LIFECYCLE = atoi(vecFileContentList[5].c_str());
			stProduceInfo.strApplicableCustomer = vecFileContentList[6];
			stProduceInfo.strRevenueType = vecFileContentList[7];
			stProduceInfo.strProductionType = vecFileContentList[8];
			stProduceInfo.nType = 2;
			if (m_vecProduceInfo.empty())
			{
				m_vecProduceInfo.push_back(stProduceInfo);
			}
			else
			{
				bIsSame = FALSE;
				for each(auto produceinfo in m_vecProduceInfo)
				{
					if (produceinfo.strProduceCode == stProduceInfo.strProduceCode)
					{
						bIsSame = TRUE;
						break;
					}
				}
				if(bIsSame == FALSE)
				{
					m_vecProduceInfo.push_back(stProduceInfo);
				}			
			}
			//ZeroMemory(&stProduceInfo,sizeof(stProduceInfo));;
		}        
        vecFileContentList.clear();
    }
}
void XhBFISSyncServerRouterImp::FileContentPraseToFundProduceInfo(vector<string> vecFilePathList)
{
    int i = 0;
    int j = 0;
	BOOL bIsSame = FALSE;
    vector<string> vecFileLineContentList;
    vector<string> vecFileContentList;
    for (vecFilePathList[0];i<vecFilePathList.size();++i)
    {
        fstream iReader(vecFilePathList[0]);
        string strTempRead((std::istreambuf_iterator<char>(iReader)),  
            std::istreambuf_iterator<char>());  
        string strTemp = UTF8ToGDB(strTempRead.c_str());  
        char* pLine;
        char decollEnterAndLF[3] = {10,13};
        pLine = strtok ((char*)strTemp.c_str(),decollEnterAndLF);
        while(pLine != NULL)
        { 
            vecFileLineContentList.push_back(pLine);
            pLine = strtok(NULL,decollEnterAndLF);
        }
    }   
    for (vecFileLineContentList[j];j < vecFileLineContentList.size();++j)
    {
        char deEsc = 27;
        vecFileContentList = strtokDefine((char*)vecFileLineContentList[j].c_str(),deEsc);
		if (vecFileContentList.size() == 6)
		{
			ST_ProduceInfo stProduceInfo;
			stProduceInfo.strProduceCode = vecFileContentList[0];
			stProduceInfo.strName = vecFileContentList[1];
			stProduceInfo.strProductionType = vecFileContentList[2];
			stProduceInfo.strRiskLevel = vecFileContentList[3];
			stProduceInfo.strRiskLevelDesc = vecFileContentList[4];
			stProduceInfo.strRevenueType = vecFileContentList[5];
			CTime time = CTime::GetCurrentTime(); 
			CString strTime = time.Format("%Y-%m-%d %H:%M:%S");
			stProduceInfo.strPublishBeinTime = strTime;
			stProduceInfo.strPublishEndTime = strTime;
			stProduceInfo.nType = 1;
			if (m_vecProduceInfo.empty())
			{
				m_vecProduceInfo.push_back(stProduceInfo);
			}
			else
			{
				bIsSame = FALSE;
				for each(auto produceinfo in m_vecProduceInfo)
				{
					if (produceinfo.strProduceCode == stProduceInfo.strProduceCode)
					{
						bIsSame = TRUE;
						break;
					}
				}
				if(bIsSame == FALSE)
				{
					m_vecProduceInfo.push_back(stProduceInfo);
				}			
			}
			//ZeroMemory(&stProduceInfo,sizeof(stProduceInfo));
		}        
        vecFileContentList.clear();
    }
}
void XhBFISSyncServerRouterImp::FileContentPraseToKernelEmployeeInfo(vector<std::string> vecFilePathList)
{
    int i = 0;
    int j = 0;
	BOOL bIsSame = FALSE;
    vector<string> vecFileLineContentList;
    vector<string> vecFileContentList;
	vector<ST_BranchInfo> vecInfo;
	if (m_pCache)
		m_pCache->QueryBranchInfo(vecInfo);
	int branch_info_size = vecInfo.size();
    for (vecFilePathList[0];i<vecFilePathList.size();++i)
    {
        fstream iReader(vecFilePathList[0]);
        string strTempRead((std::istreambuf_iterator<char>(iReader)),  
            std::istreambuf_iterator<char>());  
        string strTemp = UTF8ToGDB(strTempRead.c_str());  
        char* pLine;
        char decollEnterAndLF[3] = {10,13};
        pLine = strtok ((char*)strTemp.c_str(),decollEnterAndLF);
        while(pLine != NULL)
        { 
            vecFileLineContentList.push_back(pLine);
            pLine = strtok(NULL,decollEnterAndLF);
        }
    }   
    for (vecFileLineContentList[j];j < vecFileLineContentList.size();++j)
    {
        char deEsc = 27;
        vecFileContentList = strtokDefine((char*)vecFileLineContentList[j].c_str(),deEsc);      
		if (vecFileContentList.size() == 7)
		{
			ST_EmployeeInfo stEmployeeInfo;
			stEmployeeInfo.strJDBRID = vecFileContentList[0];
			//stEmployeeInfo.strTEL = vecFileContentList[1];
			stEmployeeInfo.strGW = vecFileContentList[2];
			stEmployeeInfo.strSTS = vecFileContentList[3];
			stEmployeeInfo.strTLNUM = vecFileContentList[4];
			stEmployeeInfo.strUSERNAME= vecFileContentList[5];
			stEmployeeInfo.strTLINST = vecFileContentList[6];
			stEmployeeInfo.strName = stEmployeeInfo.strTLNUM;
			CTime time = CTime::GetCurrentTime(); 
			CString strTime = time.Format("%Y-%m-%d %H:%M:%S");
			stEmployeeInfo.stPasswordEidtTime = strTime;

			for (int pos = 0; pos < branch_info_size; ++pos)
			{
				if (vecInfo[pos].strJDBRID.compare(stEmployeeInfo.strJDBRID) == 0)
				{
					stEmployeeInfo.strBranchId = vecInfo[pos].strBranchId;
					break;
				}
			}

			stEmployeeInfo.strPassword = m_stPasswordStrategy.strInitialPWD;     
			if (m_vecEmployeeInfo.empty())
			{
				m_vecEmployeeInfo.push_back(stEmployeeInfo);
			}
			else
			{
				bIsSame = FALSE;
				int i = 0;
				for (m_vecEmployeeInfo[i];i< m_vecEmployeeInfo.size();++i)
				{
					if (stEmployeeInfo.strTLNUM == m_vecEmployeeInfo[i].strTLNUM && m_vecEmployeeInfo[i].strJDBRID == stEmployeeInfo.strJDBRID)
					{
						//m_vecEmployeeInfo[i].strGW = stEmployeeInfo.strGW;
						//m_vecEmployeeInfo[i].strSTS = stEmployeeInfo.strSTS;
						//m_vecEmployeeInfo[i].strTLINST = stEmployeeInfo.strTLINST;
						bIsSame = TRUE;
						break;
					}
				}
				if(bIsSame == FALSE)
				{
					m_vecEmployeeInfo.push_back(stEmployeeInfo);
				}			
			}
			ZeroMemory(&stEmployeeInfo,sizeof(stEmployeeInfo));;
		}            
		else
		{
			SFTRACE("EmployeeInfo", "Ftp KernelEmployeeԱ�����ݴ��� [%s] \r\n", vecFileLineContentList[j].c_str());
		}
        vecFileContentList.clear();
    }
}
void XhBFISSyncServerRouterImp::FileContentPraseToFinancEmployeeInfo(vector<std::string> vecFilePathList)
{
    int i = 0;
    int j = 0;
    vector<string> vecFileLineContentList;
    vector<string> vecFileContentList;
	BOOL bIsSame = FALSE;
	vector<ST_BranchInfo> vecInfo;
	if (m_pCache)
		m_pCache->QueryBranchInfo(vecInfo);

	int branch_info_size = vecInfo.size();
    for (vecFilePathList[0];i<vecFilePathList.size();++i)
    {
        fstream iReader(vecFilePathList[0]);
        string strTempRead((std::istreambuf_iterator<char>(iReader)),  
            std::istreambuf_iterator<char>());  
        string strTemp = UTF8ToGDB(strTempRead.c_str());  
        char* pLine;
        char decollEnterAndLF[3] = {10,13};
        pLine = strtok ((char*)strTemp.c_str(),decollEnterAndLF);
        while(pLine != NULL)
        { 
            vecFileLineContentList.push_back(pLine);
            pLine = strtok(NULL,decollEnterAndLF);
        }
    }   
    for (vecFileLineContentList[j];j < vecFileLineContentList.size();++j)
    {
		char deEsc = 27;
		vecFileContentList = strtokDefine((char*)vecFileLineContentList[j].c_str(),deEsc);        
		if (vecFileContentList.size() == 6)
		{
			ST_EmployeeInfo stEmployeeInfo;
			stEmployeeInfo.strJDBRID = vecFileContentList[0];
			stEmployeeInfo.strTEL= vecFileContentList[1];
			stEmployeeInfo.strUSERNAME = vecFileContentList[2];
			stEmployeeInfo.strUSERSTATUS = vecFileContentList[3];
			stEmployeeInfo.strROLENAME = vecFileContentList[4];
			stEmployeeInfo.strTLNUM = vecFileContentList[5];
			stEmployeeInfo.strPassword = m_stPasswordStrategy.strInitialPWD;
			stEmployeeInfo.strName = stEmployeeInfo.strTLNUM;
			for (int pos = 0; pos < branch_info_size; ++pos)
			{
				if (vecInfo[pos].strJDBRID.compare(stEmployeeInfo.strJDBRID) == 0)
				{
					stEmployeeInfo.strBranchId = vecInfo[pos].strBranchId;
					break;
				}
			}
			CTime time = CTime::GetCurrentTime(); 
			CString strTime = time.Format("%Y-%m-%d %H:%M:%S");
			stEmployeeInfo.stPasswordEidtTime = strTime;

			if (m_vecEmployeeInfo.empty())
			{
				m_vecEmployeeInfo.push_back(stEmployeeInfo);
			}
			else
			{
				bIsSame = FALSE;
				int i = 0;
				for (m_vecEmployeeInfo[i];i< m_vecEmployeeInfo.size();++i)
				{
					if (stEmployeeInfo.strTLNUM == m_vecEmployeeInfo[i].strTLNUM && stEmployeeInfo.strJDBRID == m_vecEmployeeInfo[i].strJDBRID)
					{
						//m_vecEmployeeInfo[i].strTEL = stEmployeeInfo.strTEL;
						//m_vecEmployeeInfo[i].strUSERSTATUS = stEmployeeInfo.strUSERSTATUS;
						bIsSame = TRUE;
						break;
					}
				}
				if(bIsSame == FALSE)
				{
					m_vecEmployeeInfo.push_back(stEmployeeInfo);
				}			
			}
		}
		else
		{
			SFTRACE("EmployeeInfo", "Ftp FinancEmployeeԱ�����ݴ��� [%s] \r\n", vecFileLineContentList[j].c_str());
		}
        vecFileContentList.clear();               
    }
}
vector<string> XhBFISSyncServerRouterImp::GetDatFilePathList(string strPath,string strName,vector<string> vecFileList)
{
    string ctlFileName = strPath +"//"+ strName;
    vector<string> vecCltFileContent = ReadFindCltFile(ctlFileName);
    vector<string> vecFindDatFileName = FindOppositeDatFile(vecFileList,vecCltFileContent);	
	if (!vecFindDatFileName.empty())
	{
		if (m_bManualSync == FALSE)
		{
			m_vecFileName.push_back(vecFindDatFileName[0]);
			SFTRACE("AutoSyncLog","�ļ�%s�Զ�ͬ���ɹ� \r\n",vecFindDatFileName[0].c_str());
		}
		if (m_bManualSync == TRUE)
		{
			m_vecFileName.push_back(vecFindDatFileName[0]);
			SFTRACE("ManualSyncLog","�ļ�%s�ֶ�ͬ���ɹ� \r\n",vecFindDatFileName[0].c_str());
		}		
	}
    int j = 0;
    vector<string> vecFindDatFilePath;
    for (vecFindDatFileName[j];j<vecFindDatFileName.size();++j)
    {
        string datFilePath = strPath + "//" + vecFindDatFileName[j];
        vecFindDatFilePath.push_back(datFilePath);
    }
    return vecFindDatFilePath;
}
BOOL XhBFISSyncServerRouterImp::ReadFileAndParse(string strPath)
{    
	DISPLAY_LOG("ͬ��ģ��","��ʼ����ftp�ļ�","","",1);
	m_vecBranchInfo.clear();
	m_vecEmployeeInfo.clear();
	m_vecProduceInfo.clear();
    BOOL nRet = FALSE;
    nRet = GetFileFromFTP(strPath.c_str());
    if (nRet == FALSE)
    {
		DISPLAY_LOG("ͬ��ģ��","����FTP�ļ�ʧ�ܣ��ȴ��ϴ�","","",1);
        return nRet;
    }
    vector<string> vecFileList;
    WIN32_FIND_DATA fileData;
    char line[1024];
    string strFindPath = strPath +"//*";
    HANDLE file = FindFirstFile(strFindPath.c_str(), &fileData);
    if (NULL == file)
    {
        return FALSE;
    }
    FindNextFile(file, &fileData);
    while(FindNextFile(file, &fileData))
    {
        vecFileList.push_back(fileData.cFileName);
    }
    int i = 0;
	/*CTime time = CTime::GetCurrentTime(); 
	CString strTime = time.Format("%Y%m%d");*/
	time_t lastTime  = time(NULL) - 86400;
	struct tm *tmpter1 = localtime(&lastTime);
	char strTime1[8] ={};
	sprintf(strTime1,"%4d%02d%02d",tmpter1->tm_year+1900,tmpter1->tm_mon+1,tmpter1->tm_mday);
	string strTime = strTime1;
	string strBranchInfoFileName = "O_M37_S01_JHDATA_"+ strTime;
	string strFundProduceInfoFileName = "O_M37_S21_FUND_PROD_INFO_"+ strTime;
	string strFinancProduceInfoFileName = "O_M37_S10_PROD_INFO_"+ strTime;
	string strKernelEmployeeInfoFileName = "O_M37_TLTEL_INFO_"+ strTime;
	string strFinancEmployeeInfoFileName = "O_M37_S10_USER_"+ strTime;
    for(vecFileList[i]; i < vecFileList.size(); ++i)
    {
        int IsCtlFile = vecFileList[i].find("ctl");
		//int	IsDatFile = vecFileList[i].find("dat");
        if ((0 == vecFileList[i].find(strBranchInfoFileName)) && IsCtlFile > 0)
        {
			if (m_bManualSync == FALSE)
			{
				vector<string> vecFindDatFilePath = GetDatFilePathList(strPath,vecFileList[i],vecFileList);         
				FileContentPraseToBranchInfo(vecFindDatFilePath);
			}
			if(m_bManualSync == TRUE && m_stManualSyncParameter.nBranchInfo == 1)
			{
				vector<string> vecFindDatFilePath = GetDatFilePathList(strPath,vecFileList[i],vecFileList);         
				FileContentPraseToBranchInfo(vecFindDatFilePath);
			}
        }
        if ((0 == vecFileList[i].find(strFundProduceInfoFileName)) && IsCtlFile > 0)
        {
			if (m_bManualSync == FALSE)
			{
				vector<string> vecFindDatFilePath = GetDatFilePathList(strPath,vecFileList[i],vecFileList);
				FileContentPraseToFundProduceInfo(vecFindDatFilePath);
			}
			if (m_bManualSync == TRUE && m_stManualSyncParameter.nProduceInfo == 1)
			{
				vector<string> vecFindDatFilePath = GetDatFilePathList(strPath,vecFileList[i],vecFileList);
				FileContentPraseToFundProduceInfo(vecFindDatFilePath);
			}
        }       
        if ((0 == vecFileList[i].find(strFinancProduceInfoFileName)) && IsCtlFile > 0)
        {
			if (m_bManualSync == FALSE)
			{
				vector<string> vecFindDatFilePath = GetDatFilePathList(strPath,vecFileList[i],vecFileList);
				FileContentPraseToFinancProduceInfo(vecFindDatFilePath);
			}
			if (m_bManualSync == TRUE && m_stManualSyncParameter.nProduceInfo == 1)
			{
				vector<string> vecFindDatFilePath = GetDatFilePathList(strPath,vecFileList[i],vecFileList);
				FileContentPraseToFinancProduceInfo(vecFindDatFilePath);
			}      
        }
        if ((0 == vecFileList[i].find(strFinancEmployeeInfoFileName)) && IsCtlFile > 0)
        {
			if (m_bManualSync == FALSE)
			{
				vector<string> vecFindDatFilePath = GetDatFilePathList(strPath,vecFileList[i],vecFileList);
				FileContentPraseToFinancEmployeeInfo(vecFindDatFilePath);
			}
			if (m_bManualSync == TRUE && m_stManualSyncParameter.nEmployeeInfo == 1)
			{
				vector<string> vecFindDatFilePath = GetDatFilePathList(strPath,vecFileList[i],vecFileList);
				FileContentPraseToFinancEmployeeInfo(vecFindDatFilePath);
			}		
        }
        if ((0 == vecFileList[i].find(strKernelEmployeeInfoFileName)) && IsCtlFile > 0)
        {
			if (m_bManualSync == FALSE)
			{
				vector<string> vecFindDatFilePath = GetDatFilePathList(strPath,vecFileList[i],vecFileList);
				FileContentPraseToKernelEmployeeInfo(vecFindDatFilePath);
			}     
			if (m_bManualSync == TRUE && m_stManualSyncParameter.nEmployeeInfo == 1)
			{
				vector<string> vecFindDatFilePath = GetDatFilePathList(strPath,vecFileList[i],vecFileList);
				FileContentPraseToKernelEmployeeInfo(vecFindDatFilePath);
			}
        }
    }
	if (m_bManualSync == FALSE)
	{	
		HandleReadBranchInfo();
		HandleReadEmployInfo();		
		HandleReadProductInfo();		
	}
	m_bManualSync = FALSE;
    return nRet;
}

int XhBFISSyncServerRouterImp::Init( ISOC_DWORDPTR dwReserved /*= 0*/ )
{
	STRY;
	DoRealTimeSync(); 
	InitStation();
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::UnInit( ISOC_DWORDPTR dwReserved /*= 0*/ )
{
	STRY;
	UnInitStation();
	return 1;
	SCATCH;
	return -1;
}

void XhBFISSyncServerRouterImp::OnDisConnect(UINT64 fromAddr)
{
	STRY;
	writeLock writeLocker(m_csLockClientContext);
	auto iter = m_mapClientContext.find(fromAddr);
	if (iter != m_mapClientContext.end())
	{
		char szMsg[255];
		sprintf(szMsg,"����[%s] ����ID[%s] ����IP[%s]���˳�",iter->second->m_custom.stInfo.strName.c_str(), iter->second->m_custom.stInfo.strBranchId.c_str(), iter->second->m_custom.stInfo.strAddress.c_str());
		SFTRACE("LoginStatusLog","%s \r\n",szMsg);
		std::shared_ptr<ObjectRefCount<ST_Login> > objRef = iter->second;
		std::shared_ptr<RefCountInfo> refInfo = objRef->GetRefInfo();
		m_mapClientContext.erase(iter);
		writeLocker.unlock();
		if (refInfo)
			refInfo->DelRefObject(10);

		DISPLAY_LOG("ҵ��ģ��", szMsg, "", "", 1);
	}
	SCATCH;
}

int XhBFISSyncServerRouterImp::InitStation()
{
	STRY;
	BOOL bRet = PraseGetKeyValueData();
	if (bRet == FALSE)
	{
		TTRACE("��ȡ����������Ϣʧ�� \r\n");
	}	
	iSOC_MonFactoryManagement fmt;
	m_pComm = (IBFISCommunicateSyncServer*)fmt.CreateObject(OBJECT_TYPE_BFIS_COMMUNICATESYNCSERVER,"", __FUNCTION__);
	if (fmt.CheckObjectCanBeUse(m_pComm))
	{
#if 0
		DWORD_PTR dwCmd = MSG_ISBUSY;
		for ( ; dwCmd <=  MSG_GET_PURVIEWINFO ; dwCmd ++)
		{
			m_pComm->RegisterRecvMessageCallbackSkin(dwCmd,this);
		}
#else
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_ISBUSY,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_IS_ALIVE,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_LOGIN,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_UPLOAD_CLIENTINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_UPLOAD_BRANCHINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_UPLOAD_BUSINESSINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_UPLOAD_BUSINESSFILEINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_UPLOAD_BUSINESSRELATEINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_UPLOAD_EMPLOYEEINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_UPLOAD_EMPLOYEEPURVIEWINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_GET_CLIENTINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_UPLOAD_ROLEINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_UPLOAD_ROLEPURVIEWINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_GET_PRODUCEINFO,this);
        m_pComm->RegisterRecvMessageCallbackSkin(MSG_GET_SMS_LOGININFO, this);
        m_pComm->RegisterRecvMessageCallbackSkin(MSG_GET_PARENT_BRANCHINFO, this);
        m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_SYNC_PRODUCE, this);
        m_pComm->RegisterRecvMessageCallbackSkin(MSG_ISSUED_BRANCHINFO, this);
        m_pComm->RegisterRecvMessageCallbackSkin(MSG_ISSUED_EMPLOYEEINFO, this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_CLIENT_SET_MANUALSYNC,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_ISSUED_SYNC_ACK, this);

		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_BRANCHINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_PRODUCEINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_USERMAPINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_ROLEINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_PURVIEWINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEPURVIEWINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_CLIENTINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_BUSINESSINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_BUSINESSFILEINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_BUSINESSRELATEINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO,this); 
        m_pComm->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_BUSINESSDOCKMAGINFO,this);
		m_pComm->RegisterRecvMessageCallbackSkin(MSG_OUTGOING_DEVICE_SYNC, this);
#endif
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::UnInitStation()
{
	STRY;
	if (m_pComm)
	{
#if 0
		DWORD_PTR dwCmd = MSG_LOGIN;
		for ( ; dwCmd <=  MSG_GET_PURVIEWINFO ; dwCmd ++)
		{
			m_pComm->UnRegisterRecvMessageCallbackSkin(dwCmd,this);
		}
#else
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_ISBUSY,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_IS_ALIVE,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_LOGIN,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_UPLOAD_CLIENTINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_UPLOAD_BRANCHINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_UPLOAD_BUSINESSINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_UPLOAD_BUSINESSFILEINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_UPLOAD_BUSINESSRELATEINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_UPLOAD_EMPLOYEEINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_UPLOAD_EMPLOYEEPURVIEWINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_GET_CLIENTINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_UPLOAD_ROLEINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_UPLOAD_ROLEPURVIEWINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_GET_PRODUCEINFO,this);
        m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_ISSUED_BRANCHINFO,this);
        m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_ISSUED_EMPLOYEEINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_CLIENT_SET_MANUALSYNC,this);

		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_BRANCHINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_PRODUCEINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_USERMAPINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_ROLEINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_PURVIEWINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEPURVIEWINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_CLIENTINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_BUSINESSINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_BUSINESSFILEINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_BUSINESSRELATEINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO,this);
        m_pComm->UnRegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_NOTIFY_BUSINESSDOCKMAGINFO,this);
		m_pComm->UnRegisterRecvMessageCallbackSkin(MSG_OUTGOING_DEVICE_SYNC, this);
#endif
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::ExtendFunction( IN const ISOC_INT nExtendType,IN ISOC_DWORDPTR dwExtendData )
{
	STRY;

	SCATCH;
	return -1;
}

bool XhBFISSyncServerRouterImp::GetNeedSyncProduceInfo(vector<ST_ProduceInfo>& vecProduceInfo)
{
	STRY;
	if (NULL != m_pCache && TRUE == m_pCache->QueryProduceInfo(vecProduceInfo))
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}
bool XhBFISSyncServerRouterImp::GetNeedSyncRoleInfo(vector<ST_RoleInfo>& vecRoleInfo)
{
	STRY;
	if (NULL != m_pCache && 0 == m_pCache->QueryRoleInfo(vecRoleInfo))
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}
bool XhBFISSyncServerRouterImp::GetNeedSyncClientInfo(vector<ST_ClientInfo>& vecClientInfo)
{
	STRY;
	if (NULL != m_pCache )
	{
		CString strTime = _T("");
		if(ReadLastSyncTime(strTime) && strTime != _T("") && m_pCache->QueryClientInfo3Param(vecClientInfo,strTime.GetBuffer(0)) > 0)
		{
			strTime.ReleaseBuffer();
			return true;
		}
		strTime.ReleaseBuffer();
	}
	return false;
	SCATCH;
	return false;
}
bool XhBFISSyncServerRouterImp::GetNeedSyncBranchInfo(vector<ST_BranchInfo>& vecBranchInfo)
{
	STRY;
    if (NULL != m_pCache  && TRUE == m_pCache->QueryBranchInfo(vecBranchInfo))
    {
    return true;
    }
    return false;
	SCATCH;
	return false;
}

bool XhBFISSyncServerRouterImp::AddClientInfoToDataBase(ST_ClientInfo sClientInfo)
{
	STRY;
	if (sClientInfo.strCredenitial == "")
	{
		TTRACE("��ӿͻ���Ϣʧ�ܣ�����ͻ����֤����Ϊ��.%s[%d] \r\n",__FUNCTION__,__LINE__);
		return false;
	}
	ST_ClientInfo stInfo;
	std::string strClientKey = sClientInfo.strClientId + sClientInfo.strCredenitial;
	if (m_pCache && !m_pCache->QueryClientInfoByCredenitial(strClientKey,stInfo)
		&& m_pCache->ManageClientInfo(DBO_ADD,sClientInfo))
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}

int XhBFISSyncServerRouterImp::IssueSyncClientInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	if(vecStr.empty())
		return -1;
	std::string strLastTime = vecStr[0];
	vecStr.clear();
	vector<ST_ClientInfo> vecInfos;
	//1.��ѯ��Ҫͬ����
	if (dwReserved != 0)
	{
		if (!m_pCache || m_pCache->QueryClientInfo3Param(vecInfos,strLastTime,dwReserved) <= 0)
		{
			DISPLAY_LOG("������ģ��","���ݿ�Ͽ�����","","",0);
			return -1;
		}
	}
	else
	{
		if (!GetNeedSyncClientInfo(vecInfos))
		{
			DISPLAY_LOG("������ģ��","���ݿ�Ͽ�����","","",0);
			return -1;
		}
	}
	if(vecInfos.empty())
	{
		//DISPLAY_LOG("������ģ��","û����Ҫͬ��������","","",1);
		return 1;
	}
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter++)
	{
		//1.���л�����
		/*
		string strClientId;
		string strName;
		string strCredenitial;
		string strPhone;
		string strContent;
		int	   nExtendedInfo;
		string strExtendedInfo1;
		string strExtendedInfo2;
		*/
		std::string strOutData;
		BFIS::ClientInfo msg;
		msg.set_strclientid(iter->strClientId);
		msg.set_strname(iter->strName);
        msg.set_strcredenitialstype(iter->strCredenitialsType);
		msg.set_strcredenitial(iter->strCredenitial);
		msg.set_strphone(iter->strPhone);
		msg.set_strcontent(iter->strContent);
		msg.set_nextendedinfo(iter->nExtendedInfo);
		msg.set_strextendedinfo1(iter->strExtendedInfo1);
		msg.set_strextendedinfo2(iter->strExtendedInfo2);
		bool bSeralizeSuccess = msg.SerializeToString(&strOutData);

		if (!bSeralizeSuccess)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("���л��ͻ�����ʧ��"), _T(""), _T(""), 0); 
			return -1;
		}
		else
		{
			vecStr.push_back(strOutData);
		}
	}
#if 0
	//�洢ͬ��ʱ��
	std::string strTime;
	if(!m_pCache->QueryClientInfoLastSyncTime(strTime))
	{
		DISPLAY_LOG("ͬ������","�洢ͬ��ʱ��ʧ��","","",0);
		return -1;
	}
	CString strTmp;
	strTmp.Format("%s",strTime.c_str());
	RestoreLastSyncTime(strTmp);
#endif
	return 1;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::IssueSyncProduceInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	if (vecStr.empty())
	{
		TTRACE("��ȡ��Ҫͬ����������Ϣʧ��%s[%d]\r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	std::string strSyncTime = vecStr[0];
	if (strSyncTime == "")
	{
		strSyncTime = "0000-00-00 00:00:00";
	}
	vecStr.clear();
	std::vector<ST_ProduceInfo> vecInfos;
	if (m_pCache && m_pCache->QueryProduceNeed2Sync(strSyncTime,vecInfos) != QueryFail)
	{
		if(vecInfos.empty())
		{
			DISPLAY_LOG("������ģ��","û����Ҫͬ���Ĳ�Ʒ","","",1);
			return 1;
		}
		std::string strTemp;
		for each(auto produceinfo in vecInfos)
		{
			if(produceinfo.ConvertToString(strTemp))
			{
				vecStr.push_back(strTemp);
			}
		}
	}
	else
	{
		DISPLAY_LOG("������ģ��","��ѯ��Ҫͬ���Ĳ�Ʒ��Ϣʧ��","","",0);
		return -1;
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::IssueSyncRoleInfo(vector<std::string>& vecStr, DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	vector<ST_RoleInfo> vecInfos;
	//1.��ѯ��Ҫͬ����
	if (!m_pCache ||  m_pCache->QueryRoleInfo(vecInfos) <= 0 )
	{
		DISPLAY_LOG("������ģ��","���ݿ�Ͽ�����","","",0);
		return -1;
	}
	if(vecInfos.empty())
	{
		DISPLAY_LOG("������ģ��","û����Ҫͬ��������","","",1);
		return 1;
	}
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter++)
	{
		//1.���л�����
		/*
		string strRoleInfoId;
		string strRoleName;
		int    nRoleLevel;
		int	   nExtendedInfo;
		string strExtendedInfo1;
		string strExtendedInfo2;
		*/
		std::string strOutData;
		BFIS::RoleInfo msg;
		msg.set_strroleinfoid(iter->strRoleInfoId);
		msg.set_strrolename(iter->strRoleName);
		msg.set_nrolelevel(iter->nRoleLevel);
		msg.set_nextendedinfo(iter->nExtendedInfo);
		msg.set_strextendedinfo1(iter->strExtendedInfo1);
		msg.set_strextendedinfo2(iter->strExtendedInfo2);
		msg.set_strbranchinfoid(iter->strBranchInfoId);
		msg.set_nflag(iter->nFlag);
		bool bSeralizeSuccess = msg.SerializeToString(&strOutData);

		if (!bSeralizeSuccess)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("���л��ͻ�����ʧ��"), _T(""), _T(""), 0); 
			return -1;
		}
		else
		{
			vecStr.push_back(strOutData);
		}
	}
	return 1;
	SCATCH;
	return -1;
}
#if 0
int XhBFISSyncServerRouterImp::IssueSyncPurviewInfo(vector<std::string>& vecStr, DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	vector<ST_PurviewInfo> vecInfos;
	//1.��ѯ��Ҫͬ����
	if (!m_pCache ||  m_pCache->QueryPurviewInfo(vecInfos,dwReserved) <= 0)
	{
		DISPLAY_LOG("������ģ��","���ݿ�Ͽ�����","","",0);
		return -1;
	}
	if(vecInfos.empty())
	{
		DISPLAY_LOG("������ģ��","û����Ҫͬ��������","","",1);
		return 1;
	}
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter++)
	{
		//1.���л�����
		/*
		string strPurviewInfoId;
		string strParentPurviewId;
		string strPurviewCode;
		string strDescription;
		string strExtendedInfo1;
		string strExtendedInfo2;
		*/
		std::string strOutData;
		BFIS::PurviewInfo msg;
		msg.set_strpurviewinfoid(iter->strPurviewInfoId);
		msg.set_strparentpurviewid(iter->strParentPurviewId);
		msg.set_strpurviewcode(iter->strPurviewCode);
		msg.set_strdescription(iter->strDescription);
		msg.set_strextendedinfo1(iter->strExtendedInfo1);
		msg.set_strextendedinfo2(iter->strExtendedInfo2);
		bool bSeralizeSuccess = msg.SerializeToString(&strOutData);

		if (!bSeralizeSuccess)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("���л��ͻ�����ʧ��"), _T(""), _T(""), 0); 
			return -1;
		}
		else
		{
			vecStr.push_back(strOutData);
		}
	}
	return 1;
	SCATCH;
	return -1;
}
#endif
int XhBFISSyncServerRouterImp::IssueSyncRolePurviewInfo(vector<std::string>& vecStr, DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	vector<ST_RolePurviewInfo> vecInfos;
	//1.��ѯ��Ҫͬ����
	if (!m_pCache || m_pCache->QueryRolePurviewInfo(vecInfos) <= 0)
	{
		DISPLAY_LOG("������ģ��","���ݿ�Ͽ�����","","",0);
		return -1;
	}
	if(vecInfos.empty())
	{
		DISPLAY_LOG("������ģ��","û����Ҫͬ��������","","",1);
		return 1;
	}
	for (auto iter = vecInfos.begin(); iter != vecInfos.end(); iter++)
	{
		//1.���л�����
		/*
		string strRoleInfoPurviewId;
		string strRoleId;
		string strPruviewInfoId;
		int    nExtendedInfo;
		string strExtendedInfo1;
		string strExtendedInfo2;
		*/
		std::string strOutData;
		BFIS::RolePurviewInfo msg;
		msg.set_strroleinfopurviewid(iter->strRoleInfoPurviewId);
		msg.set_strroleid(iter->strRoleId);
		msg.set_strpruviewinfoid(iter->strPruviewInfoId);
		msg.set_nextendedinfo(iter->nExtendedInfo);
		msg.set_strextendedinfo1(iter->strExtendedInfo1);
		msg.set_strextendedinfo2(iter->strExtendedInfo2);
		bool bSeralizeSuccess = msg.SerializeToString(&strOutData);

		if (!bSeralizeSuccess)
		{
			DISPLAY_LOG(_T("ͬ������"),_T("���л��ͻ�����ʧ��"), _T(""), _T(""), 0); 
			return -1;
		}
		else
		{
			vecStr.push_back(strOutData);
		}
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnGotUploadBranchInfo(ST_BranchInfo& stInfo, DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (stInfo.strBranchId == "")
	{
		TTRACE("�����¼��ϴ���������Ϣʧ�ܣ�����IDΪ��%s[%d] \r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	if (m_pCache )
	{
		ST_BranchInfo stBranchInfo;
		if(m_pCache->QueryBranchInfoById(stInfo.strBranchId,stBranchInfo) > 0)
		{
			return (m_pCache->ManageBranchInfo(DBO_UPDATE,stInfo) == FALSE ?-1:1);
		}
		else
		{
			return (m_pCache->ManageBranchInfo(DBO_ADD, stInfo) == FALSE ?-1:1);
		}
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnGotUpLoadClientInfo( ST_ClientInfo& stInfo, DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	/*if (stInfo.strCredenitial == "")
	{
	TTRACE("�����¼��ϴ��Ŀͻ���Ϣʧ�ܣ�����Ŀͻ����֤����Ϊ��%s[%d] \r\n",__FUNCTION__,__LINE__);
	return -1;
	}*/
	//2.�ж�
	if (m_pCache )
	{
		ST_ClientInfo stOld;
		//stOld.strCredenitial = stInfo.strCredenitial;
		std::string strClientKey = stInfo.strClientId + stInfo.strCredenitial;
		//������ڣ��ж���Ϣ�Ƿ�һ�£���һ����ʹ�����µ���Ϣ����idʹ��ԭ���ģ���������ǰ��id���ͻ���
		if(m_pCache->QueryClientInfoByCredenitial(strClientKey, stOld))
		{
			//int nRet = -1;
			//stInfo.strClientId = stOld.strClientId;
			//m_pCache->ManageClientInfo(DBO_UPDATE,stInfo) == QueryFail ? nRet = -1 : nRet = OT_SUCCESS;
			//return nRet;
			///TODO:ͨ�ð汾����������������ط���������Ϊÿ������ҵ�񶼻�����һ���û���Ϣ�����Բ����ڱ��޸ĵ����⡣�����û���ϢΨһ��֮��Ҫ�жϸ���ʱ��
			return OT_SUCCESS;
		}
		else
		{
			return m_pCache->ManageClientInfo(DBO_ADD,stInfo) == FALSE?-1:1;
		}
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnGotUpLoadBusinessInfo( ST_BusinessInfo stInfo, DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if (stInfo.strBusinessInfoId == "")
	{
		TTRACE("�����¼��ϴ���ҵ����Ϣʧ�ܣ������ҵ����ϢIDΪ��%s[%d] \r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	if (m_pCache)
	{
		return m_pCache->ManageBusinessInfo(DBO_ADD,stInfo) == FALSE ?-1:1;
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnGotUpLoadBusinessFileInfo( ST_BusinessFileInfo stInfo, DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if (stInfo.strRecordId == "")
	{
		TTRACE("�����¼��ϴ���ҵ���ļ���Ϣʧ�ܣ������¼��IDΪ��%s[%d] \r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	if (m_pCache )
	{
		ST_BusinessFileInfo stOldInfo;
		QueryResultType enResult = (QueryResultType)m_pCache->QueryBusinessFileInfoById(stInfo.strRecordId, stOldInfo);
		switch(enResult)
		{
		case QuerySuccessWithResult:
			{
				return m_pCache->ManageBusinessFileInfo(DBO_UPDATE,stInfo) == FALSE ?-1:OT_EXIST;
				break;
			}
		case QuerySuccessWithoutResult:
			{
				return m_pCache->ManageBusinessFileInfo(DBO_ADD,stInfo) == FALSE ?-1:1;
				break;
			}
		case QueryFail:
			{
				return -1;
				break;
			}
		default:
			{
				return -1;
				break;
			}
		}
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnGotUpLoadBusinessRelateInfo( ST_BusinessRelateInfo stInfo, DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if (stInfo.strBusinessRelateInfoId == "")
	{
		TTRACE("�����¼��ϴ���ҵ�������Ϣʧ�ܣ������ҵ�������ϢIDΪ��%s[%d] \r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	if (m_pCache )
	{
		ST_BusinessRelateInfo stOldInfo;
		QueryResultType enResult = (QueryResultType)m_pCache->QueryBusinessRelateInfoById(stInfo.strBusinessRelateInfoId, stOldInfo);
		switch(enResult)
		{
		case QuerySuccessWithResult:
			{
				return m_pCache->ManageBusinessRelateInfo(DBO_UPDATE,stInfo) == FALSE ?-1:OT_EXIST;
				break;
			}
		case QuerySuccessWithoutResult:
			{
				return m_pCache->ManageBusinessRelateInfo(DBO_ADD,stInfo) == FALSE ?-1:1;
				break;
			}
		case QueryFail:
			{
				return -1;
				break;
			}
		default:
			{
				return -1;
				break;
			}
		}
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnGotUpLoadEmployeeInfo( ST_EmployeeInfo& stInfo, DWORD_PTR dwReserved /*= 0*/ )
{
	STRY;
	if (stInfo.strEmployeeId == "")
	{
		TTRACE("�����¼��ϴ���Ա����Ϣʧ�ܣ������Ա��IDΪ��%s[%d] \r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	if (m_pCache )
	{
		ST_EmployeeInfo stOldInfo;
		stOldInfo.strEmployeeId = stInfo.strEmployeeId;
		if (m_pCache && m_pCache->QueryEmployeeInfoById(stInfo.strEmployeeId,stOldInfo) > 0)
		{
			return m_pCache->ManageEmployeeInfo(DBO_UPDATE, stInfo) == FALSE ?-1:OT_EXIST;
		}
		else
		{
			BYTE cbyte[40]={0};
			HexToByte(stInfo.strPassword,cbyte);
			stInfo.strPassword = (char*)cbyte;
			return m_pCache->ManageEmployeeInfo(DBO_ADD,stInfo) == FALSE ?-1:1;
		}
	}
	return 1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnGotUpLoadEmployeePurviewInfo(ST_EmployeePurviewInfo& stInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (stInfo.strEmployeePurviewId == "")
	{
		TTRACE("�����¼��ϴ���Ա��Ȩ����Ϣʧ�ܣ������Ա��Ȩ��IDΪ��%s[%d] \r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	if (m_pCache )
	{
		return m_pCache->ManageEmployeePurviewInfo(DBO_ADD,stInfo) == FALSE ?-1:1;
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnGotUpLoadRoleInfo(ST_RoleInfo& stInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (stInfo.strRoleInfoId == "")
	{
		TTRACE("�����¼��ϴ��Ľ�ɫ��Ϣʧ�ܣ�����Ľ�ɫIDΪ��%s[%d] \r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	if (m_pCache )
	{
		return m_pCache->ManageRoleInfo(DBO_ADD,stInfo) == FALSE ?-1:1;
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::OnGotUpLoadRolePurviewInfo(ST_RolePurviewInfo& stInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (stInfo.strRoleInfoPurviewId == "")
	{
		TTRACE("�����¼��ϴ��Ľ�ɫȨ����Ϣʧ�ܣ�����Ľ�ɫȨ��IDΪ��%s[%d] \r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	if (m_pCache )
	{
		return m_pCache->ManageRolePurviewInfo(DBO_ADD,stInfo) == FALSE ?-1:1;
	}
	return -1;
	SCATCH;
	return -1;
}

//HANDLE g_hThreadEvent = NULL;
int XhBFISSyncServerRouterImp::DoSyncAll(vector<ST_BranchInfo> vecBranchInfo, IN ISOC_DWORDPTR dwReserved /*= 0*/ )
{
// 	STRY;
// 	//g_hThreadEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
// 	for (auto iter = vecBranchInfo.begin() ; iter != vecBranchInfo.end() ; iter ++)
// 	{
// 		m_stBranchInfo = (*iter);
// 		IThread* pThread = NULL;
// 		if(pThread)
// 		{
// 			pThread->SetRunAbleInterface(this);
// 			pThread->Start();
// 		}
// 		else
// 		{
// 			iSOC_MonFactoryManagement fmt;
// 			pThread = (IThread*)fmt.CreateObject(OBJECT_TYPE_THREAD,"",__FUNCTION__);
// 			if(pThread)
// 			{
// 				pThread->SetRunAbleInterface(this);
// 				pThread->Start();
// 			}
// 			m_vecThread.push_back(pThread);
// 		}
// 		//WaitForSingleObject(g_hThreadEvent,INFINITE);
// 		//m_eventWaitThread.reset();
// 		//m_eventWaitThread.tryWait(10*60*1000);
// 		m_eventWaitThread.wait();
// 	}
// 	//CloseHandle(g_hThreadEvent);
// 	return 1;
// 	SCATCH;
	return -1;
}


int XhBFISSyncServerRouterImp::DoRealTimeSync(IN ISOC_DWORDPTR dwReserved /*= 0*/)
{
	STRY;
	m_bSync = TRUE; 
	//IThread* pThread = NULL;		
	if(m_pThread)
	{
		if (m_pThread->IsAlive())
		{
			return 1;
		}
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
BOOL XhBFISSyncServerRouterImp::TimeCompare()
{
     CTime localTime = CTime::GetCurrentTime();
     CString str; 
     str.Format("%s",m_stBasicSetting.strSynchroTime);
     COleDateTime tm;
     tm.ParseDateTime(str);
     int nLocalTotalSec = localTime.GetHour()*3600 +localTime.GetMinute()*60+localTime.GetSecond();
     TTRACE("nLocalTotalSec:%d\t\n",nLocalTotalSec);
     int nSyscTimeTotalSec = tm.GetHour()*3600 +tm.GetMinute()*60+tm.GetSecond();
	 if (nLocalTotalSec > 23 * 3600 && !m_vecFileName.empty())
	 {
		 DISPLAY_LOG("ͬ��ģ��","��������ļ���","","",1);
		 m_vecFileName.clear();
	 }
	/* if (localTime.GetYear() == m_ctLocalDayTime.GetYear() && localTime.GetMonth() == m_ctLocalDayTime.GetMonth() && localTime.GetDay() == m_ctLocalDayTime.GetDay()
		 && m_vecFileName.size() >= 5)
     {	 
         return FALSE;
     }
     else
     {	
         return nLocalTotalSec - nSyscTimeTotalSec <= 0 ? TRUE : FALSE;
     }*/  
	 return nLocalTotalSec - nSyscTimeTotalSec <= 0 ? TRUE : FALSE;
}
BOOL XhBFISSyncServerRouterImp::DeleteDirectory(char* strDirName) 
{ 
	STRY;
	CFileFind tempFind; 
	char sTempFileFind[200]; 
	sprintf(sTempFileFind,"%s//*.*",strDirName); 
	BOOL IsFinded = tempFind.FindFile(sTempFileFind);
	while (IsFinded) 
	{			
		IsFinded = tempFind.FindNextFile(); 
		if (!tempFind.IsDots()) 
		{	 
			char sFoundFileName[200]; 
			strcpy(sFoundFileName,tempFind.GetFileName().GetBuffer(200)); 
			if (tempFind.IsDirectory()) 
			{ 
				char sTempDir[200]; 
				sprintf(sTempDir,"%s//%s",strDirName,sFoundFileName); 
				DeleteDirectory(sTempDir);
			} 
			else 
			{	
				char sTempFileName[200]; 
				sprintf(sTempFileName,"%s//%s",strDirName,sFoundFileName);
				int a = DeleteFileA(sTempFileName);
			} 
		}
	} 
	tempFind.Close();
	/*if(!RemoveDirectoryA(strDirName)) 
	{ 
	return FALSE;
	}*/
	return TRUE;
	SCATCH;
	return FALSE;
}
BOOL XhBFISSyncServerRouterImp::IsSyncBranchInfo(string strBranchId)
{
	STRY;
	for each(const auto& context in m_vecSyncEndBranchId) 
	{
		if (strBranchId == context)
		{
			return TRUE;
			break;
		}
	}
	return FALSE;
	SCATCH;
	return FALSE;
}

int XhBFISSyncServerRouterImp::SubServerSyncNotify(HANDLE hClinet)
{
	iBFIS_CommunicationInvoker invoke(hClinet);
	DWORD dwCmd = MSG_ISSUED_ALLOWSYNC;
	return invoke.Invoke(dwCmd);
}

void XhBFISSyncServerRouterImp::SyncSubServerWork()
{
	CString strFMSConfigPath = GetWorkingDirectory();
	strFMSConfigPath += "\\Config\\SyncBranchInfo.txt";
	
	m_syncEvent.Wait(600);

	char buffer[256] = { 0 };
	while (m_bSyncSubServer)
	{
		CTime localTime = CTime::GetCurrentTime();
		int nLocalTotalSec = localTime.GetHour() * 3600 + localTime.GetMinute() * 60 + localTime.GetSecond();
		int nMaxSyscTimeTotalSec = 18 * 3600;
		int nMinSyscTimeTotalSec = 6 * 3600;
		if (nLocalTotalSec < nMaxSyscTimeTotalSec &&  nLocalTotalSec > nMinSyscTimeTotalSec)
		{
			m_syncEvent.Wait(600);
			if (m_syncFile.is_open())
			{
				m_syncFile.close();
				remove(strFMSConfigPath.GetBuffer(0));
			}
			continue;
		}
		else
		{
			if (!m_syncFile.is_open())
			{
				m_syncFile.open(strFMSConfigPath.GetBuffer(0), std::ios::in | std::ios::out | ios::app);
			}
		}

		std::set<std::string> branchs;
		STRY;
		if (m_syncFile.is_open())
		{
			boost::unique_lock<boost::mutex> lock(m_fileMutex);
			m_syncFile.seekg(0, ios::beg);
			while(!m_syncFile.eof()) 
			{
				m_syncFile.getline(buffer, 100);
				std::string branch(buffer);
				if (!branch.empty())
				{
					branchs.insert(branch);
					memset(buffer, 0, 256);
				}
			}
		}
		SCATCH;

		m_syncEvent.Wait(180);
		if (!m_bSyncSubServer)
			break;

		std::map<UINT64, std::shared_ptr<ObjectRefCount<ST_Login> > >  mapClientContext;
		STRY;
		readLock readLocker(m_csLockClientContext);
		mapClientContext = m_mapClientContext;
		SCATCH;

		for each(auto &var in mapClientContext)
		{
			STRY;
			readLock readLocker(m_csLockClientContext);
			auto iter = m_mapClientContext.find(var.first);
			if (iter != m_mapClientContext.end())
			{
				std::shared_ptr<ObjectRefCount<ST_Login> > objectRefInfo = iter->second;
				auto findItor = branchs.find(objectRefInfo->m_custom.stInfo.strBranchId);
				if (findItor != branchs.end())
					continue;

				std::shared_ptr<RefCountInfo> refInfo = objectRefInfo->GetRefInfo();

				AutoObjectRefMgr refObject;
				if (refObject.AddRefCount(refInfo))
				{
					readLocker.unlock();
					int nRet = SubServerSyncNotify((HANDLE)var.first);
					if (nRet > 0)
					{
						SFTRACE("SyncInfo", "�����¼�����[%s] ͬ��\r\n", objectRefInfo->m_custom.stInfo.strName.c_str());
						m_syncEvent.Wait(600);
						if (!m_bSyncSubServer)
							break;
					}
					else
					{
						SFTRACE("SyncInfo", "�����¼�����ʧ��[%s] ����[%d]\r\n", objectRefInfo->m_custom.stInfo.strName.c_str(), nRet);
					}
				}
			}
			SCATCH;
			m_syncEvent.Wait(10);
		}
	}
}
#pragma region ʵʱ�·�
void XhBFISSyncServerRouterImp::Run()
{
	STRY;   
    BOOL bIsComeSyncTime = FALSE;
    BOOL bIsSync = TRUE;
	BOOL bRet = FALSE;

	while(m_bSync)
	{     
        //���������
        if ( m_nServerType == AppType_Server )
		{	
			bRet = PraseGetKeyValueData();
			if (bRet == FALSE)
			{
				STRY;
				boost::unique_lock<boost::mutex> lock(m_mutex);
				m_condition.wait_for(lock, boost::chrono::seconds(3));
				SCATCH;
				continue;
			}	
			if (m_stBasicSetting.nAutomaticSynchroChecked > 0)
			{
				if (TRUE == TimeCompare())
				{
					STRY;
					boost::unique_lock<boost::mutex> lock(m_mutex);
					m_condition.wait_for(lock, boost::chrono::seconds(60));
					SCATCH;
					if (!m_bSync)
						return;
					//CTime localTime = CTime::GetCurrentTime();
					if(m_vecFileName.size() < 5)
					{
						bRet = ReadFileAndParse(".//SyncFile");
						if (FALSE == bRet)
						{
							DISPLAY_LOG("ͬ��ģ��", "��ȡftp�ļ�������ʧ��,�ȴ��ļ��ϴ�", "", "", 1);
							TTRACE("��ȡftp�ļ�������ʧ�� \r\n");
							STRY;
							boost::unique_lock<boost::mutex> lock(m_mutex);
							m_condition.wait_for(lock, boost::chrono::seconds(3 * 60));
							SCATCH;
							continue;
						}
						DeleteDirectory(".//SyncFile");
					}

					m_mapClientCount = 0;
					int nRet = -1;

					SFTRACE("FTP�·�����", "FTP�Զ����¼�������Ϣ ----------------  ��ʼ\r\n");
					
					std::map<std::string, std::string> branchInfoTotalMap;
					if (m_pCache)
					{
						vector<ST_BranchInfo> vecInfo;
						m_pCache->QueryBranchInfo(vecInfo);
						for each(auto &var in vecInfo)
						{
							if (var.strParentName.empty())  //�����ж�
								continue;

							auto pos = var.strName.rfind("����");
							if (pos == std::string::npos)
							{
								branchInfoTotalMap.insert(std::make_pair(var.strBranchId, var.strName));
							}
							else
							{
								std::string subString = var.strName.substr(pos);
								if (subString.compare("����") != 0)  //��������ж�
								{
									branchInfoTotalMap.insert(std::make_pair(var.strBranchId, var.strName));
								}
							}
						}
					}

					std::map<std::string, std::string> branchInfoSendFailMap;

					int branchTotalCount = branchInfoTotalMap.size();
					std::map<UINT64, std::shared_ptr<ObjectRefCount<ST_Login> > >  mapClientContext;
					STRY;
					readLock readLocker(m_csLockClientContext);
					mapClientContext = m_mapClientContext;
					SCATCH;

					int  nSucessCount = 0;
					int nFailedCount = 0;
					m_mapClientCount = 0;
					//m_mapClientCount = mapClientContext.size();
					for each(auto &var in mapClientContext)
					{
						readLock readLocker(m_csLockClientContext);
						auto iter = m_mapClientContext.find(var.first);
						if (iter != m_mapClientContext.end())
						{
							std::shared_ptr<ObjectRefCount<ST_Login> > objectRefInfo = iter->second;
							std::shared_ptr<RefCountInfo> refInfo = objectRefInfo->GetRefInfo();
							std::string strBranch = objectRefInfo->m_custom.stInfo.strBranchId;
							AutoObjectRefMgr refObject;
							if (refObject.AddRefCount(refInfo))
							{
								readLocker.unlock();
								++m_mapClientCount;
								branchInfoTotalMap.erase(strBranch);
								HANDLE hClinet = (HANDLE)var.first;
								if (TRUE == IsSyncBranchInfo(strBranch))
								{
									++nSucessCount;
									continue;
								}

								STRY;
								if (!m_vecBranchInfo.empty())
								{
									//SFTRACE("FTP�·�����", "FTP�Զ����¼�����������Ϣ��ʼ����������[%s]����ID[%s] \r\n", objectRefInfo->m_custom.stInfo.strName.c_str(), objectRefInfo->m_custom.stInfo.strBranchId.c_str());
									nRet = DoSyncBranchInfo(hClinet, m_vecBranchInfo, 0, strBranch);
								}
								SCATCH;

								if (refObject.isDel() || nRet <= 0)
								{
									++nFailedCount;
									branchInfoSendFailMap.insert(std::make_pair(objectRefInfo->m_custom.stInfo.strBranchId, objectRefInfo->m_custom.stInfo.strName));
									continue;
								}
									
								STRY;
								if (!m_vecEmployeeInfo.empty())
								{
									//SFTRACE("FTP�·�����", "FTP�Զ����¼�����Ա����Ϣ��ʼ��������Ϣ����[%s]������ϢID[%s] \r\n", objectRefInfo->m_custom.stInfo.strName.c_str(), objectRefInfo->m_custom.stInfo.strBranchId.c_str());
									nRet = DoSyncEmployeeInfo(hClinet, m_vecEmployeeInfo, -1, strBranch);
								}
								SCATCH;

								if (refObject.isDel() || nRet <= 0)
								{
									++nFailedCount;
									branchInfoSendFailMap.insert(std::make_pair(objectRefInfo->m_custom.stInfo.strBranchId, objectRefInfo->m_custom.stInfo.strName));
									continue;
								}

								//1.�·���Ʒ��Ϣ
								STRY;
								std::vector<ST_ProduceInfo> vecProduceInfo;
								if (GetNeedSyncProduceInfo(vecProduceInfo) && !vecProduceInfo.empty())
								{
									//SFTRACE("FTP�·�����", "FTP�Զ����¼����Ͳ���Ʒ��Ϣ��ʼ����������[%s]����ID[%s] \r\n", objectRefInfo->m_custom.stInfo.strName.c_str(), objectRefInfo->m_custom.stInfo.strBranchId.c_str());
									nRet = DoSyncProduceInfo(hClinet, vecProduceInfo);
								}
								SCATCH;

								////2.�·��ͻ���Ϣ
								//STRY;
								//std::vector<ST_ClientInfo> vecClientInfo;
								//if (GetNeedSyncClientInfo(vecClientInfo) && !vecClientInfo.empty())
								//{
								//	DoSyncClientInfo(hClinet, vecClientInfo);
								//}
								//SCATCH;

								if (nRet > 0)
								{
									SFTRACE("FTP�·�����", "[���ͳɹ�]FTP�Զ����¼�������Ϣ����������[%s]����ID[%s] \r\n", objectRefInfo->m_custom.stInfo.strName.c_str(), objectRefInfo->m_custom.stInfo.strBranchId.c_str());
									m_vecSyncEndBranchId.push_back(objectRefInfo->m_custom.stInfo.strBranchId);
									++nSucessCount;
								}
								else
								{
									branchInfoSendFailMap.insert(std::make_pair(objectRefInfo->m_custom.stInfo.strBranchId, objectRefInfo->m_custom.stInfo.strName));
									++nFailedCount;
								}	
							}
						}
					}
					SFTRACE("FTP�·�����", "FTP�Զ����¼����������Ϣ,�ɹ�����[%d]ʧ������[%d]δ��������[%d]��������[%d]��ǰ������[%d]\r\n", nSucessCount, nFailedCount, branchInfoTotalMap.size(),branchTotalCount, m_mapClientCount);
					for each(auto var in  branchInfoSendFailMap)
					{
						SFTRACE("FTP�·�����", "[����ʧ������] FTP�Զ��·�ʧ��,��������[%s]����ID[%s]\r\n", var.second.c_str(), var.first.c_str());
					}

					for each(auto var in  branchInfoTotalMap)
					{
						SFTRACE("FTP�·�����", "[δ��������] FTP�Զ����·�ʧ��,��������[%s]����ID[%s]\r\n", var.second.c_str(),var.first.c_str());
					}
					SFTRACE("FTP�·�����", "FTP�Զ����¼�������Ϣ ----------------  ����\r\n");
				}
				else if(!m_vecSyncEndBranchId.empty())
				{
					m_vecSyncEndBranchId.clear();
				}					
				m_ctLocalDayTime = CTime::GetCurrentTime();
				//HandleUserPurview();
			}
        }
		else if (m_nServerType == AppType_Client) //�Ƕ��������
        {
#if 0
			std::map<UINT64, std::shared_ptr<ObjectRefCount<ST_Login> > >  mapClientContext;
			STRY;
			readLock readLocker(m_csLockClientContext);
			mapClientContext = m_mapClientContext;
			SCATCH;

			m_mapClientCount = mapClientContext.size();
			for each(auto &var in mapClientContext)
			{
				readLock readLocker(m_csLockClientContext);
				auto iter = m_mapClientContext.find(var.first);
				if (iter != m_mapClientContext.end())
				{
					std::shared_ptr<ObjectRefCount<ST_Login> > objectRefInfo = iter->second;
					std::shared_ptr<RefCountInfo> refInfo = objectRefInfo->GetRefInfo();
					std::string strBranch = objectRefInfo->m_custom.stInfo.strBranchId;
					AutoObjectRefMgr refObject;
					if (refObject.AddRefCount(refInfo))
					{
						readLocker.unlock();
						HANDLE hClinet = (HANDLE)var.first;
						STRY;
						std::vector<ST_ClientInfo> vecClientInfo;
						if (GetNeedSyncClientInfo(vecClientInfo) && !vecClientInfo.empty())
						{
							DoSyncClientInfo(hClinet, vecClientInfo);
						}
						SCATCH;

						if (refObject.isDel())
							continue;
						STRY;
						std::vector<ST_BranchInfo> vecBranchInfo;
						std::vector<ST_EmployeeInfo> vecEmployeeInfo;
						if (m_pCache)
						{
							m_pComm->GetOfflineSyscData(vecBranchInfo, vecEmployeeInfo);
						}
						if (!vecBranchInfo.empty())
						{
							SFTRACE("FTP�·�����", "FTP�Զ����¼�����������Ϣ��ʼ��������Ϣ����[%s]������ϢID[%s] \r\n", objectRefInfo->m_custom.stInfo.strName.c_str(), objectRefInfo->m_custom.stInfo.strBranchId.c_str());
							DoSyncBranchInfo(hClinet, vecBranchInfo, 0, strBranch);
						}

						if (refObject.isDel())
							continue;

						if (!vecEmployeeInfo.empty())
						{
							if (!m_pCache && m_pCache->SendReqGetSocUserGroup()<0)
							{
								DISPLAY_LOG("MCģ��", "���������ȡ�û���ʧ��", "", "", 0)
									TTRACE("���������ȡ�û���ʧ��");
							}
							if (m_pCache->SendReqGetEquipmentPermission()< 0)
							{
								DISPLAY_LOG("MCģ��", "��������õ��豸Ȩ����Ϣʧ��", "", "", 0)
									TTRACE("��������õ��豸Ȩ����Ϣʧ��");
							}
							SFTRACE("FTP�·�����", "FTP�Զ����¼�����Ա����Ϣ��ʼ��������Ϣ����[%s]������ϢID[%s] \r\n", objectRefInfo->m_custom.stInfo.strName.c_str(), objectRefInfo->m_custom.stInfo.strBranchId.c_str());
							DoSyncEmployeeInfo(hClinet, vecEmployeeInfo, -1, strBranch);
						}

						if (refObject.isDel())
							continue;

						if (!vecEmployeeInfo.empty() || !vecBranchInfo.empty())
						{
							STRY;
							std::vector<ST_ProduceInfo> vecProduceInfo;
							if (GetNeedSyncProduceInfo(vecProduceInfo) && !vecProduceInfo.empty())
							{
								SFTRACE("FTP�·�����", "FTP�Զ����¼����Ͳ���Ʒ��Ϣ��ʼ����������[%s]����ID[%s] \r\n", objectRefInfo->m_custom.stInfo.strName.c_str(), objectRefInfo->m_custom.stInfo.strBranchId.c_str());
								DoSyncProduceInfo(hClinet, vecProduceInfo);
							}
							SCATCH;
						}
						SCATCH;
					}
				}
			}
#endif
        }


		STRY;
		boost::unique_lock<boost::mutex> lock(m_mutex);
		m_condition.wait_for(lock, boost::chrono::seconds(10 * 60));
		SCATCH;
	}
	SCATCH;
}
#pragma endregion

int XhBFISSyncServerRouterImp::DoSyncClientInfo(void* toAddr,std::vector<ST_ClientInfo>& vecInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (toAddr == NULL || vecInfo.empty())
	{
		TTRACE("%s[%d]ʧ�ܣ�����Ĳ���Ϊ��\r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	std::string strTemp;
	iBFIS_CommunicationInvoker invoke((HANDLE)toAddr);
	DWORD dwCmd = MSG_ISSUED_CLIENTINFO;
	int nSuccessCount = 0,nFailCount = 0;
	for each(auto clientinfo in vecInfo)
	{
		if(clientinfo.ConvertToString(strTemp))
		{
			if(invoke.Invoke(dwCmd,strTemp) >= 0) //=0��ʾ�Ѿ�����
			{
				if(m_pCache && m_pCache->SetSyncComplete(DataType_ClientInfo,clientinfo.strClientId))
				{
					TTRACE("ͬ���ϼ��·��ͻ���Ϣ[%s]%s_�ɹ�������ͬ��״̬�ɹ� \r\n",
						clientinfo.strName.c_str(),clientinfo.strClientId.c_str());
				}
				else
				{
					TTRACE("ͬ���ϼ��·��ͻ���Ϣ[%s]%s_�ɹ�������ͬ��״̬ʧ�� \r\n",
						clientinfo.strName.c_str(),clientinfo.strClientId.c_str());
				}
				nSuccessCount ++;
			}
			else
			{
				TTRACE("ͬ���ϼ��·��ͻ���Ϣ[%s]%s_ʧ�� \r\n",
					clientinfo.strName.c_str(),clientinfo.strClientId.c_str());
				nFailCount ++;
			}
		}
	}

	TTRACE("ͬ���ϼ��·��ͻ���Ϣ,�ɹ�:%d�Σ�ʧ��:%d�� \r\n",nSuccessCount,nFailCount);
	return 1;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::DoSyncProduceInfo(void* toAddr,std::vector<ST_ProduceInfo>& vecInfo,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	if (toAddr == NULL || vecInfo.empty())
	{
		TTRACE("%s[%d]ʧ�ܣ�����Ĳ���Ϊ��\r\n",__FUNCTION__,__LINE__);
		return -1;
	}

    vector<std::string> vecTemp;
	iBFIS_CommunicationInvoker invoke((HANDLE)toAddr);
	DWORD dwCmd = MSG_ISSUED_PRODUCEINFO;
	int nSuccessCount = 0,nFailCount = 0;
	//std::vector<std::string> logInfo;
	int nSucessCount = 0;
	int nFailedCount = 0;
	for each(auto produceinfo in vecInfo)
	{
		std::string strTemp;
		if(produceinfo.ConvertToString(strTemp))
		{
            vecTemp.push_back(std::move(strTemp));
			//std::string logDes = "�·���Ʒ��Ϣ ��Ʒ����[" + produceinfo.strName + "]��ƷID[" + produceinfo.strProduceId + "] --ִ��״̬[";
			//logInfo.push_back(std::move(logDes));
			if (vecTemp.size() > 1000)
			{
				Sleep(30);
				int nRet = invoke.Invoke(dwCmd, vecTemp);
				if (nRet > 0)
				{
					nSucessCount += 1000;
				}
				else
				{
					nFailedCount += 1000;
				}
				
				//for each(auto& log in logInfo)
				//{
				//	SFTRACE("FTP�·�����", "%s%s]  \r\n", log.c_str(), optStatus.c_str());
				//}
				//logInfo.clear();
				vecTemp.clear();
			}
		}
		else
		{
			SFTRACE("FTP�·�����", "ת��ʧ�� --- ��Ʒ����[%s]��ƷID[%s]\r\n", produceinfo.strName.c_str(), produceinfo.strProduceId.c_str());
		}
	}

	int currTempCount = vecTemp.size();
	if(currTempCount > 0)
	{
		
		int nRet = invoke.Invoke(dwCmd, vecTemp);
		if (nRet > 0)
		{
			nSucessCount += currTempCount;
		}
		else
		{
			nFailedCount += currTempCount;
		}
		//for each(auto& log in logInfo)
		//{
		//	SFTRACE("FTP�·�����", "%s%s]  \r\n", log.c_str(), optStatus.c_str());
		//}
	}
	SFTRACE("FTP�·�����", "�·���Ʒ��Ϣ����,���ͳɹ���Ŀ[%d]����ʧ����Ŀ[%d] \r\n", nSucessCount, nFailedCount);
	//TTRACE("ͬ���ϼ��·���Ʒ��Ϣ,�ɹ�:%d�Σ�ʧ��:%d�� \r\n",nSuccessCount,nFailCount);
	return nFailedCount == 0 ? 1 : -1;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::DoSyncBranchInfo(void* toAddr,std::vector<ST_BranchInfo>& vecInfo,DWORD_PTR dwReserved /*= 0*/, std::string strBranch)
{
    STRY;
    if (toAddr == NULL || vecInfo.empty())
    {
        TTRACE("%s[%d]ʧ�ܣ�����Ĳ���Ϊ��\r\n",__FUNCTION__,__LINE__);
        return -1;
    }
    std::string strTemp;
    vector<std::string> vecTemp;
    iBFIS_CommunicationInvoker invoke((HANDLE)toAddr);
    DWORD dwCmd = MSG_ISSUED_BRANCHINFO;
    int nSuccessCount = 0,nFailCount = 0;
    for each(auto branchinfo in vecInfo)
    {
		if (false == strBranch.empty())
		{
			if (branchinfo.strBranchId.compare(strBranch) != 0)
			{
				continue;
			}
		}

        if(branchinfo.ConvertToString(strTemp))
        {
            vecTemp.push_back(strTemp);
        }
		else
		{
			SFTRACE("FTP�·�����", "ת��ʧ�� --- ��������[%s]����ID[%s]\r\n", branchinfo.strName.c_str(), branchinfo.strBranchId.c_str());
		}
    }

	int nRet = invoke.Invoke(dwCmd, vecTemp);
	//std::string strStatus = nRet > 0 ? "�ɹ�" : "ʧ��";
	for each(auto branchinfo in vecInfo)
	{
		//SFTRACE("FTP�·�����", "�·�������Ϣ ��������[%s]����ID[%s] -- ִ��״̬[%s] \r\n", branchinfo.strName.c_str(), branchinfo.strBranchId.c_str(), strStatus.c_str());
		if (nRet > 0)
		{
			if (m_pCache)
				m_pCache->SetSyncComplete(DataType_BranceInfo, branchinfo.strBranchId);
		}
	}

	SFTRACE("FTP�·�����", "�·�������Ϣ����,���ݴ�С[%d]  --ִ��״̬[%d]\r\n", vecInfo.size(), nRet);

    if(nRet <= 0)
    {
		return -1;
    }
    return 1;
    SCATCH;
    return -1;
}
int XhBFISSyncServerRouterImp::DoSyncEmployeeInfo(void* toAddr,std::vector<ST_EmployeeInfo>& vecInfo,DWORD_PTR dwReserved /*= 0*/,std::string strBranch)
{
    STRY;
    if (toAddr == NULL || vecInfo.empty())
    {
        TTRACE("%s[%d]ʧ�ܣ�����Ĳ���Ϊ��\r\n",__FUNCTION__,__LINE__);
        return -1;
    }
    std::string strTemp;
    vector<std::string> vecTemp;
    iBFIS_CommunicationInvoker invoke((HANDLE)toAddr);
    DWORD dwCmd = MSG_ISSUED_EMPLOYEEINFO;
    for each(auto employeeinfo in vecInfo)
    {
		if (false == strBranch.empty())
		{
			if (employeeinfo.strBranchId.compare(strBranch) != 0)
				continue;
		}

        if(employeeinfo.ConvertToString(strTemp))
        {
            vecTemp.push_back(strTemp);
        }
		else
		{
			if (dwReserved != -1)
			{
				TTRACE("ת��ʧ�� --- Ա������[%s]Ա��ID[%s] \r\n", employeeinfo.strName.c_str(), employeeinfo.strEmployeeId.c_str());
			}
			else
			{
				SFTRACE("FTP�·�����", "ת��ʧ�� --- Ա������[%s]Ա��ID[%s] \r\n", employeeinfo.strName.c_str(), employeeinfo.strEmployeeId.c_str());
			}
		}
    }
	int nRet = invoke.Invoke(dwCmd, vecTemp);
	std::string strStatus = nRet > 0 ? "�ɹ�" : "ʧ��";

	if (dwReserved != -1)
	{
		TTRACE("ͬ���ϼ��·�Ա����Ϣ״̬[%s][%d] \r\n", strStatus.c_str(), nRet);
	}
	else
	{
		for each(auto employeeinfo in vecInfo)
		{
			//SFTRACE("FTP�·�����", "�·�Ա����Ϣ Ա������[%s]Ա��ID[%s] -- ִ��״̬[%s]  \r\n", employeeinfo.strName.c_str(), employeeinfo.strEmployeeId.c_str(), strStatus.c_str());
			if (m_pCache && m_pCache->SetSyncComplete(DataType_EmployeeInfo, employeeinfo.strEmployeeId))
			{
				;
				//TTRACE("ͬ���ϼ��·�Ա����Ϣ[%s]%s_�ɹ�������ͬ��״̬�ɹ� \r\n",
				//	employeeinfo.strName.c_str(), employeeinfo.strEmployeeId.c_str());
			}
		}
		SFTRACE("FTP�·�����", "�·�Ա����Ϣ����,���ݴ�С[%d]   --ִ��״̬[%d]\r\n", vecInfo.size(), nRet);
	}

    if(nRet <= 0) //=0��ʾ�Ѿ�����
    {
		return -1;
    }
    return 1;
    SCATCH;
    return -1;
}
int XhBFISSyncServerRouterImp::DoSyncRoleInfo(void* toAddr,std::vector<ST_RoleInfo>& vecInfo,DWORD_PTR dwReserved)
{
	STRY;
	if (toAddr == NULL || vecInfo.empty())
    {
        TTRACE("%s[%d]ʧ�ܣ�����Ĳ���Ϊ��\r\n",__FUNCTION__,__LINE__);
        return -1;
    }
    std::string strTemp;
    vector<std::string> vecTemp;
    iBFIS_CommunicationInvoker invoke((HANDLE)toAddr);
    DWORD dwCmd = MSG_ISSUED_ROLEINFO;
    for each(auto roleinfo in vecInfo)
    {
		if (roleinfo.nExtendedInfo == 1)
		{
			if(roleinfo.ConvertToString(strTemp))
			{
				vecTemp.push_back(strTemp);
			}
		}        
    }
    if(invoke.Invoke(dwCmd,vecTemp)>= 0) //=0��ʾ�Ѿ�����
    {
        for each(auto roleinfo in vecInfo)
        {
			if(m_pCache && m_pCache->SetSyncComplete(DataType_RoleInfo,roleinfo.strRoleInfoId))
            {
                TTRACE("ͬ���ϼ��·���Ʒ��ɫ[%s]%s_�ɹ�������ͬ��״̬�ɹ� \r\n",
                    roleinfo.strRoleName.c_str(),roleinfo.strBranchInfoId.c_str());
            }
        }
    }
    else
    {
        TTRACE("ͬ���ϼ��·���ɫ��Ϣʧ�ܣ�����ͬ��״̬ \r\n");
        /*TTRACE("ͬ���ϼ��·���Ʒ��Ϣ[%s]%s_ʧ�� \r\n",
            employeeinfo.strName.c_str(),employeeinfo.strEmployeeId.c_str());
        nFailCount ++;*/
    }
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::DoSyncRolePurviewInfo(void* toAddr,std::vector<ST_RolePurviewInfo>& vecInfo,DWORD_PTR dwReserved)
{
	STRY;
	if (toAddr == NULL || vecInfo.empty())
    {
        TTRACE("%s[%d]ʧ�ܣ�����Ĳ���Ϊ��\r\n",__FUNCTION__,__LINE__);
        return -1;
    }
    std::string strTemp;
	vector<std::string> vecTemp;
	iBFIS_CommunicationInvoker invoke((HANDLE)toAddr);
    DWORD dwCmd = MSG_ISSUED_ROLEPURVIEW;
	vector<ST_RoleInfo> vecRoleInfo;
	vector<string> vecRoleInfoId;
	vector<ST_RolePurviewInfo> vecFancRolePurviewInfo;
	string strRoleInfoId;
	/*if(m_pCache && m_pCache->QueryRoleInfo(vecRoleInfo))
	{
	for each(auto roleinfo in vecRoleInfo)
	{
	if(roleinfo.nExtendedInfo == -2 && roleinfo.strBranchInfoId == m_strLocalBranchId)
	{
	strRoleInfoId = roleinfo.strRoleInfoId;
	}
	}
	}
	for each(auto roleinfo in vecRoleInfo)
	{
	if(roleinfo.nExtendedInfo == -2 && roleinfo.strBranchInfoId != m_strLocalBranchId)
	{			
	vecRoleInfoId.push_back(roleinfo.strRoleInfoId);
	}
	}
	for each(auto rolepurviewinfo in vecInfo)
	{
	if(rolepurviewinfo.strRoleId == strRoleInfoId)
	{
	vecFancRolePurviewInfo.push_back(rolepurviewinfo);
	}
	}
	for each (auto roleinfoid in vecRoleInfoId)
	{
	for each(auto fancrolepurviewinfo in vecFancRolePurviewInfo)
	{
	fancrolepurviewinfo.strRoleId = roleinfoid;
	vecInfo.push_back(fancrolepurviewinfo);
	}
	}*/
	for each(auto rolepurviewinfo in vecInfo)
	{
		if(rolepurviewinfo.ConvertToString(strTemp))
		{
			vecTemp.push_back(strTemp);
		}
	}
    if(invoke.Invoke(dwCmd,vecTemp)>= 0) //=0��ʾ�Ѿ�����
    {
        for each(auto rolepurviewinfo in vecInfo)
        {
            if(m_pCache && m_pCache->SetSyncComplete(DataType_RolePurviewInfo,rolepurviewinfo.strRoleInfoPurviewId))
            {
                TTRACE("ͬ���ϼ��·���Ʒ��ɫȨ��%s_�ɹ�������ͬ��״̬�ɹ� \r\n",
                    rolepurviewinfo.strRoleInfoPurviewId.c_str());
            }
        }
    }
    else
    {
        TTRACE("ͬ���ϼ��·���ɫ��ϢȨ��ʧ�ܣ�����ͬ��״̬ \r\n");
        /*TTRACE("ͬ���ϼ��·���Ʒ��Ϣ[%s]%s_ʧ�� \r\n",
            employeeinfo.strName.c_str(),employeeinfo.strEmployeeId.c_str());
        nFailCount ++;*/
    }
	SCATCH;
	return -1;
}


// void XhBFISSyncServerRouterImp::Run()
// {
// 	STRY;
// 	//HANDLE hClient = NULL;
// 	Poco::FastMutex::ScopedLock lock(m_csLockClientContext);
// 	std::vector<HANDLE> vecClient;
// 	vecClient.clear();
// 	for(auto iter = m_mapClientContext.begin(); iter != m_mapClientContext.end(); iter ++)
// 	{
// 		if (iter->second.stInfo.strBranchId == m_stBranchInfo.strBranchId)
// 		{
// 			vecClient.push_back((HANDLE)(iter->first));
// 			//break;
// 		}
// 	}
// 	ST_BranchInfo stBranchInfo = m_stBranchInfo;
// 	//SetEvent(g_hThreadEvent);
// 	this->m_eventWaitThread.set();
// 	for(auto iter = vecClient.begin() ; iter != vecClient.end() ; iter ++)
// 	{
// 		iBFIS_CommunicationInvoker invoke(*iter);
// // 		if (m_pListctrl && m_pListctrl->GetParent())
// // 		{
// // 			//PostMessage((m_pListctrl->GetParent())->m_hWnd,MSG_BTN_SHOW,(WPARAM)(0),(LPARAM)(1));
// // 		}
// 		//1.0��ȡ������Ϣ
// #if 0
// 		//1.1�·���Ҫͬ�����û�����Ϣ
// 		vector<std::string> vecRoleInfo;
// 		DWORD_PTR dwpSync = QueryType_SyncAll;
// 		if(IssueSyncRoleInfo(vecRoleInfo,dwpSync) > 0)
// 		{
// 			if (vecRoleInfo.empty())
// 			{
// 				DISPLAY_LOG("ǿ��ͬ������","û����Ҫͬ�����û�����Ϣ","","",1);
// 			}
// 			else
// 			{
// 				DWORD_PTR dwCmd = MSG_ISSUED_ROLEINFO;
// 				int nRet = invoke.Invoke(dwCmd, vecRoleInfo);
// 				if (nRet <= 0)
// 				{
// 					char szBuf[255] = {0};
// 					sprintf(szBuf,"�·��û�����Ϣ���ͻ���%s[%s]ʧ��",stBranchInfo.strName.c_str(),
// 						stBranchInfo.strBranchId.c_str());
// 					DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",0);
// 				}
// 				else
// 				{
// 					char szBuf[255] = {0};
// 					sprintf(szBuf,"�·��û�����Ϣ���ͻ���%s[%s]�ɹ�",stBranchInfo.strName.c_str(),
// 						stBranchInfo.strBranchId.c_str());
// 					DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",1);
// 					ParseRoleInfoAndSetSyncState(vecRoleInfo);
// 				}
// 			}
// 		}
// 		else
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","��ȡ��Ҫͬ�����û�����Ϣʧ��","","",0);
// 		}
// 		//1.2�·���Ҫͬ����Ȩ����Ϣ
// 		vector<std::string> vecPurviewInfo;
// 		dwpSync = QueryType_SyncAll;
// 		if(IssueSyncPurviewInfo(vecPurviewInfo,dwpSync) > 0)
// 		{
// 			if (vecPurviewInfo.empty())
// 			{
// 				DISPLAY_LOG("ǿ��ͬ������","û����Ҫͬ����Ȩ����Ϣ","","",1);
// 			}
// 			else
// 			{
// 				DWORD_PTR dwCmd = MSG_ISSUED_PURVIEWINFO;
// 				int nRet = invoke.Invoke(dwCmd, vecPurviewInfo);
// 				if (nRet <= 0)
// 				{
// 					char szBuf[255] = {0};
// 					sprintf(szBuf,"�·�Ȩ����Ϣ���ͻ���%s[%s]ʧ��",stBranchInfo.strName.c_str(),
// 						stBranchInfo.strBranchId.c_str());
// 					DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",0);
// 				}
// 				else
// 				{
// 					char szBuf[255] = {0};
// 					sprintf(szBuf,"�·�Ȩ����Ϣ���ͻ���%s[%s]�ɹ�",stBranchInfo.strName.c_str(),
// 						stBranchInfo.strBranchId.c_str());
// 					DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",1);
// 					ParsePurviewInfoAndSetSyncState(vecPurviewInfo);
// 				}
// 			}
// 		}
// 		else
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","��ȡ��Ҫͬ����Ȩ����Ϣʧ��","","",0);
// 		}
// 		//1.3�·���Ҫͬ�����û���Ȩ����Ϣ
// 		vector<std::string> vecRolePurviewInfo;
// 		dwpSync = QueryType_SyncAll;
// 		if(IssueSyncRolePurviewInfo(vecRolePurviewInfo,dwpSync) > 0)
// 		{
// 			if (vecRolePurviewInfo.empty())
// 			{
// 				DISPLAY_LOG("ǿ��ͬ������","û����Ҫͬ�����û���Ȩ����Ϣ","","",1);
// 			}
// 			else
// 			{
// 				DWORD_PTR dwCmd = MSG_ISSUED_ROLEPURVIEW;
// 				int nRet = invoke.Invoke(dwCmd, vecRolePurviewInfo);
// 				if (nRet <= 0)
// 				{
// 					char szBuf[255] = {0};
// 					sprintf(szBuf,"�·��û���Ȩ����Ϣ���ͻ���%s[%s]ʧ��",stBranchInfo.strName.c_str(),
// 						stBranchInfo.strBranchId.c_str());
// 					DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",0);
// 				}
// 				else
// 				{
// 					char szBuf[255] = {0};
// 					sprintf(szBuf,"�·��û���Ȩ����Ϣ���ͻ���%s[%s]�ɹ�",stBranchInfo.strName.c_str(),
// 						stBranchInfo.strBranchId.c_str());
// 					DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",1);
// 					ParseRolePurviewInfoAndSetSyncState(vecRolePurviewInfo);
// 				}
// 			}
// 		}
// 		else
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","��ȡ��Ҫͬ�����û���Ȩ����Ϣʧ��","","",0);
// 		}
// #endif
// 		//1.4��ȡ�ͻ���Ϣ
// 		vector<std::string> vecClientInfo;
// 		DWORD_PTR dwCmd = MSG_UPLOAD_CLIENTINFO;
// 		int nRet = 0;
// 		nRet = invoke.Invoke(dwCmd, vecClientInfo);
// 		if (nRet <= 0)
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","��ȡ��Ҫͬ���ͻ���Ϣʧ��","","",0);
// 		}
// 		else if (vecClientInfo.empty())
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","û����Ҫͬ���Ŀͻ���Ϣ","","",1);
// 		}
// 		else
// 		{
// 			ParseClientInfo(vecClientInfo);
// 			//�·��ͻ���Ϣ
// 			vector<std::string> vecClientInfo;
// 			DWORD_PTR dwpSync = QueryType_SyncAll;
// 			if(IssueSyncClientInfo(vecClientInfo,dwpSync) > 0)
// 			{
// 				if(vecClientInfo.empty())
// 				{
// 					DISPLAY_LOG("ǿ��ͬ������","û����Ҫͬ���Ŀͻ���Ϣ","","",1);
// 				}
// 				else
// 				{
// 					DWORD_PTR dwCmd = MSG_GET_CLIENTINFO;
// 					int nRet = invoke.Invoke(dwCmd, vecClientInfo);
// 					if (nRet <= 0)
// 					{
// 						char szBuf[255] = {0};
// 						sprintf(szBuf,"�·��ͻ���Ϣ���ͻ���%s[%s]ʧ��",stBranchInfo.strName.c_str(),
// 							stBranchInfo.strBranchId.c_str());
// 						DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",0);
// 					}
// 					else
// 					{
// 						char szBuf[255] = {0};
// 						sprintf(szBuf,"�·��ͻ���Ϣ���ͻ���%s[%s]�ɹ�",stBranchInfo.strName.c_str(),
// 							stBranchInfo.strBranchId.c_str());
// 						DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",1);
// 						ParseClientInfoAndSetSyncState(vecClientInfo);
// 					}
// 				}
// 			}
// 			else
// 			{
// 				DISPLAY_LOG("ǿ��ͬ������","��ȡ��Ҫͬ���Ŀͻ���Ϣʧ��","","",0);
// 			}
// 			//			}
// 		}
// 		//1.5��ȡԱ����Ϣ
// 		vector<std::string> vecEmployeeInfo;
// 		dwCmd = MSG_UPLOAD_EMPLOYEEINFO;
// 		nRet = 0;
// 		nRet = invoke.Invoke(dwCmd, vecEmployeeInfo);
// 		if (nRet <= 0)
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","��ȡ��Ҫͬ����Ա����Ϣʧ��","","",0);
// 		}
// 		else if (vecEmployeeInfo.empty())
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","û����Ҫͬ����Ա����Ϣ","","",1);
// 		}
// 		else
// 		{
// 			ParseEmployeeInfo(vecEmployeeInfo);
// 			//��ȡԱ��Ȩ����Ϣ
// 			vector<std::string> vecEmployeePurviewInfo;
// 			dwCmd = MSG_UPLOAD_EMPLOYEEPURVIEWINFO;
// 			nRet = 0;
// 			nRet = invoke.Invoke(dwCmd,vecEmployeePurviewInfo);
// 			if (nRet <= 0)
// 			{
// 				DISPLAY_LOG("ǿ��ͬ������","��ȡ��Ҫͬ����Ա��Ȩ����Ϣʧ��","","",0);
// 			}
// 			else
// 			{
// 				if (!m_pCache || m_pCache->QuerySqlStatus() <= 0)
// 				{
// 					DISPLAY_LOG("ǿ��ͬ������","û���������ݿ�","","",0);
// 				}
// 				else
// 				{
// 					if (!DelEmployeePurviewInfo(vecEmployeeInfo))
// 					{
// 						
// 					}
// 					else
// 					{
// 						if (vecEmployeePurviewInfo.empty())
// 						{
// 							DISPLAY_LOG("ǿ��ͬ������","û����Ҫͬ����Ա��Ȩ����Ϣ","","",1);
// 						}
// 						else
// 						{
// 							for (auto iter = vecEmployeePurviewInfo.begin();  iter != vecEmployeePurviewInfo.end() ; iter ++)
// 							{
// 								BFIS::EmployeePurviewInfo msg;
// 								bool bSuccess = msg.ParseFromString(*iter);
// 								if(!bSuccess)
// 								{
// 									DISPLAY_LOG("ǿ��ͬ��","����Ա��Ȩ����Ϣʧ��","","",0);
// 									continue;
// 								}
// 								ST_EmployeePurviewInfo stEmployeePurviewInfo(msg);
// 								int nRet = m_pCache->ManageEmployeePurviewInfo(DBO_ADD,stEmployeePurviewInfo);
// 								CString strMsg = _T("");
// 								strMsg.Format(_T("���Ա��Ȩ����Ϣ%s��Ա��Ȩ����ϢId��%s"),nRet == QueryFail ? "ʧ��":"�ɹ�",stEmployeePurviewInfo.strEmployeePurviewId);
// 								DISPLAY_LOG("ǿ��ͬ������",strMsg.GetBuffer(0),"","",nRet == QueryFail ? 0 : 1);
// 								strMsg.ReleaseBuffer();
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 		//�·���Ҫͬ���Ĳ�Ʒ��Ϣ
// 		vector<std::string> vecProduceInfo;
// 		DWORD_PTR dwpSync = QueryType_SyncAll;
// 		if(IssueSyncProduceInfo(vecProduceInfo,dwpSync) > 0)
// 		{
// 			if(vecProduceInfo.empty())
// 			{
// 				DISPLAY_LOG("ǿ��ͬ������","û����Ҫͬ���Ĳ�Ʒ��Ϣ","","",1);
// 			}
// 			else
// 			{
// 				DWORD_PTR dwCmd = MSG_ISSUED_PRODUCEINFO;
// 				int nRet = invoke.Invoke(dwCmd, vecProduceInfo);
// 				if (nRet <= 0)
// 				{
// 					char szBuf[255] = {0};
// 					sprintf(szBuf,"�·���Ʒ��Ϣ���ͻ���%s[%s]ʧ��",stBranchInfo.strName.c_str(),
// 						stBranchInfo.strBranchId.c_str());
// 					DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",0);
// 				}
// 				else
// 				{
// 					char szBuf[255] = {0};
// 					sprintf(szBuf,"�·���Ʒ��Ϣ���ͻ���%s[%s]�ɹ�",stBranchInfo.strName.c_str(),
// 						stBranchInfo.strBranchId.c_str());
// 					DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",1);
// 					//����ͬ���ɹ�
// 					ParseProduceInfoAndSetSyncState(vecProduceInfo);
// 				}
// 			}
// 		}
// 		else
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","��ȡ��Ҫͬ���Ĳ�Ʒ��Ϣʧ��","","",0);
// 		}
// 
// 		//��ȡҵ����Ϣ
// 		vector<std::string> vecBuinessInfo;
// 		dwCmd = MSG_UPLOAD_BUSINESSINFO;
// 		nRet = invoke.Invoke(dwCmd, vecBuinessInfo);
// 		if (nRet <= 0)
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","��ȡ��Ҫͬ����ҵ����Ϣʧ��","","",0);
// 		}
// 		else if (vecBuinessInfo.empty())
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","û����Ҫͬ����ҵ����Ϣ","","",1);
// 		}
// 		else
// 		{
// 			//
// // 			int nRes = OnGotUpLoadBusinessInfo(vecBuinessInfo);
// // 			char szBuf[255] = {0};
// // 			sprintf(szBuf,"�յ��ͻ���%s[%s]�ϴ���ҵ����Ϣ,����%s",stBranchInfo.strName.c_str(),
// // 				stBranchInfo.strBranchId.c_str(),nRes > 0 ? "�ɹ�":"ʧ��");
// // 			DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",nRes > 0 ? 1:0);
// 			ParseBusinessInfo(vecBuinessInfo);
// 		}
// 		//��ȡҵ��¼����Ϣ
// 		vector<std::string> vecBuinessFileInfo;
// 		dwCmd = MSG_UPLOAD_BUSINESSFILEINFO;
// 		nRet = 0;
// 		nRet = invoke.Invoke(dwCmd, vecBuinessFileInfo);
// 		if (nRet <= 0)
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","��ȡ��Ҫͬ����ҵ��¼����Ϣʧ��","","",0);
// 		}
// 		else if (vecBuinessFileInfo.empty())
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","û����Ҫͬ����ҵ��¼����Ϣ","","",1);
// 		}
// 		else
// 		{
// // 			int nRes = OnGotUpLoadBusinessFileInfo(vecBuinessFileInfo);
// // 			char szBuf[255] = {0};
// // 			sprintf(szBuf,"�յ��ͻ���%s[%s]�ϴ���ҵ��¼����Ϣ,����%s",stBranchInfo.strName.c_str(),
// // 				stBranchInfo.strBranchId.c_str(),nRes > 0 ? "�ɹ�":"ʧ��");
// // 			DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",nRes > 0 ? 1:0);
// 			ParseBusinessFileInfo(vecBuinessFileInfo);
// 		}
// 		//��ȡҵ���ϵ��Ϣ
// 		vector<std::string> vecBuinessRelationInfo;
// 		dwCmd = MSG_UPLOAD_BUSINESSRELATEINFO;
// 		nRet = 0;
// 		nRet = invoke.Invoke(dwCmd, vecBuinessRelationInfo);
// 		if (nRet <= 0)
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","��ȡ��Ҫͬ����ҵ���ϵ��Ϣʧ��","","",0);
// 		}
// 		else if (vecBuinessRelationInfo.empty())
// 		{
// 			DISPLAY_LOG("ǿ��ͬ������","û����Ҫͬ����ҵ���ϵ��Ϣ","","",1);
// 		}
// 		else
// 		{
// // 			int nRes = OnGotUpLoadBusinessRelateInfo(vecBuinessRelationInfo);
// // 			char szBuf[255] = {0};
// // 			sprintf(szBuf,"�յ��ͻ���%s[%s]�ϴ���ҵ���ϵ��Ϣ,����%s",stBranchInfo.strName.c_str(),
// // 				stBranchInfo.strBranchId.c_str(),nRes > 0 ? "�ɹ�":"ʧ��");
// // 			DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",nRes > 0 ? 1:0);
// 			ParseBusinessRelateInfo(vecBuinessRelationInfo);
// 		}
// 
// 		if (m_pListctrl && m_pListctrl->GetParent())
// 		{
// 			//PostMessage((m_pListctrl->GetParent())->m_hWnd,MSG_BTN_SHOW,(WPARAM)(0),(LPARAM)(-1));
// 		}
// 	}
// 	if(vecClient.empty())
// 	{
// 		char szBuf[255] = {0};
// 		sprintf(szBuf,"�·�ʧ��:û��%s[%s]���¼�����������",stBranchInfo.strName.c_str(),stBranchInfo.strBranchId.c_str());
// 		DISPLAY_LOG("ǿ��ͬ������",szBuf,"","",0);
// 	}
// 	DISPLAY_LOG("ǿ��ͬ������","ǿ��ͬ�����","","",1);
// 	SCATCH;
// }

void XhBFISSyncServerRouterImp::ParseClientInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	vector<std::string> vecNew = vecStr;
	vecStr.clear();
	for (auto iter = vecNew.begin() ; iter != vecNew.end() ; iter ++)
	{
		/*
		string strClientId;
		string strName;
		string strCredenitial;
		string strPhone;
		string strContent;
		int	   nExtendedInfo;
		string strExtendedInfo1;
		string strExtendedInfo2;
		*/
		BFIS::ClientInfo msg;
		msg.ParseFromString(*iter);
		ST_ClientInfo stClientInfo;
		stClientInfo.strClientId = msg.strclientid();
		stClientInfo.strName = msg.strname();
        stClientInfo.strCredenitialsType = msg.strcredenitialstype();
		stClientInfo.strCredenitial = msg.strcredenitial();
		stClientInfo.strPhone = msg.strphone();
		stClientInfo.strContent = msg.strcontent();
		stClientInfo.nExtendedInfo = msg.nextendedinfo();
		stClientInfo.strExtendedInfo1 = msg.strextendedinfo1();
		stClientInfo.strExtendedInfo2 = msg.strextendedinfo2();
		int nRet = OnGotUpLoadClientInfo(stClientInfo);
		TTRACE(_T("%s[%d]:�յ����Կͻ����ϴ��ͻ���Ϣ���ͻ�ID:%s�����ݿ��������ֵ:%d\r\n"),__FUNCTION__,__LINE__,stClientInfo.strClientId.c_str(),nRet);
		if (nRet > 0)
		{
			vecStr.push_back(*iter);
		}
	}
	SCATCH;
}
void XhBFISSyncServerRouterImp::ParseBusinessInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	vector<std::string> vecNew = vecStr;
	vecStr.clear();
	for (auto iter = vecNew.begin() ; iter != vecNew.end() ; iter ++)
	{
		/*
		string strBusinessInfoId;
		string strDateTime;
		string strBranchId;
		string strClientId;
		string strEmployeeId;
		string strProduceId;
		string strSubEquipmentId;
		int    nExtendedInfo;
		string strExtendedInfo1;
		string strExtendedInfo2;
		string strSubEquipmentIcmSign;
		*/
		BFIS::BusinessInfo msg;
		msg.ParseFromString(*iter);
		ST_BusinessInfo stBusinessInfo;
		stBusinessInfo.strBusinessInfoId = msg.strbusinessinfoid();
		stBusinessInfo.strDateTime = msg.strdatetime();
		stBusinessInfo.strBranchId = msg.strbranchid();
		stBusinessInfo.strClientId = msg.strclientid();
		stBusinessInfo.strEmployeeId = msg.stremployeeid();
		stBusinessInfo.strProduceId = msg.strproduceid();
		stBusinessInfo.strSubEquipmentId = msg.strsubequipmentid();
		stBusinessInfo.nExtendedInfo = msg.nextendedinfo();
		stBusinessInfo.strExtendedInfo1 = msg.strextendedinfo1();
		stBusinessInfo.strExtendedInfo2 = msg.strextendedinfo2();
		stBusinessInfo.strSubEquipmentIcmSign = msg.strsubequipmenticmsign();
		stBusinessInfo.strSerialNumber = msg.strserialnumber();
		stBusinessInfo.nMigrated = msg.nmigrated();
		stBusinessInfo.strFileCenter = msg.strfilecenter();
        stBusinessInfo.strBusinessType = msg.strbusinesstype();
        stBusinessInfo.strCardNumber = msg.strcardnumber();
        stBusinessInfo.nMarkerType = msg.nmarkertype();
		stBusinessInfo.strMediumType = msg.strmediumtype();
		stBusinessInfo.strMediumNum = msg.strmediumnum();
		int nRet = OnGotUpLoadBusinessInfo(stBusinessInfo);
		TTRACE(_T("%s[%d]:�յ����Կͻ����ϴ�ҵ����Ϣ��ҵ��ID:%s�����ݿ��������ֵ:%d\r\n"),__FUNCTION__,__LINE__,stBusinessInfo.strBusinessInfoId,nRet);
		if (nRet > 0)
		{
			vecStr.push_back(*iter);
		}
	}
	SCATCH;
}
void XhBFISSyncServerRouterImp::ParseBusinessFileInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	vector<std::string> vecNew = vecStr;
	vecStr.clear();
	for (auto iter = vecNew.begin() ; iter != vecNew.end() ; iter ++)
	{
		/*
		string strRecordId;
		string strBusinessInfoId;
		int    nType;
		string strFileId;
		string strRecordBegin;
		string strRecordEnd;
		int    nExtendedInfo;
		string strExtendedInfo1;
		string strExtendedInfo2;
		*/
		BFIS::BusinessFileInfo msg;
		msg.ParseFromString(*iter);
		ST_BusinessFileInfo stBusinessFileInfo;
		stBusinessFileInfo.strRecordId = msg.strrecordid();
		stBusinessFileInfo.strBusinessInfoId = msg.strbusinessinfoid();
		stBusinessFileInfo.nType = msg.ntype();
		stBusinessFileInfo.strFileId = msg.strfileid();
		stBusinessFileInfo.strRecordBegin = msg.strrecordbegin();
		stBusinessFileInfo.strRecordEnd = msg.strrecordend();
		stBusinessFileInfo.nExtendedInfo = msg.nextendedinfo();
		stBusinessFileInfo.strExtendedInfo1 = msg.strextendedinfo1();
		stBusinessFileInfo.strExtendedInfo2 = msg.strextendedinfo2();
		stBusinessFileInfo.nMigrated = msg.nmigrated();
		int nRet = OnGotUpLoadBusinessFileInfo(stBusinessFileInfo);
		TTRACE(_T("%s[%d]:�յ����Կͻ����ϴ�ҵ���ļ���Ϣ��ҵ���ļ�ID:%s�����ݿ��������ֵ:%d\r\n"),
			__FUNCTION__,__LINE__,stBusinessFileInfo.strRecordId,nRet);
		if (nRet > 0)
		{
			vecStr.push_back(*iter);
		}
	}
	SCATCH;
}
void XhBFISSyncServerRouterImp::ParseBusinessRelateInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	vector<std::string> vecNew = vecStr;
	vecStr.clear();
	for (auto iter = vecNew.begin() ; iter != vecNew.end() ; iter ++)
	{
		/*
		string strBusinessRelateInfoId;
		string strBusinessInfoId;
		int	   nRelateType;
		string strRelate1;
		string strRelate2;
		string strRelate3;
		*/
		BFIS::BusinessRelateInfo msg;
		msg.ParseFromString(*iter);
		ST_BusinessRelateInfo stBusinessRelateInfo;
		stBusinessRelateInfo.strBusinessRelateInfoId = msg.strbusinessrelateinfoid();
		stBusinessRelateInfo.strBusinessInfoId = msg.strbusinessinfoid();
		stBusinessRelateInfo.nRelateType = msg.nrelatetype();
		stBusinessRelateInfo.strRelate1 = msg.strrelate1();
		stBusinessRelateInfo.strRelate2 = msg.strrelate2();
		stBusinessRelateInfo.strRelate3 = msg.strrelate3();
		int nRet = OnGotUpLoadBusinessRelateInfo(stBusinessRelateInfo);
		TTRACE(_T("%s[%d]:�յ����Կͻ����ϴ�ҵ�������Ϣ��ҵ�������ϢID:%s�����ݿ��������ֵ:%d\r\n"),
			__FUNCTION__,__LINE__,stBusinessRelateInfo.strBusinessRelateInfoId,nRet);
		if (nRet > 0)
		{
			vecStr.push_back(*iter);
		}
	}
	SCATCH;
}
void XhBFISSyncServerRouterImp::ParseEmployeeInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	vector<std::string> vecNew = vecStr;
	vecStr.clear();
	for (auto iter = vecNew.begin() ; iter != vecNew.end() ; iter ++)
	{
		/*	
		string strEmployeeId;
		string strBranchId;
		string strName;
		string strPassword;
		string strCardId;
		string strRoleId;
		string strPhone;
		int	   nExtendedInfo;
		string strExtendedInfo1;
		string strExtendedInfo2;*/
		BFIS::EmployeeInfo msg;
		msg.ParseFromString(*iter);
		ST_EmployeeInfo stEmployeeInfo;
		stEmployeeInfo.strEmployeeId = msg.stremployeeid();
		stEmployeeInfo.strBranchId   = msg.strbranchid();
		stEmployeeInfo.strName       = msg.strname();
		stEmployeeInfo.strPassword   = msg.strpassword();
		stEmployeeInfo.strCardId     = msg.strcardid();
		stEmployeeInfo.strRoleId     = msg.strroleid();
		stEmployeeInfo.strPhone      = msg.strphone();
		stEmployeeInfo.nExtendedInfo = msg.nextendedinfo();
		stEmployeeInfo.strExtendedInfo1 = msg.strextendedinfo1();
		stEmployeeInfo.strExtendedInfo2 = msg.strextendedinfo2();
		stEmployeeInfo.nFlag = msg.nflag();
        stEmployeeInfo.stPasswordEidtTime = msg.stpasswordeidttime();
        stEmployeeInfo.strJDBRID = msg.strjdbrid();
        stEmployeeInfo.strTLNUM = msg.strtlnum();
        stEmployeeInfo.strTEL = msg.strtel();
        stEmployeeInfo.strGW = msg.strgw();
        stEmployeeInfo.strSTS = msg.strsts();
        stEmployeeInfo.strTLINST = msg.strtlinst();
        stEmployeeInfo.strUSERNAME = msg.strusername();
        stEmployeeInfo.strROLENAME = msg.strrolename();
        stEmployeeInfo.strUSERSTATUS = msg.struserstatus();
		stEmployeeInfo.nPassErrorCount = msg.npasserrorcount();
		int nRet = OnGotUpLoadEmployeeInfo(stEmployeeInfo);
		TTRACE(_T("%s[%d]:�յ����Կͻ����ϴ�Ա����Ϣ��Ա����ϢID:%s�����ݿ��������ֵ:%d\r\n"),
			__FUNCTION__,__LINE__,stEmployeeInfo.strEmployeeId,nRet);
		if (nRet > 0)
		{
			vecStr.push_back(*iter);
		}
	}
	SCATCH;
}

void XhBFISSyncServerRouterImp::ParseClientInfoAndSetSyncState(vector<std::string>& vecStr,bool bstate /*= true*/,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	int nRet = 0;
	for (auto iter = vecStr.begin() ; iter != vecStr.end() ; iter ++)
	{
#pragma region ��������
		/*
		string strClientId;
		string strName;
		string strCredenitial;
		string strPhone;
		string strContent;
		int	   nExtendedInfo;
		string strExtendedInfo1;
		string strExtendedInfo2;
		*/
		BFIS::ClientInfo msg;
		msg.ParseFromString(*iter);
		ST_ClientInfo stClientInfo;
		stClientInfo.strClientId = msg.strclientid();
		stClientInfo.strName = msg.strname();
        stClientInfo.strCredenitialsType = msg.strcredenitialstype();
		stClientInfo.strCredenitial = msg.strcredenitial();
		stClientInfo.strPhone = msg.strphone();
		stClientInfo.strContent = msg.strcontent();
		stClientInfo.nExtendedInfo = msg.nextendedinfo();
		stClientInfo.strExtendedInfo1 = msg.strextendedinfo1();
		stClientInfo.strExtendedInfo2 = msg.strextendedinfo2();
#pragma endregion
		nRet = m_pCache->SetSyncComplete(DataType_ClientInfo, stClientInfo.strClientId);
		TTRACE(_T("%s[%d]:���ÿͻ���Ϣͬ����ʶ[%s],ID:%s,���ݿⷵ��ֵ��%d\r\n")
			,__FUNCTION__,__LINE__,nRet>0?"�ɹ�":"ʧ��",stClientInfo.strClientId.c_str(),nRet);
	}
	SCATCH;
}
void XhBFISSyncServerRouterImp::ParseProduceInfoAndSetSyncState(vector<std::string>& vecStr,bool bstate /*= true*/,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	int nRet = 0;
	for (auto iter = vecStr.begin() ; iter != vecStr.end() ; iter ++)
	{
#pragma region ��������
		BFIS::ProduceInfo msg;
		msg.ParseFromString(*iter);
		/*
		string strProduceId;
		string strName;
		string strProduceCode;
		string strPeriod;
		string strRevenue;
		int    nMiniAmount;
		string strRiskLevel;
		string strSerialNumber;
		string strPublishBeinTime;
		string strPublishEndTime;
		string strProductionType;
		string strApplicableCustomer;
		string strRevenueType;
		string strIncrementMoney;
		string strCurrentyType;
		string strSealsBranch;
		string strRevenueInitialDay;
		string strDeadLine;
		string strPaymentDay;
		string strTrusteeFee;
		string strCommissionCharge;
		string strTrustee;
		string strOverheadCharge;
		string strRevenueCalculation;
		string strContent;
		int    nMaxTime;
		int    nMineTime;
		int    nStandardTime;
		string strPrequestion;
		int    nIsPublished;
		int    nIsEnabled;
		int	   nExtendedInfo;
		string strExtendedInfo1;
		string strExtendedInfo2;
		*/
		ST_ProduceInfo stProduceInfo;
		stProduceInfo.strProduceId			=	msg.strproduceid();        
		stProduceInfo.strName				= 	msg.strname(); 			
		stProduceInfo.strProduceCode		= 	msg.strproducecode(); 		
		stProduceInfo.nPeriod				= 	msg.nperiod(); 			
		stProduceInfo.strRevenue			= 	msg.strrevenue(); 			
		stProduceInfo.nMiniAmount			= 	msg.nminiamount(); 		
		stProduceInfo.strRiskLevel			= 	msg.strrisklevel(); 		
		stProduceInfo.strSerialNumber		= 	msg.strserialnumber(); 	
		stProduceInfo.strPublishBeinTime	= 	msg.strpublishbeintime(); 	
		stProduceInfo.strPublishEndTime		= 	msg.strpublishendtime(); 	
		stProduceInfo.strProductionType		= 	msg.strproductiontype(); 	
		stProduceInfo.strApplicableCustomer =	msg.strapplicablecustomer(); 
		stProduceInfo.strRevenueType		= 	msg.strrevenuetype(); 		
		stProduceInfo.strIncrementMoney		= 	msg.strincrementmoney(); 	
		stProduceInfo.strCurrentyType		= 	msg.strcurrentytype(); 	
		stProduceInfo.strSealsBranch		= 	msg.strsealsbranch(); 		
		stProduceInfo.strRevenueInitialDay  =	msg.strrevenueinitialday();
		stProduceInfo.strDeadLine			= 	msg.strdeadline(); 		
		stProduceInfo.strPaymentDay			= 	msg.strpaymentday(); 		
		stProduceInfo.strTrusteeFee			= 	msg.strtrusteefee(); 		
		stProduceInfo.strCommissionCharge	=	msg.strcommissioncharge(); 
		stProduceInfo.strTrustee			= 	msg.strtrustee(); 			
		stProduceInfo.strOverheadCharge		= 	msg.stroverheadcharge(); 	
		stProduceInfo.strRevenueCalculation =	msg.strrevenuecalculation(); 
		stProduceInfo.strContent			= 	msg.strcontent(); 			
		stProduceInfo.nMaxTime				= 	msg.nmaxtime(); 			
		stProduceInfo.nMineTime				= 	msg.nminetime(); 			
		stProduceInfo.nStandardTime			= 	msg.nstandardtime(); 		
		stProduceInfo.strPrequestion		= 	msg.strprequestion(); 		
		stProduceInfo.nIsPublished			= 	msg.nispublished(); 		
		stProduceInfo.nIsEnabled			= 	msg.nisenabled(); 			
		stProduceInfo.nExtendedInfo			= 	msg.nextendedinfo(); 		
		stProduceInfo.strExtendedInfo1		= 	msg.strextendedinfo1(); 	
		stProduceInfo.strExtendedInfo2		= 	msg.strextendedinfo2(); 
		stProduceInfo.nEnableMigrated		=	msg.nenablemigrated();
		stProduceInfo.nRecordExistDays		=	msg.nrecordexistdays();
#pragma endregion
		nRet = m_pCache->SetSyncComplete(DataType_ProduceInfo, stProduceInfo.strProduceId);
		TTRACE(_T("%s[%d]:���ò�Ʒ��Ϣͬ����ʶ[%s],ID:%s,���ݿⷵ��ֵ��%d\r\n")
			,__FUNCTION__,__LINE__,nRet>0?"�ɹ�":"ʧ��",stProduceInfo.strProduceId.c_str(),nRet);
	}
	SCATCH;
}
void XhBFISSyncServerRouterImp::ParseRoleInfoAndSetSyncState(vector<std::string>& vecStr,bool bstate /*= true*/,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	int nRet = 0;
	for (auto iter = vecStr.begin() ; iter != vecStr.end() ; iter ++)
	{
		ST_RoleInfo stRoleInfo;
#pragma region ��������
		BFIS::RoleInfo msg;
		msg.ParseFromString(*iter);
		/*
		string strRoleInfoId;
		string strRoleName;
		int    nRoleLevel;
		int	   nExtendedInfo;
		string strExtendedInfo1;
		string strExtendedInfo2;
		*/
		stRoleInfo.strRoleInfoId = msg.strroleinfoid();
		stRoleInfo.strRoleName   = msg.strrolename();
		stRoleInfo.nRoleLevel    = msg.nrolelevel();
		stRoleInfo.nExtendedInfo = msg.nextendedinfo();
		stRoleInfo.strExtendedInfo1 = msg.strextendedinfo1();
		stRoleInfo.strExtendedInfo2 = msg.strextendedinfo2();
		stRoleInfo.strBranchInfoId = msg.strbranchinfoid();
		stRoleInfo.nFlag = msg.nflag();
#pragma endregion
		nRet = m_pCache->SetSyncComplete(DataType_RoleInfo, stRoleInfo.strRoleInfoId);
		TTRACE(_T("%s[%d]:�����û�����Ϣͬ����ʶ[%s],ID:%s,���ݿⷵ��ֵ��%d\r\n")
			,__FUNCTION__,__LINE__,nRet>0?"�ɹ�":"ʧ��",stRoleInfo.strRoleInfoId.c_str(),nRet);
	}
	SCATCH;
}
#if 0
void XhBFISSyncServerRouterImp::ParsePurviewInfoAndSetSyncState(vector<std::string>& vecStr,bool bstate /*= true*/,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	int nRet = 0;
	for (auto iter = vecStr.begin() ; iter != vecStr.end() ; iter ++)
	{
		ST_PurviewInfo stPurviewInfo;
#pragma region ��������
		BFIS::PurviewInfo msg;
		msg.ParseFromString(*iter);
		/*
		string strPurviewInfoId;
		string strParentPurviewId;
		string strPurviewCode;
		string strDescription;
		string strExtendedInfo1;
		string strExtendedInfo2;
		*/
		stPurviewInfo.strPurviewInfoId = msg.strpurviewinfoid();
		stPurviewInfo.strParentPurviewId = msg.strparentpurviewid();
		stPurviewInfo.strPurviewCode   = msg.strpurviewcode();
		stPurviewInfo.strDescription = msg.strdescription();
		stPurviewInfo.strExtendedInfo1 = msg.strextendedinfo1();
		stPurviewInfo.strExtendedInfo2 = msg.strextendedinfo2();
#pragma endregion 
		nRet = m_pCache->SetSyncComplete(DataType_PurviewInfo, stPurviewInfo.strPurviewInfoId);
		TTRACE(_T("%s[%d]:����Ȩ����Ϣͬ����ʶ[%s],ID:%s,���ݿⷵ��ֵ��%d\r\n")
			,__FUNCTION__,__LINE__,nRet>0?"�ɹ�":"ʧ��",stPurviewInfo.strPurviewInfoId.c_str(),nRet);
	}
	SCATCH;
}
#endif
void XhBFISSyncServerRouterImp::ParseRolePurviewInfoAndSetSyncState(vector<std::string>& vecStr,bool bstate /*= true*/,DWORD_PTR dwReserved /*= 0*/)
{
	STRY;
	int nRet = 0;
	for (auto iter = vecStr.begin() ; iter != vecStr.end() ; iter ++)
	{
		ST_RolePurviewInfo stRolePurviewInfo;
#pragma region ��������
		BFIS::RolePurviewInfo msg;
		msg.ParseFromString(*iter);
		/*
		string strRoleInfoPurviewId;
		string strRoleId;
		string strPruviewInfoId;
		int    nExtendedInfo;
		string strExtendedInfo1;
		string strExtendedInfo2;
		*/
		stRolePurviewInfo.strRoleInfoPurviewId = msg.strroleinfopurviewid();
		stRolePurviewInfo.strRoleId            = msg.strroleid();
		stRolePurviewInfo.strPruviewInfoId     = msg.strpruviewinfoid();
		stRolePurviewInfo.nExtendedInfo        = msg.nextendedinfo();
		stRolePurviewInfo.strExtendedInfo1     = msg.strextendedinfo1();
		stRolePurviewInfo.strExtendedInfo2     = msg.strextendedinfo2();
#pragma endregion
		nRet = m_pCache->SetSyncComplete(DataType_RolePurviewInfo, stRolePurviewInfo.strRoleInfoPurviewId);
		TTRACE(_T("%s[%d]:�����û���Ȩ����Ϣͬ����ʶ[%s],ID:%s,���ݿⷵ��ֵ��%d\r\n")
			,__FUNCTION__,__LINE__,nRet>0?"�ɹ�":"ʧ��",stRolePurviewInfo.strRoleInfoPurviewId.c_str(),nRet);
	}
	SCATCH;
}

BOOL XhBFISSyncServerRouterImp::CreateIniFile(CString strPath)
{
	if (strPath == _T(""))
	{
		return FALSE;
	}
	CFileFind finder;
	if(!finder.FindFile((LPCTSTR)strPath))
	{
		CString strAppName = _T("LastSyncTime");
		CString strKeyName = _T("Guid");
		CString strTemp = _T("");
		GuidProducer(strTemp); 
		if(strTemp == _T("")||!WritePrivateProfileString((LPCTSTR)strAppName,(LPCTSTR)strKeyName,(LPCTSTR)strTemp,(LPCTSTR)strPath))
		{
			return FALSE;
		}
		strKeyName = _T("Time");
		strTemp = _T("1970-01-01 00:00:00");
		if (!WritePrivateProfileString((LPCTSTR)strAppName,(LPCTSTR)strKeyName,(LPCTSTR)strTemp,(LPCTSTR)strPath))
		{
			return FALSE;
		}
	}
	return TRUE;
}

void XhBFISSyncServerRouterImp::GuidProducer(CString& strGuid)
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

bool XhBFISSyncServerRouterImp::ReadLastSyncTime(CString& strTime)
{
	STRY;
	CString strPath = GetWorkingDirectory();
	strPath += _T("\\Config\\iBFIS.ClientInfoSyncTime.Config.ini");
	CString strAppName = _T("LastSyncTime");
	CString strKeyName = _T("Time");
	TCHAR tchBuf[500] = { 0 };
	//
	if(!CreateIniFile(strPath))
	{
		DISPLAY_LOG("ͬ������","ʱ��ͬ�������ļ�������","","",0);
		return false;
	}
	if(!GetPrivateProfileString((LPCTSTR)strAppName,(LPCTSTR)strKeyName,_T(""),tchBuf,500,(LPCTSTR)strPath))
	{
		return false;
	}
	strTime.Format("%s",tchBuf);
	if (strTime == _T(""))
	{
		strTime = _T("1970-01-01 00:00:00");
	}
	return true;
	SCATCH;
	return false;
}

bool XhBFISSyncServerRouterImp::RestoreLastSyncTime(CString strTime)
{
	STRY;
	CString strPath = GetWorkingDirectory();
	strPath += _T("\\Config\\iBFIS.ClientInfoSyncTime.Config.ini");

	CString strAppName = _T("LastSyncTime");
	CString strKeyName = _T("Guid");
	CString strTemp = _T("");
	GuidProducer(strTemp);
	if (strTemp != _T("") && strTime != _T(""))
	{
		if(WritePrivateProfileString((LPCTSTR)strAppName,(LPCTSTR)strKeyName,(LPCTSTR)strTemp,(LPCTSTR)strPath))
		{
			strKeyName = _T("Time");
			if (WritePrivateProfileString((LPCTSTR)strAppName,(LPCTSTR)strKeyName,(LPCTSTR)strTime,(LPCTSTR)strPath))
			{
				return true;
			}
		}
	}
	return false;
	SCATCH
	return false;
}

bool XhBFISSyncServerRouterImp::DelEmployeePurviewInfo(vector<std::string> vecStr,DWORD_PTR dwReserved/* = 0*/)
{
	STRY;
	vector<ST_EmployeeInfo> vecEmployeeInfo;
	for (auto iter = vecStr.begin(); iter != vecStr.end() ; iter ++)
	{
		BFIS::EmployeeInfo msg;
		bool bSuccess = msg.ParseFromString(*iter);
		if (bSuccess)
		{
			ST_EmployeeInfo stEmployeeInfo(msg);
			vecEmployeeInfo.push_back(stEmployeeInfo);
		}
	}
	bool bRet = true;
	for (auto iter = vecEmployeeInfo.begin(); iter != vecEmployeeInfo.end() ; iter ++)
	{
		ST_EmployeePurviewInfo stDel;
		stDel.strEmployeeId = ((*iter).strEmployeeId);
		if(m_pCache->ManageEmployeePurviewInfo(DBO_DEL,stDel) == QueryFail)
		{
			bRet = false;
			char szError[255] = {0};
			sprintf(szError,"ɾ��������Ա��Ȩ����Ϣʧ��,Ա��Id:%s",stDel.strEmployeeId);
			DISPLAY_LOG("ǿ��ͬ������",szError,"","",0);
		}
	}
	return bRet;
	SCATCH;
	return false;
}

string XhBFISSyncServerRouterImp::Cmd2Msg(DWORD_PTR dwCmd)
{
	STRY;
	string strInfo = _T("");
	switch(dwCmd)
	{
	case MSG_LOGIN:
		{
			strInfo = _T("�����¼");
		}
		break;
	case MSG_UPLOAD_CLIENTINFO:	
		{
			strInfo = _T("�ϴ��ͻ���Ϣ");
		}
		break;
	case MSG_UPLOAD_BRANCHINFO:
		{
			strInfo = _T("�ϴ�������Ϣ");
		}
		break;
	case MSG_UPLOAD_BUSINESSINFO: 
		{
			strInfo = _T("�ϴ�ҵ����Ϣ");
		}
		break;
	case MSG_UPLOAD_BUSINESSFILEINFO:
		{
			strInfo = _T("�ϴ�ҵ���ļ���Ϣ");
		}
		break;
	case MSG_UPLOAD_BUSINESSRELATEINFO:	
		{
			strInfo = _T("�ϴ�ҵ�������Ϣ");
		}
		break;
	case MSG_UPLOAD_EMPLOYEEINFO:
		{
			strInfo = _T("�ϴ�Ա����Ϣ");
		}
		break;
	case MSG_UPLOAD_EMPLOYEEPURVIEWINFO:
		{
			strInfo = _T("�ϴ�Ա��Ȩ����Ϣ");
		}
		break;
	case MSG_GET_CLIENTINFO:
		{
			strInfo = _T("��ȡ�ͻ���Ϣ");
		}
		break;
	case MSG_UPLOAD_ROLEINFO:
		{
			strInfo = _T("�ϴ���ɫ��Ϣ");
		}
		break;
	case MSG_UPLOAD_ROLEPURVIEWINFO:
		{
			strInfo = _T("�ϴ���ɫȨ����Ϣ");
		}
		break;
	case MSG_GET_PRODUCEINFO:
		{
			strInfo = _T("��ȡ��Ʒ��Ϣ");
		}
		break;
    case MSG_GET_SMS_LOGININFO:
        {
            strInfo = _T("��ȡSMS��������Ϣ");
            break;
        }
	default:
		{
			strInfo = _T("δ֪����");
		}
	}
	return strInfo;
	SCATCH;
	return _T("");
}

bool XhBFISSyncServerRouterImp::GetBranchName(UINT64 fromAddr,string& strInfo, int &bSync)
{
	STRY;
	char szBuf[255] = {0};
	readLock readLocker(m_csLockClientContext);
	auto iter = m_mapClientContext.find(fromAddr);
	if (iter != m_mapClientContext.end())
	{
		sprintf(szBuf, "%s[Url:%s]", iter->second->m_custom.stInfo.strName.c_str(), iter->second->m_custom.strUrl.c_str());
		strInfo = szBuf;
		bSync = iter->second->m_custom.notifyStatus.load();
	}
	return true;
	SCATCH;
	return false;
}

BOOL XhBFISSyncServerRouterImp::GetLocalBranchId(std::string& strBranchId)
{
	if (m_pCache)
	{
		return m_pCache->QueryLocalBranchId(strBranchId);
	}
	return false;
}

int XhBFISSyncServerRouterImp::BranchInfoNotify(int nType,ST_BranchInfo& stInfo)
{
	STRY;
	if (stInfo.strBranchId == "")
	{
		TTRACE("%s����������Ϣʧ��,����IDΪ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
	char szTemp[255] = {0};
	stInfo.nIsLocal = 0;
	if(stInfo.strParentId == "" && GetLocalBranchId(m_strLocalBranchId))
	{
		FOUTPUTDBGSTRING("����ȡ����������ID:%s[%s:%d]��\r\n",m_strLocalBranchId.c_str(),__FUNCTION__,__LINE__);
		vector<ST_BranchInfo> vecBranchInfo;
		if (m_pCache && m_pCache->QueryBranchInfo(vecBranchInfo))
		{
			if (!vecBranchInfo.empty())
			{
				for each(auto branch in vecBranchInfo)
				{
					if(stInfo.strParentJDBRID == branch.strJDBRID)
					{
						stInfo.strParentId = branch.strBranchId;
					}
				}
			}
		}
	}
	if (m_pCache && m_pCache->ManageBranchInfo((DBOperType)nType,stInfo) != QueryFail)
	{
		sprintf(szTemp,"[����֪ͨ]����������ϢName:%s[BranchId:%s]",stInfo.strName.c_str(),stInfo.strBranchId.c_str());
		DISPLAY_LOG("ͬ��",szTemp,"�ɹ�","",1);
		return 1;
	}
	return -1;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::ProduceInfoNotify(int nType,ST_ProduceInfo& stInfo)
{
	STRY;
	if (stInfo.strProduceId == "")
	{
		TTRACE("%s���²�Ʒ��Ϣʧ��,����IDΪ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
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
int XhBFISSyncServerRouterImp::UserMapInfoNotify(int nType,ST_UserMapInfo& stInfo)
{
	STRY;
	if (stInfo.strUserMapInfoId == "")
	{
		TTRACE("%s���¹�ϵӳ����Ϣʧ��,����IDΪ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
	char szTemp[255] = {0};
	if (m_pCache && m_pCache->ManageUserMapInfo((DBOperType)nType,stInfo) != QueryFail)
	{
		sprintf(szTemp,"[����֪ͨ]����ӳ����ϢUserMapInfoId:%s[EmployeeId:%s]",
			stInfo.strUserMapInfoId.c_str(),stInfo.strEmployeeId.c_str());
		DISPLAY_LOG("ͬ��",szTemp,"�ɹ�","",1);
		return 1;
	}
	return -1;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::RoleInfoNotify(int nType,ST_RoleInfo& stInfo)
{
	STRY;
	if (stInfo.strRoleInfoId == "")
	{
		TTRACE("%s���½�ɫ��Ϣʧ��,����IDΪ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
	char szTemp[255] = {0};
	if (m_pCache && m_pCache->ManageRoleInfo((DBOperType)nType,stInfo) != QueryFail)
	{
		sprintf(szTemp,"[����֪ͨ]���½�ɫ��ϢName:%s[RoleInfoId:%s]",stInfo.strRoleName.c_str(),stInfo.strRoleInfoId.c_str());
		DISPLAY_LOG("ͬ��",szTemp,"�ɹ�","",1);
		return 1;
	}
	return -1;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::EmployeeInfoNotify(int nType,ST_EmployeeInfo& stInfo)
{
	STRY;
	if (stInfo.strEmployeeId == "")
	{
		TTRACE("%s����Ա����Ϣʧ��,����IDΪ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
	char szTemp[255] = {0};
	if (m_pCache && m_pCache->ManageEmployeeInfo((DBOperType)nType,stInfo) != QueryFail)
	{
		sprintf(szTemp,"[����֪ͨ]����Ա����ϢName:%s[EmployeeId:%s]",stInfo.strName.c_str(),stInfo.strEmployeeId.c_str());
		DISPLAY_LOG("ͬ��",szTemp,"�ɹ�","",1);
		return 1;
	}
	return -1;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::ClientInfoNotify(int nType,ST_ClientInfo& stInfo)
{
	STRY;
	if (stInfo.strClientId == "")
	{
		TTRACE("%s���¿ͻ���Ϣʧ��,����IDΪ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
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
int XhBFISSyncServerRouterImp::RolePurviewInfoNotify(int nType,std::vector<ST_RolePurviewInfo>& vecInfo)
{
	STRY;
	if (vecInfo.empty())
	{
		TTRACE("%s���½�ɫȨ��ʧ��,����Ȩ����ϢΪ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
	char szMsg[255] = {0};
	int nRet = -1;
	for each(auto info in vecInfo)
	{
		sprintf(szMsg,"[����֪ͨ]���½�ɫȨ����Ϣ[RoleInfoPurviewId:%s]RoleId:%s",
			info.strRoleInfoPurviewId.c_str(),info.strRoleId.c_str());
		nRet = -1;
		if(m_pCache)
		{
			nRet = (m_pCache->ManageRolePurviewInfo((DBOperType)nType,info) == QueryFail ? -1 : 1);
		}
		DISPLAY_LOG("ͬ��",szMsg,(nRet == 1)?"�ɹ�":"ʧ��","",nRet);
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::EmployeePurviewInfoNotify(int nType,std::vector<ST_EmployeePurviewInfo>& vecInfo)
{
	STRY;
	if (vecInfo.empty())
	{
		TTRACE("%s����Ա��Ȩ��ʧ��,����Ȩ����ϢΪ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
	char szMsg[255] = {0};
	int nRet = -1;
	for each(auto info in vecInfo)
	{
		sprintf(szMsg,"[����֪ͨ]����Ա��Ȩ����Ϣ[EmployeePurviewId:%s]EmployeeId:%s",
			info.strEmployeePurviewId.c_str(),info.strEmployeeId.c_str());
		nRet = -1;
		if(m_pCache)
		{
			nRet = (m_pCache->ManageEmployeePurviewInfo((DBOperType)nType,info) == QueryFail ? -1 : 1);
		}
		DISPLAY_LOG("ͬ��",szMsg,(nRet == 1)?"�ɹ�":"ʧ��","",nRet);
	}
	return 1;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::KeyValueInfoNotify(int nType,ST_KeyValueInfo& stInfo)
{
	STRY;
	if (stInfo.strType == "")
	{
		TTRACE("%s���¼�ֵ��Ϣʧ��,��������Ϊ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
	if(m_pCache && m_pCache->ManageTransparentData((DBOperType)nType,stInfo.strType,stInfo.strCode,stInfo.strValue) != QueryFail )
	{
		DISPLAY_LOG("ͬ��","[����֪ͨ]���¼�ֵ��Ϣ","�ɹ�","",1);
		return 1;
	}
	return -1;
	SCATCH;
	return -1;
}

int XhBFISSyncServerRouterImp::BusinessInfoNotify(int nType,ST_BusinessInfo& stInfo)
{
	STRY;
	int nRet = 0;
	char szMsg[255] = {0};
	if (stInfo.strBusinessInfoId == "")
	{
		TTRACE("%s����ҵ����Ϣʧ��,��������Ϊ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
	if (m_pCache && (m_pCache->ManageBusinessInfo((DBOperType)nType,stInfo) ? nRet = 1 : nRet = 0)){}
	sprintf(szMsg,"[����֪ͨ]����ҵ����ϢBusinessId:%s[SerialNum:%s]",
		stInfo.strBusinessInfoId.c_str(),stInfo.strSerialNumber.c_str());
	DISPLAY_LOG("ͬ��",szMsg,nRet == 1 ? "�ɹ�" : "ʧ��","",nRet);
	return nRet;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::BusinessFileInfoNotify(int nType,ST_BusinessFileInfo& stInfo)
{
	STRY;
	int nRet = 0;
	char szMsg[255] = {0};
	if (stInfo.strRecordId == "")
	{
		TTRACE("%s����ҵ���ļ���Ϣʧ��,��������Ϊ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
	if (m_pCache && (m_pCache->ManageBusinessFileInfo((DBOperType)nType,stInfo) ? nRet = 1 : nRet = 0)){}
	sprintf(szMsg,"[����֪ͨ]����ҵ���ļ���ϢRecordId:%s",stInfo.strRecordId.c_str());
	DISPLAY_LOG("ͬ��",szMsg,nRet == 1 ? "�ɹ�" : "ʧ��","",nRet);
	return nRet;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::BusinessRelateInfoNotify(int nType,ST_BusinessRelateInfo& stInfo)
{
	STRY;
	int nRet = 0;
	char szMsg[255] = {0};
	if (stInfo.strBusinessRelateInfoId == "")
	{
		TTRACE("%s����ҵ�������Ϣʧ��,��������Ϊ��%s[%d]\r\n",MODULE_NAME,__FUNCTION__,__LINE__);
		return -1;
	}
	if (m_pCache && (m_pCache->ManageBusinessRelateInfo((DBOperType)nType,stInfo) ? nRet = 1 : nRet = 0)){}
	sprintf(szMsg,"[����֪ͨ]����ҵ�������ϢBusinessRelateInfoId:%s",stInfo.strBusinessRelateInfoId.c_str());
	DISPLAY_LOG("ͬ��",szMsg,nRet == 1 ? "�ɹ�" : "ʧ��","",nRet);
	return nRet;
	SCATCH;
	return -1;
}
string& replace_end(string& strDest)
{  
   int i = 0; 
   int nlen = sizeof(strDest);
   for(strDest[i];i<nlen;i++)
   {
       if (strDest[i] = ' ')
       {
           strDest[i] = '\0';
       }
   }
   strDest[nlen] = '\0';
   return strDest;
}   

int String2Hex(std::string str, BYTE *LL)
{

	string bb;
	int len=str.length();
	for(int i=1;i<=len;i++)
	{
		if(i%2==0)
		{
			bb="0x";
			bb+=str[i-1];
			bb+=str[i];
			LL[i/2-1]=StrToInt(bb.c_str());
		}

	}
	return len;
}
int XhBFISSyncServerRouterImp::HandleManualSync(ST_ManualSyncParameter& stManualSyncParameter)
{
	STRY;
	int nRet = -1;
	nRet = ReadFileAndParse(".//SyncFile");
	if (nRet == FALSE)
	{
		return nRet;
	}
	if (stManualSyncParameter.nBranchInfo == 1)
	{	
		HandleReadBranchInfo();
		STRY;
		if (!m_vecBranchInfo.empty())
		{	
			std::map<UINT64, std::shared_ptr<ObjectRefCount<ST_Login> > >  mapClientContext;
			STRY;
			readLock readLocker(m_csLockClientContext);
			mapClientContext = m_mapClientContext;
			SCATCH;

			m_mapClientCount = mapClientContext.size();
			for each(auto &var in mapClientContext)
			{
				readLock readLocker(m_csLockClientContext);
				auto iter = m_mapClientContext.find(var.first);
				if (iter != m_mapClientContext.end())
				{
					std::shared_ptr<ObjectRefCount<ST_Login> > objectRefInfo = iter->second;
					std::shared_ptr<RefCountInfo> refInfo = objectRefInfo->GetRefInfo();

					AutoObjectRefMgr refObject;
					if (refObject.AddRefCount(refInfo))
					{
						readLocker.unlock();
						SFTRACE("FTP�·�����", "�ֶ����¼�����������Ϣ��ʼ����������[%s]����ID[%s] \r\n", objectRefInfo->m_custom.stInfo.strName.c_str(),objectRefInfo->m_custom.stInfo.strBranchId.c_str());
						DoSyncBranchInfo((HANDLE)var.first, m_vecBranchInfo, 0, objectRefInfo->m_custom.stInfo.strBranchId);
					}
				}
			}
		}
		SCATCH;
	}
	if (stManualSyncParameter.nEmployeeInfo == 1)
	{
		HandleReadEmployInfo();
		STRY;
		if (!m_vecEmployeeInfo.empty())
		{
			std::map<UINT64, std::shared_ptr<ObjectRefCount<ST_Login> > >  mapClientContext;
			STRY;
			readLock readLocker(m_csLockClientContext);
			mapClientContext = m_mapClientContext;
			SCATCH;

			m_mapClientCount = mapClientContext.size();
			for each(auto &var in mapClientContext)
			{
				readLock readLocker(m_csLockClientContext);
				auto iter = m_mapClientContext.find(var.first);
				if (iter != m_mapClientContext.end())
				{
					std::shared_ptr<ObjectRefCount<ST_Login> > objectRefInfo = iter->second;
					std::shared_ptr<RefCountInfo> refInfo = objectRefInfo->GetRefInfo();
					std::string strBranch = objectRefInfo->m_custom.stInfo.strBranchId;
					AutoObjectRefMgr refObject;
					if (refObject.AddRefCount(refInfo))
					{
						readLocker.unlock();
						SFTRACE("FTP�·�����", "�ֶ����¼�����Ա����Ϣ��ʼ��������Ϣ����[%s]������ϢID[%s] \r\n", objectRefInfo->m_custom.stInfo.strName.c_str(), objectRefInfo->m_custom.stInfo.strBranchId.c_str());
						DoSyncEmployeeInfo((HANDLE)var.first, m_vecEmployeeInfo, -1, strBranch);
					}
				}
			}
		}
		SCATCH;
	}	
	if (stManualSyncParameter.nProduceInfo == 1)
	{
		STRY;	
		HandleReadProductInfo();
		std::vector<ST_ProduceInfo> vecProduceInfo;
		if (GetNeedSyncProduceInfo(vecProduceInfo) && !vecProduceInfo.empty())
		{	
			std::map<UINT64, std::shared_ptr<ObjectRefCount<ST_Login> > >  mapClientContext;
			STRY;
			readLock readLocker(m_csLockClientContext);
			mapClientContext = m_mapClientContext;
			SCATCH;

			m_mapClientCount = mapClientContext.size();
			for each(auto &var in mapClientContext)
			{
				readLock readLocker(m_csLockClientContext);
				auto iter = m_mapClientContext.find(var.first);
				if (iter != m_mapClientContext.end())
				{
					std::shared_ptr<ObjectRefCount<ST_Login> > objectRefInfo = iter->second;
					std::shared_ptr<RefCountInfo> refInfo = objectRefInfo->GetRefInfo();

					AutoObjectRefMgr refObject;
					if (refObject.AddRefCount(refInfo))
					{
						readLocker.unlock();
						SFTRACE("FTP�·�����", "�ֶ����¼����Ͳ���Ʒ��Ϣ��ʼ����������[%s]����ID[%s] \r\n", objectRefInfo->m_custom.stInfo.strName.c_str(), objectRefInfo->m_custom.stInfo.strBranchId.c_str());
						nRet = DoSyncProduceInfo((HANDLE)var.first, vecProduceInfo);
					}
				}
			}
		}
		SCATCH;
	}
	m_vecBranchInfo.clear();
	m_vecEmployeeInfo.clear();
	m_vecProduceInfo.clear();
	DeleteDirectory(".//SyncFile");
	return nRet;
	SCATCH;
	return -1;
}
int XhBFISSyncServerRouterImp::CheckIsTopServer(int nType)
{
	m_nServerType = nType;
	return TRUE;
}
int XhBFISSyncServerRouterImp::DoSyncScriptInfo(void* toAddr,DWORD_PTR dwReserved)
{
	STRY;
	if (toAddr == NULL)
    {
        TTRACE("%s[%d]ʧ�ܣ�����Ĳ���Ϊ��\r\n",__FUNCTION__,__LINE__);
        return -1;
    }
    std::string strTemp;
	vector<std::string> vecTemp;
    vector<ST_ScriptInfo> vecScriptInfo;
	if(!m_pCache || !m_pCache->QueryScriptInfoByCache(vecScriptInfo))
	{
		return -1;
	}
    iBFIS_CommunicationInvoker invoke((HANDLE)toAddr);
    DWORD dwCmd = MSG_ISSUED_SCRIPTINFO;
    for each(auto scriptinfo in vecScriptInfo)
    {
		if(scriptinfo.ConvertToString(strTemp))
		{
			vecTemp.push_back(strTemp);
		}       
    }
    if(invoke.Invoke(dwCmd,vecTemp) < 0) //=0��ʾ�Ѿ�����
    {
		TTRACE("ͬ���ϼ��·�������Ϣʧ��\r\n");
        return -1;
    }
	return 1;
	SCATCH;
	return -1;
}

