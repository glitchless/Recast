//
// Created by Oleg Morozenkov on 02.06.17.
//

#ifndef RECAST_WORLD_WITH_TEMPERATURE_H
#define RECAST_WORLD_WITH_TEMPERATURE_H


#include <fruit/fruit.h>
#include <chrono>
#include "annotations/BoundTemperatureWorldAnnotations.h"
#include "scalars/Size.h"
#include "interfaces/IBoundTemperatureWorld.h"
#include "interfaces/ITemperatureWorldUpdater.h"

namespace WorldWithTemperatureModule {
    namespace Defaults {
        static double temperatureExchangeCoefficient = 0.1;
        static std::chrono::milliseconds minDelta(20);
    }

    fruit::Component<fruit::Required<IBoundTemperatureWorld>, ITemperatureWorldUpdater>
    updaterComponent(
            double& temperatureExchangeCoefficient = Defaults::temperatureExchangeCoefficient,
            std::chrono::milliseconds& = Defaults::minDelta);

    fruit::Component<ITemperatureWorld, IBoundTemperatureWorld, ITemperatureWorldUpdater>
    boundTemperatureWorldComponent(
            Size& width, Size& height, Size& depth,
            fruit::Component<fruit::Required<IBoundTemperatureWorld>, ITemperatureWorldUpdater> updaterComponent_ = updaterComponent());
}


#endif //RECAST_WORLD_WITH_TEMPERATURE_H
