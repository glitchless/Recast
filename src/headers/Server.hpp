/**
 * @file
 * @brief Server file
 * @author LionZXY
 * @project Recast
 * @date 08.06.17
 *
 * Main server file (aka Context)
 **/

#ifndef RECAST_SERVER_H
#define RECAST_SERVER_H

#include <string>
#include <thread>
#include <world/Box2DWorld.h>
#include "threads/InputThread.hpp"
#include "commands/ICommandSender.hpp"
#include "commands/CommandManager.hpp"
#include "io/network/NetworkServer.hpp"
#include "temperature-world/interfaces/IUpdater.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkableObservable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkableGeneratable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkableMutable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkable.hpp"
#include "temperature-world/interfaces/ITemperatureWorld.hpp"

class Player;

class PlayersOnline;

typedef ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkableMutable<ITemperatureWorldChunkable<ITemperatureWorld>>>> TempWorld;

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

    virtual Box2DWorld *getWorld() { return &world; }

    std::shared_ptr<TempWorld> getTemperatureWorld() const { return temperatureWorld; }

private:
    void initTemperatureWorld();

    void update();

    void runNetworkServer(NetworkServer *tcp, NetworkServer *udp);

    volatile bool isLaunching;
    std::thread inputThread;
    std::thread listenTCPThread;
    std::thread listenUDPThread;
    PlayersOnline *players;
    NetworkServer *serverTCP;
    NetworkServer *serverUDP;
    InputThread *inputObject;
    std::shared_ptr<TempWorld> temperatureWorld;
    std::shared_ptr<IUpdater> temperatureWorldUpdater;

    Box2DWorld world;
};


#endif //RECAST_SERVER_H