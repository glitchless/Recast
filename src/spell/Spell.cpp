/**
 * @file Spell.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 21.06.17
 * @email nikita@kulikof.ru
 **/
#include "spells/Spell.h"


void Spell::tickSpell() {
    //rootNode->tick()
}

Spell::~Spell() {
    delete rootNode;
}
