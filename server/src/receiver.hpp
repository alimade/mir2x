#pragma once
#include <vector>
#include <cstdint>
#include <condition_variable>
#include "actormsgpack.hpp"

class Receiver
{
    private:
        friend class ActorPool;

    private:
        uint64_t m_uid;

    private:
        std::mutex m_lock;
        std::condition_variable m_condition;

    private:
        std::vector<ActorMsgPack> m_messageList;

    public:
        Receiver();

    public:
        ~Receiver();

    public:
        uint64_t UID() const
        {
            return m_uid;
        }

    private:
        void pushMessage(ActorMsgPack);

    public:
        size_t wait(uint64_t = 0);

    public:
        std::vector<ActorMsgPack> pop();
};
