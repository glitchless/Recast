//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_ISCALABLETEMPERATUREWORLD_H
#define RECAST_ISCALABLETEMPERATUREWORLD_H


#include "../types/IntScaleParallelepiped.hpp"

/**
 * Should not be derived directly. Use `ITemperatureWorldScalableScalable`.
 * This class is useful for `dynamic_cast`.
 */
class ITemperatureWorldScalableMixin {
public:
    /**
     * @return Scale of each cell in three dimensions.
     */
    virtual IntScaleParallelepiped cellScale() const noexcept = 0;
};

/**
 * Mixin to temperature world.
 * Makes temperature world to have scale of cells.
 *
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldScalable : public virtual T, public ITemperatureWorldScalableMixin {
};


#endif //RECAST_ISCALABLETEMPERATUREWORLD_H
