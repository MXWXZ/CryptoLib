/*************************************************************************
¸Ä±à×ÔulwanskiµÄMD5¿â£ºhttps://github.com/ulwanski/md5
*************************************************************************/
#pragma once

namespace CryptoLib {
class Encode_UrlEncode
{
public:
	static STRX Encode(STRX dat);
	static STRX Decode(STRX dat);
};
}