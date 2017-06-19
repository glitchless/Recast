//
// Created by Oleg Morozenkov on 31.05.17.
//

#include "AverageShareTemperatureWorldUpdater.h"
#include "../utils/MathUtils.h"

using namespace std;

AverageShareTemperatureWorldUpdater::AverageShareTemperatureWorldUpdater(double temperatureExchangeCoefficient,
                                                                         shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> world,
                                                                         shared_ptr<ITimer> timer)
        : _temperatureExchangeCoefficient(temperatureExchangeCoefficient)
        , _world(world)
        , _timer(timer)
{
}

void AverageShareTemperatureWorldUpdater::update() {
    const double dt = _timer->deltaFloatSeconds();

    _world->foreach([&](Coord x, Coord y, Coord z) {
        _checkThenShareTemperature(dt, x, y, z, Coord(x + Coord(1)), y, z);
        _checkThenShareTemperature(dt, x, y, z, x, Coord(y + Coord(1)), z);
        _checkThenShareTemperature(dt, x, y, z, x, y, Coord(z + Coord(1)));
    });

    _timer->update();
}

void AverageShareTemperatureWorldUpdater::_checkThenShareTemperature(double dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ) {
    if (_world->has(nextX, nextY, nextZ)) {
        _shareTemperature(dt, x, y, z, nextX, nextY, nextZ);
    }
}

void AverageShareTemperatureWorldUpdater::_shareTemperature(double dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ) {
    const Temperature currentT = _world->get(x, y, z);
    const Temperature anotherT = _world->get(nextX, nextY, nextZ);

    const Temperature averageT = Temperature((currentT + anotherT) / 2);

    const Temperature newCurrentT = MathUtils::lerp(currentT, averageT, _temperatureExchangeCoefficient * dt);
    const Temperature newAnotherT = MathUtils::lerp(anotherT, averageT, _temperatureExchangeCoefficient * dt);

    _world->set(x, y, z, newCurrentT);
    _world->set(nextX, nextY, nextZ, newAnotherT);
}
