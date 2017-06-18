//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_SCALABLESYNCHRONIZEDVECTORBOUNDTEMPERATUREWORLD_H
#define RECAST_SCALABLESYNCHRONIZEDVECTORBOUNDTEMPERATUREWORLD_H


#include "BoundTemperatureWorld.h"
#include "../types/IntScaleParallelepiped.h"
#include "../interfaces/ITemperatureWorldScalable.h"
#include "../interfaces/ITemperatureWorldScalableMutable.h"
#include "../types/Point.h"
#include "annotations/ScaledTemperatureWorldAnnotations.h"

/**
 * Bound temperature world backed by `std::vector`.
 * You can make cell size bigger for `set`, `amplify` and `foreach` methods. It's useful for optimization.
 * Cell data access is thread-safe.
 */
class ScalableBoundTemperatureWorld : public ITemperatureWorldScalableMutable<ITemperatureWorldScalable<BoundTemperatureWorld>> {
public:
    INJECT_F(ScalableBoundTemperatureWorld(
            ANNOTATED(BoundTemperatureWorldAnnotations::Bounds, Parallelepiped) bounds,
            ANNOTATED(ScaledTemperatureWorldAnnotations::CellScale, IntScaleParallelepiped) cellScale));

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
