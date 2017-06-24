//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_TEMPERATUREWORLD_H
#define RECAST_TEMPERATUREWORLD_H


#include "temperature-world/types/Coord.hpp"
#include "temperature-world/types/Temperature.hpp"

/**
 * Interface.
 * Holds temperature world data.
 */
class ITemperatureWorld {
public:
    virtual ~ITemperatureWorld() noexcept = default;

    /**
     * Tells whether temperature at the point is accessible.
     * This method doesn't throw exceptions.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @return True if the point is accessible.
     */
    virtual bool has(Coord x, Coord y, Coord z) const noexcept = 0;

    /**
     * Returns temperature at the point.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @return Temperature at the point.
     */
    virtual Temperature get(Coord x, Coord y, Coord z) const = 0;

    /**
     * Sets temperature at the point.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @param temperature Temperature to set.
     */
    virtual void set(Coord x, Coord y, Coord z, Temperature temperature) = 0;

    /**
     * Adds or substracts temperature value from existing temperature value at the point.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @param temperature Temperature difference.
     */
    virtual void amplify(Coord x, Coord y, Coord z, Temperature temperature) = 0;

    /**
     * @param x Current coordinate by x axis.
     * @return Previous coordinate by x axis.
     */
    virtual Coord previousCoordX(Coord x) const noexcept = 0;

    /**
     * @param y Current coordinate by y axis.
     * @return Previous coordinate by y axis.
     */
    virtual Coord previousCoordY(Coord y) const noexcept = 0;

    /**
     * @param z Current coordinate by z axis.
     * @return Previous coordinate by z axis.
     */
    virtual Coord previousCoordZ(Coord z) const noexcept = 0;

    /**
     * @param x Current coordinate by x axis.
     * @return Next coordinate by x axis.
     */
    virtual Coord nextCoordX(Coord x) const noexcept = 0;

    /**
     * @param y Current coordinate by y axis.
     * @return Next coordinate by y axis.
     */
    virtual Coord nextCoordY(Coord y) const noexcept = 0;

    /**
     * @param z Current coordinate by z axis.
     * @return Next coordinate by z axis.
     */
    virtual Coord nextCoordZ(Coord z) const noexcept = 0;
};


#endif //RECAST_TEMPERATUREWORLD_H
