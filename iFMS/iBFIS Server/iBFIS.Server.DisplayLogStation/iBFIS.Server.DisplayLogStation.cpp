// iBFIS.Server.DisplayLogStation.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "iBFIS.Server.DisplayLogStation.h"
#include "XhBFISDisplayLogFactoryImp.h"

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

// CiBFISServerDisplayLogStationApp

BEGIN_MESSAGE_MAP(CiBFISServerDisplayLogStationApp, CWinApp)
END_MESSAGE_MAP()


// CiBFISServerDisplayLogStationApp ����

CiBFISServerDisplayLogStationApp::CiBFISServerDisplayLogStationApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CiBFISServerDisplayLogStationApp ����

CiBFISServerDisplayLogStationApp theApp;


// CiBFISServerDisplayLogStationApp ��ʼ��

BOOL CiBFISServerDisplayLogStationApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

CISocObject* __stdcall iSOC_CreateObject()
{
	static XhBFISDisplayLogFactoryImp obj;
	return &obj;
}
