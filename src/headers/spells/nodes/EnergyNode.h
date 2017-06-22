/**
 * @file EnergyNode.h
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_ENERGYNODE_H
#define RECAST_SERVER_ENERGYNODE_H

#include "io/configs/Config.h"
#include "Node.h"

//static float MAX_TRANSFER = 0.1; //// Node throughput (pressure simulation) energyTransfer = (oldEnergy - tmp->getEnergy()) * MAX_TRANSFER
//static float TAX_ENERGY_TRANSACTION_PER_COORD = 0.001; //// Transmission expense. Can go to a useful job (heating and stuff)

class EnergyNode : public Node {
public:
    EnergyNode(float x, float y, float z, float energy) : Node(x, y, z), energy(energy) {}

    virtual bool isEnergyNode() { return true; }

    inline float getEnergy() const { return energy; }

    virtual float transferEnergy(Node *from, float count);

private:
    float energy = 0;

    void onTick(IEventListener &listener, Node *callable);
};


#endif //RECAST_SERVER_ENERGYNODE_H
