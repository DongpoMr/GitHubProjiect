#pragma once

//����궨��͹���ö�ٶ��干200�����Ѿ�ȫ������ICMS_UniqueDefine.h�����ʹ�ù��õ�ͷ�ļ�
//�Ժ󣬶���������ICMS_UniqueDefine.h��ά����������У�����Ŀ�޸��������֪ͨ������
//�������Ƿ���Ҫ����ICMS_UniqueDefine.h�ļ���
 //ͬʱ�����Ŀ����ڿ�����Ķ��嶼�ŵ�ICMS_UniqueDefine.h����ȥ��
//��ʹ��ICMS_UniqueDefine.h������Ҫ�ڸ��ԵĹ������ٴζ����ظ������ݡ�
#include "ICMS_UniqueDefine.h"
#include <string>
using namespace std;

#pragma pack(push,1)
struct ST_ICMS_CMD_HEADER
{
	WORD				wSrcType;					//Դ������
	WORD				wCmdMainType;      //����������� 
	DWORD				dwCmdSubType;     //�����������
	DWORD				dwSeqID;               //�������
	WORD				wExtendType;           //��չ��������
	DWORD				dwExndSize;          //��չ���ݴ�С
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
	//WORD		cmsAppType;		//ϵͳ���� monitor=ICMS_CLIENT_MONITOR matrix_client=ICMS_CLIENT_MATRIX matrix_server=ICMS_SERVER_MATRIX
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

//��־����
//typedef enum {SYSTEM_LOG,WARNING_LOG,OPER_LOG}LOG_KIND;

struct ST_ICMSALARM_INFO
{
	int         nAlarmEventID;
	//�����¼�����1 ��Ƶ��ʧ 2 �ƶ���� 3 �̻𱨾� 4 �ܽ籣�� 5 ����Ϊ�쳣 6 ��ͷ�ڵ�
	int         nAlarmType;
	//�����¼��ȼ�1 ���� 2 ���� 3 �ؼ� 4 ���� 5 ����
	int         nAlarmDegree;
	//�����豸����1 ͨ�� 2 ̽ͷ 3 ϵͳ
	int         nAlarmDevType;
	//�豸������ICMSϵͳ
	TCHAR		cstrICMSSign[128];
	//�����豸ID
	int         nAlarmDevID;
	//�Ƿ񵯳�������ͼ
	BOOL		bAlarmOpenMap;
	//�Ƿ�򿪱�������
	BOOL		bAlarmOpenSound;
	//�����ļ���
	TCHAR       cAlarmSoundFile[200];
	//��������״̬1 δ���� 2 ���ڴ��� 3 �Ѵ���
	int         nAlarmDealStatus;
	//���������û�
	TCHAR		cDealUser[64];
	//��������ʱ��
	TCHAR       cStartTime[64];
	//��������ʱ��
	TCHAR       cDealTime[64];
	//�����������
	TCHAR		cDescription[1000];
	//�Ƿ�Ϊ����ɾ��
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


	BOOL operator <(const ST_ICMSALARM_INFO &y )//���ȼ��Ƚ�
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

///////���ó�Ա���������ú�
#define SET_AFFAIR_CALLBACK_FUNC_EX(cachObj,theObj,GotDataEx,AffairOverTimeEx) \
	{cachObj.m_pCachedAffairSkin = theObj; \
	 cachObj.m_pOnGotDataEx = static_cast<ST_AFFAIR_CALLBACK::OnGotDataEx>(GotDataEx); \
	 cachObj.m_pOnAffairOverTimeEx = static_cast<ST_AFFAIR_CALLBACK::OnAffairOverTimeEx>(AffairOverTimeEx);}

struct ST_AFFAIR_CALLBACK
{
public:
	typedef int (*OnGotData)(DWORD_PTR cookie,UINT64 fromAddr,BYTE* pData,int dataLen); //���ڵ���ȫ�ֻ�̬������������ǰ�ģ�
	typedef int (*OnAffairOverTime)(DWORD_PTR cookie); //���ڵ���ȫ�ֻ�̬����(������ǰ��)
	typedef int (ICachedAffairSkin::*OnGotDataEx)(DWORD_PTR cookie,UINT64 fromAddr,BYTE* pData,int dataLen); //���ڵ��ó�Ա����(�Ƽ�ʹ��) --�ο���
	typedef int (ICachedAffairSkin::*OnAffairOverTimeEx)(DWORD_PTR cookie); //���ڵ��ó�Ա����(�Ƽ�ʹ��) --�ο���

	ST_AFFAIR_CALLBACK (DWORD_PTR cookie
						,OnGotData pOnGotData = NULL//�յ����ݵĻص�����
						,OnAffairOverTime pOnAffairOverTime = NULL//����ʱ�ص�����
						,int overTime = 4000//��ʱʱ��,����Ϊ��λ
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
