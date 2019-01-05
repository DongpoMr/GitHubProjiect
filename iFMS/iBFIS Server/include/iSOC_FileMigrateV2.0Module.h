#pragma once
#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_GetMigrateV20CenterListInfo
*功  能：获取当前用户可用的迁移中心的列表
*参  数：
		 [IN] lMCSession	管理中心会话
		 [IN OUT] pCenterListHead 数据链表头标识，要得到具体的迁移中心信息可使用数据链表操作函数获取，获取的具体结构体为：ST_CenterInfo
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMigrateV20CenterListInfo(IN const ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pCenterListHead);

/******************************************************************************************************************************
*函数名：iSOC_CreateMigrateV20Session
*功  能：创建针对于iSOC2.0迁移服务器的迁移会话
*参  数：
		 [IN] lMCSession	管理中心会话
		 [IN OUT] pMigrateSession	迁移会话
		 [IN] pStateCallback	状态回调
		 [IN] dwCookie			对应于状态回调的用户Cookie
		 [IN] dwReserved	保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：使用完成后要即时将其销毁,建议一个迁移任务对应一个会话
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateMigrateV20Session(IN const ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pMigrateSession,IN iSOC_OperatorStateCallback pStateCallback = NULL,IN ISOC_DWORDPTR dwCookie = 0,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseMigrateV20Session
*功  能：销毁针对于iSOC2.0迁移服务器的迁移会话
*参  数：
		 [IN] lMigrateSession	迁移会话
		 [IN] dwReserved	保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseMigrateV20Session(IN ISOC_LONGPTR lMigrateSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetMigrateV20Info
*功  能：设置迁移信息
*参  数：
		[IN] lMigrateSession	迁移会话
		[IN] strMigrateDesc		迁移描述
		[IN] strTaskUniqueFlag	迁移标识用于用户记录与此迁移有关的标识信息，可以为空
		[IN] dwReserved	保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetMigrateV20Info(IN const ISOC_LONGPTR lMigrateSession,IN const ISOC_STR strMigrateDesc,IN const ISOC_STR strTaskUniqueFlag,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetMigrateV20CenterInfo
*功  能：设置迁移任务要执行的迁移中心信息
*参  数：
		 [IN] lMigrateSession	迁移会话
		 [IN] centerInfo		迁移中心信息
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：在开始迁移之前必须要设置迁移中心信息
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetMigrateV20CenterInfo(IN const ISOC_LONGPTR lMigrateSession,IN ST_CenterInfo* pCenterInfo);

/******************************************************************************************************************************
*函数名：iSOC_SetMigrateV20Speed
*功  能：设置迁移速度
*参  数：
		 [IN] lMigrateSession	迁移会话
		 [IN] nSpeed			迁移速度
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetMigrateV20Speed(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nSpeed);

/******************************************************************************************************************************
*函数名：iSOC_AddMigrateV20TaskItem
*功  能：向迁移任务中添加一个任务子项
*参  数：
		 [IN] lMigrateSession	迁移会话
		 [IN] migrateItem		迁移子任务信息
		 [IN] dwReserved		保留参数
*返回值：调用成功返回任务子项的索引，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：这些任务不是即时的，添加后会先将任务缓存在本地，在开始任务的时候才会发送给服务器
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddMigrateV20TaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ST_MigrateItem* pMigrateItem,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_DelMigrateV20TaskItem
*功  能：删除本地的未开始的迁移任务子项
*参  数：
		 [IN] lMigrateSession	迁移会话
		 [IN] nTaskItemIdx		本地任务子项的索引值
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：此函数只用于删除本地未提交到服务器上的任务，如果任务已经提交则删除无效
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelMigrateV20TaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemIdx);

/******************************************************************************************************************************
*函数名：iSOC_StartMigrateV20Task
*功  能：开始迁移任务
*参  数：
		 [IN] lMigrateSession	迁移会话
		 [IN] dwReserved		保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartMigrateV20Task(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ControlMigrateV20Task
*功  能：对已经存在于服务器的迁移服务器控制
*参  数：
		 [IN] lMigrateSession	迁移会话
		 [IN] nControlCode		控制码，其取值为：1:开始,2:停止,3:暂停,4:删除
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlMigrateV20Task(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nControlCode);

/******************************************************************************************************************************
*函数名：iSOC_GetMigrateV20Info
*功  能：获取迁移服务信息
*参  数：
		 [IN] lMigrateSession	迁移会话
		 [IN OUT] pInfo			迁移任务信息
		 [IN] dwReserved		保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMigrateV20Info(IN const ISOC_LONGPTR lMigrateSession,IN OUT ST_MigrateInfo* pInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_AttachMigrateV20Task
*功  能：附加到一个迁移任务
*参  数：
		 [IN] lMigrateSession	迁移会话
		 [IN] pInfo				迁移任务信息
		 [IN] dwReserved		保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AttachMigrateV20Task(IN const ISOC_LONGPTR lMigrateSession,IN ST_MigrateInfo* pMigrateInfo,ISOC_DWORDPTR dwReserved = 0);





/******************************************************************************************************************************
*函数名：iSOC_CreateMigrateManagementSession
*功  能：创建迁移管理会话
*参  数：
		 [IN] lMCSession		管理中心会话
		 [IN] pMigrateManSession	迁移管理会话
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateMigrateManagementSession(IN ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pMigrateManSession);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseMigrateManagementSession
*功  能：销毁迁移管理会话
*参  数：
		 [IN] pMigrateManSession	迁移管理会话
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseMigrateManagementSession(IN ISOC_LONGPTR lMigrateManSession);

/******************************************************************************************************************************
*函数名：iSOC_QueryMigrateInfo
*功  能：查询迁移任务信息
*参  数：
		 [IN] pMigrateManSession	迁移管理会话
		 [IN] centerInfo			中心信息
		 [IN] nFlishFlag			任务完成标识，1为完成，2为未完成
		 [IN] pDeviceList			设备ID列表，ID之间用","隔开，如果查询未完成的迁移任务设备ID列表可以为空
		 [IN] pStartTime			迁移开始时间
		 [IN] pEndTime				迁移结束时间
		 [IN] pCallback				迁移任务信息回调
		 [IN] dwCookie				回调中返回的用户Cookie
		 [IN] dwReserved			保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：2.0使用此函数获取未完成的迁移任务，1.58仍然使用以前的接口
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_QueryMigrateInfo(IN const ISOC_LONGPTR lMigrateManSession,IN ST_CenterInfo* pCenterInfo,IN ISOC_INT nFlishFlag,IN const ISOC_STR pDeviceList,IN ISOC_SYSTEMTIME* pStartTime,
												IN ISOC_SYSTEMTIME* pEndTime,IN iSOC_FileMigrateInfoCallback pCallback,IN ISOC_DWORDPTR dwCookie,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetMigrateCatalogInfo
*功  能：设置迁移编目信息
*参  数：
		 [IN] pMigrateManSession	迁移管理会话
		 [IN] centerInfo			中心信息
		 [IN] migrateInfo			迁移信息
		 [IN] strCatalogInfo		编目信息字符串
		 [IN] nLenth				编目信息字符串长度
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetMigrateCatalogInfo(IN const ISOC_LONGPTR lMigrateManSession,IN ST_CenterInfo* pCenterInfo,IN ST_MigrateInfo* pMigrateInfo,IN ISOC_STR strCatalogInfo,IN ISOC_INT nLenth);

/******************************************************************************************************************************
*函数名：iSOC_SetMigrateCatalogInfo
*功  能：设置迁移编目信息
*参  数：
		 [IN] pMigrateManSession	迁移管理会话
		 [IN] centerInfo			中心信息
		 [IN] migrateInfo			迁移信息
		 [OUT] strCatalogInfo		编目信息字符串
		 [OUT] nLenth				编目信息字符串长度
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMigrateCatalogInfo(IN const ISOC_LONGPTR lMigrateManSession,IN ST_CenterInfo *pCenterInfo,IN ST_MigrateInfo *pMigrateInfo,OUT ISOC_STR* pStrCatalog,OUT ISOC_INT* pNLen);

/******************************************************************************************************************************
*函数名：iSOC_DelMigrateTask
*功  能：删除已经完成或者未完成的迁移任务
*参  数：
		 [IN] pMigrateManSession	迁移管理会话
		 [IN] centerInfo			中心信息
		 [IN] migrateInfo			迁移信息
		 [IN] dwReserved			保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelMigrateTask(IN const ISOC_LONGPTR lMigrateManSession,IN ST_CenterInfo *pCenterInfo,IN ST_MigrateInfo *pMigrateInfo,IN ISOC_DWORDPTR dwReserved = 0);
#ifdef __cplusplus
}
#endif