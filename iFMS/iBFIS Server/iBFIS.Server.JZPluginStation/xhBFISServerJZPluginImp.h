#pragma once
#include "IBFISBankPluginBase.h"
#include <string>
#include <memory>

class xhBFISServerJZPluginImp : public IBFISBankPluginBase
{
public:
	xhBFISServerJZPluginImp(void);
	~xhBFISServerJZPluginImp(void);
protected:
	virtual int OnRecvData(UINT64 fromAddr, BYTE* pData, int dataLen);
private:
	void SetParam(std::string strFinancIP,std::string strKernelIP);
	virtual ISOC_INT SendDataToBusinessSystem(BYTE* pData, int dataLen);
	void FinancParseDataToStruct(BYTE* pData,ST_BusinessDockMsgInfo& stBusinessDockMsgInfo);
	void KernelParseDataToStruct(BYTE* pData,ST_BusinessDockMsgInfo& stBusinessDockMsgInfo);
private:
	std::string        m_strCoreSystemIP;
	std::string        m_strFinancialSystemIP;
	UINT64			   m_fromAdd;
};

