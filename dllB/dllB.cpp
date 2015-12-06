// dllB.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dllB.h"
#include <dllCommon_v2.h>

DLLB_API std::string WINAPI GetTextB(void)
{
	return std::string("Hello from DllB using ") + getCommonDllText();
}
