// iBFIS.Server.MCOperateStatiom.h : iBFIS.Server.MCOperateStatiom DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CiBFISServerMCOperateStatiomApp
// �йش���ʵ�ֵ���Ϣ������� iBFIS.Server.MCOperateStatiom.cpp
//
class CISocObject;
class CiBFISServerMCOperateStatiomApp : public CWinApp
{
public:
	CiBFISServerMCOperateStatiomApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
extern "C"
{
    CISocObject* __stdcall iSOC_CreateObject();
}