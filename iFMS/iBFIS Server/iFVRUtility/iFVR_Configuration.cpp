#include "stdafx.h"
#include "iFVR_Configuration.h"
#include "Poco/Util/IniFileConfiguration.h"
#include "Poco/Path.h"
#include "Poco/AutoPtr.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/Mutex.h"
#include "Poco/UTFString.h"
#include "Poco/UnicodeConverter.h"
#include <iostream>
#include "IcmsP_Utility.h"

using namespace Poco::Util;

class XhConfigurationMan
{
public:
    static XhConfigurationMan* Instance();
    virtual ~XhConfigurationMan() {};

    std::string GetString(const std::string& section, const std::string& key);
    std::string GetString(const std::string& section, const std::string& key, const std::string& defaultValue);

    int GetInt(const std::string& section, const std::string& key);
    int GetInt(const std::string& section, const std::string& key, int defaultValue);

    double GetDouble(const std::string& section, const std::string& key);
    double GetDouble(const std::string& section, const std::string& key, double defaultValue);

    void SetString(const std::string& section, const std::string& key, const std::string value);

    void SetInt(const std::string& section, const std::string& key, int value);

    void SetDouble(const std::string& section, const std::string& key, double value);

    int Load(const std::string& path);
    int Save();
private:
    XhConfigurationMan();
    Poco::FastMutex m_lockConfig;
    Poco::AutoPtr<IniFileConfiguration> m_configPtr;
    std::string m_strConfigPath;
};
 
std::string strtoUTF8(const char* str)  
{  
#if defined (POCO_WIN32_UTF8)   
	std::string s = str;  
	setlocale(LC_ALL, "chs");     
	const char* _Source = s.c_str();    
	size_t _Dsize = s.size() + 1;    
	Poco::UTF16Char *_Dest = new wchar_t[_Dsize];    
	wmemset(_Dest, 0, _Dsize);    
	mbstowcs(_Dest, _Source, _Dsize);  
	Poco::UTF16String result = _Dest;    
	delete []_Dest;    
	setlocale(LC_ALL, "C");   

	std::string utf8str;  
	Poco::UnicodeConverter::convert(result, utf8str);   

	return utf8str;  
#else  
	return str;  
#endif  
}
XhConfigurationMan::XhConfigurationMan()
{
    m_configPtr = new IniFileConfiguration;
    std::string strConfigPath = std::string(GetWorkingDirectory()) + "\\Config\\iBFIS.Server.Config.ini";
	std::string strConfigPathUTF8 = strtoUTF8(strConfigPath.c_str());
	Load(strConfigPathUTF8);
}

XhConfigurationMan* XhConfigurationMan::Instance()
{
    static XhConfigurationMan obj;
    return &obj;
}

std::string XhConfigurationMan::GetString(const std::string& section, const std::string& key)
{
    std::string strKey = section + "." + key;
    return m_configPtr->getString(strKey);
}

std::string XhConfigurationMan::GetString(const std::string& section, const std::string& key, const std::string& defaultValue)
{
    std::string strKey = section + "." + key;
    return m_configPtr->getString(strKey, defaultValue);
}

int XhConfigurationMan::GetInt(const std::string& section, const std::string& key)
{
    std::string strKey = section + "." + key;
    return m_configPtr->getInt(strKey);
}

int XhConfigurationMan::GetInt(const std::string& section, const std::string& key, int defaultValue)
{
    std::string strKey = section + "." + key;
    return m_configPtr->getInt(strKey, defaultValue);
}

double XhConfigurationMan::GetDouble(const std::string& section, const std::string& key)
{
    std::string strKey = section + "." + key;
    return m_configPtr->getDouble(strKey);
}

double XhConfigurationMan::GetDouble(const std::string& section, const std::string& key, double defaultValue)
{
    std::string strKey = section + "." + key;
    return m_configPtr->getDouble(strKey, defaultValue);
}

int XhConfigurationMan::Load(const std::string& path)
{
    m_strConfigPath = path;
    m_configPtr->load(path);
    return 1;
}

int XhConfigurationMan::Save()
{
    {
        Poco::File configFile(m_strConfigPath);
        if (!configFile.canWrite()) //设置可写，否则无法插入数据
        {
            configFile.setWriteable(true);
        }
    }
    Poco::FastMutex::ScopedLock lock(m_lockConfig);
    Poco::FileStream fs(m_strConfigPath, std::ios::in | std::ios::out | std::ios::trunc);
    AbstractConfiguration::Keys keys;
    m_configPtr->keys(keys);
    int nKeySize = keys.size();
    for (int i = 0; i < nKeySize; i++)
    {
        AbstractConfiguration::Keys key;
        m_configPtr->keys(keys[i], key);
        int nItemSize = key.size();
        //写入sesction
        fs << "[" << keys[i] << "]\r\n";
        for (int j = 0; j < nItemSize; j++)
        {
            std::string strKey = keys[i] + "." + key[j];
            std::string strItem = m_configPtr->getString(strKey);
            //写入item
            fs << key[j] << "=" << strItem << "\r\n";
        }
    }
    fs.flush();
    fs.close();
    return 1;
}

void XhConfigurationMan::SetString(const std::string& section, const std::string& key, const std::string value)
{
    std::string strKey = section + "." + key;
    m_configPtr->setString(strKey, value);
}

void XhConfigurationMan::SetDouble(const std::string& section, const std::string& key, double value)
{
    std::string strKey = section + "." + key;
    m_configPtr->setDouble(strKey, value);
}

void XhConfigurationMan::SetInt(const std::string& section, const std::string& key, int value)
{
    std::string strKey = section + "." + key;
    m_configPtr->setInt(strKey, value);
}



iFVR_Configuration::iFVR_Configuration()
{
}


iFVR_Configuration::~iFVR_Configuration()
{
}

std::string iFVR_Configuration::GetString(const std::string& section, const std::string& key)
{
    return XhConfigurationMan::Instance()->GetString(section, key);
}

std::string iFVR_Configuration::GetString(const std::string& section, const std::string& key, const std::string& defaultValue)
{
    return XhConfigurationMan::Instance()->GetString(section, key, defaultValue);
}

int iFVR_Configuration::GetInt(const std::string& section, const std::string& key)
{
    return XhConfigurationMan::Instance()->GetInt(section, key);
}

int iFVR_Configuration::GetInt(const std::string& section, const std::string& key, int defaultValue)
{
    return XhConfigurationMan::Instance()->GetInt(section, key, defaultValue);
}

double iFVR_Configuration::GetDouble(const std::string& section, const std::string& key)
{
    return XhConfigurationMan::Instance()->GetDouble(section, key);
}

double iFVR_Configuration::GetDouble(const std::string& section, const std::string& key, double defaultValue)
{
    return XhConfigurationMan::Instance()->GetDouble(section, key, defaultValue);
}

int iFVR_Configuration::Save()
{
    return XhConfigurationMan::Instance()->Save();
}

int iFVR_Configuration::Load(const std::string& path)
{
    return 1;
}

void iFVR_Configuration::SetString(const std::string& section, const std::string& key, const std::string value)
{
    return XhConfigurationMan::Instance()->SetString(section, key, value);
}

void iFVR_Configuration::SetInt(const std::string& section, const std::string& key, int value)
{
    return XhConfigurationMan::Instance()->SetInt(section, key, value);
}

void iFVR_Configuration::SetDouble(const std::string& section, const std::string& key, double value)
{
    return XhConfigurationMan::Instance()->SetDouble(section, key, value);
}
