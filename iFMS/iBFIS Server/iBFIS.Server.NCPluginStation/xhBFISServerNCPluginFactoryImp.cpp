#include "StdAfx.h"
#include "xhBFISServerNCPluginFactoryImp.h"
#include "xhBFISServerNCPluginImp.h"
#include "IcmsP_Utility.h"


xhBFISServerNCPluginFactoryImp::xhBFISServerNCPluginFactoryImp(void)
{
}


xhBFISServerNCPluginFactoryImp::~xhBFISServerNCPluginFactoryImp(void)
{
}

CISocObject* xhBFISServerNCPluginFactoryImp::CreateObject( ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/ )
{
	STRY;
	if (nObjType == OBJECT_TYPE_BFIS_BASE_PLUGIN)
	{
		static xhBFISServerNCPluginImp obj;
		return &obj;
	}
	return nullptr;
	SCATCH;
	return nullptr;
}

ISOC_VOID xhBFISServerNCPluginFactoryImp::ReleaseObject( CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved /*= NULL*/ )
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

ISOC_bool xhBFISServerNCPluginFactoryImp::HasObjectInObjType( ISOC_UINT nObjType )
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

ISOC_INT xhBFISServerNCPluginFactoryImp::GetObjectFacilityLevel( ISOC_UINT nObjType,const ISOC_STR strFacilityDes )
{
	STRY;
	std::string strNC(strFacilityDes);
	if (nObjType == OBJECT_TYPE_BFIS_BASE_PLUGIN && strNC == "NC" )
	{
		return 5;
	}
	return -1;
	SCATCH;
	return -1;
}
