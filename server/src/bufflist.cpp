#include <vector>
#include "buffactattackmodifier.hpp"
#include "bufflist.hpp"
#include "scopedalloc.hpp"

std::tuple<uint32_t, uint32_t> BuffList::rollAttackModifier()
{
    scoped_alloc::svobuf_wrapper<BaseBuffActAttackModifier *, 16> amodList;
    for(auto &p: m_activeBuffList){
        if(p.second){
            for(auto &actPtr: p.second->m_activeActList){
                if(actPtr->getBAR().isAttackModifier()){
                    amodList.c.push_back(dynamic_cast<BaseBuffActAttackModifier *>(actPtr.get()));
                }
            }
        }
    }

    uint32_t buffID = 0;
    uint32_t modifierID = 0;

    while(!(amodList.c.empty() || (buffID && modifierID))){
        const auto pick = mathf::rand<size_t>(0, amodList.c.size() - 1);
        std::swap(amodList.c.back(), amodList.c[pick]);

        if(!buffID){
            buffID = amodList.c.back()->rollBuff();
        }

        if(!modifierID){
            modifierID = amodList.c.back()->rollModifier();
        }
        amodList.c.pop_back();
    }
    return {buffID, modifierID};
}

#define _decl_func_has_buff_act(T, F, isT) std::vector<T *> F(const char8_t *name) \
{ \
    fflassert(str_haschar(name)); \
    std::vector<T *> result; \
 \
    for(auto &p: m_activeBuffList){ \
        if(p.second){ \
            for(auto &actPtr: p.second->m_activeActList){ \
                const auto &bar = DBCOM_BUFFACTRECORD(name); \
                fflassert(bar); \
 \
                if(bar.isT() && bar.isBuffAct(name)){ \
                    result.push_back(dynamic_cast<T *>(actPtr.get())); \
                } \
            } \
        } \
    } \
    return result; \
}

_decl_func_has_buff_act(BaseBuffActAura             , BuffList::hasAura             , isAura             )
_decl_func_has_buff_act(BaseBuffActController       , BuffList::hasController       , isController       )
_decl_func_has_buff_act(BaseBuffActTrigger          , BuffList::hasTrigger          , isTrigger          )
_decl_func_has_buff_act(BaseBuffActAttributeModifier, BuffList::hasAttributeModifier, isAttributeModifier)
_decl_func_has_buff_act(BaseBuffActAttackModifier   , BuffList::hasAttackModifier   , isAttackModifier   )
_decl_func_has_buff_act(BaseBuffActSpellModifier    , BuffList::hasSpellModifier    , isSpellModifier    )

#undef _decl_func_has_buff_act
