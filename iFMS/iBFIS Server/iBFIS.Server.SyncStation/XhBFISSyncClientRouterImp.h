#pragma once
#include "iBFIS_Communication.h"
#include "iBFIS_UniqueDefine.h"
#include "IBFISSyncClient.h"
#include "IThread.h"
//#include "iBFISDBOperation.h"
#include "IBFISCommunicateSyncServer.h"
#include "IBFISDataProvider.h"
#include "iBFISDBOperation.h"
#include "ITimer.h"
#include "Poco/Mutex.h"
#include <vector>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp> 
#include <memory>
#include <boost\atomic\atomic.hpp>
#include "xhObjectRefCount.h"


using namespace std;

class XhBFISOutgoingDeviceSyncClient;

class XhBFISSyncClientRouterImp:public IRMICallbackSkin,public IRunable,public IBFISSyncClient,public ITimerCallbackSkin
{
public:
	XhBFISSyncClientRouterImp(void);

	virtual ~XhBFISSyncClientRouterImp(void);

	////////////////IRMICallbackSkin///////////////////////////
	virtual int OnInvoke(HANDLE hContext, DWORD_PTR& d);
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d,BYTE* pData,int nDataLen);
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d,std::string& s);
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,std::vector<std::string>& v1);
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,DWORD_PTR& d2,std::string& s);
	virtual int OnInvoke(HANDLE hContext,std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2);

	virtual int OnConnected(HANDLE hContext);
	virtual int OnDisConnected(HANDLE hContext);
	virtual int OnGotError(HANDLE hContext,int nErrorCode,std::string strErrorDes);

	////////////////IBFISSyncClient///////////////////////////
	virtual int Init(string strIp,string strPort,string strUser,string strPwd);
	virtual int UnInit();

	virtual int DoConnect(IN ISOC_LONG remoteIp, IN ISOC_SHORT remotePort, IN ISOC_DWORDPTR dwReserved = 0);
	virtual int DoDisConnect(IN ISOC_DWORDPTR dwReserved = 0);

	virtual int StartSync(IN ISOC_DWORDPTR dwReserved = 0);
	virtual int StopSync(IN ISOC_DWORDPTR dwReserved = 0);
	virtual int SetSyncInterval(IN ISOC_INT nSecond, IN ISOC_DWORDPTR dwReserved = 0);
	virtual int SetLocalUrl(IN const string& szUrl,IN ISOC_DWORDPTR dwReserved = 0);

    virtual int GetParentSMSInfo(string& strIp, string& strPort, string& strUser, string& strPwd);
    virtual int GetParentBranchInfo(string& strBranchID, string& strBranchName, string& strParentID);
	virtual int ExtendFunction(IN const ISOC_INT nExtendType,IN ISOC_DWORDPTR dwExtendData);

	virtual int DoNotifyData(IN DWORD_PTR d1,IN DWORD_PTR d2, IN string s, IN DWORD_PTR dwReserved = 0);
	virtual int DoNotifyData(std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2, IN DWORD_PTR dwReserved = 0);

	virtual bool GetNeedSyncBranchInfo(vector<ST_BranchInfo>& vecBranchInfo,DWORD_PTR dwReserved = 0);
	virtual bool GetNeedSyncRoleInfo(vector<ST_RoleInfo>& vecRoleInfo,DWORD_PTR dwReserved = 0);
	virtual bool GetNeedSyncRolePurviewInfo(vector<ST_RolePurviewInfo>& vecRolePurviewInfo,DWORD_PTR dwReserved = 0);
	virtual bool GetNeedSyncClientInfo(vector<ST_ClientInfo>& vecClientInfo,DWORD_PTR dwReserved = 0);
	virtual bool GetNeedSyncBusinessInfo(vector<ST_BusinessInfo>& vecBusinessInfo,DWORD_PTR dwReserved = 0);
	virtual bool GetNeedSyncBusinessFileInfo(vector<ST_BusinessFileInfo>& vecBusinessFileInfo,DWORD_PTR dwReserved = 0);
	virtual bool GetNeedSyncBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecBusinessRelateInfo,DWORD_PTR dwReserved = 0);
	virtual bool GetNeedSyncEmployeeInfo(vector<ST_EmployeeInfo>& vecEmployeeInfo,DWORD_PTR dwReserved = 0);
	virtual bool GetNeedSyncEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecEmployeePurviewInfo,DWORD_PTR dwReserved = 0);
	virtual int	ReadClientInfoSyncTime(std::string& strTime);
	virtual int WriteClientInfoSyncTime();
	/////////////////IRunable///////////////////////////////
	virtual ISOC_VOID Run();
	/////////////////ITimer/////////////////////////////////
	virtual ISOC_VOID OnTimer(IN ISOC_ID iTimerID);
	
	bool ReConnect2Server();
	//登陆,发送客户端的相关信息
	int DoLogin(DWORD_PTR dwReserved = 0);

	//上传网点信息
	int DoSyncBranchInfo(vector<ST_BranchInfo>& vecInfos,DWORD_PTR dwReserved = 0);
	//上传角色信息
	int DoSyncRoleInfo(vector<ST_RoleInfo>& vecInfos,DWORD_PTR dwReserved = 0);
	//上传角色权限权限信息
	int DoSyncRolePurview(vector<ST_RolePurviewInfo>& vecInfos,DWORD_PTR dwReserved = 0);
	//获取用户组权限
	//int DoSyncPurview(DWORD_PTR dwReserved = 0);
	//获取客户信息
	int GetSyncClientInfo(DWORD_PTR dwReserved = 0);
	//上传客户信息
	int DoSyncClientInfo(vector<ST_ClientInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	//上传员工信息
	int DoSyncEmployeeInfo(vector<ST_EmployeeInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	//上传员工权限信息
	int DoSyncEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	//获取产品信息
	int DoSyncProduceInfo(DWORD_PTR dwReserved = 0);
	//上传业务信息
	int DoSyncBusinessInfo(vector<ST_BusinessInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	//上传业务文件信息
	int DoSyncBusinessFileInfo(vector<ST_BusinessFileInfo>& vecInfos, DWORD_PTR dwReserved = 0);
	//上传业务关联信息
	int DoSyncBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	//服务器下发的处理
	int HandleIssuedProduceInfo(const vector<std::string>& vecInfos , DWORD_PTR dwReserved = 0);
	int HandleIssuedRoleInfo(const vector<std::string>& vecInfos , DWORD_PTR dwReserved = 0);
	int HandleIssuedRolePurviewInfo(const vector<std::string>& vecInfos , DWORD_PTR dwReserved = 0);
	//int HandleIssuedPurviewInfo(vector<std::string>& vecInfos , DWORD_PTR dwReserved = 0);
	int HandleIssuedClientInfo(const vector<std::string>& vecInfos , DWORD_PTR dwReserved = 0);
    int HandleIssuedBranchInfo(const vector<std::string>& vecInfos , DWORD_PTR dwReserved = 0);
    int HandleIssuedEmployeeInfo(const vector<std::string>& vecInfos , DWORD_PTR dwReserved = 0);
	int HandleIssuedMigrateTasknfo(const vector<std::string>& vecInfos , DWORD_PTR dwReserved = 0);
	int HandleIssuedScriptInfo(const vector<std::string>& vecInfos , DWORD_PTR dwReserved = 0);
	int HandleIssuedEmployeePurviewInfo(const vector<std::string>& vecInfos, DWORD_PTR dwReserved = 0);
    int IssuedBranchInfo();
    int IssuedEmployeeInfo();
	void ConnectCheckTh();
private:
	int ClientInfoNotify(int nType,ST_ClientInfo& stInfo);
	int ProduceInfoNotify(int nType,ST_ProduceInfo& stInfo);
	void ReadOutgoingDeviceXml();

	void SaveBackupData();
	void LoadBackupData();
	//保存到本地数据库
	BOOL StoreRoleInfo(DBOperType& enType,ST_RoleInfo& stRoleInfo);
	BOOL StoreClientInfo(DBOperType enType,ST_ClientInfo& stClientInfo);
	//BOOL StorePurviewInfo(DBOperType& enType,ST_PurviewInfo& stPurviewInfo);
	BOOL StoreProduceInfo(DBOperType enType,ST_ProduceInfo& stProduceInfo);
	BOOL StoreRolePurviewInfo(DBOperType& enType,ST_RolePurviewInfo& stRolePurviewInfo);
    void GuidProducer(CString& strGuid);

private:
	ITimer* m_pTimer;
	IBFISCommunicateSyncServer* m_pComm;
	iBFIS_CommunicationClient* m_pNetClient;
	IThread* m_pThread;
	//IBFISDBOperation* m_pDbOper;
	IBFISDataProvider* m_pCache;

	std::string m_strRemoteIP;
	unsigned short m_usRemotePort;

	BOOL m_bNeedStop;
	BOOL m_bNeedReConnect;
	//ObjectRefCount<HANDLE> m_hServerContext;
	//boost::shared_mutex m_csLockServerContext;

	HANDLE m_hServerContext;
	Poco::FastMutex  m_csLockConnectServer;
	ST_BranchInfo m_stBranchInfo;
	int m_nSyncInterval;
	string m_strUrl;
	//
	vector<ST_ClientInfo> m_vecBackupClient;
	vector<ST_RoleInfo> m_vecBackupRole;
	vector<ST_RolePurviewInfo> m_vecBackupRolePurview;
	vector<ST_PurviewInfo> m_vecBackupPurview;
	vector<ST_ProduceInfo> m_vecBackupProduce;

    vector<ST_BranchInfo> m_vecIssuedBranchInfo;
    vector<ST_EmployeeInfo> m_vecIssuedEmployeeInfo;

	bool   m_bIsStopReconnectThread;
	std::shared_ptr<boost::thread> m_spCheckConnectThread;
	boost::mutex m_cheackConnectMutex;
	boost::condition_variable m_cheackConnectCondition;

	GeneralEvent   m_syncEvent;

	boost::mutex m_mutexHeart;
	DWORD        m_dwHeartTime;
	std::shared_ptr<XhBFISOutgoingDeviceSyncClient>  m_outgoingDevice;
};

