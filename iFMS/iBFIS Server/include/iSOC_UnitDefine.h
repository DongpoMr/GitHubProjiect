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
	TB_STARTTALK = 1, //�����Խ�
	TB_HANG,		  //�Ҷ�
	TB_ANSWER,		  //�����Խ�
	TB_VOLUMN,		  //��������
	TB_STATE,		  //״̬
	TB_CALLIN,		  //����
	TB_BEGINTALK,	  //��ʼ�Խ�
    BC_STARTBROADCAST//�����㲥			//����
};

enum TBState{
	ONLINE = 1,
	OFFLINE,
	NONE
};

enum RecordStatus
{
    BEGIN_WITHOUT_FILE = 1,     //¼������������������δд�ļ�
    BEGIN_WITH_fILE                    //¼������������������д���ļ�����
};

//��Ƶ��Ⱦģʽ����
#define GDI_RENDER_MOD 0x01 //GDI��Ⱦģʽ
#define DDRAW_RENDER_MOD 0x02 //DDraw��Ⱦģʽ
#define D3D_RENDER_MOD 0x03 //D3D��Ⱦģʽ

////����Ƶ����ID����

#define ISOC_DEFINE_AUDIO_UNKNOW								0x0001 //δ֪��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_G711U                                 0x0002 //G711U��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_G711A                                 0x0010 //G711A��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_AAC									0x0003 //AAC��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_G726									0x0004 //G726��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_MP3									0x0005 //MP3��Ƶ��ʽ
#define ISOC_DEFINE_HIK_G722                                    0x0006 //����˽��G722��Ƶ��ʽ
#define ISOC_DEFINE_HIK_G726                                    0x0016 //����˽��G726��Ƶ��ʽ
#define ISOC_DEFINE_DAHUA_G711A                                 0x0008 //��˽��G711A��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_PCM                                   0x000a //PCM��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_G722									0x000b //G722��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_G729									0x000c //G729��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_G723_1								0x000d //G723.1��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_ADPCM                                 0x000f //ADPCM��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_AMR_NB								0x0011 //AMR-NB��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_AMR_MB								0x0012 //AMR-MB��Ƶ��ʽ

#define ISOC_DEFINE_VIDEO_UNKNOW								0x0008 //δ֪��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_JPEG									0x0010 //JPEG��Ƶ��ʽ(Motion JPEG)
#define ISOC_DEFINE_HIK_JPEG									0x0011 //����˽��JPEG��Ƶ��ʽ
#define ISOC_DEFINE_DAHUA_JPEG									0x0012 //��˽��JPEG��Ƶ��ʽ
#define ISOC_DEFINE_YAAN_JPEG									0x0013 //�ǰ�˽��JPEG��Ƶ��ʽ
#define ISOC_DEFINE_HANBANG_JPEG								0x0014 //����˽��JPEG��Ƶ��ʽ
#define ISOC_DEFINE_HUAMAI_JPEG									0x0016 //����˽��JPEG��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_MJPEGB								0x0015 //MJPEG-B��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_MPEG4									0x0020 //MPEG4��Ƶ��ʽ
#define ISOC_DEFINE_HIK_MPEG4									0x0021 //����˽��MPEG4��Ƶ��ʽ
#define ISOC_DEFINE_DAHUA_MPEG4									0x0022 //��˽��MPEG4��Ƶ��ʽ
#define ISOC_DEFINE_YAAN_MPEG4									0x0023 //�ǰ�˽��MPEG4��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_MPEG2									0x0040 //MPEG2��Ƶ��ʽ
#define ISOC_DEFINE_HIK_MPEG2									0x0041 //����˽��MPEG2��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_H264									0x0080 //H264��Ƶ��ʽ
#define ISOC_DEFINE_HIK_H264									0x0081 //����˽��H264��Ƶ��ʽ
#define ISOC_DEFINE_DAHUA_H264									0x0082 //��˽��H264��Ƶ��ʽ
#define ISOC_DEFINE_YAAN_H264									0x0083 //�ǰ�˽��H264��Ƶ��ʽ
#define ISOC_DEFINE_HUAMAI_H264									0x0084 //����˽��H264��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_MSMPEG4V1								0x0090 //MSMPEG4-V1��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_MSMPEG4V2								0x0091 //MSMPEG4-V2��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_MSMPEG4V3								0x0092 //MSMPEG4-V3��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_WMV1									0x0093 //WMV1��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_WMV2									0x0094 //WMV2��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_MEGAEYES								0x0095//������Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_MEGAEYES								0x0096//������Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_VNMPGAEYES							0x0099//���ճ�����Զ��Ƶ��ʽ
#define ISOC_DEFINE_AUDIO_VNMPGAEYES							0x009a//���ճ�����Զ��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_H265      							0x009c 

#define ISOC_DEFINE_VIDEO_SVAC									0x009b //SVAC��׼��Ƶ��ʽ
#define ISOC_DEFINE_VIDEO_YUV									0x009d //������YUV���ݸ�ʽ

////////////////////Ȩ����ֵ����/////////////////////////////////
//ϵͳȨ����
#define ISOC_SYS_AUT_BASE				0x0601		//��������
#define ISOC_SYS_AUT_LOCALKINPLAN		0x0602		//����¼��ƻ�������
#define ISOC_SYS_AUT_GROUPSURVEY		0x0603		//������Ѳ

#define ISOC_SYS_AUT_LIVEVIDEO			0x0651		//��ƵԤ��
#define ISOC_SYS_AUT_STARTRECORD		0x0652		//��ͣ¼��
#define ISOC_SYS_AUT_ADDTAG				0x0653		//��ӱ�ǩ
#define ISOC_SYS_AUT_VODVIDEO			0x0654		//�����ط�
#define ISOC_SYS_AUT_LOGRETRIEVAL		0x0655		//��־��ѯ
#define ISOC_SYS_AUT_MATRIX				0x0656		//����ǽ
#define ISOC_SYS_AUT_EMAPBROWER			0x0657		//���ӵ�ͼ���
#define ISOC_SYS_AUT_VIDEOTRANSFER		0x0658		//��ƵǨ��
#define ISOC_SYS_AUT_EVIDENCINFOVIEW	0x0659		//ȡ֤���ϲ鿴(ȡ֤��Ƶ�㲥����Ŀ��Ϣ�鿴)
#define ISOC_SYS_AUT_EVIDENCINFODELETE	0x066A		//ȡ֤����ɾ��

//���豸Ȩ����
#define ISOC_SUBEQU_AUT_LIVEVIDEO		0x0701		//ʵʱ��Ƶ�࿴
#define ISOC_SUBEQU_AUT_VOD				0x0702		//VOD��ʷ�ط�
#define ISOC_SUBEQU_AUT_VIDEODOWNLOAD	0x0703		//��Ƶ���أ�������
#define ISOC_SUBEQU_AUT_VOICELISTEN		0x0704		//��������
#define ISOC_SUBEQU_AUT_VOICETALK		0x0705		//�����Խ�
#define ISOC_SUBEQU_AUT_DEFENCE			0x0751		//����/����
#define ISOC_SUBEQU_AUT_MAPVIDEOVIEW	0x0707		//��ͼ��Ƶ�࿴
#define ISOC_SUBEQU_AUT_PTZCONTROL		0x0741		//��̨����Ȩ��
#define	ISOC_SUBEQU_AUT_TRIGGERALARM	0x0752		//������ֹͣ����
#define ISOC_SUBEQU_AUT_CANCELALARM		0x0753		//ȡ������
#define	ISOC_SUBEQU_AUT_WATCHALARMVIDEO 0x0754		//�ۿ�����¼��
#define ISOC_SUBEQU_AUT_OUTPUTCONTROL	0x0771		//�������ر����
////////////////////////////////////////////////////

/******************************************************************************************************************************
*��������iSOC_StreamDataCallback
*��  �ܣ�����ǰ�������ص�����
*��  ����
		 dwCookie �û�Cookie�������ûص�����ָ���ʱ�����û����õ�
		 enDataType ����������ö��
		 pData �����ݣ���enDataTypeΪAUDIO_FRAMEʱ��pDataΪ��Ƶ���ݣ���enDataTypeΪVIDEO_FRAMEʱ��pDataΪ��Ƶ���ݣ�
			   ��enDataTypeΪAUDIO_INFOʱ��pDataΪST_AudioInfo�ṹ��ָ�룬������Ƶ�����Ϣ��
			   ��enDataTypeΪVIDEO_INFOʱ��pDataΪST_VideoInfo�ṹ��ָ�룬������Ƶ�����Ϣ
	     dataLen pData��ָ������ݳ���
		 pts ��Ӧ�����ݵ�ʱ�������λΪms��10-E6��
		 nFrameFlag ֡���ͱ�ʶ1:I֡,2:B֡,3:P֡
		 pPrivateData ˽������
		 nPriLen ˽�����ݳ��� 
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_StreamDataCallback
typedef ISOC_INT (__stdcall *iSOC_StreamDataCallback)(const ISOC_DWORDPTR dwCookie,StreamDataType enDataType,ISOC_BYTE* pData,ISOC_INT dataLen
													  ,ISOC_UINT64 pts,ISOC_INT nFrameFlag,ISOC_BYTE* pPrivateData,ISOC_INT nPriLen);
#endif

/******************************************************************************************************************************
*��������iSOC_MediaDataCallback
*��  �ܣ���������ݻص�
*��  ����
		 dwCookie �û�Cookie�������ûص�����ָ���ʱ�����û����õ�
		 enDataType �������������
		 pFrame �������Ƶ����
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_MediaDataCallback
typedef ISOC_INT (__stdcall *iSOC_MediaDataCallback)(const ISOC_DWORDPTR dwCookie,MediaDataType enDataType,ST_VideoFrame* pFrame);
#endif

/******************************************************************************************************************************
*��������iSOC_MediaDataCallbackEx
*��  �ܣ���������ݻص�
*��  ����
        dwCookie   �û�Cookie�������ûص�����ָ���ʱ�����û����õ�
        pts        ��ǰ֡ʱ���
        enDataType �������������
        pFrame     �������Ƶ����
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_MediaDataCallbackEx
typedef ISOC_INT(__stdcall *iSOC_MediaDataCallbackEx)(const ISOC_DWORDPTR dwCookie, ISOC_UINT64 pts, MediaDataType enDataType, ST_VideoFrame* pFrame);
#endif

/******************************************************************************************************************************
*��������iSOC_AudioSpectrumCallback
*��  �ܣ���Ƶ��ֵ�ص�
*��  ����
		lSession ���ûص�������Sessionֵ
		dwCookie �û�Cookie�������ûص�����ָ���ʱ�����û����õ�
		dbAudioSpecValue ��Ƶ�׵�ֵ����ΧΪ[-60,0]
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_AudioSpectrumCallback
typedef ISOC_INT(__stdcall *iSOC_AudioSpectrumCallback)(const ISOC_LONGPTR lSession,const ISOC_DWORDPTR dwCookie, ISOC_DOUBLE dbAudioSpecValue);
#endif

/******************************************************************************************************************************
*��������iSOC_DeviceInfoChangedCallback
*��  �ܣ��豸��Ϣ����ص�
*��  ����
		 dwCookie �û�Cookie�������ûص�����ָ���ʱ�����û����õ�
		 stDeviceInfo ������豸��Ϣ
		 dwReserved ��������
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_DeviceInfoChangedCallback
typedef ISOC_INT (__stdcall *iSOC_DeviceInfoChangedCallback)(const ISOC_DWORDPTR dwCookie,ST_DeviceItem stDeviceInfo,ISOC_DWORDPTR dwReserved);
#endif

/******************************************************************************************************************************
*��������iSOC_PermissionChangedCallback
*��  �ܣ��豸Ȩ����Ϣ����ص�
*��  ����
		 dwCookie �û�Cookie�������ûص�����ָ���ʱ�����û����õ�
		 nPermissionType ��ʶΪϵͳȨ�޻����豸Ȩ�ޣ�Ϊ1ʱΪϵͳȨ�ޣ�Ϊ2ʱΪ�豸Ȩ��
		 nChengedType ������͡�0:���,1:�޸�,2:ɾ��
		 stDeviceInfo ������豸��Ϣ����nPermissionType��ʶΪϵͳȨ��ʱ���˲�������
		 dwReserved ��������
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_PermissionChangedCallback
typedef ISOC_INT (__stdcall *iSOC_PermissionChangedCallback)(const ISOC_DWORDPTR dwCookie,const ISOC_INT nPermissionType,const ISOC_INT nChengedType,ST_DeviceItem stDeviceInfo,ISOC_DWORDPTR dwReserved);
#endif

/******************************************************************************************************************************
*��������iSOC_OperatorStateCallback
*��  �ܣ�����״̬�ص�
*��  ����
		 enState ����״̬ö��
		 nOperatorType �������ͣ���OperatorType�е�һ��ֵ
		 strDes ��������
		 dwCookie �û����õ�Cookie
		 dwResevered ��������
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_OperatorStateCallback
typedef ISOC_INT (__stdcall *iSOC_OperatorStateCallback)(const OperatorState enState,const ISOC_INT nOperatorType,const ISOC_STR strDes,const ISOC_DWORDPTR dwCookie,ISOC_DWORDPTR dwResevered);
#endif

/******************************************************************************************************************************
*��������iSOC_OnGotOnlineClientInfoCallback
*��  �ܣ�����״̬�ص�
*��  ����
		 dwCookie �û�Cookie
		 strIPAddr �ͻ���IP��ַ
		 uPort �ͻ��˶˿ںţ���ʱû�ã�
		 strUserName ��¼�û���
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_OnGotOnlineClientInfoCallback
typedef ISOC_INT (__stdcall *iSOC_OnGotOnlineClientInfoCallback)(ISOC_DWORDPTR dwCookie,const ISOC_STR strIPAddr,const ISOC_UINT uPort,const ISOC_STR strUserName);
#endif

/******************************************************************************************************************************
*��������iSOC_VodFileInfoCallback
*��  �ܣ���ȡVOD�ļ���Ϣ�ص�
*��  ����
		 vodFileInfo VOD�ļ���Ϣ�ṹ��	
		 dwCookie �û����õ�Cookie
		 strQueryGUID �û���ѯʱ�����GUID
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_VodFileInfoCallback
typedef ISOC_INT (__stdcall *iSOC_VodFileInfoCallback)(const ST_VodFileInfo vodFileInfo,const ISOC_DWORDPTR dwCookie,const ISOC_STR strQueryGUID);
#endif

/******************************************************************************************************************************
*��������iSOC_GrabFileInfoCallback
*��  �ܣ���ȡץ֡�ļ���Ϣ�ص�
*��  ����
		 grabFileInfo ץ֡�ļ���Ϣ�ṹ��
		 dwCookie �û����õ�Cookie
		 strQueryGUID �û���ѯʱ�����GUID
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_GrabFileInfoCallback
typedef ISOC_INT (__stdcall *iSOC_GrabFileInfoCallback)(const ST_GrabFileInfo grabFileInfo,const ISOC_DWORDPTR dwCookie,const ISOC_STR strQueryGUID);
#endif

/******************************************************************************************************************************
*��������iSOC_VodFileTagInfoCallback
*��  �ܣ���ȡ��ǩ��Ϣ�ص�
*��  ����
		 tagInfo  ��ǩ��Ϣ�ṹ��
		 dwCookie �û����õ�Cookie
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_VodFileTagInfoCallback
typedef ISOC_INT (__stdcall *iSOC_VodFileTagInfoCallback)(const ST_TagInfo tagInfo,const ISOC_DWORDPTR dwCookie);
#endif

/******************************************************************************************************************************
*��������iSOC_WhenOnGotAlarmEventCallback
*��  �ܣ������¼��ص�
*��  ����
		 dwCookie �û����õ�Cookie
		 dwEventType �¼�����
		 pXmlContext �¼���xml����
		 nXmlLen �¼����ݳ���
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_WhenOnGotAlarmEventCallback
typedef int (__stdcall *iSOC_WhenOnGotAlarmEventCallback)(ISOC_DWORDPTR dwCookie,ISOC_DWORD dwEventType,const ISOC_STR pXmlContext,ISOC_INT nXmlLen);
#endif

/******************************************************************************************************************************
*��������iSOC_OnGotDataCallback
*��  �ܣ����յ���������ʱ�ص�
*��  ����
		 dwUserCookie �û�Cookie
		 fromAddr �������ݵķ�������ַ
		 pData ��������
		 dataLen ���ݳ���
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_OnGotDataCallback
typedef int (__stdcall *iSOC_OnGotDataCallback)(ISOC_DWORDPTR dwUserCookie,ISOC_UINT64 fromAddr,ISOC_BYTE* pData,ISOC_INT dataLen);
#endif

/******************************************************************************************************************************
*��������iSOC_OnAffairOverTimeCallback
*��  �ܣ��������ʱ�Ļص�
*��  ����
		 dwUserCookie �û�Cookie
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_OnAffairOverTimeCallback
typedef int (__stdcall *iSOC_OnAffairOverTimeCallback)(ISOC_DWORDPTR dwUserCookie);
#endif

/******************************************************************************************************************************
*��������iSOC_PresetPosInfoCallback
*��  �ܣ�Ԥ�õ���Ϣ���»ص�
*��  ����
		 nFlage ������ʶ��0��ʾ��ӣ�1��ʾ�޸ģ�2��ʾɾ��
		 dwCookie �û�Cookie
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_PresetPosInfoCallback
typedef ISOC_INT (__stdcall *iSOC_PresetPosInfoCallback)(ISOC_INT nFlage,const LPST_PRESETPOSINFO lpPresetPosInfo,ISOC_DWORDPTR dwCookie);
#endif

/******************************************************************************************************************************
*��������iSOC_TourInfoCallback
*��  �ܣ�Ѳ����Ϣ���»ص�
*��  ����
		nFlags������ʶ��0��ʾ��ӣ�1��ʾ�޸ģ�2��ʾɾ��
		 dwCookie �û�Cookie
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_TourInfoCallback
typedef ISOC_INT (__stdcall *iSOC_TourInfoCallback)(ISOC_INT nFlage,const LPST_TOURINFO lpTourInfo,ISOC_DWORDPTR dwCookie);
#endif


/******************************************************************************************************************************
*��������iSOC_DeleteFileNotifyCallback
*��  �ܣ�ɾ���ļ���Ϣ�ص�
*��  ����
		 nFileID	��ʾ�ļ�id
		 nDeleteStatusɾ���ļ�״̬ 0��ʾ��ʱ��3��ʾ��ɣ�4��ʾʧ��
		 dwUserCookie �û�Cookie

*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_DeleteFileNotifyCallback
typedef ISOC_INT (__stdcall *iSOC_DeleteFileNotifyCallback)(ISOC_ID nFileID,ISOC_INT nDeleteStatus,ISOC_DWORDPTR dwUserCookie);
#endif

/******************************************************************************************************************************
*��������iSOC_OnRecvServerTimeCallback
*��  �ܣ�������ʱ����»ص�
*��  ����
		 lMCSession	MC�Ự��ʶ
		 dwUserCookie	�û�Cookie
		 stServerTime	������ʱ��

*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_OnRecvServerTimeCallback
typedef ISOC_INT (__stdcall *iSOC_OnRecvServerTimeCallback)(IN const ISOC_LONGPTR lMCSession,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_SYSTEMTIME stServerTime);
#endif


/******************************************************************************************************************************
*��������iSOC_FileLockInfoCallback
*��  �ܣ��ļ�����ѯ�ص�
*��  ����
		 dwCookie �û�Cookie
		 nInfoType ��Ϣ���ͣ�����ȡ����ֵ����Ϊ1ʱpInfoΪ����ϢST_FileLockInfoָ�룬��Ϊ2ʱΪ���ڵ��ļ���ϢST_FileLockItemָ��,Ϊ3��ʱ���ʾһ������������Ϣ���
		 nInfoLen ��Ϣָ������Ӧ����Ϣ����
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_FileLockInfoCallback
typedef ISOC_INT (__stdcall *iSOC_FileLockInfoCallback)(ISOC_DWORDPTR dwCookie,ISOC_INT nInfoType,ISOC_BYTE* pInfo,ISOC_INT nInfoLen);
#endif

/******************************************************************************************************************************
*��������iSOC_FileMigrateInfoCallback
*��  �ܣ�Ǩ�������ѯ�ص�
*��  ����
		 dwCookie   �û�Cookie
		 nInfoType ��Ϣ���ͣ�����ȡ����ֵ����Ϊ1ʱpInfoΪ����ϢST_MigrateInfoָ�룬��Ϊ2ʱΪ���ڵ��ļ���ϢST_MigrateItemָ��,��Ϊ1ʱ
				    strCatalogInfo��nCatalogLen��Ч,��Ϊ3ʱ��һ��һ������Ǩ��������Ϣ�ص����
		 pInfo	   ��Ϣ�����Ϣ
		 nInfoLen       ��Ϣָ������Ӧ����Ϣ����
		 strCatalogInfo ��Ŀ��Ϣ
		 nCatalogLen	��Ŀ��Ϣ����
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_FileMigrateInfoCallback
typedef ISOC_INT (__stdcall *iSOC_FileMigrateInfoCallback)(ISOC_DWORDPTR dwCookie,ISOC_INT nInfoType,ISOC_BYTE* pInfo,ISOC_INT nInfoLen,const ISOC_STR strCatalogInfo,ISOC_INT nCatalogLen);
#endif

/******************************************************************************************************************************
*��������iSOC_OnGotTransparentDataInfoCallback
*��  �ܣ�͸�����ݻص�
*��  ����
		 dwCookie �û�Cookie
		 strContent ͸����������
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_OnGotTransparentDataInfoCallback
typedef ISOC_INT (__stdcall *iSOC_OnGotTransparentDataInfoCallback)(ISOC_DWORDPTR dwCookie,ISOC_STR strKey,ISOC_INT nDataArea,const ISOC_STR strContent);
#endif


/******************************************************************************************************************************
*��������iSOC_OnGotUnconfirmedAlarmInfoCallback
*��  �ܣ�δ�������ص�
*��  ����
		 dwCookie �û�Cookie
		 strContent ͸����������
		 nTransparentDataID ͸������ID
*����ֵ��
*��  ע��
******************************************************************************************************************************/
#ifndef iSOC_OnGotUnconfirmedAlarmInfoCallback
typedef ISOC_INT (__stdcall *iSOC_OnGotUnconfirmedAlarmInfoCallback)(ISOC_DWORDPTR dwCookie,ST_UntreadedAlarmInfo AlarmInfo);
#endif

/****************************
*������	:iSOC_OnGotSuperviseCallback
*����   :����¼��ص�
*����	:
		enState		    :����״̬ö��
		enType			:��������ö��
		pstSuperviseInfo:����¼���Ϣ
		dwCookie 	    :�û�����
*����ֵ
*��ע
*****************************/
#ifndef iSOC_SuperviseCallback
typedef ISOC_INT (__stdcall *iSOC_SuperviseCallback)(const OperatorState enState,const OperatorType enType, const ST_SuperviseItem* pstSuperviseInfo, const ISOC_DWORDPTR dwCookie);
#endif 

/****************************
*������	:iSOC_TalkbackCallback
*����   :�Խ��¼��ص�
*����	:
		enType		  :��������ö�� 
		enOState	  :����״̬ö��
		enState	      :�豸״̬
		pDevData 	  :�豸��Ϣ
		dwCookie 	  :�û�����
*����ֵ
*��ע
*****************************/
#ifndef iSOC_TalkbackCallback
typedef ISOC_INT (__stdcall *iSOC_TalkbackCallback)(const TBOperatorType enType, const OperatorState enOState,
					const TBState enState,	//���������Ͳ�ΪSTATEʱ����ֵĬ��ΪNONE							
					const ST_DevicePluginItem* pDevData, 	//�����ն˷���Խ�ʱ��ͨ���ýṹ����ȷ�Ϸ����ն�
					const ISOC_DWORDPTR dwCookie);
#endif

/****************************
*������	:iSOC_OnGotGPSDataCallback
*����   :��ȡGPS���ݻص�
*����	:
		lIcmsId		  :�����豸ID 
		strIcmsSign	  :���豸���ڵ����ʶ
		pData	      :GPS������Ϣ
		nDataLen 	  :������Ϣ����
		pPrivateData  :˽������
		nPrivateDataLen:˽�����ݳ���
		dwCookie 	  :�û�����
*����ֵ
*��ע
*****************************/
#ifndef iSOC_OnGotGPSDataCallback
typedef ISOC_INT (__stdcall *iSOC_OnGotGPSDataCallback)(ISOC_ID lIcmsId, ISOC_CHAR strIcmsSign[64], \
	const ISOC_BYTE* pData, ISOC_INT nDataLen, \
	const ISOC_BYTE* pPrivateData, ISOC_INT nPrivateDataLen, \
	ISOC_DWORDPTR dwCookie);
#endif

/******************************************************************************************************************************
*iSOC_GrabStatusCallback
*��  �ܣ�ץ֡״̬�ص�
*��  ����
[IN]		status				����״̬
[IN]		grabTime			ץ֡ʱ��
[IN]		dwCookie			�û�����
[IN]		dwReserved			������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע��
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