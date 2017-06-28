/**
 * @file DelayedSpellCreate.h
 * @author LionZXY
 * @project Recast-server
 * @date 28.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_DELAYEDSPELLCREATE_H
#define RECAST_SERVER_DELAYEDSPELLCREATE_H


#include <Box2D/Common/b2Math.h>
#include <world/wrappers/Entity.h>
#include <spells/Spell.hpp>

class DelayedSpellCreate {
public:
    DelayedSpellCreate(b2Vec2 pos, Spell *spell) : pos(pos), spell(spell) {}

    b2Vec2 getPos() { return pos; }

    Spell *getSpell() { return spell; }

private:
    b2Vec2 pos;
    Spell *spell;
};


#endif //RECAST_SERVER_DELAYEDSPELLCREATE_H
