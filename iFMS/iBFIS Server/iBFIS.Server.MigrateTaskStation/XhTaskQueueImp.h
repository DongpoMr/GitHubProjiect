#pragma once
#include "stdafx.h"
#include "iCMSP_SimpleLock.h"
#include "IcmsP_Utility.h"
#include "iBFIS_UniqueDefine.h"
#include "iBFISDBOperation.h"
#include "iBFIS_DataType_Define.h"
#include <list>
#include "iSOC_FileMigrateV2.0Module.h"
#include "IThread.h"
#include <map>
#include "XhMigrateItemImp.h"

class XhTaskQueueImp:public IRunable
{
public:
    XhTaskQueueImp();

    virtual ~XhTaskQueueImp();

    int SetMCSession(ISOC_LONGPTR lMCSession = 0);
    int SetMigrateCenter(ST_CenterInfo* pInfo);

    int Size();

    int PushBack(ST_BFISMigrateTask* pstTaskInfo);
    int At(int nIndex, ST_BFISMigrateTask* pstTaskInfo);

    //��������id���Ҷ�Ӧ���񣬳ɹ��򷵻ظ������ڶ����е�index,ʧ�ܷ���С��0��ֵ
    int Find(std::string strTaskID, ST_BFISMigrateTask* pstTaskInfo);
    int Remove(int nIndex);
    int Remove(std::string strTaskID);

//    int SetTask(const ST_BFISMigrateTask* pstTaskInfo);

    int UpdateProgress(int nIndex, int nProgress);
    int UpdateStatus(int nIndex, TaskStatus enStatus);

    std::vector<ST_BFISMigrateTask> GetAllTask();

    void Run();
private:
    iCMSP_SimpleCS m_csLockList;
    std::list<ST_BFISMigrateTask> m_listTasks;
    
    iCMSP_SimpleCS m_csLockItem;
    std::map<std::string, XhMigrateItemImp*> m_mapMigrateItem;  //����soc sdkǨ�ƶ���


    ISOC_LONGPTR m_mcSession;
    bool m_bExit;
    ST_CenterInfo m_stCenter;
};

