// iFVR_ServerMonitoring.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include<stdio.h>
//#include<string.h>
#include<stdlib.h>
#include "XhServerMonitoring.h"

int main()
{
	XhServerMonitoring sm;
	sm.StartMonitoring();
	system("pause");
    return 0;
}

