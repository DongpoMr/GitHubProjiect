#include "stdafx.h"
#include "XhServerMonitoring.h"
#include "IcmsP_Utility.h"
#include "iBFIS_UniqueDefine.h"
#include "IcmsP_XmlParser.h"
#include <windows.h>
#include <stdint.h>
#include <tlhelp32.h>


XhServerMonitoring::XhServerMonitoring()
	:m_spNetClient(nullptr), m_spCheckLocalServerLiveTh(nullptr), m_bIsStopCheckServerLive(false),
	m_hClinet(nullptr)
{
}


XhServerMonitoring::~XhServerMonitoring()
{
	m_bIsStopCheckServerLive = true;
	if (m_spCheckLocalServerLiveTh)
	{
		m_cheackLocalServerLiveCondition.notify_one();
		if (m_spCheckLocalServerLiveTh->joinable())
			m_spCheckLocalServerLiveTh->join();
		m_spCheckLocalServerLiveTh = nullptr;
	}
}

void XhServerMonitoring::StartMonitoring()
{
	if (nullptr == m_spNetClient)
	{
		m_spNetClient.reset(new iBFIS_CommunicationClient());
		m_spNetClient->SetRMICallbackSkin(this);
		m_spCheckLocalServerLiveTh = std::make_shared<boost::thread>(std::bind(&XhServerMonitoring::LocalServerIsLive, this));
	}
}

int XhServerMonitoring::OnConnected(HANDLE hContext)
{
	m_hClinet = hContext;
	return 0;
}

int XhServerMonitoring::OnDisConnected(HANDLE hContext)
{
	m_hClinet = nullptr;
	return 0;
}

int XhServerMonitoring::OnGotError(HANDLE hContext, int nErrorCode, std::string strErrorDes)
{
	return 0;
}

void XhServerMonitoring::LocalServerIsLive()
{
	int waitRebootTime = 300;
	int max_reconnect_count = 3;
	int nListenPort = 9989;

	STRY;
	iFVR_Configuration config;
	nListenPort = config.GetInt("LocalSet", "ListenPort", 9989);

	iCMSP_XmlParser xmlParser;
	CString strFMSConfigPath = GetWorkingDirectory();
	strFMSConfigPath += "\\Config\\iFMSConfig.xml";
	bool bRet = xmlParser.Load(strFMSConfigPath.GetBuffer(0));
	if (bRet)
	{
		if (xmlParser.FindElem("FMS"))
		{
			xmlParser.IntoElem();
			if (xmlParser.FindElem("ServerMonitoring"))
			{
				waitRebootTime = xmlParser.GetAttribInt("reboot_wait_time");
				max_reconnect_count = xmlParser.GetAttribInt("max_reconnect");
			}
		}
		TTRACE(" %s 成功加载插件配置文件 waitRebootTime[%d] nPort[%d] max_reconnect_count[%d]\r\n", __FUNCTION__, waitRebootTime, nListenPort, max_reconnect_count);
	}
	else
	{
		TTRACE(" %s 加载插件配置文件失败 默认waitRebootTime[%d] nPort[%d] max_reconnect_count[%d]\r\n", __FUNCTION__, waitRebootTime, nListenPort, max_reconnect_count);
	}
	SCATCH;

	STRY;
	boost::unique_lock<boost::mutex> lock(m_LocalServerConnectMtx);
	m_cheackLocalServerLiveCondition.wait_for(lock, boost::chrono::seconds(waitRebootTime));
	SCATCH;

	int reconnect_count = 0;
	int nRet = 0;
	while (false == m_bIsStopCheckServerLive)
	{
		STRY;
		if (nRet > 0)
		{
			boost::unique_lock<boost::mutex> lock(m_LocalServerConnectMtx);
			m_cheackLocalServerLiveCondition.wait_for(lock, boost::chrono::seconds(30));
		}
		else
		{
			boost::unique_lock<boost::mutex> lock(m_LocalServerConnectMtx);
			m_cheackLocalServerLiveCondition.wait_for(lock, boost::chrono::seconds(10));
		}
		if (nullptr == m_hClinet)
		{
			nRet = m_spNetClient->Connect("127.0.0.1", nListenPort);
			if (nRet < 0)
			{
				if (reconnect_count >= max_reconnect_count)
				{
					TTRACE(_T(" 连接服务失败，错误码[%d] 重启iFMS应用程序 重连次数[%d]\r\n"),nRet, reconnect_count);
					reconnect_count = 0;
					KillProcessHandeByName(std::string("iFMS Server.exe"));
					STRY;
					boost::unique_lock<boost::mutex> lock(m_LocalServerConnectMtx);
					m_cheackLocalServerLiveCondition.wait_for(lock, boost::chrono::seconds(waitRebootTime));
					SCATCH;
				}
				else
				{
					++reconnect_count;
					continue;
				}
			}
			else
			{
				reconnect_count = 0;
				nRet = 1;
			}
		}

		if (m_hClinet)
		{
			iBFIS_CommunicationInvoker invoke(m_hClinet);
			DWORD_PTR dwCmd = LOCAL_MSG_SERVER_IS_ALIVE;
			nRet = invoke.Invoke(dwCmd);
			if (nRet > 0)
			{
				reconnect_count = 0;
			}
			else
			{
				if (reconnect_count >= max_reconnect_count)
				{
					m_spNetClient->DisConnect();
					m_hClinet = nullptr;
					TTRACE(" 发送消息失败[%d]，重新连接服务器!\r\n", reconnect_count);
				}
				else
				{
					++reconnect_count;
				}
			}
		}
		SCATCH;
	}
}

int XhServerMonitoring::KillProcessHandeByName(std::string&& strProcessName)
{
	STRY;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return -1;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe))
	{
		if (strProcessName.compare(pe.szExeFile) == 0)
		{
			DWORD proid = pe.th32ProcessID;
			HANDLE hprocess = ::OpenProcess(PROCESS_TERMINATE, FALSE, proid);
			if (hprocess != nullptr)
			{
				::TerminateProcess(hprocess, 0);
				TTRACE(" 成功关闭iFMS进程[%s]\r\n", strProcessName.c_str());
			}
			else
			{
				TTRACE(" OpenProcess 进程失败 [%s] err[%d]\r\n", strProcessName.c_str(), GetLastError());
			}
			CloseHandle(hSnapshot);
			return 1;
		}
	}
	CloseHandle(hSnapshot);
	TTRACE(" 未找到对应进程 [%s]\r\n", strProcessName.c_str());
	SCATCH;
	return -2;
}
