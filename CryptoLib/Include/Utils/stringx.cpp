#include "stdafx.h"
#include "stringx.h"

/************************************************************************
构造函数
************************************************************************/
stringx::stringx(SXCWCH ch, const UINT rep /*= 1*/) { SetString(ch, rep); }
stringx::stringx(SXCSTR src)					{ assert(src); SetString(src); }
stringx::stringx(SXCWSTR src)					{ assert(src); SetString(src); }
stringx::stringx(const string& src)				{ SetString(src); }
stringx::stringx(const wstring& src)			{ SetString(src); }
stringx::stringx(const stringx& src)			{ SetString(src); }

/************************************************************************
设置字符串值
返回值：当前stringx对象
************************************************************************/
stringx& stringx::SetString(SXCWCH ch, const UINT rep /*= 1*/) {
	str_.assign(rep, ch);
	return *this;
}

stringx& stringx::SetString(SXCSTR src) {
	assert(src);
	
	SXWSTR wstr = new SXWCH[GetAWConvertLength(src)];
	str_ = Str2WStr(src, wstr);
	delete[] wstr;
	wstr = NULL;
	return *this;
}

stringx& stringx::SetString(SXCWSTR src) {
	assert(src);

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

/************************************************************************
数字转字符串
digit:待转换数字，不超过18446744073709551615
返回值：当前stringx对象
************************************************************************/
stringx& stringx::SetDigit(SXCULL digit) {
	SXWSTR str = new SXWCH[128];
	_ui64tow(digit, str, 10);
	str_ = str;
	delete[] str;
	str = NULL;
	return *this;
}

/************************************************************************
取字符串
返回值：取值后的string/wstring
************************************************************************/
string stringx::GetString() const {
	SXSTR str = new SXCH[GetAWConvertLength(str_.c_str())];
	WStr2Str(str_.c_str(), str);
	string ret = str;
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

/************************************************************************
取字符串
out:接收字符串的指针，需要预先初始化
返回值：接收字符串指针
************************************************************************/
SXSTR stringx::GetData(SXSTR out) const {
	WStr2Str(str_.c_str(), out);
	return out;
}

SXWSTR stringx::GetData(SXWSTR out) const {
	wcscpy(out, str_.c_str());
	return out;
}

/************************************************************************
取宽字节字符串
返回值：宽字节字符串
************************************************************************/
SXCWSTR stringx::GetData() const {
	return str_.c_str();
}

/************************************************************************
字符串转数字
返回值：转换后数字，不超过18446744073709551615
************************************************************************/
SXULL stringx::GetDigit() const {
	return wcstoull(str_.c_str(), NULL, 10);
}

/************************************************************************
取真实wstring对象
返回值：wstring对象的引用，对其的改动会同时影响stringx中的值
************************************************************************/
wstring& stringx::GetBuffer() {
	return str_;
}

/************************************************************************
取字符串完整长度（用于初始化数组等）
返回值：字符串完整长度
************************************************************************/
int stringx::GetADataLength() {
	return GetAWConvertLength(str_.c_str());
}

int stringx::GetWDataLength() {
	return (int)GetLength() + 1;
}

/************************************************************************
判断是否是纯数字
返回：true是 false 否
************************************************************************/
bool stringx::IsDigit() const {
	for (UINT i = 0; i < (UINT)GetLength(); ++i) {
		if (i == 0 && str_[i] == L'-')
			continue;
		if (str_[i] < L'0' || str_[i] > L'9')
			return false;
	}
	return true;
}

/************************************************************************
清空字符串
************************************************************************/
void stringx::Empty() {
	str_.clear();
}

/************************************************************************
判断字符串是否为空
返回值：true空 false非空
************************************************************************/
bool stringx::IsEmpty() const {
	return str_.empty();
}

/************************************************************************
取字符串长度，中文长度算1
************************************************************************/
SXULL stringx::GetLength() const {
	return str_.length();
}

/************************************************************************
取字符串某一位
index:字符位置，从0开始
返回值：位置上的字符，中文需用wchar接收
************************************************************************/
SXWCH stringx::GetAt(const int index) const {
	return str_[index];
}

/************************************************************************
设置字符串某一位
index:字符位置，从0开始
ch:单个字符，中文需用wchar传入
************************************************************************/
void stringx::SetAt(const int index, SXCWCH ch) {
	str_[index] = ch;
}

/************************************************************************
追加字符串
参数：待添加字符串
返回值：当前stringx对象
************************************************************************/
stringx& stringx::Append(const stringx& src) { str_.append(src.GetWString()); return *this; }
stringx& stringx::Append(SXCWCH ch, const UINT rep /*= 1*/) { str_.append(rep, ch); return *this; }

/************************************************************************
重载[]
************************************************************************/
SXWCH stringx::operator[] (const UINT index) const {
	return str_[index];
}

/************************************************************************
重载= + +=
************************************************************************/
stringx& stringx::operator=(const stringx&  src) { SetString(src); return *this; }
stringx stringx::operator+(const stringx&  src) const { stringx temp = *this; temp.Append(src); return temp; }
const stringx& stringx::operator+=(const stringx&  src)	{ Append(src); return *this; }

/************************************************************************
字符串比较
src:待比较字符串
************************************************************************/
int stringx::Compare(const stringx& src) const  { return str_.compare(src.GetWString()); }

/************************************************************************
字符串忽视大小写比较
src:待比较字符串
************************************************************************/
int stringx::CompareNoCase(const stringx& src) const { return _wcsicmp(str_.c_str(), src.GetWString().c_str()); }

/************************************************************************
重载== != < <= > >=
************************************************************************/
bool stringx::operator == (const stringx& src) const { return (Compare(src) == 0); };
bool stringx::operator != (const stringx& src) const { return (Compare(src) != 0); };
bool stringx::operator <= (const stringx& src) const { return (Compare(src) <= 0); };
bool stringx::operator < (const stringx& src)  const { return (Compare(src) < 0); };
bool stringx::operator >= (const stringx& src) const { return (Compare(src) >= 0); };
bool stringx::operator > (const stringx& src)  const { return (Compare(src) > 0); };

/************************************************************************
自定义大小写转换函数
c:待转换字符
返回值：是字母则转换，否则返回原值
************************************************************************/
int stringx::ToUpper(int c) {
	if (isalpha(c))
		return toupper(c);
	else return c;
}

int stringx::ToLower(int c) {
	if (isalpha(c))
		return tolower(c);
	else return c;
}

/************************************************************************
大小写转换
返回值：当前stringx对象
************************************************************************/
stringx& stringx::MakeUpper() {
	transform(str_.begin(), str_.end(), str_.begin(), ToUpper);
	return *this;
}

stringx& stringx::MakeLower() {
	transform(str_.begin(), str_.end(), str_.begin(), ToLower);
	return *this;
}

/************************************************************************
取字符串的子串
from:开始位置（包括），超过尾端返回空
to:结束位置（包括），超过尾端全部取
返回值：取得的stringx对象
************************************************************************/
stringx stringx::SubStr(UINT from, UINT to) const {
	SXULL len = GetLength();
	if (from >= len)
		return stringx();
	if (to >= len)
		to = (UINT)len - 1;
	return stringx(str_.substr(from, to - from + 1));
}

/************************************************************************
取左边开始的字符串
length:字符串长度，超过尾端全部取
返回值：取得的stringx对象
************************************************************************/
stringx stringx::Left(UINT length) const {
	if (length == 0)
		return stringx();
	SXULL len = GetLength();
	if (length > len)
		length = (UINT)len;
	return stringx(str_.substr(0, length));
}

/************************************************************************
取中间开始的字符串
pos:起始位置
length:字符串长度，负值向前取，大于剩余长度则全部取
返回值：取得的stringx对象
************************************************************************/
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
			end = (int)len - 1;
	}
	return SubStr(start, end);
}

/************************************************************************
取右边开始的字符串
length:字符串长度，大于原长度则全部取
返回值：取得的stringx对象
************************************************************************/
stringx stringx::Right(UINT length) const {
	if (length == 0)
		return stringx();
	SXULL len = GetLength();
	int pos = (int)(len - length);
	if (pos < 0) {
		pos = 0;
		length = (UINT)len;
	}
	return stringx(str_.substr(pos, length));
}

/************************************************************************
查找字符/字符串出现位置
src:查找字符串
ch:查找字符
pos:开始查找的位置
返回值：-1不存在否则返回第一次出现位置
************************************************************************/
int stringx::Find(const stringx& src, const UINT pos /*= 0*/) const {
	if (pos < 0 || pos >= GetLength())
		return -1;
	return str_.find(src.GetWString(), pos);
}

/************************************************************************
替换字符串
src:待替换字符串
ch:待替换字符
返回值：替换次数
************************************************************************/
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

/************************************************************************
去除左边空格
返回值：当前stringx对象
************************************************************************/
stringx& stringx::TrimRight() {
	str_.erase(str_.find_last_not_of(L' ') + 1);
	return *this;
}

/************************************************************************
去除右边空格
返回值：当前stringx对象
************************************************************************/
stringx& stringx::TrimLeft() {
	str_.erase(0, str_.find_first_not_of(L' '));
	return *this;
}

/************************************************************************
删除字符
返回值：删除个数
************************************************************************/
int stringx::DeleteChar(SXWCH ch) {
	wstring tmp(1, ch);
	return Replace(tmp.c_str(), L"");
}

/************************************************************************
格式化字符串
str:格式字符串
注：变参字符串需要用宽字节版本，否则不支持中文
返回值：当前stringx对象
************************************************************************/
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

/************************************************************************
GBK/UTF8编码互转
返回值：当前stringx对象
************************************************************************/
stringx& stringx::Encode2GBK() {
	if (isutf8_) {
		SXSTR tmp = new SXCH[GetGUConvertLength(str_.c_str())];
		UTF82GBK(str_.c_str(), tmp);
		SXWSTR tmp2 = new SXWCH[GetAWConvertLength(tmp)];
		Str2WStr(tmp, tmp2);
		str_ = tmp2;
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
		SXSTR tmp = new SXCH[GetAWConvertLength(str_.c_str())];
		WStr2Str(str_.c_str(), tmp);
		SXWSTR tmp2 = new SXWCH[GetGUConvertLength(tmp)];
		GBK2UTF8(tmp, tmp2);
		str_ = tmp2;
		delete[] tmp;
		delete[] tmp2;
		tmp = NULL;
		tmp2 = NULL;
		isutf8_ = true;
	}
	return *this;
}

/************************************************************************
取得多字节 宽字节互转所需长度
************************************************************************/
int stringx::GetAWConvertLength(SXCSTR str) {
	return MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
}

int stringx::GetAWConvertLength(SXCWSTR str) {
	return WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
}

/************************************************************************
取得GBK UTF8互转所需长度
************************************************************************/
int stringx::GetGUConvertLength(SXCSTR str) {
	return MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
}

int stringx::GetGUConvertLength(SXCWSTR str) {
	return WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
}

/************************************************************************
多字节/宽字节互转
str:待转换字符串
out:输出字符串
返回值：输出字符串指针
************************************************************************/
SXWSTR stringx::Str2WStr(SXCSTR str, SXWSTR out) {
	assert(str);
	assert(out);
	
	MultiByteToWideChar(CP_ACP, 0, str, -1, out, GetAWConvertLength(str));
	return out;
}

SXSTR stringx::WStr2Str(SXCWSTR str, SXSTR out) {
	assert(str);
	assert(out);

	WideCharToMultiByte(CP_ACP, 0, str, -1, out, GetAWConvertLength(str),
						NULL, NULL);
	return out;
}

/************************************************************************
GBK/UTF8互转
str:待转换字符串
out:输出字符串
返回值：输出字符串指针
************************************************************************/
SXSTR stringx::GBK2UTF8(SXCSTR str, SXSTR out) {
	assert(str);
	assert(out);

	SXWSTR wstr = new SXWCH[GetAWConvertLength(str)];
	Str2WStr(str, wstr);
	GBK2UTF8(wstr, out);
	delete[] wstr;
	wstr = NULL;
	return out;
}

SXWSTR stringx::GBK2UTF8(SXCSTR str, SXWSTR out) {
	assert(str);
	assert(out);

	SXWSTR wstr = new SXWCH[GetAWConvertLength(str)];
	Str2WStr(str, wstr);
	GBK2UTF8(wstr, out);
	delete[] wstr;
	wstr = NULL;
	return out;
}

SXSTR stringx::GBK2UTF8(SXCWSTR str, SXSTR out) {
	assert(str);
	assert(out);

	WideCharToMultiByte(CP_UTF8, 0, str, -1, out,
						GetGUConvertLength(str),
						NULL, NULL);
	return out;
}

SXWSTR stringx::GBK2UTF8(SXCWSTR str, SXWSTR out) {
	assert(str);
	assert(out);

	const int len = GetGUConvertLength(str);
	SXSTR utfstr = new SXCH[len];
	WideCharToMultiByte(CP_UTF8, 0, str, -1, utfstr, len, NULL, NULL);
	Str2WStr(utfstr, out);
	delete[] utfstr;
	utfstr = NULL;
	return out;
}

SXWSTR stringx::UTF82GBK(SXCWSTR str, SXWSTR out) {
	assert(str);
	assert(out);

	SXSTR tmp = new SXCH[GetAWConvertLength(str)];
	WStr2Str(str, tmp);
	UTF82GBK(tmp, out);
	delete[] tmp;
	tmp = NULL;
	return out;
}

SXSTR stringx::UTF82GBK(SXCWSTR str, SXSTR out) {
	assert(str);
	assert(out);
	
	SXSTR tmp = new SXCH[GetAWConvertLength(str)];
	WStr2Str(str, tmp);
	UTF82GBK(tmp, out);
	delete[] tmp;
	tmp = NULL;
	return out;
}

SXWSTR stringx::UTF82GBK(SXCSTR str, SXWSTR out) {
	assert(str);
	assert(out);

	MultiByteToWideChar(CP_UTF8, 0, str, -1, out,
						MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0));
	return out;
}

SXSTR stringx::UTF82GBK(SXCSTR str, SXSTR out) {
	assert(str);
	assert(out);

	int len = GetGUConvertLength(str);
	SXWSTR gbkstr = new SXWCH[len];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, gbkstr, len);
	WStr2Str(gbkstr, out);
	delete[] gbkstr;
	gbkstr = NULL;
	return out;
}