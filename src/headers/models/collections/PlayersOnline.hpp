/**
 * @file PlayersOnline.h
 * @brief PlayerOnline class
 * @author LionZXY
 * @project Recast-server
 * @date 16.06.17
 * @email nikita@kulikof.ru
 *
 * Player online thread-safe class
 * 
 **/
#ifndef RECAST_SERVER_PLAYERSONLINE_H
#define RECAST_SERVER_PLAYERSONLINE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <mutex>
#include "io/SQLite.hpp"
#include "models/Player.hpp"
#include "exceptions/ServerFullException.hpp"

const int SESSION_LENGTH = 128; //// Length of session string

class PlayersOnline {
public:
    PlayersOnline(int playerCount) : maxPlayers(playerCount), currentPlayers(0) {};

    ~PlayersOnline();

    std::vector<Player *> getOnlinePlayers() const; //// Return all online players

    Player *getPlayerBySession(const std::string &session) const; //// Return player by session. Thread-safe

    /**
     * Auth player on Server. Get all game data from SQLite
     * On failed auth (if user is not in a table) throw InvalidLoginOrPassword
     * On fulled server (maxPlayers == currentPlayers) throw ServerFullException
     *
     * @warning Can throw exception! Must be in try{}catch{} block
     * @param login user login
     * @param password user password
     * @return session string
     */
    std::string authPlayer(std::string login, std::string password) throw(InvalidLoginOrPassword, ServerFullException);

    /**
     * Register player in SQLite. Can throw InvalidLoginOrPassword when login already exists
     * @param login new login
     * @param password user password
     */
    void registerPlayer(std::string login, std::string password) throw(InvalidLoginOrPassword);

    /**
     * Remove user from user list and save that in SQLite
     *
     * @param session
     * @return
     */
    bool logout(const std::string &session);

    int playersOnline() const { return currentPlayers; }

private:
    std::unordered_map<std::string, Player *> players; //// Hashmap <Session, Player>
    mutable std::mutex lock_writing;
    int maxPlayers;
    volatile int currentPlayers;
    SQLite sqLite;
};


#endif //RECAST_SERVER_PLAYERSONLINE_H
