/**
 * @file networking.cpp
 * @brief Basic networking utils header file
 * @author StealthTech
 * @project Recast-server
 * @date 17.06.17
 * @email st3althtech@mail.ru
 *
 **/

#ifndef RECAST_NETWORKING_H
#define RECAST_NETWORKING_H

#include <string>
#include <unistd.h>     // close()
#include <memory>

using namespace std;

const int DEFAULT_PORT = 1337;

string int2ipv4(uint32_t ip);

class Socket {
public:
    Socket()       : m_Sd(-1) {}
    Socket(int sd) : m_Sd(sd) {}
    ~Socket()                 { if (m_Sd > 0) ::close(m_Sd); }

    int  sd() const noexcept { return m_Sd; }
    void connect(const string &host, int port)                  throw (exception);
    void connect(const string &host, int port, int timeout)     throw (exception);
    void send(const string &s)                                  throw (exception);
    bool hasData()                                              throw (exception);
    string recv()                                               throw (exception);
    string recv(size_t bytes)                                   throw (exception);
    string recvTimed(int timeout)                               throw (exception);
    void setRcvTimeout(int sec, int microsec)                   throw (exception);
    void setNonBlocked(bool opt)                                throw (exception);
    void setReuseAddr(int sd)                                   throw (exception);
    void createServerSocket(uint32_t port, uint32_t queue_size) throw (exception);
    shared_ptr<Socket> accept()                                 throw (exception);
    void close()                     { ::close(m_Sd); }

    void httpQuery(const string &query, function<void(const std::string &s)> cb) throw (exception) {
        send(query);
        string res = recv();
        cb(res);
    }

private:
    int m_Sd;
};

#endif //RECAST_NETWORKING_H