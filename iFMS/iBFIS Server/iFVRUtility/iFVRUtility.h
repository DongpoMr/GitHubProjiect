// iFVRUtility.h : iFVRUtility DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiFVRUtilityApp
// �йش���ʵ�ֵ���Ϣ������� iFVRUtility.cpp
//

class CiFVRUtilityApp : public CWinApp
{
public:
	CiFVRUtilityApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
