#pragma once
#include "iSOC_Datatype_Define.h"

//////////////////////////////////////
//对象类型定义
//////////////////////////////////////

////////////////////////////监控客户端////////////////////////////////////////////////

#define OBJECT_TYPE_FACTORY				(1)		//工厂对象
#define OBJECT_TYPE_ORGAN_SET			(5)		//组织机构对象
#define OBJECT_TYPE_MCSERVERPEER		(6)		//管理中心源对象
#define	OBJECT_TYPE_RIGHT_JUDGE			(7)		//权限判断对象
#define OBJECT_TYPE_CALLBACK_MANAGER	(8)		//回调管理对象
#define OBJECT_TYPE_NORMAL_STRUCT		(9)		//一般结构体对象
#define OBJECT_TYPE_THREAD				(10)	//线程对象
#define	OBJECT_TYPE_THREADPOOL			(11)	//线程池对象
#define OBJECT_TYPE_ALARMSERVERPEER		(12)	//报警服务器源对象
#define OBJECT_TYPE_VODFILEMANAGEMENT	(13)	//VOD文件管理对象
#define	OBJECT_TYPE_VIDEORENDER			(14)    //视频渲染对象
#define OBJECT_TYPE_AUDIORENDER			(15)    //音频渲染对象
#define OBJECT_TYPE_VIDEOCODEC			(16)    //视频编解码器对象
#define OBJECT_TYPE_VIDEODECODE			(17)    //视频解码器对象
#define OBJECT_TYPE_VIDEOENCODE			(18)	//视频编码器对象
#define OBJECT_TYPE_AUDIOCODEC			(19)	//音频编解码器对象
#define OBJECT_TYPE_AUDIODECODE			(20)	//音频解码器对象
#define OBJECT_TYPE_AUDIOENCODE			(21)	//音频编码器对象
#define OBJECT_TYPE_TIMER				(22)	//定时器对象
#define OBJECT_TYPE_REALSTREAMSOURCE	(23)	//实时流源对象
#define OBJECT_TYPE_VODSTREAMSOURCE		(24)	//VOD流源对象
#define OBJECT_TYPE_MAPSOURCE			(25)	//地图管理源对象
#define OBJECT_TYPE_EMAPSOURCE			(26)	//电子地图管理源对象 
#define OBJECT_TYPE_GISSOURCE			(27)	//gis管理源对象
#define OBJECT_TYPE_REALSTATION			(28)	//实时Station对象
#define OBJECT_TYPE_VODSTATION			(29)	//VOD station对象
#define OBJECT_TYPE_FILEEXPORT			(30)	//文件导出对象
#define OBJECT_TYPE_FILEMIGRATESOURCE	(31)	//文件迁移源对象
#define OBJECT_TYPE_DATALIST			(32)	//数据链表管理对象
#define OBJECT_TYPE_DEVICEAUDIOTALK		(33)	//设备语音对讲对象
#define OBJECT_TYPE_MONITORAUDIOTALK	(34)	//客户端语音对讲对象
#define OBJECT_TYPE_DBOPERATOR			(35)	//持久化对象
#define OBJECT_TYPE_FILEUPLOAD			(36)	//文件上传对象
#define	OBJECT_TYPE_FILEDOWNLOAD		(37)	//文件下载对象
#define OBJECT_TYPE_M2DTALKSOURCE		(38)	//设备对讲源对象
#define OBJECT_TYPE_M2MTALKSOURCE		(39)	//客户端对讲源对象
#define OBJECT_TYPE_VODFILEQUERYSOURCE	(40)	//VOD查询源对象
#define OBJECT_TYPE_HSFILEMANAGEMENT	(41)	//高速文件管理对象
#define OBJECT_TYPE_PTZCONTROL			(42)	//PTZ控制对象
#define	OBJECT_TYPE_FILEDELETE			(43)	//文件删除对象
#define OBJECT_TYPE_FILEMIGRATESTATION  (44)	//文件迁移业务对象
#define OBJECT_TYPE_SYSTEMVOLUMECONTROL (45)	//系统音量控制对象，包含输入音量和输出音量
#define OBJECT_TYPE_PRESETCREISESOURCE	(46)	//巡航预置点管理源对象
#define OBJECT_TYPE_MEDIADATAPROCESSOR	(47)	//媒体数据处理器
#define OBJECT_TYPE_GROUPLOOPMANAGER	(48)	//分组轮巡管理对象
#define OBJECT_TYPE_GLOBALLASTERROR		(49)	//全局错误描述对象
#define OBJECT_TYPE_MATRIXCONTROLSTATION (50)	//电视墙控制业务对象
#define OBJECT_TYPE_MATRIXCONTROLSOURCE	(51)	//电视墙控制源对象
#define OBJECT_TYPE_FILEEXPORTSOURCE	(55)	//文件导出源对象
#define OBJECT_TYPE_SERVERTYPE_AUTO_IDENTIFIER	(100)	//服务器类型自动识别对象
#define OBJECT_TYPE_LINEAR				(101)	//缩放类对象
#define OBJECT_TYPE_D3DMANAGER			(102)	//D3D对象管理对象（整个应用程序只能有一个D3D对象，所以要使用此对象管理供其它地方用）
#define OBJECT_TYPE_CODEINFOSTATION		(103)//获取编码格式对象
#define OBJECT_TYPE_CODEINFOSOURCE		(104)//获取编码格式源对象
#define OBJECT_TYPE_FILEMIGRATESTATIONV2 (108) //按照任务迁移的新的迁移接口对象
#define OBJECT_TYPE_FILEMIGRATESOURCEV2	 (109) //按照任务迁移的新的迁移源接口对象
#define OBJECT_TYPE_FILELOCKMANAGER		(110) //文件锁定管理对象
#define OBJECT_TYPE_FILEMIGRATEMANSOURCE (111) //文件迁移管理源对象
#define OBJECT_TYPE_IMAGE_TRANSFORM     (112)   //图像操作对象
#define OBJECT_TYPE_FFMPEGCODECMAN		(113) //FFMPEG Codec管理对象
#define OBJECT_TYPE_NETWORKMONITOR		(114) //网络监控对象
#define OBJECT_TYPE_TTSSTATION			(115) //读文字业务对象
#define OBJECT_TYPE_SUPERVISESTATION	(116)	//监察管理station对象
#define OBJECT_TYPE_DEVICECONTAINER		(117)   //设备容器对象
#define OBJECT_TYPE_TALKBACKSTATION		(118)	//对讲管理station对象
#define OBJECT_TYPE_SUPERVISESOURCE		(119)	//监察管理源对象

////////////////////////////////////管理客户端///////////////////////////////////

#define OBJECT_TYPE_MANMCSOURCE			(10001)    //管理中心源
#define OBJECT_TYPE_MANSYSSETSOURCE		(10002)	//系统设置源
#define OBJECT_TYPE_MANSYSSETSTATION	(10003)	//系统设置业务对象


////////////////////////////////////电视墙相关////////////////////////////////////

#define OBJECT_TYPE_MATRIXINFOMAN				(20088) //电视墙服务器信息管理对象
#define OBJECT_TYPE_MATRIXINFOMAN_V2			(20089) //新电视墙服务器信息管理对象，不再兼容以前的电视墙管理模式，若要兼容则使用以前的电视墙管理对象

////////////////////////////////////电视墙服务器/////////////////////////////////
#define OBJECT_TYPE_TVWALL_LIVECTRLSTATION		(20001) //电视墙服务器实时控件业务对象
#define OBJECT_TYPE_TVWALL_MAPCTRLSTATION		(20002) //电视墙服务器地图控件业务对象
#define OBJECT_TYPE_TVWALL_DATARECVSTATION		(20003) //电视墙服务器数据接收业务对象
#define OBJECT_TYPE_TVWALL_MATRIXCTRLSOURCE		(20004)	//电视墙服务器数据操控业务对象
#define OBJECT_TYPE_TVWALL_WINDOWMANAGERSOURCE	(20005) //电视墙服务器窗口控件业务对象
#define OBJECT_TYPE_TVWALL_WINDOWSFRAMESTATION  (20006) //电视墙服务器窗口框架业务对象
#define OBJECT_TYPE_TVWALL_MONITOROUTPUTMANAGER (20007) //电视墙服务器监视器输出管理对象

///////////////////////////////////大屏控制服务器相关////////////////////////////////
#define OBJECT_TYPE_DCSSERVER_TASK_MANAGER		               (40002) //大屏控制服务器任务管理业务对象
#define OBJECT_TYPE_DCSSERVER_STATIONMANAGER		           (40005) //业务管理对象

///////////////////////////////////大屏控制SDK相关////////////////////////////////////

#define OBJECT_TYPE_DCS_DATA_SOURCE				(30000) //大屏数据源对象
#define OBJECT_TYPE_DCS_SOURCE					(30001) //大屏控制源对象
#define OBJECT_TYPE_DCS_CONTROL_STATION			(30002) //大屏控制业务对象
#define OBJECT_DES_DCS_DATA_TYPE				"MySQL" //用于实时即时回放的文件描述

///////////////////////////////////设备插件SDK相关////////////////////////////////////
#define OBJECT_TYPE_DEVICEPLUGIN_TALKBACK			(400001) //IP对讲设备插件对象
///////////////////////////////////BFIS Sync相关////////////////////////////////////
#define OBJECT_TYPE_BFIS_DISPLAY_LOG_STATION			(600001)	//日志显示对象
#define OBJECT_TYPE_BFISSYNC_SERVER						(600002)	//同步服务器对象
#define OBJECT_TYPE_BFISSYNC_CLIENT						(600003)	//同步客户端
#define OBJECT_TYPE_BFISSYNC_DBOPERATORSOURCE			(600004)	//同步系统数据库对象
#define OBJECT_TYPE_BFISSYNC_LISTENSERVER               (600005)    //服务端监听对象
//////////////////////////////////BFIS Server相关/////////////////////////////////////
#define OBJECT_TYPE_BFISSERVER_DBOPERATORSOURCE			(700001)	//服务端对数据库操作对象
#define OBJECT_TYPE_BFISSERVER_CLIENTSOURCE				(700002)	//服务端对客户端操作对象	
#define OBJECT_TYPE_BFISSERVER_CACHESOURCE				(700003)	//服务端对缓存操作对象
#define OBJECT_TYPE_BFIS_CLIENTCOMMUNICATION			(700004)	//服务端与客户端通信对象
#define OBJECT_TYPE_BFIS_COMMUNICATESYNCSERVER			(700005)	//与服务端同步服务器服务端通信的对象
#define OBJECT_TYPE_BFIS_TASKMANAGER					(700006)	//服务器任务管理器 
#define OBJECT_TYPE_BFIS_NOTIFYSOURCE					(700007)	//通知对象
#define OBJECT_TYPE_BFISSERVER_MIGRATETASKSTATION       (700008)    //迁移管理对象
#define OBJECT_TYPE_BFISSERVER_NOTIFICATIONSTATION      (700009)    //通知管理对象
#define OBJECT_TYPE_BFISSERVER_MCOPERATESTATION         (700010)    //MC操作对象
#define OBJECT_TYPE_BFISSERVER_SERIALIZEDATAMEMORY      (700011)    //服务器序列化数据管理(内存方式)
//////////////////////////////////BFIS SDK相关/////////////////////////////////////
#define OBJECT_TYPE_BFIS_BASE_STATION					(800001)	//基本业务Station
#define OBJECT_TYPE_BFIS_BASE_SOURCE					(800002)	//基本业务Source
#define OBJECT_TYPE_BFIS_BASE_PLUGIN					(800003)	//基本插件


//////////////////////////////////////对象类型描述定义//////////////////////////////////////
#define OBJECT_DES_DEVICEPLUGIN_TALKBACK_SPON		"SPON"	//世邦对讲设备插件描述


//////////////////////////////////////监控客户端///////////////////////////////////////////////////////

#define OBJECT_DES_RENDER_D3D			"D3D_RENDER"    //d3d渲染描述
#define OBJECT_DES_RENDER_GDI			"GDI_RENDER"	//GDI渲染描述
#define OBJECT_DES_RENDER_DDRAW			"DDRAW_RENDER"	//ddraw渲染描述

#define OBJECT_DES_DECODE_SH264			"SH264_DECODE"	//标准h264解码描述
#define OBJECT_DES_DECODE_SMJPEG		"SMJPEG_DECODE"	//标准MJPEG解码描述
#define OBJECT_DES_DECODE_SMPEG4		"SMPEG4_DECODE"	//标准MPEG4解码描述
#define OBJECT_DES_DECODE_HKVISSION		"HKVISSION_DEOCDE"	//海康私有格式解码描述
#define OBJECT_DES_DECODE_DAHUA			"DAHUA_DECODE"	//大华私有格式解码描述
#define OBJECT_DES_DECODE_G711			"G711_DECODE"	//G711音频数据解码描述
#define OBJECT_DES_DECODE_G726			"G726_DECODE"	//G726音频数据解码描述

#define OBJECT_DES_ENCODE_SH264			"SH264_ENCODE"	//标准h264编码描述
#define OBJECT_DES_ENCODE_SMJPEG		"SMJPEG_ENCODE"	//标准MJPEG编码描述
#define OBJECT_DES_ENCODE_SMPEG4		"SMPEG4_ENCODE"	//标准MPEG4编码描述
#define OBJECT_DES_ENCODE_HKVISSION		"HKVISSION_ENCODE"	//海康私有格式编码描述"
#define OBJECT_DES_ENCODE_DAHUA			"DAHUA_ENCODE"	//大华私有格式编码描述
#define OBJECT_DES_ENCODE_G711			"G711_ENCODE"	//G711音频数据编码描述
#define OBJECT_DES_ENCODE_G726			"G726_ENCODE"	//G726音频数据编码描述

#define OBJECT_DES_VODSOURCE_SBFILE		"SBFile_SOURCE" //VOD本地SB文件描述
#define OBJECT_DES_VODSOURCE_RPBFILE	"RPBFile_SOURCE" //用于实时即时回放的文件描述
#define OBJECT_DES_VODSOURCE_GENERAL	"GENERAL_SOURCE" //一般媒体文件Source描述

#define OBJECT_DES_HSFILEMANAGEMENT_MEMFILEMAPPING "MEMFILEMAPPING"  //高速文件管理中的内存映射文件类型
#define OBJECT_DES_HSFILEMANAGEMENT_REALCACHEFILE  "REALCACHEFILE"  //实时缓冲文件，用于支持即时回放

#define OBJECT_DES_SYSTEMVOLUME_IN		"SYSTEM_VOLUME_IN"			//系统输入音量标识
#define OBJECT_DES_SYSTEMVOLUME_OUT		"SYSTEM_VOLUME_OUT"			//系统输出音量标识


////////////////////////////////////////管理客户端//////////////////////////////////////////////////////////


struct ST_CallbackCacheInfo
{
	ISOC_VOID* pCallback;
	ISOC_DWORDPTR dwCookie;
	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;
	ST_CallbackCacheInfo() : pCallback(ISOC_NULL),dwCookie(0),dwReserved1(0),dwReserved2(0)
	{
	}

	ST_CallbackCacheInfo(const ST_CallbackCacheInfo& info)
	{
		pCallback = info.pCallback;
		dwCookie = info.dwCookie;
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
	}

	bool operator == (const ST_CallbackCacheInfo& info)const
	{
		if(this->pCallback == info.pCallback && this->dwCookie == info.dwCookie && this->dwReserved1 == info.dwReserved1 && this->dwReserved2 == info.dwReserved2)
			return true;
		else
			return false;
	}
};


#define  MAX_PIXELFMT_COUNT		(3)

////////////////////////////////////信令补充///////////////////////////////////////////////////

#define ISOC_GET_SETVER_TYPE_AND_VERSION_REQ 0x5051
#define ISOC_GET_SETVER_TYPE_AND_VERSION_ACK 0x5052
