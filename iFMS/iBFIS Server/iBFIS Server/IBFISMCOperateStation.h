#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iSOC_PublicStructDefine.h"
#include "iBFIS_UniqueDefine.h"
#include <string>

interface IBFISMCOperateStation :CISocObject
{
    IBFISMCOperateStation()
    {
        m_nObjectType = OBJECT_TYPE_BFISSERVER_MCOPERATESTATION;
    }

    virtual ~IBFISMCOperateStation() {};

    virtual int LoginLocalMC(const std::string& strMCIp, unsigned short uMCPort, const std::string& strMCUserNmae, const std::string& strMCPwd) = 0;
    virtual int GetLoclMCInfo(ST_UserInfo& stUser) = 0;
    virtual int GetMCSession(LONG_PTR& pMCSession) = 0;

};