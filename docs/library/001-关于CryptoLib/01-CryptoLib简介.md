# CryptoLib简介
![MIT License](https://img.shields.io/badge/License-MIT-red.svg)
![C++](https://img.shields.io/badge/Language-C%2B%2B-brightgreen.svg)
![Version](https://img.shields.io/badge/Version-1.0-blue.svg)

CryptoLib是一个轻量级C++密码类库，完全编译只需要几十KB！包括常用哈希、加解密、硬件信息获取、拓展类等模块，基于MIT协议，可以用于商业软件。

# 支持的模块
常用哈希：

| 名称   | 长度  | 类名        |
| :----: | :---: | :---------: |
| MD5    | 32    | Hash_MD5    |
| SHA1   | 40    | Hash_SHA1   |
| SHA256 | 64    | Hash_SHA256 |
| SHA512 | 128   | Hash_SHA512 |
| CRC32* | 8     | Hash_CRC32  |

常用加解密：

| 名称       | 类名             |
| :--------: | :--------------: |
| Base64     | Encode_Base64    |
| UrlEncode* | Encode_UrlEncode |

硬件信息：

| 名称       | 类名             |
| :--------: | :--------------: |
| 硬盘序列号 | Info_DiskSN      |
| MAC地址    | Info_MacSN       |
| CPU序列号  | Info_CpuSN       |
| 主板序列号 | Info_BaseboardSN |
| BIOS序列号 | Info_BiosSN      |

拓展类：
字符串类 大数类*

*注：
- 字符串参数默认会转换为UTF-8进行哈希或加密并转换成GBK编码返回，如参数需要使用GBK编码，请在`CryptoLib.h`中将`CRYPTOLIB_ENABLE_UTF8ONLY`的值改为0
- CRC32使用的是标准Poly：0xEDB88320L
- UrlEncode遵循RFC3986标准
- 考虑到效率问题，默认数字最大长度为256，如需更改请修改`bignum.h`中的`kMaxNumLength`常量设置。


# 简单地使用
    HashClass::Generate(str)                        //计算str哈希值，默认返回小写
    HashClass::GenerateFile(_T("File Name")));      //计算文件哈希，默认返回小写
    EncodeClass::Encode(str);                       //加密
    EncodeClass::Decode(str);                       //解密
    InfoClass::GetSN();                             //取得序列号

# 鸣谢
在开发过程中，少不了下面的开源代码的支持：

ulwanski：https://github.com/ulwanski/md5

ulwanski：https://github.com/ulwanski/sha512

vog：https://github.com/vog/sha1

黑猫崽儿：http://blog.csdn.net/c_duoduo/article/details/43889759

陈秋树：http://blog.sina.com.cn/s/blog_57dff12f0100d5sn.html

liruda：http://blog.csdn.net/liruda/article/details/2254378
