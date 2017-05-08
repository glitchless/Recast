//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_TEMPERATUREWORLDUPDATER_H
#define RECAST_TEMPERATUREWORLDUPDATER_H


#include <memory>
#include "TemperatureWorld.h"

class TemperatureWorldUpdater {
public:
    static constexpr float kTemperatureExchangeCoefficient = 0.01;

    TemperatureWorldUpdater(std::shared_ptr<TemperatureWorld> world);

    void update();
    void update(float dt);

private:
    std::shared_ptr<TemperatureWorld> _world;

    void _checkThenShareTemperature(float dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ);
    void _shareTemperature(float dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ);

    long long int _lastUpdateTime = 0;
};


#endif //RECAST_TEMPERATUREWORLDUPDATER_H
