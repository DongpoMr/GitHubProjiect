#include "stdafx.h"
#include "XhBFISMCOperateStatiomFactoryImp.h"
#include "XhBFISMCOperateStatinImp.h"
#include "IcmsP_Utility.h"

XhBFISMCOperateStatiomFactoryImp::XhBFISMCOperateStatiomFactoryImp()
{
}


XhBFISMCOperateStatiomFactoryImp::~XhBFISMCOperateStatiomFactoryImp()
{
}

CISocObject* XhBFISMCOperateStatiomFactoryImp::CreateObject(ISOC_UINT nObjType, const ISOC_STR strFacilityDes, const ISOC_STR pFunction, ISOC_DWORDPTR dwReserved /*= NULL*/)
{
    STRY;
    if (nObjType == OBJECT_TYPE_BFISSERVER_MCOPERATESTATION)
    {
        static XhBFISMCOperateStatinImp obj;
        return &obj;
    }
    return nullptr;
    SCATCH;
    return nullptr;
}

ISOC_VOID XhBFISMCOperateStatiomFactoryImp::ReleaseObject(CISocObject** ppObj, const ISOC_STR pFunction, ISOC_DWORDPTR dwReserved /*= NULL*/)
{

}

ISOC_bool XhBFISMCOperateStatiomFactoryImp::HasObjectInObjType(ISOC_UINT nObjType)
{
    STRY;
    if (nObjType == OBJECT_TYPE_BFISSERVER_MCOPERATESTATION)
    {
        return true;
    }
    return false;
    SCATCH;
    return false;
}

ISOC_INT XhBFISMCOperateStatiomFactoryImp::GetObjectFacilityLevel(ISOC_UINT nObjType, const ISOC_STR strFacilityDes)
{
    STRY;
    if (nObjType == OBJECT_TYPE_BFISSERVER_MCOPERATESTATION)
    {
        return 5;
    }
    return -1;
    SCATCH;
    return -1;
}
