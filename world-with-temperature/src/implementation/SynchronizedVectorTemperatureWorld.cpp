//
// Created by Oleg Morozenkov on 31.05.17.
//

#include <cassert>
#include "SynchronizedVectorTemperatureWorld.h"

using namespace std;

SynchronizedVectorTemperatureWorld::SynchronizedVectorTemperatureWorld(Size sizeX, Size sizeY, Size sizeZ)
        : _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ)
{
    _maxX = sizeX / 2;
    _maxY = sizeY / 2;
    _maxZ = sizeZ / 2;

    _minX = _maxX - (sizeX - 1);
    _minY = _maxY - (sizeY - 1);
    _minZ = _maxZ - (sizeZ - 1);

    _data.resize((size_t) (sizeX * sizeY * sizeZ), Temperature(0));
}

bool SynchronizedVectorTemperatureWorld::has(Coord x, Coord y, Coord z) const noexcept {
    return (_minX <= x && x <= _maxX) && (_minY <= y && y <= _maxY) && (_minZ <= z && z <= _maxZ);
}

Temperature SynchronizedVectorTemperatureWorld::get(Coord x, Coord y, Coord z) const {
    lock_guard<mutex> guard(_mutex);
    return _data[_getIndexInData(x, y, z)];
}

void SynchronizedVectorTemperatureWorld::set(Coord x, Coord y, Coord z, Temperature temperature) {
    lock_guard<mutex> guard(_mutex);
    _data[_getIndexInData(x, y, z)] = temperature;
}

void SynchronizedVectorTemperatureWorld::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    lock_guard<mutex> guard(_mutex);
    _data[_getIndexInData(x, y, z)] += temperature;
}

void SynchronizedVectorTemperatureWorld::foreach(std::function<void(Coord, Coord, Coord)> func) {
    for (Coord x = _minX; x <= _maxX; x++) {
        for (Coord y = _minY; y <= _maxY; y++) {
            for (Coord z = _minZ; z <= _maxZ; z++) {
                func(x, y, z);
            }
        }
    }
}

Coord SynchronizedVectorTemperatureWorld::minX() const {
    return _minX;
}

Coord SynchronizedVectorTemperatureWorld::maxX() const {
    return _maxX;
}

Coord SynchronizedVectorTemperatureWorld::minY() const {
    return _minY;
}

Coord SynchronizedVectorTemperatureWorld::maxY() const {
    return _maxY;
}

Coord SynchronizedVectorTemperatureWorld::minZ() const {
    return _minZ;
}

Coord SynchronizedVectorTemperatureWorld::maxZ() const {
    return _maxZ;
}

Size SynchronizedVectorTemperatureWorld::sizeX() const {
    return _sizeX;
}

Size SynchronizedVectorTemperatureWorld::sizeY() const {
    return _sizeY;
}

Size SynchronizedVectorTemperatureWorld::sizeZ() const {
    return _sizeZ;
}

size_t SynchronizedVectorTemperatureWorld::_getIndexInData(Coord x, Coord y, Coord z) const {
    assert(_minX <= x && x <= _maxX);
    assert(_minY <= y && y <= _maxY);
    assert(_minZ <= z && z <= _maxZ);
    size_t index = (size_t) (x - _minX) * _sizeY * _sizeZ + (size_t) (y - _minY) * _sizeZ + (size_t) (z - _minZ);
    return index;
}
