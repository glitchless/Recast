//
// Created by Oleg Morozenkov on 30.03.17.
//

#include "TemperatureWorldUpdater.h"
#include "MathUtils.h"
#include "TimeUtils.h"

TemperatureWorldUpdater::TemperatureWorldUpdater(std::shared_ptr<TemperatureWorld> world) : _world(world) {
}

void TemperatureWorldUpdater::update() {
    if (_lastUpdateTime == 0) {
        const long long int now = TimeUtils::currentTimeMillis();
        const double deltaMillis = (double) now - _lastUpdateTime;
        update((float) (deltaMillis / 1000));
    } else {
        update(1);
    }
}

void TemperatureWorldUpdater::update(float dt) {
    for (Coord x = _world->getMinX(); x <= _world->getMaxX(); x++) {
        for (Coord y = _world->getMinY(); y <= _world->getMaxY(); y++) {
            for (Coord z = _world->getMinZ(); z <= _world->getMaxZ(); z++) {
                _checkThenShareTemperature(dt, x, y, z, x + 1, y, z);
                _checkThenShareTemperature(dt, x, y, z, x, y + 1, z);
                _checkThenShareTemperature(dt, x, y, z, x, y, z + 1);
            }
        }
    }
    _lastUpdateTime = TimeUtils::currentTimeMillis();
}

void TemperatureWorldUpdater::_checkThenShareTemperature(float dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ) {
    if (nextX <= _world->getMaxX() && nextY <= _world->getMaxY() && nextZ <= _world->getMaxZ()) {
        _shareTemperature(dt, x, y, z, nextX, nextY, nextZ);
    }
}

void TemperatureWorldUpdater::_shareTemperature(float dt, Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ) {
    Temperature currentT = _world->get(x, y, z);
    Temperature anotherT = _world->get(nextX, nextY, nextZ);
    Temperature avgT = (currentT + anotherT) / 2;
    _world->set(x, y, z, MathUtils::lerp(currentT, avgT, kTemperatureExchangeCoefficient * dt));
    _world->set(nextX, nextY, nextZ, MathUtils::lerp(anotherT, avgT, kTemperatureExchangeCoefficient * dt));
}
