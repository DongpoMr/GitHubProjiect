#pragma once
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////�ļ�ģ��ӿڵĶ���/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif


/////////////////////////////////////////////////�ļ�����ģ��ӿڶ���///////////////////////////////////////////////////////////////////////////
enum ExportFormat
{
    EFT_AVI,
    EFT_SMF,
    EFT_MPG,
    EFT_MP4
};

enum ExportVodFileState{ EXPORTS_FAILED, EXPORTS_FINISHED, EXPORTS_PROGRESS };

enum ExportMode
{
    EM_NORMAL,	    //�ɵĵ���ģʽ�������˽�������Ļ�������ת�봦��
    EM_TRANSLATE	//ת��󵼳��������Ĺ����н��н����ٱ���
};

enum ExportOverlayType
{
    EOT_TEXT,	    //��������
    EOT_BOX,		//���Ӿ��ο�
    EOT_PIC			//����ͼƬ
};

#ifndef iSOC_ExportProcCllback
typedef int(__stdcall *iSOC_ExprotProcCallback)(IN ISOC_DWORDPTR dwUserCookie, ISOC_UINT64 pts, MediaDataType enDataType, ST_VideoFrame* pFrame, ISOC_INT nProgress);
#endif

#ifndef iSOC_ExportFileCallback
	typedef int (__stdcall *iSOC_ExportFileCallback)(const ISOC_DWORDPTR dwUserCookie,const ExportVodFileState enState,const int nProgress,const ISOC_STR strDes);
#endif

/******************************************************************************************************************************
*��������iSOC_CreateExportFileSession
*��  �ܣ������ļ������Ự
*��  ����
		 [IN OUT]	pExportSession	�ļ������Ự��ʶ
		 [IN]		lMCSession		MC�Ự��ʶ
		 [IN]		nExportType		��������(0ΪAVI�ļ�,1ΪSMF�ļ�,2ΪMPG�ļ�,3ΪMP4�ļ�)
		 [IN]		strDestFilePath	����Ŀ���ļ�·��
		 [IN]		pCallback		����״̬�ص�ָ��
		 [IN]		dwUserCookie	�û�Cookie�ڵ���״̬�ص������з���
		 [IN]		nSubtitle         �����Ƿ�������Ļ�ļ���ֻ����avi��ʽ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע����nExportTypeΪ0��Ŀ���ļ��ĺ�׺������Ϊ.avi
		��nExportTypeΪ1��Ŀ���ļ��ĺ�׺������Ϊ.smf
		��nExportTypeΪ2��Ŀ���ļ��ĺ�׺������Ϊ.mpg
        ��nExportTypeΪ3��Ŀ���ļ��ĺ�׺������Ϊ.mp4
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateExportFileSession(IN OUT ISOC_LONGPTR* pExportSession,IN const ISOC_LONGPTR lMCSession,IN ISOC_INT nExportType,IN ISOC_STR strDestFilePath,IN const iSOC_ExportFileCallback pCallback = ISOC_NULL,IN const ISOC_DWORDPTR dwUserCookie = 0,IN ISOC_INT nSubtitle=0);

/******************************************************************************************************************************
*��������iSOC_AddExportFileItem
*��  �ܣ���ӷ������ϵ���Ҫ������Դ��Ƶ�ļ�
*��  ����
		 [IN]	lExportSession	�ļ������Ự��ʶ
		 [IN]	vodFileInfo		VOD�ļ���Ϣ�ṹ��	
		 [IN]	pStartTime		��ʼʱ�䣬���Ϊ�����ʾʹ��vodFileInfo�е��ļ���ʼʱ�䣬�����Ϊ����ʼʱ��Ӧ���ڵ���vodFileInfo�е��ļ���ʼʱ��
		 [IN]	pEndTime		����ʱ�䣬���Ϊ�����ʾʹ��vodFileInfo�е��ļ�����ʱ�䣬�����Ϊ�������ʱ��ӦС�ڵ���vodFileInfo�е��ļ�����ʱ��
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��lExportSession�����ȡʧ������
*��  ע���˺����ɵ��ö�Σ����ڽ�����������ϵ��ļ��ϲ�����Ϊһ���ļ�������Ҫ�����ļ��Ŀ�ʼ�ͽ���ʱ���Ⱥ�˳�����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddExportFileItem(IN const ISOC_LONGPTR lExportSession,IN const ST_VodFileInfo vodFileInfo,IN ISOC_SYSTEMTIME* pStartTime,IN ISOC_SYSTEMTIME* pEndTime);

/******************************************************************************************************************************
*��������iSOC_StartExportFile
*��  �ܣ���ʼ�ļ�����
*��  ����
		 [IN]	lExportSession	�ļ������Ự��ʶ
		 [IN]	dwReserved		��������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��lExportSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartExportFile(IN const ISOC_LONGPTR lExportSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_PauseExportFile
*��  �ܣ���ͣ�ļ�����
*��  ����
		 [IN]	lExportSession	�ļ������Ự��ʶ
		 [IN]	dwReserved		��������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��lExportSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_PauseExportFile(IN const ISOC_LONGPTR lExportSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_StopExportFile
*��  �ܣ�ֹͣ�ļ�����
*��  ����
		 [IN]	lExportSession	�ļ������Ự��ʶ
		 [IN]	dwReserved		��������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��lExportSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopExportFile(IN const ISOC_LONGPTR lExportSession,IN ISOC_DWORDPTR dwReserved);

/******************************************************************************************************************************
*��������iSOC_ReleaseExportFileSession
*��  �ܣ������ļ������Ự
*��  ����
		 [IN]	lExportSession	�ļ������Ự��ʶ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseExportFileSession(IN const ISOC_LONGPTR lExportSession);

#ifndef SET_EXPORT_FILE_REASON 
#define SET_EXPORT_FILE_REASON 0x001001 //�����ļ�����ԭ�򣬿�ͨ����չ�������ã�nExteydType�����ֵdwExtendData�����Ӧԭ����ַ���ָ��,�ڴ���Session��ʼ����֮ǰ����
#endif

/******************************************************************************************************************************
*��������iSOC_ExportFileExtendFunc
*��  �ܣ��ļ�����ģ����չ����
*��  ����
		 [IN]	lExportSession	�ļ������Ự��ʶ
		 [IN]	nExteydType		��չ����
		 [IN]	dwExtendData	��չ����
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��lExportSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ExportFileExtendFunc(IN const ISOC_LONGPTR lExportSession,IN const ISOC_INT nExteydType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*��������iSOC_SetExportMode
*��  �ܣ������ļ�����ģʽ(��ͨ��ת��)
*��  ����
[IN]	lExportSession	�ļ������Ự��ʶ
[IN]	mode		    ����ģʽ
[IN]	dwExtendData	��չ����
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��lExportSession�����ȡʧ������
*��  ע��Ĭ��Ϊ��ͨģʽ��������Ϊת��ģʽʱ���Ὣ������vod�ļ���������±����H264
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetExportMode(IN const ISOC_LONGPTR lExportSession, IN const ExportMode mode, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_AddExportOverlayInfo
*��  �ܣ���ӵ���������Ϣ
*��  ����
[IN]	lExportSession	�ļ������Ự��ʶ
[IN]    type            ��������
[IN]	pConfigParam    ��typeΪEOT_TEXTʱ������ST_ExportTextCfg���͵�ָ��
[IN]    nConifgLen      ������Ϣ�ṹ�峤��
[IN]	dwExtendData	��չ����
*����ֵ���ɹ����ش������0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��lExportSession�����ȡʧ������
*��  ע��Ŀǰֻ֧�ֵ���������Ϣ,����ֵΪ������Ϣ��id����0��ʼ
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddExportOverlayInfo(IN ISOC_LONGPTR lExportSession, ExportOverlayType type, IN ISOC_VOID* pConfigParam, IN ISOC_INT nConifgLen, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ModifyExportOverlayInfo
*��  �ܣ��޸ĵ���������Ϣ
*��  ����
[IN]	lExportSession	�ļ������Ự��ʶ
[IN]    nOverlayInfoID  ������ϢID
[IN]	pConfigParam    ��typeΪEOT_TEXTʱ������ST_ExportTextCfg���͵�ָ��
[IN]    nConifgLen      ������Ϣ�ṹ�峤��
[IN]	dwExtendData	��չ����
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��lExportSession�����ȡʧ������
*��  ע������iSOC_ExprotProcCallback�ص��õ��ø÷�����ʵ�ֶԵ������ֵ��޸�,Ŀǰֻ��Ҫ����ST_ExportTextCfg����������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ModifyExportOverlayInfo(IN ISOC_LONGPTR lExportSession, IN ISOC_INT nOverlayInfoID, IN ISOC_VOID* pConfigParam, IN ISOC_INT nConfigLen, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_DelExportOverlayInfo
*��  �ܣ�ɾ��������Ϣ
*��  ����
[IN]	lExportSession	�ļ������Ự��ʶ
[IN]    nOverlayInfoID  ������ϢID
[IN]	dwExtendData	��չ����
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��lExportSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelExportOverlayInfo(IN ISOC_LONGPTR lExportSession, IN ISOC_INT nOverlayInfoID, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_SetExportProcCallbackFunc
*��  �ܣ�����ת����Ȼص�
*��  ����
[IN]	lExportSession	�ļ������Ự��ʶ
[IN]    pFunc           �ص���ַ
[IN]    dwUserCookie    �û�����
[IN]	dwExtendData	��չ����
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��lExportSession�����ȡʧ������
*��  ע��������Ҫ�ڵ����������޸ĵ�����Ϣ�ģ������ûص������ڻص���ȥ�����޸ķ���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetExportProcCallbackFunc(IN ISOC_LONGPTR lExportSession, IN iSOC_ExprotProcCallback pFunc, IN ISOC_DWORDPTR dwUserCookie, IN ISOC_DWORDPTR dwReserved = 0);


////////////////////////////////////////////////�ļ��ϴ�ģ��ӿڶ���///////////////////////////////////////////////////////////////////////////
#ifndef iSOC_UploadFileStatusCallback
enum EN_UPLOADSTATUSFALG{ULSF_STARTFAIL=1,ULSF_STARTOK,ULSF_STOPFAIL,ULSF_STOPOK,ULSF_DELFAIL,ULSF_DELOK,ULSF_FINISHFALI,ULSF_FINISHOK};
typedef ISOC_INT (__stdcall* iSOC_UploadFileStatusCallback)(ISOC_ID nItemID,EN_UPLOADSTATUSFALG enStatusFlag,ISOC_STR strDes,ISOC_DWORDPTR dwUserCookie);
#endif

/******************************************************************************************************************************
*��������iSOC_CreateUploadFileSession
*��  �ܣ������ļ��ϴ��Ự
*��  ����
		[IN OUT]  pLUploadSession  �ļ��ϴ��Ự��ʶ
		[IN]	  lMCSession	   MC�Ự��ʶ		
		 
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLUploadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateUploadFileSession(IN OUT ISOC_LONGPTR* pLUploadSession,IN const ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*��������iSOC_AddUploadFileItem
*��  �ܣ�����ļ�������
*��  ����
		[IN]	 lUploadSession   �ļ��ϴ��Ự��ʶ
		[IN OUT] pNItemIdx		  �ļ������б�Ŵ�0��ʼ
		[IN]	 strSrcFilePath	  Դ�ļ�·��
		[IN]	 devInfo		  �豸��Ϣ
		[IN]	 strUserGUID	  �û����ɵ�guid
		[IN]	 strDes			  �ļ�������Ϣ
		[IN]	 dwReserved		  ��������
		 
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLUploadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddUploadFileItem(IN const ISOC_LONGPTR lUploadSession,IN OUT ISOC_INT* pNItemIdx,IN const ISOC_STR strSrcFilePath,IN ST_DeviceItem devInfo,IN const ISOC_STR strUserGUID = NULL,IN const ISOC_STR strDes = NULL,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_DelUploadFileItem
*��  �ܣ�ɾ���ļ�������
*��  ����
		[IN]	lUploadSession    �ļ��ϴ��Ự��ʶ
		[IN]	nItemIdx		  �ļ������б�Ŵ�0��ʼ
		[IN]	dwReserved		  ��������
		 
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLUploadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelUploadFileItem(IN const ISOC_LONGPTR lUploadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_GetUploadFileInfo
*��  �ܣ���ȡ�ļ�������Ϣ	
*��  ����
		 [IN]		lUploadSession		�ļ��ϴ��Ự��ʶ
		 [IN]		nItemIdx			�ļ������б�Ŵ�0��ʼ
		 [IN OUT]	pIFileID			�ļ�id
		 [IN OUT]	pNFileStatus		��ǰ�ļ�״̬	
		 [IN OUT]	pNProgress			��ǰ�ļ����ؽ���
		 [IN]		dwReserved			��������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLUploadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetUploadFileInfo(IN const ISOC_LONGPTR lUploadSession,IN const ISOC_INT nItemIdx,IN OUT ISOC_ID* pIFileID,IN OUT ISOC_INT* pNFileStatus,IN OUT ISOC_INT* pNProgress,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_StartUploadFile
*��  �ܣ���ʼ�����ļ�����
*��  ����
		[IN]		lUploadSession		�ļ��ϴ��Ự��ʶ
		[IN]		nItemIdx			�ļ������б�Ŵ�0��ʼ
		[IN]		dwReserved			��������
		 
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLUploadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartUploadFile(IN const ISOC_LONGPTR lUploadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_StopUploadFile
*��  �ܣ�ֹͣ�ļ�����
*��  ����
		[IN]		lUploadSession		�ļ����ػỰ��ʶ
		[IN]		nItemIdx			�ļ������б�Ŵ�0��ʼ
		[IN]		dwReserved			��������
		 
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLUploadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopUploadFile(IN const ISOC_LONGPTR lUploadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_RegsiterUploadFileStatusNotifyCallback
*��  �ܣ�ע���ļ�����״̬�ص�
*��  ����
		[IN]		lUploadSession		�ļ����ػỰ��ʶ
		[IN]		pCallback			�ļ�����״̬�ص�����ָ��
		[IN]		dwUserCookie		�û�Cookie
		 
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLUploadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegsiterUploadFileStatusNotifyCallback(IN const ISOC_LONGPTR lUploadSession,IN iSOC_UploadFileStatusCallback pCallback,IN ISOC_DWORDPTR dwUserCookie);


/******************************************************************************************************************************
*��������iSOC_UploadFileExtendFunc
*��  �ܣ��ļ����ؿ���չ���� 
*��  ����
		[IN]		lUploadSession		�ļ����ػỰ��ʶ
		[IN]		nExteydType			����չ����
		[IN]		dwExtendData		����չ���� 
		 
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ���������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLUploadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UploadFileExtendFunc(IN const ISOC_LONGPTR lUploadSession,IN const ISOC_INT nExteydType,IN ISOC_DWORDPTR dwExtendData);


/******************************************************************************************************************************
*��������iSOC_ReleaseUploadFileSession
*��  �ܣ������ļ��ϴ��Ự
*��  ����
		[IN]	lUploadSession �ļ��ϴ��Ự
*����ֵ���ɹ��򷵻ش���0��ֵ�����򷵻�С�ڵ���0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLUploadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseUploadFileSession(IN ISOC_LONGPTR lUploadSession);


////////////////////////////////////////////////�ļ�����ģ��ӿڶ���///////////////////////////////////////////////////////////////////////////
#ifndef iSOC_DownloadFileStatusCallback
enum EN_DOWNLOADSTATUSFALG{DLSF_STARTFAIL=1,DLSF_STARTOK,DLSF_STOPFAIL,DLSF_STOPOK,DLSF_FINISHFALI,DLSF_FINISHOK};
typedef ISOC_INT (__stdcall* iSOC_DownloadFileStatusCallback)(ISOC_ID nItemID,EN_DOWNLOADSTATUSFALG enStatusFlag,ISOC_STR strDes,ISOC_DWORDPTR dwUserCookie);
#endif

/******************************************************************************************************************************
*��������iSOC_GetGrapFileList
*��  �ܣ���ȡץ֡�ļ�
*��  ����
		 [IN]		lMCSession		MC�Ự��ʶ
		 [IN]		strDeviceList	��ѯ���豸ID�б����£�1,2,3,4,5... ...
		 [IN]		stQueryFilter	��ѯ����
		 [IN]		pCallBack		��ѯ����ص�����ָ��
		 [IN]		dwCookie		�û�COOKIE
		 [IN]		strQueryGuid	�û���ѯGUID��ÿ�β�ѯ�û�����ָ����ͬ�Ĳ�ѯGUID
		 [IN]		bSyncExec		�첽ģʽ��ѯ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetGrapFileList( IN const ISOC_LONGPTR lMCSession,IN const ISOC_STR strDeviceList,IN ST_VodQueryFilter stQueryFilter,IN iSOC_GrabFileInfoCallback pCallBack,IN ISOC_DWORDPTR dwCookie,IN ISOC_STR strQueryGuid = NULL,IN ISOC_BOOL bSyncExec = ISOC_TRUE );

/******************************************************************************************************************************
*��������iSOC_GetGrapFileById
*��  �ܣ���ȡץ֡�ļ�
*��  ����
[IN]		lMCSession		MC�Ự��ʶ
[IN]		strFileID    	�ļ�id
[IN]		strDeviceID     ��ѯ���豸ID
[IN]		stQueryFilter	��ѯ����
[IN]		pCallBack		��ѯ����ص�����ָ��
[IN]		dwCookie		�û�COOKIE
[IN]		strQueryGuid	�û���ѯGUID��ÿ�β�ѯ�û�����ָ����ͬ�Ĳ�ѯGUID
[IN]		bSyncExec		�첽ģʽ��ѯ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetGrapFileById(IN const ISOC_LONGPTR lMCSession, IN const ISOC_STR strFileID,IN const ISOC_STR strDeviceID, IN ST_VodQueryFilter stQueryFilter,IN iSOC_GrabFileInfoCallback pCallback, IN ISOC_DWORDPTR dwCookie, IN ISOC_STR strQueryGuid = NULL, IN ISOC_BOOL bSyncExec = ISOC_TRUE);

/******************************************************************************************************************************
*��������iSOC_CreateDownloadFileSession
*��  �ܣ������ļ����ػỰ��ʶ
*��  ����
		 [IN OUT]	pLDownloadSession	�ļ����ػỰ��ʶ
		 [IN]		lMCSession			mc�Ự��ʶ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLDownloadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateDownloadFileSession(IN OUT ISOC_LONGPTR* pLDownloadSession,IN const ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*��������iSOC_AddDownloadFileItem
*��  �ܣ������ļ�������
*��  ����
		 [IN]		lDownloadSession	�ļ����ػỰ��ʶ
		 [IN OUT]	pNItemIdx			�ļ�id��0��ʼ
		 [IN]		strDstFilePath		Ŀ���ļ�·��
		 [IN]		stFileInfo			�ļ���Ϣ
		 [IN]		strUserGUID			�û����ɵ�guid
		 [IN]		strDes				�ļ�������Ϣ
		 [IN]		dwReserved			��������

*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLDownloadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddDownloadFileItem(IN const ISOC_LONGPTR lDownloadSession,IN OUT ISOC_INT* pNItemIdx,IN const ISOC_STR strDstFilePath,IN ST_GrabFileInfo stFileInfo,IN const ISOC_STR strUserGUID = NULL,IN const ISOC_STR strDes = NULL,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_DelDownloadFileItem	
*��  �ܣ�ɾ���ļ�������
*��  ����
		[IN]		lDownloadSession	�ļ����ػỰ��ʶ
		[IN]		nItemIdx			�ļ�id��0��ʼ
		[IN]		dwReserved			��������
		 
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLDownloadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelDownloadFileItem(IN const ISOC_LONGPTR lDownloadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_GetDownloadFileInfo
*��  �ܣ���ȡ�ļ�������Ϣ
*��  ����
		[IN]		lDownloadSession	�ļ����ػỰ��ʶ
		[IN]		nItemIdx			�ļ�������id��0��ʼ
		[IN OUT]	pFileInfo			�ļ���Ϣ
		[IN OUT]	pNFileStatus		�ļ���ǰ����״̬
		[IN OUT]	pNProgress			�ļ����ؽ���
		[IN]		dwReserved			��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLDownloadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDownloadFileInfo(IN const ISOC_LONGPTR lDownloadSession,IN const ISOC_INT nItemIdx,IN OUT ST_GrabFileInfo *pFileInfo,IN OUT ISOC_INT* pNFileStatus,IN OUT ISOC_INT* pNProgress,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_StartDownloadFile
*��  �ܣ���ʼ�����ļ�����
*��  ����	
		[IN]		lDownloadSession	�ļ����ػỰ��ʶ
		[IN]		nItemIdx			�ļ�������id��0��ʼ
		[IN]		dwReserved			��������
		 
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLDownloadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartDownloadFile(IN const ISOC_LONGPTR lDownloadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_StopDownloadFile
*��  �ܣ�ֹͣ�ļ�����
*��  ����
		 [IN]		lDownloadSession	�ļ����ػỰ��ʶ
		 [IN]		nItemIdx			�ļ�������id��0��ʼ
		 [IN]		dwReserved			��������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLDownloadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopDownloadFile(IN const ISOC_LONGPTR lDownloadSession,IN const ISOC_INT nItemIdx,ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_RegsiterDownloadFileStatusNotifyCallback
*��  �ܣ�ע���ļ�����״̬�ص�
*��  ����
		[IN]		lDownloadSession	�ļ����ػỰ��ʶ
		[IN]		pCallback			�ļ����ػص�����ָ��
		[IN]		dwUserCookie		�û�cookie

*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLDownloadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegsiterDownloadFileStatusNotifyCallback(IN const ISOC_LONGPTR lDownloadSession,IN iSOC_DownloadFileStatusCallback pCallback,IN ISOC_DWORDPTR dwUserCookie);

/******************************************************************************************************************************
*��������iSOC_DownloadFileExtendFunc
*��  �ܣ��ļ����ؿ���չ����
*��  ����
		 [IN]		lDownloadSession	�ļ����ػỰ��ʶ
		 [IN]		nExteydType			����չ������
		 [IN]		dwExtendData		����չ��������Ϣ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ,�������ʧ�ܿ�ͨ��iSOC_GetLastErrorDes��pLDownloadSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DownloadFileExtendFunc(IN const ISOC_LONGPTR lDownloadSession,IN const ISOC_INT nExteydType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*��������iSOC_ReleaseDownloadFileSession
*��  �ܣ������ļ����ػỰ
*��  ����
		 [IN]	 lDownloadSession �ļ����ػỰ
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseDownloadFileSession(IN ISOC_LONGPTR lDownloadSession);



////////////////////////////////////////////////�ļ�ɾ��ģ��ӿڶ���///////////////////////////////////////////////////////////////////////////

/******************************************************************************************************************************
*��������iSOC_CreateDeleteFileSession
*��  �ܣ�����ɾ���ļ��Ự
*��  ����
		[IN OUT]	lpDeleteSession	ɾ���Ự���
		[IN]		lMCSession		�������ĻỰ
		[IN]		pCallback		ɾ�������Ϣ�ص�����
		[IN]		dwUserCookie	�û�COOKIE
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateDeleteFileSession(IN OUT ISOC_LONGPTR *lpDeleteSession,IN const ISOC_LONGPTR lMCSession,IN iSOC_DeleteFileNotifyCallback pCallback=NULL,IN ISOC_DWORDPTR dwUserCookie=0);


/******************************************************************************************************************************
*��������iSOC_DeleteFile
*��  �ܣ�ɾ�����ϴ��ĺ�Ǩ�Ƶ��ļ�
*��  ����
		[IN]	lDeleteSession	ɾ���Ự���
		[IN]	stFileInfo		Ҫɾ�����ļ���Ϣ
		[IN]	dwReserved		������
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע���첽����ʽ��ͨ��iSOC_CreateDeleteFileSession���õĻص���������ɾ�������Ϣ���ɹ���nStatus=3��ʧ�ܣ�nStatus=4����ʱ��nStatus=0(��ʱʱ��20S)
		 �ɶ�ε��ô˺�����ɾ����ͬ���ļ�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DeleteFile(IN const ISOC_LONGPTR lDeleteSession,IN const ST_VodFileInfo stFileInfo,IN ISOC_DWORDPTR dwReserved = 0);


/******************************************************************************************************************************
*��������iSOC_ReleaseDeleteFileSession
*��  �ܣ�����ɾ���ļ��Ự
*��  ����
		[IN]	lDeleteSession	ɾ���Ự���
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseDeleteFileSession(IN OUT ISOC_LONGPTR lDeleteSession);


////////////////////////////////////////////////�ļ�Ǩ��ģ��ӿڶ���///////////////////////////////////////////////////////////////////////////

/******************************************************************************************************************************
*��������iSOC_CreateMigrateSession
*��  �ܣ�����Ǩ�ƻỰ��ʶ
*��  ����
		 [IN]		lMCSession			MC�Ự��ʶ
		 [IN OUT]	pMigrateSession		Ǩ�ƻỰ��ʶָ��
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateMigrateSession(IN ISOC_LONGPTR lMCSession,IN OUT ISOC_LONGPTR* pMigrateSession);

/******************************************************************************************************************************
*��������iSOC_AddMigrateTaskItem
*��  �ܣ����Ǩ������
*��  ����
		 [IN]	lMigrateSession		Ǩ�ƻỰ
		 [IN]	stVodFileInfo		VOD�ļ���Ϣ
		 [IN]	strDesc				Ǩ������
		 [IN]	pStartTime			Ǩ���ļ���ʼʱ�䣬���Ϊ����ΪstVodFileInfo�е��ļ���ʼʱ��
		 [IN]	pEndTime			Ǩ���ļ�����ʱ�䣬���Ϊ����ΪstVodFileInfo�е��ļ�����ʱ��
		 [IN]	strUserGUID			�û�GUID�������û���ʶ�ļ���������VOD��ѯ�в�ѯ��Ǩ��ʱ���õ�GUID
		 [IN]	dwReserved			������������Ϊ0
*����ֵ�����ص�ǰ��ӵı�������IDֵ�������溯���е�nTaskItemID
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddMigrateTaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ST_VodFileInfo stVodFileInfo,IN ISOC_STR strDesc,IN ISOC_SYSTEMTIME* pStartTime,IN ISOC_SYSTEMTIME* pEndTime,IN ISOC_STR strUserGUID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_GetMigrateTaskItemCount
*��  �ܣ���ȡ��ǰǨ�ƻỰ��Ǩ������ĸ���
*��  ����
		 [IN]	lMigrateSession		Ǩ�ƻỰ
*����ֵ�����ص�ǰǨ�ƻỰ�е�Ǩ���������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMigrateTaskItemCount(IN const ISOC_LONGPTR lMigrateSession);

/******************************************************************************************************************************
*��������iSOC_GetMigrateTaskInfoByIndex
*��  �ܣ�ͨ��Ǩ������Ľű��ȡ�����������Ϣ
*��  ����
		 [IN]		lMigrateSession		Ǩ�ƻỰ
		 [IN]		nIndex				����ű꣬��0��ʼ���������-1�ķ�Χ
		 [IN OUT]	pInfo				Ǩ��������Ϣ
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ�����ʧ�ܿ�ʹ��iSOC_GetLastErrorDes��lMigrateSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetMigrateTaskInfoByIndex(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nIndex,IN OUT ST_MigrateInfo* pInfo);

/******************************************************************************************************************************
*��������iSOC_GetUnfinishedMigrateTaskInfoFromeServer
*��  �ܣ���ȡ��ǰϵͳ�е�ǰ�û�δ���Ǩ�Ƶ�����Ǩ������
*��  ����
		 [IN]	lMigrateSession		Ǩ�ƻỰ
		 [IN]	pCallback			����״̬�ص��������ȡ�ɹ���ص��������ߣ�Ȼ��ʹ��iSOC_GetMigrateTaskItemCount��iSOC_GetMigrateTaskInfoByIndexȥ����Ǩ������
		 [IN]	dwUserCookie		�û�Cookie���ڻص��д���
		 [IN]	dwReserved			��������
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ�����ʧ�ܿ�ʹ��iSOC_GetLastErrorDes��lMigrateSession�����ȡʧ������
*��  ע���˺��������ʼ����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetUnfinishedMigrateTaskInfoFromeServer(IN const ISOC_LONGPTR lMigrateSession,IN iSOC_OperatorStateCallback pCallback,IN ISOC_DWORDPTR dwUserCookie,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_DelMigrateTaskItem
*��  �ܣ�ɾ������Ǩ������
*��  ����
		 [IN]	lMigrateSession		Ǩ�ƻỰ
		 [IN]	nTaskItemID			��������ID�����Ϊ-1���ʾ��������
		 [IN]	dwReserved			��������
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ�����ʧ�ܿ�ʹ��iSOC_GetLastErrorDes��lMigrateSession�����ȡʧ������
*��  ע���˺���ֻ��������Щͨ��iSOC_AddMigrateTaskItem��ӵĻ�δ��ʼ��Ǩ�����񣬻����Ѿ���ʼ��ͨ��iSOC_StopMigrateTaskItem
		 ֹͣ������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_DelMigrateTaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_StopMigrateTaskItem
*��  �ܣ�ֹͣǨ������
*��  ����
		 [IN]	lMigrateSession		Ǩ�ƻỰ
		 [IN]	nTaskItemID			��������ID�����Ϊ-1���ʾ��������
		 [IN]	dwReserved			��������
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ�����ʧ�ܿ�ʹ��iSOC_GetLastErrorDes��lMigrateSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopMigrateTaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_PauseMigrateTaskItem
*��  �ܣ���ͣǨ������
*��  ����
		 [IN]	lMigrateSession		Ǩ�ƻỰ
		 [IN]	nTaskItemID			��������ID�����Ϊ-1���ʾ��������
		 [IN]	dwReserved			��������
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ�����ʧ�ܿ�ʹ��iSOC_GetLastErrorDes��lMigrateSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_PauseMigrateTaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_SetMigrateTaskItemSpeed
*��  �ܣ�����Ǩ�������ٶ�
*��  ����
		 [IN]	lMigrateSession		Ǩ�ƻỰ
		 [IN]	nTaskItemID			��������ID�����Ϊ-1���ʾ��������
		 [IN]	fMigrateSpeed		Ǩ���ٶȣ���KBΪ��λ
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ�����ʧ�ܿ�ʹ��iSOC_GetLastErrorDes��lMigrateSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetMigrateTaskItemSpeed(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemID,IN ISOC_FLOAT fMigrateSpeed);

/******************************************************************************************************************************
*��������iSOC_StartMigrateTaskItem
*��  �ܣ���ʼǨ������
*��  ����
		 [IN]	lMigrateSession		Ǩ�ƻỰ
		 [IN]	nTaskItemID			��������ID�����Ϊ-1���ʾ��������
		 [IN]	dwReserved			��������
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ�����ʧ�ܿ�ʹ��iSOC_GetLastErrorDes��lMigrateSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartMigrateTaskItem(IN const ISOC_LONGPTR lMigrateSession,IN ISOC_INT nTaskItemID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ReleaseMigrateSession
*��  �ܣ�����Ǩ�ƻỰ
*��  ����
		 [IN]	lMigrateSession		Ǩ�ƻỰ
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע������֮����ʹ�øûỰ���в���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseMigrateSession(IN const ISOC_LONGPTR lMigrateSession);

#ifdef __cplusplus
}
#endif
