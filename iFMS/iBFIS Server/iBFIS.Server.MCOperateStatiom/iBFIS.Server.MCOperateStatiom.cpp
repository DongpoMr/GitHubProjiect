// iBFIS.Server.MCOperateStatiom.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "iBFIS.Server.MCOperateStatiom.h"
#include "XhBFISMCOperateStatiomFactoryImp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CiBFISServerMCOperateStatiomApp

BEGIN_MESSAGE_MAP(CiBFISServerMCOperateStatiomApp, CWinApp)
END_MESSAGE_MAP()


// CiBFISServerMCOperateStatiomApp ����

CiBFISServerMCOperateStatiomApp::CiBFISServerMCOperateStatiomApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CiBFISServerMCOperateStatiomApp ����

CiBFISServerMCOperateStatiomApp theApp;


// CiBFISServerMCOperateStatiomApp ��ʼ��

BOOL CiBFISServerMCOperateStatiomApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
extern "C"
{
    CISocObject* __stdcall iSOC_CreateObject()
    {
        static XhBFISMCOperateStatiomFactoryImp obj;
        return &obj;
    }
}
