//
// Created by Oleg Morozenkov on 03.04.17.
//

#ifndef RECAST_MATHUTILS_H
#define RECAST_MATHUTILS_H


#include <cmath>

namespace MathUtils {

    template <typename T>
    inline T lerp(T a, T b, double t) {
        return (1 - t) * a + t * b;
    }

};


#endif //RECAST_MATHUTILS_H
