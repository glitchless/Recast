//
// Created by Oleg Morozenkov on 03.04.17.
//

#include <iostream>
#include <sstream>
#include <memory>
#include "crow_all.h"
#include "../src/TemperatureWorld.h"
#include "../src/TemperatureWorldUpdater.h"
#include "../src/utils/TemperatureWorldUtils.h"
#include "../src/utils/TimeUtils.h"

using namespace std;


string readFile(const string& fileName) {
    ifstream file(fileName);
    ostringstream output;
    output << file.rdbuf();
    return output.str();
}


void startServer(shared_ptr<TemperatureWorld> world, TemperatureWorldUpdater& updater) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return readFile("world-with-temperature/test/demo-web/index.html");
    });
    CROW_ROUTE(app, "/script.js")([](){
        return readFile("world-with-temperature/test/demo-web/script.js");
    });
    CROW_ROUTE(app, "/KeyboardState.js")([](){
        return readFile("world-with-temperature/test/demo-web/KeyboardState.js");
    });
    CROW_ROUTE(app, "/three.min.js")([](){
        return readFile("world-with-temperature/test/demo-web/three.min.js");
    });

    CROW_ROUTE(app, "/get_world")([world](){
        crow::json::wvalue json;
        size_t i = 0;
        world->foreach([&world, &json, &i](Coord x, Coord y, Coord z) {
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


void startUpdater(TemperatureWorldUpdater& updater) {
    const float iterationTime = 0.2;
    thread t([&updater, iterationTime]() {
        while (true) {
            updater.update(iterationTime);
        }
    });
    t.detach();
}


int main() {
    shared_ptr<TemperatureWorld> world(new TemperatureWorld(10, 10, 10));
    TemperatureWorldUpdater updater(world);

//    for (Coord x = -2; x <= 2; x++) {
//        for (Coord z = -2; z <= 2; z++) {
//            world->set(x, world->getMaxY(), z, 1000);
//        }
//    }
    for (Coord x = -2; x <= 2; x++) {
        for (Coord y = -2; y <= 2; y++) {
            for (Coord z = -2; z <= 2; z++) {
                world->set(x, y, z, 100);
            }
        }
    }

    startUpdater(updater);
    startServer(world, updater);
    return 0;
}