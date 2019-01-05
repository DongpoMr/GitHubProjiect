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
		TTRACE("%s[%d]: ����Ǩ�ƻỰʧ�ܣ�����ֵ%d, Session:%p\r\n", __FUNCTION__, __LINE__, lMigrateSession);
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
		DISPLAY_LOG("Ǩ��ģ��", "��ѯ����ʧ��", "��ȡ���ݶ���ʧ��", "", 0);
		return -1;
	}

	std::vector<ST_BusinessFileInfo> vecFiles;
	int nRet = pDataProvider->QueryBusinessFileInfoByBusinessInfoId(m_pMigrateInfo.strBusinessID, vecFiles); //��ѯҵ�������Ϣ����ȡ��ҵ����ļ���Ϣ.
	if (nRet <= 0 || vecFiles.empty())
	{
		DISPLAY_LOG("Ǩ��ģ��", "��ѯ����ʧ��", "��ȡҵ���ļ���Ϣʧ��", "", 0);
		return -1;
	}

	ST_BusinessInfo stBusiness;
	nRet = pDataProvider->QueryBusinessInfoById(m_pMigrateInfo.strBusinessID, stBusiness);

	//��ȡ¼���ļ��Ŀ�ʼ�ͽ���ʱ��
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
		SFTRACE("MigtateTask", " %s[%d] ��ȡ�豸��Ϣʧ��, ҵ��ID[%s] �豸��ICMS��ʶ[%s] �豸���ڷֿص�ID[%s] ����ֵ[%d] this[%p] \r\n",
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
	SFTRACE("MigtateTask", " %s[%d] ��ѯǨ��ҵ������, ҵ��ID[%s] �豸ID�б�[%s] ����ֵ[%d] ʱ��[%d-%d-%d %d%d%d.%d][%d-%d-%d %d%d%d.%d] this[%p]\r\n",
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
		if (false == m_bGetDataEnd) //�����ʱ�������ó����ڴ���״̬���´μ�����ѯ
			m_pMigrateInfo.nStatus = TSK_PROCESSING;  //�´�ѭ���ڴλ�ȡ
		m_nOnTimeCount = 0;
		m_pTimer->KillTimer(-1);
		m_bTaskEnd = true;
		SFTRACE("MigtateTask", " %s[%d] ��ȡǨ��ҵ������, ҵ��ID[%s] ��ѯ������־[%d] ״̬[%d] this[%p]\r\n", __FUNCTION__,
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
			/*1Ϊ�Ŷӣ�2Ϊ���ڵ��ȣ�3Ϊ��ɣ�4Ϊ��ͣ��5Ϊȡ��,6Ϊֹͣ��7Ϊ�쳣��8Ϊ�쳣����*/
			if (1 == pMigrate->nState || 2 == pMigrate->nState|| 8 == pMigrate->nState)
				m_pMigrateInfo.nStatus = TSK_PROCESSING;  //�Ѿ����������棬�����ټ�����
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
