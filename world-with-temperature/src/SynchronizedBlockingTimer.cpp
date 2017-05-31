//
// Created by Oleg Morozenkov on 31.05.17.
//

#include <unistd.h>
#include "SynchronizedBlockingTimer.h"

using namespace std;
using namespace std::chrono;

SynchronizedBlockingTimer::SynchronizedBlockingTimer(milliseconds minDelta) : _minDelta(minDelta) {
    update();
}

milliseconds SynchronizedBlockingTimer::delta() {
    lock_guard<mutex> guard(_mutex);
    return duration_cast<milliseconds>(system_clock::now() - _lastUpdateTime);
}

double SynchronizedBlockingTimer::deltaFloatSeconds() {
    return delta().count() / 1000.0;
}

void SynchronizedBlockingTimer::update() {
    lock_guard<mutex> guard(_mutex);
    const auto dt = system_clock::now() - _lastUpdateTime;
    _lastUpdateTime = system_clock::now();
    if (dt < _minDelta) {
        const useconds_t microSecs = (useconds_t) duration_cast<microseconds>(dt).count();
        usleep(microSecs);
    }
}

milliseconds SynchronizedBlockingTimer::minDelta() {
    return _minDelta;
}
