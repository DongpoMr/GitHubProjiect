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

    virtual int InitStation();	//�ڸ��Եĳ�ʼ�������е���IBFISCommunicateStation��RegisterRecvMessageCallbackSkin��ע�������Ҫ���������
    virtual int UnInitStation();

    //�������Ŀǰֻ����ֶ����񣬳ɹ����������id, strEmployeeIDΪ������id
    virtual std::string AddTaskItem(IN std::string strBusinessID, IN std::string strEmployeeID, IN ManulTaskStartType enStartType, IN std::string strTaskID = "", IN DWORD_PTR dwReserved = 0);

    //����idɾ������,ֻ��ɾ���ֶ�����
    virtual int DeleteTaskItem(IN std::string strTaskID);

    //��ȡ���������������ֶ�����͵���ļƻ�����
    virtual int GetTaskCount();

    //��������id��ȡָ��������Ϣ
    virtual int GetTaskInfo(IN std::string strTaskID, OUT ST_BFISMigrateTask* pInfo);

    //��ȡ��ǰ���е�������Ϣ
    virtual int GetTaskInfo(IN OUT std::vector<ST_BFISMigrateTask>* pVecInfos);

    //�����ֶ����񣬵���������������ִ��ʱ�������ֶ�������Ч
    virtual int ControlTaskItem(IN TaskControlType enType, IN std::string strTaskID);

    //�����Զ�����ִ��ʱ��  TODO �����ڴ��еļƻ�ʱ�䣬ͬʱд�����ݿ�
    virtual int SetAutomaticPlan(IN std::string strPlanID, IN SYSTEMTIME stTimeBegin, IN SYSTEMTIME stTimeEnd, IN bool bEnable);

    //MonitorSDK �ص�
    static ISOC_INT __stdcall static_OperatorCallback(const OperatorState enState, const ISOC_INT nOperatorType, const ISOC_STR strDes, const ISOC_DWORDPTR dwCookie, ISOC_DWORDPTR dwResevered);
    static ISOC_INT __stdcall static_OnRecvServerTimeCallback(IN const ISOC_LONGPTR lMCSession, IN ISOC_DWORDPTR dwUserCookie, IN ISOC_SYSTEMTIME stServerTime);

    virtual ISOC_VOID Run();    //Ǩ���߳�

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

