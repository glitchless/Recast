//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_POINT_H
#define RECAST_POINT_H


#include "Coord.h"

/**
 * Type.
 * Represents point in three-dimensional space.
 */
struct Point {
public:
    Point(Coord x, Coord y, Coord z) : _x(x), _y(y), _z(z) {
    }

    inline Coord x() const noexcept {
        return _x;
    }

    inline Coord y() const noexcept {
        return _y;
    }

    inline Coord z() const noexcept {
        return _z;
    }

    inline bool operator==(const Point& other) const noexcept {
        return _x == other._x && _y == other._y && _z == other._z;
    }

    inline bool operator!=(const Point& other) const noexcept {
        return !(*this == other);
    }

protected:
    Coord _x, _y, _z;
};

#endif //RECAST_POINT_H
