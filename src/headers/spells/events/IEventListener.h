/**
 * @file IEventListener.h
 * @author LionZXY
 * @project Recast-server
 * @date 21.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_IEVENTLISTENER_H
#define RECAST_SERVER_IEVENTLISTENER_H

#include "IEvent.h"

class IEventListener {
    virtual void onEvent(IEvent event) = 0;
};


#endif //RECAST_SERVER_IEVENTLISTENER_H
