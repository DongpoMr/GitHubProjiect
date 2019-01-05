#pragma once
#include "IBFISMCOperateStation.h"
#include "Poco/Event.h"
#include "iSOC_LoginModule.h"


class XhBFISMCOperateStatinImp:public IBFISMCOperateStation
{
public:
    XhBFISMCOperateStatinImp();

    virtual ~XhBFISMCOperateStatinImp();

    virtual int LoginLocalMC(const std::string& strMCIp, unsigned short uMCPort, const std::string& strMCUserNmae, const std::string& strMCPwd);

    virtual int GetLoclMCInfo(ST_UserInfo& stUser);

    static ISOC_INT __stdcall static_OperatorCallback(const OperatorState enState, const ISOC_INT nOperatorType, const ISOC_STR strDes, const ISOC_DWORDPTR dwCookie, ISOC_DWORDPTR dwResevered);

    virtual int GetMCSession(LONG_PTR& pMCSession);
private:
    LONG_PTR m_lLocalMCSession;
    Poco::Event m_eventLoginLocalMC;
    std::string m_strLocalMCIp;
    unsigned short m_uLocalMCPort;
    std::string m_strLocalMCUserName;
    std::string m_strLocalMCPwd;
    LONG_PTR m_lManSession;
    bool m_bIsLogin;
};
