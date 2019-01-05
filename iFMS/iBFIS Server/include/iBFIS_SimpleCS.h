#pragma once
#include "iCMSP_SimpleLock.h"

class iBFIS_SimpleCS
{
public:
	iBFIS_SimpleCS():m_pCS(nullptr){}
	~iBFIS_SimpleCS()
	{
		if (m_pCS)
		{
			m_pCS->LeaveCS();
		}
		m_pCS = nullptr;
	}
public:
	void EnterCS(iCMSP_SimpleCS *pCS, const TCHAR* pCallFun) 
	{
		if (pCS)
		{
			m_pCS = pCS;
			m_pCS->EnterCS(pCallFun);
		}
	}
private:
	iCMSP_SimpleCS *m_pCS;
};