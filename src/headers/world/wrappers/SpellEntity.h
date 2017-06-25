/**
 * @file SpellEntity.h
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_SPELLENTITY_H
#define RECAST_SERVER_SPELLENTITY_H


#include <spells/Spell.hpp>
#include "Entity.h"

class SpellEntity : public Entity {
public:
    SpellEntity(b2Fixture *fixture1, Spell *spell);
    ~SpellEntity();
    void update(Box2DWorld *box2DWorld);

private:
    Spell * spell;
};


#endif //RECAST_SERVER_SPELLENTITY_H
