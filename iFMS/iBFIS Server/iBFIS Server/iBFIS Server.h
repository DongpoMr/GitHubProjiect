
// iBFIS Server.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerApp:
// �йش����ʵ�֣������ iBFIS Server.cpp
//

class CiBFISServerApp : public CWinApp
{
public:
	CiBFISServerApp();

// ��д
public:
	virtual BOOL InitInstance();
    BOOL CheckIsRun();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CiBFISServerApp theApp;