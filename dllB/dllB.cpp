// dllB.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dllB.h"

DLLB_API std::string GetTextB(void)
{
	return std::string("Hello from DllB");
}