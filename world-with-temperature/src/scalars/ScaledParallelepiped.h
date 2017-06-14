//
// Created by Oleg Morozenkov on 14.06.17.
//

#ifndef RECAST_SCALEDPARALLELEPIPED_H
#define RECAST_SCALEDPARALLELEPIPED_H


#include "Parallelepiped.h"

struct ScaledParallelepiped : public Parallelepiped {
    ScaledParallelepiped(Size sizeX, Size sizeY, Size sizeZ)
            : Parallelepiped(sizeX, sizeY, sizeZ)
            , _scaleX(1), _scaleY(1), _scaleZ(1)
    {
    }

    ScaledParallelepiped(Coord minX, Coord maxX, Coord minY, Coord maxY, Coord minZ, Coord maxZ)
            : Parallelepiped(minX, maxX, minY, maxY, minZ, maxZ)
            , _scaleX(1), _scaleY(1), _scaleZ(1)
    {
    }

    ScaledParallelepiped(Size sizeX, Size sizeY, Size sizeZ, int scaleX, int scaleY, int scaleZ)
            : Parallelepiped(sizeX, sizeY, sizeZ)
            , _scaleX(scaleX), _scaleY(scaleY), _scaleZ(scaleZ)
    {
    }

    ScaledParallelepiped(Coord minX, Coord maxX, Coord minY, Coord maxY, Coord minZ, Coord maxZ, int scaleX, int scaleY, int scaleZ)
            : Parallelepiped(minX, maxX, minY, maxY, minZ, maxZ)
            , _scaleX(scaleX), _scaleY(scaleY), _scaleZ(scaleZ)
    {
    }

    /**
     * @return Scale of the world by x axis;
     */
    inline double scaleX() const noexcept {
        return _scaleX;
    };

    /**
     * @return Scale of the world by y axis;
     */
    inline double scaleY() const noexcept {
        return _scaleY;
    };

    /**
     * @return Scale of the world by z axis;
     */
    inline double scaleZ() const noexcept {
        return _scaleZ;
    };

private:
    int _scaleX;
    int _scaleY;
    int _scaleZ;
};


#endif //RECAST_SCALEDPARALLELEPIPED_H
