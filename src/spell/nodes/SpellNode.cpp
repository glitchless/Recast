/**
 * @file Node.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#include <cmath>
#include <spells/nodes/HeaterNode.hpp>
#include <spells/nodes/AimNode.h>
#include <spells/nodes/GeneratorNode.h>

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


float pSqu(float var) { // Возведение в квадрат
    return var * var;
}

/**
 * Получение расстояния от одной ноды до другой
 *
 * @param otherNode
 * @return
 */
float SpellNode::getDistance(const SpellNode *otherNode) const {
    return sqrt(pSqu(otherNode->x - x) + pSqu(otherNode->y - y) + pSqu(otherNode->z - z));
}

SpellNode::~SpellNode() {
    nowInTick = true;
    for (SpellNode *node : connectedNodes)
        if (!node->nowInTick)
            delete node;
    nowInTick = false;
}

void SpellNode::iterrator(std::function<void(SpellNode *)> next) {
    nowInTick = true;
    next(this);
    for (SpellNode *node : connectedNodes)
        if (!node->nowInTick)
            node->iterrator(next);
    nowInTick = false;
}

void SpellNode::write(Parcel &in, SpellNode *obj) {
    in.put(obj->getType());
    in.put(obj->x);
    in.put(obj->y);
    in.put(obj->z);
}

SpellNode *SpellNode::read(Parcel &out) {
    NodeType type = (NodeType) out.readInt();
    float x = out.readFloat();
    float y = out.readFloat();
    float z = out.readFloat();
    SpellNode *node;
    switch (type) {
        case NodeType::USUALLY: {
            node = new SpellNode(type, x, y, z);
            break;
        }
        case NodeType::HEATER: {
            node = new HeaterNode(x, y, z, 0);
            break;
        }
        case NodeType::ENERGY: {
            node = new EnergyNode(x, y, z, 0);
            break;
        }
        case NodeType::AIM: {
            int id = out.readInt();
            node = new AimNode(x, y, z, 0, id);
            break;
        }
        case NodeType::GENERATOR: {
            node = new GeneratorNode(x, y, z, 0);
            break;
        }
        default:
            node = NULL;
    }
    return node;
}

