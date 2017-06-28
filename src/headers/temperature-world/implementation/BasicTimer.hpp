//
// Created by Oleg Morozenkov on 11.06.17.
//

#ifndef RECAST_BASICTIMER_H
#define RECAST_BASICTIMER_H


#include "temperature-world/interfaces/ITimer.hpp"

/**
 * Timer that measures time duration between two updates.
 */
class BasicTimer : public virtual ITimer {
public:
    BasicTimer();

    std::chrono::milliseconds delta() const override;
    double deltaFloatSeconds() const override;
    bool isFirstUpdate() const override;

    void update() override;

protected:
    std::chrono::system_clock::time_point _lastUpdateTime;
    bool _isFirstUpdate;
};


#endif //RECAST_BASICTIMER_H
