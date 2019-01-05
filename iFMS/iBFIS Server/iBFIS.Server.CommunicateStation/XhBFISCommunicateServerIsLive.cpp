#include "StdAfx.h"
#include "XhBFISCommunicateServerIsLive.h"
#include "IcmsP_Utility.h"
#include "iBFIS_UniqueDefine.h"

#define RETRY_COUNT 2

XhBFISCommunicateServerIsLive::XhBFISCommunicateServerIsLive(): m_bIsStopCheckServerLive(false),m_hClinet(nullptr),m_nPort(0),
 m_spCheckLocalServerLiveTh(nullptr),m_spNetClient(nullptr)
{
}


XhBFISCommunicateServerIsLive::~XhBFISCommunicateServerIsLive()
{
	m_bIsStopCheckServerLive = true;
	if (m_spCheckLocalServerLiveTh)
	{
		m_cheackLocalServerLiveCondition.notify_all();
		m_spCheckLocalServerLiveTh->join();
	}
}

int XhBFISCommunicateServerIsLive::Start(std::string strIp, short nPort)
{
	m_nPort = nPort;
	m_strIp = "127.0.0.1";

	if (nullptr == m_spNetClient)
	{
		m_spNetClient.reset(new iBFIS_CommunicationClient());
		m_spNetClient->SetRMICallbackSkin(this);
	}

	if (nullptr == m_spCheckLocalServerLiveTh)
	{
		m_bIsStopCheckServerLive = false;
		m_spCheckLocalServerLiveTh.reset(new boost::thread(std::bind(&XhBFISCommunicateServerIsLive::CheckLocalServerIsLive, this)));
	}
	return 1;
}

void XhBFISCommunicateServerIsLive::CheckLocalServerIsLive()
{
	if (m_strIp.empty() || 0 == m_nPort)
		return;

	bool bRestartConnect = false;

	while (false == m_bIsStopCheckServerLive)
	{
		STRY;
		boost::unique_lock<boost::mutex> lock(m_LocalServerConnectMtx);
		m_cheackLocalServerLiveCondition.wait_for(lock, boost::chrono::seconds(30));
		SCATCH;

		STRY;
		int nRet = -1;
		for (int i = 0; i < RETRY_COUNT; ++i)
		{
			STRY;
			iCMSP_SimpleLock lockLinkContext(&m_csConnectContext, __FUNCTION__);
			if (nullptr == m_hClinet)
			{
				nRet = m_spNetClient->Connect(m_strIp.c_str(), m_nPort);
			}
			else
			{
				nRet = 0;
				break;
			}
			SCATCH;

			if (nRet < 0)
			{
				TTRACE(_T("%s[%d]:连接本地服务失败，错误码[%d]\r\n"), __FUNCTION__, __LINE__, nRet);

				STRY;
				boost::unique_lock<boost::mutex> lock(m_LocalServerConnectMtx);
				m_cheackLocalServerLiveCondition.wait_for(lock, boost::chrono::seconds(10));
				SCATCH;
			}
			else
			{
				break;
			}
		}

		if (nRet < 0)
		{
			SFTRACE("远程调用检测线程", "本地服务器连接失败，重启应用程序!\r\n");
			::ExitProcess(0);
		}

		SCATCH;

		int nRet = -1;
		auto future = boost::async(boost::launch::async, [this, &nRet]()
		{
			STRY;
			iCMSP_SimpleLock lockLinkContext(&m_csConnectContext, __FUNCTION__);
			if (m_hClinet == nullptr)
				return;
			iBFIS_CommunicationInvoker invoke(m_hClinet);
			DWORD_PTR dwCmd = LOCAL_MSG_SERVER_IS_ALIVE;
			nRet = invoke.Invoke(dwCmd);
			SCATCH;
		});

		if (boost::future_status::timeout == future.wait_for(boost::chrono::seconds(30))) 
		{
			SFTRACE("远程调用检测线程", "本地服务器无响应，重启应用程序!\r\n");
			::ExitProcess(0);
		}
		else
		{
			if (nRet > 0)
			{
				bRestartConnect = false;
				continue;
			}
			else
			{
				TTRACE(" 本地心跳消息发送失败[%d]\r\n", nRet);

				if (!bRestartConnect)
				{
					bRestartConnect = true;
					continue;
				}
			}

			SFTRACE("远程调用检测线程", "本地服务器无响应，重启应用程序!\r\n");
			::ExitProcess(0);
		}
	}
}

int XhBFISCommunicateServerIsLive::OnConnected(HANDLE hContext)
{
	iCMSP_SimpleLock lockLinkContext(&m_csConnectContext, __FUNCTION__);
	m_hClinet = hContext;
	return 0;
}

int XhBFISCommunicateServerIsLive::OnDisConnected(HANDLE hContext)
{
	iCMSP_SimpleLock lockLinkContext(&m_csConnectContext, __FUNCTION__);
	m_hClinet = nullptr;
	return 0;
}

int XhBFISCommunicateServerIsLive::OnGotError(HANDLE hContext, int nErrorCode, std::string strErrorDes)
{
	return 0;
}

int XhBFISCommunicateServerIsLive::OnInvoke(HANDLE hContext, DWORD_PTR & d)
{
	if (d == LOCAL_MSG_SERVER_IS_ALIVE)
		return 1;
	return 0;
}
