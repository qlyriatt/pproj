#include "server.h"

#include "../puf.h"

#include <sys/poll.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <thread>
#include <algorithm>
#include <cstring>

Server::Server() : sock_(0)
{
}

Server::~Server()
{
    stop();
}

int Server::start(int addr, int port)
{
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ < 0)
    {
        std::cerr << errno << " - error on opening socket\n";
        return -1;
    }
    int opt = 1;
    setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

    sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(addr);
    s_addr.sin_port = htons(port);
    if (bind(sock_, reinterpret_cast<sockaddr *>(&s_addr), sizeof(s_addr)) < 0)
    {
        std::cerr << errno << " - error on binding socket\n";
        return -1;
    }

    if (listen(sock_, 1) < 0)
    {
        std::cerr << errno << " - error on listen\n";
        return -1;
    }

    return 0;
}

int Server::exec()
{
    std::thread(&Server::handleClients, this).detach();

    std::string input;
    while (std::getline(std::cin, input))
    {
        if (input == "list" || input == "l")
        {
            std::cout << "Список подключенных фонарей:\n";
            for (auto &c : clients_)
            {
                auto *s_addr = reinterpret_cast<sockaddr_in *>(&c.s_addr_);
                int addr = ntohl(s_addr->sin_addr.s_addr);
                int port = ntohs(s_addr->sin_port);

                std::cout << "id: " << std::setw(3) << c.id_ << " "
                          << "addr: " << (addr >> 24) << "." << (addr >> 16 & 0xFF)
                          << "." << (addr >> 8 & 0xFF) << "." << (addr & 0xFF) << " "
                          << "port: " << port << "\n";
            }

            continue;
        }

        char *start_token = std::strtok(input.data(), " ");
        int id = atoi(start_token);
        if (id)
            start_token = std::strtok(nullptr, " ");

        uint8_t cmd = PUF::cmdFromStr(start_token);
        if (!cmd)
        {
            std::cerr << "Неизвестная команда\n";
            continue;
        }
        uint16_t value_len = PUF::valueLenFromCmd(cmd);

        int len = sizeof(cmd) + sizeof(value_len) + (value_len > 488 ? 488 : value_len);
        char buf[len];
        memmove(&buf[0], &cmd, sizeof(cmd));
        memmove(&buf[sizeof(cmd)], &value_len, sizeof(value_len));
        if (value_len)
        {
            if (auto *token = std::strtok(nullptr, " "))
            {
                memmove(&buf[sizeof(cmd) + sizeof(value_len)], token, value_len);
            }
        }

        if (id)
        {
            std::lock_guard<std::mutex> g(m_);

            auto c = std::find_if(clients_.begin(), clients_.end(), [id](Client &c)
                                  { return c.id_ == id; });
            if (c != clients_.end())
                send((*c).sock_, &buf, len, 0);
            else
                std::cerr << "Не найден фонарь с таким номером!\n";
        }
        else
        {
            std::lock_guard<std::mutex> g(m_);

            for (auto &c : clients_)
            {
                send(c.sock_, &buf, len, 0);
            }
        }
    }

    return 0;
}

void Server::stop()
{
    if (sock_ > 0)
        close(sock_);
}

void Server::handleClients()
{
    static unsigned int client_id = 1;

    while (true)
    {
        sockaddr_in s_addr;
        socklen_t addr_len = sizeof(s_addr);
        int sock = accept(sock_, reinterpret_cast<sockaddr *>(&s_addr), &addr_len);
        if (sock < 0)
        {
            std::cerr << errno << " - error on accepting\n";
            sleep(0.5);
            continue;
        }

        Client c;
        c.sock_ = sock;
        c.id_ = client_id++;
        c.s_addr_ = s_addr;

        std::lock_guard<std::mutex> g(m_);
        clients_.push_back(c);

        if (clients_.size() == 1)
            std::thread(&Server::handleDisconnects, this).detach();
    }
}

void Server::handleDisconnects()
{
    while (!clients_.empty())
    {
        pollfd poll_socks[clients_.size()];
        int i = 0;
        for (const auto &c : clients_)
        {
            poll_socks[i].fd = c.sock_;
            poll_socks[i].events = POLLIN;
            i++;
        }

        // периодически проверяется добавление новых клиентов чтобы не упустить их поллинг
        const int interval_secs = 5;
        bool restart = false;
        int events_count;
        while (true)
        {
            events_count = poll(&poll_socks[0], i, 1000 * interval_secs);
            if (events_count == -1)
            {
                std::cerr << errno << " - error in polling\n";
                sleep(0.5);
                continue;
            }
            if (events_count == 0 && clients_.size() != i)
                restart = true;

            break;
        }
        if (restart)
            continue;

        int found = 0;
        for (const auto &poll_sock : poll_socks)
        {
            if (events_count == found)
                break;

            char b;
            if ((poll_sock.revents & POLLIN) && !recv(poll_sock.fd, &b, 1, 0))
            {
                for (auto &c : clients_)
                {
                    std::lock_guard<std::mutex> g(m_);
                    clients_.erase(std::find_if(clients_.begin(), clients_.end(), [poll_sock](Client &c)
                                                { return c.sock_ == poll_sock.fd; }));
                    found++;
                    break;
                }
            }
        }
    }
}
