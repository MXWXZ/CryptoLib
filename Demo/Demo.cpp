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
	TCHAR res[1024] = { 0 };					//接收哈希值数组，大小需比哈希值长度大，本库不进行越界检查
	_tprintf(_T("	常用哈希（测试字符串：123456）\n	-----------------------------\n"));
	//MD5
	_tprintf(_T("	MD5值小写：%s\n"),Hash_MD5::Generate(str,res));				//默认返回小写
	_tprintf(_T("	MD5值大写：%s\n"), _tcsupr(Hash_MD5::Generate(str,res)));	//转换成大写
	_tprintf(_T("	本程序MD5：%s\n"), Hash_MD5::GenerateFile(_T("Demo.exe"),res));	//文件MD5
	getchar();
    return 0;
}

