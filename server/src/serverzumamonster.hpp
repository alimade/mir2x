#pragma once
#include "dbcomid.hpp"
#include "monster.hpp"

class ServerZumaMonster final: public Monster
{
    private:
        bool m_standMode = false;

    public:
        ServerZumaMonster(uint32_t monID, uint64_t argMapUID, int argX, int argY, int argDir, uint64_t masterUID)
            : Monster(monID, argMapUID, argX, argY, argDir, masterUID)
        {
            fflassert(isMonster(u8"祖玛雕像") || isMonster(u8"祖玛卫士"));
        }

    public:
        void setStandMode(bool standMode)
        {
            if(standMode != m_standMode){
                m_standMode = standMode;
                dispatchAction(ActionTransf
                {
                    .direction = Direction(),
                    .x = X(),
                    .y = Y(),
                    .extParam
                    {
                        .zumaMonster
                        {
                            .standModeReq = m_standMode,
                        },
                    },
                });
            }
        }

    protected:
        corof::awaitable<> runAICoro() override;

    protected:
        ActionNode makeActionStand() const override
        {
            return ActionStand
            {
                .direction = Direction(),
                .x = X(),
                .y = Y(),
                .extParam
                {
                    .zumaMonster
                    {
                        .standMode = m_standMode,
                    },
                },
            };
        }

    protected:
        corof::awaitable<> onAMMasterHitted(const ActorMsgPack &) override
        {
            setStandMode(true);
            return {};
        }

    protected:
        corof::awaitable<> onAMAttack(const ActorMsgPack &) override;

    protected:
        bool canMove(bool checkMoveLock) const override
        {
            return m_standMode && Monster::canMove(checkMoveLock);
        }
};
