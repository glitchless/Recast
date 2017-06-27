//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_BLOCKINGTIMER_H
#define RECAST_BLOCKINGTIMER_H


#include <mutex>
#include "temperature-world/interfaces/ITimerBlockable.hpp"

/**
 * Implementation of blocking timer.
 */
class SynchronizedBlockingTimer : public virtual ITimerBlockable<ITimer> {
public:
    SynchronizedBlockingTimer(std::chrono::milliseconds minDelta);

    std::chrono::milliseconds delta() const override;
    std::chrono::milliseconds minDelta() const override;
    double deltaFloatSeconds() const override;

    void update() override;
    void wait() override;

protected:
    std::chrono::milliseconds _minDelta;

    std::chrono::system_clock::time_point _lastUpdateTime;
    mutable std::mutex _lastUpdateTimeMutex;
};


#endif //RECAST_BLOCKINGTIMER_H
