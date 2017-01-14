#include "stdafx.h"
#include "biossn.h"

namespace CryptoLib {
STRX Info_BiosSN::GetSN() {
	STRX str = CmdPipe(_T("wmic bios get serialnumber"));
	str = str.Right((UINT)str.GetLength() - str.Find(L"\n") - 1);
	str.Replace(L"\r\n", L"");
	return str;
}
}