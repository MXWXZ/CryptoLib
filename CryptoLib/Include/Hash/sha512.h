/*************************************************************************
改编自ulwanski的SHA512代码：https://github.com/ulwanski/sha512
*************************************************************************/
#pragma once

namespace CryptoLib {
class Hash_SHA512 {
public:
	static LPCTSTR Generate(LPCTSTR dat);
	static LPCTSTR GenerateFile(LPCTSTR filename);

protected:
	static std::string sha512(const void* dat, size_t len);
	static std::string sha512file(const char* filename);
	static void init();
	static void update(const unsigned char *message, unsigned int len);
	static void final(unsigned char *digest);
	static const unsigned int DIGEST_SIZE = (512 / 8);

	typedef unsigned char uint8;
	typedef unsigned long uint32;
	typedef unsigned long long uint64;
	const static uint64 sha512_k[];
	static const unsigned int SHA384_512_BLOCK_SIZE = (1024 / 8);

	static void transform(const unsigned char *message, unsigned int block_nb);
	static unsigned int m_tot_len;
	static unsigned int m_len;
	static unsigned char m_block[2 * SHA384_512_BLOCK_SIZE];
	static uint64 m_h[8];
};
}