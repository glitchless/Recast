/**
 * @mainpage
 * @file Main.cpp
 * @brief Start point
 * @author LionZXY
 *
 * Start point Recast server. Initializing @see Server and @see MainThread.
 * Init config class @see Config.
 **/
#include "Server.h"

/**
 * @brief Main method :)
 **/
int main() {
    Server server;
    server.initServer();
    return EXIT_SUCCESS;
}