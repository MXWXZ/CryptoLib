/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/17
 *
 * @Description:
 */
#pragma once

namespace CryptoLib {
class Encode_Base64 {
public:
    static STRX Encode(CSTRX dat);
    static STRX Decode(CSTRX dat);

protected:
    static const std::string base64_chars;
    static inline bool is_base64(unsigned char c);
};
}    // namespace CryptoLib
