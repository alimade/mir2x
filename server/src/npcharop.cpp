#include "mathf.hpp"
#include "npchar.hpp"
#include "dbcomid.hpp"
#include "servermsg.hpp"
#include "serdesmsg.hpp"
#include "actormsgpack.hpp"

corof::awaitable<> NPChar::on_AM_ATTACK(const ActorMsgPack &)
{
    return {};
}

corof::awaitable<> NPChar::on_AM_ACTION(const ActorMsgPack &mpk)
{
    const auto amA = mpk.conv<AMAction>();
    switch(uidf::getUIDType(amA.UID)){
        case UID_PLY:
            {
                m_luaRunner->spawn(amA.UID, str_printf("_RSVD_NAME_trigger(SYS_ON_APPEAR, %llu)", to_llu(amA.UID)));
                dispatchAction(amA.UID, makeActionStand());
                return {};
            }
        default:
            {
                return {};
            }
    }
}

corof::awaitable<> NPChar::on_AM_NPCEVENT(const ActorMsgPack &mpk)
{
    fflassert(mpk.from());
    auto sdNPCE = mpk.deserialize<SDNPCEvent>();

    if(!sdNPCE.event.empty() && sdNPCE.event != SYS_ENTER){
        sdNPCE.event = AESHelper(this, mpk.from()).decode(sdNPCE.event.c_str());
        // m_xmlLayoutSeqIDList.erase(mpk.from());
    }

    // when CO initially sends a message to NPC, we assume its UID is the callStackUID
    // when NPC querys CO attributes the response should be handled in actor response handler, not here

    if(false
            || sdNPCE.event == SYS_EXIT
            || sdNPCE.event == SYS_NPCERROR){
        m_luaRunner->close(mpk.from());
        return {};
    }

    // can be SYS_ENTER or scritp event
    // script event defines like text button pressed etc

    if(sdNPCE.mapUID != mapUID() || mathf::LDistance2(sdNPCE.x, sdNPCE.y, X(), Y()) >= SYS_MAXNPCDISTANCE * SYS_MAXNPCDISTANCE){
        AMNPCError amNPCE;
        std::memset(&amNPCE, 0, sizeof(amNPCE));

        amNPCE.errorID = NPCE_TOOFAR;
        m_actorPod->post(mpk.from(), {AM_NPCERROR, amNPCE});

        m_luaRunner->close(mpk.from());
        return {};
    }

    // last call stack may have not been done yet
    // but player initializes new call stack, have to abandon last call stack and start a new one

    for(const auto seqID: m_luaRunner->getSeqID(mpk.from())){
        m_luaRunner->close(mpk.from(), seqID);
    }

    m_luaRunner->spawn(mpk.from(), str_printf("return _RSVD_NAME_npc_main(%llu, %s, %s, %s)",
                to_llu(mpk.from()),

                sdNPCE.path .empty() ? "nil" : luaf::quotedLuaString(sdNPCE.path ).c_str(),
                sdNPCE.event.empty() ? "nil" : luaf::quotedLuaString(sdNPCE.event).c_str(),

                sdNPCE.value.has_value() ? luaf::quotedLuaString(sdNPCE.value.value()).c_str() : "nil"));
    return {};
}

corof::awaitable<> NPChar::on_AM_NOTIFYNEWCO(const ActorMsgPack &mpk)
{
    if(uidf::getUIDType(mpk.from()) == UID_PLY){
        dispatchAction(mpk.from(), makeActionStand());
    }
    return {};
}

corof::awaitable<> NPChar::on_AM_QUERYCORECORD(const ActorMsgPack &mpk)
{
    const auto fromUID = mpk.conv<AMQueryCORecord>().UID;
    if(uidf::getUIDType(fromUID) != UID_PLY){
        throw fflerror("NPC get AMQueryCORecord from %s", uidf::getUIDTypeCStr(fromUID));
    }
    dispatchAction(fromUID, makeActionStand());
    return {};
}

corof::awaitable<> NPChar::on_AM_QUERYLOCATION(const ActorMsgPack &mpk)
{
    AMLocation amL;
    std::memset(&amL, 0, sizeof(amL));

    amL.UID       = UID();
    amL.mapUID    = mapUID();
    amL.X         = X();
    amL.Y         = Y();
    amL.Direction = Direction();

    m_actorPod->post(mpk.fromAddr(), {AM_LOCATION, amL});
    return {};
}

corof::awaitable<> NPChar::on_AM_QUERYSELLITEMLIST(const ActorMsgPack &mpk)
{
    // 
    // query all selling items for one specified itemID

    const auto amQSIL = mpk.conv<AMQuerySellItemList>();
    SDSellItemList sdSIL;
    sdSIL.npcUID = UID();
    if(DBCOM_ITEMRECORD(amQSIL.itemID).packable()){
        sdSIL.list.push_back(SDSellItem
        {
            .item     = m_sellItemList.at(amQSIL.itemID).at(0).item,
            .costList = m_sellItemList.at(amQSIL.itemID).at(0).costList,
        });
    }
    else{
        if(auto p = m_sellItemList.find(amQSIL.itemID); p != m_sellItemList.end()){
            for(const auto &[seqID, sellItem]: p->second){
                sdSIL.list.push_back(SDSellItem
                {
                    .item = sellItem.item,
                    .costList = sellItem.costList,
                });
            }
        }
    }
    forwardNetPackage(mpk.from(), SM_SELLITEMLIST, cerealf::serialize(sdSIL, true));
    return {};
}

corof::awaitable<> NPChar::on_AM_REMOTECALL(const ActorMsgPack &mpk)
{
    auto sdRC = mpk.deserialize<SDRemoteCall>();
    m_luaRunner->spawn(mpk.from(), mpk.fromAddr(), std::move(sdRC.code), std::move(sdRC.args));
    return {};
}

corof::awaitable<> NPChar::on_AM_BADACTORPOD(const ActorMsgPack &mpk)
{
    const auto amBAP = mpk.conv<AMBadActorPod>();
    m_luaRunner->close(amBAP.UID);
    return {};
}

corof::awaitable<> NPChar::on_AM_BUY(const ActorMsgPack &mpk)
{
    const auto fnSendBuyError = [&mpk, this](int buyError)
    {
        AMBuyError amBE;
        std::memset(&amBE, 0, sizeof(amBE));
        amBE.error = buyError;
        m_actorPod->post(mpk.fromAddr(), {AM_BUYERROR, amBE});
    };

    const auto amB = mpk.conv<AMBuy>();
    const auto &ir = DBCOM_ITEMRECORD(amB.itemID);
    if(!ir){
        throw fflerror("invalid itemID = %llu", to_llu(amB.itemID));
    }

    if(!ir.packable() && amB.count > 1){
        throw fflerror("buying multiple unpackable items");
    }

    auto p = m_sellItemList.find(amB.itemID);
    if(p == m_sellItemList.end()){
        fnSendBuyError(BUYERR_BADITEM);
        co_return;
    }

    auto q = p->second.find(ir.packable() ? 0 : amB.seqID);
    if(q == p->second.end()){
        fnSendBuyError(BUYERR_SOLDOUT);
        co_return;
    }

    if(q->second.locked){
        fnSendBuyError(BUYERR_LOCKED);
        co_return;
    }

    SDBuyCost sdBC;
    sdBC.item = q->second.item;
    sdBC.item.count = amB.count;
    sdBC.costList = q->second.costList; // TODO: for packable cost = itemCost x count

    if(!ir.packable()){
        q->second.locked = true;
    }

    const auto rmpk = co_await m_actorPod->send(mpk.fromAddr(), {AM_BUYCOST, cerealf::serialize(sdBC)});
    {
        const auto &ir = DBCOM_ITEMRECORD(amB.itemID);
        if(!ir){
            throw fflerror("invalid itemID = %llu", to_llu(amB.itemID));
        }

        auto p = m_sellItemList.find(amB.itemID);
        if(p == m_sellItemList.end()){
            throw fflerror("no item selling: itemID = %llu", to_llu(amB.itemID));
        }

        auto q = p->second.find(ir.packable() ? 0 : amB.seqID);
        if(q == p->second.end()){
            throw fflerror("no item selling: itemID = %llu, seqID = %llu", to_llu(amB.itemID), to_llu(amB.seqID));
        }

        if(!ir.packable()){
            if(!q->second.locked){
                throw fflerror("item lock released before get response");
            }
            q->second.locked = false;
        }

        switch(rmpk.type()){
            case AM_OK:
                {
                    if(!ir.packable()){
                        p->second.erase(q);
                    }
                    co_return;
                }
            case AM_ERROR:
                {
                     co_return;
                }
            default:
                {
                    co_return;
                }
        }
    }
}
