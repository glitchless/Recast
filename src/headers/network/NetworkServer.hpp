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

#include <vector>

#include "network/Networking.hpp"

using namespace std;

class NetworkServer {
public:
    NetworkServer(uint32_t port, bool isTCP = false);
    void run();
    void shutdown();
    bool running() { return isRunning; }
    bool registerListener(NetworkListener *listener);
    bool removeListener(NetworkListener *listener);
private:
    uint32_t port;
    bool isTCP;
    volatile bool isRunning;
    vector<NetworkListener*> listeners;

    bool nofityListener(char *request);
    void listenFor(shared_ptr<SocketTCP> client);
    void listenForBytes(shared_ptr<SocketTCP> client);
    void listenFor(shared_ptr<SocketUDP> client);
    void listenForBytes(shared_ptr<SocketUDP> client);
    string exchange(const string request);
    char* exchange(char *request);
};

#endif //RECAST_NETWORKINGSERVER_H
