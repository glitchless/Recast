//
// Created by Oleg Morozenkov on 14.06.17.
//

#ifndef RECAST_SCALEDPARALLELEPIPED_H
#define RECAST_SCALEDPARALLELEPIPED_H


#include "Parallelepiped.hpp"
#include "IntScale.hpp"

/**
 * Type.
 * Holds scales in three dimensions.
 */
struct IntScaleParallelepiped {
    IntScaleParallelepiped(IntScale x, IntScale y, IntScale z) : _x(x), _y(y), _z(z) {
    }

    IntScaleParallelepiped(int x, int y, int z, IntScale::Mode mode) : _x(IntScale(x, mode)) , _y(IntScale(y, mode)) , _z(IntScale(z, mode)) {
    }

    /**
     * @return Scale of the world by x axis;
     */
    inline IntScale x() const noexcept {
        return _x;
    };

    /**
     * @return Scale of the world by y axis;
     */
    inline IntScale y() const noexcept {
        return _y;
    };

    /**
     * @return Scale of the world by z axis;
     */
    inline IntScale z() const noexcept {
        return _z;
    };

    inline bool operator==(const IntScaleParallelepiped& other) const noexcept {
        return _x == other._x && _y == other._y && _z == other._z;
    }

    inline bool operator!=(const IntScaleParallelepiped& other) const noexcept {
        return !(*this == other);
    }

protected:
    IntScale _x;
    IntScale _y;
    IntScale _z;
};


#endif //RECAST_SCALEDPARALLELEPIPED_H
