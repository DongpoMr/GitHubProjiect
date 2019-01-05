#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_InitSobeyManagerSystem
*功  能：初始化SDK
*参  数：无		 
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_InitSobeyManagerSystem();

/******************************************************************************************************************************
*函数名：iSOC_UnInitSobeyManagerSystem
*功  能：反初始化SDK
*参  数：无	 
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UnInitSobeyManagerSystem();



iSOC_EXPORT_MODE ISOC_INT iSOC_ManUserLogin(IN const ISOC_STR strIpAddress,IN const ISOC_WORD wPort,IN const ISOC_STR strUserName,IN const ISOC_STR strUserPwd,IN OUT ISOC_LONGPTR* pMCSession,IN iSOC_OperatorStateCallback pCallBack = NULL,IN ISOC_DWORDPTR dwCookie = NULL,IN ISOC_STR strServerType = ISIS8000_SERVER,IN ISOC_DWORDPTR dwReserved = 0);
iSOC_EXPORT_MODE ISOC_INT iSOC_ManUserLogout(IN ISOC_LONGPTR lMCSession,IN ISOC_DWORDPTR dwReserved);

/******************************************************************************************************************************
*函数名：iSOC_ManGetUserInfo
*功  能：返回用户信息
*参  数：
		 [IN]		lMCSession	MC会话标识
		 [IN OUT]	pUserInfo	用户信息结构体
		 [IN]		dwReserved	保留参数，设置为0
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ManGetUserInfo(IN const ISOC_LONGPTR lMCSession,IN OUT ST_UserInfo* pUserInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ManSendCmd2MCServer
*功  能：将信令发送至MC服务器
*参  数：
		 [IN]	lMCSession MC会话标识
		 [IN]	pOutData 信令内容
		 [IN]	nOutDataLen 信令长度
		 [IN]	nCmdSubType 信令类型
		 [IN]	nOverTime 返回信令超时时间，以毫秒为单位
		 [IN]	dwCookie 用户自定义Cookie
		 [IN]	pOnGotDataCallback 返回信令的回调函数
		 [IN]	pOnOverTimeballBack 返回信令超时时的回调函数	
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ManSendCmd2MCServer(IN const ISOC_LONGPTR lMCSession,IN const ISOC_BYTE* pOutData,IN const ISOC_INT nOutDataLen,
												IN const ISOC_INT nCmdSubType,IN const ISOC_INT nOverTime,IN ISOC_DWORDPTR dwCookie = NULL,
												IN const iSOC_OnGotDataCallback pOnGotDataCallback = NULL,IN iSOC_OnAffairOverTimeCallback pOnOverTimeballback = NULL);

/******************************************************************************************************************************
*函数名：iSOC_ManRegisterRecvMsgFromMCServerCallback
*功  能：注册从MC服务器返回的信令回调
*参  数：
		 [IN]	lMCSession	MC会话标识
		 [IN]	dwCMDID		信令标识
		 [IN]	pCallback	回调函数指针
		 [IN]	dwUserCookie 用户自定义Cookie
		 [IN]	dwReserved	保留参数
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。返回-4说明已经存在
		 一个一样的回调信息
*备  注：可以多次注册同一个信令标识，多次注册的时候pCallback,dwUserCookie,dwReserved这三个参数至少有一个要不同于其它注册的，
		 否则会发生覆盖
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ManRegisterRecvMsgFromMCServerCallback(IN const ISOC_LONGPTR lMCSession,IN const ISOC_DWORD dwCMDID,IN iSOC_OnGotDataCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);


/******************************************************************************************************************************
*函数名：iSOC_ManRemoveRecvMsgFromMCServerCallback
*功  能：移除从MC服务器返回的信令回调
*参  数：
		 [IN]	lMCSession	MC会话标识
		 [IN]	dwCMDID		信令标识
		 [IN]	pCallback	回调函数指针
		 [IN]	dwUserCookie 用户自定义Cookie
		 [IN]	dwReserved	保留参数
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。返回-4说明没有找到
		 对应的回调信息
*备  注：由于系统实现了可以多次注册一个信令标识的功能，所以在移除的时候相关参数要跟注册时保持一致才能成功移除
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ManRemoveRecvMsgFromMCServerCallback(IN const ISOC_LONGPTR lMCSession,IN const ISOC_DWORD dwCMDID,IN iSOC_OnGotDataCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);

#ifdef __cplusplus
}
#endif
