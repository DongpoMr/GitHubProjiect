#ifndef __ISOC_PTSCONTROLMODULE_API_HEADER__
#define __ISOC_PTSCONTROLMODULE_API_HEADER__

#include "iSOC_UnitDefine.h"
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"

#ifdef __cplusplus 
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_CreatePtzControlSession
*��  �ܣ�����PTZ���ƻỰ
*��  ����
		[IN OUT]	lPtzCtrlSession		PTZ���ƻỰ
		[IN]		lMCSession			�������ĻỰ
		[IN]		stDeviceInfo		�豸��Ϣ
		[IN]		pStateCallback		����״̬�ص�
        [IN]        dwCookie            �û�����
*����ֵ���ɹ���ʼ���򷵻ش���0��ֵ����ʼ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreatePtzControlSession(IN OUT ISOC_LONGPTR *lPtzCtrlSession,IN ISOC_LONGPTR lMCSession,IN const ST_DeviceItem stDeviceInfo,IN iSOC_OperatorStateCallback pStateCallback = ISOC_NULL,ISOC_DWORDPTR dwCookie = 0);

/******************************************************************************************************************************
*��������iSOC_ControlPtzDirection
*��  �ܣ�����ָ���豸PTZ�İ˸������ƶ�����
*��  ����
		[IN]	lPtzCtrlSession		PTZ���ƻỰ
		[IN]	nDirection			�ƶ��ķ��򣬲μ�ֵ���£�
				{PTZ_LEFT=0,PTZ_LEFT_UP,PTZ_UP,PTZ_UP_RIGHT,PTZ_RIGHT,PTZ_DOWN_RIGHT,PTZ_DOWN,PTZ_DOWN_LEFT
				,PTZ_ABSOLUTE_POS,PTZ_STOP_MOVE,PTZ_RESET, PTZ_PUSH_FAR, PTZ_PULL_NEAR}
		[IN]	nPanSpeed			ˮƽ�ƶ��ٶ� 1-100
		[IN]	nTiltSpeed			��ֱ�ƶ��ٶ� 1-100
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzDirection(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_INT nDirection,IN ISOC_INT nPanSpeed=1,IN ISOC_INT nTiltSpeed=1);

/******************************************************************************************************************************
*��������iSOC_ControlPtzZoom
*��  �ܣ�����ָ���豸PTZ������
*��  ����
		[IN]	lPtzCtrlSession		PTZ���ƻỰ
		[IN]	bZoomIn				ΪISOC_TRUEΪ�Ŵ�ΪISOC_FALSEΪ��С
		[IN]	nSpeed				���ŵ��ٶ�	 1-100
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��ʹ��iSOC_ControlPtzDirection����PTZ_STOP_MOVEֹͣPTZ�ƶ�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzZoom(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_BOOL bZoomIn,IN ISOC_INT nSpeed=10);

/******************************************************************************************************************************
*��������iSOC_ControlPtzFocus
*��  �ܣ�����ָ���豸PTZ�ľ۽�
*��  ����
		[IN]	lPtzCtrlSession		PTZ���ƻỰ
		[IN]	bFocusIn			ΪISOC_TRUE��Ϊ�����,ΪISOC_FALSEΪ����Զ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��ʹ��iSOC_ControlPtzDirection����PTZ_STOP_MOVEֹͣPTZ�ƶ�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzFocus(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_BOOL bFocusIn);

/******************************************************************************************************************************
*��������iSOC_ControlPtzAuxiliary
*��  �ܣ�����ָ���豸PTZ����̨
*��  ����
		[IN]	lPtzCtrlSession		PTZ���ƻỰ
		[IN]	nAuxiliaryIdx		��̨����ֵ���μ�����ֵ��
				{CTRL_LIGHT�ƹ�,CTRL_FOG����,CTRL_RAIN_BRUSH��ˢ}
		[IN]	bEnable				�Ƿ���
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzAuxiliary(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_INT nAuxiliaryIdx,IN ISOC_BOOL bEnable);

/******************************************************************************************************************************
*��������iSOC_ControlPtzAuxiliary
*��  �ܣ�����ָ���豸PTZ����̨��֧��͸��
*��  ����
[IN]	lPtzCtrlSession		PTZ���ƻỰ
[IN]	nAuxiliaryIdx		��̨����ֵ���μ�����ֵ��
{CTRL_LIGHT�ƹ�,CTRL_FOG����,CTRL_RAIN_BRUSH��ˢ}
[IN]	bEnable				�Ƿ���
[IN]	pMsg				͸����Ϣ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzAuxiliaryEx(IN const ISOC_LONGPTR lPtzCtrlSession, IN ISOC_INT nAuxiliaryIdx, IN ISOC_BOOL bEnable,IN ISOC_VOID* pMsg,IN ISOC_INT nMsgLen);

/******************************************************************************************************************************
*��������iSOC_GetCurrentPtzPos
*��  �ܣ���ȡ��ǰPTZλ��
*��  ����
		[IN]	lPtzCtrlSession		PTZ���ƻỰ
		[IN OUT]pPtzPos				PTZλ����Ϣ�ṹ��
		[IN]	dwReserved			��������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetCurrentPtzPos(IN const ISOC_LONGPTR lPtzCtrlSession,IN OUT ST_PtzPos* pPtzPos,IN ISOC_DWORDPTR dwReserved);

/******************************************************************************************************************************
*��������iSOC_SetCurrentPtzPos
*��  �ܣ�����PTZλ��
*��  ����
		[IN]	lPtzCtrlSession		PTZ���ƻỰ
		[IN]	pPtzPos				PTZλ����Ϣ�ṹ��
		[IN]	dwReserved			��������
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_SetCurrentPtzPos(IN const ISOC_LONGPTR lPtzCtrlSession,IN ST_PtzPos* pPtzPos,IN ISOC_DWORDPTR dwReserved);


/******************************************************************************************************************************
*��������iSOC_PtzExtendFunc
*��  �ܣ�PTZ������չ����������ʵ��һЩ��չ����
*��  ����
		 [IN] lPtzCtrlSession PTZ���ƻỰ
		 [IN] nExType ��չ���ͱ�ʶ
		 [IN] dwExtendData ��չ����
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ����iSOC_GetLastErrorDes��ȡ��������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_PtzExtendFunc(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_INT nExType,IN ISOC_DWORDPTR dwExtendData);

/******************************************************************************************************************************
*��������iSOC_ControlDevIO
*��  �ܣ�����ָ���豸I/O����
*��  ����
		[IN]	lPtzCtrlSession		PTZ���ƻỰ
		[IN]	nIOID				IO��ID��Ŀǰ��ֵ��Ч��io����ֻ����������Ŀ���
		[IN]	bEnable				�Ƿ���
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlDevIO(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_INT nIOID,IN ISOC_BOOL bEnable);

/******************************************************************************************************************************
*��������iSOC_ReleasePtzControlSession
*��  �ܣ�����PTZ���ƻỰ
*��  ����
		[IN]	lPtzCtrlSession		PTZ���ƻỰ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleasePtzControlSession(IN const ISOC_LONGPTR lPtzCtrlSession);

/******************************************************************************************************************************
*��������iSOC_GetTourPresetPosSession
*��  �ܣ���ȡѲ��Ԥ�õ����Ự
*��  ����
		[IN OUT]	lpTPSession		Ѳ��Ԥ�õ����Ự
		[IN]		lMCSession		�������ĻỰ
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetTourPresetPosSession(IN OUT ISOC_LONGPTR *lpTPSession,IN ISOC_LONGPTR lMCSession);


/******************************************************************************************************************************
*��������iSOC_GetDeviceTourCount
*��  �ܣ���ȡ�豸Ѳ����Ϣ����
*��  ����
		[IN]		lTPSession		Ѳ��Ԥ�õ����Ự
		[IN]		stDeviceInfo	�豸��Ϣ������豸��Ϣ��strIcmsSignΪ����lIcmsId=0�����ȡȫ���豸��Ѳ����Ϣ����
*����ֵ���ɹ��򷵻��豸Ѳ����Ϣ���������ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceTourCount(IN ISOC_LONGPTR lTPSession,IN ST_DeviceItem stDeviceInfo);

/******************************************************************************************************************************
*��������iSOC_GetDeviceTourInfoByIdx
*��  �ܣ�����������ȡ�豸Ѳ����Ϣ
*��  ����
		[IN]		lTPSession		Ѳ��Ԥ�õ����Ự
		[IN OUT]	lpTourInfo		��ȡ���豸Ѳ����Ϣָ��
		[IN]		stDeviceInfo	�豸��Ϣ������豸��Ϣ��strIcmsSignΪ����lIcmsId=0����������豸�л�ȡ�������ָ���豸�л�ȡ
		[IN]		nIdx			����ֵ����0��ʼ
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceTourInfoByIdx(IN ISOC_LONGPTR lTPSession,IN OUT LPST_TOURINFO lpTourInfo,IN ST_DeviceItem stDeviceInfo,IN ISOC_INT nIdx);

/******************************************************************************************************************************
*��������iSOC_GetDeviceTourInfoByID
*��  �ܣ�����Ѳ��ID����ȡ�豸��Ѳ����Ϣ
*��  ����
		[IN]		lTPSession		Ѳ��Ԥ�õ����Ự
		[IN OUT]	lpTourInfo	��ȡ���豸Ѳ����Ϣָ��
		[IN]		nTourNum		Ѳ��ID
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDeviceTourInfoByID(IN ISOC_LONGPTR lTPSession,IN OUT LPST_TOURINFO lpTourInfo,IN ISOC_ID nTourNum);

/******************************************************************************************************************************
*��������iSOC_ControlDeviceTour
*��  �ܣ������豸Ѳ��
*��  ����
		[IN]		lTPSession		Ѳ��Ԥ�õ����Ự
		[IN]		nCtrlCode		������
					�μ�����ֵ��{INSERT_POINT=0,UPDATE_POINT,DELETE_POINT,GOTO_POINT,STOP_POINT}
		[IN]		stDeviceInfo	�豸��Ϣ
		[IN]		stTourInfo		Ѳ����Ϣ
		[IN]		dwReseved		������
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע���˺���Ϊ�첽���������Ҫ��ȡ��׼ȷ�ķ��ؽ������Ҫ����iSOC_RegistDeviceCruiseUpdateNotifyע���첽�¼��ص�����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlDeviceTour(IN ISOC_LONGPTR lTPSession,IN ISOC_INT nCtrlCode,IN ST_DeviceItem stDeviceInfo,IN LPST_TOURINFO stTourInfo,IN ISOC_DWORDPTR dwReseved=0);

/******************************************************************************************************************************
*��������iSOC_RegisterDeviceTourNotifyCallback
*��  �ܣ�ע���첽�¼��ص�����
*��  ����
		[IN]		lTPSession		Ѳ��Ԥ�õ����Ự
		[IN]		pCallback		�ص�����ָ��
		[IN]		dwCookie		�û�COOKIE
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterDeviceTourNotifyCallback(IN ISOC_LONGPTR lTPSession,IN iSOC_TourInfoCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*��������iSOC_RemoveDeviceTourNotifyCallback
*��  �ܣ��Ƴ��첽�¼��ص�����
*��  ����
		[IN]		lTPSession		Ѳ��Ԥ�õ����Ự
		[IN]		pCallback		�ص�����ָ��
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveDeviceTourNotifyCallback(IN ISOC_LONGPTR lTPSession,IN iSOC_TourInfoCallback pCallback);

/******************************************************************************************************************************
*��������iSOC_GetDevicePresetPosCount
*��  �ܣ���ȡ�豸Ԥ�õ���Ϣ����
*��  ����
		[IN]		lTPSession		Ѳ��Ԥ�õ����Ự
		[IN]		stDeviceInfo	�豸��Ϣ
*����ֵ���ɹ��򷵻�Ԥ�õ�����ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDevicePresetPosCount(IN ISOC_LONGPTR lTPSession,IN ST_DeviceItem stDeviceInfo);

/******************************************************************************************************************************
*��������iSOC_GetDevicePresetPosInfoByIdx
*��  �ܣ�����������ȡ�豸Ԥ�õ���Ϣ
*��  ����
		[IN]		lTPSession			Ѳ��Ԥ�õ����Ự
		[IN OUT]	lpPresetPosInfo	��ȡ��Ԥ�õ���Ϣָ��
		[IN]		stDeviceInfo		�豸��Ϣ������豸��Ϣ��strIcmsSignΪ����lIcmsId=0����������豸�л�ȡ�������ָ���豸�л�ȡ
		[IN]		nIdx				����ֵ����0��ʼ
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDevicePresetPosInfoByIdx(IN ISOC_LONGPTR lTPSession,IN OUT LPST_PRESETPOSINFO lpPresetPosInfo,IN ST_DeviceItem stDeviceInfo,IN ISOC_INT nIdx);

/******************************************************************************************************************************
*��������iSOC_GetDevicePresetPosInfoByID
*��  �ܣ�����Ԥ�õ�ID��ȡ�豸Ԥ�õ���Ϣ
*��  ����
		[IN]		lTPSession			Ѳ��Ԥ�õ����Ự
		[IN]		stDeviceInfo		�豸��Ϣ�ṹ��
		[IN OUT]	lpPresetPosInfo	��ȡ��Ԥ�õ���Ϣָ��
		[IN]		nPresetPosID		Ԥ�õ�ID
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDevicePresetPosInfoByID(IN ISOC_LONGPTR lTPSession,IN ST_DeviceItem stDeviceInfo,IN OUT LPST_PRESETPOSINFO lpPresetPosInfo,IN ISOC_ID nPresetPosID);

/******************************************************************************************************************************
*��������iSOC_ControlDevicePresetPos
*��  �ܣ�����ָ���豸Ԥ�õ�
*��  ����
		[IN]		lTPSession		Ѳ��Ԥ�õ����Ự
		[IN]		nCtrlCode		������
					�μ�����ֵ��{INSERT_POINT=0,UPDATE_POINT,DELETE_POINT,GOTO_POINT,STOP_POINT}
		[IN]		stDeviceInfo	�豸��Ϣ
		[IN]		lpPresetPosInfo		Ԥ�õ���Ϣ
		[IN]		dwReseved		������
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע���˺���Ϊ�첽���������Ҫ��ȡ��׼ȷ�ķ��ؽ������Ҫ����iSOC_RegistDevicePresetPosUpdateNotifyע���첽�¼��ص�����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlDevicePresetPos(IN ISOC_LONGPTR lTPSession,IN ISOC_INT nCtrlCode,IN ST_DeviceItem stDeviceInfo,IN LPST_PRESETPOSINFO lpPresetPosInfo,IN ISOC_DWORDPTR dwReseved=0);

/******************************************************************************************************************************
*��������iSOC_ControlDeviceKeepPos
*��  �ܣ�����ָ���豸����λ
*��  ����
		[IN]		lTPSession		Ѳ��Ԥ�õ����Ự
		[IN]		nCtrlCode		������
					�μ�����ֵ��{SET_POS=0,GOTO_POS}
		[IN]		stDeviceInfo		�豸��Ϣ
		[IN]		KeepPosInfo		����λλ����Ϣ
		[IN]		dwReseved		������
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע���˺���Ϊ�첽���������Ҫ��ȡ��׼ȷ�ķ��ؽ������Ҫ����iSOC_RegistDevicePresetPosUpdateNotifyע���첽�¼��ص�����
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlDeviceKeepPos(IN ISOC_LONGPTR lTPSession,IN ISOC_INT nCtrlCode,IN ST_DeviceItem stDeviceInfo,IN ISOC_DWORDPTR dwReseved=0);

/******************************************************************************************************************************
*��������iSOC_RegisterDevicePresetPosNotifyCallback
*��  �ܣ�ע��Ԥ�õ��첽�����ص�����
*��  ����
		[IN]		lTPSession		Ѳ��Ԥ�õ����Ự
		[IN]		pCallback		�첽�����ص�����
		[IN]		dwCookie		�û�COOKIE
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterDevicePresetPosNotifyCallback(IN ISOC_LONGPTR lTPSession,IN iSOC_PresetPosInfoCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*��������iSOC_RemoveDevicePresetPosNotifyCallback
*��  �ܣ��Ƴ�Ԥ�õ��첽�����ص�����
*��  ����
		[IN]		lTPSession		Ѳ��Ԥ�õ����Ự
		[IN]		pCallback		�첽�����ص�����
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_RemoveDevicePresetPosNotifyCallback(IN ISOC_LONGPTR lTPSession,IN iSOC_PresetPosInfoCallback pCallback);


/******************************************************************************************************************************
*��������iSOC_GetGroupLoopManagerSession
*��  �ܣ���ȡ������Ѳ����Ự
*��  ����
		[IN OUT]	lpGroupSession	��ȡ�ķ�����Ѳ����Ự
		[IN]		lMCSession		�������ĻỰ
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_GetGroupLoopManagerSession(IN OUT ISOC_LONGPTR *lpGroupSession,IN ISOC_LONGPTR lMCSession);

/******************************************************************************************************************************
*��������iSOC_RegisterGroupLoopNotifyCallback
*��  �ܣ�ע�������Ѳ�첽�¼�֪ͨ�ص�����
*��  ����
		[IN]		lGroupSession	������Ѳ����Ự
		[IN]		pCallback		�첽�����ص�����
		[IN]		dwCookie		�û�COOKIE
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_RegisterGroupLoopNotifyCallback(IN ISOC_LONGPTR lGroupSession,IN iSOC_OperatorStateCallback pCallback,IN ISOC_DWORDPTR dwCookie);

/******************************************************************************************************************************
*��������iSOC_GetGroupLoopPlanInfo
*��  �ܣ���ȡ����ƻ���Ϣ
*��  ����
		[IN]		lGroupSession		������Ѳ����Ự
		[IN OUT]	strGroupPlanInfo	����ƻ���Ϣ
		*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_GetGroupLoopPlanInfo(IN ISOC_LONGPTR lGroupSession,IN OUT ISOC_STR strGroupPlanInfo);

/******************************************************************************************************************************
*��������iSOC_SetGroupLoopPlanInfo
*��  �ܣ����÷���ƻ���Ϣ
*��  ����
		[IN]		lGroupSession		������Ѳ����Ự
		[IN]		strGroupPlanInfo	����ƻ���Ϣ
		*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_SetGroupLoopPlanInfo(IN ISOC_LONGPTR lGroupSession,IN ISOC_STR strGroupPlanInfo);

/******************************************************************************************************************************
*��������iSOC_GetGroupLoopSurverySchemeInfo
*��  �ܣ�������Ѳ����ID��ȡ��Ѳ������Ϣ
*��  ����
		[IN]		lGroupSession				������Ѳ����Ự
		[IN]		nGroupSurveySchemeID		��Ѳ����ID
		[IN OUT]	strGroupSurverySchemeInfo	��Ѳ������Ϣ
		*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_GetGroupLoopSurverySchemeInfo(IN ISOC_LONGPTR lGroupSession,IN ISOC_ID nGroupSurveySchemeID,IN OUT ISOC_STR strGroupSurverySchemeInfo);

/******************************************************************************************************************************
*��������iSOC_SetGroupLoopSurverySchemeInfo
*��  �ܣ�������Ѳ������Ϣ
*��  ����
		[IN]		lGroupSession				������Ѳ����Ự
		[IN]		strGroupSurverySchemeInfo	��Ѳ������Ϣ
		*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_SetGroupLoopSurverySchemeInfo(IN ISOC_LONGPTR lGroupSession,IN ISOC_STR strGroupSurverySchemeInfo);

/******************************************************************************************************************************
*��������iSOC_DelGroupLoopSurverySchemeInfo
*��  �ܣ�������Ѳ����IDɾ��ָ����Ѳ����
*��  ����
		[IN]		lGroupSession			������Ѳ����Ự
		[IN]		nGroupSurveySchemeID	��Ѳ����ID
*����ֵ���ɹ��򷵻ش���0��ֵ�����ɹ��򷵻�С��0��ֵ
*��  ע��
******************************************************************************************************************************/
//iSOC_EXPORT_MODE ISOC_INT iSOC_DelGroupLoopSurverySchemeInfo(IN ISOC_LONGPTR lGroupSession,IN ISOC_ID nGroupSurveySchemeID);


/******************************************************************************************************************************
*��������iSOC_ControlPtzAperture
*��  �ܣ�����ָ���豸PTZ�Ĺ�Ȧ
*��  ����
		[IN]	lPtzCtrlSession		PTZ���ƻỰ
		[IN]	bApertureIn			��Ȧ�Ƿ���С
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ControlPtzAperture(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_BOOL bApertureIn);


/******************************************************************************************************************************
*��������iSOC_LockPtz
*��  �ܣ�����PTZ,��ֹ�����û�ת��
*��  ����
		[IN]	lPtzCtrlSession		PTZ���ƻỰ
		[IN]	nTime			    ������ʱ�䣬����Ϊ��λ
*����ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��ͨ��״̬�ص�������֪���Ƿ�ɹ�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_LockPtz(IN const ISOC_LONGPTR lPtzCtrlSession,IN ISOC_INT nTime);


/******************************************************************************************************************************
*��������iSOC_UnlockPtz
*��  �ܣ�����PTZ,���������û�ת��
*��  ����
		[IN]	lPtzCtrlSession		PTZ���ƻỰ
*����ֵ��ʧ�ܷ���С��0��ֵ��ʧ�ܺ���Ե���iSOC_GetLastErrorDes��lPtzCtrlSession�����ȡʧ������
*��  ע��ͨ��״̬�ص�������֪���Ƿ�ɹ�
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_UnlockPtz(IN const ISOC_LONGPTR lPtzCtrlSession);

#ifdef __cplusplus 
}
#endif
#endif