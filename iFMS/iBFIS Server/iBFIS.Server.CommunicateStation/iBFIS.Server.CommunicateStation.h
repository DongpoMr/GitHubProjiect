// iBFIS.Server.CommunicateStation.h : iBFIS.Server.CommunicateStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerCommunicateStationApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.CommunicateStation.cpp
//
class CISocObject;
class CiBFISServerCommunicateStationApp : public CWinApp
{
public:
	CiBFISServerCommunicateStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
CISocObject* iSOC_CreateObject();