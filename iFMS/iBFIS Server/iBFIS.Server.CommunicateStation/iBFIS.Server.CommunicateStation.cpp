// iBFIS.Server.CommunicateStation.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "iBFIS.Server.CommunicateStation.h"
#include "iSOCObject.h"
#include "XhBFISCommunicateStationFactoryImp.h"

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

// CiBFISServerCommunicateStationApp

BEGIN_MESSAGE_MAP(CiBFISServerCommunicateStationApp, CWinApp)
END_MESSAGE_MAP()


// CiBFISServerCommunicateStationApp ����

CiBFISServerCommunicateStationApp::CiBFISServerCommunicateStationApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CiBFISServerCommunicateStationApp ����

CiBFISServerCommunicateStationApp theApp;


// CiBFISServerCommunicateStationApp ��ʼ��

BOOL CiBFISServerCommunicateStationApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

CISocObject* iSOC_CreateObject()
{
	static XhBFISCommunicateStationFactoryImp obj;
	return &obj;
}