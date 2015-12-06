// dllCommon_v1.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dllCommon_v1.h"


// This is an example of an exported function.
DLLCOMMON_V1_API std::string getCommonDllText()
{
    return std::string("dllCommon_v1");
}
