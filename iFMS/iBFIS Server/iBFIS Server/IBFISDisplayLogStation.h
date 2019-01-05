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
	SYSTEMTIME  stLogTime; //ϵͳʱ��
	string		strLogSource; //�¼���Դ
	string		strLogContent;//�¼�����
	string		strErrorDes;//�¼�����ԭ��	
	string		strDetailInfo; //�¼���ϸ����,�������������ݵ�
	int	nLogStatus;//�¼�״̬��1���ɹ�  0��ʧ��

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

//��־��ʾ�ӿ�
interface IBFISDisplayLogStation : public CISocObject
{
	IBFISDisplayLogStation()
	{
		m_nObjectType = OBJECT_TYPE_BFIS_DISPLAY_LOG_STATION;
	}

	virtual ~IBFISDisplayLogStation(){};

	//��ʾ��־��Ϣ
	virtual int DisplayLog(IN const ST_BFISLogInfo& info,IN DWORD_PTR dwReserved = NULL) = 0;
    virtual int DisplayTaskPlanInfo(IN const ST_TaskPlan& info, IN DWORD_PTR dwReserved = NULL) = 0;
    virtual int DisplayConnectionInfo(IN const ST_BFISConnectionInfo& info, IN DWORD_PTR dwReserved = NULL) = 0;
	//������ʾ��־��Ϣ�Ĵ���ӿڣ�����ʹ�õ�ʱ����Ҫ���ã�ֻ��Ҫ��Ӧ�ó���������ʱ������һ�ξ����ˣ������ط�Ҫ��ʾ��־ֻ��Ҫʹ����ʾ�Ľӿ�
	virtual int SetDisplayLogCallbackSkin(IN IBFISDisplayLogCallbackSkin* pSkin) = 0;
	//��չ����
	virtual int ExtendFunc(IN int nExType,IN DWORD_PTR dwExtendData,IN DWORD_PTR dwReserved = NULL) = 0;
};