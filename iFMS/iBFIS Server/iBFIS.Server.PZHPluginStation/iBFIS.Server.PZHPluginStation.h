// iBFIS.Server.PZHPluginStation.h : iBFIS.Server.PZHPluginStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerPZHPluginStationApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.PZHPluginStation.cpp
//

class CiBFISServerPZHPluginStationApp : public CWinApp
{
public:
	CiBFISServerPZHPluginStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
