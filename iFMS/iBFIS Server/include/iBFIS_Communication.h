#pragma once

#include <vector>
#include <string>
#pragma region ErrDefine
#define iSOCMatError_Ok                           0
#define iSOCMatError_Unspecified                  -1
#define iSOCMatError_ServerMessageLength          -2
#define iSOCMatError_ClientMessageLength          -3
#define iSOCMatError_Serialization                -4
#define iSOCMatError_Deserialization              -5
#define iSOCMatError_AppException                 -6
#define iSOCMatError_UnknownEndpoint              -8
#define iSOCMatError_EndpointPassword             -9
#define iSOCMatError_EndpointDown                -10
#define iSOCMatError_EndpointRetry               -11
#define iSOCMatError_ClientConnectTimeout        -16
#define iSOCMatError_PeerDisconnect              -17
#define iSOCMatError_ClientCancel                -18
#define iSOCMatError_PayloadFilterMismatch       -20
#define iSOCMatError_OpenSslFilterInit           -21
#define iSOCMatError_OpenSslLoadCert             -22
#define iSOCMatError_UnknownPublisher            -23
#define iSOCMatError_UnknownFilter               -24
#define iSOCMatError_NoServerStub                -25
#define iSOCMatError_Sspi                        -26
#define iSOCMatError_SspiInit                    -28
#define iSOCMatError_ClientReadTimeout           -30
#define iSOCMatError_ClientReadFail              -31
#define iSOCMatError_ClientWriteTimeout          -32
#define iSOCMatError_ClientWriteFail             -33
#define iSOCMatError_ClientConnectFail           -34
#define iSOCMatError_Socket                      -36
#define iSOCMatError_FnId                        -37
#define iSOCMatError_UnknownInterface            -38
#define iSOCMatError_NoEndpoint                  -39
#define iSOCMatError_TransportCreation           -40
#define iSOCMatError_FilterCount                 -41
#define iSOCMatError_FilterMessage               -42
#define iSOCMatError_UnfilterMessage             -43
#define iSOCMatError_SspiCredentials             -44
#define iSOCMatError_SspiEncrypt                 -45
#define iSOCMatError_SspiDecrypt                 -46
#define iSOCMatError_SspiImpersonation           -47
#define iSOCMatError_SocketClose                 -49
#define iSOCMatError_ZlibDeflate                 -50
#define iSOCMatError_ZlibInflate                 -51
#define iSOCMatError_Zlib                        -52
#define iSOCMatError_UnknownSerializationProtocol     -53
#define SfError_NoCtor                       -55
#define SfError_RefMismatch                  -56
#define SfError_DataFormat                   -57
#define SfError_ReadFailure                  -58
#define SfError_WriteFailure                 -59
#define SfError_BaseDerivedRegistration      -60
#define SfError_TypeRegistration             -61
#define iSOCMatError_NonStdException             -62
#define iSOCMatError_SocketBind                  -63
#define iSOCMatError_Decoding                    -64
#define iSOCMatError_Encoding                    -65
#define iSOCMatError_TokenRequestFailed          -66
#define iSOCMatError_ObjectFactoryNotFound       -67
#define iSOCMatError_PortInUse                   -68
#define iSOCMatError_DynamicObjectNotFound       -69
#define iSOCMatError_VersionMismatch             -70
#define iSOCMatError_SslCertVerification         -72
#define iSOCMatError_FiltersLocked               -74
#define iSOCMatError_Pipe                        -75
#define iSOCMatError_AnySerializerNotFound       -76
#define iSOCMatError_ConnectionLimitExceeded     -77
#define iSOCMatError_DeserializationNullPointer  -78
#define iSOCMatError_PipeNameTooLong             -79
#define iSOCMatError_PingBack                    -80
#define iSOCMatError_NoPingBackService           -81
#define iSOCMatError_NoDownload                  -82
#define iSOCMatError_FileOffset                  -83
#define iSOCMatError_NoUpload                    -84
#define iSOCMatError_FileOpen                    -85
#define iSOCMatError_FileRead                    -86
#define iSOCMatError_FileWrite                   -87
#define iSOCMatError_UploadFailed                -88
#define iSOCMatError_UploadInProgress            -89
#define iSOCMatError_ConcurrentUpload            -90
#define iSOCMatError_UploadFileSize              -91
#define iSOCMatError_AccessDenied                -92
#define iSOCMatError_PingBackTimeout             -93
#define iSOCMatError_AllThreadsBusy              -94
#define iSOCMatError_UnsupportedRuntimeVersion   -95
#define iSOCMatError_FdSetSize                   -97
#define iSOCMatError_DnsLookup                   -98
#define iSOCMatError_SspiHandshakeExtraData      -99
#define iSOCMatError_ProtobufWrite               -101
#define iSOCMatError_ProtobufRead                -102
#define iSOCMatError_ExtractSlice                -103
#define iSOCMatError_ServerStubExpired           -104
#define iSOCMatError_VariantDeserialization      -105
#define iSOCMatError_SspiAuthFailServer          -106
#define iSOCMatError_SspiAuthFailClient          -107
#define iSOCMatError_Win32ApiError               -108
#define iSOCMatError_SspiLengthField             -109
#define iSOCMatError_DownloadFailed              -110
#define iSOCMatError_FileSeek                    -111
#define iSOCMatError_DownloadCancelled           -112
#define iSOCMatError_ParseSockAddr               -113
#define iSOCMatError_GetSockName                 -114
#define iSOCMatError_ProtobufWriteSize           -115
#define iSOCMatError_ProtobufWriteInit           -116
#define iSOCMatError_ArraySizeMismatch           -117
#define iSOCMatError_WcharSizeMismatch           -118
#define iSOCMatError_AnyTypeNotRegistered        -119
#define iSOCMatError_CryptoApiError              -120
#define iSOCMatError_ServerStubAccessDenied      -121
#define iSOCMatError_ApiError                    -122
#define iSOCMatError_HttpProxyPort               -123
#define iSOCMatError_OpenSslError                -124
#define iSOCMatError_ProtocolNotSupported        -125
#define iSOCMatError_ClearCommunicationNotAllowed     -126
#define iSOCMatError_ThreadingError              -127
#define iSOCMatError_RcfNotInitialized           -128
#define iSOCMatError_InvalidHttpMessage          -129
#define iSOCMatError_HttpRequestContentLength    -130
#define iSOCMatError_HttpResponseContentLength   -131
#define iSOCMatError_InvalidOpenSslCertificate   -132
#define iSOCMatError_InvalidSchannelCertificate  -133
#define iSOCMatError_HttpConnectFailed           -134
#define iSOCMatError_SspiImpersonateNoSspi       -135
#define iSOCMatError_TransportProtocolNotSupported   -136
#define iSOCMatError_SslNotSupported             -137
#define iSOCMatError_SessionObjectDoesNotExist   -138
#define iSOCMatError_UploadAlreadyCompleted      -139
#define iSOCMatError_FileIndex                   -140
#define iSOCMatError_ConcurrentCalls             -141

#define iSOCMatError_User                        -1001

#define iSOCMatError_StubAssignment              -19
#define iSOCMatError_SspiAuthFail                -27
#define iSOCMatError_UnknownSubscriber           -29
#define iSOCMatError_Filter                      -35
#define iSOCMatError_NotConnected                -48
#define iSOCMatError_InvalidErrorMessage         -54

#pragma endregion ErrDefine


#ifdef _iBFS_COMMUNICATION_SDK_
#define iBFS_COMUUNICATION_MODULE __declspec(dllexport)
#else
#define iBFS_COMUUNICATION_MODULE __declspec(dllimport)
#endif
class IRMICallbackSkin
{
public:
	IRMICallbackSkin(){};
	virtual ~IRMICallbackSkin(){};
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d){return -1;};
	virtual int OnInvoke(HANDLE hContext,std::string& s){return -1;};
	virtual int OnInvoke(HANDLE hContext,std::vector<DWORD_PTR>& v,DWORD_PTR& d1 , DWORD_PTR& d2 ){return -1;};
	virtual int OnInvoke(HANDLE hContext,std::vector<std::string>& v){return -1;};
	virtual int OnInvoke(HANDLE hContext,BYTE* data,int nDataLen){return -1;};
	virtual int OnInvoke(HANDLE hContext,std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2){return -1;};
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,DWORD_PTR& d2){return -1;};
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d,std::string& s){return -1;};
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d,BYTE* pData,int nDataLen){return -1;};
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,DWORD_PTR& d2,DWORD_PTR& d3){return -1;};
	virtual int OnInvoke(HANDLE hContext,std::string& s1,std::string& s2,std::string& s3){return -1;};
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,DWORD_PTR& d2,std::string& s){return -1;};
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d,std::string& s1,std::string& s2){return -1;};
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,DWORD_PTR& d2,DWORD_PTR& d3,DWORD_PTR& d4){return -1;};
	virtual int OnInvoke(HANDLE hContext,std::string& s1,std::string& s2,std::string& s3,std::string& s4){return -1;};
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,std::vector<std::string>& v1){return -1;};
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,std::string& s1,std::vector<std::string>& v1, std::vector<std::string>& v2){return -1;};
	virtual int OnInvoke(HANDLE hContext,DWORD_PTR& d1,std::vector<std::string>& v1,std::vector<std::string>& v2,std::vector<std::string>& v3){return -1;};

	virtual int OnConnected(HANDLE hContext) = 0;
	virtual int OnDisConnected(HANDLE hContext) = 0;
	virtual int OnGotError(HANDLE hContext,int nErrorCode,std::string strErrorDes) = 0;
};

class iBFS_COMUUNICATION_MODULE iBFIS_CommunicationInvoker
{
public:
	iBFIS_CommunicationInvoker(HANDLE hContext);
	~iBFIS_CommunicationInvoker();

	int Invoke(DWORD_PTR& d) const;
	int Invoke(std::string& s) const;
	int Invoke(std::vector<DWORD_PTR>& v,DWORD_PTR& d1,DWORD_PTR& d2 ) const;
	int Invoke(std::vector<std::string>& v) const;
	int Invoke(BYTE* data,int nDataLen) const;
	int Invoke(std::vector<DWORD_PTR>& v1,std::vector<std::string>& v2) const;
	int Invoke(DWORD_PTR& d1,DWORD_PTR& d2) const;
	int Invoke(DWORD_PTR& d,std::string& s) const;
	int Invoke(DWORD_PTR& d,BYTE* pData,int nDataLen) const;
	int Invoke(DWORD_PTR& d1,DWORD_PTR& d2,DWORD_PTR& d3) const;
	int Invoke(std::string& s1,std::string& s2,std::string& s3) const;
	int Invoke(DWORD_PTR& d1,DWORD_PTR& d2,std::string& s) const;
	int Invoke(DWORD_PTR& d,std::string& s1,std::string& s2) const;
	int Invoke(DWORD_PTR& d1,DWORD_PTR& d2,DWORD_PTR& d3,DWORD_PTR& d4) const;
	int Invoke(std::string& s1,std::string& s2,std::string& s3,std::string& s4) const;
	int Invoke(DWORD_PTR& d1,std::vector<std::string>& v1) const;
	int Invoke(DWORD_PTR& d1,std::string& s1,std::vector<std::string>& v1, std::vector<std::string>& v2) const;
	int Invoke(DWORD_PTR& d1,std::vector<std::string>& v1,std::vector<std::string>& v2,std::vector<std::string>& v3) const;
private:
	void DisConnect() const;
	HANDLE m_hContext;
};

class iBFS_COMUUNICATION_MODULE iBFIS_CommunicationServer
{
public:
	iBFIS_CommunicationServer();
	~iBFIS_CommunicationServer();

	int Start(const TCHAR* strIP="0.0.0.0",int nPort=50000) const;
	int Stop() const;
	void SetRMICallbackSkin(IRMICallbackSkin* pSkin) const;
	static void GetClientAddr(HANDLE hContext, TCHAR chIP[30]);
private:
	HANDLE m_hServer;
};

class iBFS_COMUUNICATION_MODULE iBFIS_CommunicationClient
{
public:
	iBFIS_CommunicationClient();
	~iBFIS_CommunicationClient();

	int Connect(const TCHAR* strIP = "127.0.0.1",int nPort = 50000) const;
	int DisConnect() const;
	void SetRMICallbackSkin(IRMICallbackSkin* pSkin) const;

private:
	HANDLE m_hClient;
};