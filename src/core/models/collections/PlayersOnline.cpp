/**
 * @file PlayersOnline.cpp
 * @brief PlayerOnline class
 * @author LionZXY
 * @project Recast-server
 * @date 16.06.17
 * @email nikita@kulikof.ru
 *
 * Player online thread-safetly class
 * 
 **/

#include <exceptions/ServerFullException.h>
#include "models/collections/PlayersOnline.h"
#include "utils/Utils.h"

using namespace std;

string PlayersOnline::registerPlayer(Player player) {
    if (currentPlayers == maxPlayer) {
        throw ServerFullException();
    }
    string session = genRandomString(SESSION_LENGTH);
    lock_guard<mutex> locker(lock_writing);
    players[session] = new Player(player);
    currentPlayers++;
    return session;
}

bool PlayersOnline::logout(const std::string &session) {
    lock_guard<mutex> locker(lock_writing);
    unsigned long removedItems = players.erase(session);
    if (removedItems > 0) {
        currentPlayers -= removedItems;
        return true;
    } else return false;
}

//TODO Lock-free
Player *PlayersOnline::getPlayerBySession(const string &session) const {
    lock_guard<mutex> locker(lock_writing);
    auto plr = players.find(session);
    if (plr != players.end()) {
        return plr->second;
    }
    return NULL;
}

//TODO Lock-free
vector<Player *> PlayersOnline::getOnlinePlayers() const {
    lock_guard<mutex> locker(lock_writing);
    vector<Player *> onlinePlayer;
    for (auto i = players.begin(); i != players.end(); i++)
        if (i->second != NULL)
            onlinePlayer.push_back(i->second);
    return onlinePlayer;
}

PlayersOnline::~PlayersOnline() {
    for (auto i = players.begin(); i != players.end(); i++)
        if (i->second != NULL) {
            delete i->second;
            i->second = NULL;
        }
}
