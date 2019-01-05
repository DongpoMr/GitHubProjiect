#pragma once
#include "iCMSP_SimpleLock.h"
#include "IBFISSerializeDataMemoryModel.h"
#include <unordered_map>
#include <vector>

typedef struct
{
	int  nUserSpace;   //�Ѿ�ʹ�õĿռ�
	int  nTotalSpace;  //������
}SERIALIZE_SPACE_INFO_STB;

#define MAX_ALLOCATION_SPACE  1024 * 1024 * 50  //100M
class XhBFISSerializeDataStationImp : public IBFISSerializeDataMemoryModel
{
public:
	XhBFISSerializeDataStationImp();
	~XhBFISSerializeDataStationImp();
public:
	//ÿһ����������ݸ���
	virtual ISOC_BOOL SetEachPackageStoredDataNumber(IN int nStoreNum);
	virtual int GetEachPackageStoredDataNumber();
	//����һ��KEY���ں������
	virtual int CreateKey();
	//����һ���ڴ�,����һ��KEY���ڷ��ʸ�����
	virtual int CreateDataPacket(IN int nSize, IN int nKey, OUT BYTE**pData);
	//���·����С������ԭ�������ݿ����µ��ڴ���
	virtual int ReallocatePacket(IN int nSize, IN int nKey, OUT BYTE **pData);
	//���ö�ӦKEY������Ϣ
	virtual ISOC_BOOL SetPacketInfo(IN int nKey, IN int nDataSize, IN int nDataCount);
	//��ȡ��������С�� SetEachPackageStoredDataNumber��С����δ����������ݰ�
	virtual ISOC_BOOL GetNotFullPacket(OUT int& nKey);
	//����ÿһ�����ݶ�Ӧ��ϵ������λ��,nKey ,nDataPos �����ڰ�������ݾ����λ��
	virtual ISOC_BOOL SetDataPacketPos(IN std::string strInfoKey, IN int nKey, IN int nDataPos);
	//��ȡ��ӦstrInfo���ݴ�ŵ������Ϣ
	virtual ISOC_BOOL GetDataPacketPos(IN std::string strInfo, OUT int& nKey, OUT int& nDataPos);
	//ɾ����Ӧkey��λ����Ϣ
	virtual ISOC_BOOL DelDataPacketPos(IN std::string strInfo);
	//����KEY��ȡ���ݵ�ַ�������ݴ�С��
	virtual ISOC_BOOL GetDataPacket(IN int nKey, OUT BYTE **pData, OUT int& nDataSize, OUT int& nTotalDataSize );
	//��ȡ���ĸ���
	virtual int GetPacketCount();
	virtual void clear();
	virtual iCMSP_WRLock *GetWRLock();

	//����ӿ� ����Ա��Ȩ����Ϣ����
    //����ÿһ�����ݶ�Ӧ��ϵ������λ��,nKey ,nDataPos �����ڰ�������ݾ����λ��
	virtual ISOC_BOOL SetDataPacketPos(IN std::string strInfoKey, IN std::string strInfoKey2, IN int nKey, IN int nDataPos);
	//����ӿ�����Ա��Ȩ����Ϣ(һ��Ա�������ж���Ȩ����Ϣ)
	virtual ISOC_BOOL GetDataPacketPos(IN std::string strInfo, OUT std::unordered_map<std::string, SERIALIZE_POS_INFO_STB>& mapDataPosInfo);
	//ɾ����Ӧkey��λ����Ϣ
	virtual ISOC_BOOL DelDataPacketPos(IN std::string strInfoKey, IN std::string strInfoKey2);
private:
	bool IsKeyValidCheck(int nKey);
private:
	std::unordered_map<std::string, std::unordered_map<std::string, SERIALIZE_POS_INFO_STB> > m_specialDataPosInfoMap;
	std::unordered_map<std::string, SERIALIZE_POS_INFO_STB>  m_dataPosInfoMap;
	std::unordered_map<int, SERIALIZE_SPACE_INFO_STB>       m_dataSpaceMap;
	std::unordered_map<int, int>                  m_dataNotFullPacke;        //��¼δ�����İ�(����λ�ã�������ݴ�С)
	std::vector<BYTE*>                            m_dataVec;                 //���ʵ������
	int                                           m_nStoreNum;
	iCMSP_SimpleCS                                m_csDataPosInfoMtx;
	iCMSP_SimpleCS                                m_csDataSpaceMtx;
	iCMSP_SimpleCS                                m_csDataNotFullPackeMtx;
	iCMSP_SimpleCS                                m_csDataVecMtx;
	iCMSP_SimpleCS                                m_csSpecialDataMapMtx;
	iCMSP_WRLock                                  m_csWRMtx;
};

