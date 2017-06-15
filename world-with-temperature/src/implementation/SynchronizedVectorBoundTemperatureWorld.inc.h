//
// Created by Oleg Morozenkov on 15.06.17.
//

#ifndef RECAST_SYNCHRONIZEDVECTORBOUNDTEMPERATUREWORLD_INC_H
#define RECAST_SYNCHRONIZEDVECTORBOUNDTEMPERATUREWORLD_INC_H


#include "SynchronizedVectorBoundTemperatureWorld.h"

inline void swap(SynchronizedVectorBoundTemperatureWorld& first, SynchronizedVectorBoundTemperatureWorld& second) {
    std::unique_lock<std::mutex> firstGuard(first._dataMutex, std::defer_lock);
    std::unique_lock<std::mutex> secondGuard(second._dataMutex, std::defer_lock);
    std::lock(firstGuard, secondGuard);

    std::swap(first._bounds, second._bounds);
    std::swap(first._data, second._data);
}


#endif //RECAST_SYNCHRONIZEDVECTORBOUNDTEMPERATUREWORLD_INC_H
