#include "stdafx.h"
#include "convert.h"

namespace CryptoLib {
wchar_t* Convert::Str2WStr(const char * cStr) {
	const DWORD cCh = MultiByteToWideChar(CP_ACP, 0, cStr, -1, NULL, 0);
	wchar_t* wStr = new wchar_t[cCh];
	ZeroMemory(wStr, cCh * sizeof(wStr[0]));
	MultiByteToWideChar(CP_ACP, 0, cStr, -1, wStr, cCh);
	return wStr;
}

char* Convert::WStr2Str(const wchar_t * wStr) {
	const DWORD cCh = WideCharToMultiByte(CP_ACP, 0, wStr, -1, NULL, 0, NULL, NULL);									
	char* cStr = new char[cCh];
	ZeroMemory(cStr, cCh * sizeof(cStr[0]));
	WideCharToMultiByte(CP_ACP, 0, wStr, -1, cStr, cCh, NULL, NULL);
	return cStr;
}

TCHAR* Convert::CWStr2TStr(const char * cStr) {
#ifdef UNICODE
	return Str2WStr(cStr);
#else
	return const_cast<char*>(cStr);
#endif
}

TCHAR* Convert::CWStr2TStr(const wchar_t* wStr) {
#ifdef UNICODE
	return const_cast<wchar_t*>(wStr);
#else
	return WStr2Str(wStr);
#endif
}
}