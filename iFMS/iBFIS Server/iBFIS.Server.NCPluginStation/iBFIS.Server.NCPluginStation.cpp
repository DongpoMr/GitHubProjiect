// iBFIS.Server.NCPluginStation.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "iBFIS.Server.NCPluginStation.h"
#include "xhBFISServerNCPluginFactoryImp.h"s

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

// CiBFISServerNCPluginStationApp

BEGIN_MESSAGE_MAP(CiBFISServerNCPluginStationApp, CWinApp)
END_MESSAGE_MAP()


// CiBFISServerNCPluginStationApp ����

CiBFISServerNCPluginStationApp::CiBFISServerNCPluginStationApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CiBFISServerNCPluginStationApp ����

CiBFISServerNCPluginStationApp theApp;


// CiBFISServerNCPluginStationApp ��ʼ��

BOOL CiBFISServerNCPluginStationApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C"
{
	CISocObject* __stdcall iSOC_CreateObject()
	{
		static xhBFISServerNCPluginFactoryImp obj;
		return &obj;
	}
}