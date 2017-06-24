//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_SCALABLESYNCHRONIZEDVECTORBOUNDTEMPERATUREWORLD_H
#define RECAST_SCALABLESYNCHRONIZEDVECTORBOUNDTEMPERATUREWORLD_H


#include "temperature-world/types/Temperature.hpp"
#include "BoundTemperatureWorld.hpp"
#include "temperature-world/types/IntScaleParallelepiped.hpp"
#include "temperature-world/interfaces/ITemperatureWorldScalable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldScalableMutable.hpp"
#include "temperature-world/types/Point.hpp"

/**
 * Implementation of temperature world with bounds. It's backed by `std::vector`.
 * You can make cell size bigger for `set`, `amplify` and `foreach` methods. It's useful for optimization.
 */
class ScalableBoundTemperatureWorld : public virtual ITemperatureWorldScalableMutable<ITemperatureWorldScalable<BoundTemperatureWorld>> {
public:
    ScalableBoundTemperatureWorld(Parallelepiped bounds);

    IntScaleParallelepiped cellScale() const noexcept override;
    void setCellScale(IntScaleParallelepiped cellScale) override;

    void set(Coord x, Coord y, Coord z, Temperature temperature) override;
    void amplify(Coord x, Coord y, Coord z, Temperature temperature) override;
    void foreach(ForeachCellFn func) const override;

protected:
    virtual Coord _findScaledAreaMinByAxis(Coord initialCoord, IntScale scale, Coord minCoord) const noexcept;
    virtual Coord _findScaledAreaMaxByAxis(Coord initialCoord, IntScale scale, Coord maxCoord) const noexcept;
    virtual std::pair<Coord, Coord> _findScaledAreaByAxis(Coord initialCoord, IntScale scale, Coord minCoord, Coord maxCoord) const noexcept;
    virtual Parallelepiped _findScaledArea(Coord x, Coord y, Coord z) const noexcept;

    IntScaleParallelepiped _cellScale;
};


#endif //RECAST_SCALABLESYNCHRONIZEDVECTORBOUNDTEMPERATUREWORLD_H
