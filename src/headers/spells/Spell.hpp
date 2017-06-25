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
    Spell() : rootNode(new SpellNode(0, 0, 0)) {};

    Spell(SpellNode *rootNode) : rootNode(rootNode) {};

    ~Spell();

    SpellNode *getRootNode() { return rootNode; }

    void tickSpell(SpellEventListener &listener);

private:
    SpellNode *rootNode;
};


#endif //RECAST_SERVER_SPELL_H
