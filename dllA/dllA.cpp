// dllA.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dllA.h"
#include <dllCommon_v1.h>

DLLA_API std::string GetTextA(void)
{
	return std::string("Hello from DllA using ") + getCommonDllText();
}