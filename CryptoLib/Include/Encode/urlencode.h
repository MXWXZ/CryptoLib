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
class Encode_UrlEncode {
public:
    static STRX Encode(CSTRX dat);
    static STRX Decode(CSTRX dat);
};
}    // namespace CryptoLib
