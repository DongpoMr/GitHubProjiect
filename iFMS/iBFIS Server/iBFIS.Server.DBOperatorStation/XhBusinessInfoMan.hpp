#pragma once
#include "stdafx.h"
#include "iBFIS_UniqueDefine.h"
#include "XhLogDisplayInterface.h"
#include "odbcinst.h"
#import "msado26.tlb" rename_namespace("ADODB") rename("EOF","adoEOF") 
using namespace ADODB;

#define USE_BFIS_ASSERT 1
#define BFIS_ASSERT_STDSTRING(str, operate) { if(str == "") {DISPLAY_LOG("数据库模块", operate, "参数"#str"不能为空","",0); return false;}}

class XhBusinessInfoMan
{
public:
	XhBusinessInfoMan(){};
	~XhBusinessInfoMan(){};

	bool manBusinessInfo(DBOperType dbType,string& strSql,const ST_BusinessInfo& stInfo)
	{
		char szMsg[2][255] = {0};
		if(dbType == DBO_ADD)
		{
			_tcscpy(szMsg[0],"添加业务信息");
			_tcscpy(szMsg[1],
				"call proc_businessinfo_insert(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\")");
		}
		else
		{
			_tcscpy(szMsg[0],"更新业务信息");
			_tcscpy(szMsg[1],
				"call proc_businessinfo_update(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\")");
		}

#if USE_BFIS_ASSERT
		BFIS_ASSERT_STDSTRING(stInfo.strBusinessInfoId,      szMsg[0]);
		//BFIS_ASSERT_STDSTRING(stInfo.strDateTime,            szMsg[0]);
		BFIS_ASSERT_STDSTRING(stInfo.strBranchId,            szMsg[0]);
		BFIS_ASSERT_STDSTRING(stInfo.strSubEquipmentIcmSign, szMsg[0]);
		BFIS_ASSERT_STDSTRING(stInfo.strEmployeeId,          szMsg[0]);
		//BFIS_ASSERT_STDSTRING(stInfo.strClientId,            szMsg[0]);
		//BFIS_ASSERT_STDSTRING(stInfo.strProduceId,           szMsg[0]);
		//BFIS_ASSERT_STDSTRING(stInfo.strSerialNumber,        szMsg[0]);
#endif
		char szTmp[1024] = {0};
		sprintf(szTmp,szMsg[1],stInfo.strBusinessInfoId.c_str(),stInfo.strDateTime.c_str(),stInfo.strBranchId.c_str(),
			stInfo.strClientId.c_str(),stInfo.strEmployeeId.c_str(),stInfo.strProduceId.c_str(),
			stInfo.strSubEquipmentId.c_str(),stInfo.nExtendedInfo,stInfo.strExtendedInfo1.c_str(),
			stInfo.strExtendedInfo2.c_str(),stInfo.strSubEquipmentIcmSign.c_str(),stInfo.strSerialNumber.c_str(),
			stInfo.nMigrated,stInfo.strFileCenter.c_str(),stInfo.strBusinessType.c_str(),stInfo.strCardNumber.c_str(),
            stInfo.nMarkerType,stInfo.strCardType.c_str(),stInfo.strMediumType.c_str(),stInfo.strMediumNum.c_str(),
			stInfo.strOffDisputeTime.c_str());
		strSql = szTmp;
		return true;
	}

	bool addBusinessInfo(string& strSql,const ST_BusinessInfo& stInfo)
	{
		return manBusinessInfo(DBO_ADD,strSql,stInfo);
	}

	bool updateBusinessInfo(string& strSql,const ST_BusinessInfo& stInfo)
	{
		return manBusinessInfo(DBO_UPDATE,strSql,stInfo);
	}

	bool querySingleBusinessInfo(_variant_t& varFieldVal,const _RecordsetPtr& recPtr,ST_BusinessInfo& stInfo)
	{
		if(recPtr == NULL || recPtr->adoEOF)
		{
			TTRACE("[业务查询]传入_RecordsetPtr类型参数recPtr的值错误 \r\n");
			return false;
		}
		varFieldVal = recPtr->GetCollect("BusInessInfoId");
		stInfo.strBusinessInfoId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("Datetime");
		if(varFieldVal.vt != VT_NULL)
		{
			DATE dt = varFieldVal.date;  
			COleDateTime da = COleDateTime(dt);  
			stInfo.strDateTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
		}
		varFieldVal = recPtr->GetCollect("BranchId");
		stInfo.strBranchId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("ClientId");
		stInfo.strClientId   = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("EmployeeId");
		stInfo.strEmployeeId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("ProduceId");
		stInfo.strProduceId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("SubEquipmentId");
		stInfo.strSubEquipmentId = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("ExtendedInfo");
		stInfo.nExtendedInfo = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
		varFieldVal = recPtr->GetCollect("ExtendedInfo1");
		stInfo.strExtendedInfo1 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("ExtendedInfo2");
		stInfo.strExtendedInfo2 = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("SubEquipmentIcmSign");
		stInfo.strSubEquipmentIcmSign = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("SerialNumber");
		stInfo.strSerialNumber = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("Migrated");
		stInfo.nMigrated = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.dblVal;
		varFieldVal = recPtr->GetCollect("FileCenter");
		stInfo.strFileCenter = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
        varFieldVal = recPtr->GetCollect("BusinessType");
        stInfo.strBusinessType = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
        varFieldVal = recPtr->GetCollect("CardNumber");
        stInfo.strCardNumber = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
        varFieldVal = recPtr->GetCollect("MarkerType");
        stInfo.nMarkerType = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
        varFieldVal = recPtr->GetCollect("CardType");
        stInfo.strCardType = varFieldVal.vt == VT_NULL ? "": (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("MediumType");
		stInfo.strMediumType = varFieldVal.vt == VT_NULL ? "": (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("MediumNum");
		stInfo.strMediumNum = varFieldVal.vt == VT_NULL ? "": (_bstr_t)varFieldVal.bstrVal;
		varFieldVal = recPtr->GetCollect("OffDisputeTime");
		if(varFieldVal.vt != VT_NULL)
		{
			DATE dt = varFieldVal.date;  
			COleDateTime da = COleDateTime(dt);  
			stInfo.strOffDisputeTime = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
		}
		return true;
	}
	bool queryOtherParam(_variant_t& varFieldVal,const _RecordsetPtr& recPtr,const _variant_t& Index,int& nResult)
	{
		if(recPtr == NULL || recPtr->adoEOF)
		{
			TTRACE("[业务查询]传入_RecordsetPtr类型参数recPtr的值错误 \r\n");
			return false;
		}
		varFieldVal = recPtr->GetCollect(Index);
		nResult = varFieldVal.vt == VT_NULL ? 0 : (int)varFieldVal.intVal;
		return true;
	}
	bool queryOtherParam(_variant_t& varFieldVal,const _RecordsetPtr& recPtr,const _variant_t& Index,string& strResult)
	{
		if(recPtr == NULL || recPtr->adoEOF)
		{
			TTRACE("[业务查询]传入_RecordsetPtr类型参数recPtr的值错误 \r\n");
			return false;
		}
		varFieldVal = recPtr->GetCollect(Index);
		strResult = varFieldVal.vt == VT_NULL ? "" : (_bstr_t)varFieldVal.bstrVal;
		return true;
	}
};