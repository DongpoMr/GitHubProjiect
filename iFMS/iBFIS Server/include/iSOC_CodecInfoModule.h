#pragma once
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////编码参数模块接口的定义/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreateCodecInfoSession
*功  能：创建编码参数会话
*参  数：
		[IN OUT] pCodecInfoSession 编码参数会话标识
		[IN] dwReserved 扩展值，置为NULL
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：在不使用此会话后一定要使用iSOC_ReleaseCodecInfoSession将此编码参数会话销毁，不然会引起内存泄漏
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateCodecInfoSession(IN OUT ISOC_LONGPTR *pCodecInfoSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseCodecInfoSession
*功  能：销毁编码参数会话
*参  数：
		 [IN] lCodecInfoSession 码流信息会话标识
		 [IN] dwReserved 扩展值，置为NULL
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseCodecInfoSession(IN ISOC_LONGPTR lCodecInfoSession,IN ISOC_DWORDPTR dwReserved = NULL);

/******************************************************************************************************************************
*函数名：iSOC_GetDevVideoCodecInfo
*功  能：获取摄像机编码参数信息
*参  数：
		 [IN] lCodecSession 编码参数会话标识
		 [IN] lMCSession
		 [IN] deviceInfo
		 [OUT]  lDataListHead 数据链表头标识，要得到具体的编码参数信息可使用数据链表操作函数获取，获取的具体结构体为：ST_VideoInfo
		 [OUT] bAudio 是否有音频信息
		 [OUT] pAudioInfo 音频信息
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDevVideoCodecInfo(IN const ISOC_LONGPTR lCodecSession,IN const ISOC_LONGPTR lMCSession,IN const ST_DeviceItem deviceInfo,IN OUT ISOC_LONGPTR* lDataListHead,IN OUT ISOC_BOOL& bAudio,OUT ST_AudioInfo* pAudioInfo);

/******************************************************************************************************************************
*函数名：iSOC_GetVodVideoCodecInfo
*功  能：获取摄像机编码参数信息
*参  数：
		 [IN] lCodecSession 编码参数会话标识
		 [IN] lMCSession
		 [IN] VodInfo
		 [OUT] pVideoInfo 视频信息
		 [OUT] bAudio 是否有音频信息
		 [OUT] pAudioInfo 音频信息
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodVideoCodecInfo(IN const ISOC_LONGPTR lCodecSession,IN const ISOC_LONGPTR lMCSession,IN const ST_VodFileInfo VodInfo,IN OUT ST_VideoInfo* pVideoInfo,IN OUT ISOC_BOOL& bAudio,IN OUT ST_AudioInfo* pAudioInfo);

#ifdef __cplusplus
}
#endif
