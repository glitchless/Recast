/**
 * @file Main.cpp
 * @brief Starting point
 * @author LionZXY
 *
 * Starting point for Recast server. Initializing @see Server and @see MainThread.
 * Init config class @see Config.
 **/
#include <cstdlib>
#include <spells/Spell.hpp>
#include <spells/nodes/HeaterNode.hpp>
#include <spells/nodes/GeneratorNode.h>
#include <io/network/listeners/GetEntitys.h>

/**
 * @brief Main method :)
 **/
int main() {
    Server server;
    server.initServer();
    return EXIT_SUCCESS;
}
