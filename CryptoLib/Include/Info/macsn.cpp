/*************************************************************************
改编自liruda的博客：http://blog.csdn.net/liruda/article/details/2254378
*************************************************************************/
#include "stdafx.h"
#include "macsn.h"
#include <nb30.h>
#pragma comment(lib, "Netapi32.lib")

namespace CryptoLib {
STRX Info_MacSN::GetAdapterInfo(int num) {
	NCB Ncb;
	memset(&Ncb, 0, sizeof(Ncb));
	Ncb.ncb_command = NCBRESET;
	Ncb.ncb_lana_num = num;
	if (Netbios(&Ncb) != NRC_GOODRET)
		return STRX(_T(""));
	memset(&Ncb, sizeof(Ncb), 0);
	Ncb.ncb_command = NCBASTAT;
	Ncb.ncb_lana_num = num;
	strcpy((char *)Ncb.ncb_callname, "*");
	struct ASTAT {
		ADAPTER_STATUS adapt;
		NAME_BUFFER nameBuff[30];
	}adapter;
	memset(&adapter, sizeof(adapter), 0);
	Ncb.ncb_buffer = (unsigned char *)&adapter;
	Ncb.ncb_length = sizeof(adapter);
	if (Netbios(&Ncb) != 0)
		return STRX(_T(""));
	char acMAC[32];
	sprintf(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
			int(adapter.adapt.adapter_address[0]),
			int(adapter.adapt.adapter_address[1]),
			int(adapter.adapt.adapter_address[2]),
			int(adapter.adapt.adapter_address[3]),
			int(adapter.adapt.adapter_address[4]),
			int(adapter.adapt.adapter_address[5]));
	return STRX(acMAC);
}

STRX Info_MacSN::GetSN() {
	LANA_ENUM adapterList;
	NCB Ncb;
	memset(&Ncb, 0, sizeof(NCB));
	Ncb.ncb_command = NCBENUM;
	Ncb.ncb_buffer = (unsigned char *)&adapterList;
	Ncb.ncb_length = sizeof(adapterList);
	Netbios(&Ncb);
	return GetAdapterInfo(adapterList.lana[0]);
}
}