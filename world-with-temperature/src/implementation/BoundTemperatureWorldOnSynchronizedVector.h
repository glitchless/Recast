//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_VECTORTEMPERATUREWORLD_H
#define RECAST_VECTORTEMPERATUREWORLD_H


#include <vector>
#include <mutex>
#include <fruit/fruit.h>
#include "../interfaces/ITemperatureWorldBoundable.h"
#include "annotations/BoundTemperatureWorldAnnotations.h"
#include "../types/Parallelepiped.h"
#include "../fixes/fruit.h"

/**
 * Bound temperature world backed by `std::vector`.
 * Cell data access is thread-safe.
 */
class BoundTemperatureWorldOnSynchronizedVector : public ITemperatureWorldBoundable<ITemperatureWorld> {
public:
    INJECT_F(BoundTemperatureWorldOnSynchronizedVector(
            ANNOTATED(BoundTemperatureWorldAnnotations::Bounds, Parallelepiped) bounds));

    BoundTemperatureWorldOnSynchronizedVector(const BoundTemperatureWorldOnSynchronizedVector& other);
    BoundTemperatureWorldOnSynchronizedVector(BoundTemperatureWorldOnSynchronizedVector&& other);
    BoundTemperatureWorldOnSynchronizedVector& operator=(BoundTemperatureWorldOnSynchronizedVector other);

    friend void swap(BoundTemperatureWorldOnSynchronizedVector& first, BoundTemperatureWorldOnSynchronizedVector& second);

    bool has(Coord x, Coord y, Coord z) const noexcept override;
    Temperature get(Coord x, Coord y, Coord z) const override;
    void set(Coord x, Coord y, Coord z, Temperature temperature) override;
    void amplify(Coord x, Coord y, Coord z, Temperature temperature) override;

    void foreach(ForeachCellFn func) const override;

    Parallelepiped bounds() const noexcept override;

protected:
    BoundTemperatureWorldOnSynchronizedVector(const BoundTemperatureWorldOnSynchronizedVector& other, const std::lock_guard<std::mutex>&);
    BoundTemperatureWorldOnSynchronizedVector(BoundTemperatureWorldOnSynchronizedVector&& other, const std::lock_guard<std::mutex>&);

    virtual size_t _getIndexInData(Coord x, Coord y, Coord z) const;

    Parallelepiped _bounds;
    std::vector<Temperature> _data;
    mutable std::mutex _dataMutex;
};

#include "BoundTemperatureWorldOnSynchronizedVector.inc.h"


#endif //RECAST_VECTORTEMPERATUREWORLD_H
