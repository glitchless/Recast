/**
 * @file InvalidLoginOrPassword.h
 * @brief Exception when auth is failed
 * @author LionZXY
 * @project Recast-server
 * @date 17.06.17
 * @email nikita@kulikof.ru
 *
 * Exception throw when auth failed. Login incorrect or password.
 * 
 **/
#ifndef RECAST_SERVER_INVALIDLOGINORPASSWORD_H
#define RECAST_SERVER_INVALIDLOGINORPASSWORD_H

#include <exception>

class InvalidLoginOrPassword : public std::exception {
public:
    const char * what () const throw () {
        return "Invalid login or password. Try again!";
    }
};


#endif //RECAST_SERVER_INVALIDLOGINORPASSWORD_H
