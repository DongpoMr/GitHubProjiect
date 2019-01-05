#pragma once
#include <string>
#include "afxwin.h"

struct ST_ServerConf
{
	int	nAppType;
	int nListenPort;
	int nSyncInterval;
	std::string strServerIP;
	int nServerPort;
	std::string strDatabaseIP;
	int nDatabasePort;
	std::string strDatabaseUsername;
	std::string strDatabasePwd;
	std::string strDatabaseName;
	std::string strSMSIP;
	int nSMSPort;
	std::string strSMSUsername;
	std::string strSMSPwd;
};
// CiBFISSererConf 对话框

class CiBFISSererConf : public CDialogEx
{
	DECLARE_DYNAMIC(CiBFISSererConf)

public:
	CiBFISSererConf(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CiBFISSererConf();

// 对话框数据
	enum { IDD = IDD_DLG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	BOOL DefaultServerConfig(const ST_ServerConf& stInfo,bool bDefault);
	BOOL GetServerConfig(ST_ServerConf& stInfo);

private:
	bool CheckPort(int nPort,CWnd* pWnd);

	//CComboBox m_comboAppType;
	CString m_strDatabaseName;
	CString m_strDatabasePort;
	CString m_strDatabasePwd;
	CString m_strDatabaseUser;
	CString m_strListenPort;
	CString m_strServerPort;
	CString m_strSMSPort;
	CString m_strSMSPwd;
	CString m_strSMSUser;
	CString m_strSyncInterval;
	CIPAddressCtrl m_ctrlDatabaseIP;
	CIPAddressCtrl m_ctrlServerIP;
	CIPAddressCtrl m_ctrlSMSIP;
	
	int		m_nAppType;
	DWORD	m_dwServerIP;
	DWORD	m_dwDatabaseIP;
	DWORD	m_dwSMSIP;
	bool	m_bDefault;
	bool	m_bSave;
public:
	//afx_msg void OnSelchangeComboApptype();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_ctrlDBPort;
	CEdit m_ctrlListenPort;
	CEdit m_ctrlSMSPort;
	CEdit m_ctrlServerPort;
};
