#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"
/****************************************************************************************************
*���ߣ��ο���
*���ڣ�2011-06-21
*��������ʱ���ӿڣ�ʹ�õ�ʱ��ͨ��ʹҪʹ�ö�ʱ������̳�ITimerCallbackSkin�ӿڣ�Ȼ��ͨ�����������ഴ��
       ITimer��ʵ����ͨ������SetTimer��KillTimer������������ֹͣ��ʱ����
****************************************************************************************************/

interface ITimerCallbackSkin 
{
	virtual ~ITimerCallbackSkin(){};
	virtual ISOC_VOID OnTimer(IN ISOC_ID iTimerID) = 0;
};

interface ITimer : public CISocObject //��ʱ���ӿڣ��ö�ʱ��ʵ�����봰���޹صĶ�ʱ�����Ѿ����߳�ģ����ʵ�֣�����ֱ��ʹ�ã�ʹ�÷����μ�iSIS Source
{
	ITimer()
	{
		m_nObjectType = OBJECT_TYPE_TIMER;
	}
	virtual ~ITimer(){};
	
	virtual ISOC_INT SetTimer(IN ITimerCallbackSkin* pSkin,IN ISOC_ID iTimerEventID,IN ISOC_UINT uElapse) = 0;
	virtual ISOC_VOID KillTimer(IN ISOC_ID iTimerEventID) = 0;
};