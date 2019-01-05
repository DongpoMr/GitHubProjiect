#include "stdafx.h"
#include "XhBFISClientDataTrafficStationFactoryImp.h"
#include "XhBFISClientBusinessImp.h"
#include "XhBFISClientDataTrafficImp.h"
#include "iSOC_PrivateStructDefine.h"
#include "IcmsP_Utility.h"



XhBFISClientDataTrafficStationFactoryImp::XhBFISClientDataTrafficStationFactoryImp()
{

}
XhBFISClientDataTrafficStationFactoryImp::~XhBFISClientDataTrafficStationFactoryImp()
{

}
CISocObject* XhBFISClientDataTrafficStationFactoryImp::CreateObject(ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/)
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFISSERVER_CLIENTSOURCE)
	{
		static XhBFISClientBusinessImp obj;
		return &obj;
	}
	else if (nObjType == OBJECT_TYPE_BFIS_CLIENTCOMMUNICATION)
	{
		static XhBFISClientDataTrafficImp obj;
		return &obj;
	}
	return nullptr;
	SCATCH;
	return nullptr;
}
ISOC_VOID XhBFISClientDataTrafficStationFactoryImp::ReleaseObject(CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/)
{

}
ISOC_bool XhBFISClientDataTrafficStationFactoryImp::HasObjectInObjType(ISOC_UINT nObjType)
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFISSERVER_CLIENTSOURCE || nObjType == OBJECT_TYPE_BFIS_CLIENTCOMMUNICATION)
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}
ISOC_INT XhBFISClientDataTrafficStationFactoryImp::GetObjectFacilityLevel(ISOC_UINT nObjType,const ISOC_STR strFacilityDes)
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFISSERVER_CLIENTSOURCE || nObjType == OBJECT_TYPE_BFIS_CLIENTCOMMUNICATION)
	{
		return 5;
	}
	return -1;
	SCATCH;
	return -1;
}