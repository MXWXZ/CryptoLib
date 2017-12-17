/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/16
 *
 * @Description:
 */
/************************************************************************
WARNING:You MUST pre allocate the memory for any string buffer! All of the
function will NOT check the space or other things.
You can use
GetA2WLength,GetW2ALength,GetG2ULength,GetU2GLength,GetADataLength or 
GetWDataLength to get the length.

Default encoding is GBK，if you want to use UTF-8，please call SetEncodeUTF8
************************************************************************/
#pragma once

#include <string>
#include <assert.h>
#include <algorithm>
#include "windows.h"
#include <sstream>

namespace CryptoLib {
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
    stringx() {}
    explicit stringx(SXCWCH ch, const UINT rep = 1);
    stringx(LPCSTR src, bool isutf8 = false);
    stringx(LPCWSTR src, bool isutf8 = false);
    stringx(const string& src, bool isutf8 = false);
    stringx(const wstring& src, bool isutf8 = false);
    ~stringx() {}

    void SetEncodeUTF8() { isutf8_ = true; }
    void SetEncodeGBK() { isutf8_ = false; }
    stringx& SetString(SXCWCH ch, const UINT rep = 1);
    stringx& SetString(SXCSTR src);
    stringx& SetString(SXCWSTR src);
    stringx& SetString(const string& src);
    stringx& SetString(const wstring& src);
    stringx& SetString(const stringx& src);
    /**
     * digit to string
     * @param    SXCULL digit:no more than 18446744073709551615
     */
    stringx& SetDigit(SXCULL digit);

    string GetString() const;
    wstring GetWString() const;
    tstring GetTString() const;
    SXCWSTR GetData() const;
    SXSTR GetData(SXSTR out) const;
    SXWSTR GetData(SXWSTR out) const;
    stringx GetGBKStr() const;
    stringx GetUTF8Str() const;
    /**
    * string to digit
    * @return    SXULL digit,no more than 18446744073709551615
    */
    SXULL GetDigit() const;
    wstring& GetBuffer();
    int GetADataLength() const;
    int GetWDataLength() const;

    bool IsEncodeUTF8() const { return isutf8_; }
    bool IsDigit() const;

    void Empty();
    bool IsEmpty() const;
    UINT GetLength() const;     // chinese character will be count 1
    SXWCH GetAt(const UINT index) const;
    void SetAt(const UINT index, SXCWCH ch);
    stringx& Append(const stringx& src);
    stringx& Append(SXCWCH ch, const UINT rep = 1);

    SXWCH operator[] (const UINT index) const;
    stringx& operator=(const stringx& src);
    stringx operator+(const stringx& src) const;
    const stringx& operator+=(const stringx& src);
    const stringx& operator+=(const SXCWCH src);

    int Compare(const stringx& src) const;
    int CompareNoCase(const stringx& src) const;
    bool operator == (const stringx& src) const;
    bool operator != (const stringx& src) const;
    bool operator <= (const stringx& src) const;
    bool operator <  (const stringx& src) const;
    bool operator >= (const stringx& src) const;
    bool operator >  (const stringx& src) const;

    stringx& MakeUpper();
    stringx& MakeLower();

    stringx SubStr(UINT from, UINT to) const;
    stringx Left(UINT length) const;
    stringx Mid(UINT pos, int length) const;
    stringx Right(UINT length) const;

    int Find(const stringx& src, const UINT pos = 0) const;
    int Replace(const stringx& src, const stringx& dest);
    stringx& TrimRight();
    stringx& TrimLeft();
    int DeleteChar(SXWCH ch);

    stringx& __cdecl Format(SXCWSTR str, ...);

    stringx& Encode2GBK();
    stringx& Encode2UTF8();

    /**
     * MultiByte and WideChar convert length
     * @return   safe length
     * TIP:param SXCSTR will get its SXCWSTR convert result length
     *     param SXCWSTR will get its SXCSTR convert result length
     */
    static int GetA2WLength(SXCSTR str, bool isutf8 = false);
    static int GetW2ALength(SXCWSTR str, bool isutf8 = false);

    static int GetG2ULength(SXCWSTR str);
    static int GetU2GLength(SXCWSTR str);

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

    static SXWSTR Str2WStr(SXCSTR str, SXWSTR out, bool isutf8 = false);
    static SXSTR WStr2Str(SXCWSTR str, SXSTR out, bool isutf8 = false);
};

typedef stringx STRX;
typedef const stringx CSTRX;
}    // namespace CryptoLib
