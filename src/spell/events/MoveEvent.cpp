/**
 * @file MoveEvent.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#include <io/configs/Config.hpp>
#include "spells/events/MoveEvent.h"
#include "world/wrappers/SpellEntity.h"

float pSq(float var) { // Возведение в квадрат
    return var * var;
}

void MoveEvent::commit(Box2DWorld *world, SpellEntity * entity) {
    double k = Config::g("spell.event.move.density_k", 0.001); // Коэфициент сжатия силовой пружины
    Entity *target = world->getEntityById(entityId);
    if(target == NULL)
        return;

    b2Vec2 pos1 = entity->getFixture()->GetBody()->GetPosition();
    b2Vec2 pos2 = target->getFixture()->GetBody()->GetPosition();

    float xInSquare = pSq(pos1.x - pos2.x) + pSq(pos1.y - pos2.y);
    float force = (float) (xInSquare * k * energy); // Формула F=kx^2

    float distance = sqrt(xInSquare);
    b2Vec2 forceVec;
    forceVec.x = (abs(pos1.x - pos2.x) / distance) /*cos*/ * force;
    forceVec.y = (abs(pos2.y - pos2.y) / distance) /*sin*/ * force;

    entity->getFixture()->GetBody()->ApplyForceToCenter(forceVec, true);
}
