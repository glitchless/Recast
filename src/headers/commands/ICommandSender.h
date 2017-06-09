#ifndef RECAST_SERVER_ICOMMANDSENDER_H
#define RECAST_SERVER_ICOMMANDSENDER_H

#include <string>

class Server;

class Player;

class ICommandSender {
public:
    virtual bool isOP() const = 0;

    virtual Server *getServer() = 0;

    //TODO getWorld()
    virtual Player *getPlayer() = 0;

    virtual void onMessage(const std::string &msg) = 0;
};


#endif //RECAST_SERVER_ICOMMANDSENDER_H
