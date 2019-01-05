#pragma once

/******************************************
文件迁移类任务状态查询，实现了对soc sdk文件迁移的封装
*******************************************/
#include "iBFIS_DataType_Define.h"
#include "iBFIS_UniqueDefine.h"
#include "iSOC_FileMigrateV2.0Module.h"
#include <vector>
#include <boost/thread.hpp>
#include "ITimer.h"

#include "Poco/Mutex.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeParser.h"
#include "Poco/Timespan.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTimeFormatter.h"
#include <unordered_map>

class XhMigrateManagement :public ITimerCallbackSkin
{
public:
	XhMigrateManagement();
	~XhMigrateManagement();
public:
	bool CreateMigrateSession(ISOC_LONGPTR lMCSession, ST_CenterInfo* pCenterInfo);
	int SetMigrateInfo(ST_BFISMigrateTask* pInfo);
	int QueryMigrateInfo();

public:
	virtual ISOC_VOID OnTimer(IN ISOC_ID iTimerID);
public:
	static ISOC_INT __stdcall MigrateManagementFileInfoCallback(ISOC_DWORDPTR dwCookie,ISOC_INT nInfoType,ISOC_BYTE* pInfo,ISOC_INT nInfoLen,const ISOC_STR strCatalogInfo,ISOC_INT nCatalogLen);
	ISOC_INT MigrateMgrHandle(ISOC_INT nInfoType,ISOC_BYTE* pInfo,ISOC_INT nInfoLen,const ISOC_STR strCatalogInfo,ISOC_INT nCatalogLen);
	inline ST_BFISMigrateTask *GetMigrateMgrInfo() { return &m_pMigrateInfo; }
	inline bool IsMigrateMgrEnd() { return m_bTaskEnd; }
	inline bool IsFindData() { return m_bFindData; }
private:
	ISOC_LONGPTR    m_lMCSession;
	ISOC_LONGPTR    m_lMigrateMgrSession;
	ST_CenterInfo  *m_pCenterInfo;
	ST_BFISMigrateTask m_pMigrateInfo;
	Poco::DateTime m_fileBeginTime;
	Poco::DateTime m_fileEndTime;
	ITimer* m_pTimer;
	bool  m_bGetDataEnd;
	int   m_nOnTimeCount;
	bool  m_bTaskEnd;
	bool  m_bFindData;
};

