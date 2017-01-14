#include "stdafx.h"
#include "snbase.h"

namespace CryptoLib {
STRX CryptoLib::Info_SNBase::CmdPipe(STRX command) {
	LPTSTR cmd = new TCHAR[command.GetWDataLength()];
	command.GetData(cmd);
	SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
	HANDLE hRead, hWrite;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
		return STRX("");
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	GetStartupInfo(&si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	PROCESS_INFORMATION pi;
	if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
		return STRX("");
	CloseHandle(hWrite);
	string str;
	char buff[1024] = { 0 };
	DWORD dwRead = 0;
	while (ReadFile(hRead, buff, 1024, &dwRead, NULL))
		str.append(buff, dwRead);
	CloseHandle(hRead);
	delete[] cmd;
	cmd = NULL;
	return STRX(str);
}
}