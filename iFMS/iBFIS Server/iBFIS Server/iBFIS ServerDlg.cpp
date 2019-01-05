
// iBFIS ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iBFIS Server.h"
#include "iBFIS ServerDlg.h"
#include "XhLogDisplayInterface.h"
#include "iSOC_MonFactoryManagement.h"
#include "iBFISDBOperation.h"
#include "IThread.h"
#include "afxdialogex.h"
#include "SBE_SoftEncryptSys.h"
#include "iFVR_Configuration.h"
#include "iFVR_Utility.h"
#include "IcmsP_XmlParser.h"
#include <windows.h>
#include <stdint.h>
#include <tlhelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#define USE_USB_HARDWARD_LOCK_LICESENCE //���ܹ����غ�
//// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CiBFISServerDlg �Ի���




CiBFISServerDlg::CiBFISServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CiBFISServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nSyncInterval = 5;
	m_pServer = nullptr;
	m_pClient = nullptr;
	m_pThread = nullptr;
	m_strDBName = _T("ibfis");
	m_strLocalBranchId = _T("");
    m_pMigrateStation = nullptr;
    m_pTimer = nullptr;
}

CiBFISServerDlg::~CiBFISServerDlg()
{
    if (m_pTimer)
    {
        m_pTimer->KillTimer(-1);
        iSOC_MonFactoryManagement fmt;
        fmt.ReleaseObject(reinterpret_cast<CISocObject**>(&m_pTimer), __FUNCTION__);
    }
}

void CiBFISServerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LOGLIST, m_LogList);
    //  DDX_Control(pDX, IDC_MENUBTN, m_menuBtn);
    DDX_Control(pDX, IDC_TASKPLAN_LIST, m_listTaskPlan);
    DDX_Control(pDX, IDC_CONNECTION_LIST, m_connectionList);
}

BEGIN_MESSAGE_MAP(CiBFISServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_SUBMENU1,&CiBFISServerDlg::OnSetConfig)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_LOGLIST, &CiBFISServerDlg::OnNMCustomdrawLoglist)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CiBFISServerDlg ��Ϣ�������

BOOL CiBFISServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CMenu* pMenu = new CMenu;
	pMenu->LoadMenuA(IDR_MENU1);
	SetMenu(pMenu);

	LV_COLUMN lvc;
	lvc.mask = LVCF_TEXT|LVCF_SUBITEM/*|LVCF_ORDER*/|LVCF_WIDTH;
	LONG style = m_LogList.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	style |= LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB;
	m_LogList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE,0,static_cast<LPARAM>(style));
	m_LogList.InsertColumn(0, _T("ϵͳʱ��"), LVCFMT_LEFT, 150, 0);
	m_LogList.InsertColumn(1, _T("�¼���Դ"), LVCFMT_LEFT, 150, 0);
	m_LogList.InsertColumn(2, _T("�¼�����"), LVCFMT_LEFT, 350, 1);
	m_LogList.InsertColumn(3, _T("����ԭ��"), LVCFMT_LEFT, 150, 1);
	m_LogList.InsertColumn(4, _T("�¼�״̬"), LVCFMT_CENTER, 100,1);
	m_displayLogManager.SetDisplayLogList(&m_LogList);

    m_listTaskPlan.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, static_cast<LPARAM>(style));
    m_listTaskPlan.InsertColumn(0, _T("�ƻ�����ID"), LVCFMT_LEFT, 300, 0);
    m_listTaskPlan.InsertColumn(1, _T("��ʼʱ��"), LVCFMT_LEFT, 150, 0);
    m_listTaskPlan.InsertColumn(2, _T("����ʱ��"), LVCFMT_LEFT, 150, 1);
    m_listTaskPlan.InsertColumn(3, _T("����״̬"), LVCFMT_LEFT, 150, 0);
    m_displayLogManager.SetDisplayTaskPlanList(&m_listTaskPlan);

    m_connectionList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, static_cast<LPARAM>(style));
    m_connectionList.InsertColumn(0, _T("�û�ID"), LVCFMT_LEFT, 300, 0);
    m_connectionList.InsertColumn(1, _T("�û���"), LVCFMT_LEFT, 150, 0);
    m_connectionList.InsertColumn(2, _T("IP"), LVCFMT_LEFT, 150, 1);
    m_displayLogManager.SetDisplayConnectionList(&m_connectionList);

    iSOC_MonFactoryManagement fmt;

#ifdef USE_USB_HARDWARD_LOCK_LICESENCE
    TCHAR szConfigFile[MAX_PATH] = { 0 };
    sprintf_s(szConfigFile, "%s\\Config\\iBFIS.Server.Config.ini", GetWorkingDirectory());
    int nDogModel = GetPrivateProfileInt(_T("dog_setting"), _T("DongleMode"), 0, szConfigFile);
    if (nDogModel == 1)
    {
        m_bDogModel = TRUE;
    }
    else
    {
        m_bDogModel = FALSE;
    }

    m_pTimer = (ITimer *)fmt.CreateObject(OBJECT_TYPE_TIMER, "", __FUNCTION__);
    if (!m_pTimer)
    {
        TTRACE("%s[%d]:������ʱ��ʧ��\r\n", __FUNCTION__, __LINE__);
        return -2;
    }
    else
    {
        m_pTimer->SetTimer(this, 101, m_bDogModel ? 60 * 60 * 24 * 1000 : 60 * 60 * 2 * 1000);//�����1����һ�Σ�Ӳ����2Сʱ���һ��
    }
    OnTimer(101);   //�ȼ��һ��
#endif
    

	m_pThread = static_cast<IThread*>(fmt.CreateObject(OBJECT_TYPE_THREAD, __FUNCTION__, _T("")));
	if (!m_pThread)
	{
		DISPLAY_LOG(_T("��ʼ��"), _T("������ʼ���߳�ʧ�ܣ��������ó���..."),_T(""), _T(""), 0);
	}
	else
	{
		m_pThread->SetRunAbleInterface(this);
		m_pThread->Start();
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CiBFISServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CiBFISServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CiBFISServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CiBFISServerDlg::ReadConfiguration()
{
    iFVR_Configuration config;

    m_nAppType      = config.GetInt("LocalSet",  "AppType",      1);	//1��û���ϼ� 2�����ϼ�
    m_nListenPort   = config.GetInt("LocalSet",  "ListenPort",   9989);
	m_nMigrateCount  = config.GetInt("LocalSet", "MigrateCount",   5);
    m_nServerPort   = config.GetInt("Server",    "ServerPort",   0);
    m_nDBPort       = config.GetInt("DataBase",  "DataBasePort", 3306);
    m_nSyncInterval = config.GetInt("LocalSet",  "SyncInterval", 5);
    m_nSMSPort      = config.GetInt("SMS",       "SMSPort",      5150);

    m_strServerIP    = config.GetString("Server",   "ServerIP",     "").c_str();    
    m_strDBIp        = config.GetString("DataBase", "DataBaseIP",   "").c_str();    
    m_strDBUserName  = config.GetString("DataBase", "DataBaseUser", "").c_str();
    m_strDBPwd       = config.GetString("DataBase", "DataBasePwd",  "").c_str();
    m_strDBName      = config.GetString("DataBase", "DataBaseName", "").c_str();    
    m_strSMSIp       = config.GetString("SMS",      "SMSIP",        "").c_str();    
    m_strSMSUserName = config.GetString("SMS",      "SMSUser",      "").c_str();
    m_strSMSPwd      = config.GetString("SMS",      "SMSPwd",       "").c_str();

	TTRACE("AppType:%d,ListenPort:%d,ServerPort:%d,DBPort:%d,SyncInterval:%d,SMSPort:%d,ServerIP:%s,DBIP:%s,DBUser:%s,DBPwd:%s\
		   DBName:%s,SMSIP:%s,SMSUser:%s,SMSPwd:%s \r\n",m_nAppType,m_nListenPort,m_nServerPort,m_nDBPort,m_nSyncInterval,
		   m_nSMSPort, m_strServerIP, m_strDBIp, m_strDBUserName, m_strDBPwd, m_strDBName, m_strSMSIp, m_strSMSUserName, m_strSMSPwd);
    return true;
}

bool CiBFISServerDlg::WriteConfiguration()
{
    iFVR_Configuration config;
    config.SetInt("LocalSet",  "AppType",      m_nAppType     );
    config.SetInt("LocalSet",  "ListenPort",   m_nListenPort  );
	config.SetInt("LocalSet",  "MigrateCount", m_nMigrateCount  );
    config.SetInt("Server",    "ServerPort",   m_nServerPort );
    config.SetInt("DataBase",  "DataBasePort", m_nDBPort      );
    config.SetInt("LocalSet",  "SyncInterval", m_nSyncInterval);
    config.SetInt("SMS",       "SMSPort",      m_nSMSPort     );

    config.SetString("Server",   "ServerIP",     static_cast<LPCTSTR>(m_strServerIP)   );    
    config.SetString("DataBase", "DataBaseIP",   static_cast<LPCTSTR>(m_strDBIp)       );    
    config.SetString("DataBase", "DataBaseUser", static_cast<LPCTSTR>(m_strDBUserName) );
    config.SetString("DataBase", "DataBasePwd",  static_cast<LPCTSTR>(m_strDBPwd)      );
    config.SetString("DataBase", "DataBaseName", static_cast<LPCTSTR>(m_strDBName)     );    
    config.SetString("SMS",      "SMSIP",        static_cast<LPCTSTR>(m_strSMSIp)      );    
    config.SetString("SMS",      "SMSUser",      static_cast<LPCTSTR>(m_strSMSUserName));
    config.SetString("SMS",      "SMSPwd",       static_cast<LPCTSTR>(m_strSMSPwd)     );
    config.Save();
	return true;
}

void CiBFISServerDlg::Run()
{
	//��ȡ�����ļ�
	DISPLAY_LOG(_T("��ʼ��"), _T("��ʼ��ȡ�����ļ�..."),_T(""), _T(""), 1);
	ReadConfiguration();

	iSOC_MonFactoryManagement fmt;
	int nRet = -1;
	CString strDBPort;
	STRY;
	//�������ݿ�
 	IBFISDBOperation* pDBOper = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, _T(""),__FUNCTION__));
 	if (!pDBOper)
 	{
 		DISPLAY_LOG(_T("��ʼ��"), _T("�������ݿ����ʧ��"),_T("�������ó�������"), _T(""), 0);
 		return;
 	}
 	strDBPort.Format(_T("%d"), m_nDBPort);
 	DISPLAY_LOG(_T("��ʼ��"), _T("�����������ݿ�..."),_T(""), _T(""), 1);
 	pDBOper->SetDataBaseName(static_cast<LPCTSTR>(m_strDBName));
	do 
	{
		nRet = pDBOper->ConnectToDataBase(static_cast<LPCTSTR>(m_strDBIp), static_cast<LPCTSTR>(strDBPort), static_cast<LPCTSTR>(m_strDBUserName), static_cast<LPCTSTR>(m_strDBPwd));
		if (nRet <= 0)
		{
			CString strDes;
			strDes.Format(_T("�������ݿ�[%s:%d]ʧ��,�ȴ�����..."), static_cast<const char*>(m_strDBIp), m_nDBPort);
			DISPLAY_LOG(_T("��ʼ��"), static_cast<LPCTSTR>(strDes),_T(""), _T(""), 0);
			Sleep(1*1000);
			ReadConfiguration();
		}
		else
		{
			CString strDes;
			strDes.Format(_T("�������ݿ�[%s:%d]�ɹ�"), static_cast<const char*>(m_strDBIp), m_nDBPort);
			DISPLAY_LOG(_T("��ʼ��"), static_cast<LPCTSTR>(strDes),_T(""), _T(""), 1);
		}

	} while (nRet <= 0);

	pDBOper->KeepConnect();
	ST_BranchInfo stInfo;
	if(pDBOper && pDBOper->GetLocalBranchInfo(stInfo) == QuerySuccessWithResult)
	{
		m_strLocalBranchId = stInfo.strBranchId.c_str();
		CString strTitle = _T("iFMS");
		strTitle.AppendFormat(_T(" - %s"), stInfo.strName.c_str());
		this->SetWindowText(strTitle);
	}
	//��¼MC
	IBFISMCOperateStation *pMcOper = static_cast<IBFISMCOperateStation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_MCOPERATESTATION, _T(""), __FUNCTION__));
	if (!pMcOper)
	{
		DISPLAY_LOG(_T("��ʼ��"), _T("����MC��������ʧ��"), _T("�������ó�������"), _T(""), 0);
		return;
	}
    do 
    {
        nRet = pMcOper->LoginLocalMC(static_cast<string>(m_strSMSIp), m_nSMSPort, static_cast<string>(m_strSMSUserName), static_cast<string>(m_strSMSPwd));
        if (nRet <= 0)
        {
            DISPLAY_LOG(_T("��ʼ��"), _T("��¼MCʧ��"), _T(""), _T(""), 0);
            Sleep(2*1000);
        }
    } while (nRet <= 0);

    LONG_PTR pMCSession;
    pMcOper->GetMCSession(pMCSession);
	DISPLAY_LOG(_T("��ʼ��"), _T("��¼MC�ɹ�!"), _T(""), _T(""), 1);
	{
		nRet = pMcOper->GetLoclMCInfo(m_stLocalMcInfo);
		if (nRet <= 0 || m_stLocalMcInfo.strServerICMSSign == "")
		{
			DISPLAY_LOG(_T("��ʼ��"), _T("��ȡ����MC��Ϣʧ��"), _T("�������ó�������"), _T(""), 0);
			return;
		}
	}
	TTRACE("����MC��ϢUserICMSSign:%s \r\n",m_stLocalMcInfo.strUserICMSSign);
	pDBOper->SetLocalBranchId(m_stLocalMcInfo.strServerICMSSign);
    pDBOper->GetMCSessoon(pMCSession);
	SCATCH;

	STRY;
	m_pServer = static_cast<IBFISCommunicateSyncServer*>(fmt.CreateObject(OBJECT_TYPE_BFIS_COMMUNICATESYNCSERVER, __FUNCTION__, _T("")));
	if (!m_pServer)
	{
		DISPLAY_LOG(_T("��ʼ��"), _T("��������������ʧ��"),_T("�������ó�������"), _T(""), 0);
		return;
	}
	m_pServer->CheckIsTopServer(m_nAppType);
	m_pServer->Init();
	LONG lListenIP = htonl(inet_addr("0.0.0.0")); 
 	if (m_nAppType == AppType_Client)
 	{
 		LONG lServerIP = htonl(inet_addr(static_cast<LPCTSTR>(m_strServerIP)));
         std::vector<std::string> vecLocalIps = iFVR_Utility::LoclIpAddress();
         vecLocalIps.push_back("127.0.0.1");
         vecLocalIps.push_back("0.0.0.0");
         for each (const auto& var in vecLocalIps)
         {
             if (lServerIP == htonl(inet_addr(var.c_str())))//����ϼ�IP�Ǳ���IP����ͬ��
             {
#if 1
				 int ret = IsStartMonitoringProcess();
 				 m_pServer->DoListenOn(lListenIP, m_nListenPort, ret);
                 DISPLAY_LOG("��ʼ��", "��ʼ�����", "", "", 1);
                 return;
#endif
             }
         }
 		m_pClient = static_cast<IBFISSyncClient*>(fmt.CreateObject(OBJECT_TYPE_BFISSYNC_CLIENT, __FUNCTION__, _T("")));
 		if (!m_pClient)
 		{
 			DISPLAY_LOG(_T("��ʼ��"), _T("��������������ʧ��"),_T("�������ó�������"), _T(""), 0);
 			return;
 		}
		m_pClient->SetLocalUrl(vecLocalIps[0]);
 		m_pClient->Init(static_cast<LPCTSTR>(m_strDBIp),static_cast<LPCTSTR>(strDBPort),static_cast<LPCTSTR>(m_strDBUserName),static_cast<LPCTSTR>(m_strDBPwd));
 		m_pClient->SetSyncInterval(m_nSyncInterval * 60);
 		int nRet = m_pClient->DoConnect(lServerIP, m_nServerPort);
 		if (nRet != 0)
 		{
 			CString strDes;
 			strDes.Format(_T("���ӷ�����[%s:%d]ʧ��"), static_cast<const char*>(m_strServerIP), m_nServerPort);
 			DISPLAY_LOG(_T("��ʼ��"), static_cast<LPCTSTR>(strDes),_T(""), _T(""), 0);
             //return ;
 		}
		Sleep(3000);
        m_pClient->StartSync();
 	}
	
    m_pMigrateStation = static_cast<IMigrateTaskStation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_MIGRATETASKSTATION, "", __FUNCTION__));
    if (!m_pMigrateStation)
    {
        DISPLAY_LOG(_T("��ʼ��"), _T("�������ݹ���ģ��ʧ��"), _T("�������ó�������"), _T(""), 0);
        return;
    }
    IBFISTaskStation *pTmp = static_cast<IBFISTaskStation*>(m_pMigrateStation);
    int nInit = pTmp->InitStation();
    if (nInit <= 0)
    {
        DISPLAY_LOG(_T("��ʼ��"), _T("��ʼ�����ݹ���ģ��ʧ��"), _T("���ݹ���ģ�鲻�߱�����"), _T(""), 0);
        //return;
    }
	int ret = IsStartMonitoringProcess();
    int nRet = m_pServer->DoListenOn(lListenIP, m_nListenPort, ret);
	if (nRet < 0)
	{
		DISPLAY_LOG("��ʼ��","����ʧ��","","",1);
	}
	DISPLAY_LOG("��ʼ��","��ʼ�����","","",1);
	SCATCH;
}
void CiBFISServerDlg::ShowClientData(bool bShow)
{

}

int CiBFISServerDlg::IsStartMonitoringProcess()
{
	iCMSP_XmlParser xmlParser;
	CString strFMSConfigPath = GetWorkingDirectory();
	strFMSConfigPath += "\\Config\\iFMSConfig.xml";
	bool bRet = xmlParser.Load(strFMSConfigPath.GetBuffer(0));
	if (true == bRet)
	{
		TTRACE(" �ɹ����ز�������ļ�\r\n");
		if (xmlParser.FindElem("FMS"))
		{
			xmlParser.IntoElem();
			if (xmlParser.FindElem("ServerMonitoring"))
			{
				int nEnable = xmlParser.GetAttribInt("enable");
				if (nEnable == 1)
				{
					HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
					if (INVALID_HANDLE_VALUE == hSnapshot) {
						return -1;
					}
					std::string strProcessName("iFMS ServerMonitoring.exe");
					PROCESSENTRY32 pe = { sizeof(pe) };
					for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe))
					{
						if (strProcessName.compare(pe.szExeFile) == 0)
						{
							CloseHandle(hSnapshot);
							return 1;
						}
					}

					CString strModuleFilePath = GetWorkingDirectory();
					strModuleFilePath += "\\iFMS ServerMonitoring.exe";
					STARTUPINFO si;
					PROCESS_INFORMATION pi;
					ZeroMemory(&si, sizeof(si));
					si.dwFlags = STARTF_USESHOWWINDOW;
					si.wShowWindow = SW_HIDE;
					si.cb = sizeof(si);
					ZeroMemory(&pi, sizeof(pi));
					//WinExec((LPTSTR)(LPCTSTR)strModuleFilePath, SW_HIDE);
					bool bRet = CreateProcess(NULL, (LPTSTR)(LPCTSTR)strModuleFilePath, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
					TTRACE(" ��������״̬[%d] Name[%s]\r\n", bRet ? 1 : GetLastError(), strModuleFilePath.GetBuffer(0));
					return bRet ? 1 : 0;
				}
			}
		}
	}
	else
	{
		TTRACE(" %s ���ز�������ļ�ʧ��[%s]\r\n", __FUNCTION__, strFMSConfigPath.GetBuffer(0));
	}
	return 0;
}


void CiBFISServerDlg::OnSetConfig()
{
	ReadConfiguration();
	CiBFISSererConf confDlg;
	ST_ServerConf stInfo;
	ZeroMemory(&stInfo,sizeof(ST_ServerConf));
	Var2Struct(stInfo);
	confDlg.DefaultServerConfig(stInfo,true);
	if(confDlg.DoModal() == IDOK)
	{
		ZeroMemory(&stInfo,sizeof(ST_ServerConf));
		confDlg.GetServerConfig(stInfo);
		Struct2Var(stInfo);
		WriteConfiguration();
	}
}

void CiBFISServerDlg::Struct2Var(const ST_ServerConf& stInfo)
{
	m_nAppType = stInfo.nAppType;
	m_nListenPort = stInfo.nListenPort;
	m_nSyncInterval = stInfo.nSyncInterval;
	m_strServerIP.Format("%s",stInfo.strServerIP.c_str());
	m_nServerPort = stInfo.nServerPort;
	m_strDBIp.Format("%s",stInfo.strDatabaseIP.c_str());
	m_nDBPort = stInfo.nDatabasePort;
	m_strDBUserName.Format("%s",stInfo.strDatabaseUsername.c_str());
	m_strDBPwd.Format("%s",stInfo.strDatabasePwd.c_str());
	m_strDBName.Format("%s",stInfo.strDatabaseName.c_str());
	m_strSMSIp.Format("%s",stInfo.strSMSIP.c_str());
	m_nSMSPort = stInfo.nSMSPort;
	m_strSMSUserName.Format("%s",stInfo.strSMSUsername.c_str());
	m_strSMSPwd.Format("%s",stInfo.strSMSPwd.c_str());
}

void CiBFISServerDlg::Var2Struct(ST_ServerConf& stInfo)
{
	stInfo.nAppType = m_nAppType;
	stInfo.nListenPort = m_nListenPort;
	stInfo.nSyncInterval = m_nSyncInterval;
	stInfo.strServerIP = m_strServerIP;
	stInfo.nServerPort = m_nServerPort;
	stInfo.strDatabaseIP = m_strDBIp;
	stInfo.nDatabasePort = m_nDBPort;
	stInfo.strDatabaseUsername = m_strDBUserName;
	stInfo.strDatabasePwd = m_strDBPwd;
	stInfo.strDatabaseName = m_strDBName;
	stInfo.strSMSIP = m_strSMSIp;
	stInfo.nSMSPort = m_nSMSPort;
	stInfo.strSMSUsername = m_strSMSUserName;
	stInfo.strSMSPwd = m_strSMSPwd;
}

void CiBFISServerDlg::OnTimer(IN ISOC_ID iTimerID)
{
    STRY;
#ifdef USE_USB_HARDWARD_LOCK_LICESENCE
    CString strResult;
    int nVersion;
    int nDayLeft = 0;
    int nCountLeft = 0;
    CComBSTR bstrExeDescript;
    LONGLONG llModuleInfo;
    std::vector<CString> vcProjectName;
    vcProjectName.push_back(_T("iNVS"));
    std::vector<CString>::iterator itProjectName = vcProjectName.begin();
    bool bIsSuccess = true;
    int nRet = 0;
    for (; itProjectName != vcProjectName.end(); itProjectName++)
    {
        nRet = CheckDogInfo(*itProjectName);
        if (nRet > 0)
            return;
    }

    switch (nRet)
    {
    case  -1:
    {
        strResult = _T("δע��");
        break;
    }
    case -2:
    {
        strResult = _T("�������ܹ�");
        break;
    }
    case -3:
    {
        strResult = _T("���ܹ���Ϣ����");
        break;
    }
    case -4:
    {
        strResult = _T("ʣ�����Ϊ0��");
        break;
    }
    case  -5:
    {
        strResult = _T("ʣ��ʱ��Ϊ0��");
        break;
    }
    }
    TTRACE(_T("Dog check finished: %d days left, %d times left!\r\n"), nDayLeft, nCountLeft);

    MessageBox(strResult, _T("Warning"), MB_OK | MB_ICONINFORMATION);
    if (m_bDogModel)
    {
        CString strFilePath;
        strFilePath.Format("%s\\SoftLicRegister.exe", GetWorkingDirectory());
        ShellExecute(NULL, "open", strFilePath, NULL, NULL, SW_SHOWNORMAL);
        TTRACE("%s[%d]:Dog check failed,exit!!", __FUNCTION__, __LINE__);
        exit(0);
        return;
    }
    else
    {
        TTRACE("%s[%d]:Dog check failed,exit!!", __FUNCTION__, __LINE__);
        exit(0);
        return;
    }

    return;

#endif
    SCATCH;
}

int CiBFISServerDlg::CheckDogInfo(CString strProductName)
{
    SB_DogSetProductName(strProductName.AllocSysString());
    SB_DogMode(m_bDogModel ? SBE_DOGMODE_SOFT : SBE_DOGMODE_MACRO);

    if (SB_DogCheck() <= 0)
    {
        TTRACE(_T("Check dog failed!\r\n"));
        if (m_bDogModel)
            return -1;
        return -2;
    }

    int nVersion;
    CComBSTR bstrExeDescript;
    LONGLONG llModuleInfo;
    int nRet = SB_DogVersion(nVersion, bstrExeDescript, llModuleInfo);
    if (nRet <= 0 || (CString(bstrExeDescript).CompareNoCase(strProductName) != 0))
    {
        return -3;
    }

    if (nVersion == SB_VERSION_DEMO)
    {
        int nCountLeft = 0;

        int nRet = SB_DogCountLeft(nCountLeft, TRUE);
        if (nRet > 0)
        {
            if (nCountLeft <= 0)
            {
                if (m_bDogModel)
                {
                    TTRACE("%s ��Ʒ����%s ʣ�����Ϊ0\r\n", __FUNCTION__, strProductName);
                    return -1;
                }
                return -4;
            }
        }

        int nDayLeft = 0;
        nRet = SB_DogDaysLeft(nDayLeft);
        if (nRet > 0)
        {
            if (nDayLeft <= 0)
            {
                if (m_bDogModel)
                {
                    TTRACE("%s ��Ʒ����%s ʣ������Ϊ0\r\n", __FUNCTION__, strProductName);
                    return -1;
                }
                return -5;
            }
        }
    }
    return 1;
}


void CiBFISServerDlg::OnNMCustomdrawLoglist(NMHDR *pNMHDR, LRESULT *pResult)
{
    //LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    *pResult = 0;

    NMLVCUSTOMDRAW* pNMCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
    
    if (CDDS_PREPAINT == pNMCD->nmcd.dwDrawStage)
    {
        *pResult = CDRF_NOTIFYITEMDRAW;
    }
    else if (CDDS_ITEMPREPAINT == pNMCD->nmcd.dwDrawStage)
    {
        *pResult = CDRF_NOTIFYSUBITEMDRAW;
    }
    else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pNMCD->nmcd.dwDrawStage)
    {
        COLORREF  clrNewTextColor, clrNewBkColor;
        int nItem = static_cast<int>(pNMCD->nmcd.dwItemSpec);
        if (m_LogList.GetItemData(nItem) == 0)
        {
            clrNewTextColor = RGB(255, 0, 0);
           // clrNewBkColor = RGB(255, 0, 0);
        }
        else
        {
            clrNewTextColor = RGB(0, 0, 0);
           // clrNewBkColor = RGB(255, 255, 255);
        }
        pNMCD->clrText = clrNewTextColor;
        //pNMCD->clrTextBk = clrNewBkColor;
        *pResult = CDRF_DODEFAULT;

    }
}


BOOL CiBFISServerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN || pMsg->message == VK_ESCAPE)
	{
		return TRUE;
	}
	return __super::PreTranslateMessage(pMsg);
}


void CiBFISServerDlg::OnClose()
{
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_pServer != nullptr)
	{
		m_pServer->StopListen();
		m_pServer->UnInit();
	}
	if (m_pClient != nullptr)
	{
		m_pClient->DoDisConnect();
		m_pClient->UnInit();
	}

    __super::OnClose();
}
