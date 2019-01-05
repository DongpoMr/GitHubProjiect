#include "StdAfx.h"
#include "XhConnectionHandleArray.h"
#include <boost\thread\lock_factories.hpp>


XhConnectionHandleArray::XhConnectionHandleArray():m_nCurrMapSize(0)
{
	m_freeHandle.clear();
	m_clinetMap.clear();
	STRY;
	for (int i = 0; i < DEFAULT_CONNECTIONS; ++i)
	{
		m_freeHandle.push_back(new ConnectionHandleInfo());
	}
	SCATCH;
}


XhConnectionHandleArray::~XhConnectionHandleArray()
{
	m_nCurrMapSize = 0;
	STRY;
	boost::recursive_mutex::scoped_lock locker(m_mtx);
	for each (auto &var in m_clinetMap)
	{
		ConnectionHandleInfo *pItem = var.second;
		STRY;
		iBFIS_SimpleCS simpleCS;
		simpleCS.EnterCS(pItem->GetCSPtr(), __FUNCTION__);
		SCATCH;
		delete pItem;
	}
	m_clinetMap.clear();
	SCATCH;

	STRY;
	auto g_lock = boost::make_unique_lock(m_freeMtx);
	for each(auto &var in m_freeHandle)
	{
		delete var;
	}
	m_freeHandle.clear();
	SCATCH;

}
int XhConnectionHandleArray::AddNewClinet(HANDLE hCon, ConnectionHandleInfo *pItem /*nullptr*/)
{
	STRY;
	if (nullptr == pItem)
		return -1;
	boost::recursive_mutex::scoped_lock locker(m_mtx);
	m_clinetMap[hCon] = pItem;
	++m_nCurrMapSize;
	return 1;
	SCATCH;
	return -1;
}

int XhConnectionHandleArray::EraseMap(HANDLE hCon)
{
	STRY;
	auto itor = m_clinetMap.find(hCon);
	if (itor != m_clinetMap.end())
	{
		m_clinetMap.erase(itor);
		--m_nCurrMapSize;
		return 1;
	}
	SCATCH;
	return -1;
}

int XhConnectionHandleArray::PushBackFree(ConnectionHandleInfo * itemFree)
{
	STRY;
	auto g_lock = boost::make_unique_lock(m_freeMtx);
	m_freeHandle.push_back(itemFree);
	SCATCH;
	return 0;
}

ConnectionHandleInfo * XhConnectionHandleArray::GetFree()
{
	STRY;
	auto g_lock = boost::make_unique_lock(m_freeMtx);
	if (!m_freeHandle.empty())
	{
		ConnectionHandleInfo *item  = m_freeHandle.front();
		m_freeHandle.pop_front();
		return item;
	}
	else
	{
		return new ConnectionHandleInfo();
	}
	SCATCH;
	return nullptr;
}

ConnectionHandleInfo * XhConnectionHandleArray::GetContentItem(HANDLE hCon)
{
	STRY;
	boost::recursive_mutex::scoped_lock locker(m_mtx);
	auto itor = m_clinetMap.find(hCon);
	if (itor != m_clinetMap.end())
	{
		return itor->second;
	}
	SCATCH;
	return nullptr;
}
