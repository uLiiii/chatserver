#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>
using namespace std;

// 处理服务器ctrl+c结束后，重置user的状态信息
void resetHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char *argv[])
{
    string serverIp = "127.0.0.1";
    int serverPort = 6000;
    if (argc == 3)
    {
        serverIp = argv[1];
        serverPort = stoi(argv[2]);
    }

    signal(SIGINT, resetHandler);

    EventLoop loop;
    InetAddress addr(serverIp, serverPort);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();

    return 0;
}