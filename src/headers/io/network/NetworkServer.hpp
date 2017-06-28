/**
 * @file NetworkServer.hpp
 * @brief Networking server header file
 * @author StealthTech
 * @project Recast-server
 * @date 19.06.17
 * @email st3althtech@mail.ru
 *
 **/

#ifndef RECAST_NETWORKING_SERVER_HPP
#define RECAST_NETWORKING_SERVER_HPP

#include <vector>
#include <unordered_map>
#include "Networking.hpp"

class ICommandSender;
void setNonBlockedImpl(int sd, bool option) noexcept (false);

class NetworkServer {
public:
    NetworkServer(uint32_t port, ICommandSender *sender, bool isTCP = false);
    void run();
    void shutdown();
    bool running() { return isRunning; }
    bool registerListener(NetworkListener *listener);
    bool removeListener(NetworkListener *listener);
private:
    ICommandSender *sender;
    uint32_t port;
    bool isTCP;
    volatile bool isRunning;
    std::unordered_map<int, NetworkListener*>  listeners;

    bool nofityListener(char *request);
    void listenFor(std::shared_ptr<SocketTCP> client);
    void listenForBytes(std::shared_ptr<SocketTCP> client);
    void listenFor(std::shared_ptr<SocketUDP> client);
    void listenForBytes(std::shared_ptr<SocketUDP> client);
    string exchange(const string request);
    char* exchange(char *request);
};

#endif //RECAST_NETWORKING_SERVER_HPP
