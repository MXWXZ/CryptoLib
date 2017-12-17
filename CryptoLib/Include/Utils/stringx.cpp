/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/16
 *
 * @Description:
 */
#include "stdafx.h"
#include "stringx.h"

namespace CryptoLib {
stringx::stringx(SXCWCH ch, const UINT rep /*= 1*/) { SetString(ch, rep); }
stringx::stringx(LPCSTR src, bool isutf8/* = false*/) { isutf8_ = isutf8; SetString(src); }
stringx::stringx(LPCWSTR src, bool isutf8/* = false*/) { isutf8_ = isutf8; SetString(src); }
stringx::stringx(const string& src, bool isutf8/* = false*/) { isutf8_ = isutf8; SetString(src); }
stringx::stringx(const wstring& src, bool isutf8/* = false*/) { isutf8_ = isutf8; SetString(src); }

stringx& stringx::SetString(SXCWCH ch, const UINT rep /*= 1*/) {
    str_.assign(rep, ch);
    return *this;
}

stringx& stringx::SetString(SXCSTR src) {
    SXWSTR wstr = new SXWCH[GetA2WLength(src, isutf8_)];
    str_ = Str2WStr(src, wstr, isutf8_);
    delete[] wstr;
    wstr = NULL;
    return *this;
}

stringx& stringx::SetString(SXCWSTR src) {
    str_ = src;
    return *this;
}

stringx& stringx::SetString(const string& src) {
    SetString(src.c_str());
    return *this;
}

stringx& stringx::SetString(const wstring& src) {
    SetString(src.c_str());
    return *this;
}

stringx& stringx::SetString(const stringx& src) {
    str_ = src.str_;
    isutf8_ = src.isutf8_;
    return *this;
}

stringx& stringx::SetDigit(SXCULL digit) {
    SXWSTR str = new SXWCH[128];
    _ui64tow(digit, str, 10);
    str_ = str;
    delete[] str;
    str = NULL;
    return *this;
}

string stringx::GetString() const {
    SXSTR str = new SXCH[GetW2ALength(str_.c_str(), isutf8_)];
    string ret = WStr2Str(str_.c_str(), str, isutf8_);
    delete[] str;
    str = NULL;
    return ret;
}

wstring stringx::GetWString() const {
    return str_;
}

tstring stringx::GetTString() const {
#ifdef _UNICODE
    return GetWString();
#else
    return GetString();
#endif
}

SXSTR stringx::GetData(SXSTR out) const {
    WStr2Str(str_.c_str(), out);
    return out;
}

SXWSTR stringx::GetData(SXWSTR out) const {
    wcscpy(out, str_.c_str());
    return out;
}

SXCWSTR stringx::GetData() const {
    return str_.c_str();
}

stringx stringx::GetGBKStr() const {
    if (isutf8_) {
        SXSTR tmp = new SXCH[GetU2GLength(str_.c_str())];
        UTF82GBK(str_.c_str(), tmp);
        SXWSTR tmp2 = new SXWCH[GetA2WLength(tmp)];
        STRX ret = Str2WStr(tmp, tmp2);
        ret.SetEncodeGBK();
        delete[] tmp;
        delete[] tmp2;
        tmp = NULL;
        tmp2 = NULL;
        return ret;
    } else {
        return *this;
    }
}

stringx stringx::GetUTF8Str() const {
    if (!isutf8_) {
        SXSTR tmp = new SXCH[GetG2ULength(str_.c_str())];
        GBK2UTF8(str_.c_str(), tmp);
        SXWSTR tmp2 = new SXWCH[GetA2WLength(tmp, true)];
        STRX ret = Str2WStr(tmp, tmp2, true);
        ret.SetEncodeUTF8();
        delete[] tmp;
        delete[] tmp2;
        tmp = NULL;
        tmp2 = NULL;
        return ret;
    } else {
        return *this;
    }
}

SXULL stringx::GetDigit() const {
    return wcstoull(str_.c_str(), NULL, 10);
}

wstring& stringx::GetBuffer() {
    return str_;
}

int stringx::GetADataLength() const {
    return GetW2ALength(str_.c_str(), isutf8_) - 1;
}

int stringx::GetWDataLength() const {
    return GetLength();
}

bool stringx::IsDigit() const {
    for (UINT i = 0; i < GetLength(); ++i) {
        if (i == 0 && str_[i] == L'-')
            continue;
        if (str_[i] < L'0' || str_[i] > L'9')
            return false;
    }
    return true;
}

void stringx::Empty() {
    str_.clear();
}

bool stringx::IsEmpty() const {
    return str_.empty();
}

UINT stringx::GetLength() const {
    return str_.length();
}

SXWCH stringx::GetAt(const UINT index) const {
    return str_[index];
}

void stringx::SetAt(const UINT index, SXCWCH ch) {
    str_[index] = ch;
}

stringx& stringx::Append(const stringx& src) { str_.append(src.GetWString()); return *this; }
stringx& stringx::Append(SXCWCH ch, const UINT rep /*= 1*/) { str_.append(rep, ch); return *this; }

SXWCH stringx::operator[] (const UINT index) const {
    return str_[index];
}

stringx& stringx::operator=(const stringx&  src) { SetString(src); return *this; }
stringx stringx::operator+(const stringx&  src) const { stringx temp = *this; temp.Append(src); return temp; }
const stringx& stringx::operator+=(const stringx&  src) { Append(src); return *this; }

const stringx& stringx::operator+=(const SXCWCH src) { Append(src); return *this; }

int stringx::Compare(const stringx& src) const { return str_.compare(src.GetWString()); }
int stringx::CompareNoCase(const stringx& src) const { return _wcsicmp(str_.c_str(), src.GetWString().c_str()); }

bool stringx::operator == (const stringx& src) const { return (Compare(src) == 0); }
bool stringx::operator != (const stringx& src) const { return (Compare(src) != 0); }
bool stringx::operator <= (const stringx& src) const { return (Compare(src) <= 0); }
bool stringx::operator < (const stringx& src)  const { return (Compare(src) < 0); }
bool stringx::operator >= (const stringx& src) const { return (Compare(src) >= 0); }
bool stringx::operator > (const stringx& src)  const { return (Compare(src) > 0); }

int stringx::ToUpper(int c) {
    if (isalpha(c))
        return toupper(c);
    else
        return c;
}

int stringx::ToLower(int c) {
    if (isalpha(c))
        return tolower(c);
    else
        return c;
}

stringx& stringx::MakeUpper() {
    transform(str_.begin(), str_.end(), str_.begin(), ToUpper);
    return *this;
}

stringx& stringx::MakeLower() {
    transform(str_.begin(), str_.end(), str_.begin(), ToLower);
    return *this;
}

stringx stringx::SubStr(UINT from, UINT to) const {
    SXULL len = GetLength();
    if (from >= len)
        return stringx();
    if (to >= len)
        to = (UINT)len - 1;
    return stringx(str_.substr(from, to - from + 1));
}

stringx stringx::Left(UINT length) const {
    if (length == 0)
        return stringx();
    SXULL len = GetLength();
    if (length > len)
        length = (UINT)len;
    return stringx(str_.substr(0, length));
}

stringx stringx::Mid(UINT pos, int length) const {
    SXULL len = GetLength();
    int start, end;
    if (pos >= len)
        return stringx();
    if (length < 0) {
        start = pos - length + 1;
        if (start < 0)
            start = 0;
        end = pos;
    } else {
        start = pos;
        end = pos + length - 1;
        if (end >= len)
            end = static_cast<int>(len) - 1;
    }
    return SubStr(start, end);
}

stringx stringx::Right(UINT length) const {
    if (length == 0)
        return stringx();
    SXULL len = GetLength();
    int pos = static_cast<int>(len - length);
    if (pos < 0) {
        pos = 0;
        length = (UINT)len;
    }
    return stringx(str_.substr(pos, length));
}

int stringx::Find(const stringx& src, const UINT pos /*= 0*/) const {
    if (pos < 0 || pos >= GetLength())
        return -1;
    return str_.find(src.GetWString(), pos);
}

int stringx::Replace(const stringx& src, const stringx& dest) {
    int ret = 0;
    int pos = Find(src);
    UINT len = wcslen(src.GetData());
    UINT lendest = wcslen(dest.GetData());
    while (pos != -1) {
        str_.replace(pos, len, dest.GetWString());
        pos = Find(src, pos + lendest);
        ret++;
    }
    return ret;
}

stringx& stringx::TrimRight() {
    str_.erase(str_.find_last_not_of(L' ') + 1);
    return *this;
}

stringx& stringx::TrimLeft() {
    str_.erase(0, str_.find_first_not_of(L' '));
    return *this;
}

int stringx::DeleteChar(SXWCH ch) {
    wstring tmp(1, ch);
    return Replace(tmp.c_str(), L"");
}

stringx& stringx::Format(SXCWSTR str, ...) {
    const int buflen = MAX_PATH * 2;
    SXWCH buf[buflen] = { 0 };
    va_list ap;
    va_start(ap, str);
    const int len = _vsnwprintf_s(buf, buflen - 1, str, ap);
    va_end(ap);
    str_ = buf;
    return *this;
}

stringx& stringx::Encode2GBK() {
    if (isutf8_) {
        SXSTR tmp = new SXCH[GetU2GLength(str_.c_str())];
        UTF82GBK(str_.c_str(), tmp);
        SXWSTR tmp2 = new SXWCH[GetA2WLength(tmp)];
        str_ = Str2WStr(tmp, tmp2);
        delete[] tmp;
        delete[] tmp2;
        tmp = NULL;
        tmp2 = NULL;
        isutf8_ = false;
    }
    return *this;
}

stringx& stringx::Encode2UTF8() {
    if (!isutf8_) {
        SXSTR tmp = new SXCH[GetG2ULength(str_.c_str())];
        GBK2UTF8(str_.c_str(), tmp);
        SXWSTR tmp2 = new SXWCH[GetA2WLength(tmp, true)];
        str_ = Str2WStr(tmp, tmp2, true);
        delete[] tmp;
        delete[] tmp2;
        tmp = NULL;
        tmp2 = NULL;
        isutf8_ = true;
    }
    return *this;
}

////////////////////////////////////////

int stringx::GetA2WLength(SXCSTR str, bool isutf8/* = false*/) {
    return MultiByteToWideChar(isutf8 ? CP_UTF8 : CP_ACP, 0,
                               str, -1, NULL, 0);
}

int stringx::GetW2ALength(SXCWSTR str, bool isutf8/* = false*/) {
    return WideCharToMultiByte(isutf8 ? CP_UTF8 : CP_ACP, 0, str,
                               -1, NULL, 0, NULL, NULL);
}

int stringx::GetG2ULength(SXCWSTR str) {
    return WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
}

int stringx::GetU2GLength(SXCWSTR str) {
    return WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
}

SXWSTR stringx::Str2WStr(SXCSTR str, SXWSTR out, bool isutf8/* = false*/) {
    MultiByteToWideChar(isutf8 ? CP_UTF8 : CP_ACP, 0, str,
                        -1, out, GetA2WLength(str, isutf8));
    return out;
}

SXSTR stringx::WStr2Str(SXCWSTR str, SXSTR out, bool isutf8/* = false*/) {
    WideCharToMultiByte(isutf8 ? CP_UTF8 : CP_ACP, 0, str, -1, out,
                        GetW2ALength(str, isutf8), NULL, NULL);
    return out;
}

SXSTR stringx::GBK2UTF8(SXCWSTR str, SXSTR out) {
    WideCharToMultiByte(CP_UTF8, 0, str, -1, out,
                        GetG2ULength(str), NULL, NULL);
    return out;
}

SXSTR stringx::GBK2UTF8(SXCSTR str, SXSTR out) {
    SXWSTR wstr = new SXWCH[GetA2WLength(str)];
    Str2WStr(str, wstr);
    GBK2UTF8(wstr, out);
    delete[] wstr;
    wstr = NULL;
    return out;
}

SXWSTR stringx::GBK2UTF8(SXCWSTR str, SXWSTR out) {
    SXSTR utfstr = new SXCH[GetG2ULength(str)];
    GBK2UTF8(str, utfstr);
    Str2WStr(utfstr, out, true);
    delete[] utfstr;
    utfstr = NULL;
    return out;
}

SXWSTR stringx::GBK2UTF8(SXCSTR str, SXWSTR out) {
    SXWSTR wstr = new SXWCH[GetA2WLength(str)];
    Str2WStr(str, wstr);
    GBK2UTF8(wstr, out);
    delete[] wstr;
    wstr = NULL;
    return out;
}

SXSTR stringx::UTF82GBK(SXCWSTR str, SXSTR out) {
    WideCharToMultiByte(CP_ACP, 0, str, -1, out,
                        GetU2GLength(str), NULL, NULL);
    return out;
}

SXSTR stringx::UTF82GBK(SXCSTR str, SXSTR out) {
    SXWSTR wstr = new SXWCH[GetA2WLength(str, true)];
    Str2WStr(str, wstr, true);
    UTF82GBK(wstr, out);
    delete[] wstr;
    wstr = NULL;
    return out;
}

SXWSTR stringx::UTF82GBK(SXCWSTR str, SXWSTR out) {
    SXSTR gbkstr = new SXCH[GetU2GLength(str)];
    UTF82GBK(str, gbkstr);
    Str2WStr(gbkstr, out);
    delete[] gbkstr;
    gbkstr = NULL;
    return out;
}

SXWSTR stringx::UTF82GBK(SXCSTR str, SXWSTR out) {
    SXWSTR wstr = new SXWCH[GetA2WLength(str, true)];
    Str2WStr(str, wstr, true);
    UTF82GBK(wstr, out);
    delete[] wstr;
    wstr = NULL;
    return out;
}
}    // namespace CryptoLib
