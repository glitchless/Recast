//
// Created by Oleg Morozenkov on 20.06.17.
//

#include "injectors/ScalingGeneratableChunkedTemperatureWorldInjector.hpp"
#include "implementation/BoundTemperatureWorld.hpp"
#include "implementation/AverageShareTemperatureWorldUpdater.hpp"
#include "implementation/SynchronizedBlockingTimer.hpp"
#include "implementation/ScalingGeneratableChunkedTemperatureWorld.hpp"
#include "implementation/ScalableBoundTemperatureWorld.hpp"
#include "implementation/ThreadedChunkedTemperatureWorldUpdater.hpp"

using namespace std;
using namespace std::chrono;

ScalingGeneratableChunkedTemperatureWorldInjector::ScalingGeneratableChunkedTemperatureWorldInjector() {
    setMinUpdateDelta(milliseconds(20));
    setTemperatureExchangeCoefficient(0.1);
    setChunkBounds(Parallelepiped(64, 64, 64));
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

shared_ptr<ITemperatureWorldChunkableGeneratableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkable<ITemperatureWorld>>>> ScalingGeneratableChunkedTemperatureWorldInjector::world() {
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

shared_ptr<ITimer> ScalingGeneratableChunkedTemperatureWorldInjector::timer() {
    if (!_timer) {
        _makeTimer();
    }
    return _timer;
}

void ScalingGeneratableChunkedTemperatureWorldInjector::_makeWorld() {
    _world = shared_ptr<ITemperatureWorldChunkableGeneratableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkable<ITemperatureWorld>>>>(
            (ITemperatureWorldChunkableGeneratableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkable<ITemperatureWorld>>>*) new ScalingGeneratableChunkedTemperatureWorld(
                    [&](Coord x, Coord y, Coord z) { return this->_needChunkFn(x, y, z); },
                    [&](Coord x, Coord y, Coord z) { return this->_makeChunkFn(x, y, z); },
                    chunkBounds()));
}

void ScalingGeneratableChunkedTemperatureWorldInjector::_makeUpdater() {
    _updater = shared_ptr<IUpdater>(
            (IUpdater*) new ThreadedChunkedTemperatureWorldUpdater(
                    world(),
                    [&](shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) { return this->_makeChunkUpdaterFn(chunk); }));
}

void ScalingGeneratableChunkedTemperatureWorldInjector::_makeTimer() {
    _timer = make_shared<SynchronizedBlockingTimer>(minUpdateDelta());
}

bool ScalingGeneratableChunkedTemperatureWorldInjector::_needChunkFn(Coord x, Coord y, Coord z) noexcept {
    return true;
}

shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> ScalingGeneratableChunkedTemperatureWorldInjector::_makeChunkFn(Coord x, Coord y, Coord z) {
    return make_shared<ScalableBoundTemperatureWorld>(chunkBounds());
}

shared_ptr<IUpdater> ScalingGeneratableChunkedTemperatureWorldInjector::_makeChunkUpdaterFn(shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    return make_shared<AverageShareTemperatureWorldUpdater>(temperatureExchangeCoefficient(), chunk, timer());
}
