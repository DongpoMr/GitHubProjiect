// iBFIS.Server.MemoryWaySerializeDataStation.h : iBFIS.Server.MemoryWaySerializeDataStation DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerMemoryWaySerializeDataStationApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.MemoryWaySerializeDataStation.cpp
//

class CiBFISServerMemoryWaySerializeDataStationApp : public CWinApp
{
public:
	CiBFISServerMemoryWaySerializeDataStationApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
