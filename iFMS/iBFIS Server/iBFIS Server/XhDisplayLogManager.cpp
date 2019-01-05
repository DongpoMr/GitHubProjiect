#include "StdAfx.h"
#include "XhDisplayLogManager.h"
#include "iSOC_MonFactoryManagement.h"
#include "IBFISDisplayLogStation.h"


XhDisplayLogManager::XhDisplayLogManager(void) :m_pLogList(nullptr), m_pTaskPlanList(nullptr), m_nMaxCount(100)
{
	iSOC_MonFactoryManagement fmt;
	IBFISDisplayLogStation* pStation = static_cast<IBFISDisplayLogStation*>(fmt.CreateObject(OBJECT_TYPE_BFIS_DISPLAY_LOG_STATION,"",__FUNCTION__));
	if(pStation)
		pStation->SetDisplayLogCallbackSkin(this);
}


XhDisplayLogManager::~XhDisplayLogManager(void)
{
}

ISOC_INT XhDisplayLogManager::OnGotLogInfo( IN const ST_BFISLogInfo& info,IN ISOC_DWORDPTR dwReserved /*= NULL*/ )
{
	iCMSP_SimpleLock lockFunc(&m_visitFunc,__FUNCTION__);
	if(!m_pLogList)
		return -2;
	if(m_lstLogInfo.size() == m_nMaxCount)
	{
		m_pLogList->DeleteItem(m_nMaxCount - 1);
		m_lstLogInfo.pop_back();
	}
	m_lstLogInfo.push_front(info);
	CString strTime;
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d",info.stLogTime.wYear,info.stLogTime.wMonth,info.stLogTime.wDay,
		info.stLogTime.wHour,info.stLogTime.wMinute,info.stLogTime.wSecond);
	m_pLogList->InsertItem(0,strTime);
	m_pLogList->SetItemText(0,1,info.strLogSource.c_str());
	m_pLogList->SetItemText(0,2,info.strLogContent.c_str());
	m_pLogList->SetItemText(0,3,info.strErrorDes.c_str());
	m_pLogList->SetItemText(0,4,(info.nLogStatus==1)?_T("成功"):_T("失败"));
    m_pLogList->SetItemData(0, info.nLogStatus);
	return 1;
}

void XhDisplayLogManager::SetDisplayLogList( CListCtrl* pList )
{
	m_pLogList = pList;
}

ST_BFISLogInfo XhDisplayLogManager::GetLogInfo( int nIndex )
{
	ST_BFISLogInfo info;
	if(m_lstLogInfo.size() > nIndex)
	{
		auto itor = m_lstLogInfo.begin();
		::advance(itor,nIndex);
		if(itor != m_lstLogInfo.end())
			return *itor;
	}
	return info;
}

void XhDisplayLogManager::SetMaxLogCount( int nMaxCount /*= 100*/ )
{
	m_nMaxCount = nMaxCount;
}

void XhDisplayLogManager::SetDisplayTaskPlanList(CListCtrl* pList)
{
    m_pTaskPlanList = pList;
}

int XhDisplayLogManager::OnGotTaskPlanInfo(IN const ST_TaskPlan& info, IN DWORD_PTR dwReserved /*= NULL*/)
{
    iCMSP_SimpleLock lock(&m_csLockTaskPlan, __FUNCTION__);
    auto iter = m_mapPlans.find(info.strPlanID);
    if (iter == m_mapPlans.end())
    {
        m_mapPlans[info.strPlanID] = info;
        m_pTaskPlanList->InsertItem(0, info.strPlanID.c_str());
        m_pTaskPlanList->SetItemText(0, 1, info.strTimeBegin.c_str());
        m_pTaskPlanList->SetItemText(0, 2, info.strTimeEnd.c_str());
        m_pTaskPlanList->SetItemText(0, 3, (info.nEnable == 1) ? _T("启用") : _T("未启用"));
    }
    else
    {
        for (int i = 0; i < m_pTaskPlanList->GetItemCount(); i++)
        {
            if (m_pTaskPlanList->GetItemText(i,0) == info.strPlanID.c_str())
            {
                m_pTaskPlanList->SetItemText(i, 1, info.strTimeBegin.c_str());
                m_pTaskPlanList->SetItemText(i, 2, info.strTimeEnd.c_str());
                m_pTaskPlanList->SetItemText(i, 3, (info.nEnable == 1) ? _T("启用") : _T("未启用"));
                m_mapPlans[info.strPlanID] = info;
                break;
            }
        }
    }
    return 1;
}

void XhDisplayLogManager::SetDisplayConnectionList(CListCtrl* pList)
{
    m_pConnectionList = pList;
}

int XhDisplayLogManager::OnGotConnectionInfo(IN const ST_BFISConnectionInfo& info, IN DWORD_PTR dwReserved /*= NULL*/)
{
    iCMSP_SimpleLock lock(&m_csLockConnection, __FUNCTION__);
    switch (info.enState)
    {
    case ST_BFISConnectionInfo::Connected:
    {
        CString strUserID = info.strUserID.c_str();
        int nCount = m_pConnectionList->GetItemCount();
        for (int i = 0; i < nCount; i++)
        {
            if (m_pConnectionList->GetItemText(i, 0) == strUserID)
            {
                return 1;
            }
        }

        m_pConnectionList->InsertItem(0, info.strUserID.c_str());
        m_pConnectionList->SetItemText(0, 1, info.strUserName.c_str());
        m_pConnectionList->SetItemText(0, 2, info.strUserIP.c_str());
        break;
    }
    case ST_BFISConnectionInfo::DisConnect:
    {
        CString strUserID = info.strUserID.c_str();
        int nCount = m_pConnectionList->GetItemCount();
        for (int i = 0; i < nCount; i++)
        {
            if (m_pConnectionList->GetItemText(i, 0) == strUserID)
            {
                m_pConnectionList->DeleteItem(i);
                return 1;
            }
        }
        break;
    }
    default:
        break;
    }
    return 1;
}
