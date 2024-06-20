class Server
{
public:
    Server();
    ~Server();

    int start(int port);
    int exec();
private:
    static void pollClient(int sock);

    int sock_;
};
