// CiBFISSererConf.cpp : 实现文件
//

#include "stdafx.h"
#include "iBFIS Server.h"
#include "CiBFISSererConf.h"
#include "afxdialogex.h"


// CiBFISSererConf 对话框

IMPLEMENT_DYNAMIC(CiBFISSererConf, CDialogEx)

CiBFISSererConf::CiBFISSererConf(CWnd* pParent /*=NULL*/)
	: CDialogEx(CiBFISSererConf::IDD, pParent)
{

	m_strDatabaseName = _T("ibfis");
	m_strDatabasePort = _T("3306");
	m_strDatabasePwd = _T("sobey");
	m_strDatabaseUser = _T("root");
	m_strListenPort = _T("9989");
	m_strServerPort = _T("9989");
	m_strSMSPort = _T("5150");
	m_strSMSPwd = _T("123");
	m_strSMSUser = _T("admin");
	m_strSyncInterval = _T("10");
	m_bDefault = false;
	m_bSave = true;
	//  m_dwDatabaseIP = 0;
	//  m_dwServerIP = 0;
	//  m_dwSMSIP = 0;
}

CiBFISSererConf::~CiBFISSererConf()
{
}

void CiBFISSererConf::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO_APPTYPE, m_comboAppType);
	DDX_Text(pDX, IDC_EDIT_DATABASE_NAME, m_strDatabaseName);
	DDX_Text(pDX, IDC_EDIT_DATABASE_PORT, m_strDatabasePort);
	DDX_Text(pDX, IDC_EDIT_DATABASE_PWD, m_strDatabasePwd);
	DDX_Text(pDX, IDC_EDIT_DATABASE_USER, m_strDatabaseUser);
	DDX_Text(pDX, IDC_EDIT_LISTEN_PORT, m_strListenPort);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_strServerPort);
	DDX_Text(pDX, IDC_EDIT_SMS_PORT, m_strSMSPort);
	DDX_Text(pDX, IDC_EDIT_SMS_PWD, m_strSMSPwd);
	DDX_Text(pDX, IDC_EDIT_SMS_USER, m_strSMSUser);
	DDX_Text(pDX, IDC_EDIT_SYNC_INTERVAL, m_strSyncInterval);
	DDX_Control(pDX, IDC_IP_DATABASE, m_ctrlDatabaseIP);
	DDX_Control(pDX, IDC_IP_SERVER, m_ctrlServerIP);
	DDX_Control(pDX, IDC_IP_SMS, m_ctrlSMSIP);
	//  DDX_IPAddress(pDX, IDC_IP_DATABASE, m_dwDatabaseIP);
	//  DDX_IPAddress(pDX, IDC_IP_SERVER, m_dwServerIP);
	//  DDX_IPAddress(pDX, IDC_IP_SMS, m_dwSMSIP);
	DDX_Control(pDX, IDC_EDIT_DATABASE_PORT, m_ctrlDBPort);
	DDX_Control(pDX, IDC_EDIT_LISTEN_PORT, m_ctrlListenPort);
	DDX_Control(pDX, IDC_EDIT_SMS_PORT, m_ctrlSMSPort);
	DDX_Control(pDX, IDC_EDIT_SERVER_PORT, m_ctrlServerPort);
}


BEGIN_MESSAGE_MAP(CiBFISSererConf, CDialogEx)
	//ON_CBN_SELCHANGE(IDC_COMBO_APPTYPE, &CiBFISSererConf::OnSelchangeComboApptype)
	ON_BN_CLICKED(IDOK, &CiBFISSererConf::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CiBFISSererConf::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CiBFISSererConf 消息处理程序


BOOL CiBFISSererConf::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
// 	m_comboAppType.Clear();
// 	m_comboAppType.InsertString(0,"分行");
// 	m_comboAppType.InsertString(1,"支行");
	if (!m_bDefault)
	{
		((CButton*)(GetDlgItem(IDC_CHECK1)))->SetCheck(0);
		BYTE p1 = 127,p2 = 0,p3 = 0,p4 = 1;
		m_ctrlServerIP.SetAddress(p1,p2,p3,p4);
		m_ctrlDatabaseIP.SetAddress(p1,p2,p3,p4);
		m_ctrlSMSIP.SetAddress(p1,p2,p3,p4);
	}
	else
	{
		//m_comboAppType.SetCurSel(m_nAppType - 1);
		((CButton*)(GetDlgItem(IDC_CHECK1)))->SetCheck(m_nAppType - 1);
		bool bShow = (m_nAppType == 1 ? false:true);
		((CIPAddressCtrl*)GetDlgItem(IDC_IP_SERVER))->EnableWindow(bShow);
		((CEdit*)GetDlgItem(IDC_EDIT_SERVER_PORT))->EnableWindow(bShow);
		//((CEdit*)GetDlgItem(IDC_EDIT_LISTEN_PORT))->EnableWindow(bShow);
		unsigned char* pServerIP = (unsigned char*)&m_dwServerIP;
		m_ctrlServerIP.SetAddress(*pServerIP,*(pServerIP+1),*(pServerIP+2),*(pServerIP+3));
		unsigned char* pDatabaseIP = (unsigned char*)&m_dwDatabaseIP;
		m_ctrlDatabaseIP.SetAddress(*pDatabaseIP,*(pDatabaseIP+1),*(pDatabaseIP+2),*(pDatabaseIP+3));
		unsigned char* pSMSIP = (unsigned char*)&m_dwSMSIP;
		m_ctrlSMSIP.SetAddress(*pSMSIP,*(pSMSIP+1),*(pSMSIP+2),*(pSMSIP+3));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CiBFISSererConf::DefaultServerConfig(const ST_ServerConf& stInfo,bool bDefault)
{
	m_nAppType = stInfo.nAppType;
	m_strListenPort.Format("%d",stInfo.nListenPort);
	m_strSyncInterval.Format("%d",stInfo.nSyncInterval);
	m_dwServerIP = inet_addr(stInfo.strServerIP.c_str());
	m_strServerPort.Format("%d",stInfo.nServerPort);
	m_dwDatabaseIP = inet_addr(stInfo.strDatabaseIP.c_str());
	m_strDatabasePort.Format("%d",stInfo.nDatabasePort);
	m_strDatabaseUser.Format("%s",stInfo.strDatabaseUsername.c_str());
	m_strDatabasePwd.Format("%s",stInfo.strDatabasePwd.c_str());
	m_strDatabaseName.Format("%s",stInfo.strDatabaseName.c_str());
	m_dwSMSIP = inet_addr(stInfo.strSMSIP.c_str());
	m_strSMSPort.Format("%d",stInfo.nSMSPort);
	m_strSMSUser.Format("%s",stInfo.strSMSUsername.c_str());
	m_strSMSPwd.Format("%s",stInfo.strSMSPwd.c_str());
	m_bDefault = bDefault;
	return TRUE;
}

// void CiBFISSererConf::OnSelchangeComboApptype()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	int nSel = m_comboAppType.GetCurSel();
// 	bool bShow = (nSel == 0 ? true : false);
// 	((CEdit*)GetDlgItem(IDC_EDIT_LISTEN_PORT))->EnableWindow(bShow);
// }

bool CiBFISSererConf::CheckPort(int nPort, CWnd* pWnd)
{
	bool bOk = true;
	if (nPort < 1024 || nPort > 65535)
	{
		AfxMessageBox("端口范围为[1024,65535]");
		pWnd->SetFocus();
		bOk = false;
	}
	return bOk;
}

void CiBFISSererConf::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (!CheckPort(atoi(m_strDatabasePort),&m_ctrlDBPort) || 
		!CheckPort(atoi(m_strListenPort), &m_ctrlListenPort)||
		!CheckPort(atoi(m_strServerPort), &m_ctrlServerPort)||
		!CheckPort(atoi(m_strSMSPort), &m_ctrlSMSPort))
	{
		return;
	}
	//m_nAppType = m_comboAppType.GetCurSel() + 1;
 	m_ctrlServerIP.GetAddress(m_dwServerIP);
 	m_ctrlDatabaseIP.GetAddress(m_dwDatabaseIP);
 	m_ctrlSMSIP.GetAddress(m_dwSMSIP);
	m_bSave = true;
	CDialogEx::OnOK();
}

BOOL CiBFISSererConf::GetServerConfig(ST_ServerConf& stInfo)
{
	if (!m_bSave)return FALSE;
	stInfo.nAppType = m_nAppType;
	stInfo.nListenPort = atoi(m_strListenPort);
	stInfo.nSyncInterval = atoi(m_strSyncInterval);
	CString strTemp;
	unsigned char* pServerIP = (unsigned char*)&m_dwServerIP;
	strTemp.Format("%u.%u.%u.%u",*(pServerIP+3),*(pServerIP+2),*(pServerIP+1),*(pServerIP));
	//strTemp.Format("%u.%u.%u.%u",*(pServerIP),*(pServerIP+1),*(pServerIP+2),*(pServerIP+3));
	stInfo.strServerIP = strTemp;
	stInfo.nServerPort = atoi(m_strServerPort);
	unsigned char* pDatabaseIP = (unsigned char*)&m_dwDatabaseIP;
	strTemp.Format("%u.%u.%u.%u",*(pDatabaseIP+3),*(pDatabaseIP+2),*(pDatabaseIP+1),*(pDatabaseIP));
	//strTemp.Format("%u.%u.%u.%u",*(pDatabaseIP),*(pDatabaseIP+1),*(pDatabaseIP+2),*(pDatabaseIP+3));
	stInfo.strDatabaseIP = strTemp;
	stInfo.nDatabasePort = atoi(m_strDatabasePort);
	stInfo.strDatabaseUsername = m_strDatabaseUser;
	stInfo.strDatabasePwd = m_strDatabasePwd;
	stInfo.strDatabaseName = m_strDatabaseName;
	unsigned char* pSMSIP = (unsigned char*)&m_dwSMSIP;
	strTemp.Format("%u.%u.%u.%u",*(pSMSIP+3),*(pSMSIP+2),*(pSMSIP+1),*(pSMSIP));
	//strTemp.Format("%u.%u.%u.%u",*(pSMSIP),*(pSMSIP+1),*(pSMSIP+2),*(pSMSIP+3));
	stInfo.strSMSIP = strTemp;
	stInfo.nSMSPort = atoi(m_strSMSPort);
	stInfo.strSMSUsername = m_strSMSUser;
	stInfo.strSMSPwd = m_strSMSPwd;
	return TRUE;
}

void CiBFISSererConf::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCheck = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	BOOL bEnable = (m_nAppType = nCheck == 1 ? 2 : 1)== 1 ? FALSE : TRUE;
	((CIPAddressCtrl*)GetDlgItem(IDC_IP_SERVER))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_SERVER_PORT))->EnableWindow(bEnable);
}


BOOL CiBFISSererConf::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == VK_RETURN || pMsg->message == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
