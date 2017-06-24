/**
 * @file Node.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#include <cmath>
#include "spells/nodes/SpellNode.h"

using namespace std;

void SpellNode::connectNode(SpellNode *otherNode) {
    if (connectedNodes.count(otherNode) == 0) {
        connectedNodes.insert(otherNode);
        otherNode->connectedNodes.insert(this);
    }
}

void SpellNode::tick(IEventListener &listener, SpellNode *callable) {
    if (nowInTick)
        return;
    nowInTick = true;
    onTick(listener, callable);
    for (SpellNode *node : connectedNodes)
        node->tick(listener, this);
    nowInTick = false;
}

float pSq(float var) { // Squaring
    return var * var;
}

float SpellNode::getDistance(const SpellNode *otherNode) const {
    return sqrt(pSq(otherNode->x - x) + pSq(otherNode->y - y) + pSq(otherNode->z - z));
}

SpellNode::~SpellNode() {
    nowInTick = true;
    for (SpellNode *node : connectedNodes)
        if (!node->nowInTick)
            delete node;
    nowInTick = false;
}
