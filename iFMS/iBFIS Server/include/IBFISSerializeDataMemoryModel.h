#pragma once
#include "iSOCObject.h"
#include "iSOC_PrivateStructDefine.h"
#include "iBFIS_UniqueDefine.h"
#include "iCMSP_SimpleLock.h"
#include <unordered_map>
#include <string>
using namespace std;

typedef struct
{
	int  nPacketKey;   //���������Ǹ�KEY��
	int  nDataPos;     //��ӦKEY�����ݾ���λ��
}SERIALIZE_POS_INFO_STB;

interface IBFISSerializeDataMemoryModel:public CISocObject
{
	IBFISSerializeDataMemoryModel()
	{
		m_nObjectType = OBJECT_TYPE_BFISSERVER_MIGRATETASKSTATION;
	}
	virtual ~IBFISSerializeDataMemoryModel(){};

	//ÿһ����������ݸ���,������Ϊ�жϰ��Ƿ��Ƿ���������һ����
	virtual ISOC_BOOL SetEachPackageStoredDataNumber(IN int nStoreNum) = 0;
	virtual int GetEachPackageStoredDataNumber() = 0;
	//����һ��KEY���ں������
	virtual int CreateKey() = 0;
	//Ϊ��ǰnKey����һ���ڴ�,�����ص�ַ
	virtual int CreateDataPacket(IN int nSize, IN int nKey, OUT BYTE**pData) = 0;
	//���·����С, nKey��������ʱ�������ڴ治�㣬���·���
	virtual int ReallocatePacket(IN int nSize, IN int nKey, OUT BYTE **pData) = 0;
	//���ö�ӦKEY������ϢnDataSize(�������ݴ�С)nDataCount����ǰ���������ݸ�����
	virtual ISOC_BOOL SetPacketInfo(IN int nKey, IN int nDataSize, IN int nDataCount) = 0;
	//��ȡ��������С�� SetEachPackageStoredDataNumber��С����δ����������ݰ�
	virtual ISOC_BOOL GetNotFullPacket(OUT int& nKey) = 0;
	//����ÿһ�����ݶ�Ӧ��ϵ������λ��,nKey����λ�� ,nDataPos�����ڰ��о����λ��
	virtual ISOC_BOOL SetDataPacketPos(IN std::string strInfoKey, IN int nKey, IN int nDataPos) = 0;
	//��ȡ��ӦstrInfoKey���ݴ�ŵ������Ϣ
	virtual ISOC_BOOL GetDataPacketPos(IN std::string strInfoKey, OUT int& nKey, OUT int& nDataPos) = 0;
	//ɾ����Ӧkey��λ����Ϣ
	virtual ISOC_BOOL DelDataPacketPos(IN std::string strInfoKey) = 0;
	//����KEY��ȡ���ݵ�ַ�������ݴ�С��nDataSize������ʹ�õĴ�С��nTotalDataSize��ǰ�����ڴ������ܴ�С
	virtual ISOC_BOOL GetDataPacket(IN int nKey, OUT BYTE **pData, OUT int& nDataSize, OUT int& nTotalDataSize) = 0;
	//��ȡ���ĸ���
	virtual int GetPacketCount() = 0;
	virtual void clear() = 0;
	//GetDataPacketȡ����������Ҫ���޸����ݲ�������
	virtual iCMSP_WRLock *GetWRLock() = 0;

	//����ӿ�
	//strInfoKey��Ӧ�ܶ���strInfoKey2ΪKey�����ݣ����ݽṹ std::unordered_map<std::string,std::unordered_map<std::string, SERIALIZE_POS_INFO_STB>>
	virtual ISOC_BOOL SetDataPacketPos(IN std::string strInfoKey, IN std::string strInfoKey2, IN int nKey, IN int nDataPos) = 0;
	//����ӿ�����Ա��Ȩ����Ϣ(һ��Ա�������ж���Ȩ����Ϣ)
	virtual ISOC_BOOL GetDataPacketPos(IN std::string strInfo, OUT std::unordered_map<std::string, SERIALIZE_POS_INFO_STB>& mapDataPosInfo) = 0;
	//ɾ����Ӧkey��λ����Ϣ
	virtual ISOC_BOOL DelDataPacketPos(IN std::string strInfoKey, IN std::string strInfoKey2) = 0;
};
