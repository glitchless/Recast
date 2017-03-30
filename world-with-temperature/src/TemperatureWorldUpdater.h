//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_TEMPERATUREWORLDUPDATER_H
#define RECAST_TEMPERATUREWORLDUPDATER_H


#include <memory>
#include "TemperatureWorld.h"

class TemperatureWorldUpdater {
public:
    TemperatureWorldUpdater(std::shared_ptr<TemperatureWorld> world);

    void update(float dt);

private:
    std::shared_ptr<TemperatureWorld> _world;
};


#endif //RECAST_TEMPERATUREWORLDUPDATER_H
