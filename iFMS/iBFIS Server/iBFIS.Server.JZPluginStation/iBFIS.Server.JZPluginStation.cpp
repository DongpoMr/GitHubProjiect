// iBFIS.Server.JZPluginStation.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "iBFIS.Server.JZPluginStation.h"
#include "xhBFISServerJZPluginFactoryImp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
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
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CiBFISServerJZPluginStationApp

BEGIN_MESSAGE_MAP(CiBFISServerJZPluginStationApp, CWinApp)
END_MESSAGE_MAP()


// CiBFISServerJZPluginStationApp ����

CiBFISServerJZPluginStationApp::CiBFISServerJZPluginStationApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CiBFISServerJZPluginStationApp ����

CiBFISServerJZPluginStationApp theApp;


// CiBFISServerJZPluginStationApp ��ʼ��

BOOL CiBFISServerJZPluginStationApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C"
{
	CISocObject* __stdcall iSOC_CreateObject()
	{
		static xhBFISServerJZPluginFactoryImp obj;
		return &obj;
	}
}
