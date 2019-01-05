#include "stdafx.h"
#include "XhBFISDBOperatorStationFactoryImp.h"
#include "iSOC_PrivateStructDefine.h"
#include "IcmsP_Utility.h"
#include "XhBFISDBOperationImp.h"


XhBFISDBOperatorStationFactoryImp::XhBFISDBOperatorStationFactoryImp()
{

}
XhBFISDBOperatorStationFactoryImp::~XhBFISDBOperatorStationFactoryImp()
{

}
CISocObject* XhBFISDBOperatorStationFactoryImp::CreateObject(ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/)
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE)
	{
		static XhBFISDBOperationImp obj;
		return &obj;
	}
	return nullptr;
	SCATCH;
	return nullptr;
}
ISOC_VOID XhBFISDBOperatorStationFactoryImp::ReleaseObject(CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/)
{

}
ISOC_bool XhBFISDBOperatorStationFactoryImp::HasObjectInObjType(ISOC_UINT nObjType)
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE)
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}
ISOC_INT XhBFISDBOperatorStationFactoryImp::GetObjectFacilityLevel(ISOC_UINT nObjType,const ISOC_STR strFacilityDes)
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE)
	{
		return 5;
	}
	return -1;
	SCATCH;
	return -1;
}