#pragma once
#include <cmath>
#include <tuple>
#include <vector>
#include <memory>
#include <cstdint>
#include "corof.hpp"
#include "uidf.hpp"
#include "buffrecord.hpp"
#include "dbcomid.hpp"

class BattleObject;
class BaseBuffActAura;
class BaseBuffAct;
class BuffList;

// buff is an embeded class of BattleObject
// it always has a bound BO pointer and overlives buff
// it should be possible to put into BattleObject as an nested class but we split it out

class BaseBuff
{
    private:
        friend class BuffList;

    protected:
        BattleObject * const m_bo;

    protected:
        const uint64_t m_fromUID;
        const uint64_t m_fromBuffSeq;

    protected:
        const uint32_t m_id;
        const uint32_t m_seqID;

    protected:
        std::vector<std::unique_ptr<BaseBuffAct>>   m_deadActList;
        std::vector<std::unique_ptr<BaseBuffAct>> m_activeActList;

    public:
        BaseBuff(BattleObject *, uint64_t, uint64_t, uint32_t, uint32_t);

    public:
        virtual ~BaseBuff() = default;

    public:
        uint32_t id() const
        {
            return m_id;
        }

        uint32_t seqID() const
        {
            return m_seqID;
        }

        uint64_t buffSeq() const
        {
            return (to_u64(m_id) << 32) | m_seqID;
        }

        uint64_t fromUID() const
        {
            return m_fromUID;
        }

        uint32_t fromBuff() const
        {
            return to_u32(m_fromBuffSeq >> 32);
        }

        uint64_t fromBuffSeq() const
        {
            return m_fromBuffSeq;
        }

    public:
        BattleObject * getBO()
        {
            return m_bo;
        }

        const BattleObject * getBO() const
        {
            return m_bo;
        }

    public:
        virtual bool done() const
        {
            for(auto &p: m_activeActList){
                if(p){
                    return false;
                }
            }
            return true;
        }

    public:
        virtual corof::awaitable<> runOnTrigger(int);
        virtual corof::awaitable<> runOnDone();

    public:
        virtual corof::awaitable<> runOnBOMove();

    public:
        std::vector<BaseBuffActAura *> getAuraList();

    public:
        corof::awaitable<> sendAura(uint64_t);

    public:
        corof::awaitable<> dispatchAura();

    public:
        void updateAura(uint64_t);

    public:
        const BuffRecord &getBR() const
        {
            return DBCOM_BUFFRECORD(id());
        }

    public:
        const BuffRecord &fromBR() const
        {
            return DBCOM_BUFFRECORD(fromBuff());
        }

    public:
        const BuffRecord::BuffActRecordRef *fromAuraBAREF() const
        {
            for(const auto &baref: fromBR().actList){
                const auto &bar = DBCOM_BUFFACTRECORD(baref.name);
                fflassert(bar, baref.name);

                if(bar.isAura() && std::u8string_view(bar.aura.buff) == getBR().name){
                    return &baref;
                }
            }
            return nullptr;
        }

    public:
        BaseBuffAct *hasBuffAct(size_t) const;
        bool      removeBuffAct(size_t);
};
