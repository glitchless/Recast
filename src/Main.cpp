/**
 * @file Main.cpp
 * @brief Starting point
 * @author LionZXY
 *
 * Starting point for Recast server. Initializing @see Server and @see MainThread.
 * Init config class @see Config.
 **/
#include <spells/nodes/EnergyNode.h>
#include <spells/Spell.h>
#include <spells/nodes/HeaterNode.h>
#include <Server.h>

/**
 * @brief Main method :)
 **/
int main() {
    Server server;
    server.initServer();
    return EXIT_SUCCESS;
}
