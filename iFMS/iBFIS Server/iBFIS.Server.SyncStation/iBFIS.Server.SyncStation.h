// iBFIS.Server.SyncStation.h : iBFIS.Server.SyncStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerSyncStationApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.SyncStation.cpp
//
class CISocObject;
class CiBFISServerSyncStationApp : public CWinApp
{
public:
	CiBFISServerSyncStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
CISocObject* __stdcall iSOC_CreateObject();