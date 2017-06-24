/**
 * @file Spell.h
 * @author LionZXY
 * @project Recast-server
 * @date 21.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_SPELL_H
#define RECAST_SERVER_SPELL_H


#include "spells/nodes/SpellNode.hpp"
#include "spells/events/SpellEventListener.hpp"

class Spell {
public:
    Spell() : rootNode(new SpellNode(0, 0, 0)), listener(SpellEventListener(this)) {};

    Spell(SpellNode *rootNode) : rootNode(rootNode), listener(SpellEventListener(this)) {};

    ~Spell();

    SpellNode *getRootNode() { return rootNode; }

    void tickSpell(/*TODO EntityList and Temperature map*/);

private:
    SpellNode *rootNode;
    SpellEventListener listener;
};


#endif //RECAST_SERVER_SPELL_H
