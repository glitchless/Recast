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

#include "commands/ICommandSender.h"
#include "commands/CommandManager.h"
#include <memory>

/**
 * @brief Main class in Recast Server
 */
class Server : public std::enable_shared_from_this<ICommandSender> {
public:
    volatile bool isRunning;

    Server();

    ~Server();

    Server(Server &other) = delete;

    static Server *initServer();

    void mainLoop();

    bool isOP() { return true; };

    std::shared_ptr<Server> getServer() { return shared_from_this(); }

    std::shared_ptr<Player> getPlayer() { return std::shared_ptr<Player>(NULL); }

    void onMessage(std::string msg);

private:
    CommandManager manager;
};


#endif //RECAST_SERVER_H
