//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_VECTORTEMPERATUREWORLD_H
#define RECAST_VECTORTEMPERATUREWORLD_H


#include <vector>
#include <mutex>
#include <fruit/fruit.h>
#include "../interfaces/IBoundTemperatureWorld.h"
#include "annotations/BoundTemperatureWorldAnnotations.h"
#include "../scalars/ScaledParallelepiped.h"

/**
 * Bound temperature world backed by `std::vector`.
 * This class is thread-safe.
 */
class SynchronizedVectorBoundTemperatureWorld : public IBoundTemperatureWorld {
public:
    INJECT(SynchronizedVectorBoundTemperatureWorld(
            ANNOTATED(BoundTemperatureWorldAnnotations::Bounds, ScaledParallelepiped) bounds));

    SynchronizedVectorBoundTemperatureWorld(const SynchronizedVectorBoundTemperatureWorld& other);
    SynchronizedVectorBoundTemperatureWorld(SynchronizedVectorBoundTemperatureWorld&& other);
    SynchronizedVectorBoundTemperatureWorld& operator=(SynchronizedVectorBoundTemperatureWorld other);

    friend void swap(SynchronizedVectorBoundTemperatureWorld& first, SynchronizedVectorBoundTemperatureWorld& second);

    bool has(Coord x, Coord y, Coord z) const noexcept override;
    Temperature get(Coord x, Coord y, Coord z) const override;
    void set(Coord x, Coord y, Coord z, Temperature temperature) override;
    void amplify(Coord x, Coord y, Coord z, Temperature temperature) override;

    void foreach(std::function<void(Coord, Coord, Coord)> func) const override;

    Parallelepiped bounds() const noexcept override;
    ScaledParallelepiped boundsWithScale() const noexcept;

protected:
    SynchronizedVectorBoundTemperatureWorld(const SynchronizedVectorBoundTemperatureWorld& other, const std::lock_guard<std::mutex>&);
    SynchronizedVectorBoundTemperatureWorld(SynchronizedVectorBoundTemperatureWorld&& other, const std::lock_guard<std::mutex>&);

    size_t _getIndexInData(Coord x, Coord y, Coord z) const;

    ScaledParallelepiped _bounds;
    std::vector<Temperature> _data;
    mutable std::mutex _dataMutex;
};

#include "SynchronizedVectorBoundTemperatureWorld.inc.h"

#endif //RECAST_VECTORTEMPERATUREWORLD_H
