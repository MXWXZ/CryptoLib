/*************************************************************************
¸Ä±à×ÔvogµÄSHA1¿â£ºhttps://github.com/vog/sha1
============
SHA-1 in C++
============

100% Public Domain.

Original C Code
-- Steve Reid <steve@edmweb.com>
Small changes to fit into bglibs
-- Bruce Guenter <bruce@untroubled.org>
Translation to simpler C++ Code
-- Volker Grabsch <vog@notjusthosting.com>
Safety fixes
-- Eugene Hopkinson <slowriot at voxelstorm dot com>
*************************************************************************/
#pragma once

namespace CryptoLib {
class Hash_SHA1 {
public:
	static LPCTSTR Generate(LPCTSTR dat);
	static LPCTSTR GenerateFile(LPCTSTR filename);

protected:
	static const size_t BLOCK_INTS = 16;
	static const size_t BLOCK_BYTES = BLOCK_INTS * 4;

	static uint32_t digest[5];
	static std::string buffer;
	static uint64_t transforms;

	static void reset(uint32_t digest[], std::string &buffer, uint64_t &transforms);
	static uint32_t rol(const uint32_t value, const size_t bits);
	static uint32_t blk(const uint32_t block[BLOCK_INTS], const size_t i);
	static void R0(const uint32_t block[BLOCK_INTS], const uint32_t v, 
				   uint32_t &w, const uint32_t x, const uint32_t y, 
				   uint32_t &z, const size_t i);
	static void R1(uint32_t block[BLOCK_INTS], const uint32_t v,
				   uint32_t &w, const uint32_t x, const uint32_t y,
				   uint32_t &z, const size_t i);
	static void R2(uint32_t block[BLOCK_INTS], const uint32_t v,
				   uint32_t &w, const uint32_t x, const uint32_t y,
				   uint32_t &z, const size_t i);
	static void R3(uint32_t block[BLOCK_INTS], const uint32_t v,
				   uint32_t &w, const uint32_t x, const uint32_t y,
				   uint32_t &z, const size_t i);
	static void R4(uint32_t block[BLOCK_INTS], const uint32_t v,
				   uint32_t &w, const uint32_t x, const uint32_t y,
				   uint32_t &z, const size_t i);
	static void transform(uint32_t digest[], uint32_t block[BLOCK_INTS], uint64_t &transforms);
	static void buffer_to_block(const std::string &buffer, uint32_t block[BLOCK_INTS]);
	static void update(std::istream &is);
	static LPCTSTR Final();
};
}