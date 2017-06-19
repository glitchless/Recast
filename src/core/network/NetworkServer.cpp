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

#include "network/Networking.hpp"
#include "network/NetworkServer.hpp"

NetworkServer::NetworkServer(uint32_t Port) : port(Port) { };

void NetworkServer::run() {
    try {
        Socket s;
        s.createServerSocket(port, 25);

        // Creating serving processes
        pid_t pid = fork();
        std::cerr << "Server is running on port " << port << std::endl;
        if (pid > 0) {
            std::cerr << "Parent pid: " << getpid() << std::endl;
        } else {
            std::cerr << "Child pid: " << getpid() << std::endl;
        }

        // Endless loop listening to connections
        isRunning = true;
        while(isRunning) {
            std::shared_ptr<Socket> client = s.accept();
            clientWork(client);
        }
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void NetworkServer::clientWork(std::shared_ptr<Socket> client) {
    client->setRcvTimeout(30, 0); // s, ms
    while (true) try {
            std::string request = client->recv();
            std::string response = exchange(request);
            client->send(response);
        } catch(const std::exception &e) {
            std::cerr << "An exception occurred: " << e.what() << std::endl;
            return;
        }
}

void NetworkServer::shutdown() {
    isRunning = false;
}

std::string NetworkServer::exchange(const std::string action) {
    // Game logic goes here

    // Answer to client (difference snapshots? yes/no answer?)
    std::string state = check(action);

    return state;
}

std::string NetworkServer::check(const std::string action) {
    // Example
    std::string result = "DENIED";
    if (action.find("CAST") != -1) {
        // Checking appliability
        result = "APPLIED";
    }
    return result;
}
