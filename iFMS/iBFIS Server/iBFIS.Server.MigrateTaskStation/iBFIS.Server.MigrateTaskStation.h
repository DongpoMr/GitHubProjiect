// iBFIS.Server.MigrateTaskStation.h : iBFIS.Server.MigrateTaskStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerMigrateTaskStationApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.MigrateTaskStation.cpp
//
class CISocObject;
class CiBFISServerMigrateTaskStationApp : public CWinApp
{
public:
	CiBFISServerMigrateTaskStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
extern "C"
{
    CISocObject* __stdcall iSOC_CreateObject();
}