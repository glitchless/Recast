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

#include "network/Networking.hpp"

// Global
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

    void setNonBlockedImpl(int sd, bool opt) throw (exception) {
        int flags = fcntl(sd, F_GETFL, 0);
        int new_flags = (opt)? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
        if (fcntl(sd, F_SETFL, new_flags) == -1)
            throw runtime_error("An exception occurred (make non-blocked): " + string(strerror(errno)));
    }
} // namespace end //

void Socket::setNonBlocked(bool opt) throw (exception) {
    setNonBlockedImpl(m_Sd, opt);
}

void Socket::setRcvTimeout(int sec, int microsec) throw (exception) {
    struct timeval tv;
    tv.tv_sec = sec;
    tv.tv_usec = microsec;

    if (setsockopt(m_Sd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) != 0) {
        throw runtime_error("set rcvtimeout: " + string(strerror(errno)));
    }
}

void Socket::setReuseAddr(int sd) throw (exception) {
    int yes = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        ::close(sd);
        throw runtime_error("An exception occurred (setopt): " + string(strerror(errno)));
    }
}


void Socket::connect(const string &host, int port) throw (exception) {
    struct sockaddr_in address = resolve(host.data(), port);

    int sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd <= 0) {
        throw runtime_error("error to create socket: " + string(strerror(errno)));
    }

    int connected = ::connect(sd, (struct sockaddr*)&address, sizeof(address));
    if (connected == -1) {
        ::close(sd);
        throw runtime_error("connect error: " + string(strerror(errno)));
    }

    m_Sd = sd;
}

void Socket::connect(const string &host, int port, int timeout) throw (exception) {
    struct sockaddr_in address = resolve(host.data(), port);

    int sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd <= 0) {
        throw runtime_error("error to create socket: " + string(strerror(errno)));
    }

    setNonBlockedImpl(sd, true);

    int connected = ::connect(sd, (struct sockaddr*)&address, sizeof(address));
    if (connected == -1 && errno != EINPROGRESS) {
        ::close(sd);
        throw runtime_error("connect error: " + string(strerror(errno)));
    }

    fd_set write_fds;
    FD_ZERO(&write_fds);
    FD_SET(sd, &write_fds);
    struct timeval tm;
    tm.tv_sec = timeout;
    tm.tv_usec = 0;
    int sel = select(sd + 1, /*read*/NULL, /*write*/&write_fds, /*exceptions*/NULL, &tm);

    if (sel != 1) {
        ::close(sd);
        throw runtime_error("connect timeout");
    }

    m_Sd = sd;
}


void Socket::send(const string &str) throw (exception) {
    size_t left = str.size();
    ssize_t sent = 0;
    int flags = 0;

    while (left > 0) {
        sent = ::send(m_Sd, str.data() + sent, str.size() - sent, flags);
        if (-1 == sent) {
            throw runtime_error("write failed: " + string(strerror(errno)));
        }

        left -= sent;
    }
}

string Socket::recv(size_t bytes) throw (exception) {
    char *buf = new char[bytes];
    size_t r = 0;
    while (r != bytes) {
        ssize_t rc = ::recv(m_Sd, buf + r, bytes - r, 0);
        cerr << "recv_ex: " << rc << " bytes\n";

        if (rc == -1 || rc == 0) {
            delete [] buf;
            throw runtime_error("read failed: " + string(strerror(errno)));
        }
        r += rc;
    }
    string ret(buf, buf + bytes);
    delete [] buf;
    return ret;
}

namespace {
    bool parseProtocol(const string &buf, size_t &bytesLeft) {
        string::size_type hdr_end_pos = buf.find("\r\n\r\n");
        if (hdr_end_pos == string::npos) { return false; }

        string body = buf.substr(hdr_end_pos + 4, string::npos);

        string::size_type pos = buf.find("Content-Length: ");
        if (pos == string::npos) {
            throw runtime_error("http broken");
        }

        string::size_type length_pos = pos + strlen("Content-Length: ");
        size_t contentLength = stoi(buf.substr(length_pos, buf.find("\r\n", length_pos)));

        bytesLeft = contentLength - body.size();
        return true;
    }
} // namespace end //

string Socket::recv() throw (exception) {
    char buffer[256];
#ifdef __APPLE__
    // mac os x doesn't define MSG_NOSIGNAL
    int n = ::recv(m_Sd, buffer, sizeof(buffer), 0);
#else
    int n = ::recv(m_Sd, buffer, sizeof(buffer), MSG_NOSIGNAL);
#endif

    if (-1 == n && errno != EAGAIN) {
        throw runtime_error("read failed: " + string(strerror(errno)));
    }
    if (0 == n) {
        throw runtime_error("client: " + to_string(m_Sd) + " disconnected");
    }
    if (-1 == n) {
        throw runtime_error("client: " + to_string(m_Sd) + " timeouted");
    }

    string ret(buffer, buffer + n);
    while (ret.back() == '\r' || ret.back() == '\n') {
        ret.pop_back();
    }
    cerr << "client: " << m_Sd << ", recv: " << ret << " [" << n << " bytes]" << endl;
    return ret;
}


string Socket::recvTimed(int timeout) throw (exception) {
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(m_Sd, &read_fds);
    struct timeval tm;
    tm.tv_sec = timeout;
    tm.tv_usec = 0;
    int sel = select(m_Sd + 1, &read_fds, NULL, NULL, &tm); // read, write, exceptions
    if (sel != 1) {
        throw runtime_error("read timeout");
    }

    return recv();
}


bool Socket::hasData() throw (exception) {
    char buf[1];
    int n = ::recv(m_Sd, buf, sizeof(buf), MSG_PEEK);
    if (n > 0) return true;
    return false;
}

void Socket::createServerSocket(uint32_t port, uint32_t listenQueueSize) throw (exception) {
    int sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd <= 0) {
        throw runtime_error("socket: " + string(strerror(errno)));
    }

    setReuseAddr(sd);

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    if (::bind(sd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        ::close(sd);
        throw runtime_error("bind: " + string(strerror(errno)));
    }

    ::listen(sd, listenQueueSize);
    m_Sd = sd;
}

shared_ptr<Socket> Socket::accept() throw (exception) {
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));
    socklen_t cli_len = sizeof(client);

    int cli_sd = ::accept(m_Sd, (struct sockaddr*)&client, &cli_len);
    if (-1 == cli_sd)
        return shared_ptr<Socket>();
    cerr << "new client: " << cli_sd << ", from: " << int2ipv4(client.sin_addr.s_addr) << endl;

    return make_shared<Socket>(cli_sd);
}
