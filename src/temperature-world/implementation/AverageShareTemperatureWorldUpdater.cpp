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
    const double dt = _timer->deltaFloatSeconds();

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
    if (_nearDownChunk) {
        _world->foreachCellOnEdge(Edge::DOWN, [&](Coord x, Coord y, Coord z) {
            _shareTemperature(dt, _world, x, y, z, _nearDownChunk, x, _world->nextCoordY(y), z);
        });
    }
    if (_nearFarChunk) {
        _world->foreachCellOnEdge(Edge::FAR, [&](Coord x, Coord y, Coord z) {
            _shareTemperature(dt, _world, x, y, z, _nearDownChunk, x, y, _world->nextCoordZ(z));
        });
    }

    _timer->update();
}

bool AverageShareTemperatureWorldUpdater::canAddNearChunk(Edge edge, const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& chunk) const noexcept {
    return (edge == Edge::RIGHT && !_nearRightChunk && _world->nextCoordX(_world->bounds().maxX()) >= chunk->bounds().minX()) ||
           (edge == Edge::DOWN && !_nearDownChunk && _world->nextCoordY(_world->bounds().maxY()) >= chunk->bounds().minY()) ||
           (edge == Edge::FAR && !_nearFarChunk && _world->nextCoordZ(_world->bounds().maxZ()) >= chunk->bounds().minZ());
}

void AverageShareTemperatureWorldUpdater::addNearChunk(Edge edge, std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    assert(canAddNearChunk(edge, chunk));
    if (edge == Edge::RIGHT) {
        _nearRightChunk = chunk;
    } else if (edge == Edge::DOWN) {
        _nearDownChunk = chunk;
    } else if (edge == Edge::FAR) {
        _nearFarChunk = chunk;
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

    const Temperature averageT = Temperature((currentT + anotherT) / 2);

    const Temperature newCurrentT = MathUtils::lerp(currentT, averageT, _temperatureExchangeCoefficient * dt);
    const Temperature newAnotherT = MathUtils::lerp(anotherT, averageT, _temperatureExchangeCoefficient * dt);

    firstWorld->set(x, y, z, newCurrentT);
    secondWorld->set(nextX, nextY, nextZ, newAnotherT);
}
