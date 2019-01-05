#pragma once
#ifndef _ISOC_DATATYPE_DEFIINE_H_
#define _ISOC_DATATYPE_DEFIINE_H_

//////////////////////////////////////
//根据类型定义
//////////////////////////////////////

#define ISOC_INT		int
#define ISOC_STR		TCHAR*
#define ISOC_DWORD		unsigned long
#define ISOC_DWORDPTR	DWORD_PTR
#define ISOC_BOOL		int
#define ISOC_CHAR		TCHAR
#define ISOC_FLOAT		float
#define ISOC_DOUBLE		double
#define ISOC_INT64		signed __int64
#define ISOC_UINT64		unsigned __int64
#define ISOC_BYTE		unsigned char
#define ISOC_WORD		unsigned short
#define ISOC_UINT		unsigned int
#define ISOC_SHORT		short
#define ISOC_VOID		void
#define ISOC_bool		bool
#define ISOC_LONG		long
#define ISOC_LONGPTR    LONG_PTR
#define	ISOC_HWND		HWND
#define ISOC_SYSTEMTIME	SYSTEMTIME
#define	ISOC_RECT		RECT
#define ISOC_SIZE_T		size_t
#define ISOC_INTPTR     INT_PTR

//////////////////////////////////////
//根据功能定义
//////////////////////////////////////
#define ISOC_ID			ISOC_INT


//////////////////////////////////////
//根据值定义
//////////////////////////////////////
#define ISOC_TRUE		1
#define ISOC_FALSE		0
#define ISOC_true		true
#define ISOC_false		false
#define ISOC_OK			ISOC_TRUE
#define ISOC_FAIL		ISOC_FALSE
#define ISOC_NULL		0



//////////////////////////////////////
//结构体定义
//////////////////////////////////////

typedef struct ST_SIZE
{
	ISOC_INT nCX;
	ISOC_INT nCY;
} ISOC_SIZE;

typedef struct ST_POINT
{
	ISOC_INT nX;
	ISOC_INT nY;
}	ISOC_POINT;



//////////////////////////////////////
//服务器类型定义
//////////////////////////////////////

#define ICMS8000_SERVER "ICMS8000_SERVER"
#define ICMS6000_SERVER "ICMS6000_SERVER"
#define ISIS8000_SERVER "ISIS8000_SERVER"
#define ISIS8000_SERVER_20V "ISIS8000_SERVER_2.0"
#define	ILNVR_SERVER	"ILNVR_SERVER"
#define ISMP_SERVER		"ISMP_SERVER"
#define IPGS_SERVER		"IPGS_SERVER"
#define SOBEY_SERVER	"SOBEY_SERVER" //sobey安防服务器，传此参数后可有sdk自动识别所登录服务器类型
#define	UNKNOWN_SERVER	"UNKNOWN_SERVER"

#endif