#pragma once

namespace CryptoLib {
class Convert {
public:
	static wchar_t* Str2WStr(const char* cStr);
	static wchar_t* Str2WStr(const wchar_t* wStr) { return const_cast<wchar_t*>(wStr); }
	static char* WStr2Str(const wchar_t* wStr);
	static char* WStr2Str(const char* cStr) { const_cast<char*>(cStr); }
	static TCHAR* CWStr2TStr(const char* cStr);
	static TCHAR* CWStr2TStr(const wchar_t* wStr);


};
}