/**
 * @file HeatEvent.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 27.06.17
 * @email nikita@kulikof.ru
 **/
#include "spells/events/HeatEvent.hpp"
#include "world/wrappers/SpellEntity.h"
#include "spells/nodes/SpellNode.hpp"

void HeatEvent::commit(Box2DWorld *world, SpellEntity *entity, std::shared_ptr<TempWorld> tempWorld) {
    float per_real_metr = Config::g("spell.general.per_real", 0.001f);
    b2Vec2 loc = entity->getFixture()->GetBody()->GetPosition();
    Coord newX((int) (loc.x + getNode()->getX() * per_real_metr));
    Coord newY((int) (loc.y + getNode()->getY() * per_real_metr));
    Coord newZ((int) (getNode()->getZ() * per_real_metr));

    tempWorld->set(newX, newY, newZ, Temperature(tempWorld->get(newX, newY, newZ) + temp));
    entity->setType(EntityType::FIREBALL);
}
