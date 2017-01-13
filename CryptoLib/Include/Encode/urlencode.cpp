/*************************************************************************
¸Ä±à×ÔulwanskiµÄMD5¿â£ºhttps://github.com/ulwanski/md5
*************************************************************************/
#include "stdafx.h"
#include "urlencode.h"

namespace CryptoLib {
/************************************************************************
RFC3986:unreserved  = ALPHA / DIGIT / "-" / "." / "_" / "~"
************************************************************************/
STRX Encode_UrlEncode::Encode(STRX dat) {
#if CRYPTOLIB_ENABLE_UTF8ONLY
	dat.Encode2UTF8();
#endif
	string rec = dat.GetString();
	const char* str = rec.c_str();
	STRX ret;
	int len = strlen(str);
	for (int i = 0; i < len; i++){
		if (isalpha(str[i]) || isdigit(str[i])) {
			ret += str[i];
		} else if (str[i] == '-' || str[i] == '_' || str[i] == '.' || str[i] == '~') {
			ret += str[i];
		} else {
			ret.Format(L"%s%%%02x", ret.GetWString().c_str(), (BYTE)str[i]);
		}
	}
	return ret;
}

STRX Encode_UrlEncode::Decode(STRX dat) {
	string rec = dat.GetString();
	const char* str = rec.c_str();
	string tmpstr;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		char c1, c2;
		switch (str[i]) {
			case '%':
				c1 = str[++i];
				c2 = str[++i];
				if (c1 >= '0' && c1 <= '9')
					c1 -= '0';
				else if (c1 >= 'a' && c1 <= 'f')
					c1 -= 'a' - 10;
				else if (c1 >= 'A' && c1 <= 'F')
					c1 -= 'A' - 10;
				if (c2 >= '0' && c2 <= '9')
					c2 -= '0';
				else if (c2 >= 'a' && c2 <= 'f')
					c2 -= 'a' - 10;
				else if (c2 >= 'A' && c2 <= 'F')
					c2 -= 'A' - 10;
				char tmp[8];
				sprintf(tmp, "%c", (char)(c1 * 16 + c2));
				tmpstr += tmp;
				break;
			case '+':
				tmpstr += ' ';
				break;
			default:
				tmpstr += str[i];
		}
	}
	STRX ret = tmpstr;
	ret.SetEncodeUTF8();
#if CRYPTOLIB_ENABLE_UTF8ONLY
	return ret.Encode2GBK();
#else
	return ret;
#endif
}
}