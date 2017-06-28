/**
 * @file networking.cpp
 * @brief Network Listener abstract utils header file
 * @author StealthTech
 * @project Recast-server
 * @date 27.06.17
 * @email st3althtech@mail.ru
 *
 **/

#ifndef RECAST_SERVER_NETWORKLISTENER_HPP
#define RECAST_SERVER_NETWORKLISTENER_HPP

#include <string>
#include "io/network/Networking.hpp"
#include "commands/ICommandSender.hpp"

class NetworkListener {
public:
    NetworkListener(int id) : listenerId(id) {}

public:
    int getId() { return listenerId; }

    virtual char *onPacket(char *request, ICommandSender *sender) = 0;

protected:
    int listenerId;
};

class DebugNetworkListener : public NetworkListener {
public:
    using NetworkListener::NetworkListener;
public:
    char *onPacket(char *request, ICommandSender *sender) {
        sender->onMessage(std::string("Listener [") + std::to_string(listenerId) + "] got request " + request);
        return request;
    };
};

#endif //RECAST_SERVER_NETWORKLISTENER_HPP
