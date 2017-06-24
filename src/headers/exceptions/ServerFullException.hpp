/**
 * @file ServerFullException.h
 * @brief Exception - server is full
 * @author LionZXY
 * @project Recast-server
 * @date 16.06.17
 * @email nikita@kulikof.ru
 *
 * Exception thrown when server is full and user tries to connect
 * 
 **/
#ifndef RECAST_SERVER_SERVERFULLEXCEPTION_H
#define RECAST_SERVER_SERVERFULLEXCEPTION_H


#include <exception>

class ServerFullException : public std::exception {
public:
    const char *what() const throw() {
        return "Server is full!";
    }
};


#endif //RECAST_SERVER_SERVERFULLEXCEPTION_H
