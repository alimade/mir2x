#pragma once
#include <vector>
#include <string>
#include "uidf.hpp"
#include "raiitimer.hpp"
#include "fltableimpl.hpp"
#include "actormonitor.hpp"

class ActorMonitorTable: public Fl_TableImpl
{
    private:
        struct ActorMonitorDrawHelper
        {
            size_t maxAvgDelay = 0;
            size_t maxMessageDone = 0;
            size_t maxMessagePending = 0;
            std::array<size_t, UID_END> uidTypeCountList;

            ActorMonitorDrawHelper()
            {
                uidTypeCountList.fill(0);
            }
        };

    private:
        ActorMonitorDrawHelper m_monitorDrawHelper;

    private:
        std::vector<ActorMonitor> m_actorMonitorList;

    private:
        uint64_t m_selectedUID = 0;

    public:
        ActorMonitorTable(int argX, int argY, int argW, int argH, const char *labelCPtr = nullptr)
            : Fl_TableImpl(argX, argY, argW, argH, labelCPtr)
        {}

    protected:
        std::string getGridData(int, int) const override;

    private:
        static ActorMonitorDrawHelper getActorMonitorDrawHelper(const std::vector<ActorMonitor> &);

    private:
        void sortTable();
        void setupColWidth();

    private:
        bool rowSelected(int row) const
        {
            checkRowEx(row);
            return m_actorMonitorList.at(row).uid == m_selectedUID;
        }

    public:
        void updateTable();

    private:
        int selectUIDRow(uint64_t);

    public:
        void onClickOff() override
        {
            m_selectedUID = 0;
        }

        void onClickCell(int row, int) override
        {
            checkRowEx(row);
            m_selectedUID = m_actorMonitorList.at(row).uid;
        }

    public:
        void onDoubleClickCell(int, int) override;

    public:
        int getRowCount() const override
        {
            return static_cast<int>(m_actorMonitorList.size());
        }

        int getColCount() const override
        {
            return 8;
        }

        std::string getColName(int col) const override
        {
            switch(col){
                case 0: return "UID";
                case 1: return "TYPE";
                case 2: return "GROUP";
                case 3: return "LIVE";
                case 4: return "BUSY";
                case 5: return "MSG_DONE";
                case 6: return "MSG_PENDING";
                case 7: return "MSG_AVGDLY";
                default: throw fflerror("invalid col: %d", col);
            }
        }

    public:
        int uidTypeCount(int uidType) const
        {
            return static_cast<int>(m_monitorDrawHelper.uidTypeCountList.at(uidType));
        }

        int uidCount() const
        {
            return static_cast<int>(m_actorMonitorList.size());
        }
};
