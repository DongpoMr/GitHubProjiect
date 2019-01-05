#pragma once
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////文件模块接口的定义/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif


/////////////////////////////////////////////////文件导出模块接口定义///////////////////////////////////////////////////////////////////////////
enum ExportFormat
{
    EFT_AVI,
    EFT_SMF,
    EFT_MPG,
    EFT_MP4
};

enum ExportVodFileState{ EXPORTS_FAILED, EXPORTS_FINISHED, EXPORTS_PROGRESS };

enum ExportMode
{
    EM_NORMAL,	    //旧的导出模式，如果是私有码流的话不会做转码处理
    EM_TRANSLATE	//转码后导出，导出的过程中进行解码再编码
};

enum ExportOverlayType
{
    EOT_TEXT,	    //叠加文字
    EOT_BOX,		//叠加矩形框
    EOT_PIC			//叠加图片
};

#ifndef iSOC_ExportProcCllback
typedef int(__stdcall *iSOC_ExprotProcCallback)(IN ISOC_DWORDPTR dwUserCookie, ISOC_UINT64 pts, MediaDataType enDataType, ST_VideoFrame* pFrame, ISOC_INT nProgress);
#endif

#ifndef iSOC_ExportFileCallback
	typedef int (__stdcall *iSOC_ExportFileCallback)(const ISOC_DWORDPTR dwUserCookie,const ExportVodFileState enState,const int nProgress,const ISOC_STR strDes);
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreateExportFileSession
*功  能：创建文件导出会话
*参  数：
		 [IN OUT]	pExportSession	文件导出会话标识
		 [IN]		lMCSession		MC会话标识
		 [IN]		nExportType		导出类型(0为AVI文件,1为SMF文件,2为MPG文件,3为MP4文件)
		 [IN]		strDestFilePath	导出目标文件路径
		 [IN]		pCallback		导出状态回调指针
		 [IN]		dwUserCookie	用户Cookie在导出状态回调函数中返回
		 [IN]		nSubtitle         导出是否生成字幕文件，只限于avi格式
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：若nExportType为0则目标文件的后缀名必须为.avi
		若nExportType为1则目标文件的后缀名必须为.smf
		若nExportType为2则目标文件的后缀名必须为.mpg
        若nExportType为3则目标文件的后缀名必须为.mp4
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateExportFileSession(IN OUT ISOC_LONGPTR* pExportSession,IN const ISOC_LONGPTR lMCSession,IN ISOC_INT nExportType,IN ISOC_STR strDestFilePath,IN const iSOC_ExportFileCallback pCallback = ISOC_NULL,IN const ISOC_DWORDPTR dwUserCookie = 0,IN ISOC_INT nSubtitle=0);

/******************************************************************************************************************************
*函数名：iSOC_AddExportFileItem
*功  能：添加服务器上的需要导出的源视频文件
*参  数：
		 [IN]	lExportSession	文件导出会话标识
		 [IN]	vodFileInfo		VOD文件信息结构体	
		 [IN]	pStartTime		开始时间，如果为空则表示使用vodFileInfo中的文件开始时间，如果不为空则开始时间应大于等于vodFileInfo中的文件开始时间
		 [IN]	pEndTime		结束时间，如果为空则表示使用vodFileInfo中的文件结束时间，如果不为空则结束时间应小于等于vodFileInfo中的文件结束时间
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将lExportSession传入获取失败描述
*备  注：此函数可调用多次，用于将多个服务器上的文件合并下载为一个文件，但需要根据文件的开始和结束时间先后顺序调用
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddExportFileItem(IN const ISOC_LONGPTR lExportSession,IN const ST_VodFileInfo vodFileInfo,IN ISOC_SYSTEMTIME* pStartTime,IN ISOC_SYSTEMTIME* pEndTime);

/******************************************************************************************************************************
*函数名：iSOC_StartExportFile
*功  能：开始文件导出
*参  数：
		 [IN]	lExportSession	文件导出会话标识
		 [IN]	dwReserved		保留参数
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将lExportSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartExportFile(IN const ISOC_LONGPTR lExportSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_PauseExportFile
*功  能：暂停文件导出
*参  数：
		 [IN]	lExportSession	文件导出会话标识
		 [IN]	dwReserved		保留参数
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将lExportSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_PauseExportFile(IN const ISOC_LONGPTR lExportSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_StopExportFile
*功  能：停止文件导出
*参  数：
		 [IN]	lExportSession	文件导出会话标识
		 [IN]	dwReserved		保留参数
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将lExportSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopExportFile(IN const ISOC_LONGPTR lExportSession,IN ISOC_DWORDPTR dwReserved);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseExportFileSession
*功  能：销毁文件导出会话
*参  数：
		 [IN]	lExportSession	文件导出会话标识
*返回值：成功返回大于0的值，失败返回小于等于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseExportFileSession(IN const ISOC_LONGPTR lExportSession);

#ifndef SET_EXPORT_FILE_REASON 
#define SET_EXPORT_FILE_REASON 0x001001 //设置文件导出原因，可通过扩展函数设置，nExteydType传入此值dwExtendData传入对应原因的字符串指针,在创建Session后开始导出之前设置
#endif

/******************************************************************************************************************************
*函数名：iSOC_ExportFileExtendFunc
*功  能：文件导出模块扩展函数
*参  数：
		 [IN]	lExportSession	文件导出会话标识
		 [IN]	nExteydType		扩展类型
		 [IN]	dwExtendData	扩展数据
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将lExportSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ExportFileExtendFunc(IN const ISOC_LONGPTR lExportSession,IN const ISOC_INT nExteydType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*函数名：iSOC_SetExportMode
*功  能：设置文件导出模式(普通、转码)
*参  数：
[IN]	lExportSession	文件导出会话标识
[IN]	mode		    导出模式
[IN]	dwExtendData	扩展数据
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将lExportSession传入获取失败描述
*备  注：默认为普通模式，当设置为转码模式时，会将导出的vod文件解码后重新编码成H264
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetExportMode(IN const ISOC_LONGPTR lExportSession, IN const ExportMode mode, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_AddExportOverlayInfo
*功  能：添加导出叠加信息
*参  数：
[IN]	lExportSession	文件导出会话标识
[IN]    type            叠加类型
[IN]	pConfigParam    当type为EOT_TEXT时，传入ST_ExportTextCfg类型的指针
[IN]    nConifgLen      叠加信息结构体长度
[IN]	dwExtendData	扩展数据
*返回值：成功返回大等于于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将lExportSession传入获取失败描述
*备  注：目前只支持叠加文字信息,返回值为叠加信息的id，从0开始
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddExportOverlayInfo(IN ISOC_LONGPTR lExportSession, ExportOverlayType type, IN ISOC_VOID* pConfigParam, IN ISOC_INT nConifgLen, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ModifyExportOverlayInfo
*功  能：修改导出叠加信息
*参  数：
[IN]	lExportSession	文件导出会话标识
[IN]    nOverlayInfoID  叠加信息ID
[IN]	pConfigParam    当type为EOT_TEXT时，传入ST_ExportTextCfg类型的指针
[IN]    nConifgLen      叠加信息结构体长度
[IN]	dwExtendData	扩展数据
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将lExportSession传入获取失败描述
*备  注：请在iSOC_ExprotProcCallback回调用调用该方法来实现对叠加文字的修改,目前只需要设置ST_ExportTextCfg的文字描述
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ModifyExportOverlayInfo(IN ISOC_LONGPTR lExportSession, IN ISOC_INT nOverlayInfoID, IN ISOC_VOID* pConfigParam, IN ISOC_INT nConfigLen, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_DelExportOverlayInfo
*功  能：删除叠加信息
*参  数：
[IN]	lExportSession	文件导出会话标识
[IN]    nOverlayInfoID  叠加信息ID
[IN]	dwExtendData	扩展数据
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将lExportSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelExportOverlayInfo(IN ISOC_LONGPTR lExportSession, IN ISOC_INT nOverlayInfoID, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetExportProcCallbackFunc
*功  能：设置转码进度回调
*参  数：
[IN]	lExportSession	文件导出会话标识
[IN]    pFunc           回调地址
[IN]    dwUserCookie    用户数据
[IN]	dwExtendData	扩展数据
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将lExportSession传入获取失败描述
*备  注：对于需要在导出过程中修改叠加信息的，请设置回调，并在回调中去调用修改方法
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetExportProcCallbackFunc(IN ISOC_LONGPTR lExportSession, IN iSOC_ExprotProcCallback pFunc, IN ISOC_DWORDPTR dwUserCookie, IN ISOC_DWORDPTR dwReserved = 0);


////////////////////////////////////////////////文件上传模块接口定义///////////////////////////////////////////////////////////////////////////
#ifndef iSOC_UploadFileStatusCallback
enum EN_UPLOADSTATUSFALG{ULSF_STARTFAIL=1,ULSF_STARTOK,ULSF_STOPFAIL,ULSF_STOPOK,ULSF_DELFAIL,ULSF_DELOK,ULSF_FINISHFALI,ULSF_FINISHOK};
typedef ISOC_INT (__stdcall* iSOC_UploadFileStatusCallback)(ISOC_ID nItemID,EN_UPLOADSTATUSFALG enStatusFlag,ISOC_STR strDes,ISOC_DWORDPTR dwUserCookie);
#endif

/******************************************************************************************************************************
*函数名：iSOC_CreateUploadFileSession
*功  能：创建文件上传会话
*参  数：
		[IN OUT]  pLUploadSession  文件上传会话标识
		[IN]	  lMCSession	   MC会话标识		
		 
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将pLUploadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateUploadFileSession(IN OUT ISOC_LONGPTR* pLUploadSession,IN const ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*函数名：iSOC_AddUploadFileItem
*功  能：添加文件上载项
*参  数：
		[IN]	 lUploadSession   文件上传会话标识
		[IN OUT] pNItemIdx		  文件所属行编号从0开始
		[IN]	 strSrcFilePath	  源文件路径
		[IN]	 devInfo		  设备信息
		[IN]	 strUserGUID	  用户生成的guid
		[IN]	 strDes			  文件描述信息
		[IN]	 dwReserved		  保留参数
		 
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将pLUploadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddUploadFileItem(IN const ISOC_LONGPTR lUploadSession,IN OUT ISOC_INT* pNItemIdx,IN const ISOC_STR strSrcFilePath,IN ST_DeviceItem devInfo,IN const ISOC_STR strUserGUID = NULL,IN const ISOC_STR strDes = NULL,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_DelUploadFileItem
*功  能：删除文件上载项
*参  数：
		[IN]	lUploadSession    文件上传会话标识
		[IN]	nItemIdx		  文件所属行编号从0开始
		[IN]	dwReserved		  保留参数
		 
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将pLUploadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelUploadFileItem(IN const ISOC_LONGPTR lUploadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_GetUploadFileInfo
*功  能：获取文件上载信息	
*参  数：
		 [IN]		lUploadSession		文件上传会话标识
		 [IN]		nItemIdx			文件所属行编号从0开始
		 [IN OUT]	pIFileID			文件id
		 [IN OUT]	pNFileStatus		当前文件状态	
		 [IN OUT]	pNProgress			当前文件上载进度
		 [IN]		dwReserved			保留参数
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将pLUploadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetUploadFileInfo(IN const ISOC_LONGPTR lUploadSession,IN const ISOC_INT nItemIdx,IN OUT ISOC_ID* pIFileID,IN OUT ISOC_INT* pNFileStatus,IN OUT ISOC_INT* pNProgress,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_StartUploadFile
*功  能：开始启动文件上载
*参  数：
		[IN]		lUploadSession		文件上传会话标识
		[IN]		nItemIdx			文件所属行编号从0开始
		[IN]		dwReserved			保留参数
		 
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将pLUploadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartUploadFile(IN const ISOC_LONGPTR lUploadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_StopUploadFile
*功  能：停止文件上载
*参  数：
		[IN]		lUploadSession		文件上载会话标识
		[IN]		nItemIdx			文件所属行编号从0开始
		[IN]		dwReserved			保留参数
		 
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将pLUploadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopUploadFile(IN const ISOC_LONGPTR lUploadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_RegsiterUploadFileStatusNotifyCallback
*功  能：注册文件上载状态回调
*参  数：
		[IN]		lUploadSession		文件上载会话标识
		[IN]		pCallback			文件上载状态回调函数指针
		[IN]		dwUserCookie		用户Cookie
		 
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将pLUploadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegsiterUploadFileStatusNotifyCallback(IN const ISOC_LONGPTR lUploadSession,IN iSOC_UploadFileStatusCallback pCallback,IN ISOC_DWORDPTR dwUserCookie);


/******************************************************************************************************************************
*函数名：iSOC_UploadFileExtendFunc
*功  能：文件上载可扩展函数 
*参  数：
		[IN]		lUploadSession		文件上载会话标识
		[IN]		nExteydType			可扩展类型
		[IN]		dwExtendData		可扩展数据 
		 
*返回值：成功返回大于0的值，失败返回小于等于0的值，如果调用失败可通过iSOC_GetLastErrorDes将pLUploadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UploadFileExtendFunc(IN const ISOC_LONGPTR lUploadSession,IN const ISOC_INT nExteydType,IN ISOC_DWORDPTR dwExtendData);


/******************************************************************************************************************************
*函数名：iSOC_ReleaseUploadFileSession
*功  能：销毁文件上传会话
*参  数：
		[IN]	lUploadSession 文件上传会话
*返回值：成功则返回大于0的值，否则返回小于等于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLUploadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseUploadFileSession(IN ISOC_LONGPTR lUploadSession);


////////////////////////////////////////////////文件下载模块接口定义///////////////////////////////////////////////////////////////////////////
#ifndef iSOC_DownloadFileStatusCallback
enum EN_DOWNLOADSTATUSFALG{DLSF_STARTFAIL=1,DLSF_STARTOK,DLSF_STOPFAIL,DLSF_STOPOK,DLSF_FINISHFALI,DLSF_FINISHOK};
typedef ISOC_INT (__stdcall* iSOC_DownloadFileStatusCallback)(ISOC_ID nItemID,EN_DOWNLOADSTATUSFALG enStatusFlag,ISOC_STR strDes,ISOC_DWORDPTR dwUserCookie);
#endif

/******************************************************************************************************************************
*函数名：iSOC_GetGrapFileList
*功  能：获取抓帧文件
*参  数：
		 [IN]		lMCSession		MC会话标识
		 [IN]		strDeviceList	查询的设备ID列表，如下：1,2,3,4,5... ...
		 [IN]		stQueryFilter	查询条件
		 [IN]		pCallBack		查询结果回调函数指针
		 [IN]		dwCookie		用户COOKIE
		 [IN]		strQueryGuid	用户查询GUID，每次查询用户可以指定不同的查询GUID
		 [IN]		bSyncExec		异步模式查询
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetGrapFileList( IN const ISOC_LONGPTR lMCSession,IN const ISOC_STR strDeviceList,IN ST_VodQueryFilter stQueryFilter,IN iSOC_GrabFileInfoCallback pCallBack,IN ISOC_DWORDPTR dwCookie,IN ISOC_STR strQueryGuid = NULL,IN ISOC_BOOL bSyncExec = ISOC_TRUE );

/******************************************************************************************************************************
*函数名：iSOC_GetGrapFileById
*功  能：获取抓帧文件
*参  数：
[IN]		lMCSession		MC会话标识
[IN]		strFileID    	文件id
[IN]		strDeviceID     查询的设备ID
[IN]		stQueryFilter	查询条件
[IN]		pCallBack		查询结果回调函数指针
[IN]		dwCookie		用户COOKIE
[IN]		strQueryGuid	用户查询GUID，每次查询用户可以指定不同的查询GUID
[IN]		bSyncExec		异步模式查询
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：无
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetGrapFileById(IN const ISOC_LONGPTR lMCSession, IN const ISOC_STR strFileID,IN const ISOC_STR strDeviceID, IN ST_VodQueryFilter stQueryFilter,IN iSOC_GrabFileInfoCallback pCallback, IN ISOC_DWORDPTR dwCookie, IN ISOC_STR strQueryGuid = NULL, IN ISOC_BOOL bSyncExec = ISOC_TRUE);

/******************************************************************************************************************************
*函数名：iSOC_CreateDownloadFileSession
*功  能：创建文件下载会话标识
*参  数：
		 [IN OUT]	pLDownloadSession	文件下载会话标识
		 [IN]		lMCSession			mc会话标识
*返回值：调用成功返回大于0的值，失败返回小于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLDownloadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateDownloadFileSession(IN OUT ISOC_LONGPTR* pLDownloadSession,IN const ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*函数名：iSOC_AddDownloadFileItem
*功  能：创建文件下载项
*参  数：
		 [IN]		lDownloadSession	文件下载会话标识
		 [IN OUT]	pNItemIdx			文件id从0开始
		 [IN]		strDstFilePath		目标文件路径
		 [IN]		stFileInfo			文件信息
		 [IN]		strUserGUID			用户生成的guid
		 [IN]		strDes				文件描述信息
		 [IN]		dwReserved			保留参数

*返回值：调用成功返回大于0的值，失败返回小于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLDownloadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddDownloadFileItem(IN const ISOC_LONGPTR lDownloadSession,IN OUT ISOC_INT* pNItemIdx,IN const ISOC_STR strDstFilePath,IN ST_GrabFileInfo stFileInfo,IN const ISOC_STR strUserGUID = NULL,IN const ISOC_STR strDes = NULL,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_DelDownloadFileItem	
*功  能：删除文件下载项
*参  数：
		[IN]		lDownloadSession	文件下载会话标识
		[IN]		nItemIdx			文件id从0开始
		[IN]		dwReserved			保留参数
		 
*返回值：调用成功返回大于0的值，失败返回小于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLDownloadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelDownloadFileItem(IN const ISOC_LONGPTR lDownloadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_GetDownloadFileInfo
*功  能：获取文件下载信息
*参  数：
		[IN]		lDownloadSession	文件下载会话标识
		[IN]		nItemIdx			文件所属行id从0开始
		[IN OUT]	pFileInfo			文件信息
		[IN OUT]	pNFileStatus		文件当前下载状态
		[IN OUT]	pNProgress			文件下载进度
		[IN]		dwReserved			保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLDownloadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDownloadFileInfo(IN const ISOC_LONGPTR lDownloadSession,IN const ISOC_INT nItemIdx,IN OUT ST_GrabFileInfo *pFileInfo,IN OUT ISOC_INT* pNFileStatus,IN OUT ISOC_INT* pNProgress,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_StartDownloadFile
*功  能：开始启动文件下载
*参  数：	
		[IN]		lDownloadSession	文件下载会话标识
		[IN]		nItemIdx			文件所属行id从0开始
		[IN]		dwReserved			保留参数
		 
*返回值：调用成功返回大于0的值，失败返回小于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLDownloadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartDownloadFile(IN const ISOC_LONGPTR lDownloadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_StopDownloadFile
*功  能：停止文件下载
*参  数：
		 [IN]		lDownloadSession	文件下载会话标识
		 [IN]		nItemIdx			文件所属行id从0开始
		 [IN]		dwReserved			保留参数
*返回值：调用成功返回大于0的值，失败返回小于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLDownloadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopDownloadFile(IN const ISOC_LONGPTR lDownloadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_RegsiterDownloadFileStatusNotifyCallback
*功  能：注册文件下载状态回调
*参  数：
		[IN]		lDownloadSession	文件下载会话标识
		[IN]		pCallback			文件下载回调函数指针
		[IN]		dwUserCookie		用户cookie

*返回值：调用成功返回大于0的值，失败返回小于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLDownloadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegsiterDownloadFileStatusNotifyCallback(IN const ISOC_LONGPTR lDownloadSession,IN iSOC_DownloadFileStatusCallback pCallback,IN ISOC_DWORDPTR dwUserCookie);

/******************************************************************************************************************************
*函数名：iSOC_DownloadFileExtendFunc
*功  能：文件下载可扩展函数
*参  数：
		 [IN]		lDownloadSession	文件下载会话标识
		 [IN]		nExteydType			可扩展的类型
		 [IN]		dwExtendData		可扩展的数据信息
*返回值：调用成功返回大于0的值，失败返回小于0的值,如果调用失败可通过iSOC_GetLastErrorDes将pLDownloadSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DownloadFileExtendFunc(IN const ISOC_LONGPTR lDownloadSession,IN const ISOC_INT nExteydType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseDownloadFileSession
*功  能：销毁文件下载会话
*参  数：
		 [IN]	 lDownloadSession 文件下载会话
*返回值：调用成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseDownloadFileSession(IN ISOC_LONGPTR lDownloadSession);



////////////////////////////////////////////////文件删除模块接口定义///////////////////////////////////////////////////////////////////////////

/******************************************************************************************************************************
*函数名：iSOC_CreateDeleteFileSession
*功  能：创建删除文件会话
*参  数：
		[IN OUT]	lpDeleteSession	删除会话句柄
		[IN]		lMCSession		管理中心会话
		[IN]		pCallback		删除结果信息回调函数
		[IN]		dwUserCookie	用户COOKIE
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateDeleteFileSession(IN OUT ISOC_LONGPTR *lpDeleteSession,IN const ISOC_LONGPTR lMCSession,IN iSOC_DeleteFileNotifyCallback pCallback=NULL,IN ISOC_DWORDPTR dwUserCookie=0);


/******************************************************************************************************************************
*函数名：iSOC_DeleteFile
*功  能：删除已上传的和迁移的文件
*参  数：
		[IN]	lDeleteSession	删除会话句柄
		[IN]	stFileInfo		要删除的文件信息
		[IN]	dwReserved		保留字
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：异步处理方式，通过iSOC_CreateDeleteFileSession设置的回调函数返回删除结果信息。成功：nStatus=3，失败：nStatus=4，超时：nStatus=0(超时时间20S)
		 可多次调用此函数来删除不同的文件
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DeleteFile(IN const ISOC_LONGPTR lDeleteSession,IN const ST_VodFileInfo stFileInfo,IN ISOC_DWORDPTR dwReserved = 0);


/******************************************************************************************************************************
*函数名：iSOC_ReleaseDeleteFileSession
*功  能：销毁删除文件会话
*参  数：
		[IN]	lDeleteSession	删除会话句柄
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseDeleteFileSession(IN OUT ISOC_LONGPTR lDeleteSession);


////////////////////////////////////////////////文件迁移模块接口定义///////////////////////////////////////////////////////////////////////////

/******************************************************************************************************************************
*函数名：iSOC_CreateMigrateSession
*功  能：创建迁移会话标识
*参  数：
		 [IN]		lMCSession			MC会话标识
		 [IN OUT]	pMigrateSession		迁移会话标识指针
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateMigrateSession(IN ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pMigrateSession);

/******************************************************************************************************************************
*函数名：iSOC_AddMigrateTaskItem
*功  能：添加迁移任务
*参  数：
		 [IN]	lMigrateSession		迁移会话
		 [IN]	stVodFileInfo		VOD文件信息
		 [IN]	strDesc				迁移描述
		 [IN]	pStartTime			迁移文件开始时间，如果为空则为stVodFileInfo中的文件开始时间
		 [IN]	pEndTime			迁移文件结束时间，如果为空则为stVodFileInfo中的文件结束时间
		 [IN]	strUserGUID			用户GUID，用于用户标识文件，可以在VOD查询中查询出迁移时设置的GUID
		 [IN]	dwReserved			保留参数，设为0
*返回值：返回当前添加的本地任务ID值，即下面函数中的nTaskItemID
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddMigrateTaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ST_VodFileInfo stVodFileInfo,IN ISOC_STR strDesc,IN ISOC_SYSTEMTIME* pStartTime,IN ISOC_SYSTEMTIME* pEndTime,IN ISOC_STR strUserGUID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_GetMigrateTaskItemCount
*功  能：获取当前迁移会话中迁移任务的个数
*参  数：
		 [IN]	lMigrateSession		迁移会话
*返回值：返回当前迁移会话中的迁移任务个数
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMigrateTaskItemCount(IN const ISOC_LONGPTR lMigrateSession);

/******************************************************************************************************************************
*函数名：iSOC_GetMigrateTaskInfoByIndex
*功  能：通过迁移任务的脚标获取具体的任务信息
*参  数：
		 [IN]		lMigrateSession		迁移会话
		 [IN]		nIndex				任务脚标，从0开始到任务个数-1的范围
		 [IN OUT]	pInfo				迁移任务信息
*返回值：成功则返回大于0的值，不成功则返回小于0的值。如果失败可使用iSOC_GetLastErrorDes将lMigrateSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMigrateTaskInfoByIndex(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nIndex,IN OUT ST_MigrateInfo* pInfo);

/******************************************************************************************************************************
*函数名：iSOC_GetUnfinishedMigrateTaskInfoFromeServer
*功  能：获取当前系统中当前用户未完成迁移的所有迁移任务
*参  数：
		 [IN]	lMigrateSession		迁移会话
		 [IN]	pCallback			操作状态回调，如果获取成功会回调给调用者，然后使用iSOC_GetMigrateTaskItemCount和iSOC_GetMigrateTaskInfoByIndex去遍历迁移任务
		 [IN]	dwUserCookie		用户Cookie，在回调中传回
		 [IN]	dwReserved			保留参数
*返回值：成功则返回大于0的值，不成功则返回小于0的值。如果失败可使用iSOC_GetLastErrorDes将lMigrateSession传入获取失败描述
*备  注：此函数宜在最开始调用
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetUnfinishedMigrateTaskInfoFromeServer(IN const ISOC_LONGPTR lMigrateSession,IN iSOC_OperatorStateCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_DelMigrateTaskItem
*功  能：删除本地迁移任务
*参  数：
		 [IN]	lMigrateSession		迁移会话
		 [IN]	nTaskItemID			本地任务ID，如果为-1则表示所有任务
		 [IN]	dwReserved			保留参数
*返回值：成功则返回大于0的值，不成功则返回小于0的值。如果失败可使用iSOC_GetLastErrorDes将lMigrateSession传入获取失败描述
*备  注：此函数只适用于那些通过iSOC_AddMigrateTaskItem添加的还未开始的迁移任务，或者已经开始的通过iSOC_StopMigrateTaskItem
		 停止的任务。
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelMigrateTaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_StopMigrateTaskItem
*功  能：停止迁移任务
*参  数：
		 [IN]	lMigrateSession		迁移会话
		 [IN]	nTaskItemID			本地任务ID，如果为-1则表示所有任务
		 [IN]	dwReserved			保留参数
*返回值：成功则返回大于0的值，不成功则返回小于0的值。如果失败可使用iSOC_GetLastErrorDes将lMigrateSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopMigrateTaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_PauseMigrateTaskItem
*功  能：暂停迁移任务
*参  数：
		 [IN]	lMigrateSession		迁移会话
		 [IN]	nTaskItemID			本地任务ID，如果为-1则表示所有任务
		 [IN]	dwReserved			保留参数
*返回值：成功则返回大于0的值，不成功则返回小于0的值。如果失败可使用iSOC_GetLastErrorDes将lMigrateSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_PauseMigrateTaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_SetMigrateTaskItemSpeed
*功  能：设置迁移任务速度
*参  数：
		 [IN]	lMigrateSession		迁移会话
		 [IN]	nTaskItemID			本地任务ID，如果为-1则表示所有任务
		 [IN]	fMigrateSpeed		迁移速度，以KB为单位
*返回值：成功则返回大于0的值，不成功则返回小于0的值。如果失败可使用iSOC_GetLastErrorDes将lMigrateSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetMigrateTaskItemSpeed(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemID,IN ISOC_FLOAT fMigrateSpeed);

/******************************************************************************************************************************
*函数名：iSOC_StartMigrateTaskItem
*功  能：开始迁移任务
*参  数：
		 [IN]	lMigrateSession		迁移会话
		 [IN]	nTaskItemID			本地任务ID，如果为-1则表示所有任务
		 [IN]	dwReserved			保留参数
*返回值：成功则返回大于0的值，不成功则返回小于0的值。如果失败可使用iSOC_GetLastErrorDes将lMigrateSession传入获取失败描述
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartMigrateTaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*函数名：iSOC_ReleaseMigrateSession
*功  能：销毁迁移会话
*参  数：
		 [IN]	lMigrateSession		迁移会话
*返回值：成功则返回大于0的值，不成功则返回小于0的值
*备  注：销毁之后不能使用该会话进行操作
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseMigrateSession(IN const ISOC_LONGPTR lMigrateSession);

#ifdef __cplusplus
}
#endif
