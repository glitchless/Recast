/**
 * @mainpage
 * @file
 * @brief Start point
 * @author LionZXY
 *
 * Start point Recast server. Initializing @see Server and @see MainThread.
 * Init config class @see Config
 **/
#include <Server.h>
#include "stdio.h"
/**
 * @brief Main method :)
 **/
int main(){
    Server *server = Server::initServer();
    server->mainLoop();
    delete server;
    return 0;
}