// Demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "../CryptoLib/Include/CryptoLib.h"
#pragma comment(lib, "../CryptoLib/Lib/CryptoLib.lib")

using namespace CryptoLib;
int main()
{
	//注：在IDE中调试时GenerateFile由于路径问题可能会报错，注释或用绝对路径即可
	_tsetlocale(LC_ALL, _T("chs"));
	_tprintf(_T("CrytoLib库测试（UTF-8编码）\n---------------------------------------\n"));
	//常用哈希
	LPCTSTR str = _T("abc123中文");
	_tprintf(_T("	常用哈希（测试字符串：abc123中文）\n	-----------------------------\n"));
	//MD5
	_tprintf(_T("	MD5 长度：32\n"));
	_tprintf(_T("	MD5值小写：%s\n"), Hash_MD5::Generate(str).GetTString().c_str());			//默认返回小写
	_tprintf(_T("	MD5值大写：%s\n"), _tcsupr((wchar_t*)Hash_MD5::Generate(str).GetTString().c_str()));	//转换成大写
	_tprintf(_T("	本程序MD5：%s\n"), Hash_MD5::GenerateFile(_T("Demo.exe")).GetTString().c_str());	//文件MD5
	_tprintf(_T("\n"));
	//SHA1
	_tprintf(_T("	SHA1 长度：40\n"));
	_tprintf(_T("	SHA1值：%s\n"), Hash_SHA1::Generate(str).GetTString().c_str());
	_tprintf(_T("	本程序SHA1：%s\n"), Hash_SHA1::GenerateFile(_T("Demo.exe")).GetTString().c_str());
	_tprintf(_T("\n"));
	//SHA1
	_tprintf(_T("	SHA256 长度：64\n"));
	_tprintf(_T("	SHA256值：%s\n"), Hash_SHA256::Generate(str).GetTString().c_str());
	_tprintf(_T("	本程序SHA256：%s\n"), Hash_SHA256::GenerateFile(_T("Demo.exe")).GetTString().c_str());
	_tprintf(_T("\n"));
	//SHA1
	_tprintf(_T("	SHA512 长度：128\n"));
	_tprintf(_T("	SHA512值：%s\n"), Hash_SHA512::Generate(str).GetTString().c_str());
	_tprintf(_T("	本程序SHA512：%s\n"), Hash_SHA512::GenerateFile(_T("Demo.exe")).GetTString().c_str());
	_tprintf(_T("\n"));
	//SHA1
	_tprintf(_T("	CRC32 长度：8\n"));
	_tprintf(_T("	CRC32值：%s\n"), Hash_CRC32::Generate(str).GetTString().c_str());
	_tprintf(_T("	本程序CRC32：%s\n"), Hash_CRC32::GenerateFile(_T("Demo.exe")).GetTString().c_str());
	_tprintf(_T("\n"));
	
	//常用加密
	_tprintf(_T("	常用加密（测试字符串：abc123中文）\n	-----------------------------\n"));
	//Base64
	_tprintf(_T("	Base64编码：%s\n"), Encode_Base64::Encode(str).GetTString().c_str());
	_tprintf(_T("	Base64解码：%s\n"), Encode_Base64::Decode(Encode_Base64::Encode(str)).GetTString().c_str());
	_tprintf(_T("\n"));
	//UrlEncode
	_tprintf(_T("	UrlEncode编码：%s\n"), Encode_UrlEncode::Encode(str).GetTString().c_str());
	_tprintf(_T("	UrlEncode解码：%s\n"), Encode_UrlEncode::Decode(Encode_UrlEncode::Encode(str)).GetTString().c_str());
	_tprintf(_T("\n"));

	//硬件信息
	_tprintf(_T("	硬件信息（需要管理员权限）\n	-----------------------------\n"));
	_tprintf(_T("	硬盘序列号：%s\n"),Info_DiskSN::GetSN().GetTString().c_str());
	
	getchar();
    return 0;
}

