#include "stdafx.h"
#include "bignum.h"

/************************************************************************
初始化
************************************************************************/
void bignum::Init() {
	negative_ = false;
	len_ = 1;
	memset(num_, 0, sizeof(num_));
}

/************************************************************************
构造函数
************************************************************************/
bignum::bignum(const int64_t num) {
	SetDigit(num);
}

bignum::bignum(CSTRX str) {
	SetDigit(str);
}

bignum::bignum(const bignum& num) {
	SetDigit(num);
}

/************************************************************************
初始化数字
数字范围long long（-9223372036854775807~9223372036854775807）
************************************************************************/
bignum& bignum::SetDigit(const int64_t num) {
	if (num < 0) {
		SetDigit(-num);
		negative_ = true;
	} else {
		Init();
		if (num != 0) {
			int64_t t = num;
			int pos = 0;
			while (t > 0) {
				assert(pos < kMaxNumLength);

				num_[pos++] = t % 10;
				t /= 10;
			}
			len_ = pos;
		}
	}
	return *this;
}

bignum& bignum::SetDigit(CSTRX str) {
	Init();
	if (str.IsDigit()) {
		len_ = (int)str.GetLength();

		assert(len_ <= kMaxNumLength);

		for (int i = len_ - 1; i >= 0; --i)
			num_[i] = str[len_ - i - 1] - '0';
		if (str[0] == L'-') {
			num_[len_ - 1] = 0;
			len_--;
			negative_ = true;
		}
	}
	return *this;
}

bignum& bignum::SetDigit(const bignum& num) {
	Init();
	len_ = num.len_;

	assert(len_ <= kMaxNumLength);

	for (int i = 0; i < len_; ++i)
		num_[i] = num.num_[i];
	negative_ = num.negative_;
	return *this;
}

bignum& bignum::operator=(const bignum& src) {
	SetDigit(src);
	return *this;
}

/************************************************************************
long long的乘方处理
************************************************************************/
int64_t bignum::llpow(const int x) const {
	int64_t ret = 1;
	for (int i = 0; i < x; ++i)
		ret *= 10;
	return ret;
}

/************************************************************************
取得数字 范围long long（-9223372036854775807~9223372036854775807）
************************************************************************/
int64_t bignum::GetDigit() const {
	if ((*this) < -9223372036854775807 || (*this) > (int64_t)9223372036854775807)
		return 0;
	int64_t ret = 0;
	for (int i = len_ - 1; i >= 0; --i)
		ret += num_[i] * llpow(i);
	if (negative_)
		ret = -ret;
	return ret;
}

/************************************************************************
取得字符串
************************************************************************/
STRX bignum::GetStr() const {
	STRX ret;
	if (negative_)
		ret += L'-';
	for (int i = len_ - 1; i >= 0; --i)
		ret += num_[i] + L'0';
	return ret;
}

/************************************************************************
取得长度
************************************************************************/
SXULL bignum::GetLength() const {
	return len_;
}

/************************************************************************
是否为负数
false否 true是
************************************************************************/
bool bignum::IsNegetive() const {
	return negative_;
}

/************************************************************************
取绝对值
************************************************************************/
bignum bignum::Abs() const {
	bignum t = *this;
	if (negative_)
		return -t;
	else
		return t;
}

bignum bignum::Factorial() const {
	bignum ret = 1;
	for (bignum i = 2; i <= *this; ++i)
		ret *= i;
	return ret;
}

/************************************************************************
乘方运算
************************************************************************/
bignum bignum::operator^(const bignum & src) const {
	if (*this == 0)
		return bignum(0);
	if (src == 0)
		return bignum(1);
	bignum ret = *this;
	if (src.negative_) {
		if (src == -1 && (ret == 1 || ret == -1))
			return ret;
		else
			return bignum(0);
	}
	for (bignum i = 1; i < src; ++i)
		ret *= *this;
	return ret;
}

bignum& bignum::operator^=(const bignum & src) {
	*this = (*this) ^ src;
	return *this;
}

/************************************************************************
四则运算
************************************************************************/
bignum bignum::operator-() const {
	bignum ret = *this;
	ret.negative_ = !ret.negative_;
	return ret;
}

bignum bignum::operator+(const bignum& src) const {
	bignum t = *this;
	bool judge = false;
	if (t.negative_ && src.negative_)
		judge = true;
	if (!t.negative_ && src.negative_)
		return (t - (-src));
	if (t.negative_ && !src.negative_)
		return (src - (-t));
	int mxlen = max(t.len_, src.len_);
	int j = 0;
	for (int i = 0; i < mxlen + 1; i++) {
		assert(i < kMaxNumLength);

		t.num_[i] = t.num_[i] + src.num_[i] + j;
		if (t.num_[i] >= 10)
			j = 1;
		else
			j = 0;
		t.num_[i] = t.num_[i] % 10;
	}
	t.len_ = mxlen;
	if (t.num_[mxlen] != 0)
		t.len_++;
	t.negative_ = judge;
	return t;
}

bignum& bignum::operator+=(const bignum& src) {
	*this = (*this) + src;
	return *this;
}

bignum bignum::operator-(const bignum& src) const {
	bignum t = *this;
	bool judge = false;
	if (t.negative_ && src.negative_)
		return ((-src) - (-t));
	if (!t.negative_ && src.negative_)
		return (t + (-src));
	if (t.negative_ && !src.negative_)
		return -((-t) + src);
	bignum ret;
	const bignum* bigger = &t;
	const bignum* smaller = &src;
	if (t < src) {
		bigger = &src;
		smaller = &t;
		judge = true;
	}
	ret.len_ = bigger->len_;
	int j = 0;
	for (int i = 0; i < bigger->len_; ++i) {
		if (bigger->num_[i] - j >= smaller->num_[i]) {
			assert(i < kMaxNumLength);

			ret.num_[i] = bigger->num_[i] - j - smaller->num_[i];
			j = 0;
		} else {
			ret.num_[i] = bigger->num_[i] + 10 - j - smaller->num_[i];
			j = 1;
		}
	}
	for (int i = ret.len_ - 1; i >= 0; --i)
		if (ret.num_[i] == 0)
			ret.len_--;
		else
			break;
	if (ret.len_ == 0)
		ret.Init();
	ret.negative_ = judge;
	return ret;
}

bignum& bignum::operator-=(const bignum& src) {
	*this = (*this) - src;
	return *this;
}

bignum bignum::operator*(const bignum& src) const {
	const bignum* t = this;
	bool judge = false;
	if (!t->negative_ && src.negative_)
		judge = true;
	if (t->negative_ && !src.negative_)
		judge = true;
	bignum ret;
	ret.len_ = max(t->len_, src.len_);
	for (int i = 0; i < src.len_; ++i) {
		for (int j = 0; j < t->len_; ++j) {
			assert(i + j < kMaxNumLength);

			ret.num_[i + j] += src.num_[i] * t->num_[j];
			if (ret.num_[i + j] >= 10) {
				assert(i + j + 1 < kMaxNumLength);

				ret.num_[i + j + 1] += ret.num_[i + j] / 10;
				ret.num_[i + j] %= 10;
				if (i + j + 1 > ret.len_ - 1)
					ret.len_ = i + j + 2;
			}
			if (i + j > ret.len_ - 1)
				ret.len_ = i + j + 1;
		}
	}
	ret.negative_ = judge;
	return ret;
}

bignum& bignum::operator*=(const bignum& src) {
	*this = (*this)*src;
	return *this;
}

/************************************************************************
二分答案返回a/b
************************************************************************/
bignum bignum::Divide(const bignum& a, const bignum& b) const {
	if (a < b)
		return bignum(0);
	if (a == b)
		return bignum(1);
	bignum ret;
	bignum j = 1;
	for (bignum i = 2;; i *= 2) {
		bignum res = i*b;
		if (res == a)
			return i;
		if (res > a)
			return Divide(a - j*b, b) + j;
		j = i;
	}
	assert(0);
}

bignum bignum::operator/(const bignum& src) const {
	if (src == 0)
		return bignum(0);
	bignum t = *this;
	bool judge = false;
	if (!t.negative_ && src.negative_)
		judge = true;
	if (t.negative_ && !src.negative_)
		judge = true;
	t = t.Abs();
	bignum s = src.Abs();
	if (t < s)
		return bignum(0);
	bignum ret = Divide(t, s);
	ret.negative_ = judge;
	return ret;
}

bignum& bignum::operator/=(const bignum& src) {
	*this = (*this) / src;
	return *this;
}


bignum bignum::operator%(const bignum& src) const {
	bignum ret = (*this) - ((*this) / src)*src;
	return ret;
}

bignum& bignum::operator%=(const bignum& src) {
	*this = (*this) % src;
	return *this;
}

/************************************************************************
大小比较
************************************************************************/
int bignum::Compare(const bignum& src) const {
	if (src.len_ == 1 && len_ == 1 && src.num_[0] == 0 && num_[0] == 0)
		return 0;
	int bigger = 1, smaller = -1;
	if (!negative_&&src.negative_)
		return bigger;
	if (negative_ && !src.negative_)
		return smaller;
	if (negative_ && src.negative_) {
		bigger = -1;
		smaller = 1;
	}
	if (len_ < src.len_)
		return smaller;
	if (len_ > src.len_)
		return bigger;
	for (int i = len_ - 1; i >= 0; --i) {
		if (num_[i] < src.num_[i])
			return smaller;
		if (num_[i] > src.num_[i])
			return bigger;
	}
	return 0;
}
bool bignum::operator==(const bignum& src) const { return (Compare(src) == 0); }
bool bignum::operator!=(const bignum& src) const { return (Compare(src) != 0); }
bool bignum::operator>(const bignum& src)  const { return (Compare(src) > 0); }
bool bignum::operator>=(const bignum& src) const { return (Compare(src) >= 0); }
bool bignum::operator<(const bignum& src)  const { return (Compare(src) < 0); }
bool bignum::operator<=(const bignum& src) const { return (Compare(src) <= 0); }

/************************************************************************
前后置++--重载
************************************************************************/
bignum& bignum::operator++() {
	*this = (*this) + 1;
	return *this;
}

bignum bignum::operator++(int) {
	bignum tmp = *this;
	++(*this);
	return tmp;
}

bignum& bignum::operator--() {
	*this = (*this) - 1;
	return *this;
}

bignum bignum::operator--(int) {
	bignum tmp = *this;
	--(*this);
	return tmp;
}