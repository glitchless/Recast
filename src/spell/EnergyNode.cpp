/**
 * @file EnergyNode.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#include "spells/EnergyNode.h"

using namespace std;

void EnergyNode::onTick(Node *callable) {
    float oldEnergy = energy;
    EnergyNode *tmp;
    for (Node *node : connectedNodes) {
        if (node->isEnergyNode()) {
            tmp = (EnergyNode *) node;
            if (tmp->getEnergy() < oldEnergy) {
                float energyTransfer = ((oldEnergy - tmp->getEnergy()) *
                                        MAX_TRANSFER);

                energy -= tmp->transferEnergy(this, energyTransfer);
            }
        }
    }
}

float EnergyNode::transferEnergy(Node *from, float count) {
    float transactionTax = getDistance(from) * TAX_ENERGY_TRANSACTION_PER_COORD;
    if (transactionTax >= count) {
        return count;
    }
    energy += count - transactionTax;
    return count;
}
