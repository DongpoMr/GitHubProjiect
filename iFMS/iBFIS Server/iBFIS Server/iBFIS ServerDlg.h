
// iBFIS ServerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "XhDisplayLogManager.h"
#include "IBFISCommunicateSyncServer.h"
#include "IBFISSyncClient.h"
#include "IThread.h"
#include "IBFISMigrateTaskStation.h"
#include "CiBFISSererConf.h"
#include "ITimer.h"
#include <string>
#include "IBFISMCOperateStation.h"


#define WM_UPDATE_MESSAGE (WM_USER+200)
#define WM_USER_NOTIFYICON (WM_USER+10) 
// CiBFISServerDlg 对话框
class CiBFISServerDlg : public CDialogEx,public IRunable, public ITimerCallbackSkin
{
// 构造
public:
	CiBFISServerDlg(CWnd* pParent = NULL);	// 标准构造函数
    virtual ~CiBFISServerDlg();
// 对话框数据
	enum { IDD = IDD_IBFISSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSetConfig();
	afx_msg LRESULT OnUpdateMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNotifyMsg(WPARAM wparam, LPARAM lparam);
	afx_msg void changeMini();
//	afx_msg void OnClickedMenubtn();
	DECLARE_MESSAGE_MAP()

private:
	virtual void Run();
    virtual void OnTimer(IN ISOC_ID iTimerID);
    int CheckDogInfo(CString strProductName);
	void Struct2Var(const ST_ServerConf& stInfo);
	void Var2Struct(ST_ServerConf& stInfo);
	bool ReadConfiguration();
	bool WriteConfiguration();
	void ShowClientData(bool bShow);
	static UINT StartThread(LPVOID lpParam);
	void OnHandleMainBlock(LPVOID lpParam);
	int   IsStartMonitoringProcess();
	XhDisplayLogManager m_displayLogManager;
	int m_nAppType;
	CString m_strServerIP;
	int m_nMigrateCount;
	int m_nServerPort;
	CString m_strDBIp;
	int m_nDBPort;
	CString m_strDBUserName;
	CString m_strDBPwd;
	int m_nListenPort;
	int m_nSyncInterval;
	CString m_strDBName;
	CString m_strLocalBranchId;
	CString m_strSMSIp;
	int		m_nSMSPort;
	CString m_strSMSUserName;
	CString m_strSMSPwd;
	IBFISSyncClient* m_pClient;
	IBFISCommunicateSyncServer* m_pServer;
	IThread* m_pThread;
    IMigrateTaskStation* m_pMigrateStation;
	CListCtrl m_LogList;
//	CMFCMenuButton m_menuBtn;
    ITimer* m_pTimer;
	BOOL m_bDogModel;
	ST_UserInfo m_stLocalMcInfo;
	CTime m_LocalTime;
	NOTIFYICONDATA m_notify;
public:
    CListCtrl m_listTaskPlan;
    CListCtrl m_connectionList;
    afx_msg void OnNMCustomdrawLoglist(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnClose();
};
