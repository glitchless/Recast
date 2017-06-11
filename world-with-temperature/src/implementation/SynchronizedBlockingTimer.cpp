//
// Created by Oleg Morozenkov on 31.05.17.
//

#include <thread>
#include "SynchronizedBlockingTimer.h"

using namespace std;
using namespace std::chrono;

SynchronizedBlockingTimer::SynchronizedBlockingTimer(milliseconds minDelta)
        : _minDelta(minDelta), _lastUpdateTime(system_clock::now())
{
}

milliseconds SynchronizedBlockingTimer::delta() const {
    lock_guard<mutex> guard(_mutex);
    return duration_cast<milliseconds>(system_clock::now() - _lastUpdateTime);
}

double SynchronizedBlockingTimer::deltaFloatSeconds() const {
    return delta().count() / 1000.0;
}

void SynchronizedBlockingTimer::update() {
    lock_guard<mutex> guard(_mutex);
    const auto dt = system_clock::now() - _lastUpdateTime;
    _lastUpdateTime = system_clock::now();
    if (dt < _minDelta) {
        this_thread::sleep_for(_minDelta - dt);
    }
}

milliseconds SynchronizedBlockingTimer::minDelta() const {
    return _minDelta;
}
