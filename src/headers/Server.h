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
#include "commands/ICommandSender.h"
#include "commands/CommandManager.h"
#include "temperature-world/interfaces/IUpdater.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkableObservable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkableGeneratable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkable.hpp"
#include "temperature-world/interfaces/ITemperatureWorld.hpp"

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

    std::shared_ptr<ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkable<ITemperatureWorld>>>>
    getTemperatureWorld() const { return temperatureWorld; }

private:
    void initTemperatureWorld();

    void update();

    volatile bool isLaunching;
    std::thread inputThread;
    PlayersOnline *players;
    std::shared_ptr<ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkable<ITemperatureWorld>>>> temperatureWorld;
    std::shared_ptr<IUpdater> temperatureWorldUpdater;
};


#endif //RECAST_SERVER_H