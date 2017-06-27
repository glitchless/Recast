/**
 * @file networking.cpp
 * @brief Socket (TCP) utils header file
 * @author StealthTech
 * @project Recast-server
 * @date 27.06.17
 * @email st3althtech@mail.ru
 *
 **/

#ifndef RECAST_SERVER_SOCKET_TCP_HPP
#define RECAST_SERVER_SOCKET_TCP_HPP

#include "network/NetworkUtils.hpp"
#include "network/Socket.hpp"

using namespace std;

class SocketTCP : public Socket {
public:
    using Socket::Socket;
    SocketTCP(uint32_t port, uint32_t queueSize) : Socket::Socket() {
        socketBoundPort = port;
        socketQueueSize = queueSize;
        createServerSocket();
    }
public:
    void setRecvTimeout(int seconds, int microseconds);
    void createServerSocket() override;
    void createServerSocket(uint32_t port, uint32_t queueSize);

    void send(const string &str);
    void sendBytes(const char *data, size_t num);
    string recv();
    string recv(size_t bytes);
    string recvTimed(int timeout);
    char* recvBytes(size_t num);
    bool hasData();
    shared_ptr<SocketTCP> accept();
private:
    uint32_t socketQueueSize;
};

#endif //RECAST_SERVER_SOCKET_TCP_HPP
