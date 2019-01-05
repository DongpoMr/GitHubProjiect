#include "stdafx.h"
#include "XhMigrateManagement.h"
#include "IcmsP_Utility.h"
#include "iSOC_MonFactoryManagement.h"
#include "IBFISDataProvider.h"
#include "iSOC_VodModule.h"
#include <string>
#include "XhLogDisplayInterface.h"
#include "iBFISDBOperation.h"    
#include "iSOC_LoginModule.h"
#include <boost/format.hpp>


XhMigrateManagement::XhMigrateManagement():
	m_lMCSession(NULL),m_lMigrateMgrSession(NULL),m_pCenterInfo(nullptr), m_bGetDataEnd(false),
	m_nOnTimeCount(0),m_bTaskEnd(false),m_bFindData(false)
{
	iSOC_MonFactoryManagement fmt;
	m_pTimer = static_cast<ITimer*>(fmt.CreateObject(OBJECT_TYPE_TIMER, "", __FUNCTION__));
}


XhMigrateManagement::~XhMigrateManagement()
{
	if (m_pTimer)
	{
		m_pTimer->KillTimer(-1);
	}

	if (m_lMigrateMgrSession)
		iSOC_ReleaseMigrateManagementSession(m_lMigrateMgrSession);
	m_lMigrateMgrSession = NULL;
}

bool XhMigrateManagement::CreateMigrateSession(ISOC_LONGPTR lMCSession, ST_CenterInfo * pCenterInfo)
{
	STRY;
	if (lMCSession == NULL || pCenterInfo == nullptr)
		return nullptr;

	ISOC_LONGPTR lMigrateSession = NULL;
	int nRet = iSOC_CreateMigrateManagementSession(lMCSession, &lMigrateSession);
	if (nRet <= 0 || lMigrateSession == NULL)
	{
		TTRACE("%s[%d]: 创建迁移会话失败，返回值%d, Session:%p\r\n", __FUNCTION__, __LINE__, lMigrateSession);
		return nullptr;
	}
	m_lMCSession = lMCSession;
	m_pCenterInfo = pCenterInfo;
	m_lMigrateMgrSession = lMigrateSession;
	return true;
	SCATCH;
	return false;
}

int XhMigrateManagement::SetMigrateInfo(ST_BFISMigrateTask * pInfo)
{
	if (pInfo)
	{
		m_pMigrateInfo = *pInfo;
		return 1;
	}
	
	return 0;
}

int XhMigrateManagement::QueryMigrateInfo()
{
	STRY;
	if (NULL == m_lMCSession || NULL == m_lMigrateMgrSession || nullptr == m_pCenterInfo)
		return -1;

	iSOC_MonFactoryManagement fmt;
	IBFISDataProvider* pDataProvider = static_cast<IBFISDataProvider*>(fmt.CreateObject(OBJECT_TYPE_BFISSERVER_CACHESOURCE, "", __FUNCTION__));
	if (!pDataProvider)
	{
		DISPLAY_LOG("迁移模块", "查询任务失败", "获取数据对象失败", "", 0);
		return -1;
	}

	std::vector<ST_BusinessFileInfo> vecFiles;
	int nRet = pDataProvider->QueryBusinessFileInfoByBusinessInfoId(m_pMigrateInfo.strBusinessID, vecFiles); //查询业务相关信息，获取该业务的文件信息.
	if (nRet <= 0 || vecFiles.empty())
	{
		DISPLAY_LOG("迁移模块", "查询任务失败", "获取业务文件信息失败", "", 0);
		return -1;
	}

	ST_BusinessInfo stBusiness;
	nRet = pDataProvider->QueryBusinessInfoById(m_pMigrateInfo.strBusinessID, stBusiness);

	//获取录像文件的开始和结束时间
	Poco::DateTime vodBegin(2999, 1, 1), vodEnd(1800, 1, 1);
	for each (const auto& var in vecFiles)
	{
		Poco::DateTime timeBegin, timeEnd;
		int nTzd = 0;
		timeBegin = Poco::DateTimeParser::parse(var.strRecordBegin, nTzd);
		timeEnd = Poco::DateTimeParser::parse(var.strRecordEnd, nTzd);

		vodBegin > timeBegin ? vodBegin = timeBegin : 1;
		vodEnd < timeEnd ? vodEnd = timeEnd : 1;
	}

	ST_DeviceItem device;
	nRet = iSOC_GetDeviceInfoByIcmsSignAndIcmsDeviceId(m_lMCSession, &device, const_cast<TCHAR*>(stBusiness.strSubEquipmentIcmSign.c_str()), atoi(stBusiness.strSubEquipmentId.c_str()));
	if (nRet <= 0)
	{
		SFTRACE("MigtateTask", " %s[%d] 获取设备信息失败, 业务ID[%s] 设备的ICMS标识[%s] 设备所在分控的ID[%s] 返回值[%d] this[%p] \r\n",
			__FUNCTION__, __LINE__, m_pMigrateInfo.strBusinessID.c_str(), stBusiness.strSubEquipmentIcmSign.c_str(),
			stBusiness.strSubEquipmentId.c_str(), nRet, this);
		return nRet;
	}

	std::string strDevice = (boost::format("%1%") % device.lDeviceID).str();

	m_fileBeginTime = vodBegin;
	m_fileEndTime = vodEnd;
	ISOC_SYSTEMTIME sysBegin;
	sysBegin.wYear = vodBegin.year();
	sysBegin.wMonth = vodBegin.month();
	sysBegin.wDay = vodBegin.day();
	sysBegin.wHour = vodBegin.hour();
	sysBegin.wMinute = vodBegin.minute();
	sysBegin.wSecond = vodBegin.second();
	sysBegin.wMilliseconds = vodBegin.millisecond();
	ISOC_SYSTEMTIME sysEnd;
	sysEnd.wYear = vodEnd.year();
	sysEnd.wMonth = vodEnd.month();
	sysEnd.wDay = vodEnd.day();
	sysEnd.wHour = vodEnd.hour();
	sysEnd.wMinute = vodEnd.minute();
	sysEnd.wSecond = vodEnd.second();
	sysEnd.wMilliseconds = vodBegin.millisecond();
	m_bGetDataEnd = false;
	m_nOnTimeCount = 0;
	m_bTaskEnd = false;
	m_bFindData = false;

	nRet = iSOC_QueryMigrateInfo(m_lMigrateMgrSession, m_pCenterInfo, 2, strDevice.c_str(), &sysBegin, &sysEnd, MigrateManagementFileInfoCallback, reinterpret_cast<ISOC_DWORDPTR>(this));
	if (m_pTimer && nRet > 0)
	{
		m_pTimer->SetTimer(this, 1, 2000);
	}
	SFTRACE("MigtateTask", " %s[%d] 查询迁移业务数据, 业务ID[%s] 设备ID列表[%s] 返回值[%d] 时间[%d-%d-%d %d%d%d.%d][%d-%d-%d %d%d%d.%d] this[%p]\r\n",
		__FUNCTION__, __LINE__, m_pMigrateInfo.strBusinessID.c_str(), strDevice.c_str(), nRet, sysBegin.wYear, sysBegin.wMonth, sysBegin.wDay,
		sysBegin.wHour, sysBegin.wMinute, sysBegin.wSecond,sysBegin.wMilliseconds, sysEnd.wYear, sysEnd.wMonth, sysEnd.wDay,
		sysEnd.wHour, sysEnd.wMinute, sysEnd.wSecond, sysEnd.wMilliseconds, this);
	return nRet;
	SCATCH;
	return -1;
}

ISOC_VOID XhMigrateManagement::OnTimer(IN ISOC_ID iTimerID)
{
	if (m_nOnTimeCount < 5 && false == m_bGetDataEnd)
	{
		++m_nOnTimeCount;
		return;
	}
	else
	{
		if (false == m_bGetDataEnd) //如果超时，就设置成正在处理状态，下次继续查询
			m_pMigrateInfo.nStatus = TSK_PROCESSING;  //下次循环在次获取
		m_nOnTimeCount = 0;
		m_pTimer->KillTimer(-1);
		m_bTaskEnd = true;
		SFTRACE("MigtateTask", " %s[%d] 获取迁移业务数据, 业务ID[%s] 查询结束标志[%d] 状态[%d] this[%p]\r\n", __FUNCTION__,
			__LINE__, m_pMigrateInfo.strBusinessID.c_str(), m_bGetDataEnd, m_pMigrateInfo.nStatus, this);
		return;
	}
}

ISOC_INT __stdcall XhMigrateManagement::MigrateManagementFileInfoCallback(ISOC_DWORDPTR dwCookie, ISOC_INT nInfoType, ISOC_BYTE * pInfo, ISOC_INT nInfoLen, const ISOC_STR strCatalogInfo, ISOC_INT nCatalogLen)
{
	STRY;
	XhMigrateManagement* pThis = reinterpret_cast<XhMigrateManagement*>(dwCookie);
	if (pThis)
		return pThis->MigrateMgrHandle(nInfoType, pInfo, nInfoLen, strCatalogInfo, nCatalogLen);
	SCATCH;
	return -1;
}

ISOC_INT XhMigrateManagement::MigrateMgrHandle(ISOC_INT nInfoType, ISOC_BYTE * pInfo, ISOC_INT nInfoLen, const ISOC_STR strCatalogInfo, ISOC_INT nCatalogLen)
{
	if (1 == nInfoType)
	{
		m_bFindData = true;
		ST_MigrateInfo *pMigrate = (reinterpret_cast<ST_MigrateInfo *>(pInfo));
		if (pMigrate)
		{
			/*1为排队，2为正在调度，3为完成，4为暂停，5为取消,6为停止，7为异常，8为异常重试*/
			if (1 == pMigrate->nState || 2 == pMigrate->nState|| 8 == pMigrate->nState)
				m_pMigrateInfo.nStatus = TSK_PROCESSING;  //已经在任务里面，无需再加任务
			else if (7 == pMigrate->nState || 5 == pMigrate->nState ||  0 == pMigrate->nState)
				m_pMigrateInfo.nStatus = TSK_FAILED;
			else if (4 == pMigrate->nState)
				m_pMigrateInfo.nStatus = TSK_PAUSE;
			else if (6 == pMigrate->nState)
				m_pMigrateInfo.nStatus = TSK_STOP;
			else if(3 == pMigrate->nState)
				m_pMigrateInfo.nStatus = TSK_FINISHED;
		}
	}
	else if (2 == nInfoType)
	{
		;
	}
	else if (3 == nInfoType)
	{ 
		m_bGetDataEnd = true;
	}
	return 1;
}
