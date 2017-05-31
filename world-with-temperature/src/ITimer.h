//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_ITIMER_H
#define RECAST_ITIMER_H


#include <chrono>

class ITimer {
public:
    virtual ~ITimer() {}

    /**
     * @return Time from last update.
     */
    virtual std::chrono::milliseconds delta() = 0;

    /**
     * Saves update, saves "tick". It will influence value of `delta`.
     */
    virtual void update() = 0;
};


#endif //RECAST_ITIMER_H
