// iBFIS.Server.SyncStation.h : iBFIS.Server.SyncStation DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CiBFISServerSyncStationApp
// 有关此类实现的信息，请参阅 iBFIS.Server.SyncStation.cpp
//
class CISocObject;
class CiBFISServerSyncStationApp : public CWinApp
{
public:
	CiBFISServerSyncStationApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
CISocObject* __stdcall iSOC_CreateObject();