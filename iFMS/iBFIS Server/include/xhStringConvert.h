/***
Author: ATHER Shu 2009.3.20
* StringUtil类:用于ANSI、UTF-16、UTF-8之间的字串转换* 
功能：
* 1.UTF-16转ANSI ws2s
* 2.ANSI转UTF-16 s2ws
* 3.UTF-16转UTF-8 ws2utf8
* 4.UTF-8转UTF-16 utf82ws
* http://www.asarea.me* ATHER Shu(AS)
*/
#include <string>
#include <Windows.h>
using namespace std;
class StringUtil
{
public:    
	static string ws2s(const wstring& ws)    
	{        
		const wchar_t* _Source = ws.c_str();
		size_t _Dsize = WideCharToMultiByte(CP_ACP, 0, _Source, -1, NULL, 0, NULL, NULL); 
		char *_Dest = new char[_Dsize];   
		WideCharToMultiByte(CP_ACP, 0, _Source, -1, _Dest, _Dsize, NULL, NULL);    
		string result = _Dest;     
		delete []_Dest;      
		return result;   
	}    
	
	static wstring s2ws(const string& s)   
	{       
		const char* _Source = s.c_str();   
		size_t _Dsize = MultiByteToWideChar(CP_ACP, 0, _Source, -1, NULL, 0);      
		wchar_t *_Dest = new wchar_t[_Dsize];    
		MultiByteToWideChar(CP_ACP, 0, _Source, -1, _Dest, _Dsize);  
		wstring result = _Dest;       
		delete []_Dest;        
		return result;    
	}   
	
	static string ws2utf8(const wstring& ws)  
	{     
		const wchar_t* _Source = ws.c_str();
		size_t _Dsize = WideCharToMultiByte(CP_UTF8, 0, _Source, -1, NULL, 0, NULL, NULL);  
		char *_Dest = new char[_Dsize];   
		WideCharToMultiByte(CP_UTF8, 0, _Source, -1, _Dest, _Dsize, NULL, NULL);     
		string result = _Dest;      
		delete []_Dest;     
		return result;  
	}    
	
	static wstring utf82ws(const string& s)   
	{        
		const char* _Source = s.c_str(); 
		size_t _Dsize = MultiByteToWideChar(CP_UTF8, 0, _Source, -1, NULL, 0); 
		wchar_t *_Dest = new wchar_t[_Dsize];       
		MultiByteToWideChar(CP_UTF8, 0, _Source, -1, _Dest, _Dsize);   
		wstring result = _Dest;     
		delete []_Dest;        
		return result;  
	}
};