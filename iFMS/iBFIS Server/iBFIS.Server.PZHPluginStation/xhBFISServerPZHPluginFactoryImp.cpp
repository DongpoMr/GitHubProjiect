#include "StdAfx.h"
#include "xhBFISServerPZHPluginFactoryImp.h"
#include "IcmsP_Utility.h"
#include "xhBFISServerPZHPluginImp.h"

xhBFISServerPZHPluginFactoryImp::xhBFISServerPZHPluginFactoryImp(void)
{
}


xhBFISServerPZHPluginFactoryImp::~xhBFISServerPZHPluginFactoryImp(void)
{
}

CISocObject* xhBFISServerPZHPluginFactoryImp::CreateObject( ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/ )
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFIS_BASE_PLUGIN)
	{
		static xhBFISServerPZHPluginImp obj;
		return &obj;
	}
	return nullptr;
	SCATCH;
	return nullptr;
}

ISOC_VOID xhBFISServerPZHPluginFactoryImp::ReleaseObject( CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/ )
{
	STRY;
	if (ppObj == NULL || *ppObj == NULL)
		return;

	CISocObject *pObj = *ppObj;
	if (pObj->GetObjectType() == OBJECT_TYPE_BFIS_BASE_PLUGIN)
	{
		delete pObj;
		*ppObj = NULL;
	}
	SCATCH;
}

ISOC_bool xhBFISServerPZHPluginFactoryImp::HasObjectInObjType( ISOC_UINT nObjType )
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFIS_BASE_PLUGIN)
	{
		return ISOC_true;
	}
	return ISOC_false;
	SCATCH;
	return ISOC_false;
}

ISOC_INT xhBFISServerPZHPluginFactoryImp::GetObjectFacilityLevel( ISOC_UINT nObjType,const ISOC_STR strFacilityDes )
{
	STRY;
	std::string strPZH(strFacilityDes);
	if (nObjType == OBJECT_TYPE_BFIS_BASE_PLUGIN && strPZH == "PZH")
	{
		return 5;
	}
	return -1;
	SCATCH;
	return -1;
}
