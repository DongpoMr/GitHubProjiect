#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*iSOC_CreateGrabSession
*��  �ܣ���������ץ֡Session
*��  ����
[IN]		lGrabSession		Grab�Ự��ʶ
[IN]		lMCSesion			MC�Ự��ʶ
[IN]		info				VOD�ļ���Ϣ
[IN]		pCallback			ץ֡״̬�ص�
[IN]		dwCookie			�û�����
[IN]		dwReserved			������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע��һ��Session��Ӧһ��VOD�ļ������ܸ���
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateVodGrabSession(IN OUT ISOC_LONGPTR* lGrabSession, IN ISOC_LONGPTR lMCSession, ST_VodFileInfo info
    , IN iSOC_GrabStatusCallback pCallback, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*iSOC_ReleaseGrabSession
*��  �ܣ����ٿ���ץ֡Session
*��  ����
[IN]		lGrabSession		Grab�Ự��ʶ
[IN]		lMCSesion			MC�Ự��ʶ
[IN]		pCallback			ץ֡״̬�ص�
[IN]		dwCookie			�û�����
[IN]		dwReserved			������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseVodGrabSession(IN ISOC_LONGPTR lGrabSession, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*iSOC_AddVodGrabFrame
*��  �ܣ����Ҫץȡ��֡���ļ���Ϣ
*��  ����
[IN]		lGrabSession		Grab�Ự��ʶ
[IN]		stGrabTime			ץ֡ʱ��
[IN]		pstrGrabFilePath	�ļ�����·��(�����ļ���)
[IN]		dwReserved			������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddVodGrabFrame(IN ISOC_LONGPTR lGrabSession, IN ISOC_SYSTEMTIME stGrabTime, IN ISOC_STR pstrGrabFilePath, IN ISOC_DWORDPTR dwReserved = 0);


/******************************************************************************************************************************
*iSOC_AddVodGrabFrameRect
*��  �ܣ����ָ��ʱ���һ֡ͼ���ָ�����򱣴浽ָ���ļ���
*��  ����
[IN]		lGrabSession		Grab�Ự��ʶ
[IN]		stGrabTime			ץ֡ʱ��
[IN]		pstrGrabFilePath	�ļ�����·��(�����ļ���)
[IN]		grabRect			ָ��ץ֡������
[IN]		dwReserved			������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_AddVodGrabFrameRect(IN ISOC_LONGPTR lGrabSession, IN ISOC_SYSTEMTIME stGrabTime, IN ISOC_STR pstrGrabFilePath, IN ISOC_RECT grabRect, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*iSOC_RemoveVodGrabFrame
*��  �ܣ��Ƴ�Ҫץȡ��֡
*��  ����
[IN]		lGrabSession		Grab�Ự��ʶ
[IN]		stGrabTime			ץ֡ʱ��
[IN]		dwReserved			������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveVodGrabFrame(IN ISOC_LONGPTR lGrabSession, IN ISOC_SYSTEMTIME stGrabTime, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*iSOC_StartGrab
*��  �ܣ���ʼץ֡
*��  ����
[IN]		lGrabSession		Grab�Ự��ʶ
[IN]		dwReserved			������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StartGrab(IN ISOC_LONGPTR lGrabSession, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*iSOC_StopGrab
*��  �ܣ�ֹͣץ֡
*��  ����
[IN]		lGrabSession		Grab�Ự��ʶ
[IN]		dwReserved			������
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ�ɵ���iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_StopGrab(IN ISOC_LONGPTR lGrabSession, IN ISOC_DWORDPTR dwReserved = 0);

#ifdef __cplusplus
}
#endif