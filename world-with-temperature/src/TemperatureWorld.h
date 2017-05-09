//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_TEMPERATUREWORLD_H
#define RECAST_TEMPERATUREWORLD_H


#include <cstddef>
#include <vector>
#include <functional>
#include <mutex>
#include "Coord.h"
#include "Temperature.h"

class TemperatureWorld {
public:
    TemperatureWorld(size_t sizeX, size_t sizeY, size_t sizeZ);
    virtual ~TemperatureWorld();

    Temperature get(Coord x, Coord y, Coord z);
    void set(Coord x, Coord y, Coord z, Temperature temperature);
    void amplify(Coord x, Coord y, Coord z, Temperature temperature);

    inline Coord getMinX() const { return _minX; }
    inline Coord getMinY() const { return _minY; };
    inline Coord getMinZ() const { return _minZ; };
    inline Coord getMaxX() const { return _maxX; };
    inline Coord getMaxY() const { return _maxY; };
    inline Coord getMaxZ() const { return _maxZ; };

    void foreach(std::function<void(Coord, Coord, Coord)> func);

private:
    size_t _getIndexInData(Coord x, Coord y, Coord z) const;

    size_t _sizeX, _sizeY, _sizeZ;
    Coord _minX, _minY, _minZ, _maxX, _maxY, _maxZ;
    std::vector<Temperature> _data;
    std::mutex _mutex;
};


#endif //RECAST_TEMPERATUREWORLD_H
