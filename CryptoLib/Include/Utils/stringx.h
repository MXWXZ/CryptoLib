/************************************************************************
本类为保证DLL安全，所有传入字符串（char*或wchar_t*）均需要初始化分配空间
（new或数组）后再传入，所有函数均不检查长度是否足够，可以使用
stringx::GetAWConvertLength或stringx::GetGUConvertLength等取得字符串转换
所需长度，或使用足够大的空间。
比如：
wchar_t* wstr = new wchar[GetAWConvertLength(str)]; 

本类默认为GBK编码，如果传入的字符串是UTF-8编码，请调用SetEncodeUTF8，以
保证得到想要的结果
************************************************************************/
#pragma once

#include <string>
#include <assert.h>
#include <algorithm>
#include "windows.h"
#include <sstream>

typedef char SXCH;
typedef const char SXCCH;
typedef wchar_t SXWCH;
typedef const wchar_t SXCWCH;
typedef char* SXSTR;
typedef const char* SXCSTR;
typedef wchar_t* SXWSTR;
typedef const wchar_t* SXCWSTR;
typedef unsigned long long SXULL;
typedef const unsigned long long SXCULL;
using std::wstring;
using std::string;
#ifdef _UNICODE
typedef wstring tstring;
typedef SXWCH SXTCH;
typedef SXCWCH SXCTCH;
typedef SXWSTR SXTSTR;
typedef SXCWSTR SXCTSTR;
#else
typedef string tstring;
typedef SXCH SXTCH;
typedef SXCCH SXCTCH;
typedef SXSTR SXTSTR;
typedef SXCSTR SXCTSTR;
#endif

class stringx {
public:
	stringx() {};
	stringx(SXCWCH ch, const UINT rep = 1);
	stringx(SXCSTR src);
	stringx(SXCWSTR src);
	stringx(const string& src);
	stringx(const wstring& src);
	stringx(const stringx& src);
	~stringx() {};

	void SetEncodeUTF8() { isutf8_ = true; }
	void SetEncodeGBK()  { isutf8_ = false; }
	bool IsEncodeUTF8() const { return isutf8_; }
	stringx& SetString(SXCWCH ch, const UINT rep = 1);
	stringx& SetString(SXCSTR src);
	stringx& SetString(SXCWSTR src);
	stringx& SetString(const string& src);
	stringx& SetString(const wstring& src);
	stringx& SetString(const stringx& src);
	stringx& SetDigit(SXCULL digit);
	string GetString() const;
	wstring GetWString() const;
	tstring GetTString() const;
	SXCWSTR GetData() const;
	SXULL GetDigit() const;
	wstring& GetBuffer();

	void Empty();
	bool IsEmpty() const;
	SXULL GetLength() const;
	SXWCH GetAt(const int index) const;
	void SetAt(const int index, SXCWCH ch);
	stringx& Append(SXCSTR src);
	stringx& Append(SXCWSTR src);
	stringx& Append(const string& src);
	stringx& Append(const wstring& src);
	stringx& Append(const stringx& src);
	stringx& Append(SXCWCH ch, const UINT rep = 1);

	SXWCH operator[] (const UINT index) const;
	stringx& operator=(const stringx& src);
	stringx& operator=(SXCWCH ch);
	stringx& operator=(SXCSTR src);
	stringx& operator=(SXCWSTR src);
	stringx& operator=(const string& src);
	stringx& operator=(const wstring& src);
	stringx operator+(const stringx& src) const;
	stringx operator+(SXCWCH ch) const;
	stringx operator+(SXCSTR src) const;
	stringx operator+(SXCWSTR src) const;
	stringx operator+(const string& src) const;
	stringx operator+(const wstring& src) const;
	const stringx& operator+=(const stringx& src);
	const stringx& operator+=(SXCWCH ch);
	const stringx& operator+=(SXCSTR src);
	const stringx& operator+=(SXCWSTR src);
	const stringx& operator+=(const string& src);
	const stringx& operator+=(const wstring& src);

	int Compare(SXCSTR src) const;
	int Compare(SXCWSTR src) const;
	int Compare(const string& src) const;
	int Compare(const wstring& src) const;
	int Compare(const stringx& src) const;
	int CompareNoCase(SXCSTR src) const;
	int CompareNoCase(SXCWSTR src) const;
	int CompareNoCase(const string& src) const;
	int CompareNoCase(const wstring& src) const;
	int CompareNoCase(const stringx& src) const;
	bool operator == (SXCSTR src) const;
	bool operator == (SXCWSTR src) const;
	bool operator == (const string& src) const;
	bool operator == (const wstring& src) const;
	bool operator == (const stringx& src) const;
	bool operator != (SXCSTR src) const;
	bool operator != (SXCWSTR src) const;
	bool operator != (const string& src) const;
	bool operator != (const wstring& src) const;
	bool operator != (const stringx& src) const;
	bool operator <= (SXCSTR src) const;
	bool operator <= (SXCWSTR src) const;
	bool operator <= (const string& src) const;
	bool operator <= (const wstring& src) const;
	bool operator <= (const stringx& src) const;
	bool operator <  (SXCSTR src) const;
	bool operator <  (SXCWSTR src) const;
	bool operator <  (const string& src) const;
	bool operator <  (const wstring& src) const;
	bool operator <  (const stringx& src) const;
	bool operator >= (SXCSTR src) const;
	bool operator >= (SXCWSTR src) const;
	bool operator >= (const string& src) const;
	bool operator >= (const wstring& src) const;
	bool operator >= (const stringx& src) const;
	bool operator >  (SXCSTR src) const;
	bool operator >  (SXCWSTR src) const;
	bool operator >  (const string& src) const;
	bool operator >  (const wstring& src) const;
	bool operator >  (const stringx& src) const;

	stringx& MakeUpper();
	stringx& MakeLower();

	stringx SubStr(UINT from, UINT to) const;
	stringx Left(UINT length) const;
	stringx Mid(UINT pos, int length) const;
	stringx Right(UINT length) const;

	int Find(SXWCH ch, const UINT pos = 0) const;
	int Find(SXCSTR src, const UINT pos = 0) const;
	int Find(SXCWSTR src, const UINT pos = 0) const;
	int Find(const string& src, const UINT pos = 0) const;
	int Find(const wstring& src, const UINT pos = 0) const;
	int Find(const stringx& src, const UINT pos = 0) const;
	int Replace(SXCSTR src, SXCSTR dest);
	int Replace(SXCSTR src, SXCWSTR dest);
	int Replace(SXCWSTR src, SXCWSTR dest);
	int Replace(SXCWSTR src, SXCSTR dest);
	stringx& TrimRight();
	stringx& TrimLeft();
	int DeleteChar(SXWCH ch);

	stringx& __cdecl Format(SXCWSTR str, ...);

	stringx& Encode2GBK();
	stringx& Encode2UTF8();

	static int GetAWConvertLength(SXCSTR str);
	static int GetAWConvertLength(SXCWSTR str);
	static int GetGUConvertLength(SXCSTR str);
	static int GetGUConvertLength(SXCWSTR str);

protected:
	wstring str_;
	bool isutf8_ = false;

	static int ToUpper(int c);
	static int ToLower(int c);

	static SXSTR GBK2UTF8(SXCSTR str, SXSTR out);
	static SXWSTR GBK2UTF8(SXCSTR str, SXWSTR out);
	static SXSTR GBK2UTF8(SXCWSTR str, SXSTR out);
	static SXWSTR GBK2UTF8(SXCWSTR str, SXWSTR out);
	static SXSTR UTF82GBK(SXCSTR str, SXSTR out);
	static SXWSTR UTF82GBK(SXCSTR str, SXWSTR out);
	static SXSTR UTF82GBK(SXCWSTR str, SXSTR out);
	static SXWSTR UTF82GBK(SXCWSTR str, SXWSTR out);
	static SXWSTR Str2WStr(SXCSTR str, SXWSTR out);
	static SXSTR WStr2Str(SXCWSTR str, SXSTR out);
};

typedef stringx STRX;
typedef const stringx CSTRX;