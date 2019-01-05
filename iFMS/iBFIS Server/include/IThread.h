#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iSOC_Datatype_Define.h"

/****************************************************************************
 �ӿڣ�IThread
 ���ã������򵥵��߳�
 ���ߣ��ο���
 �÷���
	  �̳�IRunable�ӿڣ�����Run������������һ��IThread�ӿ�ʵ��������ָ�룬
	  ����IRunable�ӿں����Start()�����̡߳�
****************************************************************************/

interface IRunable
{
	//�������صĺ�������������ִ���̴߳���
	virtual ISOC_VOID Run() = 0;
	virtual ~IRunable(){};
};

interface IThread : public CISocObject //�߳̽ӿڣ��ýӿ��Ѿ����߳�ģ����ʵ�֣�����ֱ��ʹ�ã�ʹ�÷����μ�iSIS Source
{
	IThread()
	{
		m_nObjectType = OBJECT_TYPE_THREAD;
	}
	virtual ~IThread(){};
	//�����߳�
	virtual ISOC_VOID Start() = 0;
	//ֹͣ�̣߳����ã���Ϊ���ַ�����ǿ��ֹͣ�̣߳�һЩ�������Դ�����ܱ�����
	virtual ISOC_VOID Stop() = 0;
	//�����߳�
	virtual ISOC_VOID Suspend() = 0;
	//����IRunable�ӿ�
	virtual ISOC_VOID SetRunAbleInterface(IN IRunable* pRunable) = 0;

	enum State{START,SUSPEND,STOP,INVAL};
	// ����̵߳�ǰ״̬
	virtual IThread::State GetThreadState() = 0;
	//�õ���ǰ�̵߳����ȼ�
	virtual ISOC_INT GetPriority() const = 0;
	//���õ�ǰ�̵߳����ȼ�
	virtual ISOC_BOOL SetPriority(IN ISOC_INT nPriority = THREAD_PRIORITY_NORMAL) = 0;
	//�жϵ�ǰ�߳��Ƿ�Ϊ��߳�
	virtual ISOC_BOOL IsAlive() = 0;
	// ��ֹͣ�̺߳�������������߳�
	virtual ISOC_VOID Restart() = 0;
	virtual IRunable* GetRunAbleInterface() = 0;
	virtual ISOC_DWORD GetThreadID() = 0;
};

