/**
 * @file IEvent.h
 * @author LionZXY
 * @project Recast-server
 * @date 21.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_IEVENT_H
#define RECAST_SERVER_IEVENT_H

#include <boost/log/trivial.hpp>
#include <world/Box2DWorld.h>

class SpellNode;
class SpellEntity;

class IEvent {
public:
    IEvent(SpellNode *node) : fromNode(node) {}

    SpellNode *getNode() const { return fromNode; }

    virtual void commit(Box2DWorld *world, SpellEntity * entity) { BOOST_LOG_TRIVIAL(info) << "Calling event"; }

protected:
    SpellNode *fromNode;
};


#endif //RECAST_SERVER_IEVENT_H
