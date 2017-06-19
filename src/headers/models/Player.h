/**
 * @file
 * @brief Player file
 * @author LionZXY
 * @project Recast-server
 * @date 08.06.17
 *
 * Player file
 * 
 **/
#ifndef RECAST_SERVER_PLAYER_H
#define RECAST_SERVER_PLAYER_H

#include "Point.h"

/**
 * @brief Player class. XP, Life points and other
 */
struct Player {
public:
    Player() : location(Point(0, 0, 0)) {};

    Player(Point location) : location(location) {};

    int id;
    int userId;
    Point location;
};


#endif //RECAST_SERVER_PLAYER_H
