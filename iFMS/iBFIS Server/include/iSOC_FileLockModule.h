#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////文件锁模块接口的定义/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreateFileLockSession
*功  能：创建文件锁定Session
*参  数：
		 [IN] lMCSession MC会话
		 [IN OUT] pFileLockSession 文件锁定会话
		 [IN] pStateCallback 状态回调
		 [IN] dwCookie 状态回调中传入的用户数据
		 [IN] dwReserved 保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateFileLockSession(IN const ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pFileLockSession,
													 IN iSOC_OperatorStateCallback pStateCallback = ISOC_NULL,
													 IN ISOC_DWORDPTR dwCookie = 0,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseFileLockSession
*功  能：销毁文件锁定会话
*参  数：
		 [IN] lFileLockSession	文件锁定会话
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseFileLockSession(IN ISOC_LONGPTR lFileLockSession);

/******************************************************************************************************************************
*函数名：iSOC_GetLockCenterListHead
*功  能：获取当前用户可用的锁定中心的列表
*参  数：
		 [IN] lFileLockSession	文件锁定会话
		 [IN OUT] pCenterListHead 数据链表头标识，要得到文件锁定所有中心信息,可使用数据链表操作函数获取，获取的具体结构体为：ST_CenterInfo
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetFileLockCenterListHead(IN const ISOC_LONGPTR lFileLockSession,IN OUT ISOC_LONGPTR* pCenterListHead);

/******************************************************************************************************************************
*函数名：iSOC_GetFileLockInfo
*功  能：获取锁定信息
*参  数：
		 [IN] lFileLockSession 文件锁定会话
		 [IN] pCenterInfo 要查询的文件锁定中心
		 [IN] pCallback 接收查询数据的回调
		 [IN] dwCookie 回调中带有的用户数据
		 [IN] dwReserved 保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetFileLockInfo(IN const ISOC_LONGPTR lFileLockSession,IN const ST_CenterInfo* pCenterInfo,IN iSOC_FileLockInfoCallback pCallback,IN ISOC_DWORDPTR dwCookie,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_LockVodFile
*功  能：锁定VOD文件
*参  数：
		 [IN] lFileLockSession 文件锁定会话
		 [IN OUT] pLockInfo 锁信息，锁定的时候ID为0，锁定成功后SDK会修改ID的值为锁的ID
		 [IN] pLockItem 锁定的文件信息
		 [IN] nLockItemCount 文件信息个数
		 [IN] dwReserved 保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LockVodFile(IN const ISOC_LONGPTR lFileLockSession,IN OUT ST_FileLockInfo* pLockInfo,IN ST_FileLockItem* pLockItem,IN ISOC_INT nLockItemCount,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_UnLockVodFile
*功  能：解锁已经锁定的VOD文件
*参  数：
		 [IN] lFileLockSession 文件锁定会话
		 [IN] pCenterInfo 中心信息
		 [IN] pLockInfo 锁信息
		 [IN] dwReserved 保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UnLockVodFile(IN const ISOC_LONGPTR lFileLockSession, IN ST_CenterInfo* pCenterInfo,IN ST_FileLockInfo* pLockInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_GetCenterLockSpaceInfo
*功  能：获取中心文件锁定信息
*参  数：
		 [IN] lFileLockSession 文件锁定会话
		 [IN] pCenterInfo 中心信息
		 [IN OUT] pSpaceInfo 锁定中心锁定空间信息
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetCenterLockSpaceInfo(IN const ISOC_LONGPTR lFileLockSession,IN ST_CenterInfo* pCenterInfo,IN OUT ST_FileLockSpaceInfo* pSpaceInfo);
#ifdef __cplusplus
}
#endif