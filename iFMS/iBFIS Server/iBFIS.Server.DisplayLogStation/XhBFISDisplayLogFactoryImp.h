#pragma once
#include "IFactory.h"
#include "XhBFISDisplayLogStationImp.h"

class XhBFISDisplayLogFactoryImp :
	public IFactory
{
public:
	XhBFISDisplayLogFactoryImp(void);
	~XhBFISDisplayLogFactoryImp(void);

	//���ݶ������ͱ��봴����Ӧ�Ĺ��ܶ���
	virtual CISocObject* CreateObject(ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved = NULL);
	//���ٶ�Ӧ�Ĺ��ܶ���
	virtual ISOC_VOID ReleaseObject(CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved = NULL);
	//���ݶ�Ӧ�Ķ������ͣ����ر��������Ƿ���Դ�����Ӧ���͵Ķ���
	virtual ISOC_bool HasObjectInObjType(ISOC_UINT nObjType);
	//����ĳ�����ܶ����ĳһҵ���ҵ��ˮƽ�ĸߵ�ֵ��Խ�ӽ�0��ֵ����ʾ��ˮƽԽ�ߣ��������ֵΪ-1��˵����֧������ҵ��
	virtual ISOC_INT GetObjectFacilityLevel(ISOC_UINT nObjType,const ISOC_STR strFacilityDes);

private:
	XhBFSDisplayLogStationImp* m_pDisplayLogStation;
};

