// iBFIS.Server.JZPluginStation.h : iBFIS.Server.JZPluginStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerJZPluginStationApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.JZPluginStation.cpp
//

class CiBFISServerJZPluginStationApp : public CWinApp
{
public:
	CiBFISServerJZPluginStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
