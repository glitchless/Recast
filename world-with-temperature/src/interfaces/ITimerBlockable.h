//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_ILIMITINGTIMER_H
#define RECAST_ILIMITINGTIMER_H


#include "ITimer.h"

/**
 * Mixin to timer.
 * Makes timer to be able to ask client to wait in blocking way, so the `delta` won't be less than `minDelta`.
 */
template<typename T>
class ITimerBlockable : public virtual T {
public:
    /**
     * @return Minimum possible value of `delta`.
     */
    virtual std::chrono::milliseconds minDelta() const = 0;
};


#endif //RECAST_ILIMITINGTIMER_H
