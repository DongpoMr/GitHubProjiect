#pragma once
#include "iSOC_Datatype_Define.h"
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
interface IFactory : public CISocObject //�����ӿڣ������й�����ĸ���
{
public:
	IFactory()
	{
		m_nObjectType = OBJECT_TYPE_FACTORY;
	}
	virtual ~IFactory(){};
	//���ݶ������ͱ��봴����Ӧ�Ĺ��ܶ���
	virtual CISocObject* CreateObject(ISOC_UINT nObjType,const ISOC_STR strFacilityDes,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved = NULL) = 0;
	//���ٶ�Ӧ�Ĺ��ܶ���
	virtual ISOC_VOID ReleaseObject(CISocObject** ppObj,const ISOC_STR pFunction,ISOC_DWORDPTR dwReserved = NULL) = 0;
	//���ݶ�Ӧ�Ķ������ͣ����ر��������Ƿ���Դ�����Ӧ���͵Ķ���
	virtual ISOC_bool HasObjectInObjType(ISOC_UINT nObjType) = 0;
	//����ĳ�����ܶ����ĳһҵ���ҵ��ˮƽ�ĸߵ�ֵ��Խ�ӽ�0��ֵ����ʾ��ˮƽԽ�ߣ��������ֵΪ-1��˵����֧������ҵ��
	virtual ISOC_INT GetObjectFacilityLevel(ISOC_UINT nObjType,const ISOC_STR strFacilityDes) = 0;
};