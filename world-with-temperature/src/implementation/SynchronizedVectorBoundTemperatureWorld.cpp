//
// Created by Oleg Morozenkov on 31.05.17.
//

#include <cassert>
#include "SynchronizedVectorBoundTemperatureWorld.h"

using namespace std;

SynchronizedVectorBoundTemperatureWorld::SynchronizedVectorBoundTemperatureWorld(Size sizeX, Size sizeY, Size sizeZ)
        : _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ)
{
    _maxX = sizeX / 2;
    _maxY = sizeY / 2;
    _maxZ = sizeZ / 2;

    _minX = _maxX - (sizeX - 1);
    _minY = _maxY - (sizeY - 1);
    _minZ = _maxZ - (sizeZ - 1);

    _data.resize((size_t) (_sizeX * _sizeY * sizeZ), 0);
}

SynchronizedVectorBoundTemperatureWorld::SynchronizedVectorBoundTemperatureWorld(Coord minX, Coord maxX, Coord minY, Coord maxY, Coord minZ, Coord maxZ)
        : _minX(minX), _maxX(maxX), _minY(minY), _maxY(maxY), _minZ(minZ), _maxZ(maxZ)
{
    assert(minX < maxX && minY < maxY && minZ < maxZ);
    _sizeX = maxX - minX + 1;
    _sizeY = maxY - minY + 1;
    _sizeY = maxY - minY + 1;
    _data.resize((size_t) (_sizeX * _sizeY * _sizeZ), 0);
}

bool SynchronizedVectorBoundTemperatureWorld::has(Coord x, Coord y, Coord z) const noexcept {
    return (_minX <= x && x <= _maxX) && (_minY <= y && y <= _maxY) && (_minZ <= z && z <= _maxZ);
}

Temperature SynchronizedVectorBoundTemperatureWorld::get(Coord x, Coord y, Coord z) const {
    lock_guard<mutex> guard(_mutex);
    return _data[_getIndexInData(x, y, z)];
}

void SynchronizedVectorBoundTemperatureWorld::set(Coord x, Coord y, Coord z, Temperature temperature) {
    lock_guard<mutex> guard(_mutex);
    _data[_getIndexInData(x, y, z)] = temperature;
}

void SynchronizedVectorBoundTemperatureWorld::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    lock_guard<mutex> guard(_mutex);
    _data[_getIndexInData(x, y, z)] += temperature;
}

void SynchronizedVectorBoundTemperatureWorld::foreach(std::function<void(Coord, Coord, Coord)> func) {
    for (Coord x = _minX; x <= _maxX; x++) {
        for (Coord y = _minY; y <= _maxY; y++) {
            for (Coord z = _minZ; z <= _maxZ; z++) {
                func(x, y, z);
            }
        }
    }
}

Coord SynchronizedVectorBoundTemperatureWorld::minX() const {
    return _minX;
}

Coord SynchronizedVectorBoundTemperatureWorld::maxX() const {
    return _maxX;
}

Coord SynchronizedVectorBoundTemperatureWorld::minY() const {
    return _minY;
}

Coord SynchronizedVectorBoundTemperatureWorld::maxY() const {
    return _maxY;
}

Coord SynchronizedVectorBoundTemperatureWorld::minZ() const {
    return _minZ;
}

Coord SynchronizedVectorBoundTemperatureWorld::maxZ() const {
    return _maxZ;
}

Size SynchronizedVectorBoundTemperatureWorld::sizeX() const {
    return _sizeX;
}

Size SynchronizedVectorBoundTemperatureWorld::sizeY() const {
    return _sizeY;
}

Size SynchronizedVectorBoundTemperatureWorld::sizeZ() const {
    return _sizeZ;
}

size_t SynchronizedVectorBoundTemperatureWorld::_getIndexInData(Coord x, Coord y, Coord z) const {
    if (!has(x, y, z)) {
        throw out_of_range("This point doesn't belong to this bound temperature world");
    }
    size_t index = (size_t) (x - _minX) * _sizeY * _sizeZ + (size_t) (y - _minY) * _sizeZ + (size_t) (z - _minZ);
    return index;
}
