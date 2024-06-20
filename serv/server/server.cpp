#include "server.h"

#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <thread>

Server::Server() : sock_(0)
{
}

Server::~Server()
{
    if (sock_ > 0)
        close(sock_);
}

int Server::start(int port)
{
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ < 0)
    {
        std::cerr << "Error on opening socket\n";
        return 1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(port);
    if (bind(sock_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0)
    {
        std::cerr << "Error on binding socket\n";
        return 1;
    }

    return 0;
}

int Server::exec()
{
    listen(sock_, 1);

    while (true)
    {
        int sock = accept(sock_, nullptr, nullptr);
        if (sock < 0)
        {
            std::cerr << "Error on accepting\n";
            continue;
        }

        std::thread t(&Server::pollClient, sock);
        t.detach();
        std::cout << "detach\n";
    }

    return 0;
}

void Server::pollClient(int sock)
{
    const int timeout_secs = 10;

    pollfd poll_sock;
    poll_sock.fd = sock;
    poll_sock.events = POLLIN;

    while (true)
    {
        int poll_result = poll(&poll_sock, 1, 1000 * timeout_secs);
        if (poll_result == -1)
        {
            std::cerr << "Error in polling\n";
            break;
        }
        else if (poll_result == 0)
        {
            std::cout << "Socket " << sock << " timeout\n";
            break;
        }
        else if (poll_sock.revents & POLLIN)
        {
            poll_sock.revents = 0;

            char buf[512];
            std::ofstream output;
            output.open("log.txt", std::ios::app);
            auto time = std::time(nullptr);
            output << std::ctime(&time);
            while (true)
            {
                int bytes = recv(sock, buf, 512, MSG_DONTWAIT);

                if (bytes == -1 && (errno == EWOULDBLOCK || errno == EAGAIN))
                {
                    output << "\n";
                    output.flush();
                    output.close();
                    break;
                }
                if (bytes == 0)
                {
                    output.close();
                    goto close;
                }

                output << buf;
            }
        }
    }
close:

    close(sock);
};
