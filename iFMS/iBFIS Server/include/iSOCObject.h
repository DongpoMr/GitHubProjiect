#pragma once

#ifdef _iSOC_AUTO_GC_OBJECT_SDK
#define iSOC_AUTO_GC_CLASS_MODE __declspec(dllexport)
#else
#define iSOC_AUTO_GC_CLASS_MODE __declspec(dllimport)
#endif


#ifndef _iSOC_AUTO_GC_OBJECT_SDK
    #ifdef _DEBUG
        #ifdef _UNICODE
#pragma comment(lib,"isoc.sdk.gcobjectud.lib")
        #else
#pragma comment(lib,"isoc.sdk.gcobjectd.lib")
        #endif
    #else
        #ifdef _UNICODE
#pragma comment(lib,"isoc.sdk.gcobjectu.lib")
        #else
#pragma comment(lib,"isoc.sdk.gcobject.lib")
        #endif			
    #endif
#endif

#if 0
static bool g_bIsInit = false;
iSOC_AUTO_GC_CLASS_MODE void iSOC_AddAddr(void* pAddr,int nSize,BOOL bIsObject = TRUE);
iSOC_AUTO_GC_CLASS_MODE int iSOC_DelAddr(void* pAddr,BOOL bIsObject = TRUE);

inline void* operator new(size_t size)
{
	void* pAddr = malloc(size);
	if(pAddr)
	{
		iSOC_AddAddr(pAddr,size,FALSE);
	}
	return pAddr;
}

inline void* operator new[](size_t size)
{
	void* pAddr = malloc(size);
	if(pAddr)
	{
		iSOC_AddAddr(pAddr,size,FALSE);
	}
	return pAddr;
}

inline void* operator new(size_t size,const char* file,int line)
{
	void* pAddr = malloc(size);
	if(pAddr)
	{
		iSOC_AddAddr(pAddr,size,FALSE);
	}
	return pAddr;
}

inline void* operator new[](size_t size,const char* file,int line)
{
	void* pAddr = malloc(size);
	if(pAddr)
	{
		iSOC_AddAddr(pAddr,size,FALSE);
	}
	return pAddr;
}

inline void operator delete(void* obj)
{
	if(obj)
	{
		iSOC_DelAddr(obj,FALSE);
		free(obj);
	}
}

inline void operator delete[](void* obj)
{
	if(obj)
	{
		iSOC_DelAddr(obj,FALSE);
		free(obj);
	}
}
#endif

class iSOC_AUTO_GC_CLASS_MODE  CISocObject
{
public:
	CISocObject(void);
	virtual ~CISocObject(void);

	void* operator new(size_t size,const char* file,int line);
	void* operator new( size_t size );
	void* operator new( size_t size, void *p );
	/* Must be redefined here, since the other overloadings	*/
	/* hide the global definition.				*/
	void operator delete( void* obj );
	void operator delete( void*, void* );

	void* operator new[]( size_t size );
	void* operator new[]( size_t size, void *p );
	void* operator new[](size_t size,const char* file,int line);
	void operator delete[]( void* obj );
	void operator delete[]( void*, void* );

	unsigned int GetObjectType();
	virtual void Release();
	virtual CISocObject* GetObjectRef();
	int GetObjectRefCount();
	const TCHAR* GetLastErrorMessage();
	void SetLastErrorMessage(const TCHAR* strDes);
	//virtual int GetLastErr() = 0;
	bool m_bIsSingleMod; //标识是否是单太对像，如果是必须在创建其对象的地方将些值设置为true
protected:
	void SetObjectType(unsigned int nObjType);
	unsigned int m_nObjectType;
	int m_nObjectRefCount;
private:
	void*	m_pErrorDes;
};
