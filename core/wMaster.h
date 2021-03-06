
/**
 * Copyright (C) Anny Wang.
 * Copyright (C) Hupu, Inc.
 */

#ifndef _W_MASTER_H_
#define _W_MASTER_H_

#include <map>
#include <vector>
#include <algorithm>
#include "wCore.h"
#include "wNoncopyable.h"
#include "wEnv.h"

namespace hnet {

const char  kMasterTitle[] = " - master process";

class wServer;
class wWorker;

class wMaster : private wNoncopyable {
public:
    wMaster(const std::string& title, wServer* server);
    virtual ~wMaster();

    // 准备启动
    int PrepareStart();
    
    // 单进程模式启动
    int SingleStart();

    // M-W模式启动(master-worker)
    int MasterStart();

    // 发送命令行信号
    int SignalProcess(const std::string& signal);

    // 修改pid文件名（默认hnet.pid）
    // 修改启动worker个数（默认cpu个数）
    // 修改自定义信号处理（默认定义在wSignal.cpp文件中）
    virtual int PrepareRun();

    // 单进程为客户端事件循环体
    // M-W模式中为系统信号循环体
    virtual int Run();
    
    virtual int NewWorker(uint32_t slot, wWorker** ptr);
    virtual int HandleSignal();
    
    virtual int Reload();

    // master主进程退出函数
    virtual void ProcessExit();

    inline uint32_t& WorkerNum() { return mWorkerNum;}
    inline pid_t& Pid() { return mPid;}
    inline std::string& Title() { return mTitle;}

    template<typename T = wServer*>
    inline T Server() { return reinterpret_cast<T>(mServer);}

    template<typename T = wWorker*>
    inline T Worker(uint32_t slot = kMaxProcess) {
    	if (slot >= 0 && slot < kMaxProcess && mWorkerPool[slot]) {
    		return reinterpret_cast<T>(mWorkerPool[slot]);
    	} else {
    		return reinterpret_cast<T>(mWorker);
    	}
    }

protected:
    friend class wWorker;
    friend class wServer;

    // 启动n个worker进程
    int WorkerStart(uint32_t n, int32_t type = kProcessRespawn);
    // 创建一个worker进程
    int SpawnWorker(int64_t type);
    
    // 注册信号回调
    // 可覆盖全局变量hnet_signals，实现自定义信号处理
    int InitSignals();

    // 如果有worker异常退出，则重启
    // 如果所有的worker都退出了，则mLive = 0
    int ReapChildren();

    int CreatePidFile();
    int DeletePidFile();
    
    // 给所有worker进程发送信号
    void SignalWorker(int signo);

    // 回收退出进程状态（waitpid以防僵尸进程）
    void WorkerExitStat();

    // master进程id
    pid_t mPid;
    uint8_t mNcpu;
    std::string mTitle;
    std::string mPidPath;

    // 进程表
    uint32_t mSlot;
    uint32_t mWorkerNum;
    wWorker* mWorkerPool[kMaxProcess];

    int32_t mDelay;
    int32_t mSigio;
    int32_t mLive;

    wServer* mServer;
    wWorker* mWorker;	// 当前worker进程
    wEnv* mEnv;
};

}	// namespace hnet

#endif
