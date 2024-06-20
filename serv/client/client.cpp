#include "client.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>

Client::Client() : serv_port_(0)
{
}

Client::~Client()
{
    if (sock_ > 0)
        close(sock_);
    if (serv_port_ > 0)
        close(serv_port_);
}

int Client::start(int server_port)
{
    serv_port_ = server_port;

    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ < 0)
    {
        std::cerr << "Error on opening socket" << std::endl;
        return 1;
    }

    return 0;
}

int Client::exec()
{
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(serv_port_);
    if (connect(sock_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0)
    {
        std::cerr << "Error on connecting to server" << std::endl;
        return 1;
    }

    std::string input;
    while (std::getline(std::cin, input))
    {
        send(sock_, input.data(), input.length(), 0);
    }
    close(serv_port_);

    return 0;
}
