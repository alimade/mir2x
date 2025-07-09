#pragma once
#include <string>
#include <cstdint>

struct DCRecord
{
    int ID;
    int HP;
    int MP;

    std::u8string name;
    std::u8string description;

    DCRecord(int argID,
             int argHP,
             int argMP,

             const char8_t *argName,
             const char8_t *argDescription)
        : ID            (argID)
        , HP		    (argHP)
        , MP		    (argMP)
        , name	        (argName ? argName : u8"")
        , description	(argDescription ? argDescription : u8"")
    {}

    bool Valid() const
    {
        return ID != 0;
    }

    operator bool() const
    {
        return Valid();
    }
};
