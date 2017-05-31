//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_BLOCKINGTIMER_H
#define RECAST_BLOCKINGTIMER_H


#include <mutex>
#include "IBlockingTimer.h"

/**
 * Implementation of blocking timer.
 * This class is thread-safe.
 */
class SynchronizedBlockingTimer : public IBlockingTimer {
public:
    SynchronizedBlockingTimer(std::chrono::milliseconds minDelta);

    std::chrono::milliseconds delta() override;

    void update() override;

    std::chrono::milliseconds minDelta() override;

private:
    std::chrono::milliseconds _minDelta;

    std::chrono::system_clock::time_point _lastUpdateTime;
    std::mutex _mutex;
};


#endif //RECAST_BLOCKINGTIMER_H
