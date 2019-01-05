#pragma once
#include <string.h>
#include "IcmsP_Utility.h"
#include <boost/format.hpp>

class XhAutoScalUseTime
{
public:
	XhAutoScalUseTime(std::string strText) : m_bIsWriteLogFile(false)
	{
		m_strText = strText;
		memset(&m_liPerfFreq, 0, sizeof(LARGE_INTEGER));
		memset(&m_liPerfStart, 0, sizeof(LARGE_INTEGER));
		QueryPerformanceFrequency(&m_liPerfFreq);
		QueryPerformanceCounter(&m_liPerfStart);
	}

	XhAutoScalUseTime(std::string strText, bool bWriteLogFile) : m_bIsWriteLogFile(bWriteLogFile)
	{
		m_strText = strText;
		memset(&m_liPerfFreq, 0, sizeof(LARGE_INTEGER));
		memset(&m_liPerfStart, 0, sizeof(LARGE_INTEGER));
		QueryPerformanceFrequency(&m_liPerfFreq);
		QueryPerformanceCounter(&m_liPerfStart);
	}

	~XhAutoScalUseTime()
	{
		LARGE_INTEGER liPerfNow = { 0 };
		QueryPerformanceCounter(&liPerfNow);
		double time = ((double)(((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000)) / ((double)m_liPerfFreq.QuadPart));
		std::string strFormatedText = (boost::format("%1%使用时间：%2%ms\r\n") % m_strText % time).str();
		if (m_bIsWriteLogFile)
		{
			TTRACE(strFormatedText.c_str());
		}
		else
		{
			//OutputDebugString(strFormatedText.c_str());
		}
		
	}

private:
	LARGE_INTEGER m_liPerfFreq;
	LARGE_INTEGER m_liPerfStart;
	std::string m_strText;
	bool		m_bIsWriteLogFile;
};