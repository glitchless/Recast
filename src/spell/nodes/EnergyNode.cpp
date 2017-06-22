/**
 * @file EnergyNode.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#include "spells/nodes/EnergyNode.h"

using namespace std;

void EnergyNode::onTick(IEventListener &listener, Node *callable) {
    float oldEnergy = energy;
    EnergyNode *tmp;
    for (Node *node : connectedNodes) {
        if (node->isEnergyNode()) {
            tmp = (EnergyNode *) node;
            if (tmp->getEnergy() < oldEnergy) {
                float energyTransfer = ((oldEnergy - tmp->getEnergy()) *
                                        Config::g("spell.general.max_transfer", 0.1F));

                energy -= tmp->transferEnergy(this, energyTransfer);
            }
        }
    }
}

float EnergyNode::transferEnergy(Node *from, float count) {
    float transactionTax = getDistance(from) * Config::g("spell.general.tax",
                                                         0.001F);
    if (transactionTax >= count) {
        return count;
    }
    energy += count - transactionTax;
    return count;
}
