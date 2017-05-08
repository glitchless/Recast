//
// Created by Oleg Morozenkov on 30.03.17.
//

#include "TemperatureWorld.h"
#include "TemperatureWorldUpdater.h"

#include <memory>
#include <unistd.h>
#include <iostream>

using namespace std;

int main() {
    auto world = shared_ptr<TemperatureWorld>(new TemperatureWorld(10, 10, 10));
    auto updater = TemperatureWorldUpdater(world);

    const float kTickDelay = 0.5;
    while (true) {
        updater.update(kTickDelay);
        usleep((useconds_t) (kTickDelay * 1000000));
        cout << "Tick (delta time = " << kTickDelay << "s)" << endl;
    }

    return 0;
}