/**
 * @file PlayersOnline.h
 * @brief PlayerOnline class
 * @author LionZXY
 * @project Recast-server
 * @date 16.06.17
 * @email nikita@kulikof.ru
 *
 * Player online thread-safetly class
 * 
 **/
#ifndef RECAST_SERVER_PLAYERSONLINE_H
#define RECAST_SERVER_PLAYERSONLINE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <mutex>
#include <io/SQLite.h>
#include "models/Player.h"

const int SESSION_LENGTH = 128;

class PlayersOnline {
public:
    PlayersOnline(int playerCount) : maxPlayer(playerCount), currentPlayers(0) {};

    ~PlayersOnline();

    std::vector<Player *> getOnlinePlayers() const;

    Player *getPlayerBySession(const std::string &session) const;

    std::string authPlayer(std::string login, std::string password);

    void registerPlayer(std::string login, std::string password);

    bool logout(const std::string &session);

    int playersOnline() const { return currentPlayers; }

private:
    std::unordered_map<std::string, Player *> players; //// Hashmap <Session, Player>
    mutable std::mutex lock_writing;
    int maxPlayer;
    volatile int currentPlayers;
    SQLite sqLite;
};


#endif //RECAST_SERVER_PLAYERSONLINE_H
