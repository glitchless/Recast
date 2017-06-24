/**
 * @file SpellEventListener.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 24.06.17
 * @email nikita@kulikof.ru
 **/
#include "spells/events/SpellEventListener.h"

void SpellEventListener::onEvent(IEvent event) {
    event.commit();
}
