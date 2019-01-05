#include "stdafx.h"
#include "XhBFISMigrateTaskStationImp.h"
#include "IcmsP_Utility.h"
#include "iSOC_LoginModule.h"
#include "XhLogDisplayInterface.h"
#include "iSOC_FileMigrateV2.0Module.h"
#include "iSOC_UtilityDefine.h"
#include "iSOC_MonFactoryManagement.h"
#include "XhMigratePlanMan.hpp"
#include "IBFISDataProvider.h"
#include "IBFISClientDataTrafficSource.h"
#include "XhMigrateItemImp.h"
#include <sstream>
#include "IBFISSyncClient.h"
#include "iFVR_Utility.h"
#include "iFVR_Configuration.h"
#include <boost\thread.hpp>
#include "IcmsP_XmlParser.h"
#pragma comment(lib, "isoc.sdk.monitorsdk.lib")

#define CHECK_PARENT_SMSINFO	10010

#define MIGRATEASSERT_INT(value, LogSrc,LogContent,ErrDes,LogDetail, rtvalue)  \
	if(value <= 0) { \
	 DISPLAY_LOG(LogSrc, LogContent, ErrDes, LogDetail, 0);	\
	 return rtvalue; }

#define MIGRATEASSERT_PTR(ptr, LogSrc,LogContent,ErrDes,LogDetail, rtvalue) \
	if(ptr == nullptr) { \
	 DISPLAY_LOG(LogSrc, LogContent, ErrDes, LogDetail, 0);	\
	 return rtvalue; }

#define MIGRATEASSERT_BOOL(bvalue, LogSrc,LogContent,ErrDes,LogDetail, rtvalue)  \
	if(!bvalue) { \
	 DISPLAY_LOG(LogSrc, LogContent, ErrDes, LogDetail, 0);	\
	 return rtvalue; }

#define MIGRATEASSERT_DBRESULT(bvalue, LogSrc,LogContent,ErrDes,LogDetail, rtvalue)  \
	if(bvalue < 0) { \
	 DISPLAY_LOG(LogSrc, LogContent, ErrDes, LogDetail, 0);	\
	 return rtvalue; }

XhBFISMigrateTaskStationImp::XhBFISMigrateTaskStationImp()
    :m_sMCPort(0), m_lMCSession(NULL)/*, m_hWaitLogin(CreateEvent(NULL, TRUE, FALSE, NULL))*/
    , m_bIsLogin(false), m_pMigrateThread(nullptr), m_bIsStopMigrate(false), m_pTime(nullptr)
	, m_pMigratePlanMan(new XhMigeratePlanMan),m_outTime(120)
{
	
}


XhBFISMigrateTaskStationImp::~XhBFISMigrateTaskStationImp()
{
	m_bIsStopMigrate = true;
	m_condition.notify_all();
    SAFE_DELETE(m_pMigratePlanMan)
}

std::string XhBFISMigrateTaskStationImp::AddTaskItem(IN std::string strBusinessID, IN std::string strEmployeeID, IN ManulTaskStartType enStartType, IN std::string strTaskID /*= ""*/, IN DWORD_PTR dwReserved /*= 0*/)
{
    STRY;
    if (!m_bIsLogin)
    {
        DISPLAY_LOG("备份模块", "添加任务失败", "未连接上管理中心服务器", "", 0);
        return "";
    }

	SFTRACE("MigtateTask", " %s[%d] 创建任务开始 业务ID[%s] 员工ID[%s] \r\n",
		__FUNCTION__, __LINE__, strBusinessID.c_str(), strEmployeeID.c_str());

    iSOC_MonFactoryManagement fmt;
    IBFISDataProvider* pDataProvider = static_cast<IBFISDataProvider*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_CACHESOURCE, "", __FUNCTION__));
    MIGRATEASSERT_PTR(pDataProvider, "备份模块", "添加任务失败", "获取数据库连接失败", "", "");

    ST_BusinessInfo stBusiness;
    int nRet = pDataProvider->QueryBusinessInfoById(strBusinessID, stBusiness);
    MIGRATEASSERT_INT(nRet, "备份模块", "添加任务失败", "获取业务信息失败,未找到对应的业务信息", "", "");

    ST_ClientInfo stCustomer;
    stCustomer.strClientId = stBusiness.strClientId;
    nRet = pDataProvider->QueryClientInfoByID(stCustomer);
    MIGRATEASSERT_INT(nRet, "备份模块", "添加任务失败", "获取客户信息失败,未找到对应的客户信息", "", "");

    if (strTaskID.empty())
    {
        strTaskID = iFVR_Utility::CreateGUID();
        TTRACE("%s[%d]:添加新的迁移任务，任务id%s\r\n", __FUNCTION__, __LINE__, strTaskID.c_str());
    }

    ST_BFISMigrateTask tskInfo;
    tskInfo.strTaskID = strTaskID;
    std::string strAutoTime;
    m_pMigratePlanMan->CheckCanBeMigrate(&strAutoTime);
	TaskType eTaskType = TSK_AUTO;
    if (dwReserved == 0)
    {
		eTaskType = TSK_MANUAL;
        Poco::LocalDateTime dtNow;
        tskInfo.strAutoTime = Poco::DateTimeFormatter::format(dtNow.timestamp(), "%Y-%m-%e %H:%M:%S");
    }
    else
    {
        tskInfo.strAutoTime = strAutoTime;
    }
    tskInfo.nStatus			    = TSK_READY;
    tskInfo.strBusinessID       = strBusinessID;
    tskInfo.strProduceID        = stBusiness.strProduceId;
    tskInfo.strEmployeeID       = stBusiness.strEmployeeId;
    tskInfo.strLaunchEmployeeID = strEmployeeID;
    tskInfo.stCustomer          = stCustomer;
	tskInfo.strTimeForBusiness  = stBusiness.strDateTime;
	tskInfo.strExtendedInfo2    = stBusiness.strExtendedInfo2;

    XhMigrateItemImp* pItem = XhMigrateItemImp::CreateItem(m_lMCSession, &m_stMigrateCenter);
    MIGRATEASSERT_PTR(pItem, "备份模块", "添加任务失败", "创建任务失败", "", "");

    pItem->SetMigrateInfo(&tskInfo);
	pItem->SetMigrateOutTime(m_outTime);
	pItem->SetMigrateTaskType(eTaskType);
    pItem->SetStartType(strAutoTime.empty()? Immediately: enStartType); //如果strAutoTime为空说明当前没有启用的计划，则直接执行该任务
    if (dwReserved == 0)    //手动
    {
        Poco::FastMutex::ScopedLock lock(m_lockManueTask);
        m_mapManueTask[tskInfo.strTaskID] = pItem;
    }
    else
    {
        Poco::FastMutex::ScopedLock lock(m_lockPlanTask);
        m_mapPlanTask[tskInfo.strTaskID] = pItem;
    }
	SFTRACE("MigtateTask", " %s[%d] 创建任务成功 业务ID[%s] 员工ID[%s] 任务类型[%d] this[%p]\r\n",
		__FUNCTION__, __LINE__, strBusinessID.c_str(), stBusiness.strEmployeeId.c_str(), eTaskType, pItem);
    return tskInfo.strTaskID;
    SCATCH;
    return "";
}

int XhBFISMigrateTaskStationImp::DeleteTaskItem(IN std::string strTaskID)
{
    STRY;
    ST_BFISMigrateTask tskInfo;
    Poco::FastMutex::ScopedLock lock(m_lockManueTask);
    auto iter = m_mapManueTask.find(strTaskID);
    if (iter != m_mapManueTask.end())
    {
        XhMigrateItemImp* pItem = iter->second;
        pItem->ControlMigrate(XhMigrateItemImp::STOP);
        m_mapManueTask.erase(iter);
        delete pItem;
    }
    DISPLAY_LOG("备份模块", "删除任务", strTaskID.c_str(), "", 1);
    return 1;
    SCATCH;
    return -1;
}

int XhBFISMigrateTaskStationImp::GetTaskCount()
{
    STRY;
    Poco::FastMutex::ScopedLock lock(m_lockManueTask);
    return m_mapManueTask.size();
    SCATCH;
    return -1;
}

int XhBFISMigrateTaskStationImp::GetTaskInfo(IN std::string strTaskID, OUT ST_BFISMigrateTask* pInfo)
{
    STRY;
    Poco::FastMutex::ScopedLock lock(m_lockManueTask);
    auto iter = m_mapManueTask.find(strTaskID);
    if (iter == m_mapManueTask.end())
        return -1;

    *pInfo = *(iter->second->GetMigrateInfo());
    return 1;
    SCATCH;
    return -1;
}

int XhBFISMigrateTaskStationImp::GetTaskInfo(IN OUT std::vector<ST_BFISMigrateTask>* pVecInfos)
{
    STRY;
    STRY;
    Poco::FastMutex::ScopedLock lock(m_lockManueTask);
    for (auto iter = m_mapManueTask.begin(); iter != m_mapManueTask.end(); ++iter)
    {
        pVecInfos->push_back(*(iter->second->GetMigrateInfo()));
    }
    SCATCH;

    STRY;
    Poco::FastMutex::ScopedLock lock(m_lockPlanTask);
    for (auto iter = m_mapPlanTask.begin(); iter != m_mapPlanTask.end(); ++iter)
    {
        pVecInfos->push_back(*(iter->second->GetMigrateInfo()));
    }
    SCATCH;
    return 1;
    SCATCH;
    return -1;
}

int XhBFISMigrateTaskStationImp::ControlTaskItem(IN TaskControlType enType, IN std::string strTaskID)
{
	int nRet = -1;
    STRY;
	if (strTaskID.empty())
	{
		DISPLAY_LOG("备份模块", "控制任务失败，任务id不能为空", "", "", 0);
		return -1;
	}
    Poco::FastMutex::ScopedLock lock(m_lockManueTask);
    auto iter = m_mapManueTask.find(strTaskID);
    if (iter != m_mapManueTask.end())
	{
		XhMigrateItemImp::ControlMode mode;
		switch (enType)
		{
		case TSK_C_START:
			DISPLAY_LOG("备份模块", "收到用户启动任务请求", strTaskID.c_str(), "", 1);
			mode = XhMigrateItemImp::QUERY;
			iter->second->SetAutoStartTask();
			break;
		case TSK_C_STOP:
			DISPLAY_LOG("备份模块", "收到用户停止任务请求", strTaskID.c_str(), "", 1);
			mode = XhMigrateItemImp::STOP;
			break;
		case TSK_C_CANCEL:
			{
				DISPLAY_LOG("备份模块", "收到用户删除任务请求", strTaskID.c_str(), "", 1);
				XhMigrateItemImp* pItem = iter->second;
				int nRet = pItem->ControlMigrate(XhMigrateItemImp::CANCEL);
				if (nRet > 0)
				{
					m_mapManueTask.erase(iter);
					delete pItem;
					return 1;
				}
				return -1;
			}
		default:
			break;
		}
		return iter->second->ControlMigrate(mode);
	}
    SCATCH;
	std::string strTaskId;
	XhMigrateItemImp *pMigrateItem = nullptr;
	STRY;
	Poco::FastMutex::ScopedLock lock(m_lockPlanTask);
	auto iter = m_mapPlanTask.find(strTaskID);
	if (iter != m_mapPlanTask.end())
	{
		XhMigrateItemImp::ControlMode mode;
		switch (enType)
		{
		case TSK_C_START:
			DISPLAY_LOG("备份模块", "收到用户启动任务请求", strTaskID.c_str(), "", 1);
			mode = XhMigrateItemImp::QUERY;
			break;
		case TSK_C_STOP:
			DISPLAY_LOG("备份模块", "收到用户停止任务请求", strTaskID.c_str(), "", 1);
			mode = XhMigrateItemImp::STOP;
			strTaskId = iter->first;
			pMigrateItem = iter->second;
			nRet = pMigrateItem->ControlMigrate(XhMigrateItemImp::STOP);
			if (nRet > 0)
				m_mapPlanTask.erase(iter);
			break;
		case TSK_C_CANCEL:
		{
			DISPLAY_LOG("备份模块", "收到用户删除任务请求", strTaskID.c_str(), "", 1);
			XhMigrateItemImp* pItem = iter->second;
			int nRet = pItem->ControlMigrate(XhMigrateItemImp::CANCEL);
			if (nRet > 0)
			{
				m_mapPlanTask.erase(iter);
				delete pItem;
				return 1;
			}
			return -1;
		}
		default:
			break;
		}
		if (mode != XhMigrateItemImp::STOP)
			nRet = iter->second->ControlMigrate(mode);
	}
	SCATCH;
	if (pMigrateItem && !strTaskId.empty() && nRet > 0) //加入手动队列中，让停止不影响自动任务
	{
		Poco::FastMutex::ScopedLock lock(m_lockManueTask);
		pMigrateItem->SetMigrateTaskType(TSK_MANUAL);
		m_mapManueTask[strTaskId] = pMigrateItem;
	}
    return nRet;
}

int XhBFISMigrateTaskStationImp::SetAutomaticPlan(IN std::string strPlanID, IN SYSTEMTIME stTimeBegin, IN SYSTEMTIME stTimeEnd, IN bool bEnable)
{
    STRY;
    ST_TaskPlan plan;
    int nRet = m_pMigratePlanMan->GetPlan(strPlanID, plan);
    MIGRATEASSERT_INT(nRet, "备份模块", "更新备份计划失败", "未找到相应计划信息", "", -1);

    plan.nEnable = bEnable ? 1 : 0;
    {
        std::stringstream os;
        os << stTimeBegin.wHour << ":" << stTimeBegin.wMinute << ":" << stTimeBegin.wSecond;
        plan.strTimeBegin = os.str();
    }

    {
        std::stringstream os;
        os << stTimeEnd.wHour << ":" << stTimeEnd.wMinute << ":" << stTimeEnd.wSecond;
        plan.strTimeEnd = os.str();
    }

    nRet = m_pMigratePlanMan->SetPlan(plan);
    MIGRATEASSERT_INT(nRet, "备份模块", "更新备份计划失败", "设置备份计划信息失败", "", -2);

    iSOC_MonFactoryManagement fmt;
    IBFISDBOperation* pDBO = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
    MIGRATEASSERT_PTR(pDBO, "备份模块", "更新备份计划失败", "数据库操作失败", "", -3);

    std::vector<ST_TaskPlan> vec;
    vec.push_back(plan);
    nRet = pDBO->ManageTaskPlanInfo(DBO_UPDATE, vec);
    MIGRATEASSERT_DBRESULT(nRet, "备份模块", "更新备份计划失败", "数据库操作失败", "", -4);

    DISPLAY_LOG("备份模块", "更新备份计划成功", "", "", 1);
    return 1;
    SCATCH;
    return -1;
}

int XhBFISMigrateTaskStationImp::GetMigrateConfig()
{
#if 0
    CString strPath = GetWorkingDirectory();
    strPath += _T("\\Config\\iBFIS.Server.Config.ini");

    TCHAR tchBuf[500] = { 0 };
    GetPrivateProfileString(_T("SMS"), _T("SMSIP"), _T(""), tchBuf, 500, strPath);
    m_strMCIp = tchBuf;
    ZeroMemory(tchBuf, 500);
    m_sMCPort = GetPrivateProfileInt(_T("SMS"), _T("SMSPort"), 5150, strPath);

    GetPrivateProfileString(_T("SMS"), _T("SMSUser"), _T("Admin"), tchBuf, 500, strPath);
    m_strMCUser = tchBuf;
    ZeroMemory(tchBuf, 500);

    GetPrivateProfileString(_T("SMS"), _T("SMSPwd"), _T("123"), tchBuf, 500, strPath);
    m_strMCPwd = tchBuf;
    ZeroMemory(tchBuf, 500);
#endif
    iSOC_MonFactoryManagement fmt;
    IBFISSyncClient* pClient = static_cast<IBFISSyncClient*>(fmt.CreateObject(OBJECT_TYPE_BFISSYNC_CLIENT, "", __FUNCTION__));
    if (!pClient)
    {
        DISPLAY_LOG("备份模块", "初始化", "获取上级SMS信息失败,Client对象为空", "", 0);
        return -1;
    }

    std::string strPort;
    int nRet = pClient->GetParentSMSInfo(m_strMCIp, strPort, m_strMCUser, m_strMCPwd);
    if (nRet <= 0)
    {
        DISPLAY_LOG("备份模块", "初始化", "获取上级SMS信息失败", "", 0);
        return -2;
    }
    m_sMCPort = atoi(strPort.c_str());
    return 1;
}

ISOC_INT XhBFISMigrateTaskStationImp::static_OperatorCallback(const OperatorState enState, const ISOC_INT nOperatorType, const ISOC_STR strDes, const ISOC_DWORDPTR dwCookie, ISOC_DWORDPTR dwResevered)
{
    switch (nOperatorType)
    {
    case OT_LOGIN:
		{
			if (enState == OPERATOR_SUCCEEDED)
			{
				XhBFISMigrateTaskStationImp* pThis = reinterpret_cast<XhBFISMigrateTaskStationImp*>(dwCookie);
				//登陆成功
				pThis->m_bIsLogin = true;
				pThis->m_eventWaitLogin.set();
				break;
			}
			else
			{
				TTRACE("%s[%d]: SDK回调登陆MC失败\r\n", __FUNCTION__, __LINE__);
				XhBFISMigrateTaskStationImp* pThis = reinterpret_cast<XhBFISMigrateTaskStationImp*>(dwCookie);
				//登陆成功
				pThis->m_bIsLogin = false;
				pThis->m_eventWaitLogin.set();
				break;
			}
		}
    default:
        break;
    }
    return 1;
}

ISOC_VOID XhBFISMigrateTaskStationImp::Run()
{
    IBFISDBOperation* pDBOper = nullptr;
    IBFISDataProvider* pDataProvider = nullptr;
    {
        iSOC_MonFactoryManagement fmt;
        pDBOper = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
        if (!pDBOper)
        {
            DISPLAY_LOG("备份模块", "启动备份任务管理失败", "获取数据库对象失败", "", 0);
            return;
        }
        pDataProvider = static_cast<IBFISDataProvider*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_CACHESOURCE, "", __FUNCTION__));
        if (!pDataProvider)
        {
            DISPLAY_LOG("备份模块", "启动备份任务管理失败", "获取数据管理对象失败", "", 0);
            return;
        }
    }

	ST_BranchInfo strLocalBranchInfo;
	pDataProvider->GetLocalBranchInfo(strLocalBranchInfo);
	//m_strLocalBranchId = strBranchInfo.strBranchId;

	STRY;
	boost::unique_lock<boost::mutex> lock(m_mutex);
	m_condition.wait_for(lock, boost::chrono::seconds(10));
	SCATCH;

	//默认5条
	int nMigrateCount = 5;
	iCMSP_XmlParser xmlParser;
	int taskCheckIntervalTime = 10;
	int queryMaxWaitCount = 2;
	bool bRet = xmlParser.Load("./Config/BankPluginConfig.xml");
	if (false == bRet)
	{
		TTRACE("加载插件配置文件失败 %s\r\n",__FUNCTION__);
	}
	else
	{
		if (xmlParser.FindElem(_T("bankplugin")))
		{
			nMigrateCount = xmlParser.GetAttribInt(_T("MigrateCount"));
			m_outTime = xmlParser.GetAttribInt(_T("MigrateOutTime"));
			taskCheckIntervalTime = xmlParser.GetAttribInt(_T("TaskCheckIntervalTime"));
			queryMaxWaitCount = xmlParser.GetAttribInt(_T("QueryMaxWaitCount"));
			if (m_outTime < 60)
				m_outTime = 60;
		}
	}

	if (nullptr == m_spMigrateMgr && m_lMCSession != NULL)
	{
		m_spMigrateMgr.reset(new XhMigrateManagement());
		m_spMigrateMgr->CreateMigrateSession(m_lMCSession, &m_stMigrateCenter);
	}
	bool bFristLoadStopTask = false;

	SFTRACE("MigtateTask", " 迁移并发数[%d] 迁移超时时长[%d] 迁移任务状态监测间隔时间[%d] 最大查询次数[%d]\r\n",nMigrateCount, m_outTime, taskCheckIntervalTime, queryMaxWaitCount);

	XhMigrateItemImp::SetIntervalTime(taskCheckIntervalTime);
	XhMigrateItemImp::SetQueryWaitMaxCount(queryMaxWaitCount);
    while (!m_bIsStopMigrate)
    {
        if (!m_bIsLogin)
        {
			iFVR_Configuration config;
			int nAppType = config.GetInt("LocalSet", "AppType", 1);
			if (nAppType != AppType_Client) //上级不用再登陆mc了
			{
				m_sMCPort   = config.GetInt("SMS",       "SMSPort",      5150);
				m_strMCIp   = config.GetString("SMS",      "SMSIP",        "").c_str();    
				m_strMCUser = config.GetString("SMS",      "SMSUser",      "").c_str();
				m_strMCPwd  = config.GetString("SMS",      "SMSPwd",       "").c_str();
			}
			else
			{
				GetMigrateConfig();
			}
			int nRet = LoginMC();
            if (nRet <= 0)
            {
                DISPLAY_LOG("备份模块", "重连上级管理中心失败", "", "", 0);
				STRY;
				boost::unique_lock<boost::mutex> lock(m_mutex);
				m_condition.wait_for(lock, boost::chrono::seconds(5));
				SCATCH;
                continue;
            }
			else
			{
				DISPLAY_LOG("备份模块", "重连上级管理中心成功", "", "", 1);
			}

			m_spMigrateMgr.reset(new XhMigrateManagement());
			m_spMigrateMgr->CreateMigrateSession(m_lMCSession, &m_stMigrateCenter);
        }

		//从数据库加载停止的任务
		if (false == bFristLoadStopTask)
			LoadStopTaskFromDatabase(pDataProvider);
		bFristLoadStopTask = true;

		m_pMigratePlanMan->DELPlan();
		vector<ST_TaskPlan> vecTaskPlan;
		pDBOper->ManageTaskPlanInfo(DBO_QUERY,vecTaskPlan);	
		for each (auto& plan in vecTaskPlan)
		{
			m_pMigratePlanMan->AddPlan(plan);
		}

		ManualTaskStateCheck();

		bool bMigrate = m_pMigratePlanMan->CheckCanBeMigrate();

		//计划任务-包括手动（空闲）任务和自动迁移任务
		if (bMigrate)
		{
			STRY;   //先看看手动任务中有没有需要闲时执行的
			Poco::FastMutex::ScopedLock lock(m_lockManueTask);
			int nHandTaskCount = 0;
			for each (const auto& var in m_mapManueTask)
			{
				XhMigrateItemImp* pItem = var.second;
				if (nullptr == pItem)
					continue;

				if (pItem->GetMigrateInfo()->nType == Idle && pItem->GetMigrateInfo()->nStatus == TSK_READY)
				{
					pItem->ControlMigrate(XhMigrateItemImp::START, true);
					++nHandTaskCount;
					DISPLAY_LOG("备份模块", "计划任务", "开始执行手动闲时任务", "", 1);
					if (nHandTaskCount >= nMigrateCount) //手动闲时任务最大同时启动nMigrateCount条
						break;                                       
				}
				else if (pItem->GetMigrateInfo()->nType == Idle && pItem->GetMigrateInfo()->nStatus == TSK_PROCESSING)
				{
					++nHandTaskCount;
				}
			}
			SCATCH;
			//处理软件关闭时正在处理的任务，而处理结果未更新数据库问题
			MigtateTaskProcessingHandle(pDataProvider, pDBOper, strLocalBranchInfo, nMigrateCount);

			MigtateTaskHandle(pDBOper, pDataProvider, strLocalBranchInfo, nMigrateCount, 0);
			MigtateTaskHandle(pDBOper, pDataProvider, strLocalBranchInfo, nMigrateCount, TSK_FAILED);
			if (!m_bIsStopMigrate)
			{
				STRY;
				boost::unique_lock<boost::mutex> lock(m_mutex);
				m_condition.wait_for(lock, boost::chrono::seconds(10));
				SCATCH;
			}
		}
		else
		{
			STRY;
			boost::unique_lock<boost::mutex> lock(m_mutex);
			m_condition.wait_for(lock, boost::chrono::seconds(60));
			SCATCH;
		}
    }

	SFTRACE("MigtateTask", " 迁移线程退出 \r\n");
	DISPLAY_LOG("备份模块", "迁移线程退出", "", "", 0);
}

int XhBFISMigrateTaskStationImp::LoginMC()
{
    int nRet = iSOC_InitSobeyMonitorSystem();
    MIGRATEASSERT_INT(nRet, "备份模块", "初始化", "初始化SDK失败", "", -1);

    nRet = iSOC_UserLogin(m_strMCIp.c_str(), m_sMCPort, m_strMCUser.c_str(), m_strMCPwd.c_str(), &m_lMCSession, static_OperatorCallback, reinterpret_cast<ISOC_DWORDPTR>(this));
    if (nRet <= 0)
    {
        iSOC_UserLogout(m_lMCSession);
        m_lMCSession = NULL;
        DISPLAY_LOG("备份模块", "连接上级管理中心失败", "", "", 0);
        return -3;
    }

    m_eventWaitLogin.reset();
    m_eventWaitLogin.tryWait(3 * 60 * 1000);    //等待3分钟，防止sdk一直都没有回调
    if (!m_bIsLogin)
    {
        iSOC_UserLogout(m_lMCSession);
        m_lMCSession = NULL;
        DISPLAY_LOG("备份模块", "登陆上级管理中心失败", "", "", 0);
        return -3;
    }

    ISOC_LONGPTR pMigrateList;
    nRet = iSOC_GetMigrateV20CenterListInfo(m_lMCSession, &pMigrateList);
    MIGRATEASSERT_INT(nRet, "备份模块", "初始化", "获取迁移服务器地址失败", "", -4);

    int nCount = iSOC_GetDataListItemCount(pMigrateList);
    MIGRATEASSERT_INT(nCount, "备份模块", "初始化", "获取迁移服务器地址失败,服务器数量为0", "", -5);

    int nDataLen = sizeof(m_stMigrateCenter);
    nRet = iSOC_GetFirstDataListItem(pMigrateList, &m_stMigrateCenter, nDataLen);   //一个mc只会配一个迁移服务器
    MIGRATEASSERT_INT(nRet, "备份模块", "初始化", "获取迁移服务器信息错误", "", -6);

    nRet = iSOC_SetRecvServerTimeCallback(m_lMCSession, static_OnRecvServerTimeCallback, reinterpret_cast<ISOC_DWORDPTR>(this));
    MIGRATEASSERT_INT(nRet, "备份模块", "初始化", "注册时间同步失败", "", -7);
	return 1;
}

void XhBFISMigrateTaskStationImp::AddPlanTask(std::vector<ST_BusinessInfo>& vecBiz, IBFISDataProvider* pDataProvider, ST_BranchInfo& strLocalBranchInfo, int nMaxTaskNum, int& nPos)
{
	STRY;
	bool bFind = false;
	int nSize = vecBiz.size();
	for (int i = nPos; i < nSize; ++i)
	{
		STRY;
		Poco::FastMutex::ScopedLock lock(m_lockPlanTask);
		if (m_mapPlanTask.size() >= nMaxTaskNum)
			break;
		SCATCH;

		STRY;
		Poco::FastMutex::ScopedLock lockManue(m_lockManueTask);
		for (auto iterPlan = m_mapManueTask.begin(); iterPlan != m_mapManueTask.end(); ++iterPlan)
		{
			//手动任务存在不需要在加
			if (vecBiz[i].strBusinessInfoId == iterPlan->second->GetMigrateInfo()->strBusinessID)
			{
				bFind = true;
				break;
			}
		}
		SCATCH;

		if (bFind)
		{
			++nPos;
			bFind = false;
			continue;
		}

		ST_ProduceInfo stProduceInfo;
		if (m_strPluginName == "JZ")
		{
			if (pDataProvider && pDataProvider->QueryProduceInfoById(vecBiz[i].strProduceId, stProduceInfo)
				&& strLocalBranchInfo.strBranchId == vecBiz[i].strSubEquipmentIcmSign)
			{
				if (stProduceInfo.nEnableMigrated == 1)
				{
					AddTaskItem(vecBiz[i].strBusinessInfoId, "", Immediately, "", 1);
				}
			}
		}
		else
		{
			AddTaskItem(vecBiz[i].strBusinessInfoId, "", Immediately, "", 1);
		}
		++nPos;
		//if (vecBiz[i].nMigrated != 0)
		//{
		//	std::vector<ST_BusinessInfo> vecNoMigratrBiz;
		//	pDataProvider->QueryTaskNotMigrated(0, vecNoMigratrBiz, 0);
		//	if (!vecNoMigratrBiz.empty())
		//	{
		//		break;
		//	}
		//}
	}
	SCATCH;
}

void XhBFISMigrateTaskStationImp::DelRepeatTask(std::vector<ST_BusinessInfo>& vecBiz)
{
	STRY;
	Poco::FastMutex::ScopedLock lockPlan(m_lockPlanTask);
	Poco::FastMutex::ScopedLock lockManue(m_lockManueTask);
	if (m_mapPlanTask.size() <= 0 && m_mapManueTask.size() <= 0)
		return;
	SCATCH;

	STRY;
	bool bFind = false;
	for (auto iter = vecBiz.begin(); iter != vecBiz.end();)
	{
		STRY;
		Poco::FastMutex::ScopedLock lockPlan(m_lockPlanTask);
		for (auto iterPlan = m_mapPlanTask.begin(); iterPlan != m_mapPlanTask.end(); ++iterPlan)
		{
			//去掉已存在的任务
			if (iter->strBusinessInfoId == iterPlan->second->GetMigrateInfo()->strBusinessID)
			{
				bFind = true;
				break;
			}
		}
		SCATCH;

		if (false == bFind)
		{
			Poco::FastMutex::ScopedLock lockManue(m_lockManueTask);
			for (auto iterPlan = m_mapManueTask.begin(); iterPlan != m_mapManueTask.end(); ++iterPlan)
			{
				//去掉已存在的任务
				if (iter->strBusinessInfoId == iterPlan->second->GetMigrateInfo()->strBusinessID)
				{
					bFind = true;
					break;
				}
			}
		}

		if (bFind)
		{
			bFind = false;
			iter = vecBiz.erase(iter);
			continue;
		}

		++iter;
	}
	SCATCH;
}

bool XhBFISMigrateTaskStationImp::MigtateTaskHandle(IBFISDBOperation* pDBOper, IBFISDataProvider* pDataProvider, ST_BranchInfo& strLocalBranchInfo, int nMaxTaskNum, int nCondition)
{
	if (nullptr == pDBOper || nullptr == pDataProvider)
		return false;

	if (m_bIsStopMigrate)
		return false;

	bool bMigrate = m_pMigratePlanMan->CheckCanBeMigrate();
	if (false == bMigrate)
		return false;

	std::vector<ST_BusinessInfo> vecBiz;
	STRY;
	int nRet = pDataProvider->QueryTaskNotMigrated(0, vecBiz, nCondition);	//一次查询queryCount条数据加入计划任务队列
	SFTRACE("MigtateTask", " %s[%d] 查询迁移业务数据 QUEUE 类型[%d], 数据大小[%d] 返回值[%d]  \r\n", __FUNCTION__, __LINE__,
		nCondition, vecBiz.size(), nRet);
	SCATCH;

	int nCurrPos = 0;
	int nTaskSize = 0;
	int nVecSize = vecBiz.size();
	do
	{
		ManualTaskStateCheck();

		bMigrate = m_pMigratePlanMan->CheckCanBeMigrate();
		if (bMigrate && nCurrPos < nVecSize && m_mapPlanTask.size() < nMaxTaskNum )
			AddPlanTask(vecBiz, pDataProvider, strLocalBranchInfo, nMaxTaskNum, nCurrPos);

		STRY;
		//处理计划任务
		Poco::FastMutex::ScopedLock lock(m_lockPlanTask);
		if (m_mapPlanTask.size() <= 0)
			return false;
		SCATCH;

		AutoTaskStateCheck();

		STRY;
		if (m_mapPlanTask.size() >= nMaxTaskNum || nCurrPos >= nVecSize)
		{
			boost::unique_lock<boost::mutex> lock(m_mutex);
			m_condition.wait_for(lock, boost::chrono::seconds(5));
		}
		else
		{
			boost::unique_lock<boost::mutex> lock(m_mutex);
			m_condition.wait_for(lock, boost::chrono::seconds(2));
		}
		SCATCH;
	} while (!m_bIsStopMigrate);
	return false;
}

bool XhBFISMigrateTaskStationImp::MigtateTaskProcessingHandle(IBFISDataProvider * pDataProvider, IBFISDBOperation* pDBOper, ST_BranchInfo& strLocalBranchInfo, int nMaxTaskNum)
{
	if (nullptr == pDataProvider || nullptr == pDBOper)
		return false;

	if (m_bIsStopMigrate)
		return false;

	std::vector<ST_BusinessInfo> vecBiz;
	STRY;
	int nRet = pDataProvider->QueryTaskNotMigrated(0, vecBiz, TSK_PROCESSING);	//一次查询queryCount条数据加入计划任务队列
	SFTRACE("MigtateTask", " %s[%d] 查询执行中状态的迁移业务数据, 数据大小[%d] 返回值[%d]  \r\n", __FUNCTION__, __LINE__,
		vecBiz.size(), nRet);
	SCATCH;

	DelRepeatTask(vecBiz);

	STRY;
	ST_BFISMigrateTask stMigrateTask;
	if (m_spMigrateMgr)
	{
		for (auto iter = vecBiz.begin(); iter != vecBiz.end();)
		{
			stMigrateTask.strBusinessID = iter->strBusinessInfoId;
			m_spMigrateMgr->SetMigrateInfo(&stMigrateTask);
			int nRet = m_spMigrateMgr->QueryMigrateInfo();
			while (!m_bIsStopMigrate && nRet > 0)
			{
				if (m_spMigrateMgr->IsMigrateMgrEnd())
				{
					int nState = m_spMigrateMgr->GetMigrateMgrInfo()->nStatus;
					if (TSK_FAILED == nState || TSK_FINISHED == nState || TSK_STOP == nState || TSK_PAUSE == nState)
					{
						pDBOper->SetMigratedBusinessInfo(m_spMigrateMgr->GetMigrateMgrInfo()->strBusinessID, nState);
					}
					break;
				}
				STRY;
				boost::unique_lock<boost::mutex> lock(m_mutex);
				m_condition.wait_for(lock, boost::chrono::seconds(2));
				SCATCH;
			}

			if (m_bIsStopMigrate)
				return false;

			if (m_spMigrateMgr->IsFindData())  //如果发现任务，不需要在向迁移查询
			{
				iter = vecBiz.erase(iter);
				continue;
			}
			++iter;
		}
	}
	SCATCH;

	if (m_bIsStopMigrate)
		return false;

	STRY;
	int nCurrPos = 0;
	int nVecSize = vecBiz.size();
	do
	{
		if (nCurrPos < nVecSize)
		{
			ST_ProduceInfo stProduceInfo;
			if (m_strPluginName == "JZ")
			{
				if (pDataProvider && pDataProvider->QueryProduceInfoById(vecBiz[nCurrPos].strProduceId, stProduceInfo)
					&& strLocalBranchInfo.strBranchId == vecBiz[nCurrPos].strSubEquipmentIcmSign)
				{
					if (stProduceInfo.nEnableMigrated == 1)
					{
						AddTaskItem(vecBiz[nCurrPos].strBusinessInfoId, "", Immediately, "", 1);
					}
				}
			}
			else
			{
				AddTaskItem(vecBiz[nCurrPos].strBusinessInfoId, "", Immediately, "", 1);
			}
			++nCurrPos;
		}
		else
		{
			Poco::FastMutex::ScopedLock lock(m_lockPlanTask);
			if (m_mapPlanTask.size() <= 0)
				return false;
		}

		STRY;
		Poco::FastMutex::ScopedLock lock(m_lockPlanTask);
		for (auto iter1 = m_mapPlanTask.begin(); iter1 != m_mapPlanTask.end();)
		{
			XhMigrateItemImp* pItem = iter1->second;
			int nStatus = pItem->GetTaskState();
			if (XhMigrateItemImp::ControlMode::SUCCEED == nStatus)
			{
				delete pItem;
				pItem = nullptr;
				iter1 = m_mapPlanTask.erase(iter1);
				continue;
			}
			else if (XhMigrateItemImp::ControlMode::FAILED == nStatus)
			{
				int nMode = pItem->GetCurrQueryMode();
				if (!pItem->IsOutTime())   //如果超时不再继续查询
				{
					if (nMode == 4)
					{
						int nRet = pItem->ControlMigrate(XhMigrateItemImp::ControlMode::QUERY, true, 8);
						if (nRet <= 0)
						{
							delete pItem;
							pItem = nullptr;
							iter1 = m_mapPlanTask.erase(iter1);
							continue;
						}
					}
					else if (8 == nMode)
					{
						delete pItem;
						pItem = nullptr;
						iter1 = m_mapPlanTask.erase(iter1);
						continue;
					}
				}
				else
				{
					delete pItem;
					pItem = nullptr;
					iter1 = m_mapPlanTask.erase(iter1);
					continue;
				}
			}
			else if (XhMigrateItemImp::ControlMode::QUERY == nStatus)
			{
				int nRet = pItem->ControlMigrate(XhMigrateItemImp::ControlMode::QUERY, true, 4);
				if (nRet <= 0)
				{
					nRet = pItem->ControlMigrate(XhMigrateItemImp::ControlMode::QUERY, true, 8);
					if (nRet <= 0)
					{
						delete pItem;
						pItem = nullptr;
						iter1 = m_mapPlanTask.erase(iter1);
						continue;
					}
				}
			}

			++iter1;
		}
		SCATCH;

		STRY;
		boost::unique_lock<boost::mutex> lock(m_mutex);
		m_condition.wait_for(lock, boost::chrono::seconds(2));
		SCATCH;

	} while (!m_bIsStopMigrate);
	SCATCH;

	return true;
}

void XhBFISMigrateTaskStationImp::LoadStopTaskFromDatabase(IBFISDataProvider * pDataProvider)
{
	std::vector<ST_BusinessInfo> vecBiz;
	if (nullptr == pDataProvider)
		return;
	STRY;
	int nRet = pDataProvider->QueryTaskNotMigrated(0, vecBiz, TSK_STOP);	//一次查询queryCount条数据加入计划任务队列
	SFTRACE("MigtateTask", " %s[%d] 查询停止状态的迁移业务 数据大小[%d] 返回值[%d] \r\n", __FUNCTION__, __LINE__, vecBiz.size(), nRet);
	SCATCH;

	for each(auto &var in vecBiz)
	{
		AddTaskItem(var.strBusinessInfoId, "", Immediately);
	}
}

int XhBFISMigrateTaskStationImp::InitStation()
{
    STRY;
	iCMSP_XmlParser xmlParser;
	bool bRet = xmlParser.Load("./Config/BankPluginConfig.xml");
	if (bRet < 0)
	{
		TTRACE("查询插件失败\r\n");
	}
	bRet = xmlParser.FindElem(_T("bankplugin"));
	if (bRet < 0)
	{
		TTRACE("查询插件失败\r\n");
	}
	m_strPluginName = xmlParser.GetAttrib(_T("pluginName"));
    //读取备份计划
    int nRet = [=]()->int
    {
        iSOC_MonFactoryManagement fmt;
        IBFISDBOperation* pDBO = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
        MIGRATEASSERT_PTR(pDBO, "备份模块", "初始化", "获取备份计划失败", "", -1);

        std::vector<ST_TaskPlan> vecPlans;
        pDBO->ManageTaskPlanInfo(DBO_QUERY, vecPlans);
        //MIGRATEASSERT_BOOL(!vecPlans.empty(), "备份模块", "初始化", "获取备份计划失败,计划为空", "", -1);
		if (vecPlans.empty())
		{
			for(int i = 0; i < 3; ++ i)
			{
				ST_TaskPlan stTaskPlan;
				stTaskPlan.strPlanID = iFVR_Utility::CreateGUID();
				stTaskPlan.strTimeBegin = "00:00:00";
				stTaskPlan.strTimeEnd = "00:00:00";
				stTaskPlan.nOrderID = i + 1;
				stTaskPlan.nEnable = 0;
				vecPlans.push_back(stTaskPlan);	
				pDBO->ManageTaskPlanInfo(DBO_ADD, vecPlans);
				m_pMigratePlanMan->AddPlan(stTaskPlan);
				vecPlans.clear();
			}

		}
		else
		{
			for each (auto& plan in vecPlans)
			{
				m_pMigratePlanMan->AddPlan(plan);
			}
		}
        return 1;
    }();

    //注册信令回调
    nRet = [this]()->int
    {
        iSOC_MonFactoryManagement fmt;
        IBFISCommunicateSyncServer* pCommunicate = static_cast<IBFISCommunicateSyncServer*>(fmt.CreateObject(OBJECT_TYPE_BFIS_COMMUNICATESYNCSERVER, "", __FUNCTION__));
        if (!fmt.CheckObjectCanBeUse(pCommunicate))
            return -1;

        if (pCommunicate->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_QUERY_TASKPLAN,    this) <= 0)    return -2;
        if (pCommunicate->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLINET_QUERY_TASKINFO,    this) <= 0)    return -2;
        if (pCommunicate->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_SET_AUTO_TASKPLAN, this) <= 0)    return -2;
		if (pCommunicate->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_ADD_MANULTASK,     this) <= 0)    return -2;
		if (pCommunicate->RegisterRecvMessageCallbackSkin(IBFIS_MSG_CLIENT_CTRL_MANULTASK,    this) <= 0)    return -2;

        return 1;
    }();
    MIGRATEASSERT_INT(nRet, "备份模块", "初始化", "注册信令回调失败", "", -10);

    iFVR_Configuration config;
    int nAppType = config.GetInt("LocalSet", "AppType", 1);
    
    if (nAppType != AppType_Client) //上级不用再登陆mc了
    {
		m_sMCPort   = config.GetInt("SMS",       "SMSPort",      5150);
		m_strMCIp   = config.GetString("SMS",      "SMSIP",        "").c_str();    
		m_strMCUser = config.GetString("SMS",      "SMSUser",      "").c_str();
		m_strMCPwd  = config.GetString("SMS",      "SMSPwd",       "").c_str();
    }
	else
    //获取MC地址　TODO:将所有的配置文件通过一个统一的类来管理
	{
		GetMigrateConfig();
	}
    nRet = LoginMC();
    //启动迁移任务管理
    iSOC_MonFactoryManagement fmt;
    m_pMigrateThread = static_cast<IThread*>(fmt.CreateObject(OBJECT_TYPE_THREAD, "", __FUNCTION__));
    MIGRATEASSERT_PTR(m_pMigrateThread, "备份模块", "初始化", "启动备份任务管理失败", "", -11);

    m_pMigrateThread->SetRunAbleInterface(this);
    m_pMigrateThread->Start();
    MIGRATEASSERT_INT(nRet, "备份模块", "初始化", "登陆上级管理中心服务器失败", "", -12);

	//开启Timer
	{
		iSOC_MonFactoryManagement fmt; 
		if(m_pTime == nullptr)
			m_pTime = static_cast<ITimer*>(fmt.CreateObject(OBJECT_TYPE_TIMER,"",__FUNCTION__));
		if (!fmt.CheckObjectCanBeUse(m_pTime)) 
			return -1;
		m_pTime->SetTimer(this,CHECK_PARENT_SMSINFO,60*1000);
	}
    
    DISPLAY_LOG("备份模块", "初始化", "启动备份任务管理成功", "", 1);
    return 1;
    SCATCH;
    return -1;
}

int XhBFISMigrateTaskStationImp::UnInitStation()
{
    STRY;
    m_bIsStopMigrate = true;
	m_condition.notify_all();

    while (m_pMigrateThread->IsAlive())
    {
        Sleep(100);
    }
    SAFE_DELETE(m_pMigrateThread);
	if (m_pTime)
	{
		m_pTime->KillTimer(-1);
		iSOC_MonFactoryManagement fmt;
		fmt.ReleaseObject(reinterpret_cast<CISocObject**>(&m_pTime), __FUNCTION__);
	}
    return 1;
    SCATCH;
    return -1;
}

int XhBFISMigrateTaskStationImp::OnRecvData(UINT64 fromAddr, DWORD_PTR& d1, std::vector<std::string>& v1)
{
    STRY;
    switch (d1)
    {
    case IBFIS_MSG_CLIENT_QUERY_TASKPLAN:
    {
		DISPLAY_LOG("备份模块", "收到获取备份计划信息", "", "", 1);
        v1.clear();
        std::vector<ST_TaskPlan> vecInfos;
        m_pMigratePlanMan->GetPlan(vecInfos);
        for each (auto& plan in vecInfos)
        {
            BFIS::TaskPlan googlePlan;
            googlePlan.set_strplanid(plan.strPlanID.c_str());
            googlePlan.set_strbegintime(plan.strTimeBegin.c_str());
            googlePlan.set_strendtime(plan.strTimeEnd.c_str());
            googlePlan.set_neable(plan.nEnable);
            googlePlan.set_norderid(plan.nOrderID);
            std::string str;
            bool bSerialize = googlePlan.SerializeToString(&str);
            if (bSerialize)
            {
                v1.push_back(str);
            }
            else
            {
                TTRACE("%s[%d]: 序列化备份计划失败,计划id:%s\r\n", __FUNCTION__, __LINE__, plan.strPlanID.c_str());
            }
        }        
        return 1;
        break;
    }
    case IBFIS_MSG_CLIENT_ADD_MANULTASK:
    {
        if (v1.size() < 2)
            return -1;

        std::string strEmployeeID;
        iSOC_MonFactoryManagement fmt;
        IBFISClientDataTrafficSource* pClientSrc = static_cast<IBFISClientDataTrafficSource*>(fmt.CreateObject(OBJECT_TYPE_BFIS_CLIENTCOMMUNICATION, "", __FUNCTION__));
        if (pClientSrc)
        {
            pClientSrc->GetEmployeeId(fromAddr, strEmployeeID);
        }

		int nStartType = atoi(v1[0].c_str());
		CString strLog;
		strLog.Format("收到客户端启动%s任务", nStartType == Idle ? "闲时执行" : "立即执行");
		DISPLAY_LOG("备份模块", static_cast<LPCTSTR>(strLog), v1[1].c_str(), "", 1);
		std::string strTaskID = AddTaskItem(v1[1], strEmployeeID, static_cast<ManulTaskStartType>(nStartType));
		v1.clear();
		v1.push_back(strTaskID);
		return strTaskID.empty() ? -1 : 1;
}
    case IBFIS_MSG_CLIENT_CTRL_MANULTASK:
    {
        if (v1.size() < 2)
            return -1;
        
        return ControlTaskItem(static_cast<TaskControlType>(atoi(v1[0].c_str())), v1[1]);
        break;
    }
    case IBFIS_MSG_CLINET_QUERY_TASKINFO:
    {
        std::string strTmp;
        if (v1.empty()) //查询所有的
        {
            vector<ST_BFISMigrateTask> vecData;
            int nRet = GetTaskInfo(&vecData);
            if (nRet < 0)
                return nRet;

            for each (auto& task in vecData)
            {
                //BFIS::BackupTask googleTask;
                /*
                std::string 	strTaskID;		    //任务id
                int				nType;			    //任务类型:手动、自动
                int				nStatus;			//任务状态:进行中、暂停、准备、结束、异常
                std::string     strBusinessID;	    //关联业务id
                std::string     strProduceID;		//关联业务产品id
                std::string     strEmployeeID;	    //关联业务员工id
                ST_ClientInfo	stCustomer;		    //关联业务客户信息
                std::string		strAutoTime;		//自动任务设置的开始时间
                std::string		strBeginTime;		//任务开始时间
                std::string		strEndTime;		    //任务结束时间
                int				nProcess;			//进度,当enStatus为TSK_PROCESSING时有效
                std::string     strLaunchEmployeeID;//手动任务发起人ID
                int				nOrderID;			//排序ID，表明优先级
                */

                /*
                    string strClientId;
                    string strName;
                    string strCredenitial;
                    string strPhone;
                    string strContent;
                    int	   nExtendedInfo;
                    string strExtendedInfo1;
                    string strExtendedInfo2;*/
                /*googleTask.set_strtaskid(task.strTaskID);
                googleTask.set_ntype(task.nType);
                googleTask.set_nstatus(task.nStatus);
                googleTask.set_strbusinessid(task.strBusinessID);
                googleTask.set_strproduceid(task.strProduceID);
                googleTask.set_stremployeeid(task.strEmployeeID);
                BFIS::ClientInfo* pGoogleCustomer = googleTask.mutable_stcustomer();
                pGoogleCustomer->set_strclientid(task.stCustomer.strClientId);
                pGoogleCustomer->set_strname(task.stCustomer.strName);
                pGoogleCustomer->set_strcredenitial(task.stCustomer.strCredenitial);
                pGoogleCustomer->set_strphone(task.stCustomer.strPhone);
                pGoogleCustomer->set_strcontent(task.stCustomer.strContent);
                pGoogleCustomer->set_nextendedinfo(task.stCustomer.nExtendedInfo);
                pGoogleCustomer->set_strextendedinfo1(task.stCustomer.strExtendedInfo1);
                pGoogleCustomer->set_strextendedinfo2(task.stCustomer.strExtendedInfo2);
                googleTask.set_strautotime(task.strAutoTime);
                googleTask.set_strbegintime(task.strBeginTime);
                googleTask.set_strendtime(task.strEndTime);
                googleTask.set_nprocess(task.nProcess);
                googleTask.set_strlaunchemployeeid(task.strLaunchEmployeeID);
                googleTask.set_norderid(task.nOrderID);
				googleTask.set_strtimeforbusiness(task.strTimeForBusiness);*/
				BFIS::BackupTask googleTask;
				googleTask.set_strtaskid(task.strTaskID.c_str());
				googleTask.set_ntype(task.nType);
				googleTask.set_nstatus(task.nStatus);
				googleTask.set_strbusinessid(task.strBusinessID.c_str());
				googleTask.set_strproduceid(task.strProduceID.c_str());
				googleTask.set_stremployeeid(task.strEmployeeID.c_str());
				/*BFIS::ClientInfo googleCustomer;
				googleCustomer.set_strclientid(task.stCustomer.strClientId.c_str());
				googleCustomer.set_strname(task.stCustomer.strName.c_str());
				googleCustomer.set_strcredenitial(task.stCustomer.strCredenitial.c_str());
				googleCustomer.set_strphone(task.stCustomer.strPhone.c_str());
				googleCustomer.set_strcontent(task.stCustomer.strContent.c_str());*/
				BFIS::ClientInfo* pGoogleCustomer = googleTask.mutable_stcustomer();
				pGoogleCustomer->set_strclientid(task.stCustomer.strClientId.c_str());
				pGoogleCustomer->set_strname(task.stCustomer.strName.c_str());
				pGoogleCustomer->set_strcredenitial(task.stCustomer.strCredenitial.c_str());
				pGoogleCustomer->set_strphone(task.stCustomer.strPhone.c_str());
				pGoogleCustomer->set_strcontent(task.stCustomer.strContent.c_str());
				pGoogleCustomer->set_nextendedinfo(task.stCustomer.nExtendedInfo);
				pGoogleCustomer->set_strextendedinfo1(task.stCustomer.strExtendedInfo1.c_str());
				pGoogleCustomer->set_strextendedinfo2(task.stCustomer.strExtendedInfo2.c_str());
				//googleTask.set_allocated_stcustomer(pGoogleCustomer);
				googleTask.set_strautotime(task.strAutoTime.c_str());
				googleTask.set_strbegintime(task.strBeginTime.c_str());
				googleTask.set_strendtime(task.strEndTime.c_str());
				googleTask.set_nprocess(task.nProcess);
				googleTask.set_strlaunchemployeeid(task.strLaunchEmployeeID.c_str());
				googleTask.set_norderid(task.nOrderID);
				googleTask.set_strtimeforbusiness(task.strTimeForBusiness.c_str());
				googleTask.set_strextendedinfo2(task.strExtendedInfo2.c_str());
                bool bSerilize = googleTask.SerializeToString(&strTmp);
                if (bSerilize)
                {
                    v1.push_back(strTmp);
                }
                else
                {
                    TTRACE("%s[%d]: 序列化任务信息失败\r\n", __FUNCTION__, __LINE__);
                }
            }
            return 1;
        }
        else //查询指定的任务信息
        {
            ST_BFISMigrateTask task;
            int nRet = GetTaskInfo(v1[0], &task);
            if (nRet < 0)
                return nRet;

            v1.clear();
            BFIS::BackupTask googleTask;
            googleTask.set_strtaskid(task.strTaskID.c_str());
            googleTask.set_ntype(task.nType);
            googleTask.set_nstatus(task.nStatus);
            googleTask.set_strbusinessid(task.strBusinessID.c_str());
            googleTask.set_strproduceid(task.strProduceID.c_str());
            googleTask.set_stremployeeid(task.strEmployeeID.c_str());
            BFIS::ClientInfo googleCustomer;
            googleCustomer.set_strclientid(task.stCustomer.strClientId.c_str());
            googleCustomer.set_strname(task.stCustomer.strName.c_str());
            googleCustomer.set_strcredenitial(task.stCustomer.strCredenitial.c_str());
            googleCustomer.set_strphone(task.stCustomer.strPhone.c_str());
            googleCustomer.set_strcontent(task.stCustomer.strContent.c_str());
            googleTask.set_allocated_stcustomer(&googleCustomer);
            googleTask.set_strautotime(task.strAutoTime.c_str());
            googleTask.set_strbegintime(task.strBeginTime.c_str());
            googleTask.set_strendtime(task.strEndTime.c_str());
            googleTask.set_nprocess(task.nProcess);
            googleTask.set_strlaunchemployeeid(task.strLaunchEmployeeID.c_str());
            googleTask.set_norderid(task.nOrderID);
			googleTask.set_strtimeforbusiness(task.strTimeForBusiness);

            bool bSerialize = googleTask.SerializeToString(&strTmp);
            if (bSerialize)
            {
                v1.push_back(strTmp);
            }
            else
            {
                TTRACE("%s[%d]: 序列化任务信息失败\r\n", __FUNCTION__, __LINE__);
            }
            return bSerialize ? 1 : 0;
        }
        break;
    }
    case IBFIS_MSG_CLIENT_QUERY_MCSERVERINFO:
    {
        v1.clear();
        std::string strData;
        ST_MCServer parentInfo;
        parentInfo.strBranchID = m_strParentBranchID;
        parentInfo.strBranchName = m_strParentBranchName;
        parentInfo.strMCIP = m_strMCIp;
        parentInfo.sPort = m_sMCPort;
        parentInfo.strMCUserName = m_strMCUser;
        parentInfo.strMCUserPwd = m_strMCPwd;
        bool bSerilize = parentInfo.Convert2String(strData);
        if (bSerilize)
        {
            v1.push_back(strData);
        }
        else
        {
            DISPLAY_LOG("备份模块", "客户端获取SMS信息失败", "序列化上级SMS信息失败", "", 0);
        }
        ST_MCServer currentInfo;
        iFVR_Configuration config;
        currentInfo.strBranchID = m_stCurrentBranchInfo.strBranchId;
        currentInfo.strBranchName = m_stCurrentBranchInfo.strName;
        currentInfo.strMCIP = config.GetString("SMS", "SMSIP");
        currentInfo.sPort   = config.GetInt("SMS", "SMSPort");
        currentInfo.strMCUserName = config.GetString("SMS", "SMSUser");
        currentInfo.strMCUserPwd  = config.GetString("SMS", "SMSPwd");
        bSerilize = currentInfo.Convert2String(strData);
        if (bSerilize)
        {
            v1.push_back(strData);
        }
        else
        {
            DISPLAY_LOG("备份模块", "客户端获取SMS信息失败", "序列化本级SMS信息失败", "", 0);
        }
        return 1;
        break;
    }
    default:
        break;
    }
    SCATCH;
    return -1;
}

int XhBFISMigrateTaskStationImp::OnRecvData(UINT64 fromAddr, DWORD_PTR& d, std::string& s)
{
    STRY;
    switch (d)
    {
    case IBFIS_MSG_CLIENT_SET_AUTO_TASKPLAN:
    {
        BFIS::TaskPlan googlePlan;
        bool bParse = googlePlan.ParseFromString(s);
        MIGRATEASSERT_BOOL(bParse, "备份模块", "收到设置备份计划", "解析备份计划信息失败", "", -1);
        
        ST_TaskPlan plan(googlePlan);
        int nRet = m_pMigratePlanMan->SetPlan(plan);
        MIGRATEASSERT_BOOL(nRet, "备份模块",   "收到设置备份计划", "保存备份计划失败", "", -2);

        iSOC_MonFactoryManagement fmt;
        IBFISDBOperation* pDBO = static_cast<IBFISDBOperation*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE, "", __FUNCTION__));
        MIGRATEASSERT_PTR(pDBO, "备份模块",    "收到设置备份计划", "获取数据库连接失败，保存计划信息失败", "", -3);

        SYSTEMTIME stBegin, stEnd;
        sscanf(plan.strTimeBegin.c_str(), "%d:%d:%d", &stBegin.wHour, &stBegin.wMinute, &stBegin.wSecond);
        sscanf(plan.strTimeEnd.c_str(), "%d:%d:%d", &stEnd.wHour, &stEnd.wMinute, &stEnd.wSecond);

        return SetAutomaticPlan(plan.strPlanID, stBegin, stEnd, plan.nEnable > 0 ? true : false);
	   }
    default:
        break;
    }
    SCATCH;
    return -1;
}

ISOC_INT __stdcall XhBFISMigrateTaskStationImp::static_OnRecvServerTimeCallback(IN const ISOC_LONGPTR lMCSession, IN ISOC_DWORDPTR dwUserCookie, IN ISOC_SYSTEMTIME stServerTime)
{
    STRY;
    SetLocalTime(&stServerTime);
    SCATCH;
    return -1;
}

ISOC_VOID XhBFISMigrateTaskStationImp::OnTimer(IN ISOC_ID iTimerID)
{
	if (iTimerID == CHECK_PARENT_SMSINFO)
	{
		std::string strMcIp = m_strMCIp,strUser = m_strMCUser,strPwd = m_strMCPwd;
		unsigned short sMcPort = m_sMCPort;
		iFVR_Configuration config;
		int nAppType = config.GetInt("LocalSet", "AppType", 1);

		if (nAppType != AppType_Client) //上级不用再登陆mc了
		{
			m_sMCPort   = config.GetInt("SMS",       "SMSPort",      5150);
			m_strMCIp   = config.GetString("SMS",      "SMSIP",        "").c_str();    
			m_strMCUser = config.GetString("SMS",      "SMSUser",      "").c_str();
			m_strMCPwd  = config.GetString("SMS",      "SMSPwd",       "").c_str();
		}
		else
			//获取MC地址　TODO:将所有的配置文件通过一个统一的类来管理
		{
			GetMigrateConfig();
		}
		if(strMcIp != m_strMCIp || sMcPort != m_sMCPort || strUser != m_strMCUser || strPwd != m_strMCPwd)
		{
			iSOC_UserLogout(m_lMCSession);
			m_bIsLogin = false;
			FOUTPUTDBGSTRING("【1111111】\r\n");
		}
	}
}

void XhBFISMigrateTaskStationImp::ManualTaskStateCheck()
{
	STRY;
	//处理计划任务
	Poco::FastMutex::ScopedLock lock(m_lockManueTask);
	for (auto iter = m_mapManueTask.begin(); iter != m_mapManueTask.end();)
	{
		XhMigrateItemImp* pItem = iter->second;
		
		int nStatus = pItem->GetTaskState();
		if (XhMigrateItemImp::ControlMode::SUCCEED == nStatus)   //当任务完成时移除任务
		{
			delete pItem;
			pItem = nullptr;
			iter = m_mapManueTask.erase(iter);
			continue;
		}
		else if (XhMigrateItemImp::ControlMode::ABNORMAL == nStatus)
		{
			pItem->ControlMigrate(XhMigrateItemImp::ControlMode::ABNORMAL);
		}
		++iter;
	}
	SCATCH;
}

void XhBFISMigrateTaskStationImp::AutoTaskStateCheck()
{
	//处理计划任务
	STRY;
	Poco::FastMutex::ScopedLock lock(m_lockPlanTask);
	for (auto iter = m_mapPlanTask.begin(); iter != m_mapPlanTask.end();)
	{
		XhMigrateItemImp* pItem = iter->second;
		int nStatus = pItem->GetTaskState();
		if (XhMigrateItemImp::ControlMode::SUCCEED == nStatus || XhMigrateItemImp::ControlMode::FAILED == nStatus)
		{
			delete pItem;
			pItem = nullptr;
			iter = m_mapPlanTask.erase(iter);
			if (XhMigrateItemImp::ControlMode::SUCCEED == nStatus)
			{
				DISPLAY_LOG("备份模块", "执行计划任务成功", "", "", 1);
			}
			else
			{
				DISPLAY_LOG("备份模块", "执行计划任务失败", "", "", 0);
			}
			continue;
		}
		else if (XhMigrateItemImp::ControlMode::QUERY == nStatus)
		{
			int nRet = pItem->ControlMigrate(XhMigrateItemImp::ControlMode::QUERY);
			if (nRet <= 0)
			{
				delete pItem;
				pItem = nullptr;
				iter = m_mapPlanTask.erase(iter);
				DISPLAY_LOG("备份模块", "开始查询任务", "启动查询任务失败", "", 0);
				continue;
			}
		}
		else if (XhMigrateItemImp::ControlMode::START == nStatus)
		{
			int nRet = pItem->ControlMigrate(XhMigrateItemImp::ControlMode::START, true);
			if (nRet <= 0)
			{
				delete pItem;
				pItem = nullptr;
				iter = m_mapPlanTask.erase(iter);
				DISPLAY_LOG("备份模块", "开始任务", "启动任务失败", "", 0);
				continue;
			}
		}
		else if (XhMigrateItemImp::ControlMode::ABNORMAL == nStatus)
		{
			int nRet = pItem->ControlMigrate(XhMigrateItemImp::ControlMode::ABNORMAL);
			if (nRet > 0)
			{
				delete pItem;
				pItem = nullptr;
				iter = m_mapPlanTask.erase(iter);
				DISPLAY_LOG("备份模块", "任务取消", "任务停止", "", 1);
				continue;
			}
		}
		++iter;
	}
	SCATCH;
}
