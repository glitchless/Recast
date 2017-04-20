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


void startServer() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/index.html")([](){
        return readFile("/index.html");
    });
    CROW_ROUTE(app, "/script.js")([](){
        return readFile("/script.js");
    });
    CROW_ROUTE(app, "/three.min.js")([](){
        return readFile("/three.min.js");
    });

    CROW_ROUTE(app, "/get_world")([](){
        // TODO
        ostringstream output;
//        output <<
        return output.str();
    });

    CROW_ROUTE(app, "/update_world")([](){
        // TODO
        ostringstream output;
        return output.str();
    });

    app.port(18080).multithreaded().run();
}


void initWorld() {
    auto world = shared_ptr<TemperatureWorld>(new TemperatureWorld(10, 10, 10));
    auto updater = TemperatureWorldUpdater(world);
    // TODO
}


int main() {
    initWorld();
    startServer();
    return 0;
}