#include <cstdint>
#include <string>

// протокол управления фонарем
class PUF
{
public:
    static uint8_t cmdFromStr(std::string str);
    static std::string strFromCmd(uint8_t cmd);

    static uint16_t valueLenFromCmd(uint8_t cmd);
};