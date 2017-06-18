//
// Created by Oleg Morozenkov on 15.06.17.
//

#ifndef RECAST_SYNCHRONIZEDVECTORBOUNDTEMPERATUREWORLD_INC_H
#define RECAST_SYNCHRONIZEDVECTORBOUNDTEMPERATUREWORLD_INC_H


#include "BoundTemperatureWorld.h"

inline void swap(BoundTemperatureWorld& first, BoundTemperatureWorld& second) {
    std::swap(first._bounds, second._bounds);
    std::swap(first._data, second._data);
}


#endif //RECAST_SYNCHRONIZEDVECTORBOUNDTEMPERATUREWORLD_INC_H
