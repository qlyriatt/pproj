#include "client.h"

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "No port specified\n";
        return 1;
    }
    int serv_port = atoi(argv[1]);

    Client client;
    if (int err = client.start(serv_port))
    {
        return err;
    }

    return client.exec();
}