/**
 * @file GetEntitys.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 28.06.17
 * @email nikita@kulikof.ru
 **/
#include <world/wrappers/Entity.h>
#include "io/network/listeners/GetEntitys.h"
#include "world/Box2DWorld.h"

GetEntitys::GetEntitys() : NetworkListener(1) {}

float readFloat(char *request, int &curPos) {
    float f;
    memcpy(&f, request + curPos, sizeof(f));
    curPos += sizeof(f);
    return f;
}

using namespace std;

char *GetEntitys::onPacket(char *request, ICommandSender *sender) {
    int curPos = 1;
    float start = readFloat(request, curPos);
    float end = readFloat(request, curPos);
    auto v = sender->getWorld()->getAllEntityInChunk(start, end);
    Parcel answer;
    answer.put((int) v.size());
    for (Entity en : v) {
        Entity::write(answer, &en);
    }
    return (char *) answer.getVector()->data();
}
