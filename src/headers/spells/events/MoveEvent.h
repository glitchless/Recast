/**
 * @file MoveEvent.h
 * @author LionZXY
 * @project Recast-server
 * @date 25.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_MOVEEVENT_H
#define RECAST_SERVER_MOVEEVENT_H


#include "IEvent.hpp"

class MoveEvent : public IEvent {
public:
    MoveEvent(SpellNode *node, int entityId, float energy) : IEvent(node), entityId(entityId) {}

private:
    int entityId;
};


#endif //RECAST_SERVER_MOVEEVENT_H
