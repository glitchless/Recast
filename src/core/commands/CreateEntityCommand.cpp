/**
 * @file CreateEntityCommand.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 27.06.17
 * @email nikita@kulikof.ru
 **/
#include <world/wrappers/Entity.h>
#include "commands/CreateEntityCommand.h"
#include "Box2D/Box2D.h"
#include "world/Box2DWorld.h"

using namespace std;

bool CreateEntityCommand::isValid(const string &cmd, const vector<string> &args) const {
    return args.size() > 0 && cmd == "create" && args[0] == "entity";
}

void
CreateEntityCommand::onCommand(ICommandSender &sender, const string &cmd, const vector<string> &args) {
    if (args.size() != 3) {
        sender.onMessage("create entity [posX] [posY]");
        return;
    }
    b2BodyDef bodyDef;
    bodyDef.position.Set((float32) atof(args[1].c_str()), (float32) atof(args[2].c_str()));

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    Entity *entity = sender.getWorld()->createEntity(bodyDef, fixtureDef);
    sender.onMessage(string("Created entity. Id:") + to_string(entity->getId()));
}
