//
// Created by Oleg Morozenkov on 20.06.17.
//

#ifndef RECAST_BOUNDTEMPERATUREWORLDINJECTOR_H
#define RECAST_BOUNDTEMPERATUREWORLDINJECTOR_H


#include "../interfaces/ITemperatureWorld.h"
#include "../interfaces/ITemperatureWorldBoundable.h"
#include "../interfaces/IUpdater.h"
#include "../interfaces/ITimer.h"

class BoundTemperatureWorldInjector {
public:
    BoundTemperatureWorldInjector();

    bool hasWorldBounds() const noexcept;
    Parallelepiped worldBounds() const;
    void setWorldBounds(Parallelepiped worldBounds);

    bool hasTemperatureExchangeCoefficient() const noexcept;
    double temperatureExchangeCoefficient() const;
    void setTemperatureExchangeCoefficient(double temperatureExchangeCoefficient);

    bool hasMinUpdateDelta() const noexcept;
    std::chrono::milliseconds minUpdateDelta() const;
    void setMinUpdateDelta(std::chrono::milliseconds minUpdateDelta);

    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> world();
    std::shared_ptr<IUpdater> updater();
    std::shared_ptr<ITimer> timer();

protected:
    void _makeWorld();
    void _makeUpdater();
    void _makeTimer();

    std::unique_ptr<Parallelepiped> _worldBounds;
    std::unique_ptr<double> _temperatureExchangeCoefficient;
    std::unique_ptr<std::chrono::milliseconds> _minUpdateDelta;

    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> _world;
    std::shared_ptr<IUpdater> _updater;
    std::shared_ptr<ITimer> _timer;
};


#endif //RECAST_BOUNDTEMPERATUREWORLDINJECTOR_H
