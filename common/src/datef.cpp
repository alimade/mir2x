#include <ctime>
#include <sstream>
#include "datef.hpp"
#include "totype.hpp"
#include "fflerror.hpp"

std::string datef::now()
{
    std::time_t rawTime;
    if(std::time(&rawTime) == (std::time_t)(-1)){
        throw fflerror("std::time() failed");
    }

    // not thread-safe here
    // localtime() return an internal std::tm buffer

    if(const auto localPtr = std::localtime(&rawTime)){
        char timeStrBuf[128];
        std::strftime(timeStrBuf, sizeof(timeStrBuf), "%Y%m%d%H%M%S", localPtr);
        return timeStrBuf;
    }
    throw fflerror("std::localtime(%p) failed", to_cvptr(&rawTime));
}
