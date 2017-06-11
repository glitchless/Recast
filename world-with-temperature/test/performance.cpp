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
    using namespace BoundTemperatureWorldAnnotations;

    static Size n = 99;
    static Size worldWidth = n;
    static Size worldHeight = n;
    static Size worldDepth = n;
    Component<IBoundTemperatureWorld, ITemperatureWorldUpdater> component =
            createComponent()
                    .install(WorldWithTemperatureModule::component())
                    .bindInstance<Annotated<Width, Size>>(worldWidth)
                    .bindInstance<Annotated<Height, Size>>(worldHeight)
                    .bindInstance<Annotated<Depth, Size>>(worldDepth);
    Injector<IBoundTemperatureWorld, ITemperatureWorldUpdater> injector(component);

    auto world = injector.get<shared_ptr<IBoundTemperatureWorld>>();
    auto updater = injector.get<shared_ptr<ITemperatureWorldUpdater>>();

    BasicTimer benchmarkTimer;
    cout << "Number of blocks: " << world->sizeX() * world->sizeY() * world->sizeZ() << endl;
    while (true) {
        benchmarkTimer.update();
        updater->update();
        cout << "Update delta: " << benchmarkTimer.deltaFloatSeconds() << "s" << endl;
    }

    return 0;
}
