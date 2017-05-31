//
// Created by Oleg Morozenkov on 31.05.17.
//

#include "AverageShareTemperatureWorldUpdater.h"
#include "utils/MathUtils.h"

using namespace std;

AverageShareTemperatureWorldUpdater::AverageShareTemperatureWorldUpdater(shared_ptr<IBoundTemperatureWorld> world, double temperatureExchangeCoefficient, shared_ptr<ITimer> timer) : _world(world), _temperatureExchangeCoefficient(temperatureExchangeCoefficient), _timer(timer) {
}

void AverageShareTemperatureWorldUpdater::update() {
    const double dt = _timer->deltaFloatSeconds();

    _world->foreach([&](CoordX x, CoordY y, CoordZ z) {
        _checkThenShareTemperature(dt, x, y, z, CoordX(x + CoordX(1)), y, z);
        _checkThenShareTemperature(dt, x, y, z, x, CoordY(y + CoordY(1)), z);
        _checkThenShareTemperature(dt, x, y, z, x, y, CoordZ(z + CoordZ(1)));
    });

    _timer->update();
}

void AverageShareTemperatureWorldUpdater::_checkThenShareTemperature(double dt, CoordX x, CoordY y, CoordZ z, CoordX nextX, CoordY nextY, CoordZ nextZ) {
    if (nextX <= _world->maxX() && nextY <= _world->maxY() && nextZ <= _world->maxZ()) {
        _shareTemperature(dt, x, y, z, nextX, nextY, nextZ);
    }
}

void AverageShareTemperatureWorldUpdater::_shareTemperature(double dt, CoordX x, CoordY y, CoordZ z, CoordX nextX, CoordY nextY, CoordZ nextZ) {
    const Temperature currentT = _world->get(x, y, z);
    const Temperature anotherT = _world->get(nextX, nextY, nextZ);

    const Temperature averageT = Temperature((currentT + anotherT) / 2);

    const Temperature newCurrentT = MathUtils::lerp(currentT, averageT, _temperatureExchangeCoefficient * dt);
    const Temperature newAnotherT = MathUtils::lerp(anotherT, averageT, _temperatureExchangeCoefficient * dt);

    _world->set(x, y, z, newCurrentT);
    _world->set(nextX, nextY, nextZ, newAnotherT);
}
