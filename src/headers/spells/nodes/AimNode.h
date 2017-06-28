/**
 * @file AimNode.h
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_AIMNODE_H
#define RECAST_SERVER_AIMNODE_H

#include <spells/events/IEventListener.hpp>
#include "EnergyNode.hpp"

class AimNode: public EnergyNode {
public:
    AimNode(float x, float y, float z, float energy,
                int entityId);

private:
    int entityId;
    void onTick(IEventListener &listener, SpellNode *callable);
};


#endif //RECAST_SERVER_AIMNODE_H
