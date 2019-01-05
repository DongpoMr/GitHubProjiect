#pragma once
#include "IBFISDisplayLogStation.h"

class XhBFSDisplayLogStationImp :
	public IBFISDisplayLogStation
{
public:
	XhBFSDisplayLogStationImp(void);
	~XhBFSDisplayLogStationImp(void);

	//��ʾ��־��Ϣ
	virtual ISOC_INT DisplayLog(IN const ST_BFISLogInfo& info,IN ISOC_DWORDPTR dwReserved = NULL);
    //��ʾ����ƻ�
    virtual int DisplayTaskPlanInfo(IN const ST_TaskPlan& info, IN DWORD_PTR dwReserved = NULL);
    //��ʾ������Ϣ
    virtual int DisplayConnectionInfo(IN const ST_BFISConnectionInfo& info, IN DWORD_PTR dwReserved = NULL);
    //������ʾ��־��Ϣ�Ĵ���ӿڣ�����ʹ�õ�ʱ����Ҫ���ã�ֻ��Ҫ��Ӧ�ó���������ʱ������һ�ξ����ˣ������ط�Ҫ��ʾ��־ֻ��Ҫʹ����ʾ�Ľӿ�
	virtual ISOC_INT SetDisplayLogCallbackSkin(IN IBFISDisplayLogCallbackSkin* pSkin);
	//��չ����
	virtual ISOC_INT ExtendFunc(IN ISOC_INT nExType,IN ISOC_DWORDPTR dwExtendData,IN ISOC_DWORDPTR dwReserved = NULL);
private:
	IBFISDisplayLogCallbackSkin* m_pCallbackSkin;
};

