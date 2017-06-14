//
// Created by Oleg Morozenkov on 03.04.17.
//

#ifndef RECAST_MATHUTILS_H
#define RECAST_MATHUTILS_H


#include <cmath>
#include <cassert>

/**
 * Collection of functions which work with numbers.
 */
namespace MathUtils {

    /**
     * Makes value `a` to be more "similar" to value `b` by factor `t`.
     *
     * @tparam T Any number, e.g. `double`.
     * @param a First value.
     * @param b Second Value.
     * @param t Factor.
     * @return Linear interpolated value.
     */
    template<typename T>
    inline T lerp(T a, T b, double t) {
        return T((1 - t) * a + t * b);
    }

    /**
     * Generates random value between 0.0 and 1.0.
     *
     * @return Random value between 0.0 and 1.0.
     */
    inline double randomFloat() {
        return (double) rand() / RAND_MAX;
    }

};


#endif //RECAST_MATHUTILS_H
