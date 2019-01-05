#ifndef __ISOC_AVRENDERMODULE_API_HEADER__
#define __ISOC_AVRENDERMODULE_API_HEADER__

#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include <MMReg.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreateVideoRender
*功  能：创建视频渲染器
*参  数：
		[OUT]	lVideoRenderSession	视频渲染器会话标识
		[IN]	strRenderDes		视频渲染器类型描述
				参见如下类型描述：
					"D3D_RENDER"    //d3d渲染描述
					"GDI_RENDER"	//GDI渲染描述
					"DDRAW_RENDER"	//ddraw渲染描述
		[IN]	dwReserved			保留字
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_CreateVideoRender(OUT ISOC_LONGPTR *lVideoRenderSession,IN ISOC_STR strRenderDes,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*函数名：iSOC_InitVideoRender
*功  能：初始化视频渲染器
*参  数：
		[IN]	lVideoRenderSession	渲染器会话标识
		[IN]	hTargetWnd			目标窗口
		[IN]	stVideoSize			视频宽高
		[IN]	enVideoDataFmt		视频数据格式,如YV12=0，RGB24... ...,目前只支持YV12.
		[IN]	dwReserved=0		保留字
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_InitVideoRender(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_HWND hTargetWnd,IN ISOC_SIZE *stVideoSize,IN MediaDataType enVideoDataFmt = YV12,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*函数名：iSOC_SetVideoRenderRect
*功  能：设置视频渲染区域，不设置默认为渲染整幅图像
*参  数：
		[IN]	lVideoRenderSession	渲染器会话标识
		[IN]	rtVideoRange		视频渲染的区域值
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_SetVideoRenderRect(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_RECT rtVideoRange);

/******************************************************************************************************************************
*函数名：iSOC_SetTargetWndRenderRect
*功  能：设置目标窗口的渲染位置，不设置则默认渲染整个窗口
*参  数：
		[IN]	lVideoRenderSession	渲染器会话标识
		[IN]	rtWndRange			渲染窗口位置
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_SetTargetWndRenderRect(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_RECT rtWndRange);

/******************************************************************************************************************************
*函数名：iSOC_SetVideoRenderKeepAspectRatio
*功  能：设置是否保持宽高比
*参  数：
		[IN]	lVideoRenderSession	渲染器会话标识
		[IN]	bNeedKeepScale		是否保持宽高比
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_SetVideoRenderKeepAspectRatio(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_BOOL bNeedKeepAspectRatio);

/******************************************************************************************************************************
*函数名：iSOC_RenderVideo
*功  能：视频渲染
*参  数：
		[IN]	lVideoRenderSession	渲染器会话标识
		[IN]	szVideo				视频数据的宽高信息
		[IN]	pVideoFrame			视频数据帧
 		[IN]	dwReserved			保留字
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_RenderVideo(IN ISOC_LONGPTR lVideoRenderSession,IN ST_SIZE szVideo,IN ST_VideoFrame * pVideoFrame,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*函数名：iSOC_AddOverlayInfo
*功  能：向视频叠加信息
*参  数：
		[IN]	lVideoRenderSession	渲染器会话标识
		[IN OUT]	pOverlayInfo 叠加信息结构体，在添加的时候里面的ID值不用填，
					在添加成功后会自动改变里面的ID值，后面修改和删除都要通过里面的ID值进行索引
 		[IN]	dwReserved			保留字
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：添加多次在则不同的地方显示不同的信息
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_AddOverlayInfo(IN ISOC_LONGPTR lVideoRenderSession,IN OUT ST_OverlayInfo* pOverlayInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ModifyOverlayInfo
*功  能：修改视频叠加信息，可实现叠加信息动态变化
*参  数：
		[IN]	lVideoRenderSession	渲染器会话标识
		[IN]	overlayInfo			叠加信息结构体，里面的ID值要保证正确，否则修改不成功
 		[IN]	dwReserved			保留字
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_ModifyOverlayInfo(IN ISOC_LONGPTR lVideoRenderSession,IN ST_OverlayInfo overlayInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_DelOverlayInfo
*功  能：删除视频叠加信息
*参  数：
		[IN]	lVideoRenderSession	渲染器会话标识
		[IN]	nOverlayInfoID		视频叠加信息ID值，为-1时表示删除所有叠加信息
 		[IN]	dwReserved			保留字
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_DelOverlayInfo(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_INT nOverlayInfoID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseVideoRender
*功  能：注销视频渲染器
*参  数：
		[IN]	lVideoRenderSession	渲染器会话标识
		[IN]	dwReserved			保留字
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_ReleaseVideoRender(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_DWORDPTR dwReserved=0);



/******************************************************************************************************************************
*函数名：iSOC_CreateAudioRender
*功  能：创建音频渲染器
*参  数：
		[OUT]	lAudioRenderSession	音频渲染器会话标识
		[IN]	strRenderDes		渲染器类型描述，暂为NULL
		[IN]	dwReserved			保留字
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_CreateAudioRender(OUT ISOC_LONGPTR *lAudioRenderSession,IN ISOC_STR strRenderDes,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*函数名：iSOC_InitAudioRender
*功  能：初始化音频渲染器
*参  数：
		[IN]	lAudioRenderSession	音频渲染器会话标识
		[IN]	pAudioInfo			音频格式信息
		[IN]	dwReserved			保留字
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_InitAudioRender(IN ISOC_LONGPTR lAudioRenderSession,IN ST_AudioInfo* pAudioInfo,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*函数名：iSOC_SetAudioVolume
*功  能：设置音量
*参  数：
		[IN]	lAudioRenderSession	音频渲染器会话标识
		[IN]	lVolume				音量值
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_SetAudioVolume(IN ISOC_LONGPTR lAudioRenderSession,IN ISOC_LONGPTR lVolume);

/******************************************************************************************************************************
*函数名：iSOC_GetAudioVolume
*功  能：获取音量
*参  数：
		[IN]	lAudioRenderSession	音频渲染器会话标识
		[OUT]	lVolume				音量值
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_GetAudioVolume(IN ISOC_LONGPTR lAudioRenderSession,OUT ISOC_INT *nVolume);

/******************************************************************************************************************************
*函数名：iSOC_RenderAudio
*功  能：音频渲染
*参  数：
		[IN]	lAudioRenderSession	音频渲染器会话标识
		[IN]	pData				音频数据指针
		[IN]	nDataLen			音频数据长度
		[IN]	dwReserved			保留字
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_RenderAudio(IN ISOC_LONGPTR lAudioRenderSession,IN ISOC_BYTE* pData,IN ISOC_INT nDataLen,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseAudioRender
*功  能：注销音频渲染器
*参  数：
		[IN]	lAudioRenderSession	音频渲染器会话标识
		[IN]	dwReserved			保留字
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_ReleaseAudioRender(IN ISOC_LONGPTR lAudioRenderSession,IN ISOC_DWORDPTR dwReserved=0);

#ifdef __cplusplus
}
#endif

#endif