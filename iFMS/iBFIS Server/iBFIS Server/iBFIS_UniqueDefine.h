#pragma once
#ifndef _IBFIS_UNIQUE_DEFINE_H_
#define _IBFIS_UNIQUE_DEFINE_H_
#include <string>
#include <vector>
#include "BFIS.ProtoMessageDefine.pb.h"

using namespace std;

////////////////////////////与SDK通信命令/////////////////////////////////
#define IBFIS_MSG_CLIENT_LOGIN_2_SERVER				0x0001
#define IBFIS_MSG_CLIENT_GET_BRANCHINFO				0x0002
#define IBFIS_MSG_CLIENT_GET_PRODUCEINFO			0x0003
#define IBFIS_MSG_CLIENT_GET_USERMAPINFO			0x0004
#define IBFIS_MSG_CLIENT_GET_ROLEINFO				0x0005
#define IBFIS_MSG_CLIENT_GET_PURVIEWINFO			0x0006
#define IBFIS_MSG_CLIENT_GET_ROLEPURVIEWINFO		0x0007
#define IBFIS_MSG_CLIENT_GET_EMPLOYEEINFO			0x0008
#define IBFIS_MSG_CLIENT_GET_EMPLOYEEPURVIEWINFO	0x0009
#define IBFIS_MSG_CLIENT_GET_CLIENTINFO				0x000a
#define IBFIS_MSG_CLIENT_GET_BUSINESSINFO			0x000b
#define IBFIS_MSG_CLIENT_GET_BUSINESSFILEINFO		0x000c
#define IBFIS_MSG_CLIENT_GET_BUSINESSRELATEINFO		0x000d
#define IBFIS_MSG_CLIENT_QUERY_BUSINESSINFO			0x000e
#define IBFIS_MSG_CLIENT_GET_TRANSPARENTDATA		0x000f
#define IBFIS_MSG_CLIENT_1stACCESS_2_LOGIN_SERVER	0x0010
#define IBFIS_MSG_CLIENT_QUERY_CLIENTINFO			0x0011
#define IBFIS_MSG_CLIENT_QUERY_SUPEREMPLOYEE		0x0012
#define IBFIS_MSG_CLIENT_QUERY_PRODUCEID			0x0013	//查询用户经常使用的产品Id和使用频率
#define IBFIS_MSG_CLIENT_QUERY_TASKPLAN				0x0014	//查询任务计划
#define IBFIS_MSG_CLINET_QUERY_TASKINFO				0x0015	//查询备份任务
#define IBFIS_MSG_CLIENT_IS_ALIVE					0x0016	//心跳
#define IBFIS_MSG_CLIENT_QUERY_BUSINESSINFOUNFINISH 0x0017
#define IBFIS_MSG_CLIENT_QUERY_SCRIPTINFO           0x0018
#define IBFIS_MSG_CLIENT_GET_SCRIPTINFO             0x0019

#define IBFIS_MSG_CLIENT_ADD_BRANCHINFO				0x0021
#define IBFIS_MSG_CLIENT_ADD_PRODUCEINFO			0x0022
#define IBFIS_MSG_CLIENT_SET_USERMAPINFO			0x0023
#define IBFIS_MSG_CLIENT_ADD_ROLEINFO				0x0024
#define IBFIS_MSG_CLIENT_ADD_PURVIEWINFO			0x0025
#define IBFIS_MSG_CLIENT_SET_ROLEPURVIEWINFO		0x0026
#define IBFIS_MSG_CLIENT_ADD_EMPLOYEEINFO			0x0027
#define IBFIS_MSG_CLIENT_SET_EMPLOYEEPURVIEWINFO	0x0028
#define IBFIS_MSG_CLIENT_ADD_CLIENTINFO				0x0029
#define IBFIS_MSG_CLIENT_ADD_BUSINESSINFO			0x002a
#define IBFIS_MSG_CLIENT_SET_TRANSPARENTDATA		0x002b
#define IBFIS_MSG_CLIENT_SET_AUTO_TASKPLAN			0x002c //设置自动备份计划
#define IBFIS_MSG_CLIENT_ADD_MANULTASK				0x002d //设置手动任务

#define IBFIS_MSG_CLIENT_UPDATE_BRANCHINFO			0x0031
#define IBFIS_MSG_CLIENT_UPDATE_PRODUCEINFO			0x0032
/*#define IBFIS_MSG_CLIENT_UPDATE_USERMAPINFO			0x0033*/
#define IBFIS_MSG_CLIENT_UPDATE_ROLEINFO			0x0034
#define IBFIS_MSG_CLIENT_UPDATE_PURVIEWINFO			0x0035
/*#define IBFIS_MSG_CLIENT_UPDATE_ROLEPURVIEWINFO		0x0036*/
#define IBFIS_MSG_CLIENT_UPDATE_EMPLOYEEINFO		0x0037
/*#define IBFIS_MSG_CLIENT_UPDATE_EMPLOYEEPURVIEWINFO	0x0038*/
#define IBFIS_MSG_CLIENT_UPDATE_CLIENTINFO			0x0039
#define IBFIS_MSG_CLIENT_UPDATE_BUSINESSINFO		0x003a

#define IBFIS_MSG_CLIENT_DEL_BRANCHINFO				0x0041
#define IBFIS_MSG_CLIENT_DEL_PRODUCEINFO			0x0042
/*#define IBFIS_MSG_CLIENT_DEL_USERMAPINFO			0x0043*/
#define IBFIS_MSG_CLIENT_DEL_ROLEINFO				0x0044
#define IBFIS_MSG_CLIENT_DEL_PURVIEWINFO			0x0045
/*#define IBFIS_MSG_CLIENT_DEL_ROLEPURVIEWINFO		0x0046*/
#define IBFIS_MSG_CLIENT_DEL_EMPLOYEEINFO			0x0047
/*#define IBFIS_MSG_CLIENT_DEL_EMPLOYEEPURVIEWINFO	0x0048*/
#define IBFIS_MSG_CLIENT_DEL_CLIENTINFO				0x0049
#define IBFIS_MSG_CLIENT_DEL_BUSINESSINFO			0x004a
#define IBFIS_MSG_CLIENT_DEL_TRANSPARENTDATA		0x004b

#define IBFIS_MSG_CLIENT_CTRL_MANULTASK				0x004c	//控制手动任务
#define IBFIS_MSG_CLIENT_QUERY_MCSERVERINFO         0x004d  //查询mc信息
#define IBFIS_MSG_CLIENT_SYNC_PRODUCE               0x004e  //同步产品信息
#define IBFIS_MSG_CLIENT_ADD_SCRIPTINFO             0x0141
#define IBFIS_MSG_CLIENT_UPDATE_SCRIPTINFO          0x0142 
#define IBFIS_MSG_CLIENT_DEL_SCRIPTINFO             0x0143
#define IBFIS_MSG_CLIENT_ADD_OPERATELOGINFO         0x0144
#define IBFIS_MSG_CLIENT_UPDATE_OPERATELOGINFO      0x0145 
#define IBFIS_MSG_CLIENT_DEL_OPERATELOGINFO         0x0146
#define IBFIS_MSG_CLIENT_QUERY_OPERATELOGINFO       0x0147
#define IBFIS_MSG_CLIENT_QUERY_DISKANDCONNECT       0x0148
#define IBFIS_MSG_CLIENT_QUERY_DISKCODEANDCOUNT     0x0149
#define IBFIS_MSG_CLIENT_GET_OPERATELOGINFO         0x0150             

/////////////////////////////更新通知///////////////////////////////////
#define IBFIS_MSG_CLIENT_NOTIFY_BRANCHINFO			0x0051
#define IBFIS_MSG_CLIENT_NOTIFY_PRODUCEINFO			0x0052
#define IBFIS_MSG_CLIENT_NOTIFY_USERMAPINFO			0x0053
#define IBFIS_MSG_CLIENT_NOTIFY_ROLEINFO			0x0054
#define IBFIS_MSG_CLIENT_NOTIFY_PURVIEWINFO			0x0055
#define IBFIS_MSG_CLIENT_NOTIFY_ROLEPURVIEWINFO		0x0056
#define IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEINFO		0x0057
#define IBFIS_MSG_CLIENT_NOTIFY_EMPLOYEEPURVIEWINFO	0x0058
#define IBFIS_MSG_CLIENT_NOTIFY_CLIENTINFO			0x0059
#define IBFIS_MSG_CLIENT_NOTIFY_BUSINESSINFO		0x005a
#define IBFIS_MSG_CLIENT_NOTIFY_KEYVALUEINFO		0x005b
#define IBFIS_MSG_CLIENT_NOTIFY_BUSINESSFILEINFO	0x005c
#define IBFIS_MSG_CLIENT_NOTIFY_BUSINESSRELATEINFO	0x005d
#define IBFIS_MSG_CLIENT_NOTIFY_BUSINESSDOCKMAGINFO 0x005e
#define IBFIS_MSG_CLIENT_NOTIFY_SCRIPTINFO          0x0061
#define IBFIS_MSG_CLIENT_NOTIFY_DISKANDCONNECT      0x0062
#define IBFIS_MSG_CLIENT_NOTIFY_RECONNECT           0x0063
#define IBFIS_MSG_CLIENT_NOTIFY_DISCONNECT          0x0064
#define IBFIS_MSG_CLIENT_NOTIFY_RECORDSTATUS		0x0065 //设置录像状态

////////////////////////////同步服务命令//////////////////////////////////
#define MSG_ISBUSY							0x0101		//判断服务器是否繁忙
#define MSG_LOGIN							0x0102		//客户端登陆		
#define MSG_UPLOAD_CLIENTINFO				0x0103		//上传用户信息
#define MSG_UPLOAD_BRANCHINFO				0x0104		//上传网点信息
#define MSG_UPLOAD_BUSINESSINFO 			0x0105		//上传业务信息
#define MSG_UPLOAD_BUSINESSFILEINFO			0x0106		//上传业务录像信息
#define MSG_UPLOAD_BUSINESSRELATEINFO		0x0107		//上传业务关联信息
#define MSG_UPLOAD_EMPLOYEEINFO				0x0108		//上传员工信息
#define MSG_UPLOAD_EMPLOYEEPURVIEWINFO		0x0109		//上传员工权限信息
#define MSG_GET_CLIENTINFO					0x0110		//获取用户信息
#define MSG_UPLOAD_ROLEINFO					0x0111		//上传用户组信息
#define MSG_UPLOAD_ROLEPURVIEWINFO			0x0112		//上传用户组权限
#define MSG_GET_PRODUCEINFO					0x0113		//获取产品信息
//#define MSG_GET_PURVIEWINFO					0x0114		//获取权限信息
#define MSG_ISSUED_ROLEINFO					0x0115		//下发用户组信息
#define MSG_ISSUED_ROLEPURVIEW				0x0116		//下发用户组权限
#define MSG_ISSUED_PRODUCEINFO				0x0117		//下发产品信息
#define MSG_ISSUED_CLIENTINFO				0x0118		//下发客户信息
#define MSG_DELETE_EMPLOYEEPURVIEWINFO		0x0119		//删除服务器员工权限信息
#define MSG_GET_SMS_LOGININFO               0x011a      //获取上级登陆的mc信息   client->server
#define MSG_GET_PARENT_BRANCHINFO           0x011b      //获取上级网点信息(id 名称)
#define MSG_IS_ALIVE						0x011c		//判断通信是否存活
#define MSG_ISSUED_BRANCHINFO               0x011e
#define MSG_ISSUED_EMPLOYEEINFO             0x011f
#define MSG_CLIENT_SET_MANUALSYNC			0x0120      //设置手动同步 
#define MSG_ISSUED_MIGRATETASKINFO          0x0121 
#define MSG_ISSUED_SCRIPTINFO               0x0122      //下发话术信息
#define MSG_ISSUED_ALLOWSYNC          0x0123        //上级服务 下发开始同步消息给下级
#define MSG_ISSUED_SYNC_ACK               0x0124      //下级应答
#define MSG_OUTGOING_DEVICE_SYNC  0x0125     //外部设备更新信息
#define MSG_OUTGOING_EMPLOYEEPURVIEWINFO             0x0126  //外部设备同步员工权限信息

//服务器-本地服务
#define LOCAL_MSG_SERVER_IS_ALIVE		    0x0200		//判断本地服务是否活着

//////////////////////////服务器返回值定义/////////////////////////////////////
#define OT_SUCCESS							0x0001		//操作成功
#define OT_EXIST							0x0002		//信息存在,操作成功

//查询操作类型
enum QueryOperType
{
	QueryType_SyncPart = 0,
	QueryType_SyncAll = 100
};
//App类型
enum AppType
{
	AppType_Server = 1,
	AppType_Client
};
//数据操作类型
enum DBOperType
{
	DBO_INVAILED,DBO_QUERY,DBO_ADD,DBO_UPDATE,DBO_DEL
};
//同步数据类型
enum SyncDataType
{
	DataType_INVALID,
	DataType_BranceInfo,
	DataType_ClientInfo,
	DataType_RoleInfo,
	DataType_ProduceInfo,
	DataType_BusinessInfo,
	DataType_BusinessFileInfo,
	DataType_BusinessRelationInfo,
	DataType_EmployeeInfo,
	DataType_EmployeePurviewInfo,
	DataType_PurviewInfo,
	DataType_RolePurviewInfo,
	DataType_UserMapInfo,
	DataType_TaskPlan,
	DataType_TaskInfo,
	DataType_MCInfo,
	DataType_ScriptInfo,
	DataType_OperateLogInfo
};
//查询结果类型
enum QueryResultType
{
	QueryFail = -1,
	QuerySuccessWithoutResult = 0,
	QuerySuccessWithResult = 1
};
//数据操作类型
enum DataOperTyoe
{
	DOT_INVAILED = 0 ,DOT_ADD = 1,DOT_UPDATE, DOT_DEL
};
// struct ST_INFO
// {
// 	DBOperType dbType;
// 	SyncDataType dataType;
// 	vector<string> vecStr;
// };
// 
// typedef void (WINAPI* pSyncCallBack)(ST_INFO);

////////////////////////////////////////////////////////////////
struct ST_BranchInfo
{
	ST_BranchInfo()
	{
		nExtendedInfo = 0;
	}
	ST_BranchInfo(BFIS::BranchInfo& msg)
	{
#pragma region 反序列化
		strBranchId = msg.strbranchid();
		strName = msg.strname();
		strAddress = msg.straddress();
		strContact = msg.strcontact();			
		strPhone = msg.strphone();
		strContent = msg.strcontent();
		nExtendedInfo = msg.nextendedinfo();
		strExtendedInfo1 = msg.strextendedinfo1();
		strExtendedInfo2 = msg.strextendedinfo2();
		strParentId = msg.strparentid();
		nIsLocal = msg.nislocal();
		strJDBRID = msg.strjdbrid();
		strParentJDBRID = msg.strparentjdbrid();
		strParentName = msg.strparentname();
		strJDTYPE = msg.strjdtype();
#pragma endregion
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::BranchInfo msg;
		msg.set_strbranchid(strBranchId);
		msg.set_strname(strName);
		msg.set_straddress(strAddress);
		msg.set_strcontact(strContact);
		msg.set_strphone(strPhone);
		msg.set_strcontent(strContent);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_strparentid(strParentId);
		msg.set_nislocal(nIsLocal);
		msg.set_strjdbrid(strJDBRID);
		msg.set_strparentjdbrid(strParentJDBRID);
		msg.set_strparentname(strParentName);
		msg.set_strjdtype(strJDTYPE);
		bool bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::BranchInfo msg;
		msg.set_strbranchid(strBranchId);
		msg.set_strname(strName);
		msg.set_straddress(strAddress);
		msg.set_strcontact(strContact);
		msg.set_strphone(strPhone);
		msg.set_strcontent(strContent);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_strparentid(strParentId);
		msg.set_nislocal(nIsLocal);
		msg.set_strjdbrid(strJDBRID);
		msg.set_strparentjdbrid(strParentJDBRID);
		msg.set_strparentname(strParentName);
		msg.set_strjdtype(strJDTYPE);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	string strBranchId;
	string strName;
	string strAddress;
	string strContact;
	string strPhone;
	string strContent;
	int	   nExtendedInfo;
	string strExtendedInfo1;
	string strExtendedInfo2;
	string strParentId;
	int	   nIsLocal;
	string strJDBRID;   
	string strParentJDBRID;
	string strParentName;
	string strJDTYPE;
};

struct ST_ClientInfo
{
	ST_ClientInfo()
	{
		nExtendedInfo = 0;
	}
	ST_ClientInfo(BFIS::ClientInfo& msg)
	{
#pragma region 反序列化
		// 		BFIS::ClientInfo msg;
		// 		msg.ParseFromString(strInfo);
		strClientId = msg.strclientid();
		strName = msg.strname();
		strCredenitialsType = msg.strcredenitialstype();
		strCredenitial = msg.strcredenitial();
		strPhone = msg.strphone();
		strContent = msg.strcontent();
		nExtendedInfo = msg.nextendedinfo();
		strExtendedInfo1 = msg.strextendedinfo1();
		strExtendedInfo2 = msg.strextendedinfo2();
#pragma endregion
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::ClientInfo msg;
		msg.set_strclientid(strClientId);
		msg.set_strname(strName);
		msg.set_strcredenitialstype(strCredenitialsType);
		msg.set_strcredenitial(strCredenitial);
		msg.set_strphone(strPhone);
		msg.set_strcontent(strContent);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		bool bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::ClientInfo msg;
		msg.set_strclientid(strClientId);
		msg.set_strname(strName);
		msg.set_strcredenitialstype(strCredenitialsType);
		msg.set_strcredenitial(strCredenitial);
		msg.set_strphone(strPhone);
		msg.set_strcontent(strContent);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	string strClientId;
	string strName;
	string strCredenitialsType;
	string strCredenitial;
	string strPhone;
	string strContent;
	int	   nExtendedInfo;
	string strExtendedInfo1;
	string strExtendedInfo2;
};

struct ST_RoleInfo
{
	ST_RoleInfo()
	{
		nRoleLevel = 0;
		nExtendedInfo = 0;
	}
	ST_RoleInfo(BFIS::RoleInfo& msg)
	{
#pragma region 反序列化
		// 		BFIS::RoleInfo msg;
		// 		msg.ParseFromString(strInfo);
		strRoleInfoId = msg.strroleinfoid();
		strRoleName   = msg.strrolename();
		nRoleLevel    = msg.nrolelevel();
		nExtendedInfo = msg.nextendedinfo();
		strExtendedInfo1 = msg.strextendedinfo1();
		strExtendedInfo2 = msg.strextendedinfo2();
		strBranchInfoId = msg.strbranchinfoid();
		nFlag = msg.nflag();
#pragma endregion
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::RoleInfo msg;
		msg.set_strroleinfoid(strRoleInfoId);
		msg.set_strrolename(strRoleName);
		msg.set_nrolelevel(nRoleLevel);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_strbranchinfoid(strBranchInfoId);
		msg.set_nflag(nFlag);
		bool bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::RoleInfo msg;
		msg.set_strroleinfoid(strRoleInfoId);
		msg.set_strrolename(strRoleName);
		msg.set_nrolelevel(nRoleLevel);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_strbranchinfoid(strBranchInfoId);
		msg.set_nflag(nFlag);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	string strRoleInfoId;
	string strRoleName;
	int    nRoleLevel;
	int	   nExtendedInfo;
	string strExtendedInfo1;
	string strExtendedInfo2;
	string strBranchInfoId;
	int	   nFlag;
};

struct ST_ProduceInfo
{
	ST_ProduceInfo()
	{
		nPeriod = 0;
		nMiniAmount = 0;
		nMaxTime = 0;
		nMineTime = 0;
		nStandardTime = 0;
		nIsPublished = 0;
		nIsEnabled = 0;
		nExtendedInfo = 0;
		nEnableMigrated = 0;
		nRecordExistDays = 0;
		nType = 0;
		nPROD_LIFECYCLE = 0;
	}
	ST_ProduceInfo(BFIS::ProduceInfo& msg)
	{
#pragma region 反序列化
		// 		BFIS::ProduceInfo msg;
		// 		msg.ParseFromString(strInfo);
		strProduceId			=	msg.strproduceid();        
		strName				= 	msg.strname(); 			
		strProduceCode		= 	msg.strproducecode(); 		
		nPeriod				= 	msg.nperiod(); 			
		strRevenue			= 	msg.strrevenue(); 			
		nMiniAmount			= 	msg.nminiamount(); 		
		strRiskLevel			= 	msg.strrisklevel(); 		
		strSerialNumber		= 	msg.strserialnumber(); 	
		strPublishBeinTime	= 	msg.strpublishbeintime(); 	
		strPublishEndTime		= 	msg.strpublishendtime(); 	
		strProductionType		= 	msg.strproductiontype(); 	
		strApplicableCustomer =	msg.strapplicablecustomer(); 
		strRevenueType		= 	msg.strrevenuetype(); 		
		strIncrementMoney		= 	msg.strincrementmoney(); 	
		strCurrentyType		= 	msg.strcurrentytype(); 	
		strSealsBranch		= 	msg.strsealsbranch(); 		
		strRevenueInitialDay  =	msg.strrevenueinitialday();
		strDeadLine			= 	msg.strdeadline(); 		
		strPaymentDay			= 	msg.strpaymentday(); 		
		strTrusteeFee			= 	msg.strtrusteefee(); 		
		strCommissionCharge	=	msg.strcommissioncharge(); 
		strTrustee			= 	msg.strtrustee(); 			
		strOverheadCharge		= 	msg.stroverheadcharge(); 	
		strRevenueCalculation =	msg.strrevenuecalculation(); 
		strContent			= 	msg.strcontent(); 			
		nMaxTime				= 	msg.nmaxtime(); 			
		nMineTime				= 	msg.nminetime(); 			
		nStandardTime			= 	msg.nstandardtime(); 		
		strPrequestion		= 	msg.strprequestion(); 		
		nIsPublished			= 	msg.nispublished(); 		
		nIsEnabled			= 	msg.nisenabled(); 			
		nExtendedInfo			= 	msg.nextendedinfo(); 		
		strExtendedInfo1		= 	msg.strextendedinfo1(); 	
		strExtendedInfo2		= 	msg.strextendedinfo2(); 
		nEnableMigrated		= msg.nenablemigrated();
		nRecordExistDays	= msg.nrecordexistdays();
		nType               = msg.ntype();
		strRiskLevelDesc    = msg.strriskleveldesc();
		nPROD_LIFECYCLE     = msg.nprod_lifecycle();
#pragma endregion
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::ProduceInfo msg;
		msg.set_strproduceid(strProduceId);
		msg.set_strname(strName);
		msg.set_strproducecode(strProduceCode);
		msg.set_nperiod(nPeriod);
		msg.set_strrevenue(strRevenue);
		msg.set_nminiamount(nMiniAmount);
		msg.set_strrisklevel(strRiskLevel);
		msg.set_strserialnumber(strSerialNumber);
		msg.set_strpublishbeintime(strPublishBeinTime);
		msg.set_strpublishendtime(strPublishEndTime);
		msg.set_strproductiontype(strProductionType);
		msg.set_strapplicablecustomer(strApplicableCustomer);
		msg.set_strrevenuetype(strRevenueType);
		msg.set_strincrementmoney(strIncrementMoney);
		msg.set_strcurrentytype(strCurrentyType);
		msg.set_strsealsbranch(strSealsBranch);
		msg.set_strrevenueinitialday(strRevenueInitialDay);
		msg.set_strdeadline(strRevenueInitialDay);
		msg.set_strpaymentday(strPaymentDay);
		msg.set_strtrusteefee(strTrusteeFee);
		msg.set_strcommissioncharge(strCommissionCharge);
		msg.set_strtrustee(strTrustee);
		msg.set_stroverheadcharge(strOverheadCharge);
		msg.set_strrevenuecalculation(strRevenueCalculation);
		msg.set_strcontent(strContent);
		msg.set_nmaxtime(nMaxTime);
		msg.set_nminetime(nMineTime);
		msg.set_nstandardtime(nStandardTime);
		msg.set_strprequestion(strPrequestion);
		msg.set_nispublished(nIsPublished);
		msg.set_nisenabled(nIsEnabled);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_nenablemigrated(nEnableMigrated);
		msg.set_nrecordexistdays(nRecordExistDays);
		msg.set_ntype(nType);
		msg.set_strriskleveldesc(strRiskLevelDesc);
		msg.set_nprod_lifecycle(nPROD_LIFECYCLE);
		bool bSeralizeSuccess = false;
		bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* szBuf,int* nSize)
	{
		BFIS::ProduceInfo msg;
		msg.set_strproduceid(strProduceId);
		msg.set_strname(strName);
		msg.set_strproducecode(strProduceCode);
		msg.set_nperiod(nPeriod);
		msg.set_strrevenue(strRevenue);
		msg.set_nminiamount(nMiniAmount);
		msg.set_strrisklevel(strRiskLevel);
		msg.set_strserialnumber(strSerialNumber);
		msg.set_strpublishbeintime(strPublishBeinTime);
		msg.set_strpublishendtime(strPublishEndTime);
		msg.set_strproductiontype(strProductionType);
		msg.set_strapplicablecustomer(strApplicableCustomer);
		msg.set_strrevenuetype(strRevenueType);
		msg.set_strincrementmoney(strIncrementMoney);
		msg.set_strcurrentytype(strCurrentyType);
		msg.set_strsealsbranch(strSealsBranch);
		msg.set_strrevenueinitialday(strRevenueInitialDay);
		msg.set_strdeadline(strRevenueInitialDay);
		msg.set_strpaymentday(strPaymentDay);
		msg.set_strtrusteefee(strTrusteeFee);
		msg.set_strcommissioncharge(strCommissionCharge);
		msg.set_strtrustee(strTrustee);
		msg.set_stroverheadcharge(strOverheadCharge);
		msg.set_strrevenuecalculation(strRevenueCalculation);
		msg.set_strcontent(strContent);
		msg.set_nmaxtime(nMaxTime);
		msg.set_nminetime(nMineTime);
		msg.set_nstandardtime(nStandardTime);
		msg.set_strprequestion(strPrequestion);
		msg.set_nispublished(nIsPublished);
		msg.set_nisenabled(nIsEnabled);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_nenablemigrated(nEnableMigrated);
		msg.set_nrecordexistdays(nRecordExistDays);
		msg.set_ntype(nType);
		msg.set_strriskleveldesc(strRiskLevelDesc);
		msg.set_nprod_lifecycle(nPROD_LIFECYCLE);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(szBuf != NULL)
			bSeralizeSuccess= msg.SerializeToArray(szBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	string strProduceId;
	string strName;
	string strProduceCode;
	int	   nPeriod;
	string strRevenue;
	int    nMiniAmount;
	string strRiskLevel;
	string strSerialNumber;
	string strPublishBeinTime;
	string strPublishEndTime;
	string strProductionType;
	string strApplicableCustomer;
	string strRevenueType;
	string strIncrementMoney;
	string strCurrentyType;
	string strSealsBranch;
	string strRevenueInitialDay;
	string strDeadLine;
	string strPaymentDay;
	string strTrusteeFee;
	string strCommissionCharge;
	string strTrustee;
	string strOverheadCharge;
	string strRevenueCalculation;
	string strContent;
	int    nMaxTime;
	int    nMineTime;
	int    nStandardTime;
	string strPrequestion;
	int    nIsPublished;
	int    nIsEnabled;
	int	   nExtendedInfo;
	string strExtendedInfo1;
	string strExtendedInfo2;
	int	   nEnableMigrated;	 //是否运行迁移
	int	   nRecordExistDays; //录像存在时间
	int    nType;
	string strRiskLevelDesc;
	int    nPROD_LIFECYCLE; 
};

struct ST_EmployeeInfo
{
	ST_EmployeeInfo()
	{
		nExtendedInfo = 0;
		nFlag = 0;
		nPassErrorCount = 0;
	}
	ST_EmployeeInfo(BFIS::EmployeeInfo& msg)
	{
#pragma region 反序列化
		// 		BFIS::EmployeeInfo msg;
		// 		msg.ParseFromString(strInfo);
		strEmployeeId = msg.stremployeeid();
		strBranchId   = msg.strbranchid();
		strName       = msg.strname();
		strPassword   = msg.strpassword();
		strCardId     = msg.strcardid();
		strRoleId     = msg.strroleid();
		strPhone      = msg.strphone();
		nExtendedInfo = msg.nextendedinfo();
		strExtendedInfo1 = msg.strextendedinfo1();
		strExtendedInfo2 = msg.strextendedinfo2();      
		nFlag = msg.nflag();
		stPasswordEidtTime = msg.stpasswordeidttime();
		strJDBRID = msg.strjdbrid();
		strTLNUM = msg.strtlnum();
		strTEL = msg.strtel();
		strGW = msg.strgw();
		strSTS= msg.strsts();
		strTLINST = msg.strtlinst();
		strUSERNAME = msg.strusername();
		strROLENAME = msg.strrolename();
		strUSERSTATUS = msg.struserstatus();
		nPassErrorCount = msg.npasserrorcount();
#pragma endregion
	}
	ST_EmployeeInfo& operator=(const ST_EmployeeInfo& src)
	{
		strEmployeeId = src.strEmployeeId;
		strBranchId = src.strBranchId;
		strName = src.strName;
		strPassword = src.strPassword;
		strCardId = src.strCardId;
		strRoleId = src.strRoleId;
		strPhone = src.strPhone;
		nExtendedInfo = src.nExtendedInfo;
		strExtendedInfo1 = src.strExtendedInfo1;
		strExtendedInfo2 = src.strExtendedInfo2;
		nFlag = src.nFlag;
		stPasswordEidtTime = src.stPasswordEidtTime;
		strJDBRID = src.strJDBRID;
		strTLNUM = src.strTLNUM;
		strTEL = src.strTEL;
		strGW = src.strGW;
		strSTS = src.strSTS;
		strTLINST = src.strTLINST;
		strUSERNAME = src.strUSERNAME;
		strROLENAME = src.strROLENAME;
		strUSERSTATUS = src.strUSERSTATUS;
		nPassErrorCount = src.nPassErrorCount;
		return *this;
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::EmployeeInfo msg;
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strbranchid(strBranchId);
		msg.set_strname(strName);
		msg.set_strpassword(strPassword);
		msg.set_strcardid(strCardId);
		msg.set_strroleid(strRoleId);
		msg.set_strphone(strPhone);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_nflag(nFlag);
		msg.set_stpasswordeidttime(stPasswordEidtTime);
		msg.set_strjdbrid(strJDBRID);
		msg.set_strtlnum(strTLNUM);
		msg.set_strtel(strTEL);
		msg.set_strgw(strGW);
		msg.set_strsts(strSTS);
		msg.set_strtlinst(strTLINST);
		msg.set_strusername(strUSERNAME);
		msg.set_strrolename(strROLENAME);
		msg.set_struserstatus(strUSERSTATUS);
		msg.set_npasserrorcount(nPassErrorCount);
		bool bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::EmployeeInfo msg;
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strbranchid(strBranchId);
		msg.set_strname(strName);
		msg.set_strpassword(strPassword);
		msg.set_strcardid(strCardId);
		msg.set_strroleid(strRoleId);
		msg.set_strphone(strPhone);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_nflag(nFlag);
		msg.set_stpasswordeidttime(stPasswordEidtTime);
		msg.set_strjdbrid(strJDBRID);
		msg.set_strtlnum(strTLNUM);
		msg.set_strtel(strTEL);
		msg.set_strgw(strGW);
		msg.set_strsts(strSTS);
		msg.set_strtlinst(strTLINST);
		msg.set_strusername(strUSERNAME);
		msg.set_strrolename(strROLENAME);
		msg.set_struserstatus(strUSERSTATUS);
		msg.set_npasserrorcount(nPassErrorCount);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	string strEmployeeId;
	string strBranchId;
	string strName;
	string strPassword;
	string strCardId;
	string strRoleId;
	string strPhone;
	int	   nExtendedInfo;
	string strExtendedInfo1;
	string strExtendedInfo2;
	int    nFlag;
	string stPasswordEidtTime;
	string strJDBRID;
	string strTLNUM;
	string strTEL; 
	string strGW; 
	string strSTS; 
	string strTLINST;
	string strUSERNAME;
	string strROLENAME;
	string strUSERSTATUS;
	int nPassErrorCount;
};

struct ST_EmployeePurviewInfo
{
	ST_EmployeePurviewInfo()
	{
		nExtendedInfo = 0;
	}
	ST_EmployeePurviewInfo(BFIS::EmployeePurviewInfo& msg)
	{
#pragma region 反序列化
		strEmployeePurviewId	= msg.stremployeepurviewid();
		strEmployeeId			= msg.stremployeeid();
		strPurviewInfoId		= msg.strpurviewinfoid();
		nExtendedInfo			= msg.nextendedinfo();
		strExtendedInfo1		= msg.strextendedinfo1();
		strExtendedInfo2		= msg.strextendedinfo2();
#pragma endregion
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::EmployeePurviewInfo msg;
		msg.set_stremployeepurviewid(strEmployeePurviewId);
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strpurviewinfoid(strPurviewInfoId);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		bool bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::EmployeePurviewInfo msg;
		msg.set_stremployeepurviewid(strEmployeePurviewId);
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strpurviewinfoid(strPurviewInfoId);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	bool operator == (const ST_EmployeePurviewInfo& r)
	{
		if (this->strEmployeePurviewId.compare(r.strEmployeePurviewId) == 0
			&& this->nExtendedInfo == r.nExtendedInfo
			&& this->strEmployeeId.compare(r.strEmployeeId) == 0
			&& this->strPurviewInfoId.compare(r.strPurviewInfoId) == 0
			&& this->strExtendedInfo1.compare(r.strExtendedInfo1) == 0
			&& this->strExtendedInfo2.compare(r.strExtendedInfo2) == 0)
			return true;
		return false;
	}
	string strEmployeePurviewId;
	string strEmployeeId;
	string strPurviewInfoId;
	int	   nExtendedInfo;
	string strExtendedInfo1;
	string strExtendedInfo2;
};

struct ST_BusinessInfo
{
	ST_BusinessInfo()
	{
		nExtendedInfo = 0;
	}
	ST_BusinessInfo(BFIS::BusinessInfo& msg)
	{
#pragma region 反序列化
		// 		BFIS::BusinessInfo msg;
		// 		msg.ParseFromString(strInfo);
		strBusinessInfoId = msg.strbusinessinfoid();
		strDateTime = msg.strdatetime();
		strBranchId = msg.strbranchid();
		strClientId = msg.strclientid();
		strEmployeeId = msg.stremployeeid();
		strProduceId = msg.strproduceid();
		strSubEquipmentId = msg.strsubequipmentid();
		nExtendedInfo = msg.nextendedinfo();
		strExtendedInfo1 = msg.strextendedinfo1();
		strExtendedInfo2 = msg.strextendedinfo2();
		strSubEquipmentIcmSign = msg.strsubequipmenticmsign();
		strSerialNumber = msg.strserialnumber();
		nMigrated = msg.nmigrated();
		strFileCenter = msg.strfilecenter();
		strBusinessType = msg.strbusinesstype();
		strCardNumber = msg.strcardnumber();
		nMarkerType = msg.nmarkertype();
		strCardType = msg.strcardtype();
		strMediumType = msg.strmediumtype();
		strMediumNum = msg.strmediumnum();
		strOffDisputeTime = msg.stroffdisputetime();
#pragma endregion
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::BusinessInfo msg;
		msg.set_strbusinessinfoid(strBusinessInfoId);
		msg.set_strdatetime(strDateTime);
		msg.set_strbranchid(strBranchId);
		msg.set_strclientid(strClientId);
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strproduceid(strProduceId);
		msg.set_strsubequipmentid(strSubEquipmentId);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_strsubequipmenticmsign(strSubEquipmentIcmSign);
		msg.set_strserialnumber(strSerialNumber);
		msg.set_nmigrated(nMigrated);
		msg.set_strfilecenter(strFileCenter);
		msg.set_strbusinesstype(strBusinessType);
		msg.set_strcardnumber(strCardNumber);
		msg.set_nmarkertype(nMarkerType);
		msg.set_strcardtype(strCardType);
		msg.set_strmediumtype(strMediumType);
		msg.set_strmediumnum(strMediumNum);
		msg.set_stroffdisputetime(strOffDisputeTime);
		bool bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::BusinessInfo msg;
		msg.set_strbusinessinfoid(strBusinessInfoId);
		msg.set_strdatetime(strDateTime);
		msg.set_strbranchid(strBranchId);
		msg.set_strclientid(strClientId);
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strproduceid(strProduceId);
		msg.set_strsubequipmentid(strSubEquipmentId);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_strsubequipmenticmsign(strSubEquipmentIcmSign);
		msg.set_strserialnumber(strSerialNumber);
		msg.set_nmigrated(nMigrated);
		msg.set_strfilecenter(strFileCenter);
		msg.set_strbusinesstype(strBusinessType);
		msg.set_strcardnumber(strCardNumber);
		msg.set_nmarkertype(nMarkerType);
		msg.set_strcardtype(strCardType);
		msg.set_strmediumtype(strMediumType);
		msg.set_strmediumnum(strMediumNum);
		msg.set_stroffdisputetime(strOffDisputeTime);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	string strBusinessInfoId;
	string strDateTime;
	string strBranchId;
	string strClientId;
	string strEmployeeId;
	string strProduceId;
	string strSubEquipmentId;
	int    nExtendedInfo;
	string strExtendedInfo1;
	string strExtendedInfo2;
	string strSubEquipmentIcmSign;
	string strSerialNumber;
	int	   nMigrated;
	string strFileCenter;
	string strBusinessType;    
	string strCardNumber;     
	int nMarkerType; 
	string strCardType;
	string strMediumType;		
	string strMediumNum;
	string strOffDisputeTime;
};

struct ST_BusinessFileInfo
{
	ST_BusinessFileInfo()
	{
		nType = 0;
		nExtendedInfo = 0;
		nMigrated = 0;
	}
	ST_BusinessFileInfo(BFIS::BusinessFileInfo& msg)
	{
#pragma region 反序列化
		// 		BFIS::BusinessFileInfo msg;
		// 		msg.ParseFromString(strInfo);
		strRecordId = msg.strrecordid();
		strBusinessInfoId = msg.strbusinessinfoid();
		nType = msg.ntype();
		strFileId = msg.strfileid();
		strRecordBegin = msg.strrecordbegin();
		strRecordEnd = msg.strrecordend();
		nExtendedInfo = msg.nextendedinfo();
		strExtendedInfo1 = msg.strextendedinfo1();
		strExtendedInfo2 = msg.strextendedinfo2();
		nMigrated = msg.nmigrated();
#pragma endregion
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::BusinessFileInfo msg;
		msg.set_strrecordid(strRecordId);
		msg.set_strbusinessinfoid(strBusinessInfoId);
		msg.set_ntype(nType);
		msg.set_strfileid(strFileId);
		msg.set_strrecordbegin(strRecordBegin);
		msg.set_strrecordend(strRecordEnd);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_nmigrated(nMigrated);
		bool bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::BusinessFileInfo msg;
		msg.set_strrecordid(strRecordId);
		msg.set_strbusinessinfoid(strBusinessInfoId);
		msg.set_ntype(nType);
		msg.set_strfileid(strFileId);
		msg.set_strrecordbegin(strRecordBegin);
		msg.set_strrecordend(strRecordEnd);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		msg.set_nmigrated(nMigrated);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	string strRecordId;
	string strBusinessInfoId;
	int    nType;
	string strFileId;
	string strRecordBegin;
	string strRecordEnd;
	int    nExtendedInfo;
	string strExtendedInfo1;
	string strExtendedInfo2;
	int	   nMigrated;	//判断是否被迁移
};

struct ST_BusinessRelateInfo
{
	ST_BusinessRelateInfo()
	{
		nRelateType = 0;
	}
	ST_BusinessRelateInfo(BFIS::BusinessRelateInfo& msg)
	{
#pragma region 反序列化
		// 		BFIS::BusinessRelateInfo msg;
		// 		msg.ParseFromString(strInfo);
		strBusinessRelateInfoId = msg.strbusinessrelateinfoid();
		strBusinessInfoId = msg.strbusinessinfoid();
		nRelateType = msg.nrelatetype();
		strRelate1 = msg.strrelate1();
		strRelate2 = msg.strrelate2();
		strRelate3 = msg.strrelate3();
#pragma endregion
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::BusinessRelateInfo msg;
		msg.set_strbusinessrelateinfoid(strBusinessRelateInfoId);
		msg.set_strbusinessinfoid(strBusinessInfoId);
		msg.set_nrelatetype(nRelateType);
		msg.set_strrelate1(strRelate1);
		msg.set_strrelate2(strRelate2);
		msg.set_strrelate3(strRelate3);
		bool bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::BusinessRelateInfo msg;
		msg.set_strbusinessrelateinfoid(strBusinessRelateInfoId);
		msg.set_strbusinessinfoid(strBusinessInfoId);
		msg.set_nrelatetype(nRelateType);
		msg.set_strrelate1(strRelate1);
		msg.set_strrelate2(strRelate2);
		msg.set_strrelate3(strRelate3);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	string strBusinessRelateInfoId;
	string strBusinessInfoId;
	int	   nRelateType;
	string strRelate1;
	string strRelate2;
	string strRelate3;
};

struct ST_PurviewInfo
{
	ST_PurviewInfo()
	{

	}
	ST_PurviewInfo(BFIS::PurviewInfo& msg)
	{
#pragma region 反序列化
		// 		BFIS::PurviewInfo msg;
		// 		msg.ParseFromString(strInfo);
		strPurviewInfoId = msg.strpurviewinfoid();
		strParentPurviewId = msg.strparentpurviewid();
		strPurviewCode   = msg.strpurviewcode();
		strDescription = msg.strdescription();
		strExtendedInfo1 = msg.strextendedinfo1();
		strExtendedInfo2 = msg.strextendedinfo2();
#pragma endregion
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::PurviewInfo msg;
		msg.set_strpurviewinfoid(strPurviewInfoId);
		msg.set_strparentpurviewid(strParentPurviewId);
		msg.set_strpurviewcode(strPurviewCode);
		msg.set_strdescription(strDescription);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		bool bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::PurviewInfo msg;
		msg.set_strpurviewinfoid(strPurviewInfoId);
		msg.set_strparentpurviewid(strParentPurviewId);
		msg.set_strpurviewcode(strPurviewCode);
		msg.set_strdescription(strDescription);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	string strPurviewInfoId;
	string strParentPurviewId;
	string strPurviewCode;
	string strDescription;
	string strExtendedInfo1;
	string strExtendedInfo2;
};

struct ST_RolePurviewInfo
{
	ST_RolePurviewInfo()
	{
		nExtendedInfo = 0;
	}
	ST_RolePurviewInfo(BFIS::RolePurviewInfo& msg)
	{
#pragma region 反序列化
		// 		BFIS::RolePurviewInfo msg;
		// 		msg.ParseFromString(strInfo);
		strRoleInfoPurviewId = msg.strroleinfopurviewid();
		strRoleId            = msg.strroleid();
		strPruviewInfoId     = msg.strpruviewinfoid();
		nExtendedInfo        = msg.nextendedinfo();
		strExtendedInfo1     = msg.strextendedinfo1();
		strExtendedInfo2     = msg.strextendedinfo2();
#pragma endregion
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::RolePurviewInfo msg;
		msg.set_strroleinfopurviewid(strRoleInfoPurviewId);
		msg.set_strroleid(strRoleId);
		msg.set_strpruviewinfoid(strPruviewInfoId);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		bool bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::RolePurviewInfo msg;
		msg.set_strroleinfopurviewid(strRoleInfoPurviewId);
		msg.set_strroleid(strRoleId);
		msg.set_strpruviewinfoid(strPruviewInfoId);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	string strRoleInfoPurviewId;
	string strRoleId;
	string strPruviewInfoId;
	int    nExtendedInfo;
	string strExtendedInfo1;
	string strExtendedInfo2;
};

enum HandleType{HT_Invail,HT_Sync,HT_Client};

struct ST_LoginInfo
{
	string strUserName;
	string strUserPwd;
};

struct ST_UserMapInfo
{
	ST_UserMapInfo(){}
	ST_UserMapInfo(BFIS::UserMapInfo& msg)
	{
#pragma region 反序列化
		strUserMapInfoId = msg.strusermapinfoid();
		strEmployeeId = msg.stremployeeid();
		strSocUsername = msg.strsocusername();
		strSocPassword = msg.strsocpassword();
		strExtendedInfo1 = msg.strextendedinfo1();
		strExtendedInfo2 = msg.strextendedinfo2();
#pragma endregion
	}
	bool ConvertToString(std::string& strInfo)
	{
#pragma region 序列化
		BFIS::UserMapInfo msg;
		msg.set_strusermapinfoid(strUserMapInfoId);
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strsocusername(strSocUsername);
		msg.set_strsocpassword(strSocPassword);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		bool bSeralizeSuccess = msg.SerializeToString(&strInfo);
		return bSeralizeSuccess;
#pragma endregion
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::UserMapInfo msg;
		msg.set_strusermapinfoid(strUserMapInfoId);
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strsocusername(strSocUsername);
		msg.set_strsocpassword(strSocPassword);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	string strUserMapInfoId;
	string strEmployeeId;
	string strSocUsername;
	string strSocPassword;
	string strExtendedInfo1;
	string strExtendedInfo2;
};
struct ST_KeyValueInfo
{
	ST_KeyValueInfo()
	{
		nExtendedInfo = 0;
	}
	string strKeyValueInfoId;
	string strType;
	string strCode;
	string strValue;
	int	   nExtendedInfo;
	string strExtendedInfo1;
	string strExtendedInfo2;
};

struct  ST_BusinessQueryParam
{
	string strBranchId;
	string strEmployeeId;
	string strCustomerId;
	string strProduceId;
	string strStartTime;
	string strEndTime;
	int      nPageSize;
	int	  nPageIndex;
	int      nRecordCount;
	string strSerialNumber;
	string strCredenitialsType;
	string strBusinessType;
	string strCardNumber;
	int nMarkerType;   
	string strRiskLevel;
	string strConditionEx;
	string strMediumNum;
	string strExtendedInfo2;
	ST_BusinessQueryParam()
	{
		nPageSize = 0;
		nPageIndex = 0;
		nRecordCount = 0;
		nMarkerType = 0; 
	}
	ST_BusinessQueryParam(BFIS::BusinessQueryParam& msg)
	{
		strBranchId = msg.strbranchid();
		strEmployeeId = msg.stremployeeid();
		strCustomerId = msg.strcustomerid();
		strProduceId = msg.strproduceid();
		strStartTime = msg.strstarttime();
		strEndTime = msg.strendtime();
		nPageSize = msg.npagesize();
		nPageIndex = msg.npageindex();
		nRecordCount = msg.nrecordcount();
		strSerialNumber = msg.strserialnumber();
		strCredenitialsType = msg.strcredenitialstype();
		strBusinessType = msg.strbusinesstype();
		strCardNumber = msg.strcardnumber();
		nMarkerType = msg.nmarkertype();
		strRiskLevel = msg.strrisklevel();
		strConditionEx = msg.strconditionex();
		strMediumNum = msg.strmediumnum();
		strExtendedInfo2 = msg.strextendedinfo2();
	}
	bool ConvertToString(std::string& strInfo)
	{
		BFIS::BusinessQueryParam msg;
		msg.set_strbranchid(strBranchId);
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strcustomerid(strCustomerId);
		msg.set_strproduceid(strProduceId);
		msg.set_strstarttime(strStartTime);
		msg.set_strendtime(strEndTime);
		msg.set_npagesize(nPageSize);
		msg.set_npageindex(nPageIndex);
		msg.set_nrecordcount(nRecordCount);
		msg.set_strserialnumber(strSerialNumber);
		msg.set_strcredenitialstype(strCredenitialsType);
		msg.set_strbusinesstype(strBusinessType);
		msg.set_strcardnumber(strCardNumber);
		msg.set_nmarkertype(nMarkerType);
		msg.set_strrisklevel(strRiskLevel);
		msg.set_strconditionex(strConditionEx);
		msg.set_strmediumnum(strMediumNum);
		msg.set_strextendedinfo2(strExtendedInfo2);
		return msg.SerializeToString(&strInfo);
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::BusinessQueryParam msg;
		msg.set_strbranchid(strBranchId);
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strcustomerid(strCustomerId);
		msg.set_strproduceid(strProduceId);
		msg.set_strstarttime(strStartTime);
		msg.set_strendtime(strEndTime);
		msg.set_npagesize(nPageSize);
		msg.set_npageindex(nPageIndex);
		msg.set_nrecordcount(nRecordCount);
		msg.set_strserialnumber(strSerialNumber);
		msg.set_strcredenitialstype(strCredenitialsType);
		msg.set_strbusinesstype(strBusinessType);
		msg.set_strcardnumber(strCardNumber);
		msg.set_nmarkertype(nMarkerType);
		msg.set_strrisklevel(strRiskLevel);
		msg.set_strconditionex(strConditionEx);
		msg.set_strmediumnum(strMediumNum);
		msg.set_strextendedinfo2(strExtendedInfo2);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	ST_BusinessQueryParam(const ST_BusinessQueryParam& src)
	{
		strBranchId = src.strBranchId;
		strEmployeeId = src.strEmployeeId;
		strCustomerId = src.strCustomerId;
		strProduceId = src.strProduceId;
		strStartTime = src.strStartTime;
		strEndTime = src.strEndTime;
		nPageSize = src.nPageSize;
		nPageIndex = src.nPageIndex;
		nRecordCount = src.nRecordCount;
		strSerialNumber = src.strSerialNumber;
		strCredenitialsType = src.strCredenitialsType;
		strBusinessType = src.strBusinessType;
		strCardNumber = src.strCardNumber;
		nMarkerType = src.nMarkerType;
		strRiskLevel = src.strRiskLevel;
		strConditionEx = src.strConditionEx;
		strMediumNum = src.strMediumNum;
		strExtendedInfo2 = src.strExtendedInfo2;
	}
	ST_BusinessQueryParam& operator=(const ST_BusinessQueryParam& src)
	{
		strBranchId = src.strBranchId;
		strEmployeeId = src.strEmployeeId;
		strCustomerId = src.strCustomerId;
		strProduceId = src.strProduceId;
		strStartTime = src.strStartTime;
		strEndTime = src.strEndTime;
		nPageSize = src.nPageSize;
		nPageIndex = src.nPageIndex;
		nRecordCount = src.nRecordCount;
		strSerialNumber = src.strSerialNumber;
		strCredenitialsType = src.strCredenitialsType;
		strBusinessType = src.strBusinessType;
		strCardNumber = src.strCardNumber;
		nMarkerType = src.nMarkerType;
		strRiskLevel = src.strRiskLevel;
		strConditionEx = src.strConditionEx;
		strMediumNum = src.strMediumNum;
		strExtendedInfo2 = src.strExtendedInfo2;
		return *this;
	}
};

struct  ST_ProduceIdQueryParam
{
	string strInfoId;
	int	nCount;
	ST_ProduceIdQueryParam()
	{
		nCount = 0;
	}
	ST_ProduceIdQueryParam(BFIS::ProduceIdQueryParam& msg)
	{
		strInfoId = msg.strinfoid();
		nCount = msg.ncount();
	}
	bool ConvertToString(std::string& strInfo)
	{
		BFIS::ProduceIdQueryParam msg;
		msg.set_strinfoid(strInfoId);
		msg.set_ncount(nCount);
		return msg.SerializeToString(&strInfo);
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::ProduceIdQueryParam msg;
		msg.set_strinfoid(strInfoId);
		msg.set_ncount(nCount);
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	ST_ProduceIdQueryParam(const ST_ProduceIdQueryParam& src)
	{
		strInfoId = src.strInfoId;
		nCount = src.nCount;
	}
	ST_ProduceIdQueryParam& operator=(const ST_ProduceIdQueryParam& src)
	{
		strInfoId = src.strInfoId;
		nCount = src.nCount;
		return *this;
	}
};
struct ST_BFISMigrateTask
{
	ST_BFISMigrateTask()
	{
		nProcess = 0;
		nOrderID = 0;
		nType = 0;
		nStatus = 0;
	}
	ST_BFISMigrateTask(BFIS::BackupTask msg)
	{
		strTaskID = msg.strtaskid();
		nType = msg.ntype();
		nStatus = msg.nstatus();
		strBusinessID = msg.strbusinessid();
		strProduceID = msg.strproduceid();
		strEmployeeID = msg.stremployeeid();
		stCustomer.strClientId = msg.stcustomer().strclientid();
		stCustomer.strContent = msg.stcustomer().strcontent();
		stCustomer.strCredenitial = msg.stcustomer().strcredenitial();
		stCustomer.strName = msg.stcustomer().strname();
		stCustomer.strPhone = msg.stcustomer().strphone();
		stCustomer.strExtendedInfo1 = msg.stcustomer().strextendedinfo1();
		stCustomer.strExtendedInfo2 = msg.stcustomer().strextendedinfo2();
		stCustomer.nExtendedInfo = msg.stcustomer().nextendedinfo();
		strAutoTime = msg.strautotime();
		strBeginTime = msg.strbegintime();
		strEndTime = msg.strendtime();
		nProcess = msg.nprocess();
		strLaunchEmployeeID = msg.strlaunchemployeeid();
		nOrderID = msg.norderid();
		strTimeForBusiness = msg.strtimeforbusiness();
		strExtendedInfo2 = msg.strextendedinfo2();
	}
	bool ConvertToString(std::string& strInfo)
	{
		BFIS::BackupTask msg;
		msg.set_strtaskid(strTaskID);
		msg.set_ntype(nType);
		msg.set_nstatus(nStatus);
		msg.set_strbusinessid(strBusinessID);
		msg.set_strproduceid(strProduceID);
		msg.set_stremployeeid(strEmployeeID);
		BFIS::ClientInfo stInfo;
		stInfo.set_strclientid(stCustomer.strClientId);
		stInfo.set_strcontent(stCustomer.strContent);
		stInfo.set_strcredenitial(stCustomer.strCredenitial);
		stInfo.set_strname(stCustomer.strName);
		stInfo.set_strphone(stCustomer.strPhone);
		stInfo.set_strextendedinfo1(stCustomer.strExtendedInfo1);
		stInfo.set_strextendedinfo2(stCustomer.strExtendedInfo2);
		stInfo.set_nextendedinfo(stCustomer.nExtendedInfo);
		msg.set_allocated_stcustomer(&stInfo);
		msg.set_strautotime(strAutoTime);
		msg.set_strbegintime(strBeginTime);
		msg.set_strendtime(strEndTime);
		msg.set_nprocess(nProcess);
		msg.set_strlaunchemployeeid(strLaunchEmployeeID);
		msg.set_norderid(nOrderID);
		msg.set_strtimeforbusiness(strTimeForBusiness);
		msg.set_strextendedinfo2(strExtendedInfo2);
		return msg.SerializeToString(&strInfo);
	}
	std::string 	strTaskID;		    //任务id
	int				nType;			    //任务类型:手动、自动
	int				nStatus;			//任务状态:进行中、暂停、准备、结束、异常
	std::string     strBusinessID;	    //关联业务id
	std::string     strProduceID;		//关联业务产品id
	std::string     strEmployeeID;	    //关联业务员工id
	ST_ClientInfo	stCustomer;		    //关联业务客户信息
	std::string		strAutoTime;		//自动任务设置的开始时间
	std::string		strBeginTime;		//任务开始时间
	std::string		strEndTime;		    //任务结束时间
	int				nProcess;			//进度,当enStatus为TSK_PROCESSING时有效
	std::string     strLaunchEmployeeID;//手动任务发起人ID
	int				nOrderID;			//排序ID，表明优先级
	std::string     strTimeForBusiness;	//业务办理时间
	std::string     strExtendedInfo2;   
};

struct ST_TaskPlan
{
	ST_TaskPlan()
	{
		nEnable = 0;
		nOrderID = 0;
	}
	ST_TaskPlan(BFIS::TaskPlan& msg)
	{
		strPlanID = msg.strplanid();
		strTimeBegin = msg.strbegintime();
		strTimeEnd = msg.strendtime();
		nEnable = msg.neable();
		nOrderID = msg.norderid();
	}
	bool ConvertToString(std::string& strInfo)
	{
		BFIS::TaskPlan msg;
		msg.set_strplanid(strPlanID);
		msg.set_strbegintime(strTimeBegin);
		msg.set_strendtime(strTimeEnd);
		msg.set_neable(nEnable);
		msg.set_norderid(nOrderID);
		return msg.SerializeToString(&strInfo);
	}
	std::string		strPlanID;		//计划Id
	std::string		strTimeBegin;	//开始时间
	std::string		strTimeEnd;		//结束时间
	int				nEnable;		//1.启用 0.不启用
	int				nOrderID;		//排序ID，目前只有1、2、3
};

struct ST_MCServer
{
	ST_MCServer()
	{
		sPort = 0;
		nIsLocal = 0;
	}
	ST_MCServer(BFIS::McServer& msg)
	{
		strBranchID = msg.strbranchid();
		strBranchName = msg.strbranchname();
		strMCIP = msg.strmcip();
		sPort = msg.nport();
		strMCUserName = msg.strmcusername();
		strMCUserPwd = msg.strmcuserpwd();
		nIsLocal = msg.nislocal();
	}
	bool Convert2String(std::string& strInfo)
	{
		BFIS::McServer msg;
		msg.set_strbranchid(strBranchID);
		msg.set_strbranchname(strBranchName);
		msg.set_strmcip(strMCIP);
		msg.set_nport(sPort);
		msg.set_strmcusername(strMCUserName);
		msg.set_strmcuserpwd(strMCUserPwd);
		msg.set_nislocal(nIsLocal);
		return msg.SerializeToString(&strInfo);
	}
	string strBranchID;
	string strBranchName;
	string strMCIP;
	unsigned short sPort;
	string strMCUserName;
	string strMCUserPwd;
	int nIsLocal;
};

struct ST_MigrateLogInfo
{
	ST_MigrateLogInfo()
	{
		nType = nStatus = nOrderID = 0;
	}
	ST_MigrateLogInfo(BFIS::MigrateLog msg)
	{
		strMigrateTaskID = msg.strmigratetaskid();
		strBusinessID = msg.strbusinessid();
		strProduceID = msg.strproduceid();
		strEmployeeID = msg.stremployeeid();
		nType = msg.ntype();
		nStatus = msg.nstatus();
		strAutoTime = msg.strautotime();
		strBeginTime = msg.strbegintime();
		strEndTime = msg.strendtime();
		strLaunchEmployeeID = msg.strlaunchemployeeid();
		nOrderID = msg.norderid();
	}
	bool Convert2String(std::string& strInfo)
	{
		BFIS::MigrateLog msg;
		msg.set_strmigratetaskid(strMigrateTaskID);
		msg.set_strbusinessid(strBusinessID);
		msg.set_strproduceid(strProduceID);
		msg.set_stremployeeid(strEmployeeID);
		msg.set_ntype(nType);
		msg.set_nstatus(nStatus);
		msg.set_strautotime(strAutoTime);
		msg.set_strbegintime(strBeginTime);
		msg.set_strendtime(strEndTime);
		msg.set_strlaunchemployeeid(strLaunchEmployeeID);
		msg.set_norderid(nOrderID);
		return msg.SerializeToString(&strInfo);
	}
	string strMigrateTaskID;
	string strBusinessID;
	string strProduceID;
	string strEmployeeID;
	int nType;
	int nStatus;
	string strAutoTime;
	string strBeginTime;
	string strEndTime;
	string strLaunchEmployeeID;
	int nOrderID;
};

struct ST_QueryCondition
{
	ST_QueryCondition()
	{
		nReserved = nPageSize = nPageIndex = 0;
	}
	ST_QueryCondition(BFIS::QueryCondition msg)
	{
		strCon1 = msg.strcon1();
		strCon2 = msg.strcon2();
		nPageSize = msg.npagesize();
		nPageIndex = msg.npageindex();
		nReserved = msg.nreserved();
		strReserved = msg.strreserved();
	}
	bool Convert2String(std::string& strInfo)
	{
		BFIS::QueryCondition msg;
		msg.set_strcon1(strCon1);
		msg.set_strcon2(strCon2);
		msg.set_npagesize(nPageSize);
		msg.set_npageindex(nPageIndex);
		msg.set_nreserved(nReserved);
		msg.set_strreserved(strReserved);
		return msg.SerializeToString(&strInfo);
	}
	string strCon1;
	string strCon2;
	int nPageSize;
	int nPageIndex;
	int nReserved;
	string strReserved;
};
struct ST_BusinessDockMsgInfo
{
	string strChannelCode;
	string strServiceCode;
	string strJDBRID;
	string strOperatorId;
	string strChannelSerialNum ;
	string strKernelSerialNum;
	string strDateTime;
	string strChannelDate;
	string strRepondCode;
	string strChineseDescribeInfo;
	string strBusinessCode;
	string strBusinessName;
	string strBusinessStatus;
	string strProduceCode;
	string strObjectProduceCode;
	string strFundName;
	string strProduceName;
	string strIncomeType ;
	string strBusinessDate;
	string strClientName;
	string strCredenitialsType;
	string strCredenitialNum;
	string strMediumType;
	string strMediumNum;
	string strClientRiskLevel;
	string strProduceRiskLevel;
	string strFundType;
	string strCancelBusinessType;
	string strTerminalIP;           //终端ip
	string strTradeSerialNum;       //交易流水号
	string strFinancSerialNum;      //理财流水号

	int nSystemType;                  //1 锦州理财系统  2 锦州核心系统  3 攀枝花业务系统 4 南充业务系统
	int nBootFlag;                    //对接模式标志 1 开启录像  2 填充对接信息  3 结束录像

	string strTermId;               //终端号（乐山预留）
	string strTranTime;             //交易时间（乐山预留）
	string strAcctNo;               //客户账号（乐山预留）

	string strIBFISSerialNum;       //南充对接 理财系统生成流水号
	string strVideoEndDate;         //南充对接 录像保存时间
	string strExtendedInfo;       //预留字段
	ST_BusinessDockMsgInfo()
	{
		nSystemType = 0;
		nBootFlag = 0;
	}
	ST_BusinessDockMsgInfo(BFIS::BusinessDockMsgInfo& msg)
	{
		strChannelCode = msg.strchannelcode();
		strServiceCode = msg.strservicecode();
		strJDBRID = msg.strjdbrid();
		strOperatorId = msg.stroperatorid();
		strChannelSerialNum = msg.strchannelserialnum();
		strKernelSerialNum = msg.strkernelserialnum();
		strDateTime = msg.strdatetime();
		strChannelDate = msg.strchanneldate();
		strRepondCode = msg.strrepondcode();
		strChineseDescribeInfo = msg.strchinesedescribeinfo();
		strBusinessCode = msg.strbusinesscode();
		strBusinessName = msg.strbusinessname();
		strBusinessStatus = msg.strbusinessstatus();
		strProduceCode = msg.strproducecode();
		strObjectProduceCode = msg.strobjectproducecode();
		strFundName = msg.strfundname();
		strProduceName = msg.strproducename();
		strIncomeType = msg.strincometype();
		strBusinessDate = msg.strbusinessdate();
		strClientName = msg.strclientname();
		strCredenitialsType = msg.strcredenitialstype();
		strCredenitialNum = msg.strcredenitialnum();
		strMediumType = msg.strmediumtype();
		strMediumNum = msg.strmediumnum();
		strClientRiskLevel = msg.strclientrisklevel();
		strProduceRiskLevel = msg.strproducerisklevel();
		strFundType = msg.strfundtype();
		strCancelBusinessType = msg.strcancelbusinesstype();
	    strTerminalIP = msg.strterminalip();                
		strTradeSerialNum = msg.strtradeserialnum();        
		strFinancSerialNum = msg.strfinancserialnum();      
		nSystemType = msg.nsystemtype();                 
		nBootFlag = msg.nbootflag();                      
		strTermId = msg.strtermid();             
		strTranTime = msg.strtrantime();              
		strAcctNo = msg.stracctno();                
		strIBFISSerialNum = msg.stribfisserialnum();  
		strVideoEndDate = msg.strvideoenddate();      
		strExtendedInfo = msg.strextendedinfo();       
	}
	bool ConvertToString(std::string& strInfo)
	{
		BFIS::BusinessDockMsgInfo msg;
		msg.set_strchannelcode(strChannelCode);
		msg.set_strservicecode(strServiceCode);
		msg.set_strjdbrid(strJDBRID);
		msg.set_stroperatorid(strOperatorId);
		msg.set_strchannelserialnum(strChannelSerialNum) ;
		msg.set_strkernelserialnum(strKernelSerialNum);
		msg.set_strdatetime(strDateTime);
		msg.set_strchanneldate(strChannelDate);
		msg.set_strrepondcode(strRepondCode);
		msg.set_strchinesedescribeinfo(strChineseDescribeInfo);
		msg.set_strbusinesscode(strBusinessCode);
		msg.set_strbusinessname(strBusinessName);
		msg.set_strbusinessstatus(strBusinessStatus);
		msg.set_strproducecode(strProduceCode);
		msg.set_strobjectproducecode(strObjectProduceCode);
		msg.set_strfundname(strFundName);
		msg.set_strproducename(strProduceName);
		msg.set_strincometype(strIncomeType) ;
		msg.set_strbusinessdate(strBusinessDate);
		msg.set_strclientname(strClientName);
		msg.set_strcredenitialstype(strCredenitialsType);
		msg.set_strcredenitialnum(strCredenitialNum);
		msg.set_strmediumtype(strMediumType);
		msg.set_strmediumnum(strMediumNum);
		msg.set_strclientrisklevel(strClientRiskLevel);
		msg.set_strproducerisklevel(strProduceRiskLevel);
		msg.set_strfundtype(strFundType);
		msg.set_strcancelbusinesstype(strCancelBusinessType);
        msg.set_strterminalip(strTerminalIP);                
		msg.set_strtradeserialnum(strTradeSerialNum); 
	    msg.set_strfinancserialnum(strFinancSerialNum);      
		msg.set_nsystemtype(nSystemType);                 
		msg.set_nbootflag(nBootFlag);                  
	    msg.set_strtermid(strTermId);                 
		msg.set_strtrantime(strTranTime);              
		msg.set_stracctno(strAcctNo);          
		msg.set_stribfisserialnum(strIBFISSerialNum);   
		msg.set_strvideoenddate(strVideoEndDate);       
		msg.set_strextendedinfo(strExtendedInfo);       	
		return msg.SerializeToString(&strInfo);
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::BusinessDockMsgInfo msg;
		msg.set_strchannelcode(strChannelCode);
		msg.set_strservicecode(strServiceCode);
		msg.set_strjdbrid(strJDBRID);
		msg.set_stroperatorid(strOperatorId);
		msg.set_strchannelserialnum(strChannelSerialNum) ;
		msg.set_strkernelserialnum(strKernelSerialNum);
		msg.set_strdatetime(strDateTime);
		msg.set_strchanneldate(strChannelDate);
		msg.set_strrepondcode(strRepondCode);
		msg.set_strchinesedescribeinfo(strChineseDescribeInfo);
		msg.set_strbusinesscode(strBusinessCode);
		msg.set_strbusinessname(strBusinessName);
		msg.set_strbusinessstatus(strBusinessStatus);
		msg.set_strproducecode(strProduceCode);
		msg.set_strobjectproducecode(strObjectProduceCode);
		msg.set_strfundname(strFundName);
		msg.set_strproducename(strProduceName);
		msg.set_strincometype(strIncomeType) ;
		msg.set_strbusinessdate(strBusinessDate);
		msg.set_strclientname(strClientName);
		msg.set_strcredenitialstype(strCredenitialsType);
		msg.set_strcredenitialnum(strCredenitialNum);
		msg.set_strmediumtype(strMediumType);
		msg.set_strmediumnum(strMediumNum);
		msg.set_strclientrisklevel(strClientRiskLevel);
		msg.set_strproducerisklevel(strProduceRiskLevel);
		msg.set_strfundtype(strFundType);
		msg.set_strcancelbusinesstype(strCancelBusinessType);
		msg.set_strterminalip(strTerminalIP);                
		msg.set_strtradeserialnum(strTradeSerialNum); 
		msg.set_strfinancserialnum(strFinancSerialNum);      
		msg.set_nsystemtype(nSystemType);                 
		msg.set_nbootflag(nBootFlag);                  
		msg.set_strtermid(strTermId);                 
		msg.set_strtrantime(strTranTime);              
		msg.set_stracctno(strAcctNo);          
		msg.set_stribfisserialnum(strIBFISSerialNum);   
		msg.set_strvideoenddate(strVideoEndDate);       
		msg.set_strextendedinfo(strExtendedInfo);      
		*nSize = msg.ByteSize();
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	ST_BusinessDockMsgInfo(const ST_BusinessDockMsgInfo& src)
	{
		strChannelCode = src.strChannelCode;
		strServiceCode = src.strServiceCode;
		strJDBRID = src.strJDBRID;
		strOperatorId = src.strOperatorId;
		strChannelSerialNum = src.strChannelSerialNum ;
		strKernelSerialNum = src.strKernelSerialNum;
		strDateTime = src.strDateTime;
		strChannelDate = src.strChannelDate;
		strRepondCode = src.strRepondCode;
		strChineseDescribeInfo = src.strChineseDescribeInfo;
		strBusinessCode = src.strBusinessCode;
		strBusinessName = src.strBusinessName;
		strBusinessStatus = src.strBusinessStatus;
		strProduceCode = src.strProduceCode;
		strObjectProduceCode = src.strObjectProduceCode;
		strFundName = src.strFundName;
		strProduceName = src.strProduceName;
		strIncomeType = src.strIncomeType ;
		strBusinessDate = src.strBusinessDate;
		strClientName =  src.strClientName;
		strCredenitialsType = src.strCredenitialsType;
		strCredenitialNum = src.strCredenitialNum;
		strMediumType = src.strMediumType;
		strMediumNum = src.strMediumNum;
		strClientRiskLevel = src.strClientRiskLevel;
		strProduceRiskLevel = src.strProduceRiskLevel;
		strFundType = src.strFundType;
		strCancelBusinessType = src.strCancelBusinessType;
		strTerminalIP = src.strTerminalIP;
		strTradeSerialNum = src.strTradeSerialNum;
		strFinancSerialNum = src.strFinancSerialNum;
		nSystemType = src.nSystemType;
		nBootFlag = src.nBootFlag;
		strTermId = src.strTermId;
		strTranTime = src.strTranTime;
		strAcctNo = src.strAcctNo;
		strIBFISSerialNum = src.strIBFISSerialNum;
		strVideoEndDate = src.strVideoEndDate;
		strExtendedInfo = src.strExtendedInfo;
	}
	ST_BusinessDockMsgInfo& operator=(const ST_BusinessDockMsgInfo& src)
	{
		strChannelCode = src.strChannelCode;
		strServiceCode = src.strServiceCode;
		strJDBRID = src.strJDBRID;
		strOperatorId = src.strOperatorId;
		strChannelSerialNum = src.strChannelSerialNum ;
		strKernelSerialNum = src.strKernelSerialNum;
		strDateTime = src.strDateTime;
		strChannelDate = src.strChannelDate;
		strRepondCode = src.strRepondCode;
		strChineseDescribeInfo = src.strChineseDescribeInfo;
		strBusinessCode = src.strBusinessCode;
		strBusinessName = src.strBusinessName;
		strBusinessStatus = src.strBusinessStatus;
		strProduceCode = src.strProduceCode;
		strObjectProduceCode = src.strObjectProduceCode;
		strFundName = src.strFundName;
		strProduceName = src.strProduceName;
		strIncomeType = src.strIncomeType ;
		strBusinessDate = src.strBusinessDate;
		strClientName =  src.strClientName;
		strCredenitialsType = src.strCredenitialsType;
		strCredenitialNum = src.strCredenitialNum;
		strMediumType = src.strMediumType;
		strMediumNum = src.strMediumNum;
		strClientRiskLevel = src.strClientRiskLevel;
		strProduceRiskLevel = src.strProduceRiskLevel;
		strFundType = src.strFundType;
		strCancelBusinessType = src.strCancelBusinessType;
		strTerminalIP = src.strTerminalIP;
		strTradeSerialNum = src.strTradeSerialNum;
		strFinancSerialNum = src.strFinancSerialNum;
		nSystemType = src.nSystemType;
		nBootFlag = src.nBootFlag;
		strTermId = src.strTermId;
		strTranTime = src.strTranTime;
		strAcctNo = src.strAcctNo;
		strIBFISSerialNum = src.strIBFISSerialNum;
		strVideoEndDate = src.strVideoEndDate;
		strExtendedInfo = src.strExtendedInfo;
		return *this;
	}
};
struct ST_ManualSyncParameter
{
	int      nBranchInfo;
	int		 nProduceInfo;
	int      nEmployeeInfo;
	ST_ManualSyncParameter()
	{
		nBranchInfo = 0;
		nProduceInfo = 0;
		nEmployeeInfo = 0;
	}
	ST_ManualSyncParameter(BFIS::ManualSyncParameter& msg)
	{
		nBranchInfo = msg.nbranchinfo();
		nProduceInfo = msg.nproduceinfo();
		nEmployeeInfo = msg.nemployeeinfo();	
	}
	bool ConvertToString(std::string& strInfo)
	{
		BFIS::ManualSyncParameter msg;
		msg.set_nbranchinfo(nBranchInfo);
		msg.set_nproduceinfo(nProduceInfo);
		msg.set_nemployeeinfo(nEmployeeInfo);
		return msg.SerializeToString(&strInfo);
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::ManualSyncParameter msg;
		msg.set_nbranchinfo(nBranchInfo);
		msg.set_nproduceinfo(nProduceInfo);
		msg.set_nemployeeinfo(nEmployeeInfo);
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
	ST_ManualSyncParameter(const ST_ManualSyncParameter& src)
	{
		nBranchInfo = src.nBranchInfo;
		nProduceInfo = src.nProduceInfo;
		nEmployeeInfo = src.nEmployeeInfo;
	}
	ST_ManualSyncParameter& operator=(const ST_ManualSyncParameter& src)
	{
		nBranchInfo = src.nBranchInfo;
		nProduceInfo = src.nProduceInfo;
		nEmployeeInfo = src.nEmployeeInfo;
		return *this;
	}
};
struct ST_ScriptInfo
{
	string strScriptId;
	string strBusinessCode;
	string strBusinessType;		
	string strScriptContent;				
	int  nExtendedInfo;	
	string strExtendedInfo1;
	string strExtendedInfo2;
	ST_ScriptInfo()
	{
		nExtendedInfo = 0;
	}
	ST_ScriptInfo(BFIS::ScriptInfo& msg)
	{
		strScriptId = msg.strscriptid();
		strBusinessCode = msg.strbusinesscode();
		strBusinessType = msg.strbusinesstype();
		strScriptContent = msg.strscriptcontent();
		nExtendedInfo = msg.nextendedinfo();
		strExtendedInfo1 = msg.strextendedinfo1();
		strExtendedInfo2 = msg.strextendedinfo2();
	}
	bool operator == (const ST_ScriptInfo& r)
	{
		if (this->strScriptId.compare(r.strScriptId) == 0
			&& this->nExtendedInfo == r.nExtendedInfo
			&& this->strBusinessCode.compare(r.strBusinessCode) == 0
			&& this->strBusinessType.compare(r.strBusinessType) == 0
			&& this->strScriptContent.compare(r.strScriptContent) == 0
			&& this->strExtendedInfo1.compare(r.strExtendedInfo1) == 0
			&& this->strExtendedInfo2.compare(r.strExtendedInfo2) == 0)
			return true;
		return false;
	}
	bool ConvertToString(std::string& strInfo)
	{
		BFIS::ScriptInfo msg;
		msg.set_strscriptid(strScriptId);
		msg.set_strbusinesscode(strBusinessCode);
		msg.set_strbusinesstype(strBusinessType);
		msg.set_strscriptcontent(strScriptContent);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		return msg.SerializeToString(&strInfo);
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::ScriptInfo msg;
		msg.set_strscriptid(strScriptId);
		msg.set_strbusinesscode(strBusinessCode);
		msg.set_strbusinesstype(strBusinessType);
		msg.set_strscriptcontent(strScriptContent);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		msg.set_strextendedinfo2(strExtendedInfo2);
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
};
struct ST_OperateLogInfo
{
	string  strOperateLogId;
	string	strModule;
	string	strOperateEvent;
	string	strIp;
	string  strEmployeeId;
	string	strBranchId;
	string stOperateTime;
	int    nExtendedInfo;
	string	strExtendedInfo1;
	ST_OperateLogInfo()
	{
		nExtendedInfo = 0;
	}
	ST_OperateLogInfo(BFIS::OperateLogInfo& msg)
	{
		strOperateLogId = msg.stroperatelogid();
		strModule = msg.strmodule();
		strOperateEvent = msg.stroperateevent();
		strIp = msg.strip();
		strEmployeeId = msg.stremployeeid();
		strBranchId = msg.strbranchid();
		nExtendedInfo = msg.nextendedinfo();
		stOperateTime = msg.stoperatetime();
		strExtendedInfo1 = msg.strextendedinfo1();
	}
	bool ConvertToString(std::string& strInfo)
	{
		BFIS::OperateLogInfo msg;
		msg.set_stroperatelogid(strOperateLogId);
		msg.set_strmodule(strModule);
		msg.set_stroperateevent(strOperateEvent);
		msg.set_strip(strIp);
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strbranchid(strBranchId);
		msg.set_stoperatetime(stOperateTime);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		return msg.SerializeToString(&strInfo);
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::OperateLogInfo msg;
		msg.set_stroperatelogid(strOperateLogId);
		msg.set_strmodule(strModule);
		msg.set_stroperateevent(strOperateEvent);
		msg.set_strip(strIp);
		msg.set_stremployeeid(strEmployeeId);
		msg.set_strbranchid(strBranchId);
		msg.set_stoperatetime(stOperateTime);
		msg.set_nextendedinfo(nExtendedInfo);
		msg.set_strextendedinfo1(strExtendedInfo1);
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
};

struct ST_DiskAndConnectStatus
{
	string strBranchId;  //网点id
	int nConnectStatus;  //连接状态,1 已连接 0 断开
	int nDiskTatolSpace; //磁盘总空间，单位M
	int nDiskFreeSpace;  //磁盘剩余空间
	ST_DiskAndConnectStatus()
	{
		nConnectStatus = 0;
		nDiskTatolSpace = 0;
		nDiskFreeSpace = 0;
	}
	ST_DiskAndConnectStatus(BFIS::DiskAndConnectStatus& msg)
	{
		strBranchId = msg.strbranchid();
		nConnectStatus = msg.nconnectstatus();
		nDiskTatolSpace = msg.ndisktatolspace();
		nDiskFreeSpace = msg.ndiskfreespace();
	}
	bool ConvertToString(std::string& strInfo)
	{
		BFIS::DiskAndConnectStatus msg;
		msg.set_strbranchid(strBranchId);
		msg.set_nconnectstatus(nConnectStatus);
		msg.set_ndisktatolspace(nDiskTatolSpace);
		msg.set_ndiskfreespace(nDiskFreeSpace);
		return msg.SerializeToString(&strInfo);
	}
	bool ConvertToArrary(char* pBuf,int* nSize)
	{
		BFIS::DiskAndConnectStatus msg;
		msg.set_strbranchid(strBranchId);
		msg.set_nconnectstatus(nConnectStatus);
		msg.set_ndisktatolspace(nDiskTatolSpace);
		msg.set_ndiskfreespace(nDiskFreeSpace);
		bool bSeralizeSuccess = false;
		if(pBuf != NULL)
			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
		return bSeralizeSuccess;
	}
};
//struct ST_SyncParameter
//{
//	string strBasicSet;
//	string strStoreSet;
//	string strPwdSet;
//	ST_SyncParameter()
//	{
//		
//	}
//	ST_SyncParameter(BFIS::SyncParameter& msg)
//	{
//		strBasicSet = msg.strbasicset();
//		strStoreSet = msg.strstoreset();
//		strPwdSet = msg.strpwdset();	
//	}
//	bool ConvertToString(std::string& strInfo)
//	{
//		BFIS::SyncParameter msg;
//		msg.set_strbasicset(strBasicSet);
//		msg.set_strstoreset(strStoreSet);
//		msg.set_strpwdset(strPwdSet);
//		return msg.SerializeToString(&strInfo);
//	}
//	bool ConvertToArrary(char* pBuf,int* nSize)
//	{
//		BFIS::SyncParameter msg;
//		msg.set_strbasicset(strBasicSet);
//		msg.set_strstoreset(strStoreSet);
//		msg.set_strpwdset(strPwdSet);
//		bool bSeralizeSuccess = false;
//		if(pBuf != NULL)
//			bSeralizeSuccess = msg.SerializeToArray(pBuf,msg.ByteSize());
//		return bSeralizeSuccess;
//	}
//	ST_SyncParameter(const ST_SyncParameter& src)
//	{
//		strBasicSet = src.strBasicSet;
//		strStoreSet = src.strStoreSet;
//		strPwdSet = src.strPwdSet;
//	}
//	ST_SyncParameter& operator=(const ST_SyncParameter& src)
//	{
//		strBasicSet = src.strBasicSet;
//		strStoreSet = src.strStoreSet;
//		strPwdSet = src.strPwdSet;
//		return *this;
//	}
//};
#endif //_IBFIS_UNIQUE_DEFINE_H_
