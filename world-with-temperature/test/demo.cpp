//
// Created by Oleg Morozenkov on 03.04.17.
//

#include <iostream>
#include "lib/crow_all.h"
#include "../src/interfaces/ITemperatureWorld.h"
#include "../src/interfaces/IUpdater.h"
#include "../src/module.h"
#include "../src/utils/FileUtils.h"

using namespace std;
using namespace fruit;

void startUpdater(shared_ptr<IUpdater> updater) {
    thread t([&updater]() {
        while (true) {
            updater->update();
        }
    });
    t.detach();
}

void startServer(shared_ptr<ITemperatureWorldBoundable> world, shared_ptr<IUpdater> updater) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return FileUtils::readFile("world-with-temperature/test/demo-web/index.html");
    });
    CROW_ROUTE(app, "/script.js")([](){
        return FileUtils::readFile("world-with-temperature/test/demo-web/script.js");
    });
    CROW_ROUTE(app, "/KeyboardState.js")([](){
        return FileUtils::readFile("world-with-temperature/test/demo-web/KeyboardState.js");
    });
    CROW_ROUTE(app, "/three.min.js")([](){
        return FileUtils::readFile("world-with-temperature/test/demo-web/three.min.js");
    });

    CROW_ROUTE(app, "/get_world")([&](){
        crow::json::wvalue json;
        size_t i = 0;
        world->foreach([&](Coord x, Coord y, Coord z) {
            json["blocks"][i]["x"] = x;
            json["blocks"][i]["y"] = y;
            json["blocks"][i]["z"] = z;
            json["blocks"][i]["t"] = world->get(x, y, z);
            i++;
        });
        return json;
    });

    app.port(18080).multithreaded().run();
}

int main() {
    static Size worldWidth = 10;
    static Size worldHeight = 10;
    static Size worldDepth = 10;
    Component<ITemperatureWorldBoundable, IUpdater> component =
                    WorldWithTemperatureModule::boundTemperatureWorldComponent(worldWidth, worldHeight, worldDepth);
    Injector<ITemperatureWorldBoundable, IUpdater> injector(component);

    auto world = injector.get<shared_ptr<ITemperatureWorldBoundable>>();
    auto updater = injector.get<shared_ptr<IUpdater>>();

    for (Coord x = -2; x <= 2; x++) {
        for (Coord z = -2; z <= 2; z++) {
            world->set(x, world->maxY(), z, 750);
        }
    }

    startUpdater(updater);
    startServer(world, updater);
    return 0;
}

