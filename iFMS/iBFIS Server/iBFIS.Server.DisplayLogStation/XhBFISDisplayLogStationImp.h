#pragma once
#include "IBFISDisplayLogStation.h"

class XhBFSDisplayLogStationImp :
	public IBFISDisplayLogStation
{
public:
	XhBFSDisplayLogStationImp(void);
	~XhBFSDisplayLogStationImp(void);

	//显示日志信息
	virtual ISOC_INT DisplayLog(IN const ST_BFISLogInfo& info,IN ISOC_DWORDPTR dwReserved = NULL);
    //显示任务计划
    virtual int DisplayTaskPlanInfo(IN const ST_TaskPlan& info, IN DWORD_PTR dwReserved = NULL);
    //显示连接信息
    virtual int DisplayConnectionInfo(IN const ST_BFISConnectionInfo& info, IN DWORD_PTR dwReserved = NULL);
    //设置显示日志信息的处理接口，外面使用的时候不需要设置，只需要在应用程序启动的时候设置一次就是了，其它地方要显示日志只需要使用显示的接口
	virtual ISOC_INT SetDisplayLogCallbackSkin(IN IBFISDisplayLogCallbackSkin* pSkin);
	//扩展函数
	virtual ISOC_INT ExtendFunc(IN ISOC_INT nExType,IN ISOC_DWORDPTR dwExtendData,IN ISOC_DWORDPTR dwReserved = NULL);
private:
	IBFISDisplayLogCallbackSkin* m_pCallbackSkin;
};

