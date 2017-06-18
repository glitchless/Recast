//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_COORD_H
#define RECAST_COORD_H


#include <boost/serialization/strong_typedef.hpp>
#include "GenericScalar.h"

/**
 * Type.
 * Represents coordinate in a space.
 */
struct Coord : public GenericScalar<int> {
public:
    Coord(int value = 0) : GenericScalar(value) {
    }
};


#endif //RECAST_COORD_H
