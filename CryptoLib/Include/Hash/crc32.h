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
class Hash_CRC32 {
public:
    static STRX Generate(CSTRX dat);
    static STRX GenerateFile(CSTRX filename);

protected:
    static UINT32 table[];
    static uint32_t GetCRC(uint32_t crcinit, uint8_t * bs, uint32_t bssize);
};
}    // namespace CryptoLib
