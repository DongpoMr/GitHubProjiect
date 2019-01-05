#include "StdAfx.h"
#include "XhBFISDisplayLogFactoryImp.h"
#include "XhBFISDisplayLogStationImp.h"
#include "IcmsP_Utility.h"


XhBFISDisplayLogFactoryImp::XhBFISDisplayLogFactoryImp(void):m_pDisplayLogStation(nullptr)
{
}


XhBFISDisplayLogFactoryImp::~XhBFISDisplayLogFactoryImp(void)
{
	SAFE_DELETE(m_pDisplayLogStation);
}

CISocObject* XhBFISDisplayLogFactoryImp::CreateObject( ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/ )
{
	if(nObjType == OBJECT_TYPE_BFIS_DISPLAY_LOG_STATION)
	{
		if(!m_pDisplayLogStation)
		{
			m_pDisplayLogStation = new XhBFSDisplayLogStationImp;
		}
		return m_pDisplayLogStation;
	}
	return nullptr;
}

ISOC_VOID XhBFISDisplayLogFactoryImp::ReleaseObject( CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/ )
{
	if(ppObj)
	{
		SAFE_DELETE(*ppObj);
	}
}

ISOC_bool XhBFISDisplayLogFactoryImp::HasObjectInObjType( ISOC_UINT nObjType )
{
	if(nObjType == OBJECT_TYPE_BFIS_DISPLAY_LOG_STATION)
		return true;
	return false;
}

ISOC_INT XhBFISDisplayLogFactoryImp::GetObjectFacilityLevel( ISOC_UINT nObjType,const ISOC_STR strFacilityDes )
{
	if(nObjType == OBJECT_TYPE_BFIS_DISPLAY_LOG_STATION)
		return 5;
	return -1;
}
