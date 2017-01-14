#include "stdafx.h"
#include "baseboardsn.h"

namespace CryptoLib {
STRX Info_BaseboardSN::GetSN() {
	STRX str = CmdPipe(_T("wmic baseboard get serialnumber"));
	str = str.Right((UINT)str.GetLength() - str.Find(L"\n") - 1);
	str.Replace(L"\r\n", L"");
	return str;
}
}