#include "uidf.hpp"
#include "mathf.hpp"
#include "dbcomid.hpp"
#include "fflerror.hpp"
#include "friendtype.hpp"
#include "buffactaura.hpp"
#include "battleobject.hpp"

BaseBuffActAura::BaseBuffActAura(BaseBuff *argBuff, size_t argBuffActOff)
    : BaseBuffAct(argBuff, argBuffActOff)
    , m_auraBuffID([this]()
      {
          fflassert(getBAR().isAura());
          const auto id = DBCOM_BUFFID(getBAR().aura.buff);
          const auto &br = DBCOM_BUFFRECORD(id);

          fflassert(id);
          fflassert(br);
          return id;
      }())
{}

corof::awaitable<> BaseBuffActAura::dispatch()
{
    for(const auto uid: getBuff()->getBO()->getInViewUIDList()){
        switch(uidf::getUIDType(uid)){
            case UID_PLY:
            case UID_MON:
                {
                    co_await transmit(uid);
                    break;
                }
            default:
                {
                    break;
                }
        }
    }
}

corof::awaitable<> BaseBuffActAura::transmit(uint64_t targetUID)
{
    fflassert(targetUID);
    fflassert(targetUID != getBuff()->getBO()->UID());
    switch(uidf::getUIDType(targetUID)){
        case UID_PLY:
        case UID_MON:
            {
                if(const auto coLocOpt = co_await getBuff()->getBO()->getCOLocation(targetUID); coLocOpt.has_value()){
                    const auto &baref = getBAREF();
                    fflassert(baref);

                    if(getBuff()->getBO()->mapUID() != coLocOpt.value().mapUID){
                        co_return;
                    }

                    if(mathf::LDistance2<int>(getBuff()->getBO()->X(), getBuff()->getBO()->Y(), coLocOpt.value().x, coLocOpt.value().y) > baref.aura.radius * baref.aura.radius){
                        co_return;
                    }

                    switch(const auto friendType = co_await getBuff()->getBO()->checkFriend(targetUID)){
                        case FT_FRIEND:
                            {
                                if(getBR().favor >= 0){
                                    getBuff()->getBO()->sendBuff(targetUID, getBuff()->buffSeq(), getAuraBuffID());
                                }
                                break;
                            }
                        case FT_ENEMY:
                            {
                                if(getBR().favor <= 0){
                                    getBuff()->getBO()->sendBuff(targetUID, getBuff()->buffSeq(), getAuraBuffID());
                                }
                                break;
                            }
                        case FT_NEUTRAL:
                            {
                                getBuff()->getBO()->sendBuff(targetUID, getBuff()->buffSeq(), getAuraBuffID());
                                break;
                            }
                        default:
                            {
                                throw fflvalue(friendType);
                            }
                    }
                }
                break;
            }
        default:
            {
                break;
            }
    }
}

BaseBuffActAura *BaseBuffActAura::createAura(BaseBuff *argBuff, size_t argBuffActOff)
{
    return new BaseBuffActAura(argBuff, argBuffActOff);
}
