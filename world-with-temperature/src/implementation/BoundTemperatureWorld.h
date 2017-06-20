//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_VECTORTEMPERATUREWORLD_H
#define RECAST_VECTORTEMPERATUREWORLD_H


#include <vector>
#include "../interfaces/ITemperatureWorldBoundable.h"
#include "../types/Parallelepiped.h"

/**
 * Bound temperature world backed by `std::vector`.
 */
class BoundTemperatureWorld : public ITemperatureWorldBoundable<ITemperatureWorld> {
public:
    BoundTemperatureWorld(Parallelepiped bounds);

    BoundTemperatureWorld(const BoundTemperatureWorld& other);
    BoundTemperatureWorld(BoundTemperatureWorld&& other);
    BoundTemperatureWorld& operator=(BoundTemperatureWorld other);

    friend void swap(BoundTemperatureWorld& first, BoundTemperatureWorld& second);

    bool has(Coord x, Coord y, Coord z) const noexcept override;
    Temperature get(Coord x, Coord y, Coord z) const override;
    void set(Coord x, Coord y, Coord z, Temperature temperature) override;
    void amplify(Coord x, Coord y, Coord z, Temperature temperature) override;

    void foreach(ForeachCellFn func) const override;

    Parallelepiped bounds() const noexcept override;

protected:
    virtual size_t _getIndexInData(Coord x, Coord y, Coord z) const;

    Parallelepiped _bounds;
    std::vector<Temperature> _data;
};

#include "BoundTemperatureWorld.inc.h"


#endif //RECAST_VECTORTEMPERATUREWORLD_H
