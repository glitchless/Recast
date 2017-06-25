//
// Created by Oleg Morozenkov on 14.06.17.
//

#ifndef RECAST_PARALLELEPIPED_H
#define RECAST_PARALLELEPIPED_H


#include <cassert>
#include "Size.hpp"
#include "Coord.hpp"

/**
 * Type.
 * Represents volume in three-dimensional space.
 */
struct Parallelepiped {
public:
    Parallelepiped(Coord minX, Coord maxX, Coord minY, Coord maxY, Coord minZ, Coord maxZ)
            : _minX(minX), _maxX(maxX), _minY(minY), _maxY(maxY), _minZ(minZ), _maxZ(maxZ)
            , _sizeX(maxX - minX + 1), _sizeY(maxY - minY + 1), _sizeZ(maxZ - minZ + 1)
    {
        assert(_minX <= _maxX && _minY <= _maxY && _minZ <= _maxZ);
    }

    Parallelepiped(Size sizeX, Size sizeY, Size sizeZ)
            : _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ)
            , _maxX(sizeX / 2), _maxY(sizeY / 2), _maxZ(sizeZ / 2)
            , _minX((sizeX / 2) - (sizeX - 1)), _minY((sizeY / 2) - (sizeY - 1)), _minZ((sizeZ / 2) - (sizeZ - 1))
    {
    }

    /**
     * @return Minimum possible x coordinate.
     */
    inline Coord minX() const noexcept {
        return _minX;
    };

    /**
     * @return Maximum possible x coordinate.
     */
    inline Coord maxX() const noexcept {
        return _maxX;
    };

    /**
     * @return Minimum possible y coordinate.
     */
    inline Coord minY() const noexcept {
        return _minY;
    };

    /**
     * @return Maximum possible y coordinate.
     */
    inline Coord maxY() const noexcept {
        return _maxY;
    };

    /**
     * @return Minimum possible z coordinate.
     */
    inline Coord minZ() const noexcept {
        return _minZ;
    };

    /**
     * @return Maximum possible z coordinate.
     */
    inline Coord maxZ() const noexcept {
        return _maxZ;
    };

    /**
     * @return Size of the world by x axis;
     */
    inline Size sizeX() const noexcept {
        return _sizeX;
    };

    /**
     * @return Size of the world by y axis;
     */
    inline Size sizeY() const noexcept {
        return _sizeY;
    };

    /**
     * @return Size of the world by z axis;
     */
    inline Size sizeZ() const noexcept {
        return _sizeZ;
    };

    /**
     * @return Count of points inside.
     */
    inline Size volume() const noexcept {
        return _sizeX * _sizeY * _sizeZ;
    }

    /**
     * @param other Parallelepiped to compare with.
     * @return True if sizes of this parallepiped and other parallepiped are equal.
     */
    inline bool isSameSize(const Parallelepiped& other) const noexcept {
        return _sizeX == other._sizeX && _sizeY == other._sizeY && _sizeZ == other._sizeZ;
    }

    inline bool operator==(const Parallelepiped& other) const noexcept {
        return _minX == other._minX && _maxX == other._maxX &&
               _minY == other._minY && _maxY == other._maxY &&
               _minZ == other._minZ && _maxZ == other._maxZ;
    }

    inline bool operator!=(const Parallelepiped& other) const noexcept {
        return !(*this == other);
    }

protected:
    Coord _minX, _maxX;
    Coord _minY, _maxY;
    Coord _minZ, _maxZ;
    Size _sizeX;
    Size _sizeY;
    Size _sizeZ;
};


#endif //RECAST_PARALLELEPIPED_H
