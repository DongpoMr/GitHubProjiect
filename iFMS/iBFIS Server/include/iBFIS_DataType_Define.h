#pragma once
#ifndef _IBFIS_DATATYPE_DEFIINE_H_
#define _IBFIS_DATATYPE_DEFIINE_H_

#pragma pack(push, 1)
///////////////////////////////
///�������Ͷ���
///////////////////////////////

#define IBFIS_INT			int
#define IBFIS_STR			TCHAR*
#define IBFIS_DWORD			unsigned long
#define IBFIS_DWORDPTR		DWORD_PTR
#define IBFIS_BOOL			int
#define IBFIS_CHAR			TCHAR
#define IBFIS_FLOAT			float
#define IBFIS_DOUBLE		double
#define IBFIS_INT64			signed __int64
#define IBFIS_UINT64		unsigned __int64
#define IBFIS_BYTE			unsigned char
#define IBFIS_WORD			unsigned short
#define IBFIS_UINT			unsigned int
#define IBFIS_SHORT			short
#define IBFIS_VOID			void
#define IBFIS_bool			bool
#define IBFIS_LONG			long
#define IBFIS_LONGPTR		LONG_PTR
#define	IBFIS_HWND			HWND
#define IBFIS_SYSTEMTIME	SYSTEMTIME
#define	IBFIS_RECT			RECT
#define IBFIS_SIZE_T		size_t
#define IBFIS_TRUE			TRUE
#define IBFIS_FALSE			FALSE
#define IBFIS_true			true
#define IBFIS_false			false
#define IBFIS_OK			IBFIS_TRUE
#define IBFIS_FAIL			IBFIS_FALSE
#define IBFIS_NULL			NULL

///////////////////////////////
///ö�����Ͷ���
///////////////////////////////
//��������
enum BFIS_OperatorType
{
	BFIS_OT_LOGIN = 1,
	BFIS_OT_TRANSPARENT_DATA = 2,
	BFIS_OT_QUERY_PRODUCE = 3,
	BFIS_OT_DISCONNECT = 4,
	BFIS_OT_RECONNECT = 5,
	BFIS_OT_MANUALSYNC = 6
};
//����״̬
enum BFIS_OperatorState
{
	BFIS_OS_SUCCEEDED = 1,
	BFIS_OS_FAILED,
	BFIS_OS_FINISHED,
	BFIS_OS_UPDATE,
	BFIS_OS_TIMEOUT
};
//���»ص�����
enum BFIS_UpdateType
{
	BFIS_UT_ADD,
	BFIS_UT_MODIFY,
	BFIS_UT_DEL
};
//����״̬
enum TaskStatus	
{
	TSK_PROCESSING = 1,	//ִ����
	TSK_PAUSE, 			//��ͣ
	TSK_READY, 			//׼��
	TSK_FINISHED, 		//����
	TSK_FAILED,			//ʧ��
	TSK_STOP,           //ֹͣ
};
//��������
enum TaskType
{
	TSK_MANUAL = 1,		//�ֶ�
	TSK_AUTO			//�Զ�
};
//�ֶ������������
enum TaskControlType
{ 
	TSK_C_START = 1,	//����(�ֶ�����ֻ����ͣʱ����)
	TSK_C_STOP,			//ֹͣ
	TSK_C_CANCEL        //ȡ��(ɾ��)
};
//�ֶ�������������
enum ManulTaskStartType
{
	Immediately = 1,	//����
	Idle				//��ʱ
};
enum FinancialRiskLevel
{
	Low = 0,           //��
	HalfLow,           //�е�
	Midddle,           //�е�
	HalfHight          //�и�
};
enum FundRiskLevel
{
	A = 4,              // ���ͷ��յȼ�
	B,                  // �ͷ��յȼ�
	C,                  // �з��յȼ�
	D,                  // �ϸ߷��յȼ�
	E                   // �߷��յȼ�
};


///////////////////////////////
///�ṹ�嶨�嶨��
///////////////////////////////
struct IBFIS_ST_BranchInfo
{
	IBFIS_CHAR strBranchId[61];	//����Id
	IBFIS_CHAR strName[61];		//��������
	IBFIS_CHAR strAddress[61];	//�����ַ
	IBFIS_CHAR strContact[21];	//������ϵ��
	IBFIS_CHAR strPhone[21];	//����绰
	IBFIS_STR  pstrContent;		//��ע����
	IBFIS_INT  nExtendedInfo;	//��չ�ֶ�     ���̿ռ���� 0 ~ 100
	IBFIS_CHAR strExtendedInfo1[61];//��չ�ֶ�1    ����״̬��0�� ��ʾ������  ��1����ʾ����
	IBFIS_CHAR strExtendedInfo2[61];//��չ�ֶ�2
	IBFIS_CHAR strParentId[61]; //�ϼ�����Id
	IBFIS_INT  nIsLocal;		//��Ǳ�������
	IBFIS_CHAR strJDBRID[11];   //������
	IBFIS_CHAR strParentJDBRID[11];
	IBFIS_CHAR strParentName[31];
	IBFIS_CHAR strJDTYPE[11];
	IBFIS_ST_BranchInfo()
	{
		ZeroMemory(strBranchId,sizeof(strBranchId));
		ZeroMemory(strName,sizeof(strName));
		ZeroMemory(strAddress,sizeof(strAddress));
		ZeroMemory(strContact,sizeof(strContact));
		ZeroMemory(strPhone,sizeof(strPhone));
		nExtendedInfo = 0;
		ZeroMemory(strExtendedInfo1,sizeof(strExtendedInfo1));
		ZeroMemory(strExtendedInfo2,sizeof(strExtendedInfo2));
		ZeroMemory(strParentId,sizeof(strParentId));
		nIsLocal = 0;
		ZeroMemory(strJDBRID,sizeof(strJDBRID));
		ZeroMemory(strParentJDBRID,sizeof(strParentJDBRID));
		ZeroMemory(strParentName,sizeof(strParentName));
		ZeroMemory(strJDTYPE,sizeof(strJDTYPE));
		pstrContent = NULL;
	}
	IBFIS_ST_BranchInfo(const IBFIS_ST_BranchInfo& that)
	{
		_tcscpy(strBranchId,that.strBranchId);
		_tcscpy(strName,that.strName);
		_tcscpy(strAddress,that.strAddress);
		_tcscpy(strContact,that.strContact);
		_tcscpy(strPhone,that.strPhone);
		nExtendedInfo = that.nExtendedInfo;
		_tcscpy(strExtendedInfo1,that.strExtendedInfo1);
		_tcscpy(strExtendedInfo2,that.strExtendedInfo2);
		_tcscpy(strParentId,that.strParentId);
		pstrContent = NULL;
		nIsLocal = that.nIsLocal;
		_tcscpy(strJDBRID,that.strJDBRID);
		_tcscpy(strParentJDBRID,that.strParentJDBRID);
		_tcscpy(strParentName,that.strParentName);
		_tcscpy(strJDTYPE,that.strJDTYPE);
		if (that.pstrContent != NULL)
		{
			pstrContent = new IBFIS_CHAR[strlen(that.pstrContent) + 1];
			ZeroMemory(pstrContent,strlen(that.pstrContent) + 1);
			_tcscpy(pstrContent,that.pstrContent);
		}
	}
	IBFIS_ST_BranchInfo& operator =(const IBFIS_ST_BranchInfo& that)
	{
		_tcscpy(strBranchId,that.strBranchId);
		_tcscpy(strName,that.strName);
		_tcscpy(strAddress,that.strAddress);
		_tcscpy(strContact,that.strContact);
		_tcscpy(strPhone,that.strPhone);
		nExtendedInfo = that.nExtendedInfo;
		_tcscpy(strExtendedInfo1,that.strExtendedInfo1);
		_tcscpy(strExtendedInfo2,that.strExtendedInfo2);
		_tcscpy(strParentId,that.strParentId);
		pstrContent = NULL;
		nIsLocal = that.nIsLocal;
		_tcscpy(strJDBRID,that.strJDBRID);
		_tcscpy(strParentJDBRID,that.strParentJDBRID);
		_tcscpy(strParentName,that.strParentName);
		_tcscpy(strJDTYPE,that.strJDTYPE);
		if (that.pstrContent != NULL)
		{
			pstrContent = new IBFIS_CHAR[strlen(that.pstrContent) + 1];
			ZeroMemory(pstrContent,strlen(that.pstrContent) + 1);
			_tcscpy(pstrContent,that.pstrContent);
		}
		return *this;
	}
	~IBFIS_ST_BranchInfo()
	{
		if (pstrContent)
		{
			delete[] pstrContent;
			pstrContent = NULL;
		}
	}
};

struct IBFIS_ST_EmployeeInfo
{
	IBFIS_CHAR strEmployeeID[61];	//Ա��Id
	IBFIS_CHAR strBranchID[61];		//��������Id
	IBFIS_CHAR strName[256];		//�û���
	IBFIS_CHAR strPassword[61];		//����
	IBFIS_CHAR strCardID[129];		//��Id
	IBFIS_CHAR strRoleID[2001];		//������ɫId
	IBFIS_CHAR strPhone[21];		//�绰����
	IBFIS_STR  pstrPurviewInfo;		//Ա��Ȩ��
	IBFIS_INT  nExtendedInfo;
	IBFIS_CHAR strExtendedInfo1[61];
	IBFIS_CHAR strExtendedInfo2[61];
	IBFIS_INT  nFlag;				//���
	IBFIS_SYSTEMTIME stPasswordEidtTime; //�޸�����ʱ��
	IBFIS_CHAR strJDBRID[31];       //
	IBFIS_CHAR strTLNUM[21];        //��Ա���
	IBFIS_CHAR strTEL[21]; 
	IBFIS_CHAR strGW[21]; 
	IBFIS_CHAR strSTS[21]; 
	IBFIS_CHAR strTLINST[11];
	IBFIS_CHAR strUSERNAME[21];
	IBFIS_CHAR strROLENAME[21];
	IBFIS_CHAR strUSERSTATUS[11];
	IBFIS_INT nPassErrorCount;
	IBFIS_ST_EmployeeInfo() 
	{
		ZeroMemory(strEmployeeID, sizeof(strEmployeeID));
		ZeroMemory(strBranchID,   sizeof(strBranchID));
		ZeroMemory(strName,       sizeof(strName));
		ZeroMemory(strPassword,   sizeof(strPassword));
		ZeroMemory(strCardID,     sizeof(strCardID));
		ZeroMemory(strRoleID,     sizeof(strRoleID));
		ZeroMemory(strPhone,      sizeof(strPhone));
		ZeroMemory(strExtendedInfo1,sizeof(strExtendedInfo1));
		ZeroMemory(strExtendedInfo2,sizeof(strExtendedInfo2));
		ZeroMemory(strJDBRID,sizeof(strJDBRID));
		ZeroMemory(strTLNUM,sizeof(strTLNUM));
		ZeroMemory(strTEL,sizeof(strTEL));
		ZeroMemory(strGW,sizeof(strGW));
		ZeroMemory(strSTS,sizeof(strSTS));
		ZeroMemory(strTLINST,sizeof(strTLINST));
		ZeroMemory(strUSERNAME,sizeof(strUSERNAME));
		ZeroMemory(strROLENAME,sizeof(strROLENAME));
		ZeroMemory(strUSERSTATUS,sizeof(strUSERSTATUS));
		pstrPurviewInfo = NULL;
		nFlag = 0;
		nExtendedInfo = 0;
		nPassErrorCount = 0;
	}
	IBFIS_ST_EmployeeInfo(const IBFIS_ST_EmployeeInfo& that)
	{
		_tcscpy(strEmployeeID,that.strEmployeeID);
		_tcscpy(strBranchID,that.strBranchID);
		_tcscpy(strName,that.strName);
		_tcscpy(strPassword,that.strPassword);
		_tcscpy(strCardID,that.strCardID);
		_tcscpy(strRoleID,that.strRoleID);
		_tcscpy(strPhone,that.strPhone);
		nExtendedInfo = that.nExtendedInfo;
		_tcscpy(strExtendedInfo1,that.strExtendedInfo1);
		_tcscpy(strExtendedInfo2,that.strExtendedInfo2);
		_tcscpy(strJDBRID,that.strJDBRID);
		_tcscpy(strTLNUM,that.strTLNUM);
		pstrPurviewInfo = NULL;
		nFlag = that.nFlag;
		stPasswordEidtTime.wDay = that.stPasswordEidtTime.wDay;
		stPasswordEidtTime.wHour = that.stPasswordEidtTime.wHour;
		stPasswordEidtTime.wYear = that.stPasswordEidtTime.wYear;
		stPasswordEidtTime.wMonth = that.stPasswordEidtTime.wMonth;
		stPasswordEidtTime.wMinute = that.stPasswordEidtTime.wMinute;
		stPasswordEidtTime.wSecond = that.stPasswordEidtTime.wSecond;
		stPasswordEidtTime.wDayOfWeek = that.stPasswordEidtTime.wDayOfWeek;
		stPasswordEidtTime.wMilliseconds = that.stPasswordEidtTime.wMilliseconds;
		_tcscpy(strTEL,that.strTEL);
		_tcscpy(strGW,that.strGW);
		_tcscpy(strSTS,that.strSTS);
		_tcscpy(strTLINST,that.strTLINST);
		_tcscpy(strUSERNAME,that.strUSERNAME);
		_tcscpy(strROLENAME,that.strROLENAME);
		_tcscpy(strUSERSTATUS,that.strUSERSTATUS);
		nPassErrorCount = that.nPassErrorCount;
		if (that.pstrPurviewInfo != NULL)
		{
			pstrPurviewInfo = new IBFIS_CHAR[strlen(that.pstrPurviewInfo) + 1];
			ZeroMemory(pstrPurviewInfo,strlen(that.pstrPurviewInfo) + 1);
			_tcscpy(pstrPurviewInfo,that.pstrPurviewInfo);
		}
	}
	IBFIS_ST_EmployeeInfo& operator = (const IBFIS_ST_EmployeeInfo& that)
	{
		_tcscpy(strEmployeeID,that.strEmployeeID);
		_tcscpy(strBranchID,that.strBranchID);
		_tcscpy(strName,that.strName);
		_tcscpy(strPassword,that.strPassword);
		_tcscpy(strCardID,that.strCardID);
		_tcscpy(strRoleID,that.strRoleID);
		_tcscpy(strPhone,that.strPhone);
		nExtendedInfo = that.nExtendedInfo;
		_tcscpy(strExtendedInfo1,that.strExtendedInfo1);
		_tcscpy(strExtendedInfo2,that.strExtendedInfo2);
		_tcscpy(strJDBRID,that.strJDBRID);
		_tcscpy(strTLNUM,that.strTLNUM);
		nFlag = that.nFlag;
		pstrPurviewInfo = NULL;
		stPasswordEidtTime.wDay = that.stPasswordEidtTime.wDay;
		stPasswordEidtTime.wHour = that.stPasswordEidtTime.wHour;
		stPasswordEidtTime.wYear = that.stPasswordEidtTime.wYear;
		stPasswordEidtTime.wMonth = that.stPasswordEidtTime.wMonth;
		stPasswordEidtTime.wMinute = that.stPasswordEidtTime.wMinute;
		stPasswordEidtTime.wSecond = that.stPasswordEidtTime.wSecond;
		stPasswordEidtTime.wDayOfWeek = that.stPasswordEidtTime.wDayOfWeek;
		stPasswordEidtTime.wMilliseconds = that.stPasswordEidtTime.wMilliseconds;
		_tcscpy(strTEL,that.strTEL);
		_tcscpy(strGW,that.strGW);
		_tcscpy(strSTS,that.strSTS);
		_tcscpy(strTLINST,that.strTLINST);
		_tcscpy(strUSERNAME,that.strUSERNAME);
		_tcscpy(strROLENAME,that.strROLENAME);
		_tcscpy(strUSERSTATUS,that.strUSERSTATUS);
		nPassErrorCount = that.nPassErrorCount;
		if (that.pstrPurviewInfo != NULL)
		{
			pstrPurviewInfo = new IBFIS_CHAR[strlen(that.pstrPurviewInfo) + 1];
			ZeroMemory(pstrPurviewInfo,strlen(that.pstrPurviewInfo) + 1);
			_tcscpy(pstrPurviewInfo,that.pstrPurviewInfo);
		}
		return *this;
	}
	~IBFIS_ST_EmployeeInfo()
	{
		if (pstrPurviewInfo)
		{
			delete[] pstrPurviewInfo;
			pstrPurviewInfo = NULL;
		}
	}
};

struct IBFIS_ST_EmployeeSocInfo
{
	IBFIS_CHAR strEmployeeID[61];	//Ա��Id
	IBFIS_CHAR strSocUserName[61];	//Soc�û�
	IBFIS_CHAR strSocUserPwd[61];	//Soc����
};
struct IBFIS_ST_PurviewInfo
{
	IBFIS_CHAR strPurviewInfoID[61];	//Ȩ��Id
	IBFIS_CHAR strParentPurviewID[61];	//��Ȩ��Id
	IBFIS_CHAR strPurviewCode[61];		//Ȩ��Ψһ����
	IBFIS_CHAR strDescription[129];		//Ȩ������
	IBFIS_INT  nExtendedInfo;
	IBFIS_CHAR strExtendedInfo1[61];
	IBFIS_CHAR strExtendedInfo2[61];
	IBFIS_ST_PurviewInfo()
	{
		ZeroMemory(strPurviewInfoID, sizeof(strPurviewInfoID));
		ZeroMemory(strParentPurviewID, sizeof(strParentPurviewID));
		ZeroMemory(strPurviewCode, sizeof(strPurviewCode));
		ZeroMemory(strDescription, sizeof(strDescription));
		nExtendedInfo = 0;
		ZeroMemory(strExtendedInfo1,sizeof(strExtendedInfo1));
		ZeroMemory(strExtendedInfo2,sizeof(strExtendedInfo2));
	}
};

struct IBFIS_ST_RoleInfo
{
	IBFIS_CHAR strRoleInfoID[61];	//��ɫId
	IBFIS_CHAR strBranchID[61];		//��������Id
	IBFIS_CHAR strName[61];			//��ɫ��
	IBFIS_INT  nRoleLevel;			//��ɫ�ȼ�
	IBFIS_INT  nExtendedInfo;		//��չ�ֶ�
	IBFIS_CHAR strExtendedInfo1[61];//��չ�ֶ�1
	IBFIS_CHAR strExtendedInfo2[61];//��չ�ֶ�2
	IBFIS_STR  pstrPurviewInfo;		//��ɫȨ��
	IBFIS_INT  nFlag;
	IBFIS_ST_RoleInfo()
	{
		ZeroMemory(strRoleInfoID, sizeof(strRoleInfoID));
		ZeroMemory(strBranchID, sizeof(strBranchID));
		ZeroMemory(strName, sizeof(strName));
		ZeroMemory(strExtendedInfo1, sizeof(strExtendedInfo1));
		ZeroMemory(strExtendedInfo2, sizeof(strExtendedInfo2));
		nExtendedInfo = 0;
		nRoleLevel = 0;
		pstrPurviewInfo = NULL;
		nFlag = 0;
	}
	IBFIS_ST_RoleInfo(const IBFIS_ST_RoleInfo& that)
	{
		_tcscpy(strRoleInfoID,that.strRoleInfoID);
		_tcscpy(strBranchID,that.strBranchID);
		_tcscpy(strName,that.strName);
		_tcscpy(strExtendedInfo1,that.strExtendedInfo1);
		_tcscpy(strExtendedInfo2,that.strExtendedInfo2);
		nRoleLevel = that.nRoleLevel;
		nExtendedInfo = that.nExtendedInfo;
		nFlag = that.nFlag;
		pstrPurviewInfo = NULL;
		if (that.pstrPurviewInfo != NULL)
		{
			pstrPurviewInfo = new IBFIS_CHAR[strlen(that.pstrPurviewInfo) + 1];
			ZeroMemory(pstrPurviewInfo,strlen(that.pstrPurviewInfo) + 1);
			_tcscpy(pstrPurviewInfo,that.pstrPurviewInfo);
		}
	}
	IBFIS_ST_RoleInfo& operator = (const IBFIS_ST_RoleInfo& that)
	{
		_tcscpy(strRoleInfoID,that.strRoleInfoID);
		_tcscpy(strBranchID,that.strBranchID);
		_tcscpy(strName,that.strName);
		_tcscpy(strExtendedInfo1,that.strExtendedInfo1);
		_tcscpy(strExtendedInfo2,that.strExtendedInfo2);
		nExtendedInfo = that.nExtendedInfo;
		nRoleLevel = that.nRoleLevel;
		nFlag = that.nFlag;
		pstrPurviewInfo = NULL;
		if (that.pstrPurviewInfo != NULL)
		{
			pstrPurviewInfo = new IBFIS_CHAR[strlen(that.pstrPurviewInfo) + 1];
			ZeroMemory(pstrPurviewInfo,strlen(that.pstrPurviewInfo) + 1);
			_tcscpy(pstrPurviewInfo,that.pstrPurviewInfo);
		}
		return *this;
	}
	~IBFIS_ST_RoleInfo()
	{
		if (pstrPurviewInfo)
		{
			delete[] pstrPurviewInfo;
			pstrPurviewInfo = NULL;
		}
	}
};

struct IBFIS_ST_Customer
{
	IBFIS_CHAR strCustomerId[61];	   //�ͻ�Id
	IBFIS_CHAR strName[61];			   //�ͻ���
	IBFIS_CHAR strCredenitialsType[21]; //֤������
	IBFIS_CHAR strCredenitial[61];	   //�ͻ����֤
	IBFIS_CHAR strPhone[21];		   //�ͻ��绰
	IBFIS_CHAR strContent[21];		   //��ע����
	IBFIS_INT  nExtendedInfo;
	IBFIS_CHAR strExtendedInfo1[61];
	IBFIS_CHAR strExtendedInfo2[61];
	IBFIS_ST_Customer()
	{
		ZeroMemory(strCustomerId, sizeof(strCustomerId));
		ZeroMemory(strName, sizeof(strName));
		ZeroMemory(strCredenitialsType,sizeof(strCredenitialsType));
		ZeroMemory(strCredenitial, sizeof(strCredenitial));
		ZeroMemory(strPhone, sizeof(strPhone));
		ZeroMemory(strContent, sizeof(strContent));
		nExtendedInfo = 0;
		ZeroMemory(strExtendedInfo1,sizeof(strExtendedInfo1));
		ZeroMemory(strExtendedInfo2,sizeof(strExtendedInfo2));
	}
};

struct IBFIS_ST_ProduceInfo
{
	IBFIS_CHAR strProduceId[61];		//��ƷId
	IBFIS_CHAR strName[101];			//��Ʒ����
	IBFIS_CHAR strProduceCode[101];		//��ƷΨһ����
	IBFIS_INT  nPeriod;					//����
	IBFIS_CHAR strRevenue[61];				
	IBFIS_INT  nMiniAmount;
	IBFIS_CHAR strRiskLevel[61];
	IBFIS_CHAR strSerialNumber[101];
	IBFIS_SYSTEMTIME stPublishBeginTime;
	IBFIS_SYSTEMTIME stPublishEndTime;
	IBFIS_CHAR strProductionType[61];
	IBFIS_CHAR strApplicableCustomer[61];
	IBFIS_CHAR strRevenueType[61];
	IBFIS_CHAR strIncrementMoney[61];
	IBFIS_CHAR strCurrenyType[61];
	IBFIS_CHAR strSealsBranch[61];
	IBFIS_CHAR strRevenueInitialDay[61];
	IBFIS_CHAR strDeadLine[61];
	IBFIS_STR  pstrPaymenDay;
	IBFIS_STR  pstrTrusteeFee;
	IBFIS_CHAR strCommissionCharge[61];
	IBFIS_CHAR strTrustee[101];
	IBFIS_STR  pstrOverheadCharge;
	IBFIS_STR  pstrRevenueCalculation;
	IBFIS_STR  pstrContent;
	IBFIS_INT  nMaxTime;
	IBFIS_INT  nMiiniTime;
	IBFIS_INT  nStandardTime;
	IBFIS_STR  pstrPrequestion;
	IBFIS_INT  nIsPublished;
	IBFIS_INT  nIsEnabled;
	IBFIS_INT  nExtendedInfo;
	IBFIS_CHAR strExtendedInfo1[61];
	IBFIS_CHAR strExtendedInfo2[61];
	IBFIS_INT  nEnableMigrated;
	IBFIS_INT  nRecordExistDays;
	IBFIS_INT  nType;
	IBFIS_CHAR strRiskLevelDesc[51];
	IBFIS_INT  nPROD_LIFECYCLE;
	IBFIS_ST_ProduceInfo()
	{
		ZeroMemory(this, sizeof(IBFIS_ST_ProduceInfo));
	}
	IBFIS_ST_ProduceInfo(const IBFIS_ST_ProduceInfo& that)
	{
		_tcscpy(strProduceId,that.strProduceId);
		_tcscpy(strName,that.strName);
		_tcscpy(strProduceCode,that.strProduceCode);
		nPeriod = that.nPeriod;
		_tcscpy(strRevenue,that.strRevenue);
		nMiniAmount = that.nMiniAmount;
		_tcscpy(strRiskLevel,that.strRiskLevel);
		_tcscpy(strSerialNumber,that.strSerialNumber);
		stPublishBeginTime.wDay = that.stPublishBeginTime.wDay;
		stPublishBeginTime.wHour = that.stPublishBeginTime.wHour;
		stPublishBeginTime.wYear = that.stPublishBeginTime.wYear;
		stPublishBeginTime.wMonth = that.stPublishBeginTime.wMonth;
		stPublishBeginTime.wMinute = that.stPublishBeginTime.wMinute;
		stPublishBeginTime.wSecond = that.stPublishBeginTime.wSecond;
		stPublishBeginTime.wDayOfWeek = that.stPublishBeginTime.wDayOfWeek;
		stPublishBeginTime.wMilliseconds = that.stPublishBeginTime.wMilliseconds;
		stPublishEndTime.wDay = that.stPublishEndTime.wDay;
		stPublishEndTime.wHour = that.stPublishEndTime.wHour;
		stPublishEndTime.wYear = that.stPublishEndTime.wYear;
		stPublishEndTime.wMonth = that.stPublishEndTime.wMonth;
		stPublishEndTime.wMinute = that.stPublishEndTime.wMinute;
		stPublishEndTime.wSecond = that.stPublishEndTime.wSecond;
		stPublishEndTime.wDayOfWeek = that.stPublishEndTime.wDayOfWeek;
		stPublishEndTime.wMilliseconds = that.stPublishEndTime.wMilliseconds;
		_tcscpy(strProductionType,that.strProductionType);
		_tcscpy(strApplicableCustomer,that.strApplicableCustomer);
		_tcscpy(strRevenueType,that.strRevenueType);
		_tcscpy(strIncrementMoney,that.strIncrementMoney);
		_tcscpy(strCurrenyType,that.strCurrenyType);
		_tcscpy(strSealsBranch,that.strSealsBranch);
		_tcscpy(strRevenueInitialDay,that.strRevenueInitialDay);
		_tcscpy(strDeadLine,that.strDeadLine);
		_tcscpy(strCommissionCharge,that.strCommissionCharge);
		_tcscpy(strTrustee,that.strTrustee);
		nMaxTime = that.nMaxTime;
		nMiiniTime = that.nMiiniTime;
		nStandardTime = that.nStandardTime;
		nIsPublished = that.nIsPublished;
		nIsEnabled = that.nIsEnabled;
		pstrPaymenDay = NULL;
		nExtendedInfo = that.nExtendedInfo;
		_tcscpy(strExtendedInfo1,that.strExtendedInfo1);
		_tcscpy(strExtendedInfo2,that.strExtendedInfo2);
		if (that.pstrPaymenDay != NULL)
		{
			pstrPaymenDay = new IBFIS_CHAR[strlen(that.pstrPaymenDay) + 1];
			ZeroMemory(pstrPaymenDay,strlen(that.pstrPaymenDay) + 1);
			_tcscpy(pstrPaymenDay,that.pstrPaymenDay);
		}
		pstrTrusteeFee = NULL;
		if (that.pstrTrusteeFee != NULL)
		{
			pstrTrusteeFee = new IBFIS_CHAR[strlen(that.pstrTrusteeFee) + 1];
			ZeroMemory(pstrTrusteeFee,strlen(that.pstrTrusteeFee) + 1);
			_tcscpy(pstrTrusteeFee,that.pstrTrusteeFee);
		}
		pstrOverheadCharge = NULL;
		if (that.pstrOverheadCharge != NULL)
		{
			pstrOverheadCharge = new IBFIS_CHAR[strlen(that.pstrOverheadCharge) + 1];
			ZeroMemory(pstrOverheadCharge,strlen(that.pstrOverheadCharge) + 1);
			_tcscpy(pstrOverheadCharge,that.pstrOverheadCharge);
		}
		pstrRevenueCalculation = NULL;
		if (that.pstrRevenueCalculation != NULL)
		{
			pstrRevenueCalculation = new IBFIS_CHAR[strlen(that.pstrRevenueCalculation) + 1];
			ZeroMemory(pstrRevenueCalculation,strlen(that.pstrRevenueCalculation) + 1);
			_tcscpy(pstrRevenueCalculation,that.pstrRevenueCalculation);
		}
		pstrContent = NULL;
		if (that.pstrContent != NULL)
		{
			pstrContent = new IBFIS_CHAR[strlen(that.pstrContent) + 1];
			ZeroMemory(pstrContent,strlen(that.pstrContent) + 1);
			_tcscpy(pstrContent,that.pstrContent);
		}
		pstrPrequestion = NULL;
		if (that.pstrPrequestion != NULL)
		{
			pstrPrequestion = new IBFIS_CHAR[strlen(that.pstrPrequestion) + 1];
			ZeroMemory(pstrPrequestion,strlen(that.pstrPrequestion) + 1);
			_tcscpy(pstrPrequestion,that.pstrPrequestion);
		}
		nEnableMigrated = that.nEnableMigrated;
		nRecordExistDays = that.nRecordExistDays;
		nType = that.nType;
		_tcscpy(strRiskLevelDesc,that.strRiskLevelDesc);
		nPROD_LIFECYCLE = that.nPROD_LIFECYCLE;
	}
	IBFIS_ST_ProduceInfo& operator = (const IBFIS_ST_ProduceInfo& that)
	{
		_tcscpy(strProduceId,that.strProduceId);
		_tcscpy(strName,that.strName);
		_tcscpy(strProduceCode,that.strProduceCode);
		nPeriod = that.nPeriod;
		_tcscpy(strRevenue,that.strRevenue);
		nMiniAmount = that.nMiniAmount;
		_tcscpy(strRiskLevel,that.strRiskLevel);
		_tcscpy(strSerialNumber,that.strSerialNumber);
		stPublishBeginTime.wDay = that.stPublishBeginTime.wDay;
		stPublishBeginTime.wHour = that.stPublishBeginTime.wHour;
		stPublishBeginTime.wYear = that.stPublishBeginTime.wYear;
		stPublishBeginTime.wMonth = that.stPublishBeginTime.wMonth;
		stPublishBeginTime.wMinute = that.stPublishBeginTime.wMinute;
		stPublishBeginTime.wSecond = that.stPublishBeginTime.wSecond;
		stPublishBeginTime.wDayOfWeek = that.stPublishBeginTime.wDayOfWeek;
		stPublishBeginTime.wMilliseconds = that.stPublishBeginTime.wMilliseconds;
		stPublishEndTime.wDay = that.stPublishEndTime.wDay;
		stPublishEndTime.wHour = that.stPublishEndTime.wHour;
		stPublishEndTime.wYear = that.stPublishEndTime.wYear;
		stPublishEndTime.wMonth = that.stPublishEndTime.wMonth;
		stPublishEndTime.wMinute = that.stPublishEndTime.wMinute;
		stPublishEndTime.wSecond = that.stPublishEndTime.wSecond;
		stPublishEndTime.wDayOfWeek = that.stPublishEndTime.wDayOfWeek;
		stPublishEndTime.wMilliseconds = that.stPublishEndTime.wMilliseconds;
		_tcscpy(strProductionType,that.strProductionType);
		_tcscpy(strApplicableCustomer,that.strApplicableCustomer);
		_tcscpy(strRevenueType,that.strRevenueType);
		_tcscpy(strIncrementMoney,that.strIncrementMoney);
		_tcscpy(strCurrenyType,that.strCurrenyType);
		_tcscpy(strSealsBranch,that.strSealsBranch);
		_tcscpy(strRevenueInitialDay,that.strRevenueInitialDay);
		_tcscpy(strDeadLine,that.strDeadLine);
		_tcscpy(strCommissionCharge,that.strCommissionCharge);
		_tcscpy(strTrustee,that.strTrustee);
		nMaxTime = that.nMaxTime;
		nMiiniTime = that.nMiiniTime;
		nStandardTime = that.nStandardTime;
		nIsPublished = that.nIsPublished;
		nIsEnabled = that.nIsEnabled;
		pstrPaymenDay = NULL;
		nExtendedInfo = that.nExtendedInfo;
		_tcscpy(strExtendedInfo1,that.strExtendedInfo1);
		_tcscpy(strExtendedInfo2,that.strExtendedInfo2);
		if (that.pstrPaymenDay != NULL)
		{
			pstrPaymenDay = new IBFIS_CHAR[strlen(that.pstrPaymenDay) + 1];
			ZeroMemory(pstrPaymenDay,strlen(that.pstrPaymenDay) + 1);
			_tcscpy(pstrPaymenDay,that.pstrPaymenDay);
		}
		pstrTrusteeFee = NULL;
		if (that.pstrTrusteeFee != NULL)
		{
			pstrTrusteeFee = new IBFIS_CHAR[strlen(that.pstrTrusteeFee) + 1];
			ZeroMemory(pstrTrusteeFee,strlen(that.pstrTrusteeFee) + 1);
			_tcscpy(pstrTrusteeFee,that.pstrTrusteeFee);
		}
		pstrOverheadCharge = NULL;
		if (that.pstrOverheadCharge != NULL)
		{
			pstrOverheadCharge = new IBFIS_CHAR[strlen(that.pstrOverheadCharge) + 1];
			ZeroMemory(pstrOverheadCharge,strlen(that.pstrOverheadCharge) + 1);
			_tcscpy(pstrOverheadCharge,that.pstrOverheadCharge);
		}
		pstrRevenueCalculation = NULL;
		if (that.pstrRevenueCalculation != NULL)
		{
			pstrRevenueCalculation = new IBFIS_CHAR[strlen(that.pstrRevenueCalculation) + 1];
			ZeroMemory(pstrRevenueCalculation,strlen(that.pstrRevenueCalculation) + 1);
			_tcscpy(pstrRevenueCalculation,that.pstrRevenueCalculation);
		}
		pstrContent = NULL;
		if (that.pstrContent != NULL)
		{
			pstrContent = new IBFIS_CHAR[strlen(that.pstrContent) + 1];
			ZeroMemory(pstrContent,strlen(that.pstrContent) + 1);
			_tcscpy(pstrContent,that.pstrContent);
		}
		pstrPrequestion = NULL;
		if (that.pstrPrequestion != NULL)
		{
			pstrPrequestion = new IBFIS_CHAR[strlen(that.pstrPrequestion) + 1];
			ZeroMemory(pstrPrequestion,strlen(that.pstrPrequestion) + 1);
			_tcscpy(pstrPrequestion,that.pstrPrequestion);
		}
		nEnableMigrated = that.nEnableMigrated;
		nRecordExistDays = that.nRecordExistDays;
		nType = that.nType;
		_tcscpy(strRiskLevelDesc,that.strRiskLevelDesc);
		nPROD_LIFECYCLE = that.nPROD_LIFECYCLE;
		return *this;
	}
	~IBFIS_ST_ProduceInfo()
	{
		if (pstrPaymenDay)
		{
			delete[] pstrPaymenDay;
			pstrPaymenDay = NULL;
		}
		if (pstrTrusteeFee)
		{
			delete[] pstrTrusteeFee;
			pstrTrusteeFee = NULL;
		}
		if (pstrOverheadCharge)
		{
			delete[] pstrOverheadCharge;
			pstrOverheadCharge = NULL;
		}
		if (pstrRevenueCalculation)
		{
			delete[] pstrRevenueCalculation;
			pstrRevenueCalculation = NULL;
		}
		if (pstrContent)
		{
			delete[] pstrContent;
			pstrContent = NULL;
		}
		if (pstrPrequestion)
		{
			delete[] pstrPrequestion;
			pstrPrequestion = NULL;
		}
	}
};

struct IBFIS_ST_BusinessInfo
{
	IBFIS_CHAR strBusinessInfoID[61];	//ҵ��Id
	IBFIS_SYSTEMTIME stDateTime;		//ʱ��
	IBFIS_CHAR strBranchID[61];			//��������Id
	IBFIS_CHAR strCustomerID[61];		//�����ͻ�Id
	IBFIS_CHAR strEmployeeID[61];		//����Ա��Id
	IBFIS_CHAR strProduceID[61];		//������ƷId
	IBFIS_CHAR strSubequipmentID[61];	//�������豸Id
	IBFIS_CHAR strSubequipmentIcmsSign[61];//�������豸Icmsign
	IBFIS_INT  nExtendedInfo;
	IBFIS_CHAR strExtendedInfo1[61];
	IBFIS_CHAR strExtendedInfo2[61];
	IBFIS_CHAR strSerialNumber[61];
	IBFIS_INT  nMigrated;
	IBFIS_CHAR strFileCenter[64];
	IBFIS_CHAR strBusinessType[31];     //ҵ������  
	IBFIS_CHAR strCardNumber[61];       //����
	IBFIS_INT  nMarkerType;             //�������
	IBFIS_CHAR strCardType[21];         //������
	IBFIS_CHAR strMediumType[5];		
	IBFIS_CHAR strMediumNum[33];
	IBFIS_SYSTEMTIME stOffDisputeTime;
	IBFIS_ST_BusinessInfo()
	{
		ZeroMemory(this,sizeof(IBFIS_ST_BusinessInfo));
	}
	IBFIS_ST_BusinessInfo(const IBFIS_ST_BusinessInfo& that)
	{
		ZeroMemory(this,sizeof(IBFIS_ST_BusinessInfo));
		_tcscpy(strBusinessInfoID,that.strBusinessInfoID);
		stDateTime.wYear = that.stDateTime.wYear;
		stDateTime.wMonth = that.stDateTime.wMonth;
		stDateTime.wDay = that.stDateTime.wDay;
		stDateTime.wDayOfWeek = that.stDateTime.wDayOfWeek;
		stDateTime.wHour = that.stDateTime.wHour;
		stDateTime.wMinute = that.stDateTime.wMinute;
		stDateTime.wSecond = that.stDateTime.wSecond;
		stDateTime.wMilliseconds = that.stDateTime.wMilliseconds;
		_tcscpy(strBusinessInfoID,that.strBusinessInfoID);
		_tcscpy(strBranchID,that.strBranchID);
		_tcscpy(strCustomerID,that.strCustomerID);
		_tcscpy(strEmployeeID,that.strEmployeeID);
		_tcscpy(strProduceID,that.strProduceID);
		_tcscpy(strSubequipmentID,that.strSubequipmentID);
		_tcscpy(strSubequipmentIcmsSign,that.strSubequipmentIcmsSign);
		nExtendedInfo = that.nExtendedInfo;
		_tcscpy(strExtendedInfo1,that.strExtendedInfo1);
		_tcscpy(strExtendedInfo2,that.strExtendedInfo2);
		_tcscpy(strSerialNumber,that.strSerialNumber);
		_tcscpy(strFileCenter,that.strFileCenter);
		_tcscpy(strBusinessType,that.strBusinessType);
		_tcscpy(strCardNumber,that.strCardNumber);
		_tcscpy(strCardType,that.strCardType);
		_tcscpy(strMediumType,that.strMediumType);
		_tcscpy(strMediumNum,that.strMediumNum);
		stOffDisputeTime.wYear = that.stOffDisputeTime.wYear;
		stOffDisputeTime.wMonth = that.stOffDisputeTime.wMonth;
		stOffDisputeTime.wDay = that.stOffDisputeTime.wDay;
		stOffDisputeTime.wDayOfWeek = that.stOffDisputeTime.wDayOfWeek;
		stOffDisputeTime.wHour = that.stOffDisputeTime.wHour;
		stOffDisputeTime.wMinute = that.stOffDisputeTime.wMinute;
		stOffDisputeTime.wSecond = that.stOffDisputeTime.wSecond;
		stOffDisputeTime.wMilliseconds = that.stOffDisputeTime.wMilliseconds;
		nMigrated = that.nMigrated;
		nMarkerType = that.nMarkerType;
	}
};

struct IBFIS_ST_BusinessFileInfo
{
	IBFIS_CHAR strRecordID[61];			//¼��Id
	IBFIS_CHAR strBusinessInfoID[61];	//����ҵ��Id
	IBFIS_INT  nType;					//����
	IBFIS_CHAR strFileID[61];			//�ļ�Id
	IBFIS_SYSTEMTIME stRecordBegin;		//¼��ʼʱ��
	IBFIS_SYSTEMTIME stRecordEnd;		//¼�����ʱ��
	IBFIS_INT  nMigrated;				//�ж��Ƿ��Ѿ�Ǩ�� 1����Ǩ�� <1����δǨ��
	IBFIS_INT  nExtendedInfo;
	IBFIS_CHAR strExtendedInfo1[61];
	IBFIS_CHAR strExtendedInfo2[61];
	IBFIS_ST_BusinessFileInfo()
	{
		ZeroMemory(this,sizeof(IBFIS_ST_BusinessFileInfo));
	}
	IBFIS_ST_BusinessFileInfo(const IBFIS_ST_BusinessFileInfo& that)
	{
		_tcscpy(strRecordID,that.strRecordID);
		_tcscpy(strBusinessInfoID,that.strBusinessInfoID);
		nType = that.nType;
		_tcscpy(strFileID,that.strFileID);
		stRecordBegin.wYear = that.stRecordBegin.wYear;
		stRecordBegin.wMonth = that.stRecordBegin.wMonth;
		stRecordBegin.wDay = that.stRecordBegin.wDay;
		stRecordBegin.wDayOfWeek = that.stRecordBegin.wDayOfWeek;
		stRecordBegin.wHour = that.stRecordBegin.wHour;
		stRecordBegin.wMinute = that.stRecordBegin.wMinute;
		stRecordBegin.wSecond = that.stRecordBegin.wSecond;
		stRecordBegin.wMilliseconds = that.stRecordBegin.wMilliseconds;
		stRecordEnd.wYear = that.stRecordEnd.wYear;
		stRecordEnd.wMonth = that.stRecordEnd.wMonth;
		stRecordEnd.wDay = that.stRecordEnd.wDay;
		stRecordEnd.wDayOfWeek = that.stRecordEnd.wDayOfWeek;
		stRecordEnd.wHour = that.stRecordEnd.wHour;
		stRecordEnd.wMinute = that.stRecordEnd.wMinute;
		stRecordEnd.wSecond = that.stRecordEnd.wSecond;
		stRecordEnd.wMilliseconds = that.stRecordEnd.wMilliseconds;
		nExtendedInfo = that.nExtendedInfo;
		_tcscpy(strExtendedInfo1,that.strExtendedInfo1);
		_tcscpy(strExtendedInfo2,that.strExtendedInfo2);
	}
};

struct IBFIS_ST_BusinessRelateInfo
{
	IBFIS_CHAR strBusinessRelateInfoID[61];//ҵ������ļ�Id
	IBFIS_CHAR strBusinessInfoID[61];	//����ҵ��Id
	IBFIS_INT  nRelateType;				//��������
	IBFIS_CHAR strRelate1[101];			//��������1
	IBFIS_CHAR strRelate2[101];			//��������2
	IBFIS_STR  pstrRelate3;
	IBFIS_ST_BusinessRelateInfo()
	{
		ZeroMemory(this, sizeof(IBFIS_ST_BusinessRelateInfo));
	}
	IBFIS_ST_BusinessRelateInfo(const IBFIS_ST_BusinessRelateInfo& that)
	{
		_tcscpy(strBusinessRelateInfoID,that.strBusinessRelateInfoID);
		_tcscpy(strBusinessInfoID,that.strBusinessInfoID);
		nRelateType = that.nRelateType;
		_tcscpy(strRelate1,that.strRelate1);
		_tcscpy(strRelate2,that.strRelate2);
		pstrRelate3 = NULL;
		if (that.pstrRelate3 != NULL)
		{
			pstrRelate3 = new IBFIS_CHAR[strlen(that.pstrRelate3) + 1];
			ZeroMemory(pstrRelate3,strlen(that.pstrRelate3) + 1);
			_tcscpy(pstrRelate3,that.pstrRelate3);
		}
	}
	IBFIS_ST_BusinessRelateInfo& operator = (const IBFIS_ST_BusinessRelateInfo& that)
	{
		_tcscpy(strBusinessRelateInfoID,that.strBusinessRelateInfoID);
		_tcscpy(strBusinessInfoID,that.strBusinessInfoID);
		nRelateType = that.nRelateType;
		_tcscpy(strRelate1,that.strRelate1);
		_tcscpy(strRelate2,that.strRelate2);
		pstrRelate3 = NULL;
		if (that.pstrRelate3 != NULL)
		{
			pstrRelate3 = new IBFIS_CHAR[strlen(that.pstrRelate3) + 1];
			ZeroMemory(pstrRelate3,strlen(that.pstrRelate3) + 1);
			_tcscpy(pstrRelate3,that.pstrRelate3);
		}
		return *this;
	}
	~IBFIS_ST_BusinessRelateInfo()
	{
		if (pstrRelate3)
		{
			delete[] pstrRelate3;
			pstrRelate3 = NULL;
		}
	}
};

struct IBFIS_ST_BusinessQueryParam 
{
	IBFIS_CHAR strBranchId[61];		//��ѯ����Id
	IBFIS_CHAR strEmployeeId[61];	//��ѯԱ��Id
	IBFIS_CHAR strCustomerId[61];	//��ѯ�ͻ�Id
	IBFIS_CHAR strProduceId[61];	//��ѯ��ƷId
	IBFIS_CHAR strStartTime[61];	//��ʼʱ��
	IBFIS_CHAR strEndTime[61];		//����ʱ��
	IBFIS_INT    nPageSize ;		//ҳ����
	IBFIS_INT    nPageIndex;		//ҳ����
	IBFIS_INT    nRecordCount;		//�ܼ�¼��Ŀ
	IBFIS_CHAR strSerialNumber[61];	//��ˮ��
	IBFIS_CHAR strCredenitialsType[21]; //֤������
	IBFIS_CHAR strBusinessType[31]; //ҵ������
	IBFIS_CHAR strCardNumber[61];   //����
	IBFIS_INT nMarkerType;         //�������
	IBFIS_CHAR strRiskLevel[61];    //���յȼ�
	IBFIS_CHAR strConditionEx[2001];
	IBFIS_CHAR strMediumNum[33];
	IBFIS_CHAR strExtendedInfo2[61];
	IBFIS_ST_BusinessQueryParam()
	{
		ZeroMemory(this, sizeof(IBFIS_ST_BusinessQueryParam));
	}
};

struct IBFIS_ST_KeyValueInfo
{
	IBFIS_ST_KeyValueInfo()
	{
		ZeroMemory(this,sizeof(IBFIS_ST_KeyValueInfo));
	}
	IBFIS_CHAR strType[255];		//����
	IBFIS_CHAR strCode[255];		//Ψһ����
	IBFIS_CHAR strValue[255];		//ֵ
	IBFIS_INT  nExtendedInfo;
	IBFIS_CHAR strExtendedInfo1[61];
	IBFIS_CHAR strExtendedInfo2[61];
};

struct IBFIS_ST_ProduceUsedUsually
{
	IBFIS_ST_ProduceUsedUsually()
	{
		ZeroMemory(this,sizeof(IBFIS_ST_ProduceUsedUsually));
	}
	IBFIS_CHAR strInfoId[61];	//��ƷId
	IBFIS_INT	nCount;			//ʹ��Ƶ��
};

struct IBFIS_ST_TaskPlan
{
	IBFIS_ST_TaskPlan()
	{
		ZeroMemory(this,sizeof(IBFIS_ST_TaskPlan));
	}
	IBFIS_CHAR			strPlanID[61];	//�ƻ�Id
	IBFIS_SYSTEMTIME	strTimeBegin;	//�ƻ���ʼʱ��
	IBFIS_SYSTEMTIME	strTimeEnd;		//�ƻ�����ʱ��
	IBFIS_INT			nEnable;		//1.���� 0.������
	IBFIS_INT			nOrderID;		//����ID��Ŀǰֻ��1��2��3
};

struct IBFIS_ST_BackupTask
{
	IBFIS_ST_BackupTask()
	{
		ZeroMemory(strTaskID,61);
		ZeroMemory(strBusinessID,61);
		ZeroMemory(strProduceID,61);
		ZeroMemory(strEmployeeID,61);
		ZeroMemory(&strAutoTime,sizeof(IBFIS_SYSTEMTIME));
		ZeroMemory(&strBeginTime,sizeof(IBFIS_SYSTEMTIME));
		ZeroMemory(&strEndTime,sizeof(IBFIS_SYSTEMTIME));
		ZeroMemory(strLaunchEmployeeID,61);
		ZeroMemory(&sysTimeForBusiness,sizeof(IBFIS_SYSTEMTIME));
	}
	IBFIS_CHAR 			strTaskID[61];			//����id
	TaskType			enType;					//��������:�ֶ����Զ�
	TaskStatus			enStatus;				//����״̬:�����С���ͣ��׼�����������쳣
	IBFIS_CHAR			strBusinessID[61];		//����ҵ��id
	IBFIS_CHAR			strProduceID[61];		//����ҵ���Ʒid
	IBFIS_CHAR			strEmployeeID[61];		//����ҵ��Ա��id
	IBFIS_ST_Customer	stCustomer;				//����ҵ��ͻ���Ϣ
	IBFIS_SYSTEMTIME	strAutoTime;				//�Զ��������õĿ�ʼʱ��
	IBFIS_SYSTEMTIME	strBeginTime;			//����ʼʱ��
	IBFIS_SYSTEMTIME	strEndTime;				//�������ʱ��
	IBFIS_INT			nProcess;				//����,��enStatusΪTSK_PROCESSINGʱ��Ч
	IBFIS_CHAR			strLaunchEmployeeID[61];//�ֶ���������ID
	IBFIS_INT			nOrderID;				//����ID���������ȼ�
	IBFIS_SYSTEMTIME	sysTimeForBusiness;		//ҵ�����ʱ��
	IBFIS_CHAR			strExtendedInfo2[61];   //��ע��Ϣ
};

struct IBFIS_ST_MCServer
{
	IBFIS_CHAR strBranchId[61];	//����Id
	IBFIS_CHAR strName[61];		//��������
	IBFIS_CHAR strMCIP[20];     //MC ip
	IBFIS_WORD sMCPort;         //MC �˿�
	IBFIS_CHAR strMCUserName[20];   //MC ��½�û���
	IBFIS_CHAR strMCUserPwd[20];    //MC ��½����
	int        nIsLoal;         //�Ƿ��Ǳ���
	IBFIS_ST_MCServer()
	{
		ZeroMemory(strBranchId, 61);
		ZeroMemory(strName, 61);
		ZeroMemory(strMCIP, 20);
		ZeroMemory(strMCUserName, 20);
		ZeroMemory(strMCUserPwd, 20);
		sMCPort = 0;
		nIsLoal = 0;
	}

	IBFIS_ST_MCServer(const IBFIS_ST_MCServer& src)
	{
		lstrcpy(strBranchId, src.strBranchId);
		lstrcpy(strName, src.strName);
		lstrcpy(strMCIP, src.strMCIP);
		lstrcpy(strMCUserName, src.strMCUserName);
		lstrcpy(strMCUserPwd, src.strMCUserPwd);
		sMCPort = src.sMCPort;
		nIsLoal = src.nIsLoal;
	}
	IBFIS_ST_MCServer& operator= (const IBFIS_ST_MCServer& src)
	{
		lstrcpy(strBranchId, src.strBranchId);
		lstrcpy(strName, src.strName);
		lstrcpy(strMCIP, src.strMCIP);
		lstrcpy(strMCUserName, src.strMCUserName);
		lstrcpy(strMCUserPwd, src.strMCUserPwd);
		sMCPort = src.sMCPort;
		nIsLoal = src.nIsLoal;
		return *this;
	}
};
struct IBFIS_ST_BusinessDockMsgInfo
{
	IBFIS_CHAR strChannelCode[11];
	IBFIS_CHAR strServiceCode[9];
	IBFIS_CHAR strJDBRID[11];
	IBFIS_CHAR strOperatorId[21];
	IBFIS_CHAR strChannelSerialNum[25];      //���2�ں���ҵ��,�����ˮ��
	IBFIS_CHAR strKernelSerialNum[33];
	IBFIS_CHAR strDateTime[15];
	IBFIS_CHAR strChannelDate[9];
	IBFIS_CHAR strRepondCode[5];
	IBFIS_CHAR strChineseDescribeInfo[41];
	IBFIS_CHAR strBusinessCode[7];
	IBFIS_CHAR strBusinessName[65];
	IBFIS_CHAR strBusinessStatus[5];
	IBFIS_CHAR strProduceCode[33];
	IBFIS_CHAR strObjectProduceCode[33];
	IBFIS_CHAR strFundName[129];
	IBFIS_CHAR strProduceName[129];
	IBFIS_CHAR strIncomeType[2];
	IBFIS_CHAR strBusinessDate[9];
	IBFIS_CHAR strClientName[61];
	IBFIS_CHAR strCredenitialsType[2];
	IBFIS_CHAR strCredenitialNum[21];
	IBFIS_CHAR strMediumType[5];
	IBFIS_CHAR strMediumNum[33];
	IBFIS_CHAR strClientRiskLevel[3];
	IBFIS_CHAR strProduceRiskLevel[3];
	IBFIS_CHAR strFundType[4];
	IBFIS_CHAR strCancelBusinessType[2];
	IBFIS_CHAR strTerminalIP[21];           //�ն�ip
	IBFIS_CHAR strTradeSerialNum[25];       //������ˮ��
	IBFIS_CHAR strFinancSerialNum[25];      //�����ˮ��

	IBFIS_INT nSystemType;                  //1 �������ϵͳ  2 ���ݺ���ϵͳ  3 ��֦��ҵ��ϵͳ 4 �ϳ�ҵ��ϵͳ
	IBFIS_INT nBootFlag;                    //�Խ�ģʽ��־ 1 ����¼��  2 ���Խ���Ϣ  3 ����¼��

	IBFIS_CHAR strTermId[11];               //�ն˺ţ���ɽԤ����
	IBFIS_CHAR strTranTime[15];             //����ʱ�䣨��ɽԤ����
	IBFIS_CHAR strAcctNo[33];               //�ͻ��˺ţ���ɽԤ����

	IBFIS_CHAR strIBFISSerialNum[25];       //�ϳ�Խ� ���ϵͳ������ˮ��
	IBFIS_CHAR strVideoEndDate[15];         //�ϳ�Խ� ¼�񱣴�ʱ��
	IBFIS_CHAR strExtendedInfo[1024];       //Ԥ���ֶ�

	IBFIS_ST_BusinessDockMsgInfo()
	{
		nSystemType = 0;
		nBootFlag = 0;
		ZeroMemory(this,sizeof(IBFIS_ST_BusinessDockMsgInfo));
	}
};
struct IBFIS_ST_ScriptInfo
{
	IBFIS_CHAR	strScriptId[61];      //
	IBFIS_CHAR  strBusinessCode[7];
	IBFIS_CHAR	strBusinessType[61];  
	IBFIS_CHAR	strScriptContent[2001];
	IBFIS_INT	nExtendedInfo;
	IBFIS_CHAR	strExtendedInfo1[2001]; 
	IBFIS_CHAR	strExtendedInfo2[2001];       
	IBFIS_ST_ScriptInfo()
	{
		ZeroMemory(strScriptId, 61);
		ZeroMemory(strBusinessCode, 7);
		ZeroMemory(strBusinessType, 61);
		ZeroMemory(strScriptContent, 2001);
		ZeroMemory(strExtendedInfo1, 2001);
		ZeroMemory(strExtendedInfo2, 2001);
		nExtendedInfo = 0;
	}

	IBFIS_ST_ScriptInfo(const IBFIS_ST_ScriptInfo& src)
	{
		lstrcpy(strScriptId, src.strScriptId);
		lstrcpy(strBusinessCode, src.strBusinessCode);
		lstrcpy(strBusinessType, src.strBusinessType);
		lstrcpy(strScriptContent, src.strScriptContent);
		lstrcpy(strExtendedInfo1, src.strExtendedInfo1);
		lstrcpy(strExtendedInfo2, src.strExtendedInfo2);
		nExtendedInfo = src.nExtendedInfo;
	}
	IBFIS_ST_ScriptInfo& operator= (const IBFIS_ST_ScriptInfo& src)
	{
		lstrcpy(strScriptId, src.strScriptId);
		lstrcpy(strBusinessCode, src.strBusinessCode);
		lstrcpy(strBusinessType, src.strBusinessType);
		lstrcpy(strScriptContent, src.strScriptContent);
		lstrcpy(strExtendedInfo1, src.strExtendedInfo1);
		lstrcpy(strExtendedInfo2, src.strExtendedInfo2);
		nExtendedInfo = src.nExtendedInfo;
		return *this;
	}
};
struct IBFIS_ST_OperateLogInfo
{
	IBFIS_CHAR  strOperateLogId[61];
	IBFIS_CHAR	strModule[61];
	IBFIS_CHAR	strOperateEvent[61];
	IBFIS_CHAR	strIp[21];
	IBFIS_CHAR  strEmployeeId[61];
	IBFIS_CHAR	strBranchId[61];
	IBFIS_SYSTEMTIME stOperateTime;
	IBFIS_INT   nExtendedInfo;
	IBFIS_CHAR	strExtendedInfo1[2001];     
	IBFIS_ST_OperateLogInfo()
	{
		ZeroMemory(this,sizeof(IBFIS_ST_OperateLogInfo));
		nExtendedInfo = 0;
	}

	IBFIS_ST_OperateLogInfo(const IBFIS_ST_OperateLogInfo& src)
	{
		lstrcpy(strOperateLogId, src.strOperateLogId);
		lstrcpy(strModule, src.strModule);
		lstrcpy(strOperateEvent, src.strOperateEvent);
		lstrcpy(strIp, src.strIp);
		lstrcpy(strEmployeeId, src.strEmployeeId);
		lstrcpy(strBranchId, src.strBranchId);
		stOperateTime.wYear = src.stOperateTime.wYear;
		stOperateTime.wMonth = src.stOperateTime.wMonth;
		stOperateTime.wDay = src.stOperateTime.wDay;
		stOperateTime.wDayOfWeek = src.stOperateTime.wDayOfWeek;
		stOperateTime.wHour = src.stOperateTime.wHour;
		stOperateTime.wMinute = src.stOperateTime.wMinute;
		stOperateTime.wSecond = src.stOperateTime.wSecond;
		stOperateTime.wMilliseconds = src.stOperateTime.wMilliseconds;
		lstrcpy(strExtendedInfo1, src.strExtendedInfo1);
		nExtendedInfo = src.nExtendedInfo;
	}
	IBFIS_ST_OperateLogInfo& operator= (const IBFIS_ST_OperateLogInfo& src)
	{
		lstrcpy(strOperateLogId, src.strOperateLogId);
		lstrcpy(strModule, src.strModule);
		lstrcpy(strOperateEvent, src.strOperateEvent);
		lstrcpy(strIp, src.strIp);
		lstrcpy(strEmployeeId, src.strEmployeeId);
		lstrcpy(strBranchId, src.strBranchId);
		stOperateTime.wYear = src.stOperateTime.wYear;
		stOperateTime.wMonth = src.stOperateTime.wMonth;
		stOperateTime.wDay = src.stOperateTime.wDay;
		stOperateTime.wDayOfWeek = src.stOperateTime.wDayOfWeek;
		stOperateTime.wHour = src.stOperateTime.wHour;
		stOperateTime.wMinute = src.stOperateTime.wMinute;
		stOperateTime.wSecond = src.stOperateTime.wSecond;
		stOperateTime.wMilliseconds = src.stOperateTime.wMilliseconds;
		lstrcpy(strExtendedInfo1, src.strExtendedInfo1);
		nExtendedInfo = src.nExtendedInfo;
		return *this;
	}
};
struct IBFIS_ST_DiskAndConnectStatus
{
	char strBranchId[61];
	int nConnectStatus;  //����״̬,1 ������ 0 �Ͽ�
	int nDiskTatolSpace; //�����ܿռ䣬��λM
	int nDiskFreeSpace;  //����ʣ��ռ�
};
struct IBFIS_ST_DiskCodeAndCount
{
	char strDiskXML[1024];
};
#pragma pack(pop)
#endif