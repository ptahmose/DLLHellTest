// dllCommon_v2.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dllCommon_v2.h"


DLLCOMMON_V2_API std::string WINAPI getCommonDllText()
{
	return std::string("dllCommon_v2");
}