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
#include "base64.h"

namespace CryptoLib {
const std::string Encode_Base64::base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

inline bool Encode_Base64::is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

STRX Encode_Base64::Encode(CSTRX dat) {
    string rec;
#if CRYPTOLIB_ENABLE_UTF8ONLY
    rec = dat.GetUTF8Str().GetString();
#else
    rec = dat.GetString();
#endif
    const char* str = rec.c_str();
    STRX ret;
    int i = 0;
    int j = 0;
    int len = strlen(str);
    int pos = 0;
    uint8_t char_array_3[3];
    uint8_t char_array_4[4];

    while (len--) {
        char_array_3[i++] = str[pos++];
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';
    }
    return ret;
}

STRX Encode_Base64::Decode(CSTRX dat) {
    string rec = dat.GetString();
    const char* str = rec.c_str();
    int len = strlen(str);
    int i = 0;
    int j = 0;
    int tmp = 0;
    unsigned char char_array_4[4], char_array_3[3];
    string rettmp;

    while (len-- && (str[tmp] != '=') && is_base64(str[tmp])) {
        char_array_4[i++] = str[tmp]; tmp++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = (unsigned char)base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                rettmp += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = (unsigned char)base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) rettmp += char_array_3[j];
    }
    STRX ret(rettmp, true);
#if CRYPTOLIB_ENABLE_UTF8ONLY
    return ret.Encode2GBK();
#else
    return rettmp;
#endif
}
}    // namespace CryptoLib
