/**
 * @file Socket.cpp
 * @brief Socket abstract utils header file
 * @author StealthTech
 * @project Recast-server
 * @date 27.06.17
 * @email st3althtech@mail.ru
 *
 **/

#include <cstring>
#include "network/Socket.hpp"
using namespace std;

void setNonBlockedImpl(int sd, bool option) noexcept (false) {
    int flags = fcntl(sd, F_GETFL, 0);
    int new_flags = (option)? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    if (fcntl(sd, F_SETFL, new_flags) == -1) {
        throw runtime_error("An exception occurred (make non-blocked): " + string(strerror(errno)));
    }
}

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
