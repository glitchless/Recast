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
        static std::chrono::milliseconds minUpdateDelta(20);
        static Parallelepiped baseChunkSize(64, 64, 64);
    }

    /**
     * Makes component which can create temperature world and its updater.
     *
     * @param bounds Bounds of the temperature world.
     * @param updaterComponent Component which creates temperature world updater.
     * @return Component.
     */
    fruit::Component<ITemperatureWorld, ITemperatureWorldBoundable<ITemperatureWorld>, IUpdater>
    boundTemperatureWorldComponent(
            Parallelepiped& bounds,
            double& temperatureExchangeCoefficient = Defaults::temperatureExchangeCoefficient,
            std::chrono::milliseconds& minDelta = Defaults::minUpdateDelta);

    /**
     * Makes component which can create scaling chunked temperature world and its updater.
     *
     * @param baseChunkSize Size of each chunk.
     * @param updaterComponent_ Component which creates temperature world updater.
     * @return Component.
     */
    fruit::Component<ITemperatureWorld, IUpdater>
    chunkedTemperatureWorldComponent(
            Parallelepiped& baseChunkSize = Defaults::baseChunkSize,
            double& temperatureExchangeCoefficient = Defaults::temperatureExchangeCoefficient,
            std::chrono::milliseconds& minDelta = Defaults::minUpdateDelta);
}


#endif //RECAST_WORLD_WITH_TEMPERATURE_H
