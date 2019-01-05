#pragma once

#include "iSOC_Datatype_Define.h"
#include "iSOCObject.h"
//#include "iBFS_Sync_UniqueDefine.h"
//#include "iSOC_UnitDefine.h"
#include "iBFIS_UniqueDefine.h"
#include "iSOC_PrivateStructDefine.h"
#include <string>
using namespace std;


struct ST_BFISLogInfo
{
	SYSTEMTIME  stLogTime; //系统时间
	string		strLogSource; //事件来源
	string		strLogContent;//事件内容
	string		strErrorDes;//事件错误原因	
	string		strDetailInfo; //事件详细内容,可以是信令内容等
	int	nLogStatus;//事件状态，1：成功  0：失败

	ST_BFISLogInfo()
	{
		ZeroMemory(&stLogTime,sizeof(SYSTEMTIME));
		nLogStatus = 0;
	}

	ST_BFISLogInfo(string strSource,string strContent,string strErrDes,string strDetail,int nStatus = 1,SYSTEMTIME* pTime = NULL)
	{
		if(!pTime)
		{
			GetLocalTime(&stLogTime);
		}
		else
		{
			stLogTime = *pTime;
		}
		strLogSource = strSource;
		strLogContent = strContent;
		strErrorDes  = strErrDes;
		nLogStatus = nStatus;
		strDetailInfo = strDetail;
	}

	ST_BFISLogInfo& operator=(const ST_BFISLogInfo& info)
	{
		this->stLogTime = info.stLogTime;
		this->strErrorDes = info.strErrorDes;
		this->strLogContent = info.strLogContent;
		this->strLogSource = info.strLogSource;
		this->strDetailInfo = info.strDetailInfo;
		this->nLogStatus = info.nLogStatus;
		return *this;
	}
};

struct ST_BFISConnectionInfo
{
    enum ConnectionState
    {
        Connected = 1,
        DisConnect
    };
    std::string strUserID;
    std::string strUserName;
    std::string strUserIP;
    ConnectionState enState;
};

interface IBFISDisplayLogCallbackSkin
{
	virtual ~IBFISDisplayLogCallbackSkin(){};

	virtual int OnGotLogInfo(IN const ST_BFISLogInfo& info,IN DWORD_PTR dwReserved = NULL) = 0;
    virtual int OnGotTaskPlanInfo(IN const ST_TaskPlan& info, IN DWORD_PTR dwReserved = NULL) = 0;
    virtual int OnGotConnectionInfo(IN const ST_BFISConnectionInfo& info, IN DWORD_PTR dwReserved = NULL) = 0;
};

//日志显示接口
interface IBFISDisplayLogStation : public CISocObject
{
	IBFISDisplayLogStation()
	{
		m_nObjectType = OBJECT_TYPE_BFIS_DISPLAY_LOG_STATION;
	}

	virtual ~IBFISDisplayLogStation(){};

	//显示日志信息
	virtual int DisplayLog(IN const ST_BFISLogInfo& info,IN DWORD_PTR dwReserved = NULL) = 0;
    virtual int DisplayTaskPlanInfo(IN const ST_TaskPlan& info, IN DWORD_PTR dwReserved = NULL) = 0;
    virtual int DisplayConnectionInfo(IN const ST_BFISConnectionInfo& info, IN DWORD_PTR dwReserved = NULL) = 0;
	//设置显示日志信息的处理接口，外面使用的时候不需要设置，只需要在应用程序启动的时候设置一次就是了，其它地方要显示日志只需要使用显示的接口
	virtual int SetDisplayLogCallbackSkin(IN IBFISDisplayLogCallbackSkin* pSkin) = 0;
	//扩展函数
	virtual int ExtendFunc(IN int nExType,IN DWORD_PTR dwExtendData,IN DWORD_PTR dwReserved = NULL) = 0;
};