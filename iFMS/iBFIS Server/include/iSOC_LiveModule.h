#pragma once
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////ʵʱģ��ӿڵĶ���/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_CreateLiveSession
*��  �ܣ�����ʵʱ�Ự
*��  ����
		[IN OUT] pLiveSession ʵʱ�Ự��ʶ
		[IN] pStateCallback ״̬�ص����������ڷ��ش�ʵʱ�������кʹ򿪺�ĸ���״̬
		[IN] dwUserCookie �û�Cookie��������״̬�ص��н��û����õ�Cookieֵ���أ�������ÿ������ó�NULL
		[IN] dwReserved ��չֵ����ΪNULL
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע���ڲ�ʹ�ô˻Ự��һ��Ҫʹ��iSOC_ReleaseLiveSession����ʵʱ�Ự���٣���Ȼ�������ڴ�й©
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateLiveSession(IN OUT ISOC_LONGPTR *pLiveSession,IN const iSOC_OperatorStateCallback pStateCallback = ISOC_NULL,IN const ISOC_DWORDPTR dwUserCookie = 0,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ReleaseLiveSession
*��  �ܣ�����ʵʱ�Ự
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] dwReserved ��չֵ����ΪNULL
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseLiveSession(IN ISOC_LONGPTR lLiveSession,IN ISOC_DWORDPTR dwReserved = NULL);

/******************************************************************************************************************************
*��������iSOC_SetPriorStreamModel
*��  �ܣ������������ȸ�ʽ
*��  ����
		 [IN] pLiveSession ʵʱ�Ự���򿪳ɹ���ᴴ��һ��ʵʱ�Ự
		 [IN] nCodecID ���ȸ�ʽ����ID ������ID����,0��ʾ������
		 [IN] nStreamFlag ������־��1��ʾ��������2��ʾ��������0��ʾ������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetPriorStreamModel(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nCodecID = 0,IN ISOC_INT nStreamFlag  = 0);

/******************************************************************************************************************************
*��������iSOC_StartLiveStream
*��  �ܣ�����ʵʱ��
*��  ����
		 [IN] pLiveSession ʵʱ�Ự���򿪳ɹ���ᴴ��һ��ʵʱ�Ự
		 [IN] lMCSession MC�Ự��ʶ
		 [IN] hRenderWnd Ҫ��Ⱦ�Ĵ��ھ��
		 [IN] deviceInfo �豸��Ϣ�ṹ��
		 [IN] dwReserved ��չֵ����ΪNULL
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���pLiveSession��ֵ������¿ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartLiveStream(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_LONGPTR lMCSession,IN const ISOC_HWND hRenderWnd,IN const ST_DeviceItem deviceInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_SetLiveStreamDataCallback
*��  �ܣ�����ʵʱ�յ������ݻص����ص����������ǽ���ǰ������
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] pCallback �ص�����ָ��
		 [IN] dwCookie �û�Cookie�������ڻص����潫�����õ�Cookieֵ���أ�������ÿ������ó�NULL
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveStreamDataCallback(IN const ISOC_LONGPTR lLiveSession,IN const iSOC_StreamDataCallback pCallback,IN const ISOC_DWORDPTR dwCookie = 0);

/******************************************************************************************************************************
*��������iSOC_SetLiveMediaDataCallback
*��  �ܣ�����ʵʱ���������
*��  ����[IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] enMediaDataType ý����������
		 [IN] pCallback �ص�����ָ��
		 [IN] dwUserCookie �û�Cookie�������ڻص������н��û����õ�Cookieֵ���أ�������ÿ������ó�NULL
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveMediaDataCallback(IN const ISOC_LONGPTR lLiveSession,IN const MediaDataType enMediaDataType,IN const iSOC_MediaDataCallback pCallback,IN const ISOC_DWORDPTR dwUserCookie = 0);

/******************************************************************************************************************************
*��������iSOC_SetLiveMediaDataCallback
*��  �ܣ�����ʵʱ���������
*��  ����[IN] lLiveSession ʵʱ�Ự��ʶ
[IN] enMediaDataType ý����������
[IN] pCallback �ص�����ָ��
[IN] dwUserCookie �û�Cookie�������ڻص������н��û����õ�Cookieֵ���أ�������ÿ������ó�NULL
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveMediaDataCallbackEx(IN const ISOC_LONGPTR lLiveSession, IN const MediaDataType enMediaDataType, IN const iSOC_MediaDataCallbackEx pCallback, IN const ISOC_DWORDPTR dwUserCookie = 0);

/******************************************************************************************************************************
*��������iSOC_SetLiveLocalCacheFile
*��  �ܣ����ü�ʱ�طŵĻ����ļ�·��
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] strPath �ļ�·��
		 [IN] uFileSize�ļ���С��Ĭ��Ϊ200MB
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע�����õ��ļ��ĺ�׺��ҪΪ.rpb��������ʱĬ�ϲ����øù��ܣ�����Ϊ�տ���ȡ������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveLocalCacheFile(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_STR strPath,IN ISOC_UINT64 uFileSize = 209920000);

/******************************************************************************************************************************
*��������iSOC_FreezeLiveVideo
*��  �ܣ�ʵʱ��Ƶ����
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] bIsFreeze �����־��ΪISOC_TRUE��Ϊ������Ƶ��ΪISOC_FALSEʱΪ�������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_FreezeLiveVideo(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_BOOL bIsFreeze);

/******************************************************************************************************************************
*��������iSOC_SetLiveRenderRect
*��  �ܣ�����ʵʱ��Ⱦ������
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] pRecVideo Ҫ��Ⱦͼ�������ͼ�����Ͻ�����Ϊ(0,0)
		 [IN] pRecWnd Ҫ��Ⱦ�Ĵ������򣬴������Ͻ�����Ϊ(0,0)
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע���ô˺�����ʵ�־ֲ��Ŵ�ͽ�ͼ����Ⱦ�����ڵ�ĳһ����Ĺ���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveRenderRect(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_RECT* pRecVideo,IN const ISOC_RECT* pRecWnd);

/******************************************************************************************************************************
*��������iSOC_GetLiveVideoInfo
*��  �ܣ��õ�ʵʱ��Ƶ�������Ϣ
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN OUT] pVideoInfo ��Ƶ��Ϣ�ṹ��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLiveVideoInfo(IN const ISOC_LONGPTR lLiveSession,IN OUT ST_VideoInfo* pVideoInfo);

/******************************************************************************************************************************
*��������iSOC_GrabLiveFrame2Local
*��  �ܣ���ʵʱ��Ƶ��ĳ��֡ץ֡��ͼƬ���浽ָ���ļ�
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] strPicPath ͼƬ·��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��ͼƬ��ʽ����ͼƬ·����׺�����жϣ�֧�ֳ��õ�ͼƬ��ʽ���磺jpg,bmp
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GrabLiveFrame2Local(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_STR strPicPath);

/******************************************************************************************************************************
*��������iSOC_SetLiveRecord
*��  �ܣ�������ֹͣʵʱ��Ƶ���ֶ�¼��
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] bIsRecord ������ֹͣ�ֶ�¼���־��ΪISOC_TRUEʱ��ʾ�����ֶ�¼��ΪISOC_FALSEʱ��ʾֹͣ�ֶ�¼��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveRecord(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_BOOL bIsRecord);

/******************************************************************************************************************************
*��������iSOC_SetLiveVolume
*��  �ܣ�����ʵʱ����
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] nVolume ����ֵ����ΧΪ 0 ~ 100����Ϊ0 ʱ��������Ƶ�������Ⱦ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVolume(IN const ISOC_LONGPTR lLiveSession,IN const ISOC_INT nVolume);

/******************************************************************************************************************************
*��������iSOC_GetLiveVolume
*��  �ܣ���ȡ��Ƶ����
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
*����ֵ�����ص�ǰ����ֵ������ֵ�Ǵ��ڵ���0��ֵ�����С��0˵������ʧ�ܣ�����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLiveVolume(IN const ISOC_LONGPTR lLiveSession);

/******************************************************************************************************************************
*��������iSOC_AddLiveTag
*��  �ܣ����ʵʱ��ǩ
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] pStUserAddTime �û���ӱ�ǩ��ʱ��
		 [IN] strTagTitle ��ǩ����
		 [IN] strTagText ��ǩ����
		 [IN] dwReserved ����������ΪNULL
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddLiveTag(IN const ISOC_LONGPTR lLiveSession,IN ISOC_SYSTEMTIME* pStUserAddTime, IN ISOC_STR strTagTitle, IN ISOC_STR strTagText,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_StopLiveStream
*��  �ܣ�ֹͣʵʱ��Ƶ
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��ֹͣʵʱ��Ƶ������ڴ漰��Դ���ᱻ�ͷ���Ҫ����iSOC_ReleaseLiveSession�ͷ������Դ
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopLiveStream(IN const ISOC_LONGPTR lLiveSession);

/******************************************************************************************************************************
*��������iSOC_SetLiveVideoFlip
*��  �ܣ�ͼ�����·�ת180��
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] bIsFlip ͼ��ת��ʶ��ΪISOC_TRUEʱ��ת180�ȣ�ΪISOC_FALSEʱȡ����ת
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoFlip(IN const ISOC_LONGPTR lLiveSession,IN ISOC_BOOL bIsFlip);

/******************************************************************************************************************************
*��������iSOC_SetLiveVideoRenderState
*��  �ܣ���ʼ����ֹͣ��Ƶ��Ⱦ
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] nRenderState ��Ⱦ״̬��ʶ��Ϊ1ʱ��ʾ��Ⱦ��Ƶ��Ϊ0ʱ��ʾ����Ⱦ��Ƶ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע�������ô˺�������ʱĬ��Ϊ��Ⱦ���˺���������Ⱦ���ڱ���ס�������ص�ʱ����ã�����߳���Ч��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoRenderState(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nRenderState);

/******************************************************************************************************************************
*��������iSOC_SetLiveVideoDecodeState
*��  �ܣ���ʼ����ֹͣ����
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] nDecodeState ����״̬��ʶ��Ϊ1ʱ���룬Ϊ0 ʱ������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoDecodeState(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nDecodeState);

/******************************************************************************************************************************
*��������iSOC_SetLiveVideoKeepAspectRatio
*��  �ܣ�����ʵʱ��Ƶ���ֿ�߱�
*��  ����
		 [IN] lLiveSession  ʵʱ�Ự��ʶ
		 [IN] bIsKeep		��߱ȱ�ʶ��ΪISOC_TRUEʱ����ͼ���߱ȣ�ΪISOC_FALSEʱ������ͼ���߱�
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��Ĭ������²�����ͼ���߱ȣ�����ͼ���߱Ȼ�Ӱ��һЩ����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoKeepAspectRatio(IN const ISOC_LONGPTR lLiveSession,IN ISOC_BOOL bIsKeep);

//����ʵʱ����������ʱ������ͨ��ʵʱģ�����չ�����������ʹ��벢�����Ӧ��ʱ�������Ժ���Ϊ��λ��Ϊ����Ĭ��Ϊ10��,�磺iSOC_LiveExtendFunc��lLiveSession,SET_LIVE_REPULL_STREAM_TIME_SPAN,10*1000);
#define SET_LIVE_REPULL_STREAM_TIME_SPAN 0x000001 

//��ȡʵʱ����������ʱ������ͨ��ʵʱģ�����չ�����������ʹ��벢�����ڻ�ȡ��������ʱ���ISOC_DWORD���͵�ָ��ͨ�����һ���������룬�磺iSOC_LiveExtendFunc(lLiveSession,GET_LIVE_REPULL_STREAM_TIME_SPAN,(ISOC_DWORDPTR)&dwTimeSpan);
#define GET_LIVE_REPULL_STREAM_TIME_SPAN 0x000002

//����ʵʱ��Ⱦģʽ���ڴ���ʵʱ�Ự����������ã�ͨ��ʵʱģ�����չ�����������ʹ��벢�����Ӧ��ģʽ��Ŀǰģʽ��ʹ��GDI_RENDER_MOD��DDRAW_RENDER_MOD��D3D_RENDER_MOD��Щ��iSOC_UnitDefine.h���涨�壬ͬһ��ʵʱ�Ựֻ��������ǰʼ������Ч��
#define SET_LIVE_RENDER_MOD				 0x000003

//��ȡʵʱ��Ⱦģʽ��ͨ��ʵʱģ�����չ������Щ���ʹ��벢�����ڻ�ȡʵʱ��Ⱦģʽ��ISOC_DWORD���͵�ָ��ͨ�����һ����������
#define GET_LIVE_RENDER_MOD				 0x000004

//����ʵʱ����ʼ��ʱ��������ţ�һ��0Ϊ������1Ϊ������
#define SET_LIVE_INIT_CODEC_IDX			 0x000005

//��ȡʵʱ����ȾSession��ֻ��������ʵʱ���ɹ����ȡ������seesion��Ч
#define GET_LIVE_RENDER_SESSION			  0x000006

//���������Զ�Ӳ������֧��,Ĭ�ϲ�֧��
#define SET_LIVE_HWACCEL_SUPPORT		  0x000007

//���ö�������ʱ����ʵʱ���ɻص�ģʽ��0Ϊ���ص�(Ĭ�ϣ���������),1�ص� ��ÿ�������ɹ��󶼻�ص�
#define SET_LIVE_REPULL_CALLBACK_MOD      0X000008

/******************************************************************************************************************************
*��������iSOC_LiveExtendFunc
*��  �ܣ�ʵʱ��չ����������ʵ��һЩ��չ����
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] nExType ��չ���ͱ�ʶ
		 [IN] dwExtendData ��չ����
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LiveExtendFunc(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nExType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*��������iSOC_GetLiveStreamingServerAddr
*��  �ܣ���ȡ��ǰʵʱ��Ƶ����ý���������ַ��Ϣ
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN OUT] strStreamServerAddr ��ý���������ַ
		 [IN] dwReserved ��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLiveStreamingServerAddr(IN const ISOC_LONGPTR lLiveSession,IN OUT ISOC_STR strStreamServerAddr,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_SetCameraParameters
*��  �ܣ��������������
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] camParam �����������Ϣ�ṹ��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetCameraParameters(IN const ISOC_LONGPTR lLiveSession,IN const ST_CameraParameter camParam);

/******************************************************************************************************************************
*��������iSOC_GetCameraParameters
*��  �ܣ���ȡ���������
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] pCamParam �����������Ϣ�ṹ��ָ��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetCameraParameters(IN const ISOC_LONGPTR lLiveSession,IN OUT ST_CameraParameter* pCamParam);

/******************************************************************************************************************************
*��������iSOC_SaveCameraParametersMode
*��  �ܣ��������������ģʽ
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] nConfigMode ģʽ0������ ģʽ1��ҹ�� ģʽ2������ ģʽ3������ ģʽ4���Զ���
		 [IN] dwReserved ��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SaveCameraParametersMode(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nConfigMode,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ExecuteCameraParametersMode
*��  �ܣ�ִ�����������ģʽ
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] nAreaMode ���������ģʽ��ģʽ0����ǰ�ֿ����������豸 ģʽ1����ǰ�ֿ������û���Ⱥ�������豸 ģʽ2��ƽ�����������豸 ģʽ3����ǰ�豸
		 [IN] nConfigMode ģʽ0������ ģʽ1��ҹ�� ģʽ2������ ģʽ3������ ģʽ4���Զ���
		 [IN] dwReserved ��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ExecuteCameraParametersMode(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nAreaMode,IN ISOC_INT nConfigMode,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_GetLiveVideoCodecInfo
*��  �ܣ���ȡ��������������Ϣ
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN OUT]  lDataListHead ��������ͷ��ʶ��Ҫ�õ�����ı��������Ϣ��ʹ�������������������ȡ����ȡ�ľ���ṹ��Ϊ��ST_VideoInfo
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��Ĭ��ʹ�õ�һ��������Ϣ����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLiveVideoCodecInfo(IN const ISOC_LONGPTR lLiveSession,IN OUT ISOC_LONGPTR* lDataListHead);

/******************************************************************************************************************************
*��������iSOC_SelectLiveVideoCodec
*��  �ܣ�ѡ�����ı�����Ϣ�ӷ������ϻ�ȡʵʱ����ʹ�ô˺�����ʵ�������л�
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] stCodecInfo ������Ϣ�ṹ��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SelectLiveVideoCodec(IN const ISOC_LONGPTR lLiveSession,IN ST_VideoInfo stCodecInfo);

/******************************************************************************************************************************
*��������iSOC_GetCurrentLiveVideoCodecInfo
*��  �ܣ���ȡ��ǰѡ��ı�����Ϣ
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN OUT] pCodecInfo ������Ϣ�ṹ��ָ��
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetCurrentLiveVideoCodecInfo(IN const ISOC_LONGPTR lLiveSession,IN OUT ST_VideoInfo* pCodecInfo);

/******************************************************************************************************************************
*��������iSOC_SetCameraViewArea
*��  �ܣ�����ǰ���豸��ͼ��ʾ��ָ���ľ���λ��
*��  ����
		[IN]	lLiveSession		ʵʱ�Ự��ʶ
		[IN]	rtView		����������Ϣ
		[IN]	nSpeed				�ƶ��ٶ�
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lLiveSession�����ȡʧ������
*��  ע���˹���Ҫǰ���豸֧��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetCameraViewArea(IN const ISOC_LONGPTR lLiveSession,IN ISOC_RECT rtView,IN ISOC_INT nSpeed = 10);

iSOC_EXPORT_MODE ISOC_INT iSOC_CalculateCameraViewArea(IN ISOC_RECT rtVideoRender,IN ISOC_RECT rtMoveRange,IN ISOC_SIZE szVideo
	,IN ISOC_BOOL bIsFlip,IN ISOC_BOOL bIsKeepAspectRatio,IN ISOC_BOOL bIsCenterClicked,IN OUT ISOC_RECT* rtCameraView);

/******************************************************************************************************************************
*��������iSOC_SetLiveVideoSmoothLevel
*��  �ܣ����õ�ǰʵʱ��Ƶ��ƽ���Լ���
*��  ����
		[IN]	lLiveSession		ʵʱ�Ự��ʶ
		[IN]	nSmoothLevel		ƽ���Լ���ֵ����Χ��1��10��ֵԽ��Խƽ���������ô˺���Ĭ�ϼ���Ϊ5
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lLiveSession�����ȡʧ������
*��  ע��ƽ���Լ����ʵʱ�����෴�ģ�ƽ���Լ���Խ�ߣ�ʵʱ�Ծͻ�Խ��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoSmoothLevel(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nSmoothLevel);

/******************************************************************************************************************************
*��������iSOC_SetLiveVideoRotation
*��  �ܣ�ͼ����תһ���Ƕ�
*��  ����
		 [IN] lLiveSession  ʵʱ�Ự��ʶ
		 [IN] nAngle        ͼ����ת�Ƕȣ�Ŀǰ֧�֣�����90������180������270
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ����������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveVideoRotation(IN const ISOC_LONGPTR lLiveSession,IN ISOC_INT nAngle);

/******************************************************************************************************************************
*��������iSOC_GetLiveRotationAngle
*��  �ܣ���ȡ������ת�Ƕ�
*��  ����
		 [IN]   lLiveSession  ʵʱ�Ự��ʶ
		 [OUT]  pAngle        ͼ����ת�Ƕ�,�����Ǹ�ֵ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ����������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLiveRotationAngle(IN const ISOC_LONGPTR lLiveSession,OUT ISOC_INT *pAngle);

/******************************************************************************************************************************
*��������iSOC_SetLiveStreamDataCallbackEx
*��  �ܣ�����ʵʱ�յ������ݻص����ص����������ǽ���ǰ������
*��  ����
		 [IN] lLiveSession ʵʱ�Ự��ʶ
		 [IN] pCallback �ص�����ָ��
		 [IN] dwCookie �û�Cookie�������ڻص����潫�����õ�Cookieֵ���أ�������ÿ������ó�NULL
		 [IN] nDataType �ص��������ͣ�1��ʾ��Ƶ��2��ʾ��Ƶ��4��ʾ�û��Զ�������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveStreamDataCallbackEx(IN const ISOC_LONGPTR lLiveSession,IN const iSOC_StreamDataCallback pCallback,IN const ISOC_DWORDPTR dwCookie = 0, IN ISOC_INT nDataType = 7);


/******************************************************************************************************************************
*��������iSOC_SetLiveAudioSpectrumCallback
*��  �ܣ�����ʵʱ��Ƶ��ֵ�ص�
*��  ����
[IN] lLiveSession ʵʱ�Ự��ʶ
[IN] pCallback �ص�����ָ��
[IN] dwCookie �û�Cookie�������ڻص����潫�����õ�Cookieֵ���أ�������ÿ������ó�NULL
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetLiveAudioSpectrumCallback(IN const ISOC_LONGPTR lLiveSession, IN const iSOC_AudioSpectrumCallback pCallback, IN const ISOC_DWORDPTR dwCookie = 0);

#ifdef __cplusplus
}
#endif
