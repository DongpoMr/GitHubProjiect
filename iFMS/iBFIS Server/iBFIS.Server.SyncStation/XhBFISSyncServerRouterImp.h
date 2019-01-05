#pragma once
#include "iBFIS_Communication.h"
#include "IBFISSyncServer.h"
#include "iBFISDBOperation.h"
#include "IBFISDataProvider.h"
#include "Icms_PIocpSocket.h"
#include "IThread.h"
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <boost\atomic\atomic.hpp>
//#include "iCMSP_SimpleLock.h"
#include "Poco/Mutex.h"
#include "Poco/Event.h"
#include "IBFISPluginInterface.h"
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "xhObjectRefCount.h"
#include <fstream>


#define ICMS_IP_INT64TOSTR(nIP,pszIP) \
	sprintf(pszIP,_T("%d.%d.%d.%d:%d"), \
	(ntohl(nIP>>32)&0x000000FF),    (ntohl(nIP>>32)&0x0000FF00)>>8,\
	(ntohl(nIP>>32)&0x00FF0000)>>16,(ntohl(nIP>>32)&0xFF000000)>>24,\
	nIP&0xffffffff)


#define CLINET_SUBSERVER_MASK 31   //b("11111")

struct ST_Login
{
	ST_BranchInfo stInfo;
	string strUrl;
	// -1:等待登陆后所有消息都同步给下级还未完成，0:登陆后，下发同步信息完成但未发送同步消息 1:向下级发送同步启动消息成功 2:同步处理完成
	boost::atomic_int notifyStatus;
};
enum EN_KeyValue
{
    BasicSetting = 112501,
    SynchroSetting = 112502,
    StorageSetting = 112503,
    PasswordStrategy = 112504
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
struct ST_PasswordStrategy
{
    int nTimeoutLockChecked;
    string strPWDValidTime;
    string strRemindAdvanceTime;
    int nErrorLockChecked;
    int nMaxErrorTimes;
    int nForcedModifyChecked;
    string strInitialPWD;
};
class XhBFISSyncServerRouterImp:public IBFISSyncServer, public IRunable
{
public:
	XhBFISSyncServerRouterImp(void);

	virtual~XhBFISSyncServerRouterImp(void);

public:

	//////////////////////IBFISSyncServer////////////////////////////////////////
	virtual int Init(ISOC_DWORDPTR dwReserved = 0);
	virtual int UnInit(ISOC_DWORDPTR dwReserved = 0);
	virtual void OnDisConnect(UINT64 fromAddr);

	virtual int InitStation();	//在各自的初始化函数中调用IBFISCommunicateStation的RegisterRecvMessageCallbackSkin来注册各自需要处理的信令
	virtual int UnInitStation();
	virtual int OnRecvData(UINT64 fromAddr,DWORD_PTR& d);
	virtual int OnRecvData(UINT64 fromAddr,DWORD_PTR& d,std::string& s);
	virtual int OnRecvData(UINT64 fromAddr,DWORD_PTR& d1,std::vector<std::string>& v1);
	virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d1, DWORD_PTR& d2, std::string& s);
	virtual int OnRecvData(UINT64 fromAddr, std::vector<DWORD_PTR>& v1, std::vector<std::string>& v2);

	virtual int DoRealTimeSync(IN ISOC_DWORDPTR dwReserved = 0);
	virtual int	DoSyncAll(vector<ST_BranchInfo> vecBranchInfo, IN ISOC_DWORDPTR dwReserved = 0);
	virtual int ExtendFunction(IN const ISOC_INT nExtendType,IN ISOC_DWORDPTR dwExtendData);

	virtual bool GetNeedSyncProduceInfo(vector<ST_ProduceInfo>& vecProduceInfo);
	virtual bool GetNeedSyncRoleInfo(vector<ST_RoleInfo>& vecRoleInfo);
	virtual bool GetNeedSyncClientInfo(vector<ST_ClientInfo>& vecClientInfo);
	virtual bool GetNeedSyncBranchInfo(vector<ST_BranchInfo>& vecBranchInfo);
	virtual bool AddClientInfoToDataBase(ST_ClientInfo sClientInfo);
	///////////////////////IRunable///////////////////////////////////////////
	virtual void Run();
	//客户端获取的处理
	int IssueSyncClientInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved = 0);
	int IssueSyncProduceInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved = 0);
	int IssueSyncRoleInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved = 0);
	//int IssueSyncPurviewInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved = 0);
	int IssueSyncRolePurviewInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved = 0);

	//客户端上传的处理
	int OnGotUploadBranchInfo(ST_BranchInfo& stInfo, DWORD_PTR dwReserved = 0);
	int OnGotUpLoadClientInfo(ST_ClientInfo& stInfo, DWORD_PTR dwReserved = 0);
	int OnGotUpLoadBusinessInfo(ST_BusinessInfo stInfo, DWORD_PTR dwReserved = 0);
	int OnGotUpLoadBusinessFileInfo(ST_BusinessFileInfo stInfo, DWORD_PTR dwReserved = 0);
	int OnGotUpLoadBusinessRelateInfo(ST_BusinessRelateInfo stInfo, DWORD_PTR dwReserved = 0);
	int OnGotUpLoadEmployeeInfo(ST_EmployeeInfo& stInfo, DWORD_PTR dwReserved = 0);
	int OnGotUpLoadEmployeePurviewInfo(ST_EmployeePurviewInfo& stInfo,DWORD_PTR dwReserved = 0);
	int OnGotUpLoadRoleInfo(ST_RoleInfo& stInfo,DWORD_PTR dwReserved = 0);
	int OnGotUpLoadRolePurviewInfo(ST_RolePurviewInfo& stInfo,DWORD_PTR dwReserved = 0);

	//
	int DoSyncClientInfo(void* toAddr,std::vector<ST_ClientInfo>& vecInfo,DWORD_PTR dwReserved = 0);
	int DoSyncProduceInfo(void* toAddr,std::vector<ST_ProduceInfo>& vecInfo,DWORD_PTR dwReserved = 0);
    int DoSyncEmployeeInfo(void* toAddr,std::vector<ST_EmployeeInfo>& vecInfo,DWORD_PTR dwReserved = 0,std::string strBranch = "");
    int DoSyncBranchInfo(void* toAddr,std::vector<ST_BranchInfo>& vecInfo,DWORD_PTR dwReserved = 0, std::string strBranch = "");
	int DoSyncRoleInfo(void* toAddr,std::vector<ST_RoleInfo>& vecInfo,DWORD_PTR dwReserved = 0);
	int DoSyncRolePurviewInfo(void* toAddr,std::vector<ST_RolePurviewInfo>& vecInfo,DWORD_PTR dwReserved = 0);
	int DoSyncKeyValueInfo(void* toAddr,DWORD_PTR dwReserved = 0);
	int DoSendData(IN HANDLE hSysHandle, IN DBOperType enType, IN DWORD_PTR d1, IN std::vector<std::string>& v1, IN DWORD_PTR dwReserved = 0);
	int DoSyncMigrateTaskInfo(void* toAddr,DWORD_PTR dwReserved = 0);
	int DoSyncScriptInfo(void* toAddr,DWORD_PTR dwReserved = 0);

	//解析并处理
	void ParseClientInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved = 0);
	void ParseBusinessInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved = 0);
	void ParseBusinessFileInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved = 0);
	void ParseBusinessRelateInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved = 0);
	void ParseEmployeeInfo(vector<std::string>& vecStr,DWORD_PTR dwReserved = 0);

	//解析并设置同步状态
	void ParseClientInfoAndSetSyncState(vector<std::string>& vecStr,bool bstate = true,DWORD_PTR dwReserved = 0);
	void ParseProduceInfoAndSetSyncState(vector<std::string>& vecStr,bool bstate = true,DWORD_PTR dwReserved = 0);
	void ParseRoleInfoAndSetSyncState(vector<std::string>& vecStr,bool bstate = true,DWORD_PTR dwReserved = 0);
	//void ParsePurviewInfoAndSetSyncState(vector<std::string>& vecStr,bool bstate = true,DWORD_PTR dwReserved = 0);
	void ParseRolePurviewInfoAndSetSyncState(vector<std::string>& vecStr,bool bstate = true,DWORD_PTR dwReserved = 0);

	//根据EmployeeId删除EmployeePurviewInfo
	bool DelEmployeePurviewInfo(vector<std::string> vecStr,DWORD_PTR dwReserved = 0);

	//与ListCtrl绑定
	virtual void SetDisplayListCtrl(CListCtrl* pList);
	void SetBranchLoginLog(ST_BranchInfo stBranchInfo);
	void SetBranchLogoutLog(ST_BranchInfo stBranchInfo);
	bool AddBranchLog(ST_BranchInfo stBranchInfo);
	bool ModifyBranchLog(ST_BranchInfo stBranchInfo);
	bool FindBranchLog(CString strBranchInfoId);

	//
	virtual bool RestoreLastSyncTime(CString strTime);
	virtual bool ReadLastSyncTime(CString& strTime);

    BOOL ReadFileAndParse(string strPath);
    void FileContentPraseToBranchInfo(vector<std::string> vecPathList);
    void FileContentPraseToKernelEmployeeInfo(vector<std::string> vecPathList);
    void FileContentPraseToFinancEmployeeInfo(vector<std::string> vecPathList);
    void FileContentPraseToFinancProduceInfo(vector<std::string> vecPathList);
    void FileContentPraseToFundProduceInfo(vector<std::string> vecPathList);

    void HandleReadProductInfo();
    void HandleReadBranchInfo();
    void HandleReadEmployInfo();
	void HandleUserPurview();
	
	int HanaleSubBranchEmployInfo();
    BOOL PraseGetKeyValueData();
    BOOL GetFileFromFTP(CString LocalPath);
    BOOL PraseURL(CString& strFtpPath,CString& strFtpAdd,CString& strFtpUser,CString& strFtpPass,int& nFtpPort);
    BOOL TimeCompare();
	int CheckIsTopServer(int nType);
	BOOL DeleteDirectory(char* strDirName);
	int HandleManualSync(ST_ManualSyncParameter& stManualSyncParameter);
	int EmployeeStopUse();

private:
	int BranchInfoNotify(int nType,ST_BranchInfo& stInfo);
	int ProduceInfoNotify(int nType,ST_ProduceInfo& stInfo);
	int UserMapInfoNotify(int nType,ST_UserMapInfo& stInfo);
	int RoleInfoNotify(int nType,ST_RoleInfo& stInfo);
	int EmployeeInfoNotify(int nType,ST_EmployeeInfo& stInfo);
	int ClientInfoNotify(int nType,ST_ClientInfo& stInfo);
	int RolePurviewInfoNotify(int nType,std::vector<ST_RolePurviewInfo>& vecInfo);
	int EmployeePurviewInfoNotify(int nType,std::vector<ST_EmployeePurviewInfo>& vecInfo);
	int KeyValueInfoNotify(int nType,ST_KeyValueInfo& stInfo);
	int BusinessInfoNotify(int nType,ST_BusinessInfo& stInfo);
	int BusinessFileInfoNotify(int nType,ST_BusinessFileInfo& stInfo);
	int BusinessRelateInfoNotify(int nType,ST_BusinessRelateInfo& stInfo);
	int VirturlBranchInfo();
	vector<string> GetDatFilePathList(string strPath,string strName,vector<string> vecFileList);

	void GuidProducer(CString& strGuid);
	BOOL CreateIniFile(CString strPath);
	string Cmd2Msg(DWORD_PTR dwCmd);
	bool GetBranchName(UINT64 fromAddr,string& strInfo, int &bSync);
	BOOL GetLocalBranchId(std::string& strBranchId);
	BOOL IsSyncBranchInfo(string strBranchId);
	int      SubServerSyncNotify(HANDLE hClinet);
	void   SyncSubServerWork();
	//iBFIS_CommunicationServer* m_pNetServer;
private:
	IBFISDataProvider* m_pCache;

	IBFISCommunicateSyncServer* m_pComm;

	std::string		m_strLocalIp;
	unsigned short	m_usLocalPort;
	BOOL			m_bNeedStop;
	BOOL			m_bNeedReConnect;
	std::map<UINT64, std::shared_ptr<ObjectRefCount<ST_Login> > >  m_mapClientContext;
	boost::shared_mutex m_csLockClientContext;
	//std::map<UINT64, ST_Login>  m_mapClientContext;
	//Poco::FastMutex  m_csLockClientContext;
	CListCtrl*		m_pListctrl;
	//IThread*		m_pThread;
	vector<IThread*> m_vecThread;
	ST_BranchInfo	m_stBranchInfo;
	BOOL			m_bSync;
	BOOL			m_bBusy;
	std::string		m_strLocalBranchId;
	Poco::Event		m_eventWaitThread;
    iCMS_PTcpListner*	m_pTcpListen;
    UINT32			    m_unListenPort;
    vector<ST_BranchInfo> m_vecBranchInfo;
    vector<ST_EmployeeInfo> m_vecEmployeeInfo;
    vector<ST_ProduceInfo> m_vecProduceInfo;
	vector<string> m_vecSyncEndBranchId;
	IThread* m_pThread;

    ST_BasicSetting m_stBasicSetting;
    ST_PasswordStrategy m_stPasswordStrategy;
    CTime m_ctLocalDayTime;
    string m_strFtpPath;
	int m_nServerType;
	int m_mapClientCount;
	BOOL m_bManualSync;
	vector<ST_BranchInfo> m_vecSubBranchInfo;
	vector<string> m_vecFileName;
	ST_ManualSyncParameter m_stManualSyncParameter;

	boost::mutex m_mutex;
	boost::condition_variable m_condition;

	std::shared_ptr<boost::thread>    m_syncSubServerThread;
	bool                    m_bSyncSubServer;
	GeneralEvent       m_syncEvent;

	boost::mutex m_fileMutex;
	std::fstream   m_syncFile;
};

