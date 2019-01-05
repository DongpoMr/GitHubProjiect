#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOC_PublicStructDefine.h"
#include "iSOC_UnitDefine.h"


//////////////////////////////////////////////////¼��ģ��ӿڵĶ���/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

//����¼��Session
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateRecordSession(IN OUT ISOC_LONGPTR* lRecordSession, IN ISOC_LONGPTR lMCSession, IN ISOC_DWORDPTR dwReserved = 0);

//����¼��Session
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseRecordSession(IN  ISOC_LONGPTR lRecordSession, IN ISOC_DWORDPTR dwReserved = 0);

//�����ֶ�¼��
iSOC_EXPORT_MODE ISOC_INT iSOC_RecordControl(IN ISOC_LONGPTR lRecordSession, IN ST_DeviceItem* recordDevide, IN iSOC_OperatorStateCallback pCallback = NULL, IN ISOC_BOOL bStart = ISOC_TRUE, ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

//��ѯ¼��״̬
iSOC_EXPORT_MODE ISOC_INT iSOC_QueryRecordStatus(IN ISOC_LONGPTR lRecordSession, IN ST_DeviceItem* queryDevice, IN iSOC_RecordQueryCallback pCallback = NULL, IN ISOC_DWORDPTR dwCookie = 0, IN ISOC_DWORDPTR dwReserved = 0);

//����¼�񱣴�����
iSOC_EXPORT_MODE ISOC_INT iSOC_SetRecordSaveDay(IN ISOC_LONGPTR lRecordSession, IN ISOC_UINT uSaveDay, IN ISOC_DWORDPTR dwReserved = 0 );
 
#ifdef __cplusplus
}
#endif