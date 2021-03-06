// App.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <dllA.h>
#include <dllB.h>


typedef std::string(WINAPI *funcGetTextFromDll)(void);

funcGetTextFromDll GetFunctionFromDll(LPCTSTR dllName, LPCSTR funcName, DWORD dwFlags)
{
	HMODULE hMod = LoadLibraryEx(dllName, NULL, dwFlags);
	if (hMod == NULL)
	{
		return nullptr;
	}

	FARPROC f = GetProcAddress(hMod, funcName);
	if (f == NULL)
	{
		return nullptr;
	}

	return (funcGetTextFromDll)f;

}

void Test1()
{
	// this will (usually) print 
	// 
	//	Text from DLL A: couldn't load DllA
	//	Text from DLL B : couldn't load DllB
	// 
	// simply because the dllCommon.dll cannot be resolved

	funcGetTextFromDll getFromA = GetFunctionFromDll(_T("dllA"), "?GetTextA@@YG?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
	funcGetTextFromDll getFromB = GetFunctionFromDll(_T("dllB"), "?GetTextB@@YG?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);

	auto strFromA = (getFromA != nullptr) ? (getFromA()) : std::string("couldn't load DllA");
	auto strFromB = (getFromB != nullptr) ? (getFromB()) : std::string("couldn't load DllB");

	std::cout << "Text from DLL A: " << strFromA << std::endl;

	std::cout << "Text from DLL B: " << strFromB << std::endl;
}

void Test2()
{
	TCHAR szCurrentExecutableName[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL), szCurrentExecutableName, (sizeof(szCurrentExecutableName) / sizeof(szCurrentExecutableName[0])));
	for (size_t i = _tcslen(szCurrentExecutableName) - 1; i >= 0;--i)
	{
		if (szCurrentExecutableName[i]==_T('\\'))
		{
			szCurrentExecutableName[i] = _T('\0');
			break;
		}
	}

	std::basic_string<TCHAR> absFilename1(szCurrentExecutableName);
	absFilename1 += _T("\\dllA.dll");

	std::basic_string<TCHAR> absFilename2(szCurrentExecutableName);
	absFilename2 += _T("\\dllB.dll");

	std::basic_string<TCHAR> dllPath1(szCurrentExecutableName);
	dllPath1 += _T("\\v1\\");
	std::basic_string<TCHAR> dllPath2(szCurrentExecutableName);
	dllPath2 += _T("\\v2\\");

	DLL_DIRECTORY_COOKIE ckie1 = AddDllDirectory(dllPath1.c_str());
	funcGetTextFromDll getFromA = GetFunctionFromDll(absFilename1.c_str(), "?GetTextA@@YG?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", LOAD_LIBRARY_SEARCH_USER_DIRS);
	RemoveDllDirectory(ckie1);

	DLL_DIRECTORY_COOKIE ckie2 = AddDllDirectory(dllPath2.c_str());
	funcGetTextFromDll getFromB = GetFunctionFromDll(absFilename2.c_str(), "?GetTextB@@YG?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", LOAD_LIBRARY_SEARCH_USER_DIRS);
	RemoveDllDirectory(ckie2); 

	auto strFromA = (getFromA != nullptr) ? (getFromA()) : std::string("couldn't load DllA");
	auto strFromB = (getFromB != nullptr) ? (getFromB()) : std::string("couldn't load DllB");

	std::cout << "Text from DLL A: " << strFromA << std::endl;

	std::cout << "Text from DLL B: " << strFromB << std::endl;
}

void Test3()
{
	TCHAR szCurrentExecutableName[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL), szCurrentExecutableName, (sizeof(szCurrentExecutableName) / sizeof(szCurrentExecutableName[0])));
	for (size_t i = _tcslen(szCurrentExecutableName) - 1; i >= 0; --i)
	{
		if (szCurrentExecutableName[i] == _T('\\'))
		{
			szCurrentExecutableName[i] = _T('\0');
			break;
		}
	}

	std::basic_string<TCHAR> absFilename1(szCurrentExecutableName);
	absFilename1 += _T("\\dllA.dll");

	std::basic_string<TCHAR> absFilename2(szCurrentExecutableName);
	absFilename2 += _T("\\dllB.dll");

	std::basic_string<TCHAR> dllPath1(szCurrentExecutableName);
	dllPath1 += _T("\\v1\\");
	std::basic_string<TCHAR> dllPath2(szCurrentExecutableName);
	dllPath2 += _T("\\v2\\");


	DLL_DIRECTORY_COOKIE ckie1 = AddDllDirectory(dllPath1.c_str());

	ACTCTX ctx1;
	ctx1.cbSize = sizeof(ctx1);
	ctx1.dwFlags = ACTCTX_FLAG_RESOURCE_NAME_VALID;
	ctx1.lpSource = absFilename1.c_str();
	ctx1.lpResourceName = MAKEINTRESOURCE(2);

	HANDLE  h1 = CreateActCtx(&ctx1);
	DWORD ckieActCtx1;
	BOOL B = ActivateActCtx(h1, &ckieActCtx1);

	funcGetTextFromDll getFromA = GetFunctionFromDll(absFilename1.c_str(), "?GetTextA@@YG?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", LOAD_WITH_ALTERED_SEARCH_PATH/*LOAD_LIBRARY_SEARCH_USER_DIRS*/);
	RemoveDllDirectory(ckie1);
	DeactivateActCtx(0, ckieActCtx1);

	ACTCTX ctx2;
	ctx2.cbSize = sizeof(ctx2);
	ctx2.dwFlags = ACTCTX_FLAG_RESOURCE_NAME_VALID;
	ctx2.lpSource = absFilename2.c_str();
	ctx2.lpResourceName = MAKEINTRESOURCE(2);

	DLL_DIRECTORY_COOKIE ckie2 = AddDllDirectory(dllPath2.c_str());
	HANDLE  h2 = CreateActCtx(&ctx2);
	DWORD ckieActCtx2;
	ActivateActCtx(h2, &ckieActCtx2);


	funcGetTextFromDll getFromB = GetFunctionFromDll(absFilename2.c_str(), "?GetTextB@@YG?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", LOAD_LIBRARY_SEARCH_USER_DIRS);
	RemoveDllDirectory(ckie2);
	DeactivateActCtx(0, ckieActCtx2);

	auto strFromA = (getFromA != nullptr) ? (getFromA()) : std::string("couldn't load DllA");
	auto strFromB = (getFromB != nullptr) ? (getFromB()) : std::string("couldn't load DllB");

	std::cout << "Text from DLL A: " << strFromA << std::endl;

	std::cout << "Text from DLL B: " << strFromB << std::endl;
}

int main()
{
	//Test1();
	//Test2();
	Test3();
	return 0;
}



