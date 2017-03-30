//
// Created by Oleg Morozenkov on 30.03.17.
//

#include <cassert>
#include "TemperatureWorld.h"

TemperatureWorld::TemperatureWorld(size_t sizeX, size_t sizeY, size_t sizeZ) : _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ) {
    _maxX = (Coord) (sizeX / 2 + 1);
    _maxY = (Coord) (sizeY / 2 + 1);
    _maxZ = (Coord) (sizeZ / 2 + 1);
    _minX = -_maxX;
    _minY = -_maxY;
    _minZ = -_maxZ;
    _data.resize(sizeX * sizeY * sizeZ, 0);
}

TemperatureWorld::~TemperatureWorld() {
}

Temperature TemperatureWorld::get(Coord x, Coord y, Coord z) const {
    return _data[_getIndexInData(x, y, z)];
}

void TemperatureWorld::set(Coord x, Coord y, Coord z, Temperature temperature) {
    _data[_getIndexInData(x, y, z)] = temperature;
}

void TemperatureWorld::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    _data[_getIndexInData(x, y, z)] += temperature;
}

Coord TemperatureWorld::getMinX() const {
    return _minX;
}

Coord TemperatureWorld::getMinY() const {
    return _minY;
}

Coord TemperatureWorld::getMinZ() const {
    return _minZ;
}

Coord TemperatureWorld::getMaxX() const {
    return _maxX;
}

Coord TemperatureWorld::getMaxY() const {
    return _maxY;
}

Coord TemperatureWorld::getMaxZ() const {
    return _maxZ;
}

size_t TemperatureWorld::_getIndexInData(Coord x, Coord y, Coord z) const {
    assert(_minX <= x && x <= _maxX);
    assert(_minY <= y && y <= _maxY);
    assert(_minZ <= z && z <= _maxZ);
    return (size_t) (x - _minX) * _sizeY * _sizeZ + (size_t) (y - _minY) * _sizeZ + (size_t) (z - _minZ);
}
