#include "Utils.h"
#include <Psapi.h>

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

void FoxUtils::AttachDebugFoxConsole()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	auto _out = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleMode(_out,
		ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);

	freopen("CON", "w", stdout);
}

void FoxUtils::DetachDebugFoxConsole()
{
	fclose(stdout);
	FreeConsole();
}

DWORD FoxUtils::FindPattern(std::string moduleName, std::string Mask)
{
	const char* pat = Mask.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
		{
			return firstMatch;
		}
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
			{
				firstMatch = pCur;
			}

			if (!pat[2])
			{
				return firstMatch;
			}


			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
			{
				pat += 3;
			}
			else
			{
				pat += 2; //one ?
			}

		}
		else
		{
			pat = Mask.c_str();
			firstMatch = 0;
		}
	}
	return NULL;
}
