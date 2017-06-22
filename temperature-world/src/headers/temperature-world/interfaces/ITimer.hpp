//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_ITIMER_H
#define RECAST_ITIMER_H


#include <chrono>

/**
 * Interface.
 * Measures time.
 */
class ITimer {
public:
    virtual ~ITimer() noexcept = default;

    /**
     * @return Time from last update in milliseconds.
     */
    virtual std::chrono::milliseconds delta() const = 0;

    /**
     * @return Time from last update in float-number seconds.
     */
    virtual double deltaFloatSeconds() const = 0;

    /**
     * Saves update, saves the "tick". It will influence value of `delta`.
     */
    virtual void update() = 0;
};


#endif //RECAST_ITIMER_H
