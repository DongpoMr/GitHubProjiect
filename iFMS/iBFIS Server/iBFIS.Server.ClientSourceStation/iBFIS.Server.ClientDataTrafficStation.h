// iBFIS.Server.ClientSourceStation.h : iBFIS.Server.ClientSourceStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerClientDataTrafficStationApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.ClientSourceStation.cpp
//
class CISocObject;
class CiBFISServerClientDataTrafficStationApp : public CWinApp
{
public:
	CiBFISServerClientDataTrafficStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

CISocObject* iSOC_CreateObject();