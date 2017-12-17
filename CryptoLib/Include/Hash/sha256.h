/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/17
 *
 * @Description:adapted from 黑猫崽儿 http://blog.csdn.net/c_duoduo/article/details/43889759
 */
#pragma once

namespace CryptoLib {
class Hash_SHA256 {
public:
    static STRX Generate(CSTRX dat);
    static STRX GenerateFile(CSTRX filename);

protected:
    static char* StrSHA256(const char* str, long long length, char* sha256);
    static char* FileSHA256(const char* file, char* sha256);
};
}    // namespace CryptoLib
