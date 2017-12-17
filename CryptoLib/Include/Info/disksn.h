/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/17
 *
 * @Description:adapted from chengqiushu http://blog.sina.com.cn/s/blog_57dff12f0100d5sn.html
 */
#pragma once

namespace CryptoLib {
class Info_DiskSN {
public:
    static STRX GetSN();

protected:
    typedef struct _GETVERSIONOUTPARAMS {
        BYTE bVersion;
        BYTE bRevision;
        BYTE bReserved;
        BYTE bIDEDeviceMap;
        DWORD fCapabilities;
        DWORD dwReserved[4];
    }GETVERSIONOUTPARAMS, *PGETVERSIONOUTPARAMS, *LPGETVERSIONOUTPARAMS;
    typedef struct _IDEREGS {
        BYTE bFeaturesReg;
        BYTE bSectorCountReg;
        BYTE bSectorNumberReg;
        BYTE bCylLowReg;
        BYTE bCylHighReg;
        BYTE bDriveHeadReg;
        BYTE bCommandReg;
        BYTE bReserved;
    }IDEREGS, *PIDEREGS, *LPIDEREGS;
    typedef struct _SENDCMDINPARAMS {
        DWORD cBufferSize;
        IDEREGS irDriveRegs;
        BYTE bDriveNumber;
        BYTE bReserved[3];
        DWORD dwReserved[4];
        BYTE bBuffer[1];
    }SENDCMDINPARAMS, *PSENDCMDINPARAMS, *LPSENDCMDINPARAMS;
    typedef struct _DRIVERSTATUS {
        BYTE bDriverError;
        BYTE bIDEStatus;
        BYTE bReserved[2];
        DWORD dwReserved[2];
    }DRIVERSTATUS, *PDRIVERSTATUS, *LPDRIVERSTATUS;
    typedef struct _SENDCMDOUTPARAMS {
        DWORD cBufferSize;
        DRIVERSTATUS DriverStatus;
        BYTE bBuffer[1];
    }SENDCMDOUTPARAMS, *PSENDCMDOUTPARAMS, *LPSENDCMDOUTPARAMS;
};
}    // namespace CryptoLib
