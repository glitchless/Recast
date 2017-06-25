/**
 * @file networking.cpp
 * @brief Basic networking utils header file
 * @author StealthTech
 * @project Recast-server
 * @date 17.06.17
 * @email st3althtech@mail.ru
 *
 **/

#ifndef RECAST_NETWORKING_H
#define RECAST_NETWORKING_H

#include <string>
#include <unistd.h>
#include <memory>

using namespace std;

const int DEFAULT_PORT_TCP = 1337;
const int DEFAULT_PORT_UDP = 1338;

string int2ipv4(uint32_t ip);

class Socket {
public:
    Socket()       : socketDescr(-1), socketBoundPort(0) {}
    Socket(int sd) : socketDescr(sd), socketBoundPort(0) {}
    ~Socket() { if (socketDescr > 0) ::close(socketDescr); }
public:
    int  getSocketDescr() const noexcept { return socketDescr; }
    void setNonBlocked(bool option);
    void close() { ::close(socketDescr); }
    virtual void createServerSocket() = 0;
protected:
    void setReuseAddress(int sd);
    int socketDescr;
    uint32_t socketBoundPort;
};

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

class SocketUDP : public Socket {
public:
    using Socket::Socket;
    SocketUDP(uint32_t port) : Socket::Socket() {
        socketBoundPort = port;
        createServerSocket();
    }
public:
    void createServerSocket() override;
    void createServerSocket(uint32_t port);
    void sendTo(struct sockaddr_in &sendToAddr, const string &str);
    string recvFrom(struct sockaddr_in &recvFromAddr);

    void sendBytesTo(struct sockaddr_in &sendToAddr, const char *data, size_t num);
    char* recvBytesFrom(struct sockaddr_in &recvFromAddr);
};

#endif //RECAST_NETWORKING_H
