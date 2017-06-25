//
// Created by Oleg Morozenkov on 20.06.17.
//

#include "temperature-world/injectors/ScalingGeneratableChunkedTemperatureWorldInjector.hpp"
#include "temperature-world/implementation/BoundTemperatureWorld.hpp"
#include "temperature-world/implementation/AverageShareTemperatureWorldUpdater.hpp"
#include "temperature-world/implementation/SynchronizedBlockingTimer.hpp"
#include "temperature-world/implementation/ScalingGeneratableChunkedTemperatureWorld.hpp"
#include "temperature-world/implementation/ScalableBoundTemperatureWorld.hpp"
#include "temperature-world/implementation/ThreadedChunkedTemperatureWorldUpdater.hpp"

using namespace std;
using namespace std::chrono;
using namespace std::placeholders;

ScalingGeneratableChunkedTemperatureWorldInjector::ScalingGeneratableChunkedTemperatureWorldInjector() {
    setMinUpdateDelta(milliseconds(20));
    setTemperatureExchangeCoefficient(0.1);
    setChunkBounds(Parallelepiped(16, 16, 8));
}

bool ScalingGeneratableChunkedTemperatureWorldInjector::hasChunkBounds() const noexcept {
    return (bool) _chunkBounds;
}

Parallelepiped ScalingGeneratableChunkedTemperatureWorldInjector::chunkBounds() const {
    return *_chunkBounds;
}

void ScalingGeneratableChunkedTemperatureWorldInjector::setChunkBounds(Parallelepiped chunkBounds) {
    _chunkBounds = make_unique<Parallelepiped>(chunkBounds);
}

bool ScalingGeneratableChunkedTemperatureWorldInjector::hasTemperatureExchangeCoefficient() const noexcept {
    return (bool) _temperatureExchangeCoefficient;
}

double ScalingGeneratableChunkedTemperatureWorldInjector::temperatureExchangeCoefficient() const {
    return *_temperatureExchangeCoefficient;
}

void ScalingGeneratableChunkedTemperatureWorldInjector::setTemperatureExchangeCoefficient(double temperatureExchangeCoefficient) {
    _temperatureExchangeCoefficient = make_unique<double>(temperatureExchangeCoefficient);
}

bool ScalingGeneratableChunkedTemperatureWorldInjector::hasMinUpdateDelta() const noexcept {
    return (bool) _minUpdateDelta;
}

milliseconds ScalingGeneratableChunkedTemperatureWorldInjector::minUpdateDelta() const {
    return *_minUpdateDelta;
}

void ScalingGeneratableChunkedTemperatureWorldInjector::setMinUpdateDelta(milliseconds minUpdateDelta) {
    _minUpdateDelta = make_unique<milliseconds>(minUpdateDelta);
}

shared_ptr<ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkableMutable<ITemperatureWorldChunkable<ITemperatureWorld>>>>>
ScalingGeneratableChunkedTemperatureWorldInjector::world() {
    if (!_world) {
        _makeWorld();
    }
    return _world;
}

shared_ptr<IUpdater> ScalingGeneratableChunkedTemperatureWorldInjector::updater() {
    if (!_updater) {
        _makeUpdater();
    }
    return _updater;
}

shared_ptr<ITimerBlockable<ITimer>> ScalingGeneratableChunkedTemperatureWorldInjector::timer() {
    if (!_timer) {
        _makeTimer();
    }
    return _timer;
}

void ScalingGeneratableChunkedTemperatureWorldInjector::_makeWorld() {
    using T = remove_reference_t<decltype(*_world)>;
    _world = dynamic_pointer_cast<T>(make_shared<ScalingGeneratableChunkedTemperatureWorld>(
            &_needChunkFn,
            bind(&_makeChunkFn, chunkBounds(), _1, _2, _3),
            chunkBounds()));
    assert(_world != nullptr);
}

void ScalingGeneratableChunkedTemperatureWorldInjector::_makeUpdater() {
    using T = remove_reference_t<decltype(*_updater)>;
    _updater = dynamic_pointer_cast<T>(make_shared<ThreadedChunkedTemperatureWorldUpdater>(
            world(),
            bind(&_makeChunkUpdaterFn, temperatureExchangeCoefficient(), timer(), _1)));
    assert(_updater != nullptr);
}

void ScalingGeneratableChunkedTemperatureWorldInjector::_makeTimer() {
    using T = remove_reference_t<decltype(*_timer)>;
    _timer = dynamic_pointer_cast<T>(make_shared<SynchronizedBlockingTimer>(minUpdateDelta()));
    assert(_timer != nullptr);
}

bool ScalingGeneratableChunkedTemperatureWorldInjector::_needChunkFn(Coord x, Coord y, Coord z) noexcept {
    return true;
}

shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> ScalingGeneratableChunkedTemperatureWorldInjector::_makeChunkFn(Parallelepiped baseChunkBounds, Coord x, Coord y, Coord z) {
    Coord minX = (int) (x / baseChunkBounds.sizeX()) * baseChunkBounds.sizeX();
    Coord minY = (int) (y / baseChunkBounds.sizeY()) * baseChunkBounds.sizeY();
    Coord minZ = (int) (z / baseChunkBounds.sizeZ()) * baseChunkBounds.sizeZ();
    Coord maxX = minX + baseChunkBounds.sizeX() - 1;
    Coord maxY = minY + baseChunkBounds.sizeY() - 1;
    Coord maxZ = minZ + baseChunkBounds.sizeZ() - 1;
    Parallelepiped chunkBounds(minX, maxX, minY, maxY, minZ, maxZ);
    return make_shared<ScalableBoundTemperatureWorld>(chunkBounds);
}

shared_ptr<IUpdaterTemperatureWorldSemiChunkUpdatable<IUpdater>> ScalingGeneratableChunkedTemperatureWorldInjector::_makeChunkUpdaterFn(double temperatureExchangeCoefficient, shared_ptr<ITimerBlockable<ITimer>> timer, shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    return make_shared<AverageShareTemperatureWorldUpdater>(temperatureExchangeCoefficient, chunk, timer);
}
