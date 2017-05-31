//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_TEMPERATUREWORLD_H
#define RECAST_TEMPERATUREWORLD_H


#include "scalars/Coord.h"
#include "scalars/Temperature.h"

/**
 * Holds temperature world data.
 */
class ITemperatureWorld {
public:
    virtual ~ITemperatureWorld() {}

    /**
     * Returns temperature at the point.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @return Temperature at the point.
     */
    virtual Temperature get(CoordX x, CoordY y, CoordZ z) = 0;

    /**
     * Sets temperature at the point.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @param temperature Temperature to set.
     */
    virtual void set(CoordX x, CoordY y, CoordZ z, Temperature temperature) = 0;

    /**
     * Adds or substracts temperature value from existing temperature value at the point.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @param temperature Temperature difference.
     */
    virtual void amplify(CoordX x, CoordY y, CoordZ z, Temperature temperature) = 0;
};


#endif //RECAST_TEMPERATUREWORLD_H
