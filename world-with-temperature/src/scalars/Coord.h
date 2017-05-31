//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_COORD_H
#define RECAST_COORD_H


#include <boost/serialization/strong_typedef.hpp>

/**
 * Represents x coordinate in a world.
 */
BOOST_STRONG_TYPEDEF(int, CoordX)

/**
 * Represents y coordinate in a world.
 */
BOOST_STRONG_TYPEDEF(int, CoordY)

/**
 * Represents z coordinate in a world.
 */
BOOST_STRONG_TYPEDEF(int, CoordZ)


#endif //RECAST_COORD_H
