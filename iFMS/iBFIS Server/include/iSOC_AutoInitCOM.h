#pragma once

class iSOC_AutoInitCOM
{
public:
	iSOC_AutoInitCOM(void):bIsNeedUninitialize(true)
	{
		HRESULT hRes = ::CoInitializeEx(NULL,COINIT_MULTITHREADED);
		if(hRes == S_FALSE || hRes == RPC_E_CHANGED_MODE)
		{
			CString strMsg = "S_FALSE";
			if(hRes == RPC_E_CHANGED_MODE)
			{
				strMsg = "RPC_E_CHANGED_MODE";
			}
			//TTRACE("%s:调用CoInitializeEx函数返回%s,因此将不会调用CoUninitialize进行反初始化\r\n",__FUNCTION__,(LPCTSTR)strMsg);
			bIsNeedUninitialize = false;
		}
	}
	~iSOC_AutoInitCOM(void)
	{
		if(bIsNeedUninitialize == true)
			::CoUninitialize();
	}
private:
	bool bIsNeedUninitialize;
};
