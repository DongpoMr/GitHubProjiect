#include "stdafx.h"
#include "XhBFISMCOperateStatinImp.h"
#include "iSOC_LoginModule.h"
#include "IcmsP_Utility.h"
#include "iSOC_ManLoginModule.h"

XhBFISMCOperateStatinImp::XhBFISMCOperateStatinImp()
{
    m_lLocalMCSession = NULL;
    m_uLocalMCPort = 0;
    m_bIsLogin = false;
}


XhBFISMCOperateStatinImp::~XhBFISMCOperateStatinImp()
{
}

int XhBFISMCOperateStatinImp::LoginLocalMC(const std::string& strMCIp, unsigned short uMCPort, const std::string& strMCUserNmae, const std::string& strMCPwd)
{
    if (m_lLocalMCSession == NULL)
    {
        int nRet = iSOC_UserLogin(strMCIp.c_str(), uMCPort, strMCUserNmae.c_str(), strMCPwd.c_str(), &m_lLocalMCSession, static_OperatorCallback, reinterpret_cast<DWORD_PTR>(this));
        if (nRet <= 0)
        {
            iSOC_UserLogout(m_lLocalMCSession);
            m_lLocalMCSession = NULL;
            return nRet;
        }
        if (m_lManSession == NULL)
        {
            int nRet = iSOC_ManUserLogin(strMCIp.c_str(), uMCPort, strMCUserNmae.c_str(), strMCPwd.c_str(), &m_lManSession);
            if (nRet <= 0)
            {
                iSOC_ManUserLogout(m_lManSession,0);
                m_lManSession = NULL;
                return nRet;
            }
        }
        m_eventLoginLocalMC.reset();
        m_eventLoginLocalMC.tryWait(2 * 60 * 1000); //等待2分钟，防止sdk没有回调
		if(m_bIsLogin)
            return 1;
        else
        {
            iSOC_UserLogout(m_lLocalMCSession);
            m_lLocalMCSession = NULL;
            return -1;
        }
    }
}

int XhBFISMCOperateStatinImp::GetMCSession(LONG_PTR& pMCSession)
{
    if (NULL == m_lManSession)
    {
        return -1;  
    } 
    pMCSession = m_lManSession;
    return TRUE;
}
int XhBFISMCOperateStatinImp::GetLoclMCInfo(ST_UserInfo& stUser)
{
    if (!m_bIsLogin)
        return -1;

    return iSOC_GetUserInfo(m_lLocalMCSession, &stUser);
}

ISOC_INT __stdcall XhBFISMCOperateStatinImp::static_OperatorCallback(const OperatorState enState, const ISOC_INT nOperatorType, const ISOC_STR strDes, const ISOC_DWORDPTR dwCookie, ISOC_DWORDPTR dwResevered)
{
    switch (nOperatorType)
    {
    case OT_LOGIN:
    {
        if (enState == OPERATOR_SUCCEEDED)
        {
            XhBFISMCOperateStatinImp* pThis = reinterpret_cast<XhBFISMCOperateStatinImp*>(dwCookie);
            //登陆成功
            pThis->m_bIsLogin = true;
            pThis->m_eventLoginLocalMC.set();
            break;
        }
        else
        {
            TTRACE("%s[%d]: SDK回调登陆MC失败\r\n", __FUNCTION__, __LINE__);
            XhBFISMCOperateStatinImp* pThis = reinterpret_cast<XhBFISMCOperateStatinImp*>(dwCookie);
            //登陆成功
            pThis->m_bIsLogin = false;
            pThis->m_eventLoginLocalMC.set();
            break;
        }
    }
    default:
        break;
    }
    return 1;
}
