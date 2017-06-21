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
#include <netinet/in.h> // struct sockaddr_in
#include <thread>

#include "network/Networking.hpp"
#include "network/NetworkServer.hpp"

NetworkServer::NetworkServer(uint32_t port, bool isTCP) : port(port), isTCP(isTCP) { };

void NetworkServer::run() {
    try {
        Socket sock;
        if (isTCP) {
            sock.createServerSocketTCP(port, 25);
            cerr << "Server is running on port " << port << " for TCP connections" << endl;
        } else {
            sock.createServerSocketUDP(port);
            cerr << "Server is running on port " << port << " for UDP connections" << endl;
        }

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
            if (isTCP) {
                shared_ptr<Socket> clientTCP = sock.accept();
                clientWork(clientTCP);
            } else {
                shared_ptr<Socket> clientUDP = make_shared<Socket>(sock);
                clientWork(clientUDP);
            }
        }
    } catch(const exception &e) {
        cerr << e.what() << endl;
    }
}

void NetworkServer::clientWork(shared_ptr<Socket> client) {
    if (isTCP) {
        // TCP
        client->setRecvTimeout(30, 0); // s, ms
        while (true) try {
                string request = client->recv();
                string response = exchange(request);
                client->send(response);
            } catch(const exception &e) {
                cerr << "[ERR] An exception occurred: " << e.what() << endl;
                return;
            }
    } else {
        // UDP
        while(true) try {
                struct sockaddr_in senderAddr;
                string request = client->recvFrom(senderAddr);
                string response = exchange(request);
                client->sendTo(senderAddr, response);
            } catch(const exception &e) {
                cerr << "[ERR] An exception occurred: " << e.what() << endl;
                return;
            }
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
