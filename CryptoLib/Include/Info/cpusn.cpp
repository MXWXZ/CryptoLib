#include "stdafx.h"
#include "cpusn.h"

namespace CryptoLib {
STRX Info_CpuSN::GetSN() {
	STRX str = CmdPipe(_T("wmic cpu get processorid"));
	str = str.Right((UINT)str.GetLength() - str.Find(L"\n") - 1);
	str.Replace(L"\r\n", L"");
	return str;
}
}