/**
 * @file networking.cpp
 * @brief Basic networking utils source file
 * @author StealthTech
 * @project Recast-server
 * @date 17.06.17
 * @email st3althtech@mail.ru
 *
 **/

#include <iostream>
#include <string.h>
#include <sys/socket.h> // socket(), AF_INET/PF_INET
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h>  // inet_aton()
#include <netdb.h>      // gethostbyname
#include <fcntl.h>
#include <boost/log/trivial.hpp>

#include "network/Networking.hpp"

string int2ipv4(uint32_t ip) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "%u.%u.%u.%u", ip&0xFF, (ip&0xFF00) >> 8, (ip&0xFF0000) >> 16, (ip&0xFF000000) >> 24);
    return buffer;
}

namespace {
    struct sockaddr_in resolve(const char* host, int port) {
        struct hostent* hp = gethostbyname(host);
        if (NULL == hp) {
            throw runtime_error("An exception occurred (resolve error): " + string(strerror(errno)));
        }

        char** pAddress = hp->h_addr_list;
        while(*pAddress) {
            unsigned char *ipf = reinterpret_cast<unsigned char*>(*pAddress);
            uint32_t cur_interface_ip = 0;
            uint8_t *rimap_local_ip_ptr = reinterpret_cast<uint8_t*>(&cur_interface_ip);
            rimap_local_ip_ptr[0] = ipf[0];
            rimap_local_ip_ptr[1] = ipf[1];
            rimap_local_ip_ptr[2] = ipf[2];
            rimap_local_ip_ptr[3] = ipf[3];
            cerr << "Resolved successfully: " << int2ipv4(cur_interface_ip) << endl;
            ++pAddress;
        }

        struct sockaddr_in address;
        memset(&address, 0, sizeof(address));
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        memcpy(&address.sin_addr, hp->h_addr, hp->h_length);

        return address;
    }

    void setNonBlockedImpl(int sd, bool option) noexcept (false) {
        int flags = fcntl(sd, F_GETFL, 0);
        int new_flags = (option)? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
        if (fcntl(sd, F_SETFL, new_flags) == -1) {
            throw runtime_error("An exception occurred (make non-blocked): " + string(strerror(errno)));
        }
    }
} // namespace end //

void Socket::setNonBlocked(bool option) noexcept (false) {
    setNonBlockedImpl(socketDescr, option);
}

void Socket::setReuseAddress(int sd) noexcept (false) {
    int yes = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        ::close(sd);
        throw runtime_error("An exception occurred (setopt reuse): " + string(strerror(errno)));
    }
}

void SocketTCP::setRecvTimeout(int seconds, int microseconds) noexcept (false) {
    struct timeval tv;
    tv.tv_sec = seconds;
    tv.tv_usec = microseconds;

    if (setsockopt(socketDescr, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) != 0) {
        throw runtime_error("set rcvtimeout: " + string(strerror(errno)));
    }
}

void SocketTCP::send(const string &str) noexcept (false) {
    size_t left = str.size();
    ssize_t sent = 0;
    int flags = 0;

    while (left > 0) {
        sent = ::send(socketDescr, str.data() + sent, str.size() - sent, flags);
        if (-1 == sent) {
            throw runtime_error("write failed: " + string(strerror(errno)));
        }

        left -= sent;
    }
}

void SocketTCP::sendBytes(const char *data, size_t num) noexcept (false) {
    size_t left = num;
    ssize_t sent = 0;
    int flags = 0;

    while (left > 0) {
        sent = ::send(socketDescr, data + sent, num - sent, flags);
        if (-1 == sent) {
            throw runtime_error("write failed: " + string(strerror(errno)));
        }

        left -= sent;
    }
}

string SocketTCP::recv(size_t bytes) noexcept (false) {
    char *buffer = new char[bytes];
    size_t r = 0;
    while (r != bytes) {
        ssize_t rc = ::recv(socketDescr, buffer + r, bytes - r, 0);
        cerr << "recv_ex: " << rc << " bytes\n";

        if (rc == -1 || rc == 0) {
            delete [] buffer;
            throw runtime_error("read failed: " + string(strerror(errno)));
        }
        r += rc;
    }
    string ret(buffer, buffer + bytes);
    delete [] buffer;
    return ret;
}

char* SocketTCP::recvBytes(size_t bytes) noexcept (false) {
    char *buffer = new char[bytes];
    size_t r = 0;
    while (r != bytes) {
        ssize_t rc = ::recv(socketDescr, buffer + r, bytes - r, 0);
        cerr << "recv_ex: " << rc << " bytes\n";

        if (rc == -1 || rc == 0) {
            delete [] buffer;
            throw runtime_error("read failed: " + string(strerror(errno)));
        }
        r += rc;
    }
    return buffer;
}

string SocketTCP::recv() noexcept (false) {
    char buffer[256];
#ifdef __APPLE__
    // mac os x doesn't define MSG_NOSIGNAL
    int n = ::recv(socketDescr, buffer, sizeof(buffer), 0);
#else
    int n = ::recv(socketDescr, buffer, sizeof(buffer), MSG_NOSIGNAL);
#endif

    if (-1 == n && errno != EAGAIN) {
        throw runtime_error("read failed: " + string(strerror(errno)));
    }
    if (0 == n) {
        throw runtime_error("client: " + to_string(socketDescr) + " disconnected");
    }
    if (-1 == n) {
        throw runtime_error("client: " + to_string(socketDescr) + " timeouted");
    }

    string ret(buffer, buffer + n);
    while (ret.back() == '\r' || ret.back() == '\n') {
        ret.pop_back();
    }
    cerr << "client: " << socketDescr << ", recv: " << ret << " [" << n << " bytes]" << endl;
    return ret;
}

string SocketTCP::recvTimed(int timeout) noexcept (false) {
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(socketDescr, &read_fds);
    struct timeval tm;
    tm.tv_sec = timeout;
    tm.tv_usec = 0;
    int sel = select(socketDescr + 1, &read_fds, NULL, NULL, &tm); // read, write, exceptions
    if (sel != 1) { throw runtime_error("read timeout"); }

    return recv();
}

bool SocketTCP::hasData() noexcept (false) {
    char buf[1];
    int n = ::recv(socketDescr, buf, sizeof(buf), MSG_PEEK);
    if (n > 0) { return true; }
    return false;
}

void SocketTCP::createServerSocket(uint32_t port, uint32_t queueSize) noexcept (false) {
    int sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd <= 0) {
        throw runtime_error("socket: " + string(strerror(errno)));
    }

    setReuseAddress(sd);

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    if (::bind(sd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        ::close(sd);
        throw runtime_error("bind: " + string(strerror(errno)));
    }

    ::listen(sd, queueSize);
    socketDescr = sd;
    // setNonBlocked(true);
}

void SocketTCP::createServerSocket() noexcept (false) {
    createServerSocket(socketBoundPort, socketQueueSize);
}

shared_ptr<SocketTCP> SocketTCP::accept() noexcept (false) {
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));
    socklen_t cli_len = sizeof(client);

    int cli_sd = ::accept(socketDescr, (struct sockaddr*)&client, &cli_len);
    if (-1 == cli_sd) { return shared_ptr<SocketTCP>(); }
    cerr << "new client: " << cli_sd << ", from: " << int2ipv4(client.sin_addr.s_addr) << endl;

    return make_shared<SocketTCP>(cli_sd);
}


void SocketUDP::sendTo(struct sockaddr_in &sendToAddr, const string &str) noexcept (false) {
    sendto(socketDescr, str.data(), str.size(), 0, (struct sockaddr *) &sendToAddr, sizeof(sendToAddr));
}

void SocketUDP::sendBytesTo(struct sockaddr_in &sendToAddr, const char *data, size_t num) noexcept (false) {
    sendto(socketDescr, data, num, 0, (struct sockaddr *) &sendToAddr, sizeof(sendToAddr));
}

string SocketUDP::recvFrom(struct sockaddr_in &recvFromAddr) noexcept (false) {
    const size_t BUFFER_SIZE = 1024;
    ssize_t numBytes;
    socklen_t socketSize = sizeof(struct sockaddr_in);
    char *buffer = new char[BUFFER_SIZE];
    if ((numBytes = recvfrom(socketDescr, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*) &recvFromAddr, &socketSize) == - 1)) {
        cerr << "[ERR] Recieve failed (recvfrom): " + string(strerror(errno)) << endl;
    }
    BOOST_LOG_TRIVIAL(info) << "[INFO] Recieved message. Data: " << buffer;

    string result = string(buffer);
    delete[] buffer;
    return result;
}

char* SocketUDP::recvBytesFrom(struct sockaddr_in &recvFromAddr) noexcept (false) {
    const size_t BUFFER_SIZE = 1024;
    ssize_t numBytes;
    socklen_t socketSize = sizeof(struct sockaddr_in);
    char *buffer = new char[BUFFER_SIZE];
    if ((numBytes = recvfrom(socketDescr, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*) &recvFromAddr, &socketSize) == - 1)) {
        cerr << "[ERR] Recieve failed (recvfrom): " + string(strerror(errno)) << endl;
    }
    BOOST_LOG_TRIVIAL(info) << "[INFO] Recieved message. Data: " << buffer;

    return buffer;
}

void SocketUDP::createServerSocket(uint32_t port) noexcept (false) {
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

    if (::bind(sd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        ::close(sd);
        throw runtime_error("bind: " + string(strerror(errno)));
    }

    socketDescr = sd;
    // setNonBlocked(true);
}

void SocketUDP::createServerSocket() noexcept (false) {
    createServerSocket(socketBoundPort);
}
