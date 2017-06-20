//
// Created by Oleg Morozenkov on 20.06.17.
//

#ifndef RECAST_SCALINGGENERATABLECHUNKEDTEMPERATUREWORLDINJECTOR_H
#define RECAST_SCALINGGENERATABLECHUNKEDTEMPERATUREWORLDINJECTOR_H


#include <chrono>
#include <memory>
#include "../types/Parallelepiped.h"
#include "../interfaces/IUpdater.h"
#include "../interfaces/ITimer.h"
#include "../interfaces/ITemperatureWorld.h"
#include "../interfaces/ITemperatureWorldBoundable.h"
#include "../interfaces/ITemperatureWorldChunkable.h"
#include "../interfaces/ITemperatureWorldChunkableGeneratable.h"
#include "../interfaces/ITemperatureWorldChunkableGeneratableObservable.h"

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
