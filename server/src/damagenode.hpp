#pragma once
#include <array>
#include <utility>
#include <cstdint>
#include <cstdlib>
#include <cinttypes>
#include "protocoldef.hpp"

struct DamageNode
{
    int magicID;
    int damage;

    int dcHit;
    int mcHit;
    int modifierID; // 穿刺 吸血 etc

    operator bool () const
    {
        return magicID != 0;
    }
};
static_assert(std::is_trivially_copyable_v<DamageNode>);

struct PlainPhyDamage
{
    int damage = 0;
    int dcHit = 0;
    int modifierID = 0;
    operator DamageNode() const;
};

struct MagicDamage
{
    int magicID = 0;
    int damage = 0;
    int mcHit = 0;
    int modifierID = 0;
    operator DamageNode() const;
};
