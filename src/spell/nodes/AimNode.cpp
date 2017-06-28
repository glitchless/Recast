/**
 * @file AimNode.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#include <spells/events/MoveEvent.h>
#include "spells/nodes/AimNode.h"


void AimNode::onTick(IEventListener &listener, SpellNode *callable) {
    float energyPerTickHeater = Config::g("spell.aim.per_tick_consumer", 10);
    if (energy > energyPerTickHeater) {
        MoveEvent event(this, entityId, energyPerTickHeater);
        listener.onEvent(event);
        energy -= energyPerTickHeater;
    }
    EnergyNode::onTick(listener, callable);
}

AimNode::AimNode(float x, float y, float z, float energy,
                 int entityId) : EnergyNode(NodeType::AIM, x, y, z, energy), entityId(entityId) {

}
