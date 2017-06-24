//
// Created by Oleg Morozenkov on 24.06.17.
//

#ifndef RECAST_SERVER_EDGE_HPP
#define RECAST_SERVER_EDGE_HPP


/**
 * Represents edges of a cube.
 * When you see a cube from the side of XY plane, `left`, `right`, `up` and `down` are the edges of this plane. `Near` edge is this plane. `Far` is cube edge which is parallel to this plane.
 */
enum class Edge {
    LEFT, RIGHT, UP, DOWN, NEAR, FAR
};


#endif //RECAST_SERVER_EDGE_HPP
