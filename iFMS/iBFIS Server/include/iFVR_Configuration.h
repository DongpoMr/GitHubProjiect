#pragma once
#ifndef IFVR_CONFIGURATION_H
#define IFVR_CONFIGURATION_H

#ifdef _IFVR_CONFIGURATION_
    #define iFVR_CONFIGURATION_CLASS_MODE __declspec(dllexport)
#else
    #define iFVR_CONFIGURATION_CLASS_MODE __declspec(dllimport)
#endif

#ifndef _IFVR_CONFIGURATION_
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

class iFVR_CONFIGURATION_CLASS_MODE iFVR_Configuration
{
public:
    iFVR_Configuration();

    virtual ~iFVR_Configuration();

    std::string GetString(const std::string& section, const std::string& key);
    std::string GetString(const std::string& section, const std::string& key, const std::string& defaultValue);

    int GetInt(const std::string& section, const std::string& key);
    int GetInt(const std::string& section, const std::string& key, int defaultValue);

    double GetDouble(const std::string& section, const std::string& key);
    double GetDouble(const std::string& section, const std::string& key, double defaultValue);

    void SetString(const std::string& section, const std::string& key, const std::string value);

    void SetInt(const std::string& section, const std::string& key, int value);

    void SetDouble(const std::string& section, const std::string& key, double value);

    int Save();

private:
    int Load(const std::string& path);
};

#endif // !IFVR_CONFIGURATION_H