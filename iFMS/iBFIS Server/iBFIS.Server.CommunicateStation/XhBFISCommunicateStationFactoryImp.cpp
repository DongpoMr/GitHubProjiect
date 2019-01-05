#include "stdafx.h"
#include "iSOC_PrivateStructDefine.h"
#include "IcmsP_Utility.h"
#include "XhBFISCommunicateStationFactoryImp.h"
#include "XhBFISCommunicateSyncServerStationImp.h"



XhBFISCommunicateStationFactoryImp::XhBFISCommunicateStationFactoryImp()
{

}
XhBFISCommunicateStationFactoryImp::~XhBFISCommunicateStationFactoryImp()
{

}
CISocObject* XhBFISCommunicateStationFactoryImp::CreateObject(ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/)
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFIS_COMMUNICATESYNCSERVER)
	{
		static XhBFISCommunicateSyncServerStationImp obj;
		return &obj;
	}
	return nullptr;
	SCATCH;
	return nullptr;
}
ISOC_VOID XhBFISCommunicateStationFactoryImp::ReleaseObject(CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/)
{

}
ISOC_bool XhBFISCommunicateStationFactoryImp::HasObjectInObjType(ISOC_UINT nObjType)
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFIS_COMMUNICATESYNCSERVER)
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}
ISOC_INT XhBFISCommunicateStationFactoryImp::GetObjectFacilityLevel(ISOC_UINT nObjType,const ISOC_STR strFacilityDes)
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFIS_COMMUNICATESYNCSERVER)
	{
		return 5;
	}
	return -1;
	SCATCH;
	return -1;
}