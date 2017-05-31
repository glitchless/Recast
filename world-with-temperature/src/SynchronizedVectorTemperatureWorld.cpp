//
// Created by Oleg Morozenkov on 31.05.17.
//

#include <cassert>
#include "SynchronizedVectorTemperatureWorld.h"

using namespace std;

SynchronizedVectorTemperatureWorld::SynchronizedVectorTemperatureWorld(SizeX sizeX, SizeY sizeY, SizeZ sizeZ) : _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ) {
    _maxX = sizeX / 2;
    _maxY = sizeY / 2;
    _maxZ = sizeZ / 2;

    _minX = _maxX - (sizeX - 1);
    _minY = _maxY - (sizeY - 1);
    _minZ = _maxZ - (sizeZ - 1);

    _data.resize((size_t) (sizeX * sizeY * sizeZ), Temperature(0));
}

Temperature SynchronizedVectorTemperatureWorld::get(CoordX x, CoordY y, CoordZ z) {
    lock_guard<mutex> guard(_mutex);
    return _data[_getIndexInData(x, y, z)];
}

void SynchronizedVectorTemperatureWorld::set(CoordX x, CoordY y, CoordZ z, Temperature temperature) {
    lock_guard<mutex> guard(_mutex);
    _data[_getIndexInData(x, y, z)] = temperature;
}

void SynchronizedVectorTemperatureWorld::amplify(CoordX x, CoordY y, CoordZ z, Temperature temperature) {
    lock_guard<mutex> guard(_mutex);
    _data[_getIndexInData(x, y, z)] += temperature;
}

void SynchronizedVectorTemperatureWorld::foreach(std::function<void(CoordX, CoordY, CoordZ)> func) {
    for (CoordX x = _minX; x <= _maxX; x++) {
        for (CoordY y = _minY; y <= _maxY; y++) {
            for (CoordZ z = _minZ; z <= _maxZ; z++) {
                func(x, y, z);
            }
        }
    }
}

CoordX SynchronizedVectorTemperatureWorld::minX() const {
    return _minX;
}

CoordX SynchronizedVectorTemperatureWorld::maxX() const {
    return _maxX;
}

CoordY SynchronizedVectorTemperatureWorld::minY() const {
    return _minY;
}

CoordY SynchronizedVectorTemperatureWorld::maxY() const {
    return _maxY;
}

CoordZ SynchronizedVectorTemperatureWorld::minZ() const {
    return _minZ;
}

CoordZ SynchronizedVectorTemperatureWorld::maxZ() const {
    return _maxZ;
}

SizeX SynchronizedVectorTemperatureWorld::sizeX() const {
    return _sizeX;
}

SizeY SynchronizedVectorTemperatureWorld::sizeY() const {
    return _sizeY;
}

SizeZ SynchronizedVectorTemperatureWorld::sizeZ() const {
    return _sizeZ;
}

size_t SynchronizedVectorTemperatureWorld::_getIndexInData(CoordX x, CoordY y, CoordZ z) const {
    assert(_minX <= x && x <= _maxX);
    assert(_minY <= y && y <= _maxY);
    assert(_minZ <= z && z <= _maxZ);
    size_t index = (size_t) (x - _minX) * _sizeY * _sizeZ + (size_t) (y - _minY) * _sizeZ + (size_t) (z - _minZ);
    return index;
}
