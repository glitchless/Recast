//
// Created by Oleg Morozenkov on 30.03.17.
//

/*
#include "../src/ITemperatureWorld.h"
#include "../src/ITemperatureWorldUpdater.h"

#include <memory>
#include <unistd.h>
#include <iostream>

using namespace std;

int main() {
    const size_t n = 999999;
    auto world = shared_ptr<ITemperatureWorld>(new ITemperatureWorld(n, n, n));
    auto updater = ITemperatureWorldUpdater(world);

    const float kTickDelay = 0.5;
    while (true) {
        updater.update(kTickDelay);
        usleep((useconds_t) (kTickDelay * 1000000));
        cout << "Tick (delta time = " << kTickDelay << "s)" << endl;
    }

    return 0;
}
*/
