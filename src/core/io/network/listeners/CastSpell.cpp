/**
 * @file CastSpell.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 28.06.17
 * @email nikita@kulikof.ru
 **/
#include "io/network/listeners/CastSpell.h"
#include "spells/Spell.hpp"

CastSpell::CastSpell() : NetworkListener(2) {}

using namespace std;

char *CastSpell::onPacket(char *request, ICommandSender *sender) {
    Parcel parcel(vector<char>(request + 1, request + sizeof(request) / sizeof(char)));
    b2Vec2 pos(parcel.readFloat(), parcel.readFloat());
    Spell *spell = Spell::read(parcel);
    sender->getWorld()->asyncCreateSpellEntity(pos, spell);
    return (char *) "OK!";
}
