// iBFIS.Server.NCPluginStation.h : iBFIS.Server.NCPluginStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerNCPluginStationApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.NCPluginStation.cpp
//

class CiBFISServerNCPluginStationApp : public CWinApp
{
public:
	CiBFISServerNCPluginStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
