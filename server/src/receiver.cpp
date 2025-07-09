#include "uidf.hpp"
#include "receiver.hpp"
#include "actorpool.hpp"
#include "server.hpp"

extern ActorPool *g_actorPool;
extern Server *g_server;

Receiver::Receiver()
    : m_uid(uidf::buildReceiverUID())
{
    g_actorPool->attach(this);
}

Receiver::~Receiver()
{
    try{
        g_actorPool->detach(this);
    }
    catch(...){
        g_server->propagateException();
    }
}

void Receiver::pushMessage(ActorMsgPack mpk)
{
    {
        std::lock_guard<std::mutex> lockGuard(m_lock);
        m_messageList.push_back(std::move(mpk));
    }
    m_condition.notify_all();
}

size_t Receiver::wait(uint64_t timeout)
{
    std::unique_lock<std::mutex> lockGuard(m_lock);
    const auto fnPred = [this, origLen = m_messageList.size()]() -> bool
    {
        return m_messageList.size() > origLen;
    };

    if(timeout){
        m_condition.wait_for(lockGuard, std::chrono::milliseconds(timeout), fnPred);
    }
    else{
        m_condition.wait(lockGuard, fnPred);
    }
    return m_messageList.size();
}

std::vector<ActorMsgPack> Receiver::pop()
{
    std::vector<ActorMsgPack> popList;
    {
        std::lock_guard<std::mutex> lockGuard(m_lock);
        std::swap(popList, m_messageList);
    }
    return popList;
}
