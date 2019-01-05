
// iBFIS Server.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "iBFIS Server.h"
#include "iBFIS ServerDlg.h"
#include "iSOC_LoginModule.h"
#include "iSOC_MonFactoryManagement.h"
#include "tlhelp32.h"
#include "IcmsP_Utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ONE_APP_CHECK
// CiBFISServerApp

BEGIN_MESSAGE_MAP(CiBFISServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CiBFISServerApp ����

CiBFISServerApp::CiBFISServerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CiBFISServerApp ����

CiBFISServerApp theApp;


// CiBFISServerApp ��ʼ��

BOOL CiBFISServerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
#ifdef ONE_APP_CHECK
    if (CheckIsRun())
    {
        AfxMessageBox("��⵽��ͬ�����Ѿ�����,�����˳�!!!");
        exit(0);
    }
#endif

	iSOC_MonFactoryManagement fmt;
	fmt.AddSearchDll("\\ibfis.server.*.dll");
	fmt.InitFactories();

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CiBFISServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL CiBFISServerApp::CheckIsRun()
{
    CString strProcessName(AfxGetAppName());
    TTRACE("%s:[%d] %s\r\n", __FUNCTION__, __LINE__, (LPCTSTR)strProcessName);
    strProcessName += _T(".exe");
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);
    DWORD MyProcID = GetCurrentProcessId();
    HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return FALSE;

    BOOL bMore = ::Process32First(hProcessSnap, &pe32);
    while (bMore)
    {
        if (pe32.th32ProcessID != MyProcID && strProcessName.Compare(pe32.szExeFile) == 0)
        {
            ::CloseHandle(hProcessSnap);
            return TRUE;
        }

        bMore = ::Process32Next(hProcessSnap, &pe32);
    }

    ::CloseHandle(hProcessSnap);
    return FALSE;
}

