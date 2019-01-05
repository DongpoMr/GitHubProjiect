#pragma once
#include "stdafx.h"
#include "IBFISMigrateTaskStation.h"
#include <string>
#include <IThread.h>
#include "ITimer.h"
#include "IBFISCommunicateSyncServer.h"
#include "iCMSP_SimpleLock.h"
#include "XhMigrateItemImp.h"
#include "XhMigrateManagement.h"
#include "iBFISDBOperation.h"
#include <memory>

#include "Poco/Event.h"
#include "Poco/Mutex.h"
#include "Poco/Path.h"
#include "Poco/File.h"

#include <boost/thread.hpp>

class XhMigeratePlanMan;
class IBFISDataProvider;

class XhBFISMigrateTaskStationImp :public IMigrateTaskStation, public IRunable,public ITimerCallbackSkin
{
public:
    XhBFISMigrateTaskStationImp();

    virtual ~XhBFISMigrateTaskStationImp();

    virtual int InitStation();	//在各自的初始化函数中调用IBFISCommunicateStation的RegisterRecvMessageCallbackSkin来注册各自需要处理的信令
    virtual int UnInitStation();

    //添加任务，目前只针对手动任务，成功返回任务的id, strEmployeeID为发起人id
    virtual std::string AddTaskItem(IN std::string strBusinessID, IN std::string strEmployeeID, IN ManulTaskStartType enStartType, IN std::string strTaskID = "", IN DWORD_PTR dwReserved = 0);

    //根据id删除任务,只能删除手动任务
    virtual int DeleteTaskItem(IN std::string strTaskID);

    //获取任务总数，包括手动任务和当天的计划任务
    virtual int GetTaskCount();

    //根据任务id获取指定任务信息
    virtual int GetTaskInfo(IN std::string strTaskID, OUT ST_BFISMigrateTask* pInfo);

    //获取当前所有的任务信息
    virtual int GetTaskInfo(IN OUT std::vector<ST_BFISMigrateTask>* pVecInfos);

    //控制手动任务，当有其他任务正在执行时，启动手动任务无效
    virtual int ControlTaskItem(IN TaskControlType enType, IN std::string strTaskID);

    //设置自动任务执行时间  TODO 更新内存中的计划时间，同时写入数据库
    virtual int SetAutomaticPlan(IN std::string strPlanID, IN SYSTEMTIME stTimeBegin, IN SYSTEMTIME stTimeEnd, IN bool bEnable);

    //MonitorSDK 回调
    static ISOC_INT __stdcall static_OperatorCallback(const OperatorState enState, const ISOC_INT nOperatorType, const ISOC_STR strDes, const ISOC_DWORDPTR dwCookie, ISOC_DWORDPTR dwResevered);
    static ISOC_INT __stdcall static_OnRecvServerTimeCallback(IN const ISOC_LONGPTR lMCSession, IN ISOC_DWORDPTR dwUserCookie, IN ISOC_SYSTEMTIME stServerTime);

    virtual ISOC_VOID Run();    //迁移线程

    //TaskStation
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d1, std::vector<std::string>& v1);
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d, std::string& s);

	virtual ISOC_VOID OnTimer(IN ISOC_ID iTimerID);


private:
    int  GetMigrateConfig();
    int LoginMC();
	void AddPlanTask(std::vector<ST_BusinessInfo>& vecBiz, IBFISDataProvider* pDataProvider, ST_BranchInfo& strLocalBranchInfo, int nMaxTaskNum, int& nPos);
	void DelRepeatTask(std::vector<ST_BusinessInfo>& vecBiz);
	bool MigtateTaskHandle(IBFISDBOperation* pDBOper, IBFISDataProvider* pDataProvider, ST_BranchInfo& strLocalBranchInfo, int nMaxTaskNum, int nCondition);
	bool MigtateTaskProcessingHandle(IBFISDataProvider * pDataProvider, IBFISDBOperation* pDBOper, ST_BranchInfo& strLocalBranchInfo, int nMaxTaskNum);
	void LoadStopTaskFromDatabase(IBFISDataProvider * pDataProvider);
	void ManualTaskStateCheck();
	void AutoTaskStateCheck();
private:
    std::string m_strMCIp;
    unsigned short m_sMCPort;
    std::string m_strMCUser;
    std::string m_strMCPwd;

    ISOC_LONGPTR m_lMCSession;
    Poco::Event m_eventWaitLogin;
    bool   m_bIsLogin;
    ST_CenterInfo m_stMigrateCenter;
    IThread*  m_pMigrateThread;
    bool   m_bIsStopMigrate;
	ITimer*  m_pTime;
	CString m_strPluginName;

    XhMigeratePlanMan* m_pMigratePlanMan;
    //std::map<std::string, ST_TaskPlan> m_mapTaskPlan;

    Poco::FastMutex m_lockManueTask;
    std::map<std::string, XhMigrateItemImp*> m_mapManueTask;

    Poco::FastMutex m_lockPlanTask;
    std::map<std::string, XhMigrateItemImp*> m_mapPlanTask;
    std::string m_strParentBranchID;
    std::string m_strParentBranchName;
    std::string m_strParentPID;
    ST_BranchInfo m_stCurrentBranchInfo;

	boost::mutex m_mutex;
	boost::condition_variable m_condition;
	std::shared_ptr<XhMigrateManagement>  m_spMigrateMgr;
	int            m_outTime;
};

