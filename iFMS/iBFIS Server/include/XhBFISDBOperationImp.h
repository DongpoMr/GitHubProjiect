#pragma once
#include <afxmt.h>
#include "iSOC_Datatype_Define.h"
#include "iBFISDBOperation.h"
#include "XhBusinessInfoMan.hpp"
//#include "iCMSP_SimpleLock.h"
#include <vector>
#include <map>
#include "ITimer.h"
using namespace std;
#include "odbcinst.h"
#include "iSOC_ManLoginModule.h"
#import "msado26.tlb" rename_namespace("ADODB") rename("EOF","adoEOF") 
using namespace ADODB;

#include "Poco/Mutex.h"
struct ST_DBConnectionInfo
{
	_ConnectionPtr pDBConnection;
	bool	bIsFree;
	int     nCurrentThreadID;
	ST_DBConnectionInfo()
	{
		bIsFree = true;
		pDBConnection = NULL;
		nCurrentThreadID = GetCurrentThreadId();
	}

	ST_DBConnectionInfo& operator=(const ST_DBConnectionInfo& con)
	{
		pDBConnection = con.pDBConnection;
		bIsFree = con.bIsFree;
		nCurrentThreadID = 0;

	}
};
struct ST_UserGroupInfo
{
	int nUserGroupID;
	string strUserGroupName;
	string strICMSSign;
	int nICMSUserGroupID;
	string strParentICMSSign;
	int nICMSParentGroupID;
};
struct ST_SocUserInfo
{
	int nUserID;
	int nUserGroupID;
	int nICMSUserGroupID;
	string strICMSSign;
	int nICMSUserID;
	string strUserName;
};

struct ST_SubEquipment
{
	int nSubEquipmentID;		        //���豸��ID[int]
	string strICMSSign;				//����ϵͳ��ʶ[string]
	int nICMSSubEquipmentID;		    //�ڸ�ϵͳ�µ�ID[int]
	int nEquipmentID;				//���豸ID[int]
	int nMSCSID;					    //��Ⱥ��Ϣ��ID��iSwitch��[int]
	int nICMSEquipmentID;			//���豸����ϵͳ�µ�ID[int]
	string strSubName;					//���豸����[string]
	int nSubType;					//���豸���ʹ���[int]
};

class XhBFISDBOperationImp : public IBFISDBOperation,public ITimerCallbackSkin
{
public:
	XhBFISDBOperationImp();
	~XhBFISDBOperationImp();

	virtual void OnTimer(IN ISOC_ID iTimerID);

	virtual ISOC_BOOL KeepConnect();

	//ָ�����ݿ�����
	virtual ISOC_BOOL SetDataBaseName(IN string strName);

	virtual ISOC_BOOL SetLocalBranchId(string strGuid);
	//��ȡ��������Id
	virtual QueryResultType GetLocalBranchInfo(IN OUT ST_BranchInfo& stInfo);

	//�������ݿ�
	virtual ISOC_BOOL ConnectToDataBase(IN string strIP,IN string strPort,IN string strUser,IN string strPwd);

	//��ȡ���ݿ�������Ϣ
	virtual ISOC_BOOL GetDataBaseConfig(IN OUT string strIP,IN OUT string strPort,IN OUT string strUser,IN OUT string strPwd);

	//��ѯ���ݿ������״̬
	virtual ISOC_BOOL QuerySqlStatus();

	//�����ݿ�Ͽ����ӻ�����ʧ��ʱ������������
	virtual ISOC_BOOL ReConnectToDataBase();

	//�Ͽ����ݿ�����
	virtual ISOC_BOOL DisConnectDataBase();

	//nType = 1�����ͻ�����ѯ�ͻ���Ϣ 2�����ͻ����֤�Ų�ѯ�ͻ���Ϣ
	virtual ISOC_INT QueryClientInfoByCondition(IN int nType,IN int nCount,vector<ST_ClientInfo>& vecInfo);

	//����������Ϣ����
	virtual QueryResultType ManageBranchInfo(IN DBOperType enOperType, IN OUT ST_BranchInfo& sBranchInfo);
	QueryResultType QueryBranchInfoByID(IN OUT ST_BranchInfo& sBranchInfo,IN bool bOverlapped = true);
	ISOC_BOOL QueryDiffBranchInfo(IN int nAll,IN OUT vector<ST_BranchInfo>& vecBranchInfo); //nAll > 0,���������У����򷵻���Ҫͬ������

	//�ͻ���Ϣ����
	//nValue = 0ʱ��ʾ���ͻ�ID���£�����ֵ��ʾ�����֤�������
	//virtual QueryResultType ManageClientInfo(IN DBOperType enOperType, IN OUT ST_ClientInfo& sClientInfo, IN int nValue = 0);
	virtual QueryResultType QueryClientInfoByID(IN OUT ST_ClientInfo& sClientInfo,IN bool bOverlapped = true);
	QueryResultType QueryClientInfoByCredenitial(IN OUT ST_ClientInfo& sClientInfo,IN bool bOverlapped = true);
	ISOC_BOOL QueryDiffClientInfo(IN int nAll,IN OUT vector<ST_ClientInfo>& vecClientInfo,const string& strTime = ""); //nAll > 0,���������У����򷵻���Ҫͬ������

	//��ɫ��Ϣ����
	virtual QueryResultType ManageRoleInfo(IN DBOperType enOperType, IN OUT ST_RoleInfo& sRoleInfo);
	QueryResultType QueryRoleInfoByID(IN OUT ST_RoleInfo& sRoleInfo,IN bool bOverlapped = true);
	QueryResultType ManageClientInfo(DBOperType enOperType, ST_ClientInfo & sClientInfo, IN int nValue);
	ISOC_BOOL QueryDiffRoleInfo(IN int nAll,IN OUT vector<ST_RoleInfo>& vecRoleInfo); //nAll > 0,���������У����򷵻���Ҫͬ������

	//��Ʒ��Ϣ����
	virtual QueryResultType ManageProduceInfo(IN DBOperType enOperType, IN OUT ST_ProduceInfo& sProduceInfo);
	QueryResultType QueryProduceInfoByID(IN OUT ST_ProduceInfo& sProduceInfo,IN bool bOverlapped = true);
	ISOC_BOOL QueryDiffProduceInfo(IN int nAll,IN OUT vector<ST_ProduceInfo>& vecProduceInfo); //nAll > 0,���������У����򷵻���Ҫͬ������
	virtual QueryResultType QueryProduceNeed2Sync(IN string strSyncTime,IN OUT vector<ST_ProduceInfo>& vecInfo);
	virtual QueryResultType QueryMinProduceSyncTime(OUT string& strSyncTime);

	//ҵ����Ϣ����
	virtual QueryResultType ManageBusinessInfo(IN DBOperType enOperType, IN OUT ST_BusinessInfo& sBusinessInfo);
	virtual QueryResultType QueryBusinessInfoByID(IN OUT ST_BusinessInfo& sBusinessInfo,IN bool bOverlapped = true);
	virtual QueryResultType QueryBusinessInfoBySerialNumber(IN OUT ST_BusinessInfo& sBusinessInfo,IN bool bOverlapped = true);
	ISOC_BOOL QueryDiffBusinessInfo(IN int nAll,IN OUT vector<ST_BusinessInfo>& vecBusinessInfo); //nAll > 0,���������У����򷵻���Ҫͬ������

	virtual QueryResultType QueryBusinessInfoByCondition(ST_BusinessQueryParam stInfo,IN OUT vector<ST_BusinessInfo>& vecInfo);
	virtual QueryResultType QueryBusinessInfoUnFinished(IN OUT vector<ST_BusinessInfo>& vecInfo);
	virtual QueryResultType QueryBusinessFileInfoByBusinessInfoId(string strInfo,IN OUT vector<ST_BusinessFileInfo>& vecInfo);
	virtual QueryResultType QueryBusinessRelateInfoByBusinessInfoId(string strInfo,IN OUT vector<ST_BusinessRelateInfo>& vecInfo);
	virtual QueryResultType QueryBusinessInfoCountByCondition(ST_BusinessQueryParam stInfo,IN OUT int& nCount);
	//��ѯ�ͻ�����ʹ�õĲ�ƷId�Լ�ʹ�ô���
	virtual QueryResultType QueryBusinessInfoByEmployeeIdAndCount(string strId,int nCount,IN OUT map<std::string,int>& mapInfo);
	virtual QueryResultType QueryHotProduceIdByCount(int nCount,IN OUT map<std::string,int>& mapInfo);

	//Ա����Ϣ����
	virtual QueryResultType ManageEmployeeInfo(IN DBOperType enOperType, IN OUT ST_EmployeeInfo& sEmployeeInfo);
	QueryResultType QueryEmployeeInfoByID(IN OUT ST_EmployeeInfo& sEmployeeInfo,IN bool bOverlapped = true);
	ISOC_BOOL QueryDiffEmployeeInfo(IN int nAll,IN OUT vector<ST_EmployeeInfo>& vecEmployeeInfo);
	ISOC_BOOL ManageEmployeeInfoAndSocUser(DBOperType enType,ST_EmployeeInfo& sEmployeeInfo);
	//��ԱȨ����Ϣ����
	virtual QueryResultType ManageEmployeePurviewInfo(IN DBOperType enOperType, IN OUT ST_EmployeePurviewInfo& sEmployeePurviewInfo);
	QueryResultType ManageEmployeePurviewInfoById(IN DBOperType enOperType, IN OUT ST_EmployeePurviewInfo& sEmployeePurviewInfo) override;
	QueryResultType QueryEmployeePurviewInfoByID(IN OUT ST_EmployeePurviewInfo& stEmployeePurviewInfo,IN bool bOverlapped = true);
	QueryResultType QueryEmployeePurviewInfoAll(IN OUT vector<ST_EmployeePurviewInfo>& vecEmployeePurviewInfo);
	ISOC_BOOL QueryDiffEmployeePurviewInfo(IN int nAll,IN OUT vector<ST_EmployeePurviewInfo>& vecEmployeePurviewInfo);

	//ҵ���ļ���Ϣ����
	virtual QueryResultType ManageBusinessFileInfo(IN DBOperType enOperType, IN OUT ST_BusinessFileInfo& sBusinessFileInfo);
	QueryResultType QueryBusinessFileInfoByID(IN OUT ST_BusinessFileInfo& sBusinessFileInfo,IN bool bOverlapped = true);
	ISOC_BOOL QueryDiffBusinessFileInfo(IN int nAll,IN OUT vector<ST_BusinessFileInfo>& vecBusinessFileInfo);

	//ҵ�������Ϣ����
	virtual QueryResultType ManageBusinessRelationInfo(IN DBOperType enOperType, IN OUT ST_BusinessRelateInfo& sBusinessRelationInfo);
	QueryResultType QueryBusinessRelationInfoByID(IN OUT ST_BusinessRelateInfo& sBusinessRelationInfo,IN bool bOverlapped = true);
	ISOC_BOOL QueryDiffBusinessRelationInfo(IN int nAll,IN OUT vector<ST_BusinessRelateInfo>& vecBusinessRelationInfo);

	//�û�Ȩ����Ϣ����
	virtual QueryResultType ManagePurviewInfo(IN DBOperType enOperType, IN OUT ST_PurviewInfo& sPurviewInfo);
	QueryResultType QueryPurviewInfoByID(IN OUT ST_PurviewInfo& sPurviewInfo,IN bool bOverlapped = true);
	ISOC_BOOL QueryDiffPurviewInfo(IN int nAll,IN OUT vector<ST_PurviewInfo>& vecPurviewInfo);

	//��ɫȨ����Ϣ����
	virtual QueryResultType ManageRolePurviewInfo(IN DBOperType enOperType, IN OUT ST_RolePurviewInfo& sRolePurviewInfo);
	QueryResultType QueryRolePurviewInfoByID(IN OUT ST_RolePurviewInfo& sRolePurviewInfo,IN bool bOverlapped = true);
	ISOC_BOOL QueryDiffRolePurviewInfo(IN int nAll,IN OUT vector<ST_RolePurviewInfo>& vecRolePurviewInfo);

	//�û���ϵӳ����Ϣ����
	virtual QueryResultType ManageUserMapInfo(IN DBOperType enOperType, IN OUT ST_UserMapInfo& sUserMapInfo);
	QueryResultType QueryUserMapInfoByID(IN OUT ST_UserMapInfo& sUserMapInfo,IN bool bOverlapped = true);
	ISOC_BOOL QueryDiffUserMapInfo(IN int nAll,IN OUT vector<ST_UserMapInfo>& vecUserMapInfo);

	//����Key-Value��
	virtual ISOC_INT ManageTransparentData(DBOperType oper,std::string strType,std::string strCode,std::string strValue);
	virtual ISOC_INT QueryKeyValueInfoByTypeAndCode(std::string strType,std::string strCode,vector<ST_KeyValueInfo>& vecKeyValueInfo);

	//��������ƻ���
	virtual ISOC_INT ManageTaskPlanInfo(DBOperType oper,IN OUT vector<ST_TaskPlan>& vecInfos);

	//��������Ϣ
	virtual QueryResultType ManageScriptInfo(IN DBOperType enOperType, IN OUT ST_ScriptInfo& sScriptInfo);
	QueryResultType QueryScriptInfoByID(IN OUT ST_ScriptInfo& sScriptInfo,IN bool bOverlapped = true);
	ISOC_BOOL QueryDiffScriptInfo(IN int nAll,IN OUT vector<ST_ScriptInfo>& vecScriptInfo);
	//���������־��Ϣ
	virtual QueryResultType ManageOperateLogInfo(IN DBOperType enOperType, IN OUT ST_OperateLogInfo& sOperateLogInfo);
	virtual ISOC_BOOL QueryOperateLogInfoByEmployeeId(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strEmployeeId);
	//����ͬ�����
	virtual ISOC_BOOL SetSyncComplete(IN SyncDataType enDataType,IN string strId);

	//ɾ����Ϣ
	virtual ISOC_BOOL DeleteInfoById(IN SyncDataType enDataType,IN string strId);

	//������֤�Ƿ����
	virtual ISOC_BOOL GetIsCredenitialExisted(IN string strCredenitial);

	//��ȡ������Ϣ
	virtual ISOC_INT QueryBranchInfo(vector<ST_BranchInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	//��ȡ�ͻ���Ϣ
	virtual ISOC_INT QueryClientInfo(vector<ST_ClientInfo>& vecInfos ,const string& strTime = "", DWORD_PTR dwReserved = 0);

	//��ȡ��ɫ��Ϣ
	virtual ISOC_INT QueryRoleInfo(vector<ST_RoleInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	//��ȡ��Ʒ��Ϣ
	virtual ISOC_INT QueryProduceInfo(vector<ST_ProduceInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	//��ȡҵ����Ϣ
	virtual ISOC_INT QueryBusinessInfo(vector<ST_BusinessInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	//��ȡҵ���ļ���Ϣ
	virtual ISOC_INT QueryBusinessFileInfo(vector<ST_BusinessFileInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	//��ȡҵ�������Ϣ
	virtual ISOC_INT QueryBusinessRelateInfo(vector<ST_BusinessRelateInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	//��ȡԱ����Ϣ
	virtual ISOC_INT QueryEmployeeInfo(vector<ST_EmployeeInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	//��ȡԱ��Ȩ����Ϣ
	virtual ISOC_INT QueryEmployeePurviewInfo(vector<ST_EmployeePurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	//��ȡȨ����Ϣ
	virtual ISOC_INT QueryPurviewInfo(vector<ST_PurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	//��ȡ�û���Ȩ����Ϣ
	virtual ISOC_INT QueryRolePurviewInfo(vector<ST_RolePurviewInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	//��ȡ�û���ϵӳ����Ϣ
	virtual ISOC_INT QueryUserMapInfo(vector<ST_UserMapInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	virtual ISOC_INT QueryScriptInfo(vector<ST_ScriptInfo>& vecInfos, DWORD_PTR dwReserved = 0);

	virtual ISOC_BOOL QueryClientInfoLastSyncTime(CString& strTime,DWORD_PTR dwReserved = 0);

	//���ñ��������Ƿ�Ǩ�Ƶı�ʶ
	virtual ISOC_BOOL SetMigratedBusinessFileInfo(std::string strRecordId,int nMigrated = 0);
	//����ҵ����Ϣ�Ƿ�Ǩ�Ʊ�ʶ
	virtual ISOC_BOOL SetMigratedBusinessInfo(std::string strBusinessInfoId,int nMigrated = 0);

	//��ȡδ��Ǩ�Ƶı�������
	virtual QueryResultType QueryTaskNotMigrated(vector<ST_BusinessFileInfo>& vecInfos,int nCount,int nMigrated = 0);

	virtual QueryResultType QueryTaskNotMigrated(vector<ST_BusinessInfo>& vecInfos,int nCount,int nMigrated = 0);

	virtual QueryResultType ManageMigrateLogInfo(IN DBOperType enOperType,IN OUT ST_MigrateLogInfo& stInfo);
	virtual QueryResultType QueryMigrateLogInfoByCondition(IN const ST_QueryCondition& stCondition,std::vector<ST_MigrateLogInfo>& vecInfo);
	virtual QueryResultType QueryMigrateLogInfoCountByCondition(IN const ST_QueryCondition& stCondition,int& nTotalCount);

	static int __stdcall OnGotEquipmentPermissionDataCallback(ISOC_DWORDPTR dwUserCookie, ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen);
	static int __stdcall OnGotUserGroupDataCallback(ISOC_DWORDPTR dwUserCookie, ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen);
	static int __stdcall OnUserCreateStatusCallback(ISOC_DWORDPTR dwUserCookie, ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen);
	int GotEquipmentPermissionDataCallback(ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen);
	int GotUserGroupDataCallback(ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen);
	int UserCreateStatusCallback(ISOC_UINT64 fromAddr, ISOC_BYTE* pData, ISOC_INT dataLen);;
	ISOC_INT QueryDeskStatus(IN std::vector<std::string> vecDisk,OUT int& nDiskTotal,OUT int& nDiskFree);
	ISOC_BOOL GetMCSessoon(LONG_PTR pMCSession);
	ST_DBConnectionInfo* GetDBConnection2();
	int  FinishedUseConnection(ST_DBConnectionInfo* pDBCon);
	ISOC_BOOL IsHaveOnUserGroup();
	ISOC_BOOL SendReqGetSocUserGroup();
	ISOC_BOOL SendReqGetEquipmentPermission();
	ISOC_BOOL SendReqCreateUserGroup();
	ISOC_BOOL SendReqCreateUser(ST_EmployeeInfo& sEmployeeInfo,ST_UserGroupInfo& sUserGroupInfo);
	ISOC_BOOL SendReqModPassword(ST_SocUserInfo& stUserInfo,ST_EmployeeInfo& stEmployee);
	ISOC_BOOL SendReqSetUserPermission(ST_SocUserInfo& stUserInfo);
	ISOC_BOOL UpdateUserPermission(vector<ST_EmployeeInfo>& stEmployeeInfo);
	ISOC_BOOL SendReqSetUserGroupPermission(ST_UserGroupInfo& sUserGroupInfo);
	ISOC_BOOL XhBFISDBOperationImp::QueryNeedDelOperateLogInfo(OUT vector<ST_OperateLogInfo>& vecInfos,IN string strTime);
private:
	int CreateNewGuid(std::string& strGUID);
	//void GuidProducer(CString& strGuid);
	//BOOL RestoreLastSyncTime(CString strTime);
	//BOOL ReadLastSyncTime(CString& strTime);
	BOOL ExecuteSQL(_bstr_t strSQL,_RecordsetPtr& CRest,int& nRestAff);
	BOOL ExecuteSQLSafe( _ConnectionPtr& pcon, _bstr_t strSQL,_RecordsetPtr& CRest,int& iRestAff );
	_ConnectionPtr& GetConnection();
	BOOL ReconectByConnection(_ConnectionPtr& pcon);
	//BOOL ExcuteSQLByCmd(ST_ClientInfo stClientInfo);
	BOOL TempWayToAddClientInfo(ST_ClientInfo stClientInfo);

	Poco::FastMutex	        m_csDBLock;
	BOOL			        m_bIsDbConnection;
	ST_DBConnectionInfo*    m_pConInfo;
	int					    m_nConnectCount;

	string                  m_strIp;
	string                  m_strPort;
	string                  m_strUID;
	string                  m_strPWD;
	string					m_strDataBaseName;

	ITimer*					m_pTimer;
	string					m_strLocalBranchId;
	XhBusinessInfoMan		m_BusinessMan;
	LONG_PTR                m_pMCSeesion; 
	int                     m_nCount;
	int                     m_ResultCode;

	ST_RoleInfo   m_strRoleInfo;
	vector<ST_UserGroupInfo> m_vecUserGroupInfo;
	vector<ST_SubEquipment> m_vecSubEquipment;
	vector<ST_SocUserInfo> m_vecUserInfo;
};

class SimpleConnection  //ʹ��ʱ��ȷ����_RecordsetPtr֮ǰ����
{
public:
	_ConnectionPtr m_pCon;
	XhBFISDBOperationImp* m_pDBOper;
	static int g_nUseCount;
	static Poco::FastMutex g_csLockCount;
	ST_DBConnectionInfo* m_pDBCon;
	SimpleConnection(XhBFISDBOperationImp* pDBOper)
	{
		m_pDBOper = pDBOper;
		m_pDBCon = pDBOper->GetDBConnection2();
		//m_pCon = pDBOper->GetConnection();
		m_pCon = m_pDBCon->pDBConnection;
	}
	~SimpleConnection()
	{
		m_pDBOper->FinishedUseConnection(m_pDBCon);
	}
	SimpleConnection& operator = (const SimpleConnection& src)
	{
		m_pDBOper = src.m_pDBOper;
		m_pCon = src.m_pCon;
		return *this;
	}
	SimpleConnection(const SimpleConnection& src)
	{
		m_pDBOper = src.m_pDBOper;
		m_pCon = src.m_pCon;
	}
private:    
	SimpleConnection()
	{
		m_pCon = nullptr;
		m_pDBOper = nullptr;
	}
};
