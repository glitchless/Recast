//
// Created by Oleg Morozenkov on 03.04.17.
//

#include "MathUtils.h"

template <typename T>
T MathUtils::lerp<T>(T a, T b, float t) {
    return (1 - t) * a + t * b;
}
