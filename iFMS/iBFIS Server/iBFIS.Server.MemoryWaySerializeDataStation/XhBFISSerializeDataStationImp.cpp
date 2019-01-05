#include "stdafx.h"
#include "XhBFISSerializeDataStationImp.h"
#include "IcmsP_Utility.h"
#include<stdlib.h>


XhBFISSerializeDataStationImp::XhBFISSerializeDataStationImp()
{
}


XhBFISSerializeDataStationImp::~XhBFISSerializeDataStationImp()
{
	clear();
}

ISOC_BOOL XhBFISSerializeDataStationImp::SetEachPackageStoredDataNumber(IN int nStoreNum)
{
	m_nStoreNum = nStoreNum;
	return true;
}

int XhBFISSerializeDataStationImp::GetEachPackageStoredDataNumber()
{
	return m_nStoreNum;
}

ISOC_BOOL XhBFISSerializeDataStationImp::SetPacketInfo(IN int nKey, IN int nDataSize, IN int nDataCount)
{
	if (false == IsKeyValidCheck(nKey))
		return false;
	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csDataSpaceMtx, __FUNCTION__);
	auto itor = m_dataSpaceMap.find(nKey);
	if (itor != m_dataSpaceMap.end())
		itor->second.nUserSpace = nDataSize;
	SCATCH;

	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csDataNotFullPackeMtx, __FUNCTION__);
	auto itor = m_dataNotFullPacke.find(nKey);
	if (itor != m_dataNotFullPacke.end())
	{
		if (nDataCount >= m_nStoreNum)
			m_dataNotFullPacke.erase(itor);
		else
			itor->second = nDataCount;
	}
	else
	{
		if (nDataCount < m_nStoreNum)
			m_dataNotFullPacke[nKey] = nDataCount;
	}
	SCATCH;
	return true;
}

int XhBFISSerializeDataStationImp::CreateKey()
{
	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csDataVecMtx, __FUNCTION__);
	int nPos = m_dataVec.size();
	m_dataVec.push_back(reinterpret_cast<BYTE*>(malloc(1)));
	return nPos;
	SCATCH;
	return -1;
}

int XhBFISSerializeDataStationImp::CreateDataPacket(IN int nSize, IN int nKey, OUT BYTE**pData)
{
	if (false == IsKeyValidCheck(nKey) || nSize > MAX_ALLOCATION_SPACE)
		return -1;
	STRY;
	int nLenth = nSize * sizeof(BYTE);
	*pData = reinterpret_cast<BYTE*>(malloc(nLenth));
	if (*pData != nullptr)
	{
		memset(*pData, 0, nLenth);
		BYTE *pSrc = nullptr;
		STRY;
		iCMSP_SimpleLock lockLinkContext(&m_csDataVecMtx, __FUNCTION__);
		pSrc = m_dataVec[nKey];
		m_dataVec[nKey] = *pData;
		SCATCH;
		if (pSrc)
			free(pSrc);

		STRY;
		iCMSP_SimpleLock lockLinkContext(&m_csDataNotFullPackeMtx, __FUNCTION__);
		m_dataNotFullPacke[nKey] = 0;
		SCATCH;

		SERIALIZE_SPACE_INFO_STB stSpace;
		stSpace.nUserSpace = 0;
		stSpace.nTotalSpace = nLenth;
		iCMSP_SimpleLock lockLinkContext(&m_csDataSpaceMtx, __FUNCTION__);
		m_dataSpaceMap[nKey] = stSpace;
		return 1;
	}
	SCATCH;
	return -3;
}

int XhBFISSerializeDataStationImp::ReallocatePacket(IN int nSize, IN int nKey, OUT BYTE **pData)
{
	if (nSize > MAX_ALLOCATION_SPACE)
		return -1;
	if (nullptr == *pData)
		return -2;
	STRY;
	int nLenth = nSize * sizeof(BYTE);
	*pData = reinterpret_cast<BYTE*>(malloc(nLenth));
	if (*pData != nullptr)
	{
		BYTE *pCurrData = nullptr;
		if (false == IsKeyValidCheck(nKey))
			return -1;
		{
			iCMSP_SimpleLock lockLinkContext(&m_csDataSpaceMtx, __FUNCTION__);
			m_dataSpaceMap[nKey].nUserSpace = 0;
			m_dataSpaceMap[nKey].nTotalSpace = nLenth;
		}
		STRY;
		iCMSP_SimpleLock lockLinkContext(&m_csDataVecMtx, __FUNCTION__);
		pCurrData = m_dataVec[nKey];
		memset(*pData, 0, nLenth);
		m_dataVec[nKey] = *pData;
		SCATCH;

		if (pCurrData)
			free(pCurrData);
		return 1;
	}
	SCATCH;
	return -3;
}

ISOC_BOOL XhBFISSerializeDataStationImp::GetNotFullPacket(OUT int & nKey)
{
	if (!m_dataNotFullPacke.empty())
	{
		nKey = m_dataNotFullPacke.begin()->first;
		return true;
	}
	return false;
}

ISOC_BOOL XhBFISSerializeDataStationImp::SetDataPacketPos(IN std::string strInfoKey, IN int nKey, IN int nDataPos)
{
	if (strInfoKey.empty())
		return false;
	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csDataPosInfoMtx, __FUNCTION__);
	auto itor = m_dataPosInfoMap.find(strInfoKey);
	if (itor != m_dataPosInfoMap.end())
	{
		itor->second.nPacketKey = nKey;
		itor->second.nDataPos = nDataPos;
		return true;
	}
	else
	{
		SERIALIZE_POS_INFO_STB stPosInfo;
		stPosInfo.nPacketKey = nKey;
		stPosInfo.nDataPos = nDataPos;
		m_dataPosInfoMap[strInfoKey] = stPosInfo;
		return true;
	}
	SCATCH;
	return false;
}

ISOC_BOOL XhBFISSerializeDataStationImp::GetDataPacketPos(IN std::string strInfo, OUT int & nKey, OUT int& nDataPos)
{
	if (strInfo.empty())
		return false;
	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csDataPosInfoMtx, __FUNCTION__);
	auto itor = m_dataPosInfoMap.find(strInfo);
	if (itor != m_dataPosInfoMap.end())
	{
		nKey = itor->second.nPacketKey;
		nDataPos = itor->second.nDataPos;
		return true;
	}
	SCATCH;
	return false;
}

ISOC_BOOL XhBFISSerializeDataStationImp::DelDataPacketPos(IN std::string strInfo)
{
	if (strInfo.empty())
		return false;
	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csDataPosInfoMtx, __FUNCTION__);
	auto itor = m_dataPosInfoMap.find(strInfo);
	if (itor != m_dataPosInfoMap.end())
	{
		m_dataPosInfoMap.erase(itor);
		return true;
	}
	SCATCH;
	return false;
}

ISOC_BOOL XhBFISSerializeDataStationImp::GetDataPacket(IN int nKey, OUT BYTE **pData, OUT int& nDataSize, OUT int& nTotalDataSize)
{
	if (nullptr == pData)
		return -1;
	if (false == IsKeyValidCheck(nKey))
		return -1;
	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csDataVecMtx, __FUNCTION__);
	*pData = m_dataVec[nKey];
	SCATCH;

	iCMSP_SimpleLock lockLinkContext(&m_csDataSpaceMtx, __FUNCTION__);
	nDataSize = m_dataSpaceMap[nKey].nUserSpace;
	nTotalDataSize = m_dataSpaceMap[nKey].nTotalSpace;
	return 1;
}

int XhBFISSerializeDataStationImp::GetPacketCount()
{
	iCMSP_SimpleLock lockLinkContext(&m_csDataVecMtx, __FUNCTION__);
	return m_dataVec.size();
}

void XhBFISSerializeDataStationImp::clear()
{
	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csDataVecMtx, __FUNCTION__);
	STRY;
	for each(auto var in m_dataVec)
		free(var);
	
	SCATCH;
	m_dataVec.clear();
	SCATCH;

	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csDataNotFullPackeMtx, __FUNCTION__);
	m_dataNotFullPacke.clear();
	SCATCH;

	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csDataSpaceMtx, __FUNCTION__);
	m_dataSpaceMap.clear();
	SCATCH;

	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csDataPosInfoMtx, __FUNCTION__);
	m_dataPosInfoMap.clear();
	SCATCH;

	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csSpecialDataMapMtx, __FUNCTION__);
	m_specialDataPosInfoMap.clear();
	SCATCH;
}

iCMSP_WRLock * XhBFISSerializeDataStationImp::GetWRLock()
{
	return &m_csWRMtx;
}

ISOC_BOOL XhBFISSerializeDataStationImp::SetDataPacketPos(IN std::string strInfoKey, IN std::string strInfoKey2, IN int nKey, IN int nDataPos)
{
	if (strInfoKey.empty() || strInfoKey2.empty())
		return false;
	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csSpecialDataMapMtx, __FUNCTION__);
	auto itor = m_specialDataPosInfoMap.find(strInfoKey);
	if (itor != m_specialDataPosInfoMap.end())
	{
		SERIALIZE_POS_INFO_STB stPosInfo;
		stPosInfo.nPacketKey = nKey;
		stPosInfo.nDataPos = nDataPos;
		itor->second[strInfoKey2] = stPosInfo;
		return true;
	}
	else
	{
		std::unordered_map<std::string, SERIALIZE_POS_INFO_STB> mapData;
		SERIALIZE_POS_INFO_STB stPosInfo;
		stPosInfo.nPacketKey = nKey;
		stPosInfo.nDataPos = nDataPos;
		mapData[strInfoKey2] = stPosInfo;
		m_specialDataPosInfoMap[strInfoKey] = mapData;
		return true;
	}
	SCATCH;
	return false;
}

ISOC_BOOL XhBFISSerializeDataStationImp::GetDataPacketPos(IN std::string strInfo, OUT std::unordered_map<std::string, SERIALIZE_POS_INFO_STB>& mapDataPosInfo)
{
	if (strInfo.empty())
		return false;
	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csSpecialDataMapMtx, __FUNCTION__);
	auto itor = m_specialDataPosInfoMap.find(strInfo);
	if (itor != m_specialDataPosInfoMap.end())
	{
		mapDataPosInfo = itor->second;
		return true;
	}
	SCATCH;
	return false;
}

ISOC_BOOL XhBFISSerializeDataStationImp::DelDataPacketPos(IN std::string strInfoKey, IN std::string strInfoKey2)
{
	if (strInfoKey.empty() || strInfoKey2.empty())
		return false;
	STRY;
	iCMSP_SimpleLock lockLinkContext(&m_csSpecialDataMapMtx, __FUNCTION__);
	auto itor = m_specialDataPosInfoMap.find(strInfoKey);
	if (itor != m_specialDataPosInfoMap.end())
	{
		auto item = itor->second.find(strInfoKey2);
		if (item != itor->second.end())
		{
			itor->second.erase(item);
			return true;
		}
	}
	SCATCH;
	return false;
}

bool XhBFISSerializeDataStationImp::IsKeyValidCheck(int nKey)
{
	iCMSP_SimpleLock lockLinkContext(&m_csDataVecMtx, __FUNCTION__);
	if (nKey >= 0 && nKey < m_dataVec.size())
		return true;
	return false;
}
