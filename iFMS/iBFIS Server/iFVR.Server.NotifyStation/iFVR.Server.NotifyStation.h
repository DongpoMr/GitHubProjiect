// iFVR.Server.NotifyStation.h : iFVR.Server.NotifyStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiFVRServerNotifyStationApp
// �йش���ʵ�ֵ���Ϣ������� iFVR.Server.NotifyStation.cpp
//

class CiFVRServerNotifyStationApp : public CWinApp
{
public:
	CiFVRServerNotifyStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
