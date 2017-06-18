//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_ISCALABLETEMPERATUREWORLD_H
#define RECAST_ISCALABLETEMPERATUREWORLD_H


#include "../types/IntScaleParallelepiped.h"

/**
 * Mixin to temperature world.
 * Makes temperature world to have scale of cells.
 *
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldScalable : public virtual T {
public:
    /**
     * @return Scale of each cell in three dimensions.
     */
    virtual IntScaleParallelepiped cellScale() const noexcept = 0;
};


#endif //RECAST_ISCALABLETEMPERATUREWORLD_H
