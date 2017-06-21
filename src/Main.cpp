/**
 * @file Main.cpp
 * @brief Starting point
 * @author LionZXY
 *
 * Starting point for Recast server. Initializing @see Server and @see MainThread.
 * Init config class @see Config.
 **/
#include <spells/EnergyNode.h>
#include <iostream>
#include <boost/log/trivial.hpp>

/**
 * @brief Main method :)
 **/
int main() {
    Config::g("spell.general.tax",
                            0.001F);
    Config::g("spell.general.max_transfer",
                            0.1F);
    Config::instance()->save();
    EnergyNode node(0, 0, 0, -100);
    EnergyNode node2(0, 0, 1, 0);
    EnergyNode node3(0, 0, 2, 0);
    EnergyNode node4(0, 0, 3, 0);
    node.connectNode(&node2);
    node.connectNode(&node3);
    node.connectNode(&node4);
    while (true) {
        node.tick(NULL);
    }
    return EXIT_SUCCESS;
}
