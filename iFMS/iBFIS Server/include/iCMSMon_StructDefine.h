#pragma once

//信令宏定义和公用枚举定义共200多条已经全部加入ICMS_UniqueDefine.h，大家使用公用的头文件
//以后，对于信令在ICMS_UniqueDefine.h的维护请代丹进行，各项目修改信令后请通知代丹，
//代丹看是否需要更新ICMS_UniqueDefine.h文件。
 //同时请各项目组对于跨软件的定义都放到ICMS_UniqueDefine.h里面去，
//都使用ICMS_UniqueDefine.h，不需要在各自的工程中再次定义重复的内容。
#include "ICMS_UniqueDefine.h"
#include <string>
using namespace std;

#pragma pack(push,1)
struct ST_ICMS_CMD_HEADER
{
	WORD				wSrcType;					//源的类型
	WORD				wCmdMainType;      //信令的主类型 
	DWORD				dwCmdSubType;     //信令的子类型
	DWORD				dwSeqID;               //信令序号
	WORD				wExtendType;           //扩展数据类型
	DWORD				dwExndSize;          //扩展数据大小
};

struct ST_ICMSLOGIN_PARAM
{
	char		userName[20];
	char		userPass[20];
	char		cmsServerName[20];
	long		cmsServerIp;
	short		cmsServerPort;
	long		cmsSlaveServerIp;
	long        cmsStandbySysIp;
	//WORD		cmsAppType;		//系统类型 monitor=ICMS_CLIENT_MONITOR matrix_client=ICMS_CLIENT_MATRIX matrix_server=ICMS_SERVER_MATRIX
};


struct ST_PRECASE_INFO 
{
	int					nPrecaseNum;
	TCHAR				cPrcaseName[20];
	CString				cFirstRelatedMan;
	int					nFirstRelatedTel;
	CString				cSecondRelatedMan;
	int					nSecondRelatedTel;
	CString				cThirdRelatedMan;
	int					nThirdRelatedTel;
	TCHAR				cPrecaseDes[1000];
	ST_PRECASE_INFO()
	{
		nPrecaseNum			 = 0;
		nFirstRelatedTel	 = 0;
		nSecondRelatedTel	 = 0;
		nThirdRelatedTel	 = 0;
		cFirstRelatedMan	 = _T("");
		cSecondRelatedMan	 = _T("");
		cThirdRelatedMan	 = _T("");
		memset(cPrcaseName,0,20);
		memset(cPrecaseDes,0,1000);
	}
};

//日志类型
//typedef enum {SYSTEM_LOG,WARNING_LOG,OPER_LOG}LOG_KIND;

struct ST_ICMSALARM_INFO
{
	int         nAlarmEventID;
	//报警事件类型1 视频丢失 2 移动检测 3 烟火报警 4 周界保护 5 人行为异常 6 镜头遮挡
	int         nAlarmType;
	//报警事件等级1 紧急 2 报警 3 关键 4 错误 5 警告
	int         nAlarmDegree;
	//报警设备类型1 通道 2 探头 3 系统
	int         nAlarmDevType;
	//设备所属的ICMS系统
	TCHAR		cstrICMSSign[128];
	//报警设备ID
	int         nAlarmDevID;
	//是否弹出关联地图
	BOOL		bAlarmOpenMap;
	//是否打开报警声音
	BOOL		bAlarmOpenSound;
	//声音文件名
	TCHAR       cAlarmSoundFile[200];
	//报警处理状态1 未处理 2 正在处理 3 已处理
	int         nAlarmDealStatus;
	//处理报警的用户
	TCHAR		cDealUser[64];
	//报警发生时间
	TCHAR       cStartTime[64];
	//报警处理时间
	TCHAR       cDealTime[64];
	//处理情况描述
	TCHAR		cDescription[1000];
	//是否为本地删除
	BOOL		bDeleteLocal;
	ST_ICMSALARM_INFO()
	{
		nAlarmEventID	 = 0;
		nAlarmType		 = 0;
		nAlarmDegree	 = 0;
		nAlarmDevType	 = 0;
		nAlarmDevID		 = 0;
		nAlarmDealStatus = 0;
		bAlarmOpenMap	 = FALSE;
		bAlarmOpenSound	 = FALSE;
		bDeleteLocal     = FALSE;
		memset(cstrICMSSign,0,128);

		memset(cDealUser,0,64);
		memset(cAlarmSoundFile,0,200);
		memset(cStartTime,0,64);
		memset(cDealTime, 0,64);
		memset(cDescription,0,1000);
	}

	ST_ICMSALARM_INFO(const ST_ICMSALARM_INFO &stAlarmInfo)
	{
		this->nAlarmEventID		= stAlarmInfo.nAlarmEventID;
		this->nAlarmType		= stAlarmInfo.nAlarmType;
		this->nAlarmDegree		= stAlarmInfo.nAlarmDegree;
		this->nAlarmDevType		= stAlarmInfo.nAlarmDevType;
		this->nAlarmDevID		= stAlarmInfo.nAlarmDevID;
		this->nAlarmDealStatus	= stAlarmInfo.nAlarmDealStatus;
		this->bAlarmOpenMap		= stAlarmInfo.bAlarmOpenMap;
		this->bAlarmOpenSound	= stAlarmInfo.bAlarmOpenSound;
		this->bDeleteLocal		= stAlarmInfo.bDeleteLocal;

		memset(cstrICMSSign,0,128);

		memset(cDealUser,0,64);
		memset(cAlarmSoundFile,0,200);
		memset(cStartTime,0,64);
		memset(cDealTime, 0,64);
		memset(cDescription,0,1000);

		strcpy(this->cstrICMSSign, stAlarmInfo.cstrICMSSign);


		strcpy(this->cDealUser,stAlarmInfo.cDealUser);
		strcpy(this->cAlarmSoundFile,stAlarmInfo.cAlarmSoundFile);
		strcpy(this->cStartTime,stAlarmInfo.cStartTime);
		strcpy(this->cDealTime,stAlarmInfo.cDealTime);
		strcpy(this->cDescription,stAlarmInfo.cDescription);
	};

	const ST_ICMSALARM_INFO& operator=(const ST_ICMSALARM_INFO& rhs)
	{

		this->nAlarmEventID		= rhs.nAlarmEventID;
		this->nAlarmType		= rhs.nAlarmType;
		this->nAlarmDegree		= rhs.nAlarmDegree;
		this->nAlarmDevType		= rhs.nAlarmDevType;
		this->nAlarmDevID		= rhs.nAlarmDevID;
		this->nAlarmDealStatus	= rhs.nAlarmDealStatus;
		this->bAlarmOpenMap		= rhs.bAlarmOpenMap;
		this->bAlarmOpenSound	= rhs.bAlarmOpenSound;
		this->bDeleteLocal		= rhs.bDeleteLocal;



		memset(cstrICMSSign,0,128);

		memset(cDealUser,0,64);
		memset(cAlarmSoundFile,0,200);
		memset(cStartTime,0,64);
		memset(cDealTime, 0,64);
		memset(cDescription,0,1000);

		lstrcpy(cstrICMSSign, rhs.cstrICMSSign);

		lstrcpy(this->cDealUser,rhs.cDealUser);
		lstrcpy(this->cAlarmSoundFile,rhs.cAlarmSoundFile);
		lstrcpy(this->cStartTime,rhs.cStartTime);
		lstrcpy(this->cDealTime,rhs.cDealTime);
		lstrcpy(this->cDescription,rhs.cDescription);

		return *this;


	}


	BOOL operator <(const ST_ICMSALARM_INFO &y )//优先级比较
	{
		if(this->nAlarmDealStatus > y.nAlarmDealStatus)
		{
			return true;
		}
		else if(this->nAlarmDealStatus == y.nAlarmDealStatus)
		{
			if(this->nAlarmDegree > y.nAlarmDegree)
			{
				return true;
			}
			else if(this->nAlarmDegree == y.nAlarmDegree )
			{
				if( CString(this->cStartTime) < CString(y.cStartTime))
				{
					return true;
				}
				else
				{
					false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return false;
	}
};

interface ICachedAffairSkin
{
	//virtual ~ICachedAffairSkin(){};
};

///////调用成员函数的设置宏
#define SET_AFFAIR_CALLBACK_FUNC_EX(cachObj,theObj,GotDataEx,AffairOverTimeEx) \
	{cachObj.m_pCachedAffairSkin = theObj; \
	 cachObj.m_pOnGotDataEx = static_cast<ST_AFFAIR_CALLBACK::OnGotDataEx>(GotDataEx); \
	 cachObj.m_pOnAffairOverTimeEx = static_cast<ST_AFFAIR_CALLBACK::OnAffairOverTimeEx>(AffairOverTimeEx);}

struct ST_AFFAIR_CALLBACK
{
public:
	typedef int (*OnGotData)(DWORD_PTR cookie,UINT64 fromAddr,BYTE* pData,int dataLen); //用于调用全局或静态函数（兼容以前的）
	typedef int (*OnAffairOverTime)(DWORD_PTR cookie); //用于调用全局或静态函数(兼容以前的)
	typedef int (ICachedAffairSkin::*OnGotDataEx)(DWORD_PTR cookie,UINT64 fromAddr,BYTE* pData,int dataLen); //用于调用成员函数(推荐使用) --廖俊杰
	typedef int (ICachedAffairSkin::*OnAffairOverTimeEx)(DWORD_PTR cookie); //用于调用成员函数(推荐使用) --廖俊杰

	ST_AFFAIR_CALLBACK (DWORD_PTR cookie
						,OnGotData pOnGotData = NULL//收到数据的回调函数
						,OnAffairOverTime pOnAffairOverTime = NULL//事务超时回调函数
						,int overTime = 4000//超时时间,毫秒为单位
						,ICachedAffairSkin* pAffairSkin = NULL
						,OnGotDataEx pOnGotDataEx = NULL
						,OnAffairOverTimeEx pAffairOverTimeEx = NULL)
		:m_dwUserCookie(cookie),m_pOnGotData(pOnGotData),m_pOnAffairOverTime(pOnAffairOverTime)
		,m_nOverTime(overTime),m_pRecvData(NULL),m_pRecvSize(0),m_pOnGotDataEx(pOnGotDataEx),m_pOnAffairOverTimeEx(pAffairOverTimeEx)
		,m_pCachedAffairSkin(pAffairSkin)
	{};
	~ST_AFFAIR_CALLBACK()
	{
		if (NULL != m_pRecvData)
		{
			VirtualFree(m_pRecvData,0,MEM_RELEASE);
			m_pRecvData	= 0;
		}
			m_pRecvSize = 0;
	}

	void SetCallbackFuncEx(ICachedAffairSkin* pSkin,OnGotDataEx pOnGotDataEx,OnAffairOverTimeEx pOnAffairOverTimeEx)
	{
		m_pCachedAffairSkin = pSkin;
		m_pOnGotDataEx = pOnGotDataEx;
		m_pOnAffairOverTimeEx = pOnAffairOverTimeEx;
	}

	DWORD_PTR				m_dwUserCookie;
	OnGotData				m_pOnGotData;	
	OnAffairOverTime		m_pOnAffairOverTime;
	OnGotDataEx				m_pOnGotDataEx;
	OnAffairOverTimeEx		m_pOnAffairOverTimeEx;
	void*					m_pCachedAffairSkin;
	int						m_nOverTime;	
	BYTE*					m_pRecvData;
	int						m_pRecvSize;
};

typedef struct  
{
	DWORD SubEquipmentID;
	TCHAR szPlayType[32];
	TCHAR szICMSSign[128];

} stPlayInfo;


typedef struct ST_STATUSINFO
{
	int nFileId;
	int nTaskId;
	DWORD nICMSSubEquipmentId;
	string ICMSSign;
	string TransSvrSign;
	string TransSvrIP;
	string strDesc;
	string strStartTime;
	string strEndTime;
	long   lPort;
	int    nStatus;
	float  nDownLoadRate;
	int	   nPercent;

	ST_STATUSINFO()
	{
		nFileId = 0;
		nTaskId = 0;
		nICMSSubEquipmentId = 0;
		ICMSSign = _T("");
		TransSvrSign = _T("");
		TransSvrIP = _T("");
		strDesc = _T("");
		strStartTime = _T("");
		strEndTime = _T("");
		lPort = 0;
		nStatus = 0;
		nDownLoadRate = 0;
		nPercent = 0;
	}

	ST_STATUSINFO& operator = (ST_STATUSINFO& stInfo)
	{
		nFileId = stInfo.nFileId;
		nTaskId = stInfo.nTaskId;
		nICMSSubEquipmentId = stInfo.nICMSSubEquipmentId;
		ICMSSign = stInfo.ICMSSign;
		TransSvrSign = stInfo.TransSvrSign;
		TransSvrIP = stInfo.TransSvrIP;
		strDesc   = stInfo.strDesc;
		strStartTime = stInfo.strStartTime;
		strEndTime  = stInfo.strEndTime;
		lPort  = stInfo.lPort;
		nStatus = stInfo.nStatus;
		nDownLoadRate = stInfo.nDownLoadRate;
		nPercent = stInfo.nPercent;

		return *this;
	}

}stStatusInfo;

typedef void (*DRAWONVIDEO)(HDC hDC,RECT rtDraw);
#pragma pack(pop)
