/**
 * @file EnergyNode.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#include "spells/nodes/EnergyNode.hpp"

using namespace std;
/**
 * Каждый тик мы рапределяем почти равномерно энергию между всеми дочерними нодами. Энергия переливается только в том случае, если её где-то меньше чем в текущей ноде.
 * По умолчанию размер пакета = (Энергия текущего пакета - Энергия дочернего пакета) * 0.1 (10% от транзакции)
 * Каждая передача энергии сопровождается потерей. В контексте проекта это называется налог на энергию (energy tax). Это приводит к тому,
 * что энергия не вечна и рано или поздно пропадет из плетения.
 *
 * @param listener Вся передача событий из заклинания наружу происходит с помощью Event'ов
 * @param callable Вызывающая нода. Пока не пригождается, но мало ли. Может быть NULL
 */
void EnergyNode::onTick(IEventListener &listener, SpellNode *callable) {
    float oldEnergy = energy;
    EnergyNode *tmp;
    for (SpellNode *node : connectedNodes) {
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
/**
 *
 * Передавать энергию ноде можно ТОЛЬКО через этот метод!!! Ни в коем случае не передавать энергию через node->energy+=10;
 * Сам метод так же не высчитывает из родительской ноды энергию на передачу. Он возвращает сколько энергии ему удалось забрать
 *
 * @param from Из какой ноды энергия
 * @param count Количество передаваемой энергии
 * @return Сколько энергии передалось фактически (нормальным считается @example node->energy -= otherNode->transferEnergy(node,10);)
 */
float EnergyNode::transferEnergy(SpellNode *from, float count) {
    float transactionTax = getDistance(from) * Config::g("spell.general.tax",
                                                         0.001F);
    if (transactionTax >= count) {
        return count;
    }
    energy += count - transactionTax;
    return count;
}
