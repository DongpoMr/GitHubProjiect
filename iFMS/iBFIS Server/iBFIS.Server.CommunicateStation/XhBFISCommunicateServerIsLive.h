#pragma once
#include "iBFIS_Communication.h"
#include "iCMSP_SimpleLock.h"
#include <memory>
#include <boost\thread.hpp>
#include <string>

class XhBFISCommunicateServerIsLive : public IRMICallbackSkin
{
public:
	XhBFISCommunicateServerIsLive();
	~XhBFISCommunicateServerIsLive();
public:
	int  Start(std::string strIp, short nPort);
	void CheckLocalServerIsLive();

public:
	virtual int OnConnected(HANDLE hContext);
	virtual int OnDisConnected(HANDLE hContext);
	virtual int OnGotError(HANDLE hContext, int nErrorCode, std::string strErrorDes);
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d);
private:
	std::shared_ptr<iBFIS_CommunicationClient>  m_spNetClient;

	bool   m_bIsStopCheckServerLive;
	std::shared_ptr<boost::thread> m_spCheckLocalServerLiveTh;
	boost::mutex m_LocalServerConnectMtx;
	boost::condition_variable m_cheackLocalServerLiveCondition;

	HANDLE       m_hClinet;
	iCMSP_SimpleCS m_csConnectContext;

	std::string    m_strIp;
	short          m_nPort;
};

