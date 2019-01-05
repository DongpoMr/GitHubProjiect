#ifndef __ISOC_AVCODECMODULE_API_HEADER__
#define __ISOC_AVCODECMODULE_API_HEADER__

#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreateAVCodec
*功  能：创建编解码器
*参  数：
		[OUT]	lAVCodecSession 创建的编解码器会话标识
		[IN]	nCodecType		编解码器类型，0：视频解码器，1：音频解码器，2：视频编码器，3：音频编码器
		[IN]	strCodecDes		编解码器类型描述，其值为对应codecID的值转换成字符串
		[IN]	dwReserved		保留字
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_CreateAVCodec(OUT ISOC_LONGPTR	*lAVCodecSession,IN ISOC_INT nCodecType,IN ISOC_STR strCodecDes,IN ISOC_DWORDPTR dwReserved=0);


/******************************************************************************************************************************
*函数名：iSOC_SetAVCodecParameters
*功  能：设置解码器选项
*参  数：
		[IN]	lAVCodecSession	编解码器会话标识
		[IN]	nCtrlCmd		编解码器控制命令
				参见：
				FLUSH_CODEC_BUFFER = 1,	// flush the codec(decode,encode)'s buffer
				GET_PICTURE_DIRECTION,	// flip the output picture's direction
				SET_PICTURE_DIRECTION,	// flip the output picture's direction
				GET_BRIGHTNESS,			// adjust brightness
				SET_BRIGHTNESS,			// adjust brightness
				GET_PRIVATE_DATA,		// the private information
				SET_PRIVATE_DATA,		
				SET_DECODE_OUT_PIXEL_FMT,
				SET_IN_REAL_OR_VOD_STUATION,
		[IN]	pCtrlParam		命令值
		[IN]	nParamLen		命令值长度
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_SetAVCodecParameters(IN ISOC_LONGPTR lAVCodecSession,IN ISOC_INT nCtrlCmd,IN OUT ISOC_BYTE* pCtrlParam,IN ISOC_INT nParamLen);


/******************************************************************************************************************************
*函数名：iSOC_InitAVCodec
*功  能：初始化编解码器
*参  数：
		[IN]	lAVCodecSession	编解码器会话标识
		[IN]	pInitParam		初始化参数值
				对于视频该参数解码值为ST_VideoInitParam类型，编码值为ST_VideoEncodeInitParam类型
				对于音频则是ST_AudioInitParam类型
		[IN]	nParamLen		参数长度
		[IN]	dwReserved		保留字
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_InitAVCodec(IN ISOC_LONGPTR lAVCodecSession,IN ISOC_BYTE* pInitParam,IN ISOC_INT nParamLen,IN ISOC_DWORDPTR dwReserved=0);


/******************************************************************************************************************************
*函数名：iSOC_AVEncode
*功  能：数据编码
*参  数：
		[IN]	lAVCodecSession	编解码器会话标识
		[IN]	pSrcData		原始数据
		[IN]	nSrcLen			原始数据长度
		[OUT]	pDstData		编码后数据
		[OUT]	nDstLen			编码后数据长度
		[IN]	pPrivteParam	附加参数，默认为NULL
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_AVEncode(IN ISOC_LONGPTR lAVCodecSession,IN ISOC_BYTE* pSrcData,IN ISOC_INT nSrcLen,OUT ISOC_BYTE** pDstData,OUT ISOC_INT* nDstLen,IN ISOC_BYTE* pPrivteParam=NULL);



/******************************************************************************************************************************
*函数名：iSOC_AVDecode
*功  能：数据解码
*参  数：
		[IN]	lAVCodecSession	编解码器会话标识
		[IN]	pSrcData		原始数据
		[IN]	nSrcLen			原始数据长度
		[IN OUT] pDstData		解码后数据帧,如果为视频解码则要用ST_VideoFrame的结构体指针，如果为音频解码则为ST_AudioFrame指针
		[IN]	nDstDataLen		sizeof(ST_VideoFrame)或sizeof(ST_AudioFrame)
		[IN]	pPrivteParam	附加参数，默认为NULL。视频解码的时候为：ST_VideoParam指针
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_AVDecode(IN ISOC_LONGPTR lAVCodecSession,IN ISOC_BYTE* pSrcData,IN ISOC_INT nSrcLen,IN OUT BYTE *pDstData,IN ISOC_INT nDstDataLen,IN ISOC_BYTE* pPrivteParam=NULL);


/******************************************************************************************************************************
*函数名：iSOC_ReleaseAVCodec
*功  能：注销编解码器
*参  数：
		[IN]	lAVCodecSession	编解码器会话标识
		[IN]	dwReserved 保留参数
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_ReleaseAVCodec(IN ISOC_LONGPTR lAVCodecSession,IN ISOC_DWORDPTR dwReserved=0);



/******************************************************************************************************************************
*函数名：iSOC_FillVideoFrame
*功  能：视频数据填充
*参  数：
		[IN OUT]	pFrame			源视频帧信息
		[IN]		pFrameData		源视频帧数据
		[IN]		type			媒体格式
		[IN]		width			宽度
		[IN]		height			高度
*返回值：成功则返回转换的数据长度值，初始化则返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_FillVideoFrame(IN OUT ST_VideoFrame *pFrame, IN ISOC_BYTE *pFrameData,IN MediaDataType type, IN ISOC_INT width, IN ISOC_INT height);

/******************************************************************************************************************************
*函数名：iSOC_ConvertColorSpace
*功  能：颜色空间转换
*参  数：
		[IN]		pSrc		源数据
		[IN]		mdtSrc		源数据的颜色空间值
		[IN OUT]	pDes		目的数据
		[IN]		mdtDes		目的数据的颜色空间值
		[IN]		nWidth		图像宽度
		[IN]		nHeight		图像高度
*返回值：成功则返回转换的数据长度值，初始化则返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_ConvertColorSpace(IN ST_VideoFrame *pSrc,IN MediaDataType mdtSrc,IN OUT ST_VideoFrame* pDes,IN MediaDataType mdtDes,IN ISOC_INT nWidth,IN ISOC_INT nHeight);


#ifdef __cplusplus
}
#endif

#endif