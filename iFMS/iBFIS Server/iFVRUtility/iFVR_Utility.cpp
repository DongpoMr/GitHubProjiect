#include "stdafx.h"
#include "iFVR_Utility.h"
#include "Poco/Net/HostEntry.h"
#include "Poco/Net/DNS.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

iFVR_Utility::iFVR_Utility()
{
}


iFVR_Utility::~iFVR_Utility()
{
}

std::vector<std::string> iFVR_Utility::LoclIpAddress()
{
    std::vector<std::string> vecData;
    Poco::Net::HostEntry::AddressList addrList = Poco::Net::DNS::thisHost().addresses();
    for each(const auto& addr in addrList)
    {
        if (addr.isIPv4Compatible())
            vecData.push_back(addr.toString());
    }
    return vecData;
}

std::string iFVR_Utility::CreateGUID()
{
#if 0   //windows 2003上连续创建会生成重复的
    Poco::UUIDGenerator umake;
    std::string strGUID = umake.create().toString();
    return strGUID;
#else
	std::string strGUID;
	char pBuf[64] = {0};
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snprintf(pBuf,sizeof(pBuf),"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"
			,guid.Data1
			,guid.Data2
			,guid.Data3
			,guid.Data4[0],guid.Data4[1]
		,guid.Data4[2],guid.Data4[3],guid.Data4[4],guid.Data4[5]
		,guid.Data4[6],guid.Data4[7]);
	}
	strGUID = pBuf;
    return strGUID;
#endif
}
