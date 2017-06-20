//
// Created by Oleg Morozenkov on 30.03.17.
//

#include "../src/headers/implementation/BasicTimer.hpp"
#include "../src/headers/types/Parallelepiped.hpp"
#include "../src/headers/injectors/BoundTemperatureWorldInjector.hpp"

#include <memory>
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
    while (true) {
        benchmarkTimer.update();
        updater->update();
        cout << "Update delta: " << benchmarkTimer.deltaFloatSeconds() << "s" << endl;
    }

    return 0;
}
