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
#include "SpellNode.h"

//static float MAX_TRANSFER = 0.1; //// SpellNode throughput (pressure simulation) energyTransfer = (oldEnergy - tmp->getEnergy()) * MAX_TRANSFER
//static float TAX_ENERGY_TRANSACTION_PER_COORD = 0.001; //// Transmission expense. Can go to a useful job (heating and stuff)

class EnergyNode : public SpellNode {
public:
    EnergyNode(float x, float y, float z, float energy) : SpellNode(x, y, z), energy(energy) {}

    virtual bool isEnergyNode() { return true; }

    inline float getEnergy() const { return energy; }

    virtual float transferEnergy(SpellNode *from, float count);

protected:
    float energy = 0;

    virtual void onTick(IEventListener &listener, SpellNode *callable);
};


#endif //RECAST_SERVER_ENERGYNODE_H
