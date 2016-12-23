// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料

// TODO:  在此处引用程序需要的其他头文件

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4244)
#pragma warning(disable:4309)
#pragma warning(disable:4838)

#include "windows.h"
#include <cstdio>
#include "tchar.h"
#include <cstring>
#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "CryptoLib.h"