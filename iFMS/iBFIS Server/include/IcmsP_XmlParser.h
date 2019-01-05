/******************************************************************************
Copyright(C) Sobey .All Right Reserved
�� �� ����IcmsP_XmlParser.h XML�������ӿ��ļ�
1.ʵ�ֶ�XML�ļ��Ľ��������������������湦��
2.ʵ�ֶ�XML���ݽ����޸ĵĹ���
3.

�汾��Ϣ��1.0
�� д �ߣ�����ǿ
ʱ��ص㣺2008-11-05
���ñ�����

������ʷ��
1.0	 2008-11-06 ����ǿ	���ӻ�ø����������͵�ϵ��Get����

															iMonitor��Ŀ��
******************************************************************************/
#ifndef ICMSP_XMLPARSER_H_
#define ICMSP_XMLPARSER_H_

#ifdef _iCMSP_XML_PARSER_SDK
#define iCMS_XML_PARSER_CLASS_MODE __declspec(dllexport)
#else
#define iCMS_XML_PARSER_CLASS_MODE __declspec(dllimport)
#endif

#ifndef _iCMSP_XML_PARSER_SDK
#ifdef _DEBUG
#ifdef _UNICODE
#pragma comment(lib,"IcmsPXmlParserud.lib")
#else
#pragma comment(lib,"IcmsPXmlParserd.lib")
#endif
#else
#ifdef _UNICODE
#pragma comment(lib,"IcmsPXmlParseru.lib")
#else
#pragma comment(lib,"IcmsPXmlParser.lib")
#endif
#endif
#endif

class XhXmlParser;

class iCMS_XML_PARSER_CLASS_MODE iCMSP_XmlParser  
{
public:

	iCMSP_XmlParser() ;
	iCMSP_XmlParser( LPCTSTR szDoc ) ;
	iCMSP_XmlParser( int nFlags ) ;
	
	iCMSP_XmlParser( const iCMSP_XmlParser& xmlparser ) ;
	
	~iCMSP_XmlParser() ;

	// Navigate
	bool Load( LPCTSTR szFileName );
	//bool SetDoc( LPCTSTR pDoc ) const;          //ʹ�ô˺���ʱ,�뱣֤������ַ���������0����
	bool SetDoc( LPCTSTR pDoc , UINT nLength) ;    
	bool IsWellFormed();
	bool FindElem( LPCTSTR szName=NULL );
	bool FindChildElem( LPCTSTR szName=NULL );
	bool IntoElem();
	bool OutOfElem();
	void ResetChildPos() ;
	void ResetMainPos() ;
	void ResetPos() ;
	CString GetTagName() const;
	CString GetChildTagName() const ;
	CString GetData() const ;
	CString GetChildData() const ;
	CString GetElemContent() const ;
	CString GetAttrib( LPCTSTR szAttrib ) const ;
	CString GetChildAttrib( LPCTSTR szAttrib ) const ;
	CString GetAttribName( int n ) const;
	int FindNode( int nType=0 );
	int GetNodeType() ;
	bool SavePos( LPCTSTR szPosName=_T("") );
	bool RestorePos( LPCTSTR szPosName=_T("") );
	const CString& GetError() const ;
	int GetDocFlags() const ;
	void SetDocFlags( int nFlags );


	// Create
	bool Save( LPCTSTR szFileName );
	const CString& GetDoc() const ;
	bool AddElem( LPCTSTR szName, LPCTSTR szData=NULL, int nFlags=0 ) ;
	bool InsertElem( LPCTSTR szName, LPCTSTR szData=NULL, int nFlags=0 ) ;
	bool AddChildElem( LPCTSTR szName, LPCTSTR szData=NULL, int nFlags=0 ) ;
	bool InsertChildElem( LPCTSTR szName, LPCTSTR szData=NULL, int nFlags=0 ) ;
	bool AddElem( LPCTSTR szName, int nValue, int nFlags=0 ) ;
	bool InsertElem( LPCTSTR szName, int nValue, int nFlags=0 ) ;
	bool AddChildElem( LPCTSTR szName, int nValue, int nFlags=0 ) ;
	bool InsertChildElem( LPCTSTR szName, int nValue, int nFlags=0 ) ;
	bool AddAttrib( LPCTSTR szAttrib, LPCTSTR szValue ) ;
	bool AddChildAttrib( LPCTSTR szAttrib, LPCTSTR szValue ) ;
	bool AddAttrib( LPCTSTR szAttrib, int nValue ) ;
	bool AddChildAttrib( LPCTSTR szAttrib, int nValue ) ;
	bool AddSubDoc( LPCTSTR szSubDoc ) ;
	bool InsertSubDoc( LPCTSTR szSubDoc ) ;
	CString GetSubDoc() const ;
	bool AddChildSubDoc( LPCTSTR szSubDoc ) ;
	bool InsertChildSubDoc( LPCTSTR szSubDoc ) ;
	CString GetChildSubDoc() const ;
	bool AddNode( int nType, LPCTSTR szText ) ;
	bool InsertNode( int nType, LPCTSTR szText ) ;

	// Modify
	bool RemoveElem();
	bool RemoveChildElem();
	bool RemoveNode();
	bool SetAttrib( LPCTSTR szAttrib, LPCTSTR szValue ) ;
	bool SetChildAttrib( LPCTSTR szAttrib, LPCTSTR szValue ) ;
	bool SetAttrib( LPCTSTR szAttrib, int nValue ) ;
	bool SetChildAttrib( LPCTSTR szAttrib, int nValue ) ;
	bool SetData( LPCTSTR szData, int nFlags=0 ) ;
	bool SetChildData( LPCTSTR szData, int nFlags=0 ) ;
	bool SetData( int nValue );
	bool SetChildData( int nValue ) ;
	bool SetElemContent( LPCTSTR szContent ) ;

	// Utility
	static bool ReadTextFile( LPCTSTR szFileName, CString& strDoc, CString* pstrError=NULL, int* pnDocFlags=NULL );
	static bool WriteTextFile( LPCTSTR szFileName, CString& strDoc, CString* pstrError=NULL, int* pnDocFlags=NULL );
	static CString EscapeText( LPCTSTR szText, int nFlags = 0 );
	static CString UnescapeText( LPCTSTR szText, int nTextLength = -1 );
	
	//Help
	//���º��������ṩ��������ת������
	
	//ȡ�õ�ǰ��ǩ��Ӧ�������͵�ֵ
	bool GetDataBool() const;
	int GetDataInt() const;
	DWORD GetDataDWORD() const;
	float GetDataFloat() const;
	double GetDataDouble() const;
	COleDateTime GetDataDateTime() const;

	//ȡ�õ�ǰ�ӱ�ǩ��Ӧ�������͵�ֵ
	bool GetChildDataBool() const;
	int GetChildDataInt() const	;
	long GetChildDataLong() const;
	UINT GetChildDataUINT() const;
	DWORD GetChildDataDWORD() const;
	float GetChildDataFloat() const	;
	double GetChildDataDouble() const	;
	COleDateTime GetChildDataDateTime() const;


	//ȡ�õ�ǰ��ǩĳ������Ӧ�������͵�ֵ
	bool GetAttribBool(LPCTSTR szAttrib ) const	;
	int GetAttribInt(LPCTSTR szAttrib ) const;
	UINT GetAttribUINT(LPCTSTR szAttrib ) const	;
	DWORD GetAttribDWORD(LPCTSTR szAttrib ) const;
	float GetAttribFloat(LPCTSTR szAttrib ) const;
	double GetAttribDouble(LPCTSTR szAttrib ) const;
	COleDateTime GetAttribDateTime(LPCTSTR szAttrib ) const;


	//ȡ�õ�ǰ�ӱ�ǩĳ������Ӧ�������͵�ֵ
	bool GetChildAttribBool(LPCTSTR szAttrib ) const;
	int GetChildAttribInt(LPCTSTR szAttrib ) const;
	UINT GetChildAttribUINT(LPCTSTR szAttrib ) const;
	DWORD GetChildAttribDWORD(LPCTSTR szAttrib ) const;
	float GetChildAttribFloat(LPCTSTR szAttrib ) const	;
	double GetChildAttribDouble(LPCTSTR szAttrib ) const;
	COleDateTime GetChildAttribDateTime(LPCTSTR szAttrib ) const;


private:
	XhXmlParser *m_pXmlImplement;
};

#endif 
