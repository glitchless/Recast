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

#include "network/Networking.hpp"

class ICommandSender;
using namespace std;

class NetworkListener {
public:
    NetworkListener(int id) : listenerId(id) { }
public:
    int getId() { return listenerId; }
    virtual char* onPacket(char *request, ICommandSender * sender) = 0;
protected:
    int listenerId;
};

#endif //RECAST_SERVER_NETWORKLISTENER_HPP
