#ifndef __ISOC_PTSCONTROLMODULE_API_HEADER__
#define __ISOC_PTSCONTROLMODULE_API_HEADER__

#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef __cplusplus 
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreatePtzControlSession
*功  能：创建PTZ控制会话
*参  数：
		[IN OUT]	lPtzCtrlSession		PTZ控制会话
		[IN]		lMCSession			管理中心会话
		[IN]		stDeviceInfo		设备信息
		[IN]		pStateCallback		操作状态回调
        [IN]        dwCookie            用户数据
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreatePtzControlSession(IN OUT ISOC_LONGPTR *lPtzCtrlSession,IN ISOC_LONGPTR lMCSession,IN const ST_DeviceItem stDeviceInfo,IN iSOC_OperatorStateCallback pStateCallback = ISOC_NULL,ISOC_DWORDPTR dwCookie = 0);

/******************************************************************************************************************************
*函数名：iSOC_ControlPtzDirection
*功  能：控制指定设备PTZ的八个方向移动方向
*参  数：
		[IN]	lPtzCtrlSession		PTZ控制会话
		[IN]	nDirection			移动的方向，参见值如下：
				{PTZ_LEFT=0,PTZ_LEFT_UP,PTZ_UP,PTZ_UP_RIGHT,PTZ_RIGHT,PTZ_DOWN_RIGHT,PTZ_DOWN,PTZ_DOWN_LEFT
				,PTZ_ABSOLUTE_POS,PTZ_STOP_MOVE,PTZ_RESET, PTZ_PUSH_FAR, PTZ_PULL_NEAR}
		[IN]	nPanSpeed			水平移动速度 1-100
		[IN]	nTiltSpeed			垂直移动速度 1-100
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzDirection(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_INT nDirection,IN ISOC_INT nPanSpeed=1,IN ISOC_INT nTiltSpeed=1);

/******************************************************************************************************************************
*函数名：iSOC_ControlPtzZoom
*功  能：控制指定设备PTZ的缩放
*参  数：
		[IN]	lPtzCtrlSession		PTZ控制会话
		[IN]	bZoomIn				为ISOC_TRUE为放大，为ISOC_FALSE为缩小
		[IN]	nSpeed				缩放的速度	 1-100
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：使用iSOC_ControlPtzDirection传入PTZ_STOP_MOVE停止PTZ移动
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzZoom(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_BOOL bZoomIn,IN ISOC_INT nSpeed=10);

/******************************************************************************************************************************
*函数名：iSOC_ControlPtzFocus
*功  能：控制指定设备PTZ的聚焦
*参  数：
		[IN]	lPtzCtrlSession		PTZ控制会话
		[IN]	bFocusIn			为ISOC_TRUE是为焦距近,为ISOC_FALSE为焦距远
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：使用iSOC_ControlPtzDirection传入PTZ_STOP_MOVE停止PTZ移动
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzFocus(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_BOOL bFocusIn);

/******************************************************************************************************************************
*函数名：iSOC_ControlPtzAuxiliary
*功  能：控制指定设备PTZ的云台
*参  数：
		[IN]	lPtzCtrlSession		PTZ控制会话
		[IN]	nAuxiliaryIdx		云台控制值，参见如下值：
				{CTRL_LIGHT灯光,CTRL_FOG除雾,CTRL_RAIN_BRUSH雨刷}
		[IN]	bEnable				是否开启
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzAuxiliary(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_INT nAuxiliaryIdx,IN ISOC_BOOL bEnable);

/******************************************************************************************************************************
*函数名：iSOC_ControlPtzAuxiliary
*功  能：控制指定设备PTZ的云台并支持透传
*参  数：
[IN]	lPtzCtrlSession		PTZ控制会话
[IN]	nAuxiliaryIdx		云台控制值，参见如下值：
{CTRL_LIGHT灯光,CTRL_FOG除雾,CTRL_RAIN_BRUSH雨刷}
[IN]	bEnable				是否开启
[IN]	pMsg				透传信息
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzAuxiliaryEx(IN const ISOC_LONGPTR lPtzCtrlSession, IN ISOC_INT nAuxiliaryIdx, IN ISOC_BOOL bEnable,IN ISOC_VOID* pMsg,IN ISOC_INT nMsgLen);

/******************************************************************************************************************************
*函数名：iSOC_GetCurrentPtzPos
*功  能：获取当前PTZ位置
*参  数：
		[IN]	lPtzCtrlSession		PTZ控制会话
		[IN OUT]pPtzPos				PTZ位置信息结构体
		[IN]	dwReserved			保留参数
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetCurrentPtzPos(IN const ISOC_LONGPTR lPtzCtrlSession,IN OUT ST_PtzPos* pPtzPos,IN ISOC_DWORDPTR dwReserved);

/******************************************************************************************************************************
*函数名：iSOC_SetCurrentPtzPos
*功  能：设置PTZ位置
*参  数：
		[IN]	lPtzCtrlSession		PTZ控制会话
		[IN]	pPtzPos				PTZ位置信息结构体
		[IN]	dwReserved			保留参数
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetCurrentPtzPos(IN const ISOC_LONGPTR lPtzCtrlSession,IN ST_PtzPos* pPtzPos,IN ISOC_DWORDPTR dwReserved);


/******************************************************************************************************************************
*函数名：iSOC_PtzExtendFunc
*功  能：PTZ控制扩展函数，用于实现一些扩展功能
*参  数：
		 [IN] lPtzCtrlSession PTZ控制会话
		 [IN] nExType 扩展类型标识
		 [IN] dwExtendData 扩展数据
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_PtzExtendFunc(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_INT nExType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*函数名：iSOC_ControlDevIO
*功  能：控制指定设备I/O开关
*参  数：
		[IN]	lPtzCtrlSession		PTZ控制会话
		[IN]	nIOID				IO的ID：目前该值无效，io控制只控制了输出的开关
		[IN]	bEnable				是否开启
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlDevIO(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_INT nIOID,IN ISOC_BOOL bEnable);

/******************************************************************************************************************************
*函数名：iSOC_ReleasePtzControlSession
*功  能：销毁PTZ控制会话
*参  数：
		[IN]	lPtzCtrlSession		PTZ控制会话
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleasePtzControlSession(IN const ISOC_LONGPTR lPtzCtrlSession);

/******************************************************************************************************************************
*函数名：iSOC_GetTourPresetPosSession
*功  能：获取巡航预置点管理会话
*参  数：
		[IN OUT]	lpTPSession		巡航预置点管理会话
		[IN]		lMCSession		管理中心会话
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetTourPresetPosSession(IN OUT ISOC_LONGPTR *lpTPSession,IN ISOC_LONGPTR lMCSession);


/******************************************************************************************************************************
*函数名：iSOC_GetDeviceTourCount
*功  能：获取设备巡航信息数量
*参  数：
		[IN]		lTPSession		巡航预置点管理会话
		[IN]		stDeviceInfo	设备信息，如果设备信息中strIcmsSign为空且lIcmsId=0，则获取全部设备的巡航信息数量
*返回值：成功则返回设备巡航信息数量，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceTourCount(IN ISOC_LONGPTR lTPSession,IN ST_DeviceItem stDeviceInfo);

/******************************************************************************************************************************
*函数名：iSOC_GetDeviceTourInfoByIdx
*功  能：根据索引获取设备巡航信息
*参  数：
		[IN]		lTPSession		巡航预置点管理会话
		[IN OUT]	lpTourInfo		获取的设备巡航信息指针
		[IN]		stDeviceInfo	设备信息，如果设备信息中strIcmsSign为空且lIcmsId=0，则从所有设备中获取，否则从指定设备中获取
		[IN]		nIdx			索引值，从0开始
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceTourInfoByIdx(IN ISOC_LONGPTR lTPSession,IN OUT LPST_TOURINFO lpTourInfo,IN ST_DeviceItem stDeviceInfo,IN ISOC_INT nIdx);

/******************************************************************************************************************************
*函数名：iSOC_GetDeviceTourInfoByID
*功  能：根据巡航ID来获取设备的巡航信息
*参  数：
		[IN]		lTPSession		巡航预置点管理会话
		[IN OUT]	lpTourInfo	获取的设备巡航信息指针
		[IN]		nTourNum		巡航ID
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceTourInfoByID(IN ISOC_LONGPTR lTPSession,IN OUT LPST_TOURINFO lpTourInfo,IN ISOC_ID nTourNum);

/******************************************************************************************************************************
*函数名：iSOC_ControlDeviceTour
*功  能：控制设备巡航
*参  数：
		[IN]		lTPSession		巡航预置点管理会话
		[IN]		nCtrlCode		控制码
					参见如下值：{INSERT_POINT=0,UPDATE_POINT,DELETE_POINT,GOTO_POINT,STOP_POINT}
		[IN]		stDeviceInfo	设备信息
		[IN]		stTourInfo		巡航信息
		[IN]		dwReseved		保留字
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：此函数为异步处理，如果需要获取到准确的返回结果，需要调用iSOC_RegistDeviceCruiseUpdateNotify注册异步事件回调函数
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlDeviceTour(IN ISOC_LONGPTR lTPSession,IN ISOC_INT nCtrlCode,IN ST_DeviceItem stDeviceInfo,IN LPST_TOURINFO stTourInfo,IN ISOC_DWORDPTR dwReseved=0);

/******************************************************************************************************************************
*函数名：iSOC_RegisterDeviceTourNotifyCallback
*功  能：注册异步事件回调函数
*参  数：
		[IN]		lTPSession		巡航预置点管理会话
		[IN]		pCallback		回调函数指针
		[IN]		dwCookie		用户COOKIE
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterDeviceTourNotifyCallback(IN ISOC_LONGPTR lTPSession,IN iSOC_TourInfoCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*函数名：iSOC_RemoveDeviceTourNotifyCallback
*功  能：移除异步事件回调函数
*参  数：
		[IN]		lTPSession		巡航预置点管理会话
		[IN]		pCallback		回调函数指针
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveDeviceTourNotifyCallback(IN ISOC_LONGPTR lTPSession,IN iSOC_TourInfoCallback pCallback);

/******************************************************************************************************************************
*函数名：iSOC_GetDevicePresetPosCount
*功  能：获取设备预置点信息数量
*参  数：
		[IN]		lTPSession		巡航预置点管理会话
		[IN]		stDeviceInfo	设备信息
*返回值：成功则返回预置点数量值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDevicePresetPosCount(IN ISOC_LONGPTR lTPSession,IN ST_DeviceItem stDeviceInfo);

/******************************************************************************************************************************
*函数名：iSOC_GetDevicePresetPosInfoByIdx
*功  能：根据索引获取设备预置点信息
*参  数：
		[IN]		lTPSession			巡航预置点管理会话
		[IN OUT]	lpPresetPosInfo	获取的预置点信息指针
		[IN]		stDeviceInfo		设备信息，如果设备信息中strIcmsSign为空且lIcmsId=0，则从所有设备中获取，否则从指定设备中获取
		[IN]		nIdx				索引值，从0开始
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDevicePresetPosInfoByIdx(IN ISOC_LONGPTR lTPSession,IN OUT LPST_PRESETPOSINFO lpPresetPosInfo,IN ST_DeviceItem stDeviceInfo,IN ISOC_INT nIdx);

/******************************************************************************************************************************
*函数名：iSOC_GetDevicePresetPosInfoByID
*功  能：根据预置点ID获取设备预置点信息
*参  数：
		[IN]		lTPSession			巡航预置点管理会话
		[IN]		stDeviceInfo		设备信息结构体
		[IN OUT]	lpPresetPosInfo	获取的预置点信息指针
		[IN]		nPresetPosID		预置点ID
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDevicePresetPosInfoByID(IN ISOC_LONGPTR lTPSession,IN ST_DeviceItem stDeviceInfo,IN OUT LPST_PRESETPOSINFO lpPresetPosInfo,IN ISOC_ID nPresetPosID);

/******************************************************************************************************************************
*函数名：iSOC_ControlDevicePresetPos
*功  能：控制指定设备预置点
*参  数：
		[IN]		lTPSession		巡航预置点管理会话
		[IN]		nCtrlCode		控制码
					参见如下值：{INSERT_POINT=0,UPDATE_POINT,DELETE_POINT,GOTO_POINT,STOP_POINT}
		[IN]		stDeviceInfo	设备信息
		[IN]		lpPresetPosInfo		预置点信息
		[IN]		dwReseved		保留字
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：此函数为异步处理，如果需要获取到准确的返回结果，需要调用iSOC_RegistDevicePresetPosUpdateNotify注册异步事件回调函数
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlDevicePresetPos(IN ISOC_LONGPTR lTPSession,IN ISOC_INT nCtrlCode,IN ST_DeviceItem stDeviceInfo,IN LPST_PRESETPOSINFO lpPresetPosInfo,IN ISOC_DWORDPTR dwReseved=0);

/******************************************************************************************************************************
*函数名：iSOC_ControlDeviceKeepPos
*功  能：控制指定设备守望位
*参  数：
		[IN]		lTPSession		巡航预置点管理会话
		[IN]		nCtrlCode		控制码
					参见如下值：{SET_POS=0,GOTO_POS}
		[IN]		stDeviceInfo		设备信息
		[IN]		KeepPosInfo		守望位位置信息
		[IN]		dwReseved		保留字
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：此函数为异步处理，如果需要获取到准确的返回结果，需要调用iSOC_RegistDevicePresetPosUpdateNotify注册异步事件回调函数
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlDeviceKeepPos(IN ISOC_LONGPTR lTPSession,IN ISOC_INT nCtrlCode,IN ST_DeviceItem stDeviceInfo,IN ISOC_DWORDPTR dwReseved=0);

/******************************************************************************************************************************
*函数名：iSOC_RegisterDevicePresetPosNotifyCallback
*功  能：注册预置点异步操作回调函数
*参  数：
		[IN]		lTPSession		巡航预置点管理会话
		[IN]		pCallback		异步操作回调函数
		[IN]		dwCookie		用户COOKIE
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterDevicePresetPosNotifyCallback(IN ISOC_LONGPTR lTPSession,IN iSOC_PresetPosInfoCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*函数名：iSOC_RemoveDevicePresetPosNotifyCallback
*功  能：移除预置点异步操作回调函数
*参  数：
		[IN]		lTPSession		巡航预置点管理会话
		[IN]		pCallback		异步操作回调函数
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveDevicePresetPosNotifyCallback(IN ISOC_LONGPTR lTPSession,IN iSOC_PresetPosInfoCallback pCallback);


/******************************************************************************************************************************
*函数名：iSOC_GetGroupLoopManagerSession
*功  能：获取分组轮巡管理会话
*参  数：
		[IN OUT]	lpGroupSession	获取的分组轮巡管理会话
		[IN]		lMCSession		管理中心会话
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_GetGroupLoopManagerSession(IN OUT ISOC_LONGPTR *lpGroupSession,IN ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*函数名：iSOC_RegisterGroupLoopNotifyCallback
*功  能：注册分组轮巡异步事件通知回调函数
*参  数：
		[IN]		lGroupSession	分组轮巡管理会话
		[IN]		pCallback		异步操作回调函数
		[IN]		dwCookie		用户COOKIE
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterGroupLoopNotifyCallback(IN ISOC_LONGPTR lGroupSession,IN iSOC_OperatorStateCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*函数名：iSOC_GetGroupLoopPlanInfo
*功  能：获取分组计划信息
*参  数：
		[IN]		lGroupSession		分组轮巡管理会话
		[IN OUT]	strGroupPlanInfo	分组计划信息
		*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_GetGroupLoopPlanInfo(IN ISOC_LONGPTR lGroupSession,IN OUT ISOC_STR strGroupPlanInfo);

/******************************************************************************************************************************
*函数名：iSOC_SetGroupLoopPlanInfo
*功  能：设置分组计划信息
*参  数：
		[IN]		lGroupSession		分组轮巡管理会话
		[IN]		strGroupPlanInfo	分组计划信息
		*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_SetGroupLoopPlanInfo(IN ISOC_LONGPTR lGroupSession,IN ISOC_STR strGroupPlanInfo);

/******************************************************************************************************************************
*函数名：iSOC_GetGroupLoopSurverySchemeInfo
*功  能：根据轮巡方案ID获取轮巡方案信息
*参  数：
		[IN]		lGroupSession				分组轮巡管理会话
		[IN]		nGroupSurveySchemeID		轮巡方案ID
		[IN OUT]	strGroupSurverySchemeInfo	轮巡方案信息
		*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_GetGroupLoopSurverySchemeInfo(IN ISOC_LONGPTR lGroupSession,IN ISOC_ID nGroupSurveySchemeID,IN OUT ISOC_STR strGroupSurverySchemeInfo);

/******************************************************************************************************************************
*函数名：iSOC_SetGroupLoopSurverySchemeInfo
*功  能：设置轮巡方案信息
*参  数：
		[IN]		lGroupSession				分组轮巡管理会话
		[IN]		strGroupSurverySchemeInfo	轮巡方案信息
		*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_SetGroupLoopSurverySchemeInfo(IN ISOC_LONGPTR lGroupSession,IN ISOC_STR strGroupSurverySchemeInfo);

/******************************************************************************************************************************
*函数名：iSOC_DelGroupLoopSurverySchemeInfo
*功  能：根据轮巡方案ID删除指点轮巡方案
*参  数：
		[IN]		lGroupSession			分组轮巡管理会话
		[IN]		nGroupSurveySchemeID	轮巡方案ID
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_DelGroupLoopSurverySchemeInfo(IN ISOC_LONGPTR lGroupSession,IN ISOC_ID nGroupSurveySchemeID);


/******************************************************************************************************************************
*函数名：iSOC_ControlPtzAperture
*功  能：控制指定设备PTZ的光圈
*参  数：
		[IN]	lPtzCtrlSession		PTZ控制会话
		[IN]	bApertureIn			光圈是否缩小
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzAperture(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_BOOL bApertureIn);


/******************************************************************************************************************************
*函数名：iSOC_LockPtz
*功  能：锁定PTZ,防止其他用户转动
*参  数：
		[IN]	lPtzCtrlSession		PTZ控制会话
		[IN]	nTime			    锁定的时间，以秒为单位
*返回值：失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：通过状态回调才正真知道是否成功
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LockPtz(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_INT nTime);


/******************************************************************************************************************************
*函数名：iSOC_UnlockPtz
*功  能：解锁PTZ,允许其他用户转动
*参  数：
		[IN]	lPtzCtrlSession		PTZ控制会话
*返回值：失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lPtzCtrlSession传入获取失败描述
*备  注：通过状态回调才正真知道是否成功
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UnlockPtz(IN const ISOC_LONGPTR lPtzCtrlSession);

#ifdef __cplusplus 
}
#endif
#endif