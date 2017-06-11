//
// Created by Oleg Morozenkov on 11.06.17.
//

#ifndef RECAST_BASICTIMER_H
#define RECAST_BASICTIMER_H


#include <fruit/fruit.h>
#include "../interfaces/ITimer.h"

class BasicTimer : public ITimer {
public:
    INJECT(BasicTimer());

    std::chrono::milliseconds delta() const;

    double deltaFloatSeconds() const;

    void update();

private:
    std::chrono::system_clock::time_point _lastUpdateTime;
};


#endif //RECAST_BASICTIMER_H
