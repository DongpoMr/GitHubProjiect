#pragma once
#include "IBFISDisplayLogStation.h"
#include <list>
#include <map>
#include "iCMSP_SimpleLock.h"
using namespace std;
class XhDisplayLogManager :
	public IBFISDisplayLogCallbackSkin
{
public:
	XhDisplayLogManager(void);
	~XhDisplayLogManager(void);

	virtual int OnGotLogInfo(IN const ST_BFISLogInfo& info,IN DWORD_PTR dwReserved = NULL);
    virtual int OnGotTaskPlanInfo(IN const ST_TaskPlan& info, IN DWORD_PTR dwReserved = NULL);
    virtual int OnGotConnectionInfo(IN const ST_BFISConnectionInfo& info, IN DWORD_PTR dwReserved = NULL);

	void SetDisplayLogList(CListCtrl* pList);
    void SetDisplayTaskPlanList(CListCtrl* pList);
    void SetDisplayConnectionList(CListCtrl* pList);

	ST_BFISLogInfo GetLogInfo(int nIndex);

	void SetMaxLogCount(int nMaxCount = 100);

private:
	CListCtrl *m_pLogList;
    CListCtrl *m_pTaskPlanList;
	list<ST_BFISLogInfo> m_lstLogInfo;
	int		m_nMaxCount;
	iCMSP_SimpleCS m_visitFunc;
    iCMSP_SimpleCS m_csLockTaskPlan;
    map<std::string, ST_TaskPlan> m_mapPlans;

    iCMSP_SimpleCS m_csLockConnection;
    CListCtrl *m_pConnectionList;
};

