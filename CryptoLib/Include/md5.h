/*************************************************************************
¸Ä±à×ÔulwanskiµÄMD5¿â£ºhttps://github.com/ulwanski/md5
*************************************************************************/
#pragma once

namespace CryptoLib {
class Hash_MD5 {
public:
	static LPTSTR Generate(LPCTSTR dat, LPTSTR res);
	static LPTSTR GenerateFile(LPCTSTR filename, LPTSTR res);

protected:
	typedef unsigned int MD5_u32;
	typedef unsigned long MD5_u64;
	typedef const void* MD5_CVP;
	typedef unsigned char MD5_uCH;
	typedef struct {
		MD5_u32 lo, hi;
		MD5_u32 a, b, c, d;
		MD5_uCH buffer[64];
		MD5_u32 block[16];
	} MD5_CTX;

	static void MD5_Init(MD5_CTX* ctx);
	static void MD5_Update(MD5_CTX* ctx, MD5_CVP data, MD5_u64 size);
	static void MD5_Final(MD5_uCH* result, MD5_CTX* ctx);
	static MD5_CVP body(MD5_CTX* ctx, MD5_CVP data, MD5_u64 size);
	static void md5bin(MD5_CVP dat, size_t len, MD5_uCH out[16]);
	static char hb2hex(MD5_uCH hb);
};
}