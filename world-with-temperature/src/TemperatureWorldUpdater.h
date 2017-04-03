//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_TEMPERATUREWORLDUPDATER_H
#define RECAST_TEMPERATUREWORLDUPDATER_H


#include <memory>
#include "TemperatureWorld.h"

class TemperatureWorldUpdater {
public:
    static const float kTemperatureExchangeCoefficient = 0.01;

    TemperatureWorldUpdater(std::shared_ptr<TemperatureWorld> world);

    void update(float dt);

private:
    std::shared_ptr<TemperatureWorld> _world;

    void _checkThenShareTemperature(Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ);
    void _shareTemperature(Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ);
};


#endif //RECAST_TEMPERATUREWORLDUPDATER_H
