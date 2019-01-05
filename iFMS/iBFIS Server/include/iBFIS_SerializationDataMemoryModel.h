#pragma once
#include "BFIS.ProtoMessageDefine.pb.h"
#include "IBFISSerializeDataMemoryModel.h"
#include <string>
#include <vector>

struct ST_EmployeePurviewInfoList
{
	ST_EmployeePurviewInfoList()
	{
		nEmployeePurviewSize = 0;
		vecEmployeePurview.clear();
		nStateSign = 0;
		nReserved = 0;
	}
public:
	//新增
	bool ConvertToArrary(IBFISSerializeDataMemoryModel* pSeriaDataMgr)
	{
		if (vecEmployeePurview.size() <= 0 || nullptr == pSeriaDataMgr)
			return false;

		BFIS::EmployeePurviewInfoList msg;
		int nMaxDataSize = pSeriaDataMgr->GetEachPackageStoredDataNumber();
		int nVecSize = vecEmployeePurview.size();
		nEmployeePurviewSize = 0;
		int nCount = 1;
		int nDataPos = 0;
		int nKey = pSeriaDataMgr->CreateKey();
		for (int i = 0; i < nVecSize; ++i)
		{
			auto item = msg.add_vecemployeepurview();
			item->set_stremployeepurviewid(vecEmployeePurview[i].strEmployeePurviewId);
			item->set_stremployeeid(vecEmployeePurview[i].strEmployeeId);
			item->set_strpurviewinfoid(vecEmployeePurview[i].strPurviewInfoId);
			item->set_nextendedinfo(vecEmployeePurview[i].nExtendedInfo);
			item->set_strextendedinfo1(vecEmployeePurview[i].strExtendedInfo1);
			item->set_strextendedinfo2(vecEmployeePurview[i].strExtendedInfo2);
			++nDataPos;
			if (!vecEmployeePurview[i].strEmployeePurviewId.empty())
			{
				pSeriaDataMgr->SetDataPacketPos(vecEmployeePurview[i].strEmployeePurviewId, nKey, nDataPos);
				if (!vecEmployeePurview[i].strEmployeeId.empty())
					pSeriaDataMgr->SetDataPacketPos(vecEmployeePurview[i].strEmployeeId, vecEmployeePurview[i].strEmployeePurviewId, nKey, nDataPos);
			}
			if ((i + 1) >= nCount * nMaxDataSize || (i + 1) >= nVecSize)
			{
				msg.set_nemployeepurviewsize(nDataPos);
				int nSize = msg.ByteSize();
				BYTE *pData = nullptr;
				if (pSeriaDataMgr->CreateDataPacket(nSize, nKey, &pData) <= 0)
					return false;

				if (pData == nullptr)
					return false;

				bool bSeralizeSuccess = msg.SerializeToArray(pData,nSize);
				if (false == bSeralizeSuccess)
					return false;
				pSeriaDataMgr->SetPacketInfo(nKey, nSize, nDataPos);
				nKey = pSeriaDataMgr->CreateKey();
				msg.Clear();
				nDataPos = 0;
				++nCount; 
			}
		}
		return true;
	}

	//更新
	bool ConvertToArrary(IBFISSerializeDataMemoryModel* pSeriaDataMgr, int nKey)
	{
		if (vecEmployeePurview.size() <= 0 || nullptr == pSeriaDataMgr)
			return false;

		if (nKey < 0 || nKey >= pSeriaDataMgr->GetPacketCount())
			return false;

		BFIS::EmployeePurviewInfoList msg;
		int nMaxDataSize = pSeriaDataMgr->GetEachPackageStoredDataNumber();
		int nVecSize = vecEmployeePurview.size();
		nEmployeePurviewSize = 0;
		int nCount = 1;
		int nDataPos = 0;
		for (int i = 0; i < nVecSize; ++i)
		{
			auto item = msg.add_vecemployeepurview();
			item->set_stremployeepurviewid(vecEmployeePurview[i].strEmployeePurviewId);
			item->set_stremployeeid(vecEmployeePurview[i].strEmployeeId);
			item->set_strpurviewinfoid(vecEmployeePurview[i].strPurviewInfoId);
			item->set_nextendedinfo(vecEmployeePurview[i].nExtendedInfo);
			item->set_strextendedinfo1(vecEmployeePurview[i].strExtendedInfo1);
			item->set_strextendedinfo2(vecEmployeePurview[i].strExtendedInfo2);
			++nDataPos;
			if (!vecEmployeePurview[i].strEmployeePurviewId.empty())
			{
				pSeriaDataMgr->SetDataPacketPos(vecEmployeePurview[i].strEmployeePurviewId, nKey, nDataPos);
				if (!vecEmployeePurview[i].strEmployeeId.empty())
					pSeriaDataMgr->SetDataPacketPos(vecEmployeePurview[i].strEmployeeId, vecEmployeePurview[i].strEmployeePurviewId, nKey, nDataPos);
			}
			if ((i + 1) >= nCount * nMaxDataSize || (i + 1) >= nVecSize)
			{
				msg.set_nemployeepurviewsize(nDataPos);
				int nSize = msg.ByteSize();
				BYTE *pData = nullptr;
				int nDataSize = 0;
				int nTotalDataSize = 0;
				int nRet = pSeriaDataMgr->GetDataPacket(nKey, &pData, nDataSize, nTotalDataSize);
				if (nRet <= 0)
					return false;
				if (nTotalDataSize < nSize)
				{
					pSeriaDataMgr->ReallocatePacket(nSize, nKey, &pData);
				}

				if (pData == nullptr)
					return false;

				bool bSeralizeSuccess = msg.SerializeToArray(pData, nSize);
				if (false == bSeralizeSuccess)
					return false;
				pSeriaDataMgr->SetPacketInfo(nKey, nSize, nDataPos);
				return true;
			}
		}
		return false;
	}

	bool ConvertToStruct(BYTE* pData, int nDataSize, std::vector<ST_EmployeePurviewInfo>& stVecEmployeePurviewInfo)
	{
		if (nullptr == pData)
			return false;
		BFIS::EmployeePurviewInfoList msg;
		if (msg.ParseFromArray(pData, nDataSize))
		{
			int nDataCount = msg.nemployeepurviewsize();
			for (int i = 0; i < nDataCount; ++i)
			{
				auto item = msg.vecemployeepurview(i);
				ST_EmployeePurviewInfo stEmployeePurview;
				stEmployeePurview.strEmployeePurviewId = item.stremployeepurviewid();
				stEmployeePurview.strEmployeeId = item.stremployeeid();
				stEmployeePurview.strPurviewInfoId = item.strpurviewinfoid();
				stEmployeePurview.nExtendedInfo = item.nextendedinfo();
				stEmployeePurview.strExtendedInfo1 = item.strextendedinfo1();
				stEmployeePurview.strExtendedInfo2 = item.strextendedinfo2();
				stVecEmployeePurviewInfo.push_back(stEmployeePurview);
			}
			return true;
		}
		return false;
	}
public:
	int   nEmployeePurviewSize;
	std::vector<ST_EmployeePurviewInfo> vecEmployeePurview;
	int nStateSign;
	int nReserved;
};
