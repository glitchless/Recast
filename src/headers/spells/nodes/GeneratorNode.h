/**
 * @file GeneratorNode.h
 * @author LionZXY
 * @project Recast-server
 * @date 27.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_GENERATORNODE_H
#define RECAST_SERVER_GENERATORNODE_H


#include "EnergyNode.hpp"

class GeneratorNode : public EnergyNode {
public:
    GeneratorNode(float x, float y, float z, float energy);

private:
    virtual void onTick(IEventListener &listener, SpellNode *callable);
};


#endif //RECAST_SERVER_GENERATORNODE_H
