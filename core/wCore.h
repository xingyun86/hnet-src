
/**
 * Copyright (C) Anny Wang.
 * Copyright (C) Hupu, Inc.
 */

#ifndef _W_CORE_H_
#define _W_CORE_H_

#include "wLinux.h"

#include <cassert>
#include <cerrno>
#include <climits>
#include <ctime>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <cstdio>

namespace hnet {

using namespace std;

const bool      kLittleEndian = true;
const uint32_t 	kPageSize = 4096;

const u_char    kSetProcTitlePad = '\0';
const u_char    kLF = '\n';
const u_char    kCR = '\r';
const u_char*   kCRLF = "\r\n";

const uint32_t  kMaxHostNameLen = 255;
const uint8_t   kMaxIpLen = 16;
const uint32_t  kListenBacklog = 511;
const int32_t   kFDUnknown = -1;

const uint32_t  kKeepAliveTm = 3000;
const uint8_t   kKeepAliveCnt = 5;

const uint8_t	kHeartbeat = 5;

// 16m shm消息队列大小
const uint32_t  kMsgQueueLen = 16777216;

// 512k 客户端task消息缓冲大小
const uint32_t  kPackageSize = 524288;
const uint32_t  kMaxPackageSize = 524284;
const uint32_t  kMinPackageSize = 1;

const u_char*   kSoftwareName   = "hnet";
const u_char*   kSoftwareVer    = "0.0.1";

const u_char*   kDeamonUser = "root";
const u_char*   kDeamonGroup = "root";

const u_char*   kPidPath = "../log/hnet.pid";
const u_char*   kLockPath = "../log/hnet.lock";
const u_char*   kAcceptMutex = "../log/hnet.mutex.bin";

}   // namespace hnet

#endif