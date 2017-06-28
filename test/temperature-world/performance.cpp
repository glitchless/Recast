//
// Created by Oleg Morozenkov on 30.03.17.
//

#include "temperature-world/implementation/BasicTimer.hpp"
#include "temperature-world/types/Parallelepiped.hpp"
#include "temperature-world/injectors/BoundTemperatureWorldInjector.hpp"

#include <iostream>

using namespace std;

int main() {
    Size n = 99;
    Parallelepiped worldBounds(n, n, n);

    BoundTemperatureWorldInjector injector;
    injector.setWorldBounds(worldBounds);

    auto world = injector.world();
    auto updater = injector.updater();

    BasicTimer benchmarkTimer;
    cout << "Number of blocks: " << world->bounds().volume() << endl;
    for (size_t i = 0; i < 5; i++) {
        benchmarkTimer.update();

        updater->update();

        cout << "Update delta: " << benchmarkTimer.deltaFloatSeconds() << "s" << endl;
    }

    return 0;
}
