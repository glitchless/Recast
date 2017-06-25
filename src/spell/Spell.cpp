/**
 * @file Spell.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 21.06.17
 * @email nikita@kulikof.ru
 **/
#include <boost/log/trivial.hpp>
#include <spells/Spell.hpp>

void Spell::tickSpell(SpellEventListener &listener) {
    rootNode->tick(listener, NULL);
}

Spell::~Spell() {
    delete rootNode;
}
