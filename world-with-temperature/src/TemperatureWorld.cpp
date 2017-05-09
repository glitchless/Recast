//
// Created by Oleg Morozenkov on 30.03.17.
//

#include <cassert>
#include "TemperatureWorld.h"

using namespace std;

TemperatureWorld::TemperatureWorld(size_t sizeX, size_t sizeY, size_t sizeZ) : _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ) {
    _maxX = (Coord) (sizeX / 2);
    _maxY = (Coord) (sizeY / 2);
    _maxZ = (Coord) (sizeZ / 2);
    _minX = (Coord) (_maxX - (sizeX - 1));
    _minY = (Coord) (_maxY - (sizeY - 1));
    _minZ = (Coord) (_maxZ - (sizeZ - 1));
    _data.resize(sizeX * sizeY * sizeZ, 0);
}

TemperatureWorld::~TemperatureWorld() {
}

Temperature TemperatureWorld::get(Coord x, Coord y, Coord z) {
    lock_guard<mutex> guard(_mutex);
    return _data[_getIndexInData(x, y, z)];
}

void TemperatureWorld::set(Coord x, Coord y, Coord z, Temperature temperature) {
    lock_guard<mutex> guard(_mutex);
    _data[_getIndexInData(x, y, z)] = temperature;
}

void TemperatureWorld::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    lock_guard<mutex> guard(_mutex);
    _data[_getIndexInData(x, y, z)] += temperature;
}

size_t TemperatureWorld::_getIndexInData(Coord x, Coord y, Coord z) const {
    assert(_minX <= x && x <= _maxX);
    assert(_minY <= y && y <= _maxY);
    assert(_minZ <= z && z <= _maxZ);
    size_t index = (size_t) (x - _minX) * _sizeY * _sizeZ + (size_t) (y - _minY) * _sizeZ + (size_t) (z - _minZ);
    return index;
}

void TemperatureWorld::foreach(std::function<void(Coord, Coord, Coord)> func) {
    for (Coord x = _minX; x <= _maxX; x++) {
        for (Coord y = _minY; y <= _maxY; y++) {
            for (Coord z = _minZ; z <= _maxZ; z++) {
                func(x, y, z);
            }
        }
    }
}
