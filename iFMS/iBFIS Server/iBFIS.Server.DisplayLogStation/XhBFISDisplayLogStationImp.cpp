#include "StdAfx.h"
#include "XhBFISDisplayLogStationImp.h"


XhBFSDisplayLogStationImp::XhBFSDisplayLogStationImp(void):m_pCallbackSkin(nullptr)
{
}


XhBFSDisplayLogStationImp::~XhBFSDisplayLogStationImp(void)
{
}

ISOC_INT XhBFSDisplayLogStationImp::DisplayLog( IN const ST_BFISLogInfo& info,IN ISOC_DWORDPTR dwReserved /*= NULL*/ )
{
	if(m_pCallbackSkin)
	{
		return m_pCallbackSkin->OnGotLogInfo(info,dwReserved);
	}
	return -1;
}

ISOC_INT XhBFSDisplayLogStationImp::SetDisplayLogCallbackSkin( IN IBFISDisplayLogCallbackSkin* pSkin )
{
	m_pCallbackSkin = pSkin;
	return 1;
}

ISOC_INT XhBFSDisplayLogStationImp::ExtendFunc( IN ISOC_INT nExType,IN ISOC_DWORDPTR dwExtendData,IN ISOC_DWORDPTR dwReserved /*= NULL*/ )
{
	return 1;
}

int XhBFSDisplayLogStationImp::DisplayTaskPlanInfo(IN const ST_TaskPlan& info, IN DWORD_PTR dwReserved /*= NULL*/)
{
    if (m_pCallbackSkin)
    {
        return m_pCallbackSkin->OnGotTaskPlanInfo(info, dwReserved);
    }
    return -1;
}

int XhBFSDisplayLogStationImp::DisplayConnectionInfo(IN const ST_BFISConnectionInfo& info, IN DWORD_PTR dwReserved /*= NULL*/)
{
    if (m_pCallbackSkin)
    {
        return m_pCallbackSkin->OnGotConnectionInfo(info, dwReserved);
    }
    return -1;
}
