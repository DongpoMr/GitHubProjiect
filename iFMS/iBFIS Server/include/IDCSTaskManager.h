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
	ISOC_UINT nTaskID; //����ID
	ISOC_INT nCmdID; //����ͷID
	enum EN_CMDSrcType{SMS_SERVER = 1,DCS_CLIENT,ALARM_SERVER,DCS_SERVER,TVWALL_SERVER};
	ISOC_INT nSrcType;//����Դ���ͣ�1SMS��������2dcs�ͻ��ˣ�3����������,4DCS������,5TVWALL������
	UINT64	nSrcAddr;//��Ϣ��Դ�ĵ�ַ
	string	 strXML;//��������
	bool	bIsQueue; //�Ƿ�˳��
	ISOC_INT nSeqID;//����id
	ISOC_INT nOutputID;
	ISOC_DWORDPTR dwReserved; //�����ֶ�
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

//DCS���������`
interface IDCSTaskManager : public CISocObject
{
	IDCSTaskManager()
	{
		m_nObjectType = OBJECT_TYPE_DCSSERVER_TASK_MANAGER;
	}
	virtual ~IDCSTaskManager(){};

	//�������
	virtual ISOC_INT AddTask(IN ST_DCSTaskInfo &info) = 0;
	//����һ���µ������
	virtual ISOC_UINT CreateNewTaskID(IN ISOC_DWORDPTR dwReserved = NULL) = 0;
	virtual ISOC_UINT GetCountTask(IN BOOL bSort = TRUE, IN ISOC_DWORDPTR dwReserved1 = 0) = 0;
		
};