/**
 * @file Node.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#include <cmath>
#include "spells/Node.h"

using namespace std;

void Node::connectNode(Node *otherNode) {
    if (connectedNodes.count(otherNode) == 0) {
        connectedNodes.insert(otherNode);
        otherNode->connectedNodes.insert(this);
    }
}

void Node::tick(Node *callable) {
    if (nowInTick)
        return;
    nowInTick = true;
    onTick(callable);
    for (Node *node : connectedNodes)
        node->tick(this);
    nowInTick = false;
}

float pSq(float var) { // Squaring
    return var * var;
}

float Node::getDistance(const Node *otherNode) const {
    return sqrt(pSq(otherNode->x - x) + pSq(otherNode->y - y) + pSq(otherNode->z - z));
}
