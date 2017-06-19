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
#include <exceptions/InvalidLoginOrPassword.hpp>

#include "io/SQLite.hpp"
#include "configs/Config.hpp"
#include "Server.hpp"
#include "threads/InputThread.hpp"
#include "models/collections/PlayersOnline.hpp"

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

void Server::initServer() {
    initLogger();
    BOOST_LOG_TRIVIAL(info) << "Initializing server...";
    isLaunching = true;
    inputThread = thread(&InputThread::init, InputThread(this));
    inputThread.detach();

    BOOST_LOG_TRIVIAL(info) << "Initializing network...";
    networkServer->run();
}

Server::Server() {
    isLaunching = false;

    uint32_t port = static_cast<uint32_t>(Config::instance()->get("general.server.port", DEFAULT_PORT));
    networkServer = new NetworkServer(port);

    players = new PlayersOnline(Config::instance()->get("server.max_players", 20));
}

bool Server::shutdown() {
    networkServer->shutdown();
    return isLaunching ? !(isLaunching = false) : false; // Return true if isLaunching equals true
}

void Server::onMessage(const std::string &msg) {
    BOOST_LOG_TRIVIAL(info) << msg;
}

Server::~Server() {
    delete Config::instance();
}
