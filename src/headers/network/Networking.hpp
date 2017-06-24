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

//class Socket {
//public:
//    Socket()       : socketDescr(-1) {}
//    Socket(int sd) : socketDescr(sd) {}
//    ~Socket() { if (socketDescr > 0) ::close(socketDescr); }
//
//public:
//    int  getSocketDescr() const noexcept { return socketDescr; }
//    void setNonBlocked(bool option)                                           noexcept (false);
//    void send(const string &str)                                              noexcept (false);
//    void sendTo(struct sockaddr_in &sendToAddr, const string &str)            noexcept (false);
//    string recvFrom(struct sockaddr_in &recvFromAddr)                         noexcept (false);
//    string recv()                                                             noexcept (false);
//    string recv(size_t bytes)                                                 noexcept (false);
//    string recvTimed(int timeout)                                             noexcept (false);
//    void setRecvTimeout(int seconds, int microseconds)                        noexcept (false);
//    bool hasData()                                                            noexcept (false);
//    void createServerSocketUDP(uint32_t port)                                 noexcept (false);
//    void createServerSocketTCP(uint32_t port, uint32_t queueSize)             noexcept (false);
//    shared_ptr<Socket> accept()                                               noexcept (false);
//    void close() { ::close(socketDescr); }
//
//private:
//    void setReuseAddress(int sd)                                              noexcept (false);
//    int socketDescr;
//};

class Socket {
public:
    Socket()       : socketDescr(-1) {}
    Socket(int sd) : socketDescr(sd) {}
    ~Socket() { if (socketDescr > 0) ::close(socketDescr); }
public:
    int  getSocketDescr() const noexcept { return socketDescr; }
    void setNonBlocked(bool option);
    void close() { ::close(socketDescr); }
protected:
    void setReuseAddress(int sd);
    int socketDescr;
};

class SocketTCP : Socket {
public:
    using Socket::Socket;
    SocketTCP(uint32_t port, uint32_t queueSize) : Socket::Socket() { createServerSocket(port, queueSize); }
public:
    void setRecvTimeout(int seconds, int microseconds);
    void createServerSocket(uint32_t port, uint32_t queueSize);

    void send(const string &str);
    void sendBytes(const char *data, size_t num);
    string recv();
    string recv(size_t bytes);
    string recvTimed(int timeout);
    char* recvBytes(size_t num);
    bool hasData();
    shared_ptr<SocketTCP> accept();
};

class SocketUDP : Socket {
public:
    using Socket::Socket;
    SocketUDP(uint32_t port) : Socket::Socket() { createServerSocket(port); }
public:
    void createServerSocket(uint32_t port);
    void sendTo(struct sockaddr_in &sendToAddr, const string &str);
    string recvFrom(struct sockaddr_in &recvFromAddr);

    void sendBytesTo(struct sockaddr_in &sendToAddr, const char *data, size_t num);
    char* recvBytesFrom(struct sockaddr_in &recvFromAddr);
};

#endif //RECAST_NETWORKING_H
