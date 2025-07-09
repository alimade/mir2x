#include <utf8.h>
#include <cstring>
#include <cstdint>
#include <cinttypes>
#include <stdexcept>
#include "strf.hpp"
#include "utf8f.hpp"
#include "fflerror.hpp"

uint32_t utf8f::peekUTF8Code(const char *utf8String)
{
    // seems utf8::peek_next() is not what I need here
    // what it returns?

    fflassert(str_haschar(utf8String));
    const size_t size = std::strlen(utf8String);

    auto p = utf8String;
    try{
        utf8::advance(p, 1, utf8String + size);
    }
    catch(...){
        throw fflerror("failed to peek the first utf8 code");
    }

    fflassert(p - utf8String <= 4);

    uint32_t code = 0;
    std::memcpy(&code, utf8String, p - utf8String);
    return code;
}

std::vector<int> utf8f::buildUTF8Off(const char *utf8String)
{
    fflassert(utf8String);
    const auto size = std::strlen(utf8String);

    if(size == 0){
        return {};
    }

    std::vector<int> off;

    const char *p = utf8String;
    const char *pend = utf8String + size;

    off.reserve(size);
    for(; p < pend; utf8::advance(p, 1, pend)){
        off.push_back(p - utf8String);
    }

    return off;
}

std::string utf8f::toupper(std::string s)
{
    char *p = s.data();
    char *pend = s.data() + s.size();

    while(p < pend){
        auto lastp = p;
        utf8::advance(p, 1, pend);

        if(p - lastp == 1 && *lastp >= 'a' && *lastp <= 'z'){
            *lastp = 'A' + *lastp - 'a';
        }
    }
    return s;
}

bool utf8f::valid(const std::string &s)
{
    return utf8::is_valid(s);
}
