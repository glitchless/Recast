#ifndef RECAST_SERVER_ICOMMANDSENDER_H
#define RECAST_SERVER_ICOMMANDSENDER_H


#include <models/Player.h>
#include <boost/shared_ptr.hpp>

using namespace std;

class Server;

class ICommandSender {
public:
    ~ICommandSender() {}

    ICommandSender() {}

    virtual bool isOP() = 0;

    virtual shared_ptr<Server> getServer() = 0;

    //TODO getWorld()
    virtual shared_ptr<Player> getPlayer() = 0;

    virtual void onMessage(std::string msg) = 0;
};


#endif //RECAST_SERVER_ICOMMANDSENDER_H
