//
// Created by Oleg Morozenkov on 20.06.17.
//

#ifndef RECAST_SCALINGGENERATABLECHUNKEDTEMPERATUREWORLDINJECTOR_H
#define RECAST_SCALINGGENERATABLECHUNKEDTEMPERATUREWORLDINJECTOR_H


#include <chrono>
#include <memory>
#include "temperature-world/types/Parallelepiped.hpp"
#include "temperature-world/interfaces/IUpdater.hpp"
#include "temperature-world/interfaces/IUpdaterTemperatureWorldSemiChunkUpdatable.hpp"
#include "temperature-world/interfaces/ITimer.hpp"
#include "temperature-world/interfaces/ITimerBlockable.hpp"
#include "temperature-world/interfaces/ITemperatureWorld.hpp"
#include "temperature-world/interfaces/ITemperatureWorldBoundable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkableMutable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkableGeneratable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkableObservable.hpp"

/**
 * Injector.
 * This class builds scaling chunked temperature world and its updater.
 * You must set chunk bounds via `setChunkBounds` method. These chunk bounds will be the same for all chunks. Temperature exchange coefficient and minimum update delta are set to defaults.
 */
class ScalingGeneratableChunkedTemperatureWorldInjector {
public:
    ScalingGeneratableChunkedTemperatureWorldInjector();

    /**
     * This method is exception-safe.
     *
     * @return True if chunk bounds have been set.
     */
    bool hasChunkBounds() const noexcept;

    /**
     * This method can throw an exception if chunk bounds are not set.
     *
     * @return Chunk bounds.
     */
    Parallelepiped chunkBounds() const;

    /**
     * Sets chunk bounds.
     *
     * @param chunkBounds Chunk bounds.
     */
    void setChunkBounds(Parallelepiped chunkBounds);

    /**
     * This method is exception-safe.
     *
     * @return True if temperature exchange coefficient have been set.
     */
    bool hasTemperatureExchangeCoefficient() const noexcept;

    /**
     * The more temperature exchange coefficient is, the faster temperature exchange will be.
     * This method can throw an exception if temperature exchange coefficient is not set.
     *
     * @return Temperature exchange coefficient.
     */
    double temperatureExchangeCoefficient() const;

    /**
     * Sets temperature exchange coefficient.
     * The more temperature exchange coefficient is, the faster temperature exchange will be.
     *
     * @param temperatureExchangeCoefficient Temperature exchange coefficient.
     */
    void setTemperatureExchangeCoefficient(double temperatureExchangeCoefficient);

    /**
     * This method is exception-safe.
     *
     * @return True if minimum update delta have been set.
     */
    bool hasMinUpdateDelta() const noexcept;

    /**
     * Minimum time between world updates is the minimum update delta.
     * This method can throw an exception if minimum update delta is not set.
     *
     * @return Minimum update delta.
     */
    std::chrono::milliseconds minUpdateDelta() const;

    /**
     * Sets minimum update delta.
     * Minimum time between world updates is minimum update delta.
     *
     * @param minUpdateDelta Minimum update delta.
     */
    void setMinUpdateDelta(std::chrono::milliseconds minUpdateDelta);

    /**
     * Temperature world will be built only once for an injector instance. `updater` getter uses the same world instance.
     *
     * @return Built chunked temperature world.
     */
    std::shared_ptr<ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkableMutable<ITemperatureWorldChunkable<ITemperatureWorld>>>>> world();

    /**
     * Temperature world updater will be built only once for an injector instance. You can get the world via `world` getter.
     *
     * @return Built chunked temperature world updater.
     */
    std::shared_ptr<IUpdater> updater();

    /**
     * Timer will be built on each call.
     *
     * @return Built blocking timer which is used in the world updater.
     */
    std::shared_ptr<ITimerBlockable<ITimer>> timer();

protected:
    static bool _needChunkFn(Coord x, Coord y, Coord z) noexcept;
    static std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> _makeChunkFn(Parallelepiped baseChunkBounds, Coord x, Coord y, Coord z);
    static std::shared_ptr<IUpdaterTemperatureWorldSemiChunkUpdatable<IUpdater>> _makeChunkUpdaterFn(double temperatureExchangeCoefficient, std::function<std::shared_ptr<ITimerBlockable<ITimer>>()> timerFactory, std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk);

    void _makeWorld();
    void _makeUpdater();

    std::unique_ptr<Parallelepiped> _chunkBounds;
    std::unique_ptr<double> _temperatureExchangeCoefficient;
    std::unique_ptr<std::chrono::milliseconds> _minUpdateDelta;

    std::shared_ptr<ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkableMutable<ITemperatureWorldChunkable<ITemperatureWorld>>>>> _world;
    std::shared_ptr<IUpdater> _updater;
};


#endif //RECAST_SCALINGGENERATABLECHUNKEDTEMPERATUREWORLDINJECTOR_H
