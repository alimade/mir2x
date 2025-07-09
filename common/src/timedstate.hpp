#include <cstdint>
#include <utility>
#include "raiitimer.hpp"
template<typename T> class TimedState final
{
    private:
        T m_state;
        hres_timer m_timer;

    private:
        uint64_t m_msec;

    public:
        TimedState(T val = {}, uint64_t msec = 0)
            : m_state(std::move(val))
            , m_msec(msec)
        {}

    public:
        void set(T val, uint64_t msec = 0)
        {
            m_state = std::move(val);
            m_msec  = msec;
            m_timer.reset();
        }

        T get() const
        {
            if((m_msec > 0) && (m_timer.diff_msec() > m_msec)){
                return {};
            }
            return m_state;
        }
};
