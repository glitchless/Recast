//
// Created by Oleg Morozenkov on 08.05.17.
//

#ifndef RECAST_TEMPERATUREWORLDUTILS_H
#define RECAST_TEMPERATUREWORLDUTILS_H

#include <cstdlib>
#include <cassert>
#include "../TemperatureWorld.h"

namespace TemperatureWorldUtils {
    inline void randomize(TemperatureWorld& world, Temperature minTemp, Temperature maxTemp) {
        assert(minTemp < maxTemp);
        Temperature tempRange = maxTemp - minTemp;
        world.foreach([&world, minTemp, maxTemp, tempRange](Coord x, Coord y, Coord z) {
            world.set(x, y, z, minTemp + (Temperature) ((double) rand() / RAND_MAX * tempRange));
        });
    }
}

#endif //RECAST_TEMPERATUREWORLDUTILS_H
