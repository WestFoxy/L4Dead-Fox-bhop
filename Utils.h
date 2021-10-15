#pragma once
#include <Windows.h>
#include <string>

#define foxassert(x) if(!(x)){MessageBoxA(0,#x " failed with null", "Fox", MB_OK | MB_ICONERROR); exit(0);}

#ifdef FOXDEBUG
#define PRINTFOXPTR(x) (printf("[FOXDEBUG] " #x " = 0x%p\n", x))
#define PRINTFOX(x) (printf("[FOXDEBUG] " x))
#else
#define PRINTFOXPTR(x)
#define PRINTFOX(x)
#endif

namespace FoxUtils
{
	template <typename T>
	T* ValveGetInterface(const char* sz_module, const char* sz_interface)
	{
		typedef void* (*o_interface_t)(const char*, int);
		auto hhandle = GetModuleHandleA(sz_module);
		o_interface_t original = (o_interface_t)GetProcAddress(hhandle, "CreateInterface");
		return (T*)original(sz_interface, 0);
	}

	template <typename FoxFunc>
	FoxFunc __forceinline getFoxVMTFunc(void* FoxPtr, int num)
	{
		return (*reinterpret_cast<FoxFunc**>(FoxPtr))[num];
	}

	void AttachDebugFoxConsole();
	void DetachDebugFoxConsole();
	DWORD FindPattern(std::string moduleName, std::string Mask);

}