/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/17
 *
 * @Description:
 */
#include "stdafx.h"
#include "windows.h"
#include "../CryptoLib/Include/CryptoLib.h"
#pragma comment(lib, "../bin/CryptoLib.lib")
using namespace CryptoLib;

int main() {
    _tsetlocale(LC_ALL, _T("chs"));
    
    _tprintf(_T("CrytoLib test(UTF-8)\n---------------------------------------\n"));
    // Hash
    LPTSTR str = _T("abc?123");
    _tprintf(_T("	Hash(test string:abc?123)\n	-----------------------------\n"));
    // MD5 default is lower
    _tprintf(_T("	MD5 length:32\n"));
    _tprintf(_T("	MD5 lower:%s\n"), Hash_MD5::Generate(str).GetTString().c_str());
    _tprintf(_T("	MD5 upper:%s\n"), Hash_MD5::Generate(str).MakeUpper().GetTString().c_str());
    _tprintf(_T("	Program MD5:%s\n"), Hash_MD5::GenerateFile(_T("Demo.exe")).GetTString().c_str());
    _tprintf(_T("\n"));
    // SHA1
    _tprintf(_T("	SHA1 length:40\n"));
    _tprintf(_T("	SHA1:%s\n"), Hash_SHA1::Generate(str).GetTString().c_str());
    _tprintf(_T("	Program SHA1:%s\n"), Hash_SHA1::GenerateFile(_T("Demo.exe")).GetTString().c_str());
    _tprintf(_T("\n"));
    // SHA1
    _tprintf(_T("	SHA256 length:64\n"));
    _tprintf(_T("	SHA256:%s\n"), Hash_SHA256::Generate(str).GetTString().c_str());
    _tprintf(_T("	Program SHA256:%s\n"), Hash_SHA256::GenerateFile(_T("Demo.exe")).GetTString().c_str());
    _tprintf(_T("\n"));
    // SHA1
    _tprintf(_T("	SHA512 length:128\n"));
    _tprintf(_T("	SHA512:%s\n"), Hash_SHA512::Generate(str).GetTString().c_str());
    _tprintf(_T("	Program SHA512:%s\n"), Hash_SHA512::GenerateFile(_T("Demo.exe")).GetTString().c_str());
    _tprintf(_T("\n"));
    // SHA1
    _tprintf(_T("	CRC32 length:8\n"));
    _tprintf(_T("	CRC32:%s\n"), Hash_CRC32::Generate(str).GetTString().c_str());
    _tprintf(_T("	Program CRC32:%s\n"), Hash_CRC32::GenerateFile(_T("Demo.exe")).GetTString().c_str());
    _tprintf(_T("\n"));
    
    // encode
    _tprintf(_T("	Encode(test string:abc?123)\n	-----------------------------\n"));
    // Base64
    _tprintf(_T("	Base64 encode:%s\n"), Encode_Base64::Encode(str).GetTString().c_str());
    _tprintf(_T("	Base64 decode:%s\n"), Encode_Base64::Decode(Encode_Base64::Encode(str)).GetTString().c_str());
    _tprintf(_T("\n"));
    // UrlEncode
    _tprintf(_T("	UrlEncode encode:%s\n"), Encode_UrlEncode::Encode(str).GetTString().c_str());
    _tprintf(_T("	UrlEncode decode:%s\n"), Encode_UrlEncode::Decode(Encode_UrlEncode::Encode(str)).GetTString().c_str());
    _tprintf(_T("\n"));
    
    // hardware
    _tprintf(_T("	Hardware Info(may need admin)\n	-----------------------------\n"));
    _tprintf(_T("	Disk SN:%s\n"), Info_DiskSN::GetSN().GetTString().c_str());
    _tprintf(_T("	MAC Address:%s\n"), Info_MacSN::GetSN().GetTString().c_str());
    _tprintf(_T("	CPU SN:%s\n"), Info_CpuSN::GetSN().GetTString().c_str());
    _tprintf(_T("	Baseboard SN:%s\n"), Info_BaseboardSN::GetSN().GetTString().c_str());
    _tprintf(_T("	BIOS SN:%s\n"), Info_BiosSN::GetSN().GetTString().c_str());
    _tprintf(_T("\n"));

    _tprintf(_T("	bignum library:\n	-----------------------------\n"));
    bignum s = 2;
    s ^= 200;
    _tprintf(_T("	2^200=%s\n"), s.GetStr().GetTString().c_str());
    _tprintf(_T("	(2^200)/37=%s\n"), (s / 37).GetStr().GetTString().c_str());
    
    getchar();
    return 0;
}
