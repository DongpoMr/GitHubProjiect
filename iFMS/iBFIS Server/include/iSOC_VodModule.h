#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////VODģ��ӿڵĶ���/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_GetVodFileList
*��  �ܣ���ȡVOD�ļ�
*��  ����
		 [IN]		lMCSession		MC�Ự��ʶ
		 [IN]		strDeviceList	��ѯ���豸ID�б����£�1,2,3,4,5... ...
		 [IN]		stQueryFilter	��ѯ����
		 [IN]		pCallBack		��ѯ����ص�����ָ��
		 [IN]		dwUserCookie	�û�COOKIE
		 [IN]		strQueryGuid	�û���ѯGUID��ÿ�β�ѯ�û�����ָ����ͬ�Ĳ�ѯGUID
		 [IN]		dwReserved		��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodFileList( IN const ISOC_LONGPTR lMCSession,IN const ISOC_STR strDeviceList,IN ST_VodQueryFilter stQueryFilter,IN iSOC_VodFileInfoCallback pCallBack,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_STR strQueryGuid = NULL,IN ISOC_DWORDPTR dwReserved = 0 );

/******************************************************************************************************************************
*��������iSOC_GetVodFileTagInfoList
*��  �ܣ�����VOD�ļ���Ϣ��ѯ��Ӧ�ļ��ı�ǩ��Ϣ
*��  ����
		 [IN]		lMCSession		MC�Ự��ʶ
		 [IN]		vodFileInfo 	VOD�ļ���Ϣ
		 [IN]		pCallBack		��ѯ����ص�����ָ��
		 [IN]		dwUserCookie	�û�COOKIE
		 [IN]		dwReserved		��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodFileTagInfoList(IN const ISOC_LONGPTR lMCSession,IN const ST_VodFileInfo vodFileInfo,IN const iSOC_VodFileTagInfoCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwResreved = 0);

/******************************************************************************************************************************
*��������iSOC_CreateVodSession
*��  �ܣ�����VOD�Ự
*��  ����
		 [IN OUT]	pVodSession		VOD�Ự��ʶ
		 [IN]		pCallback		״̬�ص�����ָ��
		 [IN]		dwUserCookie	�û�Cookie
		 [IN]		dwReserved		������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע���ڲ�ʹ��ЩVOD�Ự��Ҫʹ��iSOC_ReleaseVodSession����Ự���٣���������ڴ�й©
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateVodSession(IN OUT ISOC_LONGPTR* pVodSession,IN iSOC_OperatorStateCallback pCallback = NULL,IN ISOC_DWORDPTR dwUserCookie = 0,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ReleaseVodSession
*��  �ܣ�����VOD�Ự
*��  ����
		 [IN]		lVodSession		VOD�Ự��ʶ
		 [IN]		dwReserved		������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseVodSession(IN const ISOC_LONGPTR lVodSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_StartVodStream
*��  �ܣ�����VOD��
*��  ����
		 [IN]		lVodSession		VOD�Ự��ʶ
		 [IN]		lMCSession		MC�Ự��ʶ
		 [IN]		info			VOD�ļ���Ϣָ��
		 [IN]		hRenderWnd		��Ⱦ���ھ��
		 [IN]		bIsLocalFile	�Ƿ�Ϊ�����ļ�
		 [IN]		dwReserved		������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartVodStream(IN const ISOC_LONGPTR lVodSession,IN const ISOC_LONGPTR lMCSession,IN const ST_VodFileInfo info,IN ISOC_HWND hRenderWnd,IN ISOC_BOOL bIsLocalFile,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_StopVodStream
*��  �ܣ�ֹͣVOD��
*��  ����
		 [IN]	pVodSession		VOD�Ự��ʶ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע��ֹͣVOD��Ƶ������ڴ漰��Դ���ᱻ�ͷ���Ҫ����iSOC_ReleaseVodSession�ͷ������Դ
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopVodStream(IN const ISOC_LONGPTR lVodSession);

/******************************************************************************************************************************
*��������iSOC_SetVodStreamDataCallback
*��  �ܣ�����VOD������ǰ���ݻص�
*��  ����
		 [IN]	pVodSession		VOD�Ự��ʶ
		 [IN]	pCallback		���ݻص�����ָ��
		 [IN]	dwUserCookie	�û�COOKIE
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodStreamDataCallback(IN const ISOC_LONGPTR lVodSession,IN const iSOC_StreamDataCallback pCallback,IN const ISOC_DWORDPTR dwUserCookie);

/******************************************************************************************************************************
*��������iSOC_SetVodMediaDataCallback
*��  �ܣ�����VOD����������ݻص�
*��  ����
		 [IN]	pVodSession		VOD�Ự��ʶ
		 [IN]	enMediaDataType	ý����������	
		 [IN]	pCallback		���ݻص�����ָ��
		 [IN]	dwUserCookie	�û�COOKIE
		 *����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodMediaDataCallback(IN const ISOC_LONGPTR lVodSession,IN const MediaDataType enMediaDataType,IN const iSOC_MediaDataCallback pCallback,IN const ISOC_DWORDPTR dwUserCookie);

/******************************************************************************************************************************
*��������iSOC_SetVodMediaDataCallbackEx
*��  �ܣ�����VOD����������ݻص�
*��  ����
[IN]	pVodSession		VOD�Ự��ʶ
[IN]	enMediaDataType	ý����������
[IN]	pCallback		���ݻص�����ָ��
[IN]	dwUserCookie	�û�COOKIE
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����iSOC_SetVodMediaDataCallback��������˻ص�ʱ���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodMediaDataCallbackEx(IN const ISOC_LONGPTR lVodSession, IN const MediaDataType enMediaDataType, IN const iSOC_MediaDataCallbackEx pCallback, IN const ISOC_DWORDPTR dwUserCookie);

/******************************************************************************************************************************
*��������iSOC_SetVodRenderRect
*��  �ܣ�����VOD��Ⱦ��Ƶ���������Ⱦ���ڵ�����
*��  ����
		 [IN]	pVodSession		VOD�Ự��ʶ
		 [IN]	pRecVideo		��Ⱦ����Ƶ������������ã�����Ⱦ����ͼ��
		 [IN]	pRecWnd			��Ⱦ�Ĵ���������������ã�����Ⱦ��������
		 [IN]	dwReserved		������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodRenderRect(IN const ISOC_LONGPTR lVodSession,IN ISOC_RECT* pRecVideo,IN ISOC_RECT*pRecWnd = NULL,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_GrabVodFrame2Local
*��  �ܣ�VODץ֡
*��  ����
		 [IN]	pVodSession		VOD�Ự��ʶ
		 [IN]	pPicturePath	�����ץ֡ͼƬ��·��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GrabVodFrame2Local(IN const ISOC_LONGPTR lVodSession,IN const ISOC_STR pPicturePath);

/******************************************************************************************************************************
*��������iSOC_GetVodVideoInfo
*��  �ܣ���ȡVOD��Ƶ��Ϣ
*��  ����
		 [IN]		pVodSession		VOD�Ự��ʶ
		 [IN OUT]	pVideoInfo		��Ƶ��Ϣָ��	
		 [IN]		dwReserved		������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodVideoInfo(IN const ISOC_LONGPTR lVodSession,IN OUT ST_VideoInfo*pVideoInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_SetVodPlayMode
*��  �ܣ�VOD��Ƶ���ſ���
*��  ����
		 [IN]	pVodSession		VOD�Ự��ʶ
		 [IN]	nPlayMode		��������
			�μ���PLAY=1,PAUSE,FAST_FORWARD,FAST_BACKWARD,SLOW_FORWARD,SLOW_BACKWARD,FRAME_FORWARD,FRAME_BACKWARD
		 [IN]	fFastSpeed		�����ٶȣ����������ٶ�Ϊ1.0f,ȡֵ��Χ(1.0f ~ 6.0f ),���ڿ��ֵԽ��Խ�죬��������ֵԽ��Խ��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodPlayMode(IN const ISOC_LONGPTR lVodSession,IN ISOC_INT nPlayMode,IN ISOC_FLOAT fFastSpeed=1.0f);

/******************************************************************************************************************************
*��������iSOC_SeekVodFile
*��  �ܣ�VOD���Ŷ�λ
*��  ����
		 [IN]		pVodSession		VOD�Ự��ʶ
		 [IN]		stSeek2			��λ�ľ���ʱ��ֵ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SeekVodFile(IN const ISOC_LONGPTR lVodSession,IN ISOC_SYSTEMTIME stSeek2);

/******************************************************************************************************************************
*��������iSOC_GetVodFilePlayedRange
*��  �ܣ���ȡVOD�ļ�����ʱ��
*��  ����
		 [IN]		pVodSession		VOD�Ự��ʶ
		 [IN OUT]	pStart			���ſ�ʼ����ʱ��
		 [IN OUT]	pNow			ȡ�ò��ŵľ���ʱ��
		 [IN OUT]	pTotalTs		�ļ��ܵ�ʱ�䳤��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodFilePlayedRange(IN const ISOC_LONGPTR lVodSession,IN OUT ISOC_SYSTEMTIME* pStart,IN OUT ISOC_SYSTEMTIME* pNow,IN OUT ISOC_SYSTEMTIME* pTotalTs);

/******************************************************************************************************************************
*��������iSOC_SetVodVideoFlip
*��  �ܣ�����ͼ���Ƿ�ת
*��  ����
		 [IN]		pVodSession		VOD�Ự��ʶ
		 [IN]		bIsFlip			�Ƿ�ת
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVideoFlip(IN const ISOC_LONGPTR lVodSession,IN ISOC_BOOL bIsFlip);

/******************************************************************************************************************************
*��������iSOC_SetVodVideoRenderState
*��  �ܣ�����ͼ���Ƿ���Ⱦ
*��  ����
		 [IN]		pVodSession		VOD�Ự��ʶ
		 [IN]		nRenderState	��Ⱦ״̬��Ϊ1ʱ��ʾ��Ⱦ��Ϊ0ʱ��ʾ����Ⱦ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVideoRenderState(IN const ISOC_LONGPTR lVodSession,IN ISOC_INT nRenderState);

/******************************************************************************************************************************
*��������iSOC_SetVodVideoDecodeState
*��  �ܣ�����ͼ���Ƿ����
*��  ����
		 [IN]		pVodSession		VOD�Ự��ʶ
		 [IN]		nDecodeState	����״̬��Ϊ1ʱ��ʾ���룬Ϊ0 ʱ��ʾ������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVideoDecodeState(IN const ISOC_LONGPTR lVodSession,IN ISOC_INT nDecodeState);

/******************************************************************************************************************************
*��������iSOC_SetVodVideoKeepAspectRatio
*��  �ܣ�����ͼ���߱�
*��  ����
		 [IN]		pVodSession		VOD�Ự��ʶ
		 [IN]		bIsKeepScale	�Ƿ񱣳ֿ�߱�
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVideoKeepAspectRatio(IN const ISOC_LONGPTR lVodSession,IN ISOC_BOOL bIsKeep);

/******************************************************************************************************************************
*��������iSOC_SetVodVolume
*��  �ܣ�����VOD����
*��  ����
		 [IN]		pVodSession		VOD�Ự��ʶ
		 [IN]		nVolume			��������ֵ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVolume(IN const ISOC_LONGPTR lVodSession,IN const ISOC_INT nVolume);

/******************************************************************************************************************************
*��������iSOC_GetVodVolume
*��  �ܣ���ȡVOD����
*��  ����
		 [IN]		pVodSession		VOD�Ự��ʶ
*����ֵ�����óɹ���������ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodVolume(IN const ISOC_LONGPTR lVodSession);

/******************************************************************************************************************************
*��������iSOC_AddVodFileTag
*��  �ܣ�VOD��ӱ�ǩ��Ϣ
*��  ����
		 [IN]		pVodSession		VOD�Ự��ʶ
		 [IN]		pStTagTime		��ǩʱ���
		 [IN]		pStUserAddTime	�û���ӱ�ǩ��ʱ���
		 [IN]		strTagTitle		��ǩ����
		 [IN]		strTigText		��ǩ����
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddVodFileTag(IN const ISOC_LONGPTR lVodSession,IN ISOC_SYSTEMTIME* pStTagTime,IN ISOC_SYSTEMTIME* pStUserAddTime,IN const ISOC_STR strTagTitle,IN const ISOC_STR strTigText);

/******************************************************************************************************************************
*��������iSOC_GetVodFileTagInfo
*��  �ܣ���ȡVOD��ǩ��Ϣ
*��  ����
		 [IN]		pVodSession			VOD�Ự��ʶ
		 [IN OUT]	pLDataListHead		��ǩ��Ϣ
		 [IN]		bOverTimeRequest	��ʱʱ��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pVodSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodFileTagInfo(IN const ISOC_LONGPTR lVodSession,IN OUT ISOC_LONGPTR* pLDataListHead,IN ISOC_BOOL bOverTimeRequest);

//����VOD��Ⱦģʽ���ڴ���ʵʱ�Ự����������ã�ͨ��VODģ�����չ�����������ʹ��벢�����Ӧ��ģʽ��Ŀǰģʽ��ʹ��GDI_RENDER_MOD��DDRAW_RENDER_MOD��D3D_RENDER_MOD��Щ��iSOC_UnitDefine.h���涨�壬ͬһ��VOD�Ựֻ��������ǰʼ������Ч��
#define SET_VOD_RENDER_MOD				 0x000003

//��ȡVOD��Ⱦģʽ��ͨ��VODģ�����չ������Щ���ʹ��벢�����ڻ�ȡVOD��Ⱦģʽ��ISOC_DWORD���͵�ָ��ͨ�����һ����������
#define GET_VOD_RENDER_MOD				 0x000004

//��ȡVOD��Ƶ��ȾSession��ֻ����VOD�����ɹ�����ܻ�ȡ�������ȡ��Session��Ч
#define GET_VOD_RENDER_SESSION			 0x000005

//����VOD���ģʽ���ڴ���VOD�Ự���ڿ��ǰ���ã�ͨ��VODģ�����չ�����������ʹ��벢�����Ӧ��ģʽ��Ŀǰģʽ��ʹ��0��1��Ϊ0ʱΪȫ֡ģʽ��Ϊ1ʱΪֻ��I֡ģʽ
#define  SET_VOD_FASTFORWARD_MOD		0x000006

//��ȡVOD���ģʽ��ͨ��VODģ�����չ������Щ���ʹ��벢�����ڻ�ȡVOD��Ⱦģʽ��ISOC_DWORD���͵�ָ��ͨ�����һ����������
#define GET_VOD_FASTFORWARD_MOD		    0x000007

//�����Ƿ����VPU�ļ�������
#define SET_VOD_USEVPUPARSER			0x000008

//��ȡ��ǰ��Ƶʹ�õ��ļ�����������
#define GET_VOD_FILEPARSER				0x00000a

//����Ƿ�֧��ĳ��ſ��ƹ��ܣ�ͨ��Vodģ�����չ�����������ʹ��룬dwExtendDataΪST_VodPlayCtrlSupportInfoָ��
#define CHECK_VOD_PLAY_CTRL_SUPPORT		0x00000b

//����VOD����ģʽ���ڴ���VOD�Ự���ڿ���ǰ���ã�ͨ��VODģ�����չ�����������ʹ��벢�����Ӧ��ģʽ��Ŀǰģʽ��ʹ��0��1��Ϊ0ʱ
#define SET_VOD_FASTBACKWARD_MOD		0x00000c

//��ȡVOD����ģʽ��ͨ��VODģ�����չ������Щ���ʹ��벢�����ڻ�ȡVOD��Ⱦģʽ��ISOC_DWORD���͵�ָ��ͨ�����һ����������
#define GET_VOD_FASTBACKWARD_MOD		0x00000d

//����VOD��ȡ��һ��GOP,dwExtendDataӦ����ISOC_INT64���͵�ָ��(PTS)
#define SET_VOD_NEXT_GOP				0x000009

//����VOD��ȡǰһ��GOP,dwExtendDataӦ����ISOC_INT64���͵�ָ��(PTS)
#define SET_VOD_PRE_GOP					0x000010

//����ivs������Ϣ
#define SET_IVS_CFG						0x000011

//����IVS�켣����Ϣ
#define SET_IVS_LINK_INFO				0x000012

/*
����ʼ�ճ����ص����ݣ��������ͣ״̬�����״̬��һֱ�ص����һ֡�����ݡ�
dwExtendDataӦ����ISOC_bool���͵�ָ�룬���ΪISOC_true,����ͣ�����״̬����Ȼ�ص����ݡ�
���ΪISOC_false������ͣ�����״̬�²���ص����ݡ�Ĭ�������Ϊ���ص�����״̬��
*/
#define SET_VOD_ALWAYS_CALL_DATA		0x000013

struct ST_VodPlayCtrlSupportInfo
{
	enum EN_PLAYCTRL
	{
		PLAY = 1, PAUSE, FAST_FORWARD, FAST_BACKWARD, SLOW_FORWARD, SLOW_BACKWARD, FRAME_FORWARD, FRAME_BACKWARD,SEEK
	};
	EN_PLAYCTRL nPlayCtrl; //�û����ò��ſ��ƴ���
	ISOC_BOOL bIsSupport; //�Ƿ�֧����SDK����
};

/******************************************************************************************************************************
*��������iSOC_VodExtendFunc
*��  �ܣ�VOD��չ����������ʵ��һЩ��չ����
*��  ����
		 [IN] lVodSession VOD�Ự��ʶ
		 [IN] nExType ��չ���ͱ�ʶ
		 [IN] dwExtendData ��չ����
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_VodExtendFunc(IN const ISOC_LONGPTR lVodSession,IN ISOC_INT nExType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*��������iSOC_SetVodVideoRotation
*��  �ܣ�ͼ����תһ���Ƕ�
*��  ����
		 [IN] lLiveSession  ʵʱ�Ự��ʶ
		 [IN] nAngle        ͼ����ת�Ƕȣ�Ŀǰ֧�֣�����90������180������270
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ����������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodVideoRotation(IN const ISOC_LONGPTR lVodSession,IN ISOC_INT nAngle);

/******************************************************************************************************************************
*��������iSOC_GetVodRotationAngle
*��  �ܣ���ȡ������ת�Ƕ�
*��  ����
		 [IN]   lVodSession  ʵʱ�Ự��ʶ
		 [OUT]  pAngle        ͼ����ת�Ƕ�,�����Ǹ�ֵ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ����������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetVodRotationAngle(IN const ISOC_LONGPTR lVodSession,OUT ISOC_INT *pAngle);

/******************************************************************************************************************************
*��������iSOC_SetVodStreamDataCallbackEx
*��  �ܣ����õ㲥�յ������ݻص����ص����������ǽ���ǰ������
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] pCallback �ص�����ָ��
		 [IN] dwCookie �û�Cookie�������ڻص����潫�����õ�Cookieֵ���أ�������ÿ������ó�NULL
		 [IN] nDataType �ص��������ͣ�1��ʾ��Ƶ��2��ʾ��Ƶ��4��ʾ�û��Զ�������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetVodStreamDataCallbackEx(IN const ISOC_LONGPTR lVodSession,IN const iSOC_StreamDataCallback pCallback,IN const ISOC_DWORDPTR dwCookie = 0, IN ISOC_INT nDataType = 7);

#ifdef __cplusplus
}
#endif