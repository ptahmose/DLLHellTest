// App.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <dllA.h>
#include <dllB.h>

int main()
{
	auto strFromA = GetTextA();
	auto strFromB = GetTextB();

	std::cout << "Text from DLL A: " << strFromA << std::endl;

	std::cout << "Text from DLL B: " << strFromB << std::endl;
    return 0;
}

