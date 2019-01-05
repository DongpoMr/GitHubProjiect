#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iBFIS_UniqueDefine.h"

interface IBFISTaskStation : public CISocObject
{
    virtual ~IBFISTaskStation() {};
    virtual int InitStation() = 0;	//在各自的初始化函数中调用IBFISCommunicateStation的RegisterRecvMessageCallbackSkin来注册各自需要处理的信令
    virtual int UnInitStation() = 0;
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, std::string& s) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, std::vector<DWORD_PTR>& v, DWORD_PTR& d1, DWORD_PTR& d2) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, std::vector<std::string>& v) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, BYTE* data, int nDataLen) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, std::vector<DWORD_PTR>& v1, std::vector<std::string>& v2) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d1, DWORD_PTR& d2) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d, std::string& s) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d, BYTE* pData, int nDataLen) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d1, DWORD_PTR& d2, DWORD_PTR& d3) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, std::string& s1, std::string& s2, std::string& s3) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d1, DWORD_PTR& d2, std::string& s) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d, std::string& s1, std::string& s2) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d1, DWORD_PTR& d2, DWORD_PTR& d3, DWORD_PTR& d4) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, std::string& s1, std::string& s2, std::string& s3, std::string& s4) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d1, std::vector<std::string>& v1) { return -1; };
    virtual int OnRecvData(UINT64 fromAddr, DWORD_PTR& d1, std::vector<std::string>& v1, std::vector<std::string>& v2, std::vector<std::string>& v3) { return -1; };
};