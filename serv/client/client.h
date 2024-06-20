class Client
{
public:
    Client();
    ~Client();

    int start(int serv_port);
    int exec();
private:
    int sock_;
    int serv_port_;
};
