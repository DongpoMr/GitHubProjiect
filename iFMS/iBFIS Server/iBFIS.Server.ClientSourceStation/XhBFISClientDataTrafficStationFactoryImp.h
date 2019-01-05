#pragma once
#include "IFactory.h"

class XhBFISClientDataTrafficStationFactoryImp : public IFactory
{
public:
	XhBFISClientDataTrafficStationFactoryImp();
	~XhBFISClientDataTrafficStationFactoryImp();

	//根据对象类型编码创建对应的功能对象
	virtual CISocObject* CreateObject(ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved = NULL);
	//销毁对应的功能对象
	virtual ISOC_VOID ReleaseObject(CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved = NULL);
	//根据对应的对象类型，返回本工厂类是否可以创建对应类型的对象
	virtual ISOC_bool HasObjectInObjType(ISOC_UINT nObjType);
	//返回某个功能对象对某一业务的业务水平的高低值，越接近0的值所表示的水平越高，如果返回值为-1则说明不支持这种业务
	virtual ISOC_INT GetObjectFacilityLevel(ISOC_UINT nObjType,const ISOC_STR strFacilityDes);
};