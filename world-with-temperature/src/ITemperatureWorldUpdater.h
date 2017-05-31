//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_TEMPERATUREWORLDUPDATER_H
#define RECAST_TEMPERATUREWORLDUPDATER_H


/**
 * Updates temperature world.
 */
class ITemperatureWorldUpdater {
public:
    virtual ~ITemperatureWorldUpdater() {}

    /**
     * Updates world.
     */
    virtual void update() = 0;
};


#endif //RECAST_TEMPERATUREWORLDUPDATER_H
