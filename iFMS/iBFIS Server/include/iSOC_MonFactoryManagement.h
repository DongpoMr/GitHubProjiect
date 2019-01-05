#pragma once

#include "iSocObject.h"
#ifdef _iSOC_ADD_IN_MANAGEMENT_SDK
#define iSOC_ADD_IN_MANAGEMENT_MODE __declspec(dllexport)
#else
#define iSOC_ADD_IN_MANAGEMENT_MODE __declspec(dllimport)
#endif


#ifndef _iSOC_ADD_IN_MANAGEMENT_SDK
#ifdef _DEBUG
#ifdef _UNICODE
#pragma comment(lib,"isoc.sdk.addinmanagementud.lib")
#else
#pragma comment(lib,"isoc.sdk.addinmanagementd.lib")
#endif
#else
#ifdef _UNICODE
#pragma comment(lib,"isoc.sdk.addinmanagementu.lib")
#else
#pragma comment(lib,"isoc.sdk.addinmanagement.lib")
#endif			
#endif
#endif

class iSOC_ADD_IN_MANAGEMENT_MODE iSOC_MonFactoryManagement :
	public CISocObject
{
public:
	iSOC_MonFactoryManagement(void);
	~iSOC_MonFactoryManagement(void);

	//初始化插件管理类
	ISOC_INT InitFactories();
	//反初始化插件管理类
	ISOC_INT UnInitFactories();

	//创建指定类型的对象
	CISocObject* CreateObject(const ISOC_UINT nObjectType,const ISOC_STR strFacilityDes,const ISOC_STR strFunction,ISOC_DWORDPTR dwReserved=ISOC_NULL);
	//销毁指定对象
	ISOC_INT ReleaseObject(CISocObject** ppObject,const ISOC_STR strFunction,ISOC_DWORDPTR dwReserved=NULL);
	//判断工厂创建的对象是否可用
	ISOC_BOOL CheckObjectCanBeUse(CISocObject* pObject);
	//添加指定的动态库特征名，目前默认支持_T("\\isoc.sdk.*.dll"),_T("\\isoc.dcs.*.dll"),_T("\\isoc.mat.*.dll"),_T("\\ismp.mat.*.dll")三种，此函数在init之前调用
	ISOC_INT  AddSearchDll(ISOC_STR strDllName);
	//返回能创建指定类型对应的工厂集合，如果pFactoryList为空则pListSize返回满足要求的工厂对象个数，
	ISOC_INT GetFactoryList(CISocObject** pFactoryList, ISOC_INT* pListSize, const ISOC_UINT nObjectType, const ISOC_STR strFacilityDes, const ISOC_BOOL bOnlyUseObjectType = TRUE);
};


template <typename T>
T* iSOC_CreateObject(const ISOC_UINT nObjectType, const ISOC_STR strFacilityDes, const ISOC_STR strFunction, ISOC_DWORDPTR dwReserved = ISOC_NULL)
{
	iSOC_MonFactoryManagement fmt;
	CISocObject* pObj = fmt.CreateObject(nObjectType, strFacilityDes, strFunction, dwReserved);
	return static_cast<T*>(pObj);
}

template <typename T>
ISOC_INT iSOC_ReleaseObject(T** ppObject, const ISOC_STR strFunction, ISOC_DWORDPTR dwReserved = NULL)
{
	iSOC_MonFactoryManagement fmt;
	return fmt.ReleaseObject(reinterpret_cast<CISocObject**>(ppObject), strFunction, dwReserved);
}

inline ISOC_BOOL iSOC_CheckObjectCanBeUse(CISocObject* pObject)
{
	iSOC_MonFactoryManagement fmt;
	return fmt.CheckObjectCanBeUse(pObject);
}
