// iBFIS.Server.CacheStation.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "iBFIS.Server.DataProviderStation.h"
#include "XhBFISServerDataProviderStationFactoryImp.h"

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

// CiBFISServerDataProviderStationApp

BEGIN_MESSAGE_MAP(CiBFISServerDataProviderStationApp, CWinApp)
END_MESSAGE_MAP()


// CiBFISServerDataProviderStationApp ����

CiBFISServerDataProviderStationApp::CiBFISServerDataProviderStationApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CiBFISServerDataProviderStationApp ����

CiBFISServerDataProviderStationApp theApp;


// CiBFISServerDataProviderStationApp ��ʼ��

BOOL CiBFISServerDataProviderStationApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

CISocObject* iSOC_CreateObject()
{
	static XhBFISServerDataProviderStationFactoryImp obj;
	return &obj;
}