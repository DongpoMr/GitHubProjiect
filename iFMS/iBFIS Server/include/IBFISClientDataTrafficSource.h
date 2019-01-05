#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iBFIS_UniqueDefine.h"
#include "IBFISCommunicateSyncServer.h"

interface IBFISClientDataTrafficSource:public IBFISTaskStation
{
	IBFISClientDataTrafficSource()
	{
		m_nObjectType = OBJECT_TYPE_BFIS_CLIENTCOMMUNICATION;
	}
	virtual ~IBFISClientDataTrafficSource(){};

// 	//
	virtual ISOC_BOOL Init() = 0;
	virtual ISOC_BOOL UnInit() = 0;
	virtual void DisConnect(UINT64 fromAddr) = 0;
	virtual ISOC_BOOL GetEmployeeId(UINT64 fromAddr,string& strId) = 0;
};