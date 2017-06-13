#include <iostream>
#include <thread>
#include "networking.hpp"

void runServer(uint32_t &port);
void directProvide(int argc, char *argv[], uint32_t &port);
void clientWork(std::shared_ptr<Socket> client);
std::string exchange(const std::string action);
std::string check(const std::string action);

int main(int argc, char *argv[]) {
    // Getting port somehow (defaults?)
    uint32_t port = 8888;
    // External terminal usage to set the port manually
    if (argc == 2) { directProvide(argc, argv, port); }
    // Server initialization
    runServer(port);

    return 0;
}

void runServer(uint32_t &port) {
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
        bool trigger = true;
        while(trigger) {
            std::shared_ptr<Socket> client = s.accept();
            clientWork(client);
        }
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}


void directProvide(int argc, char *argv[], uint32_t &port) {
    if (argc == 2) {
        try {
            port = static_cast<uint32_t >(std::stoi(std::string(argv[1])));
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}


void clientWork(std::shared_ptr<Socket> client) {
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

std::string exchange(const std::string action) {
    // Game logic goes here

    // Answer to client (difference snapshots? yes/no answer?)
    std::string state = check(action);

    return state;
}

std::string check(const std::string action) {
    // Example
    std::string result = "DENIED";
    if (action.find("CAST") != -1) {
        // Checking appliability
        result = "APPLIED";
    }
    return result;
}
