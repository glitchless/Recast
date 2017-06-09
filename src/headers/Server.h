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
#include <string>

class Player;

/**
 * @brief Main class in Recast Server
 */
class Server : public ICommandSender {
public:

    Server();

    ~Server();

    Server(const Server &other) = delete;

    void initServer();

    void mainLoop();

    bool isOP() const { return true; }

    Server *getServer() { return this; }

    Player *getPlayer() { return NULL; }

    void onMessage(const std::string &msg);

    bool shutdown();

private:
    CommandManager manager;
    volatile bool isRunning;
};


#endif //RECAST_SERVER_H
