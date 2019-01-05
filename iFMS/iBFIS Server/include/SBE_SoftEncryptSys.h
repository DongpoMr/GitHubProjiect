 /*********************************************************
 * Filename: SBE_SoftEncryptSys.h
 * Contents: methods/function of the sobey software encryption system APIs 
 * Date: Nov., 7, 2003
 * Revised: Nov., 11, 2003  
 * Version 0.9.2.3, bulid 031111
 * All Rights Reserved
 * Sobey Inc, P.R.China
 **********************************************************
 * [Version history]
 * 
 * Version 0.8.2.5:  (1)finished primeval software encryption structure
 *                   (2)offering unified methods/functions for developers
 *                   (3)the first user is NLE
 * Version 0.9.2.2:  Based on V 0.8.x.x
 *                   (1) add debugU and releaseU mode 
 * Version 0.9.6.6  base on v 0.9.2.2
                     (1) add Macro Dog
 */
 
#ifndef  _SBE_SOFTWARE_ENCRYPT_SYSTEM_MPAG_
#define  _SBE_SOFTWARE_ENCRYPT_SYSTEM_MPAG_

/////////////////////////////// common include ////////////////////////////
#include "atlbase.h"

//////////////////////////////// lib related //////////////////////////////
#ifdef _DEBUG   
	#ifndef _UNICODE
		#pragma comment(lib, "sbesoftcryptd.lib") 
	#else
		#pragma comment(lib, "sbesoftcryptud.lib") 
	#endif
#else
	#ifndef _UNICODE
		#pragma comment(lib, "sbesoftcrypt.lib") 
	#else
		#pragma comment(lib, "sbesoftcryptu.lib") 
	#endif
#endif

/////////////////////////////// version defination ////////////////////////
#define SB_VERSION_ERR			0
#define SB_VERSION_RELEASE		1
#define SB_VERSION_DEMO			2

///////////////////////////// return value defination ////////////////////
#define SBE_FAILURE             0       //faliure
#define SBE_SUCCESS             1       //success
#define SBE_NO_RESTRICTION      2       //no restriction defined for this setting
     

///////////////////////////////  Dog check mode  /////////////////////////
#define SBE_DOGMODE_HWRBUSB     0x01    //Hardware dongle
#define SBE_DOGMODE_SOFT        0x02    //software dongle, binding with HW
#define SBE_DOGMODE_SOFT_NO_HW	0x04	//software dongle, fixed key, not binding with HW
#define SBE_DOGMODE_SONY        0x80    //sony dog 
#define SBE_DOGMODE_MACRO     0x08    //macro hardware dog


///////////////////////////// function declaration ///////////////////////

//input the product name, must call if you choose the SBE_DOGMODE_MACRO mode
//return: 1: success
//        0: failure
extern int SB_DogSetProductName(CComBSTR bsProductName);

//set dog mode for your prefered software encrypt system
//return: 1: success
//        0: failure
extern int SB_DogMode(DWORD dwMode);

//check to see if the dog and software encrypt system propertly exist or not
//return: 1: success
//        0: failure
extern int SB_DogCheck();



//get the version of the software, which defined in the DOG
//return "nVersion":  0: SB_VERSION_ERR, 
//                    1: SB_VERSION_RELEASE 
//                    2: SB_VERSION_DEMO
//return "bstrModuleDescript": the description of the software EXE (e.g. "CY21", or "TopBox", or any string you defined)
//return "llModuleInfo" : the module controlling information of the target software
//function return:    1: success
//                    0: failure
extern int SB_DogVersion(int &nVersion, CComBSTR &bstrExeDescript, LONGLONG &llModuleInfo);



//get the lefted times count in trial version mode
//return "nCountLeft":  the lefted times, only valid in trial(demo) mode
//                      if nCountLeft <=0, the times count expired 
//function return:    1: success and a valid nCountLeft returned
//                    0: faliure
//                    2: no times count restriction (e.g. in release mode, always return 2)
extern int SB_DogCountLeft(int &nCountLeft, BOOL bDecreaseCount = FALSE);



//get the left days in trial version mode
//return "nDaysLeft":   the lefted days, only valid in trial(demo) mode
//                      if nDaysLeft <=0, the days count expired 
//function return:    1: success and a valid nDaysLeft returned
//                    0: faliure
//                    2: no days count restriction (e.g. in release mode, always return 2)
extern int SB_DogDaysLeft(int &nDaysLeft);



//get information of the software modules
//return "llModuleInfo" : the module controlling information of the target software
//function return:    1: success
//                    0: failure
extern int SB_DogInfo(LONGLONG &llModuleInfo);



/////////////////////////////////////////////////////
//save soft license key 
//valid for DogCheckMode = SBE_DOGMODE_SOFT
//          DogCheckMode = SBE_DOGMODE_SOFT_NO_HW
//function return:    1: success
//                    0: failure
extern int SB_SoftDogRegister(CComBSTR strSerial);
//////////////////////////////////////////////////////////////////////////
#endif