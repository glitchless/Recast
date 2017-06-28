/**
 * @file CastSpell.h
 * @author LionZXY
 * @project Recast-server
 * @date 28.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_CASTSPELL_H
#define RECAST_SERVER_CASTSPELL_H


#include <io/network/NetworkListener.hpp>

class CastSpell : public NetworkListener {
public:
    CastSpell();

    char *onPacket(char *request, ICommandSender *sender);
};


#endif //RECAST_SERVER_CASTSPELL_H
