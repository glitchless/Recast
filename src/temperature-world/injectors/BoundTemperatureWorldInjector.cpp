//
// Created by Oleg Morozenkov on 20.06.17.
//

#include "temperature-world/injectors/BoundTemperatureWorldInjector.hpp"
#include "temperature-world/implementation/BoundTemperatureWorld.hpp"
#include "temperature-world/implementation/AverageShareTemperatureWorldUpdater.hpp"
#include "temperature-world/implementation/SynchronizedBlockingTimer.hpp"

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

shared_ptr<ITimerBlockable<ITimer>> BoundTemperatureWorldInjector::timer() {
    if (!_timer) {
        _makeTimer();
    }
    return _timer;
}

void BoundTemperatureWorldInjector::_makeWorld() {
    using T = remove_reference_t<decltype(*_world)>;
    _world = dynamic_pointer_cast<T>(make_shared<BoundTemperatureWorld>(worldBounds()));
    assert(_world != nullptr);
}

void BoundTemperatureWorldInjector::_makeUpdater() {
    using T = remove_reference_t<decltype(*_updater)>;
    _updater = dynamic_pointer_cast<T>(make_shared<AverageShareTemperatureWorldUpdater>(temperatureExchangeCoefficient(), world(), timer()));
    assert(_updater != nullptr);
}

void BoundTemperatureWorldInjector::_makeTimer() {
    using T = remove_reference_t<decltype(*_timer)>;
    _timer = dynamic_pointer_cast<T>(make_shared<SynchronizedBlockingTimer>(minUpdateDelta()));
    assert(_timer != nullptr);
}
