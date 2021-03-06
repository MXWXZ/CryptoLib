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
/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/16
 *
 * @Description:
 */
#pragma once

#include "stdafx.h"

#define CRYPTOLIB_ENABLE_UTF8ONLY 1        // Force use UTF-8

#include "Utils/stringx.h"
#include "Utils/bignum.h"

#include "Hash/md5.h"
#include "Hash/sha1.h"
#include "Hash/sha256.h"
#include "Hash/sha512.h"
#include "Hash/crc32.h"

#include "Encode/base64.h"
#include "Encode/urlencode.h"

#include "Info/snbase.h"
#include "Info/disksn.h"
#include "Info/macsn.h"
#include "Info/cpusn.h"
#include "Info/baseboardsn.h"
#include "Info/biossn.h"
