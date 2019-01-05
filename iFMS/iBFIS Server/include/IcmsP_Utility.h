#pragma once
//!!!REMBER MUST SET PROJECT SETTING (enbale c++ execptions)TO "Yes With SEH Exceptions (/EHa)"!!!
//made in sobey.com by terry.wang at 2008-10-03

#ifdef _iCMSP_UTILITY_SDK
	#define iCMS_UTILITY_CLASS_MODE __declspec(dllexport)
#else
	#define iCMS_UTILITY_CLASS_MODE __declspec(dllimport)
#endif

#ifndef _iCMSP_UTILITY_SDK
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"IcmsPUtilityud.lib")
		#else
			#pragma comment(lib,"IcmsPUtilityd.lib")
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"IcmsPUtilityu.lib")
		#else
			#pragma comment(lib,"IcmsPUtility.lib")
		#endif			
	#endif
#endif

class iCMS_UTILITY_CLASS_MODE iCMSP_Utility
{
public:
	//write a fromated string to log file,like the sprintf,heihei
	static int Static_WriteLogWithStamp(const char* format,...);

	//write a fromated string to log file,like the sprintf,haha
	static int Static_WriteLogWithStampAndFlush(const char* format,...);

	static int Static_WriteLogWithFileName(const char *pFileName,const char *format,...);
	
	static int Static_OutputDebufString(const char* format,...);

	static void Static_SetLogNeedWriteFile(BOOL bIsWrite = FALSE);

	//dump the current thread's call stack
	static int Static_ShowCallstack();

	static const TCHAR* Static_GetWorkingDir();

	static int CtrlDump(BOOL bDumpCallStack,BOOL bDumpFile);

	static int CtrlInstallHook(BOOL bInstall);

	static int GetNowMemUseage(DWORD* pMemKB,DWORD* pVMemKb);

    static int Static_PackFile(LPCTSTR lpszSourceFile, LPCTSTR lpszDestFile, BOOL bIsAppend = 1);

    static int Static_PackFileByTime(LPCTSTR lpszSourceFolder, LPCTSTR lpszDestFile, LPCTSTR lpszBeginTime, LPCTSTR lpszEndTime,LPCTSTR lpszFileFormat = NULL, BOOL bIsAppend = 1);
private:
	//no need to explicit to create the instance of the class,so set the constrction to private
	iCMSP_Utility();
	~iCMSP_Utility();
};

//adjust the hwnd 's dc,release it,set dc to null
#define SAFE_RELEASE_DC(hwnd,hdc) {if (hdc) ::ReleaseDC(hwnd,hdc);hdc = NULL;}

//adjust the gdi object,if so,delete it ,and set the object to null
#define SAFE_DELETE_GDI(gdiObject) {if (gdiObject) DeleteObject(gdiObject);gdiObject = NULL;}

//adjust the ptr will be valid,if so,release it,and set the ptr to null 
#define SAFE_RELEASE(ptr) {STRY;if (ptr) ptr->Release();ptr = NULL;SCATCH;}

//adjust the ptr will be valid,if so,delete it,and set the ptr to null
#define SAFE_DELETE(ptr) {STRY;if (ptr) delete ptr;ptr = NULL;SCATCH;}
#define SAFE_DELETE_ARRAY(ptr) {STRY;if (ptr) delete[] ptr;ptr = NULL;SCATCH;}

//adjust the ptr will be valid,if so,global free it,and set the ptr to null
#define SAFE_FREE_GLOBAL(ptr) {if (ptr) ::GlobalFree (ptr);ptr = NULL;}

//adjust the hwnd will be is windows,if so destroy the window,set the hwnd to null
#define SAFE_DESTORYWND(hwnd) {if (hwnd && ::IsWindow (hwnd)) ::DestroyWindow (hwnd);hwnd = NULL;}

#ifdef _AFXDLL
	//adjust the pWnd will be valid,if so first destroy it,then delete it,set the pwnd to null
	#define SAFE_DESTROY_CWND(pWnd) {if (pWnd ) {pWnd->DestroyWindow();delete pWnd;pWnd = NULL;};}
#endif

//adjust the handle will be valid,if so close the handle,set the handle to null
#define SAFE_CLOSE_HANDLE(handle) {if (handle) CloseHandle(handle);handle = NULL;};

//if in vc6,the macro __FUNCTION__ is not defined,so define it to __FILE__
#ifndef __FUNCTION__
#define __FUNCTION__ __FILE__
#endif

//some very terrible warning when get to vs2005,vs2008,forgive me to disable it
#pragma warning(disable : 4996)

	//write a fromated string message to the log file,with auto created time stamp before the format string
	#define TTRACE	iCMSP_Utility::Static_WriteLogWithStamp 

	//write a fromated string message to the log file,with auto created time stamp before the format string
	//AND FLUSH THE FILE,REMMBER THAT USED AS LESS AS POSSIBLE.
	#define FTRACE	iCMSP_Utility::Static_WriteLogWithStampAndFlush 

	#define FOUTPUTDBGSTRING iCMSP_Utility::Static_OutputDebufString

	#define	SFTRACE iCMSP_Utility::Static_WriteLogWithFileName

	//just print the file's function,line to the logfile
	#define LOGLINE TTRACE("thread[%d] RUN TO %s %d\r\n",GetCurrentThreadId(), __FUNCTION__,__LINE__)

//define the USE_STACK_WALKER macro to enable the stackwalker,try,catch function
//if u not need the stack walker function,please notes the following define word,default to need
#define USE_STACK_WALKER

//show the thread 's call stack
#define DumpCallStack() iCMSP_Utility::Static_ShowCallstack() 

//in debug ,i need the crash,so comment the macro
#ifndef _DEBUG
	//define STRY to wrapper the try
	#define STRY	try{

	//define SCATCH to wrapper the exception function
	#define SCATCH		}\
					catch(...)\
						{\
							TTRACE("[thread:%u]at file[%s],function[%s].Line:[%d]\r\n", \
							GetCurrentThreadId(),__FILE__, __FUNCTION__,__LINE__);\
						};						
	//becase on xp or later platform,i install the vector exeception handle
	//which can catch all error,all !!!.so no need use the DumpCallStack()\,comment it
	//the problem is vector write a dump,and DumpCallStack write a dump again,so so so 
	//terrywang edit at 2009-11-4

#else
//if not defined the USE_STACK_WALKER,all macro got the foo
	#define STRY {
	#define SCATCH }
	#define STRACE 
#endif

#define GetWorkingDirectory() iCMSP_Utility::Static_GetWorkingDir()
#define EnableDumpCallstack() iCMSP_Utility::CtrlDump(TRUE,TRUE)
#define DisableDumpCallstack() iCMSP_Utility::CtrlDump(FALSE,FALSE)
#define InstallVectorHook() iCMSP_Utility::CtrlInstallHook(TRUE)
#define UnstallVectorHook() iCMSP_Utility::CtrlInstallHook(FALSE)

#define GetCurMemUseage iCMSP_Utility::GetNowMemUseage

#define SetLogNeedWriteFile(X) iCMSP_Utility::Static_SetLogNeedWriteFile(X)

#ifdef __cplusplus
extern "C"
{
#endif

iCMS_UTILITY_CLASS_MODE int PackFile(LPCTSTR lpszSourceFile, LPCTSTR lpszDestFile, BOOL bIsAppend = 1);

iCMS_UTILITY_CLASS_MODE int PackFilesByTime(LPCTSTR lpszSourceFolder, LPCTSTR lpszDestFile, LPCTSTR lpszBeginTime, LPCTSTR lpszEndTime,LPCTSTR lpszFileFormat = NULL, BOOL bIsAppend = 1);

iCMS_UTILITY_CLASS_MODE int CleanUpLog(LPCTSTR lpszSourceFolder, LPCTSTR lpszBeginTime, LPCTSTR lpszEndTime, LPCTSTR lpszFileFormat = NULL);

#ifdef __cplusplus
}
#endif

