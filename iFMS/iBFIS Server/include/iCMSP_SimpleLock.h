#pragma once

#ifdef _iCMSP_UTILITY_SDK
#define iCMS_UTILITY_CLASS_MODE __declspec(dllexport)
#else
#define iCMS_UTILITY_CLASS_MODE __declspec(dllimport)
#endif

#ifndef _iCMSP_UTILITY_SDK
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"IcmsPUtilityud.lib")
		#else
			#pragma comment(lib,"IcmsPUtilityd.lib")
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"IcmsPUtilityu.lib")
		#else
			#pragma comment(lib,"IcmsPUtility.lib")
		#endif
	#endif
#endif

//just so simple simple  simple cs wrapper calss,use the deconstruct to relase the cs
//u can use it like following:
//iCMSP_SimpleCS m_simpleCS;
//iCMSP_SimpleLock lock(&m_simpleCS);

class iCMSP_SimpleCS;

typedef int(__stdcall *DeadLockCallback)(void* pParam, iCMSP_SimpleCS* pCS, DWORD dwLockedTime);

iCMS_UTILITY_CLASS_MODE int __stdcall DefaultDeadLockCallback(void* pParam, iCMSP_SimpleCS* pCS, DWORD dwLockedTime);

class iCMS_UTILITY_CLASS_MODE iCMSP_SimpleCS
{
public:
	iCMSP_SimpleCS(void);
	~iCMSP_SimpleCS(void);
	void EnterCS(const TCHAR* pCallFun);
	void LeaveCS();

	const TCHAR* GetOwnerInfo();
	LONG GetRefCnt();
	DWORD GetOwnedTS();
	DWORD GetLastOwnedThreadID();
	DWORD GetMaxLockTime();
	void SetMaxLockTime(DWORD maxLockTime);
	void SetCallbackInfoWhenDeadLock(void* pParam = NULL, DeadLockCallback pCallback = DefaultDeadLockCallback);
	DeadLockCallback GetDeadLockCallback();
	void* GetUserParameter();
private:
	CRITICAL_SECTION	m_visitedCS;
	TCHAR				m_chOwnerInfo[1024];
	LONG				m_lRefCnt;
	DWORD				m_ownedTs;
	DWORD				m_dwLastThreadID;
	void*				m_pParam;
	DeadLockCallback	m_pDeadLockCB;
	DWORD				m_dwMaxLockTime;
};

class iCMS_UTILITY_CLASS_MODE iCMSP_SimpleLock
{
public:
	iCMSP_SimpleLock(iCMSP_SimpleCS* pLock,const TCHAR* pCallFun );
	~iCMSP_SimpleLock();
private:
	iCMSP_SimpleCS*				m_pLock;
};

class iCMS_UTILITY_CLASS_MODE iCMSP_WRLock
{
public:
	iCMSP_WRLock();
	~iCMSP_WRLock();
	int EnterRead(const TCHAR* pCallFun);
	int LeaveRead();
	int EnterWrite(const TCHAR* pCallFun);
	int LeaveWrite();
private:
	CRITICAL_SECTION	m_csVisitRead;
	HANDLE				m_eVisitWrite;
	LONG volatile		m_lRefCnt;
	DWORD				m_dwWriteThreadId;
	TCHAR				m_chOwnerInfo[1024];
};

class iCMS_UTILITY_CLASS_MODE iCMSP_ReadLock
{
public:
	iCMSP_ReadLock(iCMSP_WRLock &lock_,const TCHAR* pCallFun);
	~iCMSP_ReadLock();
private:
	iCMSP_ReadLock();
	iCMSP_WRLock*			m_pLock;
};

class iCMS_UTILITY_CLASS_MODE iCMSP_WriteLock
{
public:
	iCMSP_WriteLock(iCMSP_WRLock &lock_,const TCHAR* pCallFun);
	~iCMSP_WriteLock();
private:
	iCMSP_WriteLock();
	iCMSP_WRLock*			m_pLock;
};