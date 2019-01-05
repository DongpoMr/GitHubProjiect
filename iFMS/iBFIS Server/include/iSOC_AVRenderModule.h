#ifndef __ISOC_AVRENDERMODULE_API_HEADER__
#define __ISOC_AVRENDERMODULE_API_HEADER__

#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include <MMReg.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_CreateVideoRender
*��  �ܣ�������Ƶ��Ⱦ��
*��  ����
		[OUT]	lVideoRenderSession	��Ƶ��Ⱦ���Ự��ʶ
		[IN]	strRenderDes		��Ƶ��Ⱦ����������
				�μ���������������
					"D3D_RENDER"    //d3d��Ⱦ����
					"GDI_RENDER"	//GDI��Ⱦ����
					"DDRAW_RENDER"	//ddraw��Ⱦ����
		[IN]	dwReserved			������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_CreateVideoRender(OUT ISOC_LONGPTR *lVideoRenderSession,IN ISOC_STR strRenderDes,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*��������iSOC_InitVideoRender
*��  �ܣ���ʼ����Ƶ��Ⱦ��
*��  ����
		[IN]	lVideoRenderSession	��Ⱦ���Ự��ʶ
		[IN]	hTargetWnd			Ŀ�괰��
		[IN]	stVideoSize			��Ƶ���
		[IN]	enVideoDataFmt		��Ƶ���ݸ�ʽ,��YV12=0��RGB24... ...,Ŀǰֻ֧��YV12.
		[IN]	dwReserved=0		������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_InitVideoRender(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_HWND hTargetWnd,IN ISOC_SIZE *stVideoSize,IN MediaDataType enVideoDataFmt = YV12,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*��������iSOC_SetVideoRenderRect
*��  �ܣ�������Ƶ��Ⱦ���򣬲�����Ĭ��Ϊ��Ⱦ����ͼ��
*��  ����
		[IN]	lVideoRenderSession	��Ⱦ���Ự��ʶ
		[IN]	rtVideoRange		��Ƶ��Ⱦ������ֵ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_SetVideoRenderRect(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_RECT rtVideoRange);

/******************************************************************************************************************************
*��������iSOC_SetTargetWndRenderRect
*��  �ܣ�����Ŀ�괰�ڵ���Ⱦλ�ã���������Ĭ����Ⱦ��������
*��  ����
		[IN]	lVideoRenderSession	��Ⱦ���Ự��ʶ
		[IN]	rtWndRange			��Ⱦ����λ��
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_SetTargetWndRenderRect(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_RECT rtWndRange);

/******************************************************************************************************************************
*��������iSOC_SetVideoRenderKeepAspectRatio
*��  �ܣ������Ƿ񱣳ֿ�߱�
*��  ����
		[IN]	lVideoRenderSession	��Ⱦ���Ự��ʶ
		[IN]	bNeedKeepScale		�Ƿ񱣳ֿ�߱�
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_SetVideoRenderKeepAspectRatio(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_BOOL bNeedKeepAspectRatio);

/******************************************************************************************************************************
*��������iSOC_RenderVideo
*��  �ܣ���Ƶ��Ⱦ
*��  ����
		[IN]	lVideoRenderSession	��Ⱦ���Ự��ʶ
		[IN]	szVideo				��Ƶ���ݵĿ����Ϣ
		[IN]	pVideoFrame			��Ƶ����֡
 		[IN]	dwReserved			������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_RenderVideo(IN ISOC_LONGPTR lVideoRenderSession,IN ST_SIZE szVideo,IN ST_VideoFrame * pVideoFrame,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*��������iSOC_AddOverlayInfo
*��  �ܣ�����Ƶ������Ϣ
*��  ����
		[IN]	lVideoRenderSession	��Ⱦ���Ự��ʶ
		[IN OUT]	pOverlayInfo ������Ϣ�ṹ�壬����ӵ�ʱ�������IDֵ�����
					����ӳɹ�����Զ��ı������IDֵ�������޸ĺ�ɾ����Ҫͨ�������IDֵ��������
 		[IN]	dwReserved			������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע����Ӷ������ͬ�ĵط���ʾ��ͬ����Ϣ
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_AddOverlayInfo(IN ISOC_LONGPTR lVideoRenderSession,IN OUT ST_OverlayInfo* pOverlayInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ModifyOverlayInfo
*��  �ܣ��޸���Ƶ������Ϣ����ʵ�ֵ�����Ϣ��̬�仯
*��  ����
		[IN]	lVideoRenderSession	��Ⱦ���Ự��ʶ
		[IN]	overlayInfo			������Ϣ�ṹ�壬�����IDֵҪ��֤��ȷ�������޸Ĳ��ɹ�
 		[IN]	dwReserved			������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_ModifyOverlayInfo(IN ISOC_LONGPTR lVideoRenderSession,IN ST_OverlayInfo overlayInfo,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_DelOverlayInfo
*��  �ܣ�ɾ����Ƶ������Ϣ
*��  ����
		[IN]	lVideoRenderSession	��Ⱦ���Ự��ʶ
		[IN]	nOverlayInfoID		��Ƶ������ϢIDֵ��Ϊ-1ʱ��ʾɾ�����е�����Ϣ
 		[IN]	dwReserved			������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_DelOverlayInfo(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_INT nOverlayInfoID,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ReleaseVideoRender
*��  �ܣ�ע����Ƶ��Ⱦ��
*��  ����
		[IN]	lVideoRenderSession	��Ⱦ���Ự��ʶ
		[IN]	dwReserved			������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_ReleaseVideoRender(IN ISOC_LONGPTR lVideoRenderSession,IN ISOC_DWORDPTR dwReserved=0);



/******************************************************************************************************************************
*��������iSOC_CreateAudioRender
*��  �ܣ�������Ƶ��Ⱦ��
*��  ����
		[OUT]	lAudioRenderSession	��Ƶ��Ⱦ���Ự��ʶ
		[IN]	strRenderDes		��Ⱦ��������������ΪNULL
		[IN]	dwReserved			������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_CreateAudioRender(OUT ISOC_LONGPTR *lAudioRenderSession,IN ISOC_STR strRenderDes,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*��������iSOC_InitAudioRender
*��  �ܣ���ʼ����Ƶ��Ⱦ��
*��  ����
		[IN]	lAudioRenderSession	��Ƶ��Ⱦ���Ự��ʶ
		[IN]	pAudioInfo			��Ƶ��ʽ��Ϣ
		[IN]	dwReserved			������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_InitAudioRender(IN ISOC_LONGPTR lAudioRenderSession,IN ST_AudioInfo* pAudioInfo,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*��������iSOC_SetAudioVolume
*��  �ܣ���������
*��  ����
		[IN]	lAudioRenderSession	��Ƶ��Ⱦ���Ự��ʶ
		[IN]	lVolume				����ֵ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_SetAudioVolume(IN ISOC_LONGPTR lAudioRenderSession,IN ISOC_LONGPTR lVolume);

/******************************************************************************************************************************
*��������iSOC_GetAudioVolume
*��  �ܣ���ȡ����
*��  ����
		[IN]	lAudioRenderSession	��Ƶ��Ⱦ���Ự��ʶ
		[OUT]	lVolume				����ֵ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_GetAudioVolume(IN ISOC_LONGPTR lAudioRenderSession,OUT ISOC_INT *nVolume);

/******************************************************************************************************************************
*��������iSOC_RenderAudio
*��  �ܣ���Ƶ��Ⱦ
*��  ����
		[IN]	lAudioRenderSession	��Ƶ��Ⱦ���Ự��ʶ
		[IN]	pData				��Ƶ����ָ��
		[IN]	nDataLen			��Ƶ���ݳ���
		[IN]	dwReserved			������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_RenderAudio(IN ISOC_LONGPTR lAudioRenderSession,IN ISOC_BYTE* pData,IN ISOC_INT nDataLen,IN ISOC_DWORDPTR dwReserved=0);

/******************************************************************************************************************************
*��������iSOC_ReleaseAudioRender
*��  �ܣ�ע����Ƶ��Ⱦ��
*��  ����
		[IN]	lAudioRenderSession	��Ƶ��Ⱦ���Ự��ʶ
		[IN]	dwReserved			������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT	iSOC_ReleaseAudioRender(IN ISOC_LONGPTR lAudioRenderSession,IN ISOC_DWORDPTR dwReserved=0);

#ifdef __cplusplus
}
#endif

#endif