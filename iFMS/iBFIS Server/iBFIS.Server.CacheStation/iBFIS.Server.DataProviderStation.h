// iBFIS.Server.CacheStation.h : iBFIS.Server.CacheStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerDataProviderStationApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.CacheStation.cpp
//
class CISocObject;
class CiBFISServerDataProviderStationApp : public CWinApp
{
public:
	CiBFISServerDataProviderStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
CISocObject* iSOC_CreateObject();