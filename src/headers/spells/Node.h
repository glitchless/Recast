/**
 * @file Node.h
 * @author LionZXY
 * @project Recast-server
 * @date 20.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_NODE_H
#define RECAST_SERVER_NODE_H

#include <set>

class Node {
public:
    Node(float x, float y, float z) : x(x), y(y), z(z), nowInTick(false) {}

    virtual bool isEnergyNode() { return false; }

    /**
     * Link node if not already exist
     * The contract involves adding the current node from the calling party
     *
     * @param otherNode
     */
    void connectNode(Node *otherNode);

    void tick(Node *callable);

    bool inTick() const { return nowInTick; }

    float getDistance(const Node *otherNode) const;

protected:
    float x, y, z; //// Relative coordinates from root node
    std::set<Node *> connectedNodes;
    bool nowInTick;


    virtual inline void onTick(Node *callable) {};
};

#endif //RECAST_SERVER_NODE_H
