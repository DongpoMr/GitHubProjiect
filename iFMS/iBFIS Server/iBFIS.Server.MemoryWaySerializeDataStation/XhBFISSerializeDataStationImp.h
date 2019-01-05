#pragma once
#include "iCMSP_SimpleLock.h"
#include "IBFISSerializeDataMemoryModel.h"
#include <unordered_map>
#include <vector>

typedef struct
{
	int  nUserSpace;   //已经使用的空间
	int  nTotalSpace;  //总容量
}SERIALIZE_SPACE_INFO_STB;

#define MAX_ALLOCATION_SPACE  1024 * 1024 * 50  //100M
class XhBFISSerializeDataStationImp : public IBFISSerializeDataMemoryModel
{
public:
	XhBFISSerializeDataStationImp();
	~XhBFISSerializeDataStationImp();
public:
	//每一个包存放数据个数
	virtual ISOC_BOOL SetEachPackageStoredDataNumber(IN int nStoreNum);
	virtual int GetEachPackageStoredDataNumber();
	//产生一个KEY用于后面操作
	virtual int CreateKey();
	//分配一段内存,产生一个KEY用于访问改数据
	virtual int CreateDataPacket(IN int nSize, IN int nKey, OUT BYTE**pData);
	//重新分配大小，并把原来的数据拷贝新的内存中
	virtual int ReallocatePacket(IN int nSize, IN int nKey, OUT BYTE **pData);
	//设置对应KEY数据信息
	virtual ISOC_BOOL SetPacketInfo(IN int nKey, IN int nDataSize, IN int nDataCount);
	//获取包中数据小于 SetEachPackageStoredDataNumber大小就是未填充满的数据包
	virtual ISOC_BOOL GetNotFullPacket(OUT int& nKey);
	//设置每一条数据对应关系，所在位置,nKey ,nDataPos 数据在包或段数据具体的位置
	virtual ISOC_BOOL SetDataPacketPos(IN std::string strInfoKey, IN int nKey, IN int nDataPos);
	//获取对应strInfo数据存放的相关信息
	virtual ISOC_BOOL GetDataPacketPos(IN std::string strInfo, OUT int& nKey, OUT int& nDataPos);
	//删除对应key的位置信息
	virtual ISOC_BOOL DelDataPacketPos(IN std::string strInfo);
	//根据KEY获取数据地址、和数据大小等
	virtual ISOC_BOOL GetDataPacket(IN int nKey, OUT BYTE **pData, OUT int& nDataSize, OUT int& nTotalDataSize );
	//获取包的个数
	virtual int GetPacketCount();
	virtual void clear();
	virtual iCMSP_WRLock *GetWRLock();

	//特殊接口 用于员工权限信息设置
    //设置每一条数据对应关系，所在位置,nKey ,nDataPos 数据在包或段数据具体的位置
	virtual ISOC_BOOL SetDataPacketPos(IN std::string strInfoKey, IN std::string strInfoKey2, IN int nKey, IN int nDataPos);
	//特殊接口用于员工权限信息(一个员工可以有多种权限信息)
	virtual ISOC_BOOL GetDataPacketPos(IN std::string strInfo, OUT std::unordered_map<std::string, SERIALIZE_POS_INFO_STB>& mapDataPosInfo);
	//删除对应key的位置信息
	virtual ISOC_BOOL DelDataPacketPos(IN std::string strInfoKey, IN std::string strInfoKey2);
private:
	bool IsKeyValidCheck(int nKey);
private:
	std::unordered_map<std::string, std::unordered_map<std::string, SERIALIZE_POS_INFO_STB> > m_specialDataPosInfoMap;
	std::unordered_map<std::string, SERIALIZE_POS_INFO_STB>  m_dataPosInfoMap;
	std::unordered_map<int, SERIALIZE_SPACE_INFO_STB>       m_dataSpaceMap;
	std::unordered_map<int, int>                  m_dataNotFullPacke;        //记录未填满的包(包的位置，存放数据大小)
	std::vector<BYTE*>                            m_dataVec;                 //存放实际数据
	int                                           m_nStoreNum;
	iCMSP_SimpleCS                                m_csDataPosInfoMtx;
	iCMSP_SimpleCS                                m_csDataSpaceMtx;
	iCMSP_SimpleCS                                m_csDataNotFullPackeMtx;
	iCMSP_SimpleCS                                m_csDataVecMtx;
	iCMSP_SimpleCS                                m_csSpecialDataMapMtx;
	iCMSP_WRLock                                  m_csWRMtx;
};

