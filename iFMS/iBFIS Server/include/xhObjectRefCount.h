#pragma once

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <memory>
#include <boost\atomic\atomic.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

typedef boost::shared_lock<boost::shared_mutex> readLock;
typedef boost::unique_lock<boost::shared_mutex> writeLock;

struct RefCountInfo
{
	boost::mutex     mtx;
	int                 count;
	bool              bDel;
	static boost::atomic_bool m_exit;

	RefCountInfo() :count(0), bDel(false) {}

	static void setExitStatus(bool bStatus = true)
	{
		m_exit.store(bStatus);
	}

	int AddRefCount()
	{
		boost::unique_lock<boost::mutex> locker(mtx);
		if (bDel)
			return -1;
		++count;
		return count;
	}

	int DelRefCount()
	{
		boost::unique_lock<boost::mutex> locker(mtx);
		--count;
		return count;
	}

	bool isDel()
	{
		boost::unique_lock<boost::mutex> locker(mtx);
		return bDel;
	}
	bool DelRefObject(int milliseconds)
	{
		do
		{
			boost::unique_lock<boost::mutex> locker(mtx);
			bDel = true;
			if (count <= 0)
				return true;
			locker.unlock();

			if (m_exit.load())
				return true;

			if (milliseconds > 0)
				boost::this_thread::sleep_for(boost::chrono::milliseconds(milliseconds));
			else
				boost::this_thread::yield();
		} while (1);
		return false;
	}

	bool DelRefObjectTimeOut(int milliseconds)
	{
		int intervalTime = milliseconds;
		if (milliseconds > 10)
			intervalTime = 10;
		int waitTime = 0;

		boost::unique_lock<boost::mutex> locker(mtx);
		bDel = true;
		if (count <= 0)
			return true;
		locker.unlock();

		do
		{
			if (m_exit.load())
				return true;

			boost::this_thread::sleep_for(boost::chrono::milliseconds(intervalTime));
			waitTime += intervalTime;

			boost::unique_lock<boost::mutex> locker(mtx);
			bDel = true;
			if (count <= 0)
				return true;
		} while (waitTime <= milliseconds);
		return false;
	}
};

template<class T>
class ObjectRefCount
{
public:
	ObjectRefCount()
	{
		m_refInfo = std::make_shared<RefCountInfo>();
	}

	ObjectRefCount(T custom):m_custom(custom)
	{
		m_refInfo = std::make_shared<RefCountInfo>();
	}

	~ObjectRefCount() {}
public:
	std::shared_ptr<RefCountInfo>& GetRefInfo()
	{
		return m_refInfo;
	}

	T                                m_custom;
private:
	std::shared_ptr<RefCountInfo>   m_refInfo;
};

class AutoObjectRefMgr
{
public:
	AutoObjectRefMgr() :m_refInfo(nullptr), m_del(false){}
	~AutoObjectRefMgr()
	{
		if (m_refInfo && m_del)
			m_refInfo->DelRefCount();
	}

public:

	bool AddRefCount(std::shared_ptr<RefCountInfo>& refInfo)
	{
		int nRet = -1;

		if (m_refInfo == refInfo)
			return true;

		if (m_refInfo)
			m_refInfo->DelRefCount();

		m_refInfo = refInfo;
		if (m_refInfo)
		{
			nRet = m_refInfo->AddRefCount();
		}

		if (nRet != -1)
		{
			m_del = true;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool isDel()
	{
		return m_refInfo == nullptr ? false : m_refInfo->isDel();
	}
private:
		AutoObjectRefMgr(const AutoObjectRefMgr &);
		AutoObjectRefMgr& operator=(const AutoObjectRefMgr &);
private:
	std::shared_ptr<RefCountInfo> m_refInfo;
	bool                                            m_del;
};

class GeneralEvent
{
public:
	GeneralEvent():bSendEvent(false)
	{
		
	}
	void SendEvent()
	{
		boost::unique_lock<boost::mutex> locker(mtx);
		bSendEvent = true;
		cond.notify_one();
	}

	bool Wait(int s = 0)
	{
		boost::unique_lock<boost::mutex> locker(mtx);
		if (!bSendEvent)
		{
			if (s > 0)
			{
				boost::cv_status status = cond.wait_for(locker, boost::chrono::seconds(s));
				if (status == boost::cv_status::timeout)
					return false;
			}
			else
			{
				cond.wait(locker);
			}
		}
		bSendEvent = false;
		return true;
	}

	void Reset()
	{
		boost::unique_lock<boost::mutex> locker(mtx);
		bSendEvent = false;
	}
private:
	boost::mutex            mtx;
	boost::condition_variable cond;
	bool                         bSendEvent;
};