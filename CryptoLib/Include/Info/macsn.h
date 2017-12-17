/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/17
 *
 * @Description:adapted from liruda http://blog.csdn.net/liruda/article/details/2254378
 */
#pragma once

namespace CryptoLib {
class Info_MacSN :public Info_SNBase {
public:
    static STRX GetSN();

protected:
    static STRX GetAdapterInfo(int num);
};
}    // namespace CryptoLib
