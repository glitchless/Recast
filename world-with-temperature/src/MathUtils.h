//
// Created by Oleg Morozenkov on 03.04.17.
//

#ifndef RECAST_MATHUTILS_H
#define RECAST_MATHUTILS_H


namespace MathUtils {

    template <typename T>
    inline T lerp(T a, T b, float t) {
        return (1 - t) * a + t * b;
    }

};


#endif //RECAST_MATHUTILS_H
