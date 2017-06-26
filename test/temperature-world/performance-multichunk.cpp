//
// Created by Oleg Morozenkov on 30.03.17.
//

#include "temperature-world/implementation/BasicTimer.hpp"
#include "temperature-world/types/Parallelepiped.hpp"
#include "temperature-world/injectors/ScalingGeneratableChunkedTemperatureWorldInjector.hpp"

#include <memory>
#include <iostream>

using namespace std;

int main() {
    ScalingGeneratableChunkedTemperatureWorldInjector injector;
    injector.setChunkBounds(Parallelepiped(32, 32, 8));

    auto world = injector.world();
    auto updater = injector.updater();

    for (int ix = -4; ix < 4; ix++) {
        for (int iy = -4; iy < 4; iy++) {
            world->getOrGenerateChunk(ix * injector.chunkBounds().sizeX() + 1, iy * injector.chunkBounds().sizeY() + 1, 0);
        }
    }

    BasicTimer benchmarkTimer;
    for (size_t i = 0; i < 5; i++) {
        benchmarkTimer.update();

        updater->update();

        cout << "Update delta: " << benchmarkTimer.deltaFloatSeconds() << "s" << endl;
    }

    return 0;
}
