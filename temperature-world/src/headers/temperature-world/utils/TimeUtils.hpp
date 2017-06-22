//
// Created by Oleg Morozenkov on 08.05.17.
//

#ifndef RECAST_TIMEUTILS_H
#define RECAST_TIMEUTILS_H


#include <chrono>

/**
 * Collection of functions which work with time.
 */
namespace TimeUtils {

    /**
     * Gets current time since Epoch in milliseconds.
     *
     * @return Milliseconds since Epoch.
     */
    inline long long int currentTimeMillis() {
        const auto now = std::chrono::system_clock::now();
        const auto duration = now.time_since_epoch();
        const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        return millis;
    }

    /**
     * Gets current time since Epoch in seconds.
     *
     * @return Seconds since Epoch.
     */
    inline double currentTimeSeconds() {
        return (double) currentTimeMillis() / 1000;
    }

};

#endif //RECAST_TIMEUTILS_H
