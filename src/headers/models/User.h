/**
 * @file PlayerAuth.h
 * @brief //TODO Add brief
 * @author LionZXY
 * @project Recast-server
 * @date 17.06.17
 * @email nikita@kulikof.ru
 * //TODO add comment
 * 
 **/
#ifndef RECAST_SERVER_PLAYERAUTH_H
#define RECAST_SERVER_PLAYERAUTH_H

#include <string>
#include <boost/shared_ptr.hpp>
#include "Player.h"

struct User {
public:
    int id;
    int playerId;
    std::string login;
    std::string password;
    std::shared_ptr<Player> player;

    User() {}

    User(std::string login, std::string password) : login(login), password(password) {}

};


#endif //RECAST_SERVER_PLAYERAUTH_H
