#ifndef RECAST_SERVER_ICOMMANDSENDER_H
#define RECAST_SERVER_ICOMMANDSENDER_H

#include <string>
#include <world/Box2DWorld.h>

class Server;

class Player;

class ICommandSender {
public:
    virtual bool isOP() const = 0;

    virtual Server *getServer() = 0;

    virtual Box2DWorld *getWorld() = 0;

    virtual Player *getPlayer() = 0;

    virtual void onMessage(const std::string &msg) = 0;
};


#endif //RECAST_SERVER_ICOMMANDSENDER_H
