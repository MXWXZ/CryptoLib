/*************************************************************************
改编自黑猫崽儿的SHA256代码：http://blog.csdn.net/c_duoduo/article/details/43889759
*************************************************************************/
#pragma once

namespace CryptoLib {
class Hash_SHA256 {
public:
	static LPCTSTR Generate(LPCTSTR dat);
	static LPCTSTR GenerateFile(LPCTSTR filename);

protected:
	static char* StrSHA256(const char* str, long long length, char* sha256);
	static char* FileSHA256(const char* file, char* sha256);
};
}