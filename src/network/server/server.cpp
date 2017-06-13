#include <iostream>
#include <thread>
#include "networking.hpp"

const uint32_t port = 8888;

void client_work(std::shared_ptr<Socket> client);
std::string exchange(const std::string action);
std::string checkAppliability(const std::string action);

int main(int argc, char *argv[]) {
    /* Terminal usage
    // Incorrect run parameter (must be exactly 1 additional)
    // Getting run port
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " port" << std::endl;
        return 0;
    }
    int port_ = std::stoi(std::string(argv[1]));
    */
    try {
        Socket s;
        s.createServerSocket(port, 25);

        // Creating serving processes
        pid_t pid = fork();
        if (pid > 0) {
            std::cerr << "parent pid: " << getpid() << std::endl;
        } else {
            std::cerr << "child pid: " << getpid() << std::endl;
        }

        // Endless loop listening to connections
        while(true) {
            std::shared_ptr<Socket> client = s.accept();
            client_work(client);
        }
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}


void client_work(std::shared_ptr<Socket> client) {
    client->setRcvTimeout(/*sec*/30, /*microsec*/0);
    while (true) try {
            std::string line = client->recv();
            std::string response = exchange(line);

            client->send(response);
        }
        catch(const std::exception &e) {
            std::cerr << "exception: " << e.what() << std::endl;
            return;
        }
}

std::string exchange(const std::string action) {
    // Game logic goes here

    // Answer to client (difference snapshots? yes/no answer?)
    std::string state = checkAppliability(action);

    return state;
}

std::string checkAppliability(const std::string action) {
    // Example
    std::string result = "DENIED";
    if (action.find("CAST") != -1) {
        // Checking appliability
        result = "APPLIED";
    }
    return result;
}