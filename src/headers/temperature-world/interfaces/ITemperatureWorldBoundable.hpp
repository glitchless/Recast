//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_IBOUNDTEMPERATUREWORLD_H
#define RECAST_IBOUNDTEMPERATUREWORLD_H


#include <functional>
#include "temperature-world/types/Edge.hpp"
#include "temperature-world/types/Coord.hpp"
#include "temperature-world/types/Size.hpp"
#include "temperature-world/types/Temperature.hpp"
#include "ITemperatureWorld.hpp"
#include "temperature-world/types/Parallelepiped.hpp"

/**
 * Should not be derived directly. Use `ITemperatureWorldBoundable`.
 * This class is useful for `dynamic_cast`.
 */
class ITemperatureWorldBoundableMixin {
public:
    using ForeachCellFn = std::function<void(Coord, Coord, Coord)>;

    /**
     * Loops over each point.
     *
     * @param func Function to execute at each point.
     */
    virtual void foreach(ForeachCellFn func) const = 0;

    /**
     * Loops over each point on specified edge.
     *
     * @param edge Edge.
     * @param func Function to execute at each point.
     */
    virtual void foreachCellOnEdge(Edge edge, ForeachCellFn func) const = 0;

    /**
     * @return Bounds of this temperature world.
     */
    virtual Parallelepiped bounds() const noexcept = 0;
};

/**
 * Mixin to temperature world.
 * Makes temperature world not to be endless.
 *
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldBoundable : public virtual T, public virtual ITemperatureWorldBoundableMixin {
};


#endif //RECAST_IBOUNDTEMPERATUREWORLD_H
