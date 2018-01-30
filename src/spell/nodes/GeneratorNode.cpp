/**
 * @file GeneratorNode.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 27.06.17
 * @email nikita@kulikof.ru
 **/
#include "spells/nodes/GeneratorNode.h"

GeneratorNode::GeneratorNode(float x, float y, float z, float energy) : EnergyNode(NodeType::GENERATOR, x, y, z,
                                                                                   energy) {

}

void GeneratorNode::onTick(IEventListener &listener, SpellNode *callable) {
    energy += Config::g("spell.generator.per_tick", 10);
    EnergyNode::onTick(listener, callable);
}
