// iBFIS.Server.SyncStation.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "iBFIS.Server.SyncStation.h"
#include "iSOCObject.h"
#include "XhBFISServerSyncStationFactoryImp.h"

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

// CiBFISServerSyncStationApp

BEGIN_MESSAGE_MAP(CiBFISServerSyncStationApp, CWinApp)
END_MESSAGE_MAP()


// CiBFISServerSyncStationApp ����

CiBFISServerSyncStationApp::CiBFISServerSyncStationApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CiBFISServerSyncStationApp ����

CiBFISServerSyncStationApp theApp;


// CiBFISServerSyncStationApp ��ʼ��

BOOL CiBFISServerSyncStationApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

CISocObject* __stdcall iSOC_CreateObject()
{
	static XhBFISSyncStationFactoryImp obj;
	return &obj;
}