#pragma once
#include "IBFISBankPluginBase.h"
#include "iBFIS_UniqueDefine.h"
#include <string>
#include "IBFISCommunicateSyncServer.h"
#include "IBFISDataProvider.h"

class xhBFISServerNCPluginImp : public IBFISBankPluginBase
{
public:
	xhBFISServerNCPluginImp(void);
	~xhBFISServerNCPluginImp(void);
protected:
	virtual int OnRecvData(UINT64 fromAddr, BYTE* pData, int dataLen);
private:
	void ParseDataToStruct(BYTE* pData,ST_BusinessDockMsgInfo& stBusinessDockMsgInfo);
	//void GetRandomSerialNum(string& strRandomSerialNum);
	virtual ISOC_INT SendDataToBusinessSystem(BYTE* pData,int dataLen);
	void GetRandomSerialNum(string& strRandomSerialNum);
private:
	UINT64 m_fromAdd;
	string m_strPreMsg;
}; 

