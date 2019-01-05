#pragma once

#ifndef _ICMS_UNIQUEDEFINE_H
#define _ICMS_UNIQUEDEFINE_H

/************************自定义代码集规则********************************/
//资源类型代码
//级联
#define ICMS_RESOUCE_SOBEY_MILICMS			0x00100001

//Sobey
#define ICMS_RESOUCE_SOBEY_NVR2000			0x00100002
#define ICMS_RESOUCE_SOBEY_NVR3000			0x00100003
#define ICMS_RESOUCE_SOBEY_OEMNVS			0x00100004
#define ICMS_RESOUCE_SOBEY_DVS0100BHD	    0x00110005

//sony 0x00010000
#define ICMS_RESOUCE_SONY_DF40P				0x00010001
#define ICMS_RESOUCE_SONY_CS1011			0x00010002
#define ICMS_RESOUCE_SONY_RZ25P				0x00010003
#define ICMS_RESOUCE_SONY_RX570P			0x00010004
#define ICMS_RESOUCE_SONY_RZ50P				0x00010005
#define ICMS_RESOUCE_SONY_CM120				0x00010006
#define ICMS_RESOUCE_SONY_DF70P				0x00010007
#define ICMS_RESOUCE_SONY_DS60				0x00010008
#define ICMS_RESOUCE_SONY_CS20				0x00010009
#define ICMS_RESOUCE_SONY_RX550P			0x0001000A
#define ICMS_RESOUCE_SONY_DM110				0x0001000B
#define ICMS_RESOUCE_SONY_DS10				0x0001000C
#define ICMS_RESOUCE_SONY_V704				0x0001000D

//海康 0x00020000
//IPC DS-ZCD712PF
#define ICMS_RESOUCE_DS_ZCD712PF			0x00020001
//DVS DS-6102HF
#define ICMS_RESOUCE_DS_6102HF			    0x00020002
//DVR DS-8004HF-S
#define ICMS_RESOUCE_DS_8004HFS			    0x00020003
//DS-2DF1-401E    10倍光变室内网络球
#define ICMS_RESOUCE_DS_2DF1401E		   0x00020004
//DS-2CD852MF-E   高清网络摄像机
#define ICMS_RESOUCE_DS_2CD852MFE		   0x00020005
//DS-2CD892PF     网络枪型摄像机
#define ICMS_RESOUCE_DS_2CD892PF		   0x00020006
//DS-2CD892P-IR3  网络红外辅助光源摄像机
#define ICMS_RESOUCE_DS_2CD892PIR3		   0x00020007

//DS-6104HC       视频服务器
#define ICMS_RESOUCE_DS_6104HC			   0x00020008
//DS-6101HF-IP-A  视频服务器
#define ICMS_RESOUCE_DS_6101HFIPA		   0x00020009
//DS-2CD6001HF/B  智能视频服务器
#define ICMS_RESOUCE_DS_2CD6001HFB		   0x0002000a
//DS-2CD6001HF/P  智能视频服务器
#define ICMS_RESOUCE_DS_2CD6001HFP		   0x0002000b

//盈码
#define ICMS_RESOUCE_HC_ENMA		       0x00020201
//浩然
#define ICMS_RESOUCE_HC_JTDM		       0x00020202
//博超
#define ICMS_RESOUCE_HC_SUPERB		       0x00020203


//大华 0x00030000
//DH-DVR0404LN-S
#define ICMS_RESOUCE_DH_DVR0404LN			0x00030001
//DH-NVS04EB
#define ICMS_RESOUCE_DH_NVS04EB			    0x00030002
//DH-IPC-FDB465P
#define ICMS_RESOUCE_DH_IPCFDB465P			0x00030003

//Vista 报警主机
#define  ICMS_RESOUCE_VISTA120              0x00040001

//Axis  0x00050000
#define  ICMS_RESOUCE_AXIS_Q1755            0x00050001


//深圳耀德  0x00060000
#define  ICMS_RESOUCE_SZYD_81L            0x00060001

//DDS门禁  0x00070000
#define  ICMS_RESOUCE_DDS_TWODOOR         0x00070001


//安杰士  0x00080000
#define  ICMS_RESOUCE_EGISE_6208L         0x00080001

//远程插件  0x00090000
#define  ICMS_RESOUCE_REMOTE_PLUG         0x00090001

//其他资源类型待补充

//ipgs设备GUID
#define ICMS_EQUMODEGUID_IPGS (_T("{FBB0C875-BE9B-11E2-8492-FB031872F268}"))

//设备类型
#define ICMS_EQU_DVR					0x0101		//DVR
#define ICMS_EQU_NVR					0x0102		//NVR
#define ICMS_EQU_IPVIDICON				0x0103		//IPC
#define ICMS_EQU_DVS					0x0104		//DVS
#define ICMS_EQU_HOSTALARM              0x0105      //报警主机
#define ICMS_EQU_CASCADE				0x0106		//级联
#define ICMS_EQU_INDPC			        0x0107		//工控机
#define ICMS_EQU_DVS5th					0x0108
#define ICMS_EQU_IPC5th					0x0109
#define ICMS_EQU_CTRLBOARD              0x010a      //键盘
#define ICMS_EQU_ENTRANCEGUARD			0x010b      //门禁（267）
#define ICMS_EQU_PATROL					0x010c      //巡更 （268）
#define ICMS_EQU_MATRIX					0x010d     //矩阵（269）
#define ICMS_EQU_GRAPHJOINTER			0x010e     //拼接器（270）
#define ICMS_EQU_SCREEN					0x010f     //屏幕设备（271）
#define ICMS_EQU_DECORDER				0x0110		//解码器（272）


//探头输入类型
#define ICMS_SPYINPUTTYPE_OPEN			0x2001		//常开（8193）
#define ICMS_SPYINPUTTYPE_CLOSE			0x2002		//常闭（8194）

//输出连接类型
#define ICMS_OUTPUTTYPE_OPEN		    0x3001	  //常开（12289）
#define ICMS_OUTPUTTYPE_CLOSE		    0x3002	 //常闭（12290）

//设备装配角角度
#define ICMS_DEVICE_ANGLE_0				0x0001
#define	ICMS_DEVICE_ANGLE_90			0x0002
#define	ICMS_DEVICE_ANGLE_180			0x0003
#define	ICMS_DEVICE_ANGLE_270			0x0004


//摄像头类型代码
#define ICMS_VID_HIGHBALL				0x0301		//快球
#define ICMS_VID_GUNNBALL				0x0302		//枪机
#define ICMS_VID_HALFBALL				0x0303		//半球

//码率
#define ICMS_VIDEO_LOWRATE				0x0801		//低码率
#define ICMS_VIDEO_HIGHRATE				0x0802		//高码率

//探头报警类型
#define ICMS_SPYALARM_BAGINBREAAK		0x0401		//非法入侵

////报警输出类型
#define ICMS_OUTPUT_EMAL				0xE301  //邮件输出
#define ICMS_OUTPUT_SMS					0xE302  //短信输出
#define ICMS_OUTPUT_TEL					0xE303  //电话输出
#define ICMS_OUTPUT_LED					0xE304  //LED输出
#define ICMS_OUTPUT_LIGHT				0xE305  //报警灯输出


//系统权限
#define ICMS_SYS_AUT_BASE				0x0601		//基本设置
#define ICMS_SYS_AUT_LOCALKINPLAN		0x0602		//本地录像计划表设置
#define ICMS_SYS_AUT_GROUPSURVEY		0x0603		//分组轮巡

//子设备权限
#define ICMS_SUBEQU_AUT_NETPARUPD		0x0701		//远程参数修改
#define ICMS_SUBEQU_AUT_NETRESTART		0x0702		//远程重启
#define ICMS_SUBEQU_AUT_STATESEARCH		0x0703		//状态查询
#define ICMS_SUBEQU_AUT_VOICELISTEN		0x0704		//语音监听
#define ICMS_SUBEQU_AUT_VOICETALK		0x0705		//语音对讲


//日志分类
#define ICMS_LOG_SYSTEM					0x0A01		//系统日志
#define ICMS_LOG_ALARM					0x0A02		//报警日志
#define ICMS_LOG_OPERATION				0x0A03		//操作日志
#define ICMS_LOG_PATROL					0x0A04		//巡检日志

//文件类型
#define ICMS_FILE_MANUALREC				0x0B01		//手动录像
#define ICMS_FILE_ALARMREC				0x0B02		//报警录像
#define ICMS_FILE_SCHEMEREC				0x0B03		//计划录像
#define ICMS_FILE_HISTORY				0x0B04		//历史上载
#define ICMS_FILE_ALARMSNAP				0x0B05		//报警抓帧
#define ICMS_FILE_MANUALSNAP			0x0B06		//手动抓帧

//状态类型
#define ICMS_STATE_ORDERPROG			0x0C01		//点播
#define ICMS_STATE_DIRECTSEED			0x0C02		//直播
#define ICMS_STATE_PLAN					0x0C03		//计划

//计划类型
#define ICMS_PLAN_KINESCOPE				0x0D01		//录像
#define ICMS_PLAN_GUARDAGAINST			0x0D02		//布防撤防
#define ICMS_PLAN_PATROL				0x0D03		//巡检

/*此处请重新修改
#define ICMS_PLAN_PATROL				0x0D04		//上载
*/

//服务器类型//使用后面的源类型定义
//#define ICMS_SERVER_CONTROL				0x1001		//控制服务器
//#define ICMS_SERVER_ALARM				    0x1002		//报警服务器
//#define ICMS_SERVER_MAP					0x1303		//MAP服务器
//#define ICMS_SERVER_GIS					0x1004		//GIS服务器

//巡检类型
#define ICMS_PATROL_MANUAL				0x1101		//手动
#define ICMS_PATROL_AUTO				0x1102		//自动

//Matrix板卡类型代码
#define ICMS_MATRIX_VGA					0x1201		//VGA
#define ICMS_MATRIX_MD					0x1202		//MD

//Matrix板卡型号代码
#define ICMS_MATRIXNUM_USUAL			0x1301		//通用
#define ICMS_MATRIXNUM_HKDS4004MD		0x1302		//海康_DS4004MD

//电视墙服务器板卡输出类型	
#define  ICMS_MATRIX_OUTTYPE_ONE   0x8001	//单输出
#define  ICMS_MATRIX_OUTTYPE_TWO   0x8002	 //双输出
#define  ICMS_MATRIX_OUTTYPE_FOUR  0x8003	 //四输出
#define  ICMS_MATRIX_OUTTYPE_EIGHT 0x8004	 //八输出

//操作日志类型
#define  ICMS_OPERLOG_SYS         0x1901	//系统控制(开/关机)（6401）
#define  ICMS_OPERLOG_TALK        0x1902	//语音控制（6402）
#define  ICMS_OPERLOG_SNAP        0x1903	//抓帧（6403）
#define  ICMS_OPERLOG_MANREC      0x1904    //录像（6404）
#define  ICMS_OPERLOG_VOD         0x1905	//回放（6405）
#define  ICMS_OPERLOG_LIVE        0x1906    //实时流（6406）
#define  ICMS_OPERLOG_MANUAL      0x1907	//云台控制（6407）
#define  ICMS_OPERLOG_MANCIRCLE   0x1908    //巡航控制（6408）
#define  ICMS_OPERLOG_SETMAN      0x1909	//配置管理（6409）
#define  ICMS_OPERLOG_STORE       0x190a    //存储管理（6410）
#define  ICMS_OPERLOG_TASK        0x190b    //任务管理（6411）
#define  ICMS_OPERLOG_MANTEST     0x190c    //设备巡检（6412）
#define  ICMS_OPERLOG_TRANSFILE   0x190d    //文件迁移 (6413)
#define  ICMS_OPERLOG_UPLOADFILE   0x190e    //文件上载 (6414)

/***************************应用程序操作********************************/
//数据库操作类型
#define ICMS_DBT_NON					0xF001		//不操作
#define ICMS_DBT_INSERT					0xF002		//添加操作
#define ICMS_DBT_UPDATE					0xF003		//修改操作
#define ICMS_DBT_DELETE					0xF004		//删除操作
#define ICMS_DBT_SELETE					0xF005		//选择操作

/*************************** Enum宏定义 ********************************/
//报警联动录像 -- 码流类型
#define ICMS_DATARATE_LOW				0x0801		//低码流
#define ICMS_DATARATE_HIGH				0x0802		//高码流

//报警联动输出 -- 输出恢复方式
#define ICMS_OUTRENEW_DELAY				0x0901		//延迟恢复
#define ICMS_OUTRENEW_ALARMOVER			0x0902		//报警处理完恢复
#define ICMS_OUTRENEW_MANUAL			0x0903		//手动恢复

//操作源类型
#define ICMS_OPERSRC_EMAP				0x5001		//地图
#define ICMS_OPERSRC_USER				0x5002		//用户信息
#define ICMS_OPERSRC_SUBEQU				0x5003		//子设备



//报警源类型
#define ICMS_ALARMSOURCE_SUBEQU			0x4001	//子设备报警
#define ICMS_ALARMSOURCE_SERVER			0x4002	//服务器报警
#define ICMS_ALARMSOURCE_TASK			0x4003	//未完成任务报警

//报警主类型
#define ICMS_MAINSOURCE_CHANNEL			    0xE100		//通道
#define ICMS_MAINSOURCE_PROBE				0xE200		//探头
#define ICMS_MAINSOURCE_OUTPUT		   		0xE300		//输出
#define ICMS_MAINSOURCE_SYSTEM				0xE400		//系统
#define ICMS_MAINSOURCE_MANUAL				0xE500		//手动
#define ICMS_MAINSOURCE_OTHER				0xE600		//其他
#define ICMS_MAINSOURCE_PATROL				0xE700		//巡更
#define ICMS_MAINSOURCE_EGUARD				0xE800		//门禁


//报警事件类型代码
//设备
#define ICMS_ALARMEVENT_DEVOPENFAILED			0xE001	/* 打开设备失败 */
#define	ICMS_ALARMEVENT_CHANNELGETSTREAMFAILED	0xE002	/* 获取实时流失败 */
#define ICMS_ALARMEVENT_CHANNELGETSTREAMSUCCESS	0xE003	/* 实时流恢复 */

#define ICMS_ALARM_EQUIPMENT_STATE_REQ			0xE004		//获取设备布防状态
#define ICMS_ALARM_EQUIPMENT_STATE_ACK			0xE005

//通道
#define	ICMS_ALARMEVENT_MOTIONPROBE           0xE101    //移动检测
#define ICMS_ALARMEVENT_VIDEOLOST             0xE102	//视频丢失
#define	ICMS_ALARMEVENT_SHIELDALARM           0xE103	//镜头遮挡
#define ICMS_ALARMEVENT_DEPA_VMF              0xE110    //高级智能报警(越界、逆向……) 
#define	ICMS_ALARMEVENT_FIELD_CROSS           0xE111	//周界保护：越界
#define	ICMS_ALARMEVENT_FIELD_OVERLINE        0xE112	//周界保护：跨线
#define	ICMS_ALARMEVENT_FIELD_WANDER          0xE113	//周界保护：徘徊
#define	ICMS_ALARMEVENT_FIELD_DISAPEAR        0xE114	//周界保护：消失
#define	ICMS_ALARMEVENT_MANACTION_CONVERSE    0xE115	//人行为检测：倒地
#define	ICMS_ALARMEVENT_FIELD_LEAVEBEHIND     0xE121	//周界保护：遗留
#define	ICMS_ALARMEVENT_MANACTION_RATEABN     0xE122	//人行为检测：速度异常
#define	ICMS_ALARMEVENT_VAHICLE_CONVERSE      0xE131	//车辆行为检测：逆行
#define	ICMS_ALARMEVENT_VAHICLE_SCRAM         0xE132    //车辆行为检测：急停
#define	ICMS_ALARMEVENT_VAHICLE_ILLSTOP       0xE133	//车辆行为检测：非法停车
#define	ICMS_ALARMEVENT_VAHICLE_CROSSLINE     0xE134	//车辆行为检测：车辆越线
#define	ICMS_ALARMEVENT_OBJECT_COUNTNUM       0xE141    //物体／人数统计报警
#define	ICMS_ALARMEVENT_OBJECT_DUBOVERLINE    0xE142 //双向越界   原:周界保护：跨线 双向
#define	ICMS_ALARMEVENT_OBJECT_HOLD           0xE143 //人员滞留
#define	ICMS_ALARMEVENT_OBJECT_TAMPERING      0xE144 //防破坏检测（遮挡、 喷涂、虚焦、移位）
#define	ICMS_ALARMEVENT_OBJECT_AUDIO          0xE145//智能音频检测（声音探测、异响探测）
#define	ICMS_ALARMEVENT_FRAMERATE_ERROR       0xE146//帧率异常
#define	ICMS_ALARMEVENT_VIDEOSTREAM_ERROR     0xE147//录像失败
#define	ICMS_ALARMEVENT_REALSTREAM_INTERRUPT  0xE148//实时流中断
#define	ICMS_ALARMEVENT_DEVICE_OPEN_FAIL      0xE149//打开设备失败(编码器)


//探头//输入
#define	ICMS_ALARMEVENT_INFRARED 			  0xE201    //红外探测器
#define	ICMS_ALARMEVENT_MACROWAVE  	 		  0xE202    //微波探测器
#define	ICMS_ALARMEVENT_ULTRASONIC  	 	  0xE203    //超声波探测器
#define	ICMS_ALARMEVENT_DOORPROTECT  		  0xE204    //门磁
#define	ICMS_ALARMEVENT_PERIMETER    		  0xE205    //周界报警探测器
#define	ICMS_ALARMEVENT_BURNGAS      		  0xE206    //燃气探测器
#define	ICMS_ALARMEVENT_FROGPROBE    		  0xE207    //烟雾探测器
#define	ICMS_ALARMEVENT_SHAKEPROBE   		  0xE208    //震动探测器
#define	ICMS_ALARMEVENT_GLASSBROKE   		  0xE209    //玻璃破碎探测器
#define	ICMS_ALARMEVENT_TEMPERATURE   		  0xE20A    //温度探测器
#define	ICMS_ALARMEVENT_EXIBUTTON    		  0xE20B    //紧急按钮
#define	ICMS_ALARMEVENT_FINGERPRINT    		  0xE20C    //指纹检测报警

#define	ICMS_ALARMEVENT_OPENTOCLOSE    		  0xE211    //开到关
#define	ICMS_ALARMEVENT_CLOSETOOPEN    		  0xE212    //关到开

//输出
#define	ICMS_ALARMEVENT_SOUNDLIGHT 			  0xE301    //声光报警

//系统
#define ICMS_ALARMEVENT_EQUERR				  0xE401	//前端设备故障报警
#define ICMS_ALARMEVENT_SERVER				  0xE402	//服务器故障报警
#define ICMS_ALARMEVENT_NOCOMPLETE			  0xE403	//未完成任务报警
#define ICMS_ALARMEVENT_NETERROR			  0xE404	//网络故障报警
#define ICMS_ALARMEVENT_FULLDISK			  0xE405	//硬盘满报警
#define ICMS_ALARMEVENT_DISKBREAK			  0xE406	//硬盘故障报警
#define ICMS_ALARMEVENT_DECORDERROR			  0xE407	//解码卡错误报警
#define ICMS_ALARMEVENT_CPUOVER			      0xE408	//CPU超负荷报警
#define ICMS_ALARMEVENT_WRITEFAILED			  0xE409	//写文件失败报警
#define ICMS_ALARMEVENT_ENCRYPTDOGERR		  0xE40A	//检测加密狗报警
#define ICMS_ALARMEVENT_NETRECONNECT		  0xE40B	//网络重新连接成功
#define ICMS_ALARMEVENT_ALARMDEFENSE	  	  0xE903	  //防区报警
#define ICMS_ALARMEVENT_TROUBLEDEFENSE	   	  0xE904	  //防区故障

//手动
#define ICMS_ALARMEVENT_MANUAL				  0xE501	//手动报警
//其他
#define ICMS_ALARMEVENT_OTHER				  0xE601	//其他报警
#define ICMS_ALARMEVENT_TEL				      0xE602	//电话报警
#define ICMS_ALARMEVENT_SMS				      0xE603	//短信报警

//巡更
#define ICMS_ALARMEVENT_NOTARRIVE 		      0xE701    //未到巡更点

//门禁
#define	ICMS_ALARMEVENT_MGMLOCK 		   0xE801    //磁力锁控制
#define	ICMS_ALARMEVENT_DOORMGM 	       0xE802    //门磁
#define	ICMS_ALARMEVENT_CARDREADER	       0xE803    //读卡器输入
#define	ICMS_ALARMEVENT_DOORRELEASE        0xE804    //玻璃破碎
#define	ICMS_ALARMEVENT_DOORBUTTON	       0xE805    //出门按钮
#define	ICMS_ALARMEVENT_FINGERMARK		      0xE806    //指纹识别
#define ICMS_ALARMEVENT_DOORACCESS	          0xE807    //正常授权开门
#define ICMS_ALARMEVENT_DOORDENIED	          0xE808    //非法卡开门
#define ICMS_ALARMEVENT_DOORILLEGAL	          0xE809    //密码错误
#define ICMS_ALARMEVENT_DOORCLOSED	          0xE80A    //门关闭
#define ICMS_ALARMEVENT_DOORFORCED	          0xE80B    //门强迫进入
#define ICMS_ALARMEVENT_DOORHELD	          0xE80C    //开门时间过长
#define ICMS_ALARMEVENT_DOORBELL              0xE80D    //门铃请求    
#define ICMS_ALARMEVENT_DOORINTIMIDATION	  0xE81E	//胁迫开门
#define ICMS_ALARMEVENT_DOORLINKAGEOPEN	      0xE81F	//联动开门
#define ICMS_ALARMEVENT_DOORALWAYSOPEN	      0xE810	//门常开
#define ICMS_ALARMEVENT_DOORALWAYSCLOSE		  0xE811	//门常闭
#define ICMS_ALARMEVENT_DOOROVERLOAD          0xE812	//进门人数超员考勤类
#define ICMS_ALARMEVENT_DOORATTENDANCE        0xE813    //考勤事件

//音频解码器定义
#define ICMS_AUDIOCODEC_G711_64			0x7001		// G7.11（64kbps）
#define ICMS_AUDIOCODEC_G726_40			0x7002		// G7.26（40kbps）
#define ICMS_AUDIOCODEC_G726_32			0x7003		// G7.26（32kbps）
#define ICMS_AUDIOCODEC_G726_24			0x7004		// G7.26（24Kbps）
#define ICMS_AUDIOCODEC_G726_16			0x7005		// G7.26（16bps）


//子设备类型
#define ICMS_SUBEQU_CHANNEL				0x0201		//通道
#define ICMS_SUBEQU_SPY					0x0202		//探头
#define ICMS_SUBEQU_OUTPUT				0x0203		//输出
#define ICMS_SUBEQU_EGUARD				0x0204		//门禁(516)
#define ICMS_SUBEQU_PATROL				0x0205		//巡更(517)
#define ICMS_SUBEQU_DEARAE				0x0206		//防区(518)


//报警联动类型
#define	ICMS_ACTION_RECORD  0x1601 //报警录像
#define	ICMS_ACTION_SNAP    0x1602 //报警抓帧
#define	ICMS_ACTION_PTZ     0x1603	//云台联动
#define	ICMS_ACTION_OUTPUT  0x1604	//报警输出
#define	ICMS_ACTION_TVWALL  0x1605	//电视墙
#define	ICMS_ACTION_MONITOR 0x1606 //监控端关联
#define	ICMS_ACTION_EMAIL   0x1607	//邮件通知
#define	ICMS_ACTION_SMS     0x1608	//短信通知

#define ICMS_
//报警处理状态
typedef enum tag_enumAlarmStatus
{
	ICMS_ALARM_DISPOSE_NO    = 0x0F01,		//未处理 
	ICMS_ALARM_DISPOSE_DOING = 0x0F02,		//处理中
	ICMS_ALARM_DISPOSE_OK    = 0x0F03       //已处理
}EN_ICMS_AlarmStatus;


//报警事件等级
typedef enum tag_ICMS_AlarmDegree
{
	ICMS_EMERGENCY  = 1,  //紧急（Emergency）
	ICMS_ALERT      = 2,  //报警（Alert）
	ICMS_CRITICAL   = 3,  //关键（Critical）
	ICMS_ERROR      = 4,  //错误（Error）
	ICMS_WARNING    = 5   //警告（Warning）
}EN_ICMS_AlarmDegree;

//实时流控制信令
typedef enum {STOPPED,PLAY,PAUSE,SEEK_2_TIME,FORWARD_FRAME,BACKWARD_FRAME,FAST_FORWARD,FAST_BACKWARD}PLAY_CTRL;

//修改预置点
typedef enum {INSERT_POINT,UPDATE_POINT,DELETE_POINT,GOTO_POINT,STOP_POINT} SET_OPERATION;

//云台方向
typedef enum {PTZ_LEFT,PTZ_LEFT_UP,PTZ_UP,PTZ_UP_RIGHT,PTZ_RIGHT,PTZ_DOWN_RIGHT,PTZ_DOWN,PTZ_DOWN_LEFT,PTZ_ABSOLUTE_POS,PTZ_STOP_MOVE,\
PTZ_RESET, PTZ_PUSH_FAR, PTZ_PULL_NEAR }PTZ_DIRECTION;

//云台辅助功能控制
typedef enum {CTRL_LIGHT,CTRL_FOG,CTRL_RAIN_BRUSH,PROTOCOL_TRANS}AUXILIARY_METHOD;

//日志类型定义
typedef enum {SYSTEM_LOG,WARNING_LOG,OPER_LOG}LOG_KIND;

//登陆认证加密方式
typedef enum 
{
	NO_ENCRYPT = 0,//明文传输密码
	MD5 = 1,      //使用哈希值加密密码
	DES =2        //使用des加密密码
}ENCRYPTTYPE;

//录像查询类型
#define  DEVICE_RECORDTYPE_ALL 0xFF //全部录像类型
#define  DEVICE_RECORDTYPE_TIMINGRECORD 0x0000 //定时录像
#define  DEVICE_RECORDTYPE_MOTIONDETECTION 0x0001 //移动检测
#define  DEVICE_RECORDTYPE_ALARMSPRING 0x0002 //报警触发
#define  DEVICE_RECORDTYPE_ALARMORMOTIONDETECTION 0x0003 //报警|移动侦测
#define  DEVICE_RECORDTYPE_ALARMANDMOTIONDETECTION 0x0004 //报警&移动侦测
//#define  DEVICE_RECORDTYPE_APPROACHALARM 0x0002 //接近报警
//#define  DEVICE_RECORDTYPE_CASHOUTALARM 0x0003 //出钞报警
//#define  DEVICE_RECORDTYPE_CASHINALARM 0x0004 //进钞报警
#define  DEVICE_RECORDTYPE_COMMANDSPRING 0x0005 //命令触发
#define  DEVICE_RECORDTYPE_MANUALRECORD 0x0006 //手动录像
#define  DEVICE_RECORDTYPE_SHAKEALARM 0x0007 //震动报警
#define  DEVICE_RECORDTYPE_EXTERIORALARM 0x0008 //外部报警
#define  DEVICE_RECORDTYPE_CARDIDQUERY 0x0009 //卡号查询
#define  DEVICE_RECORDTYPE_COMBINATIONQUERY 0x000a //组合条件查询
#define  DEVICE_RECORDTYPE_PICQUERYBYCARDID 0x000b//按卡号查询图片
#define  DEVICE_RECORDTYPE_PICQUERY 0x000c//查询图片
#define  DEVICE_RECORDTYPE_ALLALARM 0x000d //全部报警

//录像回放状态控制
#define DEVICE_PLAYBACK_PAUSE 0x0003 //暂停播放

#define DEVICE_PLAYBACK_START 0x0004//恢复播放

#define DEVICE_PLAYBACK_FAST 0x0005//快放

#define DEVICE_PLAYBACK_SLOW 0x0006//慢放

#define DEVICE_PLAYBACK_NORMAL 0x0007//正常速度

#define DEVICE_PLAYBACK_FRAMETO 0x0008//单帧前进

#define DEVICE_PLAYBACK_FRAMEBACK 0x0001//单帧后退

#define DEVICE_PLAYBACK_STARTAUDIO 0x0009//打开声音

#define DEVICE_PLAYBACK_STOPAUDIO 0x000a//关闭声音

#define DEVICE_PLAYBACK_AUDIOVOLUME 0x000b//调节音量

#define DEVICE_PLAYBACK_SETPOS 0x000c//改变文件回放的进度

#define DEVICE_PLAYBACK_GETPOS 0x000d//获取文件回放的进度

#define DEVICE_PLAYBACK_GETTIME 0x000e//获取当前已经播放的时间

#define DEVICE_PLAYBACK_GETFRAME 0x000f//获取当前已经播放的帧数

#define DEVICE_PLAYBACK_GETTOTALFRAMES 0x0010//获取当前播放文件总的帧数

#define DEVICE_PLAYBACK_GETTOTALTIME 0x0011//获取当前播放文件总的时间

#define DEVICE_PLAYBACK_SLOWFORWARD	    0x00012//慢放
#define DEVICE_PLAYBACK_SLOWBACKWARD	0x00013//慢退

/*************************** 通讯信令宏定义 ********************************/
#pragma pack(push,1)
typedef struct tag_structiCMSCommand
{
	WORD  wSrcType;		    //源的类型
	WORD  wCmdMainType;     //信令的主类型
	DWORD dwCmdSubType;     //信令的子类型

	DWORD dwSeqID;          //信令序号
	WORD wExtendType;       //扩展数据类型
	DWORD dwExndSize;       //扩展数据大小

	tag_structiCMSCommand()
	{
		wSrcType = 0;
		wCmdMainType = 0;
		dwCmdSubType = 0;     
		dwSeqID = 0;        
		wExtendType = 0;       
		dwExndSize = 0;
	}
}ST_ICMS_Command;
#pragma pack(pop)

#define		ICMS_SERVER_SWITCH				0x1001  //转发流媒体服务器
#define		ICMS_SERVER_ALARM				0x1002  //报警服务器	
#define		ICMS_SERVER_ACQUISVER			0x1102  //报警采集服务器	
#define		ICMS_SERVER_EMAP			    0x1003  //电子地图服务器
#define		ICMS_SERVER_GISSYS				0x1004  //地图信息服务器
#define		ICMS_SERVER_INSERV				0x1006  //智能分析服务器
#define		ICMS_SERVER_MEETING				0x1007  //会议服务器
#define  	ICMS_SERVER_MATRIX			    0x1008  //电视墙服务器	
#define		ICMS_SERVER_MCENTER				0x1009  //管理服务器	
#define		ICMS_SERVER_STORE				0x100A  //存储流媒体服务器	
#define		ICMS_SERVER_SOFTDOG			    0x100B  //软件狗服务
#define		ICMS_SERVER_TRANSFER			0x100C  //迁移服务器
#define     ICMS_SERVER_TRANSWITCH			0x100D  //迁移流媒体服务器
#define		ICMS_SERVER_DBSERVER			0x100F	//数据库伺服
#define		ICMS_SERVER_DCS					0x1011	//大屏控制服务器
#define		ICMS_SERVER_NETGATE				0x1012	//互联网网关服务器
#define		ICMS_SERVER_IPGS				0x1013	//数字网关服务器
#define		ICMS_SERVER_SSWITCH				0x1014	//转存媒体服务器
#define		ICMS_SERVER_DOMAIN				0x1015	//分布式域服务器
#define		ICMS_SERVER_NMS					0x1016	//综合运维管理服务器

#define		ICMS_CLIENT_MONITOR				0xff01  //监控客户端
#define  	ICMS_CLIENT_MANAGE				0xff02  //配置管理客户端	
#define		ICMS_CLIENT_MATRIX				0xff03  //电视墙客户端	
#define		ICMS_ISWITCH_AGENT				0xff04  //用于级连时的iSwitch
#define		ICMS_SERVER_SMPNVR			    0x10f1	//基于SMP的NVR服务器
#define		ICMS_SERVER_SMPMAT			    0x10f2	//基于SMP的MAT服务器
#define		ICMS_SERVER_SMPSPS			    0x10f3	//基于SMP的SPS服务器

// 域系统类型
#define ISMS_DSYSTEM_ISMS			0X0001		// SMS系统
#define ISMS_DSYSTEM_ISMS_AGENCY	0X0002		// 级联的SMS系统
#define ISMS_DSYSTEM_IPGS			0X0003		// IPGS系统
#define ISMS_DSYSTEM_SMP			0X0004		// SMP系统
#define ISMS_DSYSTEM_ICMS8000		0X0005		// ICMS8000系统
#define ISMS_DSYSTEM_ICMS6000		0X0006		// ICMS6000系统
#define ISMS_DSYSTEM_ILNVR			0X0007		// NVR系统

//信令主类型定义
#define		ICMS_TYPE_CMDTYPE_CTRL									0x0001   //控制信令
#define		ICMS_TYPE_CMDTYPE_ALARM									0x0002   //报警信令

#define		ICMS_TYPE_CMDTYPE_ISWITCH_INTERNAL						0xffff
#define     ICMS_TYPE_CMDTYPE_IWEB_INTERNAL                         0xfffe

#define	    ISMS_SOCIMONITOR_2_IPGS_GET_SERVERPORT_REQ         		0XB001	// IPGS获取IPGS登录端口
#define	    ISMS_SOCIMONITOR_2_IPGS_GET_SERVERPORT_ACK         		0XB002
//控制信令子类型定义
//#define	ICMS_TYPE_CTRLTYPE_LOGIN_IN								0x0001   //登陆信令
//#define	ICMS_TYPE_CTRLTYPE_LOGIN_IN_ACK							0x0002   //登陆响应

//扩展数据类型定义
#define		ICMD_TYPE_EXDTYPE_XML									0x0001	//XML扩展类型
#define		ICMD_TYPE_EXDTYPE_BINARY								0x0002	//二进制数据扩展类型
#define		ICMD_TYPE_EXDTYPE_MIX									0x0003	//XML+二进制数据混合扩展类型, 

#define		ICMS_TYPE_CMDTYPE_STREAMDATA							0x0003   //流数据
#define		ICMS_DEFINE_DATA_TYPE_GPS                               0x30	 //表示该数据包为GPS数据类型

//当为此类型时，扩展数据的头4个字节为XML长度
//权限信息相关信令
//用户系统权限	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_POWER_REQ				0x0101
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_POWER_ACK				0x0102

//系统及版本信息	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_INFO_REQ					0x801a
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_INFO_ACK					0x801b

//获取设备子权限	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_DEVICE_POWER_REQ				0x0103
#define		ICMS_IMONITOR_2_IMC_GET_DEVICE_POWER_ACK				0x0104

//用户及设备子权限更新
#define     ICMS_TYPE_IMANTYPE_USER_PRIVILEGE_UPDATE				0x0b40
#define     ICMS_TYPE_IMANTYPE_USER_PRIVILEGE_UPDATE_ACK            0x0b41

//组织结构树相关信令
//获取数据版本信息
#define		ICMS_IMONITOR_2_IMC_GET_VERSION_REQ						0x0205
#define		ICMS_IMONITOR_2_IMC_GET_VERSION_ACK						0x0206
//获取子设备相关信息	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_SUBDEVICE_INFO_REQ				0x0201
#define		ICMS_IMONITOR_2_IMC_GET_SUBDEVICE_INFO_ACK				0x0202
//获取组织结构树	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_ORGANIZE_INFO_REQ				0x0203
#define		ICMS_IMONITOR_2_IMC_GET_ORGANIZE_INFO_ACK				0x0204
//组织结构树更新通知
#define		ICMS_UPDATE_ORGANIZE_NOTIFY								0x0207
// 主设备更新通知
#define		ICMS_UPDATE_MAIN_DEVICE_NOTIFY							0x0208
//存储资源分配更新通知
#define		ICMS_UPDATE_STORAGE_RESOURCE_NOTIFY						0x0209
//报警预案更新
#define		ICMS_ALARM_PLAN_UPDATE_NOTIFY							0x020A
//报警联动信息更新
#define		ICMS_ALARM_ASS_UPDATE_NOTIFY							0x020B
//计划任务更新
#define		ICMS_PLAN_UPDATE_NOTIFY									0x020C
//地图更新
#define		ISMS_MAP_LIST_UPDATE_NOTIFY								0x020D
#define		ISMS_MAP_LEAF_UPDATE_NOTIFY								0x020E
#define		ISMS_MAP_ASS_UPDATE_NOTIFY								0x020F
#define		ISMS_MAP_EQU_ASS_UPDATE_NOTIFY							0x0210
#define		ISMS_MAPPICTURE_UPDATE_NOTIFY							0x0211

//实时监看相关信令
//请求实时视频,音频参数	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GET_REAL_STREAM_REQ				0x0301
#define		ICMS_IMONITOR_2_ISWITCH_GET_REAL_STREAM_ACK				0x0302

//设置实时流传输rtp端口	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_SET_REAL_STREAM_REQ				0x0303
#define		ICMS_IMONITOR_2_ISWITCH_SET_REAL_STREAM_ACK				0x0304

//实时流控制请求	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_PLAY_CTRL_STREAM_REQ			0x0305
#define		ICMS_IMONITOR_2_ISWITCH_PLAY_CTRL_STREAM_ACK			0x0306

//实时流增加标签	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_ADD_REAL_STREAM_TAG_REQ			0x0307
#define		ICMS_IMONITOR_2_ISWITCH_ADD_REAL_STREAM_TAG_ACK			0x0308

//设置实时流是否进行录像	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_REAL_STREAM_RECORD_REQ		0x0309
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_REAL_STREAM_RECORD_ACK		0x030a

//实时流抓帧	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GRASP_REAL_STREAM_FRAME_REQ		0x030b
#define		ICMS_IMONITOR_2_ISWITCH_GRASP_REAL_STREAM_FRAME_ACK		0x030c

//调整实时流图像参数
//数据方向 : iMonitor ----> iSwitch
#define		ICMS_IMONITOR_2_ISWITCH_SET_PHOTO_INFO_REQ				0x030d
#define		ICMS_IMONITOR_2_ISWITCH_SET_PHOTO_INFO_ACK				0x030e

//请求语音对讲参数	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GET_AUDIOCHAT_REQ				0x030f
#define		ICMS_IMONITOR_2_ISWITCH_GET_AUDIOCHAT_ACK				0x0310

//手动输出控制
//数据方向 : iMonitor ----> iSwitch
#define		ICMS_IMONITOR_2_ISWITCH_MANUAL_OUTPUT_REQ					0x0311
#define		ICMS_IMONITOR_2_ISWITCH_MANUAL_OUTPUT_ACK					0x0312

// iSwitch -> iMonitor
#define	    ICMS_ISWITCH_2_IMONITOR_RESSTATUS_NOTIFY		         0x0313
#define	    ICMS_ISWITCH_2_IMONITOR_RESSTATUS_NOTIFY_ACK		     0x0314

//停止语音对讲
//数据方向 : iMonitor ----> iSwitch
#define		ICMS_IMONITOR_2_ISWITCH_STOP_AUDIOCHAT_REQ					0x0315
#define		ICMS_IMONITOR_2_ISWITCH_STOP_AUDIOCHAT_ACK					0x0316

#define		ICMS_TYPE_CTRLTYPE_DEVICE_CONTROL_REQ						0x0317
#define		ICMS_TYPE_CTRLTYPE_DEVICE_CONTROL_ACK						0x0318

#define		ICMS_TYPE_CTRLTYPE_DEVICE_CONNECT_REQ						0x0319
#define		ICMS_TYPE_CTRLTYPE_DEVICE_CONNECT_ACK						0x031a

//请求GPS数据流信令
//数据方向：iMonitor---->iSwitch
#define		ICMS_IMONITOR_2_GPSSVR_GETGPSDATA_STREAM_REQ				0x031b
#define		ICMS_IMONITOR_2_GPSSVR_GETGPSDATA_STREAM_ACK				0x031c

//数据方向 : iAlarm ----> iSwitch Alarm向iSwitch获取预录信息
#define		ICMS_TYPE_CTRLTYPE_PREREC_STATUS_REQ					0x0d3d
#define		ICMS_TYPE_CTRLTYPE_PREREC_STATUS_ACK					0x0d3e

//分配预录时请求媒体交换控制服务器地址	iAlarm --->	iMC	
#define		ICMS_IALARM_2_IMC_GET_ISWTICH_ADDR_REQ					0x0d3f
#define		ICMS_IALARM_2_IMC_GET_ISWTICH_ADDR_ACK					0x0d40

//设备离/上线状态通知
//数据方向 : iSwitch ---->iAlarm  iAlarm  ---->iMonitor
#define		ICMS_TYPE_CTRLTYPE_DEVICE_STATUS_NOTIFY		            0x0d41
#define	    ICMS_TYPE_CTRLTYPE_DEVICE_STATUS_NOTIFY_ACK		        0x0d42

//报警日志检索
//数据方向 : iMonitor ---->iAlarm  
 #define	ICMS_TYPE_CTRLTYPE_GET_ALARMLOG_REQ		                0x0d43
#define	    ICMS_TYPE_CTRLTYPE_GET_ALARMLOG_ACK		                0x0d44

//实时流转发控制请求
//数据方向 : iMC <------> iSwitch
#define		ICMS_MC_2_ISWITCH_STREAM_TRANSFER_REQ					0x0d45
#define		ICMS_MC_2_ISWITCH_STREAM_TRANSFER_ACK					0x0d46

//设备状态查询
//数据方向  iMonitor <--------> iMC <--------> iSwitch
#define     ICMS_2_SWITCH_DEVICE_STATUS_QUERY_REQ                    0x0df7
#define     ICMS_2_SWITCH_DEVICE_STATUS_QUERY_ACK                    0x0df8

#define     ICMS_2_SWITCH_DEVICE_INFO_QUERY_REQ						 0x0df9	
#define     ICMS_2_SWITCH_DEVICE_INFO_QUERY_ACK						 0x0dfa

#define		ICMS_ALARM_EQUIPSTATE_NOTIFY							0x0a1b

//设备在线状态
#define ISMS_GET_SUBEQUIPMENT_ONLINESTATE_REQ		0x8254
#define ISMS_GET_SUBEQUIPMENT_ONLINESTATE_ACK		0x8255

// 设备在线状态变更通知
#define ISMS_SUBEQUIPMENT_ONLINESTATE_CHANGED_NOTIFY	0x824f

/*************************** VOD点播相关信令 ********************************/
//获取 vod查询列表	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_GET_VOD_LIST_REQ	                0x0401
#define		ICMS_IMONITOR_2_IMC_GET_VOD_LIST_ACK					0x0402

//SIP获取 vod查询列表	iMonitor	iSwitch	
#define     ICMS_IMONITOR_2_IMC_SIP_GET_VOD_LIST_REQ                0x1409
#define     ICMS_IMONITOR_2_IMC_SIP_GET_VOD_LIST_ACK                0x1410

//获取录像抓帧图片列表	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_GET_VIDEO_GRAB_PIC_REQ				0x0403
#define		ICMS_IMONITOR_2_IMC_GET_VIDEO_GRAB_PIC_ACK				0x0404

//请求获取录像抓帧	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GET_VIDEO_RECORD_REQ		    0x0405
#define		ICMS_IMONITOR_2_ISWITCH_GET_VIDEO_RECORD_ACK			0x0406

//获取抓帧图片	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GET_VIDEO_GRAB_PIC_REQ			0x0407
#define		ICMS_IMONITOR_2_ISWITCH_GET_VIDEO_GRAB_PIC_ACK			0x0408

//请求vod文件点播视频,音频参数	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GET_VOD_STREAM_REQ				0x0409
#define		ICMS_IMONITOR_2_ISWITCH_GET_VOD_STREAM_ACK				0x040a

//请求vod文件点播视频,音频参数	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_SIP_GET_VOD_STREAM_REQ			0x140a
#define		ICMS_IMONITOR_2_ISWITCH_SIP_GET_VOD_STREAM_ACK			0x140b

//设置vod传输rtp端口	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_SET_VOD_STREAM_REQ				0x040b
#define		ICMS_IMONITOR_2_ISWITCH_SET_VOD_STREAM_ACK				0x040c

//vod流控制请求iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_VOD_STREAM_REQ				0x040d
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_VOD_STREAM_ACK				0x040e

//vod流sip控制请求iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_SIP_CTRL_VOD_STREAM_REQ			0x140c
#define		ICMS_IMONITOR_2_ISWITCH_SIP_CTRL_VOD_STREAM_ACK			0x140d

//vod增加标签	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_ADD_VOD_STREAM_TAG_REQ			0x040f
#define		ICMS_IMONITOR_2_ISWITCH_ADD_VOD_STREAM_TAG_ACK			0x0410

//vod抓帧	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_GRASP_VOD_STREAM_FRAME_REQ		0x0411
#define		ICMS_IMONITOR_2_ISWITCH_GRASP_VOD_STREAM_FRAME_ACK		0x0412

//请求vod文件tag信息	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_VOD_TAG_INFO_REQ			    0x0413
#define		ICMS_IMONITOR_2_IMC_GET_VOD_TAG_INFO_ACK			    0x0414

//iMonitor请求iSwitch移动vod文件到相对时间
#define     ICMS_IMONITOR_2_ISWITCH_SEEK_2_RELATIVE_TIME_REQ		0x0415
#define     ICMS_IMONITOR_2_ISWITCH_SEEK_2_RELATIVE_TIME_ACK		0x0416

//vod流sip seek请求iMonitor	iSwitch	
#define     ICMS_IMONITOR_2_ISWITCH_SIP_SEEK_2_RELATIVE_TIME_REQ	0x1415
#define     ICMS_IMONITOR_2_ISWITCH_SIP_SEEK_2_RELATIVE_TIME_ACK	0x1416

//iMonitor请求iSwitch获取下一个序列所有的gop
#define     ICMS_IMONITOR_2_ISWITCH_GET_NEXT_GOP_REQ				0x0417
#define     ICMS_IMONITOR_2_ISWITCH_GET_NEXT_GOP_ACK				0x0418

//iMonitor请求iSwitch获取上一个序列所有的gop
#define     ICMS_IMONITOR_2_ISWITCH_GET_PREV_GOP_REQ				0x0419
#define     ICMS_IMONITOR_2_ISWITCH_GET_PREV_GOP_ACK				0x041A

//iMonitor请求iSwitch获取获取下一个快进序列
#define     ICMS_IMONITOR_2_ISWITCH_GET_FAST_FORWARD_REQ		    0x041B
#define     ICMS_IMONITOR_2_ISWITCH_GET_FAST_FORWARD_ACK		    0x041C

//iMonitor请求iSwitch获取上一个快进序列
#define     ICMS_IMONITOR_2_ISWITCH_GET_FAST_BACKWARD_REQ			0x041D
#define     ICMS_IMONITOR_2_ISWITCH_GET_FAST_BACKWARD_ACK			0x041E

//iMonitor请求iSwitch退出当前vod点播
#define		ICMS_IMONITOR_2_ISWITCH_VOD_STOP_REQ			        0x041f
#define		ICMS_IMONITOR_2_ISWITCH_VOD_STOP_ACK			        0x0420

//文件数据传输头
#define		ICMS_ISWITCH_2_IMONITOR_DATA_TRAN			            0x0421

//iMonitor请求iSwitch开始当前vod点播
//数据方向 : iMonitor ----> iSwitch 
#define		ICMS_IMONITOR_2_ISWITCH_VOD_START_REQ			        0x0423
#define		ICMS_IMONITOR_2_ISWITCH_VOD_START_ACK				    0x0424

//iMonitor请求iSwitch暂停当前vod点播
//数据方向 : iMonitor ----> iSwitch
#define		ICMS_IMONITOR_2_ISWITCH_VOD_PAUSE_REQ			        0x0425
#define		ICMS_IMONITOR_2_ISWITCH_VOD_PAUSE_ACK			        0x0426

//iSwitch通知iMonitor事务状态
#define		ICMS_ISWITCH_2_IMONITOR_VOD_NOTIFY_REQ			        0x0427
#define		ICMS_ISWITCH_2_IMONITOR_VOD_NOTIFY_ACK			        0x0428

//录像迁移
//数据方向 : iMonitor ----> iSwitch
#define   	ICMS_CLIENT_TRANSFER_RECFILE_REQ					    0x0429
#define 	ICMS_CLIENT_TRANSFER_RECFILE_ACK					    0x042a

//图片迁移
//数据方向 : iMonitor ----> iSwitch
#define		ICMS_CLIENT_TRANSFER_PICFILE_REQ					   0x042b
#define		ICMS_CLIENT_TRANSFER_PICFILE_ACK				       0x042c

//录像迁移进度
//数据方向 : iSwitch ----> iMonitor
#define	ICMS_CLIENT_TRANSFER_PROGRESS_NOTIFY					   0x042d
#define	ICMS_CLIENT_TRANSFER_PROGRESS_NOTIFY_ACK				   0x042e

//文件迁移控制
#define		ICMS_CLIENT_TRANSFER_CONTROL_REQ					   0x042f
#define		ICMS_CLIENT_TRANSFER_CONTROL_ACK					   0x0430

// SMQ:2013-12-16 Add
// 配置标签信息
#define		ISMS_CLIENT_2_MC_SET_TAGINFO_REQ					0x0431
#define		ISMS_CLIENT_2_MC_SET_TAGINFO_ACK					0x0432

// SMQ:2013-12-16 Add
// 查询标签信息
#define		ISMS_CLIENT_2_MC_GET_TAGINFO_REQ					0x0433
#define		ISMS_CLIENT_2_MC_GET_TAGINFO_ACK					0x0434


//删除迁移文件
#define		ICMS_IMONITOR_2_ISWTCHI_DEL_TRANSFER_FILE_REQ					0x0d47
#define		ICMS_IMONITOR_2_ISWTCHI_DEL_TRANSFER_FILE_ACK					0x0d48

//monitor向MC获取特定用户的迁移信息
#define		ICMS_IMONITOR_2_MC_QUERY_TRANSFER_TASK_INFO_REQ					0x0d49
#define		ICMS_IMONITOR_2_MC_QUERY_TRANSFER_TASK_INFO_ACK					0x0d4a

//monitor向迁移服务器获取特定任务的进度和状态信息
#define		ICMS_IMONITOR_2_ISWITCH_QUERY_TRANSFER_TASK_INFO_REQ				0x0d4b
#define		ICMS_IMONITOR_2_ISWITCH_QUERY_TRANSFER_TASK_INFO_ACK				0x0d4c

//迁移服务器上报迁移任务状态信息
#define		ICMS_ISWITCH_2_MONITOR_TRANSFER_TASK_STATUS_CHANGE_NOTIFY_REQ		0x0d4d
#define		ICMS_ISWITCH_2_MONITOR_TRANSFER_TASK_STATUS_CHANGE_NOTIFY_ACK		0x0d4e

//下载文件结束通知信令
#define     ICMS_MONITOR_2_ISWITCH_UPLOAD_FILE_FINISH_NOTIFY_REQ                0x0d4f
#define     ICMS_ISWITCH_2_MONITOR_UPLOAD_FILE_FINISH_NOTIFY_ACK                0x0d50

/*************************** 轮询方案相关信令 ********************************/
//获取设备分组轮巡方案表	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_GROUP_SURVEY_SCHEME_REQ			0x0501
#define		ICMS_IMONITOR_2_IMC_GET_GROUP_SURVEY_SCHEME_ACK			0x0502

//设置设备分组轮巡方案表	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_SET_GROUP_SURVEY_SCHEME_REQ			0x0503
#define		ICMS_IMONITOR_2_IMC_SET_GROUP_SURVEY_SCHEME_ACK			0x0504

//删除设备分组轮巡设置表	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_DEL_GROUP_SURVEY_SCHEME_REQ			0x0505
#define		ICMS_IMONITOR_2_IMC_DEL_GROUP_SURVEY_SCHEME_ACK			0x0506

//获取分组轮巡计划表
//数据方向 : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_GET_GROUP_SURVEY_PLAN_REQ		    0x0507
#define		ICMS_IMONITOR_2_IMC_GET_GROUP_SURVEY_PLAN_ACK			0x0508

//数据方向 : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_SET_GROUP_SURVEY_PLAN_REQ			0x0509
#define		ICMS_IMONITOR_2_IMC_SET_GROUP_SURVEY_PLAN_ACK			0x050a

//分组轮巡计划更新通知
//数据方向 : iMC ----> iMonitor    
#define	 ICMS_IMC_TO_IMONITOR_GROUP_SURVEY_PLAN_UPDATE			0x050b
//数据方向 : iMonitor ----> Imc
#define	 ICMS_IMC_TO_IMONITOR_GROUP_SURVEY_PLAN_UPDATE_ACK		0x050c


//设备批量更新
#define	 ICMS_IMANAGER_TYPE_EQUIPMENT_BATCH_UPDATE			    0x050D
#define	 ICMS_IMANAGER_TYPE_EQUIPMENT_BATCH_UPDATE_ACK			0x050E

//批量服务更新通知
#define	 ICMS_IMANAGER_TYPE_SERVERINFO_BATCH_UPDATE			    0x050F
#define	 ICMS_IMANAGER_TYPE_SERVERINFO_BATCH_UPDATE_ACK			0x0510

//子设备参数批量更新
#define	 ICMS_IMANAGER_TYPE_SUBADVSET_BATCH_UPDATE			    0x0511
#define	 ICMS_IMANAGER_TYPE_SUBADVSET_BATCH_UPDATE_ACK			0x0512

//获取服务器类型
#define	 ISOC_GET_SETVER_TYPE_AND_VERSION_REQ					0x5051
#define	 ISOC_GET_SETVER_TYPE_AND_VERSION_ACK                   0x5052


/*************************** 云台控制相关信令 ********************************/
//获取设备预置点	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_GET_SUB_PREDEFINE_POS_REQ			0x0601
#define		ICMS_IMONITOR_2_IMC_GET_SUB_PREDEFINE_POS_ACK			0x0602

//修改设备预置点	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_SET_SUB_PREDEFINE_POS_REQ			0x0603
#define		ICMS_IMONITOR_2_IMC_SET_SUB_PREDEFINE_POS_ACK			0x0604

//获取设备巡航预置点	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_GET_SUB_PREDEFINE_CRUISE_REQ		0x0605
#define		ICMS_IMONITOR_2_IMC_GET_SUB_PREDEFINE_CRUISE_ACK		0x0606

//设备巡航预置点	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_IMC_SET_SUB_PREDEFINE_CRUISE_REQ		0x0607
#define		ICMS_IMONITOR_2_IMC_SET_SUB_PREDEFINE_CRUISE_ACK		0x0608

//ptz八个方向移动控制	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_MOVE_REQ					0x0609
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_MOVE_ACK					0x060a

//ptz的zoom控制	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_ZOOM_REQ					0x060b
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_ZOOM_ACK					0x060c

//ptz的focus控制	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_FOCUS_REQ				   0x060d
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_FOCUS_ACK				   0x060e

// 
//ptz的辅助功能控制 	iMonitor	iSwitch	
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_AUXILIARY_REQ				0x060f
#define		ICMS_IMONITOR_2_ISWITCH_PTZ_AUXILIARY_ACK				0x0610

//iMonitor到iSwitch调用设备预置点
#define		ICMS_IMONITOR_2_ISWITCH_PREDEFINE_POSITION_REQ			0x0611
#define		ICMS_IMONITOR_2_ISWITCH_PREDEFINE_POSITION_ACK			0x0612

//iMonitor到iSwitch设备巡航
#define		ICMS_IMONITOR_2_ISWITCH_PREDEFINE_CRUISE_REQ			0x0613
#define		ICMS_IMONITOR_2_ISWITCH_PREDEFINE_CRUISE_ACK			0x0614

//iMonitor到iSwitch查询ptz当前位置
//数据方向 : iMonitor ----> iSwitch
#define		ICMS_IMONITOR_2_ISWITCH_GET_PTZ_POSITION_REQ			0x0615
#define		ICMS_IMONITOR_2_ISWITCH_GET_PTZ_POSITION_ACK			0x0616

//iMonitor到iSwitch在实时监视看图像中通过鼠标控制PTZ
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_PTZ_VIEW_REQ				0x0617
#define		ICMS_IMONITOR_2_ISWITCH_CTRL_PTZ_VIEW_ACK				0x0618

//iMonitor到iSwitch在获取PTZ当前位置
#define		ICMS_IMONITOR_2_ISWITCH_GET_PTZ_CURPOS_REQ				0x0619
#define		ICMS_IMONITOR_2_ISWITCH_GET_PTZ_CURPOS_ACK				0x061a

//Ptz绝对位置移动
//数据方向 : iMonitor ----> iSwitch 
#define	 ICMS_IMONITOR_2_ISWITCH_PTZ_ABSSOLUTEMOVE_REQ				0x061b
#define	 ICMS_IMONITOR_2_ISWITCH_PTZ_ABSSOLUTEMOVE_ACK				0x061c

//Ptz云台抢占
//数据方向 : iMonitor ----> iSwitch 
#define  ICMS_IMONITOR_2_ISWITCH_PTZ_EXCLUSIVE_REQ                  0x061d
#define  ICMS_IMONITOR_2_ISWITCH_PTZ_EXCLUSIVE_ACK                  0x061e

//Ptz光圈控制
//数据方向 : iMonitor ----> iSwitch 
#define   ICMS_IMONITOR_2_ISWITCH_PTZ_APERTURE_REQ                  0x0620
#define   ICMS_IMONITOR_2_ISWITCH_PTZ_APERTURE_ACK                  0x0621

//数据方向 : iMonitor ----> iSwitch 
#define	 ICMS_IMONITOR_2_ISWITCH_IO_CONTROL_REQ						0x0622
#define	 ICMS_IMONITOR_2_ISWITCH_IO_CONTROL_ACK						0x0623

/*************************** 日志查询及其他信令 ********************************/
//获取日志表	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_LOG_REQ							0x0701
#define		ICMS_IMONITOR_2_IMC_GET_LOG_ACK							0x0702

//取报警颜色	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_WARNING_COLOR_REQ				0x0801
#define		ICMS_IMONITOR_2_IMC_GET_WARNING_COLOR_ACK				0x0802

//取系统使用率等参数	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_USEAGE_REQ				0x0803
#define		ICMS_IMONITOR_2_IMC_GET_SYSTEM_USEAGE_ACK				0x0804

//取类型对照信息参数	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_TYPE_INFO_REQ					0x0805
#define		ICMS_IMONITOR_2_IMC_GET_TYPE_INFO_ACK					0x0806

//获取在线Monitor地址
//数据方向 : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_GET_MONITORADDR_REQ					0x0807
#define		ICMS_IMONITOR_2_IMC_GET_MONITORADDR_ACK					0x0808

//获取用户定义的报警事件类型
//数据方向 : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_GET_USER_ALARMCODE_REQ		    	0x0809
#define		ICMS_IMONITOR_2_IMC_GET_USER_ALARMCODE_ACK				0x080a

//获取报警处理常用标签信息
//数据方向 : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_GET_ALARM_TAG_REQ					0x080b
#define		ICMS_IMONITOR_2_IMC_GET_ALARM_TAG_ACK					0x080c

//获取报警处理常用注释信息
//数据方向 : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_GET_ALARM_DESC_REQ					0x080d
#define		ICMS_IMONITOR_2_IMC_GET_ALARM_DESC_ACK					0x080e

//添加报警处理常用标签信息
//数据方向 : iMonitor ----> iMC
#define		ICMS_IMONITOR_2_IMC_ADD_ALARM_TAG_REQ					0x080f
#define		ICMS_IMONITOR_2_IMC_ADD_ALARM_TAG_ACK					0x0810

#define ISMS_GET_SYSTEM_INFO_REQ									0x801a
#define ISMS_GET_SYSTEM_INFO_ACK									0x801b

#define ISMS_GET_SERVER_REQ											0x8010
#define ISMS_GET_SERVER_ACK											0x8011


/*************************** 登陆认证相关信令 ********************************/
//Monitor在线登记	iMonitor	ISwitch, iMap, iAlarm	
#define		ICMS_IMONITOR_2_LOGIN_IN_REQ							0x0a01
#define		ICMS_IMONITOR_2_LOGIN_IN_ACK							0x0a02

//Monitor在线注销	iMonitor	ISwitch, iMap, iAlarm	
#define		ICMS_IMONITOR_2_LOGIN_OUT_REQ							0x0a03
#define		ICMS_IMONITOR_2_LOGIN_OUT_ACK							0x0a04

//心跳包检测	iMonitor	ISwitch, iMap, iAlarm	
#define		ICMS_IMONITOR_2_HEART_BEAT_REQ							0x0a05
#define		ICMS_IMONITOR_2_HEART_BEAT_ACK							0x0a06

//iSwitch,iAlarm,iMap,iMonitor,iManager主动发起的公共请求-> MC
#define		ICMS_TYPE_TOMC_LOGIN_REQ								0x0a07
#define		ICMS_TYPE_TOMC_LOGIN_ACK								0x0a08

//iSwitch,iAlarm,iMap,iMonitor,iManager主动发起的公共请求-> MC
#define		ICMS_TYPE_TOMC_LOGOUT_REQ								0x0a09
#define		ICMS_TYPE_TOMC_LOGOUT_ACK								0x0a0a

//上级服务器向下级服务器认证	上级iMC/iAlarm	iMC/iAlarm	
#define		ICMS_TYPE_CONNECT_SUBSERVER_REQ							0x0a0b
#define		ICMS_TYPE_CONNECT_SUBSERVER_ACK							0x0a0c

//下级服务器心跳包检测	iMC/iAlarm	上级iMC/iAlarm	
#define		ICMS_TYPE_SUBSERVER_HEART_BEAT_REQ						0x0a0d
#define		ICMS_TYPE_SUBSERVER_HEART_BEAT_ACK						0x0a0e

//下级服务器退出通知	iMC/iAlarm	上级iMC/iAlarm	
#define		ICMS_TYPE_SUBSERVER_LOGOUT_REQ							0x0a0f
#define		ICMS_TYPE_SUBSERVER_LOGOUT_ACK							0x0a10

//从服务器向主服务器认证	从iMC/iAlarm	主iMC/iAlarm	
#define		ICMS_TYPE_CONNECT_TOMAINSERV_REQ						0x0a11
#define		ICMS_TYPE_CONNECT_TOMAINSERV_ACK						0x0a12

//主从服务器心跳包检测	从iMC/iAlarm	主iMC/iAlarm	
#define		ICMS_TYPE_SERVER_HEART_BEAT_REQ							0x0a13
#define		ICMS_TYPE_SERVER_HEART_BEAT_ACK							0x0a14

//下级服务器向上级服务器注册
#define	ICMS_TYPE_CONNECT_SUPERSERVER_REQ							0x0a15
#define	ICMS_TYPE_CONNECT_SUPERSERVER_ACK							0x0a16

//服务器心跳测试请求
#define ICMS_TYPE_PINGALIVE_REQ										0x0a17
#define ICMS_TYPE_PINGALIVE_ACK										0x0a18

//ISWITCH登录过滤驱动接口信令
#define ICMS_ISWITCH_2_UID_LOGIN_REQ                                0x0a19
#define	ICMS_ISWITCH_2_UID_LOGIN_ACK							    0x0a1a



/*************************** 配置管理信令 ********************************/
//录像计划更新通知	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_RECSCHEDULE_UPDATE					0x0b01
#define		ICMS_TYPE_IMANTYPE_RECSCHEDULE_UPDATE_ACK				0x0b02

//录像上载计划更新通知	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_RECUPLOADSCHEDULE_UPDATE				0x0b03
#define		ICMS_TYPE_IMANTYPE_RECUPLOADSCHEDULE_UPDATE_ACK			0x0b04

//布防计划更新通知	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_DEFENCESCHEDULE_UPDATE				0x0b05
#define		ICMS_TYPE_IMANTYPE_DEFENCESCHEDULE_UPDATE_ACK			0x0b06

//自动巡检更新通知	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_AUTOPATROLSCHEDULE_UPDATE			0x0b07
#define		ICMS_TYPE_IMANTYPE_AUTOPATROLSCHEDULE_UPDATE_ACK		0x0b08

//手动巡检开始通知	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_MANUALPATROLSCHEDULE_START			0x0b09
#define		ICMS_TYPE_IMANTYPE_MANUALPATROLSCHEDULE_START_ACK		0x0b0a
#define		ICMS_TYPE_IMANTYPE_MANUALPATROLSCHEDULE_RESULT_ACK		0x0b0b

//手动巡检取消	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_AUTOPATROLSCHEDULE_CANCEL			0x0b0f
#define		ICMS_TYPE_IMANTYPE_AUTOPATROLSCHEDULE_CANCEL_ACK		0x0b10

//报警设置更新通知	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_ALARM_UPDATE							0x0b11
#define		ICMS_TYPE_IMANTYPE_ALARM_UPDATE_ACK						0x0b12

//设备连接通知	iManager		
#define		ICMS_TYPE_IMANTYPE_EQUIPMENT_CONNECT					0x0b13
#define		ICMS_TYPE_IMANTYPE_EQUIPMENT_CONNECT_ACK				0x0b14

//设备更新通知	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_EQUIPMENT_UPDATE						0x0b15
#define		ICMS_TYPE_IMANTYPE_EQUIPMENT_UPDATE_ACK					0x0b16

//组织结果更新	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_ORGANIZE_UPDATE  					0x0b17
#define		ICMS_TYPE_IMANTYPE_ORGANIZE_UPDATE_ACK					0x0b18

//用户更新通知	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_USER_UPDATE							0x0b19
#define		ICMS_TYPE_IMANTYPE_USER_UPDATE_ACK						0x0b1a

//地图更新通知	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_MAP_UPDATE							0x0b1b
#define		ICMS_TYPE_IMANTYPE_MAP_UPDATE_ACK						0x0b1c

//服务设置更新通知	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_SERVER_UPDATE						0x0b1d
#define		ICMS_TYPE_IMANTYPE_SERVER_UPDATE_ACK					0x0b1e

//系统设置更新	iManager	iMC	
#define		ICMS_TYPE_IMANTYPE_SYSTEM_UPDATE						0x0b21
#define		ICMS_TYPE_IMANTYPE_SYSTEM_UPDATE_ACK					0x0b22

//同步更新通知//需要更新所有数据
#define		ICMS_TYPE_IMANTYPE_SYNALLDATA_UPDATE				    0x0b1f
#define		ICMS_TYPE_IMANTYPE_SYNALLDATA_UPDATE_ACK				0x0b20

//NVR/下级ICMS更新通知
#define  ICMS_TYPE_IMANTYPE_NVRORSERV_UPDATE                        0x0b23
#define  ICMS_TYPE_IMANTYPE_NVRORSERV_UPDATE_ACK                    0x0b24

//计划设置变更通知
#define    ICMS_TYPE_IMANTYPE_PLANSET_UPDATE                        0x0b25
#define    ICMS_TYPE_IMANTYPE_PLANSET_UPDATE_ACK                    0x0b26

//子设备高级参数设置更新通知
#define    ICMS_TYPE_IMANTYPE_SUBEQU_ADVSET_UPDATE  	            0x0b27
#define    ICMS_TYPE_IMANTYPE_SUBEQU_ADVSET_UPDATE_ACK  	        0x0b28

//获取高级参数设置
#define     ICMS_TYPE_IMANTYPE_SUBEQU_GET_ADVSET_REQ  	            0x0b29
#define     ICMS_TYPE_IMANTYPE_SUBEQU_GET_ADVSET_ACK  	            0x0b2a

//前端设备控制命令
//数据方向 : iManage ---->iMC  iMC  ---->iSwitch
#define	    ICMS_TYPE_CTRLTYPE_DEVICE_POWER_NOTIFY		            0x0b2b
#define	    ICMS_TYPE_CTRLTYPE_DEVICE_POWER_NOTIFY_ACK		        0x0b2c

//报警声音设置更新通知
//数据方向 : iManage ---->iMC     iMC  ---->iAlarm
#define		ICMS_TYPE_IMANTYPE_AUDIOSET_UPDATE  	               0x0b2d
#define		ICMS_TYPE_IMANTYPE_AUDIOSET_UPDATE_ACK  			   0x0b2e

//报警事件定义更新通知
//数据方向 : iManage ---->iMC          iMC  ---->iAlarm  iMC  ---->iMonitor
#define		ICMS_TYPE_IMANTYPE_AEVENTSET_UPDATE  	               0x0b2f
#define		ICMS_TYPE_IMANTYPE_AEVENTSET_UPDATE_ACK  			   0x0b30

//文件存储分段设置更新通知
//数据方向 : iManage ---->iMC  iMC  ---->iSwitch
#define		ICMS_TYPE_IMANTYPE_FILECUT_UPDATE  						0x0b31
#define		ICMS_TYPE_IMANTYPE_FILECUT_UPDATE_ACK  					0x0b32

//输入输出设置更新通知
//数据方向 : iManage ---->iMC  iMC  ---->iSwitch
#define ICMS_TYPE_IMANTYPE_INOUTSET_UPDATE  						0x0b33
#define ICMS_TYPE_IMANTYPE_INOUTSET_UPDATE_ACK  					0x0b34

//存储通道分配更新通知
//数据方向 : iManage---->iMC  iMC -----> iManage
#define ICMS_TYPE_IMANTYPE_STORAGE_CHANNELS_UPDATE					0x0b35
#define ICMS_TYPE_IMANTYPE_STORAGE_CHANNELS_UPDATE_ACK				0x0b36

//存储单元更新通知
//数据方向 : iManage---->iMC  iMC -----> iManage
#define ICMS_TYPE_IMANTYPE_STORAGE_UNIT_UPDATE						0x0b37
#define ICMS_TYPE_IMANTYPE_STORAGE_UNIT_UPDATE_ACK					0x0b38

//存储磁盘更新通知
//数据方向 : iManage---->iMC  iMC -----> iManage
#define ICMS_TYPE_IMANTYPE_STORAGE_UPDATE							0x0b39
#define ICMS_TYPE_IMANTYPE_STORAGE_UPDATE_ACK						0x0b3A

//本级集群更新
#define ICMS_TYPE_IMANTYPE_GROUP_UPDATE								0x0b3b
#define ICMS_TYPE_IMANTYPE_GROUP_UPDATE_ACK							0x0b3c

//远程添加集群信息
#define ICMS_TYPE_IMANTYPE_ADDGROUP_REQ								0x0b3d
#define ICMS_TYPE_IMANTYPE_ADDGROUP_ACK								0x0b3e

//存储设备配置请求信令
//数据方向 : iManage---->iMC  iMC -----> iManage
#define ICMS_TYPE_IMANTYPE_STORAGE_REQ								0x0b3f
#define ICMS_TYPE_IMANTYPE_STORAGE_ACK								0x0b42

//图像参数设置模式保存信令
#define ICMS_TYPE_IMANTYPE_IMAGEMODE_REQ							0x0b44
#define ICMS_TYPE_IMANTYPE_IMAGEMODE_ACK							0x0b45

//设置图像参数模式信令
#define ICMS_TYPE_IMANTYPE_IMAGEMODE_SET_REQ						0x0b46
#define ICMS_TYPE_IMANTYPE_IMAGEMODE_SET_ACK						0x0b47

// 取证单元管理更新信令
//数据方向 : iManage---->iMC--->iSwitch  iSwitch -----> iMC -----> iManage
#define ICMS_TYPE_IMANTYPE_STORAGE_EVIDENCEUNIT_UPDATE				0x0b43
#define ICMS_TYPE_IMANTYPE_STORAGE_EVIDENCEUNIT_UPDATE_ACK			0x0b44

#define ICMS_TYPE_IMANTYPE_RELATION_EVIDENCEUNIT_UPDAT				0x0b45
#define ICMS_TYPE_IMANTYPE_RELATION_EVIDENCEUNIT_UPDATE_ACK			0x0b46

#define ICMS_TYPE_TRANTASK_UPDATE_REQ								0x0b47
#define ICMS_TYPE_TRANTASK_UPDATE_ACK								0x0b48

#define  ICMS_IMONITOR_2_MC_QUERYROUTE_INFO_REQ						0x1301
#define  ICMS_IMONITOR_2_MC_QUERYROUTE_INFO_ACK						0x1302

#define  ICMS_IMONITOR_2_MC_GETVODFILE_INFO_REQ						0x1303
#define  ICMS_IMONITOR_2_MC_GETVODFILE_INFO_ACK						0x1304

#define  ICMS_TYPE_IMANTYPE_GETDISKFREESPACE_REQ                    0x3420
#define  ICMS_TYPE_IMANTYPE_GETDISKFREESPACE_ACK                    0x3421

/*************************** 管理中心调度相关信令 ********************************/
#define     ICMS_TO_IMC_GET_RECSWITCH_ADDR_REQ						0x0dd5			//MC请求录像地址
#define     ICMS_TO_IMC_GET_RECSWITCH_ADDR_ACK						0x0dd6			//MC请求录像地址

//录像任务调度	iMC	ISwitch	
#define		ICMS_TYPE_CTRLTYPE_IMC_RECORD_REQ						0x0c01
#define		ICMS_TYPE_CTRLTYPE_IMC_RECORD_ACK						0x0c02

//IPC&DVS巡检任务调度	iMC	ISwitch	
#define		ICMS_TYPE_CTRLTYPE_IMC_DETECT_REQ						0x0c03
#define		ICMS_TYPE_CTRLTYPE_IMC_DETECT_ACK						0x0c04

//IPC&DVS巡检状态通知	iSwitch	iMC	
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_DETECTNOTIFY					0x0c05
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_DETECTNOTIFY_ACK				0x0c06

//设备巡检结果通知	iSwitch	iMC	
#define		ICMS_TYPE_CTRLTYPE_SELFTEST_REQ							0x0c07
#define		ICMS_TYPE_CTRLTYPE_SELFTEST_ACK							0x0c08

//IPC&DVS巡检完成	iSwitch	iMC	
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_DETECTFIN					0x0c09
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_DETECTFIN_ACK				0x0c0a

//系统巡检命令	iMC	iSwitch、iMatrix、iMap、iAlarm、iManager、iMonitor	
#define		ICMS_TYPE_CTRLTYPE_IMC_ALIVENOTIFY_REQ					0x0c0b
#define		ICMS_TYPE_CTRLTYPE_IMC_ALIVENOTIFY_ACK					0x0c0c

//布防任务调度	iMC	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_IMC_SETDEFENCE_REQ					0x0c0d
#define		ICMS_TYPE_CTRLTYPE_IMC_SETDEFENCE_ACK					0x0c0e

//撤防任务调度	iMC	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_IMC_CANCELDEFENCE_REQ				0x0c0f
#define		ICMS_TYPE_CTRLTYPE_IMC_CANCELDEFENCE_ACK				0x0c10

//数据更新通知	iMC	上级iMC	
#define		ICMS_TYPE_CTRLTYPE_IMC_UPDATE_REQ						0x0c11
#define		ICMS_TYPE_CTRLTYPE_IMC_UPDATE_ACK						0x0c12

//数据同步请求	上级iMC	iMC	
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYN_REQ						0x0c13
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYN_ACK						0x0c14

//同步数据传输	iMC	上级iMC	
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYNTRAN						0x0c15
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYNTRAN_ACK					0x0c16

//数据同步完成	上级iMC	iMC	
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYNEND						0x0c17
#define		ICMS_TYPE_CTRLTYPE_IMC_DATASYNEND_ACK					0x0c18

//请求报警服务器地址	iMonitor	iMC	
#define		ICMS_TO_IMC_GET_ALARM_ADDR_REQ							0x0c19
#define		ICMS_TO_IMC_GET_ALARM_ADDR_ACK							0x0c1a

//请求电子地图服务器地址	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_EMAP_ADDR_REQ					0x0c1b
#define		ICMS_IMONITOR_2_IMC_GET_EMAP_ADDR_ACK					0x0c1c

//请求媒体交换控制服务器地址	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_ISWTICH_ADDR_REQ				0x0c1d
#define		ICMS_IMONITOR_2_IMC_GET_ISWTICH_ADDR_ACK				0x0c1e

//请求数据库地址信息
//数据方向: iAlarm,iMap,iSwitch ----> iMC
#define		ICMS_TYPE_CTRLTYPE_GETDBADDR_REQ						0x0c1f
#define		ICMS_TYPE_CTRLTYPE_GETDBADDR_ACK						0x0c20

//请求vod点播媒体交换控制服务器地址	iMonitor	iMC	
#define		ICMS_IMONITOR_2_IMC_GET_VODISWTICH_ADDR_REQ				0x0c21
#define		ICMS_IMONITOR_2_IMC_GET_VODISWTICH_ADDR_ACK				0x0c22

//ISwitch通知MC预置点更新	ISwitch	iMC	
#define		ICMS_TYPE_CTRLTYPE_PRESET_UPDATE_REQ					0x0c23
#define		ICMS_TYPE_CTRLTYPE_PRESET_UPDATE_ACK					0x0c24

//ISwitch通知MC巡航更新	ISwitch	iMC	
#define		ICMS_TYPE_CTRLTYPE_CRIOSE_UPDATE_REQ					0x0c25
#define		ICMS_TYPE_CTRLTYPE_CRIOSE_UPDATE_ACK					0x0c26

//分组轮巡方案更新通知	iMC	iMonitor	
#define		ICMS_IMC_2_IMONITOR_GROUP_SURVEY_SCHEME_UPDATE			0x0c29
#define		ICMS_IMC_2_IMONITOR_GROUP_SURVEY_SCHEME_UPDATE_ACK		0x0c2a

//请求iSwitch负载状态	iMC	ISwitch	
#define		ICMS_IMC_ISWITCH_DEVOPEN_STATUS_REQ						0x0c2b
#define		ICMS_IMC_ISWITCH_DEVOPEN_STATUS_ACK						0x0c2c

//查询报警日志关联录像	iMonitor	iMC	
#define		ICMS_TYPE_CTRLTYPE_QUERY_ALARMREC_REQ					0x0c2d
#define		ICMS_TYPE_CTRLTYPE_QUERY_ALARMREC_ACK					0x0c2e

//iMC上下级服务器数据同步
#define		ICMS_TYPE_CTRLTYPE_UPSERV_DATASYN						0x0c2f
#define		ICMS_TYPE_CTRLTYPE_UPSERV_DATASYN_ACK					0x0c30

//设备上载任务调度
#define	     ICMS_TYPE_CTRLTYPE_DEVRECORD_UP		                0x0c31
#define	     ICMS_TYPE_CTRLTYPE_DEVRECORD_UP_ACK		            0x0c32


//请求多个子设备的iSwitch地址
//数据方向: iMonitor/iAlarm/iManage ----> iMC
#define		ICMS_TO_IMC_GET_MULTISWTICH_ADDR_REQ					0x0c33
#define		ICMS_TO_IMC_GET_MULTISWTICH_ADDR_ACK					0x0c34

//iMonitor到iMC请求迁移服务器地址
//数据方向: iMonitor ----> iMC
#define		ICMS_TO_IMC_GET_TRANSFER_ADDR_REQ			            0x0c35
#define		ICMS_TO_IMC_GET_TRANSFER_ADDR__ACK			            0x0c36

//获取迁移文件信息
#define		ICMS_TYPE_CTRLTYPE_TRANSFILEINFO_REQ					0x0e07
#define		ICMS_TYPE_CTRLTYPE_TRANSFILEINFO_ACK					0x0e08

//报告当前录像任务状态
//数据方向: iSwitch ----> iMC
#define	    ICMS_TYPE_CTRLTYPE_RECTASK_STATUS_NOTIFY		        0x0c37
#define	    ICMS_TYPE_CTRLTYPE_RECTASK_STATUS_NOTIFY_ACK			0x0c38

//获取iSwitch地址
//数据方向: iMonitor ----> iMC
#define	    ICMS_TYPE_CTRLTYPE_GET_ISWITCH_ADDR_REQ		            0x0c39
#define	    ICMS_TYPE_CTRLTYPE_GET_ISWITCH_ADDR_ACK			        0x0c3a

#define		ICMS_ISWITCH_IMC_GET_ISWTICH_ADDR_REQ					0x0c41
#define		ICMS_ISWITCH_IMC_GET_ISWTICH_ADDR_ACK					0x0c42

#define		ICMS_TO_IMC_GET_DISKSTORAGE_REQ							0x0c43
#define		ICMS_TO_IMC_GET_DISKSTORAGE_ACK							0x0c44

//客户端向MC发送设备视频数据上墙信令
#define		ICMS_TO_IMC_VIDEO_TO_MATRIX_REQ							0x0c45
#define		ICMS_TO_IMC_VIDEO_TO_MATRIX_ACK							0x0c46

#define		ICMS_TO_IMC_GET_SYSTEMRUNSTATUS_REQ						0x0c47			
#define		ICMS_TO_IMC_GET_SYSTEMRUNSTATUS_ACK						0x0c48

#define	ICMS_ISWITCH_IMC_NOTIFY_RECORDRUN_REQ					    0x0c49
#define		ICMS_ISWITCH_IMC_NOTIFY_RECORDRUN_ACK					0x0c4a

#define    ICMS_TYPE_IMATYPE_SERVER_CHECK_REQ						0x0c4b
#define    ICMS_TYPE_IMATYPE_SERVER_CHECK_ACK						0x0c4c

#define    ICMS_TYPE_IMC_GET_TRNFILENOTE_REQ						0x0c4d
#define    ICMS_TYPE_IMC_GET_TRANFILENOTE_ACK						0x0c4e

#define    ICMS_IMONITOR_2_ISWITCH_AVAILABLE_TALKBACK_ENCODEPRAMS_REQ  0x0c4f
#define    ICMS_IMONITOR_2_ISWITCH_AVAILABLE_TALKBACK_ENCODEPRAMS_ACK  0x0c50

//请求GPS服务器地址
#define		ICMS_IMONITOR_2_IMC_GET_GPSSVR_ADDR_REQ                  0x0c51
#define		ICMS_IMONITOR_2_IMC_GET_GPSSVR_ADDR_ACK                  0x0c52

/*************************** 报警服务相关信令 ********************************/
//探头或通道报警信令	ISwitch	 iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARMEVENT_NOTIFY					0x0d01
#define		ICMS_TYPE_CTRLTYPE_ALARMEVENT_NOTIFY_ACK				0x0d02

//系统报警信令	iSwitch, iMap, iMC	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_SYSALARM_NOTIFY						0x0d03
#define		ICMS_TYPE_CTRLTYPE_SYSALARM_NOTIFY_ACK					0x0d04

//手动报警信令	iMonitor	 iAlarm	
#define		ICMS_TYPE_CTRLTYPE_MANUALALARM_NOTIFY					0x0d05
#define		ICMS_TYPE_CTRLTYPE_MANUALALARM_NOTIF_ACK				0x0d06

//报警录像	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_STARTRECORD				0x0d07
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_STARTRECORD_ACK			0x0d08

//视频抓帧	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_VIDEOSNAP				0x0d09
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_VIDEOSNAP_ACK			0x0d00a

//PTZ联动	iAlarm	iSwitch
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_PTZ						0x0d0b
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_PTZ_ACK					0x0d0c

//报警输出	IAlarm/iMonitor	ISwitch/iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_OUTPUT					0x0d0d
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_OUTPUT_ACK				0x0d0e

//电视墙联动	iAlarm	imatrix	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_TVWALL					0x0d0f
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_TVWALL_ACK				0x0d10

//短信通知	iAlarm	短信机	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_SMS						0x0d11
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_SMS_ACK					0x0d12

//邮件通知	iAlarm	邮件服务器	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_EMAIL					0x0d13
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_EMAIL_ACK				0x0d14

//弹出地图, 视频预览, 声音提示	iAlarm	iMonitor	
#define		ICMS_TYPE_CTRLTYPE_ALARM_DESCRIPTION					0x0d15
#define		ICMS_TYPE_CTRLTYPE_ALARM_DESCRIPTION_ACK				0x0d16

//停止录像	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_STOPRECORD				0x0d17
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_STOPRECORD_ACK			0x0d18

//恢复云台	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_RESUMEPTZ				0x0d19
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_RESUMEPTZ_ACK			0x0d1a

//报警输出恢复	iAlarm	iSwitch
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_OUTPUTRESUME				0x0d1b
#define		ICMS_TYPE_CTRLTYPE_ALARMACTION_OUTPUTRESUME_ACK			0x0d1c

//布防通知	IAlarm/iMonitor	ISwitch/iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARM_SETDEFENCE						0x0d1d
#define		ICMS_TYPE_CTRLTYPE_ALARM_SETDEFENCE_ACK					0x0d1e

//撤防通知	IAlarm/iMonitor	ISwitch/iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARM_CANCELDEFENCE					0x0d1f
#define		ICMS_TYPE_CTRLTYPE_ALARM_CANCELDEFENCE_ACK				0x0d20

//预录通知	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_PRERECORD							0x0d21
#define		ICMS_TYPE_CTRLTYPE_PRERECORD_ACK						0x0d22

//报警处理结果通知	iAlarm	IMonitor/上级iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARMDEAL_RESULT						0x0d23
#define		ICMS_TYPE_CTRLTYPE_ALARMDEAL_RESULT_ACK					0x0d24

//手动报警指定处理用户	iAlarm	iMonitor	
#define		ICMS_TYPE_CTRLTYPE_ALARMMANNUL_NOTIFY					0x0d25
#define		ICMS_TYPE_CTRLTYPE_ALARMMANNUL_NOTIFY_ACK				0x0d26

//Monitor报警处理状态上报	iMonitor	IAlarm/上级iAlarm	
#define		ICMS_TYPE_CTRLTYPE_MONITOR_ALARMSTATUS					0x0d27
#define		ICMS_TYPE_CTRLTYPE_MONITOR_ALARMSTATUS_ACK				0x0d28

//Monitor报警处理结果上报	iMonitor	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_MONITOR_RESULTUP						0x0d29
#define		ICMS_TYPE_CTRLTYPE_MONITOR_RESULTUP_ACK					0x0d2a

//Monitor取消报警	iMonitor	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_MONITOR_CANCELALARM					0x0d2b
#define		ICMS_TYPE_CTRLTYPE_MONITOR_CANCELALARM_ACK				0x0d2c

//报警事件信息查询	上级iAlarm	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARMINFO_QUERY						0x0d2d
#define		ICMS_TYPE_CTRLTYPE_ALARMINFO_QUERY_ACK					0x0d2e

//通道关联信息查询	上级iAlarm	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_ALARMRELATION_QUERY					0x0d2f
#define		ICMS_TYPE_CTRLTYPE_ALARMRELATION_QUERY_ACK				0x0d30

//Iswitch心跳包检测	iSwitch	iAlarm	
#define		ICMS_ISWITCH_HEART_BEAT_REQ								0x0d31
#define		ICMS_ISWITCH_HEART_BEAT_ACK								0x0d32

//主从服务器数据同步	主iAlarm	从iAlarm
#define		ICMS_TYPE_CTRLTYPE_ALARM_DATASYN						0x0d33
#define		ICMS_TYPE_CTRLTYPE_ALARM_DATASYN_ACK					0x0d34

//关闭多个预录	iAlarm	iSwitch0	
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_STOP_PREREC_REQ				0x0d35
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_STOP_PREREC_ACK				0x0d36

//关闭指定子设备的预录	iAlarm	iSwitch	
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_STOP_SOMEPRE_REQ				0x0d37
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_STOP_SOMEPRE_ACK				0x0d38

//数据方向 : iAlarm ----> iSwitch 查询报警设备打开状态
#define		ICMS_TYPE_CTRLTYPE_ALARMEQU_STATUS_REQ					0x0d39
#define		ICMS_TYPE_CTRLTYPE_ALARMEQU_STATUS_ACK					0x0d3a

//数据方向 : iAlarm ----> iSwitch  分配报警设备
#define		ICMS_TYPE_CTRLTYPE_ALLOT_ALARMEQU_REQ					0x0d3b
#define		ICMS_TYPE_CTRLTYPE_ALLOT_ALARMEQU_ACK					0x0d3c

//数据方向 : iAlarm ----> iSwitch Alarm向iSwitch获取预录信息
#define		ICMS_TYPE_CTRLTYPE_PREREC_STATUS_REQ					0x0d3d
#define		ICMS_TYPE_CTRLTYPE_PREREC_STATUS_ACK					0x0d3e

//获取未处理报警
#define		ICMS_TYPE_CTRLTYPE_UNTREATED_ALARM_REQ					0x0d4f
#define		ICMS_TYPE_CTRLTYPE_UNTREATED_ALARM_ACK					0x0d50

/*************************** 地图服务相关信令 ********************************/
//地图结构同步	iMonitor	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_EMAPSTRUCTURE_TRAN					0x0e03
#define		ICMS_TYPE_CTRLTYPE_EMAPSTRUCTURE_TRAN_ACK				0x0e04

//地图数据同步	iMonitor	iAlarm	
#define		ICMS_TYPE_CTRLTYPE_EMAPDATA_TRAN						0x0e05
#define		ICMS_TYPE_CTRLTYPE_EMAPDATA_TRAN_ACK					0x0e06


// 设置地图结构信息
#define		ICMS_TYPE_CTRLTYPE_SET_EMAPSTRUCTURE_TRAN					0x0e09
#define		ICMS_TYPE_CTRLTYPE_SET_EMAPSTRUCTURE_TRAN_ACK				0x0e0a

//地图下载请求 iMonitor iEmap
#define    ISMS_TYPE_CTRLTYPE_GET_MAPPICTURE_REQ					0x8075
#define    ISMS_TYPE_CTRLTYPE_GET_MAPPICTURE_ACK					0x8076



/*************************** 软件狗相关信令 ********************************/
//心跳检测	软件狗	iMC/iAlarm/iMap/iSwitch	
#define		ICMS_SERVER_ACTIVE_REQ									0x0f01
#define		ICMS_SERVER_ACTIVE_ACK									0x0f02

//服务退出通知	iMC/iAlarm/iMap/iSwitch	软件狗	
#define		ICMS_SOFTDOG_STOP_REQ									0x0f03
#define		ICMS_SOFTDOG_STOP_ACK									0x0f04


/*************************** MATRIX服务相关信令 ********************************/
//获取Matrix服务器相关信息	iMatrix	iMC	
#define ICMS_GET_MATRIX_SERVER_INFO_REQ			   					0x1001	
#define ICMS_GET_MATRIX_SERVER_INFO_ACK			   					0x1002		   

//设置Matrix服务器相关信息	iMatrix	iMC	
#define ICMS_SET_MATRIX_SERVER_INFO_REQ			   					0x1003		    
#define ICMS_SET_MATRIX_SERVER_INFO_ACK			   					0x1004	

//启动电视墙分组轮巡 iMatrix	iMaxtrixServer
#define ICMS_START_MATRIX_GROUP_SURVEY_REQ			   				0x1005		    
#define  ICMS_START_MATRIX_GROUP_SURVEY_ACK				   			0x1006

//启动电视墙窗口轮巡 	iMatrix	iMaxtrixServer	
#define ICMS_START_MATRIX_WINDOW_SURVEY_REQ			   				0x1007		    
#define  ICMS_START_MATRIX_WINDOW_SURVEY_ACK				   		0x1008		   	    

//视频窗指定播放通道  iMatrix	iMaxtrixServer
#define ICMS_MATRIX_SPECIAL_SUBEQUIPMENT_PLAY_REQ			   		0x1009		        
#define  ICMS_MATRIX_SPECIAL_SUBEQUIPMENT_PLAY_ACK			   		0x100a		

//停止或暂停电视墙分组轮巡    iMatrix	iMaxtrixServer 
#define ICMS_STOP_MATRIX_GROUP_SURVEY_REQ			   				0x100b		
#define  ICMS_STOP_MATRIX_GROUP_SURVEY_ACK			   				0x100c	

       	   
//停止电视墙窗口轮巡 	iMatrix	iMaxtrixServer	
#define ICMS_STOP_MATRIX_WINDOW_SURVEY_REQ			   				0x100d		    
#define  ICMS_STOP_MATRIX_WINDOW_SURVEY_ACK				   			0x100e

//信息叠加
#define ICMS_SET_MATRIX_INFO_OVERLAY_REQ							0x100f
#define  ICMS_SET_MATRIX_INFO_OVERLAY_ACK							0x1010	   

//交换视频播放窗口信令
#define ICMS_SET_MATRIX_EXCHANGE_PLAYWND_REQ						0x1011
#define ICMS_SET_MATRIX_EXCHANGE_PLAYWND_ACK						0x1012   	  
   	  
//视频窗口全屏显示
#define ICMS_SET_MATRIX_FULLSCREEN_PLAYWND_REQ						0x1013		    
#define ICMS_SET_MATRIX_FULLSCREEN_PLAYWND_ACK						0x1014		   

//视频画面冻结
#define ICMS_SET_MATRIX_FROZEN_SCREEN_PLAYWND_REQ					0x1015		    
#define ICMS_SET_MATRIX_FROZEN_SCREEN_PLAYWND_ACK					0x1016		    

//摄像机锁定
#define ICMS_SET_MATRIX_CAMERA_LOCK_PLAYWND_REQ						0x1017		    
#define ICMS_SET_MATRIX_CAMERA_LOCK_PLAYWND_ACK						0x1018

//图像180翻转
#define ICMS_SET_MATRIX_VIDEO_ROVERSAL_PLAYWND_REQ					0x1019		    
#define ICMS_SET_MATRIX_VIDEO_ROVERSAL_PLAYWND_ACK					0x101a		    

//图像增强
#define ICMS_SET_MATRIX_IMAGE_ENHANCE_PLAYWND_REQ					0x101b		    
#define ICMS_SET_MATRIX_IMAGE_ENHANCE_PLAYWND_ACK				    0x101c

//启用智能分析
#define ICMS_SET_MATRIX_INTELLIGENCE_ANALYSIS_PLAYWND_REQ		    0x101d	
#define ICMS_SET_MATRIX_INTELLIGENCE_ANALYSIS_PLAYWND_ACK		    0x101e	

//Vod指定窗口播放视频流
#define ICMS_MATRIX_SPECIAL_VOD_PLAY_REQ						    0x1021
#define ICMS_MATRIX_SPECIAL_VOD_PLAY_ACK						    0x1022

//Vod下载指定抓帧图片
#define ICMS_MATRIX_SPECIAL_VOD_DOWNLOAD_IMAGE_REQ				    0x1023
#define ICMS_MATRIX_SPECIAL_VOD_DOWNLOAD_IMAGE_ACK				    0x1024

//Vod指定窗口图片显示
#define ICMS_MATRIX_SPECIAL_VOD_LISTIMAGE_REQ					    0x1025
#define ICMS_MATRIX_SPECIAL_VOD_LISTIMAGE_ACK					    0x1026

//Vod播放控制
#define ICMS_MATRIX_SPECIAL_VOD_PLAYCTRL_REQ				  	    0x1027
#define ICMS_MATRIX_SPECIAL_VOD_PLAYCTRL_ACK				  	    0x1028

//Vod播放控制（无级变速）
#define ICMS_MATRIX_SPECIAL_VOD_VAR_SPEED_REQ				  	     0x1029
#define ICMS_MATRIX_SPECIAL_VOD_VAR_SPEED_ACK				  	     0x102a

//Vod播放控制（放大 缩小)
#define ICMS_MATRIX_SPECIAL_VOD_VAR_AREA_REQ				  	     0x102b
#define ICMS_MATRIX_SPECIAL_VOD_VAR_AREA_ACK				  	     0x102c

//Vod信息叠加显示
#define ICMS_SET_MATRIX_INFO_VOD_LIST_REQ			  		     	 0x102d
#define ICMS_SET_MATRIX_INFO_VOD_LIST_ACK			  		     	 0x102e

//Get Matrix Server Group_Survey Status
#define ICMS_GET_MATRIX_SURVEY_REQ									 0x102f
#define ICMS_GET_MATRIX_SURVEY_ACK									 0x1030

//Do Maxtrix Server Group Survey Play
#define	ICMS_MAXTRIX_SCHE_SURVEY_REQ								 0x1200
#define ICMS_MAXTRIX_SCHE_SURVEY_ACK								 0x1201

//启动Matrix周轮巡计划
#define ICMS_MATRIX_WEEK_SCHE_SURVEY_REQ							 0x1202
#define ICMS_MATRIX_WEEK_SCHE_SURVEY_ACK							 0x1203

#define ICMS_SET_MATRIX_CAMERA_BITRATECHANG_REQ						 0x1204	
#define ICMS_SET_MATRIX_CAMERA_BITRATECHANG_ACK						 0x1205	
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_REQ					     0x1208
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_ACK					     0x1209

//调整迁移速率
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_RATE_REQ					 0x1210
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_RATE_ACK					 0x1211

//迁移转发通知消息
//消息方向:迁移转发服务器-------->迁移服务器
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_NOTIFY					 0x1212

//开始转发迁移数据
//消息方向:迁移服务器-------->迁移转发服务器
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_START					 0x1213
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_PAUSE					 0x1217
#define	ICMS_ISWITCH_ISWITCH_TRANSMIT_DATA_STOP					 0x1222

//停止转发迁移数据
#define ICMS_ISWITCH_ISWITCH_STOP_TRANSMIT_DATA_REQ                  0x1214

//迁移服务器和迁移转发服务器之间的心跳
#define ICMS_ISWITCH_ISWITCH_HEART_BEART_REQ                         0x1215
#define ICMS_ISWITCH_ISWITCH_HEART_BEART_ACK                         0x1216
//锁定迁移文件请求
#define ICMS_ISWITCH_IMC_LOCK_TRANS_FILE_REQ                         0x1218
//锁定迁移文件应答
#define ICMS_ISWITCH_IMC_LOCK_TRANS_FILE_ACK                         0x1219

#define ICMS_ISWITCH_IMC_UNLOCK_TRANS_FILE_REQ                        0x1220
//解锁迁移文件应答
#define ICMS_ISWITCH_IMC_UNLOCK_TRANS_FILE_ACK                        0x1221

//迁移本地文件请求
#define		ICMS_CLIENT_TRANSFER_FILE_REQ					         0x1227
//迁移本地文件ACK
#define		ICMS_CLIENT_TRANSFER_FILE_ACK					         0x1223
//迁移本地文件完成后的通知
#define		ICMS_CLIENT_TRANSFER_DATA_NOTIFY					     0x1224
//迁移本地文件控制信令
#define		ICMS_CLIENT_TRANSFER_DATA_CTRL                           0x1225
#define		ICMS_CLIENT_TRANSFER_DATA_CTRL_ACK                       0x1226


//ICMS冗余系统切换请求/应答 //manage-->mc
#define		ICMS_IMANAGER_TO_IMC_SYSSWITCH_REQ						0x3201
#define		ICMS_IMANAGER_TO_IMC_SYSSWITCH_ACK						0x3202

//ICMS冗余系统切换取消请求/应答 //manage-->mc
#define		ICMS_IMANAGER_TO_IMC_CANCEL_SYSSWITCH_REQ				0x3203
#define		ICMS_IMANAGER_TO_IMC_CANCEL_SYSSWITCH_ACK				0x3204

#define		ICMS_TYPE_CTRLTYPE_ISWITCH_REBOOT_REQ					0x0dd2
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_REBOOT_ACK					0x0dd3

#define		ICMS_TYPE_CTRLTYPE_ISWITCH_TAKEOVER_REQ					0x0dd6
#define		ICMS_TYPE_CTRLTYPE_ISWITCH_TAKEOVER_ACK					0x0dd7

#define		ICMS_CTRL_SWITCH_TYPE_CHANGE_NOTIY						0x0dd8
#define		ICMS_CTRL_SWITCH_TYPE_CHANGE_NOTIY_ACK					0x0dd9
/********************** Iswitch内部相关信令(0x1031 - 0x103f) ****************************/
//参数设置状态
#define ICMS_ISWITCH_NOTIFY_PARAM_UPDATE							0x1031
#define ICMS_ISWITCH_NOTIFY_RTPSTATUS								0x1032
#define ICMS_ISWITCH_NOTIFY_DELETEDEVICE							0x1033
#define	ICMS_ISWITCH_NOTIFY_DEVOPEN_STATUS							0x1034
#define ICMS_ISWTICH_NOTIFY_DEV_IDLE								0x1035
#define ICMS_ISWITCH_NOTIFY_OPEN_STREAM								0x1036
#define ICMS_ISWITCH_NOTIFY_CHANGERECDIR							0x1037
#define ICMS_ISWTICH_NOTIFY_RECTASKSTATUS							0x1038
#define ICMS_ISWTICH_HEART											0x1039
#define ICMS_ISWTICH_NOTIFY_REALSTREAMTAGRESPONSE                   0x103a

#define ICMS_ISWTICH_PING_REQ										0x10A0
#define	ICMS_ISWTICH_PING_ACK										0x10A1

/*************************** 共享域相关信令 ********************************/
//共享域更新（包括添加，删除，修改）	iManager	MC
#define ICMS_IMANAGER_PUBLICDOMAIN_UPD_REQ							0x1100
#define ICMS_IMANAGER_PUBLICDOMAIN_UPD_ACK							0x1101

//共享域成员系统更新（包括添加，删除，修改）	iManager	MC
#define ICMS_IMANAGER_PUBLICDOMAIN_MCSYS_UPD_REQ					0x1102
#define ICMS_IMANAGER_PUBLICDOMAIN_MCSYS_UPD_ACK					0x1103

//验证MC密码	MC		MC
#define ICMS_IMANAGER_PUBLICDOMAIN_VERIFY_MCPSW_REQ					0x1104
#define ICMS_IMANAGER_PUBLICDOMAIN_VERIFY_MCPSW_ACK					0x1105

//手动同步指定共享域内的所有成员	iManager	MC
#define ICMS_IMANAGER_PUBLICDOMAIN_MANUAL_SYNC_REQ					0x1106
#define ICMS_IMANAGER_PUBLICDOMAIN_MANUAL_SYNC_ACK					0x1107

//跨MC添加设备	iManager	MC
#define ICMS_IMANAGER_ACROSS_MC_ADDEQU_REQ							0x1108
#define ICMS_IMANAGER_ACROSS_MC_ADDEQU_ACK							0x1109

//跨MC添加组织机构	iManager	MC
#define ICMS_IMANAGER_ACROSS_MC_ADDORG_REQ							0x110A
#define ICMS_IMANAGER_ACROSS_MC_ADDORG_ACK							0x110B

//跨MC添加用户	iManager	MC
#define ICMS_IMANAGER_ACROSS_MC_ADDUSER_REQ							0x110C
#define ICMS_IMANAGER_ACROSS_MC_ADDUSER_ACK							0x110D

//跨MC添加用户组	iManager	MC
#define ICMS_IMANAGER_ACROSS_MC_ADDUSERGROUP_REQ					0x110E
#define ICMS_IMANAGER_ACROSS_MC_ADDUSERGROUP_ACK					0x110F

//跨MC添加服务器	iManager	MC
#define ICMS_IMANAGER_ACROSS_MC_ADDSERVER_REQ						0x1110
#define ICMS_IMANAGER_ACROSS_MC_ADDSERVER_ACK						0x1111

//跨MC添加设备(内传)	iMC		MC
#define ICMS_IMC_ACROSS_MC_ADDEQU_REQ								0x1112
#define ICMS_IMC_ACROSS_MC_ADDEQU_ACK								0x1113

//跨MC添加组织机构(内传)	iMC		MC
#define ICMS_IMC_ACROSS_MC_ADDORG_REQ								0x1114
#define ICMS_IMC_ACROSS_MC_ADDORG_ACK								0x1115

//跨MC添加用户(内传)	iMC		MC
#define ICMS_IMC_ACROSS_MC_ADDUSER_REQ								0x1116
#define ICMS_IMC_ACROSS_MC_ADDUSER_ACK								0x1117

//跨MC添加用户组(内传)	iMC		MC	
#define ICMS_IMC_ACROSS_MC_ADDUSERGROUP_REQ							0x1118
#define ICMS_IMC_ACROSS_MC_ADDUSERGROUP_ACK							0x1119

//跨MC添加服务器(内传)	iMC		MC
#define ICMS_IMC_ACROSS_MC_ADDSERVER_REQ							0x111A
#define ICMS_IMC_ACROSS_MC_ADDSERVER_ACK							0x111B

//MC向SWITCH发送指定设备图像数据上墙信令
#define ICMS_TO_ISWITCH_VIDEO_TO_MATRIX_REQ							0x1201
#define ICMS_TO_ISWITCH_VIDEO_TO_MATRIX_ACK							0x1202

//ISWITCH获取驱动过滤状态信令
#define ICMS_ISWITCH_2_UID_GET_FILTER_STATUS_REQ					0x6001
#define ICMS_ISWITCH_2_UID_GET_FILTER_STATUS_ACK					0x6002

//ISWITCH设置过滤驱动状态信令
#define ICMS_ISWITCH_2_UID_SET_FILTER_STATUS_REQ					0x6003
#define ICMS_ISWITCH_2_UID_SET_FILTER_STATUS_ACK					0x6004

/*************************** 流数据定义 ********************************/
#define ICMS_DEFINE_TYPE_NONE									0x00

//data main type
#define ICMS_DEFINE_DATA_TYPE_VIDEO								0x10
#define ICMS_DEFINE_DATA_TYPE_AUDIO								0x20
#define ICMS_DEFINE_DATA_TYPE_STREAM							0x40
#define ICMS_DEFINE_DATA_TYPE_INDUSTRY							0x60
#define ICMS_DEFINE_DATA_TYPE_METADATA							0x80
#define ICMS_DEFINE_DATA_TYPE_SELFDEFINE						0xff


//ext type
//Audio Codec Type
#define ICMS_DEFINE_AUDIO_UNKNOW								0x0001
#define ICMS_DEFINE_AUDIO_G711									0x0002
#define ICMS_DEFINE_AUDIO_G711U                                 0x0002
#define ICMS_DEFINE_AUDIO_AAC									0x0003
#define ICMS_DEFINE_AUDIO_G726									0x0004
#define ICMS_DEFINE_AUDIO_MP3									0x0005
#define ICMS_DEFINE_HIK_G722                                    0x0006
#define ICMS_DEFINE_HIK_G711                                    0x0007
#define ICMS_DEFINE_DAHUA_G711A                                 0x0008
#define ICMS_DEFINE_AUDIO_PCM                                   0x000a
#define ISOC_DEFINE_AUDIO_G722									0x000b
#define ISOC_DEFINE_AUDIO_G729                                  0x000c
#define ISOC_DEFINE_AUDIO_G723_1                                0x000d
#define ICMS_DEFINE_AUDIO_G722									0x000b
#define ICMS_DEFINE_AUDIO_G729                                  0x000c
#define ICMS_DEFINE_AUDIO_G723_1                                0x000d
#define ICMS_DEFINE_AUDIO_AMR                                   0x000e
#define ICMS_DEFINE_AUDIO_ADPCM                                 0x000f
#define ICMS_DEFINE_AUDIO_G711A                                 0x0010
#define ICMS_DEFINE_AUDIO_AMR_NB								0x0011 //AMR-NB音频格式
#define ICMS_DEFINE_AUDIO_AMR_MB								0x0012 //AMR-MB音频格式
#define ICMS_DEFINE_MPON_G711A									0x0013
#define ICMS_DEFINE_CREARO_ADPCM                                0x0014
#define ICMS_DEFINE_AUDIO_G723                                  0x0015

//Video Codec Type
#define ICMS_DEFINE_VIDEO_UNKNOW								0x0008
#define ICMS_DEFINE_VIDEO_JPEG									0x0010
#define ICMS_DEFINE_HIK_JPEG									0x0011
#define ICMS_DEFINE_DAHUA_JPEG									0x0012
#define ICMS_DEFINE_YAAN_JPEG									0x0013
#define ICMS_DEFINE_HANBANG_JPEG								0x0014
#define ICMS_DEFINE_VIDEO_MJPEGB								0x0015
#define ICMS_DEFINE_HUAMAI_JPEG                                 0x0016

#define ICMS_DEFINE_VIDEO_MPEG4									0x0020
#define ICMS_DEFINE_HIK_MPEG4									0x0021
#define ICMS_DEFINE_DAHUA_MPEG4									0x0022
#define ICMS_DEFINE_YAAN_MPEG4									0x0023

#define ICMS_DEFINE_VIDEO_MPEG2									0x0040
#define ICMS_DEFINE_HIK_MPEG2									0x0041

#define ICMS_DEFINE_VIDEO_H264									0x0080
#define ICMS_DEFINE_HIK_H264									0x0081
#define ICMS_DEFINE_DAHUA_H264									0x0082
#define ICMS_DEFINE_YAAN_H264									0x0083
#define ICMS_DEFINE_HUAMAI_H264                                 0x0084
#define ICMS_DEFINE_CREARO_H264                                 0x0085

#define ICMS_DEFINE_VIDEO_MSMPEG4V1								0x0090
#define ICMS_DEFINE_VIDEO_MSMPEG4V2								0x0091
#define ICMS_DEFINE_VIDEO_MSMPEG4V3								0x0092
#define ICMS_DEFINE_VIDEO_WMV1									0x0093
#define ICMS_DEFINE_VIDEO_WMV2									0x0094
#define ICMS_DEFINE_VIDEO_MEGAEYES								0x0095
#define ICMS_DEFINE_AUDIO_MEGAEYES								0x0096

#define ICMS_DEFINE_VIDEO_EASY7      							0x009b


#define ICMS_DEFINE_STREAM_DEC									0x0100 /* 表示为解码后的数据 */
#define ICMS_DEFINE_STREAM_RAW									0x0200 

#define ICMS_DEFINE_METADATE_DEPA								0x0300 /* Depa元数据 */

#define ICMS_DEFINE_DATA_EXTTYPE_ALTERRECDIR					0xf001 /* 录像任务存储路径切换 */

//sub type
#define ICMS_DEFINE_SUBTYPE_FRAME_I								0x01
#define ICMS_DEFINE_SUBTYPE_FRAME_P								0x02
#define ICMS_DEFINE_SUBTYPE_FRAME_B								0x03
#define ICMS_DEFINE_SUBTYPE_NOKEYFRAME							0x04   

//audio bitrate
#define ICMS_DEFINE_AUDIO_BITRATE_16K							0x01
#define ICMS_DEFINE_AUDIO_BITRATE_24K							0x02
#define ICMS_DEFINE_AUDIO_BITRATE_32K							0x03
#define ICMS_DEFINE_AUDIO_BITRATE_40K							0x04
#define ICMS_DEFINE_AUDIO_BITRATE_64K							0x05

#pragma region 域信息
#define GET_DOMAIN_SYSTEMINFO_REQ					0x3000
#define GET_DOMAIN_SYSTEMINFO_ACK					0x3001

#define GET_DOMAINCLIENT_INFO_REQ					0x3002
#define GET_DOMAINCLIENT_INFO_ACK					0x3003

#define UPDATE_DOMAINCLIENT_INFO_REQ				0x3004
#define UPDATE_DOMAINCLIENT_INFO_ACK				0x3005

#define GET_ROUTE_INFO_REQ							0x3006
#define GET_ROUTE_INFO_ACK							0x3007

#define UPDATE_ROUTE_INFO_REQ						0x3008
#define UPDATE_ROUTE_INFO_ACK						0x3009

// 创建域成员
#define IDOMAIN_ADD_DOMAINCLIENT_REQ				0x301A
#define IDOMAIN_ADD_DOMAINCLIENT_ACK				0x301B

// 关联域成员(用于域内部,单条数据)
#define IDOMAIN_ADD_DOMAINROUTE_REQ					0x301C
#define IDOMAIN_ADD_DOMAINROUTE_ACK					0x301D

// 删除域成员(用于域内部,单条数据)
#define IDOMAIN_DEL_DOMAINCLIENT_REQ				0x301E
#define IDOMAIN_DEL_DOMAINCLIENT_ACK				0x301F

// 删除域路由(用于域内部,单条数据)
#define IDOMAIN_DEL_DOMAINROUTE_REQ					0x3020
#define IDOMAIN_DEL_DOMAINROUTE_ACK					0x3021

// 手动同步
#define IDOMAIN_MANUAL_SYNC_REQ						0x3022
#define IDOMAIN_MANUAL_SYNC_ACK						0x3023

// 域成员版本验证
#define IDOMAIN_DCVERSION_VERIFY_REQ				0x3024
#define IDOMAIN_DCVERSION_VERIFY_ACK				0x3025

// 域成员关系版本验证
#define IDOMAIN_DRVERSION_VERIFY_REQ				0x3026
#define IDOMAIN_DRVERSION_VERIFY_ACK				0x3027

// 域数据版本验证
#define IDOMAIN_DDVERSION_VERIFY_REQ				0x3028
#define IDOMAIN_DDVERSION_VERIFY_ACK				0x3029

// 自动同步请求
#define IDOMAIN_AUTO_SYNC_REQ						0x302A
#define IDOMAIN_AUTO_SYNC_ACK						0x302B

// 获取域成员
#define IDOMAIN_GET_DOMAINCLENT_REQ					0x302C
#define IDOMAIN_GET_DOMAINCLENT_ACK					0x302D

// 获取域路由
#define IDOMAIN_GET_DOMAINROUTE_REQ					0x302E
#define IDOMAIN_GET_DOMAINROUTE_ACK					0x302F

// 获取域数据请求
#define IDOMAIN_GET_DOMAINDATA_REQ					0x3030
#define IDOMAIN_GET_DOMAINDATA_ACK					0x3031

// 域成员更新
#define IDOMAIN_UPDATE_DOMAINCLENT_REQ				0x3032
#define IDOMAIN_UPDATE_DOMAINCLENT_ACK				0x3033

// 域路由更新
#define IDOMAIN_UPDATE_DOMAINROUTE_REQ				0x3034
#define IDOMAIN_UPDATE_DOMAINROUTE_ACK				0x3035

// 域数据更新
#define IDOMAIN_UPDATE_DOMAINDATA_REQ				0x3036
#define IDOMAIN_UPDATE_DOMAINDATA_ACK				0x3037

// 用户认证请求
#define IDOMAIN_USER_AUTHENTICATION_REQ				0x3038
#define IDOMAIN_USER_AUTHENTICATION_ACK				0x3039

// 根据IP和端口获取目标域信息 manager -> mc -> ds
#define IDOMAIN_MANAGER_2_DSERVER_GET_DOMIANINFO_REQ	0X303A
#define IDOMAIN_MANAGER_2_DSERVER_GET_DOMIANINFO_ACK	0X303B

// 添加域成员 manager -> mc -> ds
#define IDOMAIN_MANAGER_2_DSERVER_ADD_DOMAINCLIENT_REQ	0X303C
#define IDOMAIN_MANAGER_2_DSERVER_ADD_DOMAINCLIENT_ACK	0X303D

// 设置域路由 manager -> mc -> ds
#define IDOMAIN_MANAGER_2_DSERVER_SET_DOMAINROUTE_REQ	0X303E
#define IDOMAIN_MANAGER_2_DSERVER_SET_DOMAINROUTE_ACK	0X303F

// 删除域成员 manager -> mc -> ds
#define IDOMAIN_MANAGER_2_DSERVER_DEL_DOMAINCLIENT_REQ	0X3040
#define IDOMAIN_MANAGER_2_DSERVER_DEL_DOMAINCLIENT_ACK	0X3041

// 域变更设置 manager -> mc ->ds
#define  IDOMAIN_MANAGER_2_DSERVER_DOMAIN_SET_REQ 		0x3042
#define  IDOMAIN_MANAGER_2_DSERVER_DOMAIN_SET_ACK 		0x3043

// 获取目标域系统数据版本
#define IDOMAIN_GET_DOMAIN_DATA_VERSION_REQ				0x3044
#define IDOMAIN_GET_DOMAIN_DATA_VERSION_ACK				0x3045

#pragma endregion

#define ISMS_GET_SUBEQUIPMENT_REQ					0x8000
#define ISMS_GET_SUBEQUIPMENT_ACK					0x8001

#define ISMS_GET_EQUIPMENT_REQ						0x8002
#define ISMS_GET_EQUIPMENT_ACK						0x8003

#define ISMS_GET_EQUIPMENT_TYPE_REQ					0x8004
#define ISMS_GET_EQUIPMENT_TYPE_ACK					0x8005

#define ISMS_SET_EQUIPMENT_REQ						0x8006
#define ISMS_SET_EQUIPMENT_ACK						0x8007

#define ISMS_SET_SUBEQUIPMENT_REQ					0x8008
#define ISMS_SET_SUBEQUIPMENT_ACK					0x8009

#define ISMS_SET_ORGANIZE_REQ						0x800a
#define ISMS_SET_ORGANIZE_ACK						0x800b

#define ISMS_SET_EQUORG_LINK_REQ					0x800c
#define ISMS_SET_EQUORG_LINK_ACK					0x800d

#define ISMS_GET_EQUSUB_LINK_REQ					0x800e
#define ISMS_GET_EQUSUB_LINK_ACK					0x800f

#define ISMS_GET_SERVER_REQ							0x8010
#define ISMS_GET_SERVER_ACK							0x8011

#define ISMS_SET_SERVER_REQ							0x8012
#define ISMS_SET_SERVER_ACK							0x8013

#define ISMS_GET_USERGROUP_LINK_REQ					0x8014
#define ISMS_GET_USERGROUP_LINK_ACK					0x8015

#define ISMS_SET_USERGROUP_REQ						0x8016
#define ISMS_SET_USERGROUP_ACK						0x8017

#define ISMS_SET_USER_REQ							0x8018
#define ISMS_SET_USER_ACK							0x8019

#define ISMS_GET_SYSTEM_INFO_REQ					0x801a
#define ISMS_GET_SYSTEM_INFO_ACK					0x801b

#define ISMS_LOGIN_AUTHENTICATION_REQ				0x801c
#define ISMS_LOGIN_AUTHENTICATION_ACK				0x801d

#define ISMS_LOGOUT_REQ								0x801e
#define ISMS_LOGOUT_ACK								0x801f

#define ISMS_SWITCH_RELAYSYSTEM_REQ					0x8020
#define ISMS_SWITCH_RELAYSYSTEM_ACK					0x8021

#define ISMS_CANCEL_SWITCH_RELAYSYSTEM_REQ			0x8022
#define ISMS_CANCEL_SWITCH_RELAYSYSTEM_ACK			0x8023

// 更新服务器主从关系
#define ISMS_UPDATE_SERVERLEVEL_REQ					0x8026
#define ISMS_UPDATE_SERVERLEVEL_ACK					0x8027


//获取逻辑磁盘
#define ISMS_GET_SYSSTORAGE_BASIC_REQ				0x802a
#define ISMS_GET_SYSSTORAGE_BASIC_ACK				0x802b

#define ISMS_GET_USER_BASIC_REQ						0x802e
#define ISMS_GET_USER_BASIC_ACK						0x802f

#define ISMS_GET_STORAGEDISK_INFO_REQ				0x8031
#define ISMS_GET_STORAGEDISK_INFO_ACK				0x8032

// 冗余磁盘切换请求
#define ISMS_EXCHANGLE_DISKINFO_REQ					0x8035
#define ISMS_EXCHANGLE_DISKINFO_ACK					0x8036

#define ISMS_EXCHANGLE_SERVER_REQ					0x8037
#define	ISMS_EXCHANGLE_SERVER_ACK					0x8038

//获取时间配置
#define ISMS_GET_SYSTEMTIME_REQ						0x8039
#define ISMS_GET_SYSTEMTIME_ACK						0x803a

//获取报警联动信息
#define ISMS_GET_ALARM_RELATION_REQ					0x803b
#define ISMS_GET_ALARM_RELATION_ACK					0x803c

//获取报警预案
#define ISMS_GET_ALARM_PREPLAN_REQ					0x803d
#define ISMS_GET_ALARM_PREPLAN_ACK					0x803e

//获取报警录像联动信息
#define ISMS_GET_ALARM_RECORDE_REQ					0x8040
#define ISMS_GET_ALARM_RECORDE_ACK					0x8041

//获取抓帧联动信息
#define ISMS_GET_ALARM_CATCH_REQ					0x8042
#define ISMS_GET_ALARM_CATCH_ACK					0x8043

//获取云台联动信息
#define ISMS_GET_ALARM_PTZ_REQ						0x8044
#define ISMS_GET_ALARM_PTZ_ACK						0x8045

//获取电视墙联动信息
#define ISMS_GET_ALARM_TVWALL_REQ					0x8046
#define ISMS_GET_ALARM_TVWALL_ACK					0x8047

//获取输出联动信息
#define ISMS_GET_ALARM_OUTPUT_REQ					0x8048
#define ISMS_GET_ALARM_OUTPUT_ACK					0x8049

//获取监控端联动信息
#define ISMS_GET_ALARM_MONITOR_REQ					0x804a
#define ISMS_GET_ALARM_MONITOR_ACK					0x804b

//获取Email联动信息
#define ISMS_GET_ALARM_EMAIL_REQ					0x804c
#define ISMS_GET_ALARM_EMAIL_ACK					0x804d

//获取短信联动信息
#define ISMS_GET_ALARM_SMS_REQ						0x804e
#define ISMS_GET_ALARM_SMS_AKC						0x8050

//配置巡检计划
#define ISMS_SET_INSPECTION_PLAN_INFO_REQ			0x8051
#define ISMS_SET_INSPECTION_PLAN_INFO_ACK			0x8052

//查询巡检计划	
#define ISMS_LST_INSPECTION_PLAN_INFO_REQ			0x8053
#define ISMS_LST_INSPECTION_PLAN_INFO_ACK			0x8054

//配置分组轮询计划
#define ISMS_SET_GROUP_PLAN_REQ						0x8055
#define ISMS_SET_GROUP_PLAN_ACK						0x8056

//设置录像任务
#define ISMS_SET_PLAN_WEEK_RECORD_REQ 				0x8057
#define ISMS_SET_PLAN_WEEK_RECORD_ACK				0x8058

//获取录像任务
#define ISMS_LST_PLAN_WEEK_RECORD_REQ				0x8059
#define ISMS_LST_PLAN_WEEK_RECORD_ACK				0x805A

#define ISMS_GET_DEFENCE_STATE_REQ					0x805b
#define ISMS_GET_DEFENCE_STATE_ACK					0x805c

//获取布防任务
#define ISMS_GET_PLAN_DEFENCE_REQ					0x805D
#define ISMS_GET_PLAN_DEFENCE_ACK					0x805E

//设置布防任务
#define ISMS_SET_PLAN_DEFENCE_REQ					0x805F
#define ISMS_SET_PLAN_DEFENCE_ACK					0x8060

#define ISMS_SET_ALARM_LOG_REQ						0x8961
#define ISMS_SET_ALARM_LOG_ACK						0x8962

#define ISMS_UPT_ALARM_LOG_REQ						0x8061
#define ISMS_UPT_ALARM_LOG_ACK						0x8062

#define ISMS_SET_SYSTEM_LOG_REQ						0x8063
#define ISMS_SET_SYSTEM_LOG_ACK						0x8064

#define ISMS_SET_ALARM_LEVEL_REQ                    0x8065
#define ISMS_SET_ALARM_LEVEL_ACK                    0x8066

#define ISMS_SET_USER_LOGIN_REQ                     0x8067
#define ISMS_SET_USER_LOGIN_ACK                     0x8068

//查询巡检结果
#define ISMS_GET_INSPECTION_RESULT_REQ				0x8069
#define ISMS_GET_INSPECTION_RESULT_ACK				0x806A

//获取设备与子设备关系
#define ISMS_LST_EQUIPMENT_REQ						0x806B
#define ISMS_LST_EQUIPMENT_ACK						0x806C

//获取文件扩展信息
#define ISMS_GET_FILEEXTENSION_REQ                  0x806D 
#define ISMS_GET_FILEEXTENSION_ACK                  0x806E

//设置文件扩展信息
#define ISMS_SET_FILEEXTENSION_REQ                  0x806F
#define ISMS_SET_FILEEXTENSION_ACK                  0x8070

//配置存储磁盘信息
#define ISMS_SET_DISKSTORGEINFO_REQ                 0x8071
#define ISMS_SET_DISKSTORGEINFO_ACK                 0x8072

//配置地图信息
#define ISMS_SET_MAPPICTURE_REQ                     0x8073
#define ISMS_SET_MAPPICTURE_ACK						0x8074

//获取地图数据
#define ISMS_GET_MAPPICTURE_REQ						0x8075
#define ISMS_GET_MAPPICTURE_ACK						0x8076

//获取版本信息
#define ISMS_GET_VERSION_REQ						0x8077
#define ISMS_GET_VERSION_ACK						0x8078

//配置版本信息
#define ISMS_SET_VERSION_REQ						0x8079
#define ISMS_SET_VERSION_ACK						0x8080

//获取MSCS信息
#define ISMS_GET_MSCS_REQ                           0x8081
#define ISMS_GET_MSCS_ACK                           0x8082

//配置MSCS信息
#define ISMS_SET_MSCS_REQ                           0x8083
#define ISMS_SET_MSCS_ACK                           0x8084

//配置报警联动信息
#define ISMS_SET_ALARM_RELATION_REQ					0x8085
#define ISMS_SET_ALARM_RELATION_ACK					0x8086

//配置报警预案
#define ISMS_SET_ALARM_PREPLAN_REQ					0x8087
#define ISMS_SET_ALARM_PREPLAN_ACK					0x8088

//配置报警录像联动信息
#define ISMS_SET_ALARM_RECORDE_REQ					0x8089
#define ISMS_SET_ALARM_RECORDE_ACK					0x808A

//配置抓帧联动信息
#define ISMS_SET_ALARM_CATCH_REQ					0x808B
#define ISMS_SET_ALARM_CATCH_ACK					0x808C

//配置云台联动信息
#define ISMS_SET_ALARM_PTZ_REQ						0x808D
#define ISMS_SET_ALARM_PTZ_ACK						0x808E

//配置电视墙联动信息
#define ISMS_SET_ALARM_TVWALL_REQ					0x8090
#define ISMS_SET_ALARM_TVWALL_ACK					0x8091

//配置输出联动信息
#define ISMS_SET_ALARM_OUTPUT_REQ					0x8092
#define ISMS_SET_ALARM_OUTPUT_ACK					0x8093

//配置监控端联动信息
#define ISMS_SET_ALARM_MONITOR_REQ					0x8094
#define ISMS_SET_ALARM_MONITOR_ACK					0x8095

//配置Email联动信息
#define ISMS_SET_ALARM_EMAIL_REQ					0x8096
#define ISMS_SET_ALARM_EMAIL_ACK					0x8097

//配置短信联动信息
#define ISMS_SET_ALARM_SMS_REQ						0x8098
#define ISMS_SET_ALARM_SMS_AKC						0x8099

//配置报警等级
#define ISMS_SET_ALARM_LEVER_REQ					0x809A
#define ISMS_SET_ALARM_LEVER_AKC					0x809B

//获取报警等级
#define ISMS_GET_ALARM_LEVER_REQ					0x809C
#define ISMS_GET_ALARM_LEVER_AKC					0x809D

//配置逻辑磁盘
#define ISMS_SET_SYSSTORAGE_BASIC_REQ				0x809E
#define ISMS_SET_SYSSTORAGE_BASIC_ACK				0x80AF

//获取取证资源分配管理
#define ISMS_GET_EVIDENCEALLOCATEINFO_REQ           0x80A5
#define ISMS_GET_EVIDENCEALLOCATEINFO_ACK           0x80A6

//获取取证资源分配管理
#define ISMS_SET_EVIDENCEALLOCATEINFO_REQ           0x80A7
#define ISMS_SET_EVIDENCEALLOCATEINFO_ACK           0x80A8

//获取存储资源磁盘树
#define ISMS_GET_STORAGERESOURCEDISK_REQ			0x80A9
#define ISMS_GET_STORAGERESOURCEDISK_ACK			0x80AA

//设置存储资源磁盘树
#define ISMS_SET_STORAGERESOURCEDISK_REQ			0x80AB
#define ISMS_SET_STORAGERESOURCEDISK_ACK			0x80AC

//获取存储资源分配 
#define ISMS_GET_STORAGERESOURCE_REQ				0x80AD
#define ISMS_GET_STORAGERESOURCE_ACK				0x80AE

//设置存储资源分配 
#define ISMS_SET_STORAGERESOURCE_REQ				0x80AF
#define ISMS_SET_STORAGERESOURCE_ACK				0x80b0

//获取电视墙信息
#define ISMS_GET_MATRIXSERVERINFO_REQ				0x80B1
#define ISMS_GET_MATRIXSERVERINFO_ACK				0x80B2

//设置电视墙信息
#define ISMS_SET_MATRIXSERVERINFO_REQ				0x80B3
#define ISMS_SET_MATRIXSERVERINFO_ACK				0x80B4

//删除域数据
#define ISMS_DELETE_DOMAINDATA_REQ					0x80B5
#define ISMS_DELETE_DOMAINDATA_ACK					0x80B6

//获取报警类型
#define ISMS_GET_ALARMTYPE_REQ						0x80B7
#define ISMS_GET_ALARMTYPE_ACK						0x80B8

//设置透明数据
#define ISMS_SET_TRANSPARENTDATA_REQ				0x80B9
#define ISMS_SET_TRANSPARENTDATA_ACK				0x80BA

//获取透明数据
#define ISMS_GET_TRANSPARENTDATA_REQ				0x80BB
#define ISMS_GET_TRANSPARENTDATA_ACK				0x80BC

//配置用户基本信息
#define ISMS_MOD_USER_BASIC_INFO_REQ				0x80BD
#define ISMS_MOD_USER_BASIC_INFO_ACK				0x80BE

//配置用户密码
#define ISMS_MOD_USER_PASSWORD_REQ					0x80BF
#define ISMS_MOD_USER_PASSWORD_ACK					0x80C0

//配置用户操作权限
#define ISMS_MOD_USER_OPERATE_AUTHORITY_REQ			0x80C1
#define ISMS_MOD_USER_OPERATE_AUTHORITY_ACK			0x80C2

//配置用户设备权限
#define ISMS_MOD_USER_DEVICE_AUTHORITY_REQ			0x80C3
#define ISMS_MOD_USER_DEVICE_AUTHORITY_ACK			0x80C4

//设置用户组设备权限
#define ISMS_MOD_USERGROUP_DEVICE_AUTHORITY_REQ		0x80C5
#define ISMS_MOD_USERGROUP_DEVICE_AUTHORITY_ACK		0x80C6

//获取用户组设备权限
#define	ISMS_GET_USERGROUP_DEVICE_AUTHORITY_REQ		0x80C7
#define	ISMS_GET_USERGROUP_DEVICE_AUTHORITY_ACK		0x80C8

//获取域用户信息
#define IDOMAIN_GET_DUSERINFO_REQ	0x303a
#define IDOMAIN_GET_DUSERINFO_ACK	0x303b

//配置域用户信息
#define IDOMAIN_UPDATE_DUSERINFO_REQ	0x303c
#define IDOMAIN_UPDATE_DUSERINFO_ACK	0x303d

//获取锁定的录像和抓帧文件信息
#define ISMS_GET_LOCKEDFILEINFO_REQ 	0x80C9
#define ISMS_GET_LOCKEDFILEINFO_ACK 	0x80CA

//获取物理磁盘和文件的关系
#define ISMS_GET_PHYSICSDISKANDFILERELATION_REQ 0x80CB
#define ISMS_GET_PHYSICSDISKANDFILERELATION_ACK 0x80CC

//获取迁移文件信息(取证)
#define ISMS_GET_MIGRATEFILEINFO_REQ	0x80CD
#define ISMS_GET_MIGRATEFILEINFO_ACK	0x80CE 

//获取迁移抓帧信息(取证)
#define  ISMS_GET_MIGRATEPICFILEINFO_REQ		0x80CF
#define  ISMS_GET_MIGRATEPICFILEINFO_ACK		0x80D0


//获取迁移相关信息(包括未完成的迁移任务信息, 任务完成且未被解锁的迁移任务)
#define  ISMS_GET_MIGRATETASKINFO_REQ		0x80D1
#define  ISMS_GET_MIGRATETASKINFO_ACK		0x80D2

//获取迁移存储配置信息
#define  ISMS_GETMIGRATESTORECONFIGINFO_REQ		0x80D2
#define  ISMS_GETMIGRATESTORECONFIGINFO_ACK		0x80D3

//配置迁移任务
#define  ISMS_SET_MIGRATETASK_REQ	0x80D4
#define  ISMS_SET_MIGRATETASK_ACK	0x80D5

//配置地图目录
#define	 ISMS_SET_MAPLIST_REQ	0x80D6
#define	 ISMS_SET_MAPLIST_ACK	0x80D7

//配置录像文件
#define ISMS_SET_FILESINFO_REQ		0x80D8
#define ISMS_SET_FILESINFO_ACK		0x80D9

//配置抓帧文件
#define ISMS_SET_PICFILESINFO_REQ		0x80DA
#define ISMS_SET_PICFILESINFO_ACK		0x80DB

//配置文件标签信息
#define ISMS_SET_TAGINFO_REQ 0x80DC
#define ISMS_SET_TAGINFO_ACK 0x80DD

//获取文件标签信息
#define ISMS_GET_TAGINFO_REQ 0x80DE
#define ISMS_GET_TAGINFO_ACK 0x80DF

//获取分割录像大小
#define ISMS_GET_RECORD_SIZE_REQ 0x80E0
#define ISMS_GET_RECORD_SIZE_ACK 0x80E1

//配置地图节点
#define	 ISMS_SET_MAPLEAF_REQ	0x80E2
#define	 ISMS_SET_MAPLEAF_ACK	0x80E3

//配置地图节点关系
#define	 ISMS_SET_MAPLEAFASS_REQ	0x80E4
#define	 ISMS_SET_MAPLEAFASS_ACK	0x80E5

//配置地图子设备关系
#define	 ISMS_SET_MAPSUBEQUASS_REQ	0x80E6
#define	 ISMS_SET_MAPSUBEQUASS_ACK	0x80E7

//锁定指定文件
#define ISMS_LOCKFILES_REQ         0x80E8
#define ISMS_LOCKFILES_ACK		   0x80E9

//解除锁定文件
#define ISMS_UNLOCKFILES_REQ		0x80EA
#define ISMS_UNLOCKFILES_ACK		0x80EB

//更新设备类型
#define ISMS_SET_DEVICE_TYPE_REQ	0x80EC
#define ISMS_SET_DEVICE_TYPE_ACK	0x80ED

//查询系统日志
#define ISMS_GET_SYSTEMLOG_REQ		0x80EE
#define ISMS_GET_SYSTEMLOG_ACK		0x80EF

//查询报警日志
#define ISMS_GET_ALARMLOG_REQ		0x80F0
#define ISMS_GET_ALARMLOG_ACK		0x80F1

//获取未处理的报警信息
#define ICMS_TYPE_CTRLTYPE_UNTREATED_ALARM_REQ  0x0d4f
#define ICMS_TYPE_CTRLTYPE_UNTREATED_ALARM_ACK  0x0d50

//配置迁移任务
#define  ISMS_DEL_MIGRATETASK_REQ	0x80F2
#define  ISMS_DEL_MIGRATETASK_ACK	0x80F3

//配置预置点
#define ISMS_SET_SUBPREDEFINEPOS_REQ	0x80F4
#define ISMS_SET_SUBPREDEFINEPOS_ACK	0x80F5

//配置预置点
#define ISMS_SET_SUBPREDEFINECRUISE_REQ	0x80F6
#define ISMS_SET_SUBPREDEFINECRUISE_ACK	0x80F7

//获取锁定空间大小
#define ISMS_GET_LOCKED_SPACE_LIMIT_REQ 0x80F8
#define ISMS_GET_LOCKED_SPACE_LIMIT_ACK 0x80F9

//设置锁定空间大小
#define ISMS_SET_LOCKED_SPACE_SIZE_REQ 0x80FA
#define ISMS_SET_LOCKED_SPACE_SIZE_ACK 0x80FB

// 负载请求
#define ISMS_SMS_2_SPS_GET_LOADSTATUS_INFO_REQ		0x80FC
#define	ISMS_SMS_2_SPS_GET_LOADSTATUS_INFO_ACK		0x80FD
// 负载通知
#define ISMS_SPS_2_SMS_LOADSTATUS_INFO_NOTIFY_REQ	0x80FE

//配置用户组系统权限
#define ISMS_MOD_USERGROUP_AUTHORITY_REQ 0x80FF
#define ISMS_MOD_USERGROUP_AUTHORITY_ACK 0x8100

//获取用户组系统权限
#define ISMS_GET_USERGROUP_AUTHORITY_REQ 0x8101
#define ISMS_GET_USERGROUP_AUTHORITY_ACK 0x8102

//更新录像迁移任务进度
#define  ISMS_SET_MIGRATE_CURRENT_POS_TIME_REQ	0x8103
#define  ISMS_SET_MIGRATE_CURRENT_POS_TIME_ACK	0x8104	

//设置迁移编目
#define ISOC_SET_MIGRATE_FILE_CATALOGUE_INFO_REQ 0x8105
#define ISOC_SET_MIGRATE_FILE_CATALOGUE_INFO_ACK 0x8106

//获取迁移编目信息
#define ISOC_GET_MIGRATE_FILE_CATALOGUE_INFO_REQ 0x8107
#define ISOC_GET_MIGRATE_FILE_CATALOGUE_INFO_ACK 0x8108

//配置系统信息
#define ISMS_SET_SYSTEM_INFO_REQ				0x8109
#define ISMS_SET_SYSTEM_INFO_ACK				0x810A

//删除抓帧文件
#define ISMS_DELETE_PICFILE_REQ					0x810B
#define ISMS_DELETE_PICFILE_ACK					0x810C

//ISMS数据库备份：
//手动备份数据库
#define ISMS_MANUAL_BACKUP_REQ					0x810D
#define ISMS_MANUAL_BACKUP_ACK					0x810E

//获取自动备份设置
#define ISMS_GET_AUTO_BACKUP_CONFIG_REQ			0x810F
#define ISMS_GET_AUTO_BACKUP_CONFIG_ACK			0x8110

//配置自动备份
#define ISMS_SET_AUTO_BACKUP_REQ				0x8111
#define ISMS_SET_AUTO_BACKUP_ACK				0x8112

//获取已有的备份
#define ISMS_GET_BACKUP_DATA_REQ				0x8113
#define ISMS_GET_BACKUP_DATA_ACK				0x8114

//恢复数据库
#define ISMS_RESTORE_DATABASE_REQ				0x8115
#define ISMS_RESTORE_DATABASE_ACK				0x8116

//删除备份数据
#define ISMS_DELETE_BACKUP_DATA_REQ 			0x8117
#define ISMS_DELETE_BACKUP_DATA_ACK 			0x8118

//配置系统时间
#define ISMS_SET_SYSTEMTIME_REQ					0x8119
#define ISMS_SET_SYSTEMTIME_ACK					0x811A

//获取地图节点信息
#define ISMS_GET_MAPLEAF_REQ					0x811B
#define ISMS_GET_MAPLEAF_ACK					0x811C

#define ISMS_UPT_TALK_LOG_REQ						0x8121
#define ISMS_UPT_TALK_LOG_ACK						0x8122

#define ISMS_GET_TALK_LOG_REQ						0x8123
#define ISMS_GET_TALK_LOG_ACK						0x8124


#pragma region IPGS服务信令
//数据方向 : 管理客户端----> SMS---->管理伺服
#define IPGS_SERVO_LOGIN_REQ						0x9001
#define IPGS_SERVO_LOGIN_ACK						0x9002

// 服务器信令
//数据方向 : 管理客户端----> SMS---->管理伺服
#define IPGS_SERVO_GET_SERVER_REQ					0x9003
#define IPGS_SERVO_GET_SERVER_ACK					0x9004

//数据方向 : 管理客户端----> SMS---->管理伺服
#define IPGS_SERVO_SET_SERVER_REQ					0x9005
#define IPGS_SERVO_SET_SERVER_ACK					0x9006

// 服务信令
//数据方向 : 管理伺服----> SMS---->管理客户端
#define IPGS_SERVO_GET_SERVICE_REQ					0x9007
#define IPGS_SERVO_GET_SERVICE_ACK					0x9008

//数据方向 : 管理伺服----> SMS---->管理客户端
#define IPGS_SERVO_SET_SERVICE_REQ					0x9009
#define IPGS_SERVO_SET_SERVICE_ACK					0x900a

// 系统信令
//数据方向 : 管理客户端----> SMS---->管理伺服
#define IPGS_SERVO_GET_SYSTEM_REQ					0x900b
#define IPGS_SERVO_GET_SYSTEM_ACK					0x900c

//数据方向 : 管理客户端----> SMS---->管理伺服
#define IPGS_SERVO_SET_SYSTEM_REQ					0x900d
#define IPGS_SERVO_SET_SYSTEM_ACK					0x900e

// 用户信令
//数据方向 : 管理客户端----> SMS---->管理伺服
#define IPGS_SERVO_GET_USER_REQ						0x900f
#define IPGS_SERVO_GET_USER_ACK						0x9010

//数据方向 : 管理客户端----> SMS---->管理伺服
#define IPGS_SERVO_SET_USER_REQ						0x9011
#define IPGS_SERVO_SET_USER_ACK						0x9012

// 用户映射信令
//数据方向 : 管理客户端----> SMS---->管理伺服
#define IPGS_SERVO_GET_USERMAP_REQ					0x9013
#define IPGS_SERVO_GET_USERMAP_ACK 					0x9014

//数据方向 : 管理客户端----> SMS---->管理伺服
#define IPGS_SERVO_SET_USERMAP_REQ					0x9015
#define IPGS_SERVO_SET_USERMAP_ACK					0x9016

// 操作类型信令
//数据方向 : 管理客户端----> SMS---->管理伺服
#define IPGS_SERVO_GET_OPTYPE_REQ					0x9017
#define IPGS_SERVO_GET_OPTYPE_ACK 					0x9018
#pragma endregion

// 前端设备校时
#define	ISMS_CLIENT_2_SMS_ADJUST_DEV_TIME_REQ		0x9019
#define	ISMS_CLIENT_2_SMS_ADJUST_DEV_TIME_ACK		0x901A

// 获取设备录像状态
#define	ISMS_CLIENT_2_SMS_GET_DEV_RECORD_STATE_INFO_REQ		0x901B
#define	ISMS_CLIENT_2_SMS_GET_DEV_RECORD_STATE_INFO_ACK		0x901C


// 级联系统更新通知
#define ISMS_DOMAIN_MEMBER_UPDATE_NOTIFY			0X901F

// 获取级联的迁移域成员信息
#define ISMS_GET_TRANSFER_DOMAIN_MEMBER_REQ			0X9020
#define ISMS_GET_TRANSFER_DOMAIN_MEMBER_ACK			0X9021

#pragma region 青岛招行项目信令宏定义

// 交接班设置
#define ISMS_CLIENT_2_SMS_RELIEVEVALIDATE_REQ		0X9022
#define ISMS_CLIENT_2_SMS_RELIEVEVALIDATE_ACK		0X9023

// 通告信息通知
#define ISMS_NOTICE_INFO_NOTIFY						0x901e

// 配置监察信息
#define ISMS_SET_SUPERVISE_INFO_REQ					0x9024
#define ISMS_SET_SUPERVISE_INFO_ACK					0x9025

// 查询监察信息
#define ISMS_GET_SUPERVISE_INFO_REQ             0x9026
#define ISMS_GET_SUPERVISE_INFO_ACK             0x9027

// 通告信息通知
#define ISMS_NOTICE_INFO_NOTIFY						0x901e

// 配置监察信息
#define ISMS_SET_SUPERVISE_INFO_REQ					0x9024
#define ISMS_SET_SUPERVISE_INFO_ACK					0x9025

// 查询监察信息
#define ISMS_GET_SUPERVISE_INFO_REQ					0x9026
#define ISMS_GET_SUPERVISE_INFO_ACK					0x9027

#pragma endregion
/*************************** 磁盘阵列相关信令 ********************************/
//查询所有磁盘信息 	数据方向 : 管理客户端----> LNVRLServer
#define ILNVRL_QUERY_All_DISK_INFO_REQ							0x9028
#define ILNVRL_QUERY_All_DISK_INFO_ACK 							0x9029
//建立磁盘阵列 	数据方向 : 管理客户端----> LNVRLServer
#define ILNVRL_CREATE_DISK_ARRAY_REQ							0x902a
#define ILNVRL_CREATE_DISK_ARRAY_ACK							0x902b
//查询阵列信息 	数据方向 : 管理客户端----> LNVRLServer
#define ILNVRL_QUERY_DISK_ARRAY_STATUS_REQ						0x902c
#define ILNVRL_QUERY_DISK_ARRAY_STATUS_ACK 						0x902d

//停止一个阵列 	数据方向 : 管理客户端----> LNVRLServer
#define ILNVRL_STOP_DISK_ARRAY_REQ							    0x902e
#define ILNVRL_STOP_DISK_ARRAY_ACK							    0x902f

//失效阵列中一个磁盘 	数据方向 : 管理客户端----> LNVRLServer
#define ILNVRL_FAIL_DISK_IN_ARRAY_REQ							0x9030
#define ILNVRL_FAIL_DISK_IN_ARRAY_ACK							0x9031
//移除阵列中一个磁盘 	数据方向 : 管理客户端----> LNVRLServer
#define ILNVRL_REMOVE_DISK_FROM_ARRAY_REQ						0x9032
#define ILNVRL_REMOVE_DISK_FROM_ARRAY_ACK 						0x9033
//添加磁盘到阵列（添加备份盘） 	数据方向 : 管理客户端----> LNVRLServer
#define ILNVRL_ADD_DISK_TO_ARRAY_REQ							0x9034
#define ILNVRL_ADD_DISK_TO_ARRAY_ACK 							0x9035

//清除磁盘中的原阵列信息  数据方向: 管理客户端----> LNVRLServer
#define ILNVRL_CLEAR_ARRAY_INFO_IN_DISK_REQ						0x9036
#define ILNVRL_CLEAR_ARRAY_INFO_IN_DISK_ACK 					0x9037

//磁盘阵列状态变更通知 数据方向 : LNVRLServer ---->  管理客户端
#define ILNVRL_EXTERNAL_MDADM_NOTFIY							0x9038


//设置盘柜备注信息 	数据方向 : 管理客户端----> LNVRLServer
#define ILNVRL_SET_CHEST_MARK_INFO_REQ							0x9040
#define ILNVRL_SET_CHEST_MARK_INFO_ACK 							0x9041

#define ISMS_CLIENT_2_SPS_GETRECTASK_STATUS_REQ     0x9044
#define ISMS_CLIENT_2_SPS_GETRECTASK_STATUS_ACK     0x9045
//视音频
/*#pragma pack(push,1)*/
typedef struct tag_STBasicData
{
	//视音频数据主类型
	DWORD  wMainType;
	//视音频数据扩展类型
	DWORD  wExtType;
	//视音频数据子类型
	DWORD  wSubType;
	//iCMS ID
	GUID guid_ICMS;

	GUID guidStreamFlag;

	//设备ID
	DWORD dwDeviceID;
	//子设备ID（通道。。etc）
	DWORD dwSubDeviceID;
	//数据起始时间.   100ns
	ULONGLONG llBeginTime;          
	//数据相对时间. 100ns
	ULONGLONG llRelativeTimeTick;

	union 
	{
		struct
		{
			int nWidth;
			int nHeight;
			double dFps;     
			DWORD dwBitrate; //bitrate,  bps
		}Basic_VideoInfo;

		struct 
		{
			int nFrequency;
			BYTE cChannel;
			BYTE cBitcount;
			DWORD dwBitrate;//bitrate,  bps
		}Basic_AudioIfno;

	}Basic_MediaInfo;

	//数据包大小
	DWORD dwTotalDataSize;
	//数据指针
	BYTE* pData;

	WORD wPrivateType;           //私有数据类型
	DWORD dwPrivateDataSize;     //私有数据大小
	BYTE* pPrivateData;			 //私有数据指针

	DWORD dwPanPosition;		//摄像机水平位置
	DWORD dwTiltPosition;		//摄像机垂直位置
	DWORD dwZoomScale;			//镜头景深


	DWORD dwReserved0;
	DWORD dwReserved1;

	tag_STBasicData()
	{
		wMainType		= ICMS_DEFINE_TYPE_NONE;
		wExtType		= ICMS_DEFINE_TYPE_NONE;
		wSubType		= ICMS_DEFINE_TYPE_NONE;
		guid_ICMS		= GUID_NULL;
		guidStreamFlag	= GUID_NULL;
		dwDeviceID		= 0;
		dwSubDeviceID	= 0;
		llBeginTime		= 0;          
		llRelativeTimeTick = 0;

		memset(&Basic_MediaInfo, 0, sizeof(Basic_MediaInfo));

		
		pData				= NULL;
		dwTotalDataSize		= 0;
		pPrivateData		= NULL;
		dwPrivateDataSize	= 0;  
		wPrivateType		= 0;
		

		dwPanPosition	= 0;	
		dwTiltPosition	= 0;	
		dwZoomScale		= 0;

		dwReserved0 = 0;
		dwReserved1 = 0;
	}

	~tag_STBasicData()
	{
		if (pData)
			delete[] pData;
		pData = NULL;

		if (pPrivateData)
			delete[] pPrivateData;
		pPrivateData = NULL;

		dwPrivateDataSize = 0;
		dwTotalDataSize = 0;
	}
	tag_STBasicData(const tag_STBasicData& src)
	{
		wMainType = src.wMainType;
		wExtType = src.wExtType;
		wSubType = src.wSubType;
		memcpy(&guid_ICMS, &src.guid_ICMS,sizeof(guid_ICMS));
		memcpy(&guidStreamFlag, &src.guidStreamFlag,sizeof(guidStreamFlag));
		dwDeviceID = src.dwDeviceID;
		dwSubDeviceID = src.dwSubDeviceID;
		llBeginTime = src.llBeginTime;
		llRelativeTimeTick = src.llRelativeTimeTick;
		memcpy(&Basic_MediaInfo, &src.Basic_MediaInfo, sizeof(Basic_MediaInfo));
		pData			= NULL;
		dwTotalDataSize	= 0;
		pPrivateData	= NULL;
		dwPrivateDataSize=0;
// 		if(pData)
// 		{
// 			delete []pData;
// 			pData = NULL;
// 		}
		if(src.dwTotalDataSize > 0)
		{
			pData = new BYTE[src.dwTotalDataSize];
			dwTotalDataSize = src.dwTotalDataSize;
			memcpy(pData, src.pData, dwTotalDataSize);
		}
		
		wPrivateType = src.wPrivateType;
// 		if(pPrivateData)
// 		{
// 			delete []pPrivateData;
// 			pPrivateData = NULL;
// 		}
		if(src.dwPrivateDataSize > 0)
		{
			pPrivateData = new BYTE[src.dwPrivateDataSize];
			dwPrivateDataSize = src.dwPrivateDataSize;
			memcpy(pPrivateData, src.pPrivateData, dwPrivateDataSize);	
		}
		
		dwPanPosition = src.dwPanPosition;	
		dwTiltPosition = src.dwTiltPosition;	
		dwZoomScale = src.dwZoomScale;

		dwReserved0 = src.dwReserved0;
		dwReserved1 = src.dwReserved1;
	}

	tag_STBasicData& tag_STBasicData::operator =(const tag_STBasicData& src)
	{
		wMainType = src.wMainType;
		wExtType = src.wExtType;
		wSubType = src.wSubType;
		memcpy(&guid_ICMS, &src.guid_ICMS,sizeof(guid_ICMS));
		memcpy(&guidStreamFlag, &src.guidStreamFlag,sizeof(guidStreamFlag));
		dwDeviceID = src.dwDeviceID;
		dwSubDeviceID = src.dwSubDeviceID;
		llBeginTime = src.llBeginTime;
		llRelativeTimeTick = src.llRelativeTimeTick;
		memcpy(&Basic_MediaInfo, &src.Basic_MediaInfo, sizeof(Basic_MediaInfo));

		if(pData)
		{
			delete []pData;
			pData = NULL;
		}
		
		if(src.dwTotalDataSize > 0)
		{
			pData = new BYTE[src.dwTotalDataSize];
			dwTotalDataSize = src.dwTotalDataSize;
			memcpy(pData, src.pData, dwTotalDataSize);	
		}
		

		wPrivateType = src.wPrivateType;
		if(pPrivateData)
		{
			delete []pPrivateData;
			pPrivateData = NULL;
		}
		if(src.dwPrivateDataSize)
		{
			pPrivateData = new BYTE[src.dwPrivateDataSize];
			dwPrivateDataSize = src.dwPrivateDataSize;
			memcpy(pPrivateData, src.pPrivateData, dwPrivateDataSize);	
		}		

		dwPanPosition = src.dwPanPosition;	
		dwTiltPosition = src.dwTiltPosition;	
		dwZoomScale = src.dwZoomScale;

		dwReserved0 = src.dwReserved0;
		dwReserved1 = src.dwReserved1;

		return *this;
	}

	int tag_STBasicData::Serialize(CArchive& ar)
	{
		try
		{
			if(ar.IsStoring())
			{
				ar << wMainType;
				ar << wExtType;
				ar << wSubType;
				ar.Write(&guid_ICMS,sizeof(guid_ICMS));
				ar.Write(&guidStreamFlag,sizeof(guidStreamFlag));
				ar << dwDeviceID;
				ar << dwSubDeviceID;
				ar.Write(&llBeginTime, sizeof(llBeginTime));
				ar.Write(&llRelativeTimeTick, sizeof(llRelativeTimeTick));

				ar.Write(&Basic_MediaInfo, sizeof(Basic_MediaInfo));

				ar << dwTotalDataSize;
				if (dwTotalDataSize > 0)
				{
					ar.Write(pData, dwTotalDataSize);
				}

				ar << wPrivateType;
				ar << dwPrivateDataSize;
				if (dwPrivateDataSize > 0)
				{
					ar.Write(pPrivateData, dwPrivateDataSize);
				}
	
				ar << dwPanPosition;
				ar << dwTiltPosition;
				ar << dwZoomScale;

				ar << dwReserved0;
				ar << dwReserved1;
			}
			else if(ar.IsLoading())
			{
				ar >> wMainType;
				ar >> wExtType;
				ar >> wSubType;
				ar.Read(&guid_ICMS, sizeof(guid_ICMS));
				ar.Read(&guidStreamFlag, sizeof(guidStreamFlag));
				ar >> dwDeviceID;
				ar >> dwSubDeviceID;
				ar.Read(&llBeginTime, sizeof(llBeginTime));
				ar.Read(&llRelativeTimeTick, sizeof(llRelativeTimeTick));

				ar.Read(&Basic_MediaInfo, sizeof(Basic_MediaInfo));

				ar >> dwTotalDataSize;
				if(pData)
				{
					delete []pData;
					pData = NULL;
				}
				if (dwTotalDataSize > 0)
				{
					pData = new BYTE[dwTotalDataSize];
					ar.Read(pData, dwTotalDataSize);
				}
				ar >> wPrivateType;
				ar >> dwPrivateDataSize;
				if(pPrivateData)
				{
					delete []pPrivateData;
					pPrivateData = NULL;
				}
				if (dwPrivateDataSize > 0)
				{
					pPrivateData = new BYTE[dwPrivateDataSize];
					ar.Read(pPrivateData, dwPrivateDataSize);
				}
				ar >> dwPanPosition;
				ar >> dwTiltPosition;
				ar >> dwZoomScale;

				ar >> dwReserved0;
				ar >> dwReserved1;
			}
		}
		catch(...)
		{
			//OutputDebugString(_T("STBasicData::Serialize Exception!"));
		}
		return TRUE;
	}

}ST_ICMSBASIC_DATA;
/*#pragma pack(pop)*/
///end of struct

//元数据目标信息定义
typedef struct tag_STMetaObjectInfo
{
	//当前目标数据开始
	LONG lBeginFlag;
	//运动目标ID
	LONG lObjectID;
	//运动目标类型
	LONG lObjectType;
	//目标图像特征数据
	CArray<BYTE,BYTE> arObjectInfo;
	//目标图像的描述信息
	CString strObjectInfo;
	//目标X坐标
	LONG lXPosition;
	//目标Y坐标
	LONG lYPosition;
	//目标Z坐标
	LONG lZPosition;
	//目标宽度
	LONG lWidth;
	//目标高度
	LONG lHeight;
	//目标厚度
	LONG lZLength;
	//运动目标X轴速度
	LONG lXSpeed;
	//运动目标Y轴速度
	LONG lYSpeed;
	//运动目标Z轴速度
	LONG lZSpeed;
	//目标数据结束标记
	LONG lEndFlag;

	tag_STMetaObjectInfo()
	{
		lBeginFlag = 0;
		lObjectID = 0;
		lObjectType = 0;
		lXPosition = 0;
		lYPosition = 0;
		lZPosition = 0;
		lWidth = 0;
		lHeight = 0;
		lZLength = 0;
		lXSpeed = 0;
		lYSpeed = 0;
		lZSpeed = 0;
		lEndFlag = 0;
	}
	~tag_STMetaObjectInfo()
	{

	}
	tag_STMetaObjectInfo(tag_STMetaObjectInfo &src)
	{
		lBeginFlag = src.lBeginFlag;
		lObjectID = src.lObjectID;
		lObjectType = src.lObjectType;

		DWORD dwObjectInfoCount = src.arObjectInfo.GetCount();
		for (DWORD i =0; i<dwObjectInfoCount; i++)
		{
			BYTE byElem = src.arObjectInfo[i];
			arObjectInfo.Add(byElem);
		}

		strObjectInfo = src.strObjectInfo;
		lXPosition = src.lXPosition;
		lYPosition = src.lYPosition;
		lZPosition = src.lZPosition;
		lWidth = src.lWidth;
		lHeight = src.lHeight;
		lZLength = src.lZLength;
		lXSpeed = src.lXSpeed;
		lYSpeed = src.lYSpeed;
		lZSpeed = src.lZSpeed;
		lEndFlag = src.lEndFlag;

	}

	tag_STMetaObjectInfo& tag_STMetaObjectInfo::operator = (tag_STMetaObjectInfo &src)
	{
		lBeginFlag = src.lBeginFlag;
		lObjectID = src.lObjectID;
		lObjectType = src.lObjectType;

		DWORD dwObjectInfoCount = src.arObjectInfo.GetCount();
		for (DWORD i =0; i<dwObjectInfoCount; i++)
		{
			BYTE byElem = src.arObjectInfo[i];
			arObjectInfo.Add(byElem);
		}

		strObjectInfo = src.strObjectInfo;
		lXPosition = src.lXPosition;
		lYPosition = src.lYPosition;
		lZPosition = src.lZPosition;
		lWidth = src.lWidth;
		lHeight = src.lHeight;
		lZLength = src.lZLength;
		lXSpeed = src.lXSpeed;
		lYSpeed = src.lYSpeed;
		lZSpeed = src.lZSpeed;
		lEndFlag = src.lEndFlag;
		return *this;

	}


	int tag_STMetaObjectInfo::Serialize(CArchive& ar)
	{
		try
		{
			if (ar.IsStoring())
			{
				ar<<lBeginFlag;
				ar<<lObjectID;
				ar<<lObjectType;
				DWORD dwObjectInfoCount = arObjectInfo.GetCount();
				ar<<dwObjectInfoCount;
				for (DWORD i =0; i<dwObjectInfoCount; i++)
				{
					ar<<arObjectInfo[i];
				}
				ar<<strObjectInfo;
				ar<<lXPosition;
				ar<<lYPosition;
				ar<<lZPosition;
				ar<<lWidth;
				ar<<lHeight;
				ar<<lZLength;
				ar<<lXSpeed;
				ar<<lYSpeed;
				ar<<lZSpeed;
				ar<<lEndFlag;
			} 
			else
			{
				ar>>lBeginFlag;
				ar>>lObjectID;
				ar>>lObjectType;
				DWORD dwObjectInfoCount = 0;
				ar>>dwObjectInfoCount;
				for (DWORD i =0; i<dwObjectInfoCount; i++)
				{
					BYTE byElem = 0;
					ar>>byElem;
					arObjectInfo.Add(byElem);
				}
				ar>>strObjectInfo;
				ar>>lXPosition;
				ar>>lYPosition;
				ar>>lZPosition;
				ar>>lWidth;
				ar>>lHeight;
				ar>>lZLength;
				ar>>lXSpeed;
				ar>>lYSpeed;
				ar>>lZSpeed;
				ar>>lEndFlag;
			}
		}
		catch (...)
		{
			AfxMessageBox(_T("ST_ICMSMETA_OBJECTINFO::Serialize Exception!"));
		}
		return 1;
	}
}ST_ICMSMETA_OBJECTINFO;

//元数据事件信息定义
typedef struct tag_STMetaEventInfo
{
	//开始标记
	LONG lBeginFlag;
	//警报ID
	LONG lEventID;
	//警报类型
	LONG lEventType;
	//警报事件特征数据
	CArray<BYTE,BYTE> arEventInfo;
	//当前事件规则设定参数
	CArray<BYTE,BYTE> arEventRuleInfo;
	//警报描述
	CString strEventInfo;
	//警报的时间入点
	LONGLONG llMarkInTime;
	//警报触发时间
	LONGLONG llEventTime;
	//警报的时间出点
	LONGLONG llMarkOutTime;
	//警报准确度
	float fReliability;
	//目标ID列表
	CArray<LONG,LONG> arObjcetID;
	//结束标记
	LONG lEndFlag;

	tag_STMetaEventInfo()
	{
		lBeginFlag = 0;
		lEventID = 0;
		lEventType = 0;
		llMarkInTime = 0;
		llEventTime = 0;
		llMarkOutTime = 0;
		fReliability = 0;
		lEndFlag = 0;
	}
	~tag_STMetaEventInfo()
	{

	}
	tag_STMetaEventInfo(tag_STMetaEventInfo &src)
	{
		lBeginFlag = src.lBeginFlag;
		lEventID = src.lEventID;
		lEventType = src.lEventType;

		DWORD dwEventInfoCount = src.arEventInfo.GetCount();
		for (DWORD i =0; i < dwEventInfoCount; i++)
		{
			BYTE byElem = src.arEventInfo[i];
			arEventInfo.Add(byElem);
		}

		DWORD dwEventRuleInfoCount = src.arEventRuleInfo.GetCount();
		for (DWORD i =0; i < dwEventRuleInfoCount; i++)
		{
			BYTE byElem = src.arEventRuleInfo[i];
			arEventRuleInfo.Add(byElem);
		}

		strEventInfo = src.strEventInfo;
		llMarkInTime = src.llMarkInTime;
		llEventTime = src.llEventTime;
		llMarkOutTime = src.llMarkOutTime;
		fReliability = src.fReliability;
		
		DWORD dwObjcetIDCount = src.arObjcetID.GetCount();
		for (DWORD i =0; i < dwObjcetIDCount; i++)
		{
			LONG lElem = src.arObjcetID[i];
			arObjcetID.Add(lElem);
		}
		lEndFlag = src.lEndFlag;
	}

	tag_STMetaEventInfo& tag_STMetaEventInfo::operator = (tag_STMetaEventInfo &src)
	{
		lBeginFlag = src.lBeginFlag;
		lEventID = src.lEventID;
		lEventType = src.lEventType;

		DWORD dwEventInfoCount = src.arEventInfo.GetCount();
		for (DWORD i =0; i < dwEventInfoCount; i++)
		{
			BYTE byElem = src.arEventInfo[i];
			arEventInfo.Add(byElem);
		}

		DWORD dwEventRuleInfoCount = src.arEventRuleInfo.GetCount();
		for (DWORD i =0; i < dwEventRuleInfoCount; i++)
		{
			BYTE byElem = src.arEventRuleInfo[i];
			arEventRuleInfo.Add(byElem);
		}

		strEventInfo = src.strEventInfo;
		llMarkInTime = src.llMarkInTime;
		llEventTime = src.llEventTime;
		llMarkOutTime = src.llMarkOutTime;
		fReliability = src.fReliability;

		DWORD dwObjcetIDCount = src.arObjcetID.GetCount();
		for (DWORD i =0; i < dwObjcetIDCount; i++)
		{
			LONG lElem = src.arObjcetID[i];
			arObjcetID.Add(lElem);
		}
		lEndFlag = src.lEndFlag;
		return *this;

	}

	int tag_STMetaEventInfo::Serialize(CArchive& ar)
	{
		try
		{
			if (ar.IsStoring())
			{
				ar<<lBeginFlag;
				ar<<lEventID;
				ar<<lEventType;

				DWORD dwEventInfoCount = arEventInfo.GetCount();
				ar<<dwEventInfoCount;
				for (DWORD i =0; i < dwEventInfoCount; i++)
				{
					BYTE byElem = arEventInfo[i];
					ar<<byElem;
				}

				DWORD dwEventRuleInfoCount = arEventRuleInfo.GetCount();
				ar<<dwEventRuleInfoCount;
				for (DWORD i =0; i < dwEventRuleInfoCount; i++)
				{
					BYTE byElem = arEventRuleInfo[i];
					ar<<byElem;
				}
				ar<<strEventInfo;
				ar<<llMarkInTime;
				ar<<llEventTime;
				ar<<llMarkOutTime;
				ar<<fReliability;

				DWORD dwObjcetIDCount = arObjcetID.GetCount();
				ar<<dwObjcetIDCount;
				for (DWORD i =0; i < dwObjcetIDCount; i++)
				{
					LONG lElem = arObjcetID[i];
					ar<<lElem;
				}

				ar<<lEndFlag;
			} 
			else
			{
				ar>>lBeginFlag;
				ar>>lEventID;
				ar>>lEventType;

				DWORD dwEventInfoCount = 0;
				ar>>dwEventInfoCount;
				for (DWORD i =0; i < dwEventInfoCount; i++)
				{
					BYTE byElem = 0;
					ar>>byElem;
					arEventInfo.Add(byElem);
				}

				DWORD dwEventRuleInfoCount = 0;
				ar>>dwEventRuleInfoCount;
				for (DWORD i =0; i < dwEventRuleInfoCount; i++)
				{
					BYTE byElem = 0;
					ar>>byElem;
					arEventRuleInfo.Add(byElem);
				}
				ar>>strEventInfo;
				ar>>llMarkInTime;
				ar>>llEventTime;
				ar>>llMarkOutTime;
				ar>>fReliability;

				DWORD dwObjcetIDCount = 0;
				ar>>dwObjcetIDCount;
				for (DWORD i =0; i < dwObjcetIDCount; i++)
				{
					LONG lElem = 0;
					ar>>lElem;
					arObjcetID.Add(lElem);
				}
				ar>>lEndFlag;
			}
		}
		catch (...)
		{
			AfxMessageBox(_T("ST_ICMSMETA_EVENTINFO::Serialize Exception!"));
		}
		return 1;
	}
}ST_ICMSMETA_EVENTINFO;

//元数据定义
typedef struct tag_STMetaData
{ 
	//当前元数据的开始标记
	LONG lBeginFlag;
	//通道号
	LONG lChannel;
	//当前元数据的产生时间
	LONGLONG llBeginTime;
	//活动目标个数
	LONG lObjectNum;
	//活动目标的信息
	CArray<ST_ICMSMETA_OBJECTINFO*, ST_ICMSMETA_OBJECTINFO*> arObjectInfo;
	//警报个数
	LONG lEventNum;
	//警报信息
	CArray<ST_ICMSMETA_EVENTINFO*, ST_ICMSMETA_EVENTINFO*> arEventInfo;
	//元数据包结束标记
	LONG lEndFlag;

	tag_STMetaData()
	{
		lBeginFlag = 0;
		lChannel = 0;
		llBeginTime = 0;
		lObjectNum = 0;
		lEventNum = 0;
		lEndFlag = 0;
	}
	~tag_STMetaData()
	{
		ReleaseResource();
	}

	tag_STMetaData(tag_STMetaData &src)
	{
		lBeginFlag = src.lBeginFlag;
		lChannel = src.lChannel;
		llBeginTime = src.llBeginTime;
		lObjectNum =src.lObjectNum;

		ASSERT(src.lObjectNum == src.arObjectInfo.GetCount());
		for (WORD nCount = 0; nCount < lObjectNum; nCount++)
		{
			ST_ICMSMETA_OBJECTINFO *pSrcObjectInfo = src.arObjectInfo[nCount];
			ST_ICMSMETA_OBJECTINFO *pObjectInfo = new ST_ICMSMETA_OBJECTINFO;
			memcpy(pObjectInfo, pSrcObjectInfo, sizeof(ST_ICMSMETA_OBJECTINFO));
			arObjectInfo.Add(pObjectInfo);
		}
		lEventNum = src.lEventNum;

		ASSERT(src.lEventNum == src.arEventInfo.GetCount());
		for (WORD nCount = 0; nCount < lEventNum; nCount++)
		{
			ST_ICMSMETA_EVENTINFO *pSrcEventInfo = src.arEventInfo[nCount];
			ST_ICMSMETA_EVENTINFO *pEventInfo = new ST_ICMSMETA_EVENTINFO;
			memcpy(pEventInfo, pSrcEventInfo, sizeof(ST_ICMSMETA_EVENTINFO));
			arEventInfo.Add(pEventInfo);
		}

		lEndFlag = src.lEndFlag;
	}
	
	tag_STMetaData& tag_STMetaData::operator = (tag_STMetaData &src)
	{
		lBeginFlag = src.lBeginFlag;
		lChannel = src.lChannel;
		llBeginTime = src.llBeginTime;
		lObjectNum =src.lObjectNum;

		ReleaseResource();

		ASSERT(src.lObjectNum == src.arObjectInfo.GetCount());
		for (WORD nCount = 0; nCount < lObjectNum; nCount++)
		{
			ST_ICMSMETA_OBJECTINFO *pSrcObjectInfo = src.arObjectInfo[nCount];
			ST_ICMSMETA_OBJECTINFO *pObjectInfo = new ST_ICMSMETA_OBJECTINFO;
			memcpy(pObjectInfo, pSrcObjectInfo, sizeof(ST_ICMSMETA_OBJECTINFO));
			arObjectInfo.Add(pObjectInfo);
		}
		lEventNum = src.lEventNum;

		ASSERT(src.lEventNum == src.arEventInfo.GetCount());
		for (WORD nCount = 0; nCount < lEventNum; nCount++)
		{
			ST_ICMSMETA_EVENTINFO *pSrcEventInfo = src.arEventInfo[nCount];
			ST_ICMSMETA_EVENTINFO *pEventInfo = new ST_ICMSMETA_EVENTINFO;
			memcpy(pEventInfo, pSrcEventInfo, sizeof(ST_ICMSMETA_EVENTINFO));
			arEventInfo.Add(pEventInfo);
		}

		lEndFlag = src.lEndFlag;

		return *this;
	}

	int tag_STMetaData::Serialize(CArchive& ar)
	{
		try
		{
			if (ar.IsStoring())
			{
				ar<<lBeginFlag;
				ar<<lChannel;
				ar<<llBeginTime;
				ar<<lObjectNum;

				ASSERT(lObjectNum == arObjectInfo.GetCount());
				for (WORD nCount = 0; nCount < lObjectNum; nCount++)
				{
					ST_ICMSMETA_OBJECTINFO *pObjectInfo = arObjectInfo[nCount];
					pObjectInfo->Serialize(ar);
				}

				ar<<lEventNum;

				ASSERT(lEventNum == arEventInfo.GetCount());
				for (WORD nCount = 0; nCount < lEventNum; nCount++)
				{
					ST_ICMSMETA_EVENTINFO *pEventInfo = arEventInfo[nCount];
					pEventInfo->Serialize(ar);
				}
				ar<<lEndFlag;
			} 
			else
			{
				ReleaseResource();

				ar>>lBeginFlag;
				ar>>lChannel;
				ar>>llBeginTime;
				ar>>lObjectNum;
				//ASSERT(lObjectNum == arObjectInfo.GetCount());

				for (WORD nCount = 0; nCount < lObjectNum; nCount++)
				{
					ST_ICMSMETA_OBJECTINFO *pObjectInfo = new ST_ICMSMETA_OBJECTINFO;
					pObjectInfo->Serialize(ar);
					arObjectInfo.Add(pObjectInfo);
				}

				ar>>lEventNum;
				//ASSERT(lEventNum == arEventInfo.GetCount());

				for (WORD nCount = 0; nCount < lEventNum; nCount++)
				{
					ST_ICMSMETA_EVENTINFO *pEventInfo = new ST_ICMSMETA_EVENTINFO;
					pEventInfo->Serialize(ar);
					arEventInfo.Add(pEventInfo);
				}

				ar>>lEndFlag;
			}
		}
		catch (...)
		{
			AfxMessageBox(_T("ST_ICMSMETA_DATA::Serialize Exception!"));
		}
		return 1;
	}

	void tag_STMetaData::ReleaseResource()
	{
		ASSERT(lObjectNum == arObjectInfo.GetCount());
		for (WORD nCount = 0; nCount < lObjectNum; nCount++)
		{
			ST_ICMSMETA_OBJECTINFO *pObjectInfo = arObjectInfo[nCount];
			delete pObjectInfo;
			delete arObjectInfo[nCount];
		}
		arObjectInfo.RemoveAll();

		ASSERT(lEventNum == arEventInfo.GetCount());
		for (WORD nCount = 0; nCount < lEventNum; nCount++)
		{
			ST_ICMSMETA_EVENTINFO *pEventInfo = arEventInfo[nCount];
			delete pEventInfo;
			delete arEventInfo[nCount];
		}
		arEventInfo.RemoveAll();
	}
}ST_ICMSMETA_DATA;

#endif
