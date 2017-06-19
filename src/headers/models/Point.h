#ifndef RECAST_SERVER_POINT_H
#define RECAST_SERVER_POINT_H

/**
 * @brief Just point
 *
 * It't Point. James Point.
 */
struct Point {
    double x;
    double y;
    double z;

    Point(double x, double y, double z) : x(x), y(y), z(z) {}
};


#endif //RECAST_SERVER_POINT_H
