/**
 * @file
 * @brief Server file
 * @author LionZXY
 * @project Recast
 * @date 08.06.17
 *
 * Main server file (aka Context)
 *
 **/

#ifndef RECAST_SERVER_H
#define RECAST_SERVER_H

#include <string>
#include <thread>
#include "commands/ICommandSender.hpp"
#include "commands/CommandManager.hpp"
#include "network/NetworkServer.hpp"

class Player;

class PlayersOnline;

/**
 * @brief Main class in Recast Server
 */
class Server : public ICommandSender {
public:

    Server();

    ~Server();

    Server(const Server &other) = delete;

    void initServer();

    bool isOP() const { return true; }

    Server *getServer() { return this; }

    Player *getPlayer() { return NULL; }

    void onMessage(const std::string &msg);

    bool shutdown();

    bool isRunning() const { return isLaunching; }

    PlayersOnline *getPlayers() const { return players; }

private:
    volatile bool isLaunching;
    std::thread inputThread;
    std::thread listenTCPThread;
    std::thread listenUDPThread;
    PlayersOnline *players;
    NetworkServer *serverTCP;
    NetworkServer *serverUDP;

    void runNetworkServer(NetworkServer *tcp, NetworkServer *udp);
};


#endif //RECAST_SERVER_H