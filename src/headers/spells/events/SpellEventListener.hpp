/**
 * @file SpellEventListener.h
 * @author LionZXY
 * @project Recast-server
 * @date 24.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_SPELLEVENTLISTENER_H
#define RECAST_SERVER_SPELLEVENTLISTENER_H

#include <Server.hpp>
#include "IEventListener.hpp"

class Spell;

class SpellEntity;

class SpellEventListener : public IEventListener {
public:
    SpellEventListener(Spell *spell, SpellEntity *entity, Box2DWorld *world, std::shared_ptr<TempWorld> tempWorld)
            : spell(spell),
              entity(entity),
              world(world),
              tempWorld(tempWorld) {}

    void onEvent(IEvent &event);

private:
    Spell *spell;
    SpellEntity *entity;
    Box2DWorld *world;
    std::shared_ptr<TempWorld> tempWorld;
};


#endif //RECAST_SERVER_SPELLEVENTLISTENER_H
