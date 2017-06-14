//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_TEMPERATURE_H
#define RECAST_TEMPERATURE_H


#include "GenericScalar.h"

/**
 * Represents temperature of world object.
 */
struct Temperature : public GenericScalar<int> {
    Temperature(int value = 0) : GenericScalar(value) {
    }
};


#endif //RECAST_TEMPERATURE_H