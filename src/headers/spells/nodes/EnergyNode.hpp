/**
 * @file EnergyNode.h
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_ENERGYNODE_H
#define RECAST_SERVER_ENERGYNODE_H

#include "io/configs/Config.hpp"
#include "SpellNode.hpp"

class EnergyNode : public SpellNode {
public:
    EnergyNode(float x, float y, float z, float energy) : SpellNode(NodeType::ENERGY, x, y, z), energy(energy) {}

    EnergyNode(NodeType type, float x, float y, float z, float energy) : SpellNode(type, x, y, z), energy(energy) {}

    virtual bool isEnergyNode() { return true; }

    inline float getEnergy() const { return energy; }

    virtual float transferEnergy(SpellNode *from, float count);

protected:
    float energy = 0;

    virtual void onTick(IEventListener &listener, SpellNode *callable);
};


#endif //RECAST_SERVER_ENERGYNODE_H
