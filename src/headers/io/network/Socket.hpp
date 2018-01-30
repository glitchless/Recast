/**
 * @file Socket.hpp
 * @brief Socket abstract utils header file
 * @author StealthTech
 * @project Recast-server
 * @date 27.06.17
 * @email st3althtech@mail.ru
 *
 **/

#ifndef RECAST_SERVER_SOCKET_HPP
#define RECAST_SERVER_SOCKET_HPP

#include "NetworkUtils.hpp"

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

#endif //RECAST_SERVER_SOCKET_HPP
