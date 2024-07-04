#include "client.h"
#include "netinet/in.h"

#include <cstring>
#include <iostream>

int main(int argc, char *argv[])
{
    int serv_addr = INADDR_LOOPBACK;
    int serv_port = 9999;

    if (argc >= 2)
    {
        serv_addr = 0;
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
            
            serv_addr |= atoi(token) << 24 - 8 * i;
            token = std::strtok(nullptr, ".");
        }
    }
    if (argc >= 3)
    {
        serv_port = atoi(argv[2]);
        if (serv_port < 0 || serv_port > 0xFFFF)
        {
            std::cerr << "Invalid port\n";
            return -1;
        }
    }

    Client client;
    if (int err = client.start(serv_addr, serv_port))
    {
        return err;
    }

    return client.exec();
}