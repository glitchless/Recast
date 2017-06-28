/**
 * @file SocketUDP.cpp
 * @brief Socket (UDP) utils header file
 * @author StealthTech
 * @project Recast-server
 * @date 27.06.17
 * @email st3althtech@mail.ru
 *
 **/

#include <cstring>
#include "network/SocketUDP.hpp"

using namespace std;

void SocketUDP::sendTo(struct sockaddr_in &sendToAddr, const string &str) noexcept(false) {
    sendto(socketDescr, str.data(), str.size(), 0, (struct sockaddr *) &sendToAddr, sizeof(sendToAddr));
}

void SocketUDP::sendBytesTo(struct sockaddr_in &sendToAddr, const char *data, size_t num) noexcept(false) {
    sendto(socketDescr, data, num, 0, (struct sockaddr *) &sendToAddr, sizeof(sendToAddr));
}

string SocketUDP::recvFrom(struct sockaddr_in &recvFromAddr) noexcept(false) {
    const size_t BUFFER_SIZE = 1024;
    ssize_t numBytes;
    socklen_t socketSize = sizeof(struct sockaddr_in);
    char *buffer = new char[BUFFER_SIZE];
    if ((numBytes = recvfrom(socketDescr, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *) &recvFromAddr, &socketSize) ==
                    -1)) {
        cerr << "[ERR] Recieve failed (recvfrom): " + string(strerror(errno)) << endl;
    }
    BOOST_LOG_TRIVIAL(info) << "[INFO] Recieved message. Data: " << buffer;

    string result = string(buffer);
    delete[] buffer;
    return result;
}

char *SocketUDP::recvBytesFrom(struct sockaddr_in &recvFromAddr) noexcept(false) {
    const size_t BUFFER_SIZE = 1024;
    ssize_t numBytes;
    socklen_t socketSize = sizeof(struct sockaddr_in);
    char *buffer = new char[BUFFER_SIZE];
    if ((numBytes = recvfrom(socketDescr, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *) &recvFromAddr, &socketSize) ==
                    -1)) {
        cerr << "[ERR] Recieve failed (recvfrom): " + string(strerror(errno)) << endl;
    }

    int listenerId = -1;
    char* unpacked = unpack(buffer, BUFFER_SIZE, listenerId);
    BOOST_LOG_TRIVIAL(info) << "[INFO] Recieved message for UDP listener [" << listenerId << "]. Data: " << unpacked;

    return buffer;
}

void SocketUDP::createServerSocket(uint32_t port) noexcept(false) {
    int sd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sd <= 0) {
        throw runtime_error("socket: " + string(strerror(errno)));
    }

    setReuseAddress(sd);

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    if (::bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        ::close(sd);
        throw runtime_error("bind: " + string(strerror(errno)));
    }

    socketDescr = sd;
    // setNonBlocked(true);
}

void SocketUDP::createServerSocket() noexcept(false) {
    createServerSocket(socketBoundPort);
}
