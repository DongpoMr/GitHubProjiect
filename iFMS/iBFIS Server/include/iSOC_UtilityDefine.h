#pragma once
#ifndef _ISOC_UTILITYDEFINE_H_
#define _ISOC_UTILITYDEFINE_H_
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


#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************************************************
*��������iSOC_GetDataListItemCount
*��  �ܣ���ȡ��Ӧ�������������ݸ���
*��  ����
		 [IN] lDataListHead ��������ͷ��ʶ
*����ֵ�������������������ݸ��������С��0���ʾ����ʧ�ܣ���ʹ��iSOC_GetLastErrorDes��lDataListHead�����ȡʧ��ԭ��
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDataListItemCount(IN const ISOC_LONGPTR lDataListHead);

/******************************************************************************************************************************
*��������iSOC_GetFirstDataListItem
*��  �ܣ���ȡ���������е�һ������
*��  ����
		 [IN] lDataListHead ��������ͷ��ʶ
		 [IN OUT] pDataListItem ��������ָ�룬���Զ�Ӧ������Ľṹ��
		 [IN OUT] nDataItemLen �������򳤶�
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܿ�ʹ��iSOC_GetLastErrorDes��lDataListHead�����ȡʧ��ԭ��
*��  ע����ȡ��һ�����ݺ��ڲ���Ӧ����ָ����ƶ�����һ��������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetFirstDataListItem(IN const ISOC_LONGPTR lDataListHead,IN OUT ISOC_VOID* pDataListItem,IN OUT ISOC_INT& nDataItemLen);

/******************************************************************************************************************************
*��������iSOC_GetLastDataListItem
*��  �ܣ���ȡ�������������һ������
*��  ����
		 [IN] lDataListHead ��������ͷ��ʶ
		 [IN OUT] pDataListItem ��������ָ�룬���Զ�Ӧ������Ľṹ��
		 [IN OUT] nDataItemLen �������򳤶�
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܿ�ʹ��iSOC_GetLastErrorDes��lDataListHead�����ȡʧ��ԭ��
*��  ע����ȡ���һ�����ݺ��ڲ���Ӧ����ָ����ƶ������һ��������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLastDataListItem(IN const ISOC_LONGPTR lDataListHead,IN OUT ISOC_VOID* pDataListItem,IN OUT ISOC_INT& nDataItemLen);

/******************************************************************************************************************************
*��������iSOC_GetNextDataListItem
*��  �ܣ���ȡ��һ������
*��  ����
		 [IN] lDataListHead ��������ͷ��ʶ
		 [IN OUT] pDataListItem ��������ָ�룬���Զ�Ӧ������Ľṹ��
		 [IN OUT] nDataItemLen �������򳤶�
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܿ�ʹ��iSOC_GetLastErrorDes��lDataListHead�����ȡʧ��ԭ��
*��  ע����ȡ��һ�����ݺ��ڲ���Ӧ����ָ����ƶ�����һ��������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetNextDataListItem(IN const ISOC_LONGPTR lDataListHead,IN OUT ISOC_VOID* pDataListItem,IN OUT ISOC_INT& nDataItemLen);

/******************************************************************************************************************************
*��������iSOC_GetPrevDataListItem
*��  �ܣ���ȡ��һ������
*��  ����
		 [IN] lDataListHead ��������ͷ��ʶ
		 [IN OUT] pDataListItem ��������ָ�룬���Զ�Ӧ������Ľṹ��
		 [IN OUT] nDataItemLen �������򳤶�
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ��������ʧ�ܿ�ʹ��iSOC_GetLastErrorDes��lDataListHead�����ȡʧ��ԭ��
*��  ע����ȡ��һ�����ݺ��ڲ���Ӧ����ָ����ƶ�����һ��������
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetPrevDataListItem(IN const ISOC_LONGPTR lDataListHead,IN OUT ISOC_VOID* pDataListItem,IN OUT ISOC_INT& nDataItemLen);

/******************************************************************************************************************************
*��������iSOC_IsDataListEOF
*��  �ܣ��ж��Ƿ��Ѿ�������Ľ�β
*��  ����
		 [IN] lDataListHead ��������ͷ��ʶ
*����ֵ�����Ѿ�������Ľ�β�򷵻�ISOC_TRUE�����򷵻�ISOC_FALSE
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_BOOL iSOC_IsDataListEOF(IN const ISOC_LONGPTR lDataListHead);


/******************************************************************************************************************************
*��������iSOC_GetLastErrorDes
*��  �ܣ���ȡ��Ӧ�Ự��ʶ�����һ����������
*��  ����
		 [IN] lSession ��Ӧ�ı�ʶ�����Ϊ�����ʾΪ��ȡȫ�ִ�������
		 [OUT] ppStrErrDes ��������
		 [OUT] nStrLen ������������
*����ֵ�����óɹ����ش���0��ֵ������ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLastErrorDes(IN const ISOC_LONGPTR lSession,OUT ISOC_STR* ppStrErrDes,OUT ISOC_INT& nStrLen);


/******************************************************************************************************************************
*��������iSOC_CastPTS2SystemTime
*��  �ܣ���ʱ���ת��ΪISOC_SYSTEM�ṹ��
*��  ����
		 [IN] uPTS ʱ���
		 [IN OUT] pSysTime ISOC_SYSTEM�ṹ��ָ��
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CastPTS2SystemTime(IN const ISOC_UINT64 uPTS,IN OUT ISOC_SYSTEMTIME* pSysTime);

/******************************************************************************************************************************
*��������iSOC_CastSystemTime2PTS
*��  �ܣ���ISOC_SYSTEM�ṹ���Ӧ��ֵת���ɶ�Ӧ��ISOC_UINT64���͵�PTS
*��  ����
		 [IN] stSystemTime ��Ҫת����ISOC_SYSTEM�ṹ��
		 [IN OUT] pPTS ת�������PTSָ��
*����ֵ���ɹ����ش���0��ֵ��ʧ�ܷ���С��0��ֵ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CastSystemTime2PTS(IN const ISOC_SYSTEMTIME stSystemTime,IN OUT ISOC_UINT64* pPTS);

/******************************************************************************************************************************
*��������iSOC_SetLogNeedWriteFile
*��  �ܣ�������־�Ƿ�д����־�ļ���
*��  ����
		 [IN] bIsWriteFile ָʾ�Ƿ���־д���ļ��ı���
*����ֵ����
*��  ע��Ĭ��Ϊ������־д���ļ�����ͨ��WinDbg�鿴��־
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_VOID iSOC_SetLogNeedWriteFile(IN ISOC_BOOL bIsWriteFile);

/******************************************************************************************************************************
*��������iSOC_CopyMemory
*��  �ܣ��ڴ濽������
*��  ����
		 [IN] pDest Ŀ�����ݵ�ַ
		 [IN] pSrc	Դ���ݵ�ַ
		 [IN] nSize ���������ݴ�С
*����ֵ������Ŀ�����ݵĵ�ַ
*��  ע��
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_VOID* iSOC_CopyMemory(IN ISOC_VOID* pDest,IN ISOC_VOID* pSrc,IN ISOC_INT nSize);

#ifdef __cplusplus
}

#endif
#endif