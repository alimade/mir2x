#pragma once
#include <array>
#include <cstdint>
#include "actormsg.hpp"

struct ActorMonitor
{
    uint64_t uid = 0;

    uint32_t avgDelay = 0;
    uint32_t liveTick = 0;
    uint32_t busyTick = 0;

    uint32_t messageDone    = 0;
    uint32_t messagePending = 0;

    operator bool () const
    {
        return uid != 0;
    }
};

struct ActorThreadMonitor
{
    int      threadId   = -1;
    uint64_t actorCount =  0;
    uint32_t liveTick   =  0;
    uint32_t busyTick   =  0;
};

struct AMProcMonitor
{
    uint64_t procTick  = 0;
    uint32_t sendCount = 0;
    uint32_t recvCount = 0;
};

struct TriggerMonitor
{
    uint64_t procTick = 0;
};

struct ActorPodMonitor
{
    uint64_t uid = 0;
    TriggerMonitor triggerMonitor;
    std::array<AMProcMonitor, AM_END> amProcMonitorList;

    operator bool () const
    {
        return uid != 0;
    }
};
