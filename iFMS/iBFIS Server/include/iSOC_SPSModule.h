#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"

enum SPSSessionType
{
    LIVE,
    VOD
};

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreateSPSSession
*功  能：创建SPS控制会话
*参  数：
		 [IN OUT]	pSPSSession  	SPS会话标识
		 [IN]		lMCSession		MC会话标识
		 [IN]		type     		SPS类型
		 [IN]		param       	创建参数，当type为LIVE时，应传入设备结构体，当type为VOD时，应传入ST_VodFileInfo结构体
		 [IN]		param    		参数长度
		 [IN]       pCallBack		操作状态回调
		 [IN]		dwCookie		用户数据
		 [IN]		dwReserved		扩展参数
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateSPSSession(IN OUT ISOC_LONGPTR* pSPSSession, IN const ISOC_LONGPTR lMCSession
						, IN SPSSessionType type, ISOC_VOID* param, ISOC_INT paramLen, IN iSOC_OperatorStateCallback pCallBack = NULL
						,IN ISOC_DWORDPTR dwCookie = NULL, ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_CreateSPSSession
*功  能：销毁SPS控制会话
*参  数：
        [IN]	lSPSSession  	SPS会话标识
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseSPSSession(IN ISOC_LONGPTR lSPSSession, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_RegisterRecvMsgFromSPSServerCallback
*功  能：注册从SPS服务器返回的信令回调
*参  数：
		 [IN]	lSPSSession	SPS会话标识
		 [IN]	dwCMDID		信令标识
		 [IN]	pCallback	回调函数指针
		 [IN]	dwUserCookie 用户自定义Cookie
		 [IN]	dwReserved	保留参数
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。返回-4说明已经存在
		 一个一样的回调信息
*备  注：可以多次注册同一个信令标识，多次注册的时候pCallback,dwUserCookie,dwReserved这三个参数至少有一个要不同于其它注册的，
		 否则会发生覆盖
******************************************************************************************************************************/						
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterRecvMsgFromSPSServerCallback(IN const ISOC_LONGPTR lSPSSession, IN const ISOC_DWORD dwCMDID
						, IN iSOC_OnGotDataCallback pCallback, IN ISOC_DWORDPTR dwUserCookie, IN ISOC_DWORDPTR dwReserved = 0);
	
/******************************************************************************************************************************
*函数名：iSOC_RemoveRecvMsgFromSPSServerCallback
*功  能：移除从SPS服务器返回的信令回调
*参  数：
		 [IN]	lSPSSession	SPS会话标识
		 [IN]	dwCMDID		信令标识
		 [IN]	pCallback	回调函数指针
		 [IN]	dwUserCookie 用户自定义Cookie
		 [IN]	dwReserved	保留参数
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。返回-4说明没有找到
		 对应的回调信息
*备  注：由于系统实现了可以多次注册一个信令标识的功能，所以在移除的时候相关参数要跟注册时保持一致才能成功移除
******************************************************************************************************************************/	
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveRecvMsgFromSPSServerCallback(IN const ISOC_LONGPTR lSPSSession,IN const ISOC_DWORD dwCMDID
						,IN iSOC_OnGotDataCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);
					
/******************************************************************************************************************************
*函数名：iSOC_SendCmd2SPSServer
*功  能：将信令发送至SPS服务器
*参  数：
		 [IN]	lSPSSession SPS会话标识
		 [IN]	strXmlOut 信令内容
		 [IN]	nOutXmlLen 信令长度
		 [IN]	nCmdSubType 信令类型
		 [IN]	nOverTime 返回信令超时时间，以毫秒为单位
		 [IN]	dwCookie 用户自定义Cookie
		 [IN]	pOnGotDataCallback 返回信令的回调函数
		 [IN]	pOnOverTimeballBack 返回信令超时时的回调函数	
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。
*备  注：
******************************************************************************************************************************/					
iSOC_EXPORT_MODE ISOC_INT iSOC_SendCmd2SPSServer(IN const ISOC_LONGPTR lSPSSession,IN const ISOC_STR strXmlOut,IN const ISOC_INT nOutXmlLen,
												IN const ISOC_INT nCmdSubType,IN const ISOC_INT nOverTime,IN ISOC_DWORDPTR dwCookie = NULL,
												IN const iSOC_OnGotDataCallback pOnGotDataCallback = NULL,IN iSOC_OnAffairOverTimeCallback pOnOverTimeballback = NULL);


#ifdef __cplusplus
}
#endif