//
// Created by Oleg Morozenkov on 14.06.17.
//

#ifndef RECAST_PARALLELEPIPED_H
#define RECAST_PARALLELEPIPED_H


#include <cassert>
#include "Size.h"
#include "Coord.h"

struct Parallelepiped {
public:
    Parallelepiped(Size sizeX, Size sizeY, Size sizeZ)
            : _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ)
            , _maxX(sizeX / 2), _maxY(sizeY / 2), _maxZ(sizeZ / 2)
            , _minX((sizeX / 2) - (sizeX - 1)), _minY((sizeY / 2) - (sizeY - 1)), _minZ((sizeZ / 2) - (sizeZ - 1))
    {
    }

    Parallelepiped(Coord minX, Coord maxX, Coord minY, Coord maxY, Coord minZ, Coord maxZ)
            : _minX(minX), _maxX(maxX), _minY(minY), _maxY(maxY), _minZ(minZ), _maxZ(maxZ)
            , _sizeX(maxX - minX + 1), _sizeY(maxY - minY + 1), _sizeZ(maxY - minY + 1)
    {
        assert(_minX < _maxX && _minY < _maxY && _minZ < _maxZ);
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

    inline Size volume() const noexcept {
        return _sizeX * _sizeY * _sizeZ;
    }

private:
    Size _sizeX;
    Size _sizeY;
    Size _sizeZ;
    Coord _minX, _maxX;
    Coord _minY, _maxY;
    Coord _minZ, _maxZ;
};


#endif //RECAST_PARALLELEPIPED_H
