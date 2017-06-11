//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_BLOCKINGTIMER_H
#define RECAST_BLOCKINGTIMER_H


#include <mutex>
#include <fruit/fruit.h>
#include "../interfaces/IBlockingTimer.h"
#include "../annotations/BlockingTimerAnnotations.h"

/**
 * Implementation of blocking timer.
 * This class is thread-safe.
 */
class SynchronizedBlockingTimer : public IBlockingTimer {
public:
    INJECT(SynchronizedBlockingTimer(
            ANNOTATED(BlockingTimerAnnotations::MinDelta, std::chrono::milliseconds) minDelta));

    std::chrono::milliseconds delta() const override;

    double deltaFloatSeconds() const override;

    void update() override;

    std::chrono::milliseconds minDelta() const override;

private:
    const std::chrono::milliseconds _minDelta;

    std::chrono::system_clock::time_point _lastUpdateTime;
    mutable std::mutex _mutex;
};


#endif //RECAST_BLOCKINGTIMER_H
