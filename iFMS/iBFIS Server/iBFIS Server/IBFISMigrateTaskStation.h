#pragma  once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iBFIS_UniqueDefine.h"
#include "iBFIS_DataType_Define.h"
#include "iSOC_UnitDefine.h"
#include <string>
#include "IBFISTaskStation.h"

interface IMigrateTaskStation :public IBFISTaskStation
{
    IMigrateTaskStation()
    {
        m_nObjectType = OBJECT_TYPE_BFISSERVER_MIGRATETASKSTATION;
    }
    virtual ~IMigrateTaskStation(){};

    //添加任务，目前只针对手动任务，成功返回任务的id
    virtual std::string AddTaskItem(IN std::string strBusinessID, IN std::string strEmployeeID, IN ManulTaskStartType enStartType, IN std::string strTaskID = "", IN DWORD_PTR dwReserved = 0) = 0;

    //根据id删除任务,只能删除手动任务
    virtual int DeleteTaskItem(IN std::string strTaskID) = 0;

    //获取任务总数，包括手动任务和当天的计划任务
    virtual int GetTaskCount() = 0;

    //根据任务id获取指定任务信息
    virtual int GetTaskInfo(IN std::string strTaskID, OUT ST_BFISMigrateTask* pInfo) = 0;

    //获取当前所有的任务信息
    virtual int GetTaskInfo(IN OUT std::vector<ST_BFISMigrateTask>* pVecInfos) = 0;

    //控制手动任务，当有其他任务正在执行时，启动手动任务无效
    virtual int ControlTaskItem(IN TaskControlType enType, IN std::string strTaskID) = 0;

    //设置自动任务执行时间  TODO 更新内存中的计划时间，同时写入数据库
    virtual int SetAutomaticPlan(IN std::string strPlanID, IN SYSTEMTIME stTimeBegin, IN SYSTEMTIME stTimeEnd, IN bool bEnable) = 0;
};