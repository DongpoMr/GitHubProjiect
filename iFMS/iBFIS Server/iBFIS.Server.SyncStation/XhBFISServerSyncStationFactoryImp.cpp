#include "StdAfx.h"
#include "XhBFISServerSyncStationFactoryImp.h"
#include "XhBFISSyncClientRouterImp.h"
#include "XhBFISSyncServerRouterImp.h"
#include "IcmsP_Utility.h"

XhBFISSyncStationFactoryImp::XhBFISSyncStationFactoryImp()
{

}

XhBFISSyncStationFactoryImp::~XhBFISSyncStationFactoryImp()
{

}

CISocObject* XhBFISSyncStationFactoryImp::CreateObject(ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved)
{
	STRY;
	switch(nObjType)
	{
	case OBJECT_TYPE_BFISSYNC_SERVER:
		{
			//XhBFISSyncServerRouterImp* pServer = new XhBFISSyncServerRouterImp;
            static XhBFISSyncServerRouterImp obj;
            return &obj;
		}
		break;
	case OBJECT_TYPE_BFISSYNC_CLIENT:
		{
			//XhBFISSyncClientRouterImp* pClient = new XhBFISSyncClientRouterImp;
            static XhBFISSyncClientRouterImp obj;
			return &obj;
		}
		break;
	}

	return NULL;
	SCATCH;
	return NULL;
}

ISOC_VOID XhBFISSyncStationFactoryImp::ReleaseObject(CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved)
{

}

ISOC_bool XhBFISSyncStationFactoryImp::HasObjectInObjType(ISOC_UINT nObjType)
{
	switch(nObjType)
	{
	case OBJECT_TYPE_BFISSYNC_SERVER:
	case OBJECT_TYPE_BFISSYNC_CLIENT:
		return true;
	}

	return false;
}

ISOC_INT XhBFISSyncStationFactoryImp::GetObjectFacilityLevel(ISOC_UINT nObjType,const ISOC_STR strFacilityDes)
{
	switch(nObjType)
	{
	case OBJECT_TYPE_BFISSYNC_SERVER:
	case OBJECT_TYPE_BFISSYNC_CLIENT:
		return 5;
	}
	return -1;
}
