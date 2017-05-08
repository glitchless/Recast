//
// Created by Oleg Morozenkov on 03.04.17.
//

#include <iostream>
#include <sstream>
#include <memory>
#include "crow_all.h"
#include "../src/TemperatureWorld.h"
#include "../src/TemperatureWorldUpdater.h"

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
        for (Coord x = world->getMinX(); x <= world->getMaxX(); x++) {
            for (Coord y = world->getMinY(); y <= world->getMaxY(); y++) {
                for (Coord z = world->getMinZ(); z <= world->getMaxZ(); z++) {
                    json["blocks"][i]["x"] = x;
                    json["blocks"][i]["y"] = y;
                    json["blocks"][i]["z"] = z;
                    json["blocks"][i]["t"] = world->get(x, y, z);
                    i++;
                }
            }
        }
        return json;
    });

    CROW_ROUTE(app, "/update_world")([&updater](){
        updater.update();
        return "OK";
    });

    app.port(18080).multithreaded().run();
}


int main() {
    auto world = shared_ptr<TemperatureWorld>(new TemperatureWorld(10, 10, 10));
    world->amplify(0, 0, 0, 50);
    auto updater = TemperatureWorldUpdater(world);

    startServer(world, updater);

    return 0;
}