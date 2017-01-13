/*************************************************************************
¸Ä±à×ÔulwanskiµÄMD5¿â£ºhttps://github.com/ulwanski/md5
*************************************************************************/
#pragma once

namespace CryptoLib {
class Hash_MD5 {
public:
	static STRX Generate(STRX dat);
	static STRX GenerateFile(STRX filename);

protected:
	typedef struct {
		uint32_t lo, hi;
		uint32_t a, b, c, d;
		uint8_t buffer[64];
		uint32_t block[16];
	} MD5_CTX;

	static void MD5_Init(MD5_CTX* ctx);
	static void MD5_Update(MD5_CTX* ctx, const void* data, unsigned long size);
	static void MD5_Final(uint8_t* result, MD5_CTX* ctx);
	static const void* body(MD5_CTX* ctx, const void* data, unsigned long size);
	static void md5bin(const void* dat, size_t len, uint8_t out[16]);
	static char hb2hex(uint8_t hb);
};
}