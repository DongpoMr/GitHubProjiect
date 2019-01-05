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
*函数名：iSOC_GetDataListItemCount
*功  能：获取对应数据链表中数据个数
*参  数：
		 [IN] lDataListHead 数据链表头标识
*返回值：返回数据链表中数据个数，如果小于0则表示调用失败，可使用iSOC_GetLastErrorDes将lDataListHead传入获取失败原因
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetDataListItemCount(IN const ISOC_LONGPTR lDataListHead);

/******************************************************************************************************************************
*函数名：iSOC_GetFirstDataListItem
*功  能：获取数据链表中第一个数据
*参  数：
		 [IN] lDataListHead 数据链表头标识
		 [IN OUT] pDataListItem 数据区域指针，可以对应到具体的结构体
		 [IN OUT] nDataItemLen 数据区域长度
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败可使用iSOC_GetLastErrorDes将lDataListHead传入获取失败原因
*备  注：获取第一个数据后内部对应数据指针就移动到第一个数据上
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetFirstDataListItem(IN const ISOC_LONGPTR lDataListHead,IN OUT ISOC_VOID* pDataListItem,IN OUT ISOC_INT& nDataItemLen);

/******************************************************************************************************************************
*函数名：iSOC_GetLastDataListItem
*功  能：获取数据链表中最后一个数据
*参  数：
		 [IN] lDataListHead 数据链表头标识
		 [IN OUT] pDataListItem 数据区域指针，可以对应到具体的结构体
		 [IN OUT] nDataItemLen 数据区域长度
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败可使用iSOC_GetLastErrorDes将lDataListHead传入获取失败原因
*备  注：获取最后一个数据后内部对应数据指针就移动到最后一个数据上
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLastDataListItem(IN const ISOC_LONGPTR lDataListHead,IN OUT ISOC_VOID* pDataListItem,IN OUT ISOC_INT& nDataItemLen);

/******************************************************************************************************************************
*函数名：iSOC_GetNextDataListItem
*功  能：获取下一个数据
*参  数：
		 [IN] lDataListHead 数据链表头标识
		 [IN OUT] pDataListItem 数据区域指针，可以对应到具体的结构体
		 [IN OUT] nDataItemLen 数据区域长度
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败可使用iSOC_GetLastErrorDes将lDataListHead传入获取失败原因
*备  注：获取下一个数据后内部对应数据指针就移动到下一个数据上
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetNextDataListItem(IN const ISOC_LONGPTR lDataListHead,IN OUT ISOC_VOID* pDataListItem,IN OUT ISOC_INT& nDataItemLen);

/******************************************************************************************************************************
*函数名：iSOC_GetPrevDataListItem
*功  能：获取上一个数据
*参  数：
		 [IN] lDataListHead 数据链表头标识
		 [IN OUT] pDataListItem 数据区域指针，可以对应到具体的结构体
		 [IN OUT] nDataItemLen 数据区域长度
*返回值：调用成功返回大于0的值，调用失败返回小于0的值，若调用失败可使用iSOC_GetLastErrorDes将lDataListHead传入获取失败原因
*备  注：获取上一个数据后内部对应数据指针就移动到上一个数据上
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetPrevDataListItem(IN const ISOC_LONGPTR lDataListHead,IN OUT ISOC_VOID* pDataListItem,IN OUT ISOC_INT& nDataItemLen);

/******************************************************************************************************************************
*函数名：iSOC_IsDataListEOF
*功  能：判断是否已经到链表的结尾
*参  数：
		 [IN] lDataListHead 数据链表头标识
*返回值：若已经到链表的结尾则返回ISOC_TRUE，否则返回ISOC_FALSE
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_BOOL iSOC_IsDataListEOF(IN const ISOC_LONGPTR lDataListHead);


/******************************************************************************************************************************
*函数名：iSOC_GetLastErrorDes
*功  能：获取对应会话标识的最后一个错误描述
*参  数：
		 [IN] lSession 对应的标识，如果为空则表示为获取全局错误描述
		 [OUT] ppStrErrDes 错误描述
		 [OUT] nStrLen 错误描述长度
*返回值：调用成功返回大于0的值，调用失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_GetLastErrorDes(IN const ISOC_LONGPTR lSession,OUT ISOC_STR* ppStrErrDes,OUT ISOC_INT& nStrLen);


/******************************************************************************************************************************
*函数名：iSOC_CastPTS2SystemTime
*功  能：将时间戳转换为ISOC_SYSTEM结构体
*参  数：
		 [IN] uPTS 时间戳
		 [IN OUT] pSysTime ISOC_SYSTEM结构体指针
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CastPTS2SystemTime(IN const ISOC_UINT64 uPTS,IN OUT ISOC_SYSTEMTIME* pSysTime);

/******************************************************************************************************************************
*函数名：iSOC_CastSystemTime2PTS
*功  能：将ISOC_SYSTEM结构体对应的值转换成对应的ISOC_UINT64类型的PTS
*参  数：
		 [IN] stSystemTime 需要转换的ISOC_SYSTEM结构体
		 [IN OUT] pPTS 转换过后的PTS指针
*返回值：成功返回大于0的值，失败返回小于0的值
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_INT iSOC_CastSystemTime2PTS(IN const ISOC_SYSTEMTIME stSystemTime,IN OUT ISOC_UINT64* pPTS);

/******************************************************************************************************************************
*函数名：iSOC_SetLogNeedWriteFile
*功  能：设置日志是否写入日志文件中
*参  数：
		 [IN] bIsWriteFile 指示是否将日志写入文件的变量
*返回值：无
*备  注：默认为不将日志写入文件，可通过WinDbg查看日志
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_VOID iSOC_SetLogNeedWriteFile(IN ISOC_BOOL bIsWriteFile);

/******************************************************************************************************************************
*函数名：iSOC_CopyMemory
*功  能：内存拷贝函数
*参  数：
		 [IN] pDest 目标数据地址
		 [IN] pSrc	源数据地址
		 [IN] nSize 拷贝的数据大小
*返回值：返回目标数据的地址
*备  注：
******************************************************************************************************************************/
iSOC_EXPORT_MODE ISOC_VOID* iSOC_CopyMemory(IN ISOC_VOID* pDest,IN ISOC_VOID* pSrc,IN ISOC_INT nSize);

#ifdef __cplusplus
}

#endif
#endif