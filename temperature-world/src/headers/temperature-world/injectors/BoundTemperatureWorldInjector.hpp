//
// Created by Oleg Morozenkov on 20.06.17.
//

#ifndef RECAST_BOUNDTEMPERATUREWORLDINJECTOR_H
#define RECAST_BOUNDTEMPERATUREWORLDINJECTOR_H

#include <memory>
#include "temperature-world/types/Parallelepiped.hpp"
#include "temperature-world/interfaces/ITemperatureWorld.hpp"
#include "temperature-world/interfaces/ITemperatureWorldBoundable.hpp"
#include "temperature-world/interfaces/IUpdater.hpp"
#include "temperature-world/interfaces/ITimer.hpp"

/**
 * Injector.
 * This class builds bound temperature world and its updater.
 * You must set world bounds via `setWorldBounds` method. Temperature exchange coefficient and minimum update delta are set to defaults.
 */
class BoundTemperatureWorldInjector {
public:
    BoundTemperatureWorldInjector();

    /**
     * This method is exception-safe.
     *
     * @return True if world bounds have been set.
     */
    bool hasWorldBounds() const noexcept;

    /**
     * This method can throw an exception if world bounds are not set.
     *
     * @return World bounds.
     */
    Parallelepiped worldBounds() const;

    /**
     * Sets world bounds.
     *
     * @param worldBounds World bounds.
     */
    void setWorldBounds(Parallelepiped worldBounds);

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
     * @return Built bound temperature world.
     */
    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> world();

    /**
     * Temperature world updater will be built only once for an injector instance. You can get the world via `world` getter.
     *
     * @return Built bound temperature world updater.
     */
    std::shared_ptr<IUpdater> updater();

    /**
     * Timer will be built only once for an injector instance.
     *
     * @return Built blocking timer which is used in world updater.
     */
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
