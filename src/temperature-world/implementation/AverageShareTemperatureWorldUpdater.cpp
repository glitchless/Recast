//
// Created by Oleg Morozenkov on 31.05.17.
//

#include "temperature-world/interfaces/ITimer.hpp"
#include "temperature-world/types/Temperature.hpp"
#include "temperature-world/implementation/AverageShareTemperatureWorldUpdater.hpp"
#include "temperature-world/utils/MathUtils.hpp"

using namespace std;

AverageShareTemperatureWorldUpdater::AverageShareTemperatureWorldUpdater(double temperatureExchangeCoefficient,
                                                                         shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> world,
                                                                         shared_ptr<ITimerBlockable<ITimer>> timer)
        : _temperatureExchangeCoefficient(temperatureExchangeCoefficient)
        , _world(world)
        , _timer(timer)
{
}

void AverageShareTemperatureWorldUpdater::update() {
    if (_timer->isFirstUpdate()) {
        _timer->update();
        _timer->wait();
        return;
    }

    const double dt = _timer->deltaFloatSeconds();
    _timer->update();

    _world->foreach([&](Coord x, Coord y, Coord z) {
        _checkThenShareTemperature(dt, _world, x, y, z, _world, _world->nextCoordX(x), y, z);
        _checkThenShareTemperature(dt, _world, x, y, z, _world, x, _world->nextCoordY(y), z);
        _checkThenShareTemperature(dt, _world, x, y, z, _world, x, y, _world->nextCoordZ(z));
    });

    if (_nearRightChunk) {
        _world->foreachCellOnEdge(Edge::RIGHT, [&](Coord x, Coord y, Coord z) {
            _shareTemperature(dt, _world, x, y, z, _nearRightChunk, _world->nextCoordX(x), y, z);
        });
    }
    if (_nearUpChunk) {
        _world->foreachCellOnEdge(Edge::UP, [&](Coord x, Coord y, Coord z) {
            _shareTemperature(dt, _world, x, y, z, _nearUpChunk, x, _world->nextCoordY(y), z);
        });
    }
    if (_nearFarChunk) {
        _world->foreachCellOnEdge(Edge::FAR, [&](Coord x, Coord y, Coord z) {
            _shareTemperature(dt, _world, x, y, z, _nearFarChunk, x, y, _world->nextCoordZ(z));
        });
    }

    _timer->wait();
}

bool AverageShareTemperatureWorldUpdater::canAddNearChunk(Edge edge, const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& chunk) const noexcept {
    if (_world == chunk) {
        return false;
    }
    switch (edge) {
        case Edge::RIGHT: {
            if (_nearRightChunk) {
                return false;
            }
            Coord nextOverMaxX = _world->nextCoordX(_world->bounds().maxX());
            for (Coord y = _world->bounds().minY(); y <= _world->bounds().maxY(); y++) {
                for (Coord z = _world->bounds().minZ(); z <= _world->bounds().maxZ(); z++) {
                    if (!chunk->has(nextOverMaxX, y, z)) {
                        return false;
                    }
                }
            }
            return true;
        }
        case Edge::UP: {
            if (_nearUpChunk) {
                return false;
            }
            Coord nextOverMaxY = _world->nextCoordY(_world->bounds().maxY());
            for (Coord x = _world->bounds().minX(); x <= _world->bounds().maxX(); x++) {
                for (Coord z = _world->bounds().minZ(); z <= _world->bounds().maxZ(); z++) {
                    if (!chunk->has(x, nextOverMaxY, z)) {
                        return false;
                    }
                }
            }
            return true;
        }
        case Edge::FAR: {
            if (_nearFarChunk) {
                return false;
            }
            Coord nextOverMaxZ = _world->nextCoordZ(_world->bounds().maxZ());
            for (Coord x = _world->bounds().minX(); x <= _world->bounds().maxX(); x++) {
                for (Coord y = _world->bounds().minY(); y <= _world->bounds().maxY(); y++) {
                    if (!chunk->has(x, y, nextOverMaxZ)) {
                        return false;
                    }
                }
            }
            return true;
        }
        default: {
            return false;
        }
    }
}

void AverageShareTemperatureWorldUpdater::addNearChunk(Edge edge, std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    assert(canAddNearChunk(edge, chunk));
    switch (edge) {
        case Edge::RIGHT:
            _nearRightChunk = chunk;
            break;

        case Edge::UP:
            _nearUpChunk = chunk;
            break;

        case Edge::FAR:
            _nearFarChunk = chunk;
            break;

        default:
            break;
    }
}

void AverageShareTemperatureWorldUpdater::_checkThenShareTemperature(double dt,
                                                                     const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& firstWorld,
                                                                     Coord x, Coord y, Coord z,
                                                                     const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& secondWorld,
                                                                     Coord nextX, Coord nextY, Coord nextZ)
{
    if (secondWorld->has(nextX, nextY, nextZ)) {
        _shareTemperature(dt, firstWorld, x, y, z, secondWorld, nextX, nextY, nextZ);
    }
}

void AverageShareTemperatureWorldUpdater::_shareTemperature(double dt,
                                                            const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& firstWorld,
                                                            Coord x, Coord y, Coord z,
                                                            const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& secondWorld,
                                                            Coord nextX, Coord nextY, Coord nextZ)
{
    const Temperature currentT = firstWorld->get(x, y, z);
    const Temperature anotherT = secondWorld->get(nextX, nextY, nextZ);

    const Temperature averageT = (currentT + anotherT) / 2;

    const Temperature newCurrentT = MathUtils::lerp(currentT, averageT, _temperatureExchangeCoefficient * dt);
    const Temperature newAnotherT = MathUtils::lerp(anotherT, averageT, _temperatureExchangeCoefficient * dt);

    firstWorld->set(x, y, z, newCurrentT);
    secondWorld->set(nextX, nextY, nextZ, newAnotherT);
}
