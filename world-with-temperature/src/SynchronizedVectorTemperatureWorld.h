//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_VECTORTEMPERATUREWORLD_H
#define RECAST_VECTORTEMPERATUREWORLD_H


#include <vector>
#include <mutex>
#include "IBoundTemperatureWorld.h"

/**
 * Bound temperature world backed by `std::vector`.
 * This class is thread-safe.
 */
class SynchronizedVectorTemperatureWorld : public IBoundTemperatureWorld {
public:
    SynchronizedVectorTemperatureWorld(SizeX sizeX, SizeY sizeY, SizeZ sizeZ);

    Temperature get(CoordX x, CoordY y, CoordZ z) override;

    void set(CoordX x, CoordY y, CoordZ z, Temperature temperature) override;

    void amplify(CoordX x, CoordY y, CoordZ z, Temperature temperature) override;

    void foreach(std::function<void(CoordX, CoordY, CoordZ)> func) override;

    CoordX minX() const override;

    CoordX maxX() const override;

    CoordY minY() const override;

    CoordY maxY() const override;

    CoordZ minZ() const override;

    CoordZ maxZ() const override;

    SizeX sizeX() const override;

    SizeY sizeY() const override;

    SizeZ sizeZ() const override;

private:
    size_t _getIndexInData(CoordX x, CoordY y, CoordZ z) const;

    SizeX _sizeX;
    SizeY _sizeY;
    SizeZ _sizeZ;
    CoordX _minX, _maxX;
    CoordY _minY, _maxY;
    CoordZ _minZ, _maxZ;

    std::vector<Temperature> _data;
    std::mutex _mutex;
};


#endif //RECAST_VECTORTEMPERATUREWORLD_H
