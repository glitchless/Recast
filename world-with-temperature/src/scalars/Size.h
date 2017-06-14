//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_SIZE_H_H
#define RECAST_SIZE_H_H


#include "GenericScalar.h"

/**
 * Represents world object or size of world by some axis.
 */
struct Size : public GenericScalar<int> {
    Size(int value = 0) : GenericScalar(value) {
    }
};


#endif //RECAST_SIZE_H_H
