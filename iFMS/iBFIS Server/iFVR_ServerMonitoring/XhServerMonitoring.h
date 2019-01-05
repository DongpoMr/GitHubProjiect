#pragma once
#include "stdafx.h"
#include "iBFIS_Communication.h"
#include "iCMSP_SimpleLock.h"
#include "iFVR_Configuration.h"
#include <memory>
#include <boost\thread.hpp>
#include <string>
#include <boost\thread\mutex.hpp>

class XhServerMonitoring: public IRMICallbackSkin
{
public:
	XhServerMonitoring();
	~XhServerMonitoring();
public:
	void StartMonitoring();
public:
	int OnConnected(HANDLE hContext) override;
	int OnDisConnected(HANDLE hContext) override;
	int OnGotError(HANDLE hContext, int nErrorCode, std::string strErrorDes) override;
	int OnInvoke(HANDLE hContext, DWORD_PTR& d) override { return 1; }
	int OnInvoke(HANDLE hContext, std::string& s) override { return 1; }
	int OnInvoke(HANDLE hContext, std::vector<DWORD_PTR>& v, DWORD_PTR& d1, DWORD_PTR& d2) override { return 1; }
	int OnInvoke(HANDLE hContext, std::vector<std::string>& v) override { return 1; }
	int OnInvoke(HANDLE hContext, BYTE* data, int nDataLen) override { return 1; }
	int OnInvoke(HANDLE hContext, std::vector<DWORD_PTR>& v1, std::vector<std::string>& v2) override { return 1; }
	int OnInvoke(HANDLE hContext, DWORD_PTR& d1, DWORD_PTR& d2) override { return 1; }
	int OnInvoke(HANDLE hContext, DWORD_PTR& d, std::string& s) override { return 1; }
	int OnInvoke(HANDLE hContext, DWORD_PTR& d, BYTE* pData, int nDataLen) override { return 1; }
	int OnInvoke(HANDLE hContext, DWORD_PTR& d1, DWORD_PTR& d2, DWORD_PTR& d3) override { return 1; }
	int OnInvoke(HANDLE hContext, std::string& s1, std::string& s2, std::string& s3) override { return 1; }
	int OnInvoke(HANDLE hContext, DWORD_PTR& d1, DWORD_PTR& d2, std::string& s) override { return 1; }
	int OnInvoke(HANDLE hContext, DWORD_PTR& d, std::string& s1, std::string& s2) override { return 1; }
	int OnInvoke(HANDLE hContext, DWORD_PTR& d1, DWORD_PTR& d2, DWORD_PTR& d3, DWORD_PTR& d4) override { return 1; }
	int OnInvoke(HANDLE hContext, std::string& s1, std::string& s2, std::string& s3, std::string& s4) override { return 1; }
	int OnInvoke(HANDLE hContext, DWORD_PTR& d1, std::vector<std::string>& v1) override { return 1; }
	int OnInvoke(HANDLE hContext, DWORD_PTR& d1, std::string& s1, std::vector<std::string>& v1, std::vector<std::string>& v2) override { return 1; }
	int OnInvoke(HANDLE hContext, DWORD_PTR& d1, std::vector<std::string>& v1, std::vector<std::string>& v2, std::vector<std::string>& v3) override { return 1; }
private:
	void LocalServerIsLive();
	int    KillProcessHandeByName(std::string&& strProcessName);
private:
	std::shared_ptr<iBFIS_CommunicationClient>  m_spNetClient;
	std::shared_ptr<boost::thread> m_spCheckLocalServerLiveTh;
	boost::mutex m_LocalServerConnectMtx;
	boost::condition_variable m_cheackLocalServerLiveCondition;
	bool   m_bIsStopCheckServerLive;

	boost::mutex m_hMtx;
	HANDLE       m_hClinet;
};

