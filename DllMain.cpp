#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <string>

#include "FoxApi.h"
#include "Utils.h"
#include "FunctionsHooks.h"

HINSTANCE thisLibrary = nullptr;

void SetupFox()
{
#ifdef FOXDEBUG
	FoxUtils::AttachDebugFoxConsole();
#endif

	FoxApi::initApi();
	FoxHooks::installHooks();

	Beep(1000, 100);

	//TODO: normal destruct and unhooks
	while (true)
	{
		Sleep(30000);
	}

#ifdef FOXDEBUG
	FoxUtils::DetachDebugFoxConsole();
#endif

	FreeLibraryAndExitThread(thisLibrary, 0);
}


BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDll);
		thisLibrary = hinstDll;

		CreateThread((LPSECURITY_ATTRIBUTES)0, (SIZE_T)0, (LPTHREAD_START_ROUTINE)SetupFox, (LPVOID)0, (DWORD)0, (LPDWORD)0);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{

		if (lpvReserved == nullptr)
		{
			FreeLibraryAndExitThread(hinstDll, 1);
		}
	}
	return TRUE;
}