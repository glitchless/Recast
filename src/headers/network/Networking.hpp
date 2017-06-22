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
//    void setNonBlocked(bool option)                                           throw (exception);
//    void send(const string &str)                                              throw (exception);
//    void sendTo(struct sockaddr_in &sendToAddr, const string &str)            throw (exception);
//    string recvFrom(struct sockaddr_in &recvFromAddr)                         throw (exception);
//    string recv()                                                             throw (exception);
//    string recv(size_t bytes)                                                 throw (exception);
//    string recvTimed(int timeout)                                             throw (exception);
//    void setRecvTimeout(int seconds, int microseconds)                        throw (exception);
//    bool hasData()                                                            throw (exception);
//    void createServerSocketUDP(uint32_t port)                                 throw (exception);
//    void createServerSocketTCP(uint32_t port, uint32_t queueSize)             throw (exception);
//    shared_ptr<Socket> accept()                                               throw (exception);
//    void close() { ::close(socketDescr); }
//
//private:
//    void setReuseAddress(int sd)                                              throw (exception);
//    int socketDescr;
//};

class Socket {
public:
    Socket()       : socketDescr(-1) {}
    Socket(int sd) : socketDescr(sd) {}
    ~Socket() { if (socketDescr > 0) ::close(socketDescr); }
public:
    int  getSocketDescr() const noexcept { return socketDescr; }
    void setNonBlocked(bool option)                                           throw (exception);
    void close() { ::close(socketDescr); }
protected:
    void setReuseAddress(int sd)                                              throw (exception);
    int socketDescr;
};

class SocketTCP : Socket {
public:
    using Socket::Socket;
    SocketTCP(uint32_t port, uint32_t queueSize) : Socket::Socket() { createServerSocket(port, queueSize); }
public:
    void setRecvTimeout(int seconds, int microseconds)                        throw (exception);
    void createServerSocket(uint32_t port, uint32_t queueSize)                throw (exception);

    void send(const string &str)                                              throw (exception);
    string recv()                                                             throw (exception);
    string recv(size_t bytes)                                                 throw (exception);
    string recvTimed(int timeout)                                             throw (exception);
    bool hasData()                                                            throw (exception);
    shared_ptr<SocketTCP> accept()                                            throw (exception);
};

class SocketUDP : Socket {
public:
    using Socket::Socket;
    SocketUDP(uint32_t port) : Socket::Socket() { createServerSocket(port); }
public:
    void createServerSocket(uint32_t port)                                 throw (exception);
    void sendTo(struct sockaddr_in &sendToAddr, const string &str)            throw (exception);
    string recvFrom(struct sockaddr_in &recvFromAddr)                         throw (exception);
};

#endif //RECAST_NETWORKING_H