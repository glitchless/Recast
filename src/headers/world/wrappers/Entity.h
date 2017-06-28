/**
 * @file Entity.h
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_ENTITY_H
#define RECAST_SERVER_ENTITY_H

#include <utils/Parcel.hpp>
#include "EntityData.h"
#include "EntityType.h"

class EntityData;

class b2Fixture;

class Box2DWorld;

class Entity {
public:
    Entity(b2Fixture *fixture1);

    int getId();

    virtual void update(Box2DWorld *box2DWorld) {}

    b2Fixture *getFixture() const { return fixture; }

    static void write(Parcel &in, Entity *obj);

    EntityType getType() const;

    void setType(EntityType type);

private:
    b2Fixture *fixture;
    EntityData *data;
};


#endif //RECAST_SERVER_ENTITY_H
