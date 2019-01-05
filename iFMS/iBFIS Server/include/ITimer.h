#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"
/****************************************************************************************************
*作者：廖俊杰
*日期：2011-06-21
*描述：定时器接口，使用的时候通过使要使用定时器的类继承ITimerCallbackSkin接口，然后通过工厂管理类创建
       ITimer的实例，通过调用SetTimer和KillTimer方法来开启和停止计时器。
****************************************************************************************************/

interface ITimerCallbackSkin 
{
	virtual ~ITimerCallbackSkin(){};
	virtual ISOC_VOID OnTimer(IN ISOC_ID iTimerID) = 0;
};

interface ITimer : public CISocObject //定时器接口，该定时器实现了与窗口无关的定时器，已经在线程模块中实现，可以直接使用，使用方法参见iSIS Source
{
	ITimer()
	{
		m_nObjectType = OBJECT_TYPE_TIMER;
	}
	virtual ~ITimer(){};
	
	virtual ISOC_INT SetTimer(IN ITimerCallbackSkin* pSkin,IN ISOC_ID iTimerEventID,IN ISOC_UINT uElapse) = 0;
	virtual ISOC_VOID KillTimer(IN ISOC_ID iTimerEventID) = 0;
};