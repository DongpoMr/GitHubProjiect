#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"

interface IBFISSyncClient:public CISocObject
{
	IBFISSyncClient()
	{
		m_nObjectType = OBJECT_TYPE_BFISSYNC_CLIENT;
	}
	virtual ~IBFISSyncClient(){};

	virtual int Init(string strIp,string strPort,string strUser,string strPwd) = 0;
	virtual int UnInit() = 0;

	virtual int DoConnect(IN ISOC_LONG remoteIp, IN ISOC_SHORT remotePort, IN ISOC_DWORDPTR dwReserved = 0) = 0;
	virtual int DoDisConnect(IN ISOC_DWORDPTR dwReserved = 0) = 0;

	virtual int StartSync(IN ISOC_DWORDPTR dwReserved = 0) = 0;
	virtual int StopSync(IN ISOC_DWORDPTR dwReserved = 0) = 0;
	virtual int SetSyncInterval(IN ISOC_INT nSecond, IN ISOC_DWORDPTR dwReserved = 0) = 0;
	virtual int SetLocalUrl(IN const string& szUrl,IN ISOC_DWORDPTR dwReserved = 0) = 0;

    virtual int GetParentSMSInfo(string& strIp, string& strPort, string& strUser, string& strPwd) = 0;
    virtual int GetParentBranchInfo(string& strBranchID, string& strBranchName, string& strParentID) = 0;

	virtual int ExtendFunction(IN const ISOC_INT nExtendType,IN ISOC_DWORDPTR dwExtendData) = 0;
	virtual int DoNotifyData(IN DWORD_PTR d1,IN DWORD_PTR d2, IN string s, IN DWORD_PTR dwReserved = 0) = 0;
	virtual int DoNotifyData(std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2, IN DWORD_PTR dwReserved = 0) = 0;
};
