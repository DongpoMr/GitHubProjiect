#include "StdAfx.h"
#include "xhBFISServerJZPluginFactoryImp.h"
#include "IcmsP_Utility.h"
#include "xhBFISServerJZPluginImp.h"


xhBFISServerJZPluginFactoryImp::xhBFISServerJZPluginFactoryImp(void)
{
}


xhBFISServerJZPluginFactoryImp::~xhBFISServerJZPluginFactoryImp(void)
{
}

CISocObject* xhBFISServerJZPluginFactoryImp::CreateObject( ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/ )
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFIS_BASE_PLUGIN)
	{
		static xhBFISServerJZPluginImp obj;
		return &obj;
	}
	return nullptr;
	SCATCH;
	return nullptr;
}

ISOC_VOID xhBFISServerJZPluginFactoryImp::ReleaseObject( CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/ )
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

ISOC_bool xhBFISServerJZPluginFactoryImp::HasObjectInObjType( ISOC_UINT nObjType )
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFIS_BASE_PLUGIN)
	{
		return true;
	}
	return false;
	SCATCH;
	return false;
}

ISOC_INT xhBFISServerJZPluginFactoryImp::GetObjectFacilityLevel( ISOC_UINT nObjType,const ISOC_STR strFacilityDes )
{
	STRY;
	std::string strJZ(strFacilityDes);
	if (nObjType == OBJECT_TYPE_BFIS_BASE_PLUGIN && strJZ == "JZ")
	{
		return 5;
	}
	return -1;
	SCATCH;
	return -1;
}
