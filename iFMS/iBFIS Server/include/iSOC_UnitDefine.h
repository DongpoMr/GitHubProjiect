#pragma once
#ifndef _ISOC_UNITDEFINE_H_
#define _ISOC_UNITDEFINE_H_

#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef _iSOC_SECURITY_SDK
#define iSOC_EXPORT_MODE  __declspec(dllexport)
#else
#define iSOC_EXPORT_MODE  __declspec(dllimport)
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif


enum StreamDataType {AUDIO_FRAME=1,VIDEO_FRAME,AUDIO_INFO,VIDEO_INFO, USER_DEFINEINFO};
enum OperatorType{OT_LOGIN,OT_STARTLIVESTREAM,OT_STARTVODSTREAM,OT_GOTLIVEADDR,
	OT_GOTVODADDR,OT_GOTGPSADDR,OT_PRESETPOSUPDATE,OT_M2DAUDIOTALK,OT_ALARM,OT_GROUPMANAGER,
	OT_PTZCONTROL,OT_MIGRATE,OT_EMAP,OT_SETTRANSPARENTDATA,OT_DELTRANSPARENTDATA, 
	OT_SETMONTAGE,OT_DISCONNECT,OT_RELOGIN,OT_ADDSUPERVISE,OT_UPDATESUPERVISE,OT_GETSUPERVISE, OT_DELSUPERVISE,
	OT_GPSCONTROL, OT_MATUPDATE, OT_RECORD,OT_VPUPROCESS,OT_SWITCHSERVER,OT_GRABFRAME};
enum OperatorState{OPERATOR_SUCCEEDED,OPERATOR_FAILED,OPERATOR_FINISHED,OPERATOR_UPDATE,OPERATOR_TIMEOUT};
enum MediaDataType{YV12,RGB24,RGB32,ARGB,RGBA,BGRA,DIB,DIB32,D3D9,D3D11};
enum LogType{LT_ALARM=1,LT_SYSTEM,LT_OPERATE,LT_INSPECTION};
enum TBOperatorType {
	TB_STARTTALK = 1, //开启对讲
	TB_HANG,		  //挂断
	TB_ANSWER,		  //接听对讲
	TB_VOLUMN,		  //设置声音
	TB_STATE,		  //状态
	TB_CALLIN,		  //呼入
	TB_BEGINTALK,	  //开始对讲
    BC_STARTBROADCAST//开启广播			//新增
};

enum TBState{
	ONLINE = 1,
	OFFLINE,
	NONE
};

enum RecordStatus
{
    BEGIN_WITHOUT_FILE = 1,     //录像任务已启动，但尚未写文件
    BEGIN_WITH_fILE                    //录像任务已启动，正在写入文件数据
};

//视频渲染模式定义
#define GDI_RENDER_MOD 0x01 //GDI渲染模式
#define DDRAW_RENDER_MOD 0x02 //DDraw渲染模式
#define D3D_RENDER_MOD 0x03 //D3D渲染模式

////音视频编码ID定义

#define ISOC_DEFINE_AUDIO_UNKNOW								0x0001 //未知音频格式
#define ISOC_DEFINE_AUDIO_G711U                                 0x0002 //G711U音频格式
#define ISOC_DEFINE_AUDIO_G711A                                 0x0010 //G711A音频格式
#define ISOC_DEFINE_AUDIO_AAC									0x0003 //AAC音频格式
#define ISOC_DEFINE_AUDIO_G726									0x0004 //G726音频格式
#define ISOC_DEFINE_AUDIO_MP3									0x0005 //MP3音频格式
#define ISOC_DEFINE_HIK_G722                                    0x0006 //海康私有G722音频格式
#define ISOC_DEFINE_HIK_G726                                    0x0016 //海康私有G726音频格式
#define ISOC_DEFINE_DAHUA_G711A                                 0x0008 //大华私有G711A音频格式
#define ISOC_DEFINE_AUDIO_PCM                                   0x000a //PCM音频格式
#define ISOC_DEFINE_AUDIO_G722									0x000b //G722音频格式
#define ISOC_DEFINE_AUDIO_G729									0x000c //G729音频格式
#define ISOC_DEFINE_AUDIO_G723_1								0x000d //G723.1音频格式
#define ISOC_DEFINE_AUDIO_ADPCM                                 0x000f //ADPCM音频格式
#define ISOC_DEFINE_AUDIO_AMR_NB								0x0011 //AMR-NB音频格式
#define ISOC_DEFINE_AUDIO_AMR_MB								0x0012 //AMR-MB音频格式

#define ISOC_DEFINE_VIDEO_UNKNOW								0x0008 //未知视频格式
#define ISOC_DEFINE_VIDEO_JPEG									0x0010 //JPEG视频格式(Motion JPEG)
#define ISOC_DEFINE_HIK_JPEG									0x0011 //海康私有JPEG视频格式
#define ISOC_DEFINE_DAHUA_JPEG									0x0012 //大华私有JPEG视频格式
#define ISOC_DEFINE_YAAN_JPEG									0x0013 //亚安私有JPEG视频格式
#define ISOC_DEFINE_HANBANG_JPEG								0x0014 //汉邦私有JPEG视频格式
#define ISOC_DEFINE_HUAMAI_JPEG									0x0016 //华迈私有JPEG视频格式
#define ISOC_DEFINE_VIDEO_MJPEGB								0x0015 //MJPEG-B视频格式
#define ISOC_DEFINE_VIDEO_MPEG4									0x0020 //MPEG4视频格式
#define ISOC_DEFINE_HIK_MPEG4									0x0021 //海康私有MPEG4视频格式
#define ISOC_DEFINE_DAHUA_MPEG4									0x0022 //大华私有MPEG4视频格式
#define ISOC_DEFINE_YAAN_MPEG4									0x0023 //亚安私有MPEG4视频格式
#define ISOC_DEFINE_VIDEO_MPEG2									0x0040 //MPEG2视频格式
#define ISOC_DEFINE_HIK_MPEG2									0x0041 //海康私有MPEG2视频格式
#define ISOC_DEFINE_VIDEO_H264									0x0080 //H264视频格式
#define ISOC_DEFINE_HIK_H264									0x0081 //海康私有H264视频格式
#define ISOC_DEFINE_DAHUA_H264									0x0082 //大华私有H264视频格式
#define ISOC_DEFINE_YAAN_H264									0x0083 //亚安私有H264视频格式
#define ISOC_DEFINE_HUAMAI_H264									0x0084 //华迈私有H264视频格式
#define ISOC_DEFINE_VIDEO_MSMPEG4V1								0x0090 //MSMPEG4-V1视频格式
#define ISOC_DEFINE_VIDEO_MSMPEG4V2								0x0091 //MSMPEG4-V2视频格式
#define ISOC_DEFINE_VIDEO_MSMPEG4V3								0x0092 //MSMPEG4-V3视频格式
#define ISOC_DEFINE_VIDEO_WMV1									0x0093 //WMV1视频格式
#define ISOC_DEFINE_VIDEO_WMV2									0x0094 //WMV2视频格式
#define ISOC_DEFINE_VIDEO_MEGAEYES								0x0095//天翼视频格式
#define ISOC_DEFINE_AUDIO_MEGAEYES								0x0096//天翼音频格式
#define ISOC_DEFINE_VIDEO_VNMPGAEYES							0x0099//江苏长天智远视频格式
#define ISOC_DEFINE_AUDIO_VNMPGAEYES							0x009a//江苏长天智远音频格式
#define ISOC_DEFINE_VIDEO_H265      							0x009c 

#define ISOC_DEFINE_VIDEO_SVAC									0x009b //SVAC标准视频格式
#define ISOC_DEFINE_VIDEO_YUV									0x009d //解码后的YUV数据格式

////////////////////权限码值定义/////////////////////////////////
//系统权限码
#define ISOC_SYS_AUT_BASE				0x0601		//基本设置
#define ISOC_SYS_AUT_LOCALKINPLAN		0x0602		//本地录像计划表设置
#define ISOC_SYS_AUT_GROUPSURVEY		0x0603		//分组轮巡

#define ISOC_SYS_AUT_LIVEVIDEO			0x0651		//视频预览
#define ISOC_SYS_AUT_STARTRECORD		0x0652		//启停录像
#define ISOC_SYS_AUT_ADDTAG				0x0653		//添加标签
#define ISOC_SYS_AUT_VODVIDEO			0x0654		//检索回放
#define ISOC_SYS_AUT_LOGRETRIEVAL		0x0655		//日志查询
#define ISOC_SYS_AUT_MATRIX				0x0656		//电视墙
#define ISOC_SYS_AUT_EMAPBROWER			0x0657		//电子地图浏览
#define ISOC_SYS_AUT_VIDEOTRANSFER		0x0658		//视频迁移
#define ISOC_SYS_AUT_EVIDENCINFOVIEW	0x0659		//取证资料查看(取证视频点播、编目信息查看)
#define ISOC_SYS_AUT_EVIDENCINFODELETE	0x066A		//取证资料删除

//子设备权限码
#define ISOC_SUBEQU_AUT_LIVEVIDEO		0x0701		//实时视频监看
#define ISOC_SUBEQU_AUT_VOD				0x0702		//VOD历史回放
#define ISOC_SUBEQU_AUT_VIDEODOWNLOAD	0x0703		//视频下载（导出）
#define ISOC_SUBEQU_AUT_VOICELISTEN		0x0704		//语音监听
#define ISOC_SUBEQU_AUT_VOICETALK		0x0705		//语音对讲
#define ISOC_SUBEQU_AUT_DEFENCE			0x0751		//布防/撤防
#define ISOC_SUBEQU_AUT_MAPVIDEOVIEW	0x0707		//地图视频监看
#define ISOC_SUBEQU_AUT_PTZCONTROL		0x0741		//云台控制权限
#define	ISOC_SUBEQU_AUT_TRIGGERALARM	0x0752		//触发、停止报警
#define ISOC_SUBEQU_AUT_CANCELALARM		0x0753		//取消报警
#define	ISOC_SUBEQU_AUT_WATCHALARMVIDEO 0x0754		//观看报警录像
#define ISOC_SUBEQU_AUT_OUTPUTCONTROL	0x0771		//开启、关闭输出
////////////////////////////////////////////////////

/******************************************************************************************************************************
*函数名：iSOC_StreamDataCallback
*功  能：解码前数据流回调函数
*参  数：
		 dwCookie 用户Cookie，在设置回调函数指针的时候由用户设置的
		 enDataType 流数据类型枚举
		 pData 流数据，当enDataType为AUDIO_FRAME时，pData为音频数据；当enDataType为VIDEO_FRAME时，pData为视频数据；
			   当enDataType为AUDIO_INFO时，pData为ST_AudioInfo结构体指针，返回音频相关信息；
			   当enDataType为VIDEO_INFO时，pData为ST_VideoInfo结构体指针，返回视频相关信息
	     dataLen pData所指向的数据长度
		 pts 对应流数据的时间戳，单位为ms即10-E6秒
		 nFrameFlag 帧类型标识1:I帧,2:B帧,3:P帧
		 pPrivateData 私有数据
		 nPriLen 私有数据长度 
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_StreamDataCallback
typedef ISOC_INT (__stdcall *iSOC_StreamDataCallback)(const ISOC_DWORDPTR dwCookie,StreamDataType enDataType,ISOC_BYTE* pData,ISOC_INT dataLen
													  ,ISOC_UINT64 pts,ISOC_INT nFrameFlag,ISOC_BYTE* pPrivateData,ISOC_INT nPriLen);
#endif

/******************************************************************************************************************************
*函数名：iSOC_MediaDataCallback
*功  能：解码后数据回调
*参  数：
		 dwCookie 用户Cookie，在设置回调函数指针的时候由用户设置的
		 enDataType 解码后数据类型
		 pFrame 解码后视频数据
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_MediaDataCallback
typedef ISOC_INT (__stdcall *iSOC_MediaDataCallback)(const ISOC_DWORDPTR dwCookie,MediaDataType enDataType,ST_VideoFrame* pFrame);
#endif

/******************************************************************************************************************************
*函数名：iSOC_MediaDataCallbackEx
*功  能：解码后数据回调
*参  数：
        dwCookie   用户Cookie，在设置回调函数指针的时候由用户设置的
        pts        当前帧时间戳
        enDataType 解码后数据类型
        pFrame     解码后视频数据
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_MediaDataCallbackEx
typedef ISOC_INT(__stdcall *iSOC_MediaDataCallbackEx)(const ISOC_DWORDPTR dwCookie, ISOC_UINT64 pts, MediaDataType enDataType, ST_VideoFrame* pFrame);
#endif

/******************************************************************************************************************************
*函数名：iSOC_AudioSpectrumCallback
*功  能：音频谱值回调
*参  数：
		lSession 设置回调函数的Session值
		dwCookie 用户Cookie，在设置回调函数指针的时候由用户设置的
		dbAudioSpecValue 音频谱的值，范围为[-60,0]
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_AudioSpectrumCallback
typedef ISOC_INT(__stdcall *iSOC_AudioSpectrumCallback)(const ISOC_LONGPTR lSession,const ISOC_DWORDPTR dwCookie, ISOC_DOUBLE dbAudioSpecValue);
#endif

/******************************************************************************************************************************
*函数名：iSOC_DeviceInfoChangedCallback
*功  能：设备信息变更回调
*参  数：
		 dwCookie 用户Cookie，在设置回调函数指针的时候由用户设置的
		 stDeviceInfo 变更的设备信息
		 dwReserved 保留参数
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_DeviceInfoChangedCallback
typedef ISOC_INT (__stdcall *iSOC_DeviceInfoChangedCallback)(const ISOC_DWORDPTR dwCookie,ST_DeviceItem stDeviceInfo,ISOC_DWORDPTR dwReserved);
#endif

/******************************************************************************************************************************
*函数名：iSOC_PermissionChangedCallback
*功  能：设备权限信息变更回调
*参  数：
		 dwCookie 用户Cookie，在设置回调函数指针的时候由用户设置的
		 nPermissionType 标识为系统权限还是设备权限，为1时为系统权限，为2时为设备权限
		 nChengedType 变更类型。0:添加,1:修改,2:删除
		 stDeviceInfo 变更的设备信息，当nPermissionType标识为系统权限时，此参数无用
		 dwReserved 保留参数
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_PermissionChangedCallback
typedef ISOC_INT (__stdcall *iSOC_PermissionChangedCallback)(const ISOC_DWORDPTR dwCookie,const ISOC_INT nPermissionType,const ISOC_INT nChengedType,ST_DeviceItem stDeviceInfo,ISOC_DWORDPTR dwReserved);
#endif

/******************************************************************************************************************************
*函数名：iSOC_OperatorStateCallback
*功  能：操作状态回调
*参  数：
		 enState 操作状态枚举
		 nOperatorType 操作类型，是OperatorType中的一个值
		 strDes 操作描述
		 dwCookie 用户设置的Cookie
		 dwResevered 保留参数
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_OperatorStateCallback
typedef ISOC_INT (__stdcall *iSOC_OperatorStateCallback)(const OperatorState enState,const ISOC_INT nOperatorType,const ISOC_STR strDes,const ISOC_DWORDPTR dwCookie,ISOC_DWORDPTR dwResevered);
#endif

/******************************************************************************************************************************
*函数名：iSOC_OnGotOnlineClientInfoCallback
*功  能：操作状态回调
*参  数：
		 dwCookie 用户Cookie
		 strIPAddr 客户端IP地址
		 uPort 客户端端口号（暂时没用）
		 strUserName 登录用户名
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_OnGotOnlineClientInfoCallback
typedef ISOC_INT (__stdcall *iSOC_OnGotOnlineClientInfoCallback)(ISOC_DWORDPTR dwCookie,const ISOC_STR strIPAddr,const ISOC_UINT uPort,const ISOC_STR strUserName);
#endif

/******************************************************************************************************************************
*函数名：iSOC_VodFileInfoCallback
*功  能：获取VOD文件信息回调
*参  数：
		 vodFileInfo VOD文件信息结构体	
		 dwCookie 用户设置的Cookie
		 strQueryGUID 用户查询时传入的GUID
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_VodFileInfoCallback
typedef ISOC_INT (__stdcall *iSOC_VodFileInfoCallback)(const ST_VodFileInfo vodFileInfo,const ISOC_DWORDPTR dwCookie,const ISOC_STR strQueryGUID);
#endif

/******************************************************************************************************************************
*函数名：iSOC_GrabFileInfoCallback
*功  能：获取抓帧文件信息回调
*参  数：
		 grabFileInfo 抓帧文件信息结构体
		 dwCookie 用户设置的Cookie
		 strQueryGUID 用户查询时传入的GUID
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_GrabFileInfoCallback
typedef ISOC_INT (__stdcall *iSOC_GrabFileInfoCallback)(const ST_GrabFileInfo grabFileInfo,const ISOC_DWORDPTR dwCookie,const ISOC_STR strQueryGUID);
#endif

/******************************************************************************************************************************
*函数名：iSOC_VodFileTagInfoCallback
*功  能：获取标签信息回调
*参  数：
		 tagInfo  标签信息结构体
		 dwCookie 用户设置的Cookie
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_VodFileTagInfoCallback
typedef ISOC_INT (__stdcall *iSOC_VodFileTagInfoCallback)(const ST_TagInfo tagInfo,const ISOC_DWORDPTR dwCookie);
#endif

/******************************************************************************************************************************
*函数名：iSOC_WhenOnGotAlarmEventCallback
*功  能：报警事件回调
*参  数：
		 dwCookie 用户设置的Cookie
		 dwEventType 事件类型
		 pXmlContext 事件的xml内容
		 nXmlLen 事件内容长度
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_WhenOnGotAlarmEventCallback
typedef int (__stdcall *iSOC_WhenOnGotAlarmEventCallback)(ISOC_DWORDPTR dwCookie,ISOC_DWORD dwEventType,const ISOC_STR pXmlContext,ISOC_INT nXmlLen);
#endif

/******************************************************************************************************************************
*函数名：iSOC_OnGotDataCallback
*功  能：接收到信令数据时回调
*参  数：
		 dwUserCookie 用户Cookie
		 fromAddr 发送数据的服务器地址
		 pData 具体数据
		 dataLen 数据长度
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_OnGotDataCallback
typedef int (__stdcall *iSOC_OnGotDataCallback)(ISOC_DWORDPTR dwUserCookie,ISOC_UINT64 fromAddr,ISOC_BYTE* pData,ISOC_INT dataLen);
#endif

/******************************************************************************************************************************
*函数名：iSOC_OnAffairOverTimeCallback
*功  能：接收信令超时的回调
*参  数：
		 dwUserCookie 用户Cookie
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_OnAffairOverTimeCallback
typedef int (__stdcall *iSOC_OnAffairOverTimeCallback)(ISOC_DWORDPTR dwUserCookie);
#endif

/******************************************************************************************************************************
*函数名：iSOC_PresetPosInfoCallback
*功  能：预置点信息更新回调
*参  数：
		 nFlage 操作标识，0表示添加，1表示修改，2表示删除
		 dwCookie 用户Cookie
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_PresetPosInfoCallback
typedef ISOC_INT (__stdcall *iSOC_PresetPosInfoCallback)(ISOC_INT nFlage,const LPST_PRESETPOSINFO lpPresetPosInfo,ISOC_DWORDPTR dwCookie);
#endif

/******************************************************************************************************************************
*函数名：iSOC_TourInfoCallback
*功  能：巡航信息更新回调
*参  数：
		nFlags操作标识，0表示添加，1表示修改，2表示删除
		 dwCookie 用户Cookie
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_TourInfoCallback
typedef ISOC_INT (__stdcall *iSOC_TourInfoCallback)(ISOC_INT nFlage,const LPST_TOURINFO lpTourInfo,ISOC_DWORDPTR dwCookie);
#endif


/******************************************************************************************************************************
*函数名：iSOC_DeleteFileNotifyCallback
*功  能：删除文件信息回调
*参  数：
		 nFileID	表示文件id
		 nDeleteStatus删除文件状态 0表示超时，3表示完成，4表示失败
		 dwUserCookie 用户Cookie

*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_DeleteFileNotifyCallback
typedef ISOC_INT (__stdcall *iSOC_DeleteFileNotifyCallback)(ISOC_ID nFileID,ISOC_INT nDeleteStatus,ISOC_DWORDPTR dwUserCookie);
#endif

/******************************************************************************************************************************
*函数名：iSOC_OnRecvServerTimeCallback
*功  能：服务器时间更新回调
*参  数：
		 lMCSession	MC会话标识
		 dwUserCookie	用户Cookie
		 stServerTime	服务器时间

*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_OnRecvServerTimeCallback
typedef ISOC_INT (__stdcall *iSOC_OnRecvServerTimeCallback)(IN const ISOC_LONGPTR lMCSession,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_SYSTEMTIME stServerTime);
#endif


/******************************************************************************************************************************
*函数名：iSOC_FileLockInfoCallback
*功  能：文件锁查询回调
*参  数：
		 dwCookie 用户Cookie
		 nInfoType 信息类型，可以取以下值：当为1时pInfo为锁信息ST_FileLockInfo指针，当为2时为锁内的文件信息ST_FileLockItem指针,为3的时候表示一个完整的锁信息完成
		 nInfoLen 信息指针所对应的信息长度
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_FileLockInfoCallback
typedef ISOC_INT (__stdcall *iSOC_FileLockInfoCallback)(ISOC_DWORDPTR dwCookie,ISOC_INT nInfoType,ISOC_BYTE* pInfo,ISOC_INT nInfoLen);
#endif

/******************************************************************************************************************************
*函数名：iSOC_FileMigrateInfoCallback
*功  能：迁移任务查询回调
*参  数：
		 dwCookie   用户Cookie
		 nInfoType 信息类型，可以取以下值：当为1时pInfo为锁信息ST_MigrateInfo指针，当为2时为锁内的文件信息ST_MigrateItem指针,当为1时
				    strCatalogInfo和nCatalogLen有效,当为3时表一个一完整的迁移任务信息回调完成
		 pInfo	   信息相关信息
		 nInfoLen       信息指针所对应的信息长度
		 strCatalogInfo 编目信息
		 nCatalogLen	编目信息长度
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_FileMigrateInfoCallback
typedef ISOC_INT (__stdcall *iSOC_FileMigrateInfoCallback)(ISOC_DWORDPTR dwCookie,ISOC_INT nInfoType,ISOC_BYTE* pInfo,ISOC_INT nInfoLen,const ISOC_STR strCatalogInfo,ISOC_INT nCatalogLen);
#endif

/******************************************************************************************************************************
*函数名：iSOC_OnGotTransparentDataInfoCallback
*功  能：透明数据回调
*参  数：
		 dwCookie 用户Cookie
		 strContent 透明数据内容
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_OnGotTransparentDataInfoCallback
typedef ISOC_INT (__stdcall *iSOC_OnGotTransparentDataInfoCallback)(ISOC_DWORDPTR dwCookie,ISOC_STR strKey,ISOC_INT nDataArea,const ISOC_STR strContent);
#endif


/******************************************************************************************************************************
*函数名：iSOC_OnGotUnconfirmedAlarmInfoCallback
*功  能：未处理报警回调
*参  数：
		 dwCookie 用户Cookie
		 strContent 透明数据内容
		 nTransparentDataID 透明数据ID
*返回值：
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_OnGotUnconfirmedAlarmInfoCallback
typedef ISOC_INT (__stdcall *iSOC_OnGotUnconfirmedAlarmInfoCallback)(ISOC_DWORDPTR dwCookie,ST_UntreadedAlarmInfo AlarmInfo);
#endif

/****************************
*函数名	:iSOC_OnGotSuperviseCallback
*功能   :监察事件回调
*参数	:
		enState		    :操作状态枚举
		enType			:操作类型枚举
		pstSuperviseInfo:监察事件信息
		dwCookie 	    :用户数据
*返回值
*备注
*****************************/
#ifndef iSOC_SuperviseCallback
typedef ISOC_INT (__stdcall *iSOC_SuperviseCallback)(const OperatorState enState,const OperatorType enType, const ST_SuperviseItem* pstSuperviseInfo, const ISOC_DWORDPTR dwCookie);
#endif 

/****************************
*函数名	:iSOC_TalkbackCallback
*功能   :对讲事件回调
*参数	:
		enType		  :操作类型枚举 
		enOState	  :操作状态枚举
		enState	      :设备状态
		pDevData 	  :设备信息
		dwCookie 	  :用户数据
*返回值
*备注
*****************************/
#ifndef iSOC_TalkbackCallback
typedef ISOC_INT (__stdcall *iSOC_TalkbackCallback)(const TBOperatorType enType, const OperatorState enOState,
					const TBState enState,	//当操作类型不为STATE时，该值默认为NONE							
					const ST_DevicePluginItem* pDevData, 	//当有终端发起对讲时，通过该结构体来确认发起终端
					const ISOC_DWORDPTR dwCookie);
#endif

/****************************
*函数名	:iSOC_OnGotGPSDataCallback
*功能   :获取GPS数据回调
*参数	:
		lIcmsId		  :域子设备ID 
		strIcmsSign	  :子设备所在的域标识
		pData	      :GPS坐标信息
		nDataLen 	  :坐标信息长度
		pPrivateData  :私有数据
		nPrivateDataLen:私有数据长度
		dwCookie 	  :用户数据
*返回值
*备注
*****************************/
#ifndef iSOC_OnGotGPSDataCallback
typedef ISOC_INT (__stdcall *iSOC_OnGotGPSDataCallback)(ISOC_ID lIcmsId, ISOC_CHAR strIcmsSign[64], \
	const ISOC_BYTE* pData, ISOC_INT nDataLen, \
	const ISOC_BYTE* pPrivateData, ISOC_INT nPrivateDataLen, \
	ISOC_DWORDPTR dwCookie);
#endif

/******************************************************************************************************************************
*iSOC_GrabStatusCallback
*功  能：抓帧状态回调
*参  数：
[IN]		status				操作状态
[IN]		grabTime			抓帧时间
[IN]		dwCookie			用户数据
[IN]		dwReserved			保留字
*返回值：调用成功返回大于0的值，失败返回小于0的值，失败后可调用iSOC_GetLastErrorDes获取错误描述
*备  注：
******************************************************************************************************************************/
#ifndef iSOC_GrabStatusCallback
typedef ISOC_INT(__stdcall *iSOC_GrabStatusCallback)(const OperatorState status, const ISOC_SYSTEMTIME grabTime
    , const ISOC_DWORDPTR dwCookie, IN ISOC_DWORDPTR dwReserved);
#endif

#ifndef iSOC_RecordQueryCallback
typedef ISOC_INT(__stdcall *iSOC_RecordQueryCallback)(const OperatorState status, const ST_DeviceItem* deviceInfo, ISOC_INT nRecordType, RecordStatus enStatus, const ISOC_DWORDPTR dwCookie);
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#endif