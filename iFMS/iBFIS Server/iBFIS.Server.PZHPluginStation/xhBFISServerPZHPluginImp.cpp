#include "StdAfx.h"
#include "xhBFISServerPZHPluginImp.h"
#include "IcmsP_XmlParser.h"
#include "XhBFISSyncServerRouterImp.h"


xhBFISServerPZHPluginImp::xhBFISServerPZHPluginImp(void)
{
}


xhBFISServerPZHPluginImp::~xhBFISServerPZHPluginImp(void)
{
}

int xhBFISServerPZHPluginImp::OnRecvData( UINT64 fromAddr, BYTE* pData, int dataLen )
{
	DISPLAY_LOG("实时对接","获取对接信息","成功","",1);
	char pDockIp[30] ={0};
	ICMS_IP_INT64TOSTR(fromAddr,pDockIp);
	string strDocpIp = pDockIp;
	string strInfo;
	//TTRACE("获取[%s]发来的对接信息[%s]\r\n",strDocpIp.c_str(),pData);
	SFTRACE("对接日志", "获取[%s]发来的对接信息[%s]\r\n", strDocpIp.c_str(), pData);
	ST_BusinessDockMsgInfo stBusinessDockMsgInfo;	
	if (pData && m_pDataInfoCb)
	{
		ParseDataToStruct(pData,stBusinessDockMsgInfo);
		m_pDataInfoCb->MsgCallback(&stBusinessDockMsgInfo);
	} 
	else 
	{
		TTRACE("对接消息为空或者插件回调失败");
	}
	return TRUE;
}

void xhBFISServerPZHPluginImp::ParseDataToStruct(BYTE* pData,ST_BusinessDockMsgInfo& stBusinessDockMsgInfo)
{	
	STRY;
	if (NULL != pData)
	{
		//BYTE* ObjectDate = pData + 8;
		char* czObjectDate = (char*)pData;    
		int nLen = strlen(czObjectDate);
		string strObjectDate = czObjectDate;//UTF8ToGDB(czObjectDate);
		iCMSP_XmlParser XmlParser;
		XmlParser.SetDoc(strObjectDate.c_str(), strObjectDate.size());
		if (XmlParser.FindElem("BusinessDockMsgInfo"))
		{
			XmlParser.IntoElem();
			if (XmlParser.FindElem("Flag"))
			{
				stBusinessDockMsgInfo.nBootFlag = XmlParser.GetDataInt();
			}
			if (XmlParser.FindElem("ClientLocationID"))
			{
				stBusinessDockMsgInfo.strTerminalIP = XmlParser.GetData();//终端ip
			}
			if (XmlParser.FindElem("JDBRID"))
			{
				stBusinessDockMsgInfo.strJDBRID = XmlParser.GetData();
			}
			if (XmlParser.FindElem("OperatorId"))
			{
				stBusinessDockMsgInfo.strOperatorId = XmlParser.GetData();
			}
			if (XmlParser.FindElem("DateTime"))
			{
				stBusinessDockMsgInfo.strDateTime = XmlParser.GetData();
			}
			if (XmlParser.FindElem("BusinessCode"))
			{
				stBusinessDockMsgInfo.strBusinessCode = XmlParser.GetData();
			}
			if (XmlParser.FindElem("BusinessName"))
			{
				stBusinessDockMsgInfo.strBusinessName = XmlParser.GetData();
			}
			if (XmlParser.FindElem("ProduceCode"))
			{
				stBusinessDockMsgInfo.strProduceCode = XmlParser.GetData();
			}
			if (XmlParser.FindElem("ProduceName"))
			{
				stBusinessDockMsgInfo.strProduceName =XmlParser.GetData();
			}
			if (XmlParser.FindElem("ClientName"))
			{
				stBusinessDockMsgInfo.strClientName = XmlParser.GetData();
			}
			if (XmlParser.FindElem("CredenitialsType"))
			{
				stBusinessDockMsgInfo.strCredenitialsType = XmlParser.GetData();
			}
			if (XmlParser.FindElem("CredenitialNum"))
			{
				stBusinessDockMsgInfo.strCredenitialNum = XmlParser.GetData();
			}
			if (XmlParser.FindElem("MediumType"))
			{
				stBusinessDockMsgInfo.strMediumType = XmlParser.GetData();
			}
			if (XmlParser.FindElem("MediumNum"))
			{
				stBusinessDockMsgInfo.strMediumNum = XmlParser.GetData();
			}
			if (XmlParser.FindElem("SerialNumber"))
			{
				stBusinessDockMsgInfo.strIBFISSerialNum = XmlParser.GetData();
			}
			stBusinessDockMsgInfo.nSystemType = 3;
		}
		//TTRACE("解析理财系统发来的数据：strServiceCode:%s,strJDBRID:%s,strOperatorId:%s,strChannelSerialNum:%s,strKernelSerialNum:%s,strDateTime:%s,\
		//	   strChannelDate:%s,strRepondCode:%s,strChineseDescribeInfo:%s,strBusinessCode:%s ,sstrBusinessName:%s ,strBusinessStatus:%s,\
		//	   strProduceCode:%s,strObjectProduceCode:%s,strFundName:%s,strProduceName:%s,strIncomeType:%s ,strBusinessDate:%s,strClientName:%s,\
		//	   strCredenitialsType:%s,sstrCredenitialNum:%s,strMediumType:%s,strMediumNum:%s,strClientRiskLevel:%s,strProduceRiskLevel:%s,\
		//	   strFundType:%s,strCancelBusinessType:%s,TerminalIP:%s,nSystemType:%d,\r\n",
		//	   stBusinessDockMsgInfo.strServiceCode.c_str(),stBusinessDockMsgInfo.strJDBRID.c_str(),stBusinessDockMsgInfo.strOperatorId.c_str(),
		//	   stBusinessDockMsgInfo.strChannelSerialNum.c_str(),stBusinessDockMsgInfo.strKernelSerialNum.c_str(),stBusinessDockMsgInfo.strDateTime.c_str(),
		//	   stBusinessDockMsgInfo.strChannelDate.c_str(),stBusinessDockMsgInfo.strRepondCode.c_str(),stBusinessDockMsgInfo.strChineseDescribeInfo.c_str(),
		//	   stBusinessDockMsgInfo.strBusinessCode.c_str() ,stBusinessDockMsgInfo.strBusinessName.c_str() ,stBusinessDockMsgInfo.strBusinessStatus.c_str(),
		//	   stBusinessDockMsgInfo.strProduceCode.c_str(),stBusinessDockMsgInfo.strObjectProduceCode.c_str(),stBusinessDockMsgInfo.strFundName.c_str(),stBusinessDockMsgInfo.strProduceName.c_str(),
		//	   stBusinessDockMsgInfo.strIncomeType.c_str() ,stBusinessDockMsgInfo.strBusinessDate.c_str() ,stBusinessDockMsgInfo.strClientName.c_str(),
		//	   stBusinessDockMsgInfo.strCredenitialsType.c_str(),stBusinessDockMsgInfo.strCredenitialNum.c_str() ,stBusinessDockMsgInfo.strMediumType.c_str(),
		//	   stBusinessDockMsgInfo.strMediumNum.c_str(),stBusinessDockMsgInfo.strClientRiskLevel.c_str(),stBusinessDockMsgInfo.strProduceRiskLevel.c_str(),
		//	   stBusinessDockMsgInfo.strFundType.c_str(),stBusinessDockMsgInfo.strCancelBusinessType.c_str(),stBusinessDockMsgInfo.strTerminalIP.c_str(),stBusinessDockMsgInfo.nSystemType );
		SFTRACE("对接日志", "解析理财系统发来的数据：strServiceCode:%s,strJDBRID:%s,strOperatorId:%s,strChannelSerialNum:%s,strKernelSerialNum:%s,strDateTime:%s,\
			   strChannelDate:%s,strRepondCode:%s,strChineseDescribeInfo:%s,strBusinessCode:%s ,sstrBusinessName:%s ,strBusinessStatus:%s,\
			   strProduceCode:%s,strObjectProduceCode:%s,strFundName:%s,strProduceName:%s,strIncomeType:%s ,strBusinessDate:%s,strClientName:%s,\
			   strCredenitialsType:%s,sstrCredenitialNum:%s,strMediumType:%s,strMediumNum:%s,strClientRiskLevel:%s,strProduceRiskLevel:%s,\
			   strFundType:%s,strCancelBusinessType:%s,nSystemType:%d,nBootFlag:%d\r\n",
			stBusinessDockMsgInfo.strServiceCode.c_str(), stBusinessDockMsgInfo.strJDBRID.c_str(), stBusinessDockMsgInfo.strOperatorId.c_str(),
			stBusinessDockMsgInfo.strChannelSerialNum.c_str(), stBusinessDockMsgInfo.strKernelSerialNum.c_str(), stBusinessDockMsgInfo.strDateTime.c_str(),
			stBusinessDockMsgInfo.strChannelDate.c_str(), stBusinessDockMsgInfo.strRepondCode.c_str(), stBusinessDockMsgInfo.strChineseDescribeInfo.c_str(),
			stBusinessDockMsgInfo.strBusinessCode.c_str(), stBusinessDockMsgInfo.strBusinessName.c_str(), stBusinessDockMsgInfo.strBusinessStatus.c_str(),
			stBusinessDockMsgInfo.strProduceCode.c_str(), stBusinessDockMsgInfo.strObjectProduceCode.c_str(), stBusinessDockMsgInfo.strFundName.c_str(), stBusinessDockMsgInfo.strProduceName.c_str(),
			stBusinessDockMsgInfo.strIncomeType.c_str(), stBusinessDockMsgInfo.strBusinessDate.c_str(), stBusinessDockMsgInfo.strClientName.c_str(),
			stBusinessDockMsgInfo.strCredenitialsType.c_str(), stBusinessDockMsgInfo.strCredenitialNum.c_str(), stBusinessDockMsgInfo.strMediumType.c_str(),
			stBusinessDockMsgInfo.strMediumNum.c_str(), stBusinessDockMsgInfo.strClientRiskLevel.c_str(), stBusinessDockMsgInfo.strProduceRiskLevel.c_str(),
			stBusinessDockMsgInfo.strFundType.c_str(), stBusinessDockMsgInfo.strCancelBusinessType.c_str(), stBusinessDockMsgInfo.nSystemType, stBusinessDockMsgInfo.nBootFlag);
	} 
	SCATCH;
}