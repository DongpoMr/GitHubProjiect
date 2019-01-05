#pragma once
#ifndef _ISOC_PUBLICSTRUCTDEFINE_H_
#define _ISOC_PUBLICSTRUCTDEFINE_H_

#define _CRT_SECURE_NO_DEPRECAT
#pragma warning(disable:4996)

#include "iSOC_Datatype_Define.h"

#pragma pack(push,1) 

#define  UNITDEVCODELEN   35           //长度取自数据库
struct ST_VideoInfo
{
	ISOC_ID			videoCodecId;
	ISOC_FLOAT		fFramePS;
	ISOC_FLOAT		fBitRate;
	ISOC_INT		nPicWidth;
	ISOC_INT		nPicHeight;
	ISOC_UINT64		totalTime;
	ISOC_UINT64		nowTime;
	ISOC_INT		nCodecIdx;
	ISOC_DWORDPTR	dwReserved1;
	ISOC_DWORDPTR	dwReserved2;

	ST_VideoInfo():videoCodecId(0),fFramePS(0.0f),fBitRate(0.0f),nPicWidth(0),nPicHeight(0)
		,totalTime(0),nowTime(0),nCodecIdx(0),dwReserved1(0),dwReserved2(0)
	{

	}
	
};

struct ST_AudioInfo
{
	ISOC_ID			audioCodecId;
	ISOC_FLOAT		fBitRate;
	ISOC_WORD		bChannels;
	ISOC_WORD		bBlockAlign;
	ISOC_WORD		bBitsPerSample;
	ISOC_INT		nSamplesPerSec;
	ISOC_UINT64		totalTime;
	ISOC_UINT64		nowTime;
	ISOC_DWORDPTR	dwReserved1;
	ISOC_DWORDPTR	dwReserved2;
	ST_AudioInfo():audioCodecId(0),fBitRate(0.0f),bChannels(0),bBlockAlign(0),bBitsPerSample(0)
		,nSamplesPerSec(0),totalTime(0),nowTime(0),dwReserved1(0),dwReserved2(0)
	{

	}
};

typedef ISOC_INT(__stdcall *iSOC_ReleaseDeviceExtendData)(ISOC_VOID* pExtendData, ISOC_INT nExtendDataLen);
struct ST_DeviceExtendInfo
{
	typedef enum
	{
		EXTEND_STRUCT = 1,
		EXTEND_XML = 2,
		EXTEND_JSON = 3,
		EXTEND_STRING = 4
	} ExtendInfoType;

	ISOC_INT nInfoSize;
	ISOC_INT nInfoType;
	ISOC_VOID* pExtendData;
	ISOC_INT nExtendDataLen;
	iSOC_ReleaseDeviceExtendData pReleaseDataCB;
	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;
	ST_DeviceExtendInfo()
	{
		memset(this, 0, sizeof(ST_DeviceExtendInfo));
	}
};

struct ST_DeviceItem
{
typedef enum 
            {UNKNOWN_KIND,
             ORGANIZE_NODE,
             DEVICE_CHANNEL,
             DEVICE_PROBE,
             DEVICE_OUTPUT,
             DEVICE_DOOR,
             DEVICE_PATROL,
             DEVICE_DEFENCE_AREA
            } DeviceKind;

	ST_DeviceItem()
	{
        ZeroMemory(this,sizeof(ST_DeviceItem));
        nChangeType     = -1;
        bIsDefence      = ISOC_TRUE;
	};

	ISOC_ID	    lDeviceID;                      //子设备ID(全局唯一)
	ISOC_ID	    lParentId;                      //父级节点id
	ISOC_ID	    lIcmsId;                        //自己所在域id(不全局唯一)
	ISOC_UINT	deviceKind;                     //设备种类,组织节点,设备,探头,输出
	ISOC_BOOL	beOnLine;                       //是否在线
	ISOC_DWORD	workStatus;	                    //工作是否正常,1为正常,其他值为非正常
	ISOC_BOOL	beHasPtzCtrl;                   //是否具有云台
	ISOC_INT	nDevType;                       //详细类型（枪机....）
	ISOC_CHAR   strIcmsSign[64];                //本级级联描述
	ISOC_CHAR	strDeviceName[200];             //设备名称
	ISOC_CHAR   strUnitDeviceCode[UNITDEVCODELEN];//统一设备编码
	ISOC_CHAR   strDeviceIP[16];                //设备IP
    ISOC_WORD   uDevicePort;                    //设备端口
	ISOC_ID		lBeforeParentId;                //改变前的父节点ID
	ISOC_ID		lAfterParentId;                 //改变后的父节点ID值
	ISOC_INT	nChangeType;                    //改变类型默认为-1， 0:新增，1：修改 2：删除
	ISOC_CHAR	strSystemType[128];             // 系统类型
	ISOC_BOOL	bIsDefence;                     //布防状态（如果是输出设备则表示输出状态）
    ISOC_INT    nChannelID;                     //通道号（子设备在主设备下的ID）
    ISOC_BOOL   bWithLight;                     //是否灯光
    ISOC_BOOL   bWithDemist;                    //是否除雾
    ISOC_BOOL   bWithRainBrush;                 //是否雨刷
	ISOC_DWORDPTR	dwReserved1;
	ISOC_DWORDPTR	dwReserved2;
	  
	ST_DeviceItem& operator =(const ST_DeviceItem& item)
	{
		memcpy(this,&item,sizeof(item));
		return *this;
	}
};

struct ST_VodFileInfo
{
	ISOC_ID		lDeviceID;
	ISOC_ID		lIcmsId;
	ISOC_INT	nFileArea;
	ISOC_INT	nFileID;
	ISOC_INT	nMasterFileID; //上级文件关联ID，如果等于nFileID则说明没有关联文件
	ISOC_INT	nFilesType;//文件类型:0x0b01手动录像 0x0b02报警录像  0x0b03计划录像  0x0B04历史上载  0x0B05报警抓帧  0x0B06手动抓帧  0x0b07迁移录像 
	ISOC_SYSTEMTIME	stStartTime;
	ISOC_SYSTEMTIME	stEndTime;
	ISOC_CHAR	strFilePath[260];
	ISOC_CHAR	strTrigger[200];
	ISOC_CHAR	strDevICMSSign[64];	// 文件所对应的设备的ICMSSign
	ISOC_CHAR   strUserGUID[64];
	ISOC_INT	nUserID;
	ISOC_CHAR	strSrcICMSSign[64]; // 源ICMSSign文件所在分控的ICMSSign
	ISOC_CHAR	strDesICMSSign[64]; // 目的ICMSSign发起查询任务的分控的ICMSSign，即客户端所登录的服务器的ICMSSign
	ISOC_DWORDPTR	dwReserved1;
	ISOC_DWORDPTR	dwReserved2;
	ISOC_UINT64		fileSize;	//文件大小
	ISOC_CHAR		strExtendInfo[1024];//暂时包含车次号和车厢号

	ST_VodFileInfo()
		:lIcmsId(0),nFileArea(0),nFileID(0),nFilesType(0),lDeviceID(0),nUserID(0),nMasterFileID(0),dwReserved1(0),dwReserved2(0)
	{
		ZeroMemory(&stStartTime,sizeof(ISOC_SYSTEMTIME));
		ZeroMemory(&stEndTime,sizeof(ISOC_SYSTEMTIME));
		ZeroMemory(strFilePath,sizeof(strFilePath));
		ZeroMemory(strTrigger,sizeof(strTrigger));
		ZeroMemory(strDevICMSSign,sizeof(strDevICMSSign));
		ZeroMemory(strDesICMSSign,sizeof(strDesICMSSign));
		ZeroMemory(strSrcICMSSign,sizeof(strSrcICMSSign));
		ZeroMemory(strUserGUID,sizeof(strUserGUID));
	};
	ST_VodFileInfo& operator =(const ST_VodFileInfo& info)
	{
		this->lDeviceID = info.lDeviceID;
		this->lIcmsId = info.lIcmsId;
		this->nFileArea = info.nFileArea;
		this->nFileID = info.nFileID;
		this->nMasterFileID = info.nMasterFileID;
		this->nFilesType = info.nFilesType;
		this->stEndTime = info.stEndTime;
		ZeroMemory(strFilePath,sizeof(strFilePath));
		ZeroMemory(strTrigger,sizeof(strTrigger));
		ZeroMemory(strDevICMSSign,sizeof(strDevICMSSign));
		ZeroMemory(strDesICMSSign,sizeof(strDesICMSSign));
		ZeroMemory(strSrcICMSSign,sizeof(strSrcICMSSign));
		ZeroMemory(strUserGUID,sizeof(strUserGUID));
		lstrcpy(this->strDesICMSSign,info.strDesICMSSign);
		lstrcpy(this->strFilePath,info.strFilePath);
		lstrcpy(this->strDevICMSSign,info.strDevICMSSign);
		lstrcpy(this->strSrcICMSSign,info.strSrcICMSSign);
		lstrcpy(this->strTrigger,info.strTrigger);
		lstrcpy(this->strUserGUID,info.strUserGUID);
		this->stStartTime = info.stStartTime;
		nUserID			  = info.nUserID;
		dwReserved1		  = info.dwReserved1;
		dwReserved2		  = info.dwReserved2;
		return *this;
	}
};

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

struct ST_GrabFileInfo
{
	ISOC_ID lDeviceID;
	ISOC_ID lIcmsId;
	ISOC_ID nFileID;
	ISOC_INT nFileArea;
	ISOC_INT nPicSize;
	ISOC_INT nFileType;//文件类型:0x0b01手动录像 0x0b02报警录像  0x0b03计划录像  0x0B04历史上载  0x0B05报警抓帧  0x0B06手动抓帧  0x0b07迁移录像 
	ISOC_CHAR strFileTime[20];
	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;
	ISOC_DWORDPTR dwReserved3;

	ISOC_CHAR strFileName[MAX_PATH];
	ISOC_CHAR strFilePath[MAX_PATH];
	ISOC_CHAR strDevICMSSign[64];	//文件所在设备icmssign
	ISOC_CHAR strUserGUID[64];
	ISOC_CHAR strSrcICMSSign[64]; // 源ICMSSign文件所在分控的ICMSSign
	ISOC_CHAR strDesICMSSign[64]; // 目的ICMSSign发起查询任务的分控的ICMSSign，即客户端所登录的服务器的ICMSSign
 
	ST_GrabFileInfo()
		:lIcmsId(0),lDeviceID(0),nFileID(0),nFileArea(0),nPicSize(0),nFileType(0)
		,dwReserved1(0),dwReserved2(0),dwReserved3(0)
	{
		ZeroMemory(strFileTime,sizeof(strFileTime));
		ZeroMemory(strFileName,sizeof(strFileName));
		ZeroMemory(strFilePath,sizeof(strFilePath));
		ZeroMemory(strDevICMSSign,sizeof(strDevICMSSign));
		ZeroMemory(strUserGUID,sizeof(strUserGUID));
		ZeroMemory(strSrcICMSSign, sizeof(strSrcICMSSign));
		ZeroMemory(strDesICMSSign, sizeof(strDesICMSSign));

	}

	ST_GrabFileInfo(const ST_GrabFileInfo & info)
	{
		this->dwReserved1	= info.dwReserved1;
		this->dwReserved2	= info.dwReserved2;
		this->dwReserved3	= info.dwReserved3;
		this->lDeviceID		= info.lDeviceID;
		this->lIcmsId		= info.lIcmsId;
		this->nFileArea		= info.nFileArea;
		this->nFileID		= info.nFileID;
		this->nFileType		= info.nFileType;
		this->nPicSize		= info.nPicSize;
		lstrcpy(this->strFileName,info.strFileName);
		lstrcpy(this->strFilePath,info.strFilePath);
		lstrcpy(this->strFileTime,info.strFileTime);
		lstrcpy(this->strDevICMSSign,info.strDevICMSSign);
		lstrcpy(this->strUserGUID,info.strUserGUID);
		lstrcpy(this->strSrcICMSSign,info.strSrcICMSSign);
		lstrcpy(this->strDesICMSSign,info.strDesICMSSign);

	}

	ST_GrabFileInfo & operator = (const ST_GrabFileInfo &info)
	{
		ZeroMemory(strFileTime,sizeof(strFileTime));
		ZeroMemory(strFileName,sizeof(strFileName));
		ZeroMemory(strFilePath,sizeof(strFilePath));
		ZeroMemory(strDevICMSSign,sizeof(strDevICMSSign));
		ZeroMemory(strUserGUID,sizeof(strUserGUID));
		ZeroMemory(strSrcICMSSign, sizeof(strSrcICMSSign));
		ZeroMemory(strDesICMSSign, sizeof(strDesICMSSign));		
		this->dwReserved1	= info.dwReserved1;
		this->dwReserved2	= info.dwReserved2;
		this->dwReserved3	= info.dwReserved3;
		this->lDeviceID		= info.lDeviceID;
		this->lIcmsId		= info.lIcmsId;
		this->nFileArea		= info.nFileArea;
		this->nFileID		= info.nFileID;
		this->nFileType		= info.nFileType;
		this->nPicSize		= info.nPicSize;
		lstrcpy(this->strFileName,info.strFileName);
		lstrcpy(this->strFilePath,info.strFilePath);
		lstrcpy(this->strFileTime,info.strFileTime);
		lstrcpy(this->strDevICMSSign,info.strDevICMSSign);
		lstrcpy(this->strUserGUID,info.strUserGUID);
		lstrcpy(this->strSrcICMSSign,info.strSrcICMSSign);
		lstrcpy(this->strDesICMSSign,info.strDesICMSSign);

		return *this;
	}
};

struct ST_PtzPos
{
	ISOC_INT		nPanPos;		//水平绝对位置
	ISOC_INT		nTitlePos;		//垂直绝对位置
	ISOC_INT		nZoomPos;		//Zoom位置
	ISOC_INT		nFocusPos;		//焦点位置
	ISOC_DWORDPTR	dwReserved1;	//保留变量1
	ISOC_DWORDPTR	dwReserved2;	//保留变量2
};

typedef struct ST_PresetPosInfo
{
	ST_PresetPosInfo()
		:nPresetNum(0),nXAngel(0),nYAngel(0),nChgAngel(0),nICMSSignID(0),dwReserved2(0),dwReserved1(0)
	{
		memset((ISOC_STR)strPresetName,0,sizeof(strPresetName));
		memset((ISOC_STR)strICMSSign,0,sizeof(strICMSSign));
	}
	ISOC_INT			nPresetNum;				// 预置点序号(从0到98)
	ISOC_CHAR			strPresetName[128];	// 预置点名称
	ISOC_INT			nXAngel;				// 水平角度（单位 度）
	ISOC_INT			nYAngel;				// 垂直角度（单位 度）
	ISOC_INT			nChgAngel;				// 变焦（单位 度）

	ISOC_CHAR			strICMSSign[64];		
	ISOC_ID				nICMSSignID;

	ISOC_DWORDPTR	dwReserved1;        //1.5.8版本中没用，在2.0版本中表示对应数据库主键ID
	ISOC_DWORDPTR	dwReserved2;


	ST_PresetPosInfo& operator = (const ST_PresetPosInfo & pp)
	{
		memset((ISOC_STR)strPresetName,0,sizeof(strPresetName));
		memset((ISOC_STR)strICMSSign,0,sizeof(strICMSSign));
		nPresetNum	= pp.nPresetNum;
		lstrcpy(strPresetName, pp.strPresetName);
		nXAngel		= pp.nXAngel;
		nYAngel		= pp.nYAngel;
		nChgAngel	= pp.nChgAngel;

		lstrcpy(strICMSSign, pp.strICMSSign);
		nICMSSignID	= pp.nICMSSignID;
		dwReserved1 = pp.dwReserved1;
		dwReserved2 = pp.dwReserved2;
		return *this;
	}

}ST_PRESETPOSINFO,*LPST_PRESETPOSINFO;


#define  MAX_DEVICEPRESETPOS_SIZE		(16)
typedef struct ST_TourInfo
{
	ST_TourInfo()
		:nTourNum(0),nDelayTime(1),nMoveSpeed(1),bBeLoop(0),nLoopDelayTime(0),nPresetPosCnt(0)
		,nICMSSignID(0),dwReserved1(0),dwReserved2(0)
	{
		memset((ISOC_STR)strCruiseName,0,sizeof(strCruiseName));
		memset(nPresetPosOrderNo,0,sizeof(nPresetPosOrderNo));
		memset(nPresetPosNum,0,sizeof(nPresetPosNum));
		memset((ISOC_STR)strICMSSign,0,sizeof(strICMSSign));
	}
	ISOC_CHAR				strCruiseName[128];	// 巡航名称
	ISOC_INT				nTourNum;			// 巡航序号
	ISOC_INT				nDelayTime;		// 预置点停留时间 1-2400秒
	ISOC_INT				nMoveSpeed;		// 预置点运动速度 1-24
	ISOC_INT				bBeLoop;			// 是否循环
	ISOC_INT				nLoopDelayTime;	// 循环间隔时间
	ISOC_INT				nPresetPosCnt;
	ISOC_INT				nPresetPosOrderNo[MAX_DEVICEPRESETPOS_SIZE]; // 最多16个预置点
	ISOC_INT				nPresetPosNum[MAX_DEVICEPRESETPOS_SIZE];	//预置结构体里面的nPresetNum集合，用于表示一个预置点

	ISOC_CHAR			strICMSSign[64];		
	ISOC_ID				nICMSSignID;

	ISOC_DWORDPTR	dwReserved1;
	ISOC_DWORDPTR	dwReserved2;


	ST_TourInfo operator = (const ST_TourInfo & cs)
	{
		memset((ISOC_STR)strCruiseName,0,sizeof(strCruiseName));
		memset(nPresetPosOrderNo,0,sizeof(nPresetPosOrderNo));
		memset(nPresetPosNum,0,sizeof(nPresetPosNum));
		memset((ISOC_STR)strICMSSign,0,sizeof(strICMSSign));
		lstrcpy(strCruiseName,cs.strCruiseName);
		nTourNum			= cs.nTourNum;
		nDelayTime			= cs.nDelayTime;
		nMoveSpeed		= cs.nMoveSpeed;
		bBeLoop			= cs.bBeLoop;

		nLoopDelayTime	= cs.nLoopDelayTime;
		nPresetPosCnt	= cs.nPresetPosCnt;
		memcpy(nPresetPosOrderNo,cs.nPresetPosOrderNo,sizeof(cs.nPresetPosOrderNo));
		memcpy(nPresetPosNum,cs.nPresetPosNum,sizeof(cs.nPresetPosNum));

		memset((ISOC_STR)strICMSSign,0,sizeof(ISOC_CHAR)*64);
		lstrcpy(strICMSSign, cs.strICMSSign);
		nICMSSignID	= cs.nICMSSignID;
		dwReserved1 = cs.dwReserved1;
		dwReserved2 = cs.dwReserved2;
		return *this;
	}

}ST_TOURINFO,*LPST_TOURINFO;

struct ST_CenterInfo
{
	ISOC_CHAR chCenterName[50];
	ISOC_CHAR chCenterICMSSign[64];
	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;

	ST_CenterInfo():dwReserved1(0),dwReserved2(0)
	{
		ZeroMemory(chCenterName,sizeof(chCenterName));
		ZeroMemory(chCenterICMSSign,sizeof(chCenterICMSSign));
	}

	ST_CenterInfo& operator =(const ST_CenterInfo& info)
	{
		lstrcpy(chCenterName,info.chCenterName);
		lstrcpy(chCenterICMSSign,info.chCenterICMSSign);
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
		return *this;
	}
};

#define MIGRATE_DESC_MAX_LEN 200
struct ST_MigrateInfo
{
	ISOC_INT	nTaskItemID;  //迁移任务本地ID,此字段只用于1.0的接口中有效，2.0接口中不使用此字段
	ISOC_ID		iVodFileID; //迁移的VOD文件ID,此字段只用于1.0的接口中有效，2.0接口中不使用此字段
	ISOC_ID		iTaskID; //迁移任务ID
	ISOC_ID		iDeviceID; // 设备ID
	ISOC_INT	nState;  //迁移状态，1为排队，2为正在调度，3为完成，4为暂停，5为取消,6为停止，7为异常，8为异常重试
	ISOC_INT	nProgress;  //迁移进度
	ISOC_INT	nRate; // 迁移速率，单位：B/s
	ISOC_SYSTEMTIME stMigStart;//文件迁移的开始时间,此字段只用于1.0的接口中有效，2.0接口中不使用此字段
	ISOC_SYSTEMTIME stMigEnd;	//文件迁移的结束时间,此字段只用于1.0的接口中有效，2.0接口中不使用此字段
	ISOC_CHAR	chUserGUID[64]; //用户GUID
	ISOC_CHAR	chMigrateUser[50]; //发起迁移任务的用户，只用于2.0中
	ISOC_CHAR	chMigrateDesc[MIGRATE_DESC_MAX_LEN]; //迁移描述，只用于2.0中
	ISOC_DWORDPTR	dwReserved1;
	ISOC_DWORDPTR	dwReserved2;

	ST_MigrateInfo()
	{
		ZeroMemory(this,sizeof(ST_MigrateInfo));
	}

	ST_MigrateInfo& operator =(const ST_MigrateInfo& info)
	{
		CopyMemory(this,&info,sizeof(ST_MigrateInfo));
		return *this;
	}
};

struct ST_MigrateItem
{
	ISOC_INT		nMigrateTaskID;
	ST_VodFileInfo stVodFileInfo; //视频文件信息
	ISOC_SYSTEMTIME stBeginTime; //文件中打点的开始时间
	ISOC_SYSTEMTIME stEndTime; //文件中打点的结束时间

	ST_MigrateItem():nMigrateTaskID(0)
	{
		ZeroMemory(&stBeginTime,sizeof(ISOC_SYSTEMTIME));
		ZeroMemory(&stEndTime,sizeof(ISOC_SYSTEMTIME));
	}

	ST_MigrateItem& operator =(const ST_MigrateItem& info)
	{
		nMigrateTaskID = info.nMigrateTaskID;
		stVodFileInfo = info.stVodFileInfo;
		stBeginTime = info.stBeginTime;
		stEndTime = info.stEndTime;
		return *this;
	}

	ST_MigrateItem(const ST_MigrateItem& info)
	{
		nMigrateTaskID = info.nMigrateTaskID;
		stVodFileInfo = info.stVodFileInfo;
		stBeginTime = info.stBeginTime;
		stEndTime = info.stEndTime;
	}
};

struct ST_FileLockSpaceInfo
{
	ST_CenterInfo centerInfo; //锁定中心信息
	ISOC_SIZE_T	  szLimitSpace;//限定的空间大小，以MB为单位
	ISOC_SIZE_T	  szUsedSpace;//使用的空间大小，以MB为单位
	ISOC_DWORDPTR dwReserved; //保留字段
	ST_FileLockSpaceInfo():szLimitSpace(0),szUsedSpace(0),dwReserved(0)
	{

	}

	ST_FileLockSpaceInfo& operator =(const ST_FileLockSpaceInfo& info)
	{
		centerInfo = info.centerInfo;
		szLimitSpace = info.szLimitSpace;
		szUsedSpace = info.szUsedSpace;
		dwReserved = info.dwReserved;
		return *this;
	}
};

struct ST_VodQueryFilter
{
	/*************************************************
	nFileArea表示文件所在地方，即去哪儿查询，其值
	可以是以下值中的一个：
	nFileArea =0前端和中心查询  =1中心（摄像机所在
	中心） =2前端查询 =3备份查询 =4迁移查询 =5中心（用
	户所登录的中心） ，默认值为0
	*************************************************/
	ISOC_INT nFileArea;

	/*************************************************
	文件类型，其值可以是以下值当中的一个或多个的组合
	组合方式为“或（｜）”的方式。
	nVodFileType =0x1报警文件   =0x2手动文件
	             =0x4计划文件
	*************************************************/
	ISOC_INT nVodFileType;

	/*************************************************
	当nVodFileType中包含报警文件时，nAlarmFileType表示
	报警文件的类型。其值可以是以下值当中的一个或多个的
	组合，组合方式为“或（｜）”的方式。
	nAlarmFileType =0x01所有报警类型		=0x02移动报警
				   =0x04遮拦报警			=0x08探头报警
				   =0x10智能报警			=0x20手动报警
				   =0x40其他报警			=0x80门禁报警
				   =0x100防区报警
	*************************************************/
	ISOC_INT nAlarmFileType;

	/*************************************************
	当nVodFileType中包含报警文件时，nAlarmDealStatus
	表示处理状态类型。其值可以是以下值当中的一个或两
	个的组合，组合方式为“或（｜）”的方式。
	nAlarmDealStatus =0x1已处理报警的文件
					 =0x2未处理报警的文件
	*************************************************/
	ISOC_INT nAlarmDealStatus;

	/*************************************************
	strTag为标签的值，当其长度不为0时则代表要使用标签
	查询，当其长度为0时则不使用标签。
	*************************************************/
	ISOC_CHAR strTag[1024];


	ISOC_CHAR strCardUser[48];

	ISOC_CHAR strCardID[48];
	/*************************************************
	strStartTime表示查询时间段的开始时间，精确到秒级
	字符串的内容形如"2011-04-29 10:06:00"
	*************************************************/
	ISOC_CHAR strStartTime[20];

	/*************************************************
	strEndTime表示查询时间段的结束时间，精确到秒级
	字符串的内容形如"2011-04-29 10:06:00"
	*************************************************/
	ISOC_CHAR strEndTime[20];

	/*************************************************
	migrateCenterInfo表示迁移服务器所在中心的信息，在
	nFileArea为4的时候使用此字段，此字段只对isoc2.0
	的服务器有效，1.5.8的服务器可以不使用此字段
	*************************************************/
	ST_CenterInfo migrateCenterInfo;

	ISOC_DWORDPTR	dwReserved1;
	ISOC_DWORDPTR	dwReserved2;

	ST_VodQueryFilter()
		:nFileArea(0),nVodFileType(0),nAlarmFileType(0)
		,nAlarmDealStatus(0),dwReserved1(0),dwReserved2(0)
	{
		ZeroMemory(strTag,sizeof(strTag));
		ZeroMemory(strStartTime,sizeof(strStartTime));
		ZeroMemory(strEndTime,sizeof(strEndTime));
		ZeroMemory(strCardUser,sizeof(strCardUser));
		ZeroMemory(strCardID,sizeof(strCardID));
	}

	ST_VodQueryFilter(const ST_VodQueryFilter& info)
	{
		this->nAlarmDealStatus	= info.nAlarmDealStatus;
		this->nAlarmFileType	= info.nAlarmFileType;
		this->nFileArea			= info.nFileArea;
		this->nVodFileType		= info.nVodFileType;
		lstrcpy(this->strTag,info.strTag);
		lstrcpy(this->strStartTime,info.strStartTime);
		lstrcpy(this->strEndTime,info.strEndTime);
		lstrcpy(this->strCardID,info.strCardID);
		lstrcpy(this->strCardUser,info.strCardUser);
		migrateCenterInfo = info.migrateCenterInfo;
		dwReserved1				= info.dwReserved1;
		dwReserved2				= info.dwReserved2;
	}

	ST_VodQueryFilter& operator =(const ST_VodQueryFilter& info)
	{
		ZeroMemory(strTag,sizeof(strTag));
		ZeroMemory(strStartTime,sizeof(strStartTime));
		ZeroMemory(strEndTime,sizeof(strEndTime));
		ZeroMemory(strCardUser,sizeof(strCardUser));
		ZeroMemory(strCardID,sizeof(strCardID));
		this->nAlarmDealStatus	= info.nAlarmDealStatus;
		this->nAlarmFileType	= info.nAlarmFileType;
		this->nFileArea			= info.nFileArea;
		this->nVodFileType		= info.nVodFileType;
		lstrcpy(this->strTag,info.strTag);
		lstrcpy(this->strStartTime,info.strStartTime);
		lstrcpy(this->strEndTime,info.strEndTime);
		lstrcpy(this->strCardID,info.strCardID);
		lstrcpy(this->strCardUser,info.strCardUser);
		migrateCenterInfo = info.migrateCenterInfo;
		dwReserved1				= info.dwReserved1;
		dwReserved2				= info.dwReserved2;
		return *this;
	}
};

struct ST_CameraParameter
{
	ISOC_INT nBright; //亮度
	ISOC_INT nContrast; //对比度
	ISOC_INT nSaturation; //饱和度
	ISOC_INT nHue; //色调
	ISOC_INT nAudioLevel; //音量
	ISOC_DWORDPTR dwReserved1; //保留变量1
	ISOC_DWORDPTR dwReserved2; //保留变量2

	ST_CameraParameter() : nBright(0),nContrast(0),nSaturation(0)
		,nHue(0),nAudioLevel(0),dwReserved1(0),dwReserved2(0)
	{

	};
};

struct ST_MapNode	//表示地图的层级关系
{
	ISOC_INT	nMapListID;				// Int（PK）	地图目录表ID号
	ISOC_INT	nMSuperiorID;			// Int	上级ID
	ISOC_INT	nMLevel;	            // Int	级别
	ISOC_CHAR	strPedigree[1024*4];	// Nvarchar(4000)	簇谱
	ISOC_CHAR	strCoding[1024*4];		// Nvarchar(4000)	编码
	ISOC_CHAR	strMName[128];			// Nvarchar(50)	节点名称
	ISOC_CHAR	strICMSSign[64];
	ISOC_INT	nICMSMapListID;			


	ISOC_DWORDPTR dwReserved1; //保留变量1
	ISOC_DWORDPTR dwReserved2; //保留变量2

	ST_MapNode():nMapListID(0),nMSuperiorID(0),nMLevel(0),dwReserved1(0),dwReserved2(0),nICMSMapListID(0)
	{
		ZeroMemory(strPedigree,sizeof(strPedigree));
		ZeroMemory(strCoding,sizeof(strCoding));
		ZeroMemory(strMName,sizeof(strMName));
		ZeroMemory(strICMSSign, sizeof(strICMSSign));
	}

	ST_MapNode(const ST_MapNode & mn)
	{
		nMapListID		= mn.nMapListID;
		nMSuperiorID	= mn.nMSuperiorID;
		nMLevel			= mn.nMLevel;
		nICMSMapListID	= mn.nICMSMapListID;
		lstrcpy(strICMSSign, mn.strICMSSign);
		lstrcpy(strPedigree,mn.strPedigree);
		lstrcpy(strCoding,mn.strCoding);
		lstrcpy(strMName,mn.strMName);
		dwReserved1		= mn.dwReserved1;
		dwReserved2		= mn.dwReserved2;
	}
	
	ST_MapNode& operator =(const ST_MapNode & mn)
	{
		ZeroMemory(strPedigree,sizeof(strPedigree));
		ZeroMemory(strCoding,sizeof(strCoding));
		ZeroMemory(strMName,sizeof(strMName));
		ZeroMemory(strICMSSign, sizeof(strICMSSign));
		nMapListID		= mn.nMapListID;
		nMSuperiorID	= mn.nMSuperiorID;
		nMLevel			= mn.nMLevel;
		nICMSMapListID	= mn.nICMSMapListID;
		lstrcpy(strICMSSign, mn.strICMSSign);
		lstrcpy(strPedigree,mn.strPedigree);
		lstrcpy(strCoding,mn.strCoding);
		lstrcpy(strMName,mn.strMName);
		dwReserved1		= mn.dwReserved1;
		dwReserved2		= mn.dwReserved2;

		return *this;
	}
};

struct ST_MapLeaf // 电子地图类
{
	ISOC_INT	nMapLeafID; 				// nMapLeafInfoID//Int（PK）	地图表ID号
	ISOC_INT	nMapListID;					// Int（FK）	地图目录ID
	ISOC_INT	nMapSize;
	ISOC_INT	nICMSMapLeafID;				//ICMS系统中的地图表ID
	ISOC_INT	nICMSMapListID;
	ISOC_CHAR	strMName[128];				// Nvarchar(50)	地图名称
	ISOC_CHAR	strMapVersion[128];			// Nvarchar(50)	地图版本号
	ISOC_CHAR	strMapDateTime[64];			// Datetime()	地图更改时间
	ISOC_CHAR	strLeafInfoICMSSign[64];	//地图表的ICMSSign
	
	ISOC_DWORDPTR dwReserved1; //保留变量1
	ISOC_DWORDPTR dwReserved2; //保留变量2

	ST_MapLeaf():nMapLeafID(0),nMapListID(0),dwReserved1(0),dwReserved2(0),nICMSMapLeafID(0),nMapSize(0),nICMSMapListID(0)
	{
		ZeroMemory(strMName,sizeof(strMName));
		ZeroMemory(strMapVersion,sizeof(strMapVersion));
		ZeroMemory(strMapDateTime,sizeof(strMapDateTime));
		ZeroMemory(strLeafInfoICMSSign, sizeof(strLeafInfoICMSSign));
		
	}

	ST_MapLeaf(const ST_MapLeaf & ml)
	{
		nMapLeafID  = ml.nMapLeafID;
		nMapListID	= ml.nMapListID;
		nMapSize	= ml.nMapSize;
		nICMSMapLeafID	= ml.nICMSMapLeafID;
		nICMSMapListID	= ml.nICMSMapListID;
		lstrcpy(strMName,ml.strMName);
		lstrcpy(strMapVersion,ml.strMapVersion);
		lstrcpy(strMapDateTime,ml.strMapDateTime);
		lstrcpy(strLeafInfoICMSSign, ml.strLeafInfoICMSSign);
		dwReserved1	= ml.dwReserved1;
		dwReserved2	= ml.dwReserved2;
	}

	ST_MapLeaf& operator =(const ST_MapLeaf & ml)
	{
		ZeroMemory(strMName,sizeof(strMName));
		ZeroMemory(strMapVersion,sizeof(strMapVersion));
		ZeroMemory(strMapDateTime,sizeof(strMapDateTime));
		ZeroMemory(strLeafInfoICMSSign, sizeof(strLeafInfoICMSSign));
		nMapLeafID  = ml.nMapLeafID;
		nMapListID	= ml.nMapListID;
		nICMSMapLeafID	= ml.nICMSMapLeafID;
		nICMSMapListID	= ml.nICMSMapListID;
		nMapSize		= ml.nMapSize;
		lstrcpy(strMName,ml.strMName);
		lstrcpy(strMapVersion,ml.strMapVersion);
		lstrcpy(strMapDateTime,ml.strMapDateTime);
		lstrcpy(strLeafInfoICMSSign, ml.strLeafInfoICMSSign);
		dwReserved1	= ml.dwReserved1;
		dwReserved2	= ml.dwReserved2;
		return *this;
	}
};

struct ST_MapLeafMapAss//表示与子图的关联关系
{
	ISOC_INT	nMapAssInfoID;	    // Int（PK）	地图关联表ID号
	ISOC_INT	nMapLeafID;			// nMapLeafInfoID//Int（FK）	地图ID
	ISOC_INT	nAMapLeafInfoID;	// Int（FK）	关联区域的关联地图ID
	ISOC_RECT	rectHotArea;
	ISOC_CHAR	strMapICMSSign[64];
	ISOC_INT	nICMSMapLeafInfoID;
	ISOC_DWORDPTR dwReserved1; //保留变量1
	ISOC_DWORDPTR dwReserved2; //保留变量2

	ST_MapLeafMapAss():nMapAssInfoID(0),nMapLeafID(0),nAMapLeafInfoID(0),dwReserved1(0),dwReserved2(0),nICMSMapLeafInfoID(0)
	{
		ZeroMemory(&rectHotArea,sizeof(rectHotArea));
		ZeroMemory(strMapICMSSign, sizeof(strMapICMSSign));
	}
};

struct ST_MapLeafEquAss//表示地图与设备的关联关系
{
	ISOC_INT	nEquMapAssInfoID;		// Int（PK）	组织结构与地图关联表ID号
	ISOC_INT	nMapLeafInfoID;			// Int（FK）	地图ID
	ISOC_RECT	rectHotArea;
	ISOC_INT	nSubEquipmentID;	    // Int（FK）	子设备ID号
	ISOC_INT	nAngel;					// 旋转角度
	ISOC_INT	nEquType;				// 非xml协议字段，参见
	ISOC_BOOL   bSelected;				// 非协议字段
	ISOC_INT	nStatus;				// 非协议字段 0表示正常，1表示录像
	ISOC_CHAR	sEquName[128];			// 非协议字段，设备名称
	
	ISOC_INT	nICMSSubEquipID;
	ISOC_INT	nICMSMapLeafInfoID;
	ISOC_CHAR	strSubEquipICMSSign[64];
	ISOC_CHAR	strMapLeafInfoICMSSign[64];

	ISOC_DWORDPTR dwReserved1; //保留变量1
	ISOC_DWORDPTR dwReserved2; //保留变量2

	ST_MapLeafEquAss():nEquMapAssInfoID(0),nMapLeafInfoID(0),nSubEquipmentID(0),nAngel(0),dwReserved1(0),dwReserved2(0)
		,nEquType(0),bSelected(FALSE),nStatus(0),nICMSMapLeafInfoID(0),nICMSSubEquipID(0)
	{
		ZeroMemory(&rectHotArea,sizeof(rectHotArea));
		ZeroMemory(sEquName,sizeof(sEquName));
		ZeroMemory(strMapLeafInfoICMSSign, sizeof(strMapLeafInfoICMSSign));
		ZeroMemory(strSubEquipICMSSign, sizeof(strSubEquipICMSSign));
	}

	ST_MapLeafEquAss( const ST_MapLeafEquAss& mlea)
	{
		nEquMapAssInfoID	= mlea.nEquMapAssInfoID;
		nMapLeafInfoID		= mlea.nMapLeafInfoID;
		nSubEquipmentID		= mlea.nSubEquipmentID;
		nAngel				= mlea.nAngel;
		nEquType			= mlea.nEquType;
		bSelected			= mlea.bSelected;
		nStatus				= mlea.nStatus;
		rectHotArea			= mlea.rectHotArea;
		lstrcpy(sEquName,mlea.sEquName);
		dwReserved1			= mlea.dwReserved1;
		dwReserved2			= mlea.dwReserved2;

		nICMSSubEquipID		= mlea.nICMSSubEquipID;
		nICMSMapLeafInfoID	= mlea.nICMSMapLeafInfoID;
		lstrcpy(strSubEquipICMSSign, mlea.strSubEquipICMSSign);
		lstrcpy(strMapLeafInfoICMSSign, mlea.strMapLeafInfoICMSSign);
	}


	ST_MapLeafEquAss& operator=( const ST_MapLeafEquAss& mlea)
	{
		ZeroMemory(sEquName,sizeof(sEquName));
		nEquMapAssInfoID	= mlea.nEquMapAssInfoID;
		nMapLeafInfoID		= mlea.nMapLeafInfoID;
		nSubEquipmentID		= mlea.nSubEquipmentID;
		nAngel				= mlea.nAngel;
		nEquType			= mlea.nEquType;
		bSelected			= mlea.bSelected;
		nStatus				= mlea.nStatus;
		rectHotArea			= mlea.rectHotArea;
		lstrcpy(sEquName,mlea.sEquName);

		dwReserved1			= mlea.dwReserved1;
		dwReserved2			= mlea.dwReserved2;

		nICMSSubEquipID		= mlea.nICMSSubEquipID;
		nICMSMapLeafInfoID	= mlea.nICMSMapLeafInfoID;
		lstrcpy(strSubEquipICMSSign, mlea.strSubEquipICMSSign);
		lstrcpy(strMapLeafInfoICMSSign, mlea.strMapLeafInfoICMSSign);

		return *this;
	}
};

struct ST_MapLeafOrgAss//表示地图与组织结构的关联关系
{
	ISOC_INT nOrgMapAssInfoID;		// Int（PK）	设备节点与地图关联表ID号
	ISOC_INT nOrganizeListID;		// Int（FK）	组织结构列表ID号
	ISOC_INT nMapLeafInfoID;	    // Int（FK）	地图ID

	ISOC_DWORDPTR dwReserved1; //保留变量1
	ISOC_DWORDPTR dwReserved2; //保留变量2

	ST_MapLeafOrgAss():nOrgMapAssInfoID(0),nOrganizeListID(0),nMapLeafInfoID(0),dwReserved1(0),dwReserved2(0)
	{
	}
};

struct ST_TagInfo	// 标签信息
{
	ISOC_SYSTEMTIME stTagTime;		// 标签时间
	ISOC_SYSTEMTIME	stUserAddTime;	// 用户添加标签的时间
	ISOC_CHAR		strTagTitle[1024];	// 标题
	ISOC_INT		nTitleLen;		// 标题长度
	ISOC_CHAR		strTagContent[2048];	// 内容
	ISOC_INT		nContentLen;	// 内容长度
	ISOC_DWORDPTR	dwReserved;		// 保留字

	ISOC_DWORDPTR dwReserved1; //保留变量1
	ISOC_DWORDPTR dwReserved2; //保留变量2

	ST_TagInfo():nTitleLen(0),nContentLen(0),dwReserved(0),dwReserved1(0),dwReserved2(0)
	{
		ZeroMemory(strTagContent,sizeof(strTagContent));
		ZeroMemory(strTagTitle,sizeof(strTagTitle));
		ZeroMemory(&stTagTime,sizeof(stTagTime));
		ZeroMemory(&stUserAddTime,sizeof(stUserAddTime));
	}

	~ST_TagInfo()
	{
		ZeroMemory(strTagContent,sizeof(ISOC_CHAR) * 2048);
		ZeroMemory(strTagTitle,sizeof(ISOC_CHAR) * 1024);
		nTitleLen	= 0;
		nContentLen = 0;
		dwReserved1 = 0;
		dwReserved2 = 0;
	}

	ST_TagInfo(const ST_TagInfo & ti)
	{
		stTagTime		= ti.stTagTime;
		stUserAddTime	= ti.stUserAddTime;
		dwReserved		= ti.dwReserved;
		lstrcpy(strTagTitle,ti.strTagTitle);
		nTitleLen		= ti.nTitleLen;
		lstrcpy(strTagContent,ti.strTagContent);
		nContentLen		= ti.nContentLen;
		dwReserved1	    = ti.dwReserved1;
		dwReserved2		= ti.dwReserved2;
		dwReserved		= ti.dwReserved;
	}

	ST_TagInfo& ST_TagInfo::operator =(const ST_TagInfo & ti)
	{
		ZeroMemory(strTagContent,sizeof(strTagContent));
		ZeroMemory(strTagTitle,sizeof(strTagTitle));
		stTagTime		= ti.stTagTime;
		stUserAddTime	= ti.stUserAddTime;
		dwReserved		= ti.dwReserved;

		dwReserved1		= ti.dwReserved1;
		dwReserved2		= ti.dwReserved2;
		if( ti.strTagTitle && ti.nTitleLen > 0 )
		{
			nTitleLen	= ti.nTitleLen;
			lstrcpy(strTagTitle,ti.strTagTitle);
		}
		else
		{
			nTitleLen	= 0;
		}

		if( ti.strTagContent && ti.nContentLen > 0 )
		{
			nContentLen	= ti.nContentLen;
			lstrcpy(strTagContent,ti.strTagContent);
		}
		else
		{
			nContentLen		= 0;
		}

		return *this;
	}
};

struct ST_UserInfo
{
	ISOC_INT nUserID;
	ISOC_INT nUserLevel;
	ISOC_CHAR strUserName[64];
	ISOC_CHAR strPassword[64];
	ISOC_CHAR strUserICMSSign[64]; //用户所在系统的ICMSSign
	ISOC_CHAR strServerICMSSign[64]; //用户所登录的服务器的ICMSSign
	ISOC_DWORDPTR dwReserved; //保留变量
	ISOC_DWORDPTR dwReserved1; //保留变量1
	ISOC_DWORDPTR dwReserved2; //保留变量2

	ST_UserInfo() : nUserID(0),dwReserved(0),dwReserved1(0),dwReserved2(0),nUserLevel(0)
	{
		ZeroMemory(strUserName,sizeof(strUserName));
		ZeroMemory(strUserICMSSign,sizeof(strUserICMSSign));
		ZeroMemory(strPassword,sizeof(strPassword));
		ZeroMemory(strServerICMSSign,sizeof(strServerICMSSign));
	}
};

#define ISOC_NUM_DATA_POINTERS 8
struct ST_VideoFrame
{
	ISOC_BYTE *pData[ISOC_NUM_DATA_POINTERS]; //对于RGB数据，pData[0]为对应RGB数据的首地址，其它无效；对于YUV数据，pData[0]为Y分量的首地址，pData[1]为V分量的首地址，pData[2]为
	ISOC_INT nLineSize[ISOC_NUM_DATA_POINTERS]; //与上面保持一致，对应于上面分量的一行的数据大小
	ISOC_INT nWidth; //当前帧的宽
	ISOC_INT nHeight;  //当前帧的高

	enum EN_FramePixType
	{
		PIX_YUV420P,
		PIX_RGB24,
		PIX_DIB,
		PIX_RGB32,
		PIX_RGBA,
		PIX_BGRA,
		PIX_ARGB,
		PIX_NV12,
		PIX_D3D9,
		PIX_D3D11
	};

	EN_FramePixType pixFormatType; //视频数据像素格式
	ISOC_DWORDPTR dwReserved1; //保留变量1
	ISOC_DWORDPTR dwReserved2; //保留变量2

	ST_VideoFrame()
	{
		ZeroMemory(this,sizeof(ST_VideoFrame));
	}
};

struct ST_AudioFrame
{
	ISOC_BYTE* pData; //音频数据
	ISOC_INT nDataLen; //数据长度
	ISOC_DWORDPTR dwReserved;//保留变量

	ST_AudioFrame()
	{
		ZeroMemory(this,sizeof(ST_AudioFrame));
	}
};

struct ST_MatrixServerInfo
{
	ISOC_ID		iICMSServerID;	 //对应分控的电视墙服务器ID
	ISOC_CHAR	strICMSSign[64]; //电视墙服务器所属分控的ICMSSign
	ISOC_CHAR	strServerIP[20]; //电视墙服务器的IP地址
	ISOC_UINT	uServerPort;	 //电视墙服务器的端口
	ISOC_DWORDPTR dwReserved1;	 //保留变量1
	ISOC_DWORDPTR dwReserved2;	 //保留变量2
	ST_MatrixServerInfo() : iICMSServerID(0),uServerPort(0),dwReserved1(0),dwReserved2(0)
	{
		ZeroMemory(strICMSSign,sizeof(strICMSSign));
		ZeroMemory(strServerIP,sizeof(strServerIP));
	}

	ST_MatrixServerInfo(const ST_MatrixServerInfo& info)
	{
		ZeroMemory(strICMSSign,sizeof(strICMSSign));
		ZeroMemory(strServerIP,sizeof(strServerIP));
		iICMSServerID = info.iICMSServerID;
		lstrcpy(strICMSSign,info.strICMSSign);
		lstrcpy(strServerIP,info.strServerIP);
		uServerPort = info.uServerPort;
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
	}

	ST_MatrixServerInfo& ST_MatrixServerInfo::operator =(const ST_MatrixServerInfo& info)
	{
		ZeroMemory(strICMSSign,sizeof(strICMSSign));
		ZeroMemory(strServerIP,sizeof(strServerIP));
		iICMSServerID = info.iICMSServerID;
		lstrcpy(strICMSSign,info.strICMSSign);
		lstrcpy(strServerIP,info.strServerIP);
		uServerPort = info.uServerPort;
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
		return *this;
	}
};
//输出信息
struct ST_MatrixOutputInfo
{
	ISOC_ID		iMatrixOutputID;//输出ID
	ISOC_INT	nOutputIndex;//输出Index
	ISOC_CHAR	strOutputName[50];//输出名
	ISOC_INT	nDecodeNumber;
	ISOC_INT	nLayoutNumber;
	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;
	ST_MatrixOutputInfo():iMatrixOutputID(0),nOutputIndex(0),nDecodeNumber(0),dwReserved1(0),dwReserved2(0),nLayoutNumber(1)
	{
		ZeroMemory(strOutputName,sizeof(strOutputName));
	}

	ST_MatrixOutputInfo(const ST_MatrixOutputInfo& info)
	{
		ZeroMemory(strOutputName,sizeof(strOutputName));
		iMatrixOutputID = info.iMatrixOutputID;
		nOutputIndex = info.nOutputIndex;
		lstrcpy(strOutputName,info.strOutputName);
		nDecodeNumber = info.nDecodeNumber;
		nLayoutNumber = info.nLayoutNumber;
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
	}

	ST_MatrixOutputInfo& ST_MatrixOutputInfo::operator =(const ST_MatrixOutputInfo& info)
	{
		ZeroMemory(strOutputName,sizeof(strOutputName));
		iMatrixOutputID = info.iMatrixOutputID;
		nOutputIndex = info.nOutputIndex;
		lstrcpy(strOutputName,info.strOutputName);
		nDecodeNumber = info.nDecodeNumber;
		nLayoutNumber = info.nLayoutNumber;
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
		return *this;
	}
};

struct ST_MatrixCardInfo
{
	ISOC_ID		iMatrixCardInfoID;
	ISOC_INT	nCardIndex;
	ISOC_INT	nCardType;
	ISOC_INT	nOutputNumber;
	ST_MatrixOutputInfo matrixOutputInfos[20]; //此处规定一块显卡最大输出数为20个，目前该个数已经满足需要，如果后面出现更多输出数的显卡再改变此值
	ISOC_DWORDPTR	dwReserved1;
	ISOC_DWORDPTR	dwReserved2;
	ST_MatrixCardInfo() : iMatrixCardInfoID(0),nCardIndex(0),nCardType(0),nOutputNumber(0)
		,dwReserved1(0),dwReserved2(0)
	{

	}

	ST_MatrixCardInfo(const ST_MatrixCardInfo& info)
	{
		iMatrixCardInfoID = info.iMatrixCardInfoID;
		nCardIndex = info.nCardIndex;
		nCardType = info.nCardType;
		nOutputNumber = info.nOutputNumber;
		for(int x=0;x<nOutputNumber;x++)
		{
			matrixOutputInfos[x] = info.matrixOutputInfos[x];
		}
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
	}

	ST_MatrixCardInfo& ST_MatrixCardInfo::operator =(const ST_MatrixCardInfo& info)
	{
		ZeroMemory(matrixOutputInfos,sizeof(matrixOutputInfos));
		iMatrixCardInfoID = info.iMatrixCardInfoID;
		nCardIndex = info.nCardIndex;
		nCardType = info.nCardType;
		nOutputNumber = info.nOutputNumber;
		for(int x=0;x<nOutputNumber;x++)
		{
			matrixOutputInfos[x] = info.matrixOutputInfos[x];
		}
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
		return *this;
	}
};
//通道信息
struct ST_ChannelInfo
{
	ISOC_INT	nChannelType;//通道类型 1、通道  2、电子地图
	ISOC_INT	nChannelID;//通道ID
	ISOC_CHAR strChannelICMSSign[50];//通道ICMSSign
	ISOC_CHAR strUnitDeviceCode[UNITDEVCODELEN];
	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;
	ISOC_DWORDPTR dwReserved3;
	ST_ChannelInfo():nChannelType(0),nChannelID(0),dwReserved1(0),dwReserved2(0),dwReserved3(0)
	{
		ZeroMemory(strChannelICMSSign,sizeof(strChannelICMSSign));
		ZeroMemory(strUnitDeviceCode,sizeof(strUnitDeviceCode));
	}

	ST_ChannelInfo(const ST_ChannelInfo& info)
	{
		ZeroMemory(strChannelICMSSign,sizeof(strChannelICMSSign));
		nChannelType = info.nChannelType;
		nChannelID = info.nChannelID;
		lstrcpy(strChannelICMSSign,info.strChannelICMSSign);
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
		dwReserved3 = info.dwReserved3;
		ZeroMemory(strUnitDeviceCode,sizeof(strUnitDeviceCode));
		lstrcpy(strUnitDeviceCode,info.strUnitDeviceCode);
	}

	ST_ChannelInfo& ST_ChannelInfo::operator =(const ST_ChannelInfo& info)
	{
		ZeroMemory(strChannelICMSSign,sizeof(strChannelICMSSign));
		nChannelID = info.nChannelID;
		nChannelType = info.nChannelType;
		lstrcpy(strChannelICMSSign,info.strChannelICMSSign);
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
		dwReserved3 = info.dwReserved3;
		ZeroMemory(strUnitDeviceCode,sizeof(strUnitDeviceCode));
		lstrcpy(strUnitDeviceCode,info.strUnitDeviceCode);
		return *this;
	}
};

//font alignment
#define ALIGN_TOP                      0x00000000
#define ALIGN_LEFT                     0x00000000
#define ALIGN_HCENTER                  0x00000001
#define ALIGN_RIGHT                    0x00000002
#define ALIGN_VCENTER                  0x00000004
#define ALIGN_BOTTOM                   0x00000008

//font weights

#define FONTW_DONTCARE         0
#define FONTW_THIN             100
#define FONTW_EXTRALIGHT       200
#define FONTW_LIGHT            300
#define FONTW_NORMAL           400
#define FONTW_MEDIUM           500
#define FONTW_SEMIBOLD         600
#define FONTW_BOLD             700
#define FONTW_EXTRABOLD        800
#define FONTW_HEAVY            900

struct ST_OverlayMarginInfo
{
	ISOC_INT nMarginLeft;//距离区域的左边距
	ISOC_INT nMarginTop; //距离区域的上边距
	ISOC_INT nMarginRight; //距离区域的右边距
	ISOC_INT nMarginBottom; //距离区域的下边距
	void Init()
	{
		memset(this, 0, sizeof(ST_OverlayMarginInfo));
	}
};

struct ST_OverlayFontInfo
{
	ISOC_CHAR chOverlayText[MAX_PATH];//叠加信息内容
	ISOC_INT nAlignWay;//对齐方式
	ISOC_INT nFontSize;//文字界面
	ISOC_CHAR chFontName[40];//文字名称
	ISOC_DWORD	dwFontColor;
	ISOC_DWORD dwFontWeight;
	ISOC_RECT overlayRect;//要叠加的文字区域
	ST_OverlayMarginInfo marginInfo;

	void Init()
	{
		nAlignWay = ALIGN_LEFT | ALIGN_TOP;
		nFontSize = 24;
		dwFontColor = RGB(255, 0, 0);
		dwFontWeight = FONTW_DONTCARE;
		ZeroMemory(chOverlayText, sizeof(chOverlayText));
		sprintf_s(chFontName, _T("微软雅黑"));
		ZeroMemory(&overlayRect, sizeof(ISOC_RECT));
		marginInfo.Init();
	}
};

struct ST_OverlayLineInfo
{
	ISOC_POINT *pPointLists;  //点的数组
	ISOC_INT nPointsCount;  //点的个数
	ISOC_FLOAT fWidth; //线宽
	ISOC_DWORD dwLineColor;//线的颜色
	ISOC_DWORD dwPattern; //画线模式，1为虚线，0为透明
	ISOC_FLOAT fPatternScale; //设置虚线中的间隔，参数越大，间隔越大，默认为1.0f

	void Init()
	{
		pPointLists = NULL;
		nPointsCount = 0;
		dwLineColor = RGB(255, 0, 0);
		dwPattern = 0;
		fPatternScale = 1.0f;
	}
// 	ST_OverlayLineInfo() : pPointLists(ISOC_NULL), nPointsCount(0), dwLineColor(RGB(255, 0, 0)),dwPattern(0),fPatternScale(1.0f)
// 	{
// 
// 	}
};

struct ST_OverlayPicInfo
{
	ISOC_CHAR chPicPath[MAX_PATH];//叠加图片的路径
	ISOC_RECT overlayRect;//要叠加图片的区域
};

struct ST_OverlayInfo
{
	enum EN_OverlayType
	{
		Text = 1,Picture = 2,Line = 3
	};
	ISOC_INT nOverlayID;//叠加信息id
	ISOC_INT nOverlayType;//叠加信息类型，1文字，2为图片，3为画线；
	union 
	{
		ST_OverlayFontInfo fontInfo;
		ST_OverlayLineInfo lineInfo;
		ST_OverlayPicInfo picInfo;
	}overlayInfo;
	ISOC_DWORDPTR dwReserved1;//保留字段1
	ISOC_DWORDPTR dwReserved2;//保留字段2

	ST_OverlayInfo():nOverlayID(0),nOverlayType(1), dwReserved1(0),dwReserved2(0)
	{
		overlayInfo.fontInfo.Init();
	}

	ST_OverlayInfo& operator =(const ST_OverlayInfo& info)
	{
		nOverlayID = info.nOverlayID;
		nOverlayType = info.nOverlayType;
		switch (nOverlayType)
		{
		case Text: //文字
		{
			memcpy(&this->overlayInfo.fontInfo, &info.overlayInfo.fontInfo, sizeof(ST_OverlayFontInfo));
			break;
		}
		case Picture: //图片
		{
			memcpy(&this->overlayInfo.picInfo, &info.overlayInfo.picInfo, sizeof(ST_OverlayPicInfo));
			break;
		}
		case Line: //画线
		{
			memcpy(&this->overlayInfo.lineInfo, &info.overlayInfo.lineInfo, sizeof(ST_OverlayLineInfo));
			break;
		}
		}
		dwReserved1 = info.dwReserved1;
		dwReserved2 = info.dwReserved2;
		return *this;
	}
};

struct ST_CatalogueInfo
{
	ISOC_CHAR strPoliceStation[64];//派出所
	ISOC_CHAR strMigeraterName[64];//迁移人
	ISOC_CHAR strCaseID[64];//案件编码
	ISOC_CHAR strCaseCode[64];//案件代号
	ISOC_CHAR strCaseRelator[64];//案件相关人
	ISOC_CHAR strOwnerDepart[64];//归口单位
	ISOC_CHAR strDealDepart[64];//承办单位
	ISOC_CHAR strCaseType[64];//案件类型
	ISOC_CHAR strDescribe[1024];//描述
	ST_CatalogueInfo()
	{
		ZeroMemory(&strPoliceStation,sizeof(strPoliceStation));
		ZeroMemory(&strMigeraterName,sizeof(strMigeraterName));
		ZeroMemory(&strCaseID,sizeof(strCaseID));
		ZeroMemory(&strCaseCode,sizeof(strCaseCode));
		ZeroMemory(&strCaseRelator,sizeof(strCaseRelator));
		ZeroMemory(&strOwnerDepart,sizeof(strOwnerDepart));
		ZeroMemory(&strDealDepart,sizeof(strDealDepart));
		ZeroMemory(&strDescribe,sizeof(strDescribe));
	}
	ST_CatalogueInfo ST_CatalogueInfo::operator =(const ST_CatalogueInfo& info)
	{
		ZeroMemory(&strPoliceStation,sizeof(strPoliceStation));
		ZeroMemory(&strMigeraterName,sizeof(strMigeraterName));
		ZeroMemory(&strCaseID,sizeof(strCaseID));
		ZeroMemory(&strCaseCode,sizeof(strCaseCode));
		ZeroMemory(&strCaseRelator,sizeof(strCaseRelator));
		ZeroMemory(&strOwnerDepart,sizeof(strOwnerDepart));
		ZeroMemory(&strDealDepart,sizeof(strDealDepart));
		ZeroMemory(&strDescribe,sizeof(strDescribe));
		lstrcpy(strPoliceStation,info.strPoliceStation);
		lstrcpy(strMigeraterName,info.strMigeraterName);
		lstrcpy(strCaseID,info.strCaseID);
		lstrcpy(strCaseCode,info.strCaseCode);
		lstrcpy(strCaseRelator,info.strCaseRelator);
		lstrcpy(strOwnerDepart,info.strOwnerDepart);
		lstrcpy(strDealDepart,info.strDealDepart);
		lstrcpy(strDescribe,info.strDescribe);
		return *this;
	}
};

struct ST_FileLockInfo
{
	ISOC_SYSTEMTIME	stStartTime;    //开始时间指从文件哪部分开始锁定
	ISOC_SYSTEMTIME	stEndTime;      //结束时间指锁定到文件哪部分
	ISOC_SYSTEMTIME	stUnLockDate;   //解除锁定的日期
	ISOC_INT		nLockUserID;
	ISOC_CHAR		strLockUserName[50]; //锁定用户的用户名
	ISOC_INT		nLockID;        //锁ID
	ISOC_CHAR		strLockDes[200];		//锁定描述
	ST_FileLockInfo():nLockUserID(0),nLockID(0)
	{
		ZeroMemory(&stStartTime,sizeof(ISOC_SYSTEMTIME));
		ZeroMemory(&stEndTime,sizeof(ISOC_SYSTEMTIME));
		ZeroMemory(&stUnLockDate,sizeof(ISOC_SYSTEMTIME));
		ZeroMemory(strLockUserName,sizeof(strLockUserName));
		ZeroMemory(strLockDes,sizeof(strLockDes));
	}
	ST_FileLockInfo& operator =(const ST_FileLockInfo& info)
	{
		stStartTime = info.stStartTime;
		stEndTime   = info.stEndTime;
		stUnLockDate= info.stUnLockDate;
		nLockID     = info.nLockID;
		nLockUserID = info.nLockUserID;
		lstrcpy(strLockUserName,info.strLockUserName);
		return *this;
	}

};

struct ST_FileLockItem
{
	ISOC_INT nLockID;
	ST_VodFileInfo fileInfo;
	ISOC_SYSTEMTIME stLockStartTime;
	ISOC_SYSTEMTIME stLockEndTime;
	ISOC_DWORDPTR dwReserved;

	ST_FileLockItem():nLockID(0),dwReserved(0)
	{
		ZeroMemory(&stLockStartTime,sizeof(ISOC_SYSTEMTIME));
		ZeroMemory(&stLockEndTime,sizeof(ISOC_SYSTEMTIME));
	}

	ST_FileLockItem& operator =(const ST_FileLockItem& info)
	{
		nLockID = info.nLockID;
		fileInfo = info.fileInfo;
		stLockStartTime = info.stLockStartTime;
		stLockEndTime = info.stLockEndTime;
		dwReserved = info.dwReserved;
        return *this;
	}
};

//服务器信息
struct ST_ServerInfo
{
	ISOC_INT nServerInfoID;
	ISOC_CHAR strServerName[50];
	ISOC_CHAR strServerIP[16];
	ISOC_INT nServerPort;
	ISOC_CHAR strLoginUserName[64];
	ISOC_CHAR strLoginPassword[64];
	enum EN_ServerType
	{
		ST_DCSServer,ST_TVWallServer
	};
	EN_ServerType enServerType;
	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;

	ST_ServerInfo()
	{
		ZeroMemory(this,sizeof(ST_ServerInfo));
	}

	ST_ServerInfo(const ST_ServerInfo& info)
	{
		CopyMemory(this,&info,sizeof(ST_ServerInfo));
	}

	ST_ServerInfo& operator =(const ST_ServerInfo& info)
	{
		CopyMemory(this,&info,sizeof(ST_ServerInfo));
		return *this;
	}
};

//////////////////////////监察管理相关////////////////////////////////
struct ST_SuperviseUserInfo
{
	ISOC_INT nUserID;
	ISOC_CHAR strUserName[64];
	ISOC_INT nType;
	ISOC_CHAR strDescription[2048];
	ISOC_CHAR strUserICMSSign[64]; //用户所在系统的ICMSSign
	ST_SuperviseUserInfo()
	{
		nUserID = 0;
		nType = 0;
		ZeroMemory(strUserName,64);
		ZeroMemory(strDescription,2048);
		ZeroMemory(strUserICMSSign, 64);
	}
	ST_SuperviseUserInfo(const ST_SuperviseUserInfo& src)
	{
		nUserID = src.nUserID;
		nType = src.nType;
		lstrcpy(strUserName, src.strUserName);
		lstrcpy(strDescription, src.strDescription);
		lstrcpy(strUserICMSSign, src.strUserICMSSign);
	}
	ST_SuperviseUserInfo& operator= (const ST_SuperviseUserInfo& src)
	{
		nUserID = src.nUserID;
		nType = src.nType;
		lstrcpy(strUserName, src.strUserName);
		lstrcpy(strDescription, src.strDescription);
		lstrcpy(strUserICMSSign, src.strUserICMSSign);
		return *this;
	}
};

struct ST_SuperviseItem
{
	ISOC_INT  nSuperviseID;			   //监察事件ID
	ISOC_INT  nSuperviseType;		   //事件状态 0.未处理 1.已处理
	ISOC_CHAR strDescription[1024];    //发起人描述 
	ST_SuperviseUserInfo* pstUserList; //用户用户列表
	ISOC_INT  nUserInfoCount;		   //用户列表长度
	ISOC_INT  nDevID;				   //关联设备ID
	ISOC_SYSTEMTIME stStartTime;       //事件起始时间
	ISOC_SYSTEMTIME stEndTime;         //事件结束时间
	ST_SuperviseItem()
	{
		nSuperviseID = 0;
		nSuperviseType = 0;
		ZeroMemory(strDescription, 1024);
		pstUserList = NULL;
		nUserInfoCount = 0;
		nDevID = 0;
		ZeroMemory(&stStartTime, sizeof(ISOC_SYSTEMTIME));
		ZeroMemory(&stEndTime, sizeof(ISOC_SYSTEMTIME));
	}
};

////////////////////////////////////大屏相关//////////////////////////
struct ST_DatabaseInfo
{
	ISOC_CHAR strIP[20];
	ISOC_INT nPort;
	ISOC_CHAR strUserName[20];
	ISOC_CHAR strPassword[20];
	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;

	ST_DatabaseInfo()
	{
		ZeroMemory(this,sizeof(ST_DatabaseInfo));
	}

	ST_DatabaseInfo& operator =(const ST_DatabaseInfo& info)
	{
		CopyMemory(this,&info,sizeof(ST_DatabaseInfo));
		return *this;
	}
};

struct ST_DevicePluginItem	//SDK插件公用结构体
{
	ISOC_ID nID;
	ISOC_CHAR strDeviceName[200];
	ISOC_CHAR strDeviceIP[16];
	ISOC_WORD sPort;
	ISOC_CHAR strUserName[200];
	ISOC_CHAR strUserPwd[200];
	ISOC_INT  nDevType;  //设备主类型
	ISOC_INT  nDevSubType;//设备子类型
	ISOC_CHAR strModelType[200];	//设备型号描述

	//串口信息
	ISOC_CHAR strSeriaProtocol[200];	    //串口协议,比如RS232
	ISOC_INT  nBaudrate;				    //波特率
	ISOC_INT  nDatabits;				    //数据位
	ISOC_INT  nStopBits;				    //停止位
	ISOC_INT  nParityType;			        //奇偶校验
	ISOC_CHAR strComSeq[200];			    //配置的COM口序号

	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;

	ST_DevicePluginItem():nID(0),sPort(0),nBaudrate(0),nDatabits(0)
		,nStopBits(0),nParityType(0),dwReserved1(0),dwReserved2(0)
		,nDevType(0),nDevSubType(0)
	{
		ZeroMemory(strDeviceName, sizeof(strDeviceName));
		ZeroMemory(strDeviceIP, sizeof(strDeviceIP));
		ZeroMemory(strUserName, sizeof(strUserName));
		ZeroMemory(strUserPwd, sizeof(strUserPwd));
		ZeroMemory(strSeriaProtocol, sizeof(strSeriaProtocol));
		ZeroMemory(strComSeq, sizeof(strComSeq));
		ZeroMemory(strModelType, sizeof(strModelType));
	}

	ST_DevicePluginItem(const ST_DevicePluginItem& src)
	{
		nID = src.nID;
		lstrcpy(strDeviceName, src.strDeviceName);
		lstrcpy(strDeviceIP, src.strDeviceIP);
		sPort = src.sPort;
		lstrcpy(strUserName, src.strUserName);
		lstrcpy(strUserPwd, src.strUserPwd);
		lstrcpy(strModelType, src.strModelType);
		nDevType = src.nDevType;
		nDevSubType = src.nDevSubType;

		lstrcpy(strSeriaProtocol, src.strSeriaProtocol);
		nBaudrate = src.nBaudrate;
		nDatabits = src.nDatabits;
		nStopBits = src.nStopBits;
		nParityType = src.nParityType;
		lstrcpy(strComSeq, src.strComSeq);

		dwReserved1 = src.dwReserved1;
		dwReserved2 = src.dwReserved2;
	}

	ST_DevicePluginItem& operator= (ST_DevicePluginItem& src)
	{
		nID = src.nID;
		lstrcpy(strDeviceName, src.strDeviceName);
		lstrcpy(strDeviceIP, src.strDeviceIP);
		sPort = src.sPort;
		lstrcpy(strUserName, src.strUserName);
		lstrcpy(strUserPwd, src.strUserPwd);
		lstrcpy(strModelType, src.strModelType);
		nDevType = src.nDevType;
		nDevSubType = src.nDevSubType;

		lstrcpy(strSeriaProtocol, src.strSeriaProtocol);
		nBaudrate = src.nBaudrate;
		nDatabits = src.nDatabits;
		nStopBits = src.nStopBits;
		nParityType = src.nParityType;
		lstrcpy(strComSeq, src.strComSeq);

		dwReserved1 = src.dwReserved1;
		dwReserved2 = src.dwReserved2;
		return *this;
	}

	bool operator< (const ST_DevicePluginItem& src)const
	{
		return nID < src.nID;
	}

	bool operator== (const ST_DevicePluginItem& src)const
	{
		return ((nID == src.nID) && nDevType == src.nDevType && nDevSubType == src.nDevSubType && lstrcmp(strDeviceIP, src.strDeviceIP) == 0);
	}
};

struct ST_UntreadedAlarmInfo
{
    struct ST_P_AlarmRelate
    {
        ISOC_CHAR Name[50];                     //报警关联用户名
        ST_P_AlarmRelate()
        {
            ZeroMemory(this,sizeof(ST_P_AlarmRelate));
        }
    };                              
    struct ST_P_PlanRelate
    {
        ISOC_CHAR strName[50];                  //计划关联人的名称（DB）
        ISOC_CHAR strPPhone[30];                //计划关联人的电话号码（DB）
        ST_P_PlanRelate()
        {
            ZeroMemory(this,sizeof(ST_P_PlanRelate));
        }
    }; 
    struct ST_P_DevRelate
    {
        ISOC_INT nDevLinkID;                    //关联设备所在域的ID
        ISOC_CHAR strDevLinkICMSSign[64];       //关联设备域标识（DB）
        ST_P_DevRelate()
        {
            ZeroMemory(this,sizeof(ST_P_DevRelate));
        }
    }; 

	ISOC_INT            nAlarmEventID;          //报警事件ID
	ISOC_INT            nAlarmType;             //报警类型 
	ISOC_CHAR           strContent[300];		//报警类型描述
	ISOC_CHAR			strAlarmDes[300];		//报警描述内容（DB） 
	ISOC_INT            nALevel;                //报警等级
	ISOC_UINT           nDevType;               //设备类型（通道.....）
	ISOC_CHAR           strDevICMSSign[64];     //设备的域标识（DB）
	ISOC_INT            nDevICMSSignID;         //设备所在域的ID
	ISOC_BOOL           bWithMap;               //报警是否打开地图
	ISOC_BOOL           bWithSound;             //报警是否播放音频
	ISOC_CHAR           strSoundFile[256];      //音频文件名
	ISOC_UINT           nCurTranState;          //处理状态
	ISOC_SYSTEMTIME     AlarmTime;              //报警产生时间                      

    //可用iSOC链表操作函数进行取值(eg:iSOC_GetFirstDataListItem)
    ISOC_DWORDPTR       ptrAlarmRelate;         //(ST_P_AlarmRelate)报警关联用户名链表 
    ISOC_DWORDPTR       ptrPlanRelate;          //(ST_P_PlanRelate)计划关联信息链表
    ISOC_DWORDPTR       ptrDevRelate;           //(ST_P_DevRelate)关联设备信息链表

    ISOC_INT            nPlanID;                //计划ID
    ISOC_CHAR           strPlanName[125];       //计划名称（DB）
    ISOC_CHAR           strPlanContent[300];    //计划内容
    ISOC_DWORDPTR       dwReserved1;            //预留

    ST_UntreadedAlarmInfo()
    {
        ZeroMemory(this,sizeof(ST_UntreadedAlarmInfo));
    }

    ST_UntreadedAlarmInfo& operator =(const ST_UntreadedAlarmInfo& info)
    {
        CopyMemory(this,&info,sizeof(ST_UntreadedAlarmInfo));
        return *this;
    }
};

struct ST_ExportTextCfg
{
    ISOC_INT      nOverlayID;//叠加信息id
    ISOC_CHAR     chOverlayInfo[MAX_PATH];//叠加信息内容，当为文字时其内容为要叠加的文字
    ISOC_CHAR     chFontPath[MAX_PATH]; //叠加的字体路径
    ISOC_INT      nFontSize;//文字界面
    ISOC_DWORD	  dwFontColor;
    ISOC_INT      nHAlign;	//水平对齐方式 1,左对齐 2,居中 3,右对齐
    ISOC_INT      nHOffset;
    ISOC_INT      nVAlign;	//垂直对齐方式 1,上对齐 2,居中 3,下对齐
    ISOC_INT      nVOffset;
    ISOC_DWORDPTR dwReserved1;//保留字段1
    ISOC_DWORDPTR dwReserved2;//保留字段2
};

struct ST_VideoEncodeInitParam
{
	ISOC_INT nSize;
	ISOC_INT nCodecID;
	ISOC_INT nWidth;
	ISOC_INT nHeight;
	ISOC_INT nGopSize;
	ISOC_INT nFPS;
	ISOC_INT nBitrate;
	ISOC_INT nMaxBFrames;
	ISOC_FLOAT fQCompress; //从0.0 到 1.0
	ISOC_INT nInputDataFormat;

	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;

	ST_VideoEncodeInitParam()
	{
		memset(this, 0, sizeof(ST_VideoEncodeInitParam));
		nSize = sizeof(ST_VideoEncodeInitParam);
	}
};

struct ST_VideoInitParam
{
	ST_VideoInitParam():nCodecId(0),nPicWidth(0),nPicHeight(0),fFrameRate(.0),nRate(0),nExtendKind(0),nExtendLen(0)
		,pExtendData(0),dwReserved1(0),dwReserved2(0){}	
	ISOC_INT		nCodecId; //视频编码ID
	ISOC_INT		nPicWidth; //视频宽
	ISOC_INT		nPicHeight; //视频高
	ISOC_FLOAT		fFrameRate; //帧率
	ISOC_INT		nRate; //码率
	ISOC_INT		nExtendKind; //扩展数据类型，目前为0
	ISOC_INT		nExtendLen; //扩展数据长度，对应私有数据长度
	ISOC_BYTE*		pExtendData; //扩展数据，对应私有数据
	ISOC_DWORDPTR   dwReserved1; //保留参数1
	ISOC_DWORDPTR   dwReserved2; //保留参数2
};

struct ST_AudioInitParam 
{
	ST_AudioInitParam():nCodecId(0),fBitRate(.0),nChannel(0),nSamplesPerSec(0),nBlockAlign(0),bDecode(ISOC_TRUE)
		,nExtendKind(0),nExtendLen(0),pExtendData(0){}
	ISOC_INT		nCodecId; //音频编码ID
	ISOC_INT		nChannel; //通道数
	ISOC_INT		nSamplesPerSec; //采样率
	ISOC_FLOAT		fBitRate; //码率
	ISOC_INT		nBlockAlign; //块对齐字节数
	ISOC_BOOL		bDecode; //是否解码，解码为ISOC_TRUE，编码为ISOC_FALSE
	ISOC_INT		nExtendKind;//扩展数据类型，目前为0
	ISOC_INT		nExtendLen;//扩展数据长度，对应私有数据长度
	ISOC_BYTE*		pExtendData;//扩展数据，对应私有数据
};

struct ST_VideoParam
{
	ISOC_INT nHeight; //视频宽
	ISOC_INT nWidth; //视频高
	ISOC_UINT64 uPTS; //时间戳
	ISOC_DWORDPTR dwReserved1; //保留字段1
	ISOC_DWORDPTR dwReserved2; //保留字段2
};

struct ST_FileParam
{
	ISOC_CHAR     chFilePath[MAX_PATH];		//文件路径
	ISOC_UINT64	  uStartTs;					//开始时间
	ISOC_UINT64	  uEndTs;					//结束时间
	ISOC_DWORDPTR dwReserved1;				//保留字段1
	ISOC_DWORDPTR dwReserved2;				//保留字段2
};

#pragma pack(pop)
#endif
