#pragma once
#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif
/***********************************************************************************************************************
*iSOC_CreateTalkbackSession
*功  能：创建对讲资源会话
*参  数：
	[IN]		lMCSession					所属MC回话标示
	[OUT]		plTBSession					对讲会话标示
	[IN]		pOperatorCallback			结果回调函数指针
	[IN]		dwUserCookie				用户Cookie
	[IN]		dwReserved					保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateTalkbackSession(IN const ISOC_LONGPTR lMCSession, OUT ISOC_LONGPTR* plTBSession, IN const ISOC_STR strDevType, IN iSOC_TalkbackCallback pOperatorCallback = NULL,IN ISOC_DWORDPTR dwUserCookie = 0,IN ISOC_DWORDPTR dwReserved = 0);

/***********************************************************************************************************************
*iSOC_ReleaseMatrixControlSession
*功  能：释放对讲资源会话
*参  数：
	[IN]		lTBSession					对讲会话标示
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseTalkbackSession(IN const ISOC_LONGPTR lTBSession);

/***********************************************************************************************************************
*iSOC_GetTalkbackResourcesInfoCount
*功  能：获取对讲资源数量
*参  数：
	[IN]		lTBSession					对讲会话标示
	[IN]		dwReserved					保留参数
*返回值：调用成功返回对讲资源数量，失败返回小于0的值
*备  注：无
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetTalkbackResourcesInfoCount(IN const ISOC_LONGPTR lTBSession, IN ISOC_DWORDPTR dwReserved = 0);

/***********************************************************************************************************************
*iSOC_GetTalkbackResourceByIndex
*功  能：根据index获取对讲设备信息
*参  数：
	[IN]		lTBSession					对讲会话标示
	[IN]		nIndex						对讲资源index
	[OUT]  	 	pInfo						对讲设备的信息
	[IN]		dwReserved					保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：index对应于iSOC_GetTalkbackResourcesInfoCout的返回值，范围从0到count-1
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetTalkbackResourceByIndex(IN ISOC_LONGPTR lTBSession, IN ISOC_INT nIndex, OUT ST_DevicePluginItem* pInfo, IN ISOC_DWORDPTR dwReserved = 0);

/***********************************************************************************************************************
*iSOC_LoginTalkbackResource
*功  能：登陆对讲设备
*参  数：
	[IN]		lTBSession					对讲会话标示
	[OUT]  	 	stTBInfo						对讲设备的信息
	[IN]		dwReserved					保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：index对应于iSOC_GetTalkbackResourcesInfoCout的返回值，范围从0到count-1
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LoginTalkbackResource(IN ISOC_LONGPTR lTBSession, IN ST_DevicePluginItem stTBInfo, IN ISOC_DWORDPTR dwReserved = 0);

/***********************************************************************************************************************
*iSOC_LoginTalkbackResource
*功  能：注销对讲设备
*参  数：
	[IN]		lTBSession					对讲会话标示
	[IN]		dwReserved					保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：index对应于iSOC_GetTalkbackResourcesInfoCout的返回值，范围从0到count-1
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LogoutTalkbackResource(IN ISOC_LONGPTR lTBSession, IN ISOC_DWORDPTR dwReserved = 0);

/***********************************************************************************************************************
*iSOC_SetTalkbackVolume
*功  能：设置音量大小
*参  数：
	[IN]		plTBSession					对讲会话标示
	[IN]		nVolume						音量大小，从0到100
	[IN]		dwReserved					保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetTalkbackVolume(IN ISOC_LONGPTR lTBSession, IN const ISOC_INT nVolume, IN ISOC_DWORDPTR dwReserved = 0);

/***********************************************************************************************************************
*iSOC_GetTalkbackVolume
*功  能：获取音量大小
*参  数：
	[IN]		plTBSession					对讲会话标示
	[IN]		dwReserved					保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetTalkbackVolume(IN ISOC_LONGPTR lTBSession, IN ISOC_DWORDPTR dwReserved = 0);


/***********************************************************************************************************************
*iSOC_SetTalkbackCall
*功  能：启动语音对讲
*参  数：
	[IN]		plTBSession					对讲会话标示
	[IN]		stToTBDevice				被叫设备信息
	[IN]		dwReserved					保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetTalkbackCall(IN ISOC_LONGPTR lTBSession, IN ST_DevicePluginItem stToTBDevice, IN ISOC_DWORDPTR dwReserved = 0);

/***********************************************************************************************************************
*iSOC_SetTalkbackHang
*功  能：停止语音对讲
*参  数：
	[IN]		plTBSession					对讲会话标示
	[IN]		dwReserved					保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetTalkbackHang(IN ISOC_LONGPTR lTBSession, IN ST_DevicePluginItem* pstToTBDevice = 0,IN ISOC_DWORDPTR dwReserved = 0);

/***********************************************************************************************************************
*iSOC_SetTalkbackAnswer
*功  能：接听对讲
*参  数：
	[IN]		plTBSession					对讲会话标示
	[IN]		stFromTBDevice				接听设备信息
	[IN]		dwReserved					保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetTalkbackAnswer(IN ISOC_LONGPTR lTBSession, IN ST_DevicePluginItem stFromTBDevice, IN ISOC_DWORDPTR dwReserved = 0);

/***********************************************************************************************************************
*iSOC_SetBroadcastCall
*功  能：启动语音广播
*参  数：
[IN]		plTBSession					对讲会话标示
[IN]		pszToTBDevice				被叫设备信息数组
[IN]        nDeviceCount                设备数组长度
[IN]		dwReserved					保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
***********************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetBroadcastCall(IN ISOC_LONGPTR lTBSession, IN ST_DevicePluginItem* pszToTBDevice, IN UINT nDeviceCount, IN ISOC_DWORDPTR dwReserved = 0);
#ifdef __cplusplus
}
#endif