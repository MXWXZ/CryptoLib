/*************************************************************************
改编自ulwanski的SHA512代码：https://github.com/ulwanski/sha512
*************************************************************************/
#pragma once

namespace CryptoLib {
class Hash_SHA512 {
public:
	static STRX Generate(STRX dat);
	static STRX GenerateFile(STRX filename);

protected:
	static std::string sha512(const void* dat, size_t len);
	static std::string sha512file(const char* filename);
	static void init();
	static void update(const uint8_t* message, const uint32_t len);
	static void final(uint8_t* digest);
	static const uint32_t DIGEST_SIZE = (512 / 8);

	const static uint64_t sha512_k[];
	static const uint32_t SHA384_512_BLOCK_SIZE = (1024 / 8);

	static void transform(const uint8_t *message, uint32_t block_nb);
	static uint32_t m_tot_len;
	static uint32_t m_len;
	static uint8_t m_block[2 * SHA384_512_BLOCK_SIZE];
	static uint64_t m_h[8];
};
}