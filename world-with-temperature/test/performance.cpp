//
// Created by Oleg Morozenkov on 30.03.17.
//

#include "../src/module.h"
#include "../src/implementation/BasicTimer.h"

#include <memory>
#include <iostream>

using namespace std;
using namespace fruit;

int main() {
    static Size n = 99;
    static Parallelepiped worldBounds(n, n, n);
    Component<ITemperatureWorldBoundable<ITemperatureWorld>, IUpdater> component =
                    WorldWithTemperatureModule::boundTemperatureWorldComponent(worldBounds);
    Injector<ITemperatureWorldBoundable<ITemperatureWorld>, IUpdater> injector(component);

    auto world = injector.get<shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>>();
    auto updater = injector.get<shared_ptr<IUpdater>>();

    BasicTimer benchmarkTimer;
    cout << "Number of blocks: " << world->bounds().volume() << endl;
    while (true) {
        benchmarkTimer.update();
        updater->update();
        cout << "Update delta: " << benchmarkTimer.deltaFloatSeconds() << "s" << endl;
    }

    return 0;
}
