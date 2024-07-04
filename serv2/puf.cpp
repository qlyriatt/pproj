#include "puf.h"

#include <map>

uint8_t PUF::cmdFromStr(std::string str)
{
    static std::map<std::string, uint8_t> m
    {
        {"ON", 0x12},
        {"OFF", 0x13},
        {"COLOR", 0x20}
    };

    auto cmd = m.find(str);
    
    return cmd != m.end() ? (*cmd).second : 0;
}

std::string PUF::strFromCmd(uint8_t cmd)
{
    static std::map<std::string, uint8_t> m
    {
        {"ON", 0x12},
        {"OFF", 0x13},
        {"COLOR", 0x20}
    };

    for (auto kv : m)
    {
        if (kv.second == cmd)
            return kv.first;
    }

    return {};
}

uint16_t PUF::valueLenFromCmd(uint8_t cmd)
{
    static std::map<uint8_t, uint16_t> m
    {
        {0x12, 0},
        {0x13, 0},
        {0x20, 3}
    };

    auto len = m.find(cmd);

    return len != m.end() ? (*len).second : 0;
}
