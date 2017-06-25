/**
 * @file Entity.h
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_ENTITY_H
#define RECAST_SERVER_ENTITY_H

class EntityData;
class b2Fixture;
class Box2DWorld;

class Entity {
public:
    Entity(b2Fixture *fixture1);

    int getId();

    virtual void update(Box2DWorld *box2DWorld) {}

private:
    b2Fixture *fixture;
    EntityData *data;
};


#endif //RECAST_SERVER_ENTITY_H
