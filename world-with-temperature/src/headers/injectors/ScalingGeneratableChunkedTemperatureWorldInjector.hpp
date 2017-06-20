//
// Created by Oleg Morozenkov on 20.06.17.
//

#ifndef RECAST_SCALINGGENERATABLECHUNKEDTEMPERATUREWORLDINJECTOR_H
#define RECAST_SCALINGGENERATABLECHUNKEDTEMPERATUREWORLDINJECTOR_H


#include <chrono>
#include <memory>
#include "types/Parallelepiped.hpp"
#include "interfaces/IUpdater.hpp"
#include "interfaces/ITimer.hpp"
#include "interfaces/ITemperatureWorld.hpp"
#include "interfaces/ITemperatureWorldBoundable.hpp"
#include "interfaces/ITemperatureWorldChunkable.hpp"
#include "interfaces/ITemperatureWorldChunkableGeneratable.hpp"
#include "interfaces/ITemperatureWorldChunkableGeneratableObservable.hpp"

class ScalingGeneratableChunkedTemperatureWorldInjector {
public:
    ScalingGeneratableChunkedTemperatureWorldInjector();

    bool hasChunkBounds() const noexcept;
    Parallelepiped chunkBounds() const;
    void setChunkBounds(Parallelepiped chunkBounds);

    bool hasTemperatureExchangeCoefficient() const noexcept;
    double temperatureExchangeCoefficient() const;
    void setTemperatureExchangeCoefficient(double temperatureExchangeCoefficient);

    bool hasMinUpdateDelta() const noexcept;
    std::chrono::milliseconds minUpdateDelta() const;
    void setMinUpdateDelta(std::chrono::milliseconds minUpdateDelta);

    std::shared_ptr<ITemperatureWorldChunkableGeneratableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkable<ITemperatureWorld>>>> world();
    std::shared_ptr<IUpdater> updater();
    std::shared_ptr<ITimer> timer();

protected:
    void _makeWorld();
    void _makeUpdater();
    void _makeTimer();

    bool _needChunkFn(Coord x, Coord y, Coord z) noexcept;
    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> _makeChunkFn(Coord x, Coord y, Coord z);

    std::shared_ptr<IUpdater> _makeChunkUpdaterFn(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>);

    std::unique_ptr<Parallelepiped> _chunkBounds;
    std::unique_ptr<double> _temperatureExchangeCoefficient;
    std::unique_ptr<std::chrono::milliseconds> _minUpdateDelta;

    std::shared_ptr<ITemperatureWorldChunkableGeneratableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkable<ITemperatureWorld>>>> _world;
    std::shared_ptr<IUpdater> _updater;
    std::shared_ptr<ITimer> _timer;
};


#endif //RECAST_SCALINGGENERATABLECHUNKEDTEMPERATUREWORLDINJECTOR_H
