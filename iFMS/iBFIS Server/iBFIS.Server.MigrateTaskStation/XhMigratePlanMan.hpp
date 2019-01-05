#pragma once
#include "stdafx.h"
#include "iCMSP_SimpleLock.h"
#include "IcmsP_Utility.h"
#include "iBFIS_UniqueDefine.h"
#include "iSOC_MonFactoryManagement.h"
#include "XhLogDisplayInterface.h"

#include "Poco/DateTime.h"
#include "Poco/DateTimeParser.h"
#include "Poco/LocalDateTime.h"
#include "Poco/Mutex.h"
#include "Poco/DateTimeFormatter.h"

class XhMigeratePlanMan
{
public:
    XhMigeratePlanMan() {};

    ~XhMigeratePlanMan() {};

    int AddPlan(const ST_TaskPlan& plan)
    {
        STRY;
        Poco::FastMutex::ScopedLock lock(m_lockPlan);
        auto iter = m_mapTaskPlan.find(plan.strPlanID);
        if (iter != m_mapTaskPlan.end())
            return -1;

        m_mapTaskPlan[plan.strPlanID] = plan;
        SCATCH;
        DISPLAY_TASKPLAN(plan.strPlanID, plan.strTimeBegin, plan.strTimeEnd, plan.nEnable);
        return 1;
    }

    int SetPlan(const ST_TaskPlan& plan)
    {
        STRY;
        Poco::FastMutex::ScopedLock lock(m_lockPlan);
        m_mapTaskPlan[plan.strPlanID] = plan;
        SCATCH;
        DISPLAY_TASKPLAN(plan.strPlanID, plan.strTimeBegin, plan.strTimeEnd, plan.nEnable);
        return 1;
    }

    int GetPlan(const std::string strPlanID, ST_TaskPlan& plan)
    {
        Poco::FastMutex::ScopedLock lock(m_lockPlan);
        auto iter = m_mapTaskPlan.find(strPlanID);
        if (iter != m_mapTaskPlan.end())
        {
            plan = iter->second;
            return 1;
        }
        return -1;
    }

    int GetPlan(std::vector<ST_TaskPlan>& vecPlans)
    {
        Poco::FastMutex::ScopedLock lock(m_lockPlan);
        for (auto iter = m_mapTaskPlan.begin(); iter != m_mapTaskPlan.end(); iter++)
        {
            vecPlans.push_back(iter->second);
        }
        return 1;
    }
	int DELPlan()
	{
		Poco::FastMutex::ScopedLock lock(m_lockPlan);
		m_mapTaskPlan.clear();
		return 1;
	}
    int GetCount()
    {
        Poco::FastMutex::ScopedLock lock(m_lockPlan);
        return m_mapTaskPlan.size();
    }

    //如果当前未到计划时间，则strNextTime为下次执行计划的时间，否则为当前计划的开始时间
    bool CheckCanBeMigrate(std::string* pstrNextTime = NULL)
    {
#if 0
        SYSTEMTIME timeNow;
        GetLocalTime(&timeNow);
        CTime ctimeNow(timeNow);
        iCMSP_SimpleLock lock(&m_csLockPlan, __FUNCTION__);
        for (auto iter = m_mapTaskPlan.begin(); iter != m_mapTaskPlan.end(); iter++)
        {
            SYSTEMTIME timeBegin, timeEnd;
            GetLocalTime(&timeBegin);
            GetLocalTime(&timeEnd);
            timeBegin.wHour = timeBegin.wMinute = timeBegin.wSecond = 0;
            timeEnd.wHour = timeEnd.wMinute = timeEnd.wSecond = 0;
            sscanf(iter->second.strTimeBegin.c_str(), "%d:%d:%d", &timeBegin.wHour, &timeBegin.wMinute, &timeBegin.wSecond);
            sscanf(iter->second.strTimeEnd.c_str(), "%d:%d:%d", &timeEnd.wHour, &timeEnd.wMinute, &timeEnd.wSecond);
            CTime ctimeBegin(timeBegin);
            CTime ctimeEnd(timeEnd);
            if (ctimeNow < ctimeEnd && ctimeNow > ctimeBegin)
            {
                return true;
            }
        }
        return false;
#else
        Poco::LocalDateTime timeNow;
        Poco::DateTime dtNow;
        dtNow.assign(timeNow.year(), timeNow.month(), timeNow.day(), timeNow.hour(), timeNow.minute(), timeNow.second());
        char szBuf[20] = { 0 };
        sprintf(szBuf, "%04d-%02d-%02d", timeNow.year(), timeNow.month(), timeNow.day());

        Poco::DateTime dtNextTime = dtNow;
        Poco::FastMutex::ScopedLock lock(m_lockPlan);
        for (auto iter = m_mapTaskPlan.begin(); iter != m_mapTaskPlan.end(); iter++)
        {
            if (iter->second.nEnable == 0)
                continue;

            int nTzd = 0; 
            std::string strRBegin = szBuf + iter->second.strTimeBegin;
            Poco::DateTime timeBegin = Poco::DateTimeParser::parse(strRBegin, nTzd);

            strRBegin = szBuf + iter->second.strTimeEnd;
            Poco::DateTime timeEnd = Poco::DateTimeParser::parse(strRBegin, nTzd);

            if (timeBegin > timeEnd)
            {
                timeEnd += Poco::Timespan::Timespan(1, 0, 0, 0, 0); //跨天时，结束时间加上一天
            }

            if (dtNow < timeEnd && dtNow > timeBegin)
            {
                if (pstrNextTime)
                    *pstrNextTime = Poco::DateTimeFormatter::format(timeBegin.timestamp(), "%Y-%m-%e %H:%M:%S");
                return true;
            }
            else
            {
                //取最近一次开始时间
                if (dtNextTime == dtNow) 
                {
                    dtNextTime = timeBegin;
                }
                else if (dtNextTime > timeBegin)
                {
                    dtNextTime = timeBegin;
                }
            }
        }

        if (pstrNextTime)
            *pstrNextTime = Poco::DateTimeFormatter::format(dtNextTime.timestamp(), "%Y-%m-%e %H:%M:%S");
        return false;
#endif
    }

private:
    Poco::FastMutex m_lockPlan;
    std::map<std::string, ST_TaskPlan> m_mapTaskPlan;
};
