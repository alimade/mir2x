#pragma once
#include <type_traits>
#include <queue>
#include <atomic>
#include "uidf.hpp"
#include "actorpod.hpp"
#include "actormsgpack.hpp"
#include "statetrigger.hpp"
#include "serverluacoroutinerunner.hpp"

class ServerObject
{
    protected:
        class LuaThreadRunner: public ServerLuaCoroutineRunner
        {
            public:
                LuaThreadRunner(ServerObject *);

            public:
                ServerObject *getSO() const
                {
                    return m_actorPod->getSO();
                }
        };

    private:
        struct RegisterWaitActivated
        {
            ServerObject * const so;

            bool await_ready() const noexcept
            {
                return so->m_activated;
            }

            void await_suspend(std::coroutine_handle<> handle)
            {
                so->m_waitActivatedOps.push_back(handle);
            }

            void await_resume() const noexcept {}
        };

    private:
        std::vector<std::coroutine_handle<>> m_waitActivatedOps;

    private:
        friend class ActorPod;
        friend class ServerObjectLuaThreadRunner;

    private:
        const uint64_t m_UID;

    private:
        bool m_activated = false;

    protected:
        ActorPod *m_actorPod = nullptr;

    private:
        StateTrigger m_stateTrigger;

    public:
        ServerObject(uint64_t);

    public:
        virtual ~ServerObject();

    public:
        uint64_t UID() const
        {
            return m_UID;
        }

    public:
        uint64_t activate();

    protected:
        virtual void beforeActivate()
        {
        }

    protected:
        virtual corof::awaitable<> onActivate()
        {
            return {};
        }

    protected:
        void deactivate();

    protected:
        corof::awaitable<> waitActivated()
        {
            co_await RegisterWaitActivated
            {
                .so = this,
            };
        }

    public:
        bool hasActorPod() const
        {
            return m_actorPod && m_actorPod->UID();
        }

    public:
        virtual corof::awaitable<> onActorMsg(const ActorMsgPack &) = 0;

    public:
        virtual void afterActorMsg()
        {
            m_stateTrigger.run();
        }

    public:
        std::pair<uint64_t, uint64_t> createWaitToken(uint64_t tick, std::function<void(bool)> op)
        {
            return m_actorPod->createWaitToken(tick, std::move(op));
        }

    public:
        corof::awaitable<bool> asyncWait(uint64_t tick, std::pair<uint64_t, uint64_t> * tokenPtr = nullptr)
        {
            switch(const auto mpk = co_await m_actorPod->wait(tick, tokenPtr); mpk.type()){
                case AM_TIMEOUT:
                    {
                        co_return true;
                    }
                default:
                    {
                        co_return false;
                    }
            }
        }

    public:
        // func() -> coro: execute once
        //           void: execute once
        //           bool: execute once/loop
        template<typename Func> void defer(Func && func)
        {
            m_stateTrigger.install([func = std::forward<Func>(func)]() mutable -> bool
            {
                using ReturnType = decltype(func());

                if constexpr (std::is_same_v<ReturnType, bool>){
                    return func();
                }
                else if constexpr (std::is_void_v<ReturnType>){
                    func();
                }
                else if constexpr (std::is_same_v<ReturnType, corof::awaitable<>>){
                    func().resume();
                }
                else{
                    static_assert(false);
                }
                return true;
            });
        }

        template<typename Func> auto addDelay(uint64_t tick, Func && func) // func(bool timeout)
        {
            return m_actorPod->createWaitToken(tick, [func = std::forward<Func>(func)](const ActorMsgPack &mpk)
            {
                const bool timeout = (mpk.type() == AM_TIMEOUT);
                using ReturnType = decltype(func(timeout));

                if constexpr (std::is_void_v<ReturnType>){
                    func(timeout);
                }
                else if constexpr (std::is_same_v<ReturnType, corof::awaitable<>>){
                    func(timeout).resume();
                }
                else{
                    static_assert(false);
                }
            });
        }

        void cancelDelay(const std::pair<uint64_t, uint64_t> &token)
        {
            m_actorPod->cancelWaitToken(token);
        }

    protected:
        corof::awaitable<bool> queryDead(uint64_t);

    protected:
        void forwardNetPackage(uint64_t, uint8_t, const void *, size_t);

    protected:
        void forwardNetPackage(uint64_t uid, uint8_t type)
        {
            forwardNetPackage(uid, type, nullptr, 0);
        }

        void forwardNetPackage(uint64_t uid, uint8_t type, const std::string &buf)
        {
            forwardNetPackage(uid, type, buf.data(), buf.length());
        }

        void forwardNetPackage(uint64_t uid, uint8_t type, const std::string_view &buf)
        {
            forwardNetPackage(uid, type, buf.data(), buf.size());
        }

        template<typename T> void forwardNetPackage(uint64_t uid, uint8_t type, const T &t)
        {
            static_assert(std::is_trivially_copyable_v<T>);
            forwardNetPackage(uid, type, &t, sizeof(t));
        }
};
