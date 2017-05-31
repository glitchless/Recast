//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_ILIMITINGTIMER_H
#define RECAST_ILIMITINGTIMER_H


#include "ITimer.h"

/**
 * Timer can ask client to wait in blocking way, so the `delta` won't be less than `minDelta`.
 */
class IBlockingTimer : public ITimer {
public:
    /**
     * @return Minimum possible value of `delta`.
     */
    virtual std::chrono::duration minDelta() = 0;
};


#endif //RECAST_ILIMITINGTIMER_H
