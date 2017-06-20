/**
 * @file EnergyNode.h
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_ENERGYNODE_H
#define RECAST_SERVER_ENERGYNODE_H

#include "Node.h"

const static float MAX_TRANSFER = 0.1;
const static int DEFAULT_MAX_CAPACITY = 1000;
const static float TAX_ENERGY_TRANSACTION_PER_COORD = 0.001;

class EnergyNode : public Node {
public:
    EnergyNode(float x, float y, float z, float energy) : Node(x, y, z), energy(energy) {}

    virtual bool isEnergyNode() { return true; }

    inline float getEnergy() const { return energy; }

    inline float getMaxCapacity() const { return maxCapacity; }

    virtual float transferEnergy(Node *from, float count);

private:
    float energy = 0;
    float maxCapacity = DEFAULT_MAX_CAPACITY;

    void onTick(Node *callable);
};


#endif //RECAST_SERVER_ENERGYNODE_H
