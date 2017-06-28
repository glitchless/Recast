/**
 * @file Entity.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#include <Box2D/Box2D.h>
#include <world/wrappers/EntityData.h>
#include "world/wrappers/Entity.h"

int Entity::getId() {
    if (data != NULL)
        return data->id;
    else return -1;
}

Entity::Entity(b2Fixture *fixture1) : fixture(fixture1) {
    data = (EntityData *) fixture->GetBody()->GetUserData();
}

void Entity::write(Parcel &in, Entity *obj) {
    //TODO
}

EntityType Entity::getType() const {
    if (data == NULL)
        return EntityType::UNKN;
    return data->type;
}

void Entity::setType(EntityType type)  {
    if (data == NULL)
        return;
    else data->type = type;
}
