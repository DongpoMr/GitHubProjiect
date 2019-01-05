#pragma once
#include <memory>
#include "Icms_PIocpSocket.h"
#include "iBFIS_UniqueDefine.h"
#include "IBFISPluginInterface.h"
#include "IcmsP_Utility.h"
#include "iSOC_ErrorDef.h"
#include "XhLogDisplayInterface.h"

interface IBFISBankPluginBase :public IBFISBankPluginInterface, public ITcpCallbackSink
{
	IBFISBankPluginBase()
		:m_spTcpListen(nullptr),m_nListenPort(0),m_pDataInfoCb(nullptr)
	{
	}
	virtual ~IBFISBankPluginBase() {};
public:
	virtual ISOC_INT SendDataToBusinessSystem(BYTE* pData,int dataLen){return 1;}
	virtual ISOC_INT StartDockListen(ISOC_INT nPort)
	{
		m_nListenPort = nPort;
		if(m_spTcpListen == nullptr)
			m_spTcpListen.reset(new iCMS_PTcpListner());

		if( m_spTcpListen )
		{
			m_spTcpListen->SetCallBackSink(this);
			m_spTcpListen->DoListenOn (0, m_nListenPort);
			m_spTcpListen->CheckDataHeaderControl(FALSE);
		}
		return ISOC_ERR_SUCCESS;
	}

	virtual ISOC_INT StopDockListen(ISOC_INT nPort)
	{
		int bRet = 0;
		if( m_spTcpListen)
			bRet = m_spTcpListen->StopListen();

		if(bRet > 0)
			return ISOC_ERR_SUCCESS;

		return ISOC_ERR_FAILED;
	}

	virtual ISOC_INT SetMegCb(IBFISBankPluginMsgCb *pMegCb)
	{
		STRY;
		if (nullptr == pMegCb)
			return ISOC_ERR_INVALID_PARAMETER;

		m_pDataInfoCb = pMegCb;
		SCATCH;
		return ISOC_ERR_UNKNOW_ERROR;
	}

	virtual std::string UTF8ToGDB(const char* str)
	{
		std::string result;
		WCHAR *strSrc;
		TCHAR *szRes;

		//获得临时变量的大小
		int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
		strSrc = new WCHAR[i+1];
		MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

		//获得临时变量的大小
		i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
		szRes = new TCHAR[i+1];
		WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

		result = szRes;
		delete []strSrc;
		delete []szRes;
		return result;
	}
protected:
	virtual void SetParam(std::string strFinancIP,std::string strKernelIP)
	{

	}
	virtual int OnRecvData(UINT64 fromAddr, BYTE* pData, int dataLen) = 0;
	virtual int OnConnected(UINT64 fromAddr,UINT64 localAddr)
	{
		TTRACE("插件-连接成功通知[%llu]\r\n", fromAddr);
		return TRUE;
	}
	virtual int OnClosed(UINT64 fromAddr)
	{
		TTRACE("插件-连接断开通知[%llu]\r\n", fromAddr);
		return TRUE;
	}
	virtual int OnReConnected(UINT64 fromAddr)
	{
		return TRUE;
	}
protected:
	std::shared_ptr<iCMS_PTcpListner> m_spTcpListen;
	int                m_nListenPort;
	IBFISBankPluginMsgCb *m_pDataInfoCb;
};
