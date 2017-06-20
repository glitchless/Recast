//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H
#define RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H


#include <memory>
#include "../interfaces/IUpdater.h"
#include "../interfaces/ITemperatureWorldBoundable.h"
#include "../interfaces/ITimer.h"

/**
 * Implementation of temperature world updater.
 *
 * How it works for every two cells:
 * 1. Computes average of temperatures of two cells.
 * 2. Brings temperature of each cell to this average world. Speed is determined by temperature exchange coefficient.
 */
class AverageShareTemperatureWorldUpdater : public IUpdater {
public:
    AverageShareTemperatureWorldUpdater(
            double temperatureExchangeCoefficient,
            std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> world,
            std::shared_ptr<ITimer> timer);

    void update() override;

protected:
    void _checkThenShareTemperature(double dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ);
    void _shareTemperature(double dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ);

    double _temperatureExchangeCoefficient;
    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> _world;
    std::shared_ptr<ITimer> _timer;
};


#endif //RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H
