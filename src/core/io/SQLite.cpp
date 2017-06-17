/**
 * @file SQLite.cpp
 * @brief Nice case for sqlite_orm
 * @author LionZXY
 * @project Recast-server
 * @date 17.06.17
 * @email nikita@kulikof.ru
 * 
 **/
#include <list>
#include "exceptions/InvalidLoginOrPassword.h"
#include "io/SQLite.h"

using namespace sqlite_orm;
using namespace std;

User SQLite::registerUser(string login, string password) {
    User user(login, password);
    user.id = storage.insert(user);

    Player player(Point(0, 0, 0));
    player.userId = user.id;
    player.id = storage.insert(player);

    user.player = make_shared<Player>(player);
    user.playerId = player.id;
    storage.update(user);

    return user;
}

User SQLite::authUser(string login, string password) {
    auto users = storage.get_all<User>(where(is_equal(&User::login, login)));
    for (auto &user : users) {
        if (user.password == password) {
            if (auto player = storage.get_no_throw<Player>(user.playerId)) {
                user.player = player;
            }
            return user;
        }
    }
    throw InvalidLoginOrPassword();
}

void SQLite::update(Player player) {
    storage.update(player);
}
