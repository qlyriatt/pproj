#include <netinet/in.h>

#include <mutex>
#include <vector>

class Server
{
public:
    Server();
    ~Server();

    int start(int addr, int port);
    int exec();
    void stop();
private:
    void handleClients();
    void handleDisconnects();
private:
    struct Client
    {
        int sock_;
        unsigned int id_;
        sockaddr_in s_addr_;
    };

    int sock_;

    std::mutex m_;
    std::vector<Client> clients_;
};
