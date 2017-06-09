#ifndef RECAST_SERVER_ICOMMANDSENDER_H
#define RECAST_SERVER_ICOMMANDSENDER_H


#include <boost/shared_ptr.hpp>

class Server;

class Player;

class ICommandSender {
public:
    ICommandSender() {}

    ~ICommandSender() {}

    virtual bool isOP() const = 0;

    virtual std::shared_ptr<Server> getServer()= 0;

    //TODO getWorld()
    virtual std::shared_ptr<Player> getPlayer() = 0;

    virtual void onMessage(std::string msg) = 0;
};


#endif //RECAST_SERVER_ICOMMANDSENDER_H
