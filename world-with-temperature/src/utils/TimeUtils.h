//
// Created by Oleg Morozenkov on 08.05.17.
//

#ifndef RECAST_TIMEUTILS_H
#define RECAST_TIMEUTILS_H

#include <chrono>

namespace TimeUtils {

    inline long long int currentTimeMillis() {
        const auto now = std::chrono::system_clock::now();
        const auto duration = now.time_since_epoch();
        const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        return millis;
    }

    inline double currentTimeSeconds() {
        return (double) currentTimeMillis() / 1000;
    }

};

#endif //RECAST_TIMEUTILS_H
