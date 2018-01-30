//
// Created by Oleg Morozenkov on 31.05.17.
//

#include <cassert>
#include "temperature-world/types/Temperature.hpp"
#include "temperature-world/types/Parallelepiped.hpp"
#include "temperature-world/implementation/BoundTemperatureWorld.hpp"

using namespace std;

BoundTemperatureWorld::BoundTemperatureWorld(Parallelepiped bounds) : _bounds(bounds) {
    _data.resize((size_t) (_bounds.sizeX() * _bounds.sizeY() * _bounds.sizeZ()), 0);
}

bool BoundTemperatureWorld::has(Coord x, Coord y, Coord z) const noexcept {
    return (_bounds.minX() <= x && x <= _bounds.maxX()) && (_bounds.minY() <= y && y <= _bounds.maxY()) && (_bounds.minZ() <= z && z <= _bounds.maxZ());
}

BoundTemperatureWorld::BoundTemperatureWorld(const BoundTemperatureWorld& other)
        : _bounds(other._bounds), _data(other._data)
{
}

BoundTemperatureWorld::BoundTemperatureWorld(BoundTemperatureWorld&& other)
        : _bounds(move(other._bounds)), _data(move(other._data))
{
}

BoundTemperatureWorld& BoundTemperatureWorld::operator=(BoundTemperatureWorld other) {
    swap(*this, other);
    return *this;
}

Temperature BoundTemperatureWorld::get(Coord x, Coord y, Coord z) const {
    return _data[_getIndexInData(x, y, z)];
}

void BoundTemperatureWorld::set(Coord x, Coord y, Coord z, Temperature temperature) {
    _data[_getIndexInData(x, y, z)] = temperature;
}

void BoundTemperatureWorld::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    _data[_getIndexInData(x, y, z)] += temperature;
}

void BoundTemperatureWorld::foreach(BoundTemperatureWorld::ForeachCellFn func) const {
    for (Coord x = _bounds.minX(); x <= _bounds.maxX(); x++) {
        for (Coord y = _bounds.minY(); y <= _bounds.maxY(); y++) {
            for (Coord z = _bounds.minZ(); z <= _bounds.maxZ(); z++) {
                func(x, y, z);
            }
        }
    }
}

void BoundTemperatureWorld::foreachCellOnEdge(Edge edge, ITemperatureWorldBoundableMixin::ForeachCellFn func) const {
    switch (edge) {
        case Edge::LEFT:
            for (Coord y = _bounds.minY(); y <= _bounds.maxY(); y++) {
                for (Coord z = _bounds.minZ(); z <= _bounds.maxZ(); z++) {
                    func(_bounds.minX(), y, z);
                }
            }
            break;

        case Edge::RIGHT:
            for (Coord y = _bounds.minY(); y <= _bounds.maxY(); y++) {
                for (Coord z = _bounds.minZ(); z <= _bounds.maxZ(); z++) {
                    func(_bounds.maxX(), y, z);
                }
            }
            break;

        case Edge::DOWN:
            for (Coord x = _bounds.minX(); x <= _bounds.maxX(); x++) {
                for (Coord z = _bounds.minZ(); z <= _bounds.maxZ(); z++) {
                    func(x, _bounds.minY(), z);
                }
            }
            break;

        case Edge::UP:
            for (Coord x = _bounds.minX(); x <= _bounds.maxX(); x++) {
                for (Coord z = _bounds.minZ(); z <= _bounds.maxZ(); z++) {
                    func(x, _bounds.maxY(), z);
                }
            }
            break;

        case Edge::NEAR:
            for (Coord x = _bounds.minX(); x <= _bounds.maxX(); x++) {
                for (Coord y = _bounds.minY(); y <= _bounds.maxY(); y++) {
                    func(x, y, _bounds.minZ());
                }
            }
            break;

        case Edge::FAR:
            for (Coord x = _bounds.minX(); x <= _bounds.maxX(); x++) {
                for (Coord y = _bounds.minY(); y <= _bounds.maxY(); y++) {
                    func(x, y, _bounds.maxZ());
                }
            }
            break;
    }
}

Parallelepiped BoundTemperatureWorld::bounds() const noexcept {
    return _bounds;
}

size_t BoundTemperatureWorld::_getIndexInData(Coord x, Coord y, Coord z) const {
    if (!has(x, y, z)) {
        throw out_of_range("This point doesn't belong to this bound temperature world");
    }
    size_t index = (size_t) (x - _bounds.minX()) * _bounds.sizeY() * _bounds.sizeZ() +
                   (size_t) (y - _bounds.minY()) * _bounds.sizeZ() +
                   (size_t) (z - _bounds.minZ());
    return index;
}

Coord BoundTemperatureWorld::previousCoordX(Coord x) const noexcept {
    return x - 1;
}

Coord BoundTemperatureWorld::previousCoordY(Coord y) const noexcept {
    return y - 1;
}

Coord BoundTemperatureWorld::previousCoordZ(Coord z) const noexcept {
    return z - 1;
}

Coord BoundTemperatureWorld::nextCoordX(Coord x) const noexcept {
    return x + 1;
}

Coord BoundTemperatureWorld::nextCoordY(Coord y) const noexcept {
    return y + 1;
}

Coord BoundTemperatureWorld::nextCoordZ(Coord z) const noexcept {
    return z + 1;
}
