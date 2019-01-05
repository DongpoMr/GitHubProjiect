#pragma once
#ifndef IFVR_UTILITY_H
#define IFVR_UTILITY_H

#ifdef _IFVR_CONFIGURATION_
#define iFVR_CONFIGURATION_CLASS_MODE __declspec(dllexport)
#else
#define iFVR_CONFIGURATION_CLASS_MODE __declspec(dllimport)
#endif

#ifndef _IFVR_UTILITY_
#ifdef _DEBUG
#ifdef _UNICODE
#pragma comment(lib,"iFVRUtilityud.lib")
#else
#pragma comment(lib,"iFVRUtilityd.lib")
#endif
#else
#ifdef _UNICODE
#pragma comment(lib,"iFVRUtilityu.lib")
#else
#pragma comment(lib,"iFVRUtility.lib")
#endif			
#endif
#endif

#include <string>
#include <vector>

class iFVR_CONFIGURATION_CLASS_MODE iFVR_Utility
{
public:
    iFVR_Utility();

    virtual ~iFVR_Utility();

    static std::vector<std::string> LoclIpAddress();
    static std::string CreateGUID();
};

#endif // !IFVR_UTILITY_H



