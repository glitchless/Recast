/**
 * @file ServerFullException.h
 * @brief Exceptions when server is full
 * @author LionZXY
 * @project Recast-server
 * @date 16.06.17
 * @email nikita@kulikof.ru
 *
 * Exceptions when server is full and user try connecting
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
