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
#include "interfaces/ITemperatureWorldChunkableObservable.hpp"

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
    std::shared_ptr<ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkable<ITemperatureWorld>>>> world();

    /**
     * Temperature world updater will be built only once for an injector instance. You can get the world via `world` getter.
     *
     * @return Built chunked temperature world updater.
     */
    std::shared_ptr<IUpdater> updater();

    /**
     * Timer will be built only once for an injector instance.
     *
     * @return Built blocking timer which is used in the world updater.
     */
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

    std::shared_ptr<ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkable<ITemperatureWorld>>>> _world;
    std::shared_ptr<IUpdater> _updater;
    std::shared_ptr<ITimer> _timer;
};


#endif //RECAST_SCALINGGENERATABLECHUNKEDTEMPERATUREWORLDINJECTOR_H
