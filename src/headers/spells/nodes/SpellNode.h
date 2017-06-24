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
#include "spells/events/IEventListener.h"

class SpellNode {
public:
    SpellNode(float x, float y, float z) : x(x), y(y), z(z), nowInTick(false) {}

    ~SpellNode();

    virtual bool isEnergyNode() { return false; }

    /**
     * Link node if not already exist
     * The contract involves adding the current node from the calling party
     *
     * @param otherNode
     */
    void connectNode(SpellNode *otherNode);

    void tick(IEventListener &listener, SpellNode *callable);

    bool inTick() const { return nowInTick; }

    float getDistance(const SpellNode *otherNode) const;

protected:
    float x, y, z; //// Relative coordinates from root node
    std::set<SpellNode *> connectedNodes;
    bool nowInTick;


    virtual inline void onTick(IEventListener &listener, SpellNode *callable) {};
};

#endif //RECAST_SERVER_NODE_H
