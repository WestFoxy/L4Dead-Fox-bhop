#include "TrFoxHooker.h"
#include <Windows.h>

bool TrFoxHooker::Detour32(char* src, char* dst, const intptr_t len)
{
	if (len < 5) return false;

	DWORD  curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

	intptr_t  relativeAddress = (intptr_t)(dst - (intptr_t)src) - 5;

	*src = (char)'\xE9';
	*(intptr_t*)((intptr_t)src + 1) = relativeAddress;

	VirtualProtect(src, len, curProtection, &curProtection);
	return true;
}

char* TrFoxHooker::TrampHook32(char* src, char* dst, const intptr_t len)
{
	if (len < 5) return 0;
	void* gateway = VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(gateway, src, len);
	intptr_t  gatewayRelativeAddr = ((intptr_t)src - (intptr_t)gateway) - 5;
	*(char*)((intptr_t)gateway + len) = 0xE9;
	*(intptr_t*)((intptr_t)gateway + len + 1) = gatewayRelativeAddr;

	Detour32(src, dst, len);

	return (char*)gateway;
}
