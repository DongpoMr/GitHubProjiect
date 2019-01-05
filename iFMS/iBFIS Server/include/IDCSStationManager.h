#pragma once
#include "iSOCObject.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PrivateStructDefine.h"
#include "iSOC_PublicStructDefine.h"
#include "IDCSTaskManager.h"
#include <vector>
using namespace std;

//基础业务对象，所有的处理客户端相关的需要接收xml的业务对象都必须继承此接口
//这是一个特殊的对象，没有对象标识，但继承自CISocObject，其各自的子类必须要对象标识
interface IDCSBaseStation 
{
	virtual ~IDCSBaseStation(){};

	//初始化Station，一般在这里面向StationManager注册任务
	virtual ISOC_INT InitStation(ISOC_DWORDPTR dwReserved = 0) = 0;
	//反初始化函数,如果不需要反初始化可以不实现
	virtual ISOC_INT UnInitStation(ISOC_DWORDPTR dwReserved = 0)
	{
		return -1;
	}
	//处理任务
	virtual ISOC_INT ProcessTask(ST_DCSTaskInfo& tskInfo) = 0;
};

//业务管理对象
interface IDCSStationManager : public CISocObject
{
	IDCSStationManager()
	{
		m_nObjectType = OBJECT_TYPE_DCSSERVER_STATIONMANAGER;
	}
	virtual ~IDCSStationManager(){};
	//注册任务处理对象
	virtual ISOC_INT RegisterTaskProcessor(IN ISOC_INT nSrcType,IN ISOC_INT nCmdID,IN IDCSBaseStation* pProcessStation,IN ISOC_DWORDPTR dwReserved = 0) = 0;
	virtual ISOC_INT RegisterTaskProcessor( IN ISOC_INT nSrcType,IN ISOC_INT nBeginCmdID, IN ISOC_INT nEndCmdID,
		IN IDCSBaseStation* pProcessStation,IN ISOC_DWORDPTR dwReserved /*= 0*/ ) = 0;
	//取消注册任务处理对象
	virtual ISOC_INT UnRegisterTaskProcessor(IN ISOC_INT nSrcType,IN ISOC_INT nCmdID,IN IDCSBaseStation* pProcessStation,IN ISOC_DWORDPTR dwReserved = 0)= 0;
	virtual ISOC_INT UnRegisterTaskProcessor(IN ISOC_INT nSrcType, IN ISOC_INT nBeginCmdID, IN ISOC_INT nEndCmdID, IN IDCSBaseStation* pProcessStation,
		IN ISOC_DWORDPTR dwReserved = 0) = 0;
	//获取某信令的任务处理对象
	virtual vector<IDCSBaseStation*> GetTheTaskProcessor(IN ISOC_INT nSrcType,IN ISOC_INT nCmdID,IN ISOC_DWORDPTR dwReserved = NULL) = 0;
};

