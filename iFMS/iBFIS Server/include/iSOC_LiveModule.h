#pragma once
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////实时模块接口的定义/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreateLiveSession
*功  能：创建实时会话
*参  数：
		[IN OUT] pLiveSession 实时会话标识
		[IN] pStateCallback 状态回调函数，用于返回打开实时流过程中和打开后的各种状态
		[IN] dwUserCookie 用户Cookie，用于在状态回调中将用户设置的Cookie值返回，如果不用可以设置成NULL
		[IN] dwReserved 扩展值，置为NULL
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：在不使用此会话后一定要使用iSOC_ReleaseLiveSession将此实时会话销毁，不然会引起内存泄漏
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateLiveSession(IN OUT ISOC_LONGPTR *pLiveSession,IN const iSOC_OperatorStateCallback pStateCallback = ISOC_NULL,IN const ISOC_DWORDPTR dwUserCookie = 0,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseLiveSession
*功  能：销毁实时会话
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] dwReserved 扩展值，置为NULL
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseLiveSession(IN ISOC_LONGPTR lLiveSession,IN ISOC_DWORDPTR dwReserved = NULL);

/******************************************************************************************************************************
*函数名：iSOC_SetPriorStreamModel
*功  能：设置拉流优先格式
*参  数：
		 [IN] pLiveSession 实时会话，打开成功后会创建一个实时会话
		 [IN] nCodecID 优先格式编码ID 见编码ID定义,0表示不设置
		 [IN] nStreamFlag 码流标志，1表示高码流，2表示低码流，0表示不设置
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetPriorStreamModel(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nCodecID = 0,IN ISOC_INT nStreamFlag  = 0);

/******************************************************************************************************************************
*函数名：iSOC_StartLiveStream
*功  能：启动实时流
*参  数：
		 [IN] pLiveSession 实时会话，打开成功后会创建一个实时会话
		 [IN] lMCSession MC会话标识
		 [IN] hRenderWnd 要渲染的窗口句柄
		 [IN] deviceInfo 设备信息结构体
		 [IN] dwReserved 扩展值，置为NULL
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后在pLiveSession有值的情况下可调用iSOC_GetLastErrorDes获取错误描述
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartLiveStream(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_LONGPTR lMCSession,IN const ISOC_HWND hRenderWnd,IN const ST_DeviceItem deviceInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveStreamDataCallback
*功  能：设置实时收到的数据回调，回调出的数据是解码前的数据
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] pCallback 回调函数指针
		 [IN] dwCookie 用户Cookie，用于在回调里面将所设置的Cookie值返回，如果不用可以设置成NULL
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveStreamDataCallback(IN const ISOC_LONGPTR lLiveSession,IN const iSOC_StreamDataCallback pCallback,IN const ISOC_DWORDPTR dwCookie = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveMediaDataCallback
*功  能：设置实时解码后数据
*参  数：[IN] lLiveSession 实时会话标识
		 [IN] enMediaDataType 媒体数据类型
		 [IN] pCallback 回调函数指针
		 [IN] dwUserCookie 用户Cookie，用于在回调函数中将用户设置的Cookie值返回，如果不用可以设置成NULL
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveMediaDataCallback(IN const ISOC_LONGPTR lLiveSession,IN const MediaDataType enMediaDataType,IN const iSOC_MediaDataCallback pCallback,IN const ISOC_DWORDPTR dwUserCookie = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveMediaDataCallback
*功  能：设置实时解码后数据
*参  数：[IN] lLiveSession 实时会话标识
[IN] enMediaDataType 媒体数据类型
[IN] pCallback 回调函数指针
[IN] dwUserCookie 用户Cookie，用于在回调函数中将用户设置的Cookie值返回，如果不用可以设置成NULL
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveMediaDataCallbackEx(IN const ISOC_LONGPTR lLiveSession, IN const MediaDataType enMediaDataType, IN const iSOC_MediaDataCallbackEx pCallback, IN const ISOC_DWORDPTR dwUserCookie = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveLocalCacheFile
*功  能：设置及时回放的缓存文件路径
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] strPath 文件路径
		 [IN] uFileSize文件大小，默认为200MB
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：设置的文件的后缀名要为.rpb；不设置时默认不启用该功能，设置为空可以取消缓存
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveLocalCacheFile(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_STR strPath,IN ISOC_UINT64 uFileSize = 209920000);

/******************************************************************************************************************************
*函数名：iSOC_FreezeLiveVideo
*功  能：实时视频冻结
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] bIsFreeze 冻结标志，为ISOC_TRUE是为冻结视频，为ISOC_FALSE时为解除冻结
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_FreezeLiveVideo(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_BOOL bIsFreeze);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveRenderRect
*功  能：设置实时渲染的区域
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] pRecVideo 要渲染图像的区域，图像左上角坐标为(0,0)
		 [IN] pRecWnd 要渲染的窗口区域，窗口左上角坐标为(0,0)
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：用此函数可实现局部放大和将图像渲染到窗口的某一区域的功能
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveRenderRect(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_RECT* pRecVideo,IN const ISOC_RECT* pRecWnd);

/******************************************************************************************************************************
*函数名：iSOC_GetLiveVideoInfo
*功  能：得到实时视频的相关信息
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN OUT] pVideoInfo 视频信息结构体
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLiveVideoInfo(IN const ISOC_LONGPTR lLiveSession,IN OUT ST_VideoInfo* pVideoInfo);

/******************************************************************************************************************************
*函数名：iSOC_GrabLiveFrame2Local
*功  能：将实时视频的某人帧抓帧成图片保存到指定文件
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] strPicPath 图片路径
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：图片格式根据图片路径后缀名来判断，支持常用的图片格式，如：jpg,bmp
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GrabLiveFrame2Local(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_STR strPicPath);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveRecord
*功  能：开启和停止实时视频的手动录像
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] bIsRecord 启动和停止手动录像标志，为ISOC_TRUE时表示启动手动录像，为ISOC_FALSE时表示停止手动录像
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveRecord(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_BOOL bIsRecord);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveVolume
*功  能：设置实时音量
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] nVolume 音量值，范围为 0 ~ 100，当为0 时不进行音频解码和渲染
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVolume(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_INT nVolume);

/******************************************************************************************************************************
*函数名：iSOC_GetLiveVolume
*功  能：获取视频音量
*参  数：
		 [IN] lLiveSession 实时会话标识
*返回值：返回当前音量值，音量值是大于等于0的值，如果小于0说明调用失败，可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLiveVolume(IN const ISOC_LONGPTR lLiveSession);

/******************************************************************************************************************************
*函数名：iSOC_AddLiveTag
*功  能：添加实时标签
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] pStUserAddTime 用户添加标签的时间
		 [IN] strTagTitle 标签标题
		 [IN] strTagText 标签内容
		 [IN] dwReserved 保留参数设为NULL
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddLiveTag(IN const ISOC_LONGPTR lLiveSession,IN ISOC_SYSTEMTIME* pStUserAddTime, IN ISOC_STR strTagTitle, IN ISOC_STR strTagText,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_StopLiveStream
*功  能：停止实时视频
*参  数：
		 [IN] lLiveSession 实时会话标识
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：停止实时视频后相关内存及资源不会被释放需要调用iSOC_ReleaseLiveSession释放相关资源
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopLiveStream(IN const ISOC_LONGPTR lLiveSession);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveVideoFlip
*功  能：图像上下翻转180度
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] bIsFlip 图像翻转标识，为ISOC_TRUE时翻转180度，为ISOC_FALSE时取消翻转
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoFlip(IN const ISOC_LONGPTR lLiveSession,IN ISOC_BOOL bIsFlip);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveVideoRenderState
*功  能：开始或者停止视频渲染
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] nRenderState 渲染状态标识，为1时表示渲染视频，为0时表示不渲染视频
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：不调用此函数设置时默认为渲染，此函数可以渲染窗口被挡住或者隐藏的时候调用，可提高程序效率
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoRenderState(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nRenderState);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveVideoDecodeState
*功  能：开始或者停止解码
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] nDecodeState 解码状态标识，为1时解码，为0 时不解码
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoDecodeState(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nDecodeState);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveVideoKeepAspectRatio
*功  能：设置实时视频保持宽高比
*参  数：
		 [IN] lLiveSession  实时会话标识
		 [IN] bIsKeep		宽高比标识，为ISOC_TRUE时保持图像宽高比，为ISOC_FALSE时不保持图像宽高比
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：默认情况下不保持图像宽高比，保持图像宽高比会影响一些性能
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoKeepAspectRatio(IN const ISOC_LONGPTR lLiveSession,IN ISOC_BOOL bIsKeep);

//设置实时断流重拉的时间间隔，通过实时模块的扩展函数将此类型传入并传入对应的时间间隔（以毫秒为单位）为设置默认为10秒,如：iSOC_LiveExtendFunc（lLiveSession,SET_LIVE_REPULL_STREAM_TIME_SPAN,10*1000);
#define SET_LIVE_REPULL_STREAM_TIME_SPAN 0x000001 

//获取实时断流重拉的时间间隔，通过实时模块的扩展函数将此类型传入并将用于获取断流重拉时间的ISOC_DWORD类型的指针通过最后一个参数传入，如：iSOC_LiveExtendFunc(lLiveSession,GET_LIVE_REPULL_STREAM_TIME_SPAN,(ISOC_DWORDPTR)&dwTimeSpan);
#define GET_LIVE_REPULL_STREAM_TIME_SPAN 0x000002

//设置实时渲染模式，在创建实时会话会后立即设置，通过实时模块的扩展函数将此类型传入并传入对应的模式，目前模式可使用GDI_RENDER_MOD、DDRAW_RENDER_MOD、D3D_RENDER_MOD这些在iSOC_UnitDefine.h里面定义，同一个实时会话只能在拉流前始设置生效。
#define SET_LIVE_RENDER_MOD				 0x000003

//获取实时渲染模式，通过实时模块的扩展函数将些类型传入并将用于获取实时渲染模式的ISOC_DWORD类型的指针通过最后一个参数传入
#define GET_LIVE_RENDER_MOD				 0x000004

//设置实时流初始化时的码流序号，一般0为主码流1为子码流
#define SET_LIVE_INIT_CODEC_IDX			 0x000005

//获取实时流渲染Session。只能在启动实时流成功后获取，否则seesion无效
#define GET_LIVE_RENDER_SESSION			  0x000006

//设置启用自动硬件加速支持,默认不支持
#define SET_LIVE_HWACCEL_SUPPORT		  0x000007

//设置断流重拉时启动实时流成回调模式，0为不回调(默认，不用设置),1回调 且每次重拉成功后都会回调
#define SET_LIVE_REPULL_CALLBACK_MOD      0X000008

/******************************************************************************************************************************
*函数名：iSOC_LiveExtendFunc
*功  能：实时扩展函数，用于实现一些扩展功能
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] nExType 扩展类型标识
		 [IN] dwExtendData 扩展数据
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LiveExtendFunc(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nExType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*函数名：iSOC_GetLiveStreamingServerAddr
*功  能：获取当前实时视频的流媒体服务器地址信息
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN OUT] strStreamServerAddr 流媒体服务器地址
		 [IN] dwReserved 保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLiveStreamingServerAddr(IN const ISOC_LONGPTR lLiveSession,IN OUT ISOC_STR strStreamServerAddr,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetCameraParameters
*功  能：设置摄像机参数
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] camParam 摄像机参数信息结构体
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetCameraParameters(IN const ISOC_LONGPTR lLiveSession,IN const ST_CameraParameter camParam);

/******************************************************************************************************************************
*函数名：iSOC_GetCameraParameters
*功  能：获取摄像机参数
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] pCamParam 摄像机参数信息结构体指针
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetCameraParameters(IN const ISOC_LONGPTR lLiveSession,IN OUT ST_CameraParameter* pCamParam);

/******************************************************************************************************************************
*函数名：iSOC_SaveCameraParametersMode
*功  能：保存摄像机参数模式
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] nConfigMode 模式0：白天 模式1：夜晚 模式2：雨天 模式3：雾天 模式4：自定义
		 [IN] dwReserved 保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SaveCameraParametersMode(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nConfigMode,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ExecuteCameraParametersMode
*功  能：执行摄像机参数模式
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] nAreaMode 摄像机区域模式，模式0：当前分控中心所有设备 模式1：当前分控中心用户集群下所有设备 模式2：平行域内所有设备 模式3：当前设备
		 [IN] nConfigMode 模式0：白天 模式1：夜晚 模式2：雨天 模式3：雾天 模式4：自定义
		 [IN] dwReserved 保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ExecuteCameraParametersMode(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nAreaMode,IN ISOC_INT nConfigMode,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_GetLiveVideoCodecInfo
*功  能：获取摄像机编码参数信息
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN OUT]  lDataListHead 数据链表头标识，要得到具体的编码参数信息可使用数据链表操作函数获取，获取的具体结构体为：ST_VideoInfo
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：默认使用第一个编码信息拉流
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLiveVideoCodecInfo(IN const ISOC_LONGPTR lLiveSession,IN OUT ISOC_LONGPTR* lDataListHead);

/******************************************************************************************************************************
*函数名：iSOC_SelectLiveVideoCodec
*功  能：选择具体的编码信息从服务器上获取实时流，使用此函数可实现码流切换
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] stCodecInfo 编码信息结构体
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SelectLiveVideoCodec(IN const ISOC_LONGPTR lLiveSession,IN ST_VideoInfo stCodecInfo);

/******************************************************************************************************************************
*函数名：iSOC_GetCurrentLiveVideoCodecInfo
*功  能：获取当前选择的编码信息
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN OUT] pCodecInfo 编码信息结构体指针
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetCurrentLiveVideoCodecInfo(IN const ISOC_LONGPTR lLiveSession,IN OUT ST_VideoInfo* pCodecInfo);

/******************************************************************************************************************************
*函数名：iSOC_SetCameraViewArea
*功  能：设置前端设备视图显示到指定的矩形位置
*参  数：
		[IN]	lLiveSession		实时会话标识
		[IN]	rtView		矩形区域信息
		[IN]	nSpeed				移动速度
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lLiveSession传入获取失败描述
*备  注：此功能要前端设备支持
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetCameraViewArea(IN const ISOC_LONGPTR lLiveSession,IN ISOC_RECT rtView,IN ISOC_INT nSpeed = 10);

iSOC_EXPORT_MODE ISOC_INT iSOC_CalculateCameraViewArea(IN ISOC_RECT rtVideoRender,IN ISOC_RECT rtMoveRange,IN ISOC_SIZE szVideo
	,IN ISOC_BOOL bIsFlip,IN ISOC_BOOL bIsKeepAspectRatio,IN ISOC_BOOL bIsCenterClicked,IN OUT ISOC_RECT* rtCameraView);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveVideoSmoothLevel
*功  能：设置当前实时视频的平滑性级别
*参  数：
		[IN]	lLiveSession		实时会话标识
		[IN]	nSmoothLevel		平滑性级别值，范围从1到10，值越大越平滑。不调用此函数默认级别为5
*返回值：成功返回大于0的值，失败返回小于0的值，失败后可以调用iSOC_GetLastErrorDes将lLiveSession传入获取失败描述
*备  注：平滑性级别跟实时性是相反的，平滑性级别越高，实时性就会越低
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoSmoothLevel(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nSmoothLevel);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveVideoRotation
*功  能：图像旋转一定角度
*参  数：
		 [IN] lLiveSession  实时会话标识
		 [IN] nAngle        图像旋转角度，目前支持：正反90、正反180、正反270
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述，
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoRotation(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nAngle);

/******************************************************************************************************************************
*函数名：iSOC_GetLiveRotationAngle
*功  能：获取视屏旋转角度
*参  数：
		 [IN]   lLiveSession  实时会话标识
		 [OUT]  pAngle        图像旋转角度,可以是负值
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述，
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLiveRotationAngle(IN const ISOC_LONGPTR lLiveSession,OUT ISOC_INT *pAngle);

/******************************************************************************************************************************
*函数名：iSOC_SetLiveStreamDataCallbackEx
*功  能：设置实时收到的数据回调，回调出的数据是解码前的数据
*参  数：
		 [IN] lLiveSession 实时会话标识
		 [IN] pCallback 回调函数指针
		 [IN] dwCookie 用户Cookie，用于在回调里面将所设置的Cookie值返回，如果不用可以设置成NULL
		 [IN] nDataType 回调数据类型，1表示视频，2表示音频，4表示用户自定义数据
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveStreamDataCallbackEx(IN const ISOC_LONGPTR lLiveSession,IN const iSOC_StreamDataCallback pCallback,IN const ISOC_DWORDPTR dwCookie = 0, IN ISOC_INT nDataType = 7);


/******************************************************************************************************************************
*函数名：iSOC_SetLiveAudioSpectrumCallback
*功  能：设置实时音频谱值回调
*参  数：
[IN] lLiveSession 实时会话标识
[IN] pCallback 回调函数指针
[IN] dwCookie 用户Cookie，用于在回调里面将所设置的Cookie值返回，如果不用可以设置成NULL
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveAudioSpectrumCallback(IN const ISOC_LONGPTR lLiveSession, IN const iSOC_AudioSpectrumCallback pCallback, IN const ISOC_DWORDPTR dwCookie = 0);

#ifdef __cplusplus
}
#endif
