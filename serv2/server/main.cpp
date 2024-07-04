#include "server.h"
#include "netinet/in.h"

#include <cstring>
#include <iostream>

int main(int argc, char *argv[])
{
    int addr = INADDR_LOOPBACK;
    int port = 9999;

    if (argc >= 2)
    {
        addr = 0;
        char *addr_str = argv[1];
        char *token = std::strtok(addr_str, ".");
        for (int i = 0;; ++i)
        {
            if (i > 3 && token || i < 3 && !token)
            {
                std::cerr << "Invalid address\n";
                return -1;
            }

            if (i > 3)
                break;
            
            addr |= atoi(token) << 24 - 8 * i;
            token = std::strtok(nullptr, ".");
        }
    }
    if (argc >= 3)
    {
        port = atoi(argv[2]);
        if (port < 0 || port > 0xFFFF)
        {
            std::cerr << "Invalid port\n";
            return -1;
        }
    }

    Server server;
    if (int err = server.start(addr, port))
    {
        return err;
    }

    return server.exec();
}