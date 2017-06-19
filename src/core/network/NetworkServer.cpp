/**
 * @file server.cpp
 * @brief Networking server source file
 * @author StealthTech
 * @project Recast-server
 * @date 17.06.17
 * @email st3althtech@mail.ru
 *
 **/

#include <iostream>
#include <thread>
#include <memory>
#include <sys/socket.h>

#include "network/Networking.hpp"
#include "network/NetworkServer.hpp"

NetworkServer::NetworkServer(uint32_t PortTCP, uint32_t PortUDP) : portTCP(PortTCP), portUDP(PortUDP) { };

void NetworkServer::run() {
    try {
        Socket sockTCP;
        sockTCP.createServerSocketTCP(portTCP, 25);
        cerr << "Server is running on port " << portTCP << " for TCP connections" << endl;

        Socket sockUDP;
        sockUDP.createServerSocketUDP(portUDP);
        cerr << "Server is running on port " << portUDP << " for UDP connections" << endl;

        // Creating serving processes

        pid_t pid = fork();

        if (pid > 0) {
            cerr << "Parent pid: " << getpid() << endl;
        } else {
            cerr << "Child pid: " << getpid() << endl;
        }

        // Endless loop listening to connections
        isRunning = true;
        while(isRunning) {
            shared_ptr<Socket> clientTCP = sockTCP.accept();
            clientWork(clientTCP);
            shared_ptr<Socket> clientUDP = make_shared<Socket>(sockUDP);
            clientWork(clientUDP);
        }
    } catch(const exception &e) {
        cerr << e.what() << endl;
    }
}

void NetworkServer::clientWork(shared_ptr<Socket> client) {
    client->setRecvTimeout(30, 0); // s, ms
    while (true) try {
            string request = client->recv();
            string response = exchange(request);
            client->send(response);
        } catch(const exception &e) {
            cerr << "An exception occurred: " << e.what() << endl;
            return;
        }
}

void NetworkServer::shutdown() {
    isRunning = false;
}

string NetworkServer::exchange(const string action) {
    // Game logic goes here

    // Answer to client (difference snapshots? yes/no answer?)
    string state = check(action);

    return state;
}

string NetworkServer::check(const string action) {
    // Example
    string result = "DENIED";
    if (action.find("CAST") != -1) {
        // Checking appliability
        result = "APPLIED";
    }
    return result;
}
