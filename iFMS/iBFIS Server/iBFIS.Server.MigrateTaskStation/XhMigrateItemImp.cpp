#include "stdafx.h"
#include "IcmsP_Utility.h"
#include "XhMigrateItemImp.h"
#include "iSOC_MonFactoryManagement.h"
#include "IBFISDataProvider.h"
#include "iSOC_VodModule.h"
#include <sstream>
#include "XhLogDisplayInterface.h"
#include "iSOC_LoginModule.h"
#include "iSOC_UtilityDefine.h"


class XhAutoSetOnTimer
{
public:
    XhAutoSetOnTimer(bool& bOnTimer) :_bOnTimer(bOnTimer)
    {
        _bOnTimer = true;
    };
    ~XhAutoSetOnTimer()
    {
        _bOnTimer = false;
    }

private:
    bool& _bOnTimer;
};

int XhMigrateItemImp::m_intervalTime = 10;
int XhMigrateItemImp::m_queryCount = 2;

XhMigrateItemImp::XhMigrateItemImp(ISOC_LONGPTR lMigrateSession) :m_lMigrateSession(lMigrateSession)
, m_lMCSession(NULL), m_nLastID(0), m_nVodQueryCnt(0), m_bReadyForStart(false),m_eTaskType(TSK_MANUAL)
, m_bIdleTask(false), m_bOnTimer(false),m_bWaitGetFileState(false),m_nStartTime(0)
, m_queryMode(0),m_enumTaskState(ControlMode::QUERY),m_bAutoStartTask(false),m_nOutTime(120), m_createTime(GetTickCount())
, m_waitCount(0)
{
    iSOC_MonFactoryManagement fmt;
    m_pTimer = static_cast<ITimer*>(fmt.CreateObject(OBJECT_TYPE_TIMER, "", __FUNCTION__));
}


XhMigrateItemImp::~XhMigrateItemImp()
{
    if (m_pTimer)
    {
        m_pTimer->KillTimer(-1);
    }
    while (m_bOnTimer)
    {
        Sleep(20);
    }
    iSOC_ReleaseMigrateV20Session(m_lMigrateSession);

	if (m_enumTaskState == ControlMode::SUCCEED)
	{
		SFTRACE("MigtateTask", " 析构中-业务ID[%s] 任务处理时长[%d] 迁移任务成功 this[%p]\r\n",
			m_stBFISTask.strBusinessID.c_str(), GetTickCount() - m_createTime, this);
	}
	else
	{
		SFTRACE("MigtateTask", " 析构中-业务ID[%s] 任务处理时长[%d] 迁移任务失败 状态[%d] 迁移状态[%d] 查询模式[%d] 查询超时状态[%d] OutTime[%d] this[%p]\r\n",
			m_stBFISTask.strBusinessID.c_str(), GetTickCount() - m_createTime, m_enumTaskState, m_stMigrateInfo.nState, m_queryMode, m_bWaitGetFileState, m_nOutTime, this);
	}

}

XhMigrateItemImp* XhMigrateItemImp::CreateItem(ISOC_LONGPTR lMCSession, ST_CenterInfo* pCenterInfo)
{
    if (lMCSession == NULL || pCenterInfo == nullptr)
        return nullptr;

    ISOC_LONGPTR lMigrateSession = NULL;
    int nRet = iSOC_CreateMigrateV20Session(lMCSession, &lMigrateSession);
    if (nRet <= 0 || lMigrateSession == NULL)
    {
        TTRACE("%s[%d]: 创建迁移会话失败，返回值%d, Session:%p\r\n", __FUNCTION__, __LINE__, lMigrateSession);
        return nullptr;
    }

    XhMigrateItemImp* pObj = new XhMigrateItemImp(lMigrateSession);
    pObj->SetMCSession(lMCSession);
    pObj->SetMigrateCenterInfo(pCenterInfo);
    return pObj;
}

void XhMigrateItemImp::SetMigrateCenterInfo(ST_CenterInfo* pCenterInfo)
{
    iSOC_SetMigrateV20CenterInfo(m_lMigrateSession, pCenterInfo);
    m_stCenterInfo = *pCenterInfo;
}

int XhMigrateItemImp::AddMigrateInfo(ST_MigrateItem* pInfo) const
{
    return iSOC_AddMigrateV20TaskItem(m_lMigrateSession, pInfo);
}

int XhMigrateItemImp::ControlMigrate(ControlMode enMode, bool bIdle /*= false*/,  int queryMode /*= 0*/)
{
	iSOC_MonFactoryManagement fmt;
	IBFISDBOperation* pDBO = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
	if (nullptr == pDBO)
	{
		DISPLAY_LOG("备份模块", "启动任务失败", "获取数据对象失败", "", 0);
		return -1;
	}
	
    switch (enMode)
    {
    case XhMigrateItemImp::QUERY:
    {
		m_queryMode = queryMode;
		if (m_enumTaskState != ControlMode::QUERY && m_enumTaskState != ControlMode::FAILED)
		{
			SFTRACE("MigtateTask", "%s[%d]:查询状态不正确 业务ID[%s] TaskState[%d] this[%p]\r\n", __FUNCTION__, __LINE__
				, m_stBFISTask.strBusinessID.c_str(), m_enumTaskState, this);
			return 1;
		}
		int nRet = QueryData(pDBO);
		if (nRet <= 0)
			m_bAutoStartTask = false;
		return nRet;
    }
	case XhMigrateItemImp::START:
	{
		return StartTask(pDBO);
	}
    case XhMigrateItemImp::PAUSE:
    {
        if (m_enumTaskState != ControlMode::START_EXECUTEING)  //直接返回成功
        {
            DISPLAY_LOG("备份模块", "任务还没执行", "", "", 1);
            return 1;
        }
        int nRet = iSOC_ControlMigrateV20Task(m_lMigrateSession, 3);
        if (nRet <= 0)
        {
            TTRACE("%s[%d]:暂停任务失败，SDK 返回值%d\r\n", __FUNCTION__, __LINE__, nRet);
            DISPLAY_LOG("备份模块", "暂停任务失败", "", "", 0);
			return nRet;
        }
		m_stBFISTask.nStatus = TSK_PAUSE;
		m_enumTaskState = ControlMode::PAUSE;
		pDBO->SetMigratedBusinessInfo(m_stBFISTask.strBusinessID, TSK_PAUSE);
        return nRet;
    }
    case XhMigrateItemImp::STOP:
    {
		if (m_enumTaskState == ControlMode::START_EXECUTEING)
		{
			if (StopTask() <= 0)
				return -1;

			m_enumTaskState = ControlMode::FAILED;
			m_stBFISTask.nStatus = TSK_STOP;
			m_stBFISTask.nProcess = 0;
			pDBO->SetMigratedBusinessInfo(m_stBFISTask.strBusinessID, TSK_STOP);
		}
        return 1;
    }
	case XhMigrateItemImp::ABNORMAL:
	{
		if (m_enumTaskState == ControlMode::ABNORMAL)
		{
			int nRet = StopTask();
			m_enumTaskState = ControlMode::FAILED;
			m_stBFISTask.nStatus = TSK_FAILED;
			m_stBFISTask.nProcess = 0;
			m_nStartTime = 0;
			pDBO->SetMigratedBusinessInfo(m_stBFISTask.strBusinessID, TSK_FAILED);
		}
		return 1;
		
	}
	case XhMigrateItemImp::CANCEL:
	{
		if (m_enumTaskState == ControlMode::START_EXECUTEING)
		{
			if (StopTask() <= 0)
				return -1;
		}
		m_enumTaskState = ControlMode::FAILED;
		m_stBFISTask.nStatus = TSK_FAILED;
		m_stBFISTask.nProcess = 0;
		pDBO->SetMigratedBusinessInfo(m_stBFISTask.strBusinessID, 0);
		return 1;
	}
    case XhMigrateItemImp::RESTART:
    {
		if (m_enumTaskState == ControlMode::START_EXECUTEING)
		{
			if (StopTask() <= 0)
				return -1;
		}

		iSOC_SetMigrateV20Speed(m_lMigrateSession, 1);
        int nRet = iSOC_ControlMigrateV20Task(m_lMigrateSession, 1);
        if (nRet <= 0)
        {
            TTRACE("%s[%d]:重新启动任务失败，SDK 返回值%d\r\n", __FUNCTION__, __LINE__, nRet);
            DISPLAY_LOG("备份模块", "重新启动任务失败", "", "", 0);
        }
        else
        {
			DISPLAY_LOG("备份模块", "重新启动任务成功", "", "", 1);
			m_stBFISTask.nStatus = TSK_PROCESSING;
			m_stBFISTask.nProcess = 0;
			m_enumTaskState = ControlMode::START_EXECUTEING;
			pDBO->SetMigratedBusinessInfo(m_stBFISTask.strBusinessID, TSK_PROCESSING);
        }
        return nRet;
	}
    default:
        break;
    }
    return 1;
}

void XhMigrateItemImp::OnTimer(int nTimerID)
{
    XhAutoSetOnTimer b(m_bOnTimer);
//    if (!m_vecVodInfos.empty())    //说明vod文件没有查询完成
    {
        if (m_nVodQueryCnt++ < m_queryCount && false == m_bWaitGetFileState)  //暂定超时时间20s
        {
            return;
        }
        else
        {
            if (m_vecVodInfos.empty())
            {
				//查询vod信息超时
				if (false == m_bWaitGetFileState)
				{
					SFTRACE("MigtateTask", "%s[%d]:业务ID[%s] 查询模式[%d] 等待VOD回调超过最大等待时间[10]秒 this[%p]\r\n", __FUNCTION__, __LINE__,
						m_stBFISTask.strBusinessID.c_str(), m_queryMode, this);
				}
				else
				{
					SFTRACE("MigtateTask", "%s[%d]:业务ID[%s] 查询模式[%d] 查询VOD数据大小为0 this[%p]\r\n", __FUNCTION__,
						__LINE__, m_stBFISTask.strBusinessID.c_str(), m_queryMode, this);
				}

                m_stBFISTask.nStatus = TSK_FAILED;
				m_enumTaskState = ControlMode::FAILED;
                m_stBFISTask.nProcess = 0;
                m_pTimer->KillTimer(-1);
                m_nVodQueryCnt = 0;
                iSOC_MonFactoryManagement fmt;
                IBFISDBOperation* pDBO = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
                if (pDBO)
                {
					if ((4 != m_queryMode && m_queryMode != 8) || (true == m_bWaitGetFileState && m_queryMode == 8))
						pDBO->SetMigratedBusinessInfo(m_stBFISTask.strBusinessID, TSK_FAILED);
                }
				return;
            }
			else
			{
				if (4 == m_queryMode || 8 == m_queryMode)   //如果查询的迁移任务有，代表是已经迁移的，只是当前数据库由于其它原因没有改对应迁移任务,例如程序异常，但任务还在执行
				{
					m_stBFISTask.nStatus = TSK_FINISHED;
					m_enumTaskState = ControlMode::SUCCEED;
					m_nVodQueryCnt = 0;
					m_pTimer->KillTimer(-1);
					iSOC_MonFactoryManagement fmt;
					IBFISDBOperation* pDBO = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
					pDBO->SetMigratedBusinessInfo(m_stBFISTask.strBusinessID, TSK_FINISHED);
					return;
				}

				if (m_enumTaskState == ControlMode::QUERY_EXECUTEING)
					m_enumTaskState = ControlMode::START;	
			}
        }
    }

	if (m_bAutoStartTask)
	{
		iSOC_MonFactoryManagement fmt;
		IBFISDBOperation* pDBO = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
		m_bAutoStartTask = false;
		int nRet = StartTask(pDBO);
		if (nRet <= 0)
		{
			SFTRACE("MigtateTask", " 手动迁移开始 业务ID[%s] 状态[%d] this[%p]\r\n", m_stBFISTask.strBusinessID.c_str(), nRet, this);
		}
		return;

	}
	if (m_enumTaskState != ControlMode::START_EXECUTEING)
		return;

    int migRate = iSOC_GetMigrateV20Info(m_lMigrateSession, &m_stMigrateInfo);
	if (migRate < 0)
	{
		SFTRACE("MigtateTask", " %s[%d] 获取迁移状态失败 业务ID[%s] 错误码[%d] this[%p]\r\n", __FUNCTION__, __LINE__,
			m_stBFISTask.strBusinessID.c_str(), migRate, this);
	}
    
	if (m_eTaskType == TSK_AUTO)
	{
		static int nWaitCount = m_nOutTime / m_intervalTime;
		if (m_stMigrateInfo.nState == 2)
		{
			m_waitCount = 0;
			if (m_stBFISTask.nProcess >= m_stMigrateInfo.nProgress)
			{
				if (++m_nStartTime >= nWaitCount)
				{
					SFTRACE("MigtateTask", " 迁移超时 业务ID[%s] 超过nWaitCount[%d]进度没变化[%d] state[%d] this[%p] \r\n",
						m_stBFISTask.strBusinessID.c_str(), nWaitCount, m_stBFISTask.nProcess, m_stMigrateInfo.nState, this);
					m_enumTaskState = ControlMode::ABNORMAL;
					m_pTimer->KillTimer(-1);
					m_nStartTime = 0;
					return;
				}
			}
			else
			{
				m_nStartTime = 0;
			}
		}
		else
		{
			if (++m_waitCount >= 2 * nWaitCount)
			{
				SFTRACE("MigtateTask", " 迁移超时 业务ID[%s] 超过nWaitCount[%d]等待时常 state[%d] this[%p] \r\n",
					m_stBFISTask.strBusinessID.c_str(), 2 * nWaitCount, m_stMigrateInfo.nState, this);
				m_enumTaskState = ControlMode::ABNORMAL;
				m_pTimer->KillTimer(-1);
				m_waitCount = 0;
				return;
			}
		}
	}
	else
	{
		if (m_stMigrateInfo.nState == 0 || m_stMigrateInfo.nState == 7 || m_stMigrateInfo.nState == 8)
		{
			SFTRACE("MigtateTask", " %s[%d] 停止迁移任务 业务ID[%s] 状态[%d] this[%p]\r\n", __FUNCTION__, __LINE__,
				m_stBFISTask.strBusinessID.c_str(), m_stMigrateInfo.nState, this);
		}
	}

	m_stBFISTask.nProcess = m_stMigrateInfo.nProgress;

	//迁移状态，1为排队，2为正在调度，3为完成，4为暂停，5为取消,6为停止，7为异常，8为异常重试
    switch (m_stMigrateInfo.nState)
    {
	case 0:
		{
			m_stBFISTask.nStatus = TSK_STOP;
			m_enumTaskState = ControlMode::FAILED;
			m_pTimer->KillTimer(-1);
		}
		break;
    case 1:
		{
			if ((m_waitCount % 60) == 0)
			{
				SFTRACE("MigtateTask", " 排队任务超时 任务类型[%d] 业务ID[%s] this[%p]\r\n", m_eTaskType, m_stBFISTask.strBusinessID.c_str(), this);
				break;
			}
		}
    case 2:
        {
            m_stBFISTask.nStatus = TSK_PROCESSING;
        }        
        break;
    case 3:
        {
			iSOC_MonFactoryManagement fmt;
			IBFISDBOperation* pDBO = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
            if (pDBO)
            {
				Poco::LocalDateTime timeNow;
				m_stBFISTask.strEndTime = Poco::DateTimeFormatter::format(timeNow.timestamp(), "%Y-%m-%e %H:%M:%S");
                //设置文件迁移状态
                pDBO->SetMigratedBusinessInfo(m_stBFISTask.strBusinessID, TSK_FINISHED);
                //设置文件保存网点
                ST_BusinessInfo stBizInfo;
                stBizInfo.strBusinessInfoId = m_stBFISTask.strBusinessID;
                pDBO->QueryBusinessInfoByID(stBizInfo);
                if (!stBizInfo.strBranchId.empty())
                {
                    ST_UserInfo user;
                    iSOC_GetUserInfo(m_lMCSession, &user);
                    std::stringstream os;
                    os << user.strServerICMSSign << ":" << 4;   //迁移
                    stBizInfo.strFileCenter = os.str();
                    pDBO->ManageBusinessInfo(DBO_UPDATE, stBizInfo);
                }               
                //写入迁移日志
                ST_MigrateLogInfo log;
                log.strMigrateTaskID = m_stBFISTask.strTaskID;
                log.strBusinessID = m_stBFISTask.strBusinessID;
                log.strProduceID = m_stBFISTask.strProduceID;
                log.strEmployeeID = m_stBFISTask.strEmployeeID;
                log.nType = m_stBFISTask.nType;
                log.nStatus = m_stBFISTask.nStatus;
                log.strAutoTime = m_stBFISTask.strAutoTime;
                log.strBeginTime = m_stBFISTask.strBeginTime;
                log.strEndTime = m_stBFISTask.strEndTime;
                log.strLaunchEmployeeID = m_stBFISTask.strLaunchEmployeeID;
                log.nOrderID = m_stBFISTask.nOrderID;
                pDBO->ManageMigrateLogInfo(DBO_ADD, log);
            }
            m_stBFISTask.nStatus = TSK_FINISHED;
			m_enumTaskState = ControlMode::SUCCEED;
            Poco::LocalDateTime timeNow;
			m_stBFISTask.strEndTime = Poco::DateTimeFormatter::format(timeNow.timestamp(), "%Y-%m-%e %H:%M:%S");
			m_nVodQueryCnt = 0;
			m_pTimer->KillTimer(-1);
		return;
        }
        break;
    case 4:
        {
            m_stBFISTask.nStatus = TSK_PAUSE;
        }
        break;
    case 5:
    case 6:
		{
			m_stBFISTask.nStatus = TSK_STOP;
		}
        break;
    case 7:
    case 8:
        {
			m_enumTaskState = ControlMode::ABNORMAL;
			m_pTimer->KillTimer(-1);
        }
        break;
    default:
        break;
    }

}

int XhMigrateItemImp::SetMigrateInfo(ST_BFISMigrateTask* pInfo)
{
    if (pInfo)
    {
        m_stBFISTask = *pInfo;
    }
    return 1;
}

const ST_BFISMigrateTask* XhMigrateItemImp::GetMigrateInfo() const
{
    return &m_stBFISTask;
}

int XhMigrateItemImp::SetMCSession(ISOC_LONGPTR lMCSession)
{
    m_lMCSession = lMCSession;
    return 1;
}

ISOC_INT __stdcall XhMigrateItemImp::static_VodFileInfoCallback(const ST_VodFileInfo vodFileInfo, const ISOC_DWORDPTR dwCookie, const ISOC_STR strQueryGUID)
{
    XhMigrateItemImp* pThis = reinterpret_cast<XhMigrateItemImp*>(dwCookie);
    if (!pThis)
    {
        TTRACE("%s[%d]:查询VOD信息失败，cookie为空\r\n", __FUNCTION__, __LINE__);
        return -1;
    }

    pThis->RecvVodFileCallback(vodFileInfo, strQueryGUID);
    return 1;
}

void XhMigrateItemImp::RecvVodFileCallback(const ST_VodFileInfo vodFileInfo, const ISOC_STR strQueryGUID)
{
	if (vodFileInfo.lDeviceID == 0) //结束标记直接返回
	{
		m_bWaitGetFileState = true;
		return;
	}
    Poco::FastMutex::ScopedLock lock(m_lockFiles);
#if 0
    if (m_vecFiles.empty())
    {
        TTRACE("%s[%d]: 关联文件信息为空，是否有多余的录像?\r\n", __FUNCTION__, __LINE__);
        return;
    }

    for (auto iter = m_vecFiles.begin(); iter != m_vecFiles.end(); iter++)
    {
        int nTzd = 0;
        Poco::DateTime vodBegin(vodFileInfo.stStartTime.wYear, vodFileInfo.stStartTime.wMonth, vodFileInfo.stStartTime.wDay
                              , vodFileInfo.stStartTime.wHour, vodFileInfo.stStartTime.wMinute, vodFileInfo.stStartTime.wSecond);
        Poco::DateTime vodEnd(vodFileInfo.stEndTime.wYear, vodFileInfo.stEndTime.wMonth, vodFileInfo.stEndTime.wDay
                              , vodFileInfo.stEndTime.wHour, vodFileInfo.stEndTime.wMinute, vodFileInfo.stEndTime.wSecond);

        Poco::DateTime timeBegin = Poco::DateTimeParser::parse(iter->strRecordBegin, nTzd);
        Poco::DateTime timeEnd = Poco::DateTimeParser::parse(iter->strRecordEnd, nTzd); 
        TTRACE("%s[%d]:vodBegin:%s, vodEnd:%s, timeBegin:%s, timeEnd:%s, file size:%d\r\n", __FUNCTION__, __LINE__
            , Poco::DateTimeFormatter::format(vodBegin.timestamp(), "%Y-%m-%e %H:%M:%S").c_str()
            , Poco::DateTimeFormatter::format(vodEnd.timestamp(), "%Y-%m-%e %H:%M:%S").c_str()
            , Poco::DateTimeFormatter::format(timeBegin.timestamp(), "%Y-%m-%e %H:%M:%S").c_str()
            , Poco::DateTimeFormatter::format(timeEnd.timestamp(), "%Y-%m-%e %H:%M:%S").c_str(), m_vecFiles.size());
        if ((vodBegin - timeBegin).totalSeconds() <= 3 && ((vodEnd >= timeEnd) || (timeEnd - vodEnd).totalSeconds() <= 3))
        {
            ST_MigrateItem item;
            item.stVodFileInfo = vodFileInfo;
            CopyMemory(&item.stBeginTime, &vodFileInfo.stStartTime, sizeof(item.stBeginTime));
            CopyMemory(&item.stEndTime, &vodFileInfo.stEndTime, sizeof(item.stEndTime));
            item.nMigrateTaskID = ++m_nLastID;
            AddMigrateInfo(&item);
            m_vecFiles.erase(iter);
            break;
        }
    }

    if (m_vecFiles.empty())
    {
        m_bReadyForStart = true;
    }
#endif
    Poco::DateTime timeBegin(vodFileInfo.stStartTime.wYear, vodFileInfo.stStartTime.wMonth, vodFileInfo.stStartTime.wDay
        , vodFileInfo.stStartTime.wHour, vodFileInfo.stStartTime.wMinute, vodFileInfo.stStartTime.wSecond);
    Poco::DateTime timeEnd(vodFileInfo.stEndTime.wYear, vodFileInfo.stEndTime.wMonth, vodFileInfo.stEndTime.wDay
        , vodFileInfo.stEndTime.wHour, vodFileInfo.stEndTime.wMinute, vodFileInfo.stEndTime.wSecond);

    if (timeBegin > m_fileEndTime || timeEnd < m_fileBeginTime)
    {
		SFTRACE("MigtateTask", "%s[%d]:文件时间不在业务录像范围内,vodB egin:%s, vodEnd:%s this[%p]\r\n", __FUNCTION__, __LINE__
            , Poco::DateTimeFormatter::format(timeBegin.timestamp(), "%Y-%m-%e %H:%M:%S").c_str()
            , Poco::DateTimeFormatter::format(timeEnd.timestamp(), "%Y-%m-%e %H:%M:%S").c_str(), this);
        return;
    }
	SFTRACE("MigtateTask", "%s[%d]:业务ID[%s] 文件信息 Path[%s] lDeviceID[%d] lIcmsId[%d] this[%p]\r\n", __FUNCTION__, __LINE__
		, m_stBFISTask.strBusinessID.c_str(), vodFileInfo.strFilePath, vodFileInfo.lDeviceID, vodFileInfo.lIcmsId, this);
    m_vecVodInfos.push_back(vodFileInfo);
    m_bReadyForStart = true;
}

int XhMigrateItemImp::SetStartType(ManulTaskStartType enType)
{
    m_stBFISTask.nType = enType;
    return 1;
}

ManulTaskStartType XhMigrateItemImp::GetStartType() const
{
    return static_cast<ManulTaskStartType>(m_stBFISTask.nType);
}

int XhMigrateItemImp::ClearMigrateInfo()
{
    for (int i = 0; i < m_nLastID; i++)
    {
        iSOC_DelMigrateV20TaskItem(m_lMigrateSession, i);
    }
    m_nLastID = 0;
    m_vecVodInfos.clear();
    if (m_lMigrateSession)
    {
        iSOC_ReleaseMigrateV20Session(m_lMigrateSession);
        iSOC_CreateMigrateV20Session(m_lMCSession, &m_lMigrateSession);
        iSOC_SetMigrateV20CenterInfo(m_lMigrateSession, &m_stCenterInfo);
    }
    return 1;
}

int XhMigrateItemImp::QueryData(IBFISDBOperation * pDBO)
{
	if (nullptr == pDBO)
		return -1;
	Poco::LocalDateTime timeNow;
	m_stBFISTask.strBeginTime = Poco::DateTimeFormatter::format(timeNow.timestamp(), "%Y-%m-%e %H:%M:%S");
	if (m_stBFISTask.nType == TSK_AUTO)
	{
		m_stBFISTask.strAutoTime = m_stBFISTask.strBeginTime;
	}
	iSOC_MonFactoryManagement fmt;
	IBFISDataProvider* pDataProvider = static_cast<IBFISDataProvider*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_CACHESOURCE, "", __FUNCTION__));
	if (!pDataProvider)
	{
		DISPLAY_LOG("备份模块", "启动任务失败", "获取数据对象失败", "", 0);
		return -1;
	}

	std::vector<ST_BusinessFileInfo> vecFiles;
	int nRet = pDataProvider->QueryBusinessFileInfoByBusinessInfoId(m_stBFISTask.strBusinessID, vecFiles); //查询业务相关信息，获取该业务的文件信息

	if (nRet <= 0 || vecFiles.empty())
	{
		SFTRACE("MigtateTask", " %s[%d] 获取业务文件失败, 业务ID[%s] 返回值[%d] 数据大小[%d] this[%p] \r\n", __FUNCTION__,
			__LINE__, m_stBFISTask.strBusinessID.c_str(), nRet, vecFiles.size(), this);
		return -1;
	}

	ST_BusinessInfo stBusiness;
	nRet = pDataProvider->QueryBusinessInfoById(m_stBFISTask.strBusinessID, stBusiness);

	//获取录像文件的开始和结束时间
	Poco::DateTime vodBegin(2999, 1, 1), vodEnd(1800, 1, 1);
	for each (const auto& var in vecFiles)
	{
		Poco::DateTime timeBegin, timeEnd;
		int nTzd = 0;
		timeBegin = Poco::DateTimeParser::parse(var.strRecordBegin, nTzd);
		timeEnd = Poco::DateTimeParser::parse(var.strRecordEnd, nTzd);

		vodBegin > timeBegin ? vodBegin = timeBegin : 1;
		vodEnd < timeEnd ? vodEnd = timeEnd : 1;
	}
	m_fileBeginTime = vodBegin;
	m_fileEndTime = vodEnd;
	m_stBFISTask.nProcess = 0;
	ClearMigrateInfo();
	//查询对应的vod文件信息
	ST_BranchInfo localBranch;
	nRet = pDBO->GetLocalBranchInfo(localBranch);

	ST_VodQueryFilter filter;
	if (stBusiness.strFileCenter.empty())
	{
		filter.nFileArea = 1;
	}
	else
	{
		char szGuid[50] = { 0 };
		sscanf(stBusiness.strFileCenter.c_str(), "%s:%d", szGuid, filter.nFileArea);
	}
	//localBranch.strBranchId == stBusiness.strBranchId ? filter.nFileArea = 1 : filter.nFileArea = 4;   //本级自己的业务就查设备自身所在中心内，否则查迁移
	filter.nVodFileType = 7;  //手动文件
	if (m_queryMode == 4)
		filter.migrateCenterInfo = m_stCenterInfo;
	filter.nFileArea = m_queryMode;

	strcpy(filter.strStartTime, Poco::DateTimeFormatter::format(vodBegin.timestamp(), "%Y-%m-%e %H:%M:%S").c_str());
	strcpy(filter.strEndTime, Poco::DateTimeFormatter::format(vodEnd.timestamp(), "%Y-%m-%e %H:%M:%S").c_str());
	ST_DeviceItem device;
	nRet = iSOC_GetDeviceInfoByIcmsSignAndIcmsDeviceId(m_lMCSession, &device, const_cast<TCHAR*>(stBusiness.strSubEquipmentIcmSign.c_str()), atoi(stBusiness.strSubEquipmentId.c_str()));
	if (nRet <= 0)
	{
		SFTRACE("MigtateTask", " %s[%d] 获取设备信息失败, 业务ID[%s] 设备的ICMS标识[%s] 设备所在分控的ID[%s] 返回值[%d] this[%p] \r\n",__FUNCTION__,
			__LINE__, m_stBFISTask.strBusinessID.c_str(), stBusiness.strSubEquipmentIcmSign.c_str(), stBusiness.strSubEquipmentId.c_str(), nRet, this);
		return nRet;
	}

	m_bWaitGetFileState = false;
	std::stringstream os;
	os << device.lDeviceID;
	nRet = iSOC_GetVodFileList(m_lMCSession, os.str().c_str(), filter, static_VodFileInfoCallback
		, reinterpret_cast<DWORD_PTR>(this), const_cast<TCHAR*>(m_stBFISTask.strTaskID.c_str()));

	if (m_pTimer && nRet > 0)
	{
		m_enumTaskState = ControlMode::QUERY_EXECUTEING;
		m_stBFISTask.nStatus = TSK_PROCESSING;
		m_pTimer->SetTimer(this, 1, m_intervalTime * 1000);
	}
	SFTRACE("MigtateTask", " %s[%d] 获取迁移业务文件, 业务ID[%s] 设备ID列表[%s] 返回值[%d] 时间[%s][%s] this[%p]\r\n",
		__FUNCTION__, __LINE__, m_stBFISTask.strBusinessID.c_str(), os.str().c_str(), nRet, filter.strStartTime, filter.strEndTime, this);

	return nRet;
}

int XhMigrateItemImp::StartTask(IBFISDBOperation * pDBO)
{
	if (nullptr == pDBO)
		return -1;
	if (m_bReadyForStart)
	{
		m_bReadyForStart = false;
		for each (const auto& var in m_vecVodInfos)
		{
			ST_MigrateItem item;
			item.stVodFileInfo = var;
			CopyMemory(&item.stBeginTime, &var.stStartTime, sizeof(item.stBeginTime));
			CopyMemory(&item.stEndTime, &var.stEndTime, sizeof(item.stEndTime));
			item.nMigrateTaskID = ++m_nLastID;
			AddMigrateInfo(&item);
		}
		STRY;
		iSOC_SetMigrateV20Speed(m_lMigrateSession, 1);
		int nRet = iSOC_StartMigrateV20Task(m_lMigrateSession);
		SFTRACE("MigtateTask", " %s[%d] 开始[%s]迁移任务 状态[%d] 业务ID[%s], 发起人[%s]  this[%p]\r\n", __FUNCTION__, __LINE__,
			m_stBFISTask.nType == TSK_AUTO ? "自动" : "手动", nRet, m_stBFISTask.strBusinessID.c_str(), m_stBFISTask.strLaunchEmployeeID.c_str(), this);
		if (nRet <= 0)
		{
			m_nVodQueryCnt = 0;
			m_pTimer->KillTimer(-1);
			m_enumTaskState = ControlMode::FAILED;
			m_stBFISTask.nStatus = TSK_FAILED;
			pDBO->SetMigratedBusinessInfo(m_stBFISTask.strBusinessID, TSK_FAILED);
			return -1;
		}
		pDBO->SetMigratedBusinessInfo(m_stBFISTask.strBusinessID, TSK_PROCESSING);
		m_stBFISTask.nStatus = TSK_PROCESSING;
		m_enumTaskState = ControlMode::START_EXECUTEING;
		m_nStartTime = 0;
		return 1;
		SCATCH;
	}

	return -1;
}

int XhMigrateItemImp::StopTask()
{
	int nRet = iSOC_ControlMigrateV20Task(m_lMigrateSession, 4);
	SFTRACE("MigtateTask", " %s[%d] 停止迁移 业务ID[%s] 迁移业务状态[%d] 迁移状态[%d] 返回值[%d] this[%p]\r\n", __FUNCTION__,
		__LINE__, m_stBFISTask.strBusinessID.c_str(), m_enumTaskState, m_stMigrateInfo.nState, nRet, this);
	if (nRet <= 0)
	{
		return -1;
	}
	else
	{
		m_nVodQueryCnt = 0;
		m_pTimer->KillTimer(-1);
		DISPLAY_LOG("备份模块", "停止任务成功", "", "", 1);
		return 1;
	}
}
