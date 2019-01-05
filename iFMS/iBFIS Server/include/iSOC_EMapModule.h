#ifndef __ISOC_EMAPMODULE_API_HEADER__
#define __ISOC_EMAPMODULE_API_HEADER__

#include "iSOC_UnitDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_GetEMapSession
*功  能：获取电子地图会话
*参  数：
		[IN OUT]	lEMapSession	创建的电子地图会话
		[IN]		lMCSession		管理中心会话
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetEMapSession(IN OUT ISOC_LONGPTR *lEMapSession,IN ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*函数名：iSOC_GetMapNodeInfo
*功  能：获取电子地图的层级关系点信息
*参  数：
		[IN]		lEMapSession	电子地图会话
		[IN OUT]	lDataListHead	返回数据队列，数据类型ST_MapNode
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：参见iSOC_UnitDefine.h中使用数据队列的方法
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMapNodeInfo(IN ISOC_LONGPTR lEMapSession,IN OUT ISOC_LONGPTR * lDataListHead);

/******************************************************************************************************************************
*函数名：iSOC_GetMapLeafInfo
*功  能：获取电子地图类信息
*参  数：
		[IN]		lEMapSession	电子地图会话
		[IN OUT]	lDataListHead	返回数据队列，数据类型ST_MapLeaf
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：参见iSOC_UnitDefine.h中使用数据队列的方法
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMapLeafInfo(IN ISOC_LONGPTR lEMapSession,IN OUT ISOC_LONGPTR * lDataListHead);

/******************************************************************************************************************************
*函数名：iSOC_GetMapLeafMapAssInfo
*功  能：获取电子地图与子图的关联关系信息
*参  数：
		[IN]		lEMapSession	电子地图会话
		[IN OUT]	lDataListHead	返回数据队列，数据类型ST_MapLeafMapAss
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：参见iSOC_UnitDefine.h中使用数据队列的方法
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMapLeafMapAssInfo(IN ISOC_LONGPTR lEMapSession,IN OUT ISOC_LONGPTR * lDataListHead);

/******************************************************************************************************************************
*函数名：iSOC_GetMapLeafEquAssInfo
*功  能：获取电子地图与设备的关联关系信息
*参  数：
		[IN]		lEMapSession	电子地图会话
		[IN OUT]	lDataListHead	返回数据队列，数据类型ST_MapLeafEquAss
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：参见iSOC_UnitDefine.h中使用数据队列的方法
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMapLeafEquAssInfo(IN ISOC_LONGPTR lEMapSession,IN OUT ISOC_LONGPTR * lDataListHead);

/******************************************************************************************************************************
*函数名：iSOC_GetMapLeafOrgAssInfo
*功  能：获取电子地图与组织结构的关联关系信息
*参  数：
		[IN]		lEMapSession	电子地图会话
		[IN OUT]	lDataListHead	返回数据队列，数据类型ST_MapLeafOrgAss
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：参见iSOC_UnitDefine.h中使用数据队列的方法
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMapLeafOrgAssInfo(IN ISOC_LONGPTR lEMapSession,IN OUT ISOC_LONGPTR * lDataListHead);

/******************************************************************************************************************************
*函数名：iSOC_DownLoadEmapFile
*功  能：下载电子地图到指定的目录
*参  数：
		[IN]	lEMapSession	电子地图会话
		[IN]	stMapInfo		要下载的地图信息
		[IN]	strDesFilePath	下载的电子地图绝对路径
		[IN]	dwReserved		保留字
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DownLoadEmapFile(IN ISOC_LONGPTR lEMapSession,IN ST_MapLeaf stMapInfo,IN const ISOC_STR strDesFilePath,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetEmapNotifyCallback
*功  能：设置异步事件通知回调函数
*参  数：
		[IN]	lEMapSession	电子地图会话
		[IN]	pCallback		异步事件回调函数指针
		[IN]	dwCookie		用户COOKIE
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetEmapNotifyCallback(IN ISOC_LONGPTR lEMapSession,IN iSOC_OperatorStateCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*函数名：iSOC_RegisterRecvMsgFromMapServerCallback
*功  能：注册从map服务器返回的信令回调
*参  数：
		[IN]	lEMapSession	电子地图会话
        [IN]	dwCmdID		    信令标识
        [IN]	pCallback	    回调函数指针
        [IN]	dwUserCookie    用户自定义Cookie
        [IN]	dwReserved	    保留参数
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。返回-4说明已经存在
        一个一样的回调信息
*备  注：可以多次注册同一个信令标识，多次注册的时候pCallback,dwUserCookie这两个参数至少有一个要不同于其它注册的，
        否则会发生覆盖
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterRecvMsgFromMapServerCallback(IN ISOC_LONGPTR lEMapSession,
                                                                    IN const ISOC_DWORD dwCmdID,
                                                                    IN iSOC_OnGotDataCallback pCallback,
                                                                    IN ISOC_DWORDPTR dwUserCookie,
                                                                    IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_RemoveRecvMsgFromMapServerCallback
*功  能：移除从map服务器返回的信令回调
*参  数：
		 [IN]	lEMapSession	MC会话标识
		 [IN]	dwCmdID		    信令标识
		 [IN]	pCallback	    回调函数指针
		 [IN]	dwReserved	    保留参数
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败，可使用iSOC_GetLastErrorDes获取错误描述。返回-4说明没有找到
		 对应的回调信息
*备  注：由于系统实现了可以多次注册一个信令标识的功能，当pCallback为空时，移除所有与给定的dwCmdID相关回调
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveRecvMsgFromMapServerCallback(IN ISOC_LONGPTR lEMapSession,
                                                                  IN const ISOC_DWORD dwCmdID,
                                                                  IN iSOC_OnGotDataCallback pCallback,
                                                                  IN ISOC_DWORDPTR dwReserved = 0);
#ifdef __cplusplus
}
#endif

#endif