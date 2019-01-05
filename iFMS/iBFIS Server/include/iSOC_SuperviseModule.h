#pragma  once
#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

///////////////////////////////////监察管理模块接口定义////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************************************************************
*函数名：iSOC_CreateSuperviseSession
*功  能：创建监察管理会话标识
*参  数：
		[IN OUT] pLSuperviseSession 监察管理会话标识
		[IN] pCallback 监察管理回调函数,用于各种监察事件的通知
		[IN] dwReserved 扩展参数,置为NULL
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateSuperviseSession(IN OUT ISOC_LONGPTR* pLSuperviseSession,IN ISOC_LONGPTR pLMCSession, IN iSOC_SuperviseCallback pCallback, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_CreateSuperviseSession
*功  能：添加实时流监察事件
*参  数：
		 [IN] pLSuperviseSession 监察管理会话标识
		 [IN] pLLiveSession 实时流会话标识
		 [IN] stDevInfo 设备信息
		 [IN] nRecordTime 录像时长
		 [IN] strDescription 情况描述
		 [IN] ppstUserList 转发用户列表
		 [IN] nUserCount 转发用户数量
		 [IN] dwReserved 扩展参数,置为NULL
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddLiveSupervise(IN ISOC_LONGPTR pLSuperviseSession, IN ISOC_LONGPTR pLLiveSession, IN ST_DeviceItem stDevInfo,IN ISOC_SYSTEMTIME stStartTime,IN ISOC_SYSTEMTIME stEndTime, IN const ISOC_STR strDescription, IN const ST_UserInfo* pstUserList, IN ISOC_INT nUserCount,IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_CreateSuperviseSession
*功  能：添加VOD监察事件
*参  数：
		 [IN] pLSuperviseSession 监察管理会话标识
		 [IN] pLVODSession VOD会话标识
		 [IN] stVodFileInfo VOD文件信息
		 [IN] strDescription 情况描述
		 [IN] ppstUserList 转发用户列表
		 [IN] nUserCount 转发用户数量
		 [IN] dwReserved 扩展参数,置为NULL
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddVodSupervise(IN ISOC_LONGPTR pLSuperviseSession, IN ISOC_LONGPTR pLVODSession, IN ST_VodFileInfo stVodFileInfo, IN ISOC_SYSTEMTIME stStartTime,IN ISOC_SYSTEMTIME stEndTime,  IN const ISOC_STR strDescription, IN const ST_UserInfo* pstUserList, IN ISOC_INT nUserCount, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_CreateSuperviseSession
*功  能：处理监察事件
*参  数：
		 [IN] pLSuperviseSession 监察管理会话标识
		 [IN] nSuperviseID 监察事件ID
		 [IN] pstUserInfo 用户信息
		 [IN] strDescription 处理信息
		 [IN] strDescription 情况描述
		 [IN] dwCookie 用户数据
		 [IN] dwReserved 扩展参数,置为NULL
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UpdateSupervise(IN ISOC_LONGPTR pLSuperviseSession, IN ISOC_INT nSuperviseID, IN const ST_UserInfo* pstUserInfo, IN ISOC_STR strDescription, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_CreateSuperviseSession
*功  能：添加实时流监察事件
*参  数：
		 [IN] pLSuperviseSession 监察管理会话标识

		 [IN] pstStartTime 查询起始时间
		 [IN] pstEndTime 查询结束时间
		 [IN] dwReserved 扩展参数,置为NULL
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：查询结果通过创建session时传入的回调函数来通知
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetSuperviseInfo(IN ISOC_LONGPTR pLSuperviseSession, IN ST_UserInfo* pstUserInfo, IN ISOC_SYSTEMTIME* pstStartTime, IN ISOC_SYSTEMTIME* pstEndTime, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseSuperviseSession(IN ISOC_LONGPTR pLSuperviseSession, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_DelSupervise
*功  能：删除监察事件
*参  数：
		 [IN] pLSuperviseSession 监察管理会话标识
		 [IN] nSuperviseID 监察事件ID
		 [IN] pstUserInfo 用户信息
		 [IN] dwCookie 用户数据
		 [IN] dwReserved 扩展参数,置为NULL
*返回值：成功初始化则返回大于0的值，初始化不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelSupervise(IN ISOC_LONGPTR pLSuperviseSession, IN ISOC_INT nSuperviseID, IN const ST_UserInfo* pstUserInfo, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);


#ifdef __cplusplus
}
#endif