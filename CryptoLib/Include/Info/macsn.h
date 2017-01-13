/*************************************************************************
改编自liruda的博客：http://blog.csdn.net/liruda/article/details/2254378
*************************************************************************/
#pragma once

namespace CryptoLib {
class Info_MacSN {
public:
	static STRX GetSN();

protected:
	static STRX GetAdapterInfo(int num);
};
}