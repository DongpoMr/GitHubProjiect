#pragma once
#include "iSOC_UnitDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreateTTSSession
*功  能：创建文字语音阅读会话
*参  数：
		[IN OUT] pLTTSSession   文字语音阅读会话标识
		[IN] dwReserved         扩展值，置为0
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：在不使用此会话后一定要使用iSOC_ReleaseLiveSession将此实时会话销毁，不然会引起内存泄漏
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateTTSSession(IN OUT ISOC_LONGPTR* pLTTSSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_TTSSpeak
*功  能：语音阅读
*参  数：
		[IN] lTTSSession        文字语音阅读会话标识
		[IN] strText            需要阅读的字符串
		[IN] nTextLen           字符串长度
		[IN] dwReserved         扩展值，置为0
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：在不使用此会话后一定要使用iSOC_ReleaseLiveSession将此实时会话销毁，不然会引起内存泄漏
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_TTSSpeak(IN ISOC_LONGPTR lTTSSession, IN const ISOC_STR strText, IN ISOC_INT nTextLen, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseTTSSession
*功  能：销毁文字语音阅读会话
*参  数：
        [IN OUT] pLTTSSession   文字语音阅读会话标识
        [IN] dwReserved         扩展值，置为0
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：在不使用此会话后一定要使用iSOC_ReleaseLiveSession将此实时会话销毁，不然会引起内存泄漏
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseTTSSession(IN ISOC_LONGPTR lTTSSession, IN ISOC_DWORDPTR dwReserved = 0);

#ifdef __cplusplus
}
#endif
