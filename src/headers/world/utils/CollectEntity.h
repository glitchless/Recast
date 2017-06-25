/**
 * @file CollectEntity.h
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_COLLECTENTITY_H
#define RECAST_SERVER_COLLECTENTITY_H

#include <vector>
#include <Box2D/Box2D.h>
#include "world/wrappers/Entity.h"

class CollectEntity : public b2QueryCallback {
public:
    bool ReportFixture(b2Fixture *fixture) {
        b2Body *body = fixture->GetBody();
        entitys.push_back(Entity(fixture));

        // Return true to continue the query.
        return true;
    }

    std::vector<Entity> getEntitys() const { return entitys; }

private:
    std::vector<Entity> entitys;
};


#endif //RECAST_SERVER_COLLECTENTITY_H
