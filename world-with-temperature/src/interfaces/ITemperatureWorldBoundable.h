//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_IBOUNDTEMPERATUREWORLD_H
#define RECAST_IBOUNDTEMPERATUREWORLD_H


#include <functional>
#include "../types/Coord.h"
#include "../types/Size.h"
#include "../types/Temperature.h"
#include "ITemperatureWorld.h"
#include "../types/Parallelepiped.h"

/**
 * Mixin to temperature world.
 * Makes temperature world not to be endless.
 *
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldBoundable : public virtual T {
public:
    using ForeachCellFn = std::function<void(Coord, Coord, Coord)>;

    /**
     * Loops over each point.
     *
     * @param func Function to execute at each point.
     */
    virtual void foreach(ForeachCellFn func) const = 0;

    /**
     * @return Bounds of this temperature world.
     */
    virtual Parallelepiped bounds() const noexcept = 0;
};


#endif //RECAST_IBOUNDTEMPERATUREWORLD_H
