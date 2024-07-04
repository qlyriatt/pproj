#include "client.h"

#include "../puf.h"

#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

Client::Client() : serv_addr_(0), serv_port_(0), is_on_(false)
{
}

Client::~Client()
{
    stop();
}

int Client::start(int serv_addr, int serv_port)
{
    serv_addr_ = serv_addr;
    serv_port_ = serv_port;

    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ < 0)
    {
        std::cerr << errno << " - error on opening socket\n";
        return -1;
    }

    sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(serv_addr_);
    s_addr.sin_port = htons(serv_port_);
    if (connect(sock_, reinterpret_cast<sockaddr *>(&s_addr), sizeof(s_addr)) < 0)
    {
        std::cerr << errno << " - error on connecting to server\n";
        return -1;
    }

    return 0;
}

int Client::exec()
{
    char buf[512];
    while (true)
    {
        int bytes = recv(sock_, buf, 512, 0);
        if (!bytes)
            break;

        if (bytes < 0)
        {
            std::cerr << errno << " - error on recv from server\n";
            sleep(0.5);
            continue;
        }

        uint8_t cmd;
        uint16_t value_len;
        memmove(&cmd, &buf[0], sizeof(cmd));
        memmove(&value_len, &buf[sizeof(cmd)], sizeof(value_len));

        auto str = PUF::strFromCmd(cmd);
        if (str == "ON")
        {
            if (is_on_)
                std::cout << "Фонарь уже был включен!\n";
            else
            {
                std::cout << "Включаем фонарь\n";
                is_on_ = true;
            }
        }
        else if (str == "OFF")
        {
            if (!is_on_)
                std::cout << "Фонарь уже был выключен!\n";
            else
            {
                std::cout << "Выключаем фонарь\n";
                is_on_ = false;
            }
        }
        else if (str == "COLOR")
        {
            char value[value_len];
            memmove(&value, &buf[sizeof(cmd) + sizeof(value_len)], value_len);

            std::cout << "Изменение цвета на (" << int(value[0]) << ", " << int(value[1]) << ", " << int(value[2]) << ")" << std::endl;
        }
    }

    return 0;
}

void Client::stop()
{
    if (sock_ > 0)
        close(sock_);
}
