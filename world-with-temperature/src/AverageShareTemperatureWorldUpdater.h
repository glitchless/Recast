//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H
#define RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H


#include <memory>
#include "ITemperatureWorldUpdater.h"
#include "IBoundTemperatureWorld.h"
#include "ITimer.h"

class AverageShareTemperatureWorldUpdater : public ITemperatureWorldUpdater {
public:
    AverageShareTemperatureWorldUpdater(std::shared_ptr<IBoundTemperatureWorld> world, double temperatureExchangeCoefficient, std::shared_ptr<ITimer> _timer);

    void update() override;

private:
    void _checkThenShareTemperature(double dt, CoordX x, CoordY y, CoordZ z, CoordX nextX, CoordY nextY, CoordZ nextZ);
    void _shareTemperature(double dt, CoordX x, CoordY y, CoordZ z, CoordX nextX, CoordY nextY, CoordZ nextZ);

    std::shared_ptr<IBoundTemperatureWorld> _world;
    double _temperatureExchangeCoefficient;
    std::shared_ptr<ITimer> _timer;
};


#endif //RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H
