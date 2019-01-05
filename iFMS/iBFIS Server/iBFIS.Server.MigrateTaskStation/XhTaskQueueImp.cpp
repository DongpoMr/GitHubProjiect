#include "stdafx.h"
#include "XhTaskQueueImp.h"

#define LOCKLIST iCMSP_SimpleLock lock(&m_csLockList, __FUNCTION__);
#define LOCKITEM iCMSP_SimpleLock lock(&m_csLockItem, __FUNCTION__);

XhTaskQueueImp::XhTaskQueueImp() :m_bExit(false)
{
}


XhTaskQueueImp::~XhTaskQueueImp()
{
}

int XhTaskQueueImp::Size()
{
    LOCKLIST;
    return m_listTasks.size();
}

int XhTaskQueueImp::PushBack(ST_BFISMigrateTask* pstTaskInfo)
{
    LOCKLIST;
    pstTaskInfo->nOrderID = m_listTasks.size();
    pstTaskInfo->nProcess = 0;
    pstTaskInfo->nStatus = TSK_READY;
    m_listTasks.push_back(*pstTaskInfo);
    return m_listTasks.size() - 1;
}

int XhTaskQueueImp::At(int nIndex, ST_BFISMigrateTask* pstTaskInfo)
{
    if (pstTaskInfo == nullptr) return -1;

    LOCKLIST;
    if (m_listTasks.size() <= nIndex)
    {
        return -2;
    }

    int nCount = 0;
    for (auto iter = m_listTasks.begin(); iter != m_listTasks.end(); iter++)
    {
        if (nCount++ == nIndex)
        {
            *pstTaskInfo = *iter;
            return 1;
        }
    }
    return -3;
}

int XhTaskQueueImp::Remove(int nIndex)
{
    LOCKLIST;
    if (m_listTasks.size() <= nIndex)
    {
        return -2;
    }

    int nCount = 0;
    for (auto iter = m_listTasks.begin(); iter != m_listTasks.end(); iter++)
    {
        if (nCount++ == nIndex)
        {
            m_listTasks.erase(iter);
            return 1;
        }
    }
    return 1;
}

int XhTaskQueueImp::Remove(std::string strTaskID)
{
    LOCKLIST;
    if (m_listTasks.empty())
        return 1;

    for (auto iter = m_listTasks.begin(); iter != m_listTasks.end(); iter++)
    {
        if (iter->strTaskID == strTaskID)
        {
            m_listTasks.erase(iter);
            return 1;
        }
    }
    return 1;
}

int XhTaskQueueImp::UpdateProgress(int nIndex, int nProgress)
{
    LOCKLIST;
    if (m_listTasks.size() <= nIndex)
    {
        return -2;
    }

    int nCount = 0;
    for (auto iter = m_listTasks.begin(); iter != m_listTasks.end(); iter++)
    {
        if (nCount++ == nIndex)
        {
            iter->nProcess = nProgress;
            return 1;
        }
    }
    return -3;
}

int XhTaskQueueImp::UpdateStatus(int nIndex, TaskStatus enStatus)
{
    LOCKLIST;
    if (m_listTasks.size() <= nIndex)
    {
        return -2;
    }

    int nCount = 0;
    for (auto iter = m_listTasks.begin(); iter != m_listTasks.end(); iter++)
    {
        if (nCount++ == nIndex)
        {
            iter->nStatus = enStatus;
            return 1;
        }
    }
    return -3;
}

std::vector<ST_BFISMigrateTask> XhTaskQueueImp::GetAllTask()
{
    std::vector < ST_BFISMigrateTask >  vec;
    LOCKLIST;
    if (m_listTasks.empty())
    {
        return vec;
    }

    for each (auto& var in m_listTasks)
    {
        vec.push_back(var);
    }
    return vec;
}

int XhTaskQueueImp::Find(std::string strTaskID, ST_BFISMigrateTask* pstTaskInfo)
{
    LOCKLIST;
    if (pstTaskInfo == nullptr || m_listTasks.empty())
    {
        return -1;
    }

    int nCount = 0;
    for (auto iter = m_listTasks.begin(); iter != m_listTasks.end(); iter++)
    {
        if (iter->strTaskID == strTaskID)
        {
            *pstTaskInfo = *iter;
            return nCount;
        }
    }

    return -2;
}

int XhTaskQueueImp::SetMCSession(ISOC_LONGPTR lMCSession /*= 0*/)
{
    m_mcSession = lMCSession;
}

void XhTaskQueueImp::Run()
{
    while (!m_bExit)
    {
        ST_BFISMigrateTask readyInfo, procInfo;
        //遍历链表，查看有没有正在执行的任务
        STRY;
        LOCKLIST;
        for each (const auto& var in m_listTasks)
        {
            if (var.nStatus == TSK_PROCESSING)
            {
                procInfo = var;
                break;
            }
            if (readyInfo.strTaskID.empty())
            {
                readyInfo = var;
            }
        }
        SCATCH;
        //有的话查询该任务进度
        if (!procInfo.strTaskID.empty())
        {
//             LOCKITEM;
//             auto iter = m_mapMigrateItem.find(procInfo.strTaskID);
//             if (iter != m_mapMigrateItem.end())
//             {
//                 procInfo.nProcess = iter->second->GetProcess();
//                 int nStatus = iter->second->GetStatus();
//                 if (nStatus == 3)
//                 {
//                     procInfo.nStatus = TSK_FINISHED;
//                 }
//             }
        }
        else if (!readyInfo.strTaskID.empty())  //没有的话查看是否有可以开始的任务
        {
            XhMigrateItemImp* pItem = XhMigrateItemImp::CreateItem(m_mcSession, &m_stCenter);
            if (pItem)
            {
                m_mapMigrateItem[readyInfo.strTaskID] = pItem;
                //TODO 添加VOD文件信息

                readyInfo.nStatus = TSK_PROCESSING;
            }
        }
        
        
        //Delay some time
    }
}

int XhTaskQueueImp::SetMigrateCenter(ST_CenterInfo* pInfo)
{
    if (pInfo == NULL)
        return -1;

    m_stCenter = *pInfo;
    return 1;
}
