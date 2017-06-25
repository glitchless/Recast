/**
 * @file SpellEventListener.h
 * @author LionZXY
 * @project Recast-server
 * @date 24.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_SPELLEVENTLISTENER_H
#define RECAST_SERVER_SPELLEVENTLISTENER_H

#include "IEventListener.hpp"

class Spell;
class SpellEntity;

class SpellEventListener : public IEventListener{
public:
    SpellEventListener(SpellEntity *entity, Box2DWorld *world) : spell(spell), entity(entity), world(world) {}

    void onEvent(IEvent event);

private:
    Spell *spell;
    SpellEntity *entity;
    Box2DWorld *world;
};


#endif //RECAST_SERVER_SPELLEVENTLISTENER_H
