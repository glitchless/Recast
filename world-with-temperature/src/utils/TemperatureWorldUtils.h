//
// Created by Oleg Morozenkov on 08.05.17.
//

#ifndef RECAST_TEMPERATUREWORLDUTILS_H
#define RECAST_TEMPERATUREWORLDUTILS_H


#include <cstdlib>
#include <cassert>
#include "../interfaces/IBoundTemperatureWorld.h"
#include "MathUtils.h"

/**
 * Collection of functions which work with temperature world.
 */
namespace TemperatureWorldUtils {

    /**
     * Initializes temperature world with random temperatures. Random temperatures are generated within the range.
     *
     * @param world World to initialize.
     * @param minTemperature Minimum possible temperature in the world.
     * @param maxTemperature Maximum possible temperature in the world.
     */
    inline void randomize(IBoundTemperatureWorld& world, Temperature minTemperature, Temperature maxTemperature) {
        assert(minTemperature < maxTemperature);
        const Temperature temperatureRange = maxTemperature - minTemperature;
        world.foreach([&](Coord x, Coord y, Coord z) {
            const Temperature t = minTemperature + Temperature(MathUtils::randomFloat() * temperatureRange);
            world.set(x, y, z, t);
        });
    }
    
}

#endif //RECAST_TEMPERATUREWORLDUTILS_H
