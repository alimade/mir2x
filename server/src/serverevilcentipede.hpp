#pragma once
#include "dbcomid.hpp"
#include "monster.hpp"

class ServerEvilCentipede final: public Monster
{
    private:
        bool m_standMode = false;

    public:
        ServerEvilCentipede(uint64_t argMapUID, int argX, int argY)
            : Monster(DBCOM_MONSTERID(u8"触龙神"), argMapUID, argX, argY, DIR_BEGIN, 0)
        {}

    protected:
        corof::awaitable<> runAICoro() override;

    protected:
        ActionNode makeActionStand() const override
        {
            return ActionStand
            {
                .direction = DIR_BEGIN,
                .x = X(),
                .y = Y(),
                .extParam
                {
                    .evilCentipede
                    {
                        .standMode = m_standMode,
                    },
                },
            };
        }

        void setStandMode(bool standMode)
        {
            if(standMode != m_standMode){
                m_standMode = standMode;
                dispatchAction(ActionTransf
                {
                    .direction = DIR_BEGIN,
                    .x = X(),
                    .y = Y(),
                    .extParam
                    {
                        .evilCentipede
                        {
                            .standModeReq = standMode,
                        }
                    },
                });
            }
        }

    protected:
        bool struckDamage(uint64_t, const DamageNode &damage) override
        {
            if(m_standMode){
                if(damage){
                    updateHealth(-damage.damage);
                    if(m_sdHealth.hp <= 0){
                        goDie();
                    }
                    return true;
                }
            }
            return false;
        }
};
