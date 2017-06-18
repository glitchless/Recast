//
// Created by Oleg Morozenkov on 31.05.17.
//

#include <cassert>
#include "BoundTemperatureWorldOnSynchronizedVector.h"

using namespace std;

BoundTemperatureWorldOnSynchronizedVector::BoundTemperatureWorldOnSynchronizedVector(Parallelepiped bounds) : _bounds(bounds) {
    _data.resize((size_t) (_bounds.sizeX() * _bounds.sizeY() * _bounds.sizeZ()), 0);
}

bool BoundTemperatureWorldOnSynchronizedVector::has(Coord x, Coord y, Coord z) const noexcept {
    return (_bounds.minX() <= x && x <= _bounds.maxX()) && (_bounds.minY() <= y && y <= _bounds.maxY()) && (_bounds.minZ() <= z && z <= _bounds.maxZ());
}

Temperature BoundTemperatureWorldOnSynchronizedVector::get(Coord x, Coord y, Coord z) const {
    lock_guard<mutex> guard(_dataMutex);
    return _data[_getIndexInData(x, y, z)];
}

void BoundTemperatureWorldOnSynchronizedVector::set(Coord x, Coord y, Coord z, Temperature temperature) {
    lock_guard<mutex> guard(_dataMutex);
    _data[_getIndexInData(x, y, z)] = temperature;
}

void BoundTemperatureWorldOnSynchronizedVector::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    lock_guard<mutex> guard(_dataMutex);
    _data[_getIndexInData(x, y, z)] += temperature;
}

void BoundTemperatureWorldOnSynchronizedVector::foreach(BoundTemperatureWorldOnSynchronizedVector::ForeachCellFn func) const {
    for (Coord x = _bounds.minX(); x <= _bounds.maxX(); x++) {
        for (Coord y = _bounds.minY(); y <= _bounds.maxY(); y++) {
            for (Coord z = _bounds.minZ(); z <= _bounds.maxZ(); z++) {
                func(x, y, z);
            }
        }
    }
}

Parallelepiped BoundTemperatureWorldOnSynchronizedVector::bounds() const noexcept {
    return _bounds;
}

size_t BoundTemperatureWorldOnSynchronizedVector::_getIndexInData(Coord x, Coord y, Coord z) const {
    if (!has(x, y, z)) {
        throw out_of_range("This point doesn't belong to this bound temperature world");
    }
    size_t index = (size_t) (x - _bounds.minX()) * _bounds.sizeY() * _bounds.sizeZ() +
                   (size_t) (y - _bounds.minY()) * _bounds.sizeZ() +
                   (size_t) (z - _bounds.minZ());
    return index;
}

BoundTemperatureWorldOnSynchronizedVector::BoundTemperatureWorldOnSynchronizedVector(const BoundTemperatureWorldOnSynchronizedVector& other)
        : BoundTemperatureWorldOnSynchronizedVector(other, lock_guard<mutex>(other._dataMutex))
{
}

BoundTemperatureWorldOnSynchronizedVector::BoundTemperatureWorldOnSynchronizedVector(BoundTemperatureWorldOnSynchronizedVector&& other)
        : BoundTemperatureWorldOnSynchronizedVector(move(other), lock_guard<mutex>(other._dataMutex))
{
}

BoundTemperatureWorldOnSynchronizedVector::BoundTemperatureWorldOnSynchronizedVector(const BoundTemperatureWorldOnSynchronizedVector& other, const std::lock_guard<std::mutex>&)
        : _bounds(other._bounds), _data(other._data)
{
}

BoundTemperatureWorldOnSynchronizedVector::BoundTemperatureWorldOnSynchronizedVector(BoundTemperatureWorldOnSynchronizedVector&& other, const std::lock_guard<std::mutex>&)
        : _bounds(move(other._bounds)), _data(move(other._data))
{
}

BoundTemperatureWorldOnSynchronizedVector& BoundTemperatureWorldOnSynchronizedVector::operator=(BoundTemperatureWorldOnSynchronizedVector other) {
    swap(*this, other);
    return *this;
}
