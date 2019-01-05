#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////VOD模块接口的定义/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_GetVodFileList
*功  能：获取VOD文件
*参  数：
		 [IN]		lMCSession		MC会话标识
		 [IN]		strDeviceList	查询的设备ID列表，如下：1,2,3,4,5... ...
		 [IN]		stQueryFilter	查询条件
		 [IN]		pCallBack		查询结果回调函数指针
		 [IN]		dwUserCookie	用户COOKIE
		 [IN]		strQueryGuid	用户查询GUID，每次查询用户可以指定不同的查询GUID
		 [IN]		dwReserved		保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodFileList( IN const ISOC_LONGPTR lMCSession,IN const ISOC_STR strDeviceList,IN ST_VodQueryFilter stQueryFilter,IN iSOC_VodFileInfoCallback pCallBack,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_STR strQueryGuid = NULL,IN ISOC_DWORDPTR dwReserved = 0 );

/******************************************************************************************************************************
*函数名：iSOC_GetVodFileTagInfoList
*功  能：根据VOD文件信息查询对应文件的标签信息
*参  数：
		 [IN]		lMCSession		MC会话标识
		 [IN]		vodFileInfo 	VOD文件信息
		 [IN]		pCallBack		查询结果回调函数指针
		 [IN]		dwUserCookie	用户COOKIE
		 [IN]		dwReserved		保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodFileTagInfoList(IN const ISOC_LONGPTR lMCSession,IN const ST_VodFileInfo vodFileInfo,IN const iSOC_VodFileTagInfoCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwResreved = 0);

/******************************************************************************************************************************
*函数名：iSOC_CreateVodSession
*功  能：创建VOD会话
*参  数：
		 [IN OUT]	pVodSession		VOD会话标识
		 [IN]		pCallback		状态回调函数指针
		 [IN]		dwUserCookie	用户Cookie
		 [IN]		dwReserved		保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：在不使用些VOD会话后要使用iSOC_ReleaseVodSession将其会话销毁，否则会有内存泄漏
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateVodSession(IN OUT ISOC_LONGPTR* pVodSession,IN iSOC_OperatorStateCallback pCallback = NULL,IN ISOC_DWORDPTR dwUserCookie = 0,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseVodSession
*功  能：销毁VOD会话
*参  数：
		 [IN]		lVodSession		VOD会话标识
		 [IN]		dwReserved		保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseVodSession(IN const ISOC_LONGPTR lVodSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_StartVodStream
*功  能：启动VOD流
*参  数：
		 [IN]		lVodSession		VOD会话标识
		 [IN]		lMCSession		MC会话标识
		 [IN]		info			VOD文件信息指针
		 [IN]		hRenderWnd		渲染窗口句柄
		 [IN]		bIsLocalFile	是否为本地文件
		 [IN]		dwReserved		保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartVodStream(IN const ISOC_LONGPTR lVodSession,IN const ISOC_LONGPTR lMCSession,IN const ST_VodFileInfo info,IN ISOC_HWND hRenderWnd,IN ISOC_BOOL bIsLocalFile,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_StopVodStream
*功  能：停止VOD流
*参  数：
		 [IN]	pVodSession		VOD会话标识
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：停止VOD视频后相关内存及资源不会被释放需要调用iSOC_ReleaseVodSession释放相关资源
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopVodStream(IN const ISOC_LONGPTR lVodSession);

/******************************************************************************************************************************
*函数名：iSOC_SetVodStreamDataCallback
*功  能：设置VOD流解码前数据回调
*参  数：
		 [IN]	pVodSession		VOD会话标识
		 [IN]	pCallback		数据回调函数指针
		 [IN]	dwUserCookie	用户COOKIE
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodStreamDataCallback(IN const ISOC_LONGPTR lVodSession,IN const iSOC_StreamDataCallback pCallback,IN const ISOC_DWORDPTR dwUserCookie);

/******************************************************************************************************************************
*函数名：iSOC_SetVodMediaDataCallback
*功  能：设置VOD流解码后数据回调
*参  数：
		 [IN]	pVodSession		VOD会话标识
		 [IN]	enMediaDataType	媒体数据类型	
		 [IN]	pCallback		数据回调函数指针
		 [IN]	dwUserCookie	用户COOKIE
		 *返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodMediaDataCallback(IN const ISOC_LONGPTR lVodSession,IN const MediaDataType enMediaDataType,IN const iSOC_MediaDataCallback pCallback,IN const ISOC_DWORDPTR dwUserCookie);

/******************************************************************************************************************************
*函数名：iSOC_SetVodMediaDataCallbackEx
*功  能：设置VOD流解码后数据回调
*参  数：
[IN]	pVodSession		VOD会话标识
[IN]	enMediaDataType	媒体数据类型
[IN]	pCallback		数据回调函数指针
[IN]	dwUserCookie	用户COOKIE
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：与iSOC_SetVodMediaDataCallback相比增加了回调时间戳
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodMediaDataCallbackEx(IN const ISOC_LONGPTR lVodSession, IN const MediaDataType enMediaDataType, IN const iSOC_MediaDataCallbackEx pCallback, IN const ISOC_DWORDPTR dwUserCookie);

/******************************************************************************************************************************
*函数名：iSOC_SetVodRenderRect
*功  能：设置VOD渲染视频的区域和渲染窗口的区域
*参  数：
		 [IN]	pVodSession		VOD会话标识
		 [IN]	pRecVideo		渲染的视频区域，如果不设置，则渲染整幅图像
		 [IN]	pRecWnd			渲染的窗口区域，如果不设置，则渲染整个窗口
		 [IN]	dwReserved		保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodRenderRect(IN const ISOC_LONGPTR lVodSession,IN ISOC_RECT* pRecVideo,IN ISOC_RECT*pRecWnd = NULL,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_GrabVodFrame2Local
*功  能：VOD抓帧
*参  数：
		 [IN]	pVodSession		VOD会话标识
		 [IN]	pPicturePath	保存的抓帧图片的路径
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GrabVodFrame2Local(IN const ISOC_LONGPTR lVodSession,IN const ISOC_STR pPicturePath);

/******************************************************************************************************************************
*函数名：iSOC_GetVodVideoInfo
*功  能：获取VOD视频信息
*参  数：
		 [IN]		pVodSession		VOD会话标识
		 [IN OUT]	pVideoInfo		视频信息指针	
		 [IN]		dwReserved		保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodVideoInfo(IN const ISOC_LONGPTR lVodSession,IN OUT ST_VideoInfo*pVideoInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetVodPlayMode
*功  能：VOD视频播放控制
*参  数：
		 [IN]	pVodSession		VOD会话标识
		 [IN]	nPlayMode		控制类型
			参见：PLAY=1,PAUSE,FAST_FORWARD,FAST_BACKWARD,SLOW_FORWARD,SLOW_BACKWARD,FRAME_FORWARD,FRAME_BACKWARD
		 [IN]	fFastSpeed		播放速度，正常播放速度为1.0f,取值范围(1.0f ~ 6.0f ),对于快进值越大越快，对于慢进值越大越慢
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodPlayMode(IN const ISOC_LONGPTR lVodSession,IN ISOC_INT nPlayMode,IN ISOC_FLOAT fFastSpeed=1.0f);

/******************************************************************************************************************************
*函数名：iSOC_SeekVodFile
*功  能：VOD播放定位
*参  数：
		 [IN]		pVodSession		VOD会话标识
		 [IN]		stSeek2			定位的绝对时间值
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SeekVodFile(IN const ISOC_LONGPTR lVodSession,IN ISOC_SYSTEMTIME stSeek2);

/******************************************************************************************************************************
*函数名：iSOC_GetVodFilePlayedRange
*功  能：获取VOD文件播放时间
*参  数：
		 [IN]		pVodSession		VOD会话标识
		 [IN OUT]	pStart			播放开始绝对时间
		 [IN OUT]	pNow			取得播放的绝对时间
		 [IN OUT]	pTotalTs		文件总的时间长度
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodFilePlayedRange(IN const ISOC_LONGPTR lVodSession,IN OUT ISOC_SYSTEMTIME* pStart,IN OUT ISOC_SYSTEMTIME* pNow,IN OUT ISOC_SYSTEMTIME* pTotalTs);

/******************************************************************************************************************************
*函数名：iSOC_SetVodVideoFlip
*功  能：设置图像是否翻转
*参  数：
		 [IN]		pVodSession		VOD会话标识
		 [IN]		bIsFlip			是否翻转
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVideoFlip(IN const ISOC_LONGPTR lVodSession,IN ISOC_BOOL bIsFlip);

/******************************************************************************************************************************
*函数名：iSOC_SetVodVideoRenderState
*功  能：设置图像是否渲染
*参  数：
		 [IN]		pVodSession		VOD会话标识
		 [IN]		nRenderState	渲染状态，为1时表示渲染，为0时表示不渲染
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVideoRenderState(IN const ISOC_LONGPTR lVodSession,IN ISOC_INT nRenderState);

/******************************************************************************************************************************
*函数名：iSOC_SetVodVideoDecodeState
*功  能：设置图像是否解码
*参  数：
		 [IN]		pVodSession		VOD会话标识
		 [IN]		nDecodeState	解码状态，为1时表示解码，为0 时表示不解码
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVideoDecodeState(IN const ISOC_LONGPTR lVodSession,IN ISOC_INT nDecodeState);

/******************************************************************************************************************************
*函数名：iSOC_SetVodVideoKeepAspectRatio
*功  能：保持图像宽高比
*参  数：
		 [IN]		pVodSession		VOD会话标识
		 [IN]		bIsKeepScale	是否保持宽高比
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVideoKeepAspectRatio(IN const ISOC_LONGPTR lVodSession,IN ISOC_BOOL bIsKeep);

/******************************************************************************************************************************
*函数名：iSOC_SetVodVolume
*功  能：设置VOD音量
*参  数：
		 [IN]		pVodSession		VOD会话标识
		 [IN]		nVolume			设置音量值
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVolume(IN const ISOC_LONGPTR lVodSession,IN const ISOC_INT nVolume);

/******************************************************************************************************************************
*函数名：iSOC_GetVodVolume
*功  能：获取VOD音量
*参  数：
		 [IN]		pVodSession		VOD会话标识
*返回值：调用成功返回音量值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodVolume(IN const ISOC_LONGPTR lVodSession);

/******************************************************************************************************************************
*函数名：iSOC_AddVodFileTag
*功  能：VOD添加标签信息
*参  数：
		 [IN]		pVodSession		VOD会话标识
		 [IN]		pStTagTime		标签时间点
		 [IN]		pStUserAddTime	用户添加标签的时间点
		 [IN]		strTagTitle		标签标题
		 [IN]		strTigText		标签内容
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddVodFileTag(IN const ISOC_LONGPTR lVodSession,IN ISOC_SYSTEMTIME* pStTagTime,IN ISOC_SYSTEMTIME* pStUserAddTime,IN const ISOC_STR strTagTitle,IN const ISOC_STR strTigText);

/******************************************************************************************************************************
*函数名：iSOC_GetVodFileTagInfo
*功  能：获取VOD标签信息
*参  数：
		 [IN]		pVodSession			VOD会话标识
		 [IN OUT]	pLDataListHead		标签信息
		 [IN]		bOverTimeRequest	超时时间
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pVodSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodFileTagInfo(IN const ISOC_LONGPTR lVodSession,IN OUT ISOC_LONGPTR* pLDataListHead,IN ISOC_BOOL bOverTimeRequest);

//设置VOD渲染模式，在创建实时会话会后立即设置，通过VOD模块的扩展函数将此类型传入并传入对应的模式，目前模式可使用GDI_RENDER_MOD、DDRAW_RENDER_MOD、D3D_RENDER_MOD这些在iSOC_UnitDefine.h里面定义，同一个VOD会话只能在拉流前始设置生效。
#define SET_VOD_RENDER_MOD				 0x000003

//获取VOD渲染模式，通过VOD模块的扩展函数将些类型传入并将用于获取VOD渲染模式的ISOC_DWORD类型的指针通过最后一个参数传入
#define GET_VOD_RENDER_MOD				 0x000004

//获取VOD视频渲染Session。只有在VOD启动成功后才能获取，否则获取的Session无效
#define GET_VOD_RENDER_SESSION			 0x000005

//设置VOD快进模式，在创建VOD会话后在快进前设置，通过VOD模块的扩展函数将此类型传入并传入对应的模式，目前模式可使用0和1，为0时为全帧模式，为1时为只播I帧模式
#define  SET_VOD_FASTFORWARD_MOD		0x000006

//获取VOD快进模式，通过VOD模块的扩展函数将些类型传入并将用于获取VOD渲染模式的ISOC_DWORD类型的指针通过最后一个参数传入
#define GET_VOD_FASTFORWARD_MOD		    0x000007

//设置是否加载VPU文件解析器
#define SET_VOD_USEVPUPARSER			0x000008

//获取当前视频使用的文件解析器名字
#define GET_VOD_FILEPARSER				0x00000a

//检查是否支持某项播放控制功能，通过Vod模块的扩展函数将此类型传入，dwExtendData为ST_VodPlayCtrlSupportInfo指针
#define CHECK_VOD_PLAY_CTRL_SUPPORT		0x00000b

//设置VOD快退模式，在创建VOD会话后在快退前设置，通过VOD模块的扩展函数将此类型传入并传入对应的模式，目前模式可使用0和1，为0时
#define SET_VOD_FASTBACKWARD_MOD		0x00000c

//获取VOD快退模式，通过VOD模块的扩展函数将些类型传入并将用于获取VOD渲染模式的ISOC_DWORD类型的指针通过最后一个参数传入
#define GET_VOD_FASTBACKWARD_MOD		0x00000d

//设置VOD获取后一个GOP,dwExtendData应传入ISOC_INT64类型的指针(PTS)
#define SET_VOD_NEXT_GOP				0x000009

//设置VOD获取前一个GOP,dwExtendData应传入ISOC_INT64类型的指针(PTS)
#define SET_VOD_PRE_GOP					0x000010

//设置ivs配置信息
#define SET_IVS_CFG						0x000011

//设置IVS轨迹链信息
#define SET_IVS_LINK_INFO				0x000012

/*
设置始终持续回调数据，如果是暂停状态和完成状态则一直回调最后一帧，数据。
dwExtendData应传入ISOC_bool类型的指针，如果为ISOC_true,则暂停后完成状态下仍然回调数据。
如果为ISOC_false，则暂停和完成状态下不会回调数据。默认情况下为不回调数据状态。
*/
#define SET_VOD_ALWAYS_CALL_DATA		0x000013

struct ST_VodPlayCtrlSupportInfo
{
	enum EN_PLAYCTRL
	{
		PLAY = 1, PAUSE, FAST_FORWARD, FAST_BACKWARD, SLOW_FORWARD, SLOW_BACKWARD, FRAME_FORWARD, FRAME_BACKWARD,SEEK
	};
	EN_PLAYCTRL nPlayCtrl; //用户设置播放控制代码
	ISOC_BOOL bIsSupport; //是否支持由SDK设置
};

/******************************************************************************************************************************
*函数名：iSOC_VodExtendFunc
*功  能：VOD扩展函数，用于实现一些扩展功能
*参  数：
		 [IN] lVodSession VOD会话标识
		 [IN] nExType 扩展类型标识
		 [IN] dwExtendData 扩展数据
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_VodExtendFunc(IN const ISOC_LONGPTR lVodSession,IN ISOC_INT nExType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*函数名：iSOC_SetVodVideoRotation
*功  能：图像旋转一定角度
*参  数：
		 [IN] lLiveSession  实时会话标识
		 [IN] nAngle        图像旋转角度，目前支持：正反90、正反180、正反270
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述，
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVideoRotation(IN const ISOC_LONGPTR lVodSession,IN ISOC_INT nAngle);

/******************************************************************************************************************************
*函数名：iSOC_GetVodRotationAngle
*功  能：获取视屏旋转角度
*参  数：
		 [IN]   lVodSession  实时会话标识
		 [OUT]  pAngle        图像旋转角度,可以是负值
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述，
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodRotationAngle(IN const ISOC_LONGPTR lVodSession,OUT ISOC_INT *pAngle);

/******************************************************************************************************************************
*函数名：iSOC_SetVodStreamDataCallbackEx
*功  能：设置点播收到的数据回调，回调出的数据是解码前的数据
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] pCallback 回调函数指针
		 [IN] dwCookie 用户Cookie，用于在回调里面将所设置的Cookie值返回，如果不用可以设置成NULL
		 [IN] nDataType 回调数据类型，1表示视频，2表示音频，4表示用户自定义数据
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodStreamDataCallbackEx(IN const ISOC_LONGPTR lVodSession,IN const iSOC_StreamDataCallback pCallback,IN const ISOC_DWORDPTR dwCookie = 0, IN ISOC_INT nDataType = 7);

#ifdef __cplusplus
}
#endif