/*************************************************************************
MIT License

Copyright (c) 2016

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*************************************************************************/
#pragma once

#include "stdafx.h"

#define CRYPTOLIB_ENABLE_UTF8ONLY		   1		//是否强制使用UTF-8编码

#define CRYPTOLIB_ENABLE_ALL_MODULES       1		//启用所有模块，为1则忽视下面的单独设置

#define CRYPTOLIB_ENABLE_HASH_MD5          0		//启用MD5哈希模块
#define CRYPTOLIB_ENABLE_HASH_SHA1         0		//启用SHA1哈希模块
#define CRYPTOLIB_ENABLE_HASH_SHA256       0		//启用SHA256哈希模块
#define CRYPTOLIB_ENABLE_HASH_SHA512       0		//启用SHA512哈希模块
#define CRYPTOLIB_ENABLE_HASH_CRC32        0		//启用CRC32哈希模块

#define CRYPTOLIB_ENABLE_ENCODE_BASE64     0		//启用Base64加解密模块
#define CRYPTOLIB_ENABLE_ENCODE_URLENCODE  0		//启用UrlEncode加解密模块

#define CRYPTOLIB_ENABLE_INFO_DISKSN	   0		//启用硬盘序列号获取模块
#define CRYPTOLIB_ENABLE_INFO_MACSN		   0		//启用MAC地址获取模块

#include "Utils\stringx.h"

#if (CRYPTOLIB_ENABLE_ALL_MODULES || CRYPTOLIB_ENABLE_HASH_MD5)
#include "Hash/md5.h"
#endif

#if (CRYPTOLIB_ENABLE_ALL_MODULES || CRYPTOLIB_ENABLE_HASH_SHA1)
#include "Hash/sha1.h"
#endif

#if (CRYPTOLIB_ENABLE_ALL_MODULES || CRYPTOLIB_ENABLE_HASH_SHA256)
#include "Hash/sha256.h"
#endif

#if (CRYPTOLIB_ENABLE_ALL_MODULES || CRYPTOLIB_ENABLE_HASH_SHA512)
#include "Hash/sha512.h"
#endif

#if (CRYPTOLIB_ENABLE_ALL_MODULES || CRYPTOLIB_ENABLE_HASH_CRC32)
#include "Hash/crc32.h"
#endif

#if (CRYPTOLIB_ENABLE_ALL_MODULES || CRYPTOLIB_ENABLE_ENCODE_BASE64)
#include "Encode/base64.h"
#endif

#if (CRYPTOLIB_ENABLE_ALL_MODULES || CRYPTOLIB_ENABLE_ENCODE_URLENCODE)
#include "Encode/urlencode.h"
#endif

#if (CRYPTOLIB_ENABLE_ALL_MODULES || CRYPTOLIB_ENABLE_INFO_DISKSN)
#include "Info/disksn.h"
#endif

#if (CRYPTOLIB_ENABLE_ALL_MODULES || CRYPTOLIB_ENABLE_INFO_MACSN)
#include "Info/macsn.h"
#endif