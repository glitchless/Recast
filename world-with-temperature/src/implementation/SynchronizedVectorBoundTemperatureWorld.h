//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_VECTORTEMPERATUREWORLD_H
#define RECAST_VECTORTEMPERATUREWORLD_H


#include <vector>
#include <mutex>
#include <fruit/fruit.h>
#include "../interfaces/IBoundTemperatureWorld.h"
#include "../annotations/BoundTemperatureWorldAnnotations.h"

/**
 * Bound temperature world backed by `std::vector`.
 * This class is thread-safe.
 */
class SynchronizedVectorBoundTemperatureWorld : public IBoundTemperatureWorld {
public:
    INJECT(SynchronizedVectorBoundTemperatureWorld(
            ANNOTATED(BoundTemperatureWorldAnnotations::Width, Size) sizeX,
            ANNOTATED(BoundTemperatureWorldAnnotations::Height, Size) sizeY,
            ANNOTATED(BoundTemperatureWorldAnnotations::Depth, Size) sizeZ));

    SynchronizedVectorBoundTemperatureWorld(Coord minX, Coord maxX, Coord minY, Coord maxY, Coord minZ, Coord maxZ);

    bool has(Coord x, Coord y, Coord z) const noexcept override;

    Temperature get(Coord x, Coord y, Coord z) const override;

    void set(Coord x, Coord y, Coord z, Temperature temperature) override;

    void amplify(Coord x, Coord y, Coord z, Temperature temperature) override;

    void foreach(std::function<void(Coord, Coord, Coord)> func) override;

    Coord minX() const override;

    Coord maxX() const override;

    Coord minY() const override;

    Coord maxY() const override;

    Coord minZ() const override;

    Coord maxZ() const override;

    Size sizeX() const override;

    Size sizeY() const override;

    Size sizeZ() const override;

private:
    size_t _getIndexInData(Coord x, Coord y, Coord z) const;

    const Size _sizeX;
    const Size _sizeY;
    const Size _sizeZ;
    const Coord _minX, _maxX;
    const Coord _minY, _maxY;
    const Coord _minZ, _maxZ;

    std::vector<Temperature> _data;
    mutable std::mutex _mutex;
};


#endif //RECAST_VECTORTEMPERATUREWORLD_H
