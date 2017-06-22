/**
 * @file Main.cpp
 * @brief Starting point
 * @author LionZXY
 *
 * Starting point for Recast server. Initializing @see Server and @see MainThread.
 * Init config class @see Config.
 **/
#include <spells/nodes/EnergyNode.h>
#include <boost/log/trivial.hpp>
#include <spells/Spell.h>

/**
 * @brief Main method :)
 **/
int main() {
    Spell spell;
    spell.getRootNode()->connectNode(new EnergyNode(1, 1, 1, 100));

    while (true) {
        node.tick(NULL);
    }
    return EXIT_SUCCESS;
}
