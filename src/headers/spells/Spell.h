/**
 * @file Spell.h
 * @author LionZXY
 * @project Recast-server
 * @date 21.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_SPELL_H
#define RECAST_SERVER_SPELL_H


#include <spells/events/IEventListener.h>
#include <spells/nodes/Node.h>

class Spell {
public:
    Spell() : rootNode(new Node(0, 0, 0)) {};

    Spell(Node *rootNode) : rootNode(rootNode) {};

    ~Spell();

    Node *getRootNode() { return rootNode; }

    void tickSpell(/*TODO EntityList and Temperature map*/);

private:
    Node *rootNode;
};


#endif //RECAST_SERVER_SPELL_H
