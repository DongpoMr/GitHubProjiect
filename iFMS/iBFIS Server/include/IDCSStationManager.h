#pragma once
#include "iSOCObject.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PrivateStructDefine.h"
#include "iSOC_PublicStructDefine.h"
#include "IDCSTaskManager.h"
#include <vector>
using namespace std;

//����ҵ��������еĴ���ͻ�����ص���Ҫ����xml��ҵ����󶼱���̳д˽ӿ�
//����һ������Ķ���û�ж����ʶ�����̳���CISocObject������Ե��������Ҫ�����ʶ
interface IDCSBaseStation 
{
	virtual ~IDCSBaseStation(){};

	//��ʼ��Station��һ������������StationManagerע������
	virtual ISOC_INT InitStation(ISOC_DWORDPTR dwReserved = 0) = 0;
	//����ʼ������,�������Ҫ����ʼ�����Բ�ʵ��
	virtual ISOC_INT UnInitStation(ISOC_DWORDPTR dwReserved = 0)
	{
		return -1;
	}
	//��������
	virtual ISOC_INT ProcessTask(ST_DCSTaskInfo& tskInfo) = 0;
};

//ҵ��������
interface IDCSStationManager : public CISocObject
{
	IDCSStationManager()
	{
		m_nObjectType = OBJECT_TYPE_DCSSERVER_STATIONMANAGER;
	}
	virtual ~IDCSStationManager(){};
	//ע�����������
	virtual ISOC_INT RegisterTaskProcessor(IN ISOC_INT nSrcType,IN ISOC_INT nCmdID,IN IDCSBaseStation* pProcessStation,IN ISOC_DWORDPTR dwReserved = 0) = 0;
	virtual ISOC_INT RegisterTaskProcessor( IN ISOC_INT nSrcType,IN ISOC_INT nBeginCmdID, IN ISOC_INT nEndCmdID,
		IN IDCSBaseStation* pProcessStation,IN ISOC_DWORDPTR dwReserved /*= 0*/ ) = 0;
	//ȡ��ע�����������
	virtual ISOC_INT UnRegisterTaskProcessor(IN ISOC_INT nSrcType,IN ISOC_INT nCmdID,IN IDCSBaseStation* pProcessStation,IN ISOC_DWORDPTR dwReserved = 0)= 0;
	virtual ISOC_INT UnRegisterTaskProcessor(IN ISOC_INT nSrcType, IN ISOC_INT nBeginCmdID, IN ISOC_INT nEndCmdID, IN IDCSBaseStation* pProcessStation,
		IN ISOC_DWORDPTR dwReserved = 0) = 0;
	//��ȡĳ��������������
	virtual vector<IDCSBaseStation*> GetTheTaskProcessor(IN ISOC_INT nSrcType,IN ISOC_INT nCmdID,IN ISOC_DWORDPTR dwReserved = NULL) = 0;
};

