/**
 * @file SpellEventListener.h
 * @author LionZXY
 * @project Recast-server
 * @date 24.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_SPELLEVENTLISTENER_H
#define RECAST_SERVER_SPELLEVENTLISTENER_H

#include "IEventListener.h"

class Spell;

class SpellEventListener : public IEventListener {
public:
    SpellEventListener(Spell *spell) : spell(spell) {}

    void onEvent(IEvent event);

private:
    Spell *spell;
};


#endif //RECAST_SERVER_SPELLEVENTLISTENER_H
