// iBFIS.Server.DBOperatorStation.h : iBFIS.Server.DBOperatorStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerDBOperatorStationApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.DBOperatorStation.cpp
//

class CISocObject;
class CiBFISServerDBOperatorStationApp : public CWinApp
{
public:
	CiBFISServerDBOperatorStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
CISocObject* __stdcall iSOC_CreateObject();