#pragma once
#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreateDeviceTalkSession
*功  能：创建设备对讲会话
*参  数：
		[IN OUT]	lpDeviceTalkSession	设备对讲会话 
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lDeviceTalkSession传入获取失败描述
*备  注：一个会话对应一个设备的对讲
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateDeviceTalkSession(IN OUT ISOC_LONGPTR * lpDeviceTalkSession);

/******************************************************************************************************************************
*函数名：iSOC_SetDeviceTalkInfo
*功  能：设置设备对讲信息
*参  数：	
		[IN]	lDeviceTalkSession	设备对讲会话
		[IN]	lMCSession			管理中心会话
		[IN]	stAudioInfo			音频信息
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lDeviceTalkSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetDeviceTalkInfo(IN ISOC_LONGPTR lDeviceTalkSession,IN ISOC_LONGPTR lMCSession,IN ST_AudioInfo stAudioInfo);

/******************************************************************************************************************************
*函数名：iSOC_SetDeviceTalkInfo
*功  能：获取设备支持的对讲信息
*参  数：	
		[IN]	lDeviceTalkSession	设备对讲会话
		[OUT]	ppAudioInfo			音频信息指针
		[IN OUT] nAudioInfoCount	音频信息个数
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lDeviceTalkSession传入获取失败描述
*备  注：此函数要在开始对讲之后才可以调用
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceSupportedTalkInfo(IN ISOC_LONGPTR lDeviceTalkSession,OUT ST_AudioInfo** ppAudioInfo,IN OUT ISOC_INT& nAudioInfoCount);

/******************************************************************************************************************************
*函数名：iSOC_SetDeviceTalkType
*功  能：设置设备对类型
*参  数：	
		[IN]	lDeviceTalkSession	设备对讲会话
		[IN]	nTalkType			对讲类型:0、本机获取音频  1、通过iSOC_PushAudioBuff传入音频数据
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lDeviceTalkSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetDeviceTalkType(IN ISOC_LONGPTR lDeviceTalkSession,IN ISOC_INT nTalkType=0);

/******************************************************************************************************************************
*函数名：iSOC_PushAudioBuff
*功  能：设置设备对讲数据
*参  数：	
		[IN]	lDeviceTalkSession	设备对讲会话
		[IN]	pBuff				音频数据
		[IN]nBuffLen				数据长度
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lDeviceTalkSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_PushAudioBuff(IN ISOC_LONGPTR lDeviceTalkSession,IN ISOC_BYTE* pBuff,IN ISOC_INT nBuffLen);

/******************************************************************************************************************************
*函数名：iSOC_StartDeviceTalk
*功  能：对指定设备开始对讲
*参  数：
		[IN]	lDeviceTalkSession	设备对讲会话
		[IN]	stDevInfo			设备信息
		[IN]	dwReserved			保留字
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lDeviceTalkSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartDeviceTalk(IN ISOC_LONGPTR lDeviceTalkSession,IN ST_DeviceItem stDevInfo,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*函数名：iSOC_StopDeviceTalk
*功  能：停止对讲
*参  数：
		[IN]  DeviceTalkSession 设备对讲会话
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lDeviceTalkSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopDeviceTalk(IN ISOC_LONGPTR lDeviceTalkSession);

/******************************************************************************************************************************
*函数名：iSOC_RealseDeviceTalkSession
*功  能：销毁设备对讲会话
*参  数：
		[IN]  DeviceTalkSession 设备对讲会话
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lDeviceTalkSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RealseDeviceTalkSession(IN ISOC_LONGPTR lDeviceTalkSession);

/******************************************************************************************************************************
*函数名：iSOC_CreateMonitorTalkSession
*功  能：创建客户端对讲会话
*参  数：
		[IN OUT]	lpMonitorTalkSession	客户端对讲会话
		[IN]		lMCSession				管理中心会话
		[IN]		stAudioInfo				音频信息，编码audioCodecId ---- G711:0x02 ,G726:0x04
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lMonitorTalkSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateMonitorTalkSession(IN OUT ISOC_LONGPTR *lpMonitorTalkSession,IN ISOC_LONGPTR lMCSession,IN ST_AudioInfo stAudioInfo);


/******************************************************************************************************************************
*函数名：iSOC_CtrlLocalAudioListen
*功  能：控制客户端是否监听
*参  数：
		[IN]	lMonitorTalkSession	客户端对讲会话
		[IN]	bStart				是否启动监听，TRUE：开始监听，FALSE：停止监听
		[IN]	nPort				监听端口，默认为61000
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lMonitorTalkSession传入获取失败描述
*备  注：如果需要监听对方客户端的对讲必须开始此监听
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CtrlLocalAudioListen(IN ISOC_LONGPTR lMonitorTalkSession,IN ISOC_BOOL bStart = TRUE,IN ISOC_INT nPort = 61000);

/******************************************************************************************************************************
*函数名：iSOC_CtrlMonitorTalk
*功  能：控制设备对讲
*参  数：
		[IN]	lMonitorTalkSession		客户端对讲会话
		[IN]	strMonitorIP				对讲客户端IP地址
		[IN]	nPort					端口
		[IN]	bStart					是否开始对讲，TRUE:开始，FALSE:停止
		[IN]	bBroadCast				是否广播
		[IN]	dwReserved				保留字
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lMonitorTalkSession传入获取失败描述
*备  注：此函数可以多次调用，设置不同的客户端IP地址和端口，和多个客户端对讲
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CtrlMonitorTalk(IN ISOC_LONGPTR lMonitorTalkSession,IN const ISOC_STR strMonitorIP,IN ISOC_INT nPort = 61000,IN ISOC_BOOL bStart = TRUE,IN ISOC_BOOL bBroadCast = FALSE,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*函数名：iSOC_RealseMonitorTalkSession
*功  能：销毁客户端对讲会话
*参  数：
		[IN]	lMonitorTalkSession		客户端对讲会话
*返回值：成功返回大于0的值，失败返回小于0的值，如果失败可通过iSOC_GetLastErrorDes函数将lMonitorTalkSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RealseMonitorTalkSession(IN ISOC_LONGPTR lMonitorTalkSession);

#ifdef __cplusplus
}
#endif