/**
 * @file HeaterNode.h
 * @author LionZXY
 * @project Recast-server
 * @date 24.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_HEATERNODE_H
#define RECAST_SERVER_HEATERNODE_H


#include "EnergyNode.h"

class HeaterNode: public EnergyNode {
public:
    HeaterNode(float x, float y, float z, float energy);

private:
    virtual void onTick(IEventListener &listener, SpellNode *callable);
};


#endif //RECAST_SERVER_HEATERNODE_H
