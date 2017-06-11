//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H
#define RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H


#include <memory>
#include <fruit/fruit.h>
#include "../interfaces/ITemperatureWorldUpdater.h"
#include "../interfaces/IBoundTemperatureWorld.h"
#include "../interfaces/ITimer.h"
#include "../annotations/TemperatureWorldUpdaterAnnotations.h"

class AverageShareTemperatureWorldUpdater : public ITemperatureWorldUpdater {
public:
    INJECT(AverageShareTemperatureWorldUpdater(
            ANNOTATED(TemperatureWorldUpdaterAnnotations::TemperatureExchangeCoefficient, double) temperatureExchangeCoefficient,
            std::shared_ptr<IBoundTemperatureWorld> world,
            std::shared_ptr<ITimer> timer));

    void update() override;

private:
    void _checkThenShareTemperature(double dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ);

    void _shareTemperature(double dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ);

    double _temperatureExchangeCoefficient;
    std::shared_ptr<IBoundTemperatureWorld> _world;
    std::shared_ptr<ITimer> _timer;
};


#endif //RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H
