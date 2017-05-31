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
     * @return Time from last update in milliseconds.
     */
    virtual std::chrono::milliseconds delta() = 0;

    /**
     * @return Time from last update in float-number seconds.
     */
    virtual double deltaFloatSeconds() = 0;

    /**
     * Saves update, saves "tick". It will influence value of `delta`.
     */
    virtual void update() = 0;
};


#endif //RECAST_ITIMER_H
