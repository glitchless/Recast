//
// Created by Oleg Morozenkov on 02.06.17.
//

#ifndef RECAST_WORLD_WITH_TEMPERATURE_H
#define RECAST_WORLD_WITH_TEMPERATURE_H


#include <fruit/fruit.h>
#include <chrono>
#include "types/Size.h"
#include "interfaces/ITemperatureWorldBoundable.h"
#include "interfaces/IUpdater.h"
#include "types/IntScaleParallelepiped.h"

/**
 * Namespace which has component factory methods.
 */
namespace WorldWithTemperatureModule {
    namespace Defaults {
        static double temperatureExchangeCoefficient = 0.1;
        static std::chrono::milliseconds minDelta(20);
    }

    /**
     * Makes component which can create temperature world updater.
     * Requires to configure temperature world.
     *
     * @param temperatureExchangeCoefficient Means speed of temperature exchange.
     * @param minDelta Minimum time duration between temperature world updates.
     * @return Component.
     */
    fruit::Component<fruit::Required<ITemperatureWorldBoundable<ITemperatureWorld>>, IUpdater>
    updaterComponent(
            double& temperatureExchangeCoefficient = Defaults::temperatureExchangeCoefficient,
            std::chrono::milliseconds& minDelta = Defaults::minDelta);

    /**
     * Makes component which can create temperature world and its updater.
     *
     * @param bounds Bounds of the temperature world.
     * @param updaterComponent_ Component which creates temperature world updater.
     * @return Component.
     */
    fruit::Component<ITemperatureWorld, ITemperatureWorldBoundable<ITemperatureWorld>, IUpdater>
    boundTemperatureWorldComponent(
            Parallelepiped& bounds,
            fruit::Component<fruit::Required<ITemperatureWorldBoundable<ITemperatureWorld>>, IUpdater> updaterComponent_ = updaterComponent());
}


#endif //RECAST_WORLD_WITH_TEMPERATURE_H
