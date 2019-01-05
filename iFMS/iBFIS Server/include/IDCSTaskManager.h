#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOCObject.h"
#include "iSOC_UnitDefine.h"
#include "iSOC_PrivateStructDefine.h"
#include <string>
using namespace std;

#pragma pack(push,1)

struct ST_DCSTaskInfo
{
	ISOC_UINT nTaskID; //任务ID
	ISOC_INT nCmdID; //信令头ID
	enum EN_CMDSrcType{SMS_SERVER = 1,DCS_CLIENT,ALARM_SERVER,DCS_SERVER,TVWALL_SERVER};
	ISOC_INT nSrcType;//信令源类型：1SMS服务器，2dcs客户端，3报警服务器,4DCS服务器,5TVWALL服务器
	UINT64	nSrcAddr;//信息来源的地址
	string	 strXML;//信令内容
	bool	bIsQueue; //是否讲顺序
	ISOC_INT nSeqID;//序列id
	ISOC_INT nOutputID;
	ISOC_DWORDPTR dwReserved; //保留字段
	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;
	ISOC_DWORDPTR dwReserved3;
	ST_DCSTaskInfo():nTaskID(0),nCmdID(0),nSrcType(0),nSrcAddr(0),bIsQueue(false),nSeqID(0),strXML(""),dwReserved(0)
		,dwReserved1(0),dwReserved2(0),dwReserved3(0)
	{};

	ST_DCSTaskInfo(ISOC_INT nTaskID,ISOC_INT nCmdID,ISOC_INT nSeqID,ISOC_INT nSrcType,string strXML,bool bIsQueue,ISOC_DWORDPTR dwReserved = NULL)
	{
		this->nTaskID = nTaskID;
		this->nCmdID = nCmdID;
		this->nSrcType = nSrcType;
		this->strXML = strXML;
		this->bIsQueue = bIsQueue;
		this->dwReserved = dwReserved;
		this->nSeqID   = nSeqID;
		this->dwReserved1 = dwReserved1;
		this->dwReserved2 = dwReserved2;
		this->dwReserved3 = dwReserved3;

	}

	ST_DCSTaskInfo(const ST_DCSTaskInfo& info)
	{
		this->nCmdID = info.nCmdID;
		this->nSrcType = info.nSrcType;
		this->nSrcAddr = info.nSrcAddr;
		this->nTaskID = info.nTaskID;
		this->strXML = info.strXML;
		this->bIsQueue = info.bIsQueue;
		this->dwReserved = info.dwReserved;
		this->nSeqID	= info.nSeqID;
		this->dwReserved1 = info.dwReserved1;
		this->dwReserved2 = info.dwReserved2;
		this->dwReserved3 = info.dwReserved3;

	}

	ST_DCSTaskInfo& operator =(const ST_DCSTaskInfo& info)
	{
		this->nCmdID = info.nCmdID;
		this->nSrcType = info.nSrcType;
        this->nSrcAddr = info.nSrcAddr;
		this->nTaskID = info.nTaskID;
		this->strXML = info.strXML;
		this->bIsQueue = info.bIsQueue;
		this->dwReserved = info.dwReserved;
		this->nSeqID	 = info.nSeqID;
		this->dwReserved1 = info.dwReserved1;
		this->dwReserved2 = info.dwReserved2;
		this->dwReserved3 = info.dwReserved3;

		return *this;
	}

};

#pragma pack(pop)

//DCS任务管理器`
interface IDCSTaskManager : public CISocObject
{
	IDCSTaskManager()
	{
		m_nObjectType = OBJECT_TYPE_DCSSERVER_TASK_MANAGER;
	}
	virtual ~IDCSTaskManager(){};

	//添加任务
	virtual ISOC_INT AddTask(IN ST_DCSTaskInfo &info) = 0;
	//产生一个新的任务号
	virtual ISOC_UINT CreateNewTaskID(IN ISOC_DWORDPTR dwReserved = NULL) = 0;
	virtual ISOC_UINT GetCountTask(IN BOOL bSort = TRUE, IN ISOC_DWORDPTR dwReserved1 = 0) = 0;
		
};