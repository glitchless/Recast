//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_ILIMITINGTIMER_H
#define RECAST_ILIMITINGTIMER_H


#include "ITimer.hpp"

/**
 * Should not be derived directly. Use `ITimerBlockable`.
 * This class is useful for `dynamic_cast`.
 */
class ITimerBlockableMixin {
public:
    /**
     * @return Minimum possible value of `delta`.
     */
    virtual std::chrono::milliseconds minDelta() const = 0;

    /**
     * Blocks until `delta` >= `minDelta`.
     */
    virtual void wait() = 0;
};

/**
 * Mixin to timer.
 * Makes timer to have method that block client, so the `delta` won't be less than `minDelta`.
 */
template<typename T>
class ITimerBlockable : public virtual T, public virtual ITimerBlockableMixin {
};


#endif //RECAST_ILIMITINGTIMER_H
