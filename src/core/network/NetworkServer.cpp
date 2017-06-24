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
#include <boost/log/trivial.hpp>

#include "network/Networking.hpp"
#include "network/NetworkServer.hpp"

NetworkServer::NetworkServer(uint32_t port, bool isTCP) : port(port), isTCP(isTCP) { };

void NetworkServer::run() {
    try {
        if (isTCP) {
            SocketTCP sock(port, 25);
            BOOST_LOG_TRIVIAL(info) << "Server is running on port " << port << " for TCP connections";
            fork();

            isRunning = true;
            while (isRunning) {
                shared_ptr<SocketTCP> client = sock.accept();
                listenFor(client);
            }
        } else {
            SocketUDP sock(port);
            BOOST_LOG_TRIVIAL(info) << "Server is running on port " << port << " for UDP connections";
            fork();

            isRunning = true;
            while (isRunning) {
                shared_ptr<SocketUDP> client = make_shared<SocketUDP>(sock);
                listenFor(client);
            }
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}

void NetworkServer::listenFor(shared_ptr<SocketTCP> client) {
    client->setRecvTimeout(30, 0); // s, ms
    while (true) try {
            string request = client->recv();
            string response = exchange(request);
            client->send(response);
        } catch(const exception &e) {
            cerr << "[ERR] An exception occurred: " << e.what() << endl;
            return;
            }
}

void NetworkServer::listenFor(shared_ptr<SocketUDP> client) {
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
