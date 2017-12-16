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

#include "stringx.h"

namespace CryptoLib {
const int kMaxNumLength = 256;      // max digit length

class bignum {
public:
    bignum() {}
    explicit bignum(const int64_t num);
    bignum(CSTRX str);
    explicit bignum(const bignum& num);
    ~bignum() {}
    void Init();

    /**
     * Set digit
     * range: -9223372036854775807-9223372036854775807
     */
    bignum& SetDigit(const int64_t num);
    bignum& SetDigit(CSTRX num);
    bignum& SetDigit(const bignum& num);
    int64_t GetDigit() const;
    STRX GetStr() const;
    SXULL GetLength() const;
    bool IsNegetive() const;
    bignum Abs() const;
    bignum Factorial() const;

    bignum operator-() const;
    bignum& operator=(const bignum& src);
    bignum operator+(const bignum& src) const;
    bignum operator-(const bignum& src) const;
    bignum operator*(const bignum& src) const;
    bignum operator/(const bignum& src) const;
    bignum operator^(const bignum& src) const;
    bignum operator%(const bignum& src) const;
    bignum& operator+=(const bignum& src);
    bignum& operator-=(const bignum& src);
    bignum& operator*=(const bignum& src);
    bignum& operator/=(const bignum& src);
    bignum& operator^=(const bignum& src);
    bignum& operator%=(const bignum& src);

    int Compare(const bignum& src) const;
    bool operator==(const bignum& src)const;
    bool operator!=(const bignum& src)const;
    bool operator>(const bignum& src)const;
    bool operator>=(const bignum& src)const;
    bool operator<(const bignum& src)const;
    bool operator<=(const bignum& src)const;

    bignum& operator++();
    bignum operator++(int);
    bignum& operator--();
    bignum operator--(int);

protected:
    int num_[kMaxNumLength] = { 0 };
    int len_ = 1;
    bool negative_ = false;     // false +/0 true -

    int64_t llpow(const int x) const;
    bignum Divide(const bignum& a, const bignum& b) const;
};
}    // namespace CryptoLib
