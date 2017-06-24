/**
 * @file HeaterNode.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 24.06.17
 * @email nikita@kulikof.ru
 **/
#include <spells/events/HeatEvent.hpp>
#include "spells/nodes/HeaterNode.hpp"

HeaterNode::HeaterNode(float x, float y, float z, float energy) : EnergyNode(x, y, z, energy) {}

void HeaterNode::onTick(IEventListener &listener, SpellNode *callable) {
    float energyPerTickHeater = Config::g("spell.heater.per_tick_consumer", 10);
    if (energy > energyPerTickHeater) {
        listener.onEvent(HeatEvent(this, HeatEvent::getTempFromEnergy(energyPerTickHeater)));
        energy -= energyPerTickHeater;
    }
    EnergyNode::onTick(listener, callable);
}

