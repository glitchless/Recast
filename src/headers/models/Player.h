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

    const double &getPosX() const { return location.x; }
    void setPosX(double x) { location.x = x; }
    const double &getPosY() const { return location.y; }
    void setPosY(double y) { location.y = y; }
    const double &getPosZ() const { return location.z; }
    void setPosZ(double z) { location.z = z; }
    const Point &getPoint() { return location; }
private:
    Point location;
};


#endif //RECAST_SERVER_PLAYER_H
