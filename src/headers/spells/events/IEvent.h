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

class Node;

class IEvent {
public:
    IEvent(Node *node) : fromNode(node) {}

    Node *getNode() const { return fromNode; }

    virtual void commit(/*Temperature and Entity*/) { BOOST_LOG_TRIVIAL(info) << "Calling event"; }

private:
    Node *fromNode;
};


#endif //RECAST_SERVER_IEVENT_H
