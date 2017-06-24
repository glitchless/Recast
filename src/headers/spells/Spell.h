/**
 * @file Spell.h
 * @author LionZXY
 * @project Recast-server
 * @date 21.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_SPELL_H
#define RECAST_SERVER_SPELL_H


#include "spells/nodes/Node.h"
#include "spells/events/SpellEventListener.h"


class Spell {
public:
    Spell() : rootNode(new Node(0, 0, 0)), listener(SpellEventListener(this)) {};

    Spell(Node *rootNode) : rootNode(rootNode), listener(SpellEventListener(this)) {};

    ~Spell();

    Node *getRootNode() { return rootNode; }

    void tickSpell(/*TODO EntityList and Temperature map*/);

private:
    Node *rootNode;
    SpellEventListener listener;
};


#endif //RECAST_SERVER_SPELL_H
