//
// Created by Oleg Morozenkov on 31.05.17.
//

#include <thread>
#include "temperature-world/implementation/SynchronizedBlockingTimer.hpp"

using namespace std;
using namespace std::chrono;

SynchronizedBlockingTimer::SynchronizedBlockingTimer(milliseconds minDelta)
        : _minDelta(minDelta), _lastUpdateTime(system_clock::now()), _isFirstUpdate(true)
{
}

milliseconds SynchronizedBlockingTimer::delta() const {
    lock_guard<mutex> guard(_lastUpdateTimeMutex);
    return duration_cast<milliseconds>(system_clock::now() - _lastUpdateTime);
}

milliseconds SynchronizedBlockingTimer::minDelta() const {
    return _minDelta;
}

double SynchronizedBlockingTimer::deltaFloatSeconds() const {
    return delta().count() / 1000.0;
}

bool SynchronizedBlockingTimer::isFirstUpdate() const {
    lock_guard<mutex> guard(_lastUpdateTimeMutex);
    return _isFirstUpdate;
}

void SynchronizedBlockingTimer::update() {
    lock_guard<mutex> guard(_lastUpdateTimeMutex);
    _lastUpdateTime = system_clock::now();
    _isFirstUpdate = false;
}

void SynchronizedBlockingTimer::wait() {
    milliseconds dt(0);
    {
        lock_guard<mutex> guard(_lastUpdateTimeMutex);
        dt = duration_cast<milliseconds>(system_clock::now() - _lastUpdateTime);
    }
    if (dt < _minDelta) {
        this_thread::sleep_for(_minDelta - dt);
    }
}
