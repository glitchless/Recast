/**
 * @file server.cpp
 * @brief Networking server header file
 * @author StealthTech
 * @project Recast-server
 * @date 19.06.17
 * @email st3althtech@mail.ru
 *
 **/

#ifndef RECAST_NETWORKINGSERVER_H
#define RECAST_NETWORKINGSERVER_H

#include "network/Networking.hpp"

class NetworkServer {
public:
    NetworkServer(uint32_t Port);
    void run();
    void shutdown();
private:
    uint32_t port;
    bool isRunning;

    void clientWork(std::shared_ptr<Socket> client);
    std::string exchange(const std::string action);
    std::string check(const std::string action);
};

#endif //RECAST_NETWORKINGSERVER_H
