/**
 * @file SocketUDP.hpp
 * @brief Socket (UDP) utils header file
 * @author StealthTech
 * @project Recast-server
 * @date 27.06.17
 * @email st3althtech@mail.ru
 *
 **/

#ifndef RECAST_SERVER_SOCKET_UDP_HPP
#define RECAST_SERVER_SOCKET_UDP_HPP

#include "network/NetworkUtils.hpp"
#include "network/Socket.hpp"

using namespace std;

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

#endif //RECAST_SERVER_SOCKET_UDP_HPP
