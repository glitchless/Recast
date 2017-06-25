/**
 * @file SpellEntity.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#include <Box2D/Box2D.h>
#include "world/wrappers/SpellEntity.h"

SpellEntity::SpellEntity(b2Fixture *fixture1, Spell *spell) : Entity(fixture1), spell(spell) {}

void SpellEntity::update(Box2DWorld *box2DWorld) {
    spell->tickSpell();
}

SpellEntity::~SpellEntity() {
    delete spell;
}
