//
// Created by Oleg Morozenkov on 02.06.17.
//

#ifndef RECAST_WORLD_WITH_TEMPERATURE_H
#define RECAST_WORLD_WITH_TEMPERATURE_H


#include <fruit/fruit.h>
#include "annotations/BoundTemperatureWorldAnnotations.h"
#include "scalars/Size.h"
#include "interfaces/IBoundTemperatureWorld.h"
#include "interfaces/ITemperatureWorldUpdater.h"

namespace WorldWithTemperatureModule {
    fruit::Component<
            fruit::Required<
                    fruit::Annotated<BoundTemperatureWorldAnnotations::Width, Size>,
                    fruit::Annotated<BoundTemperatureWorldAnnotations::Height, Size>,
                    fruit::Annotated<BoundTemperatureWorldAnnotations::Depth, Size>>,
            ITemperatureWorld, IBoundTemperatureWorld, ITemperatureWorldUpdater> component();
}


#endif //RECAST_WORLD_WITH_TEMPERATURE_H
