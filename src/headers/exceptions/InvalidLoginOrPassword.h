/**
 * @file InvalidLoginOrPassword.h
 * @brief //TODO Add brief
 * @author LionZXY
 * @project Recast-server
 * @date 17.06.17
 * @email nikita@kulikof.ru
 * //TODO add comment
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
