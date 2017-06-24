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

class SpellNode;

class IEvent {
public:
    IEvent(SpellNode *node) : fromNode(node) {}

    SpellNode *getNode() const { return fromNode; }

    virtual void commit(/*Temperature and Entity*/) { BOOST_LOG_TRIVIAL(info) << "Calling event"; }

private:
    SpellNode *fromNode;
};


#endif //RECAST_SERVER_IEVENT_H
