/**
 * @file GetEntitys.h
 * @author LionZXY
 * @project Recast-server
 * @date 28.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_GETENTITYS_H
#define RECAST_SERVER_GETENTITYS_H

#include <io/network/NetworkListener.hpp>

class GetEntitys: public NetworkListener {
public:

    GetEntitys();

    char *onPacket(char *request, ICommandSender *sender);
};


#endif //RECAST_SERVER_GETENTITYS_H
