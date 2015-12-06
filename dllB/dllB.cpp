// dllB.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dllB.h"
#include <dllCommon_v2.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='dllCommon' version='2.0.0.0' processorArchitecture='*' \"")

DLLB_API std::string WINAPI GetTextB(void)
{
	return std::string("Hello from DllB using ") + getCommonDllText();
}
