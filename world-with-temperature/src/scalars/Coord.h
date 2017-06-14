//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_COORD_H
#define RECAST_COORD_H


#include <boost/serialization/strong_typedef.hpp>
#include "GenericScalar.h"

/**
 * Represents coordinate in a world.
 */
struct Coord : public GenericScalar<int> {
    Coord(int value = 0) : GenericScalar(value) {
    }
};


#endif //RECAST_COORD_H
