#ifndef RECAST_SERVER_POINT_H
#define RECAST_SERVER_POINT_H

/**
 * @brief Just point
 *
 * It't Point. James Point.
 */
struct Point {
    float x;
    float y;
    float z;

    Point(float x, float y, float z) : x(x), y(y), z(z) {}
};


#endif //RECAST_SERVER_POINT_H
