#pragma once
#include "iSOC_UnitDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************************************************************
*函数名：iSOC_GetAlarmSession
*功  能：获取报警会话
*参  数：
		 [IN] lMCSession	MC会话
		 [IN OUT] pAlarmSession	报警会话
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lMCSession传入获取失败描述
*备  注：在使用报警相关功能时这是第一步，必须要获取一个报警会话之后才能进行其它报警操作
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_GetAlarmSession(IN const ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pAlarmSession);

/******************************************************************************************************************************
*函数名：iSOC_SendManualAlarm
*功  能：发送手动报警
*参  数：
		 [IN] lAlarmSession	报警会话
		 [IN] devInfo	设备信息结构体
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可通过iSOC_GetLastErrorDes函数将lAlarmSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_SendManualAlarm(IN ISOC_LONGPTR lAlarmSession, IN ST_DeviceItem devInfo);

/******************************************************************************************************************************
*函数名：iSOC_SendCmd2AlarmServer
*功  能：向报警服务器发送相关指令
*参  数：
		 [IN] lAlarmSession	报警会话
		 [IN] dwXMLType	指令类型
		 [IN] pXmlContext 指令内容
		 [IN] nXmlLen 指令内容长度
		 [IN] dwReserved 保留参数，默认为0
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可通过iSOC_GetLastErrorDes函数将lAlarmSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_SendCmd2AlarmServer(IN const ISOC_LONGPTR lAlarmSession,IN const ISOC_DWORD dwXMLType,IN const ISOC_STR pXmlContext,IN const ISOC_INT nXmlLen,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetOnGotAlarmEventCallback
*功  能：设置报警服务器返回信息回调
*参  数：
		 [IN] lAlarmSession	报警会话
		 [IN] pCallback 函数指针
		 [IN] dwCookie 用户Cookie
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可通过iSOC_GetLastErrorDes函数将lAlarmSession传入获取失败描述
*备  注：在获取到报警会话后就紧接着使用此函数，这样在各个指令发送给报警服务器后才可以及时收到返回结果
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_SetOnGotAlarmEventCallback(IN const ISOC_LONGPTR lAlarmSession,IN iSOC_WhenOnGotAlarmEventCallback pCallback,IN ISOC_DWORDPTR dwCookie = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetDeviceDefence
*功  能：设置设备布防或撤防
*参  数：
		 [IN] lAlarmSession	报警会话
		 [IN] devInfo 设备信息结构体
		 [IN] bIsDefence 布防或撤防标识，ISOC_TRUE为布防,ISOC_FALSE为撤防
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可通过iSOC_GetLastErrorDes函数将lAlarmSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_SetDeviceDefence(IN const ISOC_LONGPTR lAlarmSession,IN ST_DeviceItem devInfo,IN ISOC_BOOL bIsDefence = ISOC_TRUE);

/******************************************************************************************************************************
*函数名：iSOC_AlarmExtendFunc
*功  能：报警相关扩展函数
*参  数：
		 [IN] lAlarmSession	报警会话
		 [IN] nExtendType	扩展类型
		 [IN] dwExtendData	扩展数据
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可通过iSOC_GetLastErrorDes函数将lAlarmSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_AlarmExtendFunc(IN const ISOC_LONGPTR lAlarmSession,IN const ISOC_INT nExtendType,IN ISOC_DWORDPTR dwExtendData);


/******************************************************************************************************************************
*函数名：iSOC_GetUnconfirmedAlarmInfo
*功  能：获取未处理报警信息
*参  数：
		 [IN] lAlarmSession	                报警会话
		 [IN] pOnGotUnconfirmedAlarmInfo    回调函数
		 [IN] dwCookie                      用户数据
		 [IN] pStartTime                    开始时间
		 [IN] pEndTime                      结束时间
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lMCSession传入获取失败描述
*备  注：pStartTime为空不限制开始时间，pEndTime为空不限制结束时间
******************************************************************************************************************************/
iSOC_EXPORT_MODE	ISOC_INT iSOC_GetUnconfirmedAlarmInfo(IN const ISOC_LONGPTR lAlarmSession,iSOC_OnGotUnconfirmedAlarmInfoCallback pOnGotUnconfirmedAlarmInfoCallback,ISOC_DWORDPTR dwCookie,IN ISOC_SYSTEMTIME *pStartTime,IN ISOC_SYSTEMTIME *pEndTime);

#ifdef __cplusplus
}
#endif