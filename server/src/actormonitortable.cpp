#include <FL/Fl.H>
#include <algorithm>
#include <FL/fl_draw.H>

#include "strf.hpp"
#include "uidf.hpp"
#include "totype.hpp"
#include "actorpool.hpp"
#include "podmonitorwindow.hpp"
#include "actormonitortable.hpp"

extern ActorPool *g_actorPool;
extern PodMonitorWindow *g_podMonitorWindow;

std::string ActorMonitorTable::getGridData(int nRow, int nCol) const
{
    if(!(checkRow(nRow) && checkCol(nCol))){
        return "";
    }

    const auto fnAdjustLength = [](std::string szString, size_t nNewLength) -> std::string
    {
        if(nNewLength <= szString.length()){
            return szString;
        }
        return std::string(nNewLength - szString.size(), ' ') + szString;
    };

    const auto &monitor = m_actorMonitorList.at(nRow);
    switch(nCol){
        case 0: // UID
            {
                return str_printf("%016llx", to_llu(monitor.uid));
            }
        case 1: // TYPE
            {
                return uidf::getUIDTypeCStr(monitor.uid);
            }
        case 2: // GROUP
            {
                return std::to_string(g_actorPool->getBucketID(monitor.uid));
            }
        case 3: // LIVE
            {
                return getTimeString(monitor.liveTick);
            }
        case 4: // BUSY
            {
                return getTimeString(monitor.busyTick);
            }
        case 5: // MSG_DONE
            {
                return fnAdjustLength(std::to_string(monitor.messageDone), digitLength(m_monitorDrawHelper.maxMessageDone));
            }
        case 6: // MSG_PENDING
            {
                return fnAdjustLength(std::to_string(monitor.messagePending), digitLength(m_monitorDrawHelper.maxMessagePending));
            }
        case 7: // MSG_AVGDLY
            {
                return fnAdjustLength(std::to_string(monitor.avgDelay), digitLength(m_monitorDrawHelper.maxAvgDelay));
            }
        default:
            {
                return "???";
            }
    }
}

ActorMonitorTable::ActorMonitorDrawHelper ActorMonitorTable::getActorMonitorDrawHelper(const std::vector<ActorMonitor> &monitorList)
{
    ActorMonitorTable::ActorMonitorDrawHelper result;
    for(const auto &monitor: monitorList){
        result.uidTypeCountList.at(uidf::getUIDType(monitor.uid))++;
        result.maxAvgDelay       = (std::max<uint32_t>)(result.maxAvgDelay, monitor.avgDelay);
        result.maxMessageDone    = (std::max<uint32_t>)(result.maxMessageDone, monitor.messageDone);
        result.maxMessagePending = (std::max<uint32_t>)(result.maxMessagePending, monitor.messagePending);
    }
    return result;
}

void ActorMonitorTable::setupColWidth()
{
    const auto fnHeaderWidth = [this](int nCol) -> int
    {
        if(checkCol(nCol)){
            return 10 + getColName(nCol).size() * 10;
        }
        return 100;
    };

    if(m_actorMonitorList.empty()){
        for(int i = 0; i < getColCount(); ++i){
            col_width(i, fnHeaderWidth(i));
        }
    }
    else{
        col_width(0, (std::max<int>)(fnHeaderWidth(0), 150)); // UID
        col_width(1, (std::max<int>)(fnHeaderWidth(1),  80)); // TYPE
        col_width(2, (std::max<int>)(fnHeaderWidth(2),  30)); // GROUP
        col_width(3, (std::max<int>)(fnHeaderWidth(3), 160)); // LIVE
        col_width(4, (std::max<int>)(fnHeaderWidth(4), 160)); // BUSY
        col_width(5, (std::max<int>)(fnHeaderWidth(5), 120)); // MSG_DONE
        col_width(6, (std::max<int>)(fnHeaderWidth(6),  30)); // MSG_PENDING
        col_width(7, (std::max<int>)(fnHeaderWidth(5), 120)); // MSG_AVGDLY
    }
}

void ActorMonitorTable::updateTable()
{
    m_actorMonitorList = g_actorPool->getActorMonitor();
    m_monitorDrawHelper = getActorMonitorDrawHelper(m_actorMonitorList);

    setupLayout();
    sortTable();

    if(selectUIDRow(m_selectedUID) < 0){
        m_selectedUID = 0;
    }
    setupColWidth();
}

void ActorMonitorTable::sortTable()
{
    if(sortByCol() < 0){
        return;
    }

    std::sort(m_actorMonitorList.begin(), m_actorMonitorList.end(), [this](const ActorMonitor &lhs, const ActorMonitor &rhs) -> bool
    {
        auto fnArgedCompare = [this](const auto &x, const auto &y) -> bool
        {
            if(sortOrder()){
                return x < y;
            }
            else{
                return x > y;
            }
        };

        switch(sortByCol()){
            case 0 : return fnArgedCompare(lhs.uid, rhs.uid);
            case 1 : return fnArgedCompare(uidf::getUIDType(lhs.uid), uidf::getUIDType(rhs.uid));
            case 2 : return fnArgedCompare(g_actorPool->getBucketID(lhs.uid), g_actorPool->getBucketID(rhs.uid));
            case 3 : return fnArgedCompare(lhs.liveTick, rhs.liveTick);
            case 4 : return fnArgedCompare(lhs.busyTick, rhs.busyTick);
            case 5 : return fnArgedCompare(lhs.messageDone, rhs.messageDone);
            case 6 : return fnArgedCompare(lhs.messagePending, rhs.messagePending);
            case 7 : return fnArgedCompare(lhs.avgDelay, rhs.avgDelay);
            default: return fnArgedCompare(&lhs, &rhs); // keep everything as it or reversed
        }
    });
}

int ActorMonitorTable::selectUIDRow(uint64_t uid)
{
    if(!uid){
        return -1;
    }

    int uidRow = -1;
    for(int row = 0; row < getRowCount(); ++row){
        if(m_actorMonitorList[row].uid == uid){
            select_row(row, 1);
            uidRow = row;
        }
        else{
            select_row(row, 0);
        }
    }
    return uidRow;
}

void ActorMonitorTable::onDoubleClickCell(int row, int)
{
    g_podMonitorWindow->setPodUID(m_actorMonitorList.at(row).uid);
    g_podMonitorWindow->updateTable();
    g_podMonitorWindow->showAll();
}
