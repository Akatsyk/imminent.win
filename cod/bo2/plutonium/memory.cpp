#include "framework.h"

MODULEINFO GetModuleInfo(LPCSTR szModule) {
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandleA(szModule);
	if (hModule == 0) return modinfo;
	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

BOOL Memory::MatchPattern(const BYTE* pData, const BYTE* bMask, const char* szMask) {
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}

DWORD Memory::Scan(char* szSig, char* szMask) {
	DWORD dwAddress = (DWORD)GetModuleHandleA(NULL);
	DWORD dwLen = GetModuleInfo(NULL).SizeOfImage;

	for (DWORD i = 0; i < dwLen; i++)
		if (MatchPattern((BYTE*)(dwAddress + i), (BYTE*)szSig, szMask))
			return (DWORD)(dwAddress + i);

	return 0;
}

DWORD Memory::ScanPattern(DWORD dwAddress, DWORD dwLen, char* bMask, char* szMask) {
	for (DWORD i = 0; i < dwLen; i++)
		if (MatchPattern((BYTE*)(dwAddress + i), (BYTE*)bMask, szMask))
			return (DWORD)(dwAddress + i);

	return 0;
}