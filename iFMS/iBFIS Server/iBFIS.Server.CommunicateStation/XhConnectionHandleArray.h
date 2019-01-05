#pragma once
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost\thread\mutex.hpp>
#include "iBFIS_UniqueDefine.h"
#include "iCMSP_SimpleLock.h"
#include "iBFIS_SimpleCS.h"
#include "IcmsP_Utility.h"
#include <unordered_map>
#include <deque>

#define MAX_CONNECTIONS 500
#define DEFAULT_CONNECTIONS 50

struct ConnectionHandleInfo : public boost::noncopyable
{
	HANDLE hConnection;
	iCMSP_SimpleCS visitConnection;

	ConnectionHandleInfo() : hConnection(nullptr)
	{
	}

	void SetConnection(HANDLE hCon)
	{
		hConnection = hCon;
	}

	HANDLE GetConnection()
	{
		return hConnection;
	}

	iCMSP_SimpleCS* GetCSPtr()
	{
		return &visitConnection;
	}
};

class XhConnectionHandleArray
{
public:
	XhConnectionHandleArray();
	~XhConnectionHandleArray();
public:
	int AddNewClinet(HANDLE hCon, ConnectionHandleInfo *pItem = nullptr);
	int EraseMap(HANDLE hCon);
	int PushBackFree(ConnectionHandleInfo *itemFree);
	ConnectionHandleInfo *GetFree();
	ConnectionHandleInfo* GetContentItem(HANDLE hCon);
	inline boost::recursive_mutex& GetArraySimpleCS()
	{
		return m_mtx;
	}
	inline int GetMapCount()
	{
		boost::recursive_mutex::scoped_lock locker(m_mtx);
		return m_nCurrMapSize;
	}
private:
	std::unordered_map<HANDLE, ConnectionHandleInfo*> m_clinetMap;
	int                                           m_nCurrMapSize;
	boost::recursive_mutex                        m_mtx;
	boost::mutex                                  m_freeMtx;
	std::deque<ConnectionHandleInfo *>            m_freeHandle;

};

