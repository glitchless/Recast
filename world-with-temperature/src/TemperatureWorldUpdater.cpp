//
// Created by Oleg Morozenkov on 30.03.17.
//

#include "TemperatureWorldUpdater.h"
#include "MathUtils.h"

TemperatureWorldUpdater::TemperatureWorldUpdater(std::shared_ptr<TemperatureWorld> world) : _world(world) {
}

void TemperatureWorldUpdater::update(float dt) {
    for (Coord x = _world->getMinX(); x <= _world->getMaxX(); x++) {
        for (Coord y = _world->getMinY(); y <= _world->getMaxY(); y++) {
            for (Coord z = _world->getMinZ(); z <= _world->getMaxZ(); z++) {
                _checkThenShareTemperature(x, y, z, x + 1, y, z);
                _checkThenShareTemperature(x, y, z, x, y + 1, z);
                _checkThenShareTemperature(x, y, z, x, y, z + 1);
            }
        }
    }
}

void TemperatureWorldUpdater::_checkThenShareTemperature(Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ) {
    if (nextX <= _world->getMaxX() && nextY <= _world->getMaxY() && nextZ <= _world->getMaxZ()) {
        _shareTemperature(x, y, z, nextX, nextY, nextZ);
    }
}

void TemperatureWorldUpdater::_shareTemperature(Coord x, Coord y, Coord z, Coord nextX, Coord nextY, Coord nextZ) {
    Temperature currentT = _world->get(x, y, z);
    Temperature anotherT = _world->get(nextX, nextY, nextZ);
    Temperature avgT = (currentT + anotherT) / 2;
    _world->set(x, y, z, MathUtils::lerp(currentT, avgT, kTemperatureExchangeCoefficient));
    _world->set(nextX, nextY, nextZ, MathUtils::lerp(anotherT, avgT, kTemperatureExchangeCoefficient));
}
