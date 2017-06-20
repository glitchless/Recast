/**
 * @file EnergyNode.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#include "spells/EnergyNode.h"
#include <map>

using namespace std;

void EnergyNode::onTick(Node *callable) {
    map<EnergyNode *, float> needEnergy;
    EnergyNode *tmp;
    float maxEnergyTransfer = 0; // Сумма. Сколько нода может отдать дочерним нодам при избытке энергии (при наилучшем случае)
    float maxEnergy = 0;
    for (Node *node : connectedNodes) {
        if (node->isEnergyNode()) {
            tmp = (EnergyNode *) node;
            if (tmp->getEnergy() < energy && tmp->getEnergy() < tmp->getMaxCapacity()) {
                float energyTransfer = ((energy - tmp->getEnergy()) *
                                        MAX_TRANSFER); // Количество энергии, которое нода может передать максимально дочерней (при наилучшем случае)
                needEnergy[tmp] = energyTransfer;
                maxEnergyTransfer += energyTransfer;
                if (tmp->getEnergy() + energyTransfer > maxEnergy)
                    maxEnergy = tmp->getEnergy() + energyTransfer;
            }
        }
    }

    float energyAviliable = energy - maxEnergy;

    if (maxEnergyTransfer != 0) {
        for (pair<EnergyNode *, float> node : needEnergy) {
            float transferEnergy = (node.second * energyAviliable) / maxEnergyTransfer;
            if (transferEnergy > node.second)
                transferEnergy = node.second;
            energy -= node.first->transferEnergy(this, transferEnergy);
        }
    }
}

float EnergyNode::transferEnergy(Node *from, float count) {
    float transactionTax = getDistance(from) * TAX_ENERGY_TRANSACTION_PER_COORD;
    if (transactionTax >= count) {
        return count;
    }
    float aviliableEnergy = count - transactionTax; // Энергия, которая была перемещенна
    if (energy + aviliableEnergy < maxCapacity) {
        energy += aviliableEnergy;
    } else {
        float aviliable = maxCapacity - energy; // Энергия, которую мы можем впихнуть
        energy += aviliable;
        return aviliable + transactionTax;
    }
    return count;
}
