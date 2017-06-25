/**
 * @file Box2DWorld.h
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_BOX2DWORLD_H
#define RECAST_SERVER_BOX2DWORLD_H

#include <vector>
#include <set>
#include <unordered_map>
#include "world/wrappers/Entity.h"
#include <Box2D/Box2D.h>

class Spell;
class SpellEntity;

class Box2DWorld : public b2DestructionListener {
public:
    Box2DWorld();

    ~Box2DWorld();

    void update();

    std::vector<Entity> getAllEntityInChunk(float x1, float x2);

    Entity *createEntity(b2BodyDef &bodyDef, b2FixtureDef &fixtureDef);

    SpellEntity *createSpellEntity(b2Vec2 &position, Spell *spell);

    void subscribeToUpdate(Entity *entity) { needTickEntity.push_back(entity); }

    void SayGoodbye(b2Fixture *fixture);

    void SayGoodbye(b2Joint *joint) {}

private:
    b2World *world;
    std::set<int> existGround; // Костыль божественной мощи
    std::vector<Entity *> needTickEntity;
    std::unordered_map<int, Entity *> entitysId;

    int freeId = 0;

    void checkAndCreateGround(float x1, float x2);

    void checkAndCreateGround(float x);
};


#endif //RECAST_SERVER_BOX2DWORLD_H
