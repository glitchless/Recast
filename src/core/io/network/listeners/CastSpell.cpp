/**
 * @file CastSpell.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 28.06.17
 * @email nikita@kulikof.ru
 **/
#include "io/network/listeners/CastSpell.h"

CastSpell::CastSpell() : NetworkListener(2) {}

char *CastSpell::onPacket(char *request, ICommandSender *sender) {
    //TODO

    return NULL;
}
