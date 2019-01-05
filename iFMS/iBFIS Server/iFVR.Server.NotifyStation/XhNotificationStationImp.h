#pragma once
#include "iFVRNotificationStation.h"

class XhNotificationStationImp:public IFVRNotificationStation
{
public:
    XhNotificationStationImp();

    virtual ~XhNotificationStationImp();

    void RegisterMsgObserver(int nMsg, const Poco::AbstractObserver& observer);
    void RemoveMsgObserver(int nMsg, const Poco::AbstractObserver& observer);
    void PostSyncNotification(Poco::Notification::Ptr pNotification);
};

