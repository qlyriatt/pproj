class Client
{
public:
    Client();
    ~Client();

    int start(int serv_addr, int serv_port);
    int exec();
    void stop();
private:
    int sock_;
    int serv_addr_;
    int serv_port_;

    bool is_on_;
};
