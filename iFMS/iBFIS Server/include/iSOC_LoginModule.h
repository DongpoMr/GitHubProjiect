#pragma once
#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_InitSobeyMonitorSystem
*功  能：初始化SDK
*参  数：无		 
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：注意:此函数有文件操作，因此不能在DLL或者应用程序的初始化函数中调用
		（微软MSDN上明确说明了不能在DLL或者应用程序初始化函数中操作文件，否则可能会出现应用程序无法启动或者卡死的问题）。
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_InitSobeyMonitorSystem();

/******************************************************************************************************************************
*函数名：iSOC_UnInitSobeyMonitorSystem
*功  能：反初始化SDK
*参  数：无	 
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UnInitSobeyMonitorSystem();


/******************************************************************************************************************************
*函数名：iSOC_UserLogin
*功  能：用户登录
*参  数：
		 [IN] strIpAddress 管理服务器IP地址
		 [IN] wPort 管理服务器端口
		 [IN] strUserName 用户名
		 [IN] strUserPwd 密码
		 [IN OUT] pMCSession 管理中心会话标识，简称MC会话标识
		 [IN] pCallBack 操作状态回调函数指针
		 [IN] dwCookie 用户Cookie，用于用户使用，在操作状态回调中将用户设置的Cookie返回
		 [IN] nClientType 客户端类型，可以为：1表示为客户端登录，2表示为电视墙控制端登录，3表示为电视墙服务器登录
		 [IN] strServerType 服务器系统类型，参见iSOC_Datatype_Define.h中服务器类型定义
		 [IN] dwReserved 保留参数，一般设置为，当其值为10001时则登录时不会向服务器获取初始化数据（即设备数据等）
*返回值：调用成功返回大于0的值，调用失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UserLogin(IN const ISOC_STR strIpAddress,IN const ISOC_WORD wPort,IN const ISOC_STR strUserName,IN const ISOC_STR strUserPwd,IN OUT ISOC_LONGPTR* pMCSession,IN iSOC_OperatorStateCallback pCallBack = NULL,IN ISOC_DWORDPTR dwCookie = NULL,IN ISOC_INT nClientType = 1,IN const ISOC_STR strServerType = SOBEY_SERVER,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_UserLogout
*功  能：用户注销
*参  数：
		 [IN] lMCSession MC会话标识
*返回值：调用成功返回大于0的值，调用失败返回小于0的值。若调用失败，可使用iSOC_GetLastErrorDes获取错误描述
*备  注：如果成功注销，对应的MC会话标识所申请的资源都会被释放，因此，成功注销后MC会话标识不应该再被使用
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UserLogout(IN const ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*函数名：iSOC_GetUserInfo
*功  能：返回用户信息
*参  数：
		 [IN]		lMCSession	MC会话标识
		 [IN OUT]	pUserInfo	用户信息结构体
		 [IN]		dwReserved	保留参数，设置为0
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetUserInfo(IN const ISOC_LONGPTR lMCSession,IN OUT ST_UserInfo* pUserInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_GetDeviceCount
*功  能：获取设备总数
*参  数：
		 [IN] lMCSession MC会话标识
*返回值：调用成功返回大于0的值，调用失败返回小于0的值。若调用失败，可使用iSOC_GetLastErrorDes获取错误描述
*备  注：获取的设备总数包括组织机构数目
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceCount(IN const ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*函数名：iSOC_GetDeviceInfoByIndex
*功  能：通过索引序号获取设备信息
*参  数：
		 [IN] lMCSession MC会话标识
		 [IN OUT] pDevInfo 设备信息结构体指针
		 [IN] nIdx 索引序号。索引序号是从0-设备总数-1的值
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。
*备  注：获取的设备信息中设备ID值为负值表示所得到的信息为组织机构的信息
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceInfoByIndex(IN const ISOC_LONGPTR lMCSession,IN OUT ST_DeviceItem *pDevInfo,IN const ISOC_INT nIdx);

/******************************************************************************************************************************
*函数名：iSOC_GetDeviceInfoByUnitCode
*功  能：通过统一编码获取设备信息
*参  数：
		 [IN] lMCSession MC会话标识
		 [IN OUT] pDevInfo 设备信息结构体指针
		 [IN] strUnitCode 设备统一编码
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。
*备  注：获取的设备信息中设备ID值为负值表示所得到的信息为组织机构的信息
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceInfoByUnitCode(IN const ISOC_LONGPTR lMCSession,IN OUT ST_DeviceItem *pDevInfo,IN const ISOC_STR strUnitCode);

/******************************************************************************************************************************
*函数名：iSOC_GetDeviceInfoByDeviceId
*功  能：通过设备ID获取设备信息
*参  数：
	     [IN] lMCSession MC会话标识
		 [IN OUT] pDevInfo 设备信息结构体指针
		 [IN] iDeviceId 设备ID值，此ID值为全局唯一的ID值，即对应ST_DeviceItem中的lDeviceID
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。
*备  注：获取的设备信息中设备ID值为负值表示所得到的信息为组织机构的信息
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceInfoByDeviceId(IN const ISOC_LONGPTR lMCSession,IN OUT ST_DeviceItem *pDevInfo,IN const ISOC_ID iDeviceId);

/******************************************************************************************************************************
*函数名：iSOC_GetDeviceInfoByIcmsSignAndIcmsDeviceId
*功  能：通过ICMS标识和设备所在分控的ID即IcmsId获取设备信息
*参  数：
	     [IN] lMCSession MC会话标识
		 [IN OUT] pDevInfo 设备信息结构体指针
		 [IN] strICMSSign 设备的ICMS标识
		 [IN] iICMSDeviceId 设备所在分控的ID，此值不是全局唯一的，但在设备所在分控是全局唯一的。此值对应ST_DeviceItem中的lIcmsId
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。
*备  注：获取的设备信息中设备ID值为负值表示所得到的信息为组织机构的信息。使用此函数查找设备是效率最高的，建议使用此函数
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceInfoByIcmsSignAndIcmsDeviceId(IN const ISOC_LONGPTR lMCSession,IN OUT ST_DeviceItem *pDevInfo,IN ISOC_STR strICMSSign,IN ISOC_ID iICMSDeviceId);


/******************************************************************************************************************************
*函数名：iSOC_RegisterDeviceChangedNotifyCallback
*功  能：设置设备更新回调
*参  数：
	     [IN] lMCSession MC会话标识
		 [IN] pCallback 设备变更回调函数
		 [IN] dwCookie 用户cookie
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterDeviceChangedNotifyCallback(IN const ISOC_LONGPTR lMCSession,IN iSOC_DeviceInfoChangedCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*函数名：iSOC_RegisterPermissionChangedNotifyCallback
*功  能：设置权限更新回调
*参  数：
	     [IN] lMCSession MC会话标识
		 [IN] pCallback 设备变更回调函数
		 [IN] dwCookie 用户cookie
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterPermissionChangedNotifyCallback(IN const ISOC_LONGPTR lMCSession,IN iSOC_PermissionChangedCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*函数名：iSOC_CheckDevicePermission
*功  能：判断设备权限
*参  数：
		 [IN] lMCSession MC会话标识
		 [IN] stDevInfo 设备信息结构体
		 [IN] nPermissionCode 子设备权限代码，其具体值参见iSOC_Datatype_Define.h中设备权限码定义
*返回值：如果具有对应权限返回ISOC_TRUE，不具有对应权限返回ISOC_FALSE
*备  注：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_BOOL iSOC_CheckDevicePermission(IN const ISOC_LONGPTR lMCSession,IN const ST_DeviceItem stDevInfo,IN const ISOC_INT nPermissionCode);

/******************************************************************************************************************************
*函数名：iSOC_CheckSystemPermission
*功  能：判断系统权限
*参  数：
		 [IN] lMCSession MC会话标识
		 [IN] nPermissionCode 系统权限代码，其具体值参见iSOC_Datatype_Define.h中系统权限码定义
		 [IN] dwReserved 保留参数，设置为NULL
*返回值：如果具有对应权限返回ISOC_TRUE，不具有对应权限返回ISOC_FALSE
*备  注：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_BOOL iSOC_CheckSystemPermission(IN const ISOC_LONGPTR lMCSession,IN const ISOC_INT nPermissionCode,IN ISOC_DWORDPTR dwReserved = NULL);

/******************************************************************************************************************************
*函数名：iSOC_SendCmd2MCServer
*功  能：将信令发送至MC服务器
*参  数：
		 [IN]	lMCSession MC会话标识
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
iSOC_EXPORT_MODE ISOC_INT iSOC_SendCmd2MCServer(IN const ISOC_LONGPTR lMCSession,IN const ISOC_STR strXmlOut,IN const ISOC_INT nOutXmlLen,
												IN const ISOC_INT nCmdSubType,IN const ISOC_INT nOverTime,IN ISOC_DWORDPTR dwCookie = NULL,
												IN const iSOC_OnGotDataCallback pOnGotDataCallback = NULL,IN iSOC_OnAffairOverTimeCallback pOnOverTimeballback = NULL);

/******************************************************************************************************************************
*函数名：iSOC_RegisterRecvMsgFromMCServerCallback
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
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterRecvMsgFromMCServerCallback(IN const ISOC_LONGPTR lMCSession,IN const ISOC_DWORD dwCMDID,IN iSOC_OnGotDataCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);


/******************************************************************************************************************************
*函数名：iSOC_RemoveRecvMsgFromMCServerCallback
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
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveRecvMsgFromMCServerCallback(IN const ISOC_LONGPTR lMCSession,IN const ISOC_DWORD dwCMDID,IN iSOC_OnGotDataCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);


/******************************************************************************************************************************
*函数名：iSOC_GetOnlineClientInfo
*功  能：获取在线客户端的信息
*参  数：
		 [IN] lMCSession MC会话标识
		 [IN] pCallBack	 客户端信息回调函数，strDes包含了客户端的信息，格式为ip:name，例如：172.16.12.1:client1
		 [IN] dwCookie	 用户COOKIE
*返回值：调用成功返回大于0的值，调用失败返回小于0的值。若调用失败，可使用iSOC_GetLastErrorDes获取错误描述
*备  注：每回调一次返回一条客户端信息，如果同时在线多个客户端，就会产生多个回调
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetOnlineClientsInfo(IN const ISOC_LONGPTR lMCSession,IN iSOC_OnGotOnlineClientInfoCallback pCallBack,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*函数名：iSOC_SetRecvServerTimeCallback
*功  能：设置收到服务器同步的时间时的回调函数
*参  数：
		 [IN] lMCSession MC会话标识
		 [IN] pCallBack	 时间信息回调函数
		 [IN] dwCookie	 用户COOKIE
*返回值：调用成功返回大于0的值，调用失败返回小于0的值。若调用失败，可使用iSOC_GetLastErrorDes获取错误描述
*备  注：每回调一次返回一条客户端信息，如果同时在线多个客户端，就会产生多个回调
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetRecvServerTimeCallback(IN const ISOC_LONGPTR lMCSession,IN iSOC_OnRecvServerTimeCallback pCallback,IN ISOC_DWORDPTR dwCookie);

//设置从服务器信息，通过扩展函数设置，dwExtendData传入ST_ServerInfo结构体指针
#define ISOC_SET_SLAVE_SERVER_INFO    0x00000001

/******************************************************************************************************************************
*函数名：iSOC_MCModuleExtendFunc
*功  能：MC相关的扩展函数
*参  数：
[IN]		lMCSession			MC会话标识
[IN]		nExteydType			可扩展的类型
[IN]		dwExtendData		可扩展的数据信息
*返回值：调用成功返回大于0的值，失败返回小于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLDownloadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_MCModuleExtendFunc(IN const ISOC_LONGPTR lMCSession,IN const ISOC_INT nExteydType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*函数名：iSOC_SetTransparentData
*功  能：设置透明通道数据
*参  数：
[IN]		lMCSession			MC会话标识
[IN]		strKey
[IN]		nDataArea
[IN]		strContent
[IN]		dwExtendData		可扩展的数据信息
*返回值：调用成功返回大于0的值，失败返回小于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLDownloadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetTransparentData(IN const ISOC_LONGPTR lMCSession,IN const ISOC_STR strKey,IN ISOC_INT nDataArea,IN const ISOC_STR strContent,IN iSOC_OperatorStateCallback pOperatorCallback,IN ISOC_DWORDPTR dwCookie = ISOC_NULL,IN ISOC_DWORDPTR dwReserved = ISOC_NULL);


iSOC_EXPORT_MODE ISOC_INT iSOC_DelTransparentData(IN const ISOC_LONGPTR lMCSession,IN const ISOC_STR strKey,IN ISOC_INT nDataArea,IN iSOC_OperatorStateCallback pOperatorCallback,IN ISOC_DWORDPTR dwCookie = ISOC_NULL,IN ISOC_DWORDPTR dwReserved = ISOC_NULL);

/******************************************************************************************************************************
*函数名：iSOC_GetTransparentData
*功  能：获取透明通道数据
*参  数：
[IN]		lMCSession			MC会话标识
[IN]		nExteydType			可扩展的类型
[IN]		dwExtendData		可扩展的数据信息
*返回值：调用成功返回大于0的值，失败返回小于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLDownloadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetTransparentData(IN const ISOC_LONGPTR lMCSession,IN const ISOC_INT nDataArea,IN const ISOC_STR strKey,IN iSOC_OnGotTransparentDataInfoCallback pCallback,IN ISOC_DWORDPTR dwCookie = ISOC_NULL,IN ISOC_DWORDPTR dwReserved = ISOC_NULL);


iSOC_EXPORT_MODE ISOC_INT iSOC_GetSystemTypeAndVersion(IN const ISOC_LONGPTR lMCSession,IN OUT ISOC_CHAR chServerType[20],IN OUT ISOC_CHAR chVersion[16]);

/******************************************************************************************************************************
*函数名：iSOC_GetServerInfoList
*功  能：获取登录用户用权限的服务器信息
*参  数：
		 [IN]	lMCSession	MC会话标识
		 [IN]	enServerType 服务器类型
		 [IN]	pServerInfoHeader	服务器信息头，使用链表函数操作，返回的结构体类型为：ST_ServerInfo
		 [IN]	dwReserved	保留参数
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。返回-4说明没有找到
		 对应的回调信息
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetServerInfoList(IN const ISOC_LONGPTR lMCSession,IN ST_ServerInfo::EN_ServerType enServerType,IN OUT ISOC_LONGPTR* pServerInfoHeader,IN ISOC_DWORDPTR dwReserved);

/******************************************************************************************************************************
*函数名：iSOC_GetLocalSystemVersion
*功  能：获取当前系统sdk版本号
*参  数：
		[IN OUT]	chLocalVersion 本地SDK版本号

*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。返回-4说明没有找到
		 对应的回调信息
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLocalSystemVersion(IN OUT ISOC_CHAR chLocalVersion[20]);

#ifdef __cplusplus
}
#endif