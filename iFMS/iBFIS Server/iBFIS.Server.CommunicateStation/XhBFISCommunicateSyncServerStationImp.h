#pragma once
#include "iBFIS_Communication.h"
#include "iCMSP_SimpleLock.h"
#include "IBFISClientDataTrafficSource.h"
#include "IBFISSyncServer.h"
#include "IBFISSyncClient.h"
#include "IBFISCommunicateSyncServer.h"
#include "IThread.h"
#include <map>
#include <set>
#include "Poco/Mutex.h"
#include "XhConnectionHandleArray.h"
#include "iBFIS_UniqueDefine.h"
#include "IBFISDataProvider.h"
#include "IBFISPluginInterface.h"
#include <unordered_map>
#include <unordered_set>
#include "ICallbackManagement.h"
#include <boost/noncopyable.hpp>
#include "iBFIS_SimpleCS.h"
#include "XhBFISCommunicateServerIsLive.h"
#include "xhObjectRefCount.h"
#include <boost/unordered_map.hpp>
#include <boost\thread.hpp>


#define CLINET_CONNET_DISTRIBUTION 20
#define MODULE_NAME "[服务端模块]"

struct _NotifyMessage
{
	int nType;
	DWORD_PTR dwCmd;
	vector<std::string> vecStr;
	DWORD_PTR dwReserved;
};

struct ST_BasicSetting
{
	string strSynchroInfoPath;
	int nAutomaticSynchroChecked;
	string strSynchroTime;
	string strCoreSystemIP;
	string strFinancialSystemIP;
	int nPublicPort;
};
class XhBFISCommunicateSyncServerStationImp : public IBFISCommunicateSyncServer,public IRMICallbackSkin,public IRunable,public IBFISBankPluginMsgCb
{
public:
	XhBFISCommunicateSyncServerStationImp();
	~XhBFISCommunicateSyncServerStationImp();
	//***************************** IBFISBankPluginMsgCb **************************************************************************/
	virtual void MsgCallback(ST_BusinessDockMsgInfo* pBusinessDockMsgInfo,const IBFIS_DWORDPTR dwCookie = 0,IBFIS_DWORDPTR dwResevered = 0);
	
	virtual ISOC_BOOL Init();
	virtual ISOC_BOOL UnInit();

	//设置监听端口(同时监听SyncClient和Client)
	virtual int DoListenOn(IN long localIp, IN short localPort, IN DWORD_PTR dwReserved = 0);
	//停止监听端口
	virtual int StopListen(IN DWORD_PTR dwReserved = 0);

	virtual int OnConnected(HANDLE hContext);
	virtual int OnDisConnected(HANDLE hContext);
	virtual int OnGotError(HANDLE hContext,int nErrorCode,std::string strErrorDes);
	//接收信令并发送数据
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d);
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d,std::string& s);
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,std::vector<std::string>& v1);
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,std::vector<std::string>& v1,std::vector<std::string>& v2, std::vector<std::string>& v3);
	virtual int OnInvoke(HANDLE hContext,std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2);
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,DWORD_PTR& d2,std::string& s);

	//发送数据到控制端
	virtual int DoSendData(IN HANDLE hClient, IN DBOperType enType,IN DWORD_PTR d1, IN string s1, IN DWORD_PTR dwReserved = 0);
	virtual int DoSendData(IN HANDLE hClient, IN DBOperType enType,IN DWORD_PTR d1, IN std::vector<std::string>& v1, IN DWORD_PTR dwReserved = 0);
	virtual int DoSendData(IN HANDLE hClient, IN DWORD_PTR d1,IN DWORD_PTR d2, IN string s, IN DWORD_PTR dwReserved = 0);
	virtual int DoSendData(IN HANDLE hClient, std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2, IN DWORD_PTR dwReserved = 0);
	virtual int DoSendData(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN BYTE* pData, IN int nDataSize, IN DWORD_PTR dwReserved = 0);
	//可扩展函数接口
	virtual int  ExtendFunction(IN const int nExtendType, IN DWORD_PTR dwExtendData);
	//注册消息处理对象
	virtual int RegisterRecvMessageCallbackSkin(IN DWORD_PTR dwCmdID,IN IBFISTaskStation* pProcessStation,IN ISOC_DWORDPTR dwReserved = 0);
	//取消消息任务处理对象
	virtual int UnRegisterRecvMessageCallbackSkin(IN DWORD_PTR dwCmdID,IN IBFISTaskStation* pProcessStation,IN ISOC_DWORDPTR dwReserved = 0);

	virtual int AddNotifyMsg(IN DBOperType enType,IN DWORD_PTR dwCmdID,IN string s1,IN DWORD_PTR dwReserved = 0);
	virtual int AddNotifyMsg(IN DBOperType enType,IN DWORD_PTR dwCmdID,IN std::vector<std::string>& v1,IN DWORD_PTR dwReserved = 0);

    virtual int SetOfflineSyscData(vector<ST_BranchInfo>& vecBranchInfo, vector<ST_EmployeeInfo>& vecEmployeeInfo);
    virtual int GetOfflineSyscData(vector<ST_BranchInfo>& vecBranchInfo, vector<ST_EmployeeInfo>& vecEmployeeInfo);

	virtual int CheckIsTopServer(int nNum);
	virtual BOOL PraseGetKeyValueData();
	void GetRandomSerialNum(string& strRandomSerialNum);
	bool CreateBankDockingPlugin();
	BOOL ReviewBusinessSerialNum(ST_BusinessDockMsgInfo& stBusinessDockMsgInfo);
	void GetRecvMessage(string& strRecvMsg,string strSucessedFlag,string strDescribeInfo);

	/////////////////IRunable///////////////////////////////
	virtual ISOC_VOID Run();

	//ANASY
	void NotifyMegHandle(ST_CallBackInfo stCallBackInfo);
	void DockingMessageHandle(std::string meg);
	void HandleDockingRecvVideoStatus(std::vector<std::string>& v1);

private:

	void CheckDiskSpace(int time);
	//发送数据到控制端
	int XhDoSendData(IN HANDLE hClient, IN DBOperType enType,IN DWORD_PTR d1, IN string& s1, IN DWORD_PTR dwReserved = 0);
	int XhDoSendData(IN HANDLE hClient, IN DBOperType enType,IN DWORD_PTR d1, IN std::vector<std::string>& v1, IN DWORD_PTR dwReserved = 0);
	int XhDoSendData(IN HANDLE hClient, IN DWORD_PTR d1,IN DWORD_PTR d2, IN string s, IN DWORD_PTR dwReserved = 0);
	int XhDoSendData(IN HANDLE hClient, std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2, IN DWORD_PTR dwReserved = 0);
	int XhDoSendData(IN HANDLE hClient, IN DWORD_PTR d1, IN string s, IN DWORD_PTR dwReserved = 0);

	static string Cmd2Msg(IN DBOperType enType,IN DWORD_PTR dwCmd);
	int  ClinetNotifyDiskAndConnect(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved);
	int  ClinetQueryOperateLogInfo(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved);
	int  SendLowerLevelServer(_NotifyMessage &itemMeg);
	int  SendHigherServer( _NotifyMessage &itemMeg);
	int  AddConnectAndDiskStatus(IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved);
	int  DelConnectAndDiskStatus(IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved);
	int  QueryConnectAndDiskStatus(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved);
	int  CheckDiskSpaceInfo(IN HANDLE hClient, IN DWORD_PTR dwReserved = 0);

	int SendLoginQueryInfo(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN std::vector<std::string>& v1, IN DWORD_PTR dwReserved);
	int SendLoginQueryInfo(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN BYTE *pData, IN int nDataSize, IN DWORD_PTR dwReserved);
	int SendDefaultInfo(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN std::vector<std::string>& v1, IN DWORD_PTR dwReserved);

	int SendMegToClinet(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR dwCmd, std::vector<std::string> &vecParam, IN DWORD_PTR dwReserved);
	int SendMegToClinet(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR dwCmd, std::string &strParam, IN DWORD_PTR dwReserved);
	int SendMegToClinet(_NotifyMessage &meg);
	int SendMegToAllClinet(IN DBOperType enType, IN DWORD_PTR dwCmd, std::string &strParam, IN DWORD_PTR dwReserved);

	int GetArrayKey(IN HANDLE hClient, int nRange = CLINET_CONNET_DISTRIBUTION);
	inline void RcfConnectCheck(int errorCode, HANDLE hClient) 
	{
		if (errorCode == -17 || errorCode == -49 || errorCode == -34) 
		{
			auto var = boost::async(boost::launch::async, [this, hClient]() { 
				OnDisConnected(hClient);
			}); 
		}
	}
private:
	IThread* m_pThread;
	iBFIS_CommunicationServer* m_pNetServer;

	iCMSP_SimpleCS m_csBranchContext;
	iCMSP_SimpleCS m_csNotifyMsg;
	iCMSP_SimpleCS m_csDeletedContext;
	
	iCMSP_SimpleCS m_csNewClinetContext;
	iCMSP_SimpleCS m_csClinetContext;
	iCMSP_SimpleCS m_csNewBranchClinetContext;
	iCMSP_SimpleCS m_csBranchClinetContext;

	IBFISClientDataTrafficSource* m_pClientDataTrafficSource;  //监听客户端连接的对象
	IBFISSyncServer* m_pSyncServer;  //与下级服务器同步的服务器对象
	IBFISSyncClient* m_pSyncClient;  //与上级服务器相连的对象

	boost::unordered_map<DWORD,IBFISTaskStation*> m_mapTaskStation;	//任务注册

	boost::shared_mutex            m_connectMtx;
	boost::shared_mutex            m_connectUserClientMtx;
	boost::shared_mutex            m_connectBranchClientMtx;
	boost::shared_mutex            m_connectBranchClientInfoMtx;
	
	std::map<HANDLE, std::shared_ptr<ObjectRefCount<HANDLE> > >  m_mapClientContext;
	std::map<HANDLE, std::shared_ptr<ObjectRefCount<HANDLE> > >  m_mapUserClinetContext;
	std::map<HANDLE, std::shared_ptr<ObjectRefCount<HANDLE> > >  m_mapBranchClinetContext;
	std::map<string, std::shared_ptr<ObjectRefCount<HANDLE> > > m_mapBranchContextInfo;

	std::vector<_NotifyMessage> m_vecNotifyMsg;	//通知消息
    std::vector<ST_BranchInfo> m_vecBranchInfo; 
    std::vector<ST_EmployeeInfo> m_vecEmployeeInfo;
	std::vector<ST_BusinessDockMsgInfo> m_vecBusinessDockMsgInfo;
	BOOL m_bNeedStop;
	int m_nServerType;
	IBFISDataProvider* m_pCache;
	std::string		m_strLocalBranchId;
	ST_BranchInfo	m_stBranchInfo;
	ST_BasicSetting m_stBasicSetting;
	IBFISBankPluginInterface *m_pBankPluginInter;
	ST_BusinessDockMsgInfo m_stBusinessDockMsgInfo;
	ICallbackManagement* m_pCallbackManager;
	CString m_strPluginName;

	XhBFISCommunicateServerIsLive  m_localServerCheck;

	std::shared_ptr<boost::thread>    m_dockingThread;
	boost::mutex            m_dockingMtx;
	boost::condition_variable m_dockingCondition;
	std::set<std::string>   m_dockingMegSet;

};
