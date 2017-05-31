//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_IBOUNDTEMPERATUREWORLD_H
#define RECAST_IBOUNDTEMPERATUREWORLD_H


#include <functional>
#include "scalars/Coord.h"
#include "scalars/Size.h"
#include "scalars/Temperature.h"
#include "ITemperatureWorld.h"

/**
 * Holds temperate world data. Temperature world is not endless.
 */
class IBoundTemperatureWorld : public ITemperatureWorld {
public:
    /**
     * Loops over each point.
     *
     * @param func Function to execute at each point.
     */
    virtual void foreach(std::function<void(CoordX, CoordY, CoordZ)> func) = 0;

    /**
     * @return Minimum possible x coordinate.
     */
    virtual CoordX minX() const = 0;

    /**
     * @return Maximum possible x coordinate.
     */
    virtual CoordX maxX() const = 0;

    /**
     * @return Minimum possible y coordinate.
     */
    virtual CoordY minY() const = 0;

    /**
     * @return Maximum possible y coordinate.
     */
    virtual CoordY maxY() const = 0;

    /**
     * @return Minimum possible z coordinate.
     */
    virtual CoordZ minZ() const = 0;

    /**
     * @return Maximum possible z coordinate.
     */
    virtual CoordZ maxZ() const = 0;

    /**
     * @return Size of the world by x axis;
     */
    virtual SizeX sizeX() const = 0;

    /**
     * @return Size of the world by y axis;
     */
    virtual SizeY sizeY() const = 0;

    /**
     * @return Size of the world by z axis;
     */
    virtual SizeZ sizeZ() const = 0;
};


#endif //RECAST_IBOUNDTEMPERATUREWORLD_H
