#pragma once
#include <map>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>
#include "pathf.hpp"
#include "sgf.hpp"
#include "scopedalloc.hpp"
#include "charobject.hpp"
#include "damagenode.hpp"
#include "actionnode.hpp"
#include "protocoldef.hpp"
#include "buffacttrigger.hpp"
#include "buff.hpp"
#include "bufflist.hpp"

class BattleObject: public CharObject
{
    public:
        friend class CharObject;
        friend class BaseBuff;
        friend class BaseBuffAct;
        friend class BaseBuffActAura;
        friend class BaseBuffActTrigger;
        friend class BaseBuffActAttributeModifier;
        template<uint32_t> friend class BuffActTrigger;

    protected:
        class LuaThreadRunner: public CharObject::LuaThreadRunner
        {
            public:
                LuaThreadRunner(BattleObject *);

            public:
                BattleObject *getBO() const
                {
                    return static_cast<BattleObject *>(getCO());
                }
        };

    protected:
        class BOPathFinder final: public pathf::AStarPathFinder
        {
            private:
                friend class BattleObject;

            private:
                const BattleObject *m_BO;

            private:
                const int m_checkCO;

            private:
                mutable std::map<uint32_t, int> m_cache;

            public:
                /* ctor */  BOPathFinder(const BattleObject *, int);
                /* dtor */ ~BOPathFinder() = default;

            private:
                int getGrid(int, int) const;
        };

    protected:
        enum SpeedType: int
        {
            SPEED_NONE = 0,
            SPEED_MOVE,
            SPEED_ATTACK,
        };

    protected:
        struct Offender
        {
            uint64_t uid = 0;
            uint64_t damage = 0;
            uint64_t activeTime = 0;
        };

    protected:
        SDHealth m_sdHealth;
        SDBuffedAbility m_sdBuffedAbility;

    protected:
        BuffList m_buffList;

    protected:
        bool m_moveLock = false;
        bool m_attackLock = false;

    protected:
        int m_lastAction = ACTION_NONE;
        std::array<uint32_t, ACTION_END> m_lastActionTime;

    protected:
        std::vector<Offender> m_offenderList;

    protected:
        TimedState<bool> m_dead;

    public:
        BattleObject(
                uint64_t, // uid
                uint64_t, // server map uid
                int,      // map x
                int,      // map y
                int);     // direction

    public:
        ~BattleObject() = default;

    public:
        void beforeActivate() override;

    protected:
        virtual void reportCO(uint64_t) = 0;

    protected:
        void dispatchHealth();
        void dispatchHealth(uint64_t);
        void dispatchAttackDamage(uint64_t, int, int);

    protected:
        virtual std::optional<std::tuple<int, int, int>> oneStepReach(int, int) const;

    protected:
        virtual int Speed(int) const;

    protected:
        corof::awaitable<bool> requestJump(
                int,            // x
                int,            // y
                int);           // direction

    protected:
        corof::awaitable<bool> requestMove(
                int,            // x
                int,            // y
                int,            // speed
                bool,           // allowHalfMove
                bool);          // removeMonster: force monster on (x, y) go to somewhere else to make room

    protected:
        corof::awaitable<bool> requestSpaceMove(
                int,            // x
                int,            // y
                bool);          // strictMove

    protected:
        corof::awaitable<bool> requestMapSwitch(
                uint64_t,       // mapUID
                int,            // x
                int,            // y
                bool);          // strictMove

    protected:
        virtual bool canAct()        const;
        virtual bool canMove(bool)   const;
        virtual bool canAttack(bool) const;

    protected:
        void setLastAction(int);

    protected:
        virtual bool dcValid(int, bool) = 0;

    protected:
        virtual DamageNode getAttackDamage(int, int) const = 0;

    protected:
        virtual bool struckDamage(uint64_t, const DamageNode &) = 0;

    protected:
        corof::awaitable<uint64_t> addMonster(uint32_t, int, int, bool);

    protected:
        virtual int maxStep() const
        {
            return 1;
        }

        virtual int moveSpeed()
        {
            return SYS_DEFSPEED;
        }

    protected:
        // estimate how many hops we need
        // this function checks map but can't check CO
        // if we found one-hop distance we need send move request to servermap
        // return:
        //          -1: invalid
        //           0: no move needed
        //           1: one-hop can reach
        //           2: more than one-hop can reach
        int estimateHop(int, int);

    protected:
        int attackSpeed() const
        {
            return SYS_DEFSPEED;
        }

        int MagicSpeed() const
        {
            return SYS_DEFSPEED;
        }

    protected:
        std::array <pathf::PathNode, 3>   getChaseGrid(int, int, int) const;
        std::vector<pathf::PathNode> getValidChaseGrid(int, int, int) const;

    protected:
        void getValidChaseGrid(int, int, int, scoped_alloc::svobuf_wrapper<pathf::PathNode, 3> &) const;

    protected:
        int checkPathGrid(int, int) const;
        std::optional<double> oneStepCost(const BattleObject::BOPathFinder *, int, int, int, int, int, int) const;

    protected:
        virtual corof::awaitable<int> checkFriend(uint64_t) = 0;

    protected:
        corof::awaitable<std::optional<SDHealth>> queryHealth(uint64_t);

    protected:
        corof::awaitable<uint64_t> queryFinalMaster(uint64_t);

    protected:
        bool isOffender(uint64_t);

    protected:
        template<typename... Args> void dispatchInViewCONetPackage(uint8_t type, Args && ... args)
        {
            for(const auto &[uid, coLoc]: m_inViewCOList){
                if(uidf::getUIDType(coLoc.uid) == UID_PLY){
                    forwardNetPackage(coLoc.uid, type, std::forward<Args>(args)...);
                }
            }
        }

    protected:
        void removeBuff(uint64_t, bool);
        void removeFromBuff(uint64_t, uint64_t, bool);

    protected:
        BaseBuff *addBuff(uint64_t, uint64_t, uint32_t);

    protected:
        void sendBuff(uint64_t, uint64_t, uint32_t);

    protected:
        void dispatchBuffIDList();

    protected:
        virtual bool updateHealth(
                int = 0,    // hp
                int = 0,    // mp
                int = 0,    // maxHP
                int = 0);   // maxMP

    protected:
        virtual std::pair<int, SDTaggedValMap &> updateBuffedAbility(
                uint32_t,   // buffActID
                int,        // percentage
                int);       // value
    public:
        const auto &getHealth() const
        {
            return m_sdHealth;
        }

    protected:
        void notifyDead(uint64_t);
};
