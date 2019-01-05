#pragma once
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////GIS模块接口的定义/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreateGISSession
*功  能：创建GIS会话
*参  数：
		 [IN]		hParentWnd		父窗口句柄
		 [IN]		strLoginURL		GIS服务器URL
		 [IN OUT]	pLGisSession	GIS会话标识
		 [IN]		dwReserved		保留参数设为0
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateGISSession(IN const ISOC_HWND hParentWnd,IN const ISOC_STR strLoginURL,IN OUT ISOC_LONGPTR* pLGisSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseGISSession
*功  能：销毁GIS会话
*参  数：
		 [IN]	lGisSession	GIS会话标识
		 [IN]	dwReserved	保留参数设为0
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseGISSession(IN const ISOC_LONGPTR lGisSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_GetSafeGISHwnd
*功  能：得到GIS窗口的窗口句柄
*参  数：
		 [IN]		lGisSession	GIS会话标识
		 [IN OUT]	pHwnd		GIS窗口句柄
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetSafeGISHwnd(IN const ISOC_LONGPTR lGisSession,IN OUT ISOC_HWND* pHwnd);

/******************************************************************************************************************************
*函数名：iSOC_SetGISWindowRect
*功  能：设置GIS窗口位置
*参  数：
		 [IN]	lGisSession	GIS会话标识
		 [IN]	pRecGisWnd  GIS窗口区域信息结构体指针。区域信息的坐标是相对于GIS窗口的父窗口的客户区坐标的，如果GIS窗口的父窗口
							是桌面窗口，那么区域坐标人屏幕坐标系。
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetGISWindowRect(IN const ISOC_LONGPTR lGisSession,IN const ISOC_RECT* pRecGisWnd);

/******************************************************************************************************************************
*函数名：iSOC_SearchRoadInGIS
*功  能：道路查询
*参  数：
		 [IN]		lGisSession		GIS会话标识
		 [IN]		strRoadName		要查询的道路名
		 [IN OUT]	pQueryResult	查询出的结果，以逗号分隔
		 [IN]		dwReserved		保留参数设为0
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SearchRoadInGIS(IN const ISOC_LONGPTR lGisSession,IN const ISOC_STR strRoadName,OUT ISOC_STR* pQueryResult, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_LocateRoadInGIS
*功  能：在地图上找出对应道路
*参  数：
		 [IN]	lGisSession		GIS会话标识
		 [IN]	strRoadName		道路名
		 [IN]	dwReserved		保留参数
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LocateRoadInGIS(IN const ISOC_LONGPTR lGisSession,IN const ISOC_STR strRoadName,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_LocateCameraInGIS
*功  能：在地图上找出对应摄像机并标识
*参  数：
		 [IN]	lGisSession		GIS会话标识
		 [IN]	strCameraIDs	摄像机ID，多个摄像机使用逗号将其ID分隔
		 [IN]	dwReserved		保留参数
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LocateCameraInGIS(IN const ISOC_LONGPTR lGisSession,IN const ISOC_STR strCameraIDs,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_LocatePoliceStationInGIS
*功  能：在地图上找出对应的派出所并标识
*参  数：
		 [IN]	lGisSession		GIS会话标识
		 [IN]	strPcsName		派出所名称
		 [IN]	dwReserved		保留参数
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LocatePoliceStationInGIS(IN const ISOC_LONGPTR lGisSession,IN const ISOC_STR strPcsName,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_GisExtendFunc
*功  能：GIS模块扩展函数
*参  数：
		 [IN]	lGisSession		GIS会话标识
		 [IN]	nExteydType		扩展类型
		 [IN]	dwExtendData	扩展数据
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GISExtendFunc(IN const ISOC_LONGPTR lGisSession,IN const ISOC_INT nExteydType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*函数名：iSOC_RegisterSelectedDevicePlayVideoMsgInGIS
*功  能：设置在GIS上选择的设备需要显示视频时向外面发送的信息参数
*参  数：
		 [IN]	lGisSession		GIS会话标识
		 [IN]	hRecvMsgWnd		接收消息的窗口
		 [IN]	lMsg			消息值
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterSelectedDevicePlayVideoMsgInGIS(IN ISOC_LONGPTR lGisSession,IN ISOC_HWND hRecvMsgWnd,IN ISOC_LONG lMsg);

#ifdef __cplusplus
}
#endif