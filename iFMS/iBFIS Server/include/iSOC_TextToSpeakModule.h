#pragma once
#include "iSOC_UnitDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_CreateTTSSession
*��  �ܣ��������������Ķ��Ự
*��  ����
		[IN OUT] pLTTSSession   ���������Ķ��Ự��ʶ
		[IN] dwReserved         ��չֵ����Ϊ0
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע���ڲ�ʹ�ô˻Ự��һ��Ҫʹ��iSOC_ReleaseLiveSession����ʵʱ�Ự���٣���Ȼ�������ڴ�й©
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CreateTTSSession(IN OUT ISOC_LONGPTR* pLTTSSession,IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_TTSSpeak
*��  �ܣ������Ķ�
*��  ����
		[IN] lTTSSession        ���������Ķ��Ự��ʶ
		[IN] strText            ��Ҫ�Ķ����ַ���
		[IN] nTextLen           �ַ�������
		[IN] dwReserved         ��չֵ����Ϊ0
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע���ڲ�ʹ�ô˻Ự��һ��Ҫʹ��iSOC_ReleaseLiveSession����ʵʱ�Ự���٣���Ȼ�������ڴ�й©
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_TTSSpeak(IN ISOC_LONGPTR lTTSSession, IN const ISOC_STR strText, IN ISOC_INT nTextLen, IN ISOC_DWORDPTR dwReserved = 0);

/******************************************************************************************************************************
*��������iSOC_ReleaseTTSSession
*��  �ܣ��������������Ķ��Ự
*��  ����
        [IN OUT] pLTTSSession   ���������Ķ��Ự��ʶ
        [IN] dwReserved         ��չֵ����Ϊ0
*����ֵ�����óɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע���ڲ�ʹ�ô˻Ự��һ��Ҫʹ��iSOC_ReleaseLiveSession����ʵʱ�Ự���٣���Ȼ�������ڴ�й©
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_ReleaseTTSSession(IN ISOC_LONGPTR lTTSSession, IN ISOC_DWORDPTR dwReserved = 0);

#ifdef __cplusplus
}
#endif
