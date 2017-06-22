/**
 * @file Node.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#include <cmath>
#include "spells/nodes/Node.h"

using namespace std;

void Node::connectNode(Node *otherNode) {
    if (connectedNodes.count(otherNode) == 0) {
        connectedNodes.insert(otherNode);
        otherNode->connectedNodes.insert(this);
    }
}

void Node::tick(IEventListener &listener, Node *callable) {
    if (nowInTick)
        return;
    nowInTick = true;
    onTick(listener, callable);
    for (Node *node : connectedNodes)
        node->tick(listener, this);
    nowInTick = false;
}

float pSq(float var) { // Squaring
    return var * var;
}

float Node::getDistance(const Node *otherNode) const {
    return sqrt(pSq(otherNode->x - x) + pSq(otherNode->y - y) + pSq(otherNode->z - z));
}

Node::~Node() {
    nowInTick = true;
    for (Node *node : connectedNodes)
        if (!node->nowInTick)
            delete node;
    nowInTick = false;
}
