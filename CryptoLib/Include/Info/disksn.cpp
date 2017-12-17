/**
* Copyright (c) 2017-2050
* All rights reserved.
*
* @Author:MXWXZ
* @Date:2017/12/17
*
* @Description:adapted from ³ÂÇïÊ÷ http://blog.sina.com.cn/s/blog_57dff12f0100d5sn.html
*/
#include "stdafx.h"
#include "disksn.h"

namespace CryptoLib {
//////////////////////////////////////////////////////////////////////////
#define DFP_GET_VERSION   0x00074080
#define DFP_RECEIVE_DRIVE_DATA 0x0007c088
#define IDE_ATAPI_IDENTIFY  0xA1
#define IDE_ATA_IDENTIFY  0xEC
#define IDENTIFY_BUFFER_SIZE 512
//////////////////////////////////////////////////////////////////////////
STRX Info_DiskSN::GetSN() {
    BYTE IdOutCmd[530];
    HANDLE drive = CreateFile(_T("\\\\.\\PhysicalDrive0"), GENERIC_READ |
                              GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                              NULL, OPEN_EXISTING, 0, NULL);
    if (drive == INVALID_HANDLE_VALUE)
        return _T("");

    GETVERSIONOUTPARAMS VersionParams;
    DWORD cbBytesReturned = 0;
    memset((void*)&VersionParams, 0, sizeof(VersionParams));
    if (!DeviceIoControl(drive, DFP_GET_VERSION, NULL, 0, &VersionParams, sizeof(VersionParams), &cbBytesReturned, NULL))
        return _T("");
    if (VersionParams.bIDEDeviceMap <= 0)
        return _T("");
    BYTE bIDCmd = 0;
    SENDCMDINPARAMS scip;
    bIDCmd = (VersionParams.bIDEDeviceMap >> 0 & 0x10) ? IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;
    memset(&scip, 0, sizeof(scip));
    memset(IdOutCmd, 0, sizeof(IdOutCmd));
    scip.cBufferSize = IDENTIFY_BUFFER_SIZE;
    scip.irDriveRegs.bFeaturesReg = 0;
    scip.irDriveRegs.bSectorCountReg = 1;
    scip.irDriveRegs.bSectorNumberReg = 1;
    scip.irDriveRegs.bCylLowReg = 0;
    scip.irDriveRegs.bCylHighReg = 0;
    scip.irDriveRegs.bDriveHeadReg = 0xA0 | (((BYTE)drive & 1) << 4);
    scip.irDriveRegs.bCommandReg = bIDCmd;
    scip.bDriveNumber = (BYTE)drive;
    scip.cBufferSize = IDENTIFY_BUFFER_SIZE;
    if (!DeviceIoControl(drive, DFP_RECEIVE_DRIVE_DATA, &scip, sizeof(SENDCMDINPARAMS) - 1, (LPVOID)&IdOutCmd, sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1, &cbBytesReturned, NULL))
        return _T("");
    USHORT *pIdSector = (USHORT *)((PSENDCMDOUTPARAMS)IdOutCmd)->bBuffer;
    CloseHandle(drive);
    int nIndex = 0, nPosition = 0;
    char szSeq[256] = { 0 };
    for (nIndex = 13; nIndex < 20; nIndex++) {
        szSeq[nPosition++] = (unsigned char)(pIdSector[nIndex] / 256);
        szSeq[nPosition++] = (unsigned char)(pIdSector[nIndex] % 256);
    }
    STRX ret = szSeq;
    ret.TrimLeft();
    ret.TrimRight();
    return ret;
}
}    // namespace CryptoLib
