#include "server.h"

#include <iostream>

int main(int argc, char *argv[])
{
    // if (argc < 2)
    // {
    //     std::cerr << "No port specified\n";
    //     return 1;
    // }
    // int port = atoi(argv[1]);
    int port = 4444;

    Server server;
    if (int err = server.start(port))
    {
        return err;
    }

    return server.exec();
}