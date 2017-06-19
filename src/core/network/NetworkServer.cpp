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
        cerr << "Server is running on port " << port << endl;
        if (pid > 0) {
            cerr << "Parent pid: " << getpid() << endl;
        } else {
            cerr << "Child pid: " << getpid() << endl;
        }

        // Endless loop listening to connections
        isRunning = true;
        while(isRunning) {
            shared_ptr<Socket> client = s.accept();
            clientWork(client);
        }
    } catch(const exception &e) {
        cerr << e.what() << endl;
    }
}

void NetworkServer::clientWork(shared_ptr<Socket> client) {
    client->setRcvTimeout(30, 0); // s, ms
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
