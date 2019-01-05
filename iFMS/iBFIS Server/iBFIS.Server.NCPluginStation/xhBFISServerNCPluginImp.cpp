#include "StdAfx.h"
#include "xhBFISServerNCPluginImp.h"
#include "IcmsP_XmlParser.h"
#include "xhBFISSyncServerRouterImp.h"
#include "iBFIS_DataType_Define.h"




xhBFISServerNCPluginImp::xhBFISServerNCPluginImp(void):m_fromAdd(0)
{
}


xhBFISServerNCPluginImp::~xhBFISServerNCPluginImp(void)
{
}
ISOC_INT xhBFISServerNCPluginImp::SendDataToBusinessSystem(BYTE* pData,int dataLen)
{
	STRY;
	if (nullptr == pData || dataLen <= 0)
		return ISOC_ERR_INVALID_PARAMETER;

	int nRet = 0;
	string strRecvMsg = (char*)pData;
	string strTotalRecvMsg = m_strPreMsg + strRecvMsg;
	int nLen = strTotalRecvMsg.size();
	char szLenHand[9] ={};
	sprintf(szLenHand,"%08d",nLen);
	string strLenHand = szLenHand;
	string strTotalRecvMsg1 = strLenHand +  strTotalRecvMsg;
	TTRACE("返回消息内容为:%s \r\n",strTotalRecvMsg1.c_str());
	if (m_spTcpListen)
		nRet = m_spTcpListen->SendData(m_fromAdd, (BYTE*)strTotalRecvMsg1.c_str(), strTotalRecvMsg1.size());
	if (nRet <= 0 )
	{
		//DISPLAY_LOG("对接模块","发送到核心服务器信息","失败","",nRet);
		return ISOC_ERR_FAILED;
	}

	return ISOC_ERR_SUCCESS;
	SCATCH;
	return ISOC_ERR_UNKNOW_ERROR;
}
int xhBFISServerNCPluginImp::OnRecvData( UINT64 fromAddr, BYTE* pData, int dataLen )
{
	BYTE* pData1 = pData + 8;
	char szPreMsg[57] = {};
	strncpy(szPreMsg,(char*)pData1,56);
	m_strPreMsg = szPreMsg;
	DISPLAY_LOG("实时对接","获取对接信息","成功","",1);
	m_fromAdd = fromAddr;
	char pDockIp[30] ={0};
	ICMS_IP_INT64TOSTR(fromAddr,pDockIp);
	string strDocpIp = pDockIp;
	string strInfo;
	TTRACE("获取[%s]发来的对接信息[%s]\r\n",strDocpIp.c_str(),pData);
	//SFTRACE("对接日志", "获取[%s]发来的对接信息[%s]\r\n", strDocpIp.c_str(), pData);
	ST_BusinessDockMsgInfo stBusinessDockMsgInfo;	
	if (pData && m_pDataInfoCb)
	{
		ParseDataToStruct(pData,stBusinessDockMsgInfo);
		m_pDataInfoCb->MsgCallback(&stBusinessDockMsgInfo);
	}
	return TRUE;
}

void xhBFISServerNCPluginImp::ParseDataToStruct(BYTE* pData,ST_BusinessDockMsgInfo& stBusinessDockMsgInfo)
{	
	STRY;
	if (NULL != pData)
	{
		BYTE* ObjectDate = pData + 64;
		char* czObjectDate = (char*)ObjectDate;    
		int nLen = strlen(czObjectDate);
		string strObjectDate = czObjectDate; //UTF8ToGDB(czObjectDate);
		iCMSP_XmlParser XmlParser;
		XmlParser.SetDoc(strObjectDate.c_str(), strObjectDate.size());
		if (XmlParser.FindElem("root"))
		{
			XmlParser.IntoElem();
			if (XmlParser.FindElem("req"))
			{
				XmlParser.IntoElem();
				if (XmlParser.FindElem("JDBRID"))
				{
					stBusinessDockMsgInfo.strJDBRID = XmlParser.GetData();
				}
				if (XmlParser.FindElem("OperatorId"))
				{
					stBusinessDockMsgInfo.strOperatorId = XmlParser.GetData();
				}
				if (XmlParser.FindElem("TerminalIP"))
				{
					stBusinessDockMsgInfo.strTerminalIP = XmlParser.GetData();//终端ip
				}
				if (XmlParser.FindElem("DateTime"))
				{
					stBusinessDockMsgInfo.strDateTime = XmlParser.GetData();
				}
				if (XmlParser.FindElem("BootFlag"))
				{
					stBusinessDockMsgInfo.nBootFlag = XmlParser.GetDataInt();
				}
				if (XmlParser.FindElem("SystemFlag"))
				{
					stBusinessDockMsgInfo.nSystemType = XmlParser.GetDataInt();
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
				if (XmlParser.FindElem("VideoEndDate"))
				{
					stBusinessDockMsgInfo.strVideoEndDate = XmlParser.GetData();
				}
				if (XmlParser.FindElem("ReviewContent"))
				{
					stBusinessDockMsgInfo.strExtendedInfo = XmlParser.GetData();
				}
			}
			switch (stBusinessDockMsgInfo.nSystemType)
			{
				case 1: 
				{
					stBusinessDockMsgInfo.strRepondCode = "1";
				}
				break;
				case 2:
				{
					stBusinessDockMsgInfo.strRepondCode = "2";
				}
				break;
				case 3:
				{
					stBusinessDockMsgInfo.strRepondCode = "3";
				}
				break;
				case 4:
				{
					stBusinessDockMsgInfo.strRepondCode = "4";
				}
				break;
			default:
				break;
			}
			string strRandomSerialNum;
			GetRandomSerialNum(strRandomSerialNum);
			stBusinessDockMsgInfo.strIBFISSerialNum = strRandomSerialNum;
			stBusinessDockMsgInfo.nSystemType = 4;
			
		}
		TTRACE("解析理财系统发来的数据：strServiceCode:%s,strJDBRID:%s,strOperatorId:%s,strChannelSerialNum:%s,strKernelSerialNum:%s,strDateTime:%s,\
			   strChannelDate:%s,strRepondCode:%s,strChineseDescribeInfo:%s,strBusinessCode:%s ,sstrBusinessName:%s ,strBusinessStatus:%s,\
			   strProduceCode:%s,strObjectProduceCode:%s,strFundName:%s,strProduceName:%s,strIncomeType:%s ,strBusinessDate:%s,strClientName:%s,\
			   strCredenitialsType:%s,sstrCredenitialNum:%s,strMediumType:%s,strMediumNum:%s,strClientRiskLevel:%s,strProduceRiskLevel:%s,\
			   strFundType:%s,strCancelBusinessType:%s,nSystemType:%d,nBootFlag:%d\r\n",
			   stBusinessDockMsgInfo.strServiceCode.c_str(),stBusinessDockMsgInfo.strJDBRID.c_str(),stBusinessDockMsgInfo.strOperatorId.c_str(),
			   stBusinessDockMsgInfo.strChannelSerialNum.c_str(),stBusinessDockMsgInfo.strKernelSerialNum.c_str(),stBusinessDockMsgInfo.strDateTime.c_str(),
			   stBusinessDockMsgInfo.strChannelDate.c_str(),stBusinessDockMsgInfo.strRepondCode.c_str(),stBusinessDockMsgInfo.strChineseDescribeInfo.c_str(),
			   stBusinessDockMsgInfo.strBusinessCode.c_str() ,stBusinessDockMsgInfo.strBusinessName.c_str() ,stBusinessDockMsgInfo.strBusinessStatus.c_str(),
			   stBusinessDockMsgInfo.strProduceCode.c_str(),stBusinessDockMsgInfo.strObjectProduceCode.c_str(),stBusinessDockMsgInfo.strFundName.c_str(),stBusinessDockMsgInfo.strProduceName.c_str(),
			   stBusinessDockMsgInfo.strIncomeType.c_str() ,stBusinessDockMsgInfo.strBusinessDate.c_str() ,stBusinessDockMsgInfo.strClientName.c_str(),
			   stBusinessDockMsgInfo.strCredenitialsType.c_str(),stBusinessDockMsgInfo.strCredenitialNum.c_str() ,stBusinessDockMsgInfo.strMediumType.c_str(),
			   stBusinessDockMsgInfo.strMediumNum.c_str(),stBusinessDockMsgInfo.strClientRiskLevel.c_str(),stBusinessDockMsgInfo.strProduceRiskLevel.c_str(),
			   stBusinessDockMsgInfo.strFundType.c_str(),stBusinessDockMsgInfo.strCancelBusinessType.c_str(),stBusinessDockMsgInfo.nSystemType,stBusinessDockMsgInfo.nBootFlag);
		//SFTRACE("对接日志", "解析理财系统发来的数据：strServiceCode:%s,strJDBRID:%s,strOperatorId:%s,strChannelSerialNum:%s,strKernelSerialNum:%s,strDateTime:%s,\
		//	   strChannelDate:%s,strRepondCode:%s,strChineseDescribeInfo:%s,strBusinessCode:%s ,sstrBusinessName:%s ,strBusinessStatus:%s,\
		//	   strProduceCode:%s,strObjectProduceCode:%s,strFundName:%s,strProduceName:%s,strIncomeType:%s ,strBusinessDate:%s,strClientName:%s,\
		//	   strCredenitialsType:%s,sstrCredenitialNum:%s,strMediumType:%s,strMediumNum:%s,strClientRiskLevel:%s,strProduceRiskLevel:%s,\
		//	   strFundType:%s,strCancelBusinessType:%s,nSystemType:%d,nBootFlag:%d\r\n",
		//	stBusinessDockMsgInfo.strServiceCode.c_str(), stBusinessDockMsgInfo.strJDBRID.c_str(), stBusinessDockMsgInfo.strOperatorId.c_str(),
		//	stBusinessDockMsgInfo.strChannelSerialNum.c_str(), stBusinessDockMsgInfo.strKernelSerialNum.c_str(), stBusinessDockMsgInfo.strDateTime.c_str(),
		//	stBusinessDockMsgInfo.strChannelDate.c_str(), stBusinessDockMsgInfo.strRepondCode.c_str(), stBusinessDockMsgInfo.strChineseDescribeInfo.c_str(),
		//	stBusinessDockMsgInfo.strBusinessCode.c_str(), stBusinessDockMsgInfo.strBusinessName.c_str(), stBusinessDockMsgInfo.strBusinessStatus.c_str(),
		//	stBusinessDockMsgInfo.strProduceCode.c_str(), stBusinessDockMsgInfo.strObjectProduceCode.c_str(), stBusinessDockMsgInfo.strFundName.c_str(), stBusinessDockMsgInfo.strProduceName.c_str(),
		//	stBusinessDockMsgInfo.strIncomeType.c_str(), stBusinessDockMsgInfo.strBusinessDate.c_str(), stBusinessDockMsgInfo.strClientName.c_str(),
		//	stBusinessDockMsgInfo.strCredenitialsType.c_str(), stBusinessDockMsgInfo.strCredenitialNum.c_str(), stBusinessDockMsgInfo.strMediumType.c_str(),
		//	stBusinessDockMsgInfo.strMediumNum.c_str(), stBusinessDockMsgInfo.strClientRiskLevel.c_str(), stBusinessDockMsgInfo.strProduceRiskLevel.c_str(),
		//	stBusinessDockMsgInfo.strFundType.c_str(), stBusinessDockMsgInfo.strCancelBusinessType.c_str(), stBusinessDockMsgInfo.nSystemType, stBusinessDockMsgInfo.nBootFlag);
	} 
	SCATCH;
}
void xhBFISServerNCPluginImp::GetRandomSerialNum(string& strRandomSerialNum)
{
	STRY;
	CTime t = CTime::GetCurrentTime(); //获取系统日期
	CString strDateTime;
	strDateTime.Format("%04d%02d%02d%02d%02d%02d", t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());
	strRandomSerialNum = strDateTime.GetBuffer(0);
	SCATCH;
}

