//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_TEMPERATUREWORLDUPDATER_H
#define RECAST_TEMPERATUREWORLDUPDATER_H


#include <memory>
#include <mutex>
#include "TemperatureWorld.h"

class TemperatureWorldUpdater {
public:
    static constexpr double kTemperatureExchangeCoefficient = 1;

    TemperatureWorldUpdater(std::shared_ptr<TemperatureWorld> world);

    void update(double minDt);

private:
    std::shared_ptr<TemperatureWorld> _world;

    void _checkThenShareTemperature(double dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ);
    void _shareTemperature(double dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ);

    double _lastUpdateTime = 0;
    std::mutex _mutex;
};


#endif //RECAST_TEMPERATUREWORLDUPDATER_H
