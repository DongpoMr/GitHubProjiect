#pragma once
#include "IBFISBankPluginBase.h"
#include "iBFIS_UniqueDefine.h"
#include <string>

class xhBFISServerPZHPluginImp : public IBFISBankPluginBase
{
public:
	xhBFISServerPZHPluginImp(void);
	~xhBFISServerPZHPluginImp(void);
protected:
	virtual int OnRecvData(UINT64 fromAddr, BYTE* pData, int dataLen);
private:
	void ParseDataToStruct(BYTE* pData,ST_BusinessDockMsgInfo& stBusinessDockMsgInfo);
};

