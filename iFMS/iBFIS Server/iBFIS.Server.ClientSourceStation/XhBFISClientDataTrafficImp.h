#pragma once
#include "IBFISClientSource.h"
#include "iBFIS_Communication.h"
//#include "iCMSP_SimpleLock.h"
#include "IBFISClientSource.h"
#include "IBFISClientDataTrafficSource.h"
#include <map>
#include "Poco/Mutex.h"
#include "IThread.h"
#include "iBFIS_ServerTaskBase.h"
#include "ICallbackManagement.h"
#include "IBFISSerializeDataMemoryModel.h"
#include <unordered_map>

struct ST_Login
{
	ST_EmployeeInfo stInfo;
	std::string strUrl;
};
struct ST_StoreSet
{
	int nFixedTermSaveTime;
	int nUnFixedTermSaveTime;
	int nNeedAddInforSaveTime;
	int nMarkCanceledSaveTime;
	int nOperateLogSaveTime;
};
class XhBFISClientDataTrafficImp : public IBFISClientDataTrafficSource,public IRunable
{
public:
	XhBFISClientDataTrafficImp();
	~XhBFISClientDataTrafficImp();
public:
	//
	virtual ISOC_BOOL Init();
	virtual ISOC_BOOL UnInit();
	virtual ISOC_BOOL InitStation();
	virtual ISOC_BOOL UnInitStation();
	virtual void DisConnect(UINT64 fromAddr);
	virtual ISOC_BOOL GetEmployeeId(UINT64 fromAddr,string& strId);
	virtual ISOC_BOOL PraseGetKeyValueData(ST_StoreSet& stStoreSet);
	//virtual ISOC_BOOL HandleFixedTermBusiness(vector<ST_BusinessInfo>& vecBusiness,ST_StoreSet& stStoreSet);
	virtual ISOC_BOOL HandleUnFixedTermBusiness(vector<ST_BusinessInfo>& vecBusiness,ST_StoreSet& stStoreSet);
	ISOC_BOOL GetDeviceInfo(vector<string>& arrDrives);
	virtual ISOC_BOOL TimingDelOperateLog(int nOperateLogSaveTime);
	virtual ISOC_BOOL HandleDelBusinessByVideoEndTime(vector<ST_BusinessInfo>& vecBusiness,ST_StoreSet& stStoreSet);
	//接收信令并发送数据
	virtual int OnRecvData(UINT64 fromAddr,DWORD_PTR& d);
	virtual int OnRecvData(UINT64 fromAddr,DWORD_PTR& d,std::string& s);
	virtual int OnRecvData(UINT64 fromAddr,DWORD_PTR& d1,std::vector<std::string>& v1);
	virtual int OnRecvData(UINT64 fromAddr,DWORD_PTR& d1,std::vector<std::string>& v1,std::vector<std::string>& v2, std::vector<std::string>& v3);

	/////////////////IRunable///////////////////////////////
	virtual ISOC_VOID Run();
private:
	bool GetEmployeeName(UINT64 fromAddr,string& strInfo);
	static DBOperType Cmd2DataOperType(DWORD dwCmd);
	static string Cmd2Msg(DWORD dwCmd);
private:
	int  ClientLogin2(UINT64 fromAddr, std::vector<std::string>& v1 );
	int  ClientGetBranchInfo(std::vector<std::string>& v1);
	int  ClientGetProduceInfo( std::vector<std::string>& v1 );
	int  ClientGetPurviewInfo(std::vector<std::string>& v1);
	int  ClientGetRoleInfo(std::vector<std::string>& v1);
	int  ClientGetPolepurviewInfo(std::vector<std::string>& v1);
	int  ClientGetEmployeeInfo(std::vector<std::string>& v1);
	int  ClientGetEmployeepurviewInfo(std::vector<std::string>& v1);
	int  ClientGetEmployeepurviewInfo(IBFISSerializeDataMemoryModel **pEmployeePurviewInfo);
	int  ClientGetUserMapInfo(std::vector<std::string>& v1);
	int  ClientGetClientInfo(std::vector<std::string>& v1);
	int  ClientGetScriptInfo(std::vector<std::string>& v1);
	std::string PackMeg(std::vector<std::string>& strResult);
	int  ParseMeg(std::string& meg, std::vector<std::string>& strResult);
private:
	std::unordered_map<UINT64, ST_Login> m_mapClientContext;
	Poco::FastMutex  m_csLockClientContext;
	IBFISClientSource* m_pClientSource;
	IBFISCommunicateSyncServer* m_pCommunicateSource;
	std::string	m_strLocalBranchId;
	IThread* m_pThread;
	BOOL m_bCheckUnFinishEmp;
	std::map<string,UINT64> m_mapUserName;
	ICallbackManagement* m_pCallbackManager;
};
