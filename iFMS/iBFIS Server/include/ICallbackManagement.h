#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"
#include "IcmsP_Utility.h"
#include <vector>
#include <boost/atomic.hpp>
#include <functional>
#include <string>
#include <vector>

struct ST_CallBackInfo;

#ifndef SelfProcessCallback
#define SelfProcessCallback std::function<int(ST_CallBackInfo)>
#endif

#pragma pack(push,1) 
struct ST_CallBackInfo
{
	ISOC_VOID* pCallBackAddr;
	std::vector<std::string> vecStrArry;
	std::vector<ISOC_DWORDPTR> vecDwordArry;
	SelfProcessCallback pSelfCallback;
	int		nCallIdx;
	bool	bIsQueue;   //是否讲顺序，如果讲顺序则会跟据nCallIdx的值，同一个值的多次任务有先后顺序
	int		nQueueState; //外面不能使用此字段

	ST_CallBackInfo() : pCallBackAddr(NULL),pSelfCallback(NULL),nCallIdx(0),bIsQueue(false),nQueueState(0)
	{
		vecDwordArry.clear();
		vecStrArry.clear();
	}

	ST_CallBackInfo(const ST_CallBackInfo& info)
	{
		pCallBackAddr = info.pCallBackAddr;
		vecStrArry = info.vecStrArry;
		vecDwordArry = info.vecDwordArry;
		pSelfCallback = info.pSelfCallback;
		nCallIdx = info.nCallIdx;
		bIsQueue = info.bIsQueue;
		nQueueState = info.nQueueState;
	}

	ST_CallBackInfo& operator =(const ST_CallBackInfo& info )
	{
		pCallBackAddr = info.pCallBackAddr;
		vecStrArry = info.vecStrArry;
		vecDwordArry = info.vecDwordArry;
		pSelfCallback = info.pSelfCallback;
		nCallIdx = info.nCallIdx;
		bIsQueue = info.bIsQueue;
		nQueueState = info.nQueueState;
		return *this;
	}

	static int GetCallIndex()
	{
		static boost::atomic<int> nCallIndex(0);
		return ++nCallIndex;
	}
};
#pragma pack(pop)

class XhAutoScaleTimeSpanEx
{
public:
	XhAutoScaleTimeSpanEx(bool bAutoLog = false, int nLogMinSpan = 0, const char* strFunction = nullptr, DWORD dwCmdSubType = 0)
	{
		m_dwTicketCount = GetTickCount();
		m_bAutoLog = bAutoLog;
		m_nLogMinSpan = nLogMinSpan;
		m_strFunction = strFunction == nullptr ? "" : strFunction;
		m_dwCmdSubType = dwCmdSubType;
	}

	DWORD Millisecond()
	{
		return GetTickCount() - m_dwTicketCount;
	}

	DWORD Seconds()
	{
		return (GetTickCount() - m_dwTicketCount) / 1000;
	}
	~XhAutoScaleTimeSpanEx()
	{
		if (m_bAutoLog && (GetTickCount() - m_dwTicketCount > m_nLogMinSpan))
		{
			TTRACE("%s 执行指令[%ld] 耗时%dms\r\n", m_strFunction.empty() ? __FUNCTION__ : m_strFunction.c_str(), m_dwCmdSubType, GetTickCount() - m_dwTicketCount);
		}
	}

private:
	DWORD m_dwTicketCount;
	bool m_bAutoLog;
	int m_nLogMinSpan;
	std::string m_strFunction;
	DWORD m_dwCmdSubType;
};

interface ICallbackManagement : public CISocObject
{
	virtual ISOC_INT AddCallBack(ST_CallBackInfo& info,const char* strFunction) = 0;
	ICallbackManagement()
	{
		m_nObjectType = OBJECT_TYPE_CALLBACK_MANAGER;
	}
	//扩展函数
	virtual ISOC_INT ExtendFunction(const ISOC_INT nExtendType,ISOC_DWORDPTR dwExtendData) = 0;
	virtual ~ICallbackManagement(){};
};