//
// Created by Oleg Morozenkov on 30.03.17.
//

#ifndef RECAST_TEMPERATUREWORLDUPDATER_H
#define RECAST_TEMPERATUREWORLDUPDATER_H


/**
 * Interface.
 * Updates something.
 */
class IUpdater {
public:
    virtual ~IUpdater() noexcept = default;

    /**
     * Updates.
     */
    virtual void update() = 0;
};


#endif //RECAST_TEMPERATUREWORLDUPDATER_H
