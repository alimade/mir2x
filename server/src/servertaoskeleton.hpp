#pragma once
#include "dbcomid.hpp"
#include "fflerror.hpp"
#include "servertaosummon.hpp"

class ServerTaoSkeleton final: public ServerTaoSummon
{
    public:
        ServerTaoSkeleton(uint64_t argMapUID, int argX, int argY, uint64_t masterUID)
            : ServerTaoSummon(DBCOM_MONSTERID(u8"变异骷髅"), argMapUID, argX, argY, DIR_DOWNLEFT, masterUID)
        {}

    protected:
        DamageNode getAttackDamage(int dc, int) const override
        {
            fflassert(to_u32(dc) == DBCOM_MAGICID(u8"物理攻击"));
            return PlainPhyDamage
            {
                .damage = mathf::rand<int>(getMR().dc[0] + m_masterSC[0], getMR().dc[1] + m_masterSC[1]),
                .dcHit = getMR().dcHit,
            };
        }
};
