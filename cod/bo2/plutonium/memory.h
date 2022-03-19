#pragma once

namespace Memory {
	BOOL MatchPattern(const BYTE* pData, const BYTE* bMask, const char* szMask);
	DWORD Scan(char* szSig, char* szMask);
	DWORD ScanPattern(DWORD dwAddress, DWORD dwLen, char* bMask, char* szMask);
};