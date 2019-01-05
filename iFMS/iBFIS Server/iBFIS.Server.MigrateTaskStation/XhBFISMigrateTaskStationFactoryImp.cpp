#include "stdafx.h"
#include "XhBFISMigrateTaskStationFactoryImp.h"
#include "XhBFISMigrateTaskStationImp.h"
#include "IcmsP_Utility.h"

XhBFISMigrateTaskStationFactoryImp::XhBFISMigrateTaskStationFactoryImp()
{
}


XhBFISMigrateTaskStationFactoryImp::~XhBFISMigrateTaskStationFactoryImp()
{
}

CISocObject* XhBFISMigrateTaskStationFactoryImp::CreateObject(ISOC_UINT nObjType, const ISOC_STR strFacilityDes, const ISOC_STR pFunction, ISOC_DWORDPTR dwReserved /*= NULL*/)
{
    STRY;
    if (nObjType == OBJECT_TYPE_BFISSERVER_MIGRATETASKSTATION)
    {
        static XhBFISMigrateTaskStationImp obj;
        return &obj;
    }
    return NULL;
    SCATCH;
    return NULL;
}

ISOC_VOID XhBFISMigrateTaskStationFactoryImp::ReleaseObject(CISocObject** ppObj, const ISOC_STR pFunction, ISOC_DWORDPTR dwReserved /*= NULL*/)
{

}

ISOC_bool XhBFISMigrateTaskStationFactoryImp::HasObjectInObjType(ISOC_UINT nObjType)
{
    STRY;
    if (nObjType == OBJECT_TYPE_BFISSERVER_MIGRATETASKSTATION)
    {
        return true;
    }
    return false;
    SCATCH;
    return false;
}

ISOC_INT XhBFISMigrateTaskStationFactoryImp::GetObjectFacilityLevel(ISOC_UINT nObjType, const ISOC_STR strFacilityDes)
{
    STRY;
    if (nObjType == OBJECT_TYPE_BFISSERVER_MIGRATETASKSTATION)
    {
        return 5;
    }
    return -1;
    SCATCH;
    return -1;
}
