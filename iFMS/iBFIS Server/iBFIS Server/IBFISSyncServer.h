#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include <vector>
#include "iBFIS_UniqueDefine.h"
#include "IBFISCommunicateSyncServer.h"

interface IBFISSyncServer:public IBFISTaskStation
{
	IBFISSyncServer()
	{
		m_nObjectType = OBJECT_TYPE_BFISSYNC_SERVER;
	}
	virtual ~IBFISSyncServer(){};

	virtual int		Init(ISOC_DWORDPTR dwReserved = 0) = 0;
	virtual int		UnInit(ISOC_DWORDPTR dwReserved = 0) = 0;
	virtual void	OnDisConnect(UINT64 fromAddr) = 0;

	virtual int     DoSyncAll(vector<ST_BranchInfo> vecBranchInfo, IN ISOC_DWORDPTR dwReserved = 0) = 0;

	virtual int		ExtendFunction(IN const ISOC_INT nExtendType,IN ISOC_DWORDPTR dwExtendData) = 0;

	virtual void	SetDisplayListCtrl(CListCtrl* pList) = 0;

	virtual bool	RestoreLastSyncTime(CString strTime) = 0;
	virtual bool	ReadLastSyncTime(CString& strTime) = 0;
	virtual int    CheckIsTopServer(int nType) = 0;
};