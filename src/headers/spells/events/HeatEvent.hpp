/**
 * @file HeatEvent.h
 * @author LionZXY
 * @project Recast-server
 * @date 21.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_HEATEVENT_H
#define RECAST_SERVER_HEATEVENT_H

#include <io/configs/Config.hpp>
#include "IEvent.hpp"

class HeatEvent : public IEvent {
public:
    HeatEvent(SpellNode *node, float temp) : IEvent(node), temp(temp) {};

    static float getTempFromEnergy(float energyEjection) {
        return Config::g("spell.heater.temp_per_energy", 1) * energyEjection;
    }

    void commit(Box2DWorld *world, SpellEntity *entity, std::shared_ptr<TempWorld> tempWorld);

private:
    float temp;

};


#endif //RECAST_SERVER_HEATEVENT_H
