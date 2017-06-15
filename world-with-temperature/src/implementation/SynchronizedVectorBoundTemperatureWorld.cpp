//
// Created by Oleg Morozenkov on 31.05.17.
//

#include <cassert>
#include "SynchronizedVectorBoundTemperatureWorld.h"

using namespace std;

SynchronizedVectorBoundTemperatureWorld::SynchronizedVectorBoundTemperatureWorld(ScaledParallelepiped bounds) : _bounds(bounds) {
    _data.resize((size_t) (_bounds.sizeX() * _bounds.sizeY() * _bounds.sizeZ()), 0);
}

bool SynchronizedVectorBoundTemperatureWorld::has(Coord x, Coord y, Coord z) const noexcept {
    return (_bounds.minX() <= x && x <= _bounds.maxX()) && (_bounds.minY() <= y && y <= _bounds.maxY()) && (_bounds.minZ() <= z && z <= _bounds.maxZ());
}

Temperature SynchronizedVectorBoundTemperatureWorld::get(Coord x, Coord y, Coord z) const {
    lock_guard<mutex> guard(_dataMutex);
    return _data[_getIndexInData(x, y, z)];
}

void SynchronizedVectorBoundTemperatureWorld::set(Coord x, Coord y, Coord z, Temperature temperature) {
    lock_guard<mutex> guard(_dataMutex);
    _data[_getIndexInData(x, y, z)] = temperature;
}

void SynchronizedVectorBoundTemperatureWorld::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    lock_guard<mutex> guard(_dataMutex);
    _data[_getIndexInData(x, y, z)] += temperature;
}

void SynchronizedVectorBoundTemperatureWorld::foreach(std::function<void(Coord, Coord, Coord)> func) const {
    for (Coord x = _bounds.minX(); x <= _bounds.maxX(); x++) {
        for (Coord y = _bounds.minY(); y <= _bounds.maxY(); y++) {
            for (Coord z = _bounds.minZ(); z <= _bounds.maxZ(); z++) {
                func(x, y, z);
            }
        }
    }
}

Parallelepiped SynchronizedVectorBoundTemperatureWorld::bounds() const noexcept {
    return _bounds;
}

ScaledParallelepiped SynchronizedVectorBoundTemperatureWorld::boundsWithScale() const noexcept {
    return _bounds;
}

size_t SynchronizedVectorBoundTemperatureWorld::_getIndexInData(Coord x, Coord y, Coord z) const {
    if (!has(x, y, z)) {
        throw out_of_range("This point doesn't belong to this bound temperature world");
    }
    size_t index = (size_t) (_bounds.scaleX() * x - _bounds.minX()) * _bounds.sizeY() * _bounds.sizeZ()
                   + (size_t) (_bounds.scaleY() * y - _bounds.minY()) * _bounds.sizeZ()
                   + (size_t) (_bounds.scaleZ() * z - _bounds.minZ());
    return index;
}

SynchronizedVectorBoundTemperatureWorld::SynchronizedVectorBoundTemperatureWorld(const SynchronizedVectorBoundTemperatureWorld& other)
        : SynchronizedVectorBoundTemperatureWorld(other, lock_guard<mutex>(other._dataMutex))
{
}

SynchronizedVectorBoundTemperatureWorld::SynchronizedVectorBoundTemperatureWorld(SynchronizedVectorBoundTemperatureWorld&& other)
        : SynchronizedVectorBoundTemperatureWorld(other, lock_guard<mutex>(other._dataMutex))
{
}

SynchronizedVectorBoundTemperatureWorld::SynchronizedVectorBoundTemperatureWorld(const SynchronizedVectorBoundTemperatureWorld& other, const std::lock_guard<std::mutex>&)
        : _bounds(other._bounds), _data(other._data)
{
}

SynchronizedVectorBoundTemperatureWorld::SynchronizedVectorBoundTemperatureWorld(SynchronizedVectorBoundTemperatureWorld&& other, const std::lock_guard<std::mutex>&)
        : _bounds(move(other._bounds)), _data(move(other._data))
{
}

SynchronizedVectorBoundTemperatureWorld& SynchronizedVectorBoundTemperatureWorld::operator=(SynchronizedVectorBoundTemperatureWorld other) {
    swap(*this, other);
    return *this;
}
