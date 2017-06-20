//
// Created by Oleg Morozenkov on 20.06.17.
//

#include "BoundTemperatureWorldInjector.h"
#include "../implementation/BoundTemperatureWorld.h"
#include "../implementation/AverageShareTemperatureWorldUpdater.h"
#include "../implementation/SynchronizedBlockingTimer.h"

using namespace std;
using namespace std::chrono;

BoundTemperatureWorldInjector::BoundTemperatureWorldInjector() {
    setMinUpdateDelta(milliseconds(20));
    setTemperatureExchangeCoefficient(0.1);
}

bool BoundTemperatureWorldInjector::hasWorldBounds() const noexcept {
    return (bool) _worldBounds;
}

Parallelepiped BoundTemperatureWorldInjector::worldBounds() const {
    return *_worldBounds;
}

void BoundTemperatureWorldInjector::setWorldBounds(Parallelepiped worldBounds) {
    _worldBounds = make_unique<Parallelepiped>(worldBounds);
}

bool BoundTemperatureWorldInjector::hasTemperatureExchangeCoefficient() const noexcept {
    return (bool) _temperatureExchangeCoefficient;
}

double BoundTemperatureWorldInjector::temperatureExchangeCoefficient() const {
    return *_temperatureExchangeCoefficient;
}

void BoundTemperatureWorldInjector::setTemperatureExchangeCoefficient(double temperatureExchangeCoefficient) {
    _temperatureExchangeCoefficient = make_unique<double>(temperatureExchangeCoefficient);
}

bool BoundTemperatureWorldInjector::hasMinUpdateDelta() const noexcept {
    return (bool) _minUpdateDelta;
}

milliseconds BoundTemperatureWorldInjector::minUpdateDelta() const {
    return *_minUpdateDelta;
}

void BoundTemperatureWorldInjector::setMinUpdateDelta(milliseconds minUpdateDelta) {
    _minUpdateDelta = make_unique<milliseconds>(minUpdateDelta);
}

shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> BoundTemperatureWorldInjector::world() {
    if (!_world) {
        _makeWorld();
    }
    return _world;
}

shared_ptr<IUpdater> BoundTemperatureWorldInjector::updater() {
    if (!_updater) {
        _makeUpdater();
    }
    return _updater;
}

shared_ptr<ITimer> BoundTemperatureWorldInjector::timer() {
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
