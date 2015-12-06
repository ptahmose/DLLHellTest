// dllA.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dllA.h"
#include <dllCommon_v1.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='dllCommon' version='1.0.0.0' processorArchitecture='*' \"")


DLLA_API std::string WINAPI GetTextA(void)
{
	return std::string("Hello from DllA using ") + getCommonDllText();
}