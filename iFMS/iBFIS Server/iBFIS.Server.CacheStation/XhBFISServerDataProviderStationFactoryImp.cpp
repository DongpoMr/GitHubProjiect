#include "stdafx.h"
#include "XhBFISServerDataProviderStationFactoryImp.h"
#include "IcmsP_Utility.h"
#include "XhBFISDataProviderImp.h"


XhBFISServerDataProviderStationFactoryImp::XhBFISServerDataProviderStationFactoryImp(void)
{

}


XhBFISServerDataProviderStationFactoryImp::~XhBFISServerDataProviderStationFactoryImp(void)
{

}

CISocObject* XhBFISServerDataProviderStationFactoryImp::CreateObject( ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/ )
{
	if(nObjType == OBJECT_TYPE_BFISSERVER_CACHESOURCE)
	{
		static XhBFISDataProviderImp obj;
		return &obj;
	}
	return nullptr;
}

ISOC_VOID XhBFISServerDataProviderStationFactoryImp::ReleaseObject( CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/ )
{
	if(ppObj)
	{
		SAFE_DELETE(*ppObj);
	}
}

ISOC_bool XhBFISServerDataProviderStationFactoryImp::HasObjectInObjType( ISOC_UINT nObjType )
{
	if(nObjType == OBJECT_TYPE_BFISSERVER_CACHESOURCE)
		return true;
	return false;
}

ISOC_INT XhBFISServerDataProviderStationFactoryImp::GetObjectFacilityLevel( ISOC_UINT nObjType,const ISOC_STR strFacilityDes )
{
	if(nObjType == OBJECT_TYPE_BFISSERVER_CACHESOURCE)
		return 5;
	return -1;
}
