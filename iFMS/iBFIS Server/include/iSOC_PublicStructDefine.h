#pragma once
#ifndef _ISOC_PUBLICSTRUCTDEFINE_H_
#define _ISOC_PUBLICSTRUCTDEFINE_H_

#define _CRT_SECURE_NO_DEPRECAT
#pragma warning(disable:4996)

#include "iSOC_Datatype_Define.h"

#pragma pack(push,1) 

#define  UNITDEVCODELEN   35           //����ȡ�����ݿ�
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

	ISOC_ID	    lDeviceID;                      //���豸ID(ȫ��Ψһ)
	ISOC_ID	    lParentId;                      //�����ڵ�id
	ISOC_ID	    lIcmsId;                        //�Լ�������id(��ȫ��Ψһ)
	ISOC_UINT	deviceKind;                     //�豸����,��֯�ڵ�,�豸,̽ͷ,���
	ISOC_BOOL	beOnLine;                       //�Ƿ�����
	ISOC_DWORD	workStatus;	                    //�����Ƿ�����,1Ϊ����,����ֵΪ������
	ISOC_BOOL	beHasPtzCtrl;                   //�Ƿ������̨
	ISOC_INT	nDevType;                       //��ϸ���ͣ�ǹ��....��
	ISOC_CHAR   strIcmsSign[64];                //������������
	ISOC_CHAR	strDeviceName[200];             //�豸����
	ISOC_CHAR   strUnitDeviceCode[UNITDEVCODELEN];//ͳһ�豸����
	ISOC_CHAR   strDeviceIP[16];                //�豸IP
    ISOC_WORD   uDevicePort;                    //�豸�˿�
	ISOC_ID		lBeforeParentId;                //�ı�ǰ�ĸ��ڵ�ID
	ISOC_ID		lAfterParentId;                 //�ı��ĸ��ڵ�IDֵ
	ISOC_INT	nChangeType;                    //�ı�����Ĭ��Ϊ-1�� 0:������1���޸� 2��ɾ��
	ISOC_CHAR	strSystemType[128];             // ϵͳ����
	ISOC_BOOL	bIsDefence;                     //����״̬�����������豸���ʾ���״̬��
    ISOC_INT    nChannelID;                     //ͨ���ţ����豸�����豸�µ�ID��
    ISOC_BOOL   bWithLight;                     //�Ƿ�ƹ�
    ISOC_BOOL   bWithDemist;                    //�Ƿ����
    ISOC_BOOL   bWithRainBrush;                 //�Ƿ���ˢ
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
	ISOC_INT	nMasterFileID; //�ϼ��ļ�����ID���������nFileID��˵��û�й����ļ�
	ISOC_INT	nFilesType;//�ļ�����:0x0b01�ֶ�¼�� 0x0b02����¼��  0x0b03�ƻ�¼��  0x0B04��ʷ����  0x0B05����ץ֡  0x0B06�ֶ�ץ֡  0x0b07Ǩ��¼�� 
	ISOC_SYSTEMTIME	stStartTime;
	ISOC_SYSTEMTIME	stEndTime;
	ISOC_CHAR	strFilePath[260];
	ISOC_CHAR	strTrigger[200];
	ISOC_CHAR	strDevICMSSign[64];	// �ļ�����Ӧ���豸��ICMSSign
	ISOC_CHAR   strUserGUID[64];
	ISOC_INT	nUserID;
	ISOC_CHAR	strSrcICMSSign[64]; // ԴICMSSign�ļ����ڷֿص�ICMSSign
	ISOC_CHAR	strDesICMSSign[64]; // Ŀ��ICMSSign�����ѯ����ķֿص�ICMSSign�����ͻ�������¼�ķ�������ICMSSign
	ISOC_DWORDPTR	dwReserved1;
	ISOC_DWORDPTR	dwReserved2;
	ISOC_UINT64		fileSize;	//�ļ���С
	ISOC_CHAR		strExtendInfo[1024];//��ʱ�������κźͳ����

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
	ISOC_INT nFileType;//�ļ�����:0x0b01�ֶ�¼�� 0x0b02����¼��  0x0b03�ƻ�¼��  0x0B04��ʷ����  0x0B05����ץ֡  0x0B06�ֶ�ץ֡  0x0b07Ǩ��¼�� 
	ISOC_CHAR strFileTime[20];
	ISOC_DWORDPTR dwReserved1;
	ISOC_DWORDPTR dwReserved2;
	ISOC_DWORDPTR dwReserved3;

	ISOC_CHAR strFileName[MAX_PATH];
	ISOC_CHAR strFilePath[MAX_PATH];
	ISOC_CHAR strDevICMSSign[64];	//�ļ������豸icmssign
	ISOC_CHAR strUserGUID[64];
	ISOC_CHAR strSrcICMSSign[64]; // ԴICMSSign�ļ����ڷֿص�ICMSSign
	ISOC_CHAR strDesICMSSign[64]; // Ŀ��ICMSSign�����ѯ����ķֿص�ICMSSign�����ͻ�������¼�ķ�������ICMSSign
 
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
	ISOC_INT		nPanPos;		//ˮƽ����λ��
	ISOC_INT		nTitlePos;		//��ֱ����λ��
	ISOC_INT		nZoomPos;		//Zoomλ��
	ISOC_INT		nFocusPos;		//����λ��
	ISOC_DWORDPTR	dwReserved1;	//��������1
	ISOC_DWORDPTR	dwReserved2;	//��������2
};

typedef struct ST_PresetPosInfo
{
	ST_PresetPosInfo()
		:nPresetNum(0),nXAngel(0),nYAngel(0),nChgAngel(0),nICMSSignID(0),dwReserved2(0),dwReserved1(0)
	{
		memset((ISOC_STR)strPresetName,0,sizeof(strPresetName));
		memset((ISOC_STR)strICMSSign,0,sizeof(strICMSSign));
	}
	ISOC_INT			nPresetNum;				// Ԥ�õ����(��0��98)
	ISOC_CHAR			strPresetName[128];	// Ԥ�õ�����
	ISOC_INT			nXAngel;				// ˮƽ�Ƕȣ���λ �ȣ�
	ISOC_INT			nYAngel;				// ��ֱ�Ƕȣ���λ �ȣ�
	ISOC_INT			nChgAngel;				// �佹����λ �ȣ�

	ISOC_CHAR			strICMSSign[64];		
	ISOC_ID				nICMSSignID;

	ISOC_DWORDPTR	dwReserved1;        //1.5.8�汾��û�ã���2.0�汾�б�ʾ��Ӧ���ݿ�����ID
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
	ISOC_CHAR				strCruiseName[128];	// Ѳ������
	ISOC_INT				nTourNum;			// Ѳ�����
	ISOC_INT				nDelayTime;		// Ԥ�õ�ͣ��ʱ�� 1-2400��
	ISOC_INT				nMoveSpeed;		// Ԥ�õ��˶��ٶ� 1-24
	ISOC_INT				bBeLoop;			// �Ƿ�ѭ��
	ISOC_INT				nLoopDelayTime;	// ѭ�����ʱ��
	ISOC_INT				nPresetPosCnt;
	ISOC_INT				nPresetPosOrderNo[MAX_DEVICEPRESETPOS_SIZE]; // ���16��Ԥ�õ�
	ISOC_INT				nPresetPosNum[MAX_DEVICEPRESETPOS_SIZE];	//Ԥ�ýṹ�������nPresetNum���ϣ����ڱ�ʾһ��Ԥ�õ�

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
	ISOC_INT	nTaskItemID;  //Ǩ�����񱾵�ID,���ֶ�ֻ����1.0�Ľӿ�����Ч��2.0�ӿ��в�ʹ�ô��ֶ�
	ISOC_ID		iVodFileID; //Ǩ�Ƶ�VOD�ļ�ID,���ֶ�ֻ����1.0�Ľӿ�����Ч��2.0�ӿ��в�ʹ�ô��ֶ�
	ISOC_ID		iTaskID; //Ǩ������ID
	ISOC_ID		iDeviceID; // �豸ID
	ISOC_INT	nState;  //Ǩ��״̬��1Ϊ�Ŷӣ�2Ϊ���ڵ��ȣ�3Ϊ��ɣ�4Ϊ��ͣ��5Ϊȡ��,6Ϊֹͣ��7Ϊ�쳣��8Ϊ�쳣����
	ISOC_INT	nProgress;  //Ǩ�ƽ���
	ISOC_INT	nRate; // Ǩ�����ʣ���λ��B/s
	ISOC_SYSTEMTIME stMigStart;//�ļ�Ǩ�ƵĿ�ʼʱ��,���ֶ�ֻ����1.0�Ľӿ�����Ч��2.0�ӿ��в�ʹ�ô��ֶ�
	ISOC_SYSTEMTIME stMigEnd;	//�ļ�Ǩ�ƵĽ���ʱ��,���ֶ�ֻ����1.0�Ľӿ�����Ч��2.0�ӿ��в�ʹ�ô��ֶ�
	ISOC_CHAR	chUserGUID[64]; //�û�GUID
	ISOC_CHAR	chMigrateUser[50]; //����Ǩ��������û���ֻ����2.0��
	ISOC_CHAR	chMigrateDesc[MIGRATE_DESC_MAX_LEN]; //Ǩ��������ֻ����2.0��
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
	ST_VodFileInfo stVodFileInfo; //��Ƶ�ļ���Ϣ
	ISOC_SYSTEMTIME stBeginTime; //�ļ��д��Ŀ�ʼʱ��
	ISOC_SYSTEMTIME stEndTime; //�ļ��д��Ľ���ʱ��

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
	ST_CenterInfo centerInfo; //����������Ϣ
	ISOC_SIZE_T	  szLimitSpace;//�޶��Ŀռ��С����MBΪ��λ
	ISOC_SIZE_T	  szUsedSpace;//ʹ�õĿռ��С����MBΪ��λ
	ISOC_DWORDPTR dwReserved; //�����ֶ�
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
	nFileArea��ʾ�ļ����ڵط�����ȥ�Ķ���ѯ����ֵ
	����������ֵ�е�һ����
	nFileArea =0ǰ�˺����Ĳ�ѯ  =1���ģ����������
	���ģ� =2ǰ�˲�ѯ =3���ݲ�ѯ =4Ǩ�Ʋ�ѯ =5���ģ���
	������¼�����ģ� ��Ĭ��ֵΪ0
	*************************************************/
	ISOC_INT nFileArea;

	/*************************************************
	�ļ����ͣ���ֵ����������ֵ���е�һ�����������
	��Ϸ�ʽΪ���򣨣������ķ�ʽ��
	nVodFileType =0x1�����ļ�   =0x2�ֶ��ļ�
	             =0x4�ƻ��ļ�
	*************************************************/
	ISOC_INT nVodFileType;

	/*************************************************
	��nVodFileType�а��������ļ�ʱ��nAlarmFileType��ʾ
	�����ļ������͡���ֵ����������ֵ���е�һ��������
	��ϣ���Ϸ�ʽΪ���򣨣������ķ�ʽ��
	nAlarmFileType =0x01���б�������		=0x02�ƶ�����
				   =0x04��������			=0x08̽ͷ����
				   =0x10���ܱ���			=0x20�ֶ�����
				   =0x40��������			=0x80�Ž�����
				   =0x100��������
	*************************************************/
	ISOC_INT nAlarmFileType;

	/*************************************************
	��nVodFileType�а��������ļ�ʱ��nAlarmDealStatus
	��ʾ����״̬���͡���ֵ����������ֵ���е�һ������
	������ϣ���Ϸ�ʽΪ���򣨣������ķ�ʽ��
	nAlarmDealStatus =0x1�Ѵ��������ļ�
					 =0x2δ���������ļ�
	*************************************************/
	ISOC_INT nAlarmDealStatus;

	/*************************************************
	strTagΪ��ǩ��ֵ�����䳤�Ȳ�Ϊ0ʱ�����Ҫʹ�ñ�ǩ
	��ѯ�����䳤��Ϊ0ʱ��ʹ�ñ�ǩ��
	*************************************************/
	ISOC_CHAR strTag[1024];


	ISOC_CHAR strCardUser[48];

	ISOC_CHAR strCardID[48];
	/*************************************************
	strStartTime��ʾ��ѯʱ��εĿ�ʼʱ�䣬��ȷ���뼶
	�ַ�������������"2011-04-29 10:06:00"
	*************************************************/
	ISOC_CHAR strStartTime[20];

	/*************************************************
	strEndTime��ʾ��ѯʱ��εĽ���ʱ�䣬��ȷ���뼶
	�ַ�������������"2011-04-29 10:06:00"
	*************************************************/
	ISOC_CHAR strEndTime[20];

	/*************************************************
	migrateCenterInfo��ʾǨ�Ʒ������������ĵ���Ϣ����
	nFileAreaΪ4��ʱ��ʹ�ô��ֶΣ����ֶ�ֻ��isoc2.0
	�ķ�������Ч��1.5.8�ķ��������Բ�ʹ�ô��ֶ�
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
	ISOC_INT nBright; //����
	ISOC_INT nContrast; //�Աȶ�
	ISOC_INT nSaturation; //���Ͷ�
	ISOC_INT nHue; //ɫ��
	ISOC_INT nAudioLevel; //����
	ISOC_DWORDPTR dwReserved1; //��������1
	ISOC_DWORDPTR dwReserved2; //��������2

	ST_CameraParameter() : nBright(0),nContrast(0),nSaturation(0)
		,nHue(0),nAudioLevel(0),dwReserved1(0),dwReserved2(0)
	{

	};
};

struct ST_MapNode	//��ʾ��ͼ�Ĳ㼶��ϵ
{
	ISOC_INT	nMapListID;				// Int��PK��	��ͼĿ¼��ID��
	ISOC_INT	nMSuperiorID;			// Int	�ϼ�ID
	ISOC_INT	nMLevel;	            // Int	����
	ISOC_CHAR	strPedigree[1024*4];	// Nvarchar(4000)	����
	ISOC_CHAR	strCoding[1024*4];		// Nvarchar(4000)	����
	ISOC_CHAR	strMName[128];			// Nvarchar(50)	�ڵ�����
	ISOC_CHAR	strICMSSign[64];
	ISOC_INT	nICMSMapListID;			


	ISOC_DWORDPTR dwReserved1; //��������1
	ISOC_DWORDPTR dwReserved2; //��������2

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

struct ST_MapLeaf // ���ӵ�ͼ��
{
	ISOC_INT	nMapLeafID; 				// nMapLeafInfoID//Int��PK��	��ͼ��ID��
	ISOC_INT	nMapListID;					// Int��FK��	��ͼĿ¼ID
	ISOC_INT	nMapSize;
	ISOC_INT	nICMSMapLeafID;				//ICMSϵͳ�еĵ�ͼ��ID
	ISOC_INT	nICMSMapListID;
	ISOC_CHAR	strMName[128];				// Nvarchar(50)	��ͼ����
	ISOC_CHAR	strMapVersion[128];			// Nvarchar(50)	��ͼ�汾��
	ISOC_CHAR	strMapDateTime[64];			// Datetime()	��ͼ����ʱ��
	ISOC_CHAR	strLeafInfoICMSSign[64];	//��ͼ���ICMSSign
	
	ISOC_DWORDPTR dwReserved1; //��������1
	ISOC_DWORDPTR dwReserved2; //��������2

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

struct ST_MapLeafMapAss//��ʾ����ͼ�Ĺ�����ϵ
{
	ISOC_INT	nMapAssInfoID;	    // Int��PK��	��ͼ������ID��
	ISOC_INT	nMapLeafID;			// nMapLeafInfoID//Int��FK��	��ͼID
	ISOC_INT	nAMapLeafInfoID;	// Int��FK��	��������Ĺ�����ͼID
	ISOC_RECT	rectHotArea;
	ISOC_CHAR	strMapICMSSign[64];
	ISOC_INT	nICMSMapLeafInfoID;
	ISOC_DWORDPTR dwReserved1; //��������1
	ISOC_DWORDPTR dwReserved2; //��������2

	ST_MapLeafMapAss():nMapAssInfoID(0),nMapLeafID(0),nAMapLeafInfoID(0),dwReserved1(0),dwReserved2(0),nICMSMapLeafInfoID(0)
	{
		ZeroMemory(&rectHotArea,sizeof(rectHotArea));
		ZeroMemory(strMapICMSSign, sizeof(strMapICMSSign));
	}
};

struct ST_MapLeafEquAss//��ʾ��ͼ���豸�Ĺ�����ϵ
{
	ISOC_INT	nEquMapAssInfoID;		// Int��PK��	��֯�ṹ���ͼ������ID��
	ISOC_INT	nMapLeafInfoID;			// Int��FK��	��ͼID
	ISOC_RECT	rectHotArea;
	ISOC_INT	nSubEquipmentID;	    // Int��FK��	���豸ID��
	ISOC_INT	nAngel;					// ��ת�Ƕ�
	ISOC_INT	nEquType;				// ��xmlЭ���ֶΣ��μ�
	ISOC_BOOL   bSelected;				// ��Э���ֶ�
	ISOC_INT	nStatus;				// ��Э���ֶ� 0��ʾ������1��ʾ¼��
	ISOC_CHAR	sEquName[128];			// ��Э���ֶΣ��豸����
	
	ISOC_INT	nICMSSubEquipID;
	ISOC_INT	nICMSMapLeafInfoID;
	ISOC_CHAR	strSubEquipICMSSign[64];
	ISOC_CHAR	strMapLeafInfoICMSSign[64];

	ISOC_DWORDPTR dwReserved1; //��������1
	ISOC_DWORDPTR dwReserved2; //��������2

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

struct ST_MapLeafOrgAss//��ʾ��ͼ����֯�ṹ�Ĺ�����ϵ
{
	ISOC_INT nOrgMapAssInfoID;		// Int��PK��	�豸�ڵ����ͼ������ID��
	ISOC_INT nOrganizeListID;		// Int��FK��	��֯�ṹ�б�ID��
	ISOC_INT nMapLeafInfoID;	    // Int��FK��	��ͼID

	ISOC_DWORDPTR dwReserved1; //��������1
	ISOC_DWORDPTR dwReserved2; //��������2

	ST_MapLeafOrgAss():nOrgMapAssInfoID(0),nOrganizeListID(0),nMapLeafInfoID(0),dwReserved1(0),dwReserved2(0)
	{
	}
};

struct ST_TagInfo	// ��ǩ��Ϣ
{
	ISOC_SYSTEMTIME stTagTime;		// ��ǩʱ��
	ISOC_SYSTEMTIME	stUserAddTime;	// �û���ӱ�ǩ��ʱ��
	ISOC_CHAR		strTagTitle[1024];	// ����
	ISOC_INT		nTitleLen;		// ���ⳤ��
	ISOC_CHAR		strTagContent[2048];	// ����
	ISOC_INT		nContentLen;	// ���ݳ���
	ISOC_DWORDPTR	dwReserved;		// ������

	ISOC_DWORDPTR dwReserved1; //��������1
	ISOC_DWORDPTR dwReserved2; //��������2

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
	ISOC_CHAR strUserICMSSign[64]; //�û�����ϵͳ��ICMSSign
	ISOC_CHAR strServerICMSSign[64]; //�û�����¼�ķ�������ICMSSign
	ISOC_DWORDPTR dwReserved; //��������
	ISOC_DWORDPTR dwReserved1; //��������1
	ISOC_DWORDPTR dwReserved2; //��������2

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
	ISOC_BYTE *pData[ISOC_NUM_DATA_POINTERS]; //����RGB���ݣ�pData[0]Ϊ��ӦRGB���ݵ��׵�ַ��������Ч������YUV���ݣ�pData[0]ΪY�������׵�ַ��pData[1]ΪV�������׵�ַ��pData[2]Ϊ
	ISOC_INT nLineSize[ISOC_NUM_DATA_POINTERS]; //�����汣��һ�£���Ӧ�����������һ�е����ݴ�С
	ISOC_INT nWidth; //��ǰ֡�Ŀ�
	ISOC_INT nHeight;  //��ǰ֡�ĸ�

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

	EN_FramePixType pixFormatType; //��Ƶ�������ظ�ʽ
	ISOC_DWORDPTR dwReserved1; //��������1
	ISOC_DWORDPTR dwReserved2; //��������2

	ST_VideoFrame()
	{
		ZeroMemory(this,sizeof(ST_VideoFrame));
	}
};

struct ST_AudioFrame
{
	ISOC_BYTE* pData; //��Ƶ����
	ISOC_INT nDataLen; //���ݳ���
	ISOC_DWORDPTR dwReserved;//��������

	ST_AudioFrame()
	{
		ZeroMemory(this,sizeof(ST_AudioFrame));
	}
};

struct ST_MatrixServerInfo
{
	ISOC_ID		iICMSServerID;	 //��Ӧ�ֿصĵ���ǽ������ID
	ISOC_CHAR	strICMSSign[64]; //����ǽ�����������ֿص�ICMSSign
	ISOC_CHAR	strServerIP[20]; //����ǽ��������IP��ַ
	ISOC_UINT	uServerPort;	 //����ǽ�������Ķ˿�
	ISOC_DWORDPTR dwReserved1;	 //��������1
	ISOC_DWORDPTR dwReserved2;	 //��������2
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
//�����Ϣ
struct ST_MatrixOutputInfo
{
	ISOC_ID		iMatrixOutputID;//���ID
	ISOC_INT	nOutputIndex;//���Index
	ISOC_CHAR	strOutputName[50];//�����
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
	ST_MatrixOutputInfo matrixOutputInfos[20]; //�˴��涨һ���Կ���������Ϊ20����Ŀǰ�ø����Ѿ�������Ҫ�����������ָ�����������Կ��ٸı��ֵ
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
//ͨ����Ϣ
struct ST_ChannelInfo
{
	ISOC_INT	nChannelType;//ͨ������ 1��ͨ��  2�����ӵ�ͼ
	ISOC_INT	nChannelID;//ͨ��ID
	ISOC_CHAR strChannelICMSSign[50];//ͨ��ICMSSign
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
	ISOC_INT nMarginLeft;//�����������߾�
	ISOC_INT nMarginTop; //����������ϱ߾�
	ISOC_INT nMarginRight; //����������ұ߾�
	ISOC_INT nMarginBottom; //����������±߾�
	void Init()
	{
		memset(this, 0, sizeof(ST_OverlayMarginInfo));
	}
};

struct ST_OverlayFontInfo
{
	ISOC_CHAR chOverlayText[MAX_PATH];//������Ϣ����
	ISOC_INT nAlignWay;//���뷽ʽ
	ISOC_INT nFontSize;//���ֽ���
	ISOC_CHAR chFontName[40];//��������
	ISOC_DWORD	dwFontColor;
	ISOC_DWORD dwFontWeight;
	ISOC_RECT overlayRect;//Ҫ���ӵ���������
	ST_OverlayMarginInfo marginInfo;

	void Init()
	{
		nAlignWay = ALIGN_LEFT | ALIGN_TOP;
		nFontSize = 24;
		dwFontColor = RGB(255, 0, 0);
		dwFontWeight = FONTW_DONTCARE;
		ZeroMemory(chOverlayText, sizeof(chOverlayText));
		sprintf_s(chFontName, _T("΢���ź�"));
		ZeroMemory(&overlayRect, sizeof(ISOC_RECT));
		marginInfo.Init();
	}
};

struct ST_OverlayLineInfo
{
	ISOC_POINT *pPointLists;  //�������
	ISOC_INT nPointsCount;  //��ĸ���
	ISOC_FLOAT fWidth; //�߿�
	ISOC_DWORD dwLineColor;//�ߵ���ɫ
	ISOC_DWORD dwPattern; //����ģʽ��1Ϊ���ߣ�0Ϊ͸��
	ISOC_FLOAT fPatternScale; //���������еļ��������Խ�󣬼��Խ��Ĭ��Ϊ1.0f

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
	ISOC_CHAR chPicPath[MAX_PATH];//����ͼƬ��·��
	ISOC_RECT overlayRect;//Ҫ����ͼƬ������
};

struct ST_OverlayInfo
{
	enum EN_OverlayType
	{
		Text = 1,Picture = 2,Line = 3
	};
	ISOC_INT nOverlayID;//������Ϣid
	ISOC_INT nOverlayType;//������Ϣ���ͣ�1���֣�2ΪͼƬ��3Ϊ���ߣ�
	union 
	{
		ST_OverlayFontInfo fontInfo;
		ST_OverlayLineInfo lineInfo;
		ST_OverlayPicInfo picInfo;
	}overlayInfo;
	ISOC_DWORDPTR dwReserved1;//�����ֶ�1
	ISOC_DWORDPTR dwReserved2;//�����ֶ�2

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
		case Text: //����
		{
			memcpy(&this->overlayInfo.fontInfo, &info.overlayInfo.fontInfo, sizeof(ST_OverlayFontInfo));
			break;
		}
		case Picture: //ͼƬ
		{
			memcpy(&this->overlayInfo.picInfo, &info.overlayInfo.picInfo, sizeof(ST_OverlayPicInfo));
			break;
		}
		case Line: //����
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
	ISOC_CHAR strPoliceStation[64];//�ɳ���
	ISOC_CHAR strMigeraterName[64];//Ǩ����
	ISOC_CHAR strCaseID[64];//��������
	ISOC_CHAR strCaseCode[64];//��������
	ISOC_CHAR strCaseRelator[64];//���������
	ISOC_CHAR strOwnerDepart[64];//��ڵ�λ
	ISOC_CHAR strDealDepart[64];//�а쵥λ
	ISOC_CHAR strCaseType[64];//��������
	ISOC_CHAR strDescribe[1024];//����
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
	ISOC_SYSTEMTIME	stStartTime;    //��ʼʱ��ָ���ļ��Ĳ��ֿ�ʼ����
	ISOC_SYSTEMTIME	stEndTime;      //����ʱ��ָ�������ļ��Ĳ���
	ISOC_SYSTEMTIME	stUnLockDate;   //�������������
	ISOC_INT		nLockUserID;
	ISOC_CHAR		strLockUserName[50]; //�����û����û���
	ISOC_INT		nLockID;        //��ID
	ISOC_CHAR		strLockDes[200];		//��������
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

//��������Ϣ
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

//////////////////////////���������////////////////////////////////
struct ST_SuperviseUserInfo
{
	ISOC_INT nUserID;
	ISOC_CHAR strUserName[64];
	ISOC_INT nType;
	ISOC_CHAR strDescription[2048];
	ISOC_CHAR strUserICMSSign[64]; //�û�����ϵͳ��ICMSSign
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
	ISOC_INT  nSuperviseID;			   //����¼�ID
	ISOC_INT  nSuperviseType;		   //�¼�״̬ 0.δ���� 1.�Ѵ���
	ISOC_CHAR strDescription[1024];    //���������� 
	ST_SuperviseUserInfo* pstUserList; //�û��û��б�
	ISOC_INT  nUserInfoCount;		   //�û��б���
	ISOC_INT  nDevID;				   //�����豸ID
	ISOC_SYSTEMTIME stStartTime;       //�¼���ʼʱ��
	ISOC_SYSTEMTIME stEndTime;         //�¼�����ʱ��
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

////////////////////////////////////�������//////////////////////////
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

struct ST_DevicePluginItem	//SDK������ýṹ��
{
	ISOC_ID nID;
	ISOC_CHAR strDeviceName[200];
	ISOC_CHAR strDeviceIP[16];
	ISOC_WORD sPort;
	ISOC_CHAR strUserName[200];
	ISOC_CHAR strUserPwd[200];
	ISOC_INT  nDevType;  //�豸������
	ISOC_INT  nDevSubType;//�豸������
	ISOC_CHAR strModelType[200];	//�豸�ͺ�����

	//������Ϣ
	ISOC_CHAR strSeriaProtocol[200];	    //����Э��,����RS232
	ISOC_INT  nBaudrate;				    //������
	ISOC_INT  nDatabits;				    //����λ
	ISOC_INT  nStopBits;				    //ֹͣλ
	ISOC_INT  nParityType;			        //��żУ��
	ISOC_CHAR strComSeq[200];			    //���õ�COM�����

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
        ISOC_CHAR Name[50];                     //���������û���
        ST_P_AlarmRelate()
        {
            ZeroMemory(this,sizeof(ST_P_AlarmRelate));
        }
    };                              
    struct ST_P_PlanRelate
    {
        ISOC_CHAR strName[50];                  //�ƻ������˵����ƣ�DB��
        ISOC_CHAR strPPhone[30];                //�ƻ������˵ĵ绰���루DB��
        ST_P_PlanRelate()
        {
            ZeroMemory(this,sizeof(ST_P_PlanRelate));
        }
    }; 
    struct ST_P_DevRelate
    {
        ISOC_INT nDevLinkID;                    //�����豸�������ID
        ISOC_CHAR strDevLinkICMSSign[64];       //�����豸���ʶ��DB��
        ST_P_DevRelate()
        {
            ZeroMemory(this,sizeof(ST_P_DevRelate));
        }
    }; 

	ISOC_INT            nAlarmEventID;          //�����¼�ID
	ISOC_INT            nAlarmType;             //�������� 
	ISOC_CHAR           strContent[300];		//������������
	ISOC_CHAR			strAlarmDes[300];		//�����������ݣ�DB�� 
	ISOC_INT            nALevel;                //�����ȼ�
	ISOC_UINT           nDevType;               //�豸���ͣ�ͨ��.....��
	ISOC_CHAR           strDevICMSSign[64];     //�豸�����ʶ��DB��
	ISOC_INT            nDevICMSSignID;         //�豸�������ID
	ISOC_BOOL           bWithMap;               //�����Ƿ�򿪵�ͼ
	ISOC_BOOL           bWithSound;             //�����Ƿ񲥷���Ƶ
	ISOC_CHAR           strSoundFile[256];      //��Ƶ�ļ���
	ISOC_UINT           nCurTranState;          //����״̬
	ISOC_SYSTEMTIME     AlarmTime;              //��������ʱ��                      

    //����iSOC���������������ȡֵ(eg:iSOC_GetFirstDataListItem)
    ISOC_DWORDPTR       ptrAlarmRelate;         //(ST_P_AlarmRelate)���������û������� 
    ISOC_DWORDPTR       ptrPlanRelate;          //(ST_P_PlanRelate)�ƻ�������Ϣ����
    ISOC_DWORDPTR       ptrDevRelate;           //(ST_P_DevRelate)�����豸��Ϣ����

    ISOC_INT            nPlanID;                //�ƻ�ID
    ISOC_CHAR           strPlanName[125];       //�ƻ����ƣ�DB��
    ISOC_CHAR           strPlanContent[300];    //�ƻ�����
    ISOC_DWORDPTR       dwReserved1;            //Ԥ��

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
    ISOC_INT      nOverlayID;//������Ϣid
    ISOC_CHAR     chOverlayInfo[MAX_PATH];//������Ϣ���ݣ���Ϊ����ʱ������ΪҪ���ӵ�����
    ISOC_CHAR     chFontPath[MAX_PATH]; //���ӵ�����·��
    ISOC_INT      nFontSize;//���ֽ���
    ISOC_DWORD	  dwFontColor;
    ISOC_INT      nHAlign;	//ˮƽ���뷽ʽ 1,����� 2,���� 3,�Ҷ���
    ISOC_INT      nHOffset;
    ISOC_INT      nVAlign;	//��ֱ���뷽ʽ 1,�϶��� 2,���� 3,�¶���
    ISOC_INT      nVOffset;
    ISOC_DWORDPTR dwReserved1;//�����ֶ�1
    ISOC_DWORDPTR dwReserved2;//�����ֶ�2
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
	ISOC_FLOAT fQCompress; //��0.0 �� 1.0
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
	ISOC_INT		nCodecId; //��Ƶ����ID
	ISOC_INT		nPicWidth; //��Ƶ��
	ISOC_INT		nPicHeight; //��Ƶ��
	ISOC_FLOAT		fFrameRate; //֡��
	ISOC_INT		nRate; //����
	ISOC_INT		nExtendKind; //��չ�������ͣ�ĿǰΪ0
	ISOC_INT		nExtendLen; //��չ���ݳ��ȣ���Ӧ˽�����ݳ���
	ISOC_BYTE*		pExtendData; //��չ���ݣ���Ӧ˽������
	ISOC_DWORDPTR   dwReserved1; //��������1
	ISOC_DWORDPTR   dwReserved2; //��������2
};

struct ST_AudioInitParam 
{
	ST_AudioInitParam():nCodecId(0),fBitRate(.0),nChannel(0),nSamplesPerSec(0),nBlockAlign(0),bDecode(ISOC_TRUE)
		,nExtendKind(0),nExtendLen(0),pExtendData(0){}
	ISOC_INT		nCodecId; //��Ƶ����ID
	ISOC_INT		nChannel; //ͨ����
	ISOC_INT		nSamplesPerSec; //������
	ISOC_FLOAT		fBitRate; //����
	ISOC_INT		nBlockAlign; //������ֽ���
	ISOC_BOOL		bDecode; //�Ƿ���룬����ΪISOC_TRUE������ΪISOC_FALSE
	ISOC_INT		nExtendKind;//��չ�������ͣ�ĿǰΪ0
	ISOC_INT		nExtendLen;//��չ���ݳ��ȣ���Ӧ˽�����ݳ���
	ISOC_BYTE*		pExtendData;//��չ���ݣ���Ӧ˽������
};

struct ST_VideoParam
{
	ISOC_INT nHeight; //��Ƶ��
	ISOC_INT nWidth; //��Ƶ��
	ISOC_UINT64 uPTS; //ʱ���
	ISOC_DWORDPTR dwReserved1; //�����ֶ�1
	ISOC_DWORDPTR dwReserved2; //�����ֶ�2
};

struct ST_FileParam
{
	ISOC_CHAR     chFilePath[MAX_PATH];		//�ļ�·��
	ISOC_UINT64	  uStartTs;					//��ʼʱ��
	ISOC_UINT64	  uEndTs;					//����ʱ��
	ISOC_DWORDPTR dwReserved1;				//�����ֶ�1
	ISOC_DWORDPTR dwReserved2;				//�����ֶ�2
};

#pragma pack(pop)
#endif
