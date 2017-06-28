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
#include <spells/nodes/EnergyNode.hpp>
#include <spells/Spell.hpp>
#include <io/network/listeners/GetEntitys.h>

#include "io/SQLite.hpp"
#include "models/collections/PlayersOnline.hpp"
#include "temperature-world/injectors/ScalingGeneratableChunkedTemperatureWorldInjector.hpp"
#include "spells/nodes/HeaterNode.hpp"
#include "spells/nodes/GeneratorNode.h"

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

    for (int ix = -4; ix < 4; ix++) {
        for (int iy = -4; iy < 4; iy++) {
            temperatureWorld->getOrGenerateChunk(ix * injector.chunkBounds().sizeX(), iy * injector.chunkBounds().sizeY(), 0);
        }
    }
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

    Spell *spell = new Spell();
    SpellNode *node = new HeaterNode(1, 1, 1, 0);
    node->connectNode(new GeneratorNode(2, 2, 2, 0));
    spell->getRootNode()->connectNode(node);
    b2Vec2 pos(0.0f, 0.0f);
    world.subscribeToUpdate((Entity *) world.createSpellEntity(pos, spell));
    while (isRunning()) {
        update();
    }
}

void Server::update() {
    temperatureWorldUpdater->update();
    world.update();
    inputObject->getManager()->executeDelayedCommandInUI();
    for (Entity &entity : world.getAllEntityInChunk(-100.0f, 100.0f)) {
        BOOST_LOG_TRIVIAL(info) << entity.getType();
    }
}

Server::Server() : world(this) {
    isLaunching = false;

    uint32_t portTCP = static_cast<uint32_t>(Config::g("general.server.port.tcp", DEFAULT_PORT_TCP));
    uint32_t portUDP = static_cast<uint32_t>(Config::g("general.server.port.udp", DEFAULT_PORT_UDP));

    serverTCP = new NetworkServer(portTCP, this, true);
    serverUDP = new NetworkServer(portUDP, this, false);

    players = new PlayersOnline(Config::instance()->get("server.max_players", 20));
}

void Server::runNetworkServer(NetworkServer *tcp, NetworkServer *udp) {
    tcp->registerListener(new DebugNetworkListener(0));
    udp->registerListener(new DebugNetworkListener(0));
    tcp->registerListener(new GetEntitys());
    udp->registerListener(new GetEntitys());
    listenUDPThread = thread(&NetworkServer::run, udp);
    listenUDPThread.detach();
    listenTCPThread = thread(&NetworkServer::run, tcp);
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
