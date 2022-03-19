// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"

extern "C" {
	_declspec(dllexport) const char* __cdecl DiscordCreate(int a1, int a2, int a3);
}

const char* DiscordCreate(int a1, int a2, int a3)
{
	return "Discord Create Spoofed.";
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		std::cout << "DLL Successfully Injected." << std::endl;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}