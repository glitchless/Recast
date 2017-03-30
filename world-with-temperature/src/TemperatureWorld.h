//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_TEMPERATUREWORLD_H
#define RECAST_TEMPERATUREWORLD_H


#include <cstddef>
#include <vector>
#include "Coord.h"
#include "Temperature.h"

class TemperatureWorld {
public:
    TemperatureWorld(size_t sizeX, size_t sizeY, size_t sizeZ);
    virtual ~TemperatureWorld();

    Temperature get(Coord x, Coord y, Coord z) const;
    void set(Coord x, Coord y, Coord z, Temperature temperature);
    void amplify(Coord x, Coord y, Coord z, Temperature temperature);

    Coord getMinX() const;
    Coord getMinY() const;
    Coord getMinZ() const;
    Coord getMaxX() const;
    Coord getMaxY() const;
    Coord getMaxZ() const;

private:
    size_t _getIndexInData(Coord x, Coord y, Coord z) const;

    size_t _sizeX, _sizeY, _sizeZ;
    Coord _minX, _minY, _minZ, _maxX, _maxY, _maxZ;
    std::vector<Temperature> _data;
};


#endif //RECAST_TEMPERATUREWORLD_H
