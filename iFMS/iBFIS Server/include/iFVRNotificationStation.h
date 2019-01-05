#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iBFIS_UniqueDefine.h"
#include "Poco/AbstractObserver.h"
#include "Poco/Notification.h"


interface IFVRNotificationStation :public CISocObject
{
    IFVRNotificationStation()
    {
        m_nObjectType = OBJECT_TYPE_BFISSERVER_NOTIFICATIONSTATION;
    }
    virtual ~IFVRNotificationStation() {};

    virtual void RegisterMsgObserver(int nMsg, const Poco::AbstractObserver& observer) = 0;
    virtual void RemoveMsgObserver(int nMsg, const Poco::AbstractObserver& observer) = 0;
    virtual void PostSyncNotification(Poco::Notification::Ptr pNotification) = 0;
};