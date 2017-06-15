//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_IBOUNDTEMPERATUREWORLD_H
#define RECAST_IBOUNDTEMPERATUREWORLD_H


#include <functional>
#include "../scalars/Coord.h"
#include "../scalars/Size.h"
#include "../scalars/Temperature.h"
#include "ITemperatureWorld.h"
#include "../scalars/Parallelepiped.h"

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
    virtual void foreach(std::function<void(Coord, Coord, Coord)> func) const = 0;

    /**
     * @return Bounds of this temperature world.
     */
    virtual Parallelepiped bounds() const noexcept = 0;
};


#endif //RECAST_IBOUNDTEMPERATUREWORLD_H
