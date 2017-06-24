/**
 * @file Server.cpp
 * @brief Config file
 * @author LionZXY
 * @project Recast
 * @email nikita@kulikof.ru
 * @date 08.06.17
 *
 * Server file description
 *
 **/

#include <boost/log/trivial.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/filesystem.hpp>
#include <Box2D/Box2D.h>

#include "Server.hpp"
#include "io/SQLite.hpp"
#include "io/configs/Config.hpp"
#include "models/collections/PlayersOnline.hpp"
#include "temperature-world/injectors/ScalingGeneratableChunkedTemperatureWorldInjector.hpp"

using namespace std;
using namespace boost;

void initLogger() {
    string output = (string("recast_") + to_string(time(NULL)) + string(".log"));
    filesystem::path dir("./logs/");
    if (!filesystem::exists(dir)) {
        if (filesystem::create_directory(dir)) {
            BOOST_LOG_TRIVIAL(info) << "Folder " << dir << " create successful";
        } else {
            BOOST_LOG_TRIVIAL(info) << "Failed create dir: " << dir;
        }
    }
    log::add_file_log(dir.string() + output);
    log::add_console_log(std::cout);
}

void Server::initTemperatureWorld() {
    ScalingGeneratableChunkedTemperatureWorldInjector injector;
    temperatureWorld = injector.world();
    temperatureWorldUpdater = injector.updater();

    temperatureWorld->getOrGenerateChunk(0, 0, 0);
}

void Server::initServer() {
    initLogger();
    initTemperatureWorld();

    BOOST_LOG_TRIVIAL(info) << "Initializing server...";
    isLaunching = true;
    inputObject = new InputThread(this);
    inputThread = thread(&InputThread::init, inputObject);
    inputThread.detach();

    BOOST_LOG_TRIVIAL(info) << "Initializing network...";
    runNetworkServer(serverTCP, serverUDP);

    b2Vec2 gravity(0.0f, -10.0f);
}

void Server::update() {
    //temperatureWorldUpdater->update();
}

Server::Server() {
    isLaunching = false;

    uint32_t portTCP = static_cast<uint32_t>(Config::instance()->get("general.server.port.tcp", DEFAULT_PORT_TCP));
    uint32_t portUDP = static_cast<uint32_t>(Config::instance()->get("general.server.port.udp", DEFAULT_PORT_UDP));

    serverTCP = new NetworkServer(portTCP, true);
    serverUDP = new NetworkServer(portUDP, false);

    players = new PlayersOnline(Config::instance()->get("server.max_players", 20));
}

void Server::runNetworkServer(NetworkServer *tcp, NetworkServer *udp) {
    listenUDPThread = thread(&NetworkServer::run, tcp);
    listenUDPThread.detach();
    listenTCPThread = thread(&NetworkServer::run, udp);
    listenTCPThread.detach();
}

bool Server::shutdown() {
    serverTCP->shutdown();
    serverUDP->shutdown();
    return isLaunching ? !(isLaunching = false) : false; // Return true if isLaunching equals true
}

void Server::onMessage(const std::string &msg) {
    BOOST_LOG_TRIVIAL(info) << msg;
}

Server::~Server() {
    delete serverTCP;
    delete serverUDP;
    delete inputObject;
    delete Config::instance();
}
