//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_SIZE_H_H
#define RECAST_SIZE_H_H


#include <boost/serialization/strong_typedef.hpp>

/**
 * Represents size of world or world object by x axis.
 */
BOOST_STRONG_TYPEDEF(int, SizeX)

/**
 * Represents size of world or world object by y axis.
 */
BOOST_STRONG_TYPEDEF(int, SizeY)

/**
 * Represents size of world or world object by z axis.
 */
BOOST_STRONG_TYPEDEF(int, SizeZ)


#endif //RECAST_SIZE_H_H
