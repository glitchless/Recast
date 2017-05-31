//
// Created by Oleg Morozenkov on 31.05.17.
//

#include <cassert>
#include "VectorTemperatureWorld.h"

using namespace std;

VectorTemperatureWorld::VectorTemperatureWorld(SizeX sizeX, SizeY sizeY, SizeZ sizeZ) : _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ) {
    _maxX = sizeX / 2;
    _maxY = sizeY / 2;
    _maxZ = sizeZ / 2;

    _minX = _maxX - (sizeX - 1);
    _minY = _maxY - (sizeY - 1);
    _minZ = _maxZ - (sizeZ - 1);

    _data.resize((size_t) (sizeX * sizeY * sizeZ), Temperature(0));
}

Temperature VectorTemperatureWorld::get(CoordX x, CoordY y, CoordZ z) {
    lock_guard<mutex> guard(_mutex);
    return _data[_getIndexInData(x, y, z)];
}

void VectorTemperatureWorld::set(CoordX x, CoordY y, CoordZ z, Temperature temperature) {
    lock_guard<mutex> guard(_mutex);
    _data[_getIndexInData(x, y, z)] = temperature;
}

void VectorTemperatureWorld::amplify(CoordX x, CoordY y, CoordZ z, Temperature temperature) {
    lock_guard<mutex> guard(_mutex);
    _data[_getIndexInData(x, y, z)] += temperature;
}

void VectorTemperatureWorld::foreach(std::function<void(CoordX, CoordY, CoordZ)> func) {
    for (CoordX x = _minX; x <= _maxX; x++) {
        for (CoordY y = _minY; y <= _maxY; y++) {
            for (CoordZ z = _minZ; z <= _maxZ; z++) {
                func(x, y, z);
            }
        }
    }
}

CoordX VectorTemperatureWorld::minX() const {
    return _minX;
}

CoordX VectorTemperatureWorld::maxX() const {
    return _maxX;
}

CoordY VectorTemperatureWorld::minY() const {
    return _minY;
}

CoordY VectorTemperatureWorld::maxY() const {
    return _maxY;
}

CoordZ VectorTemperatureWorld::minZ() const {
    return _minZ;
}

CoordZ VectorTemperatureWorld::maxZ() const {
    return _maxZ;
}

SizeX VectorTemperatureWorld::sizeX() const {
    return _sizeX;
}

SizeY VectorTemperatureWorld::sizeY() const {
    return _sizeY;
}

SizeZ VectorTemperatureWorld::sizeZ() const {
    return _sizeZ;
}

size_t VectorTemperatureWorld::_getIndexInData(CoordX x, CoordY y, CoordZ z) const {
    assert(_minX <= x && x <= _maxX);
    assert(_minY <= y && y <= _maxY);
    assert(_minZ <= z && z <= _maxZ);
    size_t index = (size_t) (x - _minX) * _sizeY * _sizeZ + (size_t) (y - _minY) * _sizeZ + (size_t) (z - _minZ);
    return index;
}
