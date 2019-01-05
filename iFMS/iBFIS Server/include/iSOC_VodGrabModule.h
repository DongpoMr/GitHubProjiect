#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*iSOC_CreateGrabSession
*功  能：创建快速抓帧Session
*参  数：
[IN]		lGrabSession		Grab会话标识
[IN]		lMCSesion			MC会话标识
[IN]		info				VOD文件信息
[IN]		pCallback			抓帧状态回调
[IN]		dwCookie			用户数据
[IN]		dwReserved			保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：一个Session对应一个VOD文件，不能复用
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateVodGrabSession(IN OUT ISOC_LONGPTR* lGrabSession, IN ISOC_LONGPTR lMCSession, ST_VodFileInfo info
    , IN iSOC_GrabStatusCallback pCallback, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*iSOC_ReleaseGrabSession
*功  能：销毁快速抓帧Session
*参  数：
[IN]		lGrabSession		Grab会话标识
[IN]		lMCSesion			MC会话标识
[IN]		pCallback			抓帧状态回调
[IN]		dwCookie			用户数据
[IN]		dwReserved			保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseVodGrabSession(IN ISOC_LONGPTR lGrabSession, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*iSOC_AddVodGrabFrame
*功  能：添加要抓取的帧及文件信息
*参  数：
[IN]		lGrabSession		Grab会话标识
[IN]		stGrabTime			抓帧时间
[IN]		pstrGrabFilePath	文件保存路径(包含文件名)
[IN]		dwReserved			保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddVodGrabFrame(IN ISOC_LONGPTR lGrabSession, IN ISOC_SYSTEMTIME stGrabTime, IN ISOC_STR pstrGrabFilePath, IN ISOC_DWORDPTR dwReserved = 0);


/******************************************************************************************************************************
*iSOC_AddVodGrabFrameRect
*功  能：添加指定时间的一帧图像的指定区域保存到指定文件中
*参  数：
[IN]		lGrabSession		Grab会话标识
[IN]		stGrabTime			抓帧时间
[IN]		pstrGrabFilePath	文件保存路径(包含文件名)
[IN]		grabRect			指定抓帧的区域
[IN]		dwReserved			保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddVodGrabFrameRect(IN ISOC_LONGPTR lGrabSession, IN ISOC_SYSTEMTIME stGrabTime, IN ISOC_STR pstrGrabFilePath, IN ISOC_RECT grabRect, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*iSOC_RemoveVodGrabFrame
*功  能：移除要抓取的帧
*参  数：
[IN]		lGrabSession		Grab会话标识
[IN]		stGrabTime			抓帧时间
[IN]		dwReserved			保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveVodGrabFrame(IN ISOC_LONGPTR lGrabSession, IN ISOC_SYSTEMTIME stGrabTime, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*iSOC_StartGrab
*功  能：开始抓帧
*参  数：
[IN]		lGrabSession		Grab会话标识
[IN]		dwReserved			保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartGrab(IN ISOC_LONGPTR lGrabSession, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*iSOC_StopGrab
*功  能：停止抓帧
*参  数：
[IN]		lGrabSession		Grab会话标识
[IN]		dwReserved			保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopGrab(IN ISOC_LONGPTR lGrabSession, IN ISOC_DWORDPTR dwReserved = 0);

#ifdef __cplusplus
}
#endif