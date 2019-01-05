#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iSOC_Datatype_Define.h"

/****************************************************************************
 接口：IThread
 作用：创建简单的线程
 作者：廖俊杰
 用法：
	  继承IRunable接口，重载Run函数，再申请一个IThread接口实例化对象指针，
	  设置IRunable接口后调用Start()启动线程。
****************************************************************************/

interface IRunable
{
	//必须重载的函数，在这里面执行线程代码
	virtual ISOC_VOID Run() = 0;
	virtual ~IRunable(){};
};

interface IThread : public CISocObject //线程接口，该接口已经在线程模块中实现，可以直接使用，使用方法参见iSIS Source
{
	IThread()
	{
		m_nObjectType = OBJECT_TYPE_THREAD;
	}
	virtual ~IThread(){};
	//启动线程
	virtual ISOC_VOID Start() = 0;
	//停止线程，慎用，因为这种方法是强制停止线程，一些类对象资源将不能被回收
	virtual ISOC_VOID Stop() = 0;
	//挂起线程
	virtual ISOC_VOID Suspend() = 0;
	//设置IRunable接口
	virtual ISOC_VOID SetRunAbleInterface(IN IRunable* pRunable) = 0;

	enum State{START,SUSPEND,STOP,INVAL};
	// 获得线程当前状态
	virtual IThread::State GetThreadState() = 0;
	//得到当前线程的优先级
	virtual ISOC_INT GetPriority() const = 0;
	//设置当前线程的优先级
	virtual ISOC_BOOL SetPriority(IN ISOC_INT nPriority = THREAD_PRIORITY_NORMAL) = 0;
	//判断当前线程是否为活动线程
	virtual ISOC_BOOL IsAlive() = 0;
	// 当停止线程后可以重新启动线程
	virtual ISOC_VOID Restart() = 0;
	virtual IRunable* GetRunAbleInterface() = 0;
	virtual ISOC_DWORD GetThreadID() = 0;
};

