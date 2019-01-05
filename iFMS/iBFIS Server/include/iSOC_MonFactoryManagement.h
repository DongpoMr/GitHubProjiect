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

	//��ʼ�����������
	ISOC_INT InitFactories();
	//����ʼ�����������
	ISOC_INT UnInitFactories();

	//����ָ�����͵Ķ���
	CISocObject* CreateObject(const ISOC_UINT nObjectType,const ISOC_STR strFacilityDes,const ISOC_STR strFunction,ISOC_DWORDPTR dwReserved=ISOC_NULL);
	//����ָ������
	ISOC_INT ReleaseObject(CISocObject** ppObject,const ISOC_STR strFunction,ISOC_DWORDPTR dwReserved=NULL);
	//�жϹ��������Ķ����Ƿ����
	ISOC_BOOL CheckObjectCanBeUse(CISocObject* pObject);
	//���ָ���Ķ�̬����������ĿǰĬ��֧��_T("\\isoc.sdk.*.dll"),_T("\\isoc.dcs.*.dll"),_T("\\isoc.mat.*.dll"),_T("\\ismp.mat.*.dll")���֣��˺�����init֮ǰ����
	ISOC_INT  AddSearchDll(ISOC_STR strDllName);
	//�����ܴ���ָ�����Ͷ�Ӧ�Ĺ������ϣ����pFactoryListΪ����pListSize��������Ҫ��Ĺ������������
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
