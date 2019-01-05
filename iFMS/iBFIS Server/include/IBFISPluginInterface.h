#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iBFIS_DataType_Define.h"

interface IBFISBankPluginMsgCb
{
public:
	IBFISBankPluginMsgCb() {}
	virtual ~IBFISBankPluginMsgCb() {}
public:
	virtual void MsgCallback(ST_BusinessDockMsgInfo* pBusinessDockMsgInfo,const IBFIS_DWORDPTR dwCookie = 0,IBFIS_DWORDPTR dwResevered = 0) = 0;
};

interface IBFISBankPluginInterface :CISocObject
{
	IBFISBankPluginInterface()
	{
		m_nObjectType = OBJECT_TYPE_BFIS_BASE_PLUGIN;
	}

	virtual ~IBFISBankPluginInterface() {};
public:
	/******************************** 通用 **********************************/
	virtual ISOC_INT SendDataToBusinessSystem(BYTE* pData,int dataLen) = 0;
	virtual ISOC_INT StartDockListen(ISOC_INT nPort) = 0;
	virtual ISOC_INT StopDockListen(ISOC_INT nPort) = 0;
	virtual ISOC_INT SetMegCb(IBFISBankPluginMsgCb *pMegCb) = 0;

	/********************************* 其它 *********************************/
	virtual void SetParam(std::string strFinancIP,std::string strKernelIP) = 0;
};
