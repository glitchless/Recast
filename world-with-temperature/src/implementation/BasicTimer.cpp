//
// Created by Oleg Morozenkov on 11.06.17.
//

#include "implementation/BasicTimer.hpp"

using namespace std;
using namespace std::chrono;

BasicTimer::BasicTimer() : _lastUpdateTime(system_clock::now()) {
}

chrono::milliseconds BasicTimer::delta() const {
    return duration_cast<milliseconds>(system_clock::now() - _lastUpdateTime);
}

double BasicTimer::deltaFloatSeconds() const {
    return delta().count() / 1000.0;
}

void BasicTimer::update() {
    _lastUpdateTime = system_clock::now();
}
