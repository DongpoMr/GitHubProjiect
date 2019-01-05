#include "stdafx.h"
#include "XhBFISSerializeDataStationFactoryImp.h"
#include "IcmsP_Utility.h"
#include "XhBFISSerializeDataStationImp.h"


XhBFISSerializeDataStationFactoryImp::XhBFISSerializeDataStationFactoryImp()
{
}


XhBFISSerializeDataStationFactoryImp::~XhBFISSerializeDataStationFactoryImp()
{
}

CISocObject * XhBFISSerializeDataStationFactoryImp::CreateObject(ISOC_UINT nObjType, const ISOC_STR strFacilityDes, const ISOC_STR pFunction, ISOC_DWORDPTR dwReserved)
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFISSERVER_SERIALIZEDATAMEMORY)
	{
		return new XhBFISSerializeDataStationImp();
	}
	return nullptr;
	SCATCH;
	return nullptr;
}

ISOC_VOID XhBFISSerializeDataStationFactoryImp::ReleaseObject(CISocObject ** ppObj, const ISOC_STR pFunction, ISOC_DWORDPTR dwReserved)
{
	STRY;
	if (ppObj == NULL || *ppObj == NULL)
		return;

	CISocObject *pObj = *ppObj;
	if (pObj->GetObjectType() == OBJECT_TYPE_BFISSERVER_SERIALIZEDATAMEMORY)
	{
		delete pObj;
		*ppObj = NULL;
	}
	SCATCH;
}

ISOC_bool XhBFISSerializeDataStationFactoryImp::HasObjectInObjType(ISOC_UINT nObjType)
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFISSERVER_SERIALIZEDATAMEMORY)
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}

ISOC_INT XhBFISSerializeDataStationFactoryImp::GetObjectFacilityLevel(ISOC_UINT nObjType, const ISOC_STR strFacilityDes)
{
	    STRY;
    if (nObjType == OBJECT_TYPE_BFISSERVER_SERIALIZEDATAMEMORY)
    {
        return 5;
    }
    return -1;
    SCATCH;
    return -1;
}
