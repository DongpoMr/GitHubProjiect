#pragma once
#include "iSOC_UnitDefine.h"

//////////////////////////////////////////////////GISģ��ӿڵĶ���/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_CreateGISSession
*��  �ܣ�����GIS�Ự
*��  ����
		 [IN]		hParentWnd		�����ھ��
		 [IN]		strLoginURL		GIS������URL
		 [IN OUT]	pLGisSession	GIS�Ự��ʶ
		 [IN]		dwReserved		����������Ϊ0
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateGISSession(IN const ISOC_HWND hParentWnd,IN const ISOC_STR strLoginURL,IN OUT ISOC_LONGPTR* pLGisSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ReleaseGISSession
*��  �ܣ�����GIS�Ự
*��  ����
		 [IN]	lGisSession	GIS�Ự��ʶ
		 [IN]	dwReserved	����������Ϊ0
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseGISSession(IN const ISOC_LONGPTR lGisSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_GetSafeGISHwnd
*��  �ܣ��õ�GIS���ڵĴ��ھ��
*��  ����
		 [IN]		lGisSession	GIS�Ự��ʶ
		 [IN OUT]	pHwnd		GIS���ھ��
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetSafeGISHwnd(IN const ISOC_LONGPTR lGisSession,IN OUT ISOC_HWND* pHwnd);

/******************************************************************************************************************************
*��������iSOC_SetGISWindowRect
*��  �ܣ�����GIS����λ��
*��  ����
		 [IN]	lGisSession	GIS�Ự��ʶ
		 [IN]	pRecGisWnd  GIS����������Ϣ�ṹ��ָ�롣������Ϣ�������������GIS���ڵĸ����ڵĿͻ�������ģ����GIS���ڵĸ�����
							�����洰�ڣ���ô������������Ļ����ϵ��
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetGISWindowRect(IN const ISOC_LONGPTR lGisSession,IN const ISOC_RECT* pRecGisWnd);

/******************************************************************************************************************************
*��������iSOC_SearchRoadInGIS
*��  �ܣ���·��ѯ
*��  ����
		 [IN]		lGisSession		GIS�Ự��ʶ
		 [IN]		strRoadName		Ҫ��ѯ�ĵ�·��
		 [IN OUT]	pQueryResult	��ѯ���Ľ�����Զ��ŷָ�
		 [IN]		dwReserved		����������Ϊ0
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SearchRoadInGIS(IN const ISOC_LONGPTR lGisSession,IN const ISOC_STR strRoadName,OUT ISOC_STR* pQueryResult, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_LocateRoadInGIS
*��  �ܣ��ڵ�ͼ���ҳ���Ӧ��·
*��  ����
		 [IN]	lGisSession		GIS�Ự��ʶ
		 [IN]	strRoadName		��·��
		 [IN]	dwReserved		��������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LocateRoadInGIS(IN const ISOC_LONGPTR lGisSession,IN const ISOC_STR strRoadName,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_LocateCameraInGIS
*��  �ܣ��ڵ�ͼ���ҳ���Ӧ���������ʶ
*��  ����
		 [IN]	lGisSession		GIS�Ự��ʶ
		 [IN]	strCameraIDs	�����ID����������ʹ�ö��Ž���ID�ָ�
		 [IN]	dwReserved		��������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LocateCameraInGIS(IN const ISOC_LONGPTR lGisSession,IN const ISOC_STR strCameraIDs,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_LocatePoliceStationInGIS
*��  �ܣ��ڵ�ͼ���ҳ���Ӧ���ɳ�������ʶ
*��  ����
		 [IN]	lGisSession		GIS�Ự��ʶ
		 [IN]	strPcsName		�ɳ�������
		 [IN]	dwReserved		��������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LocatePoliceStationInGIS(IN const ISOC_LONGPTR lGisSession,IN const ISOC_STR strPcsName,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_GisExtendFunc
*��  �ܣ�GISģ����չ����
*��  ����
		 [IN]	lGisSession		GIS�Ự��ʶ
		 [IN]	nExteydType		��չ����
		 [IN]	dwExtendData	��չ����
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GISExtendFunc(IN const ISOC_LONGPTR lGisSession,IN const ISOC_INT nExteydType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*��������iSOC_RegisterSelectedDevicePlayVideoMsgInGIS
*��  �ܣ�������GIS��ѡ����豸��Ҫ��ʾ��Ƶʱ�����淢�͵���Ϣ����
*��  ����
		 [IN]	lGisSession		GIS�Ự��ʶ
		 [IN]	hRecvMsgWnd		������Ϣ�Ĵ���
		 [IN]	lMsg			��Ϣֵ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С�ڵ���0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterSelectedDevicePlayVideoMsgInGIS(IN ISOC_LONGPTR lGisSession,IN ISOC_HWND hRecvMsgWnd,IN ISOC_LONG lMsg);

#ifdef __cplusplus
}
#endif