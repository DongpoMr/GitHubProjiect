#pragma once
/******************************************
文件迁移类，实现了对soc sdk文件迁移的封装
*******************************************/
#include "iBFIS_DataType_Define.h"
#include "iBFIS_UniqueDefine.h"
#include "iSOC_FileMigrateV2.0Module.h"
#include "iBFISDBOperation.h"
#include "ITimer.h"
#include <vector>
#include <boost/thread.hpp>

#include "Poco/Mutex.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeParser.h"
#include "Poco/Timespan.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTimeFormatter.h"

#define INTERVAL_TIME 2000

class XhMigrateItemImp :public ITimerCallbackSkin
{
public:
    enum ControlMode
    {
		QUERY = 0,      //查询
        START,          //开始
        PAUSE,          //暂停
        STOP,           //停止
        RESTART,        //暂停后开始
		CANCEL,         //取消
		FAILED,         //失败
		SUCCEED,        //成功
		ABNORMAL,       //异常
		QUERY_EXECUTEING,     //任务执行当中
		START_EXECUTEING,     //任务执行当中
    };
    static XhMigrateItemImp* CreateItem(ISOC_LONGPTR lMCSession, ST_CenterInfo* pCenterInfo);

    virtual ~XhMigrateItemImp();
    
    //bIdle 是否闲时，启动时可用，如果是闲时迁移，则设置迁移速度为10倍
    int ControlMigrate(ControlMode enMode, bool bIdle = false, int queryMode = 0);

    int SetMCSession(ISOC_LONGPTR lMCSession);

    int SetMigrateInfo(ST_BFISMigrateTask* pInfo);
	inline void SetMigrateOutTime(int nOutTime) { m_nOutTime = nOutTime; }
	inline void SetMigrateTaskType(TaskType eTaskType) { m_eTaskType = eTaskType; }

    const ST_BFISMigrateTask* GetMigrateInfo() const;
	inline bool IsOutTime() { return !m_bWaitGetFileState; }
	inline int GetCurrQueryMode() { return m_queryMode; }
	inline ControlMode GetTaskState() { return m_enumTaskState; }
	inline void SetAutoStartTask() { m_bAutoStartTask = true; }

    virtual void OnTimer(int nTimerID);

    int SetStartType(ManulTaskStartType enType);

    ManulTaskStartType GetStartType() const;
	static void SetIntervalTime(int time) { m_intervalTime = time; }
	static void SetQueryWaitMaxCount(int count_) { m_queryCount = count_; }
	
    static ISOC_INT __stdcall static_VodFileInfoCallback(const ST_VodFileInfo vodFileInfo, const ISOC_DWORDPTR dwCookie, const ISOC_STR strQueryGUID);

private:
    XhMigrateItemImp();

    XhMigrateItemImp(ISOC_LONGPTR lMigrateSession);

    int AddMigrateInfo(ST_MigrateItem* pInfo) const;
    void SetMigrateCenterInfo(ST_CenterInfo* pCenterInfo);
    void RecvVodFileCallback(const ST_VodFileInfo vodFileInfo, const ISOC_STR strQueryGUID);
    int ClearMigrateInfo();

	int QueryData(IBFISDBOperation* pDBO);
	int StartTask(IBFISDBOperation* pDBO);
	int StopTask();

    ISOC_LONGPTR m_lMigrateSession;

    ST_MigrateInfo m_stMigrateInfo;
    ST_CenterInfo m_stCenterInfo;
    ITimer* m_pTimer;

    ST_BFISMigrateTask m_stBFISTask;
    ISOC_LONGPTR m_lMCSession;
	DWORD        m_nStartTime;

    Poco::FastMutex m_lockFiles;
    Poco::DateTime m_fileBeginTime;
    Poco::DateTime m_fileEndTime;
    vector<ST_VodFileInfo> m_vecVodInfos;
    int  m_nLastID;
    int  m_nVodQueryCnt;
    bool m_bReadyForStart;
    bool m_bIdleTask;
    bool m_bOnTimer;

	bool   m_bWaitGetFileState;
	int    m_queryMode;
	ControlMode m_enumTaskState;
	bool  m_bAutoStartTask;
	int   m_nOutTime;
	TaskType m_eTaskType;
	DWORD  m_createTime;
	int           m_waitCount;
	static int m_intervalTime;
	static int m_queryCount;
};

