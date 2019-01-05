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
		SFTRACE("MigtateTask", " ������-ҵ��ID[%s] ������ʱ��[%d] Ǩ������ɹ� this[%p]\r\n",
			m_stBFISTask.strBusinessID.c_str(), GetTickCount() - m_createTime, this);
	}
	else
	{
		SFTRACE("MigtateTask", " ������-ҵ��ID[%s] ������ʱ��[%d] Ǩ������ʧ�� ״̬[%d] Ǩ��״̬[%d] ��ѯģʽ[%d] ��ѯ��ʱ״̬[%d] OutTime[%d] this[%p]\r\n",
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
        TTRACE("%s[%d]: ����Ǩ�ƻỰʧ�ܣ�����ֵ%d, Session:%p\r\n", __FUNCTION__, __LINE__, lMigrateSession);
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
		DISPLAY_LOG("����ģ��", "��������ʧ��", "��ȡ���ݶ���ʧ��", "", 0);
		return -1;
	}
	
    switch (enMode)
    {
    case XhMigrateItemImp::QUERY:
    {
		m_queryMode = queryMode;
		if (m_enumTaskState != ControlMode::QUERY && m_enumTaskState != ControlMode::FAILED)
		{
			SFTRACE("MigtateTask", "%s[%d]:��ѯ״̬����ȷ ҵ��ID[%s] TaskState[%d] this[%p]\r\n", __FUNCTION__, __LINE__
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
        if (m_enumTaskState != ControlMode::START_EXECUTEING)  //ֱ�ӷ��سɹ�
        {
            DISPLAY_LOG("����ģ��", "����ûִ��", "", "", 1);
            return 1;
        }
        int nRet = iSOC_ControlMigrateV20Task(m_lMigrateSession, 3);
        if (nRet <= 0)
        {
            TTRACE("%s[%d]:��ͣ����ʧ�ܣ�SDK ����ֵ%d\r\n", __FUNCTION__, __LINE__, nRet);
            DISPLAY_LOG("����ģ��", "��ͣ����ʧ��", "", "", 0);
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
            TTRACE("%s[%d]:������������ʧ�ܣ�SDK ����ֵ%d\r\n", __FUNCTION__, __LINE__, nRet);
            DISPLAY_LOG("����ģ��", "������������ʧ��", "", "", 0);
        }
        else
        {
			DISPLAY_LOG("����ģ��", "������������ɹ�", "", "", 1);
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
//    if (!m_vecVodInfos.empty())    //˵��vod�ļ�û�в�ѯ���
    {
        if (m_nVodQueryCnt++ < m_queryCount && false == m_bWaitGetFileState)  //�ݶ���ʱʱ��20s
        {
            return;
        }
        else
        {
            if (m_vecVodInfos.empty())
            {
				//��ѯvod��Ϣ��ʱ
				if (false == m_bWaitGetFileState)
				{
					SFTRACE("MigtateTask", "%s[%d]:ҵ��ID[%s] ��ѯģʽ[%d] �ȴ�VOD�ص��������ȴ�ʱ��[10]�� this[%p]\r\n", __FUNCTION__, __LINE__,
						m_stBFISTask.strBusinessID.c_str(), m_queryMode, this);
				}
				else
				{
					SFTRACE("MigtateTask", "%s[%d]:ҵ��ID[%s] ��ѯģʽ[%d] ��ѯVOD���ݴ�СΪ0 this[%p]\r\n", __FUNCTION__,
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
				if (4 == m_queryMode || 8 == m_queryMode)   //�����ѯ��Ǩ�������У��������Ѿ�Ǩ�Ƶģ�ֻ�ǵ�ǰ���ݿ���������ԭ��û�иĶ�ӦǨ������,��������쳣����������ִ��
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
			SFTRACE("MigtateTask", " �ֶ�Ǩ�ƿ�ʼ ҵ��ID[%s] ״̬[%d] this[%p]\r\n", m_stBFISTask.strBusinessID.c_str(), nRet, this);
		}
		return;

	}
	if (m_enumTaskState != ControlMode::START_EXECUTEING)
		return;

    int migRate = iSOC_GetMigrateV20Info(m_lMigrateSession, &m_stMigrateInfo);
	if (migRate < 0)
	{
		SFTRACE("MigtateTask", " %s[%d] ��ȡǨ��״̬ʧ�� ҵ��ID[%s] ������[%d] this[%p]\r\n", __FUNCTION__, __LINE__,
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
					SFTRACE("MigtateTask", " Ǩ�Ƴ�ʱ ҵ��ID[%s] ����nWaitCount[%d]����û�仯[%d] state[%d] this[%p] \r\n",
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
				SFTRACE("MigtateTask", " Ǩ�Ƴ�ʱ ҵ��ID[%s] ����nWaitCount[%d]�ȴ�ʱ�� state[%d] this[%p] \r\n",
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
			SFTRACE("MigtateTask", " %s[%d] ֹͣǨ������ ҵ��ID[%s] ״̬[%d] this[%p]\r\n", __FUNCTION__, __LINE__,
				m_stBFISTask.strBusinessID.c_str(), m_stMigrateInfo.nState, this);
		}
	}

	m_stBFISTask.nProcess = m_stMigrateInfo.nProgress;

	//Ǩ��״̬��1Ϊ�Ŷӣ�2Ϊ���ڵ��ȣ�3Ϊ��ɣ�4Ϊ��ͣ��5Ϊȡ��,6Ϊֹͣ��7Ϊ�쳣��8Ϊ�쳣����
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
				SFTRACE("MigtateTask", " �Ŷ�����ʱ ��������[%d] ҵ��ID[%s] this[%p]\r\n", m_eTaskType, m_stBFISTask.strBusinessID.c_str(), this);
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
                //�����ļ�Ǩ��״̬
                pDBO->SetMigratedBusinessInfo(m_stBFISTask.strBusinessID, TSK_FINISHED);
                //�����ļ���������
                ST_BusinessInfo stBizInfo;
                stBizInfo.strBusinessInfoId = m_stBFISTask.strBusinessID;
                pDBO->QueryBusinessInfoByID(stBizInfo);
                if (!stBizInfo.strBranchId.empty())
                {
                    ST_UserInfo user;
                    iSOC_GetUserInfo(m_lMCSession, &user);
                    std::stringstream os;
                    os << user.strServerICMSSign << ":" << 4;   //Ǩ��
                    stBizInfo.strFileCenter = os.str();
                    pDBO->ManageBusinessInfo(DBO_UPDATE, stBizInfo);
                }               
                //д��Ǩ����־
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
        TTRACE("%s[%d]:��ѯVOD��Ϣʧ�ܣ�cookieΪ��\r\n", __FUNCTION__, __LINE__);
        return -1;
    }

    pThis->RecvVodFileCallback(vodFileInfo, strQueryGUID);
    return 1;
}

void XhMigrateItemImp::RecvVodFileCallback(const ST_VodFileInfo vodFileInfo, const ISOC_STR strQueryGUID)
{
	if (vodFileInfo.lDeviceID == 0) //�������ֱ�ӷ���
	{
		m_bWaitGetFileState = true;
		return;
	}
    Poco::FastMutex::ScopedLock lock(m_lockFiles);
#if 0
    if (m_vecFiles.empty())
    {
        TTRACE("%s[%d]: �����ļ���ϢΪ�գ��Ƿ��ж����¼��?\r\n", __FUNCTION__, __LINE__);
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
		SFTRACE("MigtateTask", "%s[%d]:�ļ�ʱ�䲻��ҵ��¼��Χ��,vodB egin:%s, vodEnd:%s this[%p]\r\n", __FUNCTION__, __LINE__
            , Poco::DateTimeFormatter::format(timeBegin.timestamp(), "%Y-%m-%e %H:%M:%S").c_str()
            , Poco::DateTimeFormatter::format(timeEnd.timestamp(), "%Y-%m-%e %H:%M:%S").c_str(), this);
        return;
    }
	SFTRACE("MigtateTask", "%s[%d]:ҵ��ID[%s] �ļ���Ϣ Path[%s] lDeviceID[%d] lIcmsId[%d] this[%p]\r\n", __FUNCTION__, __LINE__
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
		DISPLAY_LOG("����ģ��", "��������ʧ��", "��ȡ���ݶ���ʧ��", "", 0);
		return -1;
	}

	std::vector<ST_BusinessFileInfo> vecFiles;
	int nRet = pDataProvider->QueryBusinessFileInfoByBusinessInfoId(m_stBFISTask.strBusinessID, vecFiles); //��ѯҵ�������Ϣ����ȡ��ҵ����ļ���Ϣ

	if (nRet <= 0 || vecFiles.empty())
	{
		SFTRACE("MigtateTask", " %s[%d] ��ȡҵ���ļ�ʧ��, ҵ��ID[%s] ����ֵ[%d] ���ݴ�С[%d] this[%p] \r\n", __FUNCTION__,
			__LINE__, m_stBFISTask.strBusinessID.c_str(), nRet, vecFiles.size(), this);
		return -1;
	}

	ST_BusinessInfo stBusiness;
	nRet = pDataProvider->QueryBusinessInfoById(m_stBFISTask.strBusinessID, stBusiness);

	//��ȡ¼���ļ��Ŀ�ʼ�ͽ���ʱ��
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
	//��ѯ��Ӧ��vod�ļ���Ϣ
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
	//localBranch.strBranchId == stBusiness.strBranchId ? filter.nFileArea = 1 : filter.nFileArea = 4;   //�����Լ���ҵ��Ͳ��豸�������������ڣ������Ǩ��
	filter.nVodFileType = 7;  //�ֶ��ļ�
	if (m_queryMode == 4)
		filter.migrateCenterInfo = m_stCenterInfo;
	filter.nFileArea = m_queryMode;

	strcpy(filter.strStartTime, Poco::DateTimeFormatter::format(vodBegin.timestamp(), "%Y-%m-%e %H:%M:%S").c_str());
	strcpy(filter.strEndTime, Poco::DateTimeFormatter::format(vodEnd.timestamp(), "%Y-%m-%e %H:%M:%S").c_str());
	ST_DeviceItem device;
	nRet = iSOC_GetDeviceInfoByIcmsSignAndIcmsDeviceId(m_lMCSession, &device, const_cast<TCHAR*>(stBusiness.strSubEquipmentIcmSign.c_str()), atoi(stBusiness.strSubEquipmentId.c_str()));
	if (nRet <= 0)
	{
		SFTRACE("MigtateTask", " %s[%d] ��ȡ�豸��Ϣʧ��, ҵ��ID[%s] �豸��ICMS��ʶ[%s] �豸���ڷֿص�ID[%s] ����ֵ[%d] this[%p] \r\n",__FUNCTION__,
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
	SFTRACE("MigtateTask", " %s[%d] ��ȡǨ��ҵ���ļ�, ҵ��ID[%s] �豸ID�б�[%s] ����ֵ[%d] ʱ��[%s][%s] this[%p]\r\n",
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
		SFTRACE("MigtateTask", " %s[%d] ��ʼ[%s]Ǩ������ ״̬[%d] ҵ��ID[%s], ������[%s]  this[%p]\r\n", __FUNCTION__, __LINE__,
			m_stBFISTask.nType == TSK_AUTO ? "�Զ�" : "�ֶ�", nRet, m_stBFISTask.strBusinessID.c_str(), m_stBFISTask.strLaunchEmployeeID.c_str(), this);
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
	SFTRACE("MigtateTask", " %s[%d] ֹͣǨ�� ҵ��ID[%s] Ǩ��ҵ��״̬[%d] Ǩ��״̬[%d] ����ֵ[%d] this[%p]\r\n", __FUNCTION__,
		__LINE__, m_stBFISTask.strBusinessID.c_str(), m_enumTaskState, m_stMigrateInfo.nState, nRet, this);
	if (nRet <= 0)
	{
		return -1;
	}
	else
	{
		m_nVodQueryCnt = 0;
		m_pTimer->KillTimer(-1);
		DISPLAY_LOG("����ģ��", "ֹͣ����ɹ�", "", "", 1);
		return 1;
	}
}
