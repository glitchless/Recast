#ifndef RECAST_SERVER_ICOMMANDSENDER_H
#define RECAST_SERVER_ICOMMANDSENDER_H


#include <models/Player.h>
#include <boost/shared_ptr.hpp>
#include <Server.h>

class ICommandSender {
public:
    ~ICommandSender() {}

    ICommandSender() {}

    virtual bool isOP() = 0;

    virtual Server *getServer() = 0;

    //TODO getWorld()
    virtual Player *getPlayer() = 0;

    virtual void onMessage(std::string msg) = 0;
};


#endif //RECAST_SERVER_ICOMMANDSENDER_H
