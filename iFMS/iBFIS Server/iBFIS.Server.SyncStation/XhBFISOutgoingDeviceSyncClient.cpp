#include "StdAfx.h"
#include "XhBFISOutgoingDeviceSyncClient.h"
#include "IcmsP_Utility.h"
#include "XhLogDisplayInterface.h"
#include <functional>
#include <IcmsP_XmlParser.h>


XhBFISOutgoingDeviceSyncClient::XhBFISOutgoingDeviceSyncClient(XhBFISSyncClientRouterImp *parent):m_parent(parent), m_pNetClient(nullptr),
m_handle(nullptr), m_sync(nullptr), m_run(true), m_waitFinishTime(120)
{
	
}


XhBFISOutgoingDeviceSyncClient::~XhBFISOutgoingDeviceSyncClient()
{
	m_run = false;
	if (m_sync && m_sync->joinable())
	{
		STRY;
		boost::unique_lock<boost::mutex> lock(m_mutex);
		m_condition.notify_one();
		SCATCH;
		m_sync->join();
	}
		
}

int XhBFISOutgoingDeviceSyncClient::Init(const std::string host, const int port, const int timeInterval, int waitFinishTime)
{
	m_host = host;
	m_port = port;
	m_times = timeInterval;
	m_waitFinishTime = waitFinishTime;
	if (!m_pNetClient)
	{
		m_pNetClient = new(std::nothrow) iBFIS_CommunicationClient;
		if (nullptr == m_pNetClient)
			return -1;
		m_pNetClient->SetRMICallbackSkin(this);
	}
	return 1;
}

int XhBFISOutgoingDeviceSyncClient::StartSync()
{
	boost::unique_lock<boost::mutex> locker(m_thread_mutex);
	if (m_sync && m_sync->joinable())
		return 1;
	else
	{
		m_sync = std::make_shared<boost::thread>(std::bind(&XhBFISOutgoingDeviceSyncClient::_Entry, this));
	}
	return 0;
}

int XhBFISOutgoingDeviceSyncClient::OnInvoke(HANDLE hContext, DWORD_PTR & d1, std::vector<std::string>& v1)
{
	if (MSG_ISSUED_SCRIPTINFO == d1)
	{
		DISPLAY_LOG("外出设备同步", "外出设备同步话术数据", "", "", 1);
		boost::unique_lock<boost::mutex> lock(m_mutex);
		m_condition.notify_one();
	}
	else if (MSG_ISSUED_EMPLOYEEINFO == d1)
	{
		DISPLAY_LOG("外出设备同步", "外出设备同步员工数据", "", "", 1);
	}
	else if (MSG_ISSUED_ROLEINFO == d1)
	{
		DISPLAY_LOG("外出设备同步", "外出设备同步角色数据", "", "", 1);
	}
	else if (MSG_ISSUED_ROLEPURVIEW == d1)
	{
		DISPLAY_LOG("外出设备同步", "外出设备同步角色权限数据", "", "", 1);
	}
	else if (MSG_ISSUED_PRODUCEINFO == d1)
	{
		DISPLAY_LOG("外出设备同步", "外出设备同步产品数据", "", "", 1);
	}
	else if (MSG_OUTGOING_EMPLOYEEPURVIEWINFO == d1)
	{
		DISPLAY_LOG("外出设备同步", "外出设备同步员工权限数据", "", "", 1);
	}
	if (m_parent)
		return m_parent->OnInvoke(hContext, d1, v1);
	return -1;
}

int XhBFISOutgoingDeviceSyncClient::OnInvoke(HANDLE hContext, DWORD_PTR & d, std::string & s)
{
	if (m_parent)
		return m_parent->OnInvoke(hContext, d, s);
	return -1;
}

int XhBFISOutgoingDeviceSyncClient::OnConnected(HANDLE hContext)
{
	STRY;
	boost::unique_lock<boost::mutex> locker(m_handleMtx);
	m_handle = hContext;
	SCATCH;

	boost::unique_lock<boost::mutex> lock(m_mutex);
	m_condition.notify_one();
	return 1;
}

int XhBFISOutgoingDeviceSyncClient::OnDisConnected(HANDLE hContext)
{
	STRY;
	boost::unique_lock<boost::mutex> locker(m_handleMtx);
	m_handle = nullptr;
	SCATCH;
	return 1;
}

int XhBFISOutgoingDeviceSyncClient::OnGotError(HANDLE hContext, int nErrorCode, std::string strErrorDes)
{
	return 0;
}

void XhBFISOutgoingDeviceSyncClient::_Entry()
{
	bool send_sucess = false;
	DISPLAY_LOG("外出设备同步", "进入同步线程", "", "", 1);
	while (m_run)
	{
		STRY;
		boost::unique_lock<boost::mutex> lock(m_mutex);
		m_condition.wait_for(lock, boost::chrono::seconds(m_times));
		SCATCH;

		STRY;
		boost::unique_lock<boost::mutex> locker(m_handleMtx);
		if (m_handle)
		{
			DISPLAY_LOG("外出设备同步", "外出设备同步开始", "", "", 1);
			iBFIS_CommunicationInvoker invoke(m_handle);
			int n_ret = 0;
			int send_count = 0;
			do
			{
				DWORD cmd = MSG_OUTGOING_DEVICE_SYNC;
				n_ret = invoke.Invoke(cmd);
				if (n_ret > 0)
				{
					DISPLAY_LOG("外出设备同步", "发送同步消息成功", "", "", 1);
					send_sucess = true;
					break;
				}
				++send_count;
				boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
			} while (send_count <= 3);

			if (false == send_sucess)
			{
				char szMeg[100] = { 0 };
				sprintf(szMeg, "外出设备同步状态[%d]", n_ret);
				DISPLAY_LOG("外出设备同步", szMeg, "", "", 0);
				m_handle = nullptr;
			}
		}
		SCATCH;

		if (send_sucess)
		{
			DISPLAY_LOG("外出设备同步", "外出设备等待同步数据", "", "", 1);
			STRY;
			boost::unique_lock<boost::mutex> lock(m_mutex);
			if (m_condition.wait_for(lock, boost::chrono::seconds(m_waitFinishTime)) == boost::cv_status::no_timeout)
			{
				DISPLAY_LOG("外出设备同步", "外出设备同步数据完成", "", "", 1);

				CString strFMSConfigPath = GetWorkingDirectory();
				strFMSConfigPath += "\\Config\\OutgoingDevice.xml";
				iCMSP_XmlParser xmlParser;
				const bool b_ret = xmlParser.Load(strFMSConfigPath);
				if (true == b_ret)
				{
					if (xmlParser.FindElem("FMS"))
					{
						xmlParser.IntoElem();
						if (xmlParser.FindElem("OutgoingDevice"))
						{
							std::string strTime = boost::gregorian::to_iso_string(boost::gregorian::day_clock::local_day());
							int currTime = boost::lexical_cast<int>(strTime);
							xmlParser.SetAttrib("lastSyncTime", currTime);
							xmlParser.Save(strFMSConfigPath);
						}
					}
				}
				return;
			}
			send_sucess = false;
			DISPLAY_LOG("外出设备同步", "外出设备等待同步数据超时", "", "", 1);
			SCATCH;
			continue;
		}
		char szMeg[100] = { 0 };
		sprintf(szMeg, "外出设备同步开始连接IP[%s] Port[%d]", m_host.c_str(), m_port);
		const int n_ret = m_pNetClient->Connect(m_host.c_str(), m_port);
		DISPLAY_LOG("外出设备同步", szMeg, "", "", n_ret == 0 ? 1 : 0);
	}
}
