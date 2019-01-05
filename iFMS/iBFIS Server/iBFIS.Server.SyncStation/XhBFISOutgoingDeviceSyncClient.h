#pragma once
#include "iBFIS_Communication.h"
#include "XhBFISSyncClientRouterImp.h"

class XhBFISOutgoingDeviceSyncClient : public IRMICallbackSkin
{
public:
	XhBFISOutgoingDeviceSyncClient(XhBFISSyncClientRouterImp *parent);
	~XhBFISOutgoingDeviceSyncClient();
public:
	int Init(const std::string host, const int port, const int times, int waitFinishTime);
	int StartSync();

	int OnInvoke(HANDLE hContext, DWORD_PTR& d1, std::vector<std::string>& v1) override;
	int OnInvoke(HANDLE hContext, DWORD_PTR& d, std::string& s) override;
	int OnConnected(HANDLE hContext) override;
	int OnDisConnected(HANDLE hContext) override;
	int OnGotError(HANDLE hContext, int nErrorCode, std::string strErrorDes) override;
private:
	void _Entry();
private:
	iBFIS_CommunicationClient * m_pNetClient;
	std::string m_host;
	int            m_port;
	int            m_times;
	XhBFISSyncClientRouterImp  *m_parent;
	boost::mutex m_mutex;
	boost::condition_variable m_condition;
	boost::mutex m_handleMtx;
	HANDLE  m_handle;
	boost::mutex m_thread_mutex;
	std::shared_ptr<boost::thread>   m_sync;
	bool           m_run;
	int              m_waitFinishTime;
};

