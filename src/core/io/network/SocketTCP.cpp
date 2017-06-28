/**
 * @file SocketTCP.cpp
 * @brief Socket (TCP) utils source file
 * @author StealthTech
 * @project Recast-server
 * @date 27.06.17
 * @email st3althtech@mail.ru
 *
 **/

#include <cstring>
#include "io/network/SocketTCP.hpp"

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

