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

    //�������Ŀǰֻ����ֶ����񣬳ɹ����������id
    virtual std::string AddTaskItem(IN std::string strBusinessID, IN std::string strEmployeeID, IN ManulTaskStartType enStartType, IN std::string strTaskID = "", IN DWORD_PTR dwReserved = 0) = 0;

    //����idɾ������,ֻ��ɾ���ֶ�����
    virtual int DeleteTaskItem(IN std::string strTaskID) = 0;

    //��ȡ���������������ֶ�����͵���ļƻ�����
    virtual int GetTaskCount() = 0;

    //��������id��ȡָ��������Ϣ
    virtual int GetTaskInfo(IN std::string strTaskID, OUT ST_BFISMigrateTask* pInfo) = 0;

    //��ȡ��ǰ���е�������Ϣ
    virtual int GetTaskInfo(IN OUT std::vector<ST_BFISMigrateTask>* pVecInfos) = 0;

    //�����ֶ����񣬵���������������ִ��ʱ�������ֶ�������Ч
    virtual int ControlTaskItem(IN TaskControlType enType, IN std::string strTaskID) = 0;

    //�����Զ�����ִ��ʱ��  TODO �����ڴ��еļƻ�ʱ�䣬ͬʱд�����ݿ�
    virtual int SetAutomaticPlan(IN std::string strPlanID, IN SYSTEMTIME stTimeBegin, IN SYSTEMTIME stTimeEnd, IN bool bEnable) = 0;
};