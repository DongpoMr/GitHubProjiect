// iBFIS.Server.DisplayLogStation.h : iBFIS.Server.DisplayLogStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerDisplayLogStationApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.DisplayLogStation.cpp
//

class CISocObject;
class CiBFISServerDisplayLogStationApp : public CWinApp
{
public:
	CiBFISServerDisplayLogStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

CISocObject* __stdcall iSOC_CreateObject();