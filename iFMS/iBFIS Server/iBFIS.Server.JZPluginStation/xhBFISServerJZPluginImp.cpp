#include "StdAfx.h"
#include "xhBFISServerJZPluginImp.h"
#include "xhBFISSyncServerRouterImp.h"
#include "iBFIS_DataType_Define.h"


xhBFISServerJZPluginImp::xhBFISServerJZPluginImp(void):m_fromAdd(0)
{
}


xhBFISServerJZPluginImp::~xhBFISServerJZPluginImp(void)
{
}
ISOC_INT xhBFISServerJZPluginImp::SendDataToBusinessSystem(BYTE* pData, int dataLen)
{
	STRY;
	if (nullptr == pData || dataLen <= 0)
		return ISOC_ERR_INVALID_PARAMETER;
	int nRet = -1;
	if (m_spTcpListen)
	{
		nRet = m_spTcpListen->SendData(m_fromAdd, pData, dataLen);
	}
	SFTRACE("Docking","对接信息返回状态[%d]\r\n", nRet);
	if (nRet <= 0)
	{
		//DISPLAY_LOG("对接模块","发送到核心服务器信息","失败","",nRet);
		return ISOC_ERR_FAILED;
	}

	return ISOC_ERR_SUCCESS;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}
int xhBFISServerJZPluginImp::OnRecvData( UINT64 fromAddr, BYTE* pData, int dataLen )
{
	DISPLAY_LOG("对接模块", "收到银行业务系统发来的对接信息", "成功", "", 1);
	m_fromAdd = fromAddr;
	char pDockIp[30] ={0};
	ICMS_IP_INT64TOSTR(fromAddr,pDockIp);
	std::string strDocpIp = pDockIp;
	std::string strInfo;
	SFTRACE("Docking", "银行业务系统IP[%s]  理财配置IP[%s] 核心配置IP[%s]发来的对接信息[%s]\r\n", strDocpIp.c_str(), m_strFinancialSystemIP.c_str(), m_strCoreSystemIP.c_str(),pData);
	ST_BusinessDockMsgInfo stBusinessDockMsgInfo;	
	if (pData && m_pDataInfoCb)
	{
		if (std::string::npos != strDocpIp.find(m_strFinancialSystemIP))
		{
			FinancParseDataToStruct(pData,stBusinessDockMsgInfo); 
			m_pDataInfoCb->MsgCallback(&stBusinessDockMsgInfo);
		}
		if (std::string::npos != strDocpIp.find(m_strCoreSystemIP))
		{
			KernelParseDataToStruct(pData,stBusinessDockMsgInfo);
			m_pDataInfoCb->MsgCallback(&stBusinessDockMsgInfo);
		}
	}  
	return TRUE;
}

void xhBFISServerJZPluginImp::KernelParseDataToStruct(BYTE* pData,ST_BusinessDockMsgInfo& stBusinessDockMsgInfo)
{
	STRY;
	if (nullptr != pData)
	{
		BYTE* ObjectDate = pData + 8;
		char* strObjectDate = (char*)ObjectDate;    
		int nLen = strlen(strObjectDate);
		//替换空格
		int i = 0;
		for (strObjectDate[i]; i < nLen; i++ )
		{
			if(' ' == strObjectDate[i])
			{
				strObjectDate[i] = '\0';
			}
		}
		IBFIS_ST_BusinessDockMsgInfo stBusinessDockMsgInfoPrase;
		strncpy(stBusinessDockMsgInfoPrase.strBusinessCode,strObjectDate,4);
		strObjectDate += 4;
		strncpy(stBusinessDockMsgInfoPrase.strTradeSerialNum,strObjectDate,32);
		strObjectDate += 32;
		//string strClientName = UTF8ToGDB(strObjectDate);
		strncpy(stBusinessDockMsgInfoPrase.strClientName,strObjectDate,60);
		strObjectDate += 60;
		strncpy(stBusinessDockMsgInfoPrase.strCredenitialsType,strObjectDate,1);
		strObjectDate += 1;
		strncpy(stBusinessDockMsgInfoPrase.strCredenitialNum,strObjectDate,20);
		strObjectDate += 20;
		strncpy(stBusinessDockMsgInfoPrase.strMediumType,strObjectDate,3);
		strObjectDate += 3;
		strncpy(stBusinessDockMsgInfoPrase.strMediumNum,strObjectDate,32);
		strObjectDate += 32;
		string strBusinessCode = stBusinessDockMsgInfoPrase.strBusinessCode;
		if ("6A11" == strBusinessCode)
		{
			ZeroMemory(stBusinessDockMsgInfoPrase.strBusinessCode,sizeof(stBusinessDockMsgInfoPrase.strBusinessCode)); 
			strcpy(stBusinessDockMsgInfoPrase.strBusinessCode,"903");
			strncpy(stBusinessDockMsgInfoPrase.strChannelDate,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strDateTime,strObjectDate,6);
			strObjectDate += 6;
			strncpy(stBusinessDockMsgInfoPrase.strOperatorId,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strJDBRID,strObjectDate,10);
			strObjectDate += 10;
			strncpy(stBusinessDockMsgInfoPrase.strFinancSerialNum,strObjectDate,24);
			strObjectDate += 24;
			/*strncpy(stBusinessDockMsgInfoPrase.strRepondCode,strObjectDate,4);
			strObjectDate += 4;*/
		}
		if ("6A12" == strBusinessCode )
		{
			ZeroMemory(stBusinessDockMsgInfoPrase.strBusinessCode,sizeof(stBusinessDockMsgInfoPrase.strBusinessCode)); 
			strcpy(stBusinessDockMsgInfoPrase.strBusinessCode,"904");
			strncpy(stBusinessDockMsgInfoPrase.strProduceCode,strObjectDate,32);
			strObjectDate += 32;
			strncpy(stBusinessDockMsgInfoPrase.strProduceRiskLevel,strObjectDate,1);
			strObjectDate += 1;
			strncpy(stBusinessDockMsgInfoPrase.strClientRiskLevel,strObjectDate,1);
			strObjectDate += 1;
			strncpy(stBusinessDockMsgInfoPrase.strOperatorId,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strJDBRID,strObjectDate,10);
			strObjectDate += 10;
			strncpy(stBusinessDockMsgInfoPrase.strFinancSerialNum,strObjectDate,24);
			strObjectDate += 24;
			/*strncpy(stBusinessDockMsgInfoPrase.strRepondCode,strObjectDate,4);
			strObjectDate += 4;*/
		}
		if ("6A13" == strBusinessCode )
		{
			ZeroMemory(stBusinessDockMsgInfoPrase.strBusinessCode,sizeof(stBusinessDockMsgInfoPrase.strBusinessCode)); 
			strcpy(stBusinessDockMsgInfoPrase.strBusinessCode,"906");
			strncpy(stBusinessDockMsgInfoPrase.strChannelDate,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strDateTime,strObjectDate,6);
			strObjectDate += 6;
			strncpy(stBusinessDockMsgInfoPrase.strProduceCode,strObjectDate,32);
			strObjectDate += 32;
			strncpy(stBusinessDockMsgInfoPrase.strOperatorId,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strJDBRID,strObjectDate,10);
			strObjectDate += 10;
			strncpy(stBusinessDockMsgInfoPrase.strFinancSerialNum,strObjectDate,24);
			strObjectDate += 24;
			/*strncpy(stBusinessDockMsgInfoPrase.strRepondCode,strObjectDate,4);
			strObjectDate += 4;*/
		}
		if ("6A14" == strBusinessCode )
		{
			ZeroMemory(stBusinessDockMsgInfoPrase.strBusinessCode,sizeof(stBusinessDockMsgInfoPrase.strBusinessCode)); 
			strcpy(stBusinessDockMsgInfoPrase.strBusinessCode,"905");
			strncpy(stBusinessDockMsgInfoPrase.strChannelDate,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strDateTime,strObjectDate,6);
			strObjectDate += 6;
			//string strClientName = UTF8ToGDB(strObjectDate);
			strncpy(stBusinessDockMsgInfoPrase.strProduceName,strObjectDate/*strClientName.c_str()*/,32);
			strObjectDate += 32;
			strncpy(stBusinessDockMsgInfoPrase.strProduceCode,strObjectDate,32);
			strObjectDate += 32;
			strncpy(stBusinessDockMsgInfoPrase.strCancelBusinessType,strObjectDate,1);
			strObjectDate += 1;
			strncpy(stBusinessDockMsgInfoPrase.strOperatorId,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strJDBRID,strObjectDate,10);
			strObjectDate += 10;
			strncpy(stBusinessDockMsgInfoPrase.strFinancSerialNum,strObjectDate,24);
			strObjectDate += 24;
			/*strncpy(stBusinessDockMsgInfoPrase.strRepondCode,strObjectDate,4);
			strObjectDate += 4;*/
		}
		if ("6E21" == strBusinessCode )
		{
			ZeroMemory(stBusinessDockMsgInfoPrase.strBusinessCode,sizeof(stBusinessDockMsgInfoPrase.strBusinessCode)); 
			strcpy(stBusinessDockMsgInfoPrase.strBusinessCode,"907");
			strncpy(stBusinessDockMsgInfoPrase.strChannelDate,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strDateTime,strObjectDate,6);
			strObjectDate += 20;
			strncpy(stBusinessDockMsgInfoPrase.strOperatorId,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strJDBRID,strObjectDate,10);
			strObjectDate += 10;
			/*strncpy(stBusinessDockMsgInfoPrase.strRepondCode,strObjectDate,4);
			strObjectDate += 4;*/ 
		}
		if ("6E22" == strBusinessCode)
		{
			ZeroMemory(stBusinessDockMsgInfoPrase.strBusinessCode,sizeof(stBusinessDockMsgInfoPrase.strBusinessCode)); 
			strcpy(stBusinessDockMsgInfoPrase.strBusinessCode,"908");
			strncpy(stBusinessDockMsgInfoPrase.strChannelDate,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strDateTime,strObjectDate,6);
			strObjectDate += 20;
			strncpy(stBusinessDockMsgInfoPrase.strOperatorId,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strJDBRID,strObjectDate,10);
			strObjectDate += 10;
		}
		if ("6E23" == strBusinessCode)
		{
			ZeroMemory(stBusinessDockMsgInfoPrase.strBusinessCode,sizeof(stBusinessDockMsgInfoPrase.strBusinessCode)); 
			strcpy(stBusinessDockMsgInfoPrase.strBusinessCode,"909");
			strncpy(stBusinessDockMsgInfoPrase.strChannelDate,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strDateTime,strObjectDate,6);
			strObjectDate += 6;
			strncpy(stBusinessDockMsgInfoPrase.strOperatorId,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strJDBRID,strObjectDate,10);
			strObjectDate += 10;
		}
		if ("6E24"== strBusinessCode)
		{
			ZeroMemory(stBusinessDockMsgInfoPrase.strBusinessCode,sizeof(stBusinessDockMsgInfoPrase.strBusinessCode)); 
			strcpy(stBusinessDockMsgInfoPrase.strBusinessCode,"910");
			strncpy(stBusinessDockMsgInfoPrase.strChannelDate,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strDateTime,strObjectDate,6);
			strObjectDate += 20;
			strncpy(stBusinessDockMsgInfoPrase.strOperatorId,strObjectDate,8);
			strObjectDate += 8;
			strncpy(stBusinessDockMsgInfoPrase.strJDBRID,strObjectDate,10);
			strObjectDate += 10;
		}
		stBusinessDockMsgInfo.strChannelCode = stBusinessDockMsgInfoPrase.strChannelCode;
		stBusinessDockMsgInfo.strServiceCode = stBusinessDockMsgInfoPrase.strServiceCode;
		stBusinessDockMsgInfo.strJDBRID = stBusinessDockMsgInfoPrase.strJDBRID;
		stBusinessDockMsgInfo.strOperatorId = stBusinessDockMsgInfoPrase.strOperatorId;
		stBusinessDockMsgInfo.strChannelSerialNum = stBusinessDockMsgInfoPrase.strChannelSerialNum; 
		stBusinessDockMsgInfo.strKernelSerialNum = stBusinessDockMsgInfoPrase.strKernelSerialNum;
		stBusinessDockMsgInfo.strDateTime = stBusinessDockMsgInfoPrase.strDateTime;
		stBusinessDockMsgInfo.strChannelDate = stBusinessDockMsgInfoPrase.strChannelDate;
		stBusinessDockMsgInfo.strRepondCode = stBusinessDockMsgInfoPrase.strRepondCode;
		stBusinessDockMsgInfo.strChineseDescribeInfo = stBusinessDockMsgInfoPrase.strChineseDescribeInfo;
		stBusinessDockMsgInfo.strBusinessCode = stBusinessDockMsgInfoPrase.strBusinessCode;  
		stBusinessDockMsgInfo.strBusinessName = stBusinessDockMsgInfoPrase.strBusinessName;
		stBusinessDockMsgInfo.strBusinessStatus = stBusinessDockMsgInfoPrase.strBusinessStatus;
		stBusinessDockMsgInfo.strProduceCode = stBusinessDockMsgInfoPrase.strProduceCode;
		stBusinessDockMsgInfo.strObjectProduceCode = stBusinessDockMsgInfoPrase.strObjectProduceCode;
		stBusinessDockMsgInfo.strFundName = stBusinessDockMsgInfoPrase.strFundName;
		stBusinessDockMsgInfo.strProduceName = stBusinessDockMsgInfoPrase.strProduceName;
		stBusinessDockMsgInfo.strIncomeType = stBusinessDockMsgInfoPrase.strIncomeType;
		stBusinessDockMsgInfo.strBusinessDate = stBusinessDockMsgInfoPrase.strBusinessDate;
		stBusinessDockMsgInfo.strClientName = stBusinessDockMsgInfoPrase.strClientName;
		stBusinessDockMsgInfo.strCredenitialsType = stBusinessDockMsgInfoPrase.strCredenitialsType;
		stBusinessDockMsgInfo.strCredenitialNum = stBusinessDockMsgInfoPrase.strCredenitialNum;
		stBusinessDockMsgInfo.strMediumType = stBusinessDockMsgInfoPrase.strMediumType;
		stBusinessDockMsgInfo.strMediumNum = stBusinessDockMsgInfoPrase.strMediumNum;
		stBusinessDockMsgInfo.strClientRiskLevel = stBusinessDockMsgInfoPrase.strClientRiskLevel;
		stBusinessDockMsgInfo.strProduceRiskLevel = stBusinessDockMsgInfoPrase.strProduceRiskLevel;
		stBusinessDockMsgInfo.strFundType = stBusinessDockMsgInfoPrase.strFundType;
		stBusinessDockMsgInfo.strCancelBusinessType = stBusinessDockMsgInfoPrase.strCancelBusinessType;
		stBusinessDockMsgInfo.strFinancSerialNum = stBusinessDockMsgInfoPrase.strFinancSerialNum;
		stBusinessDockMsgInfo.strTradeSerialNum = stBusinessDockMsgInfoPrase.strTradeSerialNum;
		stBusinessDockMsgInfo.nBootFlag = stBusinessDockMsgInfo.strClientName.empty() ? 1 : 3;
		stBusinessDockMsgInfo.nSystemType = 2;
		stBusinessDockMsgInfo.strRepondCode = "2";
		SFTRACE("Docking","解析核心系统发来的数据：strServiceCode:%s,strJDBRID:%s,strOperatorId:%s,strChannelSerialNum:%s,strKernelSerialNum:%s,strDateTime:%s,\
			strChannelDate:%s,strRepondCode:%s,strChineseDescribeInfo:%s,strBusinessCode:%s ,sstrBusinessName:%s ,strBusinessStatus:%s,\
			strProduceCode:%s,strObjectProduceCode:%s,strFundName:%s,strProduceName:%s,strIncomeType:%s ,strBusinessDate:%s,strClientName:%s,\
			strCredenitialsType:%s,sstrCredenitialNum:%s,strMediumType:%s,strMediumNum:%s,strClientRiskLevel:%s,strProduceRiskLevel:%s,\
			strFundType:%s,strCancelBusinessType:%s,nSystemType:%d,nbootFlag:%d,CancelBusinessType:%s,TradeSerialNum:%s \r\n",
			stBusinessDockMsgInfo.strServiceCode.c_str(),stBusinessDockMsgInfo.strJDBRID.c_str(),stBusinessDockMsgInfo.strOperatorId.c_str(),
		stBusinessDockMsgInfo.strChannelSerialNum.c_str(),stBusinessDockMsgInfo.strKernelSerialNum.c_str(),stBusinessDockMsgInfo.strDateTime.c_str(),
		stBusinessDockMsgInfo.strChannelDate.c_str(),stBusinessDockMsgInfo.strRepondCode.c_str(),stBusinessDockMsgInfo.strChineseDescribeInfo.c_str(),
		stBusinessDockMsgInfo.strBusinessCode.c_str() ,stBusinessDockMsgInfo.strBusinessName.c_str() ,stBusinessDockMsgInfo.strBusinessStatus.c_str(),
		stBusinessDockMsgInfo.strProduceCode.c_str(),stBusinessDockMsgInfo.strObjectProduceCode.c_str(),stBusinessDockMsgInfo.strFundName.c_str(),stBusinessDockMsgInfo.strProduceName.c_str(),
		stBusinessDockMsgInfo.strIncomeType.c_str() ,stBusinessDockMsgInfo.strBusinessDate.c_str() ,stBusinessDockMsgInfo.strClientName.c_str(),
		stBusinessDockMsgInfo.strCredenitialsType.c_str(),stBusinessDockMsgInfo.strCredenitialNum.c_str() ,stBusinessDockMsgInfo.strMediumType.c_str(),
		stBusinessDockMsgInfo.strMediumNum.c_str(),stBusinessDockMsgInfo.strClientRiskLevel.c_str(),stBusinessDockMsgInfo.strProduceRiskLevel.c_str(),
		stBusinessDockMsgInfo.strFundType.c_str(),stBusinessDockMsgInfo.strCancelBusinessType.c_str(),stBusinessDockMsgInfo.nSystemType,stBusinessDockMsgInfo.nBootFlag,
		stBusinessDockMsgInfo.strFinancSerialNum.c_str(),stBusinessDockMsgInfo.strTradeSerialNum.c_str());
	}    
	SCATCH;
}

void xhBFISServerJZPluginImp::SetParam(std::string strFinancIP,std::string strKernelIP)
{
	m_strCoreSystemIP = strKernelIP;
	m_strFinancialSystemIP = strFinancIP;
}

void xhBFISServerJZPluginImp::FinancParseDataToStruct(BYTE* pData,ST_BusinessDockMsgInfo& stBusinessDockMsgInfo)
{	
	STRY;
	if (nullptr != pData)
	{
		BYTE* ObjectDate = pData + 8;
		char* strObjectDate = (char*)ObjectDate;    
		int nLen = strlen(strObjectDate);
		//替换空格
		int i = 0;
		for (strObjectDate[i]; i < nLen; i++ )
		{
			if(' ' == strObjectDate[i])
			{
				strObjectDate[i] = '\0';
			}
		}
		IBFIS_ST_BusinessDockMsgInfo stBusinessDockMsgInfoPrase;
		strncpy(stBusinessDockMsgInfoPrase.strChannelCode,strObjectDate,10);
		strObjectDate += 10;
		strncpy(stBusinessDockMsgInfoPrase.strServiceCode,strObjectDate,8);
		strObjectDate += 8;
		strncpy(stBusinessDockMsgInfoPrase.strJDBRID,strObjectDate,8);
		strObjectDate += 8;
		strncpy(stBusinessDockMsgInfoPrase.strOperatorId,strObjectDate,20);
		strObjectDate += 20;
		strncpy(stBusinessDockMsgInfoPrase.strChannelSerialNum,strObjectDate,24);
		strObjectDate += 24;
		strncpy(stBusinessDockMsgInfoPrase.strKernelSerialNum,strObjectDate,16);
		strObjectDate += 16;
		strncpy(stBusinessDockMsgInfoPrase.strDateTime,strObjectDate,14);
		strObjectDate += 14;
		strncpy(stBusinessDockMsgInfoPrase.strChannelDate,strObjectDate,8);
		strObjectDate += 8;
		strncpy(stBusinessDockMsgInfoPrase.strRepondCode,strObjectDate,4);
		strObjectDate += 4;
		strncpy(stBusinessDockMsgInfoPrase.strChineseDescribeInfo,strObjectDate,40);
		strObjectDate += 40;
		strncpy(stBusinessDockMsgInfoPrase.strBusinessCode,strObjectDate,6);
		strObjectDate += 6;   
		strncpy(stBusinessDockMsgInfoPrase.strBusinessName,strObjectDate,64);
		strObjectDate += 64;
		strncpy(stBusinessDockMsgInfoPrase.strBusinessStatus,strObjectDate,4);
		strObjectDate += 4;
		strncpy(stBusinessDockMsgInfoPrase.strProduceCode,strObjectDate,32);
		strObjectDate += 32;
		strncpy(stBusinessDockMsgInfoPrase.strObjectProduceCode,strObjectDate,32);
		strObjectDate += 32;
		strncpy(stBusinessDockMsgInfoPrase.strFundName,strObjectDate,128);
		strObjectDate += 128;
		strncpy(stBusinessDockMsgInfoPrase.strProduceName,strObjectDate,128);
		strObjectDate += 128;
		strncpy(stBusinessDockMsgInfoPrase.strIncomeType,strObjectDate,1);
		strObjectDate += 1;
		strncpy(stBusinessDockMsgInfoPrase.strBusinessDate,strObjectDate,8);
		strObjectDate += 8;
		strncpy(stBusinessDockMsgInfoPrase.strClientName,strObjectDate,60);
		strObjectDate += 60;
		strncpy(stBusinessDockMsgInfoPrase.strCredenitialsType,strObjectDate,1);
		strObjectDate += 1;
		strncpy(stBusinessDockMsgInfoPrase.strCredenitialNum,strObjectDate,20);
		strObjectDate += 20;
		strncpy(stBusinessDockMsgInfoPrase.strMediumType,strObjectDate,4);
		strObjectDate += 4;
		strncpy(stBusinessDockMsgInfoPrase.strMediumNum,strObjectDate,32);
		strObjectDate += 32;
		strncpy(stBusinessDockMsgInfoPrase.strClientRiskLevel,strObjectDate,2);
		strObjectDate += 2;
		strncpy(stBusinessDockMsgInfoPrase.strProduceRiskLevel,strObjectDate,2);
		strObjectDate += 2;
		strncpy(stBusinessDockMsgInfoPrase.strFundType,strObjectDate,3);
		strObjectDate += 3;
		strncpy(stBusinessDockMsgInfoPrase.strCancelBusinessType,strObjectDate,1);
		stBusinessDockMsgInfo.strChannelCode = stBusinessDockMsgInfoPrase.strChannelCode;
		stBusinessDockMsgInfo.strServiceCode = stBusinessDockMsgInfoPrase.strServiceCode;
		stBusinessDockMsgInfo.strJDBRID = stBusinessDockMsgInfoPrase.strJDBRID;
		stBusinessDockMsgInfo.strOperatorId = stBusinessDockMsgInfoPrase.strOperatorId;
		stBusinessDockMsgInfo.strChannelSerialNum = stBusinessDockMsgInfoPrase.strChannelSerialNum;
		stBusinessDockMsgInfo.strKernelSerialNum = stBusinessDockMsgInfoPrase.strKernelSerialNum;
		stBusinessDockMsgInfo.strDateTime = stBusinessDockMsgInfoPrase.strDateTime;
		stBusinessDockMsgInfo.strChannelDate = stBusinessDockMsgInfoPrase.strChannelDate;
		stBusinessDockMsgInfo.strRepondCode = stBusinessDockMsgInfoPrase.strRepondCode;
		stBusinessDockMsgInfo.strChineseDescribeInfo = stBusinessDockMsgInfoPrase.strChineseDescribeInfo;
		stBusinessDockMsgInfo.strBusinessCode = stBusinessDockMsgInfoPrase.strBusinessCode;  
		stBusinessDockMsgInfo.strBusinessName = stBusinessDockMsgInfoPrase.strBusinessName;
		stBusinessDockMsgInfo.strBusinessStatus = stBusinessDockMsgInfoPrase.strBusinessStatus;
		stBusinessDockMsgInfo.strProduceCode = stBusinessDockMsgInfoPrase.strProduceCode;
		stBusinessDockMsgInfo.strObjectProduceCode = stBusinessDockMsgInfoPrase.strObjectProduceCode;
		stBusinessDockMsgInfo.strFundName = stBusinessDockMsgInfoPrase.strFundName;
		stBusinessDockMsgInfo.strProduceName = stBusinessDockMsgInfoPrase.strProduceName;
		stBusinessDockMsgInfo.strIncomeType = stBusinessDockMsgInfoPrase.strIncomeType;
		stBusinessDockMsgInfo.strBusinessDate = stBusinessDockMsgInfoPrase.strBusinessDate;
		stBusinessDockMsgInfo.strClientName = stBusinessDockMsgInfoPrase.strClientName;
		stBusinessDockMsgInfo.strCredenitialsType = stBusinessDockMsgInfoPrase.strCredenitialsType;
		stBusinessDockMsgInfo.strCredenitialNum = stBusinessDockMsgInfoPrase.strCredenitialNum;
		stBusinessDockMsgInfo.strMediumType = stBusinessDockMsgInfoPrase.strMediumType;
		stBusinessDockMsgInfo.strMediumNum = stBusinessDockMsgInfoPrase.strMediumNum;
		stBusinessDockMsgInfo.strClientRiskLevel = stBusinessDockMsgInfoPrase.strClientRiskLevel;
		stBusinessDockMsgInfo.strProduceRiskLevel = stBusinessDockMsgInfoPrase.strProduceRiskLevel;
		stBusinessDockMsgInfo.strFundType = stBusinessDockMsgInfoPrase.strFundType;
		stBusinessDockMsgInfo.strCancelBusinessType = stBusinessDockMsgInfoPrase.strCancelBusinessType;
		stBusinessDockMsgInfo.nSystemType = 1;
		stBusinessDockMsgInfo.nBootFlag = stBusinessDockMsgInfo.strClientName.empty() ? 1 : 3;
		stBusinessDockMsgInfo.strRepondCode = "1";
		SFTRACE("Docking", "解析理财系统发来的数据：strServiceCode:%s,strJDBRID:%s,strOperatorId:%s,strChannelSerialNum:%s,strKernelSerialNum:%s,strDateTime:%s,\
			   strChannelDate:%s,strRepondCode:%s,strChineseDescribeInfo:%s,strBusinessCode:%s ,sstrBusinessName:%s ,strBusinessStatus:%s,\
			   strProduceCode:%s,strObjectProduceCode:%s,strFundName:%s,strProduceName:%s,strIncomeType:%s ,strBusinessDate:%s,strClientName:%s,\
			   strCredenitialsType:%s,sstrCredenitialNum:%s,strMediumType:%s,strMediumNum:%s,strClientRiskLevel:%s,strProduceRiskLevel:%s,\
			   strFundType:%s,strCancelBusinessType:%s,nSystemType:%d\r\n",
			   stBusinessDockMsgInfo.strServiceCode.c_str(),stBusinessDockMsgInfo.strJDBRID.c_str(),stBusinessDockMsgInfo.strOperatorId.c_str(),
			   stBusinessDockMsgInfo.strChannelSerialNum.c_str(),stBusinessDockMsgInfo.strKernelSerialNum.c_str(),stBusinessDockMsgInfo.strDateTime.c_str(),
			   stBusinessDockMsgInfo.strChannelDate.c_str(),stBusinessDockMsgInfo.strRepondCode.c_str(),stBusinessDockMsgInfo.strChineseDescribeInfo.c_str(),
			   stBusinessDockMsgInfo.strBusinessCode.c_str() ,stBusinessDockMsgInfo.strBusinessName.c_str() ,stBusinessDockMsgInfo.strBusinessStatus.c_str(),
			   stBusinessDockMsgInfo.strProduceCode.c_str(),stBusinessDockMsgInfo.strObjectProduceCode.c_str(),stBusinessDockMsgInfo.strFundName.c_str(),stBusinessDockMsgInfo.strProduceName.c_str(),
			   stBusinessDockMsgInfo.strIncomeType.c_str() ,stBusinessDockMsgInfo.strBusinessDate.c_str() ,stBusinessDockMsgInfo.strClientName.c_str(),
			   stBusinessDockMsgInfo.strCredenitialsType.c_str(),stBusinessDockMsgInfo.strCredenitialNum.c_str() ,stBusinessDockMsgInfo.strMediumType.c_str(),
			   stBusinessDockMsgInfo.strMediumNum.c_str(),stBusinessDockMsgInfo.strClientRiskLevel.c_str(),stBusinessDockMsgInfo.strProduceRiskLevel.c_str(),
			   stBusinessDockMsgInfo.strFundType.c_str(),stBusinessDockMsgInfo.strCancelBusinessType.c_str(),stBusinessDockMsgInfo.nSystemType );
	} 
	SCATCH;
}
