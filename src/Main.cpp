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
    EnergyNode node(0, 0, 0, 10);
    EnergyNode node2(0, 0, 1, 100);
    EnergyNode node3(0, 0, 2, 70);
    EnergyNode node4(0, 0, 3, 0);
    node.connectNode(&node2);
    node.connectNode(&node3);
    node.connectNode(&node4);
    while (true) {
        node.tick(NULL);
    }
    return EXIT_SUCCESS;
}
