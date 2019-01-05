#pragma once
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////GPS模块接口的定义/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************************************************************
*函数名：iSOC_CreateGPSSession
*功  能：创建GPS会话
*参  数：
		 [IN OUT]	pLGPSSession	GPS会话标识
		 [IN]		pStateCallback	状态回调函数
		 [IN]		dwUserCookie	用户自定义数据
		 [IN]		dwReserved		保留参数设为0
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateGPSSession(IN OUT ISOC_LONGPTR* pLGPSSession, \
	IN const iSOC_OperatorStateCallback pStateCallback = ISOC_NULL,\
	IN const ISOC_DWORDPTR dwUserCookie = 0,\
	IN ISOC_DWORDPTR dwReserved = 0	);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseGPSSession
*功  能：创建GPS会话
*参  数：
		 [IN ]	pLGPSSession	GPS会话标识
		 [IN]	dwReserved		保留参数设为0
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseGPSSession(IN ISOC_LONGPTR lGPSSession, IN ISOC_DWORDPTR dwReserved = 0	);

/******************************************************************************************************************************
*函数名：iSOC_SetGPSDataStreamCallBack
*功  能：设置GPS数据流回调
*参  数：
		 [IN]		pLGPSSession	GPS会话标识
		 [IN]		pDataCallBack	GPS数据流回调函数
		 [IN]		dwUserCookie	用户自定义数据
		 [IN]		dwReserved		保留参数设为0
*返回值：无
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_VOID iSOC_SetGPSDataStreamCallBack(IN ISOC_LONGPTR lGPSSession, \
	IN const iSOC_OnGotGPSDataCallback pDataCallBack, \
	IN const ISOC_DWORDPTR dwUserCookie = 0, \
	IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_StartGPSStream
*功  能：启动GPS数据流
*参  数：
		 [IN]		pLGPSSession	GPS会话标识
		 [IN]		lMCSession		MC会话标识
		 [IN]		stDevItem		子设备信息
		 [IN]		dwReserved		保留参数设为0
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartGPSStream(IN ISOC_LONGPTR lGPSSession, \
	IN const ISOC_LONGPTR lMCSession,\
	IN const ST_DeviceItem stDevItem, \
	IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_StopGPSStream
*功  能：停止GPS数据流
*参  数：
		 [IN]		pLGPSSession	GPS会话标识
		 [IN]		pDevItem		子设备信息，为空时停止当前所有的GPS数据流，否则停止指定的某个GPS数据流
		 [IN]		dwReserved		保留参数设为0
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopGPSStream(IN ISOC_LONGPTR lGPSSession, \
	IN const ST_DeviceItem* pDevItem = NULL, \
	IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_GPSExtendFunction
*功  能：停止GPS数据流
*参  数：
		 [IN]		pLGPSSession	GPS会话标识
		 [IN] nExType 扩展类型标识
		 [IN] dwExtendData 扩展数据
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GPSExtendFunction(IN ISOC_LONGPTR lGPSSession, \
	IN ISOC_DWORD dwExtendType,\
	IN ISOC_VOID* pExtendData);

#ifdef __cplusplus
}
#endif