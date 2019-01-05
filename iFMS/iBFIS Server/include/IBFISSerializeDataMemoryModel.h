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
	int  nPacketKey;   //数据所在那个KEY中
	int  nDataPos;     //对应KEY中数据具体位置
}SERIALIZE_POS_INFO_STB;

interface IBFISSerializeDataMemoryModel:public CISocObject
{
	IBFISSerializeDataMemoryModel()
	{
		m_nObjectType = OBJECT_TYPE_BFISSERVER_MIGRATETASKSTATION;
	}
	virtual ~IBFISSerializeDataMemoryModel(){};

	//每一个包存放数据个数,用来作为判断包是否是否是完整的一个包
	virtual ISOC_BOOL SetEachPackageStoredDataNumber(IN int nStoreNum) = 0;
	virtual int GetEachPackageStoredDataNumber() = 0;
	//产生一个KEY用于后面操作
	virtual int CreateKey() = 0;
	//为当前nKey分配一段内存,并返回地址
	virtual int CreateDataPacket(IN int nSize, IN int nKey, OUT BYTE**pData) = 0;
	//重新分配大小, nKey插入数据时，可能内存不足，重新分配
	virtual int ReallocatePacket(IN int nSize, IN int nKey, OUT BYTE **pData) = 0;
	//设置对应KEY数据信息nDataSize(填充的数据大小)nDataCount（当前包填充的数据个数）
	virtual ISOC_BOOL SetPacketInfo(IN int nKey, IN int nDataSize, IN int nDataCount) = 0;
	//获取包中数据小于 SetEachPackageStoredDataNumber大小就是未填充满的数据包
	virtual ISOC_BOOL GetNotFullPacket(OUT int& nKey) = 0;
	//设置每一条数据对应关系，所在位置,nKey包的位置 ,nDataPos数据在包中具体的位置
	virtual ISOC_BOOL SetDataPacketPos(IN std::string strInfoKey, IN int nKey, IN int nDataPos) = 0;
	//获取对应strInfoKey数据存放的相关信息
	virtual ISOC_BOOL GetDataPacketPos(IN std::string strInfoKey, OUT int& nKey, OUT int& nDataPos) = 0;
	//删除对应key的位置信息
	virtual ISOC_BOOL DelDataPacketPos(IN std::string strInfoKey) = 0;
	//根据KEY获取数据地址、和数据大小等nDataSize（数据使用的大小）nTotalDataSize当前包的内存分配的总大小
	virtual ISOC_BOOL GetDataPacket(IN int nKey, OUT BYTE **pData, OUT int& nDataSize, OUT int& nTotalDataSize) = 0;
	//获取包的个数
	virtual int GetPacketCount() = 0;
	virtual void clear() = 0;
	//GetDataPacket取出来的数据要与修改数据操作互斥
	virtual iCMSP_WRLock *GetWRLock() = 0;

	//特殊接口
	//strInfoKey对应很多条strInfoKey2为Key的数据，数据结构 std::unordered_map<std::string,std::unordered_map<std::string, SERIALIZE_POS_INFO_STB>>
	virtual ISOC_BOOL SetDataPacketPos(IN std::string strInfoKey, IN std::string strInfoKey2, IN int nKey, IN int nDataPos) = 0;
	//特殊接口用于员工权限信息(一个员工可以有多种权限信息)
	virtual ISOC_BOOL GetDataPacketPos(IN std::string strInfo, OUT std::unordered_map<std::string, SERIALIZE_POS_INFO_STB>& mapDataPosInfo) = 0;
	//删除对应key的位置信息
	virtual ISOC_BOOL DelDataPacketPos(IN std::string strInfoKey, IN std::string strInfoKey2) = 0;
};
