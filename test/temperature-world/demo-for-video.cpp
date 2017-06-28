//
// Created by Oleg Morozenkov on 03.04.17.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <list>
#include "temperature-world/interfaces/ITemperatureWorldBoundable.hpp"
#include "lib/crow_all.h"
#include "temperature-world/interfaces/ITemperatureWorld.hpp"
#include "temperature-world/interfaces/IUpdater.hpp"
#include "temperature-world/injectors/ScalingGeneratableChunkedTemperatureWorldInjector.hpp"
#include "temperature-world/utils/FileUtils.hpp"

using namespace std;
using namespace std::chrono;

static Coord fireballX = 4;
void updateFireball(const shared_ptr<ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkableMutable<ITemperatureWorldChunkable<ITemperatureWorld>>>>>& world) {
    try {
        fireballX += 3;
        for (int i = 0; i < 3; i++) {
            world->set(fireballX + i, 0, 0, 300);
        }
    } catch (exception& ignored) {
    }
}

void startServer(shared_ptr<ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkableMutable<ITemperatureWorldChunkable<ITemperatureWorld>>>>> world, shared_ptr<IUpdater> updater) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return FileUtils::readFile("test/temperature-world/demo-web/index.html");
    });
    CROW_ROUTE(app, "/script.js")([](){
        return FileUtils::readFile("test/temperature-world/demo-web/script.js");
    });
    CROW_ROUTE(app, "/KeyboardState.js")([](){
        return FileUtils::readFile("test/temperature-world/demo-web/KeyboardState.js");
    });
    CROW_ROUTE(app, "/three.min.js")([](){
        return FileUtils::readFile("test/temperature-world/demo-web/three.min.js");
    });

    CROW_ROUTE(app, "/get_world")([&](){
        updater->update();
        updateFireball(world);

        crow::json::wvalue json;
        size_t i = 0;
        world->foreachChunk([&](const shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& chunk) {
            chunk->foreach([&](Coord x, Coord y, Coord z) {
                json["blocks"][i]["x"] = x;
                json["blocks"][i]["y"] = y;
                json["blocks"][i]["z"] = z;
                json["blocks"][i]["t"] = chunk->get(x, y, z);
                i++;
            });
        });
        return json;
    });

    app.port(18080).multithreaded().run();
}

int main() {
    ScalingGeneratableChunkedTemperatureWorldInjector injector;
    injector.setChunkBounds(Parallelepiped(4, 4, 4));

    auto world = injector.world();
    auto updater = injector.updater();

    for (int ix = 0; ix <= 10; ix++) {
        for (int iy = 0; iy <= 1; iy++) {
            for (int iz = 0; iz <= 1; iz++) {
                world->getOrGenerateChunk(ix * injector.chunkBounds().sizeX(), iy * injector.chunkBounds().sizeY(), iz * injector.chunkBounds().sizeZ());
            }
        }
    }

    startServer(world, updater);
    return 0;
}

