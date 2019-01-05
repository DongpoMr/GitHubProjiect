#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iBFIS_UniqueDefine.h"
#include "IBFISTaskStation.h"


interface IBFISCommunicateSyncServer : public CISocObject
{
	IBFISCommunicateSyncServer()
	{
		m_nObjectType = OBJECT_TYPE_BFIS_COMMUNICATESYNCSERVER;
	}
	virtual ~IBFISCommunicateSyncServer(){};

	//
	virtual ISOC_BOOL Init() = 0;
	virtual ISOC_BOOL UnInit() = 0;

	//设置监听端口(同时监听SyncClient和Client)
	virtual int DoListenOn(IN long localIp, IN short localPort, IN DWORD_PTR dwReserved = 0) = 0;
	//停止监听端口
	virtual int StopListen(IN DWORD_PTR dwReserved = 0) = 0;

	//发送数据到控制端
	virtual int DoSendData(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN string s1, IN DWORD_PTR dwReserved = 0) = 0;
	virtual int DoSendData(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN std::vector<std::string>& v1, IN DWORD_PTR dwReserved = 0) = 0;
	virtual int DoSendData(IN HANDLE hClient, IN DBOperType enType, IN DWORD_PTR d1, IN BYTE* pData, IN int nDataSize, IN DWORD_PTR dwReserved = 0) = 0;

	//可扩展函数接口
	virtual int  ExtendFunction(IN const int nExtendType, IN DWORD_PTR dwExtendData) = 0;

	//注册消息处理对象
	virtual int RegisterRecvMessageCallbackSkin(IN DWORD_PTR dwCmdID,IN IBFISTaskStation* pProcessStation,IN ISOC_DWORDPTR dwReserved = 0) = 0;
	//取消消息任务处理对象
	virtual int UnRegisterRecvMessageCallbackSkin(IN DWORD_PTR dwCmdID,IN IBFISTaskStation* pProcessStation,IN ISOC_DWORDPTR dwReserved = 0)= 0;

	//
	virtual int AddNotifyMsg(IN DBOperType enType, IN DWORD_PTR dwCmdID,IN string s1,IN DWORD_PTR dwReserved = 0) = 0;
	virtual int AddNotifyMsg(IN DBOperType enType, IN DWORD_PTR dwCmdID,IN std::vector<std::string>& v1,IN DWORD_PTR dwRvieserved = 0) = 0;

    virtual int SetOfflineSyscData(vector<ST_BranchInfo>& vecBranchInfo, vector<ST_EmployeeInfo>& vecEmployeeInfo) = 0;
    virtual int GetOfflineSyscData(vector<ST_BranchInfo>& vecBranchInfo, vector<ST_EmployeeInfo>& vecEmployeeInfo) = 0;
	virtual int CheckIsTopServer(int nNum) = 0;
};