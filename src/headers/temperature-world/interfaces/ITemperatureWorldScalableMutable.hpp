//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_ITEMPERATUREWORLDSCALABLEMUTABLE_H_H
#define RECAST_ITEMPERATUREWORLDSCALABLEMUTABLE_H_H


#include "../types/IntScale.hpp"

/**
 * Should not be derived directly. Use `ITemperatureWorldScalableMutable`.
 * This class is useful for `dynamic_cast`.
 */
class ITemperatureWorldScalableMutableMixin {
public:
    /**
     * Sets scale of each cell.
     *
     * @param scale Scale in three dimensions.
     */
    virtual void setCellScale(IntScaleParallelepiped scale) = 0;
};

/**
 * Mixin to temperature world.
 * Makes temperature world to set scale of cells.
 *
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldScalableMutable : public virtual T, public virtual ITemperatureWorldScalableMutableMixin {
};


#endif //RECAST_ITEMPERATUREWORLDSCALABLEMUTABLE_H_H
