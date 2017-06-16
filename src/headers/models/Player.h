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
 * @brief Player class.
 *
 * Aka Context for Player only.
 */
class Player {
public:
    Player(Point location) : location(location) {};

private:
    int id;
    Point location;
};


#endif //RECAST_SERVER_PLAYER_H
