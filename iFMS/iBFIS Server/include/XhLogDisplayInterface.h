#pragma once
#include "IBFISDisplayLogStation.h"
#include <string>
#include "iSOC_MonFactoryManagement.h"
#include <WinBase.h>
#include "IcmsP_Utility.h"
using namespace std;

class XhLogDisplayInterface
{
public:
	XhLogDisplayInterface()
	{

	}
	~XhLogDisplayInterface()
	{

	}

	ISOC_VOID DisplayLog(IN string strLogSrc,IN string strLogContent,IN string strErrorDes,
		IN string strLogDetalInfo,IN ISOC_INT nLogStatus = 1)
	{
		ST_BFISLogInfo logInfo;
		GetLocalTime(&logInfo.stLogTime);
		logInfo.strLogSource = strLogSrc;
		logInfo.strLogContent = strLogContent;
		logInfo.strErrorDes = strErrorDes;
		logInfo.strDetailInfo = strLogDetalInfo;
		logInfo.nLogStatus = nLogStatus;

		TTRACE("%s  %s  %s  %s %s\r\n",strLogSrc.c_str(),strLogContent.c_str(),strErrorDes.c_str(),strLogDetalInfo.c_str(), nLogStatus==1?_T("成功"):_T("失败"));

		iSOC_MonFactoryManagement fmt;
		IBFISDisplayLogStation* pLogStation = (IBFISDisplayLogStation*)fmt.CreateObject(OBJECT_TYPE_BFIS_DISPLAY_LOG_STATION,"",__FUNCTION__);
		if(!pLogStation)
			return;
		pLogStation->DisplayLog(logInfo);
	}

    ISOC_VOID DisplayTaskPlanInfo(IN string strPlanID, IN string strBeginTime, IN string strEndTime, IN ISOC_INT nEnable)
    {
        ST_TaskPlan info;
        info.strPlanID = strPlanID;
        info.strTimeBegin = strBeginTime;
        info.strTimeEnd = strEndTime;
        info.nEnable = nEnable;
        TTRACE("%s  %s  %s  %s\r\n", strPlanID.c_str(), strBeginTime.c_str(), strEndTime.c_str(), nEnable == 1 ? _T("启用") : _T("未启用"));

        iSOC_MonFactoryManagement fmt;
        IBFISDisplayLogStation* pLogStation = (IBFISDisplayLogStation*)fmt.CreateObject(OBJECT_TYPE_BFIS_DISPLAY_LOG_STATION, "", __FUNCTION__);
        if (!pLogStation)
            return;
        pLogStation->DisplayTaskPlanInfo(info);

    }

    ISOC_VOID DisplayConnectionInfo(IN string strUserID, IN string strUserName, IN string strUserIP, IN int nConnected)
    {
        ST_BFISConnectionInfo info;
        info.strUserID = strUserID;
        info.strUserName = strUserName;
        info.strUserIP = strUserIP;
        nConnected > 0 ? info.enState = ST_BFISConnectionInfo::Connected:info.enState = ST_BFISConnectionInfo::DisConnect;
        TTRACE("%s  %s  %s  %s\r\n", strUserID.c_str(), strUserName.c_str(), strUserIP.c_str(), nConnected > 0 ? _T("连接") : _T("断开连接"));
        iSOC_MonFactoryManagement fmt;
        IBFISDisplayLogStation* pLogStation = (IBFISDisplayLogStation*)fmt.CreateObject(OBJECT_TYPE_BFIS_DISPLAY_LOG_STATION, "", __FUNCTION__);
        if (!pLogStation)
            return;
        pLogStation->DisplayConnectionInfo(info);
    }

};

#define DISPLAY_LOG(LogSrc,LogContent,ErrDes,LogDetail,LogStat) {\
								XhLogDisplayInterface logInter;\
								logInter.DisplayLog(LogSrc,LogContent,ErrDes,LogDetail,LogStat);\
								}

#define DISPLAY_TASKPLAN(taskID, taskBegin, taskEnd, taskEnable) {\
                                XhLogDisplayInterface logInter;\
                                logInter.DisplayTaskPlanInfo(taskID, taskBegin, taskEnd, taskEnable);\
                                }

#define DISPLAY_CONNECTION(userid, username, userip, connectstate) {\
                                XhLogDisplayInterface logInter;\
                                logInter.DisplayConnectionInfo(userid, username, userip, connectstate);\
                                }

#define DCS_SYSTEM_LOG _T("signaling")