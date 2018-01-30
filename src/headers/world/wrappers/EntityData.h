/**
 * @file EntityData.h
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_ENTITYDATA_H
#define RECAST_SERVER_ENTITYDATA_H

#include "EntityType.h"

class SpellEntity;

class EntityData {
public:
    int id = -1;
    SpellEntity *spellEntity = NULL;
    EntityType type = EntityType::UNKN;
};


#endif //RECAST_SERVER_ENTITYDATA_H
