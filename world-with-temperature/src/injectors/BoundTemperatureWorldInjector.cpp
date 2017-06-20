//
// Created by Oleg Morozenkov on 20.06.17.
//

#include "BoundTemperatureWorldInjector.h"
#include "../implementation/BoundTemperatureWorld.h"
#include "../implementation/AverageShareTemperatureWorldUpdater.h"
#include "../implementation/SynchronizedBlockingTimer.h"

using namespace std;

bool BoundTemperatureWorldInjector::hasWorldBounds() const noexcept {
    return (bool) _worldBounds;
}

Parallelepiped BoundTemperatureWorldInjector::worldBounds() const {
    return *_worldBounds;
}

void BoundTemperatureWorldInjector::setWorldBounds(Parallelepiped worldBounds) {
    _worldBounds = make_unique(worldBounds);
}

bool BoundTemperatureWorldInjector::hasTemperatureExchangeCoefficient() const {
    return (bool) _temperatureExchangeCoefficient;
}

double BoundTemperatureWorldInjector::temperatureExchangeCoefficient() const {
    return *_temperatureExchangeCoefficient;
}

void BoundTemperatureWorldInjector::setTemperatureExchangeCoefficient(double temperatureExchangeCoefficient) {
    _temperatureExchangeCoefficient = make_unique(temperatureExchangeCoefficient);
}

bool BoundTemperatureWorldInjector::hasMinUpdateDelta() const {
    return (bool) _minUpdateDelta;
}

std::chrono::milliseconds BoundTemperatureWorldInjector::minUpdateDelta() const {
    return *_minUpdateDelta;
}

void BoundTemperatureWorldInjector::setMinUpdateDelta(std::chrono::milliseconds minUpdateDelta) {
    _minUpdateDelta = make_unique(minUpdateDelta);
}

std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> BoundTemperatureWorldInjector::world() {
    if (!_world) {
        _makeWorld();
    }
    return _world;
}

std::shared_ptr<IUpdater> BoundTemperatureWorldInjector::updater() {
    if (!_updater) {
        _makeUpdater();
    }
    return _updater;
}

std::shared_ptr<ITimer> BoundTemperatureWorldInjector::timer() {
    if (!_timer) {
        _makeTimer();
    }
    return _timer;
}

void BoundTemperatureWorldInjector::_makeWorld() {
    _world = make_shared<BoundTemperatureWorld>(worldBounds());
}

void BoundTemperatureWorldInjector::_makeUpdater() {
    _updater = make_shared<AverageShareTemperatureWorldUpdater>(temperatureExchangeCoefficient(), world(), timer());
}

void BoundTemperatureWorldInjector::_makeTimer() {
    _timer = make_shared<SynchronizedBlockingTimer>(minUpdateDelta());
}
