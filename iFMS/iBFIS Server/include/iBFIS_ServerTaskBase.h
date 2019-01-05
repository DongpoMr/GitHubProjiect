#pragma once
#include "IDCSStationManager.h"
#include "iSOC_PrivateStructDefine.h"
#include "iSOC_MonFactoryManagement.h"
#include "iSOC_ErrorDef.h"

interface IBFIS_ServerTaskBase : public IDCSBaseStation
{
public:
	IBFIS_ServerTaskBase()
	{
		iSOC_MonFactoryManagement fmt;
		m_pTaskMgrStaion = static_cast<IDCSStationManager*>(fmt.CreateObject(OBJECT_TYPE_DCSSERVER_STATIONMANAGER, "",__FUNCTION__));
		m_pTaskManger = static_cast<IDCSTaskManager*>(fmt.CreateObject(OBJECT_TYPE_DCSSERVER_TASK_MANAGER, "",__FUNCTION__));
	}
	virtual ~IBFIS_ServerTaskBase() 
	{
		iSOC_MonFactoryManagement fmt;
		if (m_pTaskMgrStaion)
			fmt.ReleaseObject((CISocObject **)(&m_pTaskMgrStaion), __FUNCTION__);
		if (m_pTaskManger)
			fmt.ReleaseObject((CISocObject **)(&m_pTaskManger), __FUNCTION__);
		m_pTaskMgrStaion = nullptr;
		m_pTaskManger = nullptr;
	}
public:
	//初始化Station，一般在这里面向StationManager注册任务
	virtual ISOC_INT InitStation(ISOC_DWORDPTR dwReserved = 0)
	{
		return 1;//return RegisterTaskProcessor();
	}
	//处理任务
	virtual ISOC_INT ProcessTask(ST_DCSTaskInfo& tskInfo) = 0;

	virtual ISOC_INT UnInitStation(ISOC_DWORDPTR dwReserved = 0)
	{
		return 1;//return UnRegisterTaskProcessor();
	}
	virtual ISOC_INT RegisterTaskProcessor() = 0;
	virtual ISOC_INT UnRegisterTaskProcessor() = 0;

	virtual ISOC_INT CheckObjectEffective()
	{
		iSOC_MonFactoryManagement fmt;
		if (m_pTaskManger)
		{
			if (fmt.CheckObjectCanBeUse(m_pTaskManger))
			{
				fmt.ReleaseObject((CISocObject **)(&m_pTaskManger), __FUNCTION__);
				m_pTaskManger = nullptr;
			}
		}
				
		if (m_pTaskMgrStaion)
		{
			if (fmt.CheckObjectCanBeUse(m_pTaskMgrStaion))
			{
				UnRegisterTaskProcessor();
				fmt.ReleaseObject((CISocObject **)(&m_pTaskMgrStaion), __FUNCTION__);
				m_pTaskMgrStaion = nullptr;
			}
		}

		if (nullptr == m_pTaskMgrStaion || nullptr == m_pTaskManger)
			return ISOC_ERR_FAILED;
		return ISOC_ERR_SUCCESS;
	}

protected:
	IDCSStationManager  *m_pTaskMgrStaion;
	IDCSTaskManager     *m_pTaskManger;
};