/**
 * @file Box2DWorld.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#include "world/Box2DWorld.h"
#include <world/utils/CollectEntity.h>
#include <world/wrappers/EntityData.h>
#include "world/wrappers/SpellEntity.h"

static const float32 WIDTH_CHUNK = 50.0f;
static const float32 STEP_TIME = 1.0f / 60.0f;
static const int32 POS_ITERRATION_PER_CALCULATE = 10;
static const int32 VELOCITY_ITERRATION_PER_CALCULATE = 10;
static const float32 MAX_HEIGHT = 100.0f;

Box2DWorld::Box2DWorld() {
    // Создание мира с гравитацией 10g
    world = new b2World(b2Vec2(0.0f, -10.0f));
    world->SetDestructionListener(this);

    // Создание земли
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body *ground = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(WIDTH_CHUNK, 10.0f);
    ground->CreateFixture(&groundBox, 0.0f);
    existGround.insert(-1);
    existGround.insert(0);
    existGround.insert(1);
}

Box2DWorld::~Box2DWorld() {
    delete world;
}

void Box2DWorld::update() {
    world->Step(STEP_TIME, VELOCITY_ITERRATION_PER_CALCULATE, POS_ITERRATION_PER_CALCULATE);
    for (Entity *entity: needTickEntity)
        if (entity != NULL)
            entity->update(this);
}


std::vector<Entity> Box2DWorld::getAllEntityInChunk(float x1, float x2) {
    checkAndCreateGround(x1, x2);
    CollectEntity collectEntity;
    b2AABB aabb;
    aabb.lowerBound.Set(x1, -MAX_HEIGHT);
    aabb.upperBound.Set(x2, MAX_HEIGHT);
    world->QueryAABB(&collectEntity, aabb);
    return collectEntity.getEntitys();
}

void Box2DWorld::checkAndCreateGround(float x1, float x2) {
    for (float x = x1; x <= x2; x += WIDTH_CHUNK) {
        if (existGround.count(((int) (x / WIDTH_CHUNK)) + 1) == 0) {
            b2BodyDef groundBodyDef;
            groundBodyDef.position.Set((((int) (x / WIDTH_CHUNK)) * WIDTH_CHUNK) + WIDTH_CHUNK / 2, -10.0f);
            b2Body *ground = world->CreateBody(&groundBodyDef);
            b2PolygonShape groundBox;
            groundBox.SetAsBox(WIDTH_CHUNK / 2, 10.0f);
            ground->CreateFixture(&groundBox, 0.0f);
            existGround.insert(((int) (x / WIDTH_CHUNK)) + 1);
        }
    }
}

void Box2DWorld::checkAndCreateGround(float x) {
    checkAndCreateGround(x, x);
}

Entity *Box2DWorld::createEntity(b2BodyDef &bodyDef, b2FixtureDef &fixtureDef) {
    if (bodyDef.userData == NULL) {
        bodyDef.userData = new EntityData();
    }
    while (entitysId[freeId] != NULL)
        freeId++;
    ((EntityData *) bodyDef.userData)->id = freeId;

    b2Body *body = world->CreateBody(&bodyDef);
    Entity *entity = new Entity(body->CreateFixture(&fixtureDef));
    entitysId[freeId] = entity;
    return entity;
}

void Box2DWorld::SayGoodbye(b2Fixture *fixture) {
    EntityData *data = (EntityData *) fixture->GetUserData();
    if (data != NULL) {
        if (entitysId[data->id] != NULL) {
            needTickEntity.erase(std::remove(needTickEntity.begin(), needTickEntity.end(), entitysId[data->id]),
                                 needTickEntity.end());
            delete entitysId[data->id];
            entitysId[data->id] = NULL;
        }
        if(data->spellEntity != NULL){
            data->spellEntity = NULL;
        }
        delete data;
    }
}

SpellEntity *Box2DWorld::createSpellEntity(b2Vec2 &position, Spell *spell) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    EntityData *data = new EntityData();
    bodyDef.userData = data;

    while (entitysId[freeId] != NULL)
        freeId++;
    ((EntityData *) bodyDef.userData)->id = freeId;

    b2Body *body = world->CreateBody(&bodyDef);
    SpellEntity *entity = new SpellEntity(body->CreateFixture(&fixtureDef), spell, this);
    entitysId[freeId] = entity;
    data->spellEntity = entity;
    return (SpellEntity *) entity;
}
