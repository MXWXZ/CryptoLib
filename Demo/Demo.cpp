// Demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../CryptoLib/Include/CryptoLib.h"
#pragma comment(lib, "../CryptoLib/Lib/CryptoLib.lib")

using namespace CryptoLib;

int main()
{
	_tsetlocale(LC_ALL, _T("chs"));
	_tprintf(_T("CrytoLib库测试\n---------------------------------------\n"));
	//常用哈希
	LPCTSTR str = _T("123456");
	_tprintf(_T("	常用哈希（测试字符串：123456）\n	-----------------------------\n"));
	//MD5
	_tprintf(_T("	MD5 长度：32\n"));
	_tprintf(_T("	MD5值小写：%s\n"),Hash_MD5::Generate(str));				//默认返回小写
	_tprintf(_T("	MD5值大写：%s\n"), _tcsupr(const_cast<wchar_t*>(Hash_MD5::Generate(str))));	//转换成大写
	_tprintf(_T("	本程序MD5：%s\n"), Hash_MD5::GenerateFile(_T("Demo.exe")));	//文件MD5
	_tprintf(_T("\n"));
	//SHA1
	_tprintf(_T("	SHA1 长度：40\n"));
	_tprintf(_T("	SHA1值：%s\n"), Hash_SHA1::Generate(str));				//默认返回小写
	_tprintf(_T("	本程序SHA1：%s\n"), Hash_SHA1::GenerateFile(_T("Demo.exe")));	//文件MD5
	_tprintf(_T("\n"));
	//SHA1
	_tprintf(_T("	SHA256 长度：64\n"));
	_tprintf(_T("	SHA256值：%s\n"), Hash_SHA256::Generate(str));				//默认返回小写
	_tprintf(_T("	本程序SHA256：%s\n"), Hash_SHA256::GenerateFile(_T("Demo.exe")));	//文件MD5
	_tprintf(_T("\n"));
	//SHA1
	_tprintf(_T("	SHA512 长度：128\n"));
	_tprintf(_T("	SHA512值：%s\n"), Hash_SHA512::Generate(str));				//默认返回小写
	_tprintf(_T("	本程序SHA512：%s\n"), Hash_SHA512::GenerateFile(_T("Demo.exe")));	//文件MD5
	_tprintf(_T("\n"));
	getchar();
    return 0;
}

